import numpy as np
import pandas as pd
from sklearn.model_selection import cross_val_score
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import GridSearchCV
from sklearn import tree
from sklearn.metrics import confusion_matrix
import warnings

warnings.simplefilter(action='ignore', category=FutureWarning)
np.random.seed(1000)
testSize = 0.7
folds = 5

class DataSet:
    def __init__(self, dataSet, ignoreColumns, testSize):
        self.labels = {'full': None, 'train': None, 'test': None}
        self.examples = {'full': None, 'train': None, 'test': None}

        self.examples['full'] = (pd.read_csv(dataSet)).drop(columns=ignoreColumns)
        self.labels['full'] = (self.examples['full']['koi_disposition']).replace(['FALSE POSITIVE', 'CONFIRMED'], [0,1])
        self.examples['full'] = self.examples['full'].drop(columns=['koi_disposition'])
        
        msk = np.random.rand(len(self.examples['full'])) < testSize
        self.examples['train'] = self.examples['full'][msk]
        self.examples['test'] = self.examples['full'][~msk]
        self.labels['train'] = self.labels['full'][msk]
        self.labels['test'] = self.labels['full'][~msk]
        
def naiveBayes(df, output, folds):
    model = GaussianNB()
    return cross_val_score(model, df, output, cv=folds)

def decisionTree(df, output, trainExamples, trainLabels, maxDepth, folds):
    parameters = {'max_depth':maxDepth}
    
    model = GridSearchCV(tree.DecisionTreeClassifier(), parameters)
    model = model.fit(trainExamples, trainLabels)

    return cross_val_score(model, df, output, cv=folds)

ds = DataSet('dataset.csv', ['kepoi_name'], testSize)

naiveBayesScore = naiveBayes(ds.examples['full'], ds.labels['full'], folds)
naiveBayesScore

decisionTreeScore = decisionTree(ds.examples['full'], ds.labels['full'], ds.examples['train'], 
                                 ds.labels['train'], range(3,20), folds)
decisionTreeScore