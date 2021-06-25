#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include "cpress.hpp"

#define ASCII_SIZE 256

using namespace std;

/*
 *  Huffman compression algorithm.
 * */

bool comparator0(Node A, Node B) {
  return A.prob < B.prob;
}

int main(int argc, char* argv[])
{


  HuffmanTree htree;
  if (argc == 1) {
    
    /*
     *  stderr
     * */
    cerr << "An error has occured. There is no file to compress.\n";
    exit(1);
  }

  
  long long int numbers[2 * ASCII_SIZE];
  memset(numbers, 0, sizeof(numbers));
  FileHandle file(argv[1]);
  FILE *fp = file.fp;
  
  file.readFile(numbers);
  htree.populateTree(numbers);


 

  /*
   * Should be using a priority queue for min heap to simulate the algorithm.
   * Instead, using STL sort()
   * */

  sort(htree.tree.begin(), htree.tree.begin() + htree.count, comparator0);
  htree.compress();

  FILE *compress_fp = NULL;
  string compressed_file = argv[1];
  compressed_file += "_compressed";
  
  compress_fp  = fopen(&compressed_file[0], "wb");

  file.writeFile(compress_fp, fp, compressed_file, file.filesize(), htree);

  cout << "Finished!\n";
  return 0;
}


