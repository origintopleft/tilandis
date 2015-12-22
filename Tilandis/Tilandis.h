#pragma once
#ifndef __TILANDIS_H
#define __TILANDIS_H
#include <string>
#include <tchar.h>
#include "rapidjson\document.h"
// Home namespace
namespace Tilandis {
	// TODO: tristates
	extern void PrintUsage();

	// cmdline.cpp
	extern bool UsingCommandLine(int argc, TCHAR *argv[]);
	extern std::wstring LinkName;
	extern std::wstring PathName;
	extern std::wstring WorkingDirectory;
	extern std::wstring Args;

	extern bool AddToRegistry;
	extern std::wstring RegistryProtocolName;
	extern bool CreateMode;
	extern bool DeleteMode;
	extern bool ForceLink;

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
		extern rapidjson::Document * LinkDocument;

		extern bool CreateLink(); // Will get info from the above variables
		extern bool DeleteLink();
		extern bool LaunchLink(const char *);

		extern bool PrepareTheLinkDocument();
		extern bool SaveLinkDocument();
	}

	extern bool RegisterProtocol();
}

extern std::wstring basedir(std::wstring);
#endif //__TILANDIS_H