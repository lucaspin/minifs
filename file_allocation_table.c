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
  /* memory bitmap fill zero */
  for (; i < SECTOR_NUMBER; i++) {
    memory_bitmap[i] = 0;
  }
  /* reserving FAT space */
  for (i = 0; i < RESERVED_BLOCK_NUMBER; i++) {
    memory_bitmap[i] = 1;
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
    /* check file_name and if it is_directory */
    if (!strcmp(current_dir->entries[i].file_name, dir_name) && current_dir->entries[i].is_directory == 1) {
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

int add_file(directory* current_dir, int current_dir_initial_block, char* new_file_name, int file_size) {
  uint8_t free_slot;

  if (get_duplicate_name_in_directory(current_dir, new_file_name)) {
    printf("[ERROR] Duplicated name found %s\n", new_file_name);
    return -1;
  }

  if ((free_slot = get_next_available_slot(current_dir)) == -1) {
    fprintf(stderr, "%s\n", "[ERROR] No more slots available on directory!");
    return -2;
  }

  /* Determining how many sectors do we need to save the file */
  int sectors_needed = (file_size / BLOCK_SIZE);
  if (file_size % BLOCK_SIZE) {sectors_needed++; }
  printf("Sectors needed: %d\n", sectors_needed);

  /* Disk space verification */
  if (sectors_needed > get_total_free_space_in_sectors()) {
    fprintf(stderr, "%s\n", "[ERROR] Cannot create file! Insufficient space in the filesystem!");
    return -3;
  }

  // add file entry to parent directory and update it on fs
  int fat_initial_index = get_first_fat_available();
  file_entry* new_entry = make_file_entry(new_file_name, file_size, fat_initial_index, 0);
  current_dir->entries[free_slot] = *new_entry;
  memcpy((void*) filesystem + (current_dir_initial_block * BLOCK_SIZE), (void*) current_dir, BLOCK_SIZE);

  /* Allocate entries in FAT and its memory_bitmap (logically allocating the file)
   * We aren't allocating physical data into the filesystem */
  if (allocate_n_fat_slots(sectors_needed, fat_initial_index) == 0) {
    fprintf(stdout, "[DEBUG] File allocated\n");
    return 0;
  } else {
    fprintf(stderr, "[ERROR] Can't allocate file\n");
    return -4;
  }

}

int add_directory(directory* current_dir, int current_dir_initial_block, char* new_dir_name) {
  uint8_t free_slot;

  if (get_duplicate_name_in_directory(current_dir, new_dir_name)) {
    fprintf(stderr, "[ERROR] Duplicated name found %s\n", new_dir_name);
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

int print_directory(directory* dir) {
  int total_directory_size = 0;
  int total_number_files = 0;
  int total_number_dirs = 0;

  /* for each VALID file_entry in dir, print it */
  int i = 0;
  for (i = 0; i < MAX_FILE_ENTRIES; i++) {
    file_entry* fe = &dir->entries[i];
    /* filestamp is our validation */
    if (fe->timestamp != 0) {
      print_file_entry(fe);
      if (fe->is_directory == 1) total_number_dirs++;
      if (fe->is_directory == 0) {
        total_number_files++;
        total_directory_size += fe->file_size;
      }
    }
  }
  fprintf(stdout,"\n \t\t\t %d File(s) \t \t \t %d bytes\n ", total_number_files, total_directory_size );
  fprintf(stdout,"\t\t\t %d Dir(s) \t \t \t %d bytes free\n", total_number_dirs, get_total_free_space_in_bytes() );
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

int allocate_n_fat_slots(int number_sector_to_allocate, int initial_fat_index) {
  /* validation */
  if (memory_bitmap[initial_fat_index] == 1) {
    fprintf(stderr, "[ERROR] Initial_fat_index already in use");
    return -3;
  }
  if (number_sector_to_allocate < 0) {
    fprintf(stderr, "[ERROR] Invalid value in 'allocate_n_fat_slots'");
    return -2;
  }
  if (number_sector_to_allocate > get_total_free_space_in_sectors()) {
    fprintf(stderr, "[ERROR] Insufficient free sectors in FAT");
    return -1;
  }

  /* allocating */
  int remaining_sectors = number_sector_to_allocate;
  int current_index = initial_fat_index;

  for (; remaining_sectors > 0; remaining_sectors--) {

    /* set that sector to 'busy' */
    memory_bitmap[current_index] = 1;

    /* if it's the last sector to allocate */
    if (remaining_sectors == 1) {
      fprintf(stdout, "[DEBUG] Allocating n=%d, FAT[%d] = %d, ", remaining_sectors, current_index, file_allocation_table[current_index]);
      file_allocation_table[current_index] = -1;
      return 0;
    } else {
      file_allocation_table[current_index] = get_first_fat_available();
      fprintf(stdout, "[DEBUG] Allocating n=%d, FAT[%d] = %d, ", remaining_sectors, current_index, file_allocation_table[current_index]);
      current_index = get_first_fat_available();
    }

  }
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

int set_fat_by_index(int index, int value) {
  memory_bitmap[index] = 1;
  file_allocation_table[index] = value;
  return 0;
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

void print_map_sec() {
  fprintf(stdout, "[DEBUG] FAT SECTOR MAP:\n");
  int chunk_size = 32, chunk_counter = 0;
  fprintf(stdout, "\t0\t: ");
  for (int count = 0; count < SECTOR_NUMBER; count++) {
    if (memory_bitmap[count] == 1) {
      fprintf(stdout, "x");
    } else {
      fprintf(stdout, "-");
    }
    chunk_counter++;
    /* tabulating the graph */
    if (chunk_counter == chunk_size && !(count == SECTOR_NUMBER-1)) {
        fprintf(stdout, "\n\t%d\t: ", count);
        chunk_counter = 0;
    }
  }

  fprintf(stdout, "\n[LEGEND] 'x': used sector, '-': free sector\n");
}

void print_fat() {
  fprintf(stdout, "[DEBUG] Printing fat allocated sector:\n");
  for (int count = 0; count < SECTOR_NUMBER; count++) {
    if (file_allocation_table[count] != -1) {
      fprintf(stdout, "fat[%d]: %d | ",count, file_allocation_table[count]);
    }
  }
}

int get_next_fat_index(int fat_index) {
  if (fat_index > SECTOR_NUMBER -1 || fat_index < -1) {
    fprintf(stderr, "[ERROR] Unexpected behaviour!! fat_index out-of bounds!");
    return -2;
  }

  return file_allocation_table[fat_index];
}

