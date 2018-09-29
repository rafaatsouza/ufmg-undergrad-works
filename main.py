from gensim.models import Word2Vec
import gensim
from nltk.tokenize import word_tokenize
from itertools import chain
from glob import glob
from nltk.tokenize import word_tokenize
import os,logging
import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)

def CorpusToLower(original, new):
    file = open(original, 'r')
    lines = [line.lower() for line in file]
    with open(new, 'w') as out:
         out.write(lines)


def InsereLinhaPath(path, msg):
    openMode = 'w'
    try:
        if os.path.exists(path):
            openMode = 'a'
    except Exception as e:
        openMode = 'w'
        pass

    with open(path, openMode) as out:
         out.writelines(msg + '\n')


def FazTodaDesgraca(corpusPath, windowSize, modelSg, basicLogOutputhPath, basicModelOutputhPath, basicResultOutputhPath, wordsPath): #modelSg: 1 for Skip-gram, 0 for CBOW
    basicName = '100_' + str(windowSize) + '_' + str(modelSg)
    logName = 'log_' + basicName
    logging.basicConfig(filename=logName,format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)
    corpus = gensim.models.word2vec.Text8Corpus(corpusPath, max_sentence_length=10000)
    model = gensim.models.Word2Vec(corpus, window=windowSize, workers=8, min_count=100, iter=5,sg=modelSg)
    model.save(basicModelOutputhPath + basicName)

    words = open(wordsPath, 'r')
    for words in [line.rstrip().lower().split() for line in words if line.find(':') == -1]:
        try:
            similarities = model.wv.most_similar(positive=[words[1], words[2]],negative=[words[0]], topn=50)
            i = 0
            findedIndex = -1
            while i <= (len(similarities) - 1):
                if(str(similarities[i][0]) == words[3]):
                    findedIndex = i
                    i = len(similarities) + 1
                else:
                    i = i + 1

            if findedIndex > 0 :
                InsereLinhaPath((basicResultOutputhPath + basicName + '.csv'), (words[3] + ',' + str(similarities[findedIndex][0])) + ';' + str(float(similarities[0][1]) - float(similarities[findedIndex][1])))
        except:
            pass

    model.wv.accuracy(wordsPath)#resulta em estatisticas no log criado


# originalTextPath = 'dataset/text8'
# lowerCaseTextPath = 'dataset/newText8'
#
# CorpusToLower(originalTextPath, lowerCaseTextPath)

FazTodaDesgraca('dataset/newText8', 1, 1, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')
FazTodaDesgraca('dataset/newText8', 2, 1, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')
FazTodaDesgraca('dataset/newText8', 4, 1, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')
FazTodaDesgraca('dataset/newText8', 6, 1, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')
FazTodaDesgraca('dataset/newText8', 8, 1, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')
FazTodaDesgraca('dataset/newText8', 10, 1, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')
FazTodaDesgraca('dataset/newText8', 1, 2, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')
FazTodaDesgraca('dataset/newText8', 2, 2, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')
FazTodaDesgraca('dataset/newText8', 4, 2, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')
FazTodaDesgraca('dataset/newText8', 6, 2, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')
FazTodaDesgraca('dataset/newText8', 8, 2, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')
FazTodaDesgraca('dataset/newText8', 10, 2, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt')

# corpus = gensim.models.word2vec.Text8Corpus('dataset/text8', max_sentence_length=10000)
# model = gensim.models.Word2Vec(corpus,size=tng_size, window=tng_window, min_count=tng_min_count, workers=tng_workers, iter=tng_iter,sg=tng_sg)
# model.save(output_path)
# similarities = model.wv.most_similar(positive=[word_tokens[1], word_tokens[2]],negative=[word_tokens[0]], topn=50)
#
# model.wv.accuracy('questions-words.txt')#resulta em estatisticas no log criado
