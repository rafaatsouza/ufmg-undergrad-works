import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def generateGraph(result, directory):
    plt.rcdefaults()
    fig, ax = plt.subplots()
    keys = [(k) for k in sorted(results, key=results.get,reverse=True)]
    y_pos = np.arange(len(np.array(keys)))
    ax.barh(y_pos, np.array([result[k] for k in sorted(results, key=results.get,reverse=True)]), align='center', color='blue', ecolor='black')
    ax.set_yticks(y_pos)
    ax.set_yticklabels(np.array(keys))
    ax.invert_yaxis()
    ax.set_xlabel('Accuracy')
    ax.set_ylabel('Eppochs')
    ax.set_title('Accuracy by Eppoch quantity')
    ax.grid(True)

    plt.xlim(0.55, 0.75)#1.005)
    
    del keys
    
    if not os.path.exists(directory):
        os.makedirs(directory)

    plt.savefig('{}/accuracyByEppochCount.png'.format(directory))

results = {}
csv = pd.read_csv('csv/accuracyByEppochCount.csv')

for index, row in csv.iterrows():
    results[row[0].split(';')[0]] = float("%.3f" % float(row[0].split(';')[1]))

generateGraph(results, 'graphImages')