#pragma once
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#ifndef __TILANDIS_H
#define __TILANDIS_H
// Standard headers
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <tchar.h>
#include <Windows.h>
#include "rapidjson\document.h"
#include "resource.h"
// Home namespace
namespace Tilandis {
	// TODO: tristates
	extern void PrintUsage(std::wstring);

	// cmdline.cpp
	extern bool UsingCommandLine(int argc, wchar_t* argv[]);
	extern std::wstring LinkName;
	extern std::wstring PathName;
	extern std::wstring WorkingDirectory;
	extern std::wstring Args;

	extern bool AddToRegistry;
	extern std::wstring RegistryProtocolName;
	extern bool CreateMode;
	extern bool DeleteMode;
	extern bool ForceLink;
	extern bool LinkInAdminMode;

	extern std::wstring BaseDirectory;

	extern std::wstring Err; // initialized in linkmgmt.cpp, theoretically settable anywhere

	namespace Exceptions { // exceptions.cpp
		class BadCommandLine;
		extern BadCommandLine MissingArg;
		extern BadCommandLine BadArgCombo;

		class BadLink;
		extern BadLink NoSuchLink;
		extern BadLink MissingFile;
		extern BadLink LaunchFailed;
	}
	namespace Links { // linkmgmt.cpp
		extern rapidjson::GenericDocument<rapidjson::UTF8<wchar_t>> * LinkDocument;

		extern bool CreateLink(); // Will get info from the above variables
		extern bool DeleteLink();
		extern bool LaunchLink(const wchar_t *);

		extern bool PrepareTheLinkDocument();
		extern bool SaveLinkDocument();
	}

	namespace GetOpt { // cmdline.cpp
		extern int a;
		extern int d;
		extern int f;
		extern int n;
		extern int p;
		extern int w;
		extern int r;
	}

	extern bool RegisterProtocol();
}

extern std::wstring basedir(std::wstring);
#endif //__TILANDIS_H