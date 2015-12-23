#include <iostream>
#include <string>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

#include "getopt.c"
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

bool Tilandis::UsingCommandLine(int argc, wchar_t* argv[]) {
	int curarg;

	if (argc < 3) { // 1 = "tilandis.exe", 2 = "tilandis.exe tilecreator:example"
		return false;
	}

	static struct option long_options[] =
	{
		{ L"args", ARG_REQ, 0, L'a' },
		{ L"newlink", ARG_REQ, 0, L'n' },
		{ L"delete", ARG_REQ, 0, L'd' },
		{ L"force", ARG_REQ, 0, L'f' },
		{ L"path", ARG_REQ, 0, L'p' },
		{ L"register", ARG_REQ, 0, L'r' },
		{ L"workdir", ARG_REQ, 0, L'w' },
	};

	bool StillGoing = true;
	int optindex = 0;
	const wchar_t* optstring = L"a:d:fn:p:r:w:";
	while (StillGoing) {
		curarg = getopt_long(argc, argv, optstring, long_options, &optindex);

		if (curarg == -1) {
			StillGoing = false;
		}
		switch (curarg) {
			case L'a':
				Tilandis::Args = *optarg;
				break;
			case L'w':
				Tilandis::WorkingDirectory = *optarg;
				break;
			case L'd':
				Tilandis::DeleteMode = true;
				Tilandis::LinkName = *optarg;
				break;
			case L'n':
				Tilandis::CreateMode = true;
				Tilandis::LinkName = *optarg;
				break;
			case L'p':
				Tilandis::PathName = *optarg;
				break;
			case L'r':
				Tilandis::AddToRegistry = true;
				Tilandis::RegistryProtocolName = *optarg;
				break;
			case L'f':
				Tilandis::ForceLink = true;
			case L'?':
				throw Tilandis::Exceptions::BadArgCombo;
			default:
				Tilandis::PrintUsage();
				exit(1);
		}
	}
	return true; // If there was a problem it would have returned false by now
}