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
