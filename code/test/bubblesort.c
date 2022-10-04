#include "syscall.h"

#define MAX_LENGTH 100


int main(){


    // int n, a[SIZE + 1], order, temp, i, j;
    // do {
    //     PrintString("Enter n (0 <= n <= 100): ");
    //     n = ReadNum();
    //     if (n < 0 || n > 100)
    //         PrintString(
    //             "n has to be an integer between 1 and 100 (inclusive), please "
    //             "try again\n");
    // } while (n < 0 || n > 100);

    // for (i = 0; i < n; i++) {
    //     PrintString("Enter a[");
    //     PrintNum(i);
    //     PrintString("]: ");
    //     a[i] = ReadNum();
    // }

    int n = 0;
    int i, j, choose, temp = 0;
    int arr[MAX_LENGTH + 1];
    do{
        PrintString("Length of array(It's need smaller 100): ");
        n = ReadNum();
    }
    while(n > MAX_LENGTH || n < 0);

    for(i = 0; i < n; i++){
        PrintString("Enter arr[");
        PrintNum(i);
        PrintString("]: ");
        arr[i] = ReadNum();
    }

    do{
        PrintString("You want sort array to increase(1) or decrease(0): "); 
        choose = ReadNum();
    }while(choose != 0 || choose != 1);

    if(choose == 1){
        // Sắp xếp tăng dần
        for (i = 0; i < n - 1; i++){
            for (j = 0; j < n - i - 1; j++)
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