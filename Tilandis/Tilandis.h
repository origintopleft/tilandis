#pragma once
#ifndef __TILANDIS_H
#define __TILANDIS_H
#include <string>
#include <tchar.h>
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

	extern std::string Err;
}
#endif //__TILANDIS_H