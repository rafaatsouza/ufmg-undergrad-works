import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

np.random.seed(1000)

def genetateGraphByEppochCountAndBatchType(directory):
    results = {}
    results['default'] = {}
    results['train_size'] = {}

    csv = pd.read_csv('csv/accuracyByEppochCountAndBatchType.csv')

    for index, row in csv.iterrows():
        results[row[0].split(';')[1]][row[0].split(';')[0]] = float("%.3f" % float(row[0].split(';')[2]))

    keys = [k for k in results['train_size']]
    plt.grid(True)
    plt.xlabel('Eppochs')
    plt.ylabel('Accuracy')
    plt.xlim([-1,15])
    plt.plot(np.array([results['default'][k] for k in results['default']]), label="Batch Size Default")
    plt.plot(np.array([results['train_size'][k] for k in results['train_size']]), label="Batch Size = Train Size")
    plt.xticks([i for i in range(len(keys))], keys)
    plt.legend()
    
    plt.tight_layout()

    if not os.path.exists(directory):
        os.makedirs(directory)

    plt.savefig('{}/AccuracyByEppochCountAndBatchType.png'.format(directory))

def genetateGraphKerasOrVader(directory):
    plt.grid(True)
    plt.xlabel('Type')
    plt.ylabel('Accuracy')
    plt.ylim([0.6, 0.76])
    
    csv = pd.read_csv('csv/KerasVaderCompare.csv')

    for index, row in csv.iterrows():
        key = 'Word2Vec + Convolutional Network' if row[0].split(';')[1] == 'keras' else row[0].split(';')[1]
        plt.bar(key ,float("%.3f" % float(row[0].split(';')[2])))
    
    plt.tight_layout()

    if not os.path.exists(directory):
        os.makedirs(directory)

    plt.savefig('{}/AccuracyKerasOrVader.png'.format(directory))

#genetateGraphByEppochCountAndBatchType('graphImages')
genetateGraphKerasOrVader('graphImages')