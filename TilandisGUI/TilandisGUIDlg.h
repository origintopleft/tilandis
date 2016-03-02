
// TilandisGUIDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CTilandisGUIDlg dialog
class CTilandisGUIDlg : public CDialogEx
{
// Construction
public:
	CTilandisGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TILANDISGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// Button: "Register Tilandis"
	CButton BTN_RegisterProtocol;

public:
	afx_msg void OnBnClickedPathbrowse();
	afx_msg void OnBnClickedRegisterprotocol();
};
