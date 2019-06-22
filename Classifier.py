from keras.models import Sequential
from keras.layers import Convolution2D
from keras.layers import MaxPooling2D
from keras.layers import Flatten
from keras.layers import Dense

import DataSet as ds
import numpy as np
import os

class Classifier:
    def __init__(self, spamFolderPath, notSpamFolderPath, batchSize, foldsCount):
        self.batchSize = batchSize
        self.foldsCount = foldsCount

        self.ds = ds.DataSet(spamFolderPath, notSpamFolderPath, self.batchSize, self.foldsCount)

        self.classifier = Sequential()
        self.classifier.add(Convolution2D(32, (3, 3), input_shape = (64, 64, 3), activation = 'relu'))
        self.classifier.add(MaxPooling2D(pool_size = (2, 2)))
        self.classifier.add(Convolution2D(32, (3, 3), activation = 'relu'))
        self.classifier.add(MaxPooling2D(pool_size = (2, 2)))
        self.classifier.add(Flatten())
        self.classifier.add(Dense(128, kernel_initializer ='uniform', activation = 'relu'))
        self.classifier.add(Dense(1, kernel_initializer ='uniform', activation = 'sigmoid'))

        self.classifier.compile(optimizer = 'adam', loss = 'binary_crossentropy', metrics = ['accuracy'])

    def fitGenerator(self, eppochs):
        os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
        k_accuracy = []
        k_loss = []
        for i in range(0, self.foldsCount):
            score = self.classifier.fit_generator(
                        self.ds.kfolds[i]['trainDataAug'], 
                        steps_per_epoch=(len(self.ds.kfolds[i]['trainDataAug'])/self.batchSize), 
                        validation_steps=(len(self.ds.kfolds[i]['trainDataAug'])/self.batchSize),
                        validation_data=self.ds.kfolds[i]['testDataAug'], epochs=eppochs, verbose=0)
            k_accuracy.append(score.history['acc'][0])
            k_loss.append(score.history['loss'][0])
        return {'loss': (np.array([loss for loss in k_loss])).mean(), 'accuracy': (np.array([accuracy for accuracy in k_accuracy])).mean() }