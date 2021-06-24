#pragma once
#include <iostream>
#include <vector>
#define TREE_SIZE 30


class Node {

  public:

    Node *lptr, *rptr;
    int prob;
    char chtr;
    std::string bit;
    Node();
    //Node();
    
};

class HuffmanTree {

  public:
    
    Node* tptr;
    std::vector <Node> tree;
    int count; // number of populated nodes in the tree array

  
    HuffmanTree();
    void mergeNodes(Node*, Node*, Node*);
    void populateTree(long long*);
    void compress();



};



class FileHandle {

  public:

    FILE *fp;
    FileHandle(char*);
    int filesize();
    void readFile(long long*);
    void writeFile(FILE *, FILE*, std::string, int, HuffmanTree);
    void writeUchar(FILE *, unsigned char, unsigned char*, int);

};

