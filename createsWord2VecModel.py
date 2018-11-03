import pandas as pd
import multiprocessing
import os.path

from gensim.models.word2vec import Word2Vec
from nltk.stem.lancaster import LancasterStemmer
from nltk.tokenize import RegexpTokenizer

emotionTweetsPath = 'dataset/emotions_tweets.csv'
word2vecPath = 'model/word2vec.model'

corpus = []
tokenized_corpus = []

tkr = RegexpTokenizer('[a-zA-Z0-9@]+')
stemmer = LancasterStemmer()

word2vecIterations = 25
vector_size = 512

emotions_tweets = pd.read_csv(emotionTweetsPath, encoding="ISO-8859-1")

for index, row in emotions_tweets.iterrows():
    tweet = row[5]
    if tweet.startswith('"'):
        tweet = tweet[1:]
    if tweet.endswith('"'):
        tweet = tweet[::-1]

    corpus.append(tweet.strip().lower())

for i, tweet in enumerate(corpus):
    tokens = [stemmer.stem(t) for t in tkr.tokenize(tweet) if not t.startswith('@')]
    tokenized_corpus.append(tokens)

del emotions_tweets
del corpus
del tkr
del stemmer

word2vec = Word2Vec(sentences=tokenized_corpus,
                    size=vector_size,
                    window=10,
                    negative=20,
                    iter=word2vecIterations,
                    seed=1000,
                    workers=multiprocessing.cpu_count())
word2vec.save(word2vecPath)
del word2vec
