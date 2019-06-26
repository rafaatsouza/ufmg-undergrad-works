from keras.models import Sequential
from keras.layers import Convolution2D, MaxPooling2D, Flatten, Dense, Dropout
from sklearn import metrics
import numpy as np
import os

class Classifier:
    def __init__(self, batchSize):
        self.batchSize = batchSize

    def fitAugGenerator(self, eppochs, folds):
        os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

        clf = self.InitAugClassifier()

        k_train_accuracy = []
        k_train_loss = []
        k_test_loss = []
        k_test_accuracy = []

        for fold in folds:
            score = clf.fit_generator(
                        fold['trainDataAug'], 
                        steps_per_epoch=(fold['trainSize']/self.batchSize),
                        validation_steps=(fold['trainSize']/self.batchSize),
                        validation_data=fold['testDataAug'], epochs=eppochs, verbose=0)
            k_train_accuracy.append(score.history['acc'][0])
            k_train_loss.append(score.history['loss'][0])
            
            augEvaluate = clf.evaluate_generator(
                        fold['validationDataAug'],
                        steps=(fold['trainSize']/self.batchSize),
                        verbose=0)

            k_test_loss.append(augEvaluate[0])
            k_test_accuracy.append(augEvaluate[1])

            del score
            del augEvaluate

        del clf

        result = {'train_loss': (np.array([loss for loss in k_train_loss])).mean(), 
                  'train_accuracy': (np.array([accuracy for accuracy in k_train_accuracy])).mean(),
                  'test_loss': (np.array([accuracy for accuracy in k_test_loss])).mean(),
                  'test_accuracy': (np.array([accuracy for accuracy in k_test_accuracy])).mean() }

        del k_train_accuracy
        del k_train_loss
        del k_test_loss
        del k_test_accuracy

        return result

    def InitAugClassifier(self):
        clf = Sequential()
        clf.add(Convolution2D(32, (3, 3), input_shape = (64, 64, 3), activation = 'relu'))
        clf.add(MaxPooling2D(pool_size = (2, 2)))
        clf.add(Convolution2D(32, (3, 3), activation = 'relu'))
        clf.add(MaxPooling2D(pool_size = (2, 2)))
        clf.add(Flatten())
        clf.add(Dense(128, kernel_initializer ='uniform', activation = 'relu'))
        clf.add(Dense(1, kernel_initializer ='uniform', activation = 'sigmoid'))
        clf.compile(optimizer = 'adam', loss = 'binary_crossentropy', metrics = ['accuracy'])
        return clf