#include "syscall.h"

#define MAX_LENGTH 100


int main(){

    int n = 0;
    int i, j, choose, temp = 0;
    int arr[MAX_LENGTH + 1];
    do{
        PrintString("Length of array(It's need smaller 100): ");
        n = ReadNum();
    }
    while(n > MAX_LENGTH || n < 0);

    PrintString("N = ");
    PrintNum(n);


    for(i = 0; i < n; i++){
        PrintString("Enter arr[");
        PrintNum(i);
        PrintString("]: ");
        arr[i] = ReadNum();
    }

    do{
        PrintString("You want sort array to increase(1) or decrease(0): "); 
        choose = ReadNum();
    }while(choose != 0 && choose != 1);

    if(choose == 1){
        // Sắp xếp tăng dần
        for (i = 0; i < n - 1; i++){
            for (j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    
    }
    else{
        // Sắp xếp giảm dần
        for (i = 0; i < n - 1; i++){
            for (j = 0; j < n - i - 1; j++)
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
    for(i = 0; i < n; i++){
        PrintNum(arr[i]);
        PrintChar(' ');
    }
    PrintChar('\n');

    Halt();
}