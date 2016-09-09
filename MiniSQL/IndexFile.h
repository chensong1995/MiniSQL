/**********************************************************************************************//**
 * @file    IndexFile.h
 *
 * @brief   Declares the index file class.
 **************************************************************************************************/

#pragma once
#include "IndexOrDataFile.h"
#include "IndexHeader.h"
#include <string>

using namespace std;

class IndexFile : public IndexOrDataFile {
public:

    IndexFile(string indexName, unsigned int headerSize);


    /**********************************************************************************************//**
     * @fn  IndexFile::~IndexFile();
     *
     * @brief   Destructor, which frees the header and writes the header back.
     *
     * @author  Chen
     * @date    6/10/2016
     **************************************************************************************************/

    virtual ~IndexFile();
};