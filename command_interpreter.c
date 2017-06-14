/**
 * MINIFS - Mini File System
 *
 * This is an educational project for the OS-II class on Sao Paulo State University - UNESP.
 * Authors: Dalton Lima @daltonbr
 *          Lucas Pinheiros @lucaspin
 * https://github.com/lucaspin/minifs
 * command_interpreter.c
 */

#include "command_interpreter.h"
#include "filesystem.h"

action_t* get_action_from_user() {
  char typed_command[MAX_COMMAND_LENGTH];

  fprintf(stdout, "%s", "== Type your command > ");
  fflush(stdout);

  fgets(typed_command, MAX_COMMAND_LENGTH, stdin);
  strip_line_endings(typed_command);

  return parse_action(typed_command);
}

void strip_line_endings(char* typed_command) {
  size_t length = strlen(typed_command);
  if (typed_command[length - 1] == '\n') {
    typed_command[length - 1] = '\0';
  }
}

action_t* parse_action(char* typed_action) {
  action_t* action = (action_t*) malloc(sizeof(action_t));
  char* token = strtok(typed_action, COMMAND_DELIMITER);

  if (check_command(token, action)) {
    return action;
  } else {
    return NULL;
  }
}

char* get_filename() {
  char* filename = strtok(NULL, COMMAND_DELIMITER);
  return filename;
}

int get_filesize() {
  char* file_size = strtok(NULL, COMMAND_DELIMITER);
  char* string_after_number;
  long int value = strtol(file_size, &string_after_number, 10);

  if (value <= 0) {
    fprintf(stderr, "\n%s\n", "[ERROR] This isn't a valid file size! It must be a positive integer value!");
    return NULL;
  }

  return (int) value;
}

int check_no_more_arguments() {
  if (strtok(NULL, COMMAND_DELIMITER) != NULL) {
    fprintf(stderr, "\n%s\n\n", "[ERROR] Too many arguments!");
    return 0;
  }

  return 1;
}

int check_command(char* command, action_t* action) {
  if (!strcmp(command, MKDIR_COMMAND)) {
    action->file_size = 0;
    action->cmd = MKDIR;

    char* filename = get_filename();
    if (filename != NULL) {
      strcpy(action->path, filename);
    } else {
      fprintf(stderr, "\n%s\n", "[ERROR] You must specify a directory name!");
      return 0;
    }

  } else if (!strcmp(command, MKFILE_COMMAND)) {
    action->cmd = MKFILE;

    char* filename = get_filename();
    if (filename != NULL) {
      strcpy(action->path, filename);
    } else {
      fprintf(stderr, "\n%s\n", "[ERROR] You must specify a file name!");
      return 0;
    }

    int file_size = get_filesize();
    if (file_size != NULL) {
      action->file_size = file_size;
    } else {
      return 0;
    }
  } else if (!strcmp(command, RMDIR_COMMAND)) {
    action->cmd = RMDIR;
    action->file_size = 0;

    char* filename = get_filename();
    if (filename != NULL) {
      strcpy(action->path, filename);
    } else {
      fprintf(stderr, "\n%s\n", "[ERROR] You must specify a directory name!");
      return 0;
    }
  } else if (!strcmp(command, LISTDIR_COMMAND)) {
    action->cmd = LISTDIR;
    action->file_size = 0;

    char* filename = get_filename();
    if (filename != NULL) {
      strcpy(action->path, filename);
    }
  } else if (!strcmp(command, SHOWSEC_COMMAND)) {
    action->cmd = SHOWSEC;
    action->file_size = 0;

    char* filename = get_filename();
    if (filename != NULL) {
      strcpy(action->path, filename);
    } else {
      fprintf(stderr, "\n%s\n", "[ERROR] You must specify a file name!");
      return 0;
    }
  } else if (!strcmp(command, MAPSEC_COMMAND)) {
    action->cmd = MAPSEC;
    strcpy(action->path, "");
    action->file_size = 0;
  } else if (!strcmp(command, DIRTREE_COMMAND)) {
    action->cmd = DIRTREE;
    strcpy(action->path, "");
    action->file_size = 0;
  } else if (!strcmp(command, HELP_COMMAND)) {
    action->cmd = HELP;
    strcpy(action->path, "");
    action->file_size = 0;
  } else if (!strcmp(command, EXIT_COMMAND)) {
    action->cmd = EXIT;
    strcpy(action->path, "");
    action->file_size = 0;
  } else {
    fprintf(stderr, "\n%s\n", "[ERROR] Invalid command! Type 'help' for a list of commands!\n");
    // TODO: show help menu
    return 0;
  }

  return check_no_more_arguments();
}

void show_help() {
  fprintf(stdout, "\t%s\n", "Commands:");
  fprintf(stdout, "\t\t%s %s - %s\n", MKDIR_COMMAND, "<path_name>", "Create a directory");
  fprintf(stdout, "\t\t%s %s - %s\n", MKFILE_COMMAND, "<path_name> <file_size>", "Create a file");
  fprintf(stdout, "\t\t%s %s - %s\n", RMDIR_COMMAND, "<path_name>", "Remove a directory");
  fprintf(stdout, "\t\t%s %s - %s\n", LISTDIR_COMMAND, "<path_name>", "List the contents of a directory");
  fprintf(stdout, "\t\t%s %s - %s\n", SHOWSEC_COMMAND, "<path_name>", "Show the sectors that a file occupies");
  fprintf(stdout, "\t\t%s - %s\n", MAPSEC_COMMAND, "Show the sector map for all the filesystem");
  fprintf(stdout, "\t\t%s - %s\n", DIRTREE_COMMAND, "Show the directory tree");
  fprintf(stdout, "\t\t%s - %s\n", HELP_COMMAND, "Help! But if you are here, you don't really needed this disclaimer =) !");
  fprintf(stdout, "\t\t%s - %s\n", EXIT_COMMAND, "Exit the filesystem CLI");
}