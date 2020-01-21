
// Lab3-Bitmape.h : main header file for the Lab3-Bitmape application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLab3BitmapeApp:
// See Lab3-Bitmape.cpp for the implementation of this class
//

class CLab3BitmapeApp : public CWinApp
{
public:
	CLab3BitmapeApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLab3BitmapeApp theApp;
