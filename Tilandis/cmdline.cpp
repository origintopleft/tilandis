#include <iostream>
#include <string>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

#include "Tilandis.h"
#include "exceptions.h"

bool Tilandis::AddToRegistry = false;
std::wstring Tilandis::LinkName = L"";
std::wstring Tilandis::PathName = L"";
std::wstring Tilandis::Args = L"";
std::wstring Tilandis::WorkingDirectory = L"";
std::wstring Tilandis::RegistryProtocolName = L"";
bool Tilandis::CreateMode = false;
bool Tilandis::DeleteMode = false;
bool Tilandis::ForceLink = false;
bool Tilandis::LinkInAdminMode = false;

tristate Tilandis::UsingCommandLine(int argc, wchar_t* argv[]) {
	if (argc < 3) { // 1 = "tilandis.exe", 2 = "tilandis.exe tilecreator:example"
		return False;
	}
	else {
		wchar_t curflag;
		bool lookingforarg = false;
		std::wstring curargstr; // shorthand for developer convenience. the compiler will probably optimize this one away
		for (int curarg = 1; curarg < argc; curarg++) {
			curargstr = argv[curarg];
			if (lookingforarg) {
				if (curargstr[0] == L'-') {
					throw Tilandis::Exceptions::MissingArg;
					return False;
				}

				std::wstring resultarg = argv[curarg];
				switch (curflag) {
				case L'n': // -n
					Tilandis::CreateMode = true;
					Tilandis::LinkName = resultarg;
					break;
				case L'a': // -a
					Tilandis::Args = resultarg;
					break;
				case L'p':
					Tilandis::PathName = resultarg;
					break;
				case L'w': // -w
					Tilandis::WorkingDirectory = resultarg;
					break;
				case L'd': // -d
					Tilandis::DeleteMode = true;
					Tilandis::LinkName = resultarg;
					break;
				case L'r':
					Tilandis::AddToRegistry = true;
					Tilandis::RegistryProtocolName = resultarg;
					break;
				}
				lookingforarg = false;
			}
			else {
				if (curargstr[0] != L'-') {
					throw Tilandis::Exceptions::MissingArg;
					return False;
				}
				switch (curargstr[1]) {
				case L'f':
					Tilandis::ForceLink = true;
					break;
				case L'A':
					Tilandis::LinkInAdminMode = true;
					break;
				case L'n':
					curflag = L'n';
					lookingforarg = true;
					break;
				case L'a':
					curflag = L'a';
					lookingforarg = true;
					break;
				case L'p':
					curflag = L'p';
					lookingforarg = true;
					break;
				case L'w':
					curflag = L'w';
					lookingforarg = true;
					break;
				case L'd':
					curflag = L'd';
					lookingforarg = true;
					break;
				case L'r':
					curflag = L'r';
					lookingforarg = true;
					break;
				default:
					std::wcout << "Unrecognized argument: " << curargstr << std::endl;
					Tilandis::PrintUsage(argv[0]);
					return False;
				}
			}
		}
	}
	return False; // If there was a problem it would have returned false by now
}