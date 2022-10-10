/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 
#define __STDC_LIMIT_MACROS

#include "kernel.h"
#include "synchconsole.h"
#include <stdint.h>

#define LF ((char)10)
#define CR ((char)13)
#define TAB ((char)9)
#define SPACE ((char)' ')

#define MAX_LENGTH 10
bool isBlank(char c) { return c == LF || c == CR || c == TAB || c == SPACE; }
// Kiểm tra nếu


void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

int SysReadNum()
{
  // Bước 1: Đọc các kí tự vào trong bàn phím
  char numberInput[MAX_LENGTH];

  int n = 0;
  bool isNegative = false;
  char c = kernel->synchConsoleIn->GetChar();

  // Khi nhận kí tự enter thì kết thúc việc nhập, 
  // tuy nhiên nếu người dùng vẫn cố nhập thì sẽ ghi lại vào vị trí 0 của mảng,
  // đợi khi người dùng kết thúc nhập thì kiểm tra n với MAX_LENGTH thì sẽ trả lại 0.
  while (c != (char)10)
  {
    if(c == (char)'-' && n == 0){
      isNegative = true;
    }
    else if(n < MAX_LENGTH){
      numberInput[n++] = c;
    }
    // Khi số lượng kí tự vượt quá cũng đáng dấu -> trả về 0
    else
    {
      DEBUG(dbgSys, "Number is too long.\n");
      numberInput[0] = c;
    }
    c = kernel->synchConsoleIn->GetChar();
  }

  if(n > MAX_LENGTH){
    DEBUG(dbgSys, "Value return is zero\n");
    return 0;
  }

  // Bước 2:Xử lý các trường hợp sẽ gặp phải

  // Trường hợp độ dài chuỗi là rỗng.
  int length = n;
  if (length == 0)
  {
    DEBUG(dbgSys, "Value of integer is zero\n");
    return 0;
  }

  // Trường hợp chuỗi nhập vào không phải là số nguyên
  bool isInteger = true;

  for (int i = 0; i < length; i++)
  {
    c = numberInput[i];
    
    if (!(c >= (char)'0') && (c <= (char)'9'))
    {
      isInteger = false;
      break;
    }
  }
  if (!isInteger)
  {
    DEBUG(dbgSys, "Value of input not a integer \n");
    return 0;
  }

  // Kiểm tra các trường hợp số nhập vào tại các vị trí cực trị của khoảng giá trị INT
  int num = 0;
  for(int i = 0; i < length; i++){

    int temp = (numberInput[i] - '0');
    if(isNegative){
      DEBUG(dbgSys, "calc -");
      if(num == 214748364 && temp == 8){
        
        DEBUG(dbgSys, "Value is equal INT_MIN: " << INT32_MIN << "\n");
        return INT32_MIN;
      }
      else if((num == 214748364 && temp > 8) || num > 214748364){
        DEBUG(dbgSys, "Value is out range of INT: " << 0 << "\n");
        return 0;
      }
    }
    else{
      if(num == 214748364 && temp == 7){
        DEBUG(dbgSys, "Value is equal INT_MAX: " << INT32_MAX << "\n");
        return INT32_MAX;
      }
      else if((num == 214748364 && temp > 7) || num > 214748364){
        DEBUG(dbgSys, "Value is out range of INT: " << 0 << "\n");
        return 0;
      }
    }

    num = num * 10 + temp;
  }

  num = (isNegative) ? -num : num;
  DEBUG(dbgSys, "Final result: " << num << "\n");

  return num;
}

void SysPrintNum(int number) {
    // Check có bằng 0
    if(number == 0){
      DEBUG(dbgSys, "Number is zero.\n");
      kernel->synchConsoleOut->PutChar('0');
      return;
    }

    // Cần kiểm tra có bằng min hay không
    // bởi vì cần chuyển số âm thành số nguyên rồi mới gán lại vào mảng char
    // thì khi đổi thành số dương thì chỉ tối đa là 2147483647
    // dẫn tới việc tràn số.
    if (number == INT32_MIN) {
        kernel->synchConsoleOut->PutChar('-');
        char intMin[11] = "2147483648";
        for (int i = 0; i < 11; ++i)
            kernel->synchConsoleOut->PutChar(intMin[i]);
        return;
    }

    // Kiểm tra số âm
    if (number < 0) {
        kernel->synchConsoleOut->PutChar('-');
        number = -number;
    }

    // Tiến hành in kết quả.
    int n = 0;
    char numberPrint[MAX_LENGTH];
    while (number) {
        numberPrint[n++] = number % 10;
        number /= 10;
    }
    for (int i = n - 1; i >= 0; --i){
        kernel->synchConsoleOut->PutChar(numberPrint[i] + '0');
    }
}

char SysReadChar() {
  char c;
  c = kernel->synchConsoleIn->GetChar();
  return c;
}

void SysPrintChar(char c) {
  //xuất kí tự c ra màn hình
  kernel->synchConsoleOut->PutChar(c);
}

void SysReadString(char* string, int len) {

  char c;
  int i;
  i=0;

  //đọc tới len kí tự hoặc tới khi kết thúc chuỗi nhập
  for(;i < len; i++){
    c = SysReadChar();
    //khi người dung nhấn enter thì sẽ dừng đọc
    if(c==LF) break;
    string[i] = c;
  }
  
  //gán kí tự '\0' vào cuối chuỗi nhập
  string[i] = '\0';

  return;
}

void SysPrintString(char* string){
  int len;
  len = 0;
  //nếu chuỗi rỗng thì dừng 
  if(!string) return;
  //xuất ra màn hình tới khi nào gặp kí tự '\0' thì dừng
  while (string[len] != '\0')
  {
    SysPrintChar(string[len]);
    len++;
  }
  //in kí tự '\0' 
  SysPrintChar(string[len]);
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
