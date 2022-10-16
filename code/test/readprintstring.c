#include "syscall.h"
int main(){
    char* string;
    int len;
    len = 255;
    ReadString(string,255);
    PrintString(string);

    Halt();
    return;
}