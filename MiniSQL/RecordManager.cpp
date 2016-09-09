#include "RecordManager.h"
#include "BufferManager.h"
#include "API.h"
#include <regex>
#include <cstdint>
#include "MyException.h"
#include <unordered_map>
#include <memory>
#include <sstream>
#include <iostream>
#include <limits>

RecordPointer RecordManager::illegalPointer(INT32_MAX, INT32_MAX);


char* RecordManager::retrieveData(const Table& table, const RecordPointer& position) {
    BufferBlock& block = BufferManager::getBlock(table.name, "data", position.getBlockNo());
    //block.pinBlock();
    block.setDirty();
    return block.getBlockContent() + position.getBlockOffset();
   //memcpy_s(data, dataSize, block.getBlockContent() + position.getBlockOffset(), dataSize);
    //block.unpinBlock();
}


const bool RecordManager::isClausesSatisfied(const char * data, const vector<AttributeConstraint>& attributeList, const vector<Clause>& clauses) {
    if (NULL == data) {
        throw MyException("Internal Error: Fail to read data from NULL pointer! (RecordManager::isClausesSatisfied())");
    }

    /* Retrieve data */
    unordered_map<string, string> attributesAndType;
    unordered_map<string, int32_t> intAttributes;
    unordered_map<string, float> floatAttributes;
    unordered_map<string, string> charAttributes;
    bool isLegal;
    unsigned int offset = 0;
    memcpy_s(&isLegal, sizeof(bool), data, sizeof(bool)); /* Retrieve the legal flag */
    offset += sizeof(bool);
    if (!isLegal) { /* That record has already been deleted */
        return false;
    }

    for (unsigned int i = 0; i < attributeList.size(); i++) {
        if ("INT" == attributeList[i].getType()) {
            memcpy_s(&intAttributes[attributeList[i].getColumnName()], sizeof(int32_t), data + offset, sizeof(int32_t));
            offset += sizeof(int32_t);
            attributesAndType[attributeList[i].getColumnName()] = "INT";
        } else if ("FLOAT" == attributeList[i].getType()) {
            memcpy_s(&floatAttributes[attributeList[i].getColumnName()], sizeof(float), data + offset, sizeof(float));
            offset += sizeof(float);
            attributesAndType[attributeList[i].getColumnName()] = "FLOAT";
        } else if ("CHAR" == attributeList[i].getType()) {
            unsigned int length = attributeList[i].getLength();
            for (unsigned int j = 0; j < length; j++) {
                char temp;
                memcpy_s(&temp, sizeof(char), data + offset, sizeof(char));
                charAttributes[attributeList[i].getColumnName()].push_back(temp);
                offset++;
            }
            attributesAndType[attributeList[i].getColumnName()] = "CHAR";
        } else {
            throw MyException("Internal Error: Type \"" + attributeList[i].getType() + "\" is not supported!");
        }
    }

    /* Check clauses */
    for (unsigned int i = 0; i < clauses.size(); i++) {
        if (attributesAndType.find(clauses[i].getAttribute()) == attributesAndType.end()) { /* The attribute in the clause does not exist */
            throw MyException("Internal Error: Attribute \"" + clauses[i].getAttribute() + "\" is illegal!");
        } else {
            stringstream stream(clauses[i].getValue());
            if ("INT" == attributesAndType[clauses[i].getAttribute()]) {
                int32_t valueInClause;
                stream >> valueInClause;
                if (!checkSingleClause(intAttributes[clauses[i].getAttribute()], valueInClause, clauses[i].getOperator())) {
                    return false;
                }
            } else if ("FLOAT" == attributesAndType[clauses[i].getAttribute()]) {
                float valueInClause;
                stream >> valueInClause;
                if (!checkSingleClause(floatAttributes[clauses[i].getAttribute()], valueInClause, clauses[i].getOperator())) {
                    return false;
                }
            } else if ("CHAR" == attributesAndType[clauses[i].getAttribute()]) {
                string valueInClause = clauses[i].getValue();
                if (!checkSingleClause(charAttributes[clauses[i].getAttribute()], valueInClause, clauses[i].getOperator())) {
                    return false;
                }
            }
        }


    }

    /* All clauses have been checked, no mismatch found */
    return true;
}

unsigned int RecordManager::getSize(const string& type) {
    if (regex_match(type, regex("int", regex_constants::icase))) {
        return sizeof(int32_t);
    } else if (regex_match(type, regex("char", regex_constants::icase))) {
        return sizeof(char);
    } else if (regex_match(type, regex("float", regex_constants::icase))) {
        return sizeof(float);
    } else {
        throw MyException("Internal Error: Fail to get the size of type " + type + " !");
    }
}


unsigned int RecordManager::getSize(const vector<AttributeConstraint>& attrList) {
    unsigned int totalSize = 1;
    for (unsigned int i = 0; i < attrList.size(); i++) {
        totalSize += getSize(attrList[i].getType())* attrList[i].getLength();
    }
    return totalSize;
}


vector<string> RecordManager::getDataInString(const char * data, const vector<AttributeConstraint>& attributeList) {
    unsigned int offset = 1; // ignore flag
    vector<string> result;

    for (unsigned int i = 0; i < attributeList.size(); i++) { /* For each attribute */
        stringstream stream;
        if ("INT" == attributeList[i].getType()) {
            int32_t intBuff;
            memcpy_s(&intBuff, sizeof(int32_t), data + offset, sizeof(int32_t));
            offset += sizeof(int32_t);
            stream << intBuff;
            result.push_back(stream.str());
        } else if ("FLOAT" == attributeList[i].getType()) {
            float floatBuff;
            memcpy_s(&floatBuff, sizeof(float), data + offset, sizeof(float));
            offset += sizeof(float);
            stream << floatBuff;
            result.push_back(stream.str());
        } else if ("CHAR" == attributeList[i].getType()) {
            string stringBuff = "";
            unsigned int length = attributeList[i].getLength();
            for (unsigned int j = 0; j < length; j++) {
                char temp;
                memcpy_s(&temp, sizeof(char), data + offset, sizeof(char));
                stringBuff.push_back(temp);
                offset++;
            }
            result.push_back(stringBuff);
        } else {
            throw MyException("Internal Error: Type \"" + attributeList[i].getType() + "\" is not supported!");
        }
    }
    return result;
}


ResultSet RecordManager::searchOrDelete(const Table & table, vector<Clause>& clauses, const bool deleteFlag, vector<RecordPointer>& finalRecords) {
    ResultSet result;

    /* Initial column names */
    vector<string> columnNames;
    for (unsigned int i = 0; i < table.attrList.size(); i++) {
        columnNames.push_back(table.attrList[i].getColumnName());
    }
    result.setColumnNames(columnNames);

    vector<Index> indexes = API::getIndex(table.name);
    Clause* pClauseWithIndex = nullptr;
    Index indexUsed;

    /* First pick a attribute that has index */
    for (unsigned int i = 0; i < clauses.size() && nullptr == pClauseWithIndex; i++) { /* For each clause */
        for (unsigned int j = 0; j < indexes.size(); j++) { /* Check if the attribute in the clause is in the index list */
            if (clauses[i].getAttribute() == indexes[j].attr) { /* IN */
                pClauseWithIndex = new Clause(clauses[i]);
                indexUsed = indexes[j];
                clauses.erase(clauses.begin() + i);
                break;
            }
        }
    }

    /* If index exists, then use it first */
    vector<RecordPointer> filteredRecords;
    if (nullptr != pClauseWithIndex) { /* Index exists */
        /* Find the type of the attribute with index */
        string type;
        unsigned int i;
        for (i = 0; i < table.attrList.size(); i++) {
            if (table.attrList[i].getColumnName() == pClauseWithIndex->getAttribute()) {
                type = table.attrList[i].getType();
                break;
            }
        }
        if (i > table.attrList.size()) { /* Not found */
            throw MyException("Internal Error: Fail to locate index \"" + indexUsed.name + "\"!");
        } else if ("INT" == type) {
            int32_t lowerBound = std::numeric_limits<int32_t>::min();
            int32_t upperBound = std::numeric_limits<int32_t>::max();
            handleIndexClauses(table, lowerBound, upperBound, pClauseWithIndex, filteredRecords, indexUsed);
        } else if ("FLOAT" == type) {
            // TODO
            float lowerBound = std::numeric_limits<float>::min();
            float upperBound = std::numeric_limits<float>::max();
            handleIndexClauses(table, lowerBound, upperBound, pClauseWithIndex, filteredRecords, indexUsed);
        } else if ("CHAR" == type) {
            string lowerBound = "";
            string upperBound = "";
            for (unsigned int j = 0; j < 256; j++) {
                upperBound.push_back('A');
            }
            handleIndexClauses(table, lowerBound, upperBound, pClauseWithIndex, filteredRecords, indexUsed);
        } else {
            throw MyException("Internal Error: Unknown type \"" + type + "\" encountered!");
        }
    }

    /* Check other clauses */
    char *data= nullptr;
    unsigned int deletedCount = 0;
    if (nullptr != pClauseWithIndex) { /* Index has been used, check filteredRecords */
        for (unsigned int i = 0; i < filteredRecords.size(); i++) {
            data = retrieveData(table, filteredRecords[i]);
            if (isClausesSatisfied(data, table.attrList, clauses)) { /* A satisfying record found */
                finalRecords.push_back(filteredRecords[i]);
                result.appendRow(getDataInString(data, table.attrList));
                if (deleteFlag) { /* A delete request */
                    data[0] = (char)false;
                    deletedCount++;
                } 
            }
        }
    } else { /* No index has been used, check the entire table */
        RecordPointer position(0, 0);
        while (position.getBlockNo() < table.end.getBlockNo() || 
            (position.getBlockNo() == table.end.getBlockNo() && position.getBlockOffset() < table.end.getBlockOffset())) {
            /* Traverse the table from begining to end */
            data = retrieveData(table, position);
            if (isClausesSatisfied(data, table.attrList, clauses)) { /* A satisfying record found */
                finalRecords.push_back(position);
                result.appendRow(getDataInString(data, table.attrList));
                if (deleteFlag) { /* A delete request */
                    data[0] = (char)false;
                    deletedCount++;
                }
            }
            position.next(getSize(table.attrList), BufferManager::blockSize); /* Go to next position */
        }
    }
    if (deleteFlag) { /* Update header */
        BufferManager::getDataHeader(table.name).updateRowCount(BufferManager::getDataHeader(table.name).getRowCount() - deletedCount);
    }
    if (nullptr != pClauseWithIndex) {
        delete pClauseWithIndex;
    }
    return result;
}

ResultSet RecordManager::deleteFrom(const Table & table, vector<Clause> clauses) {
    vector<RecordPointer> finalRecords;
    return searchOrDelete(table, clauses, true, finalRecords);
}


ResultSet RecordManager::search(const Table & table, vector<Clause> clauses) {
    vector<RecordPointer> finalRecords;
    return searchOrDelete(table, clauses, false, finalRecords);
}

ResultSet RecordManager::search(const Table & table, vector<Clause> clauses, vector<RecordPointer>& results) {
    return searchOrDelete(table, clauses, false, results);
}

void RecordManager::createTable(const string & tableName) {
    BufferManager::createDataFile(tableName);
}

void RecordManager::dropTable(const string & tableName) {
    BufferManager::deleteFile(tableName, "data");
}

void RecordManager::Insert(const Table & table, vector<string>& values) {
    if (table.attrList.size() != values.size()) {
        throw MyException("Error: Illegal number of values!");
    } else { /* value count is legal */
        RecordPointer endOfFile = table.end;
        //endOfFile.next(getSize(table.attrList), BufferManager::blockSize); /* Go to the next position */
        //if (endOfFile.getBlockOffset() >= 1470) {
        //    cout << "Warning!" << endl;
        //}
        try {
            BufferManager::getBlock(table.name, "data", endOfFile.getBlockNo());
        } catch (MyException ex) {
            if (ex.getMessage() == "Internal Error: The file does not have that many blocks!\n") {
                BufferManager::createBlock(table.name, "data");
            }
        }

        /* Check for unique/primary key constarints */
        for (unsigned int i = 0; i < table.attrList.size(); i++) {
            const AttributeConstraint& dsh = table.attrList[i];
            if (table.attrList[i].isUnique()) {
                vector<Clause> checkedClauses;
                checkedClauses.push_back(Clause(table.attrList[i].getColumnName(), values[i], "="));
                vector<RecordPointer> results;
                search(table, checkedClauses, results);
                if (results.size() > 0) { /* Violation found */
                    throw MyException("Error: Unique constraint is violated!");
                }
            }
        }
        BufferBlock& block = BufferManager::getBlock(table.name, "data", endOfFile.getBlockNo());
        block.pinBlock();
        char* data = retrieveData(table, endOfFile);
        memset(data, 0, getSize(table.attrList));
        unsigned int offset = 0;
        bool flag = true;
        memcpy_s(data, sizeof(bool), &flag, sizeof(bool));
        offset += sizeof(bool); /* Active flag */


        for (unsigned int i = 0; i < table.attrList.size(); i++) {
            stringstream stream(values[i]);
            if ("INT" == table.attrList[i].getType()) {
                int32_t intBuff;
                stream >> intBuff;
                if (stream.fail()) {
                    throw MyException("Error: Illegal value \"" + values[i] + "\"!");
                } else {
                    memcpy_s(data + offset, sizeof(int32_t), &intBuff, sizeof(int32_t));
                    offset += sizeof(int32_t);
                }
            } else if ("FLOAT" == table.attrList[i].getType()) {
                float floatBuff;
                stream >> floatBuff;
                if (stream.fail()) {
                    throw MyException("Error: Illegal value \"" + values[i] + "\"!");
                } else {
                    memcpy_s(data + offset, sizeof(float), &floatBuff, sizeof(float));
                    offset += sizeof(float);
                }
            } else if ("CHAR" == table.attrList[i].getType()) {
                // one line removed
                if (values[i].length() > table.attrList[i].getLength()) {
                    throw MyException("Error: Input string is too long! (\"" + values[i] + "\")!");
                }
                memcpy_s(data + offset, sizeof(char) * values[i].length(), values[i].c_str(), sizeof(char) * values[i].length());
                offset += sizeof(char) * table.attrList[i].getLength();
            } else {
                throw MyException("Internal Error: Record for table " + table.name + " might be ruined because of illegal type encountered!");
            }

        }

        block.unpinBlock();
        BufferManager::getDataHeader(table.name).updateRowCount(BufferManager::getDataHeader(table.name).getRowCount() + 1);
    }




}




