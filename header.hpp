/************************************************************************************
 * main.cpp       --       by: JoelG(joelg@naples.net)        --        Sep 4, 1999 *
 *----------------------------------------------------------------------------------*
 * This program is designed to search the specified directory for any ROM files,    *
 * load up a multiple choice list of all found files, and then allow the user to    *
 * load up (g|s)snes9x with the specified file.                                     *
 *----------------------------------------------------------------------------------*
 *	Copyright (C) 1999-2000 Joel Gerber (Read LICENSE for more information)	    *
 ************************************************************************************/

#include <iostream>
#include <vector>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

#define ever ;;
#define success EXIT_SUCCESS
#define failure EXIT_FAILURE

unsigned int choice;
signed int return_val, break_it;

char *fchoice;
char run_this[200];
char *args, *directory, *log_file, *argy[2000];
char *snes9x_exec = "snes9x";
char *prog_name = "csnes9x";
const char *version = "1.0.2";

vector <char *> rom_name;  // Declare the vector to hold the filenames in.
vector <char *> menu;      // Declare the vector to hold all menu items.
vector <char *> holder;

int Get_Files(char *directory);
inline int Print_Menu(void);
inline void Print_Help(char *command_arg);
inline void Print_Version(void);

#include "funcs.hpp" // Include file containing functions.
