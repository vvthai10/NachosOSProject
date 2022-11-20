#include "syscall.h"
#define MAX_FILE_LENGTH 255
int main() {
    //nhập tên file
    char fileName[MAX_FILE_LENGTH];
    int id;
    PrintString("NOTE: max file name is 255\n");
    PrintString("delete file name: ");
    ReadString(fileName,MAX_FILE_LENGTH);
    //xóa file
    Remove(fileName);

    Halt();
}