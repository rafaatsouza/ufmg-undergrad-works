trainFileName = 'dataset/macmorpho/macmorpho-train.txt'
cleanedTrainFileName = 'dataset/cleanedFiles/train.txt'

file = open(trainFileName, 'r')
newFile = open(cleanedTrainFileName, 'w')
for line in file:
    for word in line.split(' '):
        newFile.write('{} '.format((word.split('_'))[1]))