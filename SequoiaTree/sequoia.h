#ifndef __SEQUOIA_H
#define __SEQUOIA_H

#include <iostream>
using namespace std;
//Utility function
int max(int x, int y);

class SequoiaNode;
class Sequoia;
class SequoiaNode
{
  friend Sequoia;
  friend ostream& operator<<(ostream&, const SequoiaNode*);
private:
  int value;
  SequoiaNode* left;
  SequoiaNode* right;
  SequoiaNode* parent;
  int height;
public:
  //Basic constructor and destructor
  SequoiaNode(int x) { value = x; height = 1; left = right = parent = nullptr; }
  ~SequoiaNode() { delete left; delete right; }
  //Optional:  copy constructor or copy assignment

  //These functions are *required*
  void insert(int x);
  SequoiaNode* remove();
  int checkHeight() const;
  bool isTall() const;

  //May add any number of additional functions
  //E.g.,
  SequoiaNode* search(int x);
  void fixBalanceInsert();
  void fixBalanceRemove();
  int calcHeight(SequoiaNode* node);
  bool isLeaf();
  bool hasRightChild();
  bool hasLeftChild();
  bool hasTwoChildren();
  int getMaxFromLeftTree();
  /*SequoiaNode* rightRotate(SequoiaNode* y);
  SequoiaNode* leftRotate(SequoiaNode* y);*/
  bool isTall2() const;
};

class Sequoia
{
  friend ostream& operator<<(ostream&, const Sequoia&);
private:
  SequoiaNode* root;
  int size;
public:
  //Basic constructor and destructor
  Sequoia() { root = nullptr; size = 0; }
  ~Sequoia() { delete root; }
  //Optional: copy constructor or copy assignment

  //These functions are required
  void insert(int x);
  void remove(int x);
  bool checkHeight() const;
  bool isTall() const;

  //May add any number of additional functions
  int getRoot() { return root->value; }
 
};

//Print functions (required)
ostream& operator<<(ostream&, const Sequoia&);
ostream& operator<<(ostream&, const SequoiaNode*);

#endif //__SEQUOIA_H