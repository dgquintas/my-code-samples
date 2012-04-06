import os.path

absFilePath = os.path.abspath(__file__)
print "file", absFilePath
print "dir", os.path.dirname(absFilePath)
