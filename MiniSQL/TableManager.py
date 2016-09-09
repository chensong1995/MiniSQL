import glob
import os
import sys
d=os.getcwd()
os.chdir(d+'/Catalog')
tables=glob.glob('*.attr')
tableName=sys.argv[1]+'.attr'
if tableName in tables:
    print('1')
else:
    print('0')
