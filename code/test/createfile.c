#include "syscall.h"
#define MAX_FILE_LENGTH 255
int
main()
{
  //nhập tên file
  char fileName[MAX_FILE_LENGTH];
  PrintString("NOTE: max file name is 255\n");
  PrintString("Input file name  ");
  ReadString(fileName,MAX_FILE_LENGTH);
  //tạo file
  CreateFile(fileName);
  Halt();
  
}
