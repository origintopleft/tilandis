#pragma once
#ifndef __TILANDIS_H
#define __TILANDIS_H
#include <string>
#include <tchar.h>
#include "rapidjson\document.h"
// Home namespace
namespace Tilandis {
	// TODO: tristates
	extern bool UsingCommandLine(int argc, TCHAR *argv[]);
	extern void PrintUsage();

	extern bool CreateLink(); // Will get info from the below variables
	extern bool DeleteLink(); 

	extern std::string LinkName;
	extern std::string PathName;
	extern std::string WorkingDirectory;
	extern std::string Args;

	extern bool AddToRegistry;
	extern bool DeleteMode;
	extern bool ForceLink;

	extern std::string Err;

	namespace Exceptions {
		class BadCommandLine;
		extern BadCommandLine MissingArg;
		extern BadCommandLine BadArgCombo;
	}
	namespace Links {
		extern rapidjson::Document *LinkDocument;

		extern bool PrepareTheLinkDocument();
	}
}
#endif //__TILANDIS_H