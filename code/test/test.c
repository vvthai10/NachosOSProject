#include"syscall.h"
int main() {
    // int check = CreateFile("index.txt");
    // int check1 = CreateFile("tung.txt");
    // int check2 = CreateFile("mtp.txt");
    
    char fileName[] = "mtp.txt";
    char fileName1[] = "tung.txt";
    // int i;
    int id;

    // for(i = 0; i < 20; i++){
    //     id = Open(fileName, 0);
    //     if( id != -1){
    //         PrintString("File ");
    //         PrintString(fileName);
    //         PrintString(" open successful\n");

    //         PrintString("\tFile descriptor id: ");
    //         PrintNum(id);
    //         PrintString("\n");

    //         Close(id);
    //     }
    //     else{
    //         PrintString("Open file failed\n");
    //     }
    // }

    // id = Open("mtp.txt", 0);
    // if( id != -1){
    //     PrintString("File ");
    //     PrintString(fileName);
    //     PrintString(" open successful\n");

    //     PrintString("\tFile descriptor id: ");
    //     PrintNum(id);
    //     PrintString("\n");

    //     Close(id);
    // }
    // else{
    //     PrintString("Open file failed\n");
    // }

    // id = Open(fileName, 0);
    // if( id != -1){
    //     // PrintString("File ");
    //     // PrintString(fileName);
    //     // PrintString(" open successful\n");

    //     // PrintString("\tFile descriptor id: ");
    //     PrintNum(id);
    //     // PrintString("\n");

    //     // Close(id);
    // }
    // else{
    //     PrintString("Open file failed\n");
    // }
    // id = Open(fileName1, 0);
    // if( id != -1){
    //     // PrintString("File ");
    //     // PrintString(fileName1);
    //     // PrintString(" open successful\n");

    //     // PrintString("\tFile descriptor id: ");
    //     PrintNum(id);
    //     // PrintString("\n");

    //     // Close(id);
    // }
    // else{
    //     PrintString("Open file failed\n");
    // }

    char buffer[100];
    int i;
    int write;

    int fileid = Open("index.txt", 1);
    int read = Read(buffer, 50, fileid);
    int len = 0;
    while (buffer[len] != '\0') ++len;
    PrintString("Read ");
    PrintNum(len);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);

    fileid = Open("mtp.txt", 0);
    write = Write(buffer, len, fileid);

    PrintString("Write ");
    PrintNum(write);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);

    fileid = Open("tung.txt", 0);
    read = Read(buffer, 50, fileid);
    len = 0;
    while (buffer[len] != '\0') ++len;

    PrintString("Read ");
    PrintNum(len);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    // Write to the same file
    write = Write(buffer, len, fileid);
    PrintString("Write ");
    PrintNum(write);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);

    for (i = 0; i < len; ++i) {
        buffer[i] = 0;
    }
    Read(buffer, 50, 0);
    len = 0;
    while (buffer[len] != '\0') ++len;
    PrintNum(Write(buffer, len, 1));

    Halt();
}