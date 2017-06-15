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

/////////////////////////////////////////////////////////////////////////////
// functions
/////////////////////////////////////////////////////////////////////////////

void initialize_memory_bitmap();
void initialize_file_allocation_table();

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
 * Add a file into a directory
 * @param   current_dir: this is the parent directory
 *          file_size: file size in bytes
 * @return  return 0 when successful
 *                -1 duplicated name
 *                -2 no more slots available on directory
 *                -3 insufficient space in the filesystem
 *                -4 can't allocate file, other reasons
 */
int add_file(directory* current_dir, int current_dir_initial_block, char* new_file_name, int file_size);

/**
 * Add a directory into another
 * @param   current_dir: this is the parent directory
 *          new_dir_name: the name of the directory to add inside the parent
 * @return  return 0 when successful, -1 otherwise
 */
int add_directory(directory* current_dir, int current_dir_initial_block, char* new_dir_name);

/**
 * Print out a directory to the screen
 * @param   dir: directory to be printed
 * @return  return 0 when successful, -1 otherwise
 */
int print_directory(directory* dir);

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
int file_entry_exists_in_directory(directory *dir, char *name);

/**
 * Allocate the n requested sectors in the fat
 * @param   initial_fat_index: the index to start the file allocation
 * @return  return  0 when successful allocate all sectors
 *          return -1 Insufficient free sectors in FAT
 *          return -2 Negative value in 'allocate_n_fat_slots'
 *          return -3 initial_fat_index already in use
 */
int allocate_n_fat_slots(int number_sector_to_allocate, int initial_fat_index);
int get_first_fat_available();
int set_entry_fat(int index, int lookup);
int free_fat(int index);
void print_map_sec();

/**
 * get the next fat_index pointed by another
 * @param   fat_index: the fat_index to look
 * @return  return the next fat_index
 *          -1 will indicate end a file sector chain (not an error)
 *          -2 will indicate an ERROR: fat_index out-of-bounds
 */
int get_next_fat_index(int fat_index);

file_entry* get_file_entry_in_dir(directory* current_dir, char* file_name);

/**
 * is this file_entry a valid DIRECTORY
 * @return  return 0 when successful, -1 otherwise
 */
int is_valid_directory(file_entry* fe);

/**
 * is this file_entry a valid FILE
 * @return  return 0 when successful, -1 otherwise
 */
int is_valid_file(file_entry* fe);

int remove_directory(directory* current_dir, int current_dir_initial_block, char* new_dir_name);
void empty_file_entry(file_entry* entry);
int is_directory_empty(directory* dir);
#endif