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

void initialize_fs() {
  // TODO: setup boot sector
  /* The boot sector itself is a reserved space, the only thing that
   * we are going to do there is to allocate the root directory
   * (even that won't be really needed) */

  // TODO: setup filesystem itself
  /* Filesystem is instantiated globally in main.c
   * using it like a sort of singleton
   * thought about that? */

  // setup root directory
  set_root_directory();
}

file_entry* make_file_entry(char* name, uint16_t file_size, int initial_block, int is_directory) {
  file_entry* entry = (file_entry*) malloc(sizeof(file_entry*));
  // TODO: make a name validation
  strncpy(entry->file_name, name, sizeof(&name));
  entry->is_directory = (uint8_t) is_directory;
  entry->file_size = (uint16_t) file_size;
  entry->initial_block = (uint8_t) initial_block;
  entry->timestamp = (uint32_t) time(NULL);
  return entry;
}

void nullify_path_matrix(char matrix[MAX_DIRECTORY_SUBLEVELS][MAX_FILE_NAME_SIZE]) {
  int i = 0, j = 0;

  for (i = 0; i < MAX_DIRECTORY_SUBLEVELS; i++) {
    for (j = 0; j < MAX_FILE_NAME_SIZE; j++) {
      matrix[i][j] = NULL;
    }
  }
}

int make_directory(char* path) {
  char parsed_path[MAX_DIRECTORY_SUBLEVELS][MAX_FILE_NAME_SIZE];
  nullify_path_matrix(parsed_path);

  int path_levels = parse_path(path, parsed_path);

  if (path_levels > 0) {
    int i = 0;
    directory* current_directory = get_root_directory();
    int current_directory_initial_block = 0;

    /* path verification */
    while (i < path_levels) {
      if (i != (path_levels - 1) && get_directory(current_directory, &current_directory_initial_block, parsed_path[i])) {
        fprintf(stderr, "[ERROR] Directory %s does not exist!\n", parsed_path[i]);
        return -1;
      }
      i++;
    }

    add_directory(current_directory, current_directory_initial_block, parsed_path[i - 1]);
  }

  return 0;
}

int make_file(char* path, int file_size) {
  char parsed_path[MAX_DIRECTORY_SUBLEVELS][MAX_FILE_NAME_SIZE];
  nullify_path_matrix(parsed_path);

  int path_levels = parse_path(path, parsed_path);

  if (path_levels > 0) {
    int i = 0;
    directory* current_directory = get_root_directory();
    int current_directory_initial_block = 0;

    /* path verification */
    while (i < path_levels) {
      if (i != (path_levels - 1) && get_directory(current_directory, &current_directory_initial_block, parsed_path[i])) {
        fprintf(stderr, "[ERROR] Directory %s does not exist!\n", parsed_path[i]);
        return -1;
      }
      i++;
    }

    /* if file cannot be added */
    if(add_file(current_directory, current_directory_initial_block, parsed_path[i - 1], file_size) == 0) {
      fprintf(stdout, "[DEBUG] Creating file %s with size %d\n", parsed_path[i - 1], file_size);
    } else {
      fprintf(stderr, "[ERROR] File %s cannot be created!\n", parsed_path[i - 1]);
      return -3;
    }
  }

  return 0;
}

int list_dir(char* path) {
  char parsed_path[MAX_DIRECTORY_SUBLEVELS][MAX_FILE_NAME_SIZE];
  nullify_path_matrix(parsed_path);

  int path_levels = parse_path(path, parsed_path);

  if (path_levels >= 0) {
    int i = 0;
    directory* current_directory = get_root_directory();
    int current_directory_initial_block = 0;

    /* path verification */
    while (i < path_levels) {
      if (get_directory(current_directory, &current_directory_initial_block, parsed_path[i])) {
        fprintf(stderr, "[ERROR] Directory %s does not exist!\n", parsed_path[i]);
        return -1;
      }
      i++;
    }

    fprintf(stdout, "Directory of ~/%s\n", path);
    print_directory(current_directory);
  }

  return 0;
}

int parse_path(char* path, char output_path_parsed[MAX_DIRECTORY_SUBLEVELS][MAX_FILE_NAME_SIZE]) {
  int count = 0;
  char* token;

  token = strtok(path, SLASH_SEPARATOR);

  while (token != NULL) {
    if (strlen(token) > MAX_FILE_NAME_SIZE) {
      fprintf(stderr, "[ERROR] %s %s\n", token, "exceeds the file name size permitted!");
      return -1;
    }

    strcpy(output_path_parsed[count], token);
    count++;

    if (count > MAX_DIRECTORY_SUBLEVELS) {
      fprintf(stderr, "[ERROR] %s\n", "The maximum number of sub-directories is eight!");
      return -1;
    }

    token = strtok(NULL, SLASH_SEPARATOR);
  }

  return count;
}

void print_file_entry(file_entry* fe) {
  if (fe->is_directory) {
    fprintf(stdout, "%s \t <DIR> \t \t \t %s \n",
            timestamp_to_string(fe->timestamp), fe->file_name);
  } else {
    fprintf(stdout, "%s \t \t \t %u \t %s \n",
            timestamp_to_string(fe->timestamp), fe->file_size, fe->file_name);
  }
}

char* timestamp_to_string(uint32_t timestamp) {
  time_t raw_time = timestamp;
  /* removing '\n' */
  char* output_string = ctime(&raw_time);
  return strtok(output_string, "\n");
}

int get_total_free_space_in_bytes() {
  return get_total_free_space_in_sectors() * BLOCK_SIZE;
}

//TODO:
int get_total_free_space_in_sectors() {
  int i, free_sector_count = 0;
  for (i = 0; i < SECTOR_NUMBER; i++){
    if (memory_bitmap[i] == 0) {free_sector_count++;}
  }
  return free_sector_count;
}
