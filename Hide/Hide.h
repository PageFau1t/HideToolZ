
// Hide.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CApp:
// See Hide.cpp for the implementation of this class
//

class CApp : public CWinApp
{
public:
	CApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
public:
	BOOL muteOnHide;
	BOOL hkShift, hkCtrl, hkAlt, hkWin;
	int hk;

	DECLARE_MESSAGE_MAP()
};

extern CApp theApp;