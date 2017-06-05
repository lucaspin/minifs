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
void set_root(directory* root);
int get_first_slot_in_directory(directory* dir);
int get_first_fat_available();
int set_entry_fat(int index, int lookup);
int free_fat(int index);
void print_fat();

#endif