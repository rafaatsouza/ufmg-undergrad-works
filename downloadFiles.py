import urllib.request
import pandas as pd
import os

csvFileName = 'files.csv'
folderName = 'images/uncategorized'

if not os.path.exists(folderName):
    os.makedirs(folderName)

df = pd.read_csv(csvFileName, sep=";")
imagesNameList = []

for index, row in df.iterrows():
    filename = 'image_' + str(index) + '.' + (row['name'].split("."))[1]
    try:
        if(row['name'] not in imagesNameList):
            urllib.request.urlretrieve(row['link'], folderName + '/' + filename)
            imagesNameList.append(row['name'])
    except:
        print('Error with {}'.format(filename))
