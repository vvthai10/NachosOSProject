#include "openfile.h"
#include "sysdep.h"

#define TABLE_LENGTH 20
#define READWRITE 0
#define READ 1
#define CONSOLE_INPUT 2
#define CONSOLE_OUTPUT  3


/*
    - Dùng để quản lý danh sách các file đang được mở. 
    - hực hiện các thao tác với file: mở, đóng, đọc, viết, seek
*/
class FileTable {
   private:
    OpenFile** openFiles;

   public:
    FileTable() {
        openFiles = new OpenFile*[TABLE_LENGTH];
    }

    // Thực hiện kiểm tra các điều kiện và mở các file được yêu cầu
    int AddOpenFile(char* fileName, int type) {
        int index = -1;

        // Kiểm tra danh sách quản lý file còn vị trí trống hay không
        for (int i = 2; i < TABLE_LENGTH; i++) {
            if (openFiles[i] == NULL) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            return -1;
        }

        // Thực hiện mở file theo yêu cầu của người dùng
        int descriptor;
        if (type == READWRITE){
            descriptor = OpenForReadWrite(fileName, FALSE);
        }
        if (type == READ){
            descriptor = OpenForRead(fileName, FALSE);
        }
        if (descriptor == -1){
            return -1;
        }

        // Tiến hành lưu trữ các thông tin cho một file khi đã mở
        openFiles[index] = new OpenFile(descriptor);
        openFiles[index]->descriptorId = descriptor;
        openFiles[index]->type = type;
        openFiles[index]->fileName = new char[strlen(fileName)];
        strcpy(openFiles[index]->fileName, fileName);

        return index;
    }

    // Thực hiện kiểm tra các điều kiện và đóng các file được yêu cầu
    int RemoveOpenFile(int index) {
        // Kiểm tra index có nằm trong giới hạn quản lý không
        if (index < 2 || index >= TABLE_LENGTH){
            return -1;
        }
        // Kiểm tra tại vị trí index có đang mở file không
        if (openFiles[index] != NULL) {
            Close(openFiles[index]->descriptorId);
            openFiles[index] = NULL;
            return 0;
        }
        return -1;
    }

    // Thực hiện kiểm tra các điều kiện và đọc file
    int ReadFile(char* buffer, int size, int id){
        // Kiểm tra có id có đang nằm trong danh sách quản lý không
        if(id < 2 || id >= TABLE_LENGTH){
            return -1;
        }
        // Kiểm tra tại vị trí index có đang mở file không
        if(openFiles[id] == NULL){
            return -1;
        }
        int sizeRead = openFiles[id]->Read(buffer, size);
        // Nếu số lượng kí tự đọc thực sự ít hơn số lượng yêu cầu, do file ngắn, trả về -2
        if(sizeRead != size){
            return -2;
        }
        return sizeRead;
    }

    // Thực hiện kiểm tra các điều kiện và viết file
    int WriteFile(char* buffer, int size, int id){
        // Kiểm tra có id có đang nằm trong danh sách quản lý không
        if(id < 2 || id >= TABLE_LENGTH){
            return -1;
        }
        // Kiểm tra tại vị trí index có đang mở file không và loại file đang mở có cho viết hay không
        if(openFiles[id] == NULL || openFiles[id]->type != READWRITE){
            return -1;
        }
        int sizeWrite = openFiles[id]->Write(buffer, size);
        
        return sizeWrite;
    }
    
    // Kiểm tra file có đang mở bằng tên file
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
    
    //đưa con trỏ file của file ở vị trí index trong bảng tới vị trí pos
    /*
    Nếu index nằm ngoài chiều dài tối đa của bảng hoặc ở vị trí 0 và 1 thì không thực hiện
    Nếu tại index không có file nào đang mở thì không thực hiện
    Nếu pos == -1 thì sẽ pos = độ dài của dữ liệu trong file 
    Nếu pos nằm ngoài phạm vi có thể tới của con trỏ file thì không thực hiện
    đưa con trỏ file tới vị trí pos
    */
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

