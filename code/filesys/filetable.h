#pragma once
#include "openfile.h"
#include "sysdep.h"

#define TABLE_LENGTH 20
#define READWRITE 0
#define READ 1
#define CONSOLE_INPUT 2
#define CONSOLE_OUTPUT 3

class FileTable{
    private:
        OpenFile** openFiles;
        char** fileNames;

    public:
        FileTable(){
            openFiles = new OpenFile*[TABLE_LENGTH];
            openFiles[0]->type = CONSOLE_INPUT;
            openFiles[1]->type = CONSOLE_OUTPUT;

            fileNames = new char*[TABLE_LENGTH];
            for (int i = 0; i < TABLE_LENGTH; i++)
            {
                /* code */
                fileNames[i] = NULL;
            }
            
        }

        ~FileTable(){
            for(int i = 0; i < TABLE_LENGTH; i++){
                if(openFiles[i] != NULL){
                    delete[] openFiles[i];
                }
            }
            delete[] openFiles;
            
            for (int i = 2; i < TABLE_LENGTH; i++)
            {
                if(fileNames[i] != NULL) {
                    delete[] fileNames[i];
                }
            }
            delete[] fileNames;
        }

        // Them file can mo vao bang
        int AddOpenFile(char* fileName, int type){
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
                openFiles[index]->descriptorId = OpenForReadWrite(fileName, false);
            }
            if(type == READ){
                openFiles[index]->descriptorId = OpenForRead(fileName, false);
            }

            //Khong the mo file
            if (openFiles[index]->descriptorId == -1) {
                return -1;
            }
            openFiles[index] = new OpenFile(openFiles[index]->descriptorId);
            filesType[index] = type;
            fileNames[index] = new char[strlen(fileName)];
            fileNames[index] = fileName;
            return index;
        }

        // Xoa file khoi bang cac file dang mo <-> Close
        int RemoveOpenFile(int id){
            
            if(id < 2 || id >= TABLE_LENGTH) {
                return -1;
            }
            if(openFiles[id] != NULL){
                Close(openFiles[id]->descriptorId);
                openFiles[id] = NULL;
                
                //delete fileNames[index];
                fileNames[id] = "D";
                return 0;
            }

            return -1;
        }

        int ReadFile(char* buffer, int charCount, int id){
            if(id >= TABLE_LENGTH || id < 0){
                return -1;
            }
            if(openFiles[id] == NULL){
                return -1;
            }
            int res = openFiles[id]->Read(buffer, charCount);
            if(res != charCount){
                return -2;
            }
            return res;
        }

        int WriteFile(char* buffer, int charCount, int id){
            if(id >= TABLE_LENGTH || id < 0){
                return -1;
            }
            if(openFiles[id] == NULL || openFiles[id]->type == READ){
                return -1;
            }

            return openFiles[id]->Write(buffer, charCount);
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

        int IsFileOpen(char* fileName) {
            for (int i = 2; i < TABLE_LENGTH; i++)
            {
                if(fileNames[i] == fileName) {
                    return i;
                }
            }
            return -1;
            
        }
};
