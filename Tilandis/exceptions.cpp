#include "Tilandis.h"
#include "exceptions.h"

Tilandis::Exceptions::BadCommandLine::BadCommandLine(Tilandis::Exceptions::BadCommandLine::subtype_t mysubtype) {
	subtype = mysubtype;
}

Tilandis::Exceptions::BadCommandLine::BadCommandLine(const Tilandis::Exceptions::BadCommandLine& copyme) {
	 // I can't just do subtype = copyme.subtype, probably because it defines a separate enum for each instance
	 // c'est la vie i guess
	 switch (copyme.subtype) {
	 case MissingArg:
		 subtype = MissingArg;
	 case BadArgCombo:
		 subtype = BadArgCombo;
	 }
}
 const char* Tilandis::Exceptions::BadCommandLine::what() const throw() {
	 if (subtype == MissingArg) { return "An argument is missing. Don't know what to do."; }
	 else if (subtype == BadArgCombo) { return "Your arguments don't make sense together. Are you perhaps trying to create and delete at the same time?"; }
 }

Tilandis::Exceptions::BadCommandLine Tilandis::Exceptions::MissingArg(MissingArg);
Tilandis::Exceptions::BadCommandLine Tilandis::Exceptions::BadArgCombo(BadArgCombo);