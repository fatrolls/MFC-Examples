// AnalyzerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HttpAnalyzer.h"
#include "AnalyzerDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnalyzerDlg dialog


CAnalyzerDlg::CAnalyzerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnalyzerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnalyzerDlg)
	_szheader = _T("");
	_szsource = _T("");
	_szurl = _T("");
	//}}AFX_DATA_INIT
}


void CAnalyzerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnalyzerDlg)
	DDX_Text(pDX, IDC_HEADER, _szheader);
	DDX_Text(pDX, IDC_SOURCE, _szsource);
	DDX_Text(pDX, IDC_URL, _szurl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnalyzerDlg, CDialog)
	//{{AFX_MSG_MAP(CAnalyzerDlg)
	ON_BN_CLICKED(IDC_GO, OnGo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalyzerDlg message handlers

void CAnalyzerDlg::OnGo() {
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	_szsource="";
	_szheader="";
	
	if(_pclient->Connect((const char*)_szurl)){
		if(_pclient->Request(_pclient->GetURI())){
			unsigned char buf[1024]="\0";
			_pclient->QueryRawHeader(buf, 1024);
			_szheader=buf;
			memset(buf, 0x00, 1024);
			while(_pclient->Response(buf, 1024)){
				_szsource+=buf;
				memset(buf, 0x00, 1024);
			}

			char szpath[1024];
			::GetCurrentDirectory(1024, szpath);
			strcat(szpath, "\\tmp.html");

			HANDLE file=(HANDLE)::CreateFile(szpath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			unsigned long nw=0;
			WriteFile(file, (const char*)_szsource, _szsource.GetLength(), &nw, NULL);
			::CloseHandle(file);
		}
		_pclient->Close();
	}
	
	UpdateData(FALSE);

	_pview->doShow();
}
