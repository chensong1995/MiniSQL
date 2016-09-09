import glob
import os
import sys
d=os.getcwd()
os.chdir(d+'/Catalog')
indexName=sys.argv[1]
indecies=glob.glob('*.'+indexName)
if indecies!=[]:
    print('1')
else:
    print('0')
