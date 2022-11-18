#include"syscall.h"

int main() {
    int id;
    PrintString("Hello\n");
    id = Open("test.txt",0);
    if( id != -1){
            PrintString("File ");
            PrintString("test.txt");
            PrintString(" open successful\n");

            PrintString("File descriptor id: ");
            PrintNum(id);
            PrintString("\n");
            PrintString("current positon is: ");
            PrintNum(Seek(-1,id));
            PrintString("\n");
            Remove("test.txt");
            Close(id);
        }
}
