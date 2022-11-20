<<<<<<< HEAD
/* createfile.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a create file syscall that create file and returns the result.
=======
/* add.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a add syscall that adds two values and returns the result.
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
 *
 */

#include "syscall.h"
<<<<<<< HEAD

=======
#define MAX_FILE_LENGTH 255
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
int
main()
{
  //nhập tên file
<<<<<<< HEAD
  char fileName[255];
  PrintString("Input file name (max length is 255): ");
  ReadString(fileName,255);
  //tạo file
  CreateFile(fileName);
  Halt();
=======
  char fileName[MAX_FILE_LENGTH];
  PrintString("Input file name (max length is 255): ");
  ReadString(fileName,MAX_FILE_LENGTH);
  //tạo file
  CreateFile(fileName);
  Halt();
  
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
}
