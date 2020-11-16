#include <stdlib.h>
#include<iostream>
#include<string>
#include<iomanip>
#include<stdio.h>
#include<cstdio>
#include<cmath>
#include<fstream>
using namespace std;

#include "bst.h"


int main(int argc, char* argv[]){


  BST numbers;
  string command;
  while(cin >> command){//
    if(command == "print_inorder"){
      numbers.print_inorder();
      cout << endl;
    }else if(command == "heightPrint"){
      numbers.heightPrint();
      cout << endl;
    }else if(command == "printBF"){
      numbers.printBF();
      cout << endl;
    }
    else if(command == "findPrint"){
      string akey;
      cin >> akey;
      numbers.findPrint(akey);
    }else if(command == "insert"){
      string word;
      cin >> word;
      int len ;
      cin >> len;
      string akey = word.substr(0, len);
      numbers.insert(akey, word);
    }else if(command == "remove"){
      string akey;
      cin >> akey;
      numbers.remove(akey);
    }else if (command == "printSize"){
      numbers.printSize();
      cout << endl;
    }else if (command == "findLCA"){
      string akey1 = "";
      string akey2 = "";
      cin >> akey1;
      cin >> akey2;
      numbers.findLCA(akey1, akey2);
    }else if (command == "findKthSmallest"){
      int k = 0;
      cin >> k;
      numbers.findKSmallest(k);
    }else if (command == "printLongestPath"){
      numbers.printLongestPath();
    }else if (command == "collectSubtree"){
      string akey = "";
      cin >> akey;
      numbers.collectSubtree(akey);
    }else{
      cerr << "ERROR: command " << command << " is not found." << endl;
    }
  }//while

  return 0;

}//main()
