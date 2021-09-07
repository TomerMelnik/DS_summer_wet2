//
// Created by timor on 02/01/2021.
//

#include "HashTable.h"

HashTable::HashTable(int size) {
    table = new LinkedList<NodeCourse> *[size];
    sizeOfTable = size;
    numberOfCourses = 0;

    for (int i = 0; i < sizeOfTable; ++i) {
        table[i] = new LinkedList<NodeCourse>;
    }
}
HashTable::~HashTable() {
    if (table != nullptr) {
        for (int i = 0; i < sizeOfTable; ++i) {

            delete table[i];
        }
    }

    delete [] table;
}

int HashTable:: Hash(int courseId) const{
    return (courseId % sizeOfTable);
}

int HashTable::HashAux(int size ,int courseId) {
    return (courseId % size);
}

void HashTable::resizeTable(int reduceOrIncrease){
    int new_size ;
    if(reduceOrIncrease == REDUCE) {
        new_size = (sizeOfTable / 2 < DEFAULTSIZE) ? DEFAULTSIZE : sizeOfTable / 4;
    }
    else {
        new_size = (sizeOfTable == 0) ? DEFAULTSIZE : sizeOfTable * 2;
    }

    HashTable *tmp = new HashTable(new_size);

    for(int i = 0 ;i < sizeOfTable;i++){
        std::shared_ptr<ListNode<NodeCourse>> runOfList = table[i]->head->next;
        while (runOfList->next != nullptr) {
            NodeCourse *tmp_data = new NodeCourse(*runOfList->returnData());
            tmp->insert(tmp_data);
            runOfList = runOfList->next;
        }

        runOfList.reset();
    }

    //  *this = *tmp;
    LinkedList<NodeCourse> **table_to_delete = this->table;

    for (int j = 0; j < sizeOfTable; ++j) {
        delete table_to_delete[j];
    }

    delete[] table_to_delete;

    this->table = tmp->table;
    tmp->table = nullptr;

    this->sizeOfTable = tmp->sizeOfTable;
    this->numberOfCourses = tmp->numberOfCourses;

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

    LinkedList<NodeCourse>* tmp = new LinkedList<NodeCourse>[new_size];

    for(int i = 0 ;i < sizeOfTable;i++){
        std::shared_ptr<ListNode<NodeCourse>> runOfList = table[i]->head->next;
        std::shared_ptr<ListNode<NodeCourse>> tailOfList = table[i]->tail;
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
void HashTable::insert(NodeCourse * T) {
    insertAux(T, sizeOfTable);
}

void HashTable::insertAux(NodeCourse *courseInput, int size) {
    int index = HashAux(size,courseInput->id());
    table[index]->insertFront(courseInput);
    numberOfCourses++;

    if (numberOfCourses >= sizeOfTable - 1) {
        resizeTable(INCREASE);
    }

}

NodeCourse* HashTable::find(int courseId){
    int index = Hash(courseId);
    return table[index]->find(courseId);
}
void HashTable::remove(int courseId){
    int index = Hash(courseId);
    table[index]->remove(courseId);
    numberOfCourses--;
    if (4 * numberOfCourses < sizeOfTable && sizeOfTable > DEFAULTSIZE) {
        resizeTable(REDUCE);
    }
}

