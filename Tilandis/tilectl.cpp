#include "Tilandis.h"
#include "exceptions.h"
#include <map>
#include <vector>

tristate Tilandis::ParseTileCTL(std::wstring ctlcmd) {
	ctlcmd.erase(0, 10); // erases "tilectl://"

	/* TileCTL cliff notes:
	 * tilectl://<command>/<link>?option=value&option=value
	 * examples without tilectl:// prefix:
	 * new/notepad?path=C:\Windows\notepad.exe&workdir=C:\Windows&args=C:\file.txt&admin=true
	 * delete/notepad
	 * "edit" and "launch" might happen, currently uncertain
	 */

	// This particular implementation moves through each part of the tilectl command by erasing the parts
	// it's already understood. This is not required by any standard, it just happens to be the easiest
	// thing for me to implement at the moment (plus I think it helps with memory management?)

	// command
	size_t slashpos = ctlcmd.find(L'/');
	std::wstring command = ctlcmd.substr(0, slashpos);
	ctlcmd.erase(0, slashpos + 1);

	// link name (and args, if we have them)
	bool hasargs;
	size_t questpos = ctlcmd.find(L'?');
	std::map<std::wstring, std::wstring> dict_args;

	if (questpos != ctlcmd.npos) { // ? is present
		hasargs = true;
		Tilandis::LinkName = ctlcmd.substr(0, questpos);
		ctlcmd.erase(0, questpos + 1);

		// Count the args so we know how long the for loop is going to be
		// this enables the erase method so I don't have to think about the math
		size_t andpos = 0;
		int numargs = 0;
		while (true) {
			andpos = ctlcmd.find(L'&', andpos + 1);
			numargs++;
			if (andpos == ctlcmd.npos) {
				// out of &s
				break;
			}
		}

		for (int i = 0; i < numargs; i++) {
			andpos = ctlcmd.find(L'&');
			std::wstring curarg = ctlcmd.substr(0, andpos);

			size_t equalspos = curarg.find(L'=');
			std::wstring option = curarg.substr(0, equalspos);
			std::wstring value = curarg.substr(equalspos + 1, curarg.npos);

			if (option == L"path") { Tilandis::PathName = value; }
			else if (option == L"args") { Tilandis::Args = value; }
			else if (option == L"workdir") { Tilandis::WorkingDirectory = value; }
			else if (option == L"admin") {
				std::transform(value.begin(), value.end(), value.begin(), ::towlower); // lowercase string

				if (value == L"true") { Tilandis::LinkInAdminMode = true; }
			} else {
				dict_args[option] = value;
			}

			ctlcmd.erase(0, andpos + 1);
		}
	} else {
		hasargs = false;
		Tilandis::LinkName = ctlcmd;
		ctlcmd.erase(0, ctlcmd.npos); // should empty the string
	}

	std::transform(command.begin(), command.end(), command.begin(), ::towlower); // lowercase string
	if (command == L"new") {
		if (!hasargs) {
			throw Tilandis::Exceptions::MissingArg;
			return False;
		} else if (Tilandis::LinkName == L"") {
			throw Tilandis::Exceptions::MissingArg;
			return False;
		} else if (Tilandis::PathName == L"") {
			throw Tilandis::Exceptions::MissingArg;
			return False;
		}

		Tilandis::CreateMode = true;
		return True;
	} else if (command == L"delete") {
		if (Tilandis::LinkName == L"") {
			throw Tilandis::Exceptions::MissingArg;
			return False;
		}

		Tilandis::DeleteMode = true;
		return True;
	} else if (command == L"enum") { // Lists existing links
		if (!hasargs) {
			throw Tilandis::Exceptions::MissingArg;
			return False;
		}

		WSADATA wsa;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { // Winsock failure
			std::wstring outstr = L"Winsock failed to start up, error code: ";
			outstr += std::to_wstring(WSAGetLastError());
			MessageBox(NULL, outstr.c_str(), L"Tilandis", MB_ICONERROR);
			return False;
		}

		struct sockaddr_in sai_caller;
		memset((wchar_t *) &sai_caller, 0, sizeof(sai_caller));
		sai_caller.sin_family = AF_INET;
		sai_caller.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

		int port;
		try { port = std::stoi(dict_args.at(L"port")); }
		catch (std::out_of_range) {
			throw Tilandis::Exceptions::MissingArg;
			return False;
		}
		sai_caller.sin_port = htons(port);

		int buflen;
		char* buf;

		std::ifstream ifile_links;
		ifile_links.open(Tilandis::BaseDirectory + L"\\links.json", std::ios::binary);
		if (ifile_links.is_open()) { // File exists
			// read file to memory
			std::vector<char> filedata;
			char current;
			while (ifile_links >> std::noskipws >> current) { filedata.push_back(current); }
			
			// set up socket buffer
			buflen = filedata.size();
			buf = filedata.data();
		} else { // file doesn't exist, or can't be read, or something
			// The caller expects *something*, so lets give it an empty array
			buflen = 3;
			buf = "{}";

			MessageBox(NULL, L"Couldn't open the links document for the link enumeration request.\n\nThis is usually because the file links.json doesn't exist (make a link first).", L"Tilandis", MB_ICONERROR);
		}

		SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sock == SOCKET_ERROR) {
			std::wstring outstr = L"The command was successful, but there was an error with the socket: ";
			outstr += std::to_wstring(WSAGetLastError());
			MessageBox(NULL, outstr.c_str(), L"Tilandis", MB_ICONERROR);
			return False;
		}
		int result = sendto(sock, buf, buflen, 0, (sockaddr *) &sai_caller, sizeof(sai_caller));
		if (result == SOCKET_ERROR) {
			std::wstring outstr = L"The command was successful, but there was an error with the UDP request: ";
			outstr += std::to_wstring(WSAGetLastError());
			MessageBox(NULL, outstr.c_str(), L"Tilandis", MB_ICONERROR);
			return False;
		}

		closesocket(sock);
		WSACleanup();
		return Mixed; // "success" (even if the file thing didn't work, because we can recover from that) but no need to manipulate links.json
	}
}