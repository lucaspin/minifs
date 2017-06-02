/**
 * MINIFS - Mini File System
 *
 * This is an educational project for the OS-II class on Sao Paulo State University - UNESP.
 * Authors: Dalton Lima @daltonbr
 *          Lucas Pinheiros @lucaspin
 * https://github.com/lucaspin/minifs
 * file_allocation_table.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "filesystem.h"
#include "file_allocation_table.h"

void initiate_fs() {
// TODO: setup boot sector
// TODO: setup filesystem itself
// TODO: setup root directory
}

void initialize_fat() {
  for (int count = 0; count < SECTOR_NUMBER; count++) {
    file_allocation_table[count] = -1;
  }
}

int get_first_fat_available() {
  for (int count = 0; count < SECTOR_NUMBER; count++) {
    if (file_allocation_table[count] == -1) {
      return count;
    }
  }
  return -1;
}

int set_entry_fat(int index, int lookup) {
  if (index >= 0 && index < SECTOR_NUMBER &&
      lookup >= 0 && lookup < SECTOR_NUMBER) {
    file_allocation_table[index] = lookup;
    return 0;
  }
  exit(-1);
}

int free_fat(int index) {
  if (index >= 0 && index < SECTOR_NUMBER) {
    file_allocation_table[index] = -1;
    return 0;
  }
  exit(-1);
}

void print_fat() {
  fprintf(stdout, "[DEBUG] Printing fat allocated sector:\n");
  for (int count = 0; count < SECTOR_NUMBER; count++) {
    if (file_allocation_table[count] != -1) {
      fprintf(stdout, "fat[%d]: %d | ",count, file_allocation_table[count]);
    }
  }
}