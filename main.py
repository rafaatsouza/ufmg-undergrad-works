import tensorflow as tf
import Classifier as clf
import Utils as ut

SPAM_FOLDER = 'dataset/spam/'
NOT_SPAM_FOLDER = 'dataset/not_spam/'
BATCH_SIZE = 32
FOLDS_COUNT = 5

tf.logging.set_verbosity(tf.logging.ERROR)

classifier = clf.Classifier(SPAM_FOLDER, NOT_SPAM_FOLDER, BATCH_SIZE, FOLDS_COUNT)

for i in range(1,31):
    print('Teste com {} época(s)'.format(i))
    result = classifier.fitGenerator(i)
    ut.Utils.registerToFile('{};{};{};{};{}\n'.format(i, result['train_loss'], result['train_accuracy'], result['test_loss'], result['test_accuracy']), 'results', 'results.csv')