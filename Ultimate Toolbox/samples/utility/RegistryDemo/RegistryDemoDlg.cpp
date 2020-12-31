// RegistryDemoDlg.cpp : implementation file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

#include "stdafx.h"
#include "utsampleabout.h"
#include "RegistryDemo.h"
#include "RegistryDemoDlg.h"
#include "RegistryListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRegistryDemoDlg dialog
static const TCHAR szOpen[] =				_T("Open(BOOL bCreate)");
static const TCHAR szClose[] =				_T("Close()");
static const TCHAR szDelete[] =				_T("Delete()");
static const TCHAR szIsOpen[] =				_T("IsOpen()");
static const TCHAR szFlush[] =				_T("Flush()");
static const TCHAR szGetStringValue[] =		_T("GetStringValue(LPCTSTR pszName, BOOL bAllowUnexpanded)");
static const TCHAR szGetMultiStringValue[] =_T("GetMultiStringValue(LPCTSTR pszName)");
static const TCHAR szGetMultiStringValue2[]=_T("GetMultiStringValue(CStringArray& array, LPCTSTR pszName)");
static const TCHAR szGetNumberValue[] =		_T("GetNumberValue(LPCTSTR pszName, BOOL bLittleEndian)");
static const TCHAR szGetBinaryValue[] =		_T("GetBinaryValue(LPCTSTR pszName)");

static const TCHAR szSetStringValue[] =				_T("SetStringValue(LPCTSTR pszNew, LPCTSTR pszName, BOOL bUnexpanded)");
static const TCHAR szSetMultiStringValue[] =		_T("SetMultiStringValue(LPCTSTR pszNew, LPCTSTR pszName)");
static const TCHAR szSetNumberValue[] =				_T("SetNumberValue(DWORD nNew, LPCTSTR pszName, BOOL bLittleEndian)");
static const TCHAR szSetBinaryValue[] =				_T("SetBinaryValue(LPCTSTR pszName)");
static const TCHAR szGetClassName[] =				_T("GetClassName()");
static const TCHAR szGetNumberOfSubKeys[] =			_T("GetNumberOfSubkeys()");
static const TCHAR szGetLongestSubkeyNameLength[] =	_T("GetLongestSubkeyNameLength()");
static const TCHAR szGetLongestClassNameLength[] =	_T("GetLongestClassNameLength()");
static const TCHAR szGetNumberOfValues[] =			_T("GetNumberOfValues()");
static const TCHAR szGetLongestValueNameLength[] =	_T("GetLongestValueNameLength()");

static const TCHAR szGetLongestValueDataLength[] =	_T("GetLongestValueDataLength()");
static const TCHAR szGetSecurityDescriptorLength[] =_T("GetSecurityDescriptorLength()");
static const TCHAR szGetLastWriteTime[] =_T("GetLastWriteTime()");
static const TCHAR szGetValueSize[] =_T("GetValueSize()");
static const TCHAR szGetValueType[] =_T("GetValueType()");

#define OPEN_INDEX				0
#define CLOSE_INDEX				1
#define DELETE_INDEX			2
#define IS_OPEN					3
#define FLUSH					4
#define GET_STRING_VALUE		5
#define GET_MULTI_STRING_VALUE	6
#define GET_MULTI_STRING_VALUE_2 7
#define GET_NUMBER_VALUE		8
#define GET_BINARY_VALUE		9

#define SET_STRING_VALUE		10
#define SET_MULTI_STRING_VALUE	11
#define SET_NUMBER_VALUE		12
#define SET_BINARY_VALUE		13
#define GET_CLASS_NAME			14
#define GET_NUMBER_OF_SUBKEYS	15
#define GET_LONGEST_SUBKEY_NAME_LENGTH 16
#define GET_LONGEST_CLASS_NAME_LENGTH 17
#define GET_NUMBER_OF_VALUES	18
#define GET_LONGEST_VALUE_NAME_LENGTH 19

#define GET_LONGEST_VALUE_DATA_LENGTH 20
#define GET_SECURITY_DESCRIPTOR_LENGTH 21
#define GET_LAST_WRITE_TIME		22
#define GET_VALUE_SIZE			23
#define GET_VALUE_TYPE			24

CRegistryDemoDlg::COXAction CRegistryDemoDlg::m_actions[] =
	{
	//	 m_bEnableFullRegistryItem;
	//     |    m_bEnableBool1
	//	   |     |     m_bEnableText1
	//     |     |      |     m_bEnableNewValue
	//     |     |      |      |     m_pszText
	//     |     |      |      |      |
	//     |     |      |      |      |

		{ TRUE, TRUE,  FALSE, FALSE, szOpen },
		{ FALSE,FALSE, FALSE, FALSE, szClose },
		{ TRUE, FALSE, FALSE, FALSE, szDelete },
		{ FALSE,FALSE, FALSE, FALSE, szIsOpen },
		{ FALSE,FALSE, FALSE, FALSE, szFlush },
		{ TRUE, TRUE,  TRUE,  FALSE, szGetStringValue },
		{ TRUE, FALSE, TRUE,  FALSE, szGetMultiStringValue },
		{ TRUE, FALSE, TRUE,  FALSE, szGetMultiStringValue2 },
		{ TRUE, TRUE,  TRUE,  FALSE, szGetNumberValue },
		{ TRUE, FALSE, TRUE,  FALSE, szGetBinaryValue },

		{ TRUE, TRUE,  TRUE,  TRUE,  szSetStringValue },
		{ TRUE, FALSE, TRUE,  TRUE,  szSetMultiStringValue },
		{ TRUE, TRUE,  TRUE,  TRUE,  szSetNumberValue },
		{ TRUE, FALSE, TRUE,  FALSE, szSetBinaryValue },
		{ TRUE, FALSE,  FALSE, FALSE, szGetClassName },		
		{ TRUE, FALSE,  FALSE, FALSE, szGetNumberOfSubKeys },
		{ TRUE, FALSE,  FALSE, FALSE, szGetLongestSubkeyNameLength },
		{ TRUE, FALSE,  FALSE, FALSE, szGetLongestClassNameLength },
		{ TRUE, FALSE,  FALSE, FALSE, szGetNumberOfValues },	
		{ TRUE, FALSE,  FALSE, FALSE, szGetLongestValueNameLength },

		{ TRUE, FALSE,  FALSE, FALSE, szGetLongestValueDataLength },
		{ TRUE, FALSE,  FALSE, FALSE, szGetSecurityDescriptorLength },
		{ TRUE, FALSE,  FALSE, FALSE, szGetLastWriteTime },
		{ TRUE, FALSE, TRUE,  FALSE, szGetValueSize },
		{ TRUE, FALSE, TRUE,  FALSE, szGetValueType },

		// ... End with m_pszText == NULL
		{ FALSE, FALSE, FALSE, FALSE, NULL}
	};


CRegistryDemoDlg::CRegistryDemoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CRegistryDemoDlg::IDD, pParent)
	{
	//{{AFX_DATA_INIT(CRegistryDemoDlg)
	m_sFullRegistryItem = _T("");
	m_sKeyNames = _T("");
	m_sMachineName = _T("");
	m_sRegistryName = _T("");
	m_sValueName = _T("");
	m_bBool1 = FALSE;
	m_sText1 = _T("");
	m_sNewValue = _T("");
	m_bDepthFirst = FALSE;
	m_bIncludeSubkeys = FALSE;
	m_bIncludeValues = TRUE;
	m_bRecursive = FALSE;
	m_bReversedOrder = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

void CRegistryDemoDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegistryDemoDlg)
	DDX_Control(pDX, IDC_NEW_VALUE_STATIC, m_wndNewValueStatic);
	DDX_Control(pDX, IDC_NEW_VALUE, m_wndNewValue);
	DDX_Control(pDX, IDC_TEXT_1_STATIC, m_wndText1Static);
	DDX_Control(pDX, IDC_TEXT_1, m_wndText1);
	DDX_Control(pDX, IDC_BOOL_1, m_wndBool1);
	DDX_Control(pDX, IDC_RESULT, m_wndResult);
	DDX_Control(pDX, IDC_FULL_REGISTRY_ITEM_STATIC, m_wndFullRegistryItemStatic);
	DDX_Control(pDX, IDC_FULL_REGISTRY_ITEM, m_wndFullRegistryItem);
	DDX_Control(pDX, IDC_ACTIONS, m_wndActions);
	DDX_Control(pDX, IDC_REGISTRY_NAME, m_wndRegistryName);
	DDX_Text(pDX, IDC_FULL_REGISTRY_ITEM, m_sFullRegistryItem);
	DDX_Text(pDX, IDC_KEY_NAMES, m_sKeyNames);
	DDX_Text(pDX, IDC_MACHINE_NAME, m_sMachineName);
	DDX_CBString(pDX, IDC_REGISTRY_NAME, m_sRegistryName);
	DDX_Text(pDX, IDC_VALUE_NAME, m_sValueName);
	DDX_Check(pDX, IDC_BOOL_1, m_bBool1);
	DDX_Text(pDX, IDC_TEXT_1, m_sText1);
	DDX_Text(pDX, IDC_NEW_VALUE, m_sNewValue);
	DDX_Check(pDX, IDC_DEPTH_FIRST, m_bDepthFirst);
	DDX_Check(pDX, IDC_INCLUDE_SUBKEYS, m_bIncludeSubkeys);
	DDX_Check(pDX, IDC_INCLUDE_VALUES, m_bIncludeValues);
	DDX_Check(pDX, IDC_RECURSE, m_bRecursive);
	DDX_Check(pDX, IDC_REVERSED_ORDER, m_bReversedOrder);
	//}}AFX_DATA_MAP
	}

BEGIN_MESSAGE_MAP(CRegistryDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CRegistryDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COMBINE, OnCombine)
	ON_BN_CLICKED(IDC_SPLIT, OnSplit)
	ON_BN_CLICKED(IDC_DO, OnDo)
	ON_CBN_SELCHANGE(IDC_ACTIONS, OnSelchangeActions)
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_LIST, OnList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegistryDemoDlg message handlers

BOOL CRegistryDemoDlg::OnInitDialog()
	{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
		{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Initalize the controls contents
	m_wndRegistryName.AddString(_T(""));
	m_wndRegistryName.AddString(COXRegistryItem::m_pszClassesRoot);
	m_wndRegistryName.AddString(COXRegistryItem::m_pszCurrentUser);
	m_wndRegistryName.AddString(COXRegistryItem::m_pszLocalMachine);
	m_wndRegistryName.AddString(COXRegistryItem::m_pszUsers);
	m_wndRegistryName.AddString(COXRegistryItem::m_pszPerformanceData);
	m_wndRegistryName.AddString(COXRegistryItem::m_pszCurrentConfig);
	m_wndRegistryName.AddString(COXRegistryItem::m_pszDynData);

	// Init combo contents
	int nComboIndex = 0;
	DWORD nArrayIndex = 0;
	COXAction* pAction = m_actions;
	while (pAction->m_pszText != NULL)
		{
		nComboIndex = m_wndActions.AddString(pAction->m_pszText);
		m_wndActions.SetItemData(nComboIndex, nArrayIndex);
		nArrayIndex++;
		pAction++;
		}

	// Init combo selection
	m_wndActions.SelectString(-1, szOpen);
	OnSelchangeActions();

	return TRUE;  // return TRUE  unless you set the focus to a control
	}

void CRegistryDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
	{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
		{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
		dlgAbout.DoModal();
		}
	else
		{
		CDialog::OnSysCommand(nID, lParam);
		}
	}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRegistryDemoDlg::OnPaint() 
	{
	if (IsIconic())
		{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
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
		CDialog::OnPaint();
		}
	}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRegistryDemoDlg::OnQueryDragIcon()
	{
	return (HCURSOR) m_hIcon;
	}

void CRegistryDemoDlg::OnCombine() 
	{
	if (!UpdateData(TRUE))
		return;

	m_registryItem.SetMachineName(m_sMachineName);
	m_registryItem.SetRegistryName(m_sRegistryName);
	m_registryItem.SetKeyNames(m_sKeyNames);
	m_registryItem.SetValueName(m_sValueName);

	// Get the full (and the parts)
	m_sFullRegistryItem = m_registryItem.GetFullRegistryItem();
	m_sMachineName = m_registryItem.GetMachineName();
	m_sRegistryName = m_registryItem.GetRegistryName();
	m_sKeyNames = m_registryItem.GetKeyNames();
	m_sValueName = m_registryItem.GetValueName();

	UpdateData(FALSE);
	}

void CRegistryDemoDlg::OnSplit() 
	{
	if (!UpdateData(TRUE))
		return;

	m_registryItem.SetFullRegistryItem(m_sFullRegistryItem);

	// Get the parts (and the full)
	m_sMachineName = m_registryItem.GetMachineName();
	m_sRegistryName = m_registryItem.GetRegistryName();
	m_sKeyNames = m_registryItem.GetKeyNames();
	m_sValueName = m_registryItem.GetValueName();
	m_sFullRegistryItem = m_registryItem.GetFullRegistryItem();

	UpdateData(FALSE);
	}

void CRegistryDemoDlg::OnDo() 
	{
	int nComboIndex = m_wndActions.GetCurSel();
	DWORD nArrayIndex = m_wndActions.GetItemData(nComboIndex);
	COXAction* pAction = &m_actions[nArrayIndex];

	// Default to no result
	m_sCallResult.Empty();

	// First build the parts again
	if (m_wndFullRegistryItem.IsWindowEnabled())
		OnSplit();

	// Then execute the correct function
	switch (nArrayIndex)
		{
		case OPEN_INDEX:
			m_registryItem.Open(m_bBool1);
			break;
		case CLOSE_INDEX:
			m_registryItem.Close();
			break;
		case DELETE_INDEX:
			m_registryItem.Delete();
			break;
		case IS_OPEN:
			m_sCallResult = m_registryItem.IsOpen() ? _T("TRUE") : _T("FALSE");
			break;
		case FLUSH:
			m_registryItem.Flush();
			break;
		case GET_STRING_VALUE:
			m_sCallResult = m_registryItem.GetStringValue(m_sText1.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)m_sText1, m_bBool1);
			break;
		case GET_MULTI_STRING_VALUE:
			m_sCallResult = m_registryItem.GetMultiStringValue(m_sText1.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)m_sText1);
			break;
		case GET_MULTI_STRING_VALUE_2:
			{
			CStringArray stringArray;
			m_registryItem.GetMultiStringValue(stringArray, m_sText1.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)m_sText1);
			}
			break;
		case GET_NUMBER_VALUE:
			m_sCallResult.Format(_T("%u"), 
				m_registryItem.GetNumberValue(m_sText1.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)m_sText1, m_bBool1));
			break;
		case GET_BINARY_VALUE:
			{
			CByteArray binaryValue;
			m_registryItem.GetBinaryValue(binaryValue, m_sText1.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)m_sText1);
			}
			break;
		case SET_STRING_VALUE:
			m_registryItem.SetStringValue(m_sNewValue, m_sText1.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)m_sText1, m_bBool1);
			break;
		case SET_MULTI_STRING_VALUE:
			m_registryItem.SetMultiStringValue(m_sNewValue, m_sText1.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)m_sText1);
			break;
		case SET_NUMBER_VALUE:
			m_registryItem.SetNumberValue(_ttol(m_sNewValue), m_sText1.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)m_sText1, m_bBool1);
			break;
		case SET_BINARY_VALUE:
			{
			CByteArray binaryValue;
			binaryValue.Add((BYTE)1);
			binaryValue.Add((BYTE)2);
			binaryValue.Add((BYTE)3);
			binaryValue.Add((BYTE)4);
			m_registryItem.SetBinaryValue(binaryValue, m_sText1.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)m_sText1);
			}
			break;
		case GET_CLASS_NAME:
			m_sCallResult = m_registryItem.GetClassName();
			break;
		case GET_NUMBER_OF_SUBKEYS:
			m_sCallResult.Format(_T("%i"), m_registryItem.GetNumberOfSubkeys());
			break;
		case GET_LONGEST_SUBKEY_NAME_LENGTH:
			m_sCallResult.Format(_T("%i"), m_registryItem.GetLongestSubkeyNameLength());
			break;
		case GET_LONGEST_CLASS_NAME_LENGTH:
			m_sCallResult.Format(_T("%i"), m_registryItem.GetLongestClassNameLength());
			break;
		case GET_NUMBER_OF_VALUES:
			m_sCallResult.Format(_T("%i"), m_registryItem.GetNumberOfValues());
			break;
		case GET_LONGEST_VALUE_NAME_LENGTH:
			m_sCallResult.Format(_T("%i"), m_registryItem.GetLongestValueNameLength());
			break;
		case GET_LONGEST_VALUE_DATA_LENGTH:
			m_sCallResult.Format(_T("%i"), m_registryItem.GetLongestValueDataLength());
			break;
		case GET_SECURITY_DESCRIPTOR_LENGTH:
			m_sCallResult.Format(_T("%i"), m_registryItem.GetSecurityDescriptorLength());
			break;
		case GET_LAST_WRITE_TIME:
			m_sCallResult = m_registryItem.GetLastWriteTime().Format(_T("%#c"));
			break;
		case GET_VALUE_SIZE:
			m_sCallResult.Format(_T("%i"), m_registryItem.GetValueSize(m_sText1.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)m_sText1));
			break;
		case GET_VALUE_TYPE:
			m_sCallResult.Format(_T("%i"), m_registryItem.GetValueType(m_sText1.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)m_sText1));
			break;
		default:
			TRACE1("CRegistryDemoDlg::OnDo : Unexpected case in switch : %i\n", nArrayIndex);
			ASSERT(FALSE);
			break;
		}

	// Process the result
	CString sResult = pAction->m_pszText;
	sResult += _T("\r\n");
	if (SUCCEEDED(m_registryItem.GetLastError()))
		sResult += _T("Succeeded");
	else
		{
		CString sError;
		sError.Format(_T("FAILED with Error Code : %i"), HRESULT_CODE(m_registryItem.GetLastError()));
		sResult += sError;
		}
	if (!m_sCallResult.IsEmpty())
		{
		sResult += _T("\r\n");
		sResult += _T("Result = ");
		sResult += m_sCallResult;
		}
	m_wndResult.SetWindowText(sResult);
	}

void CRegistryDemoDlg::OnSelchangeActions() 
	{
	int nComboIndex = m_wndActions.GetCurSel();
	DWORD nArrayIndex = m_wndActions.GetItemData(nComboIndex);
	COXAction* pAction = &m_actions[nArrayIndex];

	// Conditionally enable/disable the window
	m_wndFullRegistryItemStatic.EnableWindow(pAction->m_bEnableFullRegistryItem);
	m_wndFullRegistryItem.EnableWindow(pAction->m_bEnableFullRegistryItem);
	m_wndBool1.EnableWindow(pAction->m_bEnableBool1);
	m_wndText1Static.EnableWindow(pAction->m_bEnableText1);
	m_wndText1.EnableWindow(pAction->m_bEnableText1);
	m_wndNewValueStatic.EnableWindow(pAction->m_bEnableNewValue);
	m_wndNewValue.EnableWindow(pAction->m_bEnableNewValue);
	}

void CRegistryDemoDlg::OnDefault() 
	{
	m_registryItem.InitializeFromApplication();	
		
	// Get the parts (and the full)
	m_sMachineName = m_registryItem.GetMachineName();
	m_sRegistryName = m_registryItem.GetRegistryName();
	m_sKeyNames = m_registryItem.GetKeyNames();
	m_sValueName = m_registryItem.GetValueName();
	m_sFullRegistryItem = m_registryItem.GetFullRegistryItem();

	UpdateData(FALSE);
	}

void CRegistryDemoDlg::OnList() 
	{
	OnSplit();

	CRegistryListDlg regListDlg;
	regListDlg.SetSearchItem(m_registryItem, m_bIncludeValues, m_bIncludeSubkeys, m_bReversedOrder, 
		m_bRecursive, m_bDepthFirst);
	regListDlg.DoModal();
	}
