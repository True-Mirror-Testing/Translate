// DlgWriteConfig.cpp : implementation file
//

#include "pch.h"
#include "Translate.h"
#include "DlgWriteConfig.h"
#include "afxdialogex.h"


//Samuil Stoynov
// CDlgWriteConfig dialog

IMPLEMENT_DYNAMIC(CDlgWriteConfig, CDialogEx)

CDlgWriteConfig::CDlgWriteConfig(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WRITE_CONFIG, pParent)
{

}

CDlgWriteConfig::~CDlgWriteConfig()
{
}

void CDlgWriteConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON4, m_btnSave);
	DDX_Control(pDX, IDC_BUTTON1, m_btnLoad);
	DDX_Control(pDX, IDC_MFCEDITBROWSE2, m_ebSaveDir);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_ebLoadFile);
	DDX_Control(pDX, IDC_MFCVSLISTBOX1, m_lbWords);
	DDX_Control(pDX, IDC_EDIT2, m_ebFileName);
}


BEGIN_MESSAGE_MAP(CDlgWriteConfig, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgWriteConfig::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgWriteConfig::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgWriteConfig::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgWriteConfig message handlers


void CDlgWriteConfig::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString csLoadFile;
	m_ebLoadFile.GetWindowText(csLoadFile);
	if (csLoadFile != "")
	{
		theApp.m_csConfig = csLoadFile;
		MessageBox(_T("The file is saved"), _T("Message"), MB_ICONEXCLAMATION);
	}
	else
	{
		MessageBox(_T("Please, select the file"), _T("Warning"), MB_ICONEXCLAMATION);
	}
}


void CDlgWriteConfig::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CString csSaveDir;
	m_ebSaveDir.GetWindowText(csSaveDir);

	if (csSaveDir == "")
	{
		MessageBox(_T("Please, select the directory!"), _T("Warning"), MB_ICONEXCLAMATION);
		return;
	}

	CString FileName;
	m_ebFileName.GetWindowText(FileName);

	if (FileName == "")
	{
		MessageBox(_T("Please, write the file name!"), _T("Warning"), MB_ICONEXCLAMATION);
		return;
	}
	else
	{
		//check file format
		int i = FileName.ReverseFind('.');
		if (i > 0)
			FileName = FileName.Left(i);
	}


	CStdioFile file;
	if (m_lbWords.GetCount() > 0)
	{
		if (!file.Open(csSaveDir + "\\" + FileName + ".txt", CStdioFile::modeReadWrite | CStdioFile::modeCreate | CFile::shareDenyNone))
		{
			MessageBox(_T("Can not open the congig file!"), _T("Warning"), MB_ICONEXCLAMATION);
		}
		else
		{
			for (int y = 0; y < theApp.COL * 2; y++)
			{
				CString csword = m_lbWords.GetItemText(y);
				if (csword != "")
					file.WriteString(m_lbWords.GetItemText(y) + _T("\n"));
			}
			file.Close();
			MessageBox(_T("The file has been saved"), _T("Message"), MB_ICONEXCLAMATION);
		}
	}
	else
	{
		MessageBox(_T("There is no words"), _T("Warning"), MB_ICONEXCLAMATION);
	}
}

void CDlgWriteConfig::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString csLoadFile;
	CStdioFile file;
	CString csLine;

	m_ebLoadFile.GetWindowText(csLoadFile);
	
	if (csLoadFile == "")
	{
		MessageBox(_T("Please, select the file"), _T("Warning"), MB_ICONEXCLAMATION);
	}

	if (!file.Open(csLoadFile, CStdioFile::modeReadWrite  | CFile::shareDenyNone))
	{
		MessageBox(_T("Can not open the congig file"), _T("Warning"), MB_ICONEXCLAMATION);
	}
	else
	{
		//find path end file name
		int i = csLoadFile.ReverseFind('\\');
		CString pathName = csLoadFile.Left(i);

		CString fileName = csLoadFile.Right(csLoadFile.GetLength()-i-1);
		i = fileName.ReverseFind('.');
		if (i > 0)
			fileName = fileName.Left(i);

		
		m_ebFileName.SetWindowText(fileName);
		m_ebSaveDir.SetWindowText(pathName);

		//remove old words
		for (int i = m_lbWords.GetCount()-1; i> 0; i--)
		{
			m_lbWords.RemoveItem(i);
		}
		
		//write new words
		file.ReadString(csLine);
		while (csLine !="")
		{
			m_lbWords.AddItem(csLine);
			file.ReadString(csLine);
		}
		file.Close();
		
	}

}


BOOL CDlgWriteConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	//set file format
	m_ebLoadFile.EnableFileBrowseButton(_T("txt"), _T("Text files|*.txt||"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
