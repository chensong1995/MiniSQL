#pragma once
#include <vector>
#include <cstdint>

#include "com.h"
#include "Interpreter.h"
#include "index.h"
#include "catalog.h"
#include "RecordManager.h"

using namespace std;

namespace API {


    vector<Index> getIndex(const string& tableName);
    template <typename T, int size>
    void indexFunctions(Index& index, const array<T, size>& key, const index::Pointer& p = { INT_MAX, INT_MAX });
    void indexFuns(Index& index, const string& key, const index::Pointer& p = { INT_MAX, INT_MAX });

    void createTable(const string& tableName, const vector<AttributeConstraint>& attributes);

    void createIndex(const string& tableName, const string& indexName, const string& attributeName);

    void dropTable(const string& tableName);

    void dropIndex(const string& indexName);

    void insertTuple(const string& tableName, vector<string>& values);

    void deleteTuple(const string& tableName, vector<Clause>& clauses);

    ResultSet search(const string& tableName, vector<Clause>& clauses);

    void quit();

    RecordPointer getPointerBetween(Index & index, const string & keyA, const string & keyB, bool withLeftBound = true, bool withRightBound = true);
    RecordPointer getPointerBetween(Index & index, const int & keyA, const int & keyB, bool withLeftBound = true, bool withRightBound = true);
    RecordPointer getPointerBetween(Index & index, const float & keyA, const float & keyB, bool withLeftBound = true, bool withRightBound = true);

    template <typename T, int size>
    void indexFunctions(Index& index, const array<T, size>& key, const index::Pointer& p) {
        if (!(p.blockNo == INT_MAX&&p.blockOffset == INT_MAX)) {
            if (!index::insertIndex(index, key, p)) {
                string errorMessage = "inertKey on \"" + index.name + "\" failed when trying to inert ";
                for (auto&e : key) {
                    errorMessage += e;
                }
                throw MyException(errorMessage + "\n");
            }
        } else {
            if (!index::deleteKey(index, key)) {
                string errorMessage = "deleteKey on \"" + index.name + "\" failed when trying to delete ";
                for (auto&e : key) {
                    errorMessage += e;
                }
                throw MyException(errorMessage + "\n");
            }
        }
    }
};