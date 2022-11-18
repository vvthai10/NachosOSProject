/* add.c
 *	Simple program to test whether the systemcall interface works.
 *	
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int
main()
{
  int result = 456;
  
  // result = Add(42, 23);
<<<<<<< HEAD
  // result = ReadNum();
  PrintNum(result);

=======
  result = ReadChar();
  PrintChar(result);
>>>>>>> origin/main
  // Always use halt() because don't create sysExit
  Halt();
}
