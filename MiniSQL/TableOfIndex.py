import glob
import os
import sys
import re
d=os.getcwd()
os.chdir(d+'/Catalog')
indexName=sys.argv[1]
files=glob.glob('*.'+indexName)
for fileName in files:
    postfix=re.sub(r'.\w+$', '', fileName)
    print(postfix)
