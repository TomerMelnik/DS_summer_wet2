//
// Created by timor on 02/01/2021.
//

#include "HashTable.h"

HashTable::HashTable(int size) {
    table = new LinkedList<imageNode> *[size];
    sizeOfTable = size;
    numberOfImages = 0;

    for (int i = 0; i < sizeOfTable; ++i) {
        table[i] = new LinkedList<imageNode>;
    }
}

HashTable::~HashTable() {
    if (table != nullptr) {
        for (int i = 0; i < sizeOfTable; ++i) {

            delete table[i];
        }
    }

    delete[] table;
}

int HashTable::Hash(int imageID) const {
    return (imageID % sizeOfTable);
}

int HashTable::HashAux(int size, int imageID) {
    return (imageID % size);
}

void HashTable::resizeTable(int reduceOrIncrease) {
    int new_size;
    if (reduceOrIncrease == REDUCE) {
        new_size = (sizeOfTable / 2 < DEFAULTSIZE) ? DEFAULTSIZE : sizeOfTable / 4;
    } else {
        new_size = (sizeOfTable == 0) ? DEFAULTSIZE : sizeOfTable * 2;
    }

    HashTable *tmp = new HashTable(new_size);

    for (int i = 0; i < sizeOfTable; i++) {
        std::shared_ptr <ListNode<imageNode>> runOfList = table[i]->head->next;
        while (runOfList->next != nullptr) {
            imageNode *tmp_data = runOfList->data;
            runOfList->data = nullptr;
            tmp->insert(tmp_data);
            runOfList = runOfList->next;
        }

        runOfList.reset();
    }

    //  *this = *tmp;
    LinkedList<imageNode> **table_to_delete = this->table;

    for (int j = 0; j < sizeOfTable; ++j) {
        delete table_to_delete[j];
    }

    delete[] table_to_delete;

    this->table = tmp->table;
    tmp->table = nullptr;

    this->sizeOfTable = tmp->sizeOfTable;
    this->numberOfImages = tmp->numberOfImages;

    delete tmp;

}


void HashTable::reduceTable() {
}

/*
void HashTable::increaseTable() {
    int new_size;
    if(sizeOfTable == 0) {
        new_size = DEFAULTSIZE;
    }
    else {
        new_size = 2 * sizeOfTable;
    }

    LinkedList<imageNode>* tmp = new LinkedList<imageNode>[new_size];

    for(int i = 0 ;i < sizeOfTable;i++){
        std::shared_ptr<ListNode<imageNode>> runOfList = table[i]->head->next;
        std::shared_ptr<ListNode<imageNode>> tailOfList = table[i]->tail;
        while(runOfList != table[i]->tail){
            insertAux(tmp,runOfList->returnData(),new_size);
            runOfList = runOfList->next;
        }
        runOfList = nullptr;
        tailOfList= nullptr;
    }

    sizeOfTable=new_size;
    delete [] table;//TODO
    table = tmp;
}
*/
void HashTable::insert(imageNode *T) {
    insertAux(T, sizeOfTable);
}

void HashTable::insertAux(imageNode *node, int size) {
    int index = HashAux(size, node->id());
    table[index]->insertFront(node);
    numberOfImages++;
    if (numberOfImages >= sizeOfTable - 1) {
        resizeTable(INCREASE);
    }
}

imageNode *HashTable::find(int imageID) {
    int index = Hash(imageID);
    return table[index]->find(imageID);
}

void HashTable::remove(int imageID) {
    int index = Hash(imageID);
    table[index]->remove(imageID);
    numberOfImages--;
    if (4 * numberOfImages < sizeOfTable && sizeOfTable > DEFAULTSIZE) {
        resizeTable(REDUCE);
    }
}

