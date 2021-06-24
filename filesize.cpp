#include <fstream>
#include <iostream>
#include <cstdio>
using namespace std;

/*
 *
 * Temporarly the program can only tell the size of a single file.
 *
 * */

int main(int argc, char* argv[]) {

  if (argc == 1) {
    
    /*
     *  stderr
     * */
    cerr << "An error has occured. There is no file to verify.\n";
    exit(1);
  }
  int i = 1;
  while (i < argc) {
    FILE *fp = fopen(&argv[i][0], "rb");
    if (!fp) {

      cout << "There is no such file in the current folder\n";
      exit(1);
    }

    /*
     *  Sets the position indicator associated with the stream to a new position.
     *  int fseek ( FILE * stream, long int offset, int origin );
     * */

    fseek(fp, 0, SEEK_END);


    /*
     *  Returns the current value of the position indicator of the stream.
     *  For binary streams, this is the number of bytes from the beginning of the file.
     *  long int ftell ( FILE * stream );
     * */
    int filesize = ftell(fp);

    cout << "File " << argv[i] << " has " << filesize << " bytes\n";


    /*
     * Moves the file position indicator to the beginning of the given file stream.
     * void rewind( FILE *stream );
     * */
    rewind(fp);


    /*
     *  Closes the file associated with the stream and disassociates it.
     *  int fclose ( FILE * stream );
     *  Even if the call fails, the stream passed as parameter will no longer be associated with the file nor its buffers.
     * */
    fclose(fp);

    i++;
  }
  return 0;
}



