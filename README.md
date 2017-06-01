### minifs

This is an educational project for the OS-II class on Sao Paulo State University - UNESP.

#### Requirements

[ ] Simulate a disk with 256 sectors of 512 bytes. The first 10 sectors will be reserved for the boot sector, the filesystem itself and the root directory; the ones can be used for user files.

[ ] Allow file allocation in a non-contiguous manner. Suggestion: use a block allocation table and a bitmap to manage the free space.

[ ] Allow directory and sub-directory creation with the command `mkdir`, until a maximum of 8 levels. Each directory can contain several sub-directories. Each directory/sub-directory occupies one sector of the disk.

[ ] Allow file creation inside the directories and sub-directories with the command `mkfile`. Each directory can contain several files. When creating a file, its size must be specified (size in bytes), and disk sectors must be allocated accordingly. File names must be unique inside a directory/sub-directory.

[ ] Allow directory/sub-directory deletion with the command `rmdir`. Empty directories can't be deleted.

[ ] list the files and sub-directories with the command `listdir`. On the list:

  * directories must indicate that they are directories
  * files must show size, time and creation date
  * In the end, it must appear: the total number of files and directories, the total size of files and directories and the amount of free disk space.


[ ] `showsec` command to indicate which sectors are occupied by some file.

[ ] `mapsec` command to show the free and occupied sectors of the disk

[ ] `dirtree` command to show the filesystem tree of directories

[ ] `help` command to show the available commands

[ ] `exit` command to exit the program

#### Authors
 * Dalton Lima @daltonbr
 * Lucas Pinheiros @lucaspin
