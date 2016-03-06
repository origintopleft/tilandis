
// TilandisGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TilandisGUI.h"
#include "TilandisGUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// from Tilandis/Utility.cpp
// there's a TODO in TilandisGUIDlg.h about this
std::wstring_convert<Utility::UTF8, wchar_t> Utility::UTF8Converter;

std::wstring Utility::basedir(std::wstring path) {
	size_t lastslash = path.find_last_of(L"\\"); // ignoring forward slash
	if (lastslash != path.npos) {
		return path.substr(0, lastslash);
	}
	else {
		return path; // probably a URL
	}
}


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
	DDX_Control(pDX, IDC_PATHBOX, EDT_PathBox);
	DDX_Control(pDX, IDC_NAMEBOX, EDT_NameBox);
	DDX_Control(pDX, IDC_WDBOX, EDT_WDBox);
	DDX_Control(pDX, IDC_ARGSBOX, EDT_ArgBox);
}

BEGIN_MESSAGE_MAP(CTilandisGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_REGISTERPROTOCOL, &CTilandisGUIDlg::OnBnClickedRegisterprotocol)
	ON_BN_CLICKED(IDC_PATHBROWSE, &CTilandisGUIDlg::OnBnClickedPathbrowse)
	ON_BN_CLICKED(IDC_WDBROWSE, &CTilandisGUIDlg::OnBnClickedWdbrowse)
	ON_BN_CLICKED(IDC_DELETELINK, &CTilandisGUIDlg::OnBnClickedDeletelink)
	ON_BN_CLICKED(IDC_CREATELINK, &CTilandisGUIDlg::OnBnClickedCreatelink)
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

		EDT_PathBox.SetWindowText((LPWSTR)dispname);
	}
}


void CTilandisGUIDlg::OnBnClickedWdbrowse()
{
	IFileDialog *openbox = NULL;
	HRESULT hr_result = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&openbox));
	DWORD openbox_opts;
	openbox->GetOptions(&openbox_opts);
	openbox->SetOptions(openbox_opts | FOS_PICKFOLDERS);

	wchar_t str_path[MAX_PATH];
	int int_result = EDT_PathBox.GetWindowText((LPTSTR) &str_path, MAX_PATH);

	if (str_path > 0) {
		std::wstring wstr_path = std::wstring(str_path);
		std::wstring wstr_basedir = Utility::basedir(wstr_path);

		IShellItem* startdir;
		hr_result = SHCreateItemFromParsingName(wstr_basedir.c_str(), NULL, IID_PPV_ARGS(&startdir));
		if (SUCCEEDED(hr_result)) { openbox->SetFolder(startdir); }
	}
	
	hr_result = openbox->Show(m_hWnd);
	if (SUCCEEDED(hr_result)) {
		CComPtr<IShellItem> pItem;
		if (!SUCCEEDED(openbox->GetResult(&pItem))) {
			return;
		}
		LPOLESTR dispname = NULL;
		pItem->GetDisplayName(SIGDN_FILESYSPATH, &dispname); // *dispname == "C:\Some\Path"

		EDT_WDBox.SetWindowText((LPWSTR) dispname);
	}
}


void CTilandisGUIDlg::OnBnClickedDeletelink()
{
	LPWSTR str_name[512];
	for (int i = 0; i < 512; i++) {
		str_name[i] = '\0';
	}
	int length = EDT_NameBox.GetWindowText((LPTSTR) str_name, 512);
	if (length < 1) {
		MessageBox(L"You're supposed to put a link name in the box to the left. (That's the thing you type into TileCreator)", L"Tilandis GUI Error", MB_ICONERROR);
		return;
	}

	wchar_t str_args[768];
	for (int i = 0; i < 768; i++) {
		str_args[i] = '\0';
	}

	wcscat_s(str_args, (size_t) 768, L"-d ");
	wcscat_s(str_args, (size_t) 768, (const wchar_t*) str_name);

	ShellExecute(NULL, NULL, L"Tilandis.exe", str_args, NULL, 0);
}


void CTilandisGUIDlg::OnBnClickedCreatelink()
{
	int length;
	LPWSTR str_name[512];
	for (int i = 0; i < 512; i++) {
		str_name[i] = '\0';
	}
	length = EDT_NameBox.GetWindowText((LPTSTR) str_name, 512);
	if (length < 1) {
		MessageBox(L"You're supposed to put a link name in the box to the left. (That's the thing you type into TileCreator)", L"Tilandis GUI Error", MB_ICONERROR);
		return;
	}

	// String containing the full list of arguments to Tilandis
	wchar_t str_args[2048]; // Create args could run for a lot longer
	for (int i = 0; i < 2048; i++) {
		str_args[i] = '\0';
	}

	// Name
	wcscat_s(str_args, (size_t) 2048, L"-n \"");
	wcscat_s(str_args, (size_t) 2048, (const wchar_t*) str_name);
	wcscat_s(str_args, (size_t) 2048, L"\"");

	// Path
	LPWSTR str_path[MAX_PATH];
	length = EDT_PathBox.GetWindowText((LPTSTR) str_path, MAX_PATH);
	if (length < 1) {
		MessageBox(L"You need to specify a path. This is the thing you actually launch.");
		return;
	}

	wcscat_s(str_args, (size_t) 2048, L" -p \"");
	wcscat_s(str_args, (size_t) 2048, (const wchar_t*) str_path);
	wcscat_s(str_args, (size_t) 2048, L"\"");

	// Working directory
	LPWSTR str_workdir[MAX_PATH];
	for (int i = 0; i < MAX_PATH; i++) {
		str_workdir[i] = '\0';
	}
	length = EDT_WDBox.GetWindowText((LPTSTR) str_workdir, MAX_PATH);
	if (length > 0) {
		// User specified a working directory, lets define it
		// We skip this arg if the user does, because the code to automatically determine the path is already
		// in Tilandis itself (specifically, linkmgmt.cpp)
		wcscat_s(str_args, (size_t) 2048, L" -w \"");
		wcscat_s(str_args, (size_t) 2048, (const wchar_t*) str_workdir);
		wcscat_s(str_args, (size_t) 2048, L"\"");
	}
	
	// Arguments
	LPWSTR str_linkargs[1024];
	for (int i = 0; i < 1024; i++) {
		str_linkargs[i] = '\0';
	}
	length = EDT_ArgBox.GetWindowText((LPTSTR) str_linkargs, 1024);
	if (length > 0) {
		// User specified args, lets define it
		// We skip this arg if the user does, because no args = do nada
		// Before we get into that though, we need to properly escape quotation marks
		// that's easier to do with wstrings
		// TODO: this is twiddly and somehow manages to replace the entire thing with just \"
		std::wstring wstr_linkargs = (wchar_t*) str_linkargs;
		wstr_linkargs.replace(wstr_linkargs.begin(), wstr_linkargs.end(), L"\"", L"\\\"");

		// now we append the result to str_args
		wcscat_s(str_args, (size_t) 2048, L" -a \"");
		wcscat_s(str_args, (size_t) 2048, wstr_linkargs.c_str());
		wcscat_s(str_args, (size_t) 2048, L"\"");
	}

	MessageBox((LPCWSTR) str_args);
	ShellExecute(NULL, NULL, L"Tilandis.exe", str_args, NULL, 0);
}
