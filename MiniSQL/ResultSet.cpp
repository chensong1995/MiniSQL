/**********************************************************************************************//**
 * @file    ResultSet.cpp
 *
 * @brief   Implements the result set class.
 **************************************************************************************************/

#include "ResultSet.h"
#include "MyException.h"

/**********************************************************************************************//**
 * @fn  ResultSet::ResultSet()
 *
 * @brief   Default constructor. currentRow is set to -1.
 *
 * @author  Chen
 * @date    6/4/2016
 **************************************************************************************************/

ResultSet::ResultSet() {
    currentRow = -1;
}

/**********************************************************************************************//**
 * @fn  void ResultSet::clear()
 *
 * @brief   Clears this object to its blank/initial state. currentRow is set to -1.
 *
 * @author  Chen
 * @date    6/5/2016
 **************************************************************************************************/

void ResultSet::clear() {
    columnNames.clear();
    data.clear();
    currentRow = -1;
}



/**********************************************************************************************//**
 * @fn  bool ResultSet::next()
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

bool ResultSet::next() {
    currentRow++;
    if ((int)data.size() <= currentRow) {
        return false;
    } else {
        return true;
    }
}

/**********************************************************************************************//**
 * @fn  vector<string> ResultSet::getData()
 *
 * @brief   Gets the data of the current row.
 *
 * @author  Chen
 * @date    6/4/2016
 *
 * @return  The data of the current row. When the row pointer is illegal, a MyException with
 *          a corresponding error message is thrown.
 **************************************************************************************************/

vector<string> ResultSet::getData() {
    if ((int)data.size() <= currentRow || currentRow < 0) { // too big or too small
        throw MyException("Illegal row pointer!");
    }
    return data[currentRow];
}

/**********************************************************************************************//**
 * @fn  vector<string> ResultSet::getColumnNames() const
 *
 * @brief   Gets column names.
 *
 * @author  Chen
 * @date    6/5/2016
 *
 * @return  The column names.
 **************************************************************************************************/

vector<string> ResultSet::getColumnNames() const {
    return columnNames;
}

void ResultSet::setColumnNames(vector<string> columnNames) {
    this->columnNames = columnNames;
}

/**********************************************************************************************//**
 * @fn  void ResultSet::appendRow(vector<string> newData)
 *
 * @brief   Appends a row to the table data.
 *
 * @author  Chen
 * @date    6/5/2016
 *
 * @param   newData Data of the new row.
 **************************************************************************************************/

void ResultSet::appendRow(vector<string> newData) {
    data.push_back(newData);
}
