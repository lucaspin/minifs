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
//#include "file_allocation_table.h"

extern int file_allocation_table[SECTOR_NUMBER];
extern int memory_bitmap[SECTOR_NUMBER];

/* setup root directory and stores it at the filesystem */
void initiate_fs();
directory* get_root();
directory* get_directory(directory* current_dir);
/**
 * Add a directory into another
 * @param   current_dir: this in parent directory
 *          new_dir_name: the name of the directory to add inside the parent
 * @return  return 0 when successful, -1 otherwise
 */
int add_directory(directory* current_dir, char* new_dir_name);
void set_root(directory* root);
/**
 * get the first slot available in a directory
 * @param   dir: this is the directory to look at
 * @return  return the index of the first slot available, or -1 otherwise
 */
int get_first_slot_in_directory(directory* dir);

/**
 * verify for duplicates names in a directory
 * @param   dir: this is the directory to look at
 *          name: the name for the query
 * @return  return 0 when not find duplicated names, or -1 otherwise
 */
int get_duplicate_name_in_directory(directory* dir, char* name);
int get_first_fat_available();
int set_entry_fat(int index, int lookup);
int free_fat(int index);
void print_fat();

#endif