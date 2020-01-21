
// Lab2-GDI transformacije.h : main header file for the Lab2-GDI transformacije application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLab2GDItransformacijeApp:
// See Lab2-GDI transformacije.cpp for the implementation of this class
//

class CLab2GDItransformacijeApp : public CWinApp
{
public:
	CLab2GDItransformacijeApp() ;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLab2GDItransformacijeApp theApp;
