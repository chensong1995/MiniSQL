/**********************************************************************************************//**
 * @file    BufferManager.h
 *
 * @brief   Declares the buffer manager class.
 **************************************************************************************************/

#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "BufferBlock.h"
#include "IndexHeader.h"
#include "DataHeader.h"
#include "IndexFile.h"
#include "DataFile.h"
#include "IndexOrDataFile.h"

using namespace std;

/**********************************************************************************************//**
 * @class   BufferManager
 *
 * @brief   Manager for buffers. DO NOT INSTANTIATE THIS CLASS!!! Use static functions is fine. 
 *
 * @author  Chen
 * @date    6/11/2016
 **************************************************************************************************/

class BufferManager {
private:
    
    static const unsigned int maxBlocksInMemory = 5; /* The memory can hold up to 5 blocks at a time */
    static const unsigned int maxOpenedFiles = 20;
    static vector<IndexOrDataFile*> openedFiles; /* A vector holding all file streams that is currently open */
    static vector<BufferBlock*> openedBlocks;

    const static unsigned int headerSize = 100;

    friend class BufferBlock;


    friend class IndexFile;

    static IndexFile* openIndexFile(string indexName);

    friend class DataFile;

    static DataFile* openDataFile(string tableName);

    static const string path;

public:
    static const uint32_t blockSize = 4096; /* One block is 4096 Bytes */


    /**********************************************************************************************//**
     * @fn  static void BufferManager::createDataFile(const string tableName);
     *
     * @brief   Creates a data file in \\DBFiles. MyException will be thrown if error occurs
     *
     * @author  Chen
     * @date    6/11/2016
     *
     * @param   tableName   Name of the table.
     **************************************************************************************************/

    static void createDataFile(const string tableName);

    /**********************************************************************************************//**
     * @fn  static void BufferManager::createIndexFile(const string indexName);
     *
     * @brief   Creates  a index file in \\DBFiles. MyException will be thrown if error occurs
     *
     * @author  Chen
     * @date    6/11/2016
     *
     * @param   indexName   Name of the index.
     **************************************************************************************************/

    static void createIndexFile(const string indexName);

    /**********************************************************************************************//**
     * @fn  static IndexHeader& BufferManager::getIndexHeader(const string indexName);
     *
     * @brief   Gets index header.
     *
     * @author  Chen
     * @date    6/11/2016
     *
     * @param   indexName   Name of the index.
     *
     * @return  The index header.
     **************************************************************************************************/

    static IndexHeader& getIndexHeader(const string indexName);

    /**********************************************************************************************//**
     * @fn  static DataHeader& BufferManager::getDataHeader(const string tableName);
     *
     * @brief   Gets data header.
     *
     * @author  Chen
     * @date    6/11/2016
     *
     * @param   tableName   Name of the table.
     *
     * @return  The data header.
     **************************************************************************************************/

    static DataHeader& getDataHeader(const string tableName);

    /**********************************************************************************************//**
     * @fn  static BufferBlock& BufferManager::getBlock(const string name, const string fileType, const unsigned int blockNo);
     *
     * @brief   Gets a block.
     *
     * @author  Chen
     * @date    6/11/2016
     *
     * @param   name        The name.
     * @param   fileType    Type of the file.
     * @param   blockNo     The block no.
     *
     * @return  The block.
     **************************************************************************************************/

    static  BufferBlock& getBlock(const string name, const string fileType, const unsigned int blockNo);

    /**********************************************************************************************//**
     * @fn  static const unsigned int BufferManager::createBlock(const string name, const string fileType);
     *
     * @brief   Creates a block. VERY VERY IMPORTANT: The block is TOTALLY EMPTY, free row record in
     *          the header is NOT UPDATED!!!!!
     *
     * @author  Chen
     * @date    6/11/2016
     *
     * @param   name        The name.
     * @param   fileType    Type of the file.
     *
     * @return  The new block.
     **************************************************************************************************/

    static const unsigned int createBlock(const string name, const string fileType);


    /**********************************************************************************************//**
     * @fn  void BufferManager::clear();
     *
     * @brief   Clears all blocks, closes all files. If a block has the dirty bit set, then write back.
     *          MyException will be thrown if a block is pinned.
     *
     * @author  Chen
     * @date    6/10/2016
     **************************************************************************************************/

    static void clear();

    /**********************************************************************************************//**
     * @fn  static void BufferManager::deleteFile(const string name, const string fileType);
     *
     * @brief   Deletes the file. If the file does not exist, MyException will be thrown.
     *
     * @author  Chen
     * @date    6/13/2016
     *
     * @param   name        The name.
     * @param   fileType    Type of the file.
     **************************************************************************************************/

    static void deleteFile(const string name, const string fileType);
};