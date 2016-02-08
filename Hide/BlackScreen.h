#pragma once


// CBlackScreen dialog

class CBlackScreen : public CDialogEx
{
	DECLARE_DYNAMIC(CBlackScreen)

public:
	CBlackScreen(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBlackScreen();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
};
