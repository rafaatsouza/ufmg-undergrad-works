import numpy as np
import multiprocessing
import tensorflow as tf
import keras.backend as K

from sklearn.metrics import confusion_matrix
from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Flatten
from keras.layers.convolutional import Conv1D
from keras.optimizers import Adam

from Word2VecModel import Word2VecModel as w2c

class KerasNetwork:
    def __init__(self, max_length, vector_size, train_size, test_size, word2vecIterations, tweetsDataSet):
        config = tf.ConfigProto(intra_op_parallelism_threads=multiprocessing.cpu_count(), 
                        inter_op_parallelism_threads=multiprocessing.cpu_count(), 
                        allow_soft_placement=True, device_count = {'CPU' : 1, 'GPU' : 1})

        self.train_size = train_size
        self.test_size = test_size
        self.max_length = max_length
        self.vector_size = vector_size

        session = tf.Session(config=config)
        K.set_session(session)
        
        self.GeneratesTrainTestData(word2vecIterations, tweetsDataSet)

    def GeneratesTrainTestData(self, word2vecIterations, tweetsDataSet):
        word2vec = w2c.getWord2VecModel('model/{}-{}/word2vec.model'.format(word2vecIterations, self.vector_size), 
                                        self.vector_size, tweetsDataSet.tokenized_corpus, 
                                        word2vecIterations)

        tweets_word2vec = word2vec.wv
        del word2vec

        indexes = set(np.random.choice(len(tweetsDataSet.tokenized_corpus), self.train_size + self.test_size, replace=False))

        self.trainData = np.zeros((self.train_size, self.max_length, self.vector_size), dtype=K.floatx())
        self.trainClassData = np.zeros((self.train_size, 2), dtype=np.int32)
        self.testData = np.zeros((self.test_size, self.max_length, self.vector_size), dtype=K.floatx())
        self.testClassData = np.zeros((self.test_size, 2), dtype=np.int32)

        for i, index in enumerate(indexes):
            for t, token in enumerate(tweetsDataSet.tokenized_corpus[index]):
                if t >= self.max_length:
                    break

                if token not in tweets_word2vec:
                    continue

                if i < self.train_size:
                    self.trainData[i, t, :] = tweets_word2vec[token][:self.vector_size]
                else:
                    self.testData[i - self.train_size, t, :] = tweets_word2vec[token][:self.vector_size]

            if i < self.train_size:
                self.trainClassData[i, :] = [0.0, 1.0] if tweetsDataSet.labels[index] == 0 else [1.0, 0.0]
            else:
                self.testClassData[i - self.train_size, :] = [0.0, 1.0] if tweetsDataSet.labels[index] == 0 else [1.0, 0.0]

        del indexes
        del tweets_word2vec

    def GetModel(self):
        model = Sequential()

        model.add(Conv1D(32, kernel_size=3, activation='elu', padding='same', \
                                    input_shape=(self.max_length, self.vector_size)))
        model.add(Conv1D(32, kernel_size=3, activation='elu', padding='same'))
        model.add(Conv1D(32, kernel_size=3, activation='elu', padding='same'))
        model.add(Conv1D(32, kernel_size=3, activation='elu', padding='same'))
        model.add(Dropout(0.25))

        model.add(Conv1D(32, kernel_size=2, activation='elu', padding='same'))
        model.add(Conv1D(32, kernel_size=2, activation='elu', padding='same'))
        model.add(Conv1D(32, kernel_size=2, activation='elu', padding='same'))
        model.add(Conv1D(32, kernel_size=2, activation='elu', padding='same'))
        model.add(Dropout(0.25))

        model.add(Flatten())

        model.add(Dense(256, activation='tanh'))
        model.add(Dense(256, activation='tanh'))
        model.add(Dropout(0.5))

        model.add(Dense(2, activation='softmax'))

        model.compile(loss='binary_crossentropy', optimizer=Adam(lr=0.0001, decay=1e-6), metrics=['accuracy'])

        return model

    def getScoreDefaultByEppochs(self, countEppochs):
        self.model = self.GetModel()
        
        self.model.fit(self.trainData,self.trainClassData,
                batch_size=len(self.trainData),
                shuffle=True,
                epochs=countEppochs, 
                validation_split=0.2,verbose=0)

        score = (self.model.evaluate(self.testData,self.testClassData,batch_size=len(self.testData),verbose=0))[1]

        del self.model

        return score

    def getScoresByEppochCountAndBatchs(self, countEppochs):
        accuracies = {}

        trintaDois = self.GetModel()
        trintaDois.fit(self.trainData,self.trainClassData, shuffle=True, epochs=countEppochs, validation_split=0.2,verbose=0)
        accuracies['trintaDois'] = (trintaDois.evaluate(self.testData,self.testClassData,batch_size=len(self.testData),verbose=0))[1]
        del trintaDois

        trainDataSize = self.GetModel()
        trainDataSize.fit(self.trainData,self.trainClassData, batch_size=len(self.trainData), shuffle=True, epochs=countEppochs, validation_split=0.2,verbose=0)
        accuracies['trainDataSize'] = (trainDataSize.evaluate(self.testData,self.testClassData,batch_size=len(self.testData),verbose=0))[1]
        del trainDataSize

        return accuracies