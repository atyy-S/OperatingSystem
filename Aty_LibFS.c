#include "libFS.h"

//global vars
FileEntry file_table [MAX_FILES]; //file table to track files
int file_count=0;
char file_data[MAX_FILES][MAX_FILESIZE];


//crate new file 
int fileCreate(const char *filename){
    //check for existing file with the same name
    for (int i =0; i< file_count; i++){
        if (strcmp(file_table[i].filename, filename)==0){
            printf("☠️Error: File '%s' already exist, try different name!!! \n", filename);
            return- 1;
        }
    }
    //Add files to the file table
    strcpy(file_table[file_count].filename, filename);
    file_table[file_count].size=0;
    file_table[file_count].is_open=0; //file is closed
    
    // clear file contents
    memset(file_data[file_count], 0, MAX_FILESIZE);
    file_count++;
    printf("Yeyyy🥳🥳... file '%s' is created successfully, now dance", filename);
    return 0;
}        
      
//open file
int fileOpen(const char *filename){

    for (int i =0; i<file_count; i++){
        if (strcmp(file_table[i].filename, filename)==0){

            if (file_table[i].is_open){
                printf("ERRORRR☠️: file '%s' already open, close it 1st \n", filename);
                return -1;
            }

            file_table[i].is_open=1; //mark file is open
            printf("File '%s' is open successfilly 🥳🥳", filename);
            return i; //file index
        }
    }
    printf("ERROORRR☠️☠️ file '%s' CANNOT be found \n", filename);
    return -1;
}

//Write file
int fileWrite(int file_index, const char *data){

    if  (!file_table[file_index].is_open){
        printf("ERROOORR☠️☠️👻 FIle '%s' is not open \n", file_table[file_index].filename);
        return -1;
    }
    int data_size=strlen(data);

    //Check if date large (pass the limit)
    if (data_size > MAX_FILESIZE) {
        printf("ERROOORR☠️ Data too large brovv!\n");
        return -1;
    }

    //write data to the local file
    memcpy(file_data[file_index], data, data_size);
    file_table[file_index].size = data_size;
    printf("Congratulation 🥳Data Written to file '%s' successfullyyy \n", file_table[file_index].filename);
    return 0;
}

//Read file
int fileRead (int file_index, char *buffer, int buffer_size){
    
    //check valid index
    if (file_index <0 || file_index >=file_count){
        printf("ERROOrrr👻👻 invalid file index\n");
        return-1;
    }

    //check if file is open
    if (!file_table[file_index].is_open) {
        printf("ERROOORR👻File is not open.\n", "don't ask me why🥲✌️ \n");
        return -1;
    }

    //decide how many byte to read
    int n; //bytes_to_read
    if (file_table[file_index].size < buffer_size){
       n= file_table[file_index].size;
    } 
    else {
        n= buffer_size;   
    } 
    memcpy(buffer, file_data[file_index], n);
    return n;   
}

//Close file
int fileClose(int file_index){

    //check valid index
    if (file_index < 0 || file_index >= file_count) {
        printf("ERROOORR👻invalid file index.\n");
        return -1;
    }

    //check if file already close
    if (!file_table[file_index].is_open) {
        printf("BRooooveee file already closed 🙄.\n");
        return -1;
    }

    file_table[file_index].is_open = 0;
    return 0;
}

//delate file
int fileDelate(const char *filename){
     for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
            // shift all files left
            for (int j = i; j < file_count - 1; j++) {
                file_table[j] = file_table[j + 1];
                memcpy(file_data[j], file_data[j + 1], MAX_FILESIZE);
            }
            file_count--;
            return 0;
        }
    }

    printf("ERROOORR👻 file not found.\n");
    return -1;

}