import re

class Bayes:
    def __init__(self, tweetsDataSet):
        self.tds = tweetsDataSet

    def calc_prob(self, word, category):

        if word not in self.tds.bayes_feature_set or word not in self.tds.bayes_dataset[category]:
            return 0

        return float(self.tds.bayes_dataset[category][word])/self.tds.bayes_no_of_items[category]


    # Weighted probability of a word for a category
    def weighted_prob(self, word, category):
        # basic probability of a word - calculated by calc_prob
        basic_prob=self.calc_prob(word,category)

        # total_no_of_appearances - in all the categories
        if word in self.tds.bayes_feature_set:
            tot=sum(self.tds.bayes_feature_set[word].values())
        else:
            tot=0
            
        # Weighted probability is given by the formula
        # (weight*assumedprobability + total_no_of_appearances*basic_probability)/(total_no_of_appearances+weight)
        # weight by default is taken as 1.0
        # assumed probability is 0.5 here
        weight_prob=((1.0*0.5)+(tot*basic_prob))/(1.0+tot)
        return weight_prob


    # To get probability of the test data for the given category
    def test_prob(self, test, category):
        # Split the test data
        split_data=re.split('[^a-zA-Z][\'][ ]',test)
        
        data=[]
        for i in split_data:
            if ' ' in i:
                i=i.split(' ')
                for j in i:
                    if j not in data:
                        data.append(j.lower())
            elif len(i) > 2 and i not in data:
                data.append(i.lower())

        p=1
        for i in data:
            p*=self.weighted_prob(i,category)
        return p

    # Naive Bayes implementation
    def naive_bayes(self, test):
        '''
            p(A|B) = p(B|A) * p(A) / p(B)
            Assume A - Category
                B - Test data
                p(A|B) - Category given the Test data
            Here ignoring p(B) in the denominator (Since it remains same for every category)
        '''
        results={}
        for i in self.tds.bayes_dataset.keys():
            # Category Probability
            # Number of items in category/total number of items
            cat_prob=float(self.tds.bayes_no_of_items[i])/sum(self.tds.bayes_no_of_items.values())

            # p(test data | category)
            test_prob1=self.test_prob(test,i)

            results[i]=test_prob1*cat_prob

        return results
