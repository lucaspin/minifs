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
#include <memory.h>
#include "filesystem.h"
#include "file_allocation_table.h"

void initialize_memory_bitmap() {
  int i = 0;
  for (; i < SECTOR_NUMBER; i++) {
    memory_bitmap[i] = 0;
  }
}

void initialize_file_allocation_table() {
  int i = 0;
  for (; i < SECTOR_NUMBER; i++) {
    file_allocation_table[i] = -1;
  }
}

directory* get_root_directory() {
  directory* output_dir = malloc(sizeof(directory));
  memcpy((void*) output_dir, (void*) filesystem, BLOCK_SIZE);
  return output_dir;
}

int get_directory(directory* current_dir, int* current_dir_initial_block, char* dir_name) {
  int i;
  for (i = 0; i < MAX_FILE_ENTRIES; i++) {
    if (!strcmp(current_dir->entries[i].file_name, dir_name)) {
      int next_dir_block = current_dir->entries[i].initial_block;
      get_directory_from_fat_by_id(next_dir_block, current_dir);
      *current_dir_initial_block = next_dir_block;
      return 0;
    }
  }
  return -1;
}

void get_directory_from_fat_by_id(int initial_block_offset, directory *output_dir) {
  int offset = initial_block_offset * BLOCK_SIZE;
  memcpy((void*) output_dir, (void*) filesystem + offset, sizeof(directory));
}

int add_directory(directory* current_dir, int current_dir_initial_block, char* new_dir_name) {
  uint8_t free_slot;

  if (get_duplicate_name_in_directory(current_dir, new_dir_name)) {
    printf("[ERROR] Duplicated name found %s\n", new_dir_name);
    return -1;
  }

  if ((free_slot = get_next_available_slot(current_dir)) == -1) {
    fprintf(stderr, "%s\n", "No more slots available on directory!");
    return -1;
  }

  // add file entry to parent directory and update it on fs
  int index = get_first_fat_available();
  file_entry* new_entry = make_file_entry(new_dir_name, 0, index, 1);
  current_dir->entries[free_slot] = *new_entry;
  memcpy((void*) filesystem + (current_dir_initial_block * BLOCK_SIZE), (void*) current_dir, BLOCK_SIZE);

  // create new directory structure on filesystem
  int offset = index * BLOCK_SIZE;
  directory* new_directory = malloc(sizeof(directory));
  memcpy((void*) filesystem + offset, (void*) new_directory, BLOCK_SIZE);
  memory_bitmap[index] = 1;
  return 0;
}

// TODO:
int print_directory(directory* dir) {
  /* for each VALID file_entry in dir, print it */
  fprintf(stdout, "print_directory not implemented yet!\n");
  int i = 0;
  for (i = 0; i < MAX_FILE_ENTRIES; i++) {
    file_entry* fe = &dir->entries[i];
    if (fe->timestamp != 0) {
      print_file_entry(fe);
    }
  }
  return 0;
  }

void set_root_directory() {
  directory* root = malloc(sizeof(directory));
  memcpy((void*) filesystem, (void*) root, BLOCK_SIZE);
  memory_bitmap[0] = 1;
}


uint8_t get_next_available_slot(directory* dir) {
  uint8_t i = 0;

  for (i = 0; i < MAX_FILE_ENTRIES; i++) {
    if (!strcmp(dir->entries[i].file_name, "")) {
      return i;
    }
  }

  return (uint8_t) -1;
}

int get_duplicate_name_in_directory(directory* dir, char* name) {
  for (int i = 0; i < MAX_FILE_ENTRIES; i++) {
    if (!strcmp(dir->entries[i].file_name, name)) {
      return -1;
    }
  }
  return 0;
}

int get_first_fat_available() {
  int count = 0;

  for (; count < SECTOR_NUMBER; count++) {
    if (memory_bitmap[count] == 0) {
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

