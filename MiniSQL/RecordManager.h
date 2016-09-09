#pragma once
#include "ResultSet.h"
#include "Clause.h"
#include "com.h"
#include "MyException.h"

using namespace std;

class RecordManager {
private:

    static RecordPointer illegalPointer;


    /** oper:    =, <>, <, >, <= or >= */
    template <typename T>
    static const bool checkSingleClause(const T& valueInRecord, const T& valueInClause, const string& oper) {
        if ("=" == oper) {
            return valueInRecord == valueInClause;
        } else if ("<>" == oper) {
            return valueInRecord != valueInClause;
        } else if ("<" == oper) {
            return valueInRecord < valueInClause;
        } else if (">" == oper) {
            return valueInRecord > valueInClause;
        } else if ("<=" == oper) {
            return valueInRecord <= valueInClause;
        } else if (">=" == oper) {
            return valueInRecord >= valueInClause;
        } else {
            throw MyException("Internal Error: Illegal operator \"" + oper + "\"!");
        }
    }

    /** oper:    =, <, >, <= or >= */
    /**          <> can NOT be handled */
    template <typename T>
    static const void assignBounds(T& lowerBound, T& upperBound, const Clause& clause) {
        stringstream stream(clause.getValue());
        if ("=" == clause.getOperator()) {
            stream >> lowerBound;
            upperBound = lowerBound;
        } else if ("<" == clause.getOperator() || "<=" == clause.getOperator()) {
            stream >> upperBound;
        } else if (">" == clause.getOperator() || ">=" == clause.getOperator()) {
            stream >> lowerBound;
        } else {
            throw MyException("Internal Error: Illegal operator \"" + clause.getOperator() + "\"!");
        }
        if (stream.fail()) {
            throw MyException("Error: Illegal value \"" + clause.getValue() + "\"!");
        }
    }

    static char* retrieveData(const Table& table, const RecordPointer& position);

    template <typename T>
    static void handleIndexClauses(const Table& table, T& lowerBound, T& upperBound, const Clause* const pClauseWithIndex, vector<RecordPointer>& filteredRecords, Index& indexUsed) {
        if ("<>" == pClauseWithIndex->getOperator()) { /* Handle "<>" operator */
            T origUpper = upperBound;
            stringstream stream(pClauseWithIndex->getValue());
            /* First half: those smaller than the value */
            stream >> upperBound;
            if (stream.fail()) {
                throw MyException("Error: Illegal value \"" + pClauseWithIndex->getValue() + "\"!");
            }
            RecordPointer pos = API::getPointerBetween(indexUsed, lowerBound, upperBound);
            while (pos != illegalPointer) {
                filteredRecords.push_back(pos);
            }
            /* Second half: those bigger than the value */
            lowerBound = upperBound;
            upperBound = origUpper;
            pos = API::getPointerBetween(indexUsed, lowerBound, upperBound);
            while (pos != illegalPointer) {
                filteredRecords.push_back(pos);
            }
        } else { /* Other operators */
            assignBounds(lowerBound, upperBound, *pClauseWithIndex);
            RecordPointer pos = API::getPointerBetween(indexUsed, lowerBound, upperBound);
            while (pos != illegalPointer) {
                filteredRecords.push_back(pos);
            }
            /* Check the first and last record when handling ">=" or "<=" */
            if (">=" == pClauseWithIndex->getOperator() || "<=" == pClauseWithIndex->getOperator()) {
                vector<Clause> theClause;
                char* data = nullptr;
                theClause.push_back(*pClauseWithIndex);
                /* Check first record */
                data = retrieveData(table, filteredRecords.front());
                if (!isClausesSatisfied(data, table.attrList, theClause)) { /* Not satisfied */
                    filteredRecords.erase(filteredRecords.begin());
                }
                /* Check last record */
                data = retrieveData(table, filteredRecords.back());
                if (!isClausesSatisfied(data, table.attrList, theClause)) { /* Not satisfied */
                    filteredRecords.erase(filteredRecords.end());
                }
            }
        }
    }

    static const bool isClausesSatisfied(const char* data, const vector<AttributeConstraint>& attributeList, const vector<Clause>& clauses);


    static unsigned int getSize(const string& type);

    static vector<string> getDataInString(const char* data, const vector<AttributeConstraint> & attributeList);

    /* deleteFlag == true  : delete
       deleteFlag == false : search */
    static ResultSet searchOrDelete(const Table & table, vector<Clause>& clauses, const bool deleteFlag, vector<RecordPointer>& finalRecords);

public:

    static unsigned int getSize(const vector<AttributeConstraint>& attrList);

    static ResultSet deleteFrom(const Table & table, vector<Clause> clauses);

    static ResultSet search(const Table & table, vector<Clause> clauses);

    static ResultSet search(const Table & table, vector<Clause> clauses, vector<RecordPointer>& results);

    static void createTable(const string& tableName);

    static void dropTable(const string& tableName);

    static void Insert(const Table& table, vector<string>& values);

};