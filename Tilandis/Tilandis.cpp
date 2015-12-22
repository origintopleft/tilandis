/*
 * Tilandis
 * by Nicholas "Lavacano" O'Connor
 * Purpose: I'll make my own TileCreator proxy! With blackjack! And hookers!
 */

// Standard headers
#include <iostream>
#include <string>
#include <fstream>
#include <tchar.h>
#include <Windows.h>

// Third party headers
#include "XGetopt.cpp"

// Tilandis code
#include "Tilandis.h"
#include "exceptions.h"

int main() {
	if (!Tilandis::Links::PrepareTheLinkDocument()) {
		std::cerr << "Failed to prepare the link document." << std::endl;
		return 1;
	}
	if (Tilandis::UsingCommandLine(__argc, __argv)) { // FIXME: Commandline processing, while it works, is extremely friggin weird because I wrote it stoned
		try {
			if (Tilandis::DeleteMode && Tilandis::CreateMode) { throw Tilandis::Exceptions::BadArgCombo; }
			if (Tilandis::DeleteMode) { Tilandis::Links::DeleteLink(); }
			if (Tilandis::CreateMode) { Tilandis::Links::CreateLink(); }
			if (Tilandis::AddToRegistry) { Tilandis::RegisterProtocol(); }
		}
		catch (Tilandis::Exceptions::BadCommandLine exc) {
			std::cerr << exc.what() << std::endl;
			return 1;
		}
	}
	else {
		if (__argc == 1) {
			Tilandis::PrintUsage();
		}
		else if (__argc == 2) {
			std::string LinkName = __argv[1];
			size_t pos;
			if ((pos = LinkName.find(":")) != std::string::npos) { // if we FIND a colon
				LinkName.erase(0, pos + 1); // Remove protocols from the beginning
			}
			if (!Tilandis::Links::LaunchLink(LinkName.c_str())) {
				std::ofstream err;
				err.open("tilandis.err");
				err << LinkName;
			}
		}
	}
	
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
	std::cout << "\t-f :: Replace any existing link with the same name. (Mnemonic: \"force\")" << std::endl;
}

bool Tilandis::RegisterProtocol() {
	HKEY registry;
	DWORD regresult;
	long WINAPI result = RegCreateKeyEx(HKEY_CLASSES_ROOT, Tilandis::RegistryProtocolName.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &registry, &regresult);
	if (regresult == REG_OPENED_EXISTING_KEY) { std::cout << "note: this protocol's already registered with something"; }
	return true;
}