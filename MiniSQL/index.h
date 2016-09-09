#ifndef INDEX_H
#define INDEX_H
#include <vector>
#include <array>
#include <string>
#include <iostream>
#include "catalog.h"
#include "BufferManager.h"
#include "AttributeConstraint.h"
#include "ResultSet.h"
#include "RecordPointer.h"
#include "com.h"
#define NUM_OF_ELEMS ((4096-100-sizeof(Tail))/sizeof(Velement<T, size>))
using namespace std;
using namespace tools;
namespace index {
    //bit wise version of Record pointer,{0, 0} means NULL
    typedef struct Pointer {
        /** @brief   The block# within the file (zero-based). */
        uint32_t blockNo;
        /** @brief   The offset within the block. */
        uint32_t blockOffset;
        Pointer(uint32_t no = 0, uint32_t off = 0) :blockNo(no), blockOffset(off) {};
    }Pointer;
    template <typename T, int size>
    class Velement {
    public:
        //points to the record if on leaf node
        Pointer child;
        //points to the tail part of the node
        Pointer tail;
        //points to the next element
        Pointer next;
        array<T, size> key;
    };
    typedef struct Tail {
        //number of elements in this node
        int count;
        int is_leaf;
        //points to the parent node
        Pointer parent;
        //points to the node itself
        Pointer head;
    }Tail;
    //a node in a B+ tree
    template <typename T, int size>
    class Node {
    public:
        //a node can have at most NUM_OF_ELEMS elements
        array<Velement<T, size>, NUM_OF_ELEMS> elements;
        //tail:
        Tail tail;
    };
    //Interfaces:
    bool createIndex(const Index& index);
    bool dropIndex(const string& indexName);
    template <typename T, int size>
    bool deleteKey(const Index& index, const array<T, size>& key);
    template <typename T, int size>
    bool insertKey(const Index& index, const array<T, size>& key, const RecordPointer& p);

    //don't care:
    template <typename T, int size>
    Pointer findKeyLeaf(const Index& index, const array<T, size>& key);
    template <typename T, int size>
    bool deletetIndex(const Index& index, const array<T, size>& key, const Pointer& p);
    template <typename T, int size>
    bool deleteIndex(const Index& index, const AttributeConstraint& attr, array<T, size>& key, const Pointer& p);
    template <typename T, int size>
    bool insertIndex(Index& index, const array<T, size>& key, const Pointer& p);
    template <typename T, int size>
    bool insertIndex(Index& index, const AttributeConstraint& attr, array<T, size>& key, const Pointer& p);
    bool insertIndex(Index& index, const AttributeConstraint& attr, const string& value, const Pointer& p);
    template <typename T, int size>
    bool insertIndex(Index& index, const array<T, size>& key, const Pointer& p);
    Pointer rtop(const RecordPointer& p);

    //some tools:
    template <typename T, int size>
    Pointer nextPointer(const Index& index, const Pointer& presentPointer);
    template <typename T, int size>
    Pointer findKeyLeaf(const Index& index, const array<T, size>& key);
    template <typename T, int size>
    Pointer getEFN(const Index& index, const Pointer& node, const Velement<T, size>& element);
    template <typename T, int size>
    int cmp(const Velement<T, size>& e1, const Velement<T, size>& e2);
    template <typename T, int size>
    int cmp(const array<T, size>& k1, const array<T, size>& k2);
    template <typename T, int size>
    RecordPointer nextEnd(const string& name, const Pointer& end);
    template <typename T, int size>
    void copyKey(array<T, size>& dest, const array<T, size> srce);
    template <typename T, int size>
    Pointer getElementN(const Pointer& nodePointer, int n);
    template <typename T, int size>
    Pointer& setTailPointer(Velement<T, size>& element, const Pointer& nodePointer);
    template <typename T, int size>
    Pointer insertKey(Index&index, Velement<T, size>& key, Node<T, size>& dest);

    bool writePosition(const string& name, const void* cont, const Pointer& p, size_t size);
#define write(name, object, position) writePosition(name, &object, position, sizeof(object))

    void* getPosition(const string& name, const Pointer& p);
    void endOccupation(const string& name, const Pointer& p);

    Tail* getTail(const string& name, const Pointer& p);

    template <typename T, int size>
    Node<T, size>* getNode(const string& name, const Pointer& p);

    template <typename T, int size>
    Velement<T, size>* getElement(const string& name, const Pointer& p);

    template <typename T, int size>
    int cmp(const Velement<T, size>& e1, const Velement<T, size>& e2) {
        for (unsigned int i = 0; i < e1.key.size(); i++) {
            if (e1.key[i] < e2.key[i]) {
                return -1;
            } else if (e1.key[i] > e2.key[i]) {
                return 1;
            }
        }
        return 0;
    }

    template <typename T, int size>
    bool deleteKey(const Index& index, const array<T, size>& key) {
        try {
            Pointer leaf = findKeyLeaf(index, key);
            Node<T, size> node;
            int flag;
            memmove(&node, getNode<T, size>(index.name, leaf), sizeof(node));
            endOccupation(index.name, leaf);
            for (auto&e : node.elements) {
                flag = cmp(key, e.key);
                if (!flag) {
                    e.child = { 0, 0 };
                    write(index.name, node, leaf);
                    endOccupation(index.name, leaf);
                } else if (flag < 0) {
                    break;
                }
            }
        } catch (...) {
            return false;
        }
        return true;
    }
    template <typename T, int size>
    int cmp(const array<T, size>& k1, const array<T, size>& k2) {
        for (unsigned int i = 0; i < k1.size(); i++) {
            if (k1[i] < k2[i]) {
                return -1;
            } else if (k1[i] > k2[i]) {
                return 1;
            }
        }
        return 0;
    }
    template <typename T, int size>
    Velement<T, size> nextElement(const Index& index, const Velement<T, size>& presentElement) {
        Pointer nextP;
        Velement<T, size> nextE;
        nextP = presentElement.next;
        memmove(&nextE, getElement<T, size>(index.name, nextP), sizeof(nextE));
        endOccupation(index.name, nextP);
        while (nextE.child.blockNo == 0 && nextE.child.blockOffset == 0) {
            if (nextE.next.blockNo == 0 && nextE.next.blockOffset == 0) {
                return nextE;
            }
            nextE = nextElement(index, nextE);
        }
        return nextE;
    }
    template <typename T, int size>
    Velement<T, size> findKeyElement(const Index& index, const array<T, size>& key) {
        Pointer leaf = findKeyLeaf(index, key);
        Node<T, size> node;
        memmove(&node, getNode<T, size>(index.name, leaf), sizeof(node));
        endOccupation(index.name, leaf);
        for (int i = 0; i < node.tail.count; i++) {
            if (cmp(key, node.elements[i].key) <= 0) {
                return node.elements[i];
            }
        }
        return Velement<T, size>();
    }
    template <typename T, int size>
    RecordPointer getPointerBetween(Index& index, const array<T, size>& keyA, const array<T, size>& keyB, bool withLeftBound, bool withRightBound) {
        static string presentIndex = index.name;
        static Velement<T, size> presentElement = findKeyElement(index, keyA);
        static bool first = true;
        if (presentIndex != index.name) {
            presentIndex = index.name;
            presentElement = findKeyElement(index, keyA);
            first = true;
        }
        if (first) {
            first = false;
            if (!withLeftBound) {
                if (cmp(presentElement.key, keyA) <= 0) {
                    presentElement = nextElement(index, presentElement);
                }
            }
        } else {
            presentElement = nextElement(index, presentElement);
        }
        if (!withRightBound) {
            if (cmp(presentElement.key, keyB) >= 0) {
                return RecordPointer(INT_MAX, INT_MAX);
            }
        } else {
            if (cmp(presentElement.key, keyB) > 0) {
                return RecordPointer(INT_MAX, INT_MAX);
            }
        }
        if (presentElement.child.blockNo == 0 && presentElement.child.blockOffset == 0) {
            return RecordPointer(INT_MAX, INT_MAX);
        } else {
            return RecordPointer(presentElement.child.blockNo, presentElement.child.blockOffset);
        }
    }
    template <typename T, int size>
    RecordPointer getPointerBetween(Index& index, const array<T, size>& keyA, const array<T, size>& keyB) {
        return getPointerBetween(index, keyA, keyB, true, true);
    }
    template <typename T, int size>
    RecordPointer getPointerBetween(Index& index, const array<T, size>& keyA, const array<T, size>& keyB, bool withLeftBound) {
        return getPointerBetween(index, keyA, keyB, withLeftBound, true);
    }
    template <typename T, int size>
    bool insertKey(const Index& index, const array<T, size>& key, const RecordPointer& p);
    template <typename T, int size>
    Pointer findKeyLeaf(const Index& index, const array<T, size>& key) {
        Pointer root = rtop(index.root), last = { 0, 0 };
        Velement<T, size> elem;
        Node<T, size> node;
        int i;
        copyKey(elem.key, key);
        do {
            memmove(&node, getNode<T, size>(index.name, root), sizeof(node));
            endOccupation(index.name, root);
            if (node.tail.parent.blockNo != last.blockNo || node.tail.parent.blockOffset != last.blockOffset) {
                node.tail.parent = last;
                write(index.name, node, root);
                endOccupation(index.name, root);
            }
            for (i = 0; i < node.tail.count; i++) {
                if (cmp(elem, node.elements[i]) < 0) {
                    break;
                }
            }
            last = root;
            root = node.elements[i ? i - 1 : 0].child;
        } while (node.tail.is_leaf == 0);
        return last;
    }
    template <typename T, int size>
    Pointer& setTailPointer(Velement<T, size>& element, const Pointer& nodePointer) {
        element.tail.blockNo = nodePointer.blockNo;
        element.tail.blockOffset = nodePointer.blockOffset + sizeof(element) * NUM_OF_ELEMS;
        return element.tail;
    }
    template <typename T, int size>
    Pointer getElementN(const Pointer& nodePointer, int n) {
        return{ nodePointer.blockNo, nodePointer.blockOffset + sizeof(Velement<T, size>) * n };
    }
    template <typename T, int size>
    RecordPointer nextEnd(const string& name, const Pointer& end) {
        //Velement<T, size>* head = getElement<T, size>(name, end);
        //if (head->next.blockNo == 0 && head->next.blockOffset == 0){
        endOccupation(name, end);
        if (end.blockOffset + sizeof(Node<T, size>) * 2< 4096) {
            return RecordPointer(end.blockNo, end.blockOffset + sizeof(Node<T, size>));
        } else {
            BufferManager::createBlock(name, "index");
            return RecordPointer(end.blockNo + 1, 100);
        }
        //}
        //else{
        //	endOccupation(name, end);
        //	RecordPointer next(head->next.blockNo, head->next.blockOffset);
        //	return next;
        //}
    }
    template <typename T, int size>
    void copyKey(array<T, size>& dest, const array<T, size> srce) {
        for (unsigned int i = 0; i < dest.size(); i++) {
            dest[i] = srce[i];
        }
    }
    template <typename T, int size>
    Pointer getEFN(const Index& index, const Pointer& node, const Velement<T, size>& element) {
        Node<T, size> n;
        memmove(&n, getNode<T, size>(index.name, node), sizeof(n));
        endOccupation(index.name, node);
        for (int i = 0; i < n.tail.count; i++) {
            if (!cmp(n.elements[i], element)) {
                return getElementN<T, size>(node, i);
            }
        }
        return{ 0, 0 };
    }
    //返回key所在的node指针
    template <typename T, int size>
    Pointer insertKey(Index&index, Velement<T, size>& key, Node<T, size>& dest) {
        array<Velement<T, size>, NUM_OF_ELEMS + 1> list;
        int keyIndex = 0, count = dest.tail.count + 1, flag;
        for (int i = 0; i < dest.tail.count; i++) {
            flag = cmp(key, dest.elements[i]);
            if (flag < 0) {
                Velement<T, size> t = dest.elements[i];
                key.next = t.next;
                list[i] = key;
                list[i].next = getElementN<T, size>(dest.tail.head, i + 1);
                keyIndex = i;
                for (int j = i; j < dest.tail.count; j++) {
                    if (j < dest.tail.count - 1) {
                        dest.elements[j].next = getElementN<T, size>(dest.tail.head, j + 2);
                    }
                    list[j + 1] = dest.elements[j];
                }
                break;
            } else if (!flag) {
                dest.elements[i].child = key.child;
                return dest.tail.head;
            } else {
                list[i] = dest.elements[i];
                if (i == dest.tail.count - 1) {
                    keyIndex = i;
                    key.next = list[i].next;
                    list[i].next = getElementN<T, size>(dest.tail.head, i + 1);
                    list[i + 1] = key;
                }
            }
        }
        if (count > NUM_OF_ELEMS) {
            //divide into two nodes
            Node<T, size>newNode, parent;
            Pointer end = rtop(index.end);
            index.end = nextEnd<T, size>(index.name, rtop(index.end));
            list[(NUM_OF_ELEMS - 1) / 2].next = end;
            //change next of [dest.last, new.last)
            for (int i = (NUM_OF_ELEMS - 1) / 2; i < NUM_OF_ELEMS; i++) {
                list[i].next = getElementN<T, size>(end, i - (NUM_OF_ELEMS - 1) / 2);
            }
            for (int i = 0; i < (NUM_OF_ELEMS + 1) / 2; i++) {
                dest.elements[i] = list[i];
            }
            for (int i = (NUM_OF_ELEMS + 1) / 2; i < NUM_OF_ELEMS + 1; i++) {
                setTailPointer<T, size>(list[i], end);
                newNode.elements[i - ((NUM_OF_ELEMS + 1) / 2)] = list[i];
            }
            dest.tail.count = (NUM_OF_ELEMS + 1) / 2;

            newNode.tail.count = (NUM_OF_ELEMS + 1) / 2;
            newNode.tail.is_leaf = dest.tail.is_leaf;
            newNode.tail.head = end;
            //cascade insert into parent
            if (dest.tail.parent.blockNo == 0 && dest.tail.parent.blockOffset == 0) {
                Pointer root = rtop(index.end);
                index.root = index.end;
                index.end = nextEnd<T, size>(index.name, rtop(index.end));
                copyKey(parent.elements[0].key, dest.elements[0].key);
                parent.elements[0].child = dest.tail.head;
                parent.elements[0].next = getElementN<T, size>(root, 1);
                setTailPointer(parent.elements[0], root);

                copyKey(parent.elements[1].key, newNode.elements[0].key);
                parent.elements[1].child = newNode.tail.head;
                parent.elements[1].next = { 0, 0 };
                setTailPointer(parent.elements[1], root);

                parent.tail.count = 2;
                parent.tail.is_leaf = 0;
                parent.tail.head = root;
                parent.tail.parent = { 0, 0 };
                write(index.name, parent, root);
                endOccupation(index.name, root);
                dest.tail.parent = root;
                newNode.tail.parent = root;
            } else {
                Velement<T, size> nkey;
                Pointer np;
                memmove(&parent, getNode<T, size>(index.name, dest.tail.parent), sizeof(parent));
                setTailPointer<T, size>(nkey, dest.tail.parent);
                copyKey(nkey.key, newNode.elements[0].key);
                nkey.child = newNode.tail.head;
                insertKey<T, size>(index, nkey, parent);
            }
            //write into buffer
            write(index.name, dest, dest.tail.head);
            endOccupation(index.name, dest.tail.head);

            write(index.name, newNode, end);
            endOccupation(index.name, end);
            return keyIndex < ((NUM_OF_ELEMS + 1) / 2) ? dest.tail.parent : newNode.tail.parent;
        } else {
            for (int i = 0; i < count; i++) {
                dest.elements[i] = list[i];
            }
            dest.tail.count = count;
            write(index.name, dest, dest.tail.head);
            endOccupation(index.name, dest.tail.head);
            return dest.tail.parent;
        }
    }
    template <typename T, int size>
    bool insertIndex(Index& index, const array<T, size>& key, const Pointer& p) {
        try {
            if (index.root.getBlockNo() == index.end.getBlockNo() && index.root.getBlockOffset() == index.end.getBlockOffset()) {
                Node<T, size> newNode;
                Velement<T, size> newElement;
                //init tail
                newNode.tail.count = 1;
                newNode.tail.is_leaf = true;
                newNode.tail.parent = { 0, 0 };
                newNode.tail.head = rtop(index.root);
                //construct element
                setTailPointer(newElement, rtop(index.root));
                copyKey(newElement.key, key);
                newElement.child = p;
                newElement.next = { 0, 0 };
                newNode.elements[0] = newElement;

                index.end = nextEnd<T, size>(index.name, rtop(index.end));
                write(index.name, newNode, rtop(index.root));
                endOccupation(index.name, rtop(index.root));
                /*
                Velement<T, size> newElement;
                Tail* tail = getTail(setTailPointer(newElement, index.end));
                Pointer position = getElementN(index.root, tail->count);
                for (int i = 0; i < size; i++){
                newElement.key[i] = key[i];
                }
                newElement.child = p;
                if (tail->count < NUM_OF_ELEMS-1){
                newElement.next = getElementN<T, size>(index.root, tail->count + 1);
                }
                else{

                }
                write(index.name, newElement, position);
                */
            } else {
                //insert element into node
                //mess:
                Pointer position = findKeyLeaf(index, key);
                Node<T, size> dest;
                memmove(&dest, getNode<T, size>(index.name, position), sizeof(dest));
                endOccupation(index.name, position);
                Velement<T, size> _key;
                copyKey(_key.key, key);
                _key.child = p;
                setTailPointer(_key, position);
                insertKey(index, _key, dest);
            }
        } catch (...) {
            cerr << "insertIndex failed\n";
            return false;
        }
        return true;
    }
    template <typename T, int size>
    Node<T, size>* getNode(const string& name, const Pointer& p) {
        return (Node<T, size>*) getPosition(name, p);
    }

    template <typename T, int size>
    Velement<T, size>* getElement(const string& name, const Pointer& p) {
        return (Velement<T, size>*) getPosition(name, p);
    }

}
#endif
