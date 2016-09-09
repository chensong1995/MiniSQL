/**********************************************************************************************//**
 * @file    IndexHeader.h
 *
 * @brief   Declares the index header class.
 **************************************************************************************************/

#pragma once
#include <string>
#include <cstdint>
#include <memory>
#include "Header.h"
using namespace std;

/**********************************************************************************************//**
 * @class   IndexHeader
 *
 * @brief   The header of index files.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

class IndexHeader : public Header {
private:
    /** @brief   Name of the index. */
    string indexName;

    /** @brief   Size of the header in the .index file. */
    static const int headerSize = 100;
    /** @brief   Size of the index name within the index. */
    static const int indexNameSize = 64;

public:

    /**********************************************************************************************//**
     * @fn  IndexHeader::IndexHeader(const char* BinaryHeader)
     *
     * @brief   Constructor, which converts the physical binary file header into member variables.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @param   BinaryHeader    The physical binary file header.
     **************************************************************************************************/

    IndexHeader(const char* BinaryHeader);

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

    const string getIndexName() const;

}; 