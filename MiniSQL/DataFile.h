/**********************************************************************************************//**
 * @file    DataFile.h
 *
 * @brief   Declares the data file class.
 **************************************************************************************************/

#pragma once
#include "IndexOrDataFile.h"
#include "DataHeader.h"
class DataFile : public IndexOrDataFile {
public:

    /**********************************************************************************************//**
     * @fn  DataFile::DataFile(string tableName, unsigned int headerSize)
     *
     * @brief   Constructor.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @param   tableName   Name of the table.
     * @param   headerSize  Size of the header.
     **************************************************************************************************/

    DataFile(string tableName, unsigned int headerSize);

    /**********************************************************************************************//**
     * @fn  DataFile::~DataFile()
     *
     * @brief   Destructor, which frees the header and writes the header back.
     *
     * @author  Chen
     * @date    6/10/2016
     **************************************************************************************************/

    ~DataFile();
};