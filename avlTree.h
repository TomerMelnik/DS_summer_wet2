//
// Created by Tomer Melnik on 2021/08/23.
//

#ifndef DS_SUMMER_WET1_AVLTREE_H
#define DS_SUMMER_WET1_AVLTREE_H


#include <iostream>

template<class T>
class Node {
public:
    T *data;
    Node *right;
    Node *left;
    int height;
    T *maxInSubtree;

    explicit Node(T *value);

    ~Node();
};

template<class T>
void updateMax(Node<T> *root) {
    T *max;
    if (root->left && root->right) {
        if (root->left->maxInSubtree->getData() > root->right->maxInSubtree->getData()) {
            max = root->data->getData() < root->left->maxInSubtree->getData() ? root->left->maxInSubtree : root->data;
        } else {
            max = root->data->getData() > root->right->maxInSubtree->getData() ? root->data : root->right->maxInSubtree;
        }
    } else if (root->left) {
        max = root->data->getData() < root->left->maxInSubtree->getData() ? root->left->maxInSubtree : root->data;
    } else if (root->right) {
        max = root->data->getData() > root->right->maxInSubtree->getData() ? root->data : root->right->maxInSubtree;
    } else {
        max = root->data;
    }
    root->maxInSubtree = max;
}


template<class T>
class AVLTree {
public:
    Node<T> *root;
    int numOfNodes;

    AVLTree<T>() : root(NULL), numOfNodes(0) {}

    AVLTree<T>(T **arr, int size);

    ~AVLTree();

    void insert(T *data);

    void remove(int key);

    Node<T> *find(int key);

    T **toArray();

    T *getMaxValue();

};

static int max(int a, int b);


template<class T>
Node<T>::Node(T *value) {
    data = value;
    right = nullptr;
    left = nullptr;
    height = 1;
    maxInSubtree = value;
}

template<class T>
Node<T>::~Node() {

    if (data != NULL) {
        delete data;
    }
}


template<class T>
Node<T> *fillTree(T **arr, int start, int end) {
    if (start > end)
        return nullptr;
    int mid = (start + end) / 2;
    Node<T> *root = new Node<T>(arr[mid]);
    root->left = fillTree(arr, start, mid - 1);
    root->right = fillTree(arr, mid + 1, end);
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    updateMax(root);
    return root;
}

template<class T>
AVLTree<T>::AVLTree(T **arr, int size) : numOfNodes(size) {
    root = fillTree(arr, 0, size - 1);
}


template<class T>
AVLTree<T>::~AVLTree() {
    clearTree(root);
}

template<class T>
Node<T> *AVLTree<T>::find(int key) {
    return findNode(root, key);
}


template<class T>
void AVLTree<T>::remove(int key) {

    this->root = removeNode(this->root, key);
    numOfNodes--;
}

template<class T>
void AVLTree<T>::insert(T *data) {
    root = insertNode(root, data);
    numOfNodes++;

}

template<class T>
T *AVLTree<T>::getMaxValue() {
    if (root == nullptr) return nullptr;

    return root->maxInSubtree;
}

template<class T>
T **AVLTree<T>::toArray() {
    T **arr = new T *[numOfNodes];
    int *currentNum = new int();
    *currentNum = 0;
    toArrayAux(currentNum, root, arr);
    delete currentNum;
    return arr;
}

template<class T>
void toArrayAux(int *currentNum, Node<T> *current, T **arr) {
    if (!current) return;
    toArrayAux(currentNum, current->left, arr);
    arr[(*currentNum)] = current->data;
    (*currentNum)++;
    toArrayAux(currentNum, current->right, arr);
}

template<class T>
static void clearTree(Node<T> *node) {
    if (node != NULL) {
        if (node->left != NULL) {
            clearTree(node->left);
        }

        if (node->right != NULL) {
            clearTree(node->right);
        }
        delete node;
    }
}


template<class T>
Node<T> *findNode(Node<T> *node, int key) {
    if (node == NULL)
        return NULL;
    if (key < node->data->getID())
        return findNode(node->left, key);
    if (key > node->data->getID())
        return findNode(node->right, key);
    return node;
}

template<class T>
static int getHeight(Node<T> *node) {
    if (node == NULL)
        return 0;
    return node->height;
}


template<class T>
static Node<T> *rightRotate(Node<T> *old_root) {
    Node<T> *new_root = old_root->left;
    Node<T> *right_son = new_root->right;

    new_root->right = old_root;
    old_root->left = right_son;

    old_root->height = 1 + max(getHeight(old_root->left), getHeight(old_root->right));
    new_root->height = 1 + max(getHeight(new_root->left), getHeight(new_root->right));

    updateMax(old_root);//Updates Rank
    updateMax(new_root);
    return new_root;
}

template<class T>
static Node<T> *leftRotate(Node<T> *old_root) {
    Node<T> *new_root = old_root->right;
    Node<T> *left_son = new_root->left;

    new_root->left = old_root;
    old_root->right = left_son;

    old_root->height = 1 + max(getHeight(old_root->left), getHeight(old_root->right));
    new_root->height = 1 + max(getHeight(new_root->left), getHeight(new_root->right));

    updateMax(old_root);//Updates Rank
    updateMax(new_root);

    return new_root;
}

template<class T>
static int getBalanceFactor(Node<T> *node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

template<class T>
static Node<T> *insertNode(Node<T> *root, T *data) {
    if (root == NULL) {
        Node<T> *node = new Node<T>(data);
        return node;
    }
    if (data->getID() < root->data->getID())
        root->left = insertNode(root->left, data);
    else if (data->getID() > root->data->getID())
        root->right = insertNode(root->right, data);
    else
        return root;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right)); //Updates height
    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0) //LL case
        return rightRotate(root);
    if (balance > 1 && getBalanceFactor(root->left) < 0) //LR
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) <= 0) //RR case
        return leftRotate(root);
    if (balance < -1 && getBalanceFactor(root->left) > 0) //RL
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    updateMax(root);
    return root;
}

template<class T>
static Node<T> *getInorderNext(Node<T> *node) {// gets the node with the next closest large value
    Node<T> *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

template<class T>
static Node<T> *getInorderFather(Node<T> *node)//gets Father of Inorder Successor
{
    Node<T> *current = node;
    while (current->left != NULL && current->left->left != NULL)
        current = current->left;
    return current;
}


template<class T>
static Node<T> *
rotateAux(Node<T> *curr_node, Node<T> *successor_father) // Dont ask me why but if i remove this nothing works
{
    if (curr_node == NULL)
        return NULL;
    if (curr_node != successor_father)
        curr_node->left = rotateAux(curr_node->left, successor_father);
    curr_node->height = 1 + max(getHeight(curr_node->left), getHeight(curr_node->right)); //updates height
    int balance = getBalanceFactor(curr_node);

    if (balance > 1 && getBalanceFactor(curr_node->left) >= 0) //LL case
        return rightRotate(curr_node);
    if (balance > 1 && getBalanceFactor(curr_node->left) < 0) //LR case
    {
        curr_node->left = leftRotate(curr_node->left);
        return rightRotate(curr_node);
    }
    if (balance < -1 && getBalanceFactor(curr_node->right) <= 0) //RR case
        return leftRotate(curr_node);
    if (balance < -1 && getBalanceFactor(curr_node->left) > 0) //RL case
    {
        curr_node->right = rightRotate(curr_node->right);
        return leftRotate(curr_node);
    }
    updateMax(curr_node);
    return curr_node;
}


template<class T>
static Node<T> *removeNode(Node<T> *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data->getID())
        root->left = removeNode(root->left, key);

    else if (key > root->data->getID())
        root->right = removeNode(root->right, key);

    else //Remove Current Node
    {
        if (root->left == NULL || root->right == NULL) //one or fewer children
        {
            Node<T> *temp = root;
            if (root->left != NULL) {
                root = root->left;
            } else {
                root = root->right;
            }


            delete temp;


        } else //two children
        {
            auto successor = getInorderNext(root->right); //gets Inorder successor
            auto successor_father = getInorderFather(root->right);
            auto left = root->left;
            if (successor_father != successor)
                successor_father->left = successor->right;
            if (root->right != successor)
                successor->right = root->right;
            delete root;
            root = successor;
            root->left = left;
            root->right = rotateAux(root->right, successor_father);
        }
    }
    if (root == NULL)return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right)); //updates height
    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0) //LL case
        return rightRotate(root);
    if (balance > 1 && getBalanceFactor(root->left) < 0) //LR case
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) <= 0) //RR case
        return leftRotate(root);
    if (balance < -1 && getBalanceFactor(root->left) > 0) //RL case
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    updateMax(root);
    return root;
}

static int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}


#endif //DS_SUMMER_WET1_AVLTREE_H
