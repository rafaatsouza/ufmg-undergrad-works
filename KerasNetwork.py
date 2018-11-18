import multiprocessing
import tensorflow as tf
import keras.backend as K
from keras.callbacks import EarlyStopping
from keras.models import Sequential
from keras.layers.core import Dense, Dropout, Flatten
from keras.layers.convolutional import Conv1D
from keras.optimizers import Adam

class KerasNetwork:
    def __init__(self, max_length, vector_size, tweets_treino, classes_treino):
        config = tf.ConfigProto(intra_op_parallelism_threads=multiprocessing.cpu_count(), 
                        inter_op_parallelism_threads=multiprocessing.cpu_count(), 
                        allow_soft_placement=True, device_count = {'CPU' : 1, 'GPU' : 1})

        session = tf.Session(config=config)
        K.set_session(session)
        self.run(max_length, vector_size, tweets_treino, classes_treino)

    def run(self, max_length, vector_size, tweets_treino, classes_treino):
        self.model = Sequential()

        self.model.add(Conv1D(32, kernel_size=3, activation='elu', padding='same', input_shape=(max_length, vector_size)))
        self.model.add(Conv1D(32, kernel_size=3, activation='elu', padding='same'))
        self.model.add(Conv1D(32, kernel_size=3, activation='elu', padding='same'))
        self.model.add(Conv1D(32, kernel_size=3, activation='elu', padding='same'))
        self.model.add(Dropout(0.25))

        self.model.add(Conv1D(32, kernel_size=2, activation='elu', padding='same'))
        self.model.add(Conv1D(32, kernel_size=2, activation='elu', padding='same'))
        self.model.add(Conv1D(32, kernel_size=2, activation='elu', padding='same'))
        self.model.add(Conv1D(32, kernel_size=2, activation='elu', padding='same'))
        self.model.add(Dropout(0.25))

        self.model.add(Flatten())

        self.model.add(Dense(256, activation='tanh'))
        self.model.add(Dense(256, activation='tanh'))
        self.model.add(Dropout(0.5))

        self.model.add(Dense(2, activation='softmax'))

        self.model.compile(loss='categorical_crossentropy',
              optimizer=Adam(lr=0.0001, decay=1e-6),
              metrics=['accuracy'])
#           callbacks=[EarlyStopping(min_delta=0.00001, patience=2)])

        self.model.fit(tweets_treino,classes_treino,
                batch_size=len(tweets_treino),
                shuffle=True,
                epochs=100, 
                validation_split=0.2,verbose=0)

    def getScores(self, tweets_test, classes_test):
        return self.model.evaluate(tweets_test,classes_test,batch_size=len(tweets_test),verbose=0)

