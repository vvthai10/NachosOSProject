#include "syscall.h"
#define MAX_FILE_LENGTH 255
int
main()
{
  //nhập tên file
  char fileName[MAX_FILE_LENGTH];
  PrintString("Input file name (max length is 255): ");
  ReadString(fileName,MAX_FILE_LENGTH);
  //tạo file
  CreateFile(fileName);
  Halt();
  
}
