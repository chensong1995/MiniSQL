import glob
import os
import sys
try:
    d=os.getcwd()
    os.chdir(d+'/Catalog')
    tableName=sys.argv[1]
    tables=glob.glob(tableName+'.*')
    for tableFile in tables:
        os.remove(tableFile)
except:
    print("Failed")
