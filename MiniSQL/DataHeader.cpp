/**********************************************************************************************//**
 * @file    DataHeader.cpp
 *
 * @brief   Implements the data header class.
 **************************************************************************************************/

#include "DataHeader.h"
#include <memory>

/**********************************************************************************************//**
 * @fn  DataHeader::DataHeader(const char * BinaryHeader)
 *
 * @brief   Constructor, which converts the physical binary file header into member variables.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @param   BinaryHeader    The physical binary file header.
 **************************************************************************************************/

DataHeader::DataHeader(const char * BinaryHeader) : pFirstAvailRow(0, 0) {
    headerType = "data";

    char buff[tableNameSize];
    memcpy_s(buff, tableNameSize, BinaryHeader, tableNameSize);
    tableName = string(buff); /* Retrieve the table name */
    memcpy_s(&blockSize, sizeof(blockSize), 
        BinaryHeader + tableNameSize, 
        sizeof(blockSize)); /* Retrieve the block size */
    memcpy_s(&rowCount, sizeof(rowCount), 
        BinaryHeader + tableNameSize + sizeof(blockSize),
        sizeof(rowCount)); /* Retrieve the row count */
    memcpy_s(&blockCount, sizeof(blockCount), 
        BinaryHeader + tableNameSize + sizeof(blockSize) + sizeof(rowCount), 
        sizeof(blockCount)); /* Retrieve the block count */
    uint32_t blockNo, blockOffset;
    memcpy_s(&blockNo, sizeof(blockNo),
        BinaryHeader + tableNameSize + sizeof(blockSize) + sizeof(rowCount) + sizeof(blockCount),
        sizeof(blockNo)); /* Retrieve the block no */
    memcpy_s(&blockOffset, sizeof(blockOffset),
        BinaryHeader + tableNameSize + sizeof(blockSize) + sizeof(rowCount) + sizeof(blockCount) + sizeof(blockNo),
        sizeof(blockOffset)); /* Retrieve the block offset */
    pFirstAvailRow = RecordPointer(blockNo, blockOffset);
}

/**********************************************************************************************//**
 * @fn  const string DataHeader::getTableName() const
 *
 * @brief   Gets table name.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @return  The table name.
 **************************************************************************************************/

const string DataHeader::getTableName() const {
    return tableName;
}



/**********************************************************************************************//**
 * @fn  const uint32_t DataHeader::getRowCount() const
 *
 * @brief   Gets row count.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @return  The row count.
 **************************************************************************************************/

const uint32_t DataHeader::getRowCount() const {
    return rowCount;
}


/**********************************************************************************************//**
 * @fn  const RecordPointer DataHeader::getPointerToFirstAvailRow() const
 *
 * @brief   Gets pointer to first available row.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @return  The pointer to first available row.
 **************************************************************************************************/

const RecordPointer DataHeader::getPointerToFirstAvailRow() const {
    return pFirstAvailRow;
}

/**********************************************************************************************//**
 * @fn  void DataHeader::updateRowCount(const uint32_t newCount)
 *
 * @brief   Updates the row count described by newCount.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @param   newCount    Number of news.
 **************************************************************************************************/

void DataHeader::updateRowCount(const uint32_t newCount) {
    rowCount = newCount;
}

void DataHeader::updatePointerToFirstAvailRow(const RecordPointer & pointer) {
    this->pFirstAvailRow = pointer;
}



