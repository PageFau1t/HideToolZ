#pragma once
#include "../VolumeCtrl/VolumeCtrl.h"
#pragma comment(lib,"../debug/VolumeCtrl.lib")


// CSettings dialog

class CSettings : public CDialogEx
{
	DECLARE_DYNAMIC(CSettings)

public:
	CSettings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSettings();

// Dialog Data
	enum { IDD = IDD_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnMuteOnHide();
	afx_msg void OnApplyHotkey();
};
