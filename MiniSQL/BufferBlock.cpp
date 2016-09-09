/**********************************************************************************************//**
 * @file    BufferBlock.cpp
 *
 * @brief   Implements the buffer block class.
 **************************************************************************************************/

#include "BufferBlock.h"
#include "BufferManager.h"



BufferBlock::BufferBlock(IndexOrDataFile& file, const unsigned int blockNo) : blockNo(blockNo), blockSize(file.getFileHeader().getBlockSize()) {

    if (file.getFileHeader().getHeaderType() == "index") {
        fileHeader = new IndexHeader((IndexHeader&)file.getFileHeader());
    } else {
        fileHeader = new DataHeader((DataHeader&)file.getFileHeader());
    }
    if (blockNo >= file.getFileHeader().getBlockCount()) {
        throw MyException("Internal Error: The file does not have that many blocks!");
    }
    file.getFileStream().seekg(headerSize + blockNo * blockSize, ios::beg);
    blockContent = new char[blockSize];
    file.getFileStream().read(blockContent, blockSize);
    dirty = false;
    pin = false;
}

/**********************************************************************************************//**
 * @fn  char * const BufferBlock::getBlockContent()
 *
 * @brief   Gets block content.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @return  The block content.
 **************************************************************************************************/

char * const BufferBlock::getBlockContent() {
    return blockContent;
}

/**********************************************************************************************//**
 * @fn  const unsigned int BufferBlock::getBlockNo() const
 *
 * @brief   Gets block no (zero-based).
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @return  The block no.
 **************************************************************************************************/

const unsigned int BufferBlock::getBlockNo() const {
    return blockNo;
}

/**********************************************************************************************//**
 * @fn  const unsigned int BufferBlock::getBlockSize() const
 *
 * @brief   Gets block size.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @return  The block size.
 **************************************************************************************************/

const unsigned int BufferBlock::getBlockSize() const {
    return blockSize;
}

/**********************************************************************************************//**
 * @fn  void BufferBlock::pinBlock()
 *
 * @brief   Pin the block.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

void BufferBlock::pinBlock() {
    pin = true;
}

/**********************************************************************************************//**
 * @fn  void BufferBlock::unpinBlock()
 *
 * @brief   Unpin the block.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

void BufferBlock::unpinBlock() {
    pin = false;
}

/**********************************************************************************************//**
 * @fn  const bool BufferBlock::isPinned() const
 *
 * @brief   Check if the block is pinned.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @return  true if the block is pinned, false otherwise.
 **************************************************************************************************/

const bool BufferBlock::isPinned() const {
    return pin;
}

/**********************************************************************************************//**
 * @fn  void BufferBlock::setDirty()
 *
 * @brief   Sets the dirty flag.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

void BufferBlock::setDirty() {
    dirty = true;
}

/**********************************************************************************************//**
 * @fn  void BufferBlock::resetDirty()
 *
 * @brief   Resets the dirty flag.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

void BufferBlock::resetDirty() {
    dirty = false;
}

Header& BufferBlock::getFileHeader() {
     return *fileHeader;
 }

/**********************************************************************************************//**
 * @fn  BufferBlock::~BufferBlock()
 *
 * @brief   Destructor, which frees the memory allocated for blockContent and writes the block 
 *          back if dirty bit is set.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

BufferBlock::~BufferBlock() {
    if (dirty) {
        IndexOrDataFile* file;
        /* Write the block back */
        if ("index" == fileHeader->getHeaderType()) {
            file = BufferManager::openIndexFile(((IndexHeader*)fileHeader)->getIndexName());
        } else {
            file = BufferManager::openDataFile(((DataHeader*)fileHeader)->getTableName());
        }
        fstream& stream = file->getFileStream();
        stream.seekp(headerSize + blockNo * blockSize, ios::beg); /* Go to the right place */
        stream.write(blockContent, blockSize);
    }
    delete fileHeader;
    delete[] blockContent;
}
