#ifndef CATALOG_H
#define CATALOG_H
#include <vector>
#include <string>
#include <map>
#include "AttributeConstraint.h"
#include "com.h"
#include "ResultSet.h"
#include "RecordPointer.h"
using namespace std;
using namespace tools;
namespace catalog {
    extern map<string, Table> tables;
    extern map<string, Table> tofi;
    extern map<string, vector<Index>> ioft;
    //all the functions canbe used by others
    Table& getTable(const string& tableName);
    vector<AttributeConstraint>& getAttributes(const string& tableName);
    vector<Index>& getIndecies(const string& tableName);
    void getEnd(Table& table);
    //true�����Ŀ����
    bool hasTable(const string& tableName);
    bool hasIndex(const string& indexName);
    //������Ŀ�����ļ�, false��ʾ����ʧ��
    bool createTable(const Table& table);//class Table ���޸�
    bool createIndex(const Index& index);
    //ɾ����Ŀ�����ļ�
    bool dropTable(const string& tableName);
    bool dropIndex(const string& indexName);

    RecordPointer getIndexRoot(const string& indexName);
    bool setIndexRoot(const string& indexName, RecordPointer position);

    //name = tableName.attributeName
    string tableOfIndex(const string& indexName);
    Index getIndex(const string& indexName);
    //AttributeConstraint attrOfTable(const string& tableName, const string& attrName);
}
#endif
