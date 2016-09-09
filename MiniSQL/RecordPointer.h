/**********************************************************************************************//**
 * @file    RecordPointer.h
 *
 * @brief   Declares the record pointer class.
 **************************************************************************************************/

#pragma once
#include <cstdint>

/**********************************************************************************************//**
 * @class   RecordPointer
 *
 * @brief   A record pointer, who points to a record(tuple) in .data/.index files.
 *
 * @author  Chen
 * @date    6/10/2016
 **************************************************************************************************/

class RecordPointer {
private:
    /** @brief   The block# within the file (zero-based). */
    uint32_t blockNo;
    /** @brief   The offset within the block. */
    uint32_t blockOffset;
public:

    /**********************************************************************************************//**
     * @fn  RecordPointer::RecordPointer(const uint32_t blockNo, const uint32_t blockOffset);
     *
     * @brief   Constructor, which initializes the block number and the block offset.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @param   blockNo     The block no (zero-based).
     * @param   blockOffset The block offset.
     **************************************************************************************************/

    RecordPointer(const uint32_t blockNo, const uint32_t blockOffset);

    /**********************************************************************************************//**
     * @fn  const uint32_t RecordPointer::getBlockNo() const;
     *
     * @brief   Gets block no (zero-based).
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @return  The block no.
     **************************************************************************************************/

    const uint32_t getBlockNo() const;

    /**********************************************************************************************//**
     * @fn  const uint32_t RecordPointer::getBlockOffset() const;
     *
     * @brief   Gets block offset.
     *
     * @author  Chen
     * @date    6/10/2016
     *
     * @return  The block offset.
     **************************************************************************************************/

    const uint32_t getBlockOffset() const;


    const bool operator !=(const RecordPointer& another) const;


    const bool next(const uint32_t recordSize, const uint32_t blockSize);

};