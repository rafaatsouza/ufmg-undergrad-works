import os
import pandas as pd
from sklearn.utils import shuffle
from keras.preprocessing.image import ImageDataGenerator

class DataSet:
    def __init__(self, spamFolderPath, notSpamFolderPath, batchSize, foldsCount):
        df = shuffle(self.GetDataFrame(spamFolderPath, notSpamFolderPath))

        foldSize = round(df.shape[0] / foldsCount)
        folds = [df[x:x+foldSize] for x in range(0, len(df), foldSize)]
        if(len(folds) > foldsCount):
            lastFold = folds.pop()
            folds[foldSize-1] = folds[foldSize-1].append(lastFold)
            del lastFold

        train_datagen = ImageDataGenerator(rescale=1./255, 
                        shear_range=0.2, 
                        zoom_range=0.2, 
                        fill_mode='reflect',
                        horizontal_flip=True)
        
        test_datagen = ImageDataGenerator(rescale=1./255)

        self.kfolds = []
        for i in range(0, foldsCount):
            self.kfolds.append({ 'trainDataAug': None, 'testDataAug': None })

            testDf = folds[i]
            trainDf = None

            for j in [x for x in range(0, foldsCount) if x!=i]:
                if(trainDf is None):
                    trainDf = folds[j]
                else:
                    trainDf = trainDf.append(folds[j])

            self.kfolds[i]['trainDataAug'] = train_datagen.flow_from_dataframe(
                                                trainDf, x_col='id', y_col='label', 
                                                target_size=(64, 64), batch_size=batchSize,
                                                class_mode='binary')
            
            self.kfolds[i]['testDataAug'] = test_datagen.flow_from_dataframe(
                                                testDf, x_col='id', y_col='label', 
                                                target_size=(64, 64), batch_size=batchSize,
                                                class_mode='binary')
            
            del trainDf
            del testDf

        del df
        del foldSize
        del folds
        del train_datagen
        del test_datagen

    def GetDataFrame(self, spamFolderPath, notSpamFolderPath):
        data = []

        for filename in os.listdir(spamFolderPath):
            data.append(['{}{}'.format(spamFolderPath,filename), '1'])

        for filename in os.listdir(notSpamFolderPath):
            data.append(['{}{}'.format(notSpamFolderPath,filename), '0'])

        return pd.DataFrame(data, columns = ['id', 'label'])