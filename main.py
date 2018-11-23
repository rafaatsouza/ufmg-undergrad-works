import numpy as np
from keras import initializers
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import OneHotEncoder
from sklearn.feature_extraction.text import CountVectorizer


np.random.seed(1000)

file = open('dataset/cleanedFiles/train.txt', 'r')
trainFileCorpus = [word for line in file for word in line.split()]
del file

vectorizer = CountVectorizer(lowercase=False, token_pattern='[A-Z;+;-]+')
trainData = vectorizer.fit_transform(trainFileCorpus)
print(trainData.toarray())