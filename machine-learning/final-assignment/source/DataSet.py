import os
import numpy as np
import pandas as pd
from sklearn.utils import shuffle
from keras.preprocessing.image import ImageDataGenerator

class DataSet:
    def __init__(self, spamFolderPath, notSpamFolderPath, notSpamProportion):
        self.df = shuffle(self.GetDataFrame(spamFolderPath, notSpamFolderPath, notSpamProportion))
        
    def GetDataFrame(self, spamFolderPath, notSpamFolderPath, notSpamProportion):
        data = []
        spamCount = 0
        notSpamCount = 0
        for filename in os.listdir(spamFolderPath):
            data.append(['{}{}'.format(spamFolderPath,filename), '1'])
            spamCount += 1
        for filename in os.listdir(notSpamFolderPath):
            if(notSpamCount >= (spamCount * notSpamProportion)):
                break
            data.append(['{}{}'.format(notSpamFolderPath,filename), '0'])
            notSpamCount += 1
        print('Dataframe filled with {} images labelled as "not_spam" and {} images labelled "spam"'.format(notSpamCount, spamCount))
        return pd.DataFrame(data, columns = ['id', 'label'])

    def GetAugFolds(self, batchSize, foldsCount):
        folds = self.GetEqualDataFrameFolds(self.df, foldsCount)

        train_datagen = ImageDataGenerator(rescale=1./255, 
                        shear_range=0.2, 
                        zoom_range=0.2, 
                        fill_mode='reflect',
                        horizontal_flip=True)
        
        test_datagen = ImageDataGenerator(rescale=1./255)
        validation_datagen = ImageDataGenerator(rescale=1./255)

        kfolds = []
        for i in range(0, foldsCount):
            kfolds.append({ 'trainSize': 0, 'trainDataAug': None, 'testDataAug': None, 'validationDataAug': None })

            trainDf = None
            testDf = None
            validationDf = folds[i]

            for j in [x for x in range(0, foldsCount) if x!=i]:
                if(trainDf is None):
                    trainDf = folds[j]
                else:
                    trainDf = trainDf.append(folds[j])

            trainFolds = self.GetEqualDataFrameFolds(trainDf, foldsCount)
            
            trainDf = None
            testDf = trainFolds[0]
            for x in range(1, len(trainFolds)):
                if(trainDf is None):
                    trainDf = trainFolds[x]
                else:
                    trainDf = trainDf.append(trainFolds[x])

            kfolds[i]['trainDataAug'] = train_datagen.flow_from_dataframe(
                                                trainDf, x_col='id', y_col='label', target_size=(64, 64), 
                                                batch_size=batchSize, class_mode='binary')

            kfolds[i]['testDataAug'] = validation_datagen.flow_from_dataframe(
                                                testDf, x_col='id', y_col='label', target_size=(64, 64), 
                                                batch_size=batchSize, class_mode='binary')

            kfolds[i]['validationDataAug'] = test_datagen.flow_from_dataframe(
                                                validationDf, x_col='id', y_col='label', target_size=(64, 64), 
                                                batch_size=batchSize, class_mode='binary')

            kfolds[i]['trainSize'] = len(trainDf)
            
            del trainDf
            del testDf
            del validationDf

        del folds
        del train_datagen
        del test_datagen
        del validation_datagen

        return kfolds

    def GetEqualDataFrameFolds(self, df, foldsCount):
        foldSize = round(df.shape[0] / foldsCount)
        folds = [df[x:x+foldSize] for x in range(0, df.shape[0], foldSize)]
        if(len(folds) > foldsCount):
            lastPart = folds.pop()
            folds[foldSize-1] = folds[foldSize-1].append(lastPart)
            del lastPart
        del foldSize
        return folds