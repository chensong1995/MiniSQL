/**********************************************************************************************//**
 * @file    IndexOrDataFile.h
 *
 * @brief   Declares the index or data file class.
 **************************************************************************************************/

#pragma once
#include <fstream>
#include <string>
#include "MyException.h"
#include "Header.h"

using namespace std;

/**********************************************************************************************//**
 * @class   IndexOrDataFile
 *
 * @brief   An index or data file.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

class IndexOrDataFile {
protected:
    /** @brief   the file stream. */
    fstream* theFile;
    Header* fileHeader;
    /** @brief   Size of the header in the .index file. */
    static const int headerSize = 100;

    const string path = "DBFiles\\";
public:

    /**********************************************************************************************//**
     * @fn  IndexOrDataFile::IndexOrDataFile(string fileName);
     *
     * @brief   Constructor, which opens the specified file.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @param   fileName    Filename of the file.
     **************************************************************************************************/

    IndexOrDataFile(string fileName);

    Header& getFileHeader();


    /**********************************************************************************************//**
     * @fn  fstream& IndexOrDataFile::getFileStream()
     *
     * @brief   Gets file stream.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @return  The file stream.
     **************************************************************************************************/

    fstream& getFileStream();

    /**********************************************************************************************//**
     * @fn  IndexOrDataFile::~IndexOrDataFile();
     *
     * @brief   Destructor, which closes the file and frees the dynamically allocated memory.
     *
     * @author  Chen
     * @date    6/10/2016
     **************************************************************************************************/

    virtual ~IndexOrDataFile();
};