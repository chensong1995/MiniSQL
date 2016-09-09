#ifndef COM_H
#define COM_H
#include "AttributeConstraint.h"
#include "ResultSet.h"
#include "RecordPointer.h"
#include <fstream>
class Table {
public:
    string name;
    vector<AttributeConstraint> attrList;
    RecordPointer end;
    Table(string name = "", int blockNo = 0, int blockOffset = 0) :name(name), end(blockNo, blockOffset) {};
    bool writeBack() {
        fstream write;
        write.open("Catalog\\" + name + ".end", fstream::out);
        if (!write.is_open()) {
            return false;
        }
        write << end.getBlockNo() << " " << end.getBlockOffset();
        return true;
    }
};
class Index {
public:
    string name;
    string table;
    string attr;
    string type;
    int length;
    RecordPointer root;
    RecordPointer end;
    Index(string name = "", string table = "", string attrName = "", string type = "CHAR", int length = 1, int blockNo = 0, int offset = 100, int endB = 0, int endO = 100) :name(name), table(table), attr(attrName), type(type), length(length), root(RecordPointer(blockNo, offset)), end(RecordPointer(endB, endO)) {};
    bool writeBack() {
        fstream write;
        write.open("Catalog\\" + table + "." + name, fstream::out);
        if (!write.is_open()) {
            return false;
        }
        write << name << " " << table << " " << attr << " " << type << " " << length << " " << root.getBlockNo() << " " << root.getBlockOffset() << " " << end.getBlockNo() << " " << end.getBlockOffset() << "\n";

        return true;
    }
};

namespace tools {
    //拆分数组
    vector<string> split(const string &s, const string &seperator);
    //返回一个表中所含词条数组，该表不存在返回空
    string exec(const string cmd);
}
#endif
