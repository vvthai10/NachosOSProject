#include"syscall.h"
int main() {
<<<<<<< HEAD
    // int check = CreateFile("index.txt");
    char fileName[] = "index.txt";
    int i;
=======
    int check = CreateFile("index.txt");
    int check1 = CreateFile("tung.txt");
    int check2 = CreateFile("mtp.txt");
    
    char fileName[] = "mtp.txt";
    char fileName1[] = "tung.txt";
    // int i;
>>>>>>> 674904582b932696e88aaa777420d8ab02f627d4
    int id;

    // for(i = 0; i < 20; i++){
    //     id = Open(fileName, 0);
    //     if( id != -1){
    //         PrintString("File ");
    //         PrintString(fileName);
    //         PrintString(" open successful\n");
<<<<<<< HEAD

    //         PrintString("File descriptor id: ");
    //         PrintNum(id);
    //         PrintString("\n");
    //         PrintString("current positon is: ");
    //         PrintNum(Seek(-1,id));
    //         PrintString("\n");
    //         Close(id);
    //     }
    //     else{
    //         PrintString("Open file failed\n");
    //     }
    // }
    Remove("index.txt");
=======

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
>>>>>>> 674904582b932696e88aaa777420d8ab02f627d4
    Halt();
}