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

int make_file_entry(char* name, uint16_t file_size, file_entry* output) {
  int index = get_first_fat_available();

  if(index != -1) {
    //TODO: add in the offset later, the 10 initial bytes reserved for the system
    int offset = index * BLOCK_SIZE;
    file_entry* entry = (file_entry*) malloc(sizeof(file_entry));
    //TODO: make a name validation
    strncpy(entry->file_name, name, sizeof(&name));
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

//TODO: instantiate a directory
int make_directory(char* path) {

  /* Parse the path */
  char* parsed_path = malloc (sizeof (char*) * (MAX_DIRECTORY_SUBLEVELS+1));
  printf("parsed_path malloc'ed size: %d \n", (sizeof (char*) * (MAX_DIRECTORY_SUBLEVELS+1)));
  //char** p_parsed_path = parsed_path;
  //*parsed_path = malloc(sizeof(char) * (MAX_DIRECTORY_SUBLEVELS+1) * (MAX_FILE_NAME_SIZE+1));
  int path_levels = parse_path(path, &parsed_path);

  int j = 0;
  int offset = j * sizeof(char*);
  while (parsed_path[offset] != NULL) {
    printf(" [DEBUG]Path[%d]: %s", j, parsed_path[offset]);
    j++;
  }

  /* max subdirectories verification */
  if (path_levels == -1) {
    printf("[ERROR] Exceeded number os subdirectories!\n");
    return -2;
  }

  /* getting root */
  directory* current_directory;
  get_root(current_directory);

  int i = 0;
  /* path verification */
  while (i+1 != path_levels) {
    if (get_directory(current_directory, &parsed_path[i])) {
      printf("[DEBUG] Directory %s found!\n", &parsed_path[i]);
    } else {
      printf("[ERROR] Directory %s not found!\n", &parsed_path[i]);
      return -1;
    }
    i++;
  }

  /* the directory to add */
  add_directory(current_directory, &parsed_path[i]);
  //TODO: add some errors verification

  return 0;
}

int parse_path(char* path, char** output_path_parsed) {
  int count = 0;
  char* token;

  //*output_path_parsed = malloc((MAX_FILE_NAME_SIZE+1) * (MAX_DIRECTORY_SUBLEVELS+1));
  token = strtok(path, SLASH_SEPARATOR);
  int offset = sizeof(char*) * count;
  //*output_path_parsed+offset = token;
  memcpy(*output_path_parsed+offset, token, sizeof(char*));
  //strcpy(*output_path_parsed[count], token);

  while(token != NULL) {
    token = strtok(NULL, SLASH_SEPARATOR);
    count++;
    if (count > MAX_DIRECTORY_SUBLEVELS) {
      return -1;
    }
    offset = sizeof(char*) * count;
    if (token) {
      memcpy(*output_path_parsed+offset, token, sizeof(char*));
    } else {
      *output_path_parsed[offset] = NULL;
    }
    //strcpy(*output_path_parsed[count], token);
  }
  return count;
}

//TODO: find if we have enough space to save a file, returning the first slot in fat if positive, and -1 if negative
//int has_space_in_fat_for_file(uint16_t file_size) {
//
//
//}

//int free_slots_in_fat() {
//
//}

void print_file_entry(file_entry* fe) {
  fprintf(stdout, "[DEBUG] file name: %s\n", fe->file_name);
  fprintf(stdout, "[DEBUG] is_directory: %d\n", fe->is_directory);
  fprintf(stdout, "[DEBUG] initial block: %u\n", fe->initial_block);
  fprintf(stdout, "[DEBUG] time stamp: %u\n", fe->timestamp);
}
