import os

trainFileName = 'dataset/macmorpho/macmorpho-train.txt'

treino = {}

file = open(trainFileName, 'r')
for line in file:
    words = line.split(' ')
    for word in words:
        wordInfo = word.split('_')
        treino[wordInfo[0]] = wordInfo[1].split('+')