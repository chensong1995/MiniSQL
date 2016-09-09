/**********************************************************************************************//**
 * @file    IndexHeader.cpp
 *
 * @brief   Implements the index header class.
 **************************************************************************************************/

#include "IndexHeader.h"

/**********************************************************************************************//**
 * @fn  IndexHeader::IndexHeader(const char * BinaryHeader)
 *
 * @brief   Constructor, which converts the physical binary file header into member variables.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @param   BinaryHeader    The physical binary file header.
 **************************************************************************************************/

IndexHeader::IndexHeader(const char * BinaryHeader) {
    headerType = "index";

    char buff[indexNameSize];
    memcpy_s(buff, indexNameSize, BinaryHeader, indexNameSize);
    indexName = string(buff); /* Retrieve the index name */
    memcpy_s(&blockSize, sizeof(blockSize), BinaryHeader + indexNameSize, sizeof(blockSize)); /* Retrieve the block size */
    memcpy_s(&blockCount, sizeof(blockCount), BinaryHeader + indexNameSize + sizeof(blockSize), sizeof(blockCount)); /* Retrieve the block count */
}

/**********************************************************************************************//**
 * @fn  const string IndexHeader::getIndexName() const
 *
 * @brief   Gets index name.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @return  The index name.
 **************************************************************************************************/

const string IndexHeader::getIndexName() const {
    return indexName;
}

