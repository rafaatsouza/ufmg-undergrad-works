import multiprocessing

from pathlib import Path
from gensim.models.word2vec import Word2Vec

class Word2VecModel:
    def getWord2VecModel(csvpath, vector_size, corpus, iterations):
        modelFile = Path(csvpath)
        if(modelFile.exists() and modelFile.is_file()):
            print('Modelo já existe')
            return Word2Vec.load(csvpath)
        else:
            print('Modelo ainda não existe no path {}'.format(csvpath))
            word2vec = Word2Vec(sentences=corpus,
                    size=vector_size,
                    window=10,
                    negative=20,
                    iter=iterations,
                    seed=1000,
                    workers=multiprocessing.cpu_count())
            word2vec.save(csvpath)
            return word2vec