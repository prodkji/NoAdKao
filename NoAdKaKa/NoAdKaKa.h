
// NoAdKaKa.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CNoAdKaKaApp:
// See NoAdKaKa.cpp for the implementation of this class
//

class CNoAdKaKaApp : public CWinApp
{
public:
	CNoAdKaKaApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	CRITICAL_SECTION m_Sectionsafe;
	CTime LastTime;


	DECLARE_MESSAGE_MAP()
};

extern CNoAdKaKaApp theApp;