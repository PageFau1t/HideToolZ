// Settings.cpp : implementation file
//

#include "stdafx.h"
#include "Hide.h"
#include "Settings.h"
#include "afxdialogex.h"


// CSettings dialog

IMPLEMENT_DYNAMIC(CSettings, CDialogEx)

CSettings::CSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSettings::IDD, pParent)
{

}

CSettings::~CSettings()
{
}

void CSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettings, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CSettings::OnMuteOnHide)
	ON_BN_CLICKED(IDC_BUTTON1, &CSettings::OnApplyHotkey)
END_MESSAGE_MAP()


// CSettings message handlers


BOOL CSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	if (theApp.muteOnHide)
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(0);
	if (theApp.hkShift)
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(0);
	if (theApp.hkCtrl)
		((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(0);
	if (theApp.hkAlt)
		((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(0);
	if (theApp.hkWin)
		((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(0);
	
	int buf = 0;
	switch (theApp.hk)
	{
	case VK_F1: buf = 0; break;
	case VK_F2: buf = 1; break;
	case	VK_F3: 	buf = 2; 	break;
	case	VK_F4: 	buf = 3; 	break;
	case	VK_F5: 	buf = 4; 	break;
	case	VK_F6: 	buf = 5; 	break;
	case	VK_F7: 	buf = 6; 	break;
	case	VK_F8: 	buf = 7; 	break;
	case	VK_F9: 	buf = 8; 	break;
	case	VK_F10: 	buf = 9; 	break;
	case	VK_F11: 	buf = 10; 	break;
	case	VK_F12: 	buf = 11; 	break;
	case	0x30: 	buf = 12; 	break;
	case	0x31: 	buf = 13; 	break;
	case	0x32: 	buf = 14; 	break;
	case	0x33: 	buf = 15; 	break;
	case	0x34: 	buf = 16; 	break;
	case	0x35: 	buf = 17; 	break;
	case	0x36: 	buf = 18; 	break;
	case	0x37: 	buf = 19; 	break;
	case	0x38: 	buf = 20; 	break;
	case	0x39: 	buf = 21; 	break;

	case	0x41: 	buf = 22; 	break;
	case	0x42: 	buf = 23; 	break;
	case	0x43: 	buf = 24; 	break;
	case	0x44: 	buf = 25; 	break;
	case	0x45: 	buf = 26; 	break;
	case	0x46: 	buf = 27; 	break;
	case	0x47: 	buf = 28; 	break;
	case	0x48: 	buf = 29; 	break;
	case	0x49: 	buf = 30; 	break;
	case	0x4A: 	buf = 31; 	break;
	case	0x4B: 	buf = 32; 	break;
	case	0x4C: 	buf = 33; 	break;
	case	0x4D: 	buf = 34; 	break;
	case	0x4E: 	buf = 35; 	break;
	case	0x4F: 	buf = 36; 	break;
	case	0x50: 	buf = 37; 	break;
	case	0x51: 	buf = 38; 	break;
	case	0x52: 	buf = 39; 	break;
	case	0x53: 	buf = 40; 	break;
	case	0x54: 	buf = 41; 	break;
	case	0x55: 	buf = 42; 	break;
	case	0x56: 	buf = 43; 	break;
	case	0x57: 	buf = 44; 	break;
	case	0x58: 	buf = 45; 	break;
	case	0x59: 	buf = 46; 	break;
	case	0x5A: 	buf = 47; 	break;

	default:
		break;
	}
	((CComboBox*)GetDlgItem(IDC_COMBO))->SetCurSel(buf);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSettings::OnMuteOnHide()
{
	// TODO: Add your control notification handler code here
	theApp.muteOnHide = !theApp.muteOnHide;
}


void CSettings::OnApplyHotkey()
{
	// TODO: Add your control notification handler code here
	theApp.muteOnHide=((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	theApp.hkShift = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
	theApp.hkCtrl = ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck();;
	theApp.hkAlt = ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck();;
	theApp.hkWin = ((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck();

	int buf=0;
	switch (((CComboBox*)GetDlgItem(IDC_COMBO))->GetCurSel())
	{
	case 0: buf = VK_F1; break;
	case 1: buf = VK_F2; break;
	case 2: buf = VK_F3; break;
	case 3: buf = VK_F4; break;
	case 4: buf = VK_F5; break;
	case 5: buf = VK_F6; break;
	case 6: buf = VK_F7; break;
	case 7: buf = VK_F8; break;
	case 8: buf = VK_F9; break;
	case 9: buf = VK_F10; break;
	case 10: buf = VK_F11; break;
	case 11: buf = VK_F12; break; 
	case 12: buf = 0x30; break;
	case 13: buf = 0x31; break;
	case 14: buf = 0x32; break;
	case 15: buf = 0x33; break;
	case 16: buf = 0x34; break;
	case 17: buf = 0x35; break;
	case 18: buf = 0x36; break;
	case 19: buf = 0x37; break;
	case 20: buf = 0x38; break;
	case 21: buf = 0x39; break;

	case 22: buf = 0x41; break;
	case 23: buf = 0x42; break;
	case 24: buf = 0x43; break;
	case 25: buf = 0x44; break;
	case 26: buf = 0x45; break;
	case 27: buf = 0x46; break;
	case 28: buf = 0x47; break;
	case 29: buf = 0x48; break;
	case 30: buf = 0x49; break;
	case 31: buf = 0x4A; break;
	case 32: buf = 0x4B; break;
	case 33: buf = 0x4C; break;
	case 34: buf = 0x4D; break;
	case 35: buf = 0x4E; break;
	case 36: buf = 0x4F; break;
	case 37: buf = 0x50; break;
	case 38: buf = 0x51; break;
	case 39: buf = 0x52; break;
	case 40: buf = 0x53; break;
	case 41: buf = 0x54; break;
	case 42: buf = 0x55; break;
	case 43: buf = 0x56; break;
	case 44: buf = 0x57; break;
	case 45: buf = 0x58; break;
	case 46: buf = 0x59; break;
	case 47: buf = 0x5A; break;

	default:
		break;
	}
	theApp.hk = buf;

	int bufMOD = 0;
	if (theApp.hkShift)
		bufMOD |= MOD_SHIFT;
	if (theApp.hkAlt)
		bufMOD |= MOD_ALT;
	if (theApp.hkCtrl)
		bufMOD |= MOD_CONTROL;
	if (theApp.hkWin)
		bufMOD |= MOD_WIN;
	if (!UnregisterHotKey(GetParent()->GetSafeHwnd(), 49040))
		MessageBox(L"Error: Failed to unregister previous Hotkey.");
	if (!RegisterHotKey(GetParent()->GetSafeHwnd(), 49040, bufMOD, theApp.hk))
		MessageBox(L"Error: Failed to register Hotkey.");
}
