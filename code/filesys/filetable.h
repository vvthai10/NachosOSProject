#pragma once
#include "openfile.h"
#include "sysdep.h"

#define TABLE_LENGTH 20
#define CONSOLE_INPUT 0
#define CONSOLE_OUTPUT 1
#define READWRITE 0
#define READ 1
#define WRITE 2

class FileTable{
    private:
        OpenFile** openFiles;
        int* filesType;
        int *filesDescriptor;

    public:
        FileTable(){
            openFiles = new OpenFile*[TABLE_LENGTH];
            filesType = new int[TABLE_LENGTH];
            filesType[CONSOLE_INPUT] = READ;
            filesType[CONSOLE_OUTPUT] = WRITE;

            filesDescriptor = new int[TABLE_LENGTH];
        }

        ~FileTable(){
            for(int i = 0; i < TABLE_LENGTH; i++){
                if(openFiles[i] != NULL){
                    delete[] openFiles[i];
                }
            }

            delete[] openFiles;
            delete[] filesType;
            delete[] filesDescriptor;
        }

        // Them file can mo vao bang
        int Insert(char* fileName, int type){
            int index = -1;

            for(int i = 2; i < TABLE_LENGTH; i++){
                if(openFiles[i] == NULL){
                    index = i;
                    break;
                }
            }

            // Khong con vi tri trong bang table
            if(index == -1){
                return -1;
            }

            if(type == READWRITE){
                filesDescriptor[index] = OpenForReadWrite(fileName, false);
            }
            if(type == READ){
                filesDescriptor[index] = OpenForRead(fileName, false);
            }

            // printf("File descriptor: %d, index: %d", filesDescriptor[index], index);

            //Khong the mo file
            if (filesDescriptor[index] == -1) {
                return -1;
            }
            openFiles[index] = new OpenFile(filesDescriptor[index]);
            filesType[index] = type;

            return index;
        }

        // Xoa file khoi bang cac file dang mo <-> Close
        int Remove(int index){
            
            if(index < 2 || index >= TABLE_LENGTH) {
                return -1;
            }
            if(openFiles[index] != NULL){
                Close(filesDescriptor[index]);
                openFiles[index] = NULL;
                return 0;
            }

            return -1;
        }
        //index of openfile in table
        int Seek(int pos, int index) {
            if (index <= 1 || index >= TABLE_LENGTH) return -1;
            if (openFiles[index] == NULL) return -1;
            // use seek(-1) to move to the end of file
            if (pos == -1) pos = openFiles[index]->Length();
            if (pos < 0 || pos > openFiles[index]->Length()) return -1;
            return openFiles[index]->Seek(pos);
        }
};