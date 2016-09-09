#ifndef INDEX_H
#define INDEX_H
#include "AttributeConstraint.h"
#include "ResultSet.h"
#include "RecordPointer.h"
#include "com.h"
#include <vector>
#include <array>
#include <string>
using namespace std;
using namespace tools;
namespace index {
    //bit wise version of Record pointer
    typedef struct Pointer {
        /** @brief   The block# within the file (zero-based). */
        uint32_t blockNo;
        /** @brief   The offset within the block. */
        uint32_t blockOffset;
    }Pointer;
    //an element in a node, see document for details
    typedef struct pointer_section {
        Pointer parent;
        //points to the record if on leaf node
        Pointer child;
        //points to the tail part of the node
        Pointer tail;
    }pointer_section;
    template <typename T, int size>
    class Velement {
    public:
        //points to the record if on leaf node
        Pointer child;
        //points to the tail part of the node
        Pointer tail;
        //points to the next element
        array<T, size> elements;
    };
    typedef struct Tail {
        //number of elements in this node
        int count;
        int is_leaf;
        //points to the next node
        Pointer parent;
    }Tail;
    //a node in a B+ tree
    template <typename T, int size>
    class Node {
    public:
        //a node can have at most
        array<Velement<T, size>, 5> elements;
        //tail:
        Tail tail;
    };
    //Interfaces:
    bool createIndex(const Index index);
    bool dropIndex(const Index index);

    bool deleteTuple(const Table& table, const vector<string>& values);
    bool insertTuple(const Table& table, const vector<string>& values, const RecordPointer& p);
    //name = tableName.attributeName
    template <typename T>
    RecordPointer findKey(const string& name, const T& Key);
    template <typename T>
    RecordPointer findKey(const Index& index, const T& Key);

    template <typename T>
    RecordPointer getPointerBetween(Index& index, const T& keyA, const T& keyB);

    //don't care:
    template <typename T, int size>
    bool deletetIndex(const Index& index, const array<T, size>& key, const Pointer& p);
    template <typename T, int size>
    bool deleteIndex(const Index& index, const AttributeConstraint& attr, array<T, size>& key, const Pointer& p);
    template <typename T, int size>
    bool insertIndex(const Index& index, const array<T, size>& key, const Pointer& p);
    template <typename T, int size>
    bool insertIndex(const Index& index, const AttributeConstraint& attr, array<T, size>& key, const Pointer& p);

    Pointer rtop(const RecordPointer& p);

    bool writePosition(const string& name, const void* cont, const Pointer& p, size_t size);
#define write(name, object, position) writePosition(name, &object, position, sizeof(object))

    void* getPosition(const string& name, const Pointer& p);
    void endOccupation(const string& name, const Pointer& p);

    Tail* getTail(const string& name, const Pointer& p);

    template <typename T, int size>
    Node<T, size>* getNode(const string& name, const Pointer& p);

    template <typename T, int size>
    Velement<T, size>* getElement(const string& name, const Pointer& p);
}
#endif
