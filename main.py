import numpy as np
from keras import initializers
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import OneHotEncoder
from VectorizedData import VectorizedData as vd

np.random.seed(1000)
trainData = (vd.getVectorizedData('dataset/macmorpho/macmorpho-train.txt')).toarray()
testData = (vd.getVectorizedData('dataset/macmorpho/macmorpho-test.txt')).toarray()

n = 10

knownTrainData = []
predictedTrainData = []
knownTestData = []
predictedTestData = []

for index in range(len(trainData) - n):
    knownTrainData.append(trainData[index:(index+n)])
    predictedTrainData.append(trainData[(index+n)])
    
knownTrainData = np.array(knownTrainData)
predictedTrainData = np.array(predictedTrainData)

for index in range(len(testData) - n):
    knownTestData.append(testData[index:(index+n)])
    predictedTestData.append(testData[(index+n)])
    
knownTestData = np.array(knownTestData)
predictedTestData = np.array(predictedTestData)

del trainData
del testData

model = Sequential()
model.add(LSTM(50,input_shape=(n,26)))
model.add(Dense(25,activation='relu'))
model.add(Dense(26, activation='sigmoid'))
model.compile(loss='binary_crossentropy',optimizer ='adam',metrics=['accuracy'])

model.fit(knownTrainData,predictedTrainData,epochs=2, batch_size=20,validation_split=0.2,verbose=1)

del knownTrainData
del predictedTrainData

score = model.evaluate(knownTestData,predictedTestData,batch_size=20,verbose=0)
print('Accurracy: {}'.format(score[1]))