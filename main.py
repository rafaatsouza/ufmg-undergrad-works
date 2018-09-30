from gensim.models import Word2Vec
import gensim
import os,logging
import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)

def IgnoreCorpus(original, new, percentage):
    file = open(original, 'r')
    for line in file:
        words = line.split(' ')
        limit = len(words)/100*percentage
        count = 0
        for word in words:
            if(count <= limit):
                with open(new, ('w' if count == 0 else 'a')) as out:
                     out.write((word.lower() if count == 0 else ' ' + word.lower()))
                count = count + 1


def CorpusToLower(original, new):
    file = open(original, 'r')
    lines = [line.lower() for line in file]
    with open(new, 'w') as out:
         out.write(lines)


def InsereLinha(path, msg):
    openMode = 'w'
    try:
        if os.path.exists(path):
            openMode = 'a'
    except Exception as e:
        openMode = 'w'
        pass

    with open(path, openMode) as out:
         out.writelines(msg + '\n')


def FazTodaDesgraca(corpusPath, windowSize, modelSg, basicLogOutputhPath, basicModelOutputhPath, basicResultOutputhPath, wordsPath, percentage): #modelSg: 1 for Skip-gram, 0 for CBOW
    basicName = str(percentage) + '_' + str(windowSize) + '_' + str(modelSg)
    logName = basicLogOutputhPath + 'log_' + basicName
    logging.basicConfig(filename=logName,format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)
    corpus = gensim.models.word2vec.Text8Corpus(corpusPath, max_sentence_length=10000)
    model = gensim.models.Word2Vec(corpus, window=windowSize, min_count=100, iter=5,sg=modelSg)
    model.save(basicModelOutputhPath + basicName)

    words = open(wordsPath, 'r')
    for words in [line.rstrip().lower().split() for line in words if line.find(':') == -1]:
        try:
            similarities = model.wv.most_similar(positive=[words[1], words[2]],negative=[words[0]], topn=50)
            i = 0
            while i <= (len(similarities) - 1):
                if(str(similarities[i][0]) == words[3]):
                    InsereLinha((basicResultOutputhPath + basicName + '.csv'), (words[3] + '<->' + str(similarities[0][0])) + ';' + str(float(similarities[0][1]) - float(similarities[i][1])).replace('.', ','))
                    i = len(similarities) + 1
                else:
                    i = i + 1
        except:
            pass

    model.wv.accuracy(wordsPath)#resulta em estatisticas no log criado


# originalTextPath = 'dataset/text8'
# lowerCaseTextPath = 'dataset/newText8'
#
# CorpusToLower(originalTextPath, lowerCaseTextPath)

FazTodaDesgraca('dataset/newText8', 1, 0, 'log/', 'model/', 'output/' , 'dataset/questions-words.txt', 100)
