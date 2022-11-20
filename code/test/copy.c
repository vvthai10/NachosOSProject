#include "syscall.h"
#define MAX_FILE_LENGTH 255
/*
copy a.txt b.txt
sẽ copy dữ liệu từ file a.txt vào b.txt
nếu b.txt không tồn tại thì sẽ tạo file b.txt
nếu b.txt có sẵn dữ liệu sẽ nối dữ liệu từ file a.txt vào cuối b.txt
*/
int main() {
    int i = 0;
    int n;

    char fileName1[MAX_FILE_LENGTH];        //tên file 1
    char fileName2[MAX_FILE_LENGTH];        //tên fil2
    char readBuffer[255];                   //buffer ghi dữ liệu
    char readBuffer2[255];                  //buffer ghi dữ liệu
    int readSize;                           //kích thước file đọc
    int idSource1;                          //id của file 1 khi mở
    int idSource2;                          //id của file 2 khi mở

    PrintString("NOTE: max file name is 255\n");
    //nhập tên file
    PrintString("input source file name (max length 255): ");
    ReadString(fileName1,MAX_FILE_LENGTH);

    PrintString("input destination file name (max length 255): ");
    ReadString(fileName2,MAX_FILE_LENGTH);
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
    readSize = Seek(-1,idSource1);
    Seek(0,idSource1);
    n = readSize / 255;

    Seek(-1,idSource2);
    //đọc file source
    for(;i < n;i++){  
        Read(readBuffer,255,idSource1);
        //ghi vào file destination
        Write(readBuffer,255,idSource2);
    }
    //đọc phần còn lại trong file 
    Read(readBuffer2,255,idSource1);
    //ghi vào file destination
    Write(readBuffer2,readSize - n * 255 ,idSource2);

    Close(idSource1);
    Close(idSource2);
    Halt();
}