from gensim.models import Word2Vec
import gensim
from nltk.tokenize import word_tokenize
from itertools import chain
from glob import glob
from nltk.tokenize import word_tokenize
import os,logging


logging.basicConfig(filename="log",format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)

#converter corpus para lowercase

corpus = gensim.models.word2vec.Text8Corpus('dataset/text8', max_sentence_length=10000)

# model = gensim.models.Word2Vec(corpus,size=tng_size, window=tng_window, min_count=tng_min_count, workers=tng_workers, iter=tng_iter,sg=tng_sg)
# model.save(output_path)
# similarities = model.wv.most_similar(positive=[word_tokens[1], word_tokens[2]],negative=[word_tokens[0]], topn=50)
#
# model.wv.accuracy('questions-words.txt')#resulta em estatisticas no log criado


def CorpusToLower(corp):
    i = 0
    for val in corp:
        for v in val:
            print(v)
            i = i + 1
            if i > 0:
                break


CorpusToLower(corpus)
