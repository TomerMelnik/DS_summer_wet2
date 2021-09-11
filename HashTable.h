//
// Created by timor on 02/01/2021.
//

#ifndef RATUV2_HASHTABLE_H
#define RATUV2_HASHTABLE_H

#include "unionFind.h"
#include "LinkedList.h"
#include "ImageNode.h"

#define REDUCE 2
#define INCREASE 3
#define DEFAULTSIZE 10

#include "ImageNode.h"

class HashTable {
    LinkedList<imageNode> **table;
    int sizeOfTable;
    int numberOfImages;
    friend class LinkedList<imageNode>;


    void resizeTable(int reduceOrIncrease);

    void reduceTable();

    void increaseTable();

    int Hash(int imageID) const;

    void insertAux(imageNode *, int size);

    static int HashAux(int size, int imageID);

public:


    HashTable(int size = DEFAULTSIZE);

    ~HashTable();

    HashTable(const HashTable &T);

    void insert(imageNode *);

    imageNode *find(int);

    void remove(int);


};

#endif //RATUV2_HASHTABLE_H
