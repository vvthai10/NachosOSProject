#include "syscall.h"

int main() {
    char fileName1[255];
    char fileName2[255];
    char* readBuffer;
    int readSize;
    int idSource1;
    int idSource2;
    //nhập dữ liệu
    PrintString("input file source 1 (max length 255): ");
    ReadString(fileName1,255);
    PrintChar("\n");
    PrintString("input file source 2 (max length 255): ");
    ReadString(fileName2,255);
    //mở file
    idSource1 = Open(fileName1, 0);
    idSource2 = Open(fileName2, 1);
    if(idSource1 == -1 || idSource2 == -1) {
        Halt();
    }
    //lấy dữ liệu từ file nguồn 2
    readSize = Seek(-1,idSource2);
    Seek(0,idSource2);
    Read(readBuffer, 255, idSource2);
    //move con trỏ file tới cuối file
    Seek(-1,idSource1);
    //viết dữ liệu vào file nguồn 1
    Write(readBuffer,readSize,idSource1);
    //đóng file
    Close(idSource1);
    Close(idSource2);
    Halt();
}