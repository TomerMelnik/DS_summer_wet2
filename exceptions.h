//
// Created by Tomer Melnik on 2021/09/05.
//

#ifndef DATASTRUCTURES2_1_EXCEPTIONS_H
#define DATASTRUCTURES2_1_EXCEPTIONS_H

#include <exception>

class Success : public std::exception {
};

class Failure : public std::exception {
};

class Invalid_Input : public std::exception {
};
#endif //DATASTRUCTURES2_1_EXCEPTIONS_H
