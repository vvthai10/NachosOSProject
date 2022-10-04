#include "syscall.h"

#define MAX_LENGTH 100


int main(){

    int n = 0;
    do{
        PrintString("Length of array(It's need smaller 100): ");
        n = ReadNum();
    }
    while(n <= MAX_LENGTH);
    int arr[n];

    for(int i = 0; i < n; i++){
        int temp = 0;
        PrintString("a[");
        PrintNum(i);
        PrintString("] = ");
        temp = ReadNum();
        arr[i] = temp;       
    }

    int case;
    do{
        PrintString("You want sort array to increase(1) or decrease(0): "); 
        case = ReadString();
    }while(case != 0 || case != 1)

    int temp = 0;
    if(case == 1){
        // Sắp xếp tăng dần
        for (int i = 0; i < n - 1; i++){
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    temp = arr[i];
                    arr[i] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    
    }
    else{
        // Sắp xếp giảm dần
        for (int i = 0; i < n - 1; i++){
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] < arr[j + 1])
                {
                    temp = arr[i];
                    arr[i] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    PrintString("Array after sort: ");
    for(int i = 0; i < n; i++){
        PrintNum(arr[i]);
        PrintChar(' ');
    }
    PrintChar('\n');

    Halt();
}