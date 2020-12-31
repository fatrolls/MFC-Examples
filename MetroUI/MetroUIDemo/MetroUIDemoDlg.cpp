
// MetroUIDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MetroUIDemo.h"
#include "MetroUIDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 
// 用于应用程序“关于”菜单项的 CAboutDl g 对话框             
  
class CAboutDlg : public CDialog  
{
public:   
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX }; 

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持             

// 实现
protected: 
	DECLARE_MESSAGE_MAP() 
};  

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMetroUIDemoDlg 对话框




CMetroUIDemoDlg::CMetroUIDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMetroUIDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMetroUIDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMetroUIDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CMetroUIDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMetroUIDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMetroUIDemoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMetroUIDemoDlg 消息处理程序
#include <uxtheme.h>
#pragma comment(lib,"uxtheme.lib")
BOOL CMetroUIDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。  

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标   
	SetIcon(m_hIcon, FALSE);		// 设置小图标                   

	// TODO: 在此添加额外的初始 化代码   
	int a = GetSystemMetrics( SM_CYCAPTION );
	int b = GetSystemMetrics( SM_CXSIZEFRAME );
	int c = GetSystemMetrics( SM_CYSIZEFRAME );
	int d = GetSystemMetrics( SM_CXFIXEDFRAME );
	int e = GetSystemMetrics( SM_CYFIXEDFRAME );

	GetDlgItem( IDC_STATIC1 )->ModifyStyle( SS_LEFT,0 );

	CTabCtrl * pTabCtrl = (CTabCtrl *)GetDlgItem(IDC_TAB1);
	pTabCtrl->InsertItem( 0,_T("河南省") );
	pTabCtrl->InsertItem( 1,_T("湖北省") );
	pTabCtrl->InsertItem( 2,_T("湖南省") );

	//EnableThemeDialogTexture(m_hWnd,ETDT_ENABLE | ETDT_USETABTEXTURE);

	HBRUSH hBrush = ::CreateSolidBrush( 0x0000ff );
	int ret = SetClassLong( GetDlgItem(IDC_STATIC1)->m_hWnd,GCL_HBRBACKGROUND,(LONG)hBrush);
	GetDlgItem(IDC_STATIC1)->Invalidate();
	hBrush = (HBRUSH)GetClassLong( GetDlgItem(IDC_STATIC1)->m_hWnd,GCL_HBRBACKGROUND );
	DWORD error =GetLastError();

 
	return TRUE;  // 除非将焦点设置到控件，否则返 回 TRUE    
}

void CMetroUIDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMetroUIDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMetroUIDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMetroUIDemoDlg::OnBnClickedButton1()
{
	CFileDialog dlg( TRUE,0,0,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("所有文件 (*.*)|*.*||"),this );
	if( dlg.DoModal() == IDOK )
	{
		CString strFile = dlg.GetPathName();

		CFile file( strFile,CFile::modeRead );
		unsigned char buf[1];
		int len = file.GetLength();
		int i = 0;
		CString str,strText;
		while( i < len )
		{
			file.Read( buf,1 );
			i++;
			str.Format( _T("0x%02x,"),buf[0] );
			strText += str;
			if( i % 100 == 0 )
				strText += _T("\r\n");
		}
		SetDlgItemText( IDC_EDIT1,strText );
	}

}

void CMetroUIDemoDlg::OnBnClickedButton2()
{
	MessageBox( _T("大家好，我是系统确认框，MessageBox妹妹。\r\n\r\n我刚从韩国回来，希望大家还认得我。"),_T("提示"),MB_YESNOCANCEL | MB_ICONINFORMATION );  
} 

void CMetroUIDemoDlg::OnBnClickedButton3()
{
	BROWSEINFO   bf;  

    LPITEMIDLIST   lpitem;  

    memset(&bf,0,sizeof   BROWSEINFO);  

    bf.hwndOwner=m_hWnd;  

    bf.lpszTitle=_T("选择路径");  

    bf.ulFlags=BIF_RETURNONLYFSDIRS;     //属性你可自己选择  

    lpitem=SHBrowseForFolder(&bf);  

    if(lpitem==NULL)     //如果没有选择路径则返回   0   

        return  ;  


    //如果选择了路径则复制路径,返回路径长度   

	TCHAR buf[MAX_PATH] = { 0 };

    SHGetPathFromIDList(lpitem,buf); 

}
       