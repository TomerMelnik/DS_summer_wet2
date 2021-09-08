//
// Created by Tomer Melnik on 2021/09/05.
//

#include "ImageTagger.h"
ImageTagger::~ImageTagger() {
    delete hash;
}
void ImageTagger::addImage(int imageID){
    if(hash->find(imageID)) throw Failure();
    imageNode* node = new imageNode(imageID, this->pixels);
    hash->insert(node);
}
void ImageTagger::addImage(int imageID){
    if(hash->find(imageID)) throw Failure();
    imageNode* node = new imageNode(imageID, this->pixels);
    hash->insert(node);
}
void ImageTagger::deleteImage(int imageID) {
    if(!hash->find(imageID)) throw Failure();
    hash->remove(imageID);
}
void ImageTagger::SetLabelScore(int imageID, int pixel, int label, int score) {
    imageNode* node = hash->find(imageID);
    if(!node) throw Failure();
    node->setLabelScore(pixel, label, score);
}
void ImageTagger::ResetLabelScore(int imageID, int pixel, int label) {
    imageNode* node = hash->find(imageID);
    if(!node) throw Failure();
    node->resetLabelScore(pixel, label);
}
void ImageTagger::GetHighestScoredLabel(int imageID, int pixel, int *label) {
    imageNode* node = hash->find(imageID);
    if(!node) throw Failure();
    node->getHighestScoredLabel(pixel, label);
}
void ImageTagger::MergeSuperPixels(int imageID, int pixel1, int pixel2) {
    imageNode* node = hash->find(imageID);
    if(!node) throw Failure();
    node->mergeSuperPixels(pixel1, pixel2);
}
