// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
#define INT_MIN -2147483657
#define INT_MAX 2147483657
#define LF ((char)10)
#define CR ((char)13)
#define TAB ((char)9)
#define SPACE ((char)' ')
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------


//tăng giá trị thành ghi PC
void increasePC()
{
	/* set previous programm counter (debugging only)*/
	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	/* set next programm counter for brach execution */
	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}
//copy chuỗi thuộc địa chỉ virtAddr của userspace sang kernelspace
char *User2System(int virtAddr, int limit)
{
	int i; // index
	int oneChar;
	char *kernelBuf = NULL;
	kernelBuf = new char[limit + 1]; // need for terminal string
	if (kernelBuf == NULL)
		return kernelBuf;
	memset(kernelBuf, 0, limit + 1);
	// printf("\n Filename u2s:");
	for (i = 0; i < limit; i++)
	{
		kernel->machine->ReadMem(virtAddr + i, 1, &oneChar);
		kernelBuf[i] = (char)oneChar;
		// printf("%c",kernelBuf[i]);
		if (oneChar == 0)
			break;
	}
	return kernelBuf;
}
//Copy chuỗi từ System space sang User space
int System2User(int virtAddr, int len, char *buffer)
{
	if (len < 0)
		return -1;
	if (len == 0)
		return len;
	int i = 0;
	int oneChar = 0;
	do
	{
		oneChar = (int)buffer[i];
		kernel->machine->WriteMem(virtAddr + i, 1, oneChar);
		i++;
	} while (i < len && oneChar != 0);
	return i;
}

void HandleSyscallReadNum(){
	int result = SysReadNum();
	kernel->machine->WriteRegister(2, result);
	return;
}

void HandleSyscallPrintNum(){
	int numberPrint = kernel->machine->ReadRegister(4);
    SysPrintNum(numberPrint);
	return;
}

void HandleSyscallReadChar(){
	char character;
	// đọc một kí tự do người dùng nhập vào;
	//nếu người dùng nhập vào hơn 1 kí tự thì sẽ đọc kí tự đầu tiên
	character = SysReadChar();
	kernel->machine->WriteRegister(2, character);
	return;
}

void HandleSyscallPrintChar(){
	char inputCh;
	//đọc kí tự do người dùng truyền vào
	inputCh = kernel->machine->ReadRegister(4);
	//xuất ra màn hình
	SysPrintChar(inputCh);
	return;
}
void HandleSyscallRandomNum(){
	int ranNum;
	//lấy một số ngẫu nhiên 
	srand((int)time(NULL));
	ranNum =  rand();
	//trả kết quả về
	kernel->machine->WriteRegister(2, ranNum);
	return;
}

void HandleSyscallReadString(){
	int virtAddr;	//địa chỉ vùng nhớ thuộc quyền user sẽ lưu chuỗi nhập vào
	int len;	//chiều dài cần đọc 
	virtAddr = kernel->machine->ReadRegister(4);
	len = kernel->machine->ReadRegister(5);
	DEBUG(dbgSys,"Do dai chuoi muon doc la: " << len << "\n");
	DEBUG(dbgSys,"Dia chi vung chua chuoi la: " << virtAddr << "\n");
	
	char* buffer;
	buffer = new char[len+1];
	//đọc chuỗi do người dùng nhập vào
	//chuỗi sẻ lưu vào vùng nhớ do hệ điều hành quản lý (kernel space)
	SysReadString(buffer,len);
	DEBUG(dbgSys,"Chuoi nhap vao la: " << buffer);
	//trả chuỗi về vùng nhớ mà người dùng có thể truy cập (user space)
	System2User(virtAddr,len,buffer);
	delete[] buffer;
	return;
}

void HandleSyscallPrintString(){
	int virtAddr = kernel->machine->ReadRegister(4);
	//chuyển chuỗi xuông vùng kernel space để HĐH xử lý
	char* inputString ;
	//chỉ đọc chuỗi tối đa 255 kí tự
	inputString = User2System(virtAddr,255);
	DEBUG(dbgSys,"Chuoi xuat ra man hinh la: " << inputString << "\n");
	//xuất ra màn hình
	SysPrintString(inputString);
	return;
}

void HandleSyscallCreateFile(){
	int virtAddr = kernel->machine->ReadRegister(4); 
	// NOTE: Do dai toi da cho file name la 32
	char* fileName = User2System(virtAddr,255);

	if(strlen(fileName) == 0){
		printf("File name empty.\n");
		kernel->machine->WriteRegister(2, -1);
	}
	else if(fileName == NULL){
		printf("File name is more long.\n");
		kernel->machine->WriteRegister(2, -1);
	}
	else{
		if(!kernel->fileSystem->Create(fileName)){
			printf("File is not create.\n");
			kernel->machine->WriteRegister(2, -1);
		}
		else{
			printf("Create file successful.\n");
			kernel->machine->WriteRegister(2, 0);
		}
	}

	delete[] fileName;
}

void HandleSyscallOpenFile(){
	DEBUG(dbgSys, "Start open file.\n");
	int virtAddr = kernel->machine->ReadRegister(4);
	int type = kernel->machine->ReadRegister(5);

	char* fileName = User2System(virtAddr, 255);
	DEBUG(dbgSys, "\tFile name: " << fileName << "\n");

	if(type != 0 && type != 1){
		DEBUG(dbgSys, "\tType is incorrect. Not open file.\n");
		kernel->machine->WriteRegister(2, -1);
		delete fileName;
		return;
	}
	int id = kernel->fileSystem->Open(fileName, type);
	if(id == -1){
		DEBUG(dbgSys, "\tNot open file, some error: full table, name don't exist,...\n");
		kernel->machine->WriteRegister(2, -1);
		delete fileName;
		return;
	}
	DEBUG(dbgSys, "\tOpen file '" << fileName << "' successful\n");
	
	kernel->machine->WriteRegister(2, id);
	delete fileName;
}

void HandleSyscallCloseFile(){
	DEBUG(dbgSys, "Start close file.\n");
	int fileDescriptor = kernel->machine->ReadRegister(4);
	DEBUG(dbgSys, "\tFile descriptor id: " << fileDescriptor << "\n");
	int check = kernel->fileSystem->Close(fileDescriptor);

	DEBUG(dbgSys,"\tCheck process: " << check);
	kernel->machine->WriteRegister(2, check);
	return;
}

void HandleSyscallSeek() {
	int pos = kernel->machine->ReadRegister(4);
	int fileId =kernel->machine->ReadRegister(5);

	kernel->machine->WriteRegister(2, SysSeek(pos,fileId));
	
	return;
}

void HandleSyscallRemove() {
	int virAddr = kernel->machine->ReadRegister(4);
	char* fileName = User2System(virAddr,255);
	if(strlen(fileName) == 0){
		printf("File name empty.\n");
		kernel->machine->WriteRegister(2, -1);
		return;
	}
	else if(fileName == NULL){
		printf("File name is more long.\n");
		kernel->machine->WriteRegister(2, -1);
		return;
	}

	if(kernel->fileSystem->IsFileOpen(fileName) == 1) {
		printf("File is open \n");
		kernel->machine->WriteRegister(2, -1);
		delete[] fileName;
		return;
	}
	if(!kernel->fileSystem->Remove(fileName)){
		printf("file doesn't exist\n");
		kernel->machine->WriteRegister(2, -1);
	}else {
		printf("remove success");
		kernel->machine->WriteRegister(2, 0);
	}
	delete[] fileName;
	return;
}

void HandleSyscallReadFile() {
	int virtAddr = kernel->machine->ReadRegister(4);
	int size = kernel->machine->ReadRegister(5);
	int id = kernel->machine->ReadRegister(6);

	char* buffer = User2System(virtAddr, size);

	DEBUG(dbgSys, "Read file has id: " << id << "\n");
	int check;

	// Doc tu stdin
	if(id == 0){
		check = kernel->synchConsoleIn->GetString(buffer, size);
	}

	// Doc tu file
	check = kernel->fileSystem->Read(buffer, size, id);

	kernel->machine->WriteRegister(2, check);
	System2User(virtAddr, size, buffer);

	delete[] buffer;
}

void HandleSyscallWriteFile() {
	int virtAddr = kernel->machine->ReadRegister(4);
	int size = kernel->machine->ReadRegister(5);
	int id = kernel->machine->ReadRegister(6);

	char* buffer = User2System(virtAddr, 255);

	DEBUG(dbgSys, "Write file have id: " << id << "\n");
	int check;
	// Doc tu stdin
	if(id == 1){
		check = kernel->synchConsoleOut->PutString(buffer, size);
	}

	check = kernel->fileSystem->Write(buffer, size, id);
	DEBUG(dbgSys, "Res return when run write: " << check << "\n");
	kernel->machine->WriteRegister(2, check);
	System2User(virtAddr, size, buffer);

	delete[] buffer;
}

void ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

	switch (which)
	{
	case SyscallException:
		switch (type)
		{
		case SC_Halt:
			DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

			SysHalt();

			ASSERTNOTREACHED();
			break;

		case SC_Add:
			DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

			/* Process SysAdd Systemcall*/
			int res;
			res = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
							/* int op2 */ (int)kernel->machine->ReadRegister(5));

			DEBUG(dbgSys, "Add returning with " << res << "\n");
			/* Prepare Result */
			kernel->machine->WriteRegister(2, (int)res);
			/* Modify return point */

			increasePC();
			return;
			ASSERTNOTREACHED();
		case SC_ReadNum:
			HandleSyscallReadNum();
			increasePC();
			return;
		case SC_PrintNum:
			HandleSyscallPrintNum();
			increasePC();
			return;
		case SC_ReadChar:
			HandleSyscallReadChar();
			increasePC();
			return;
		case SC_PrintChar:
			HandleSyscallPrintChar();
			increasePC();
			return;
		case SC_RandomNum:
			HandleSyscallRandomNum();
			increasePC();
			return;
		case SC_ReadString:
			HandleSyscallReadString();
			increasePC();
			return;
		case SC_PrintString:
			HandleSyscallPrintString();
			increasePC();
			return;
		case SC_CreateFile:
			HandleSyscallCreateFile();
			increasePC();
			return;
		case SC_Open:
			HandleSyscallOpenFile();
			increasePC();
			return;
		case SC_Close:
			HandleSyscallCloseFile();
			increasePC();
			return;
		case SC_Read:
			HandleSyscallReadFile();
			increasePC();
			return;
		case SC_Write:
			HandleSyscallWriteFile();
			increasePC();
			return;
		case SC_Seek:
			HandleSyscallSeek();
			increasePC();
			return;
		case SC_Remove:
			HandleSyscallRemove();
			increasePC();
			return;
		default:
			cerr << "Unexpected system call " << type << "\n";
			break;
		}

		break;
	case PageFaultException:
		printf("PageFaultException\n");
		SysHalt();
		break;
	case ReadOnlyException:
		printf("ReadOnlyException\n");
		SysHalt();
		break;
	case BusErrorException:
		printf("BusErrorException\n");
		SysHalt();
		break;
	case AddressErrorException:
		printf("AddressErrorException\n");
		SysHalt();
		break;
	case OverflowException:
		printf("OverflowException\n");
		SysHalt();
		break;
	case IllegalInstrException:
		printf("IllegalInstrException\n");
		SysHalt();
		return;
		break;
	case NumExceptionTypes:
		printf("NumExceptionTypes\n");
		SysHalt();
		return;
		break;
	case NoException:
		return;
		break;
	default:
		cerr << "Unexpected user mode exception" << (int)which << "\n";
		break;
	}
	ASSERTNOTREACHED();
}
