#include <string>
#include <fstream>
#include <Windows.h>
#include <PathCch.h>
#include <tchar.h>
#include <iostream>

#include "Tilandis.h"
#include "Utility.h"
#include "exceptions.h"
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\filereadstream.h"

std::wstring Tilandis::Err = L"";

rapidjson::GenericDocument<rapidjson::UTF8<wchar_t>> *Tilandis::Links::LinkDocument = new rapidjson::GenericDocument<rapidjson::UTF8<wchar_t>>;

bool Tilandis::Links::PrepareTheLinkDocument() {
	/* Note about MS stupidity:
	 *		Some twat at MS decided that fopen, as it was, was somehow a "dangerous" function, and that you should be using
	 *		fopen_s instead. The reason he's a twat is because he's using the same error as actual unsafe functions.
	 *		For cross platform use, you would do `FILE* infile = fopen("links.json", "r")` as your condition, and that would
	 *		both define infile for you, and switch to the else block if it failed, all in one line, and then #ifdef WIN32.
	 *		Since this is a Windows 10 only project, we only need to change to fopen_s.
	 */
	FILE* infile;
	std::wstring configfilename = Tilandis::BaseDirectory + L"\\links.json";
	//std::wcerr << configfilename << std::endl;
	errno_t errcode = _wfopen_s(&infile, configfilename.c_str(), L"r");
	rapidjson::ParseResult result;
	if (errcode == 0) {
		char inbuffer[8192]; // 8KB, should be fine unless you manage to have an unnecessarily large links file
							 // Consider allowing users to configure this
		rapidjson::FileReadStream instream(infile, inbuffer, 8192); // last argument is size of buffer, so again 8KB

		result = Tilandis::Links::LinkDocument->ParseStream(instream);

		fclose(infile);
	}
	else {
		/* We couldn't read the file. There's no reason for multiple Tilandis processes to be reading the config at once,
		 * so we're just going to reckon the file doesn't exist and assume a set of defaults (a.k.a. nothing)
		 * In the highly unlikely event that some other program happens to have that file open at that *exact* moment,
		 * this could cause issues, but unless you're an anti-virus program, having my files open is either a bug or a PEBKAC ;-) */
		result = Tilandis::Links::LinkDocument->Parse(L"{}");
	}
	if (!result) {  // It failed
		//std::cerr << result.Code() << std::endl;
		return false;
	}
	else { return true; }
}

bool Tilandis::Links::ManipulateLinkDocument() {
	if (Tilandis::DeleteMode && Tilandis::CreateMode) { throw Tilandis::Exceptions::BadArgCombo; }
	if (Tilandis::DeleteMode) { Tilandis::Links::DeleteLink(); }
	if (Tilandis::CreateMode) {
		try {
			bool success = Tilandis::Links::CreateLink();
			if (!success) {
				std::wcout << Tilandis::Err << std::endl;
			}
		} catch (Tilandis::Exceptions::BadCommandLine exc) {
			wchar_t* excwhat = L"";
			const char* excwhatmbs = "";
			excwhatmbs = exc.what(); // we do it this way because the (reasonably) paranoid compiler doesn't reckon the pointer will always be initialized
			mbstowcs_s(NULL, excwhat, strlen(excwhatmbs) + 1, excwhatmbs, (size_t) 2048);
			MessageBox(NULL, excwhat, L"Tilandis", 0);
			return false;
		}
	}

	return true;
}

bool Tilandis::Links::CreateLink() {
	if (Tilandis::PathName.empty()) { throw Tilandis::Exceptions::MissingArg; }
	if (Tilandis::LinkName.empty()) { throw Tilandis::Exceptions::MissingArg; }

	if (Tilandis::Links::LinkDocument->HasMember(Tilandis::LinkName.c_str())) { // we already have a link with that name
		if (Tilandis::ForceLink) { // -f opt
			Tilandis::Links::DeleteLink(); // reminder: these functions use the global variables in the Tilandis namespace because C++ doesn't have
										   //			optional variables, at least not in the Pythonic sense where you can just declare args=None
										   //           sure i could probably just pass more JSON to everything but i feel like this way uses less
										   //           memory or something
		}
		else {
			Tilandis::Err = L"Link already exists (you might try -f)";
			return false;
		}
	}

	// This thing gets recycled!
	rapidjson::GenericValue<rapidjson::UTF8<wchar_t>> value;
	rapidjson::GenericValue<rapidjson::UTF8<wchar_t>> name;

	// New object to add to the DOM
	name.SetString(Tilandis::LinkName.c_str(), Tilandis::Links::LinkDocument->GetAllocator());
	value.SetObject();
	Tilandis::Links::LinkDocument->AddMember(name, value, Tilandis::Links::LinkDocument->GetAllocator());
	rapidjson::GenericValue<rapidjson::UTF8<wchar_t>>& newlink = (*Tilandis::Links::LinkDocument)[Tilandis::LinkName.c_str()];

	// Path name
	name.SetString(L"path");
	value.SetString(Tilandis::PathName.c_str(), Tilandis::Links::LinkDocument->GetAllocator());
	newlink.AddMember(name, value, Tilandis::Links::LinkDocument->GetAllocator());

	// Args
	if (Tilandis::Args != L"") { //if we have them, anyway
		name.SetString(L"args");
		value.SetString(Tilandis::Args.c_str(), Tilandis::Links::LinkDocument->GetAllocator());
		newlink.AddMember(name, value, Tilandis::Links::LinkDocument->GetAllocator());
	}

	// Working directory
	name.SetString(L"workdir");
	if (Tilandis::WorkingDirectory != L"") { // has the user specified one?
		// If we're in this block, yes
		value.SetString(Tilandis::WorkingDirectory.c_str(), Tilandis::Links::LinkDocument->GetAllocator());
	}
	else {
		// Nope. Time to find it our damn selves.
		value.SetString(Utility::basedir(Tilandis::PathName).c_str(), Tilandis::Links::LinkDocument->GetAllocator());
	}
	newlink.AddMember(name, value, Tilandis::Links::LinkDocument->GetAllocator());

	// Run as administrator?
	name.SetString(L"asadmin");
	value.SetBool(Tilandis::LinkInAdminMode);
	newlink.AddMember(name, value, Tilandis::Links::LinkDocument->GetAllocator());

	Tilandis::Links::SaveLinkDocument();
	return true;
}

bool Tilandis::Links::DeleteLink() {
	if (!Tilandis::Links::LinkDocument->HasMember(Tilandis::LinkName.c_str())) { return false; }
	
	Tilandis::Links::LinkDocument->RemoveMember(Tilandis::LinkName.c_str());
	Tilandis::Links::SaveLinkDocument();
	return true;
}

bool Tilandis::Links::LaunchLink(const wchar_t * LinkName) {
	if (!Tilandis::Links::LinkDocument->HasMember(LinkName)) {
		throw Tilandis::Exceptions::NoSuchLink;
		return false; // shhh, little debugger. go to sleep in your directory. Dala loves you
	}
	rapidjson::GenericValue<rapidjson::UTF8<wchar_t>>& link = (*Tilandis::Links::LinkDocument)[LinkName];
	std::wcout << link[L"path"].GetString() << L" in working directory " << link[L"workdir"].GetString();

	std::wstring path	 = link[L"path"].GetString();
	std::wstring workdir = link[L"workdir"].GetString();
	std::wstring args;
	if (link.HasMember(L"args")) { args = link[L"args"].GetString(); }
	else { args = L""; }
	bool asadmin = false;
	if (link.HasMember(L"asadmin")) { asadmin = link[L"asadmin"].GetBool(); }

	if (asadmin) {
		ShellExecute(NULL, L"runas", path.c_str(), args.c_str(), workdir.c_str(), SW_SHOWDEFAULT);
	}
	else {
		ShellExecute(NULL, NULL, path.c_str(), args.c_str(), workdir.c_str(), SW_SHOWDEFAULT);
	}
	//Sleep(2000);

	// using taskkill to close TileCreator (nicely) behind us
	// TODO: configurable
	wchar_t sys32[128];
	GetEnvironmentVariable(L"WINDIR", sys32, sizeof(sys32));
	wcscat_s(sys32, L"\\system32\\taskkill.exe");
	//MessageBox(NULL, sys32, sys32, 0);
	ShellExecute(NULL, NULL, sys32, L"/fi \"windowtitle eq TileCreator\"", NULL, SW_HIDE);
	return true;
}

bool Tilandis::Links::SaveLinkDocument() {
	std::ofstream outfile;
	std::wstring outfilename = Tilandis::BaseDirectory + L"\\links.json";
	outfile.open(outfilename.c_str());

	rapidjson::StringBuffer outbuffer;
	rapidjson::Writer<rapidjson::StringBuffer,rapidjson::UTF16<>> outwriter(outbuffer);
	Tilandis::Links::LinkDocument->Accept(outwriter);

	outfile << outbuffer.GetString() << std::endl;
	outfile.close();

	return true;
}