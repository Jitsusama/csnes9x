/************************************************************************************
 * main.cpp       --       by: JoelG(joelg@naples.net)        --        Sep 4, 1999 *
 *----------------------------------------------------------------------------------*
 * This program is designed to search the specified directory for any ROM files,    *
 * load up a multiple choice list of all found files, and then allow the user to    *
 * load up (g|s)snes9x with the specified file.                                     *
 *----------------------------------------------------------------------------------*
 *	Copyright (C) 1999-2000 Joel Gerber (Read LICENSE for more information)	    *
 ************************************************************************************/

#include "header.hpp"

int main(int argc, char *argv[]) {
	rl_unbind_key('\t');	// Disable readline()'s file-name completion.
	prog_name = argv[0];	// Set prog_name to name of program.

	/* if snes9x rom dir variable is not set, use /roms/ */
	if(getenv("SNES96_ROM_DIR") == '\0')
		directory = "/roms/";
	else directory = getenv("SNES96_ROM_DIR");

	/* if snes9x executable variable is not set, use the default */
	if(getenv("SNES96_EXEC") == '\0')
		snes9x_exec = snes9x_exec;
	else snes9x_exec = getenv("SNES96_EXEC");

	/* if snes9x log file variable is not set, use /dev/null */
	if(getenv("SNES96_LOG_FILE") == '\0')
		log_file = "/dev/null";
	else log_file = getenv("SNES96_LOG_FILE");

	/* parse commandline args */
	for(int arg = 0; arg < argc; arg++) {
		for(uint p = 0; p < strlen(argv[arg]); p++) {
			if(argv[arg][p] == '-' && argv[arg][++p] == '-') {
				switch(argv[arg][p + 1]) {
					case 'h': // Help
						Print_Help(argv[0]);
						return success;
					case 'v': // Version
						Print_Version();
						return success;
					case 'd': // Directory
						directory = argv[arg + 1];
						break_it = 1;
						continue;
					case 'e': // Executable
						snes9x_exec = argv[arg + 1];
						break_it = 1;
						continue;
					case 'l': // Logging
						log_file = argv[arg + 1];
						break_it = 1;
						continue;
				}
			}
		}
		if(break_it == 1){ ++arg; break_it = 0; continue; }
		/* put extraneous args into the snes9x arg vector */
		else holder.push_back(argv[arg]);
	}

	if(!directory || Get_Files(directory) == failure) return failure;

	for(ever) { // Begin the entire hoopla!
		if(!menu.size()) {
			cerr << "No ROMS in dir (" << directory << ")\n";
			return failure;
		} else if(Print_Menu() == failure) return failure; // Print out ROMS.

		/* internal menuing system */
		choose: // Yes, this is a goto.
		cout << "Choose [1-" << menu.size() << "] or h for help: ";
		fchoice = readline('\0');

		switch(*fchoice) { // Options while program is running.
			case 'q': case 'Q': cout << "Exiting...\n";
					    free(fchoice);
					    return success;
			case 'h': case 'H': Print_Usage(); goto choose;
			case 'l': case 'L': Print_Menu();  goto choose;
			default: sscanf(fchoice, "%u", &choice);
		}

		if(choice > menu.size() || choice < 1) {
			ding(); // Cool ding effect for wrong choice.
			cerr << "Invalid choice!\n";
			goto choose;
		}

		sprintf(run_this, "%s%s", directory, menu[choice - 1]);

		/* the meat and potatoes of launching snes9x */
		int pid = fork();
		if(pid == 0) {
			argy[0] = snes9x_exec;	// Set executable as arg.
			argy[1] = run_this;	// Set rom name as arg.
			for(uint i = 2, j = 1;
				 i < holder.size() + 2 && j < holder.size();
				 i++, j++) argy[i] = holder[j];
			/* redirect snes9x's various messages to something else but stdout/err */
			freopen(log_file, "w", stdout);
			freopen(log_file, "w", stderr);
			/* start up snes9x with provided arguements. */
			return_val = execvp(snes9x_exec, argy);
			if(return_val == -1) {
				perror(prog_name);
				cerr << "Problem loading up " << snes9x_exec << "!\n"
				     << "Make sure it is located in your PATH variable!\n";
				free(fchoice);
				return failure;
			}
		}

		/* print out snes9x information */
		cout << snes9x_exec << " " << run_this << " ";
		for(uint loop = 1; loop < holder.size(); loop++)
			cout << holder[loop] << " ";
		cout << "started.\n";
		goto choose;
	}
}
