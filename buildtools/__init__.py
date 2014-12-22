from os import path, makedirs

def make_directories(dir):
    if path.exists(dir):
        if path.isdir(dir):
            return False
        else:
            raise IOError("%s already exists and is NOT a directory!" % dir)
    else:
        print("Creating directory %s", dir)
        makedirs(dir)
        return True
        
        
