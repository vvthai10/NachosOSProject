#include "syscall.h"

int
main()
{
    char* content = (char*) malloc(4) ;
    content[0] = '\t';
    content[2] = '\n';
    for (int i = 33; i < 127 ; i++){
        PrintNum(i);        
        content[1] = (char) i;    
        PrintString(content);        
    }    
    free(content);
  Halt();  
}