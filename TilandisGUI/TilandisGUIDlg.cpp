
// TilandisGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TilandisGUI.h"
#include "TilandisGUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTilandisGUIDlg dialog



CTilandisGUIDlg::CTilandisGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TILANDISGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTilandisGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REGISTERPROTOCOL, BTN_RegisterProtocol);
}

BEGIN_MESSAGE_MAP(CTilandisGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_REGISTERPROTOCOL, &CTilandisGUIDlg::OnBnClickedRegisterprotocol)
	ON_BN_CLICKED(IDC_PATHBROWSE, &CTilandisGUIDlg::OnBnClickedPathbrowse)
END_MESSAGE_MAP()


// CTilandisGUIDlg message handlers

BOOL CTilandisGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Add a UAC shield to the Register Tilandis button
	// the shield itself doesn't actually do jack in the way of shit, the request for
	// administrator rights comes from the "runas" verb in ShellExecute
	BTN_RegisterProtocol.SetShield(TRUE);
	// BULLSHIT: Whoever wrote the documentation for this function better have been fucking fired
	//			 by now. It's listed on MSDN as "SetElevationRequired" (a method that doesn't exist)
	//			 and says it takes a true C++ bool when instead it takes one of those oddball BOOL
	//			 types that are actually just ints (UPPERCASE vs lowercase)

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTilandisGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTilandisGUIDlg::OnPaint()
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
HCURSOR CTilandisGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTilandisGUIDlg::OnBnClickedRegisterprotocol()
{
	ShellExecute(NULL, L"runas", L"Tilandis.exe", L"-r tilecreator", NULL, SW_SHOWDEFAULT);
}


void CTilandisGUIDlg::OnBnClickedPathbrowse()
{
	IFileDialog *openbox = NULL;
	COMDLG_FILTERSPEC filters[] = {
		{L"Executable files", L"*.exe"},
		{L"All files (yes, this works!)", L"*.*"}
	};
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&openbox));

	if (!SUCCEEDED(hr)) {
		MessageBox(L"Failed to create a file dialog.", L"Tilandis GUI");
		return;
	}

	openbox->SetFileTypes(2, filters);
	openbox->SetTitle(L"Program (or file) to launch");

	hr = openbox->Show(m_hWnd);
	if (SUCCEEDED(hr)) {
		CComPtr<IShellItem> pItem;
		if (!SUCCEEDED(openbox->GetResult(&pItem))) {
			return;
		}
		LPOLESTR dispname = NULL;
		pItem->GetDisplayName(SIGDN_FILESYSPATH, &dispname); // *dispname == "C:\Some\Path\File.name"

		SetDlgItemText(IDC_PATHBOX, (LPWSTR)dispname);
	}
}
