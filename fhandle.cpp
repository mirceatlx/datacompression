#include "cpress.hpp"

/*
 * Implementation of FileHandle class.
 * */


FileHandle::FileHandle(char* filename) {

  fp = fopen(filename, "r");
  if (!fp) {
    std::cout << "There is no such file in the current folder\n";
     exit(1);
  }

}


int FileHandle::filesize() {

  fseek(fp, 0, SEEK_END);

  int size = ftell(fp);
  rewind(fp);

  return size;
}


void FileHandle::readFile(long long *numbers) {

  /*
   * Counts the number of appearances of every character in the specified file.
   * */

  int fsize = filesize();
  char x; // 1 byte
  fread(&x, 1, 1, fp);
  for (int i = 0; i < fsize; i++) {
    numbers[x]++;
    fread(&x, 1, 1, fp);
  }

  rewind(fp);

}

void FileHandle::writeFile(FILE *fp, FILE *original, std::string file, int pastsize, HuffmanTree t) {
  fp = fopen(&file[0], "w");
  /*
   * Writing byte count of the original file to the compressed file's first 8 bytes.
   * Done to make sure that it can work on little, big and middle-endian systems.
   * */
  long int total_bits = 0;
  unsigned char temp;
  for(int i = 0; i < 8; i++) {
    temp = pastsize % 256;
    fwrite(&temp, 1, 1, fp);
    pastsize /= 256;
  }
  total_bits += 64; 

  fwrite(&t.count, 1, 1, fp); // put the number of symbols in the original file
  total_bits += 8;

  int check_pass = 0;
  fwrite(&check_pass, 1, 1, fp); // if check_pass is 0, the file does not have any password
  total_bits += 8;

  char *ptr;
  unsigned char curr_byte, len, curr_ch;
  int curr_bit_count = 0, bits = 0;
  std::string str_arr[256];
  Node* node_ptr;

  /*
   *  Write the byte and number of bits of representation.
   *  Then writing the transformed version of the symbol rep.
   * */

  std::vector <Node> ::iterator it = t.tree.begin();
  for(node_ptr = &(*it); node_ptr < &(*(it + t.count)); node_ptr++) {
    str_arr[node_ptr->chtr] = node_ptr->bit;
    len = node_ptr->bit.length();
    curr_ch = node_ptr->chtr;
    writeUchar(fp, curr_ch, &curr_byte, curr_bit_count);
    writeUchar(fp, len, &curr_byte, curr_bit_count);

    total_bits += len + 16;

    ptr = &node_ptr->bit[0];
    while(*ptr) {
      if (curr_bit_count == 8) {
        fwrite(&curr_byte, 1, 1, fp);
        curr_bit_count = 0;
      }
      switch(*ptr) {
        case '1': curr_byte <<= 1; curr_byte |= 1; curr_bit_count++; break;
        case '0': curr_byte <<= 1; curr_bit_count++; break;
        default: break;
      }
      ptr++;
      }

    bits += len * node_ptr->prob;
    }

  total_bits += bits;

  if (total_bits % 8 != 0) {
      total_bits = (total_bits / 8 + 1) * 8; // 8 * number of bytes in the compressed file
  }

  /*
   * Translation of the orginial file using the given encoding.
   * */

  unsigned char x;
  fread(&x, 1, 1, original);
  for(int i = 0; i < bits;) {
    ptr = &str_arr[x][0];
    while(*ptr) {
      if (curr_bit_count == 8) {
        fwrite(&curr_byte, 1, 1, fp);
        curr_bit_count = 0;
      }
      switch(*ptr) {
        case '1': i++;curr_byte <<= 1; curr_byte |= 1; curr_bit_count++; break;
        case '0': i++;curr_byte <<= 1; curr_bit_count++; break;
        default: break;
      }
      ptr++;
    }

    fread(&x, 1, 1, original);

  }

  if (curr_bit_count == 8) {
    fwrite(&curr_byte, 1, 1, fp);
    curr_bit_count = 0;
  }
  else {
    curr_byte <<= 8 - curr_bit_count;
    fwrite(&curr_byte, 1, 1, fp);
    curr_bit_count = 0;
  }

  fclose(fp);
  fclose(original);

  std::cout << "Compression is complete.\n";
}


void FileHandle::writeUchar(FILE *fp, unsigned char uchar, unsigned char* curr_byte, int curr_bit_count) {
   (*curr_byte) <<= 8 - curr_bit_count;
   (*curr_byte) |= (uchar >>  curr_bit_count);
   fwrite(curr_byte, 1, 1, fp);
   *curr_byte = uchar;
}




