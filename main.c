#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "filesystem.h"
#include "command_interpreter.h"

#define TRUE 1;
#define FALSE 0;

char filesystem[SECTOR_NUMBER * BLOCK_SIZE];
extern int file_allocation_table;
extern int memory_bitmap;

int main() {
  action_t* action = (action_t*) malloc(sizeof(action_t));
  initiate_fs();

  do {
    do {
      action = get_action_from_user();
    } while (action == NULL);

    switch (action->cmd) {
      case MKDIR:
        fprintf(stdout, "%s\n", MKDIR_COMMAND);
        // TODO
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
      case EXIT:
        fprintf(stdout, "%s\n", EXIT_COMMAND);
        fprintf(stdout, "%s\n", "Bye!\n");
        break;
    }
  } while (action->cmd != EXIT);

  return 0;
}