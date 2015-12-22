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
	extern std::string LinkName;
	extern std::string PathName;
	extern std::string WorkingDirectory;
	extern std::string Args;

	extern bool AddToRegistry;
	extern std::string RegistryProtocolName;
	extern bool CreateMode;
	extern bool DeleteMode;
	extern bool ForceLink;

	extern std::string Err; // initialized in linkmgmt.cpp, theoretically settable anywhere

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
#endif //__TILANDIS_H