#include"syscall.h"
int main() {
    int check = CreateFile("index.txt");
    int check1 = CreateFile("tung.txt");
    int check2 = CreateFile("mtp.txt");
    
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

    id = Open(fileName, 0);
    if( id != -1){
        // PrintString("File ");
        // PrintString(fileName);
        // PrintString(" open successful\n");

        // PrintString("\tFile descriptor id: ");
        PrintNum(id);
        // PrintString("\n");

        // Close(id);
    }
    else{
        PrintString("Open file failed\n");
    }
    id = Open(fileName1, 0);
    if( id != -1){
        // PrintString("File ");
        // PrintString(fileName1);
        // PrintString(" open successful\n");

        // PrintString("\tFile descriptor id: ");
        PrintNum(id);
        // PrintString("\n");

        // Close(id);
    }
    else{
        PrintString("Open file failed\n");
    }
    Halt();
}