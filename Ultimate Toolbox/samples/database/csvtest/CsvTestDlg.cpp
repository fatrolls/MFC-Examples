// CsvTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CsvTest.h"
#include "CsvTestDlg.h"
#include "OXCsvFile.h"
#include "OXTrace.h"
#include "utsampleabout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCsvTestDlg dialog

CCsvTestDlg::CCsvTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCsvTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCsvTestDlg)
	m_bUseHeaders = FALSE;
	m_strData = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCsvTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCsvTestDlg)
	DDX_Control(pDX, IDC_SAVE, m_ctrlSave);
	DDX_Check(pDX, IDC_USE_HEADERS, m_bUseHeaders);
	DDX_Text(pDX, IDC_DATA, m_strData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCsvTestDlg, CDialog)
	//{{AFX_MSG_MAP(CCsvTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCsvTestDlg message handlers

BOOL CCsvTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlSave.EnableWindow(FALSE);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	OXTRACE_SETDUMPFILE(_T("trace.txt"));
	OXTRACE_SETPREFIX(TRUE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCsvTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		OnAbout();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCsvTestDlg::OnPaint() 
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
HCURSOR CCsvTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

static LPCTSTR headers[]={	_T("ID"), _T("Name"), _T("Byte"), _T("Integer"), 
							_T("Float"), _T("Double"), _T("String"), 
							_T("Valid"), NULL };

static LPCTSTR aliases[]={ _T("Int"), _T("I"), NULL };

static const int nColumns=sizeof(headers) / sizeof(headers[0]) - 1;

static LPCTSTR headers2[]={ _T("ID"), _T("Last Name"), _T("Address"), NULL };

static LPCTSTR lpstrYesNo[]={ _T("Yes"), _T("No"), NULL };

//
// Read in one of two predefined comma delimted files, and display their contents in the
// multiline edit control in this dialog.
// Note that the input files for this example use the technique of putting two
// separate tables into a single CSV file, which is not supported by all programs. But,
// it can still be a very useful technique for your own use.
//
void CCsvTestDlg::OnOK() 
{
	//
	// Retrieve the settings from the dialog
	//
	UpdateData();

	COXCsvFile inFile;
	CFileException fe;
	LPCTSTR lpstrInFilename=(m_bUseHeaders ? _T("headers.csv") : 
		_T("noheader.csv"));
	SData data;

	//
	// clear out the old data array
	//
	m_aData.RemoveAll();

	//
	// disable the save button
	//
	m_ctrlSave.EnableWindow(FALSE);

	//
	// Open the input file
	//
	if (!inFile.Open(lpstrInFilename, CFile::modeRead, &fe))
	{
		return ;
	}

	TRY
	{
		CWaitCursor cursor;
		short nId;
		int nYesNo;
		int index;

		OXTRACE(_T("CCsvTestDlg::OnOK()"));

		//
		// check if we shuold check for headers in the input file
		//
		if (m_bUseHeaders)
		{
			//
			// Read in the headers from the input file. After reading the
			// headers in from the first line of the file, set the aliases
			// for the "Integer" column.
			// Note: by using the column headers, and using those headers
			// in the calls to ReadColumn(), the exact order of the columns
			// in the CSV file becomes irrelevant to your program. This is
			// shown by the fact that the columns in "headers.csv" are in
			// a different order from "noheader.csv", but the results displayed
			// in the edit control are the same.
			//
			inFile.GetColumns(8);
			inFile.SetAliases(headers[3], aliases);
		}
		else
		{
			//
			// Since there are no headers in the input file, set the names
			// of the columns that we will use in later calls, and let
			// the COXCsvFile object know how many columns to expect.
			// Note, if you want to only refer to the columns by their column
			// indicies, this call does not need to be made, as the first call
			// to ReadLine() will set the number of columns in the table.
			//
			inFile.SetColumns(headers);
		}

		//
		// Read the individual records from one file to the other.
		//
		// NOTE : I said records, not lines, since quoted strings can
		// contain new lines in them. This is a feature supported by programs
		// like MS Access, but not by MS Excel.
		//
		while (inFile.ReadLine())
		{
			data.Clear();

			if (inFile.IsLineEmpty())
			{
				//
				// Blank lines can either be ignored, or they can be used like
				// here to mark the end of one table, and the start of another
				// one.
				//
				OXTRACE(_T("Reached the end of the first table"));
				break;
			}

			OXTRACE(_T("Reading next line"));

			//
			// Read the data from the various columns into the members of the
			// SData structure.
			//
			inFile.ReadColumn(_T("ID"), data.nId);
			OXTRACE_WRITEVAL(_T("ID"), data.nId);

			inFile.ReadColumn(_T("Name"), data.strName);
			OXTRACE_WRITEVAL(_T("Name"), data.strName);

			inFile.ReadColumn(_T("Byte"), data.ucByte);
			OXTRACE_WRITEVAL(_T("Byte"), data.ucByte);

			inFile.ReadColumn(_T("Integer"), data.nInt);
			OXTRACE_WRITEVAL(_T("Integer"), data.nInt);

			inFile.ReadColumn(_T("Float"), data.fFloat);
			OXTRACE_WRITEVAL(_T("Float"), data.fFloat);
			
			inFile.ReadColumn(_T("Double"), data.fDouble);
			OXTRACE_WRITEVAL(_T("Double"), data.fDouble);
			
			inFile.ReadColumn(_T("String"), data.strString);
			OXTRACE_WRITEVAL(_T("String"), data.strString);
			
			inFile.ReadColumn(_T("Valid"), nYesNo, lpstrYesNo);
			OXTRACE_WRITEVAL(_T("Valid"), nYesNo);
			data.bValid = (nYesNo == 0);

			m_aData.Add(data);
		}

		//
		// Read in the second table, merging its data with the first
		//
		if (m_bUseHeaders)
		{
			//
			// Read in the headers for the second table in this file.
			//
			inFile.GetColumns(3);
		}
		else
		{
			//
			// Set the names, and number of columns to expect, for the
			// second table in this file
			//
			inFile.SetColumns(headers2);
		}

		//
		// Read the records in one at a time from the second table.
		//
		while (inFile.ReadLine())
		{
			if (inFile.IsLineEmpty())
			{
				//
				// Blank lines can either be ignored, like here, or they can be 
				// used to mark the end of one table, and the start of another
				// one.
				//
				continue;
			}

			OXTRACE(_T("Reading next line"));

			//
			// Read the ID field for this record, and search for it in the
			// SData array, to match the records from the two tables up to
			// each other.
			//
			inFile.ReadColumn(_T("ID"), nId);
			OXTRACE_WRITEVAL(_T("ID"), nId);


			for (index = 0 ; index < m_aData.GetSize() ; ++index)
			{
				if (m_aData[index].nId == nId)
				{
					//
					// found the matching record from the previous table
					//
					break;
				}
			}

			if (index >= m_aData.GetSize())
			{
				//
				// skip this record, as this ID did not exist in the other table
				//
				OXTRACE_WRITEVAL(_T("ID not found from earlier table"), nId);
				continue;
			}

			//
			// Read the remaining columns into the SData structure from the previous
			// table
			//
			inFile.ReadColumn(_T("Last Name"), m_aData[index].strLastName);
			OXTRACE_WRITEVAL(_T("Last Name"), m_aData[index].strLastName);

			inFile.ReadColumn(_T("Address"), m_aData[index].strAddress);
			OXTRACE_WRITEVAL(_T("Address"), m_aData[index].strAddress);
		}

		//
		// format the data for the multiline edit control
		//
		m_strData.Empty();
		for (index = 0 ; index < m_aData.GetSize() ; ++index)
		{
			CString strTemp;
			data = m_aData[index];

			strTemp.Format(_T("%u. %s %s, %s\r\n")
						   _T("    %u, %d, %f, %f, %s\r\n")
						   _T("    \"%s\"\r\n"),
						   data.nId, data.strName, data.strLastName, data.strAddress,
						   data.ucByte, data.nInt, data.fFloat, data.fDouble,
						   (data.bValid ? _T("Valid") : _T("Invalid")),
						   data.strString);
			m_strData += strTemp;
		}
		UpdateData(FALSE);

		//
		// enable the Save button
		//
		m_ctrlSave.EnableWindow(m_aData.GetSize() > 0);
	}
	CATCH_ALL(e)
	{
		inFile.Abort();
	}
	END_CATCH_ALL
}

//
// Write the data from the data array out to a CSV file. The data
// will be written out using the same two tables to a single CSV file
// format that it was read in with.
//
void CCsvTestDlg::OnSave() 
{
	//
	// Update the members of the class from the dialog
	//
	UpdateData();

	COXCsvFile inFile, outFile;
	CFileException fe;
	LPCTSTR lpstrOutFilename = _T("out.csv");
	SData data;

	//
	// Open the output file
	//
	if (!outFile.Open(lpstrOutFilename, CFile::modeCreate | CFile::modeReadWrite, &fe))
	{
		return ;
	}

	TRY
	{
		CWaitCursor cursor;

		OXTRACE(_T("CCsvTestDlg::OnOK()"));

		//
		// Check for header usage
		//
		if (m_bUseHeaders)
		{
			//
			// Write out the headers for the first table
			//
			outFile.SetColumns(headers);
			outFile.WriteHeaders();
		}
		else
		{
			//
			// Set up how many columns there will be in the first table
			//
			outFile.Initialize(nColumns);
		}

		//
		// loop through the SData elements that were filled in during the read.
		//
		int index = 0 ;
		for (index = 0 ; index < m_aData.GetSize() ; ++index)
		{
			data = m_aData[index];

			//
			// Write the column data out to the current record buffer in outFile.
			//
			outFile.WriteColumn(0, data.nId);
			outFile.WriteColumn(1, data.strName);
			outFile.WriteColumn(2, data.ucByte);
			outFile.WriteColumn(3, data.nInt);
			outFile.WriteColumn(4, data.fFloat);
			outFile.WriteColumn(5, data.fDouble);
			outFile.WriteColumn(6, data.strString);
			outFile.WriteColumn(7, lpstrYesNo[data.bValid ? 0 : 1]);

			//
			// Write this record out to the output file.
			//
			outFile.WriteLine();
		}

		//
		// This call to WriteLine, with no columns, will write out a blank line,
		// providing a separator between the tables.
		// Initialize is called to clear the old header information.
		//
		outFile.Initialize();
		outFile.WriteLine();

		if (m_bUseHeaders)
		{
			//
			// Write out the headers for the second table in the file.
			//
			outFile.SetColumns(headers2);
			outFile.WriteHeaders();
		}
		else
		{
			//
			// Set up how many columns there will be in the second
			// table in the file.
			//
			outFile.Initialize(3);
		}

		//
		// Loop through the records one more time.
		//
		for (index = 0 ; index < m_aData.GetSize() ; ++index)
		{
			data = m_aData[index];

			//
			// Write the data for this record to the current record
			// buffer in outFile.
			//
			outFile.WriteColumn(0, data.nId);
			outFile.WriteColumn(1, data.strLastName);
			outFile.WriteColumn(2, data.strAddress);

			//
			// Write the current record to the output file.
			//
			outFile.WriteLine();
		}
	}
	CATCH_ALL(e)
	{
		outFile.Abort();
	}
	END_CATCH_ALL
}

void CCsvTestDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	
	CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
	dlgAbout.DoModal();
}
