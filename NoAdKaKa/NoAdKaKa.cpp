
// NoAdKaKa.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NoAdKaKa.h"
#include "NoAdKaKaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNoAdKaKaApp

BEGIN_MESSAGE_MAP(CNoAdKaKaApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CNoAdKaKaApp construction

CNoAdKaKaApp::CNoAdKaKaApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CNoAdKaKaApp object

CNoAdKaKaApp theApp;


// CNoAdKaKaApp initialization

BOOL CNoAdKaKaApp::InitInstance()
{
	CWinApp::InitInstance();


	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;


	HANDLE mutex = ::CreateMutex(NULL, TRUE, _T("NONO"));
	if (::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return FALSE;
	}
	::ReleaseMutex(mutex);


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CNoAdKaKaDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

