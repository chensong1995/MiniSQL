/**********************************************************************************************//**
 * @file    IndexFile.cpp
 *
 * @brief   Implements the index file class.
 **************************************************************************************************/

#include "IndexFile.h"

/**********************************************************************************************//**
 * @fn  IndexFile::IndexFile(string tableName, unsigned int headerSize)
 *
 * @brief   Constructor, which opens the index file and creates the header.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @param   tableName   Name of the table.
 * @param   headerSize  Size of the header.
 **************************************************************************************************/

IndexFile::IndexFile(string indexName, unsigned int headerSize) : IndexOrDataFile(indexName + ".index") {
    char* buff = new char[headerSize];
    theFile->read(buff, headerSize);
    fileHeader = new IndexHeader(buff);
    delete[] buff;
}

/**********************************************************************************************//**
 * @fn  IndexFile::~IndexFile()
 *
 * @brief   Destructor, which frees the header and writes the header back.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

IndexFile::~IndexFile() {
    theFile->seekp(0, ios::beg); /* Go to the beginning of the .index file */
    theFile->write(((IndexHeader*)fileHeader)->getIndexName().c_str(), ((IndexHeader*)fileHeader)->getIndexName().length()+1); /* Write back header */
    theFile->seekp(64, ios::beg);
    uint32_t blockSize, blockCount;
    blockSize = ((IndexHeader*)fileHeader)->getBlockSize();
    blockCount = ((IndexHeader*)fileHeader)->getBlockCount();

    theFile->write((char*)&blockSize, sizeof(blockSize)); /* Write back block size */
    theFile->write((char*)&blockCount, sizeof(blockCount)); /* Write back block count */

    delete fileHeader;

}
