import os
from pathlib import Path

class Utils:    
    def registerToFile(msg, directory, fileName):
        path = '{}/{}'.format(directory, fileName)
            
        if not os.path.exists(directory):
            os.makedirs(directory)

        regFile = Path(path)
        with open(path, ('a' if regFile.exists() and regFile.is_file() else 'w')) as out:
                out.write(msg)
            