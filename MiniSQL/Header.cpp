#include "Header.h"

const uint32_t Header::getBlockSize() const {
    return blockSize;
}

const uint32_t Header::getBlockCount() const {
    return blockCount;
}

const string Header::getHeaderType() const {
    return headerType;
}

void Header::updateBlockCount(const uint32_t newCount) {
    blockCount = newCount;
}