#include "syscall.h"
#define MAX_FILE_LENGTH 255
int main() {
    int i;
    int n;
    char fileName1[MAX_FILE_LENGTH];        //tên file1
    char fileName2[MAX_FILE_LENGTH];        //tên file2
    char readBuffer[255];                   //buffer ghi dữ liệu
    char readBuffer2[255];                  //buffer ghi dữ liệu
    int readSize;                           //kích thước file nối vào 
    int idSource1;                          //id của file 1 khi mở
    int idSource2;                          //id của file 2 khi mở
    PrintString("NOTE: max file name is 255\n");
    //nhập dữ liệu
    PrintString("input file source 1:  ");
    ReadString(fileName1,MAX_FILE_LENGTH);
    PrintString("input file source 2:  ");
    ReadString(fileName2,MAX_FILE_LENGTH);
    //mở file
    idSource1 = Open(fileName1, 0);
    idSource2 = Open(fileName2, 1);
    if(idSource1 == -1 || idSource2 == -1) {
        Halt();
    }
    //lấy dữ liệu từ file nguồn 2
    readSize = Seek(-1,idSource2);
    Seek(0,idSource2);
    n = readSize / 255;
    //move con trỏ file tới cuối file nguồn 1
    Seek(-1,idSource1);
    for(;i<n;i++){
        Read(readBuffer, 255, idSource2);
        //viết dữ liệu vào file nguồn 1
        Write(readBuffer,255,idSource1);
    }
    
    //đọc phần còn lại trong file nguồn 2
    Read(readBuffer2,255,idSource2);
    //viết dữ liệu vào file nguồn 1
    Write(readBuffer2,readSize - n * 255 ,idSource1);
    
    //đóng file
    Close(idSource1);
    Close(idSource2);
    Halt();
}
