#include <iostream>
#include <string>
#include <tchar.h>

#include "XGetopt.h"
#include "Tilandis.h"
#include "exceptions.h"

bool Tilandis::AddToRegistry = false;
std::string Tilandis::LinkName = "";
std::string Tilandis::PathName = "";
std::string Tilandis::Args = "";
std::string Tilandis::WorkingDirectory = "";
std::string Tilandis::RegistryProtocolName = "";
bool Tilandis::CreateMode = false;
bool Tilandis::DeleteMode = false;
bool Tilandis::ForceLink = false;

bool Tilandis::UsingCommandLine(int argc, TCHAR *argv[]) {
	int curarg;

	if (argc < 3) { // 1 = "tilandis.exe", 2 = "tilandis.exe tilecreator:example"
		return false;
	}

	while ((curarg = getopt(argc, argv, _T("a:d:fn:p:r:w:"))) != EOF) {
		switch (curarg) {
		case _T('a'):
			Tilandis::Args = optarg;
			break;
		case _T('w'):
			Tilandis::WorkingDirectory = optarg;
			break;
		case _T('d'):
			Tilandis::DeleteMode = true;
			Tilandis::LinkName = optarg;
			break;
		case _T('n'):
			Tilandis::CreateMode = true;
			Tilandis::LinkName = optarg;
			break;
		case _T('p'):
			Tilandis::PathName = optarg;
			break;
		case _T('r'):
			Tilandis::AddToRegistry = true;
			Tilandis::RegistryProtocolName = optarg;
			break;
		case _T('f'):
			Tilandis::ForceLink = true;
		case _T('?'):
			throw Tilandis::Exceptions::BadArgCombo;
		default:
			Tilandis::PrintUsage();
			exit(1);
		}
	}
	return true; // If there was a problem it would have returned false by now
}