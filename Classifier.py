from keras.models import Sequential
from keras.layers import Convolution2D
from keras.layers import MaxPooling2D
from keras.layers import Flatten
from keras.layers import Dense

import DataSet as ds
import os

class Classifier:
    def __init__(self, trainFolderPath, testFolderPath, batchSize):
        self.batchSize = batchSize
        self.ds = ds.DataSet('dataset/train','dataset/test',self.batchSize)

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
        score = self.classifier.fit_generator(
                self.ds.training_set, 
                steps_per_epoch=(self.ds.train_num_samples/self.batchSize), 
                validation_steps=(self.ds.train_num_samples/self.batchSize),
                validation_data=self.ds.test_set, epochs=eppochs, verbose=0)
        result = {'loss': score.history['loss'][0], 'accuracy': score.history['acc'][0] }
        del score
        return result
