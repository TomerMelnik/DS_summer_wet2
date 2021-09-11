//
// Created by Linoy on 9/7/2021.
//

#include "unionFind.h"


AVLTree<LabelNode> *mergeTrees(AVLTree<LabelNode> *t1, AVLTree<LabelNode> *t2) {
    LabelNode **arr1 = t1->toArray();
    LabelNode **arr2 = t2->toArray();
    printf("starting");

    int size = t1->numOfNodes + t2->numOfNodes;
    LabelNode **arrTemp = (LabelNode **) malloc(sizeof(LabelNode *) * size);
    int i = 0;
    while (i < size) {
        if ((*arr1)->getID() > (*arr2)->getID()) {
            arrTemp[i] = (*arr1);
            arr1++;
        } else if ((*arr1)->getID() < (*arr2)->getID()) {
            arrTemp[i] = (*arr2);
            arr2++;
        } else {
            arrTemp[i] = (*arr2);
            arrTemp[i]->setData((*arr1)->getData() + (*arr2)->getData());
            arr2++;
            arr1++;
            size--;
        }
        i++;
    }
    printf("finishing");
    arrTemp = (LabelNode **) realloc(arrTemp, sizeof(LabelNode*) * size);
    AVLTree<LabelNode> *newTree = new AVLTree<LabelNode>(arrTemp, size);
    delete t1;
    delete t2;
    printf("aa");
    return newTree;
}

unionFind::unionFind(int size) : size(size) {
    groupArray = new int[size];
    groupSizeArray = new int[size];
    groupLabelTree = new AVLTree<LabelNode>*[size];
    for (int i = 0; i < size; i++) {
        groupArray[i] = i;
        groupSizeArray[i] = 1;
        groupLabelTree[i] = new AVLTree<LabelNode>();
    }
}

unionFind::~unionFind() {
    delete[] groupArray;
    delete[] groupLabelTree;
    delete[] groupSizeArray;
}

int unionFind::Find(int id) {
    if (groupArray[id] != id) groupArray[id] = Find(groupArray[id]);
    return groupArray[id];
}

void unionFind::Union(int first, int second) {
    int firstG = Find(first);
    int secondG = Find(second);
    if (firstG == secondG) throw Failure();
    if (groupSizeArray[firstG] < groupSizeArray[secondG]) {
        groupArray[firstG] = secondG;
    } else if (groupSizeArray[firstG] > groupSizeArray[secondG]) {
        groupArray[secondG] = firstG;
    } else {
        groupArray[firstG] = secondG;
        groupSizeArray[secondG] = groupSizeArray[secondG] + 1;
    }
    int g = Find(first);
    printf("merging trees");
    AVLTree<LabelNode> *newTree = mergeTrees(groupLabelTree[firstG], groupLabelTree[secondG]);
    groupLabelTree[g] = newTree;
}
