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
    //true则此项目存在
    bool hasTable(const string& tableName);
    bool hasIndex(const string& indexName);
    //创建项目描述文件, false表示创建失败
    bool createTable(const Table& table);//class Table 需修改
    bool createIndex(const Index& index);
    //删除项目描述文件
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
