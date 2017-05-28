#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SECTOR_NUMBER 256
#define BLOCK_SIZE 512
#define RESERVED_BLOCK_NUMBER 10
#define MAX_FILE_NAME_SIZE 8        // 8 gives us 16 bytes per file_entry
#define MAX_FILE_ENTRIES 32

/* 16 bytes in size */
typedef struct file_entry {
  char file_name[MAX_FILE_NAME_SIZE+1];
  uint8_t initial_block;
  uint32_t timestamp;
} file_entry;

/* not sure about this structure yet */
typedef struct directory {
  file_entry entries[MAX_FILE_ENTRIES];
} directory;

char filesystem[SECTOR_NUMBER * BLOCK_SIZE];
int file_allocation_table[SECTOR_NUMBER];

// 16 bytes (per entry) * 32 = 512 bytes
//const int MAX_FILE_ENTRIES = 32; 

int main() {
    /* just a single test, to validate our concept
     * create the root folder, a folder inside it */
  // directory* root = (directory*) malloc(BLOCK_SIZE);
  // directory* folder = (directory*) malloc(BLOCK_SIZE);

  printf("[DEBUG] sizeof(file_entry): %lu bytes\n", sizeof(file_entry));
  printf("[DEBUG] sizeof(directory)  MAX_FILE_ENTRIES: %lu bytes\n", sizeof(directory));

  /* Converting from time_t to string */
  time_t t = time(NULL);
  struct tm *ptm = gmtime(&t);
  char buf[256];
  strftime(buf, sizeof buf, "%F %T", ptm);
  // buf format "yyyy-mm-dd hh:mm:ss"
  puts(buf);

  /* time_t uses 8 bytes, but we can use uint32_t (4 bytes instead) */
  uint32_t seconds = time(NULL);
  printf("[DEBUG] Seconds since January 1, 1970 = %d\n", seconds);
  
  /* Instantiate a file entry */
  file_entry* entry = (file_entry*) malloc(sizeof(file_entry));
  strncpy(entry->file_name,"fold", 4);
  entry->initial_block = 3;
  entry->timestamp = seconds;
    fprintf(stdout, "\n[DEBUG] File instantiated\n");
    fprintf(stdout, "[DEBUG] file name: %s\n", entry->file_name);
    fprintf(stdout, "[DEBUG] initial block: %u\n", entry->initial_block);
    fprintf(stdout, "[DEBUG] time stamp: %u\n", entry->timestamp);

  /* copy the new instantiated file entry to the 'hard drive' at the slot #3 (hardcoded for tests)
  * memcpy( (void*)dst, (void*)src, n * sizeof(int) ); */
  u_int8_t index = 3;
  u_int16_t offset = index * BLOCK_SIZE;
  memcpy((void*)filesystem+offset, (void*)entry, BLOCK_SIZE);

  /* casting the file in the hard-drive to a temp_file */
  file_entry* temp_entry = (file_entry*) malloc(sizeof(file_entry));
  memcpy((void*)temp_entry, (void*)filesystem+offset, BLOCK_SIZE);    

  fprintf(stdout, "\n[DEBUG] Reading from 'hard drive'\n");
  fprintf(stdout, "[DEBUG] file name: %s\n", temp_entry->file_name);
  fprintf(stdout, "[DEBUG] initial block: %u\n", temp_entry->initial_block);
  fprintf(stdout, "[DEBUG] time stamp: %u\n", temp_entry->timestamp);
  
  return 0;
}