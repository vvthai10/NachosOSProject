#include "syscall.h"
int main(){
    char* string;
    int len;
    len = 5;
    ReadString(string,len);
    PrintString(string);

    Halt();
    return;
}