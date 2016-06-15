/************************************************************************************
 * main.cpp       --       by: JoelG(joelg@naples.net)        --        Sep 4, 1999 *
 *----------------------------------------------------------------------------------*
 * This program is designed to search the specified directory for any ROM files,    *
 * load up a multiple choice list of all found files, and then allow the user to    *
 * load up (g|s)snes9x with the specified file.                                     *
 *----------------------------------------------------------------------------------*
 *	Copyright (C) 1999-2000 Joel Gerber (Read LICENSE for more information)	    *
 ************************************************************************************/

/*------------------------------------------------------------------------
   Uses scandir on the retrieved dir name, and puts all retrieved entries
   into a vector named rom_name, and then retrieves the ROM names from
   that vector and stores them in rom_name. Returns SUCCESS/FAILURE.
-------------------------------------------------------------------------*/
int Get_Files(char *directory) {
	struct dirent **namelist;
	int dir = scandir(directory, &namelist, 0, alphasort);
	if(dir < 0) { // Problem retrieving filenames from dir.
		perror(prog_name);
		return failure;
	} else
		while(dir--) // Scan through the list of filenames.
			rom_name.push_back(namelist[dir]->d_name); // Put the filename into an array.
	for(signed long int count = rom_name.size(); count != -1; count--) {
		if(rom_name[count] == '\0' || !strstr(rom_name[count], ".smc") &&
		   !strstr(rom_name[count], ".SMC") && !strstr(rom_name[count], ".FIG") &&
		   !strstr(rom_name[count], ".fig") && !strstr(rom_name[count]," .1") &&
		   !strstr(rom_name[count], ".zip") && !strstr(rom_name[count], ".ZIP"))
			continue;
		else
			menu.push_back(rom_name[count]); // Put the correct files in the menu array.
	}
	return success;
}

/*------------------------------------------------------------------------
   Prints out a menu containing all the found rom files in the specified
   directory.
-------------------------------------------------------------------------*/
inline int Print_Menu(void) {
	cout << "Type the number of the game you wish to start.\n";
	for(ulong menu_count = 1; menu_count != menu.size() + 1; menu_count++)
		cout << "(" << menu_count << ")\t" << menu[menu_count - 1] << endl;
	return success;
}

/*--------------------------------------
   Prints out simplistic Help Message.
--------------------------------------*/
inline void Print_Help(char *command_arg) {
	Print_Version();
	cout << "\nUsage " << command_arg << " [ options ]\n\n"
	     << "Options:\n"
	     << "  [--help]            Displays this Help Message.\n"
	     << "  [--version]         Displays Program Version.\n"
	     << "  [--directory] dir   Directory to search for ROMs in.\n"
	     << "  [--executable] exe  Name of the snes9x Executable you wish to use.\n"
	     << "  [--logfile] file    Name of the file to log snes9x errors to [/dev/null].\n\n"
	     << "Send any comments/criticisms to joelg@pentaventures.com or joelgg@onebox.com\n"
	     << "\"Christ Jesus came into the world to save sinners.\" (I Timothy 1:15)\n";
}

/*--------------------------------------
   Prints out the Version Information.
--------------------------------------*/
inline void Print_Version(void) {
	cout << "Snes9X ROM Launcher Version " << version << endl
	     << "This Software comes with ABSOLUTELY NO WARRANTY!\n"
	     << "Release under the GPL, read LICENSE for more information.\n";
}

/*----------------------------------------------------
   Prints out Usage Information for running program.
----------------------------------------------------*/
inline void Print_Usage(void) {
	cout << "Options:\n"
	     << "  [h]   Displays this Help Message.\n"
	     << "  [q]   Quits Program.\n"
	     << "  [l]   List ROM Images in Directory.\n"
	     << "  [int] Chooses ROM Image to Load.\n";
}
