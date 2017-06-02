/**
 * MINIFS - Mini File System
 *
 * This is an educational project for the OS-II class on Sao Paulo State University - UNESP.
 * Authors: Dalton Lima @daltonbr
 *          Lucas Pinheiros @lucaspin
 * https://github.com/lucaspin/minifs
 * filesystem.c
 */

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "file_allocation_table.h"

int make_file_entry(char* name, file_entry* output) {
  int index = get_first_fat_available();

  if(index != -1) {
    //TODO: add in the offset later, the 10 initial bytes reserved for the system
    int offset = index * BLOCK_SIZE;
    file_entry* entry = (file_entry*) malloc(sizeof(file_entry));
    //TODO: make a name validation
    strncpy(entry->file_name, name, 4);
    entry->is_directory = FALSE;
    entry->initial_block = index;
    entry->timestamp = time(NULL);
    output = entry;

    memcpy ((void*)filesystem+offset, (void*)entry, sizeof(file_entry));
    return index;
  } else {
    return -1;
  }
}

void print_file_entry(file_entry* fe) {
  fprintf(stdout, "[DEBUG] file name: %s\n", fe->file_name);
  fprintf(stdout, "[DEBUG] is_directory: %d\n", fe->is_directory);
  fprintf(stdout, "[DEBUG] initial block: %u\n", fe->initial_block);
  fprintf(stdout, "[DEBUG] time stamp: %u\n", fe->timestamp);
}
