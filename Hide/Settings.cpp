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
	ON_BN_CLICKED(IDC_CHECK1, &CSettings::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CSettings message handlers


BOOL CSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	if (theApp.muteOnHide)
	{
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(1);
	}	
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSettings::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	theApp.muteOnHide = !theApp.muteOnHide;
}
