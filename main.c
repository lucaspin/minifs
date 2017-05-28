#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SECTOR_NUMBER 256
#define BLOCK_SIZE 512
#define RESERVED_BLOCK_NUMBER 10
#define MAX_FILE_NAME_SIZE 8        // 8 gives us 16 bytes per file_entry
#define MAX_FILE_ENTRIES 32
#define TRUE 1;
#define FALSE 0;

/* 16 bytes in size */
typedef struct file_entry {
  char file_name[MAX_FILE_NAME_SIZE+1];
  uint8_t is_directory;
  uint8_t initial_block;
  uint32_t timestamp;
} file_entry;

typedef struct directory {
  file_entry entries[MAX_FILE_ENTRIES];
} directory;

char filesystem[SECTOR_NUMBER * BLOCK_SIZE];
int file_allocation_table[SECTOR_NUMBER];

int main() {
  int index;
  int offset;
    /* just a single test, to validate our concept
     * root --> folder --> fileA */
  printf("[DEBUG] sizeof(file_entry): %lu bytes\n", sizeof(file_entry));
  printf("[DEBUG] sizeof(directory) with MAX_FILE_ENTRIES: %lu bytes\n", sizeof(directory));

  directory* root = (directory*) malloc(BLOCK_SIZE);
  directory* folder = (directory*) malloc(BLOCK_SIZE);

  file_entry* root_entry = (file_entry*) malloc(sizeof(file_entry));
  file_entry* folder_entry = (file_entry*) malloc(sizeof(file_entry));
  file_entry* fileA_entry = (file_entry*) malloc(sizeof(file_entry));

  /* file entry for 'root' (fat#0) */
  index = 0;  /* this index could be get with first_fit algorithm */
  strncpy(root_entry->file_name,"root", 4);
  root_entry->is_directory = TRUE;
  root_entry->initial_block = index;
  root_entry->timestamp = time(NULL);
  offset = index * BLOCK_SIZE;
  int directory_index = 0 * sizeof(file_entry);  // index inside a folder, again using first fit
  sleep(2);

  /* file_entry for 'folder' (fat#1) */
  index = 1;
  strncpy(folder_entry->file_name,"folder", 6);
  folder_entry->is_directory = TRUE;
  folder_entry->initial_block = index;
  folder_entry->timestamp = time(NULL);
  
  directory_index = 0 * sizeof(file_entry);
  /* 'folder' --> 'root' */
  memcpy((void*)root->entries+directory_index, (void*)folder_entry, sizeof(file_entry));
  sleep(2);

  /* file_entry for 'fileA' (fat#2) */
  index = 2;
  strncpy(fileA_entry->file_name,"fileA", 5);
  folder_entry->is_directory = FALSE;
  fileA_entry->initial_block = index;
  fileA_entry->timestamp = time(NULL);
  offset = index * BLOCK_SIZE;
  directory_index = 0 * sizeof(file_entry);
  /* 'fileA' --> 'folder' */
  memcpy((void*)folder->entries+directory_index, (void*)fileA_entry, sizeof(file_entry));
  
  /* 'root' --> fat#0 */
  index = 0;
  offset = index * BLOCK_SIZE;
  memcpy((void*)filesystem+offset, (void*)root, BLOCK_SIZE);
  
  /* 'folder' --> fat#1 */
  index = 1;
  offset = index * BLOCK_SIZE;
  memcpy((void*)filesystem+offset, (void*)folder, BLOCK_SIZE);
  
  /* 'fileA' --> fat#2 */
  index = 2;
  offset = index * BLOCK_SIZE;
  memcpy((void*)filesystem+offset, (void*)fileA_entry, BLOCK_SIZE);
  
  /* reading from 'Hard-Drive' */
      /* placeholders */
  directory* temp_root;  // needed to read from fat#0
  directory* temp_folder;
  //file_entry* temp_root_entry = (file_entry*)filesystem;
  file_entry* temp_folder_entry = (file_entry*) malloc(sizeof(file_entry));
  file_entry* temp_fileA_entry = (file_entry*) malloc(sizeof(file_entry));
  
  /* root_entry are taken from memmory */
  fprintf(stdout, "[DEBUG] file name: %s\n", root_entry->file_name);
  fprintf(stdout, "[DEBUG] is_directory: %d\n", root_entry->is_directory);
  fprintf(stdout, "[DEBUG] initial block: %u\n", root_entry->initial_block);
  fprintf(stdout, "[DEBUG] time stamp: %u\n", root_entry->timestamp);

  /* Assuming 'root' will always be at fat #0 */
  offset = 0 * BLOCK_SIZE;
  temp_root = (void*)filesystem + offset;
  memcpy((void*)temp_folder_entry, (void*)temp_root, sizeof(file_entry));
  
  fprintf(stdout, "[DEBUG] file name: %s\n", temp_folder_entry->file_name);
  fprintf(stdout, "[DEBUG] is_directory: %d\n", temp_folder_entry->is_directory);
  fprintf(stdout, "[DEBUG] initial block: %u\n", temp_folder_entry->initial_block);
  fprintf(stdout, "[DEBUG] time stamp: %u\n", temp_folder_entry->timestamp);

  offset = temp_folder_entry->initial_block * BLOCK_SIZE;  // reading from fat#1
  temp_folder = (void*)filesystem + offset;
  memcpy((void*)temp_fileA_entry, (void*)temp_folder, sizeof(file_entry));
  
  fprintf(stdout, "[DEBUG] file name: %s\n", temp_fileA_entry->file_name);
  fprintf(stdout, "[DEBUG] is_directory: %d\n", temp_fileA_entry->is_directory);
  fprintf(stdout, "[DEBUG] initial block: %u\n", temp_fileA_entry->initial_block);
  fprintf(stdout, "[DEBUG] time stamp: %u\n", temp_fileA_entry->timestamp);
    
  offset = temp_fileA_entry->initial_block * BLOCK_SIZE;  // reading from fat#2
  memcpy((void*)temp_fileA_entry, (void*)filesystem+offset, BLOCK_SIZE);
  
  fprintf(stdout, "[DEBUG] file name: %s\n", temp_fileA_entry->file_name);
  fprintf(stdout, "[DEBUG] is_directory: %d\n", temp_fileA_entry->is_directory);
  fprintf(stdout, "[DEBUG] initial block: %u\n", temp_fileA_entry->initial_block);
  fprintf(stdout, "[DEBUG] time stamp: %u\n", temp_fileA_entry->timestamp);

  return 0;
}