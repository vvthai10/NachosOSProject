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

#define MAX_LENGTH 11
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
  char numberInput[MAX_LENGTH + 2];

  int n = 0;
  char c = kernel->synchConsoleIn->GetChar();

  // Khi nhận kí tự enter thì kết thúc việc nhập, 
  // tuy nhiên nếu người dùng vẫn cố nhập thì sẽ ghi lại vào vị trí 0 của mảng,
  // đợi khi người dùng kết thúc nhập thì kiểm tra n với MAX_LENGTH thì sẽ trả lại 0.
  while (c != (char)10)
  {
    numberInput[n++] = c;
    if (n > MAX_LENGTH)
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
    if (i == 0 && c == (char)'-')
    {
      isInteger = true;
    }
    else if (!CheckInput(c))
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

  // Trường hợp nó vượt quá ngưỡng của phạm vi integer
  //-2147483648 to 2147483647
  // Đang gặp lỗi nhập trùng vào 2 khoảng thì đúng hàm strcmp = 0 nhưng lại trả là 1
  if (numberInput[0] == (char)'-')
  {
    DEBUG(dbgSys, "Compare with -2147483648: " << strcmp(numberInput, "-2147483648") << "\n");
  }
  else
  {
    DEBUG(dbgSys, "Compare with 2147483647: "<< strcmp("2147483647", "2147483647") << "\n");
    DEBUG(dbgSys, "Compare with 2147483647: "<< strcmp(numberInput, "2147483647") << "\n");
  }

  return 0;
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
