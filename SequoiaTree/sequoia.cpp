#include "sequoia.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

//Sequoia Code below!
int max(int x, int y) {
    if (x > y)
        return x;
    else
        return y;

}

int SequoiaNode::calcHeight(SequoiaNode* node)
{
    if (node == nullptr)
        return 0;
    else
    {
        int leftSide;
        int rightSide;
        leftSide = calcHeight(node->left);
        rightSide = calcHeight(node->right);
        if (leftSide > rightSide)
        {
            return leftSide + 1;

        }
        else
            return rightSide + 1;
    }
}

//call through parent
void SequoiaNode::fixBalanceInsert() {
    SequoiaNode* temp = this;
    while (temp != nullptr) {
        temp->height = calcHeight(temp);
        if (temp->isTall2()) {
            temp = temp->parent;
        }
        else {
            //Case:1
            if (temp->left != nullptr && temp->right != nullptr) {
                if (temp->left->height >= temp->right->height && temp->left->height < (2 * temp->right->height)) {
                    //rotating left
                    temp->right->parent = temp->parent;
                    if (temp->parent != nullptr)
                        temp->parent->right = temp->right;
                    temp->parent = temp->right;
                    temp->right = temp->right->left;
                    temp->parent->left = temp;


                }//Case:2
                else if (temp->right->height > temp->left->height && temp->right->height != (2 * temp->left->height)) {
                    temp->left->parent = temp->parent;
                    if (temp->parent != nullptr)
                        temp->parent->left = temp->left;
                    temp->parent = temp->left;
                    temp->left = temp->left->right;
                    temp->parent->right = temp;

                }
            }
            temp = temp->parent;
        }

    }



}
//call through parent
void SequoiaNode::fixBalanceRemove() {
    SequoiaNode* temp = this;
    while (temp != nullptr) {
        temp->height = calcHeight(temp);
        if (temp->isTall2()) {
            temp = temp->parent;
        }
        else {
            //Case:1
            if (temp->left != nullptr && temp->right != nullptr) {
                if (temp->left->height >= temp->right->height && temp->left->height < (2 * temp->right->height)) {
                    //rotating left
                    temp->right->parent = temp->parent;
                    if (temp->parent != nullptr)
                        temp->parent->right = temp->right;
                    temp->parent = temp->right;
                    temp->right = temp->right->left;
                    temp->parent->left = temp;



                }//Case:2
                else if (temp->right->height > temp->left->height && temp->right->height != (2 * temp->left->height)) {
                    temp->left->parent = temp->parent;
                    if (temp->parent != nullptr)
                        temp->parent->left = temp->left;
                    temp->parent = temp->left;
                    temp->left = temp->left->right;
                    temp->parent->right = temp;

                }
            }

        }
    }
}
void Sequoia::insert(int x) {
    if (root == nullptr) {
        root = new SequoiaNode(x);
        root->height = root->calcHeight(root);
        return;
    }
    SequoiaNode* temp = root;
    SequoiaNode* curr = nullptr;
    while (temp != nullptr) {
        curr = temp;
        if (x > temp->value)
            temp = temp->right;
        else
            temp = temp->left;
    }
    if (x < curr->value) {
        temp = new SequoiaNode(x);
        curr->left = temp;
        curr->left->parent = curr;
    }
    else if (x > curr->value) {
        temp = new SequoiaNode(x);
        curr->right = temp;
        curr->right->parent = curr;
    }
    //calculate height at each node
    while (temp != nullptr) {
        temp->height = temp->calcHeight(temp);
        temp = temp->parent;
    }
    curr->fixBalanceInsert();
    if (root->parent != nullptr) {
        root = root->parent;
    }

}
bool SequoiaNode::isLeaf() {
    if (this->right == nullptr && this->left == nullptr)
        return true;
    return false;
}
bool SequoiaNode::hasRightChild() {
    if (this->right != nullptr && this->left == nullptr)
        return true;
    return false;
}
bool SequoiaNode::hasLeftChild() {
    if (this->right == nullptr && this->left != nullptr)
        return true;
    return false;
}
bool SequoiaNode::hasTwoChildren() {
    if (this->right != nullptr && this->left != nullptr)
        return true;
    return false;

}
int SequoiaNode::getMaxFromLeftTree() {
    SequoiaNode* temp = this;
    SequoiaNode* prev = this;
    temp = temp->left;
    while (temp != nullptr) {
        prev = temp;
        temp = temp->right;
    }
    int val = prev->value;
    delete prev;
    prev = nullptr;
    return val;
}
//Deletion SequoiaNode
SequoiaNode* SequoiaNode::remove() {
    SequoiaNode* temp = this;
    if (temp->isLeaf()) {
        temp = nullptr;
    }
    else if (temp->hasTwoChildren()) {
        temp->value = temp->getMaxFromLeftTree();
    }
    else if (temp->hasLeftChild()) {
        temp->parent = temp->left;
        temp = nullptr;
    }
    else if (temp->hasRightChild()) {
        temp->parent = temp->right;
        temp = nullptr;
    }
    return temp;
}

void Sequoia::remove(int x) {
    SequoiaNode* temp = root;
    SequoiaNode* prev = nullptr;
    while (temp != nullptr) {
        if (x == temp->value) {
            if (temp->isLeaf()) {
                prev = temp->parent;
                if (prev->right == temp) {
                    delete prev->right;
                    prev->right = nullptr;
                }
                else if (prev->left == temp) {
                    delete prev->left;
                    prev->left = nullptr;
                }
                break;
            }
            else if (temp->hasTwoChildren()) {
                prev = temp;
                temp->value = temp->getMaxFromLeftTree();
                break;
            }
            else if (temp->hasLeftChild()) {
                prev = temp;
                temp->value = temp->left->value;
                delete temp->left;
                temp->left = nullptr;
                break;
            }
            else if (temp->hasRightChild()) {
                prev = temp;
                temp->value = temp->right->value;
                delete temp->right;
                temp->right = nullptr;
                break;
            }
        }
        else if (x < temp->value) {
            temp = temp->left;
        }
        else if (x > temp->value) {
            temp = temp->right;
        }
    }

    temp = prev;
    while (prev != nullptr) {
        prev->height = prev->calcHeight(prev);
        prev = prev->parent;
    }

    prev = temp;

    prev->fixBalanceRemove();
}
SequoiaNode* SequoiaNode::search(int x) {
    SequoiaNode* temp = this;
    while (temp != nullptr) {
        if (x == temp->value) {
            return temp;
        }
        else if (x < temp->value) {
            temp = temp->left;
        }
        else if (x > temp->value) {
            temp = temp->right;
        }
    }
}

void SequoiaNode::insert(int x) {
    SequoiaNode* temp = this;
    SequoiaNode* prev = this;
    while (temp != nullptr) {
        if (x > temp->value) {
            prev = temp;
            temp = temp->right;
        }
        else if (x < temp->value) {
            prev = temp;
            temp = temp->left;
        }
    }
    if (x > prev->value) {
        prev->right = new SequoiaNode(x);
        prev->right->parent = prev;
    }else if (x < prev->value) {
        prev->left = new SequoiaNode(x);
        prev->left->parent = prev;
    }

}
bool SequoiaNode::isTall2() const {
    int lht = 0, rht = 0;
    if (left != nullptr)
    {
        lht = left->height;
        if (!left->isTall2())
            return false;
    }
    if (right != nullptr)
    {
        rht = right->height;
        if (!right->isTall2())
            return false;
    }
    if (lht >= 2 * rht || rht >= 2 * lht)
        return true;
    else
    {
        return false;
    }
}