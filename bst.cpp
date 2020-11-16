#include<iostream> 
#include <algorithm>
using namespace std; 
#include "bst.h"

void BST::heightPrint(Tnode *cur){
  if(cur != NULL){
    heightPrint(cur->left);
    cout << cur->height << " ";
    heightPrint(cur->right);
  }

}
void BST::findPrint(Tnode *cur, string akey){
  if(cur != NULL){
    if(cur->key == akey){
      int asize = (int)(cur->value).size();
      for(int i = 0; i < asize ; i++)
        cout << (cur->value)[i] << " ";
      cout << endl;
      return;
    }else if(akey < cur->key)
      findPrint(cur->left, akey);
    else
      findPrint(cur->right, akey);
  }
}//findPrint()

void BST::print_inorder(Tnode *cur){
  if(cur == NULL)
    return;
  print_inorder(cur->left);
  cout << "(" << cur->key << "){";
  int asize = (int)(cur->value).size();
  for(int i = 0; i < asize; i++)
    cout << (cur->value)[i] << " " ;
  cout << "} ";
  print_inorder(cur->right);
}//print_inorder


void BST::clean(Tnode *cur){
  if(cur == NULL)
    return;
  clean(cur->left);
  clean(cur->right);
  delete cur;
}//clean()

Tnode* BST::insert(Tnode *cur, string akey, string aval){
  if(akey < cur->key){
    if(cur->left == NULL){
      cur->left = new Tnode(akey, aval);
      updateHeight(cur);
      updateSize(cur);
      return cur;
    }
    else{
      cur -> left = insert(cur->left, akey, aval);
      if ((balanceFactor(cur) < -1) || (balanceFactor(cur) > 1))
        cur  = rebalance(cur);
      updateHeight(cur);
      updateSize(cur);
      return cur;
    }
  }//if 
  else if(akey > cur->key){
    if(cur->right == NULL){
      cur->right = new Tnode(akey, aval);
      updateHeight(cur);
      updateSize(cur);
      return cur;
    }
    else{
      cur -> right = insert(cur->right, akey, aval);
      if ((balanceFactor(cur) < -1) || (balanceFactor(cur) > 1))
        cur  = rebalance(cur);
      updateHeight(cur);
      updateSize(cur);
      return cur;
    }
  }//else if
  else{
    (cur->value).push_back(aval);
    return cur;
  }

  updateHeight(cur);
  updateSize(cur);
  return cur;
}//insert()

int BST::getHeight(Tnode* cur)
{
  if (!cur)
    return -1;

  return max(getHeight(cur -> left), getHeight(cur -> right)) + 1;
}

void BST::updateHeight(Tnode* cur)
{
  if (!cur)
    return;

  int lh = getHeight(cur -> left);
  int rh = getHeight(cur -> right);
  int myh = (lh > rh) ? lh + 1 : rh + 1;

  cur -> height = myh;
}

int BST::balanceFactor(Tnode* cur)
{
  if (!cur)
    return 0;

  return getHeight(cur -> left) - getHeight(cur -> right);
}

Tnode* BST::rebalance(Tnode* cur)
{
  if (!cur)
    return cur;

  if (balanceFactor(cur) == 2)
  {
    if (balanceFactor(cur -> left) >= 0)
    {
      cur = rightRotation(cur);
    }

    else
    {
      cur -> left = leftRotation(cur -> left);
      cur = rightRotation(cur);
    }
  }

  else if (balanceFactor(cur) == -2)
  {
    if (balanceFactor(cur -> right) <= 0)
    {
      cur = leftRotation(cur);
    }

    else
    {
      cur -> right = rightRotation(cur -> right);
      cur = leftRotation(cur);
    }
  }

  else
  {
      updateHeight(cur);
      updateSize(cur);
  }
  return cur;
}

Tnode* BST::rightRotation(Tnode* cur)
{
  Tnode* leftChild = cur -> left;
  cur -> left = cur -> left -> right;
  updateHeight(cur);
  updateSize(cur);
  leftChild -> right = cur;
  updateHeight(leftChild);
  updateSize(leftChild);
  return leftChild;
}

Tnode* BST::leftRotation(Tnode* cur)
{
  Tnode* rightChild = cur -> right;
  cur -> right = cur -> right -> left;
  updateHeight(cur);
  updateSize(cur);
  rightChild -> left = cur;
  updateHeight(rightChild);
  updateSize(rightChild);
  return rightChild;
}

void BST::printBF(Tnode* cur)
{
  if (!cur)
    return;

  printBF(cur -> left);

  cout << balanceFactor(cur) << " ";

  printBF(cur -> right);
}

Tnode* BST::getLeftMost(Tnode* cur)
{
  if (!cur)
    return cur;

  if (cur -> left)
    return getLeftMost(cur -> left);

  return cur;

}

Tnode* BST::remove(Tnode* cur, string akey)
{
  if (!cur)
    return NULL;

  if (akey == cur -> key)
  {
    if ((!cur -> left) && (!cur -> right)) 
    { 
      delete cur;
      cur = NULL;
    }

    else if ((!cur -> left) || (!cur -> right))
    {
      Tnode* temp = cur -> left;
      if (!cur -> left)
        temp = cur -> right;
      delete cur;
      cur = temp;
    }

    else
    {
      Tnode* lmn = getLeftMost(cur -> right);
      cur -> key  = lmn -> key;
      cur -> value = lmn -> value;
      cur -> right = remove(cur -> right, lmn -> key);
      cur = rebalance(cur);
    }
  }

  else if (akey < cur -> key)
  {
    cur -> left = remove(cur -> left, akey);
    cur = rebalance(cur);
  }

  else
  {
    cur -> right = remove(cur -> right, akey);
    cur = rebalance(cur);
  }

  //cur = rebalance(cur);
  updateHeight(cur);
  updateSize(cur);

  return cur;
}

int BST::getSize(Tnode* cur)
{
  if (!cur)
    return 0;

  return getSize(cur -> left) + getSize(cur -> right) + 1;
}

void BST::updateSize(Tnode* cur)
{
  if (!cur)
          return;
  if (!cur-> left && !cur -> right)
    return;

  else if (cur -> left && cur -> right)
    cur -> size = getSize(cur -> left) + getSize(cur -> right) + 1;

  else if (cur -> left && !cur -> right)
    cur -> size = getSize(cur -> left);

  else if (!cur -> left && cur -> right)
    cur -> size = getSize(cur -> right);
}

void BST::printSize(Tnode* cur)
{
  if (!cur)
    return;

  printSize(cur -> left);

  cout << getSize(cur) << " ";

  printSize(cur -> right);
}

void BST::findLCA(Tnode* cur, string k1, string k2)
{
  if (!cur)
    return;

  if ((k1 < cur -> key) && (k2 > cur -> key))
    cout << cur -> key;
  
  else if ((k1 > cur -> key) && (k2 < cur -> key))
    cout << cur -> key;

  else if ((k1 < cur -> key) && (k2 < cur -> key))
    findLCA(cur -> left, k1, k2);

  else if ((k1 > cur -> key) && (k2 > cur -> key))
    findLCA(cur -> right, k1, k2);
}

string BST::findKSmallest(Tnode* cur, int k)
{
  if (!cur)
    return "";

  int sizeL = getSize(cur -> left);

  if (k <= sizeL)
    return findKSmallest(cur -> left, k);

  else if (k == sizeL + 1)
    return cur -> key;

  else
    return findKSmallest(cur -> right, k - sizeL - 1);
}

void BST::printLongestPath(Tnode* cur)
{
  if (!cur)
    return;

  int heightL = getHeight(cur -> left);
  int heightR = getHeight(cur -> right);

  cout << cur -> key << " ";

  if (heightL >= heightR)
    printLongestPath(cur -> left);

  else if (heightR > heightL)
    printLongestPath(cur -> right);
}

Tnode* BST::findK(Tnode* cur, string k)
{
  if (!cur)
    return cur;

  if (cur -> key == k)
    return cur;

  else if (k < cur -> key)
    return findK(cur -> left, k);

  else
    return findK(cur -> right, k);
}

void BST::collectSubtree(Tnode* cur, vector<string> &subtree, string akey)
{
  if (!cur)
    return;

  collectSubtree(cur -> left, subtree, akey);

  subtree.push_back(cur -> key);

  collectSubtree(cur -> right, subtree, akey);
}

void BST::printSubtree(vector<string> subtree)
{
  for (int i = 0; i < (int) subtree.size(); i++)
    cout << subtree[i] << " ";

  cout << endl;
}
