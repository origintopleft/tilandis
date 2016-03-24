#include "Tilandis.h"
#include "exceptions.h"

tristate Tilandis::ParseTileCTL(std::wstring ctlcmd) {
	ctlcmd.erase(0, 10); // erases "tilectl://"

	// TileCTL cliff notes:
	// tilectl://<command>/<link>?option=value&option=value
	// examples without tilectl:// prefix:
	// new/notepad?path=C:\Windows\notepad.exe&workdir=C:\Windows&args=C:\file.txt&admin=true
	// delete/notepad
	// "edit" and "launch" might happen, currently uncertain

	// This particular implementation moves through each part of the tilectl command by erasing the parts
	// it's already understood. This is not required by any standard, it just happens to be the easiest
	// thing for me to implement at the moment (plus I think it helps with memory management?)

	// command
	size_t slashpos = ctlcmd.find(L'/');
	std::wstring command = ctlcmd.substr(0, slashpos);
	ctlcmd.erase(0, slashpos + 1);

	// link name (and args, if we have them)
	bool hasargs;
	size_t questpos = ctlcmd.find(L'?');

	if (questpos != ctlcmd.npos) { // ? is present
		hasargs = true;
		Tilandis::LinkName = ctlcmd.substr(0, questpos);
		ctlcmd.erase(0, questpos + 1);

		// Count the args so we know how long the for loop is going to be
		// this enables the erase method so I don't have to think about the math
		size_t andpos = 0;
		int numargs = 0;
		while (true) {
			andpos = ctlcmd.find(L'&', andpos + 1);
			numargs++;
			if (andpos == ctlcmd.npos) {
				// out of &s
				break;
			}
		}

		for (int i = 0; i < numargs; i++) {
			andpos = ctlcmd.find(L'&');
			std::wstring curarg = ctlcmd.substr(0, andpos);

			size_t equalspos = curarg.find(L'=');
			std::wstring option = curarg.substr(0, equalspos);
			std::wstring value = curarg.substr(equalspos + 1, curarg.npos);

			if (option == L"path") { Tilandis::PathName = value; } else if (option == L"args") { Tilandis::Args = value; } else if (option == L"workdir") { Tilandis::WorkingDirectory = value; } else if (option == L"admin") {
				std::transform(value.begin(), value.end(), value.begin(), ::towlower); // lowercase string

				if (value == L"true") { Tilandis::LinkInAdminMode = true; }
			}

			ctlcmd.erase(0, andpos + 1);
		}
	} else {
		hasargs = false;
		Tilandis::LinkName = ctlcmd;
		ctlcmd.erase(0, ctlcmd.npos); // should empty the string
	}

	std::transform(command.begin(), command.end(), command.begin(), ::towlower); // lowercase string
	if (command == L"new") {
		if (!hasargs) {
			throw Tilandis::Exceptions::MissingArg;
			return False;
		} else if (Tilandis::LinkName == L"") {
			throw Tilandis::Exceptions::MissingArg;
			return False;
		} else if (Tilandis::PathName == L"") {
			throw Tilandis::Exceptions::MissingArg;
			return False;
		}

		Tilandis::CreateMode = true;
		return True;
	} else if (command == L"delete") {
		if (Tilandis::LinkName == L"") {
			throw Tilandis::Exceptions::MissingArg;
			return False;
		}

		Tilandis::DeleteMode = true;
		return True;
	}
}