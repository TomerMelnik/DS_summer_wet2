//
// Created by Linoy on 9/7/2021.
//

#include "unionFind.h"


AVLTree<LabelNode> *mergeTrees(AVLTree<LabelNode> *t1, AVLTree<LabelNode> *t2) {
    LabelNode **arr1 = t1->toArray();
    LabelNode **arr2 = t2->toArray();
    int n = t1->numOfNodes, m = t2->numOfNodes;
    LabelNode **arrTemp = new LabelNode*[n+m];
    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (arr1[i]->getID() > arr2[j]->getID()) {
            arrTemp[k] = new LabelNode(arr1[i]->getID(), arr1[i]->getData());
            i++;
        } else if (arr1[i]->getID() < arr2[j]->getID()) {
            arrTemp[k] = new LabelNode(arr2[j]->getID(), arr2[j]->getData());
            j++;
        } else {
            arrTemp[k] = new LabelNode(arr2[j]->getID(),arr1[i]->getData() + arr2[j]->getData());
            j++;
            i++;
        }
        k++;
    }
    while (i< n)
    {
        arrTemp[k] = new LabelNode(arr1[i]->getID(), arr1[i]->getData());
        i++; 
        k++;
    }
    while (j < m) {
        arrTemp[k] = new LabelNode(arr2[j]->getID(), arr2[j]->getData());
        j++; 
        k++;
    }
    AVLTree<LabelNode> *newTree = new AVLTree<LabelNode>(arrTemp, k);
    delete t1;
    delete t2;
    delete[] arr1;
    delete[] arr2;
    delete[] arrTemp;
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
    for(int i = 0; i< size; i++)
    {
        delete groupLabelTree[i];
        groupLabelTree[i] = nullptr;
    }
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
    AVLTree<LabelNode>* tree1 = groupLabelTree[firstG];
    AVLTree<LabelNode>* tree2 = groupLabelTree[secondG];
    if (groupSizeArray[firstG] < groupSizeArray[secondG]) {
        groupArray[firstG] = secondG;
    } else if (groupSizeArray[firstG] > groupSizeArray[secondG]) {
        groupArray[secondG] = firstG;
    } else {
        groupArray[firstG] = secondG;
        groupSizeArray[secondG] = groupSizeArray[secondG] + 1;
    }
    groupLabelTree[firstG] = nullptr;
    groupLabelTree[secondG] = nullptr;
    int g = Find(first);
    AVLTree<LabelNode> *newTree = mergeTrees(tree1, tree2);
    groupLabelTree[g] = newTree;
}
