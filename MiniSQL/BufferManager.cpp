#include "BufferManager.h"
#include "IndexFile.h"
#include <cstdio>

vector<IndexOrDataFile*>BufferManager::openedFiles;
vector<BufferBlock*>BufferManager::openedBlocks;
const string BufferManager::path = "DBFiles\\";


IndexFile* BufferManager::openIndexFile(string indexName) {
    /* The file is already open */
    for (unsigned int i = 0; i < openedFiles.size(); i++) {
        if (openedFiles[i]->getFileHeader().getHeaderType() == "index" 
            && ((IndexHeader&)(openedFiles[i])->getFileHeader()).getIndexName() == indexName) {
            return (IndexFile*)openedFiles[i];
        }
    }
    if (openedFiles.size() >= maxOpenedFiles) {
        /* Remove the first one in vector: openedFiles */
        delete openedFiles[0];
        openedFiles.erase(openedFiles.begin());
    }
    openedFiles.push_back(new IndexFile(indexName, headerSize));
    return (IndexFile*)openedFiles[openedFiles.size() - 1];
}

DataFile* BufferManager::openDataFile(string tableName) {
    /* The file is already open */
    for (unsigned int i = 0; i < openedFiles.size(); i++) {
        if (openedFiles[i]->getFileHeader().getHeaderType() == "data" 
            && ((DataHeader&)(openedFiles[i]->getFileHeader())).getTableName() == tableName) {
            return (DataFile*)openedFiles[i];
        }
    }
    if (openedFiles.size() >= maxOpenedFiles) {
        /* Remove the first one in vector: openedFiles */
        delete openedFiles[0];
        openedFiles.erase(openedFiles.begin());
    }
    openedFiles.push_back(new DataFile(tableName, headerSize));
    return (DataFile*)openedFiles[openedFiles.size() - 1];
}

void BufferManager::createDataFile(const string tableName) {
    fstream file(path + tableName + ".data", ios::in);
    if (file.good()) {
        throw MyException("Internal Error: File already exists!");
    } 
    file = fstream(path + tableName + ".data", ios::out|ios::binary);
    if (!file.good()) {
        throw MyException("Error: Fail to create the file!");
    }
    file.write(tableName.c_str(), tableName.length()+1); /* Write back header */
    char zeroBuffer[100];
    memset(zeroBuffer, 0, 100);
    file.write(zeroBuffer, 64 - tableName.length() - 1);
    uint32_t blockSize, rowCount, blockCount, blockNo, blockOffset;
    blockSize = BufferManager::blockSize;
    rowCount = 0;
    blockCount = 0;
    blockNo = 0;
    blockOffset = 0;

    file.write((char*)&blockSize, sizeof(blockSize)); /* Write back block size */
    file.write((char*)&rowCount, sizeof(rowCount)); /* Write back row count */
    file.write((char*)&blockCount, sizeof(blockCount)); /* Write back block count */
    file.write((char*)&blockNo, sizeof(blockNo)); /* Write back block no */
    file.write((char*)&blockOffset, sizeof(blockOffset)); /* Write back block offset */
    file.write(zeroBuffer, 16); /* Preserved */
    file.close();
    createBlock(tableName, "data");
}

void BufferManager::createIndexFile(const string indexName) {
    fstream file(path + indexName + ".index", ios::in);
    if (file.good()) {
        throw MyException("Internal Error: File already exists!");
    }
    file = fstream(path + indexName + ".index", ios::out | ios::binary);
    if (!file.good()) {
        throw MyException("Error: Fail to create the file!");
    }
    file.write(indexName.c_str(), indexName.length() + 1); /* Write back header */
    char zeroBuffer[100];
    memset(zeroBuffer, 0, 100);
    file.write(zeroBuffer, 64 - indexName.length() - 1);
    uint32_t blockSize, blockCount;
    blockSize = BufferManager::blockSize;
    blockCount = 0;

    file.write((char*)&blockSize, sizeof(blockSize)); /* Write back block size */
    file.write((char*)&blockCount, sizeof(blockCount)); /* Write back block count */
    file.write(zeroBuffer, 28); /* Preserved */
    file.close();
    createBlock(indexName, "index");
}

IndexHeader& BufferManager::getIndexHeader(const string indexName) {
    return (IndexHeader&)(openIndexFile(indexName)->getFileHeader());
}

DataHeader& BufferManager::getDataHeader(const string tableName) {
    return (DataHeader&)(openDataFile(tableName)->getFileHeader());
}

BufferBlock & BufferManager::getBlock(const string name, const string fileType, const unsigned int blockNo) {
    IndexOrDataFile* file;
    if ("index" == fileType) {
        file = openIndexFile(name);
    } else if ("data" == fileType) {
        file = openDataFile(name);
    } else {
        throw MyException("Internal Error: File type is illegal!");
    }
    if (openedBlocks.size() >= maxBlocksInMemory) {
        /* Release first unpinned block */
        unsigned int i;
        for (i = 0; i < openedBlocks.size(); i++) {
            if (!openedBlocks[i]->isPinned()) {
                delete openedBlocks[i];
                openedBlocks.erase(openedBlocks.begin() + i);
                break;
            }
        }
        if (i >= openedBlocks.size()) {  /* If all blocks are pinned */
            throw MyException("Error: Fail to get the block, memory is full!");
        }
    }
    /* Check if the block already exists */
    for (unsigned int i = 0; i < openedBlocks.size(); i++) {
        if ("index" == fileType  &&
            blockNo == openedBlocks[i]->getBlockNo() &&
           ((IndexHeader&)openedBlocks[i]->getFileHeader()).getIndexName() == name) {
            return *openedBlocks[i];
        } else if ("data" == fileType &&
            blockNo == openedBlocks[i]->getBlockNo() &&
            ((DataHeader&)openedBlocks[i]->getFileHeader()).getTableName() == name) {
            return *openedBlocks[i];
        }
    }
    /* Not exist */
    BufferBlock* block = new BufferBlock(*file, blockNo);
    openedBlocks.push_back(block);
    return *block;
}

const unsigned int BufferManager::createBlock(const string name, const string fileType) {
    IndexOrDataFile* file;
    if ("index" == fileType) {
        file = openIndexFile(name);
    } else if ("data" == fileType) {
        file = openDataFile(name);
    } else {
        throw MyException("Internal Error: File type is illegal!");
    }
    unsigned int newBlockNo = file->getFileHeader().getBlockCount();
    file->getFileHeader().updateBlockCount(newBlockNo + 1);
    fstream& stream = file->getFileStream();
    stream.seekp(0, ios::end); /* Move to the end of the file */
    char block[blockSize];
    memset(block, 0, blockSize);
    stream.write(block, blockSize);
    clear();
    return newBlockNo;
}

void BufferManager::clear() {
    for (unsigned int i = 0; i < openedBlocks.size(); i++) {
        delete openedBlocks[i];
    }

    for (unsigned int i = 0; i < openedFiles.size(); i++) {
        delete openedFiles[i];
    }
    openedBlocks.clear();
    openedFiles.clear();
}

void BufferManager::deleteFile(const string name, const string fileType) {
    clear();
    if (0 != remove((path + name + "." + fileType).c_str())) {
        throw MyException("Internal Error: Fail to delete " + fileType + " file: " + name);
    }
}
