
// TranslateDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Translate.h"
#include "TranslateDlg.h"
#include "afxdialogex.h"

#include "DlgWriteConfig.h"

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


// CTranslateDlg dialog



CTranslateDlg::CTranslateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRANSLATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_index = 0;
	m_incorrect_count = theApp.COL - 1;
	m_count_all = theApp.COL * 2;
}

void CTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, m_edit_from);
	DDX_Control(pDX, IDC_EDIT6, m_edit_to);
	DDX_Control(pDX, IDC_EDIT1, m_edit_original);
	DDX_Control(pDX, IDC_EDIT3, m_edit_translation);
	DDX_Control(pDX, IDC_EDIT2, m_edit_correct);
	DDX_Control(pDX, IDC_CHECK1, m_check_spelling);
	DDX_Control(pDX, IDC_EDIT5, m_edit_count);
}

BEGIN_MESSAGE_MAP(CTranslateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTranslateDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CTranslateDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTranslateDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTranslateDlg::OnBnClickedButton3)
	ON_WM_CLOSE()
	ON_COMMAND(ID_WRITEACONFIGFILE_WRITEACONFIGFILE, &CTranslateDlg::OnWriteaconfigfileWriteaconfigfile)
END_MESSAGE_MAP()


// CTranslateDlg message handlers

BOOL CTranslateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: Add extra initialization here
	

	/*TCHAR buffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buffer);
	CString path = (CString)buffer; */

	/*task parse string 
	CString myDir;
	int i;
	CString test = path;

	while (test != "")
	{
		i = test.Find("\\");
		if (i >= 0)
		{
			myDir += test.Left(i)+  ", ";
			test = test.Right(test.GetLength() - i -1);
		}
		else
		{
			test = "";
		}
	}*/

	OnWriteaconfigfileWriteaconfigfile();
	
	m_edit_from.SetWindowText(theApp.arrWords[0][0]);
	m_edit_to.SetWindowText(theApp.arrWords[1][0]);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTranslateDlg::IncorectCount(int* count, bool flag)
{
	if (flag)
	{
		(*count)--;
	}
	else
	{
		*count = (m_count_all-2)/2;
	}

	CString cs_MyStr;
	cs_MyStr.Format(_T("%d"), *count);
	cs_MyStr += _T(" words");
	m_edit_count.SetWindowText(cs_MyStr);
}

void CTranslateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTranslateDlg::OnPaint()
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
HCURSOR CTranslateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTranslateDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if (m_incorrect_count == 0)
	{
		int i = MessageBox(_T("You know all words :) Do you want to restart the dictionary?"), _T("Congratulation!"), MB_ICONINFORMATION | MB_OK | MB_OKCANCEL);
		if (IDCANCEL != i)
		{
			OnBnClickedButton3();
		}
		return;
	}

	srand((unsigned)time(NULL));
	int i;
	int index;
	do
	{
		i = rand();
		if (m_count_all > 4)
			index = i % ((m_count_all) / 2);
		else
			index = 1;

	} while (theApp.arrWords[0][index] == "" || index == 0 || arrCorect[index - 1]);

	m_edit_original.SetWindowText(theApp.arrWords[0][index]);
	m_index = index;
	m_edit_translation.SetWindowText(_T(""));
	m_edit_correct.SetWindowText(_T(""));

}


void CTranslateDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	if (m_check_spelling.GetCheck())
	{ 
		m_edit_translation.SetReadOnly(true);
		m_edit_translation.SetWindowText(_T(""));
	}
	else
	{
		m_edit_translation.SetReadOnly(false);
	}

}


void CTranslateDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString csOrig;
	m_edit_original.GetWindowText(csOrig);
	if (csOrig.Trim() == "")
	{
		MessageBox(_T("Click on \"Get Word\" Button!"), _T("Warning"), MB_ICONEXCLAMATION);
		return;
	}

	if (!m_check_spelling.GetCheck())
	{
		CString csTranslation;
		m_edit_translation.GetWindowText(csTranslation);
		if (csTranslation == theApp.arrWords[1][m_index])
		{
			CString csCorrect;
			m_edit_correct.GetWindowText(csCorrect);
			if (csCorrect == _T(""))
			{
				//m_incorrect_count--;
				IncorectCount(&m_incorrect_count, true);
			}
			arrCorect[m_index - 1] = true;
			m_edit_correct.SetWindowText(theApp.arrWords[1][m_index]);
			m_edit_translation.SetWindowText(_T(""));
		}
		else
		{
			m_edit_translation.SetWindowText(_T(""));
		}
		if(csTranslation =="")
		{
			MessageBox(_T("Write the word!"), _T("Warning"), MB_ICONEXCLAMATION);			
		}
	}
	else
	{
		m_edit_correct.SetWindowText(theApp.arrWords[1][m_index]);

	}
	
}

//this is a comment yay
void CTranslateDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	m_edit_translation.SetWindowText(_T(""));
	m_edit_correct.SetWindowText(_T(""));
	m_edit_original.SetWindowText(_T(""));
	//m_incorrect_count = COL-1;
	IncorectCount(&m_incorrect_count, false);

	for (int i = 0; i < theApp.COL - 1; i++)
	{
		arrCorect[i] = false;
	}

	//Maria Stoynova
	//Fixes #1
}


void CTranslateDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
//	MessageBox(_T("Come back soon!"), _T("Bye!"), MB_ICONEXCLAMATION);

	CDialogEx::OnClose();
}


void CTranslateDlg::OnWriteaconfigfileWriteaconfigfile()
{
	// TODO: Add your command handler code here
	CStdioFile file;

	CDlgWriteConfig dlgConfigFile;
	dlgConfigFile.DoModal();

	//test changes

	if (theApp.m_csConfig != "")
	{
		if (!file.Open(theApp.m_csConfig, CStdioFile::modeRead | CFile::shareDenyNone))
		{
			MessageBox(_T("Can not open the congig file"), _T("Warning"), MB_ICONEXCLAMATION);
		}
		else
		{
			int i = 0;
			int iCount = 0;
			CString csLine;

			m_count_all = 0;

			while (iCount < theApp.COL * 2)
			{
				file.ReadString(csLine);
				i = iCount / 2;
				if (csLine != "")
				{
					m_count_all++;
					if (iCount % 2)
						theApp.arrWords[1][i] = csLine.Trim();// MakeUpper() or MakeLower() ??
					else
						theApp.arrWords[0][i] = csLine.Trim();
				}
				else
				{

					if (iCount % 2)
						theApp.arrWords[1][i] = "";// MakeUpper() or MakeLower() ??
					else
						theApp.arrWords[0][i] = "";
				}
				iCount++;
			}

			file.Close();
		}
	}

	OnBnClickedButton3();
}
