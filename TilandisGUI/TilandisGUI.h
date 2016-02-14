
// TilandisGUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTilandisGUIApp:
// See TilandisGUI.cpp for the implementation of this class
//

class CTilandisGUIApp : public CWinApp
{
public:
	CTilandisGUIApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTilandisGUIApp theApp;