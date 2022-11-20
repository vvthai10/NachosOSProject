#include "syscall.h"
#define MAX_FILE_LENGTH 255
/*
đọc nội dung của file và hiện lên console 

*/
int main() {
    int i = 0;
    int n;


    char fileName[MAX_FILE_LENGTH];     //tên file
    char buffer[255];                   //buffer ghi dữ liệu
    int size;                           //kích thước file cần đọc
    int id;                             //id của file mở 
    char buffer2[255];                  //buffer ghi dữ liệu

    //nhập tên file
    PrintString("NOTE: max file name is 255\n");
    PrintString("input file name: ");
    ReadString(fileName,MAX_FILE_LENGTH);
    //mở file
    id = Open(fileName,1);
    if(id == -1){
        PrintString("file name error\n");
        Halt();
    }
    
    size = Seek(-1,id);
    Seek(0,id);
    n = size / 255;
    for(;i < n;i++) {
        //đọc file
        Read(buffer,255,id);
        //xuất dữ liệu file ra màn hình
        PrintString(buffer);
        
    }
    //đọc phần còn lại trong file
    Read(buffer2,255,id);
    //xuất dữ liệu file ra màn hình
    PrintString(buffer2);
    PrintString("\n");
    Close(id);
    Halt();
}
