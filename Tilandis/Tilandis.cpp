/*
 * Tilandis
 * by Nicholas "Lavacano" O'Connor
 * Purpose: I'll make my own TileCreator proxy! With blackjack! And hookers!
 */

// Standard headers
#include <iostream>
#include <string>
#include <tchar.h>
#include <Windows.h>

// Third party headers
#include "XGetopt.cpp"

// Tilandis code
#include "Tilandis.h"

int main() {
	std::cout << "I don't actually do shit yet:  ";
	if (Tilandis::UsingCommandLine(__argc, __argv)) {
		if (!Tilandis::LinkName.empty()) { std::cout << "You're creating the link: " << Tilandis::LinkName << std::endl; }
		if (!Tilandis::PathName.empty()) { std::cout << "Your link will launch: " << Tilandis::PathName << std::endl; }
		if (!Tilandis::Args.empty()) { std::cout << "Your arguments are: " << Tilandis::Args << std::endl; }
		if (!Tilandis::WorkingDirectory.empty()) { std::cout << "Your working directory is: " << Tilandis::WorkingDirectory << std::endl; }
		if (Tilandis::AddToRegistry) { std::cout << "You would register Tilandis into the registry while we're at it."; }
	}
	else {
		if (__argc == 1) {
			Tilandis::PrintUsage();
		}
		else if (__argc == 2) { std::cout << "You would launch link: " << __argv[1] << std::endl; }
	}
	
	Sleep(5000);

	return 0;
}

void Tilandis::PrintUsage() {
	std::string myname = __argv[0];
	std::cout << "Usage for " << myname << ":" << std::endl;
	std::cout << '\t' << myname << " <link name> :: Launch a link" << std::endl;
	std::cout << '\t' << myname << " -n <link name> <options> :: Create a link" << std::endl;
	std::cout << '\t' << myname << " -d <link name> :: Delete a link" << std::endl;
	std::cout << std::endl; // separating blank line
	std::cout << "Options for -n include:" << std::endl;
	std::cout << "\t-p <pathname> :: Required. Path to thing to launch (accepts URLs)" << std::endl;
	std::cout << "\t-a <args> :: Arguments to pass to the program." << std::endl;
	std::cout << "\t-w <directory> :: The working directory to launch the program in. Defaults to the same as the file location." << std::endl;
}