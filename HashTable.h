//
// Created by timor on 02/01/2021.
//

#ifndef RATUV2_HASHTABLE_H
#define RATUV2_HASHTABLE_H
#include "NodeCourse.h"
#include "LinkedList.h"

#define REDUCE 2
#define INCREASE 3
#define DEFAULTSIZE 10
class HashTable{
    LinkedList<NodeCourse> **table;
    int sizeOfTable;
    int numberOfCourses;


    void resizeTable(int reduceOrIncrease);
    void reduceTable();
    void increaseTable();
    int Hash(int courseId) const;

    void insertAux(NodeCourse *, int size);
    static int HashAux(int size ,int courseId) ;

    public:


    HashTable(int size = DEFAULTSIZE);
    ~HashTable();
    HashTable(const HashTable& T);
    void insert(NodeCourse*);
    NodeCourse* find(int);
    void remove(int);


};
#endif //RATUV2_HASHTABLE_H
