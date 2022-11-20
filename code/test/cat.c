#include "syscall.h"
<<<<<<< HEAD

int main() {

    char fileName[255];
    char* buffer;
=======
#define MAX_FILE_LENGTH 255
/*
đọc nội dung của file và hiện lên console 
tuy nhiên nội dung file không đươc quá 255 kí tự
*/
int main() {

    char fileName[MAX_FILE_LENGTH];
    char buffer[MAX_FILE_LENGTH];
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
    int size;
    int id;
    //nhập tên file
    PrintString("input file name (max length is 255): ");
<<<<<<< HEAD
    ReadString(fileName,255);
=======
    ReadString(fileName,MAX_FILE_LENGTH);
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
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
<<<<<<< HEAD
}
=======
}
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
