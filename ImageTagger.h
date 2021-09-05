//
// Created by Tomer Melnik on 2021/09/05.
//

#ifndef DS_SUMMER_WET2_IMAGETAGGER_H
#define DS_SUMMER_WET2_IMAGETAGGER_H


class ImageTagger {


public:
    ImageTagger(int pixels);
   void addImage(int imageID);
   void deleteImage(int imageID);
   void SetLabelScore( int imageID, int pixel, int label, int score);
   void ResetLabelScore(int imageID, int pixel, int label);
   void MergeSuperPixels(int imageID, int pixel1, int pixel2);
   void GetHighestScoredLabel(int imageID, int pixel, int *label);

};


#endif //DS_SUMMER_WET2_IMAGETAGGER_H
