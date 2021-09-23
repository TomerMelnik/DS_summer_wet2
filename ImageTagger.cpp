//
// Created by Tomer Melnik on 2021/09/05.
//

#include "ImageTagger.h"

ImageTagger::~ImageTagger() {
    delete hash;
}

void ImageTagger::addImage(int imageID) {
    if (imageID <= 0) throw Invalid_Input();
    if (hash->find(imageID)!= nullptr) throw Failure();
    imageNode *node = new imageNode(imageID, this->pixels);
    hash->insert(node);
}

void ImageTagger::deleteImage(int imageID) {
    if (imageID <= 0) throw Invalid_Input();
    if (!hash->find(imageID)) throw Failure();
    hash->remove(imageID);
}

void ImageTagger::SetLabelScore(int imageID, int pixel, int label, int score) {
    if (imageID <= 0 || pixel < 0 || pixel >= this->pixels || label <= 0 || score <= 0) throw Invalid_Input();


    imageNode *node = hash->find(imageID);
    if (!node) throw Failure();
    node->setLabelScore(pixel, label, score);
}

void ImageTagger::ResetLabelScore(int imageID, int pixel, int label) {
    if (imageID <= 0 || pixel < 0 || pixel >= this->pixels || label <= 0) throw Invalid_Input();

    imageNode *node = hash->find(imageID);
    if (!node) throw Failure();
    node->resetLabelScore(pixel, label);
}

void ImageTagger::GetHighestScoredLabel(int imageID, int pixel, int *label) {
    if (imageID <= 0 || pixel < 0 || pixel >= pixels || !label) throw Invalid_Input();

    imageNode *node = hash->find(imageID);
    if (!node) throw Failure();
    node->getHighestScoredLabel(pixel, label);
    if(*label == 178){

    }
}

void ImageTagger::MergeSuperPixels(int imageID, int pixel1, int pixel2) {
    if (imageID <= 0 || pixel1 < 0 || pixel1 >= pixels || pixel2 < 0 || pixel2 >= pixels) throw Invalid_Input();


    imageNode *node = hash->find(imageID);
    if (!node) throw Failure();
    node->mergeSuperPixels(pixel1, pixel2);
}
