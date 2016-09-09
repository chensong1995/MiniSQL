#include "DataFile.h"

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

DataFile::DataFile(string tableName, unsigned int headerSize) : IndexOrDataFile(tableName + ".data") {
    char* buff = new char[headerSize];
    theFile->read(buff, headerSize);
    fileHeader = new DataHeader(buff);
    delete[] buff;
}

/**********************************************************************************************//**
 * @fn  DataFile::~DataFile()
 *
 * @brief   Destructor, which frees the header and writes the header back.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

DataFile::~DataFile() {
    theFile->seekp(0, ios::beg); /* Go to the beginning of the .index file */
    theFile->write(((DataHeader*)fileHeader)->getTableName().c_str(), ((DataHeader*)fileHeader)->getTableName().length()+1); /* Write back header */
    theFile->seekp(64, ios::beg);
    uint32_t blockSize, rowCount, blockCount, blockNo, blockOffset;
    blockSize = ((DataHeader*)fileHeader)->getBlockSize();
    rowCount = ((DataHeader*)fileHeader)->getRowCount();
    blockCount = ((DataHeader*)fileHeader)->getBlockCount();
    blockNo = ((DataHeader*)fileHeader)->getPointerToFirstAvailRow().getBlockNo();
    blockOffset = ((DataHeader*)fileHeader)->getPointerToFirstAvailRow().getBlockOffset();

    theFile->write((char*)&blockSize, sizeof(blockSize)); /* Write back block size */
    theFile->write((char*)&rowCount, sizeof(rowCount)); /* Write back row count */
    theFile->write((char*)&blockCount, sizeof(blockCount)); /* Write back block count */
    theFile->write((char*)&blockNo, sizeof(blockNo)); /* Write back block no */
    theFile->write((char*)&blockOffset, sizeof(blockOffset)); /* Write back block offset */

    delete fileHeader;

}
