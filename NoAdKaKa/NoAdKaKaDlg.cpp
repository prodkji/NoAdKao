
// NoAdKaKaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NoAdKaKa.h"
#include "NoAdKaKaDlg.h"
#include "afxdialogex.h"

#include <Windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNoAdKaKaDlg dialog




CNoAdKaKaDlg::CNoAdKaKaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNoAdKaKaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNoAdKaKaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNoAdKaKaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CNoAdKaKaDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CNoAdKaKaDlg::OnBnClickedOk)
	ON_MESSAGE(WM_TRAYICON_MSG, TrayIconMsg)
END_MESSAGE_MAP()


// CNoAdKaKaDlg message handlers


UINT CNoAdKaKaDlg::EventProcess(LPVOID pParam)
{
	CNoAdKaKaDlg *pDlg = (CNoAdKaKaDlg*)pParam;


	while(1)
	{
		if( ::WaitForSingleObject(pDlg->m_evtStop, 0) == WAIT_OBJECT_0 ) break;

		pDlg->DoProcess();
		Sleep(5);
		pDlg->ShowWindow(SW_HIDE);
	}

	pDlg->m_evtThreadDone.SetEvent();
	return 0;
}

LRESULT CNoAdKaKaDlg::TrayIconMsg(WPARAM wParam, LPARAM lParam)
{
	// 등록된 TrayIcon 클릭하면 Show....
	if(lParam == WM_LBUTTONDBLCLK)
	{  
		NOTIFYICONDATA nid;
		ZeroMemory(&nid, sizeof(nid));
		nid.cbSize = sizeof(nid);
		nid.uID = 0;
		nid.hWnd = this->GetSafeHwnd();

		// 작업 표시줄(TaskBar)의 상태 영역에 아이콘을 삭제한다.
		Shell_NotifyIcon(NIM_DELETE, &nid);


		OnBnClickedOk();
	}
	return 0;
}

BOOL CNoAdKaKaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.uID = 0;
	nid.hWnd = this->GetSafeHwnd();

	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	lstrcpy(nid.szTip, "NoAdKaKa");
	nid.uCallbackMessage = WM_TRAYICON_MSG;

	BOOL bRet = ::Shell_NotifyIcon(NIM_ADD,&nid); 
//	AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);


	pCheckWinThread = NULL;
	m_evtStop.ResetEvent();
	m_evtThreadDone.ResetEvent();
	pCheckWinThread = ::AfxBeginThread(EventProcess, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);


	/// 1차 커밋후 //2차는 분기 테스트 //
	//AfxMessageBox("Do Branch Process");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNoAdKaKaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNoAdKaKaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNoAdKaKaDlg::OnBnClickedButton1()
{
	/// 1차 테스트 : "커밋" ///
	int a = 99;
}

void CNoAdKaKaDlg::OnBnClickedOk()
{
	m_evtStop.SetEvent();
	::WaitForSingleObject(m_evtThreadDone, 1000);
	CDialogEx::OnOK();
}


void CNoAdKaKaDlg::DoProcess(void)
{
	HWND KakaoMain, KakaoAD, KakaoWnd, KakaoChatWnd;
	RECT RectMain, RectChild;

	KakaoAD = ::FindWindowA(_T("EVA_Window_Dblclk"), _T(""));

	if (KakaoAD != NULL)
	{
		::ShowWindow(KakaoAD, SW_HIDE);
	}

	KakaoMain = ::FindWindowA(_T("EVA_Window_Dblclk"), _T("카카오톡"));
	if (KakaoMain != NULL)
	{
		KakaoWnd = ::FindWindowExA(KakaoMain, NULL, _T("EVA_ChildWindow"), _T(""));

		KakaoChatWnd = ::FindWindowExA(KakaoMain, NULL, _T("EVA_ChildWindow"), NULL);

		if (KakaoWnd != NULL)
		{
			::ShowWindow(KakaoWnd, SW_HIDE);
			::GetWindowRect(KakaoMain, &RectMain);
			::GetWindowRect(KakaoChatWnd, &RectChild);
			::SetWindowPos(KakaoChatWnd, HWND_BOTTOM, 0, 0, (RectMain.right - RectMain.left), (RectMain.bottom - RectMain.top - 32), SWP_NOMOVE);
		}
	}
}



int CNoAdKaKaDlg::GitUnderstand_01()
{
	// 원복후 함수 이름 다른것으로 재작업
	int power = 0;

	int crashtest = 102;
	int bug = -1;
	return 0;
}


int CNoAdKaKaDlg::work2()
{
	int work2 = 101;
	return 0;
}


int CNoAdKaKaDlg::Work1()
{
	int work1 = 99;

	int work1add = 100;

	return 0;
}
