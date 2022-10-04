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


#include "kernel.h"
#include "synchconsole.h"
#include "stdlib.h"

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
  // int num = 0;
  bool isNegative = false;
  char c = kernel->synchConsoleIn->GetChar();

  // Khi nhận kí tự enter thì kết thúc việc nhập
  while (c != (char)10)
  {
    if(c == (char)'-' && n == 0){
      isNegative = true;
    }
    else{
      numberInput[n++] = c;
    }
    if (n > MAX_LENGTH)
    {
      DEBUG(dbgSys, "Number is too long");
      break;
    }
    c = kernel->synchConsoleIn->GetChar();
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

  // Trường hợp check ngoài giới hạn int sẽ gán sau
  // Trường hợp nhập vào là 0000006
  DEBUG(dbgSys, "Length: " << length << "\n");
  if (length == 10){
    char valueCheck[11];
    strncpy(valueCheck, numberInput, 10);
    valueCheck[10] = '\0';
    DEBUG(dbgSys, "Value need check: " << valueCheck << "\n");
    if(isNegative)
    {
      // bool isSmallerMin = false;
      
      DEBUG(dbgSys, "Compare with -2147483648: " << strcmp(numberInput, "-2147483648") << "\n");
    }
    else
    {  
      // bool isLargerMax = false;
      DEBUG(dbgSys, "Compare with 2147483647: "<< strcmp("2147483647", "2147483647") << "\n");
      DEBUG(dbgSys, "Compare with 2147483647: "<< strcmp(numberInput, "2147483647") << "\n");
    }
  }

  int num = 0;
  for(int i = 0; i < length; i++){

    num = num * 10 + (numberInput[i] - '0');
    DEBUG(dbgSys, "Result: " << num << "\n");

  }

  DEBUG(dbgSys, "Result: " << num << "\n");

  return num;
}

void SysPrintNum(int number) {
    // Check có bằng 0
    if(number == 0){
      DEBUG(dbgSys, "Number is zero.\n");
      kernel->synchConsoleOut->PutChar('0');
      return;
    }

    // if (num == INT32_MIN) {
    //     kernel->synchConsoleOut->PutChar('-');
    //     for (int i = 0; i < 10; ++i)
    //         kernel->synchConsoleOut->PutChar("2147483648"[i]);
    //     return;
    // }

    if (number < 0) {
        kernel->synchConsoleOut->PutChar('-');
        number = -number;
    }
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
  kernel->synchConsoleOut->PutChar(c);
}

void SysReadString(char* string, int len) {

  char c;
  int i;
  i=0;


  for(;i < len; i++){
    c = SysReadChar();
    if(c==LF) break;
    string[i] = c;
  }
  
    
  string[i] = '\0';

  return;
}

void SysPrintString(char* string){
  int len;
  len = 0;
  if(!string) return;
  while (string[len] != '\0')
  {
    SysPrintChar(string[len]);
    len++;
  }
  SysPrintChar(string[len]);
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
