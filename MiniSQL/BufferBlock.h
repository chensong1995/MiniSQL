/**********************************************************************************************//**
 * @file    BufferBlock.h
 *
 * @brief   Declares the buffer block class.
 **************************************************************************************************/

#pragma once
#include <fstream>
#include "DataFile.h"
#include "IndexFile.h"
#include "Header.h"

using namespace std;

class BufferBlock {
private:
    /** @brief   The block content. */
    char* blockContent;
    /** @brief   Size of the header. */
    static const unsigned int headerSize = 100;
    /** @brief   The block no (zero-based). */
    const unsigned int blockNo;
    /** @brief   Size of the block. */
    const unsigned int blockSize;
    /** @brief   Indicates whther the data in this buffer has been modified */
    bool dirty;
    /** @brief   Indicates whther this buffer is pinned. */
    bool pin;
    Header* fileHeader;

public:


    BufferBlock(IndexOrDataFile& file, const unsigned int blockNo);

    /**********************************************************************************************//**
     * @fn  char* const BufferBlock::getBlockContent()
     *
     * @brief   Gets block content.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @return  The block content.
     **************************************************************************************************/

    char* const getBlockContent();

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

    const unsigned int getBlockNo() const;

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

    const unsigned int getBlockSize() const;

    /**********************************************************************************************//**
     * @fn  void BufferBlock::pinBlock()
     *
     * @brief   Pin the block.
     *
     * @author  Chen
     * @date    6/10/2016
     **************************************************************************************************/

    void pinBlock();

    /**********************************************************************************************//**
     * @fn  void BufferBlock::unpinBlock()
     *
     * @brief   Unpin the block.
     *
     * @author  Chen
     * @date    6/10/2016
     **************************************************************************************************/

    void unpinBlock();

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

    const bool isPinned() const;

    /**********************************************************************************************//**
     * @fn  void BufferBlock::setDirty()
     *
     * @brief   Sets the dirty flag.
     *
     * @author  Chen
     * @date    6/10/2016
     **************************************************************************************************/

    void setDirty();

    /**********************************************************************************************//**
     * @fn  void BufferBlock::resetDirty()
     *
     * @brief   Resets the dirty flag.
     *
     * @author  Chen
     * @date    6/10/2016
     **************************************************************************************************/

    void resetDirty();


    Header& getFileHeader();



    /**********************************************************************************************//**
     * @fn  BufferBlock::~BufferBlock()
     *
     * @brief   Destructor, which frees the memory allocated for blockContent and writes the block
     *          back if dirty bit is set.
     *
     * @author  Chen
     * @date    6/10/2016
     **************************************************************************************************/

    ~BufferBlock();
};