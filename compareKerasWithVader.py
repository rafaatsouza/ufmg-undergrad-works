import numpy as np
import TweetsDataSet as td
import KerasNetwork as kn
import Vader as vd
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
vader = vd.Vader()

del train_size
del test_size
del vector_size
del word2vecIterations
del max_length
del datasetFilePath

scores = {}
scores['Vader'] = vader.getVaderScore(tweetsDataSet.testData)
del tweetsDataSet

print(scores['Vader'])

#scores['Neural'] = kerasModel.getScoreDefaultByEppochs(100)

#ut.Utils.registerToFile('{};{};{}\n'.format(100, 'keras', scores['Neural']), 'csv', 'KerasVaderCompare.csv')
#ut.Utils.registerToFile('{};{};{}\n'.format(100, 'vader', scores['Vader']), 'csv', 'KerasVaderCompare.csv')