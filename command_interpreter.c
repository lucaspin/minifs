#include "command_interpreter.h"

action_t* get_action_from_user() {
  char typed_command[MAX_COMMAND_LENGTH];

  fprintf(stdout, "%s", "== Type your command > ");
  fgets(typed_command, MAX_COMMAND_LENGTH, stdin);
  strip_line_endings(typed_command);

  return parse_action(typed_command);
}

void strip_line_endings(char* typed_command) {
  int length = strlen(typed_command);
  if (typed_command[length - 1] == '\n') {
    typed_command[length - 1] = '\0';
  }
}

action_t* parse_action(char* typed_action) {
  action_t* action = (action_t*) malloc(sizeof(action_t));
  const char delimiter[2] = " ";
  char* token = strtok(typed_action, delimiter);

  if (check_command(token, action)) {
    return action;
  } else {
    fprintf(stderr, "%s\n", "I'm sorry, my friend, but this isn't a valid command!\n");
    // TODO: show help menu
    return NULL;
  }
}

int check_command(char* command, action_t* action) {
  if (!strcmp(command, MKDIR_COMMAND)) {
    // TODO: Get path
    action->file_size = 0;
    action->cmd = MKDIR;
  } else if (!strcmp(command, MKFILE_COMMAND)) {
    // TODO: Get path
    // TODO: Get file size
    action->cmd = MKFILE;
  } else if (!strcmp(command, RMDIR_COMMAND)) {
    // TODO: Get path
    action->path = NULL;
    action->cmd = RMDIR;
  } else if (!strcmp(command, LISTDIR_COMMAND)) {
    // TODO: Get path
    action->cmd = LISTDIR;
    action->file_size = 0;
  } else if (!strcmp(command, SHOWSEC_COMMAND)) {
    action->cmd = SHOWSEC;
    action->path = NULL;
    action->file_size = 0;
  } else if (!strcmp(command, MAPSEC_COMMAND)) {
    action->cmd = MAPSEC;
    action->path = NULL;
    action->file_size = 0;
  } else if (!strcmp(command, DIRTREE_COMMAND)) {
    action->cmd = DIRTREE;
    action->path = NULL;
    action->file_size = 0;
  } else if (!strcmp(command, HELP_COMMAND)) {
    action->cmd = HELP;
    action->path = NULL;
    action->file_size = 0;
  } else if (!strcmp(command, EXIT_COMMAND)) {
    action->cmd = EXIT;
    action->path = NULL;
    action->file_size = 0;
  } else {
    return 0;
  }

  return 1;
}