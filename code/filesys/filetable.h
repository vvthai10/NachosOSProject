#include "openfile.h"
#include "sysdep.h"

#define TABLE_LENGTH 20
#define READWRITE 0
#define READ 1
#define CONSOLE_INPUT 2
#define CONSOLE_OUTPUT  3

class FileTable {
   private:
    OpenFile** openFiles;

   public:
    FileTable() {
        openFiles = new OpenFile*[TABLE_LENGTH];
    }

<<<<<<< HEAD
    int AddOpenFile(char* fileName, int type) {
=======
    int Insert(char* fileName, int type) {
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
        int index = -1;
        for (int i = 2; i < TABLE_LENGTH; i++) {
            if (openFiles[i] == NULL) {
                index = i;
                break;
            }
        }

<<<<<<< HEAD
        // Khong con vi tri trong trong bang quan ly file mo
=======
        // Khong con vi tri trong trong bang file mo
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
        if (index == -1) {
            return -1;
        }

        int descriptor;
        if (type == READWRITE){
            descriptor = OpenForReadWrite(fileName, FALSE);
        }
        if (type == READ){
            descriptor = OpenForRead(fileName, FALSE);
        }

        // Khong the mo file
<<<<<<< HEAD
        if (descriptor == -1){
            return -1;
        }
=======
        if (descriptor == -1) return -1;
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
        openFiles[index] = new OpenFile(descriptor);
        openFiles[index]->descriptorId = descriptor;
        openFiles[index]->type = type;
        openFiles[index]->fileName = new char[strlen(fileName)];
        strcpy(openFiles[index]->fileName, fileName);

        return index;
    }

<<<<<<< HEAD
    int RemoveOpenFile(int index) {
        if (index < 2 || index >= TABLE_LENGTH) return -1;
        if (openFiles[index] != NULL) {
=======
    int Remove(int index) {
        if (index < 2 || index >= TABLE_LENGTH) return -1;
        if (openFiles[index]) {
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
            Close(openFiles[index]->descriptorId);
            openFiles[index] = NULL;
            return 0;
        }
        return -1;
    }

    int ReadFile(char* buffer, int size, int id){
        if(id < 2 || id >= TABLE_LENGTH){
            return -1;
        }
        if(openFiles[id] == NULL){
            return -1;
        }
        int sizeRead = openFiles[id]->Read(buffer, size);
<<<<<<< HEAD
        // So luong ki tu muon doc lon hon so luong ki tu co trong file
=======
        // So luong ki tu doc duoc co bang kich thuoc quy dinh
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
        if(sizeRead != size){
            return -2;
        }
        return sizeRead;
    }

    int WriteFile(char* buffer, int size, int id){
        if(id < 2 || id >= TABLE_LENGTH){
            return -1;
        }
        if(openFiles[id] == NULL || openFiles[id]->type != READWRITE){
            return -1;
        }
        int sizeWrite = openFiles[id]->Write(buffer, size);
        
        return sizeWrite;
    }
<<<<<<< HEAD

=======
    /*
        Kiểm tra 1 file có đang mở không bằng tên file đó
        Nếu file đang mở thì trả về 1
        Nếu không trả về 0
    */
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
    bool CheckFileOpen(char* nameCheck){
        for(int i = 2; i < TABLE_LENGTH; i++){
            if(openFiles[i]){
                if(strcmp(openFiles[i]->fileName, nameCheck) == 0){
                    return true;
                }
                return false;
            }
        }
    }
<<<<<<< HEAD

=======
    //đưa con trỏ file của file ở vị trí index trong bảng tới vị trí pos
    /*
    Nếu index nằm ngoài chiều dài tối đa của bảng hoặc ở vị trí 0 và 1 thì không thực hiện
    Nếu tại index không có file nào đang mở thì không thực hiện
    Nếu pos == -1 thì sẽ pos = độ dài của dữ liệu trong file 
    Nếu pos nằm ngoài phạm vi có thể tới của con trỏ file thì không thực hiện
    đưa con trỏ file tới vị trí pos
    */
>>>>>>> 7a675ff2ff57ddf58673c8682cbe69e027cf9f30
    int Seek(int pos, int index) {
        if (index <= 1 || index >= TABLE_LENGTH) return -1;
        if (openFiles[index] == NULL) return -1;
        // use seek(-1) to move to the end of file
        if (pos == -1) pos = openFiles[index]->Length();
        if (pos < 0 || pos > openFiles[index]->Length()) return -1;
        return openFiles[index]->Seek(pos);
    }

    ~FileTable() {
        for (int i = 0; i < TABLE_LENGTH; i++) {
            if (openFiles[i]){
                delete openFiles[i];
            }
        }
        delete[] openFiles;
    }
};

