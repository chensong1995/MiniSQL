/**********************************************************************************************//**
 * @file    Interpreter.h
 *
 * @brief   Declares the interpreter class.
 **************************************************************************************************/

#pragma once
#include "ResultSet.h"
#include "Clause.h"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

/**********************************************************************************************//**
 * @class   Interpreter
 *
 * @brief   The interpreter, which gets a SQL query, executes it, and return the result (if has).
 *
 * @author  Chen
 * @date    6/4/2016
 **************************************************************************************************/

class Interpreter {
private:

    /** @brief   The stringstream for the query statement. */
    stringstream statementStream;

    /** @brief   The result of execution. */
    ResultSet result;

    /**********************************************************************************************//**
     * @fn  vector<Clause> Interpreter::parseWhere();
     *
     * @brief   Parses WHERE clauses.
     *
     * @author  Chen
     * @date    6/8/2016
     *
     * @return  A vector<Clause>
    *
     * @exception   MyException Thrown when My error condition occurs.
     *
     * @return  A vector<Clause>
     **************************************************************************************************/

    vector<Clause> parseWhere();

    /**********************************************************************************************//**
     * @fn  void Interpreter::select();
     *
     * @brief   Handles SELECT statements.
     *
     * @author  Chen
     * @date    6/9/2016
     *
    * @exception   MyException Thrown when syntax error occurs.
    **************************************************************************************************/

    void select();

    void createTable();

    void createIndex();

    void create();

    void drop();

    void insertInto();

    void deleteFrom();

    void execFile();


public:

    /**********************************************************************************************//**
     * @fn  bool Interpreter::executeStatement(string statment);
     *
     * @brief   Executes the statement given by the parameter.
     *
     * @author  Chen
     * @date    6/4/2016
     * 
     * @exception   MyException Thrown when syntax error occurs.
     *
     * @param   statement    The SQL statement.
     *
     * @return  If return true, there are something returned by the database.
     **************************************************************************************************/
    bool executeStatement(string statement);

    /**********************************************************************************************//**
     * @fn  void Interpreter::printResults();
     *
     * @brief   Prints the results.
     *
     * @author  Chen
     * @date    6/4/2016
     **************************************************************************************************/

    void printResults();
};