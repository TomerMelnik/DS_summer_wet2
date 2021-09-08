//
// Created by Linoy on 9/8/2021.
//

#include "ImageNode.h"

imageNode::~imageNode() {
    delete UF;
}

void imageNode::setLabelScore(int pixel, int label, int score) {
    int g = UF->find(pixel);
    AVLTree<LabelNode>* groupLabelTree = UF->groupLabelTree[g];
    if(groupLabelTree->find(label)) groupLabelTree->remove(label);
    LabelNode* labelNode = new LabelNode(label, score);
    groupLabelTree->insert(labelNode);
}

void imageNode::resetLabelScore(int pixel, int label) {
    int g = UF->find(pixel);
    AVLTree<LabelNode>* groupLabelTree = UF->groupLabelTree[g];
    if(groupLabelTree->find(label)) groupLabelTree->remove(label);
}

void imageNode::getHighestScoredLabel(int pixel, int *label) {
    int g = UF->find(pixel);
    AVLTree<LabelNode>* groupLabelTree = UF->groupLabelTree[g];
    if (!groupLabelTree->root) throw Failure();
    LabelNode* maxNode = groupLabelTree->getMaxValue();
    label* = maxNode->getId();
}

void imageNode::mergeSuperPixels(int pixel1, int pixel2){
    UF->Union(pixel1, pixel2);
}