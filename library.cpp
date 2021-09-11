//
// Created by Tomer Melnik on 2021/09/05.
//

#include "library.h"
#include "ImageTagger.h"
#include "exceptions.h"


void *Init(int pixels) {
    ImageTagger *DS = new ImageTagger(pixels);
    return (void *) DS;
}

StatusType AddImage(void *DS, int imageID) {
    if (DS == nullptr) return INVALID_INPUT;
    try {
        ((ImageTagger *) DS)->addImage(imageID);
        return SUCCESS;
    }
    catch (Success &e) { return SUCCESS; }
    catch (Failure &e) { return FAILURE; }
    catch (Invalid_Input &e) { return INVALID_INPUT; }


}

StatusType DeleteImage(void *DS, int imageID) {
    if (DS == nullptr) return INVALID_INPUT;
    try {
        ((ImageTagger *) DS)->deleteImage(imageID);
        return SUCCESS;
    }
    catch (Success &e) { return SUCCESS; }
    catch (Failure &e) { return FAILURE; }
    catch (Invalid_Input &e) { return INVALID_INPUT; }
}

StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score) {
    if (DS == nullptr) return INVALID_INPUT;
    try {
        ((ImageTagger *) DS)->SetLabelScore(imageID, pixel, label, score);
        return SUCCESS;
    }
    catch (Success &e) { return SUCCESS; }
    catch (Failure &e) { return FAILURE; }
    catch (Invalid_Input &e) { return INVALID_INPUT; }
}

StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label) {
    if (DS == nullptr) return INVALID_INPUT;

    try {
        ((ImageTagger *) DS)->ResetLabelScore(imageID, pixel, label);
        return SUCCESS;
    }
    catch (Success &e) { return SUCCESS; }
    catch (Failure &e) { return FAILURE; }
    catch (Invalid_Input &e) { return INVALID_INPUT; }
}

StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label) {
    if (DS == nullptr) return INVALID_INPUT;
    try {
        ((ImageTagger *) DS)->GetHighestScoredLabel(imageID, pixel, label);
        return SUCCESS;
    }
    catch (Success &e) { return SUCCESS; }
    catch (Failure &e) { return FAILURE; }
    catch (Invalid_Input &e) { return INVALID_INPUT; }
}

StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2) {
    if (DS == nullptr) return INVALID_INPUT;


    try {
        ((ImageTagger *) DS)->MergeSuperPixels(imageID, pixel1, pixel2);
        return SUCCESS;
    }
    catch (Success &e) { return SUCCESS; }
    catch (Failure &e) { return FAILURE; }
    catch (Invalid_Input &e) { return INVALID_INPUT; }
}

}

void Quit(void **DS) {

    auto image_tagger = (ImageTagger *) (*DS);
    delete image_tagger;
    *DS = nullptr;
}
