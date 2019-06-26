import tensorflow as tf
import Classifier as clf
import DataSet as ds
import Utils as ut

SPAM_FOLDER = 'dataset/spam/'
NOT_SPAM_FOLDER = 'dataset/new_not_spam/'
BATCH_SIZE = 32
FOLDS_COUNT = 5
NOT_SPAM_PROPORTION = 1

tf.logging.set_verbosity(tf.logging.ERROR)

dataset = ds.DataSet(SPAM_FOLDER, NOT_SPAM_FOLDER, NOT_SPAM_PROPORTION)
classifier = clf.Classifier(BATCH_SIZE)

folds = dataset.GetAugFolds(BATCH_SIZE, FOLDS_COUNT)

for i in range(1,31):
    print('Teste com {} época(s)'.format(i))
    result = classifier.fitAugGenerator(i, folds)
    if(i == 1):
        ut.Utils.registerToFile('eppochs;train_loss;train_accuracy;test_loss;test_accuracy\n', 'results', 'teste.csv')
    csvLine = '{};{};{};{};{}\n'.format(i, result['train_loss'], result['train_accuracy'], result['test_loss'], result['test_accuracy'])
    ut.Utils.registerToFile(csvLine, 'results', 'teste.csv')
    del csvLine