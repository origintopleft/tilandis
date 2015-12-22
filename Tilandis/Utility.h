#pragma once
#ifndef __UTILITY_H
#define __UTILITY_H

#include <codecvt>
#include <locale>
#include <string>

namespace Utility {
	extern std::wstring basedir(std::wstring);

	typedef std::codecvt_utf8<wchar_t> UTF8;
	
	extern std::wstring_convert<UTF8, wchar_t> UTF8Converter;
}

#endif //__UTILITY_H