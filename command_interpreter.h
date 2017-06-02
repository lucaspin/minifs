/**
 * MINIFS - Mini File System
 *
 * This is an educational project for the OS-II class on Sao Paulo State University - UNESP.
 * Authors: Dalton Lima @daltonbr
 *          Lucas Pinheiros @lucaspin
 * https://github.com/lucaspin/minifs
 * command_interpreter.h
 */

#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// #define statements
/////////////////////////////////////////////////////////////////////////////

#define MKDIR_COMMAND "mkdir"
#define MKFILE_COMMAND "mkfile"
#define RMDIR_COMMAND "rmdir"
#define LISTDIR_COMMAND "listdir"
#define SHOWSEC_COMMAND "showsec"
#define MAPSEC_COMMAND "mapsec"
#define DIRTREE_COMMAND "dirtree"
#define HELP_COMMAND "help"
#define EXIT_COMMAND "exit"
#define COMMAND_DELIMITER " "

// TODO: need to calculate this properly
#define MAX_COMMAND_LENGTH 100
#define MAX_PATH_LENGTH 72

/////////////////////////////////////////////////////////////////////////////
// Structures
/////////////////////////////////////////////////////////////////////////////

typedef enum {
  MKDIR,
  MKFILE,
  RMDIR,
  LISTDIR,
  SHOWSEC,
  MAPSEC,
  DIRTREE,
  HELP,
  EXIT
} command_type;

typedef struct action_t {
  command_type cmd;
  char path[MAX_PATH_LENGTH];
  int file_size;
} action_t;

/////////////////////////////////////////////////////////////////////////////
// functions
/////////////////////////////////////////////////////////////////////////////

/**
 * Expect the input from user, and parse it.
 * @return a action_t object containing all the information about the action.
 */
action_t* get_action_from_user();

/**
 * TODO: Re-do this in a more general way
 * Strip line endings from the command.
 * @param typed_command
 */
void strip_line_endings(char* command);

/**
 * Parse the typed action from user, and transforms it into a action_t object
 * @param   typed_action
 * @return  an action_t object containing all the information about the action.
 */
action_t* parse_action(char* action);

/**
 * Check if an action contains a valid command.
 * @param   command
 * @param   action
 * @return  TRUE if valid command, FALSE otherwise.
 */
int check_command(char* command, action_t* action);

int get_filesize();
char* get_filename();
int check_no_more_arguments();
void show_help();

#endif