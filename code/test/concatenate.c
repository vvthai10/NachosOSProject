#include "syscall.h"
<<<<<<< HEAD

int main() {
    char fileName1[255];
    char fileName2[255];
    char* readBuffer;
=======
#define MAX_FILE_LENGTH 255
int main() {
    char fileName1[MAX_FILE_LENGTH];
    char fileName2[MAX_FILE_LENGTH];
    char readBuffer[MAX_FILE_LENGTH];
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
    int readSize;
    int idSource1;
    int idSource2;
    //nhập dữ liệu
    PrintString("input file source 1 (max length 255): ");
<<<<<<< HEAD
    ReadString(fileName1,255);
    PrintChar("\n");
    PrintString("input file source 2 (max length 255): ");
    ReadString(fileName2,255);
=======
    ReadString(fileName1,MAX_FILE_LENGTH);
    PrintChar("\n");
    PrintString("input file source 2 (max length 255): ");
    ReadString(fileName2,MAX_FILE_LENGTH);
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
    //mở file
    idSource1 = Open(fileName1, 0);
    idSource2 = Open(fileName2, 1);
    if(idSource1 == -1 || idSource2 == -1) {
        Halt();
    }
    //lấy dữ liệu từ file nguồn 2
    readSize = Seek(-1,idSource2);
    Seek(0,idSource2);
<<<<<<< HEAD
    Read(readBuffer, 255, idSource2);
=======
    Read(readBuffer, MAX_FILE_LENGTH, idSource2);
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
    //move con trỏ file tới cuối file nguồn 1
    Seek(-1,idSource1);
    //viết dữ liệu vào file nguồn 1
    Write(readBuffer,readSize,idSource1);
    //đóng file
    Close(idSource1);
    Close(idSource2);
    Halt();
}
