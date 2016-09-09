#pragma once
#include <cstdint>
#include <string>

using namespace std;

class Header {
protected:

    /** @brief   Size of the block. */
    uint32_t blockSize;
    /** @brief   Number of blocks. */
    uint32_t blockCount;

    string headerType; // "index" or "data"

public:

    const uint32_t getBlockSize() const;

    const uint32_t getBlockCount() const;

    const string getHeaderType() const;

    void updateBlockCount(const uint32_t newCount);

};