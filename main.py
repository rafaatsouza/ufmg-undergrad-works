import os
import numpy as np
import KerasNetwork as kn
import matplotlib.pyplot as plt

np.random.seed(1000)
trainFileName = 'dataset/macmorpho/macmorpho-train.txt'
testFileName = 'dataset/macmorpho/macmorpho-test.txt'

def saveClassesGraph(result, neural):
    plt.rcdefaults()
    fig, ax = plt.subplots()
    keys = [(k) for k,v in sorted(result.items())]
    y_pos = np.arange(len(np.array(keys)))
    ax.barh(y_pos, np.array([(v) for k,v in sorted(result.items())]), align='center', color='blue', ecolor='black')
    ax.set_yticks(y_pos)
    ax.set_yticklabels(np.array(keys))
    ax.invert_yaxis()
    ax.set_xlabel('Accuracy')
    ax.set_title('Accuracy by Class')
    ax.grid(True)

    plt.xlim(0.9, 1.005)

    if not os.path.exists('graphs'):
        os.makedirs('graphs')

    plt.savefig('graphs/accuracyByClass_{}.png'.format(n))

    del keys

def saveAllTotalValuesGraph(values):
    plt.title('Acurácia de acordo com o tamanho da janela')
    plt.grid(True)
    plt.xlabel('Tamanho da janela')
    plt.ylabel('Acurácia')
    plt.plot(np.array([values[key] for key in values]))
    plt.legend()
    plt.tight_layout()

    if not os.path.exists('graphs'):
        os.makedirs('graphs')

    plt.savefig('graphs/allTotalValues.png')

totalValues = {}
for n in range(3,16):
    neural = kn.KerasNetwork(trainFileName, testFileName, n)
    result = neural.evaluateModel()
    totalValues[n] = (neural.allModelEvaluate)
    saveClassesGraph(result, neural)
saveAllTotalValuesGraph(totalValues)