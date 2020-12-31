// MarkupDlg.cpp : implementation file
//
// Markup Release 11.5
// Copyright (C) 2011 First Objective Software, Inc. All rights reserved
// Go to www.firstobject.com for the latest CMarkup and EDOM documentation
// Use in commercial applications requires written permission
// This software is provided "as is", with no warranty.

#include "stdafx.h"
#include "MarkupApp.h"
#include "MarkupDlg.h"
#include <afxpriv.h>
#include <io.h>
#include <locale.h>
#include "Markup.h"
#include "MarkupTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkupDlg dialog

CMarkupDlg::CMarkupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMarkupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMarkupDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMarkupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMarkupDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMarkupDlg, CDialog)
	//{{AFX_MSG_MAP(CMarkupDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_PARSE, OnButtonParse)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMarkupDlg::OnPaint() 
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

HCURSOR CMarkupDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/////////////////////////////////////////////////////////////////////////////
// CMarkupDlg message handlers

BOOL CMarkupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	LoadSystemSettings();

	SetWindowText( _T("CMarkup Evaluation Test Dialog") );

	// Run test
	CMarkupTest test;
	// strcpy( test.m_szLogFile, "log.txt" );
	test.RunTest();
	CString csResults = MCD_2PCSZ(test.m_strResult);

	// Log results
	CMarkup xmlSettings;
	MCD_STR strTestingFilename = _T("CMarkupTesting.xml");
	BOOL bTestingFileLoaded = xmlSettings.Load( strTestingFilename );
	if ( test.m_bLSFileLoaded && ! bTestingFileLoaded )
	{
		xmlSettings.SetDoc( NULL );
		xmlSettings.AddElem( _T("CMarkupTesting") );
		bTestingFileLoaded = TRUE;
	}
	if ( bTestingFileLoaded )
	{
		// Load/Save
		CMarkup xmlTestResults;
		xmlTestResults.AddElem( _T("Test") );
		xmlTestResults.SetAttrib( _T("v"), test.m_strVer );
		xmlTestResults.SetAttrib( _T("b"), test.m_strBuild );
		xmlTestResults.SetAttrib( _T("t"), (LPCTSTR)CTime::GetCurrentTime().Format("%d-%b-%Y %H:%M:%S") );
		xmlTestResults.SetAttrib( _T("c"), test.m_nCreateSpeed );
		xmlTestResults.SetAttrib( _T("ac"), test.m_nAttribCreateSpeed );
		xmlTestResults.SetAttrib( _T("p"), test.m_nParseSpeed );
		xmlTestResults.SetAttrib( _T("ap"), test.m_nAttribParseSpeed );
		if ( test.m_nWriterSpeed )
			xmlTestResults.SetAttrib( _T("w"), test.m_nWriterSpeed );
		if ( test.m_nReaderSpeed )
			xmlTestResults.SetAttrib( _T("r"), test.m_nReaderSpeed );
		CString csTestLog = csResults;
		while ( xmlSettings.FindChildElem(_T("LoadParseFile")) )
		{
			MCD_STR strFile = xmlSettings.GetChildData();
			test.LoadParse( strFile );
			CString csLog;
			csLog.Format( _T("%s\r\n%s\r\n"), MCD_2PCSZ(strFile), MCD_2PCSZ(test.m_strResult) );
			csTestLog += csLog;
			xmlTestResults.AddChildElem( _T("File") );
			xmlTestResults.IntoElem();
			xmlTestResults.SetAttrib( _T("filename"), strFile );
			xmlTestResults.SetAttrib( _T("ms"), test.m_nLoadMilliseconds );
			xmlTestResults.AddChildElem( _T("Log"), test.m_strResult );
			xmlTestResults.AddChildSubDoc( test.m_strLoadResult );
			xmlTestResults.OutOfElem();
		}
		xmlTestResults.AddChildElem( _T("Log"), (LPCTSTR)csTestLog );
		xmlSettings.ResetChildPos();
		if ( ! xmlSettings.FindChildElem(_T("Results")) )
			xmlSettings.AddChildElem(_T("Results"));
		xmlSettings.IntoElem();
		xmlSettings.AddChildSubDoc( xmlTestResults.GetDoc() );
		xmlSettings.Save( strTestingFilename );
	}

	GetDlgItem( IDC_ST_TEST_RESULTS )->SetWindowText( csResults );
	GetDlgItem( IDC_ST_PARSE_RESULTS )->SetWindowText( _T("") );

	if ( m_bAutoExit )
		PostMessage( WM_CLOSE );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMarkupDlg::OnDestroy() 
{
	SaveSystemSettings();
	CDialog::OnDestroy();
}

void SetEntry( CMarkup& xml, MCD_STR strSection, MCD_STR strEntry, MCD_STR strValue )
{
	// Find/Create root element of xml document
	xml.ResetPos();
	if ( ! xml.FindElem() )
		xml.AddElem( _T("Settings") ); // or whatever root element name is

	// Find/Create section
	BOOL bFoundSection = FALSE;
	while ( xml.FindChildElem(_T("Section")) )
	{
		// Is this the right section?
		if ( xml.GetChildAttrib(_T("name")) == strSection )
		{
			bFoundSection = TRUE;
			break;
		}
	}
	if ( ! bFoundSection )
	{
		xml.AddChildElem( _T("Section") );
		xml.SetChildAttrib( _T("name"), strSection );
	}

	// Find/Create entry
	xml.IntoElem();
	BOOL bFoundEntry = FALSE;
	while ( xml.FindChildElem(_T("Entry")) )
	{
		// Is this the right entry?
		if ( xml.GetChildAttrib(_T("name")) == strEntry )
		{
			bFoundEntry = TRUE;
			break;
		}
	}
	if ( ! bFoundEntry )
	{
		xml.AddChildElem( _T("Entry") );
		xml.SetChildAttrib( _T("name"), strEntry );
	}

	// Set value
	xml.SetChildData( strValue );
}

bool FindEntry( CMarkup& xml, MCD_STR strSection, MCD_STR strEntry, MCD_STR& strValue )
{
	// Loop through sections
	xml.ResetPos();
	while ( xml.FindChildElem(_T("Section")) )
	{
		// Is this the right section?
		if ( xml.GetChildAttrib(_T("name")) == strSection )
		{
			// Check entries in this section
			xml.IntoElem();
			while ( xml.FindChildElem(_T("Entry")) )
			{
				// Is this the right entry?
				if ( xml.GetChildAttrib(_T("name")) == strEntry )
				{
					strValue = xml.GetChildData();
					return TRUE;
				}
			}
			break; // don't check any other sections
		}
	}
	return FALSE;
}

void CMarkupDlg::LoadSystemSettings()
{
	CMarkup xmlSettings;

#if defined( _MBCS ) && defined( MARKUP_STDCONV )
	setlocale( LC_ALL, "C" );
	setlocale( LC_ALL, "" );
#endif // MBCS STDCONV

	MCD_STR strTestingFilename = _T("CMarkupTesting.xml");
	BOOL bTestingFileLoaded = xmlSettings.Load( strTestingFilename );
	if ( ! bTestingFileLoaded )
		return;

	MCD_STR strFilename;
	if ( FindEntry(xmlSettings,_T("Settings"),_T("Filename"),strFilename) && strFilename != _T("") )
	{
#if ! defined(UNICODE) && ! defined(_MBCS) // UTF-8
		// Note, all non-UNICODE MSXML builds define MBCS so this won't be necessary for MSXML
		strFilename = CMarkup::UTF8ToA( strFilename );
#endif // UTF-8
		GetDlgItem( IDC_EDIT_FILE )->SetWindowText( MCD_2PCSZ(strFilename) );
	}
	MCD_STR csPos;
	if ( FindEntry(xmlSettings,_T("Settings"),_T("Position"),csPos) )
	{
		CPoint ptDlg;
		if ( _stscanf( MCD_2PCSZ(csPos), _T("%d,%d"), &ptDlg.x, &ptDlg.y ) == 2 )
		{
			CRect rect;
			GetWindowRect( &rect );
			if ( rect.Width() > 10 )
			{
				rect.OffsetRect( ptDlg.x - rect.left, ptDlg.y - rect.top ); 
				MoveWindow( &rect );
			}
		}
	}
}

void CMarkupDlg::SaveSystemSettings()
{
	CMarkup xmlSettings;

#if defined( _MBCS ) && defined( MARKUP_STDCONV )
	setlocale( LC_ALL, "C" );
	setlocale( LC_ALL, "" );
#endif // MBCS STDCONV

	MCD_STR strTestingFilename = _T("CMarkupTesting.xml");
	BOOL bTestingFileLoaded = xmlSettings.Load( strTestingFilename );
	if ( ! bTestingFileLoaded )
		return;

	// Force settings to top of log
	if ( ! xmlSettings.FindChildElem(_T("Section")) )
	{
		xmlSettings.ResetPos();
		if ( xmlSettings.FindElem() )
		{
			xmlSettings.InsertChildElem( _T("Section") );
			xmlSettings.SetChildAttrib( _T("name"), _T("Settings") );
		}
	}
	xmlSettings.ResetPos();

	CString csFilename;
	GetDlgItem( IDC_EDIT_FILE )->GetWindowText( csFilename );
	MCD_STR strFilename = csFilename;
#if ! defined(UNICODE) && ! defined(_MBCS) // UTF-8
	// Note, all non-UNICODE MSXML builds define MBCS so this won't be necessary for MSXML
	strFilename = CMarkup::AToUTF8( strFilename );
#endif // UTF-8
	SetEntry( xmlSettings, _T("Settings"), _T("Filename"), strFilename );
	CRect rect;
	GetWindowRect( &rect );
	CString csPos;
	csPos.Format( _T("%d,%d"), rect.left, rect.top );
	MCD_STR strPos = csPos;
	SetEntry( xmlSettings, _T("Settings"), _T("Position"), strPos );
	xmlSettings.Save( strTestingFilename );
}

void CMarkupDlg::OnButtonBrowse() 
{
	LPCTSTR szTypes =
		_T("XML Files (*.xml)|*.xml|")
		_T("Text Files (*.txt)|*.txt|")
		_T("All Files (*.*)|*.*||");

	CFileDialog dlg( TRUE, _T("xml"), NULL, OFN_NOCHANGEDIR, szTypes );
	if ( dlg.DoModal() == IDCANCEL )
		return;

	CString csFilename = dlg.GetPathName();
	GetDlgItem( IDC_EDIT_FILE )->SetWindowText( csFilename );
	GetDlgItem( IDC_ST_PARSE_RESULTS )->SetWindowText( _T("") );
}

void CMarkupDlg::OnButtonParse() 
{
	GetDlgItem( IDC_ST_PARSE_RESULTS )->SetWindowText( _T("") );

	// Get pathname
	CString csPath;
	GetDlgItem( IDC_EDIT_FILE )->GetWindowText( csPath );
	if ( csPath.IsEmpty() )
	{
		OnButtonBrowse();
		GetDlgItem( IDC_EDIT_FILE )->GetWindowText( csPath );
		if ( csPath.IsEmpty() )
			return;
		RedrawWindow();
	}
	MCD_STR strPath = (LPCTSTR)csPath;
	CMarkupTest test;
	test.LoadParse( strPath );
	CString csMsg = MCD_2PCSZ(test.m_strResult);
	GetDlgItem( IDC_ST_PARSE_RESULTS )->SetWindowText( csMsg );
}

