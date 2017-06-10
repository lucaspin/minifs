/**
 * MINIFS - Mini File System
 *
 * This is an educational project for the OS-II class on Sao Paulo State University - UNESP.
 * Authors: Dalton Lima @daltonbr
 *          Lucas Pinheiros @lucaspin
 * https://github.com/lucaspin/minifs
 * file_allocation_table.h
 */

#ifndef FILE_ALLOCATION_TABLE_H
#define FILE_ALLOCATION_TABLE_H

#include "filesystem.h"

int file_allocation_table[SECTOR_NUMBER];
int memory_bitmap[SECTOR_NUMBER];

/**
 * Get a reference to the root directory (inside the reserved space in the filesystem)
 * @param   output_dir: this is a pointer to the searched root directory
 */
directory* get_root_directory();

/**
 * Get a directory inside another
 * @param   current_dir: this is the parent directory, it will be used as an output also
 *          name: name of the searched directory
 * @return  return 0 when successful, -1 otherwise
 */
int get_directory(directory* current_dir, int* current_dir_initial_block, char* dir_name);

/**
 * Get a directory from the filesystem (by index)
 * @param   initial_block_offset: index in fat (not in bytes)
 *          output_dir: holds the directory loaded from filesystem
 */
void get_directory_from_fat_by_id(int initial_block_offset, directory *output_dir);

/**
 * Add a directory into another
 * @param   current_dir: this is the parent directory
 *          new_dir_name: the name of the directory to add inside the parent
 * @return  return 0 when successful, -1 otherwise
 */
int add_directory(directory* current_dir, int current_dir_initial_block, char* new_dir_name);

/**
 * memcopy the root directory inside the reserved space in the filesystem
 */
void set_root_directory();

/**
 * get the next slot available in a directory
 * @param   dir: this is the directory to look at
 * @return  return the index of the first slot available, or -1 otherwise
 */
uint8_t get_next_available_slot(directory* dir);

/**
 * verify for duplicates names in a directory
 * @param   dir: this is the directory to look at
 *          name: the name for the query
 * @return  return 0 when not find duplicated names, or -1 otherwise
 */
int get_duplicate_name_in_directory(directory* dir, char* name);
int get_first_fat_available();
int set_entry_fat(int index, int lookup);
void initialize_file_allocation_table();
void initialize_memory_bitmap();
int free_fat(int index);
void print_fat();

#endif