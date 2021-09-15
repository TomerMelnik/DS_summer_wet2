cmake_minimum_required(VERSION 3.15)
project(DataStructures2.1)

set(CMAKE_CXX_STANDARD 11)

add_executable(Tagger main.cpp ImageNode.cpp ImageNode.h ImageTagger.h ImageTagger.cpp library.h library.cpp exceptions.h avlTree.h HashTable.cpp HashTable.h unionFind.cpp unionFind.h)