/**
 * MINIFS - Mini File System
 *
 * This is an educational project for the OS-II class on Sao Paulo State University - UNESP.
 * Authors: Dalton Lima @daltonbr
 *          Lucas Pinheiros @lucaspin
 * https://github.com/lucaspin/minifs
 * filesystem.h
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdint.h>

#define SECTOR_NUMBER 256
#define BLOCK_SIZE 512
#define RESERVED_BLOCK_NUMBER 10
#define MAX_FILE_ENTRIES 21
#define TRUE 1;
#define FALSE 0;
#define MAX_FILE_NAME_SIZE 12

typedef struct file_entry {
  char file_name[MAX_FILE_NAME_SIZE+1];
  uint8_t is_directory;
  uint8_t initial_block;
  uint16_t file_size;
  uint32_t timestamp;
} file_entry;

typedef struct directory {
  file_entry entries[MAX_FILE_ENTRIES];
} directory;

// variables
char filesystem[SECTOR_NUMBER * BLOCK_SIZE];

// functions
int make_file_entry(char* name, file_entry* output);
void print_file_entry(file_entry* fe);

#endif