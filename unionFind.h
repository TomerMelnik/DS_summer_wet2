//
// Created by Linoy on 9/7/2021.
//

#ifndef DS_SUMMER_WET2_UNIONFIND_H
#define DS_SUMMER_WET2_UNIONFIND_H

#include <iostream>
#include <ostream>
#include <string>
#include "avlTree.h"
#include "exceptions.h"


class LabelNode {
    int id;
    int data;
public:

    LabelNode(int label, int score) : id(label), data(score) {}

    int getID() { return id; }

    int getData() { return data; }

    void setData(int data) { this->data = data; }


    bool operator>(LabelNode n) {
         return this->data > n.getData();
    }

    bool operator<(LabelNode n) {
        return this->data < n.getData();
    }

    bool operator==(LabelNode n){
        return this->data == n.getData() && this->getID() == n.getID();
    }
};

class unionFind {
    int *groupArray;
    int *groupSizeArray;
    int size;
public:
    AVLTree<LabelNode> **groupLabelTree;

    unionFind(int size);

    ~unionFind();

    int Find(int id);

    void Union(int first, int second);
};



#endif //DS_SUMMER_WET2_UNIONFIND_H
