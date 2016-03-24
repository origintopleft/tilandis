#pragma once
#ifndef __TILECTL_H
#define __TILECTL_H
#include "Tilandis.h"

namespace Tilandis {
	extern tristate ParseTileCTL(std::wstring ctlcmd);
}

#endif // !__TILECTL_H