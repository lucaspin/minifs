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
#define SLASH_SEPARATOR "/"
#define MAX_DIRECTORY_SUBLEVELS 8

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
extern char filesystem[SECTOR_NUMBER * BLOCK_SIZE];

/////////////////////////////////////////////////////////////////////////////
// functions
/////////////////////////////////////////////////////////////////////////////

/**
 * TODO: verify and instantiate a file_entry
 * @param
 * @return
 */
file_entry* make_file_entry(char* name, uint16_t file_size, int initial_block, int is_directory);

/**
 * Setup root directory and stores it at the filesystem
 */
void initialize_fs();

void nullify_path_matrix(char matrix[MAX_DIRECTORY_SUBLEVELS][MAX_FILE_NAME_SIZE]);

/**
 * @param   path to create the directory (name included)
 * @return  return 0 when successful,
 *                 -1 invalid path
 *                 -2 to subdirectories levels exceeded (8 maximum)
 */
int make_directory(char* path);

/**
 * @param   path to create the directory (name included)
 * @return  return 0 when successful,
 *                 -1 invalid path
 *                 -2 to subdirectories levels exceeded (8 maximum)
 */
int make_file(char* path, int file_size);

/**
 * list the files and sub-directories
 * @param   path to list (name included)
 * @return  return 0 when successful
 *                 -1 invalid path
 *                 -2 to subdirectories levels exceeded (8 maximum)
 *                 -3 file cannot be created
 */
int list_dir(char* path);

/**
 * parse the path and verify for maximum sublevels
 * @param   full path to create the directory (name included)
 *          output_path_parsed: char* array to output the parsed path
 * @return  return the number of elements in the complete path when successful
 *          -1 to invalid paths
 */
int parse_path(char *path, char output_path_parsed[MAX_DIRECTORY_SUBLEVELS][MAX_FILE_NAME_SIZE]);
void print_file_entry(file_entry* fe);
char* timestamp_to_string(uint32_t timestamp);
int get_total_free_space_in_bytes();
int get_total_free_space_in_sectors();

//TODO:
int print_sectors_used_by_file();

#endif