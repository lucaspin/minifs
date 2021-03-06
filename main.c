/**
 * MINIFS - Mini File System
 *
 * This is an educational project for the OS-II class on Sao Paulo State University - UNESP.
 * Authors: Dalton Lima @daltonbr
 *          Lucas Pinheiros @lucaspin
 * https://github.com/lucaspin/minifs
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//#include <unistd.h>
#include "filesystem.h"
#include "command_interpreter.h"
#include "file_allocation_table.h"

#define TRUE 1;
#define FALSE 0;

char filesystem[SECTOR_NUMBER * BLOCK_SIZE];
int file_allocation_table[SECTOR_NUMBER];
int memory_bitmap[SECTOR_NUMBER];

int main() {
  action_t* action;
  initialize_file_allocation_table();
  initialize_memory_bitmap();
  initialize_fs();

  do {
    do {
      action = get_action_from_user();
    } while (action == NULL);

    switch (action->cmd) {
      case MKDIR:
        make_directory(action->path);
        break;
      case MKFILE:
        make_file(action->path, action->file_size);
        break;
      case RMDIR:
        remove_directory_handler(action->path);
        break;
      case RMFILE:
        fprintf(stdout, "%s\n", RMFILE_COMMAND);
        // TODO
        break;
      case LISTDIR:
        list_dir(action->path);
        break;
      case SHOWSEC:
        print_sectors_used_by_file(action->path);
        break;
      case MAPSEC:
        print_map_sec();
        break;
      case DIRTREE:
        dirtree_handler();
        break;
      case HELP:
        show_help();
        break;
      case EXIT:
        fprintf(stdout, "%s\n", "Exiting file system...!\n");
        break;
    }
  } while (action->cmd != EXIT);

  return 0;
}