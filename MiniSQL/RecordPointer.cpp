/**********************************************************************************************//**
 * @file    RecordPointer.cpp
 *
 * @brief   Implements the record pointer class.
 **************************************************************************************************/

#include "RecordPointer.h"

/**********************************************************************************************//**
 * @fn  RecordPointer::RecordPointer(uint32_t blockNo, uint32_t blockOffset)
 *
 * @brief   Constructor.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @param   blockNo     The block no (zero-based).
 * @param   blockOffset The block offset.
 **************************************************************************************************/

RecordPointer::RecordPointer(const uint32_t blockNo, const uint32_t blockOffset) {
    this->blockNo = blockNo;
    this->blockOffset = blockOffset;
}

/**********************************************************************************************//**
 * @fn  const uint32_t RecordPointer::getBlockNo() const
 *
 * @brief   Gets block no (zero-based).
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @return  The block no.
 **************************************************************************************************/

const uint32_t RecordPointer::getBlockNo() const {
    return blockNo;
}

/**********************************************************************************************//**
 * @fn  const uint32_t RecordPointer::getBlockOffset() const
 *
 * @brief   Gets block offset.
 *
 * @author  Chen
 * @date    6/10/2016
 *
 * @return  The block offset.
 **************************************************************************************************/

const uint32_t RecordPointer::getBlockOffset() const {
    return blockOffset;
}

const bool RecordPointer::operator!=(const RecordPointer & another) const {
     return this->blockNo != another.blockNo || this->blockOffset != another.blockOffset;
 }

const bool RecordPointer::next(const uint32_t recordSize, const uint32_t blockSize) {

    blockOffset += recordSize;
    if (blockOffset + recordSize > blockSize) {
        blockNo++;
        blockOffset = 0;
        return true;
    } else {
        return false;
    }

 }
