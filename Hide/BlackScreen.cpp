// BlackScreen.cpp : implementation file
//

#include "stdafx.h"
#include "Hide.h"
#include "BlackScreen.h"
#include "afxdialogex.h"


// CBlackScreen dialog

IMPLEMENT_DYNAMIC(CBlackScreen, CDialogEx)

CBlackScreen::CBlackScreen(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBlackScreen::IDD, pParent)
{

}

CBlackScreen::~CBlackScreen()
{
}

void CBlackScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBlackScreen, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBlackScreen message handlers

//ÆÁ±Î»Ø³µºÍESC  
BOOL CBlackScreen::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CBlackScreen::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	RECT rect;
	rect.left = 0;
	rect.right = 1920;
	rect.top = 0;
	rect.bottom = 1080;

	dc.FillSolidRect(&rect, RGB(0, 0, 0));
}
