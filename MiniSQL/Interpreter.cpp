/**********************************************************************************************//**
 * @file    Interpreter.cpp
 *
 * @brief   Implements the interpreter class.
 **************************************************************************************************/

#include "Interpreter.h"
#include "BufferManager.h"
#include "ResultSet.h"
#include "AttributeConstraint.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <vector>
#include "API.h"

using namespace std;

/**********************************************************************************************//**
 * @fn  vector<Clause> Interpreter::parseWhere()
 *
 * @brief   Parses WHERE clauses.
 *
 * @author  Chen
 * @date    6/8/2016
 *
 * @exception   MyException Thrown when My error condition occurs.
 *
 * @return  A vector<Clause>
 **************************************************************************************************/

vector<Clause> Interpreter::parseWhere() {
    vector<Clause> allClauses;
    while (statementStream.rdbuf()->in_avail() > 1) { /* Still something in the statement other than the final linefeed is left */
        string attribute, oper, value;
        statementStream >> attribute >> oper >> value;
        if (!statementStream.good()) {
            throw MyException("Syntax Error: Illegal clause after WHERE!");
        }
        allClauses.push_back(Clause(attribute, value, oper));
        string buffer;
        statementStream >> buffer;
        if (!regex_match(buffer, regex("and", regex_constants::icase)) && statementStream.rdbuf()->in_avail() > 1) {
            throw MyException("Syntax Error: Illegal clause after WHERE!");
        }
    }
    return allClauses;
}

/**********************************************************************************************//**
 * @fn  void Interpreter::select()
 *
 * @brief   Handles SELECT statements
 *
 * @author  Chen
 * @date    6/9/2016
 *
 * @exception   MyException Thrown when syntax error occurs.
 **************************************************************************************************/

void Interpreter::select() {
    string buffer;
    string tableName; /* name of the selected table */
    vector<Clause> whereClauses; /* clauses after WHERE */

    statementStream >> buffer; /* retrieves attribute name */
    if (buffer != "*") {
        throw MyException("attribute name can only be \"*\"!");
    }
    statementStream >> buffer; /* retrieve keyword FROM */
    if (!regex_match(buffer, regex("from", regex_constants::icase))) {
        throw MyException("Syntax error: Keyword \"FROM\" expected!");
    }
    statementStream >> tableName; /* retrieve table name */
    if (statementStream.rdbuf()->in_avail() > 1) { /* still WHERE clauses */
        statementStream >> buffer; /* retrieve keyword WHERE */
        if (!regex_match(buffer, regex("where", regex_constants::icase))) {
            throw MyException("Syntax error: Keyword \"WHERE\" expected!");
        }
        whereClauses = parseWhere();
    }
    /* Call API here with tableName and whereClauses */
    result = API::search(tableName, whereClauses);
    //cout << "****Call API here****" << endl;
    //cout << whereClauses[0].getAttribute() << ' ' << whereClauses[0].getOperator() << ' ' << whereClauses[0].getValue() << endl;
    //cout << whereClauses[1].getAttribute() << ' ' << whereClauses[1].getOperator() << ' ' << whereClauses[1].getValue() << endl;
}

void Interpreter::createTable() {

    string tableName, buffer;
    vector<AttributeConstraint> attributes;
    bool isPrimaryKeyAssigned = false;
    statementStream >> tableName;
    statementStream >> buffer; /* Read in opening parenthesis */
    if ("(" != buffer) {
        throw MyException("Syntax Error: An opening parenthesis expected after table name!");
    }
    while (statementStream.rdbuf()->in_avail() > 0) {
        statementStream >> buffer;
        if (")" == buffer) { /* final closing parenthesis encountered */
            break;
        } else {
            string columnName = buffer;
            string type;
            statementStream >> type;
            if (regex_match(columnName, regex("primary", regex_constants::icase)) &&
                regex_match(type, regex("key", regex_constants::icase))) {              /* Assigning a primary key */
                if (isPrimaryKeyAssigned) { /* The system only supports one attribute to be the primary key */
                    throw MyException("Error: Only one primary key is allowed!");
                }
                isPrimaryKeyAssigned = true;
                statementStream >> buffer; /* Read in the opening parenthesis '(' */
                if ("(" != buffer) {
                    throw MyException("Syntax Error: An opening parenthesis expected after keyword \"PRIMARY KEY\"!");
                }
                statementStream >> buffer; /* Read in the column name who is going to be set as the primary key */
                unsigned int i;/* iterator */
                for (i = 0; i < attributes.size(); i++) { /* Find that attribute record */
                    if (attributes[i].getColumnName() == buffer) { /* Found */
                        attributes[i].setPrimaryKey();
                        break;
                    }
                }
                if (i >= attributes.size()) { /* Record not found */
                    throw MyException("Error: Fail to set primary key, attribute \"" + buffer + "\" not found!");
                }
                statementStream >> buffer; /* Read in closing parenthesis ')' */
                if (")" != buffer) {
                    throw MyException("Syntax Error: A closing parenthesis expected after keyword \"PRIMARY KEY\"!");
                }
            } else { /* Add a new attribute */
                bool isUnique = false;
                unsigned int length = 1;
                if (regex_match(type, regex("char", regex_constants::icase))) {
                    statementStream >> buffer; /* Read in the opening parenthesis '(' */
                    if ("(" != buffer) {
                        throw MyException("Syntax Error: An opening parenthesis expected after type specifier \"CHAR\"!");
                    }
                    statementStream >> length; /* Read in the length of the character array */
                    if (!statementStream.good()) {
                        throw MyException("Syntax Error: Illegal length of the character array!");
                    }
                    statementStream >> buffer; /* Read in closing parenthesis ')' */
                    if (")" != buffer) {
                        throw MyException("Syntax Error: A closing parenthesis expected after keyword \"PRIMARY KEY\"!");
                    }
                }
                char symbol; /* Read in UNIQUE */
                statementStream >> symbol;
                statementStream.putback(symbol);
                if (symbol == 'u' || symbol == 'U') {
                    statementStream >> buffer;
                    if (!regex_match(buffer, regex("unique", regex_constants::icase))) {
                        throw MyException("Syntax Error: Check the syntax around \"" + buffer + "\"!");
                    } else {
                        isUnique = true;
                    }
                }
                /* Check if an attribute with the same name has already existed */
                for (unsigned int i = 0; i < attributes.size(); i++) {
                    if (attributes[i].getColumnName() == columnName) {
                        throw MyException("Syntax Error: Duplicated attribute \"" + columnName + "\"!");
                    }
                }
                /* Add that attribute */
                attributes.push_back(AttributeConstraint(columnName, type, false, isUnique, length));
            }
            statementStream >> buffer; /* Read in a comma or a closing parenthesis */
            if (!statementStream.good()) {
                throw MyException("Syntax Error: Check the syntax after keyword \"CREATE\"");
            }
            if (")" == buffer) {
                break;
            } else if ("," != buffer) {
                throw MyException("Syntax Error: A separator expected instead of \"" + buffer + "\"!");
            }
        }


    }

    if (statementStream.rdbuf()->in_avail() > 0) {
        getline(statementStream, buffer);
        if (!regex_match(buffer, regex("\\s*"))) {
            throw MyException("Syntax Error: Unknown expressions after the closing parenthesis!");
        }
    }

    // Call API here with tableName and attributes
    API::createTable(tableName, attributes);
    //cout << "****Call API here****" << endl;
    //cout << "Size: " << attributes.size() << endl;
    //cout << attributes[0].getColumnName() << " " << attributes[0].getType() << "(" << attributes[0].getLength() << ") UNIQUE:" << attributes[0].isUnique() << " PRIMARY KEY: " << attributes[0].isPrimaryKey() << endl;
    //cout << attributes[1].getColumnName() << " " << attributes[1].getType() << "(" << attributes[1].getLength() << ") UNIQUE:" << attributes[1].isUnique() << " PRIMARY KEY: " << attributes[1].isPrimaryKey() << endl;
    //cout << attributes[2].getColumnName() << " " << attributes[2].getType() << "(" << attributes[2].getLength() << ") UNIQUE:" << attributes[2].isUnique() << " PRIMARY KEY: " << attributes[2].isPrimaryKey() << endl;

}

void Interpreter::createIndex() {
    string indexName, tableName, attributeName, buffer;
    statementStream >> indexName; /* Read in index name */
    statementStream >> buffer; /* Read in keyword ON */
    if (!regex_match(buffer, regex("on", regex_constants::icase))) {
        throw MyException("Syntax Error: Keyword \"ON\" expected!");
    }
    statementStream >> tableName; /* Read in table name */
    statementStream >> buffer; /* Read in opening parenthesis '(' */
    if ("(" != buffer) {
        throw MyException("Syntax Error: An opening parenthesis expected!");
    }
    statementStream >> attributeName; /* Read in attribute name */
    statementStream >> buffer; /* Read in closing parenthesis ')' */
    if (")" != buffer) {
        throw MyException("Syntax Error: A closing parenthesis expected!");
    }


    if (statementStream.rdbuf()->in_avail() > 0) {
        getline(statementStream, buffer);
        if (!regex_match(buffer, regex("\\s*"))) {
            throw MyException("Syntax Error: Unknown expressions after the closing parenthesis!");
        }
    }
    // Call API here with indexName, attributeName and tableName
    API::createIndex(tableName, indexName, attributeName);
    //cout << "****Call API here****" << endl;
    //cout << "indexName: " << indexName << "; attributeName: " << attributeName << "; tableName: " << tableName << endl;

}

void Interpreter::create() {
    string whatToCreate; /* can be TABLE or INDEX */


    statementStream >> whatToCreate;
    if (regex_match(whatToCreate, regex("table", regex_constants::icase))) {
        createTable();
    } else if (regex_match(whatToCreate, regex("index", regex_constants::icase))) {
        createIndex();
    } else {
        throw MyException("Syntax Error: Keyword \"TABLE\" or \"INDEX\" expected after \"CREATE\"!");
    }
}

void Interpreter::drop() {
    string whatToDrop; /* Can be TABLE or INDEX */
    statementStream >> whatToDrop;
    if (regex_match(whatToDrop, regex("table", regex_constants::icase))) {
        string tableName, buffer;
        statementStream >> tableName;
        if (!statementStream.good()) {
            throw MyException("Syntax Error: Table name expected after keyword \"TABLE\"!");
        } else if (statementStream.rdbuf()->in_avail() > 0) {
            getline(statementStream, buffer);
            if (!regex_match(buffer, regex("\\s*"))) {
                throw MyException("Syntax Error: Unknown expressions after the table name!");
            }
        }
        // Call API here with tableName
        API::dropTable(tableName);
        //cout << "****Call API here****" << endl;
        //cout << "DROP TABLE: " << tableName << endl;

    } else if (regex_match(whatToDrop, regex("index", regex_constants::icase))) {
        string indexName, buffer;
        statementStream >> indexName;
        if (!statementStream.good()) {
            throw MyException("Syntax Error: Index name expected after keyword \"TABLE\"!");
        } else if (statementStream.rdbuf()->in_avail() > 0) {
            getline(statementStream, buffer);
            if (!regex_match(buffer, regex("\\s*"))) {
                throw MyException("Syntax Error: Unknown expressions after the index name!");
            }
        }
        // Call API here with indexName
        API::dropIndex(indexName);
        //cout << "****Call API here****" << endl;
        //cout << "DROP INDEX: " << indexName << endl;

    } else {
        throw MyException("Syntax Error: Only TABLE or INDEX can be dropped!");
    }
}

void Interpreter::insertInto() {
    string tableName, buffer;
    vector<string> values;
    statementStream >> tableName; /* Read in table name */
    statementStream >> buffer; /* Read in keyword VALUES */
    if (!regex_match(buffer, regex("values", regex_constants::icase))) {
        throw MyException("Syntax Error: Keyword \"VALUES\" expected after table name!");
    }
    statementStream >> buffer; /* Read in opening parenthesis */
    if ("(" != buffer) {
        throw MyException("Syntax Error: An opening parenthesis expected after keyword \"VALUES\"!");
    }
    while (true) {
        statementStream >> buffer; /* Read in the value */
        if (regex_match(buffer, regex("\'.*\'"))) {
            buffer.erase(0, 1);
            buffer.erase(buffer.length() - 1, 1); /* Get rid of quotation marks */
        }
        values.push_back(buffer); /* Push the new value into the container */
        statementStream >> buffer; /* Read in the separtator, can be comma or closing parenthesis */
        if (")" == buffer) {
            break; /* End of the VALUES clause encountered */
        } else if ("," != buffer) {
            throw MyException("Syntax Error: A separator expected in the VALUES clause!");
        }
    }
    /* Check if there is anything unknown left in the statement */
    if (statementStream.rdbuf()->in_avail() > 0) {
        getline(statementStream, buffer);
        if (!regex_match(buffer, regex("\\s*"))) {
            throw MyException("Syntax Error: Unknown expressions after VALUES clause!");
        }
    }

    // Call API here with tableName and values
    API::insertTuple(tableName, values);
    //cout << "****Call API here****" << endl;
    //cout << "Table to be inserted: " << tableName << endl;
    //cout << "Values: ";
    //for (unsigned int i = 0; i < values.size(); i++) {
    //    cout << values[i] << "\t";
    //}
}

void Interpreter::deleteFrom() {
    string tableName, buffer;
    vector<Clause> clauses;
    statementStream >> tableName; /* Read in the table name */

    if (statementStream.rdbuf()->in_avail() > 0) { /* WHERE clause expected */
        getline(statementStream, buffer);
        if (!regex_match(buffer, regex("\\s*"))) {
            //stringstream tempStream(buffer); /* A new string stream */
            //tempStream >> buffer; /* Read in keyword WHERE */
            statementStream.seekg(-(int)buffer.length(), ios::cur);
            statementStream >> buffer;
            if (!regex_match(buffer, regex("where", regex_constants::icase))) {
                throw MyException("Syntax Error: Unknown expressions after the table name!");
            } else {
                clauses = parseWhere();
            }

        }
    }

    API::deleteTuple(tableName, clauses);
    //cout << "****Call API here****" << endl;
    //cout << "Table to be deleted from: " << tableName << endl;
    //cout << "WHERE clauses: " << endl;
    //for (unsigned int i = 0; i < clauses.size(); i++) {
    //    cout << clauses[i].getAttribute() << ' ' << clauses[i].getOperator() << ' ' << clauses[i].getValue() << endl;
    //}

}

void Interpreter::execFile() {
    string fileName;
    statementStream >> fileName;
    if (!regex_match(fileName, regex(".*.sql", regex_constants::icase))) { /* Filename must has the postfix .sql */
        throw MyException("Error: Illegal filename!");
    }
    ifstream SQLFile(fileName);  /* Open the file */
    if (!SQLFile.good()) {
        throw MyException("Error: Cannot open the file!");
    } else {
        while (true) {
            string statement;
            char temp;
            do {
                temp = SQLFile.get();
                statement.push_back(temp);
            } while (';' != temp && SQLFile.good()); /* Read in a statement */
            if (!SQLFile.good()) {
                throw MyException("Syntax Error: Statement must end with a semicolon!");
            }
            cout << "Executing SQL statement: " << statement << endl;
            if (executeStatement(statement)) {
                printResults();
            } else {
                cout << "Query has been executed successfully!" << endl << endl;
            }
            /* Get rid of white spaces after the semicolon */
            while (SQLFile.good()) {
                temp = SQLFile.peek();
                if ('\n' == temp || '\r' == temp) {
                    string buffer;
                    getline(SQLFile, buffer);
                } else if (regex_match(string(&temp, 1), regex("\\s"))) {
                    SQLFile.seekg(1, ios::cur); /* move the cursor forward */
                } else {
                    break;
                }
            }
            if (!SQLFile.good()) {
                break;
            }
        }
    }
    SQLFile.close();

}

/**********************************************************************************************//**
 * @fn  bool Interpreter::executeStatement(string statement)
 *
 * @brief   Executes the statement given by the parameter.
 *
 * @author  Chen
 * @date    6/9/2016
 *
 * @exception   MyException Thrown when syntax error occurs.
 *
 * @param   statement   The SQL statement.
 *
 * @return  If return true, there are something returned by the database.
 **************************************************************************************************/

bool Interpreter::executeStatement(string statement) {
    /* First add additional spaces before and after operators */
    statement = regex_replace(statement, regex("([^<>=])(=|<>|<|>|<=|>=)([^<>=])"), "$1 $2 $3");
    /* Add additional spaces before and after parenthese and commas */
    statement = regex_replace(statement, regex("(\\(|\\)|,)"), " $1 ");
    /* Then get rid of all consecutive white spaces */
    statement = regex_replace(statement, regex("\\s+"), " ");
    /* Check if the statement terminates with a semicolon */
    if (!regex_match(statement, regex(".*;"))) {
        throw MyException("Syntax error: Statement does not end with a semicolon!");
    } else {
        statement.erase(statement.length() - 1, 1); /* get rid of the semicolon */
    }
    statementStream = stringstream(statement + "\n"); /* Initialize the stream for statement */
    string command; /* User's command, can be SELECT, CREATE, DROP, INSERT INTO, DELETE FROM, EXECFILE or QUIT  */
    statementStream >> command;

    if (regex_match(command, regex("select", regex_constants::icase))) {
        /* SELECT statement */
        select();
        return true; /* SELECT has return value */
    } else if (regex_match(command, regex("create", regex_constants::icase))) {
        /* CREATE statement */
        create(); 
        return false; /* CREATE has no return value */
    } else if (regex_match(command, regex("drop", regex_constants::icase))) {
        /* DROP statement */
        drop();
        return false; /* DROP has no return value */
    } else if (regex_match(command, regex("insert", regex_constants::icase))) {
        statementStream >> command;
        if (!regex_match(command, regex("into", regex_constants::icase))) {
            throw MyException("Command is not supported!");
        } else {
            /* INSERT INTO statement */
            insertInto();
            return false; /* INSERT INTO has no return value */
        }
    } else if (regex_match(command, regex("delete", regex_constants::icase))) {
        statementStream >> command;
        if (!regex_match(command, regex("from", regex_constants::icase))) {
            throw MyException("Command is not supported!");
        } else {
            /* DELETE FROM statement */
            deleteFrom();
            return false; /* DELETE FROM has no return value */
        }
    } else if (regex_match(command, regex("execfile", regex_constants::icase))) {
        /* executes a .SQL file */
        try {
            execFile();
        } catch (MyException ex) {
            cout << ex.getMessage() << endl;
        }
        return false; /* EXECFILE has no return value */
    } else if (regex_match(command, regex("quit", regex_constants::icase))) {
        /* quit the system */
        cout << "Thank you for using miniSQL system!" << endl;
        BufferManager::clear();
        API::quit();
        exit(0);
    } else if (regex_match(command, regex("test", regex_constants::icase))) {
        cout << "Test mode" << endl << endl;
        result.clear();
        result.setColumnNames({ "word1", "word2", "word3" });
        result.appendRow({ "hello", "world", "" });
        result.appendRow({ "good", "afternoon", "" });
        return true;
    } else {
        throw MyException("Command is not supported!");
    }
    return false;
}

/**********************************************************************************************//**
 * @fn  void Interpreter::printResults()
 *
 * @brief   Print results.
 *
 * @author  Chen
 * @date    6/5/2016
 **************************************************************************************************/

void Interpreter::printResults() {
    

    vector<unsigned int> columnWidth;
    unsigned int rowCount = 0; /* number of rows */
    vector<vector<string>> data;
    const unsigned int minWidth = 15;
    const unsigned int borderWidth = 3;

    /* First calculate the column widths */
    /* The column width is the maximum width of all items (and the column name) */
    cout << "+";
    vector<string> columnNames = result.getColumnNames();
    /* Assign widths to be the lengths of column names */
    for (unsigned int i = 0; i < columnNames.size(); i++) {
        columnWidth.push_back(columnNames[i].length());
    }
    /* Check if any item is longer than the colum names */
    while (result.next()) {
        data.push_back(result.getData()); /* Retrieve the data and store it locally */
        for (unsigned int i = 0; i < data[rowCount].size(); i++) {
            if (data[rowCount][i].length() > columnWidth[i]) {
                columnWidth[i] = data[rowCount][i].length();
            }
        }
        rowCount++;
    }
    /* Add borders and print the top line*/
    for (unsigned int i = 0; i < columnNames.size(); i++) {
        columnWidth[i] = (columnWidth[i] + 2 * borderWidth >= minWidth) ? columnWidth[i] + 2 * borderWidth : minWidth;
        cout << setfill('-') << setw(columnWidth[i] + 1) << "+";
    }

    cout << endl;

    /* Then print the column names */
    cout << "+";
    for (unsigned int i = 0; i < columnNames.size(); i++) {
        int borderBefore = (columnWidth[i] - columnNames[i].length()) / 2;
        int borderAfter = columnWidth[i] - columnNames[i].length() - borderBefore;

        /* spaces before the column name */
        for (int i = 0; i < borderBefore; i++) {
            cout << " ";
        }
        /* the column name */
        cout << setfill(' ') << setw(columnWidth[i] - borderBefore - borderAfter) << columnNames[i];

        /* spaces after the column name */
        for (int i = 0; i < borderAfter; i++) {
            cout << " ";
        }

        cout << "+";
    }
    cout << endl;

    /* Next the middle line */
    cout << "+";
    for (unsigned int i = 0; i < columnNames.size(); i++) {
        cout << setfill('-') << setw(columnWidth[i] + 1) << "+";
    }
    cout << endl;

    /* Then the contents */
    for (unsigned int row = 0; row < data.size(); row++) {
        cout << "+";
        for (unsigned int col = 0; col < data[row].size(); col++) {

            int borderBefore = (columnWidth[col] - data[row][col].length()) / 2;
            int borderAfter = columnWidth[col] - data[row][col].length() - borderBefore;

            /* spaces before the column name */
            for (int i = 0; i < borderBefore; i++) {
                cout << " ";
            }
            /* the item */
            cout << setw(columnWidth[col] - borderBefore - borderAfter) << setfill(' ') << data[row][col];

            /* spaces after the column name */
            for (int i = 0; i < borderAfter; i++) {
                cout << " ";
            }

            cout << "+"; 
        }
        cout << endl;
    }

    /* Finally the bottom line */
    cout << "+";
    for (unsigned int i = 0; i < columnNames.size(); i++) {
        cout << setfill('-') << setw(columnWidth[i] + 1) << "+";
    }
    cout << endl;
    cout << rowCount << " row(s) in set." << endl << endl;
}
