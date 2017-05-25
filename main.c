#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SECTOR_NUMBER 256
#define BLOCK_SIZE 512
#define RESERVED_BLOCK_NUMBER 10
#define MAX_FILE_NAME_SIZE 4

typedef struct file_entry {
  char file_name[MAX_FILE_NAME_SIZE];
  unsigned char initial_block;
  unsigned int timestamp;
} file_entry;

typedef struct directory {
  file_entry* entries;
} directory;

char filesystem[SECTOR_NUMBER * BLOCK_SIZE];
int file_allocation_table[SECTOR_NUMBER];

const int MAX_FILE_ENTRIES = BLOCK_SIZE / sizeof(file_entry);

int main() {
  directory* root = (directory*) malloc(BLOCK_SIZE);
  directory* foo = (directory*) malloc(BLOCK_SIZE);

  file_entry* entry = (file_entry*) malloc(sizeof(file_entry));
  strcpy(entry->file_name, "foo");
  entry->initial_block = 11;
  entry->timestamp = (unsigned) time(NULL);

  foo->entries

  return 0;
}