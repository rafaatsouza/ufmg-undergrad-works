import requests
from pathlib import Path

class StopWords:
    def __init__(self):
        self.data_url = 'https://storage.googleapis.com/kaggle-datasets/1760/3048/englishST.txt?GoogleAccessId=web-data@kaggle-161607.iam.gserviceaccount.com&Expires=1542838404&Signature=LOG%2BVrXgHwTb3KRMwXZ0if%2BkiTQdpmqbVnfUALDOfaV6VVhj4ReRzlwoQCu12phYdb12xA0Z5VYwsvDl0lh7cPNAnX82iItA26mJ%2FLvT5PcqRfL4sU%2FnqwRkde0aV6%2FrFcJkv8bcRkv1mS8yAsJTmpAUeufJGJEDh6DOirURjDWtbhSV6dzeOhiEc2M6uQqyQEvj7cJcnCpv0n%2B3qDKrnU7IJpdoqlpj4kLH4qO3sqqCSQdrYeVpnpwSa93nj8voOMTNx9avv%2FF3J5LhxOm8quWUw7sfA%2B3BCYH5jtS1%2FU9n7TMinMHT0nPAhORqUB4gCxc6BFkKF%2FvY57mt%2Fi3oxQ%3D%3D'
        self.local_filename = 'dataset/stopwords.txt'
        self.list = []
        self.getList()

    def getList(self):
        modelFile = Path(self.local_filename)
        if(modelFile.exists() == False or modelFile.is_file() == False):
            response = requests.get(self.data_url)
            response.raise_for_status()
            file = open(self.local_filename, 'w')
            file.write(response.text)
            file.close()
            
        self.FileToList()
    
    def FileToList(self):
        with open(self.local_filename, 'r') as f:
            for line in f:
                self.list.append(line.strip().lower())
