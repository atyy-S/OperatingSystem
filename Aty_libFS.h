#ifndef LIBFS_H
#define LIBFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constants
#define MAX_FILES 111
#define MAX_FILENAME 111
#define MAX_FILESIZE 1024

//file system structure
typedef struct{
    char filename [MAX_FILENAME];
    int size;
    int is_open;
} FileEntry;

extern FileEntry file_table[MAX_FILES];
extern char file_data[MAX_FILES][MAX_FILESIZE];
extern int file_count;

//Fuction Prototypes
int fileCreate(const char *filename);
int fileOpen(const char *filename);
int fileWrite(int file_index, const char *data);
int fileRead (int file_index, char *buffer, int buffer_size);
int fileClose(int file_index);
int fileDelete(const char *filename);

#endif //LIBFS
