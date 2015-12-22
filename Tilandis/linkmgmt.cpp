#include <string>
#include <fstream>
#include <Windows.h>
#include <PathCch.h>
#include <tchar.h>
#include <iostream>

#include "Tilandis.h"
#include "exceptions.h"
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\filereadstream.h"

std::string Tilandis::Err = "";

rapidjson::Document *Tilandis::Links::LinkDocument = new rapidjson::Document;

bool Tilandis::Links::PrepareTheLinkDocument() {
	/* Note about MS stupidity:
	 *		Some twat at MS decided that fopen, as it was, was somehow a "dangerous" function, and that you should be using
	 *		fopen_s instead. The reason he's a twat is because he's using the same error as actual unsafe functions.
	 *		For cross platform use, you would do `FILE* infile = fopen("links.json", "r")` as your condition, and that would
	 *		both define infile for you, and switch to the else block if it failed, all in one line, and then #ifdef WIN32.
	 *		Since this is a Windows 10 only project, we only need to change to fopen_s.
	 */
	FILE* infile;
	errno_t errcode = fopen_s(&infile, "links.json", "r");
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
		result = Tilandis::Links::LinkDocument->Parse("{}");
	}
	if (!result) {  // It failed
		std::cerr << result.Code() << std::endl;
		return false;
	}
	else { return true; }
}

bool Tilandis::Links::CreateLink() {
	if (Tilandis::PathName.empty()) { throw Tilandis::Exceptions::MissingArg; }
	if (Tilandis::LinkName.empty()) { throw Tilandis::Exceptions::MissingArg; }

	/*  >>> ---- >>>> ---- RapidJSON doesn't speak string >>>> ---- VVVV */
	if (Tilandis::Links::LinkDocument->HasMember(Tilandis::LinkName.c_str())) { // we already have a link with that name
		if (Tilandis::ForceLink) { // -f opt
			Tilandis::Links::DeleteLink(); // reminder: these functions use the global variables in the Tilandis namespace because C++ doesn't have
										   //			optional variables, at least not in the Pythonic sense where you can just declare args=None
										   //           sure i could probably just pass more JSON to everything but i feel like this way uses less
										   //           memory or something
		}
		else {
			Tilandis::Err = "Link already exists (you might try -f)";
			return false;
		}
	}

	// This thing gets recycled!
	rapidjson::Value value;
	rapidjson::Value name;

	// New object to add to the DOM
	name.SetString(Tilandis::LinkName.c_str(), Tilandis::Links::LinkDocument->GetAllocator());
	value.SetObject();
	Tilandis::Links::LinkDocument->AddMember(name, value, Tilandis::Links::LinkDocument->GetAllocator());
	rapidjson::Value& newlink = (*Tilandis::Links::LinkDocument)[Tilandis::LinkName.c_str()];

	// Path name
	name.SetString("path");
	value.SetString(Tilandis::PathName.c_str(), Tilandis::Links::LinkDocument->GetAllocator());
	newlink.AddMember(name, value, Tilandis::Links::LinkDocument->GetAllocator());

	// Args
	if (Tilandis::Args != "") { //if we have them, anyway
		name.SetString("args");
		value.SetString(Tilandis::Args.c_str(), Tilandis::Links::LinkDocument->GetAllocator());
		newlink.AddMember(name, value, Tilandis::Links::LinkDocument->GetAllocator());
	}

	// Working directory
	name.SetString("workdir");
	if (Tilandis::WorkingDirectory != "") { // has the user specified one?
		// If we're in this block, yes
		value.SetString(Tilandis::WorkingDirectory.c_str(), Tilandis::Links::LinkDocument->GetAllocator());
	}
	else {
		// Nope. Time to find it our damn selves.
		value.SetString("C:\\", Tilandis::Links::LinkDocument->GetAllocator()); // FIXME: actually set up an autodetect for working dirs
													// BULLSHIT: Need to also figure out how PathCchRemoveFileSpec works
	}
	newlink.AddMember(name, value, Tilandis::Links::LinkDocument->GetAllocator());

	Tilandis::Links::SaveLinkDocument();
	return true;
}

bool Tilandis::Links::DeleteLink() {
	if (!Tilandis::Links::LinkDocument->HasMember(Tilandis::LinkName.c_str())) { return false; }
	
	Tilandis::Links::LinkDocument->EraseMember(Tilandis::LinkName.c_str());
	Tilandis::Links::SaveLinkDocument();
	return true;
}

bool Tilandis::Links::LaunchLink(char * LinkName) {
	std::cout << "You would launch " << LinkName;
	Sleep(5000);
	return true;
}

bool Tilandis::Links::SaveLinkDocument() {
	std::ofstream outfile;
	outfile.open("links.json");

	rapidjson::StringBuffer outbuffer;
	rapidjson::Writer<rapidjson::StringBuffer> outwriter(outbuffer);
	Tilandis::Links::LinkDocument->Accept(outwriter);

	outfile << outbuffer.GetString() << std::endl;
	outfile.close();

	return true;
}