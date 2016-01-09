/*
 * Tilandis
 * by Nicholas "Lavacano" O'Connor
 * Purpose: I'll make my own TileCreator proxy! With blackjack! And hookers!
 */
#include <iostream>
// Tilandis code
#include "Tilandis.h"
#include "exceptions.h"
#include "Utility.h"

std::wstring Tilandis::BaseDirectory = L"";
int CALLBACK wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR, int nShow) {
	// Note to self: Do not EVER, under ANY circumstances, use the lpCmdLine parameter passed to wWinMain
	// That parameter is full of lies and deceit and cannot be trusted
	LPWSTR* argv;
	int argc;
	argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	wchar_t* argvzero = new wchar_t[65535];
	GetModuleFileName(NULL, argvzero, 65535);


	std::wstring argvzerostr = argvzero;

	Tilandis::BaseDirectory = Utility::basedir(argvzerostr);
	if (!Tilandis::Links::PrepareTheLinkDocument()) {
		std::wcout << "Failed to prepare the link document." << std::endl;
		return 1;
	}
	if (Tilandis::UsingCommandLine(argc, argv)) { // FIXME: Commandline processing, while it works, is extremely friggin weird because I wrote it stoned
		try {
			if (Tilandis::DeleteMode && Tilandis::CreateMode) { throw Tilandis::Exceptions::BadArgCombo; }
			if (Tilandis::DeleteMode) { Tilandis::Links::DeleteLink(); }
			if (Tilandis::CreateMode) {
				try {
					bool success = Tilandis::Links::CreateLink();
					if (!success) {
						std::wcout << Tilandis::Err << std::endl;
					}
				}
				catch (Tilandis::Exceptions::BadCommandLine exc) {
					std::wcout << exc.what() << std::endl;
					return 1;
				}
			}
			if (Tilandis::AddToRegistry) {
				bool result = Tilandis::RegisterProtocol();
				if (!result) {
					MessageBox(NULL, L"Failed to register Tilandis with specified protocol (hint: this function needs administrator rights)", L"Tilandis", 0);
					return 1;
				}
				else {
					MessageBox(NULL, L"Tilandis has \"successfully\" registered itself with the specified protocol.\r\nBe aware that though no error is reported, many failure cases aren't currently detected. You'll have to double-check the registry yourself.", L"Tilandis", 0);
					return 0;
				}
			}
		}
		catch (Tilandis::Exceptions::BadCommandLine exc) {
			std::wcout << exc.what() << std::endl;
			return 1;
		}
	}
	else {
		if (argc == 1) {
			Tilandis::PrintUsage(argv[0]); // TODO: make this run a GUI instead
		}
		else if (argc == 2) {
			std::wstring LinkName = argv[1];
			size_t pos;
			if ((pos = LinkName.find(L":")) != std::wstring::npos) { // if we FIND a colon
				LinkName.erase(0, pos + 1); // Remove protocols from the beginning
				wchar_t nasties[] = L"/\\\r\n";
				for (size_t i = 0; i < wcslen(nasties); ++i) { // slash removal
					LinkName.erase(std::remove(LinkName.begin(), LinkName.end(), nasties[i]), LinkName.end());
				}
			}
			try {
				if (!Tilandis::Links::LaunchLink(LinkName.c_str())) {
					std::wstring wincapt = LinkName;
					wincapt.append(L": Failure to launch");
					std::wstring errmsg = L"Tilandis failed to launch the link " + LinkName + L". Check your configuration.";
					MessageBox(NULL, errmsg.c_str(), wincapt.c_str(), MB_ICONERROR);
				}
			}
			catch (Tilandis::Exceptions::BadLink exc) {
				std::wstring wincapt; 
				wincapt.assign(argv[1]);
				wincapt.append(L": Bad Link");
				std::wstring errmsg = Utility::UTF8Converter.from_bytes(exc.what());
				MessageBox(NULL, errmsg.c_str(), wincapt.c_str(), MB_ICONWARNING);
				return 1;
			}
		}
	}
	
	return 0;
}

void Tilandis::PrintUsage(std::wstring arg0) {
	std::wcout << "Usage for " << arg0 << ":" << std::endl;
	std::wcout << '\t' << arg0 << " <link name> :: Launch a link" << std::endl;
	std::wcout << '\t' << arg0 << " -n <link name> <options> :: Create a link" << std::endl;
	std::wcout << '\t' << arg0 << " -d <link name> :: Delete a link" << std::endl;
	std::wcout << std::endl; // separating blank line
	std::wcout << "Options for -n include:" << std::endl;
	std::wcout << "\t-p <pathname> :: Required. Path to thing to launch (accepts URLs)" << std::endl;
	std::wcout << "\t-a <args> :: Arguments to pass to the program." << std::endl;
	std::wcout << "\t-w <directory> :: The working directory to launch the program in. Defaults to the same as the file location." << std::endl;
	std::wcout << "\t-f :: Replace any existing link with the same name. (Mnemonic: \"force\")" << std::endl;
}

bool Tilandis::RegisterProtocol() {
	HKEY registry;
	DWORD regresult;
	long result = RegCreateKeyEx(HKEY_CLASSES_ROOT, (wchar_t*)Tilandis::RegistryProtocolName.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &registry, &regresult);
	if (regresult == REG_OPENED_EXISTING_KEY) { std::wcout << "note: this protocol's already registered with something" << std::endl; }

	result = RegSetValueEx(registry, L"URL Protocol", 0, REG_SZ, NULL, 0);
	if (result != ERROR_SUCCESS) {
		return false;
	}
	HKEY subregistry;
	result = RegCreateKeyEx(registry, L"shell\\open\\command", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &subregistry, &regresult);

	wchar_t* argvzero = new wchar_t[65535];
	GetModuleFileName(NULL, argvzero, 65535);
	std::wstringstream regstringstream;
	regstringstream << L'"' << argvzero << L"\" \"%1\"";
	std::wstring regstring = regstringstream.str();
	std::wcout << argvzero << L"  " << std::endl;
	const wchar_t* regbytes = regstring.c_str();
	result = RegSetValueEx(subregistry, NULL, 0, REG_SZ, (LPBYTE) regbytes, 65535);
	if (!result) { return false; }
	return true;
}