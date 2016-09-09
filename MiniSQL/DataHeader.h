/**********************************************************************************************//**
 * @file    DataHeader.h
 *
 * @brief   Declares the data header class.
 **************************************************************************************************/

#pragma once
#include <string>
#include <cstdint>
#include "RecordPointer.h"
#include "Header.h"

using namespace std;

/**********************************************************************************************//**
 * @class   DataHeader
 *
 * @brief   The header of .date files.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

class DataHeader : public Header {
private:
    /** @brief   Name of the table. */
    string tableName;
    /** @brief   Number of rows. */
    uint32_t rowCount;
    /** @brief   A pointer to the first available row. */
    RecordPointer pFirstAvailRow;
    /** @brief   Size of the header in the .data file. */
    static const int headerSize = 100;
    /** @brief   Size of the table name within the index. */
    static const int tableNameSize = 64;
public:

    /**********************************************************************************************//**
     * @fn  DataHeader::DataHeader(const char* BinaryHeader);
     *
     * @brief   Constructor, which converts the physical binary file header into member variables.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @param   BinaryHeader    The physical binary file header.
     **************************************************************************************************/

    DataHeader(const char* BinaryHeader);

    /**********************************************************************************************//**
     * @fn  const string DataHeader::getTableName() const;
     *
     * @brief   Gets table name.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @return  The table name.
     **************************************************************************************************/

    const string getTableName() const;


    /**********************************************************************************************//**
     * @fn  const uint32_t DataHeader::getRowCount() const;
     *
     * @brief   Gets row count.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @return  The row count.
     **************************************************************************************************/

    const uint32_t getRowCount() const;


    /**********************************************************************************************//**
     * @fn  const RecordPointer DataHeader::getPointerToFirstAvailRow() const;
     *
     * @brief   Gets pointer to first available row.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @return  The pointer to first available row.
     **************************************************************************************************/

    const RecordPointer getPointerToFirstAvailRow() const;

    /**********************************************************************************************//**
     * @fn  void DataHeader::updateRowCount(const uint32_t newCount);
     *
     * @brief   Updates the row count described by newCount.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @param   newCount    Number of news.
     **************************************************************************************************/

    void updateRowCount(const uint32_t newCount);


    void updatePointerToFirstAvailRow(const RecordPointer& pointer);

};