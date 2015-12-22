#include "Utility.h"

std::wstring_convert<Utility::UTF8, wchar_t> Utility::UTF8Converter;

std::wstring Utility::basedir(std::wstring path) {
	size_t lastslash = path.find_last_of(L"\\"); // ignoring forward slash
	if (lastslash != path.npos) {
		return path.substr(0, lastslash);
	}
	else {
		return path; // probably a URL
	}
}