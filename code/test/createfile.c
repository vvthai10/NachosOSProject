/* add.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int
main()
{
  //nhập tên file
  char fileName[255];
  PrintString("Input file name (max length is 255): ");
  ReadString(fileName,255);
  //tạo file
  CreateFile(fileName);
  Halt();
  
}
