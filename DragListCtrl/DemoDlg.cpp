#include "stdafx.h"
#include "Resource.h"
#include "DemoDlg.h"



//设置类成为通用版本
#ifdef	_UNICODE
#define titoa _itow	
#else	
#define titoa	_itoa
#endif	



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CDemoDlg::CDemoDlg(CWnd* pParent)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl2);
	DDX_Control(pDX, IDC_LIST3, m_ListCtrl3);
	DDX_Control(pDX, IDC_LIST4, m_ListBox1);
	DDX_Control(pDX, IDC_LIST5, m_ListBox2);
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);			// Set big icon
	::SetWindowPos(m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE); //设置窗口最顶
 	static CLoadMyLibrary inst(m_hWnd);
	//-----------------------------------------------------------------------------

/****************************************************************************
初始化list1 的数据
****************************************************************************/

	//设置扩展样式
	DWORD dwStyle = m_ListCtrl.GetExtendedStyle();		//获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT;				//选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES;					//网格线（report风格时）
//	dwStyle |= LVS_EX_CHECKBOXES;					//item前生成checkbox控件
//	dwStyle |= LVS_SHOWSELALWAYS;			//不要在这里设置，在控件属性里设置,否则显示会有问题
//	dwStyle |= LVS_SHAREIMAGELISTS			//如果一个程序里有两个Listctrl同用一个HIMAGELIST，则其中一个摧毁不会影响另外一个，Specifies that the control does not take ownership of the image lists assigned to it (that is, it does not destroy the image lists when it is destroyed). This style enables the same image lists to be used with multiple list view controls.
	m_ListCtrl.SetExtendedStyle(dwStyle);				//设置扩展风格

	SHFILEINFO shFinfo;
	//获取系统小图标
	HIMAGELIST hImageListSmall=(HIMAGELIST)::SHGetFileInfo(_T("c:\\"),0,&shFinfo,sizeof(SHFILEINFO),
						SHGFI_SYSICONINDEX|	SHGFI_SMALLICON);

	//获取系统大图标
	 HIMAGELIST hImageListLarge=(HIMAGELIST)::SHGetFileInfo(_T(""),0,&shFinfo,sizeof(SHFILEINFO),
						SHGFI_SYSICONINDEX|	SHGFI_ICON);
	
	m_ListCtrl.SetImageList(CImageList::FromHandle(hImageListSmall),LVSIL_SMALL);
	m_ListCtrl.SetImageList(CImageList::FromHandle(hImageListLarge),LVSIL_NORMAL);
	
	//设置列
	m_ListCtrl.InsertColumn(0,   _T("第一列"),   LVCFMT_LEFT,   60);   
	m_ListCtrl.InsertColumn(1,   _T("第二列"),   LVCFMT_LEFT,   60);   
	m_ListCtrl.InsertColumn(2,   _T("第三列"),   LVCFMT_LEFT,   100);   

	TCHAR buf[20];
	for(int j=0;j<30;j++)
	{
		titoa(j,buf,10);
		
		//插入参数
		int nRow = m_ListCtrl.InsertItem(m_ListCtrl.GetItemCount(), buf,0);//插入1行"11"代表第0列的数据 参数(行数,标题,图标索引)
		titoa(j+100,buf,10);
		m_ListCtrl.SetItemText(nRow, 1, buf);	
		titoa(j+1000,buf,10);
		m_ListCtrl.SetItemText(nRow, 2, _T("CtrlList1"));		
	}
	


/****************************************************************************
初始化list2 的数据
****************************************************************************/

	{
		//设置扩展样式
		DWORD dwStyle = m_ListCtrl2.GetExtendedStyle();		//获取当前扩展样式
		dwStyle |= LVS_EX_FULLROWSELECT;				//选中某行使整行高亮（report风格时）
		dwStyle |= LVS_EX_GRIDLINES;					//网格线（report风格时）
		//	dwStyle |= LVS_EX_CHECKBOXES;					//item前生成checkbox控件
		//	dwStyle |= LVS_SHOWSELALWAYS;			//不要在这里设置，在控件属性里设置,否则显示会有问题
		//	dwStyle |= LVS_SHAREIMAGELISTS			//如果一个程序里有两个Listctrl同用一个HIMAGELIST，则其中一个摧毁不会影响另外一个，Specifies that the control does not take ownership of the image lists assigned to it (that is, it does not destroy the image lists when it is destroyed). This style enables the same image lists to be used with multiple list view controls.
		m_ListCtrl2.SetExtendedStyle(dwStyle);				//设置扩展风格

		SHFILEINFO shFinfo;
		//获取系统小图标
		HIMAGELIST hImageListSmall=(HIMAGELIST)::SHGetFileInfo(_T("c:\\"),0,&shFinfo,sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX|	SHGFI_SMALLICON);

		//获取系统大图标
		HIMAGELIST hImageListLarge=(HIMAGELIST)::SHGetFileInfo(_T(""),0,&shFinfo,sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX|	SHGFI_ICON);

		m_ListCtrl2.SetImageList(CImageList::FromHandle(hImageListSmall),LVSIL_SMALL);
		m_ListCtrl2.SetImageList(CImageList::FromHandle(hImageListLarge),LVSIL_NORMAL);

		//设置列
		m_ListCtrl2.InsertColumn(0,   _T("第一列"),   LVCFMT_LEFT,   60);   
		m_ListCtrl2.InsertColumn(1,   _T("第二列"),   LVCFMT_LEFT,   60);   
		m_ListCtrl2.InsertColumn(2,   _T("第三列"),   LVCFMT_LEFT,   100);   

		TCHAR buf[20];
		for(int j=0;j<3;j++)
		{
			titoa(j,buf,10);

			//插入参数
			int nRow = m_ListCtrl2.InsertItem(m_ListCtrl2.GetItemCount(), buf,0);//插入1行"11"代表第0列的数据 参数(行数,标题,图标索引)
			titoa(j+200,buf,10);
			m_ListCtrl2.SetItemText(nRow, 1, buf);	
			titoa(j+1000,buf,10);
			m_ListCtrl2.SetItemText(nRow, 2, _T("CtrlList2"));		
		}

	}


/****************************************************************************
初始化list3 的数据
****************************************************************************/

	{
		//设置扩展样式
		DWORD dwStyle = m_ListCtrl3.GetExtendedStyle();		//获取当前扩展样式
		dwStyle |= LVS_EX_FULLROWSELECT;				//选中某行使整行高亮（report风格时）
		dwStyle |= LVS_EX_GRIDLINES;					//网格线（report风格时）
		//	dwStyle |= LVS_EX_CHECKBOXES;					//item前生成checkbox控件
		//	dwStyle |= LVS_SHOWSELALWAYS;			//不要在这里设置，在控件属性里设置,否则显示会有问题
		//	dwStyle |= LVS_SHAREIMAGELISTS			//如果一个程序里有两个Listctrl同用一个HIMAGELIST，则其中一个摧毁不会影响另外一个，Specifies that the control does not take ownership of the image lists assigned to it (that is, it does not destroy the image lists when it is destroyed). This style enables the same image lists to be used with multiple list view controls.
		m_ListCtrl3.SetExtendedStyle(dwStyle);				//设置扩展风格

		SHFILEINFO shFinfo;
		//获取系统小图标
		HIMAGELIST hImageListSmall=(HIMAGELIST)::SHGetFileInfo(_T("c:\\"),0,&shFinfo,sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX|	SHGFI_SMALLICON);

		//获取系统大图标
		HIMAGELIST hImageListLarge=(HIMAGELIST)::SHGetFileInfo(_T(""),0,&shFinfo,sizeof(SHFILEINFO),
			SHGFI_SYSICONINDEX|	SHGFI_ICON);

		m_ListCtrl3.SetImageList(CImageList::FromHandle(hImageListSmall),LVSIL_SMALL);
		m_ListCtrl3.SetImageList(CImageList::FromHandle(hImageListLarge),LVSIL_NORMAL);

		//设置列
		m_ListCtrl3.InsertColumn(0,   _T("第一列"),   LVCFMT_LEFT,   60);   
		m_ListCtrl3.InsertColumn(1,   _T("第二列"),   LVCFMT_LEFT,   60);   
		m_ListCtrl3.InsertColumn(2,   _T("第三列"),   LVCFMT_LEFT,   100);   

		TCHAR buf[20];
		for(int j=0;j<30;j++)
		{
			titoa(j,buf,10);

			//插入参数
			int nRow = m_ListCtrl3.InsertItem(m_ListCtrl3.GetItemCount(), buf,0);//插入1行"11"代表第0列的数据 参数(行数,标题,图标索引)
			titoa(j+300,buf,10);
			m_ListCtrl3.SetItemText(nRow, 1, buf);	
			titoa(j+1000,buf,10);
			m_ListCtrl3.SetItemText(nRow, 2, _T("CtrlList3"));		
		}

	}

/****************************************************************************

****************************************************************************/
	{
		TCHAR buf[20];
		for(int j=0;j<30;j++)
		{
			titoa(j,buf,10);
			m_ListBox1.AddString(buf);

			_tcscat(buf,_T("  List2"));
			m_ListBox2.AddString(buf);
		}
	}

	return TRUE;  
}






