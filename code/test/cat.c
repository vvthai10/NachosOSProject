#include "syscall.h"
#define MAX_FILE_LENGTH 255
/*
đọc nội dung của file và hiện lên console 
tuy nhiên nội dung file không đươc quá 255 kí tự
*/
int main() {

    char fileName[MAX_FILE_LENGTH];
    char buffer[MAX_FILE_LENGTH];
    int size;
    int id;
    //nhập tên file
    PrintString("input file name (max length is 255): ");
    ReadString(fileName,MAX_FILE_LENGTH);
    //mở file
    id = Open(fileName,1);
    if(id == -1){
        PrintString("file name error\n");
        Halt();
    }
    //đọc file
    size = Seek(-1,id);
    Seek(0,id);
    Read(buffer,size,id);
    //xuất dữ liệu file ra màn hình
    PrintString(buffer);
    Close(id);
    Halt();
}
