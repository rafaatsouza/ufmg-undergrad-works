from keras.preprocessing.image import ImageDataGenerator

class DataSet:
    def __init__(self, trainFolderPath, testFolderPath):
        train_datagen = ImageDataGenerator(rescale=1./255, 
                        shear_range=0.2, 
                        zoom_range=0.2, 
                        fill_mode='reflect',
                        horizontal_flip=True)
        
        test_datagen = ImageDataGenerator(rescale=1./255)

        self.training_set = train_datagen.flow_from_directory(trainFolderPath, target_size=(64, 64), class_mode='binary', subset='training')
        self.test_set = test_datagen.flow_from_directory(testFolderPath, target_size=(64, 64), class_mode='binary', subset='validation')

        del train_datagen
        del test_datagen