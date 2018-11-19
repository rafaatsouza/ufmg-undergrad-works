import pandas as pd
import numpy as np
import StopWords as st

from nltk.stem.lancaster import LancasterStemmer
from nltk.tokenize import RegexpTokenizer

class TweetsDataSet:
    def __init__(self, datasetPath, size):
        self.datasetPath = datasetPath
        self.labels = []
        self.corpus = []
        self.tokenized_corpus = []
        self.process(size)

    def process(self, size):
        tokenizer = RegexpTokenizer('[a-zA-Z0-9@]+')
        stemmer = LancasterStemmer()

        emotions_tweets = pd.read_csv(self.datasetPath, encoding="ISO-8859-1")
        indexes = set(np.random.choice(len(emotions_tweets), size, replace=False))

        for index in indexes:
            line = emotions_tweets.iloc[index]
            classe = int(line[0])
            if(classe == 0):
                self.labels.append(0)
            if(classe == 4):
                self.labels.append(1)
            tweet = line[5][1:] if line[5].startswith('"') else (line[5][::-1] if line[5].endswith('"') else line[5])
            self.corpus.append(tweet.strip().lower())

        stopWords = st.StopWords().list

        for i, tweet in enumerate(self.corpus):
            tokens = [stemmer.stem(t) for t in tokenizer.tokenize(tweet) if (not t.startswith('@'))]
            tokens = [t for t in tokens if not t.strip().lower() in stopWords]
            self.tokenized_corpus.append(tokens)

        del stopWords
        del emotions_tweets
        del stemmer
        del tokenizer
        del indexes