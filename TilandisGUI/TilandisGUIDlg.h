
// TilandisGUIDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <string>
#include <locale>
#include <codecvt>

// from Tilandis/Utility.h
// TODO: move all Utility code into a separate DLL project? maybe?
namespace Utility {
	extern std::wstring basedir(std::wstring);

	typedef std::codecvt_utf8<wchar_t> UTF8;

	extern std::wstring_convert<UTF8, wchar_t> UTF8Converter;
}


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
	// Editbox: "Path or URL"
	CEdit EDT_PathBox;
	// Editbox: "Link Name"
	CEdit EDT_NameBox;

public:
	afx_msg void OnBnClickedPathbrowse();
	afx_msg void OnBnClickedRegisterprotocol();
	afx_msg void OnBnClickedWdbrowse();
	afx_msg void OnBnClickedDeletelink();

};
