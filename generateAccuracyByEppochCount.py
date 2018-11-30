import numpy as np
import TweetsDataSet as td
import KerasNetwork as kn
import numpy as np
import Utils as ut
        
train_size = 21000
test_size = 9000
vector_size = 512
word2vecIterations = 50
max_length = 18
datasetFilePath = 'dataset/emotions_tweets.csv'

np.random.seed(1000)

print('Iniciando')

tweetsDataSet = td.TweetsDataSet(datasetFilePath, (train_size + test_size), train_size)
kerasModel = kn.KerasNetwork(max_length, vector_size, train_size, test_size, word2vecIterations, tweetsDataSet)

del train_size
del test_size
del vector_size
del word2vecIterations
del max_length
del datasetFilePath
del tweetsDataSet

for i in range(1,16):
    print('Teste com {} épocas'.format((i * 10)))
    kerasModel.TrainModel((i * 10))
    scores = kerasModel.getScores()
    print('Neural Accurracy: {}'.format(scores[1]))
    ut.Utils.registerToFile('{};{}\n'.format((i * 10), scores[1]), 'csv', 'accuracyByEppochCount.csv')
    del kerasModel.model
    del kerasModel.KerasPredict