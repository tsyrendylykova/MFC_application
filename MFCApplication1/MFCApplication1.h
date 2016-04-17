
// MFCApplication1.h : main header file for the MFCApplication1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGraphAppApp:
// See MFCApplication1.cpp for the implementation of this class
//

class CGraphAppApp : public CWinApp
{
public:
	CGraphAppApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphAppApp theApp;
