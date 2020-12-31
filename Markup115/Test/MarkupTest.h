// MarkupTest.h : header file
//
// Markup Release 11.5
// Copyright (C) 2011 First Objective Software, Inc. All rights reserved
// Go to www.firstobject.com for the latest CMarkup and EDOM documentation
// Use in commercial applications requires written permission
// This software is provided "as is", with no warranty.

#if !defined(_MARKUPTEST_H_INCLUDED_)
#define _MARKUPTEST_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMarkupTest

#include "Markup.h"

struct CMarkupTest
{
	CMarkupTest()
	{
		m_pszLogFile = NULL;
		m_nCreateSpeed = 0;
		m_nAttribCreateSpeed = 0;
		m_nParseSpeed = 0;
		m_nAttribParseSpeed = 0;
		m_nWriterSpeed = 0;
		m_nReaderSpeed = 0;
		m_nLoadMilliseconds = 0;
	};
	int RunTest();
	void LoadParse( MCD_CSTR_FILENAME pszPath );

	MCD_STR m_strResult;
	MCD_PCSZ_FILENAME m_pszLogFile;
	int m_nErrorCount;
	bool m_bLSFileLoaded;

	MCD_STR m_strVer;
	MCD_STR m_strBuild;
	int m_nLoadMilliseconds;
	MCD_STR m_strLoadResult;
	int m_nCreateSpeed;
	int m_nAttribCreateSpeed;
	int m_nParseSpeed;
	int m_nAttribParseSpeed;
	int m_nWriterSpeed;
	int m_nReaderSpeed;

protected:
	void StartCheckZone( MCD_STR strCheckZone );
	int Check( int bCorrect, MCD_PCSZ pszProblem = NULL );
	int Alert( MCD_STR strMsg );
	void AppendLog( MCD_STR strMsg );
	int RandInt( int nNumber );

	MCD_STR m_strCheckZone;
	int m_nTotalZones;
	int m_nCheckCount;
	int m_nTotalChecks;
	int m_nLogWordWrap;
};

#endif // !defined(_MARKUPTEST_H_INCLUDED_)
