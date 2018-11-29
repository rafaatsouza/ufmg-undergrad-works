import re
import pandas as pd
import numpy as np
import StopWords as st

from nltk.stem.lancaster import LancasterStemmer
from nltk.tokenize import RegexpTokenizer

class TweetsDataSet:
    def __init__(self, datasetPath, size, train_size):
        self.datasetPath = datasetPath
        self.labels = []
        self.corpus = []
        self.tokenized_corpus = []
        self.bayes_dataset = {}
        self.bayes_no_of_items = {}
        self.bayes_feature_set = {}
        self.bayes_test = []
        self.process(size, train_size)

    def process(self, size, train_size):
        tokenizer = RegexpTokenizer('[a-zA-Z0-9@]+')
        stemmer = LancasterStemmer()

        emotions_tweets = pd.read_csv(self.datasetPath, encoding="ISO-8859-1")
        indexes = set(np.random.choice(len(emotions_tweets), size, replace=False))
        count = 0

        for index in indexes:
            count+= 1
            line = emotions_tweets.iloc[index]
            classe = int(line[0])
            if(classe == 4):
                classe = 1
            self.labels.append(classe)
            tweet = line[5][1:] if line[5].startswith('"') else (line[5][::-1] if line[5].endswith('"') else line[5])
            self.corpus.append(tweet.strip().lower())
            #bayes vvvvvvv
            if(count <= train_size):
                self.bayes_no_of_items.setdefault(classe,0)
                self.bayes_no_of_items[classe]+=1
                self.bayes_dataset.setdefault(classe,{})
                for i in (re.split('[^a-zA-Z\']',tweet)):
                    if len(i) > 2:
                        self.bayes_dataset[classe].setdefault(i.lower(),0)
                        self.bayes_dataset[classe][i.lower()]+=1
                        self.bayes_feature_set.setdefault(i.lower(),{})
                        self.bayes_feature_set[i.lower()].setdefault(classe,0)
                        self.bayes_feature_set[i.lower()][classe]+=1
            else:
                self.bayes_test.append((tweet.strip().lower(), classe))

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