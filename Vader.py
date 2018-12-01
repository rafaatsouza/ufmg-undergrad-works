from vaderSentiment.vaderSentiment import SentimentIntensityAnalyzer

class Vader:
    def __init__(self):
        self.analyzer = SentimentIntensityAnalyzer()

    def AnalyzeSentence(self, sentence):    
        vs = self.analyzer.polarity_scores(sentence)

        if(vs['compound'] >= 0):#.05):
            return 1
        elif(vs['compound'] < 0):#-0.05):
            return 0
        
        # if(vs['pos'] > vs['neg']):
        #     return 1
        # else:
        #     return 0

    def getVaderScore(self, testData):
        totalCount = 0
        successCount = 0
        for item in testData:
            totalCount += 1
            if(self.AnalyzeSentence(item[0]) == item[1]):
                successCount += 1
        
        return (successCount/len(testData))