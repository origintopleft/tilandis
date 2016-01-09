#pragma once
#ifndef __GUI_H
#define __GUI_H

#include <afxwin.h>
#include "Tilandis.h"

namespace GUI {
	class CTilandisWinApp : public CWinApp {
	public:
		BOOL InitInstance();
		int Run();
	};

	CTilandisWinApp * TilandisWinApp = new CTilandisWinApp();

	CDialog * RegisterProtocol = new CDialog();

	bool InitMFC();
	bool ShowDialog(CDialog *);
}

#endif