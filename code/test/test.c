#include"syscall.h"
int main() {
    int check = CreateFile("index.txt");
    char fileName[] = "index.txt";
    int i;
    int id;

    for(i = 0; i < 20; i++){
        id = Open(fileName, 0);
        if( id != -1){
            PrintString("File ");
            PrintString(fileName);
            PrintString(" open successful\n");
            PrintString("File descriptor id: ");
            PrintNum(id);
            PrintString("\n");
            PrintString("current positon is: ");
            PrintNum(Seek(-1,id));
            PrintString("\n");
            Close(id);
        }
        else{
            PrintString("Open file failed\n");
        }
    }

    
    Remove("index.txt");
    Halt();
}