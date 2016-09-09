/**********************************************************************************************//**
 * @file    ResultSet.h
 *
 * @brief   Declares the result set class.
 **************************************************************************************************/

#pragma once
#include <string>
#include <vector>
#include "MyException.h"

using namespace std;

/**********************************************************************************************//**
 * @class   ResultSet
 *
 * @brief   A result set for query returns
 *
 * @author  Chen
 * @date    6/4/2016
 **************************************************************************************************/

class ResultSet {
private:
    /** @brief   List of names of the columns. */
    vector<string> columnNames;

    /** @brief   The content of the returned table. */
    vector<vector<string>> data;

    /** @brief   Indicate which row in the data is currently refered to. */
    int currentRow;


public:

    /**********************************************************************************************//**
     * @fn  ResultSet::ResultSet();
     *
     * @brief   Default constructor. currentRow is set to -1.
     *
     * @author  Chen
     * @date    6/4/2016
     **************************************************************************************************/
    ResultSet();

    /**********************************************************************************************//**
     * @fn  void ResultSet::clear();
     *
     * @brief   Clears this object to its blank/initial state. currentRow is set to -1.
     *
     * @author  Chen
     * @date    6/5/2016
     **************************************************************************************************/

    void clear();

    /**********************************************************************************************//**
     * @fn  void ResultSet::appendRow(vector<string> newData);
     *
     * @brief   Appends a row to the table data.
     *
     * @author  Chen
     * @date    6/5/2016
     *
     * @param   newData Data of the new row.
     **************************************************************************************************/

    void appendRow(vector<string> newData);

    /**********************************************************************************************//**
     * @fn  bool ResultSet::next();
     *
     * @brief   Moves the row pointer to the next position.
     *          Initially, the row pointer is just before the 0th row.
     *          The first call to this function shifts the pointer to the 0th row.
     *
     * @author  Chen
     * @date    6/4/2016
     *
     * @return  The funtion returns false when the it reaches the end of the table,
     *          and returns true otherwise.
     **************************************************************************************************/
    bool next();

    /**********************************************************************************************//**
     * @fn  vector<string> ResultSet::getData();
     *
     * @brief   Gets the data of the current row.
     *
     * @author  Chen
     * @date    6/4/2016
     *
     * @return  The data of the current row. When the row pointer is illegal, a MyException with 
     *          a corresponding error message is thrown.
     **************************************************************************************************/

    vector<string> getData();

    /**********************************************************************************************//**
     * @fn  vector<string> ResultSet::getColumnNames() const;
     *
     * @brief   Gets column names.
     *
     * @author  Chen
     * @date    6/5/2016
     *
     * @return  The column names.
     **************************************************************************************************/

    vector<string> getColumnNames() const;

    /**********************************************************************************************//**
     * @fn  void ResultSet::setColumnNames(vector<string> columnNames);
     *
     * @brief   Sets column names.
     *
     * @author  Chen
     * @date    6/5/2016
     *
     * @param   columnNames List of names of the columns.
     **************************************************************************************************/

    void setColumnNames(vector<string> columnNames);

};