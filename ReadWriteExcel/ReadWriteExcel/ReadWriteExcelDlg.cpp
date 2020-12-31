
// ReadWriteExcelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadWriteExcel.h"
#include "ReadWriteExcelDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "Application.h"
#include "Workbooks.h"
#include "Workbook.h"
#include "Worksheets.h"
#include "Worksheet.h"
#include "Range.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReadWriteExcelDlg 对话框




IMPLEMENT_DYNAMIC(CReadWriteExcelDlg, CDialogEx);

CReadWriteExcelDlg::CReadWriteExcelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReadWriteExcelDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CReadWriteExcelDlg::~CReadWriteExcelDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CReadWriteExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CReadWriteExcelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CReadWriteExcelDlg 消息处理程序

BOOL CReadWriteExcelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// TODO: 在此添加额外的初始化代码

	m_ListCtrl.SetExtendedStyle(LVS_REPORT | LVS_EX_FULLROWSELECT);

	CApplication ExcelApp;
	CWorkbooks books;
	CWorkbook book;
	CWorksheets sheets;
	CWorksheet sheet;
	CRange range;
	LPDISPATCH lpDisp = NULL;

	//创建Excel 服务器(启动Excel)
	if(!ExcelApp.CreateDispatch(_T("Excel.Application"),NULL))
	{
		AfxMessageBox(_T("启动Excel服务器失败!"));
		return -1;
	}

	/*判断当前Excel的版本*/
	CString strExcelVersion = ExcelApp.get_Version();
	int iStart = 0;
	strExcelVersion = strExcelVersion.Tokenize(_T("."), iStart);
	if (_T("11") == strExcelVersion)
	{
		AfxMessageBox(_T("当前Excel的版本是2003。"));
	}
	else if (_T("12") == strExcelVersion)
	{
		AfxMessageBox(_T("当前Excel的版本是2007。"));
	}
	else
	{
		AfxMessageBox(_T("当前Excel的版本是其他版本。"));
	}

	ExcelApp.put_Visible(TRUE);
	ExcelApp.put_UserControl(FALSE);

	/*得到工作簿容器*/
	books.AttachDispatch(ExcelApp.get_Workbooks());

	/*打开一个工作簿，如不存在，则新增一个工作簿*/
	CString strBookPath = _T("C:\\tmp.xls");
	try
	{
		/*打开一个工作簿*/
		lpDisp = books.Open(strBookPath, 
			vtMissing, vtMissing, vtMissing, vtMissing, vtMissing,
			vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, 
			vtMissing, vtMissing, vtMissing, vtMissing);
		book.AttachDispatch(lpDisp);
	}
	catch(...)
	{
		/*增加一个新的工作簿*/
		lpDisp = books.Add(vtMissing);
		book.AttachDispatch(lpDisp);
	}
	

	/*得到工作簿中的Sheet的容器*/
	sheets.AttachDispatch(book.get_Sheets());

	/*打开一个Sheet，如不存在，就新增一个Sheet*/
	CString strSheetName = _T("NewSheet");
	try
	{
		/*打开一个已有的Sheet*/
		lpDisp = sheets.get_Item(_variant_t(strSheetName));
		sheet.AttachDispatch(lpDisp);
	}
	catch(...)
	{
		/*创建一个新的Sheet*/
		lpDisp = sheets.Add(vtMissing, vtMissing, _variant_t((long)1), vtMissing);
		sheet.AttachDispatch(lpDisp);
		sheet.put_Name(strSheetName);
	}

	system("pause");

	/*向Sheet中写入多个单元格,规模为10*10 */
	lpDisp = sheet.get_Range(_variant_t("A1"), _variant_t("J10"));
	range.AttachDispatch(lpDisp);

	VARTYPE vt = VT_I4; /*数组元素的类型，long*/
	SAFEARRAYBOUND sabWrite[2]; /*用于定义数组的维数和下标的起始值*/
	sabWrite[0].cElements = 10;
	sabWrite[0].lLbound = 0;
	sabWrite[1].cElements = 10;
	sabWrite[1].lLbound = 0;

	COleSafeArray olesaWrite;
	olesaWrite.Create(vt, sizeof(sabWrite)/sizeof(SAFEARRAYBOUND), sabWrite);

	/*通过指向数组的指针来对二维数组的元素进行间接赋值*/
	long (*pArray)[2] = NULL;
	olesaWrite.AccessData((void **)&pArray);
	memset(pArray, 0, sabWrite[0].cElements * sabWrite[1].cElements * sizeof(long));

	/*释放指向数组的指针*/
	olesaWrite.UnaccessData();
	pArray = NULL;

	/*对二维数组的元素进行逐个赋值*/
	long index[2] = {0, 0};
	long lFirstLBound = 0;
	long lFirstUBound = 0;
	long lSecondLBound = 0;
	long lSecondUBound = 0;
	olesaWrite.GetLBound(1, &lFirstLBound);
	olesaWrite.GetUBound(1, &lFirstUBound);
	olesaWrite.GetLBound(2, &lSecondLBound);
	olesaWrite.GetUBound(2, &lSecondUBound);
	for (long i = lFirstLBound; i <= lFirstUBound; i++)
	{
		index[0] = i;
		for (long j = lSecondLBound; j <= lSecondUBound; j++)
		{
			index[1] = j;
			long lElement = i * sabWrite[1].cElements + j; 
			olesaWrite.PutElement(index, &lElement);
		}
	}

	/*把ColesaWritefeArray变量转换为VARIANT,并写入到Excel表格中*/
	VARIANT varWrite = (VARIANT)olesaWrite;
	range.put_Value2(varWrite);

	system("pause");

	/*根据文件的后缀名选择保存文件的格式*/
 	CString strSaveAsName = _T("C:\\new.xlsx");
	CString strSuffix = strSaveAsName.Mid(strSaveAsName.ReverseFind(_T('.')));
	XlFileFormat NewFileFormat = xlOpenXMLWorkbook;
	if (0 == strSuffix.CompareNoCase(_T(".xls")))
	{
		NewFileFormat = xlExcel8;
	}
	book.SaveAs(_variant_t(strSaveAsName), _variant_t((long)NewFileFormat), vtMissing, vtMissing, vtMissing, 
		vtMissing, 0, vtMissing, vtMissing, vtMissing, 
		vtMissing, vtMissing);

	system("pause");

	/*读取Excel表中的多个单元格的值，在listctrl中显示*/
	VARIANT varRead = range.get_Value2();
	COleSafeArray olesaRead(varRead);

	VARIANT varItem;
	CString strItem;
	lFirstLBound = 0;
	lFirstUBound = 0;
	lSecondLBound = 0;
	lSecondUBound = 0;
	olesaRead.GetLBound(1, &lFirstLBound);
	olesaRead.GetUBound(1, &lFirstUBound);
	olesaRead.GetLBound(2, &lSecondLBound);
	olesaRead.GetUBound(2, &lSecondUBound);
	memset(index, 0, 2 * sizeof(long));
	m_ListCtrl.InsertColumn(0, _T(""), 0, 100);
	for (long j = lSecondLBound; j<= lSecondUBound; j++)
	{
		CString strColName = _T("");
		strColName.Format(_T("%d"), j);
		m_ListCtrl.InsertColumn(j, strColName, 0, 100);
	}
	for (long i = lFirstLBound; i <= lFirstUBound; i++)
	{
		CString strRowName = _T("");
		strRowName.Format(_T("%d"), i);
		m_ListCtrl.InsertItem(i-1, strRowName);

		index[0] = i;
		for (long j = lSecondLBound; j <= lSecondUBound; j++)
		{
			index[1] = j;
			olesaRead.GetElement(index, &varItem);

			switch (varItem.vt)
			{
			case VT_R8:
				{
					strItem.Format(_T("%d"), (int)varItem.dblVal);
				}

			case VT_BSTR:
				{
					strItem = varItem.bstrVal;
				}

			case VT_I4:
				{
					strItem.Format(_T("%ld"), (int)varItem.lVal);
				}

			default:
				{

				}
			}

			m_ListCtrl.SetItemText(i-1, j, strItem);
		}
	}



	/*释放资源*/
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	ExcelApp.Quit();
	ExcelApp.ReleaseDispatch();
	
// 	/*退出，不显示对话框*/
// 	exit(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CReadWriteExcelDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReadWriteExcelDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CReadWriteExcelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CReadWriteExcelDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CReadWriteExcelDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CReadWriteExcelDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CReadWriteExcelDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

