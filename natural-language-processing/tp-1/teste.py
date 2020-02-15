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


originalTextPath = 'dataset/newText8'
NewTextPath = 'dataset/50_newText8'

IgnoreCorpus(originalTextPath, NewTextPath, 50)

# corpus = gensim.models.word2vec.Text8Corpus('dataset/text8', max_sentence_length=10000)
# model = gensim.models.Word2Vec(corpus,size=tng_size, window=tng_window, min_count=tng_min_count, workers=tng_workers, iter=tng_iter,sg=tng_sg)
# model.save(output_path)
# similarities = model.wv.most_similar(positive=[word_tokens[1], word_tokens[2]],negative=[word_tokens[0]], topn=50)
#
# model.wv.accuracy('questions-words.txt')#resulta em estatisticas no log criado
