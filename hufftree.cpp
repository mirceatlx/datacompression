#include "cpress.hpp"
#define TREE_SIZE 30

/*
 * Importance of the order of children.
 * */

HuffmanTree::HuffmanTree() : tree(TREE_SIZE * 3) {

  //tptr = tree;
  //Node* temp = new Node()[2 * TREE_SIZE];
  //tree = temp;
  //tptr = tree;
  
}

void HuffmanTree::mergeNodes(Node* A, Node* B, Node* C) {

  C->prob = A->prob + B->prob;
  C->lptr = A;
  C->rptr = B;


}


void HuffmanTree::populateTree(long long *numbers) {
  /*
   * Populate the tree with respect to the values found in the specified file.
   * */
  long long* p;

  std::vector <Node> ::iterator it = tree.begin();
  tptr = &(*it);
  int temp = 0;
  for(p = numbers; p < numbers + 256; p++) {
    if (*p) {
      tptr->lptr = tptr->rptr = NULL;
      tptr->prob = *p;
      tptr->chtr = p - numbers;
      tptr++;
      temp++;
    }
  }

  count = temp; // class variable
  
}


void HuffmanTree::compress() {
   /*
    * Compression algorithm.
    * Take the 2 nodes with the smallest probability of the symbol they represent.
    * Create a new internal node having these 2 nodes as children.
    * Repeat the process.
    *
    * isleaf traverses through leaves
    * notleaf traverses through nodes that are not leaves 
    *
    * Convention : left child : 1
    *              right child : 0
    * */

    
    std::vector <Node> ::iterator it = tree.begin();
    Node* min1 = &(*it), *min2 = &(*it) + 1, *current = &(*it) + count, *notleaf = &(*it) + count, *isleaf = &(*it) + 2;
    for(int i = 0; i < count - 1; i++) {
      
      current->prob = min1->prob + min2->prob;
      current->lptr = min1;
      current->rptr = min2;
      min1->bit = "1";
      min2->bit = "0";
      current++;

      if (isleaf >= &(*it) + count) {
        /*
         * If isleaf passes tree + count, then min1 needs to be an internal node.
         * */
        min1 = notleaf;
        notleaf++;
      }
      else {
        if(isleaf->prob < notleaf->prob) {
          min1 = isleaf;
          isleaf++;
        }
        else {
          min1 = notleaf;
          notleaf++;
        }
      }
      // same thinking for min2
      if (isleaf >= &(*it) + count) {
        /*
         * If isleaf passes tree + count, then min2 needs to be an internal node.
         * */
        min2 = notleaf;
        notleaf++;
      }
      else {
        if(isleaf->prob < notleaf->prob) {
          min2 = isleaf;
          isleaf++;
        }
        else {
          min2 = notleaf;
          notleaf++;
        }
      }

      /*
       * In the end, node tree + 2 * count - 2 is going to be the root of the tree.
       * */

    }


    /*
     * Encoding the tree.
     * Every leaf is assigned a transformation string that corresponds to it.
     * The most used character is using the least number of bits.
     * */
    it = tree.begin();
    for (Node* temp = &(*it) + 2 * count - 2; temp >= &(*it); temp--) {
      if(temp->lptr) {
        temp->lptr->bit = temp->bit + temp->lptr->bit;
      }
      if (temp->rptr) {
        temp->rptr->bit = temp->bit + temp->rptr->bit;
      }
    }


}






