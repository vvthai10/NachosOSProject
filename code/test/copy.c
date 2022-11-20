#include "syscall.h"
<<<<<<< HEAD
=======
#define MAX_FILE_LENGTH 255
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
/*
copy a.txt b.txt
sẽ copy dữ liệu từ file a.txt vào b.txt
nếu b.txt không tồn tại thì sẽ tạo file b.txt
nếu b.txt có sẵn dữ liệu sẽ nối dữ liệu từ file a.txt vào cuối b.txt
*/
int main() {
<<<<<<< HEAD
    char fileName1[255];
    char fileName2[255];
    char* readBuffer;
=======
    char fileName1[MAX_FILE_LENGTH];
    char fileName2[MAX_FILE_LENGTH];
    char readBuffer[MAX_FILE_LENGTH];
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
    int readSize;

    int idSource1;
    int idSource2;

    //nhập tên file
    PrintString("input source file name (max length 255): ");
<<<<<<< HEAD
    ReadString(fileName1,255);
    PrintChar('\n');
    PrintString("input destination file name (max length 255): ");
    ReadString(fileName2,255);
=======
    ReadString(fileName1,MAX_FILE_LENGTH);
    PrintChar('\n');
    PrintString("input destination file name (max length 255): ");
    ReadString(fileName2,MAX_FILE_LENGTH);
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
    //mở file
    idSource1 = Open(fileName1,1);
    idSource2 = Open(fileName2, 0);
    //kiểm tra file cần copy
    if(idSource1 == -1 ) {
        PrintString("file name error\n");
        Halt();
    }
    //nếu destination file không tồn tại sẽ tạo file mới
    if(idSource2 == -1) {
        CreateFile(fileName2);
        idSource2 = Open(fileName2,0);

    }
    //đọc file source
    readSize = Seek(-1,idSource1);
    Seek(0,idSource1);
    Read(readBuffer,readSize,idSource1);

    //ghi vào file destination
    Seek(-1,idSource2);
    Write(readBuffer,readSize,idSource2);
    Close(idSource1);
    Close(idSource2);
    Halt();
}