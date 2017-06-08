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
  action_t* action = (action_t*) malloc(sizeof(action_t));
  initiate_fs();

//  printf("[DEBUG] sizeof pointer: %d\n", sizeof(char*));
//  printf("[DEBUG] sizeof directory: %d\n", sizeof(directory));
//  printf("[DEBUG] sizeof file_entry: %d\n", sizeof(file_entry));

  do {
    do {
      action = get_action_from_user();
    } while (action == NULL);

    switch (action->cmd) {
      case MKDIR:
        fprintf(stdout, "%s\n", MKDIR_COMMAND);
        // TODO:
        make_directory(action->path);
        break;
      case MKFILE:
        fprintf(stdout, "%s\n", MKFILE_COMMAND);
        // TODO:
        break;
      case RMDIR:
        fprintf(stdout, "%s\n", RMDIR_COMMAND);
        // TODO
        break;
      case LISTDIR:
        fprintf(stdout, "%s\n", LISTDIR_COMMAND);
        // TODO
        break;
      case SHOWSEC:
        fprintf(stdout, "%s\n", SHOWSEC_COMMAND);
        // TODO
        break;
      case MAPSEC:
        fprintf(stdout, "%s\n", MAPSEC_COMMAND);
        // TODO
        break;
      case DIRTREE:
        fprintf(stdout, "%s\n", DIRTREE_COMMAND);
        // TODO
        break;
      case HELP:
        show_help();
        break;
      case CLEAR:
        fprintf(stdout, "%s\n", CLEAR_COMMAND);
        // TODO
        break;
      case EXIT:
        fprintf(stdout, "%s\n", EXIT_COMMAND);
        fprintf(stdout, "%s\n", "Bye!\n");
        break;
    }
  } while (action->cmd != EXIT);

  return 0;
}