from sklearn.feature_extraction.text import CountVectorizer

class VectorizedData:
    def __init__(self, fileName):
        self.features = []
        self.fileName = fileName

    def getVectorizedData(self):
        data = []
        file = open(self.fileName, 'r')
        for line in file:
                for word in line.split(' '):
                        data.append((word.split('_'))[1])
        vectorizer = CountVectorizer(lowercase=False, token_pattern='[A-Z;+;-]+')
        corpus = (vectorizer.fit_transform(data)).toarray()
        self.features = vectorizer.get_feature_names()
        del data
        del vectorizer
        
        return corpus

    def getFeatureNameByOneHot(self, oneHotVector):
        for index in range(len(oneHotVector)):
            if(oneHotVector[index] == 1):
                return self.features[index]