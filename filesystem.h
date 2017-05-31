#include <stdint.h>

#define SECTOR_NUMBER 256
#define BLOCK_SIZE 512
#define RESERVED_BLOCK_NUMBER 10
#define MAX_FILE_ENTRIES 32

// 8 gives us 16 bytes per file_entry
#define MAX_FILE_NAME_SIZE 8

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

// variables
char filesystem[SECTOR_NUMBER * BLOCK_SIZE];

// functions
void initiate_fs();