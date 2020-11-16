#include<iostream>
using namespace std;

#include "tnode.h"
#ifndef BST_H
#define BST_H
class BST{
  public:
    BST():  root(NULL) {};
    ~BST(){ clean(root); root = NULL; };

    void insert(string akey, string word){
      if(root == NULL){
        root = new Tnode(akey, word);
        return;
      }
      root = insert(root, akey, word);
      updateHeight(root);
      updateSize(root);
    };
    void print_inorder(){ print_inorder(root);
      cout << endl;
    };
    void findPrint(string akey){ findPrint(root, akey); };
    void heightPrint(){ 
      heightPrint(root); 
      cout << endl;
    };

    void updateHeight(Tnode *cur);
    void printBF() {printBF(root); cout << endl;}
    int balanceFactor(Tnode* cur);

    void remove(string akey)
    {
      if (!root)
        return;

      root = remove(root, akey);
      updateHeight(root);
      updateSize(root);
    };

    void updateSize(Tnode* cur);
    void printSize()
    {
      printSize(root);
      cout << endl;
    };

    void findLCA(string k1, string k2)
    {
      findLCA(root, k1, k2);
      cout << endl;
    };

    void findKSmallest(int k)
    {
      string kSmallest = findKSmallest(root, k);
      cout << kSmallest;
      cout << endl;
    };

    void printLongestPath()
    {
      printLongestPath(root);
      cout << endl;
    };

    void collectSubtree(string akey)
    {
      vector<string> subtree;

      Tnode* cur = findK(root, akey);

      if (cur)
      {
        collectSubtree(cur, subtree, akey);

        printSubtree(subtree);
      }
    };

  private:
    void heightPrint(Tnode *cur);
    Tnode* insert(Tnode *cur, string akey, string aval);
    void print_inorder(Tnode *cur);
    Tnode *root = NULL;
    void clean(Tnode* cur);
    Tnode* copy(Tnode* cur);
    void findPrint(Tnode* cur, string key);
    int getHeight(Tnode* cur);
    Tnode* rebalance(Tnode* cur);
    Tnode* rightRotation(Tnode* cur);
    Tnode* leftRotation(Tnode* cur);
    void printBF(Tnode* cur);
    Tnode* getLeftMost(Tnode* cur);
    Tnode* remove(Tnode* cur, string akey);
    int getSize(Tnode* cur);
    void printSize(Tnode* cur);
    void findLCA(Tnode* cur, string k1, string k2);
    string findKSmallest(Tnode* cur, int k);
    void printLongestPath(Tnode* cur);
    Tnode* findK(Tnode* cur, string k);
    void collectSubtree(Tnode* cur, vector<string> &subtree, string akey);
    void printSubtree(vector<string> subtree);
};

#endif
