import glob
import os
import sys
import re
d=os.getcwd()
os.chdir(d+'/Catalog')
tableName=sys.argv[1]
files=glob.glob(tableName+'.*')
for fileName in files:
    if fileName!=tableName+'.attr' and fileName!=tableName+'.end':
        postfix=re.findall(r'.\w+$', fileName)[0]
        print(postfix[1:])
