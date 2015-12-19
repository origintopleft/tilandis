#pragma once
#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H
#include "Tilandis.h"

class Tilandis::Exceptions::BadCommandLine : public std::exception {
public:
	enum subtype_t { MissingArg, BadArgCombo } subtype;
	inline Tilandis::Exceptions::BadCommandLine(subtype_t mysubtype);
	inline Tilandis::Exceptions::BadCommandLine(const Tilandis::Exceptions::BadCommandLine& copyme);

	const char* what() const throw();
};

#endif //__EXCEPTIONS_H