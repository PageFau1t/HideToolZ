
// mainwnd.cpp : implementation file
//

#include "stdafx.h"
#include "Hide.h"
#include "mainwnd.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// mainwnd dialog
#define UM_MSG1 WM_USER+10084
#define UM_TRAY WM_USER+10085


mainwnd::mainwnd(CWnd* pParent /*=NULL*/)
: CDialogEx(mainwnd::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void mainwnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(mainwnd, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &mainwnd::OnRestore)
	ON_MESSAGE(UM_MSG1, OnFindWindow)
	ON_BN_CLICKED(IDC_BUTTON2, &mainwnd::OnHide)
	ON_WM_HOTKEY()
	ON_BN_CLICKED(IDC_BUTTON3, &mainwnd::OnAddProcess)
	ON_BN_CLICKED(IDC_BUTTON4, &mainwnd::OnRemoveProcess)
	ON_BN_CLICKED(IDC_BUTTON5, &mainwnd::OnRefresh)
	ON_BN_CLICKED(IDC_BUTTON6, &mainwnd::OnBnClickedButton6)
END_MESSAGE_MAP()


// mainwnd message handlers

BOOL mainwnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	theApp.muteOnHide = 1;
	countHidden = 0;
	hideState = 0;
	countTgt = 1;

	//列初始化
	m_list1 = (CListCtrl*)GetDlgItem(IDC_LIST1);
	m_list1->ModifyStyle(NULL, LVS_REPORT);
	m_list2 = (CListCtrl*)GetDlgItem(IDC_LIST2);
	m_list2->ModifyStyle(NULL, LVS_REPORT);
	m_list1->InsertColumn(0, L"Process", LVCFMT_LEFT, 100);
	m_list1->InsertColumn(1, L"PID", LVCFMT_LEFT, 50);
	m_list2->InsertColumn(0, L"Process", LVCFMT_LEFT, 100);
	m_list2->InsertColumn(1, L"PID", LVCFMT_LEFT, 50);

	RegisterHotKey(GetSafeHwnd(), 49040, MOD_ALT, VK_F1);
	GetProcessList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void mainwnd::OnPaint()
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
HCURSOR mainwnd::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//屏蔽回车和ESC  
BOOL mainwnd::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}


BOOL mainwnd::GetProcessList()
{
	HANDLE hProcessSnap = NULL;
	PROCESSENTRY32 pe32 = { 0 };

	//  Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return (FALSE);
	}

	//  Fill in the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	//  Walk the snapshot of the processes, and for each process,
	//  display information.
	if (Process32First(hProcessSnap, &pe32))
	{
		DWORD         dwPriorityClass;
		BOOL          bGotModule = FALSE;
		MODULEENTRY32 me32 = { 0 };

		DWORD PID;
		CString Name;
		CString strPID;
		m_list1->DeleteAllItems();
		do
		{
			//取得进程名和PID
			PID = pe32.th32ProcessID;
			Name.Format(L"%s", pe32.szExeFile);

			if (Name == L"Hide.exe")
			{
				tgtPID[0] = PID;
			}
			//加入List1
			int row = m_list1->InsertItem(0, Name);
			strPID.Format(L"%d", PID);
			m_list1->SetItemText(row, 1, strPID);

		} while (Process32Next(hProcessSnap, &pe32));

	}
	else
	{
		return FALSE;
	}

	// Do not forget to clean up the snapshot object.
	CloseHandle(hProcessSnap);

	return TRUE;
}


void mainwnd::RefreshPID()
{
	HANDLE hProcessSnap = NULL;
	PROCESSENTRY32 pe32 = { 0 };

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessSnap, &pe32))
	{
		DWORD         dwPriorityClass;
		BOOL          bGotModule = FALSE;
		MODULEENTRY32 me32 = { 0 };

		DWORD PID;
		CString Name;
		countTgt = 1;
		do
		{
			//取得进程名和PID
			PID = pe32.th32ProcessID;
			Name.Format(L"%s", pe32.szExeFile);

			for (int i = 0; i < m_list2->GetItemCount(); i++)
			{
				if (Name == m_list2->GetItemText(i, 0))//若进程名在List2中
				{
					//保存PID
					tgtPID[countTgt] = PID;
					countTgt++;
				}
			}
		} while (Process32Next(hProcessSnap, &pe32));

	}

	CloseHandle(hProcessSnap);
}


BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam)
{
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWnd, &dwPid); // 获得找到窗口所属的进程PID
	if (dwPid == lParam) // 判断是否是目标进程的窗口  
	{
		PostMessage(theApp.m_pMainWnd->m_hWnd, UM_MSG1, (WPARAM)hWnd, 0);
	}
	return TRUE;
}


LRESULT mainwnd::OnFindWindow(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)wParam;

	if (::IsWindowVisible(hWnd))//判断是否显性窗口
	{
		::ShowWindow(hWnd, SW_HIDE);
		hiddenHWND[countHidden] = hWnd;
		countHidden++;

	}

	return S_OK;
}


void mainwnd::OnRestore()
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < countHidden; i++)
	{
		::ShowWindow(hiddenHWND[i], SW_SHOW);
	}
	countHidden = 0;
	hideState = 0;

	if (theApp.muteOnHide)
	{
		volCtrl.SetMute(0);
	}
}


void mainwnd::OnHide()
{
	// TODO: Add your control notification handler code here
	RefreshPID();
	for (int i = 0; i < countTgt; i++)
	{
		EnumWindows(EnumWindowCallBack, tgtPID[i]);
	}
	hideState = 1;

	if (theApp.muteOnHide)
	{
		volCtrl.SetMute(1);
	}	
}


void mainwnd::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: Add your message handler code here and/or call default
	if (hideState == 0)
	{
		OnHide();
	}
	else
	{
		OnRestore();
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void mainwnd::OnAddProcess()
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < m_list1->GetItemCount(); i++)
	{
		if (m_list1->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			int nRow = m_list2->InsertItem(0, m_list1->GetItemText(i, 0));//插入行
			m_list2->SetItemText(nRow, 1, m_list1->GetItemText(i, 1));//设置数据
		}
	}
}


void mainwnd::OnRemoveProcess()
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < m_list2->GetItemCount(); i++)
	{
		if (m_list2->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			int nRow = m_list2->DeleteItem(i);
		}
	}
}


void mainwnd::OnRefresh()
{
	// TODO: Add your control notification handler code here
	GetProcessList();
}


void mainwnd::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	settingDlg = new CSettings(this);
	settingDlg->DoModal();
}
