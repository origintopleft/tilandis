#include <iostream>
#include <string>
#include <tchar.h>

#include "XGetopt.h"
#include "Tilandis.h"

bool Tilandis::AddToRegistry = false;
std::string Tilandis::LinkName = "";
std::string Tilandis::PathName = "";
std::string Tilandis::Args = "";
std::string Tilandis::WorkingDirectory = "";
bool Tilandis::DeleteMode = false;

bool Tilandis::UsingCommandLine(int argc, TCHAR *argv[]) {
	int curarg;

	if (argc == 1) { return false; }

	if (argc == 2 && __argv[1] != "-r") { return false; }

	while ((curarg = getopt(argc, argv, _T("a:d:n:p:rw:"))) != EOF) {
		switch (curarg) {
		case _T('a'):
			Tilandis::Args = optarg;
			break;
		case _T('w'):
			Tilandis::WorkingDirectory = optarg;
			break;
		case _T('d'):
			Tilandis::DeleteMode = true;
			break;
		case _T('n'):
			Tilandis::LinkName = optarg;
			break;
		case _T('p'):
			Tilandis::PathName = optarg;
			break;
		case _T('r'):
			Tilandis::AddToRegistry = true;
			break;
		default:
			Tilandis::PrintUsage();
			exit(1);
		}
	}
	return true; // If there was a problem it would have returned false by now
}