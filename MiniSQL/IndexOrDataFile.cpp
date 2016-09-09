/**********************************************************************************************//**
 * @file    IndexOrDataFile.cpp
 *
 * @brief   Implements the index or data file class.
 **************************************************************************************************/

#include "IndexOrDataFile.h"

/**********************************************************************************************//**
 * @fn  IndexOrDataFile::IndexOrDataFile(string fileName)
 *
 * @brief   Constructor, which opens the specified file.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @exception   MyException Thrown when My error condition occurs.
 *
 * @param   fileName    Filename of the file.
 **************************************************************************************************/

IndexOrDataFile::IndexOrDataFile(string fileName) {
    theFile = new fstream(path + fileName, ios::binary|ios::in|ios::out);
    if (!theFile->good()) {
        throw MyException("Error: Fail to open the file \"" + fileName + "\"!");
    }
}

/**********************************************************************************************//**
 * @fn  fstream & IndexOrDataFile::getFileStream()
 *
 * @brief   Gets file stream.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @return  The file stream.
 **************************************************************************************************/

fstream & IndexOrDataFile::getFileStream() {
    return *theFile;
}


Header&  IndexOrDataFile::getFileHeader() {
    return *fileHeader;
}

/**********************************************************************************************//**
 * @fn  IndexOrDataFile::~IndexOrDataFile()
 *
 * @brief   Destructor, which closes the file and frees the dynamically allocated memory.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

IndexOrDataFile::~IndexOrDataFile() {
    theFile->close();
    delete theFile;
}
