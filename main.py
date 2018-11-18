import numpy as np
import multiprocessing
import keras.backend as K
import TweetsDataSet as td
import KerasNetwork as kn
from Word2VecModel import Word2VecModel as w2c

train_size = 21000
test_size = 9000
vector_size = 512
word2vecIterations = 50
max_length = 18

np.random.seed(1000)

tweetsDataSet = td.TweetsDataSet('dataset/emotions_tweets.csv', train_size + test_size)
word2vec = w2c.getWord2VecModel('model/{}-{}/word2vec.model'.format(word2vecIterations, vector_size), 
                                vector_size, tweetsDataSet.tokenized_corpus, 
                                word2vecIterations)

tweets_word2vec = word2vec.wv
del word2vec

indexes = set(np.random.choice(len(tweetsDataSet.tokenized_corpus), train_size + test_size, replace=False))

tweets_treino = np.zeros((train_size, max_length, vector_size), dtype=K.floatx())
classes_treino = np.zeros((train_size, 2), dtype=np.int32)
tweets_test = np.zeros((test_size, max_length, vector_size), dtype=K.floatx())
classes_test = np.zeros((test_size, 2), dtype=np.int32)

for i, index in enumerate(indexes):
    for t, token in enumerate(tweetsDataSet.tokenized_corpus[index]):
        if t >= max_length:
            break

        if token not in tweets_word2vec:
            continue

        if i < train_size:
            tweets_treino[i, t, :] = tweets_word2vec[token][:vector_size]
        else:
            tweets_test[i - train_size, t, :] = tweets_word2vec[token][:vector_size]

    if i < train_size:
        classes_treino[i, :] = [0.0, 1.0] if tweetsDataSet.labels[index] == 0 else [1.0, 0.0]
    else:
        classes_test[i - train_size, :] = [0.0, 1.0] if tweetsDataSet.labels[index] == 0 else [1.0, 0.0]

del indexes
del train_size
del test_size
del tweetsDataSet
del tweets_word2vec

model = kn.KerasNetwork(max_length, vector_size, tweets_treino, classes_treino)

del vector_size
del max_length

scores = model.getScores(tweets_test, classes_test)
print('Accurracy: {}'.format(scores[1]))