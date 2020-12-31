// IgnoreDlg.cpp : implementation file
//

#include "stdafx.h"
#include "crashfinder.h"
#include "IgnoreDlg.h"
#include "binaryImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIgnoreDlg dialog


CIgnoreDlg::CIgnoreDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIgnoreDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIgnoreDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CIgnoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIgnoreDlg)
	DDX_Control(pDX, IDC_IGNORELIST, m_IgnoreList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIgnoreDlg, CDialog)
	//{{AFX_MSG_MAP(CIgnoreDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIgnoreDlg message handlers

void CIgnoreDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CFileDialog filedlg(FALSE, _T("exe"), NULL, OFN_FILEMUSTEXIST, 
		_T("Binary Image (*.exe; *.dll; *.ocx) | *.exe;*.dll;*.ocx ||"), this);
	if (filedlg.DoModal()==IDOK)
	{
		if (m_IgnoreList.FindString(-1, filedlg.GetPathName())==LB_ERR)
		{
			int Index=m_IgnoreList.AddString(filedlg.GetPathName());
			if (Index!=LB_ERR)
			{
				m_IgnoreList.SetCheck(Index, 1);
			}
		}
		else
		{
			MessageBox(_T("This image has already existed!"));
		}
	}
}

void CIgnoreDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	int selcount=m_IgnoreList.GetSelCount();
	if (selcount>0)
	{
		CString deleteValue;
		int* pIndex=new int[selcount];
		selcount=m_IgnoreList.GetSelItems(selcount, pIndex);
		for (int i=selcount-1;i>=0;i--)
		{
			m_IgnoreList.GetText(pIndex[i], deleteValue);
			m_DeleteList[deleteValue]=NULL;
			m_IgnoreList.DeleteString(pIndex[i]);
		}
		delete []pIndex;
	}
}

BOOL CIgnoreDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMapStringToPtr ignoreList;
	CBinaryImage::InitIgnoredImage(ignoreList);
	CString imageName;
	LPVOID pPtr;
	POSITION pos=ignoreList.GetStartPosition();
	while (pos!=NULL)
	{
		ignoreList.GetNextAssoc(pos, imageName, pPtr);
		int Index=m_IgnoreList.AddString(imageName);
		if (Index!=LB_ERR)
		{
			if (pPtr!=NULL)
			{
				m_IgnoreList.SetCheck(Index, 1);
			}
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIgnoreDlg::OnOK()
{
	HKEY hkey;
	DWORD disposition;
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\MSJ\\CRASHFINDER"), 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, &disposition)
		==ERROR_SUCCESS)
	{
		CString szValueName;
		LPVOID pPtr;
		DWORD data;
		POSITION pos=m_DeleteList.GetStartPosition();
		while (pos!=NULL)
		{
			m_DeleteList.GetNextAssoc(pos, szValueName, pPtr);
			RegDeleteValue(hkey, szValueName);
		}
		int count=m_IgnoreList.GetCount();
		for (int i=0;i<count;i++)
		{
			m_IgnoreList.GetText(i, szValueName);
			szValueName.MakeUpper();
			if (m_IgnoreList.GetCheck(i)==1)
			{
				data=1;
			}
			else
			{
				data=0;
			}
			RegSetValueEx(hkey, szValueName, 0, REG_DWORD, (LPBYTE)&data, sizeof(data));
		}
		RegCloseKey(hkey);
	}
	CDialog::OnOK();
}
