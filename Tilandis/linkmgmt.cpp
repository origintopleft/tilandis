#include <string>
#include <fstream>
#include <sstream>

#include "Tilandis.h"
#include "exceptions.h"
#include "rapidjson\document.h"

std::string Tilandis::Err = "";

rapidjson::Document Tilandis::Links::LinkDocument;

bool Tilandis::Links::PrepareTheLinkDocument() {
	std::ifstream linksfile;
	char* jsoncstr;
	linksfile.open("links.json");
	if (linksfile.is_open()) {
		std::stringstream linksstream; // Feed the whole file into this stringstream
		std::string curline;
		while (getline(linksfile, curline)) {
			linksstream << curline; // Don't need to worry whether the newline at the end is there or not,
									// still valid to RapidJSON
		}
		linksfile.close();
		std::string temp = linksstream.str();
		jsoncstr = temp.c_str(); // DING! Order up!
	}
	else {
		/* We couldn't read the file. There's no reason for multiple Tilandis processes to be reading the config at once,
		 * so we're just going to reckon the file doesn't exist and assume a set of defaults (a.k.a. nothing)
		 * In the highly unlikely event that some other program happens to have that file open at that *exact* moment,
		 * this could cause issues, but unless you're an anti-virus program, having my files open is either a bug or a PEBKAC ;-) */
		jsoncstr = "{}";
	}
	rapidjson::ParseResult result = Tilandis::Links::LinkDocument.Parse(jsoncstr);
	if (!result) {
		return false; // It failed
	}
	
}

bool Tilandis::CreateLink() {
	if (Tilandis::PathName.empty()) { throw Tilandis::Exceptions::MissingArg; }
	if (Tilandis::LinkName.empty()) { throw Tilandis::Exceptions::MissingArg; }


}

bool Tilandis::DeleteLink() {
	return true; //stub
}