//
// Created by Linoy on 9/8/2021.
//

#ifndef DS_SUMMER_WET2_IMAGENODE_H
#define DS_SUMMER_WET2_IMAGENODE_H
#include "unionFind.h"

class imageNode{
    unionFind* UF;
    int imageID;
public:
    imageNode(int imageID, int pixels) : imageID(imageID){
        UF = new unionFind(pixels);
    }
    ~imageNode();
    int id(){
        return imageID;
    }
    void setLabelScore(int pixel, int label, int score);
    void resetLabelScore(int pixel, int label, int score);
    void getHighestScoredLabel(int pixel, int* label);
    void mergeSuperPixels(int pixel1, int pixel2);
};

#endif //DS_SUMMER_WET2_IMAGENODE_H
