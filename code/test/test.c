#include"syscall.h"
int main() {
    // int check = CreateFile("index.txt");
    // char fileName[] = "index.txt";
    // int i;
    // int id;

    // for(i = 0; i < 20; i++){
    //     id = Open(fileName, 0);
    //     if( id != -1){
    //         PrintString("File ");
    //         PrintString(fileName);
    //         PrintString(" open successful\n");

    //         PrintString("File descriptor id: ");
    //         PrintNum(id);
    //         PrintString("\n");

    //         // Close(id);
    //     }
    //     else{
    //         PrintString("Open file failed\n");
    //     }
    // }
    // Remove("index.txt");
    // Halt();


    // ------------ TEST READ ---------
    char buffer[100];
    int i;
    int write;

    int fileid = Open("index.txt", 1);
    int read = Read(buffer, 10, fileid);
    int len = 0;
    while (buffer[len] != '\0') ++len;
    PrintString("Value return: ");
    PrintNum(read);
    PrintString("\nRead ");
    PrintNum(len);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);
    // ------------ TEST READ ---------

    // ------------ TEST WRITE ---------
    fileid = Open("sontung.txt", 0);
    write = Write(buffer, len, fileid);

    PrintString("Write ");
    PrintNum(write);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    Close(fileid);
    // ------------ TEST WRITE ---------


    // ------------ TEST READ ---------
    fileid = Open("index.txt", 0);
    read = Read(buffer, 50, fileid);
    len = 0;
    while (buffer[len] != '\0') ++len;

    PrintString("Value return: ");
    PrintNum(read);
    PrintString("\nRead ");
    PrintNum(len);
    PrintString(" characters: ");
    PrintString(buffer);
    PrintString("\n");
    // ------------ TEST READ ---------


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
    Read(buffer, 15, 0);
    len = 0;
    while (buffer[len] != '\0') ++len;
    PrintString("\nSize len: ");
    PrintNum(len);
    Write(buffer, len, 1);
   //  PrintNum(Write(buffer, len, 1));

    Halt();
}

// #include"syscall.h"

// int main()  
// {
//    char name1[255];
//    char name2[255];
//    ReadString(name1, 255);
//    ReadString(name2, 255);

//    PrintString(name1);
//    PrintString("\n");
//    PrintString(name2);
// //    PrintString(name2);
//    Halt();
// }