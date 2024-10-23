
// NoAdKaKaDlg.h : header file
//

#pragma once

#define  WM_TRAYICON_MSG WM_USER + 1


// CNoAdKaKaDlg dialog
class CNoAdKaKaDlg : public CDialogEx
{
// Construction
public:
	CNoAdKaKaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NOADKAKA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	HHOOK hKeyboardHook;
	HHOOK hMouseHook;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	LRESULT TrayIconMsg(WPARAM wParam, LPARAM lParam); 

public:
	afx_msg void OnBnClickedButton1();

	CEvent m_evtThreadDone;
	CEvent m_evtStop;
	BOOL	m_bOdd;

	static UINT EventProcess(LPVOID pParam);

	CWinThread *pCheckWinThread;
	afx_msg void OnBnClickedOk();
	void DoProcess(void);
	int GitUnderstand_01();
	int Work1();
	int work2();
	int MakeUserBusyEvent();
	BOOL Idle_OverTime();
};

