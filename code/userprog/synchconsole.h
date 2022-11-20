// synchconsole.h 
//	Data structures for synchronized access to the keyboard
//	and console display devices.
//
//	NOTE: this abstraction is not completely implemented.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef SYNCHCONSOLE_H
#define SYNCHCONSOLE_H

#include "copyright.h"
#include "utility.h"
#include "callback.h"
#include "console.h"
#include "synch.h"

// The following two classes define synchronized input and output to
// a console device

class SynchConsoleInput : public CallBackObj {
  public:
    SynchConsoleInput(char *inputFile); // Initialize the console device
    ~SynchConsoleInput();		// Deallocate console device

    char GetChar();		// Read a character, waiting if necessary
    int GetString(char* buffer, int size){
      char temp = GetChar();
      int i = 0;
      while(temp != (char)10){
        if(i < size){
          buffer[i] = temp;
        }
        i++;
        temp = GetChar();
      }
<<<<<<< HEAD
      return size;
=======
      // int i = 0;
      // do{
      //   temp = GetChar();
      //   if(i < size && temp != (char)10){
      //     buffer[i] = temp;
      //   }
      //   i++;
      // }while(temp != (char)10);

      // for(int i = 0; i < size; i++){
      //   buffer[i] = GetChar();
      //   if(buffer[i] == (char)10){
      //     buffer[i] = 0;
      //     return -2;
      //   }
      // }
      return i;
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
    }	
    
  private:
    ConsoleInput *consoleInput;	// the hardware keyboard
    Lock *lock;			// only one reader at a time
    Semaphore *waitFor;		// wait for callBack

    void CallBack();		// called when a keystroke is available
};

class SynchConsoleOutput : public CallBackObj {
  public:
    SynchConsoleOutput(char *outputFile); // Initialize the console device
    ~SynchConsoleOutput();

    void PutChar(char ch);	// Write a character, waiting if necessary
    int PutString(char* buffer, int size){
      for(int i = 0; i < size; i++){
        PutChar(buffer[i]);
      }
      return size;
    }
    
  private:
    ConsoleOutput *consoleOutput;// the hardware display
    Lock *lock;			// only one writer at a time
    Semaphore *waitFor;		// wait for callBack

    void CallBack();		// called when more data can be written
};

#endif // SYNCHCONSOLE_H
