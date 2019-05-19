import numpy as np
import pandas as pd
import seaborn as sns
from sklearn import metrics
import matplotlib.pyplot as plt
from matplotlib import gridspec
from sklearn.utils import shuffle
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import cross_val_score
from sklearn import svm, tree, ensemble, neighbors, preprocessing

DATASET_NAME = 'dataset.csv'
TEST_SIZE = 0.7
FOLDS_COUNT = 5
MAX_DEPTH = 15
np.random.seed(1000)

class DataSet:
    def __init__(self, ignoreColumns):
        self.df = (pd.read_csv(DATASET_NAME)).drop(columns=ignoreColumns)
        
        self.target = (self.df['koi_disposition'] == 'CONFIRMED').astype(int)
        self.df = self.df.drop(columns=['koi_disposition'])
        
        self.features = self.df.shape[1]
                
        self.df = pd.DataFrame(preprocessing.MinMaxScaler().fit_transform(self.df.values))
        
        msk = np.random.rand(len(self.df)) < TEST_SIZE
        self.trainDf = self.df[msk]
        self.trainTarget = self.target[msk]
        
def naiveBayesClassifier(df, output):
    return (cross_val_score(GaussianNB(), df, output, cv=FOLDS_COUNT)).mean()

def decisionTreeClassifier(df, output, maxDepth):
    clf = tree.DecisionTreeClassifier(max_depth=maxDepth)
    return (cross_val_score(clf, df, output, cv=FOLDS_COUNT)).mean()
    
def randomForestClassifier(df, output, trainExamples, trainLabels, features, maxDepth):
    clf = ensemble.RandomForestClassifier(n_estimators=features, max_depth=maxDepth)
    clf = clf.fit(trainExamples, trainLabels)
    return (cross_val_score(clf, df, output, cv=FOLDS_COUNT)).mean()

def adaboostClassifier(df, output, trainExamples, trainLabels, estimatorsCount):
    clf = ensemble.AdaBoostClassifier(n_estimators=estimatorsCount)
    clf = clf.fit(trainExamples, trainLabels)
    return (cross_val_score(clf, df, output, cv=FOLDS_COUNT)).mean()

def knnClassifier(df, output, trainExamples, trainLabels, k):
    clf = (neighbors.KNeighborsClassifier(n_neighbors=k)).fit(trainExamples, trainLabels)
    return (cross_val_score(clf, df, output, cv=FOLDS_COUNT)).mean()
    
def svmLinearClassifier(df, output, trainExamples, trainLabels, C):
    clf = (svm.SVC(C, kernel='linear', gamma='auto')).fit(trainExamples, trainLabels)
    return (cross_val_score(clf, df, output, cv=FOLDS_COUNT)).mean()

def svmRbfClassifier(df, output, trainExamples, trainLabels, C):
    clf = (svm.SVC(C, kernel='rbf', gamma='auto')).fit(trainExamples, trainLabels)
    return (cross_val_score(clf, df, output, cv=FOLDS_COUNT)).mean()

def svmSigmoidClassifier(df, output, trainExamples, trainLabels, C):
    clf = (svm.SVC(C, kernel='sigmoid', gamma='auto')).fit(trainExamples, trainLabels)
    return (cross_val_score(clf, df, output, cv=FOLDS_COUNT)).mean()

def svmPolyClassifier(df, output, trainExamples, trainLabels, C):
    clf = (svm.SVC(C, kernel='poly', gamma='auto')).fit(trainExamples, trainLabels)
    return (cross_val_score(clf, df, output, cv=FOLDS_COUNT)).mean()

def showDecisionTreeStats(maxDepth):
    decisionTreeScores = [0]
    for i in range(1,maxDepth+1):
        decisionTreeScores.append(decisionTreeClassifier(ds.df, ds.target, i))

    gs = gridspec.GridSpec(1, 1, figure=plt.figure(num=None, figsize=(8, 5)))
    ax = plt.subplot(gs[0])
    ax.title.set_text('Acurácia de acordo com o aumento da altura da arvore')
    ax.grid(True)
    ax.set_xlabel('Altura')
    ax.set_ylabel('Acurácia')
    ax.set_xlim([1, maxDepth])
    ax.set_ylim([0.7, 1])
    ax.plot(np.array([score for score in decisionTreeScores]), label="Decision Tree")
    ax.plot(np.array([naiveBayesMeanScore for i in range(0, len(decisionTreeScores))]), label="Naive Bayes")
    ax.legend()
    plt.show()
    
def showRandomForestStats(maxDepth):
    randomForestUnlimtdDepthScores = [0]
    for i in range(1,ds.features + 1):
        randomForestUnlimtdDepthScores.append(randomForestClassifier(ds.df, ds.target, ds.trainDf, ds.trainTarget, i, None))

    randomForestDepthByFeaturesScores = {}
    for i in range(1, maxDepth + 1):
        randomForestDepthByFeaturesScores[i] = [0]
        for j in range(1, ds.features + 1):
            randomForestDepthByFeaturesScores[i].append(randomForestClassifier(ds.df, ds.target, ds.trainDf, ds.trainTarget, j, i))

    gs = gridspec.GridSpec(4, 1, figure=plt.figure(num=None, figsize=(16, 22)), height_ratios=[3,8,8,8])
    ax1 = plt.subplot(gs[0])
    ax1.title.set_text('Acurácia com altura ilimitada x aumento de features')
    ax1.set_xlabel('Features')
    ax1.set_ylabel('Acurácia')
    ax1.set_xlim([1, ds.features])
    ax1.set_yticks([0.91, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98])
    ax1.set_ylim([0.91, 0.98])
    ax1.plot(np.array([score for score in randomForestUnlimtdDepthScores]), label="Random Forest")
    ax1.plot(np.array([naiveBayesMeanScore for i in range(0, len(randomForestUnlimtdDepthScores))]), label="Naive Bayes")
    ax1.legend()
    ax1.grid(True)

    ax2 = plt.subplot(gs[1])
    ax2.title.set_text('Acurácia da altura (de 1 a 5) x aumento de features')
    ax2.set_xlabel('Features')
    ax2.set_ylabel('Acurácia')
    ax2.set_xlim([1, ds.features])
    ax2.set_ylim([0.67, 0.98])
    for j in range(1, 6):
        ax2.plot(np.array([score for score in randomForestDepthByFeaturesScores[j]]), label="RF Depth={}".format(j))
    ax2.plot(np.array([naiveBayesMeanScore for j in range(0, len(randomForestUnlimtdDepthScores))]), label="Naive Bayes")
    ax2.legend()
    ax2.grid(True)

    ax3 = plt.subplot(gs[2])
    ax3.title.set_text('Acurácia da altura (de 6 a 10) x aumento de features')
    ax3.set_xlabel('Features')
    ax3.set_ylabel('Acurácia')
    ax3.set_xlim([1, ds.features])
    ax3.set_ylim([0.905, 0.97])
    for j in range(6, 11):
        ax3.plot(np.array([score for score in randomForestDepthByFeaturesScores[j]]), label="RF Depth={}".format(j))
    ax3.plot(np.array([naiveBayesMeanScore for j in range(0, len(randomForestUnlimtdDepthScores))]), label="Naive Bayes")
    ax3.legend()
    ax3.grid(True)

    ax4 = plt.subplot(gs[3])
    ax4.title.set_text('Acurácia da altura (de 11 a 15) x aumento de features')
    ax4.set_xlabel('Features')
    ax4.set_ylabel('Acurácia')
    ax4.set_xlim([1, ds.features])
    ax4.set_ylim([0.91, 0.97])
    for j in range(11, 15):
        ax4.plot(np.array([score for score in randomForestDepthByFeaturesScores[j]]), label="RF Depth={}".format(j))
    ax4.plot(np.array([naiveBayesMeanScore for j in range(0, len(randomForestUnlimtdDepthScores))]), label="Naive Bayes")
    ax4.legend()
    ax4.grid(True)

    plt.subplots_adjust(hspace=0.25)
    plt.show()
    
def showAdaboostStats():
    adaboostScores = [0]
    for i in range(1, ds.features + 1):
        adaboostScores.append(adaboostClassifier(ds.df, ds.target, ds.trainDf, ds.trainTarget, i))

    gs = gridspec.GridSpec(1, 1, figure=plt.figure(num=None, figsize=(8, 5)))
    ax = plt.subplot(gs[0])
    ax.title.set_text('Acurácia de acordo com o aumento features')
    ax.grid(True)
    ax.set_xlabel('Features')
    ax.set_ylabel('Acurácia')
    ax.set_xlim([1, ds.features + 1])
    ax.set_ylim([0.7, 1])
    ax.plot(np.array([score for score in adaboostScores]), label="Adaboost")
    ax.plot(np.array([naiveBayesMeanScore for i in range(0, len(adaboostScores))]), label="Naive Bayes")
    ax.legend()
    plt.show()
    
def showKnnStats(kValues):
    knnScores = {}

    for i in range(0,len(kValues)):
        knnScores[kValues[i]] = knnClassifier(ds.df, ds.target, ds.trainDf, ds.trainTarget, kValues[i])

    fig, ax = plt.subplots(figsize=(8,8))
    sns.lineplot(x=kValues, y=[v for k,v in knnScores.items()], color='r', ax=ax)
    sns.lineplot(x=kValues, y=[naiveBayesMeanScore for i in knnScores.items()], color='b', ax=ax)    
    ax.legend(['KNN', 'Naive Bayes'], facecolor='w')
    plt.xticks(kValues)
    plt.xlim([0.5, 29.5])
    plt.grid(True)
    plt.show()
    
def showSvmStats():
    penalties = [1,2,3,4,5,6,7,8,9,10]
    svmScores = {}

    svmScores['linear'] = [0]
    svmScores['rbf'] = [0]
    svmScores['sigmoid'] = [0]
    svmScores['poly'] = [0]

    for i in penalties:
        svmScores['linear'].append(svmLinearClassifier(ds.df, ds.target, ds.trainDf, ds.trainTarget, i))
        svmScores['rbf'].append(svmRbfClassifier(ds.df, ds.target, ds.trainDf, ds.trainTarget, i))
        svmScores['sigmoid'].append(svmSigmoidClassifier(ds.df, ds.target, ds.trainDf, ds.trainTarget, i))
        svmScores['poly'].append(svmPolyClassifier(ds.df, ds.target, ds.trainDf, ds.trainTarget, i))

    gs = gridspec.GridSpec(1, 1, figure=plt.figure(num=None, figsize=(8, 5)))
    ax = plt.subplot(gs[0])
    ax.title.set_text('Acurácia de acordo com o aumento penalidade')
    ax.grid(True)
    ax.set_xlabel('Penalidade')
    ax.set_ylabel('Acurácia')
    ax.set_xticks(penalties)
    ax.set_xlim([0.9, 10.1])
    ax.set_ylim([0.55, 0.95])
    ax.plot(np.array([score for score in svmScores['linear']]), label="Linear")
    ax.plot(np.array([score for score in svmScores['rbf']]), label="RBF")
    ax.plot(np.array([score for score in svmScores['sigmoid']]), label="Sigmoid")
    ax.plot(np.array([score for score in svmScores['poly']]), label="Polynomial")
    ax.plot(np.array([naiveBayesMeanScore for i in range(0, (len(penalties) +1))]), label="Naive Bayes")
    ax.legend()
    plt.show()
    
def showConfusionMatrix():
    cm = metrics.confusion_matrix(y_val, y_pred)

    fig, ax = plt.subplots(figsize=(7, 7))
    im = ax.imshow(cm, interpolation='nearest', cmap=plt.cm.Blues)
    ax.figure.colorbar(im, ax=ax)
    ax.set(xticks=np.arange(cm.shape[1]),
           yticks=np.arange(cm.shape[0]),
           xticklabels=classes, yticklabels=classes,
           title="Matriz de Confusão",
           ylabel="Real",
           xlabel="Predito")

    plt.setp(ax.get_xticklabels(), rotation=45, ha="right",
             rotation_mode="anchor")

    for i in range(cm.shape[0]):
        for j in range(cm.shape[1]):
            ax.text(j, i, format(cm[i, j], "d"),
                    ha="center", va="center",
                    color="white" if cm[i, j] > cm.max()/2. else "black")
    fig.tight_layout()
    plt.show()

ds = DataSet(['kepoi_name'])
naiveBayesMeanScore = naiveBayesClassifier(ds.df, ds.target)

showDecisionTreeStats(MAX_DEPTH)

showRandomForestStats(MAX_DEPTH)

showAdaboostStats()

showKnnStats([1,3,5,7,9,11,13,15,17,19,21,23,25,27,29])

showSvmStats()