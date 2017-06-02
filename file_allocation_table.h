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

/* return first slot in fat available, returns -1 if full */
void initiate_fs();
int get_first_fat_available();
int set_entry_fat(int index, int lookup);
int free_fat(int index);
void print_fat();

#endif