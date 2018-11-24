import numpy as np
import VectorizedData as vd
from keras import initializers
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM

class KerasNetwork:
    def __init__(self, trainFileName, testFileName, windowSize):
        self.trainFileName = trainFileName
        self.testFileName = testFileName
        self.windowSize = windowSize
        self.trainModel()

    def trainModel(self):
        trainData = vd.VectorizedData(self.trainFileName).getVectorizedData()
        knownTrainData = []
        predictedTrainData = []

        for index in range(len(trainData) - self.windowSize):
            knownTrainData.append(trainData[index:(index+self.windowSize)])
            predictedTrainData.append(trainData[(index+self.windowSize)])
            
        del trainData
        knownTrainData = np.array(knownTrainData)
        predictedTrainData = np.array(predictedTrainData)

        self.model = Sequential()
        self.model.add(LSTM(50,input_shape=(self.windowSize,26)))
        self.model.add(Dense(25,activation='relu'))
        self.model.add(Dense(26, activation='sigmoid'))
        self.model.compile(loss='binary_crossentropy',optimizer ='adam',metrics=['accuracy'])
        self.model.fit(knownTrainData,predictedTrainData,epochs=2, batch_size=20,validation_split=0.2,verbose=0)

        del knownTrainData
        del predictedTrainData

    def evaluateModel(self):
        testVectorizedData = vd.VectorizedData(self.testFileName)
        testData = testVectorizedData.getVectorizedData()
        knownTestDataByClass = {}
        predictedTestDataByClass = {}
        knownTestData = []
        predictedTestData = []

        for index in range(len(testData) - self.windowSize):
            dictIndex = testVectorizedData.getFeatureNameByOneHot(testData[(index+self.windowSize)])
            if dictIndex not in knownTestDataByClass:
                knownTestDataByClass[dictIndex] = []       
            if dictIndex not in predictedTestDataByClass:
                predictedTestDataByClass[dictIndex] = []        
            knownTestDataByClass[dictIndex].append(testData[index:(index+self.windowSize)])
            predictedTestDataByClass[dictIndex].append(testData[(index+self.windowSize)])
            knownTestData.append(testData[index:(index+self.windowSize)])
            predictedTestData.append(testData[(index+self.windowSize)])

        for key in knownTestDataByClass:
            knownTestDataByClass[key] = np.array(knownTestDataByClass[key])
        for key in predictedTestDataByClass:
            predictedTestDataByClass[key] = np.array(predictedTestDataByClass[key])
        knownTestData = np.array(knownTestData)
        predictedTestData = np.array(predictedTestData)

        del testVectorizedData
        del testData

        scores = {}
        for key in knownTestDataByClass:
            scores[key] = ((self.model.evaluate(knownTestDataByClass[key],predictedTestDataByClass[key],batch_size=20,verbose=0))[1])
        del knownTestDataByClass
        del predictedTestDataByClass

        self.allModelEvaluate = ((self.model.evaluate(knownTestData,predictedTestData,batch_size=20,verbose=0))[1])

        del knownTestData
        del predictedTestData

        return scores
