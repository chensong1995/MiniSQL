import glob
import os
import sys
try:
    d=os.getcwd()
    os.chdir(d+'/Catalog')
    indexName=sys.argv[1]
    indecies=glob.glob('*.'+indexName)
    for indexFile in indecies:
        os.remove(indexFile)
except:
    print("Failed")
