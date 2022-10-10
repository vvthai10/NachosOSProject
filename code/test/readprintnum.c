/* add.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int main()
{
  PrintNum(ReadNum());    
  // Always use halt() because don't create sysExit
  Halt();
}
