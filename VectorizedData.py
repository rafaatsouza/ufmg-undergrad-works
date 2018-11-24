from sklearn.feature_extraction.text import CountVectorizer

class VectorizedData:
    def getVectorizedData(fileName):
        data = []
        file = open(fileName, 'r')
        for line in file:
                for word in line.split(' '):
                        data.append((word.split('_'))[1])
        vectorizer = CountVectorizer(lowercase=False, token_pattern='[A-Z;+;-]+')
        return vectorizer.fit_transform(data)