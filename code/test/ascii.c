#include "syscall.h"

int main()
{
  int i;
  char* content = (char*) malloc(4) ;
  content[0] = '\t';
  content[2] = '\n';
  for (i = 33; i < 127 ; i++){
      PrintNum(i);        
      content[1] = (char) i;    
      PrintString(content);        
  }    
  free(content);
  Halt();  
}