#include "catalog.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <fstream>
#include "MyException.h"

namespace catalog {
    map<string, Table> tables;
    map<string, Table> tofi;
    map<string, vector<Index>> ioft;
    Table& getTable(const string& tableName) {
        if (tables.find(tableName) != tables.end()) {
            return tables[tableName];
        }
        //cout << "getTable from file\n";
        Table t;
        fstream table;
        table.open("Catalog\\" + tableName + ".attr", fstream::in);
        if (!table.is_open()) {
            t.name = "";
        } else {
            t.name = tableName;
            string line, name, type;
            int length;
            vector<string> parts;
            while (getline(table, line)) {
                bool isPrime = false, isUnique = false;
                parts = split(line, " ");
                name = parts[0];
                if (parts[1] == "INT" || parts[1] == "FLOAT") {
                    type = parts[1];
                    length = 1;
                } else {
                    type = "CHAR";
                    string len;
                    for (unsigned int i = 4; i < parts[1].length(); i++) {
                        len += parts[1][i];
                    }
                    length = stoi(len);
                }
                for (unsigned int i = 2; i < parts.size(); i++) {
                    if (parts[i] == "UNIQUE") {
                        isUnique = true;
                    } else if (parts[i] == "PRIME") {
                        isPrime = true;
                    }
                }
                t.attrList.push_back(AttributeConstraint(name, type, isPrime, isUnique, length));
            }
        }
        getEnd(t);
        tables[tableName] = t;
        return tables[tableName];
    }
    void getEnd(Table& table) {
        fstream t;
        t.open("Catalog\\" + table.name + ".end", fstream::in);
        if (!t.is_open()) {
            table.end = RecordPointer(INT_MAX, INT_MAX);
            throw MyException("get table information failed");
        } else {
            int no, offset;
            t >> no >> offset;
            table.end = RecordPointer(no, offset);
        }
    }
    vector<AttributeConstraint>& getAttributes(const string& tableName) {
        return getTable(tableName).attrList;
    }
    vector<Index>& getIndecies(const string& tableName) {
        string res;
        vector<Index> indecies;
        if (ioft.find(tableName) != ioft.end()) {
            return ioft[tableName];
        }
        //cout << "getIndecies from file\n";
        res = exec("python GetIndecies.py " + tableName);
        for (auto&indexName : split(res, "\n")) {
            indecies.push_back(getIndex(indexName));
        }
        ioft[tableName] = indecies;
        return ioft[tableName];
    }
    bool hasTable(const string& tableName) {
        string res;
        res = exec("python TableManager.py " + tableName);
        return res == "1\n";
    }
    bool hasIndex(const string& indexName) {
        string res;
        res = exec("python IndexManager.py " + indexName);
        return res == "1\n";
    }
    //创建项目描述文件, false表示创建失败
    bool createTable(const Table& table) {
        if (hasTable(table.name)) {
            return false;
        }
        tables[table.name] = table;
        fstream write;
        write.open("Catalog\\" + table.name + ".attr", fstream::out);
        if (!write.is_open()) {
            return false;
        }
        for (auto&attr : table.attrList) {
            write << attr.getColumnName() << " ";
            if (attr.getType() == "CHAR") {
                write << "CHAR" << attr.getLength() << " ";
            } else {
                write << attr.getType() << " ";
            }
            if (attr.isPrimaryKey()) {
                write << "PRIME ";
            }
            if (attr.isUnique()) {
                write << "UNIQUE ";
            }
            write << "\n";
        }
        write.close();
        write.open("Catalog\\" + table.name + ".end", fstream::out);
        if (!write.is_open()) {
            return false;
        }
        write << table.end.getBlockNo() << " " << table.end.getBlockOffset();
        return true;
    }
    bool createIndex(const Index& index) {
        if (hasIndex(index.name)) {
            return false;
        }
        ioft[index.table].push_back(index);
        tofi[index.name] = getTable(index.table);
        fstream write;
        write.open("Catalog\\" + index.table + "." + index.name, fstream::out);
        if (!write.is_open()) {
            return false;
        }
        write << index.name << " " << index.table << " " << index.attr << " " << index.type << " " << index.length << " " << index.root.getBlockNo() << " " << index.root.getBlockOffset() << " " << index.end.getBlockNo() << " " << index.end.getBlockOffset() << "\n";

        return true;
    }
    //删除项目描述文件
    bool dropTable(const string& tableName) {
        tables.erase(tableName);
        ioft.erase(tableName);
        string res;
        res = exec("python DropTable.py " + tableName);
        return res == "";
    }
    bool dropIndex(const string& indexName) {
        Table t = tofi[indexName];
        for (std::vector<Index>::iterator iter = ioft[t.name].begin(); iter < ioft[t.name].end(); iter++) {
            if (iter->name == indexName) {
                ioft[t.name].erase(iter++);
                break;
            }
        }
        tofi.erase(indexName);
        string res;
        res = exec("python DropIndex.py " + indexName);
        return res == "";
    }
    RecordPointer getIndexRoot(const string& indexName) {
        return getIndex(indexName).root;
    }
    //根据名字获取index
    Index getIndex(const string& indexName) {
        //cout << "getIndex from file\n";
        if (!hasIndex(indexName)) {
            return Index();
        } else {
            fstream read;
            string name, table, attr, type;
            int blockNo, offSet, endB, endO, length;
            read.open("Catalog\\" + tableOfIndex(indexName) + "." + indexName, fstream::in);
            read >> name >> table >> attr >> type >> length >> blockNo >> offSet >> endB >> endO;
            return Index(name, table, attr, type, length, blockNo, offSet, endB, endO);
        }
    }
    string tableOfIndex(const string& indexName) {
        string res;
        res = exec("python TableOfIndex.py " + indexName);
        return split(res, "\n")[0];
    }
    AttributeConstraint attrOfTable(const string& tableName, const string& attrName) {
        fstream table;
        table.open("Catalog\\" + tableName + ".attr", fstream::in);
        if (!table.is_open()) {
        } else {
            string line, name, type;
            bool isPrime, isUnique;
            int length;
            vector<string> parts;
            while (getline(table, line)) {
                parts = split(line, " ");
                name = parts[0];
                if (name == attrName) {
                    continue;
                }
                isPrime = isUnique = false;
                if (parts[1] == "INT" || parts[2] == "FLOAT") {
                    type = parts[1];
                    length = 1;
                } else {
                    type = "CHAR";
                    length = parts[1][4] - '0';
                }
                for (unsigned int i = 2; i < parts.size(); i++) {
                    if (parts[i] == "UNIQUE") {
                        isUnique = true;
                    } else if (parts[i] == "PRIMARY") {
                        isPrime = true;
                    }
                }
                return AttributeConstraint(name, type, isPrime, isUnique, length);
            }
        }
        return AttributeConstraint("", "", false, false);
    }
}