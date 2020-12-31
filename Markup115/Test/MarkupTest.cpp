// MarkupTest.cpp : implementation file
//
// Markup Release 11.5
// Copyright (C) 2011 First Objective Software, Inc. All rights reserved
// Go to www.firstobject.com for the latest CMarkup and EDOM documentation
// Use in commercial applications requires written permission
// This software is provided "as is", with no warranty.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <sys/timeb.h>
#include <time.h>
#include "MarkupTest.h"

#define MARKUP_RELEASE MCD_T("11.5")

#if defined(MARKUP_MBCS) && defined(MARKUP_WINCONV)
#include <mbstring.h>
#endif

#ifdef MARKUP_MSXML
#include "MarkupMSXML.h"
#endif

#if _MSC_VER >= 1300 // VC++ 2002 (7.0)
#pragma warning(disable:4127)
#endif // VC++ 2002 (7.0)

#ifdef MARKUP_MSXML
void SimpleMerge( CMarkupMSXML& xmlMaster, CMarkupMSXML& xmlUpdate )
#else
void SimpleMerge( CMarkup& xmlMaster, CMarkup& xmlUpdate )
#endif
{
	// Generic merge xmlUpdate into xmlMaster when element names are unique among siblings
	// removing elements from xmlUpdate as added to or overrided in xmlMaster
	//
	MCD_STR strMergeName;
	xmlMaster.ResetPos();
	xmlUpdate.ResetPos();
	bool bMergeFinished = false;
	if ( ! xmlMaster.FindChildElem() )
	{
		xmlMaster = xmlUpdate;
		bMergeFinished = true;
	}
	xmlUpdate.FindChildElem();
	while ( ! bMergeFinished )
	{
		// Process Element
		xmlMaster.IntoElem();
		xmlUpdate.IntoElem();
		strMergeName = xmlMaster.GetTagName();

		// Did this one match?
		xmlUpdate.ResetMainPos();
		bool bMatched = xmlUpdate.FindElem( strMergeName );
		if ( bMatched )
		{
			// Merge attributes
			for ( int nAttrib=0; !MCD_STRISEMPTY((strMergeName=xmlUpdate.GetAttribName(nAttrib))); ++nAttrib )
				xmlMaster.SetAttrib( strMergeName, xmlUpdate.GetAttrib(strMergeName) );
		}

		// Next element (depth first)
		bool bChildFound = xmlMaster.FindChildElem();
		while ( ! bChildFound && ! bMergeFinished )
		{
			if ( bMatched )
			{
				while ( xmlUpdate.FindChildElem() )
				{
					xmlMaster.AddChildSubDoc( xmlUpdate.GetChildSubDoc() );
					xmlUpdate.RemoveChildElem();
				}
				xmlUpdate.RemoveElem();
			}
			if ( xmlMaster.OutOfElem() )
			{
				xmlUpdate.OutOfElem();
				bChildFound = xmlMaster.FindChildElem();
				if ( ! bChildFound )
				{
					bMatched = true;
					xmlUpdate.ResetChildPos();
				}
			}
			else
				bMergeFinished = true;
		}
	}
}

MCD_STR TruncToLastEOL( MCD_STR strVal )
{
	// locate and truncate from final EOL
	// also cuts any trailing indentation
	int nLength = MCD_STRLENGTH(strVal);
	const MCD_CHAR* pszVal = MCD_2PCSZ(strVal);
	int nLastEOL = nLength;
	int nChar = 0;
	while ( nChar < nLength )
	{
		// Go to next EOL
		nLastEOL = nLength;
		while ( nChar < nLength && pszVal[nChar] != '\r'
				&& pszVal[nChar] != '\n' )
			nChar += MCD_CLEN(&pszVal[nChar]);
		nLastEOL = nChar;
		while ( nChar < nLength
				&& MCD_PSZCHR(MCD_T(" \t\n\r"),pszVal[nChar]) )
			++nChar;
	}
	if ( nLastEOL < nLength )
		strVal = MCD_STRMID( strVal, 0, nLastEOL );
	return strVal;
}

int GetMilliCount()
{
	// Something like GetTickCount but portable
	// It rolls over every ~ 12.1 days (0x100000/24/60/60)
	// Use GetMilliSpan to correct for rollover
	timeb tb;
	ftime( &tb );
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int GetMilliSpan( int nTimeStart )
{
	int nSpan = GetMilliCount() - nTimeStart;
	if ( nSpan < 0 )
		nSpan += 0x100000 * 1000;
	return nSpan;
}

/////////////////////////////////////////////////////////////////////////////
// CMarkupTest
//
// Cross-platform testing for CMarkup (and VC++ testing for CMarkupMSXML)
//

int CMarkupTest::Alert( MCD_STR strMsg )
{
	AppendLog( MCD_T("\r\n") + strMsg + MCD_T("\r\n") );
	m_strResult += strMsg + MCD_T("\r\n");
	return -1;
}

void CMarkupTest::StartCheckZone( MCD_STR strCheckZone )
{
	m_nCheckCount = 0;
	++m_nTotalZones;
	m_strCheckZone = strCheckZone;
	AppendLog( MCD_T("\r\n") + strCheckZone );
}

int CMarkupTest::Check( int bCorrect, MCD_PCSZ pszProblem/*=NULL*/ )
{
	++m_nCheckCount;
	++m_nTotalChecks;
	MCD_CHAR szCheckNumber[100];
	MCD_SPRINTF( MCD_SSZ(szCheckNumber), MCD_T(" %d"), m_nCheckCount );
	MCD_STR strMsg = szCheckNumber;
	AppendLog( strMsg );
	if ( ! bCorrect )
	{
		if ( MCD_STRISEMPTY(m_strCheckZone) )
			m_strCheckZone = MCD_T("Unknown Check Zone");
		MCD_STR strError = MCD_T("Error: ");
		strError += m_strCheckZone;
		strError += MCD_T(", check");
		strError += szCheckNumber;
		if ( pszProblem )
		{
			strError += MCD_T(" ");
			strError += pszProblem;
		}
		++m_nErrorCount;
		return Alert( strError );
	}
	return 0;
}

void CMarkupTest::AppendLog( MCD_STR strMsg )
{
	if ( m_pszLogFile )
	{
		FILE* fp = NULL;
		MCD_FOPEN( fp, m_pszLogFile, (m_nLogWordWrap==-1)?MCD_T_FILENAME("wb"):MCD_T_FILENAME("ab") );
		if ( m_nLogWordWrap == -1 )
			m_nLogWordWrap = 0;
		if ( fp )
		{
			int nLen = MCD_STRLENGTH(strMsg);
			for ( int nChar=0; nChar<nLen; ++nChar )
			{
				if ( strMsg[nChar] == '\n' )
					m_nLogWordWrap = 0;
				if ( m_nLogWordWrap > 64 && strMsg[nChar] == ' ' )
				{
					fputc( '\r', fp );
					fputc( '\n', fp );
					m_nLogWordWrap = 0;
				}
				fputc( (int)strMsg[nChar], fp );
				++m_nLogWordWrap;
				
			}
			fclose( fp );
		}
	}
}

int CMarkupTest::RandInt( int nNumber )
{
	//
	// Return an integer between 0 and nNumber
	//
	static bool bSeeded = false;
	if ( ! bSeeded )
	{
		srand( (unsigned)time( NULL ) );
		bSeeded = true;
	}

	// Sometimes rand() returns something close enough to 1 to make nRandom == nNumber
	int nRandom = rand() * nNumber / RAND_MAX;
	if ( nRandom == nNumber )
		--nRandom;
	return nRandom;
}

int CMarkupTest::RunTest()
{
	// Instantiate XML objects for use in tests
#ifdef MARKUP_MSXML
	CMarkupMSXML xml, xml2, xml3;
#else
	CMarkup xml, xml2, xml3, mResult;
#endif

	m_nErrorCount = 0;
	m_nTotalZones = 0;
	m_nTotalChecks = 0;
	m_nLogWordWrap = -1;

	// Indicate class and build options
	m_strVer = MARKUP_RELEASE;
	MCD_STRCLEAR(m_strBuild);
#if defined(MARKUP_MSXML)
	m_strBuild += MCD_T("MSXML");
#if defined(MARKUP_MSXML1)
	m_strBuild += MCD_T("1");
#else // not MSXML1
#if defined(MARKUP_MSXML3)
	m_strBuild += MCD_T("3");
#elif defined(MARKUP_MSXML4)
	m_strBuild += MCD_T("4");
#else // not MSXML3 or MSXML4
	m_strBuild += MCD_T("6");
#endif // not MSXML4
	MCD_CHAR szVer[30];
	MCD_SPRINTF( MCD_SSZ(szVer), MCD_T(" (instance MSXML%d)"), xml.GetVersionCreated() );
	m_strBuild += szVer;
#endif // not MSXML1
#endif // MSXML
	if ( ! MCD_STRISEMPTY(m_strBuild) )
		m_strBuild += MCD_T(" ");
#if defined(MARKUP_STL)
	m_strBuild += MCD_T("STL");
#else // not STL
	m_strBuild += MCD_T("MFC");
#endif // not STL
#if defined(MARKUP_ICONV)
	m_strBuild += MCD_T(" ICONV");
#endif // ICONV
#if defined(MARKUP_WINCONV)
	m_strBuild += MCD_T(" WINCONV");
#endif // WINCONV
#if defined(MARKUP_WCHAR)
	m_strBuild += MCD_T(" WCHAR");
#endif // WCHAR
#if defined(MARKUP_MBCS)
	m_strBuild += MCD_T(" MBCS");
#endif // MBCS
#if defined(_DEBUG)
	m_strBuild += MCD_T(" Debug");
#endif // DEBUG
	if ( sizeof(MCD_INTFILEOFFSET) > 4 )
		m_strBuild += MCD_T(" HUGE"); // file mode supports files over 2GB
	m_strResult = MCD_T("CMarkup ") + m_strVer + MCD_T(" ") + m_strBuild + MCD_T("\r\n");

	// Performance Measure for create and parse
	const int nPerfTestElems = 10000; // controls size of test document
	const int nPerfMilliSample = 150; // how long to test
	int nPerfElems = 0;
	int nPerfCreateTime = 0;
	int nPerfCreateLength = 0;
	int nTimeStart = GetMilliCount();
	xml.AddElem( MCD_T("root") );
	xml.IntoElem();
	while ( nPerfCreateTime < nPerfMilliSample )
	{
		xml.AddElem( MCD_T("elem"), MCD_T("data") );
		xml.SetAttrib( MCD_T("attrib"), MCD_T("value") );
		++nPerfElems;
		if ( ! (nPerfElems % nPerfTestElems) )
		{
			nPerfCreateLength += MCD_STRLENGTH( xml.GetDoc() );
			xml.SetDoc( NULL );
			xml.AddElem( MCD_T("root") );
			xml.IntoElem();
		}
		if ( ! (nPerfElems % 100) )
			nPerfCreateTime = GetMilliSpan( nTimeStart );
	}
	nPerfCreateLength += MCD_STRLENGTH( xml.GetDoc() );
	nPerfElems = 0;
	xml.SetDoc( NULL );
	xml.AddElem( MCD_T("root") );
	xml.IntoElem();
	while ( nPerfElems < nPerfTestElems )
	{
		xml.AddElem( MCD_T("elem"), MCD_T("data") );
		xml.SetAttrib( MCD_T("attrib"), MCD_T("value") );
		++nPerfElems;
	}
	int nPerfParseTime = 0;
	int nPerfParseLength = 0;
	nTimeStart = GetMilliCount();
	while ( nPerfParseTime < nPerfMilliSample )
	{
		xml.SetDoc( xml.GetDoc() ); // this performs the parse
		nPerfParseLength += MCD_STRLENGTH( xml.GetDoc() );
		nPerfParseTime = GetMilliSpan( nTimeStart );
	}
	m_nCreateSpeed = nPerfCreateTime? nPerfCreateLength/nPerfCreateTime: 0;
	m_nParseSpeed = nPerfParseTime? nPerfParseLength/nPerfParseTime: 0;

	// Integer Method Test
	StartCheckZone( MCD_T("Integer Method Test") );
	xml.SetDoc( NULL );
	xml.AddElem( MCD_T("R"), 5 );
	Check( MCD_STRTOINT(xml.GetData()) == 5 );
	xml.SetData( MCD_T("") );
	Check( xml.InsertChildElem( MCD_T("C"), 1 ) );
	Check( xml.AddChildElem( MCD_T("C"), 3 ) );
	Check( xml.IntoElem() );
	Check( xml.InsertElem( MCD_T("C"), 2 ) );
	xml.ResetMainPos();
	Check( xml.FindElem() );
	Check( MCD_STRTOINT(xml.GetData()) == 1 );
	Check( xml.FindElem() );
	Check( MCD_STRTOINT(xml.GetData()) == 2 );
	Check( xml.FindElem() );
	Check( MCD_STRTOINT(xml.GetData()) == 3 );

	// Quote and special chars in attrib value test
	StartCheckZone( MCD_T("Attrib Value Test") );
	Check( xml.SetDoc( MCD_T("<H g1=\">\" g2=\'>\' d=\"d\'d\" s=\'s\"s\'/>") ) );
	Check( xml.FindElem() );
	Check( xml.GetAttrib(MCD_T("d")) == MCD_T("d\'d") );
	Check( xml.GetAttrib(MCD_T("s")) == MCD_T("s\"s") );
	Check( xml.SetAttrib( MCD_T("d"), MCD_T("d\'d") ) );
	Check( xml.GetAttrib(MCD_T("d")) == MCD_T("d\'d") );
	Check( xml.GetAttrib(MCD_T("s")) == MCD_T("s\"s") );
	Check( xml.GetAttrib(MCD_T("g1")) == MCD_T(">") );
	Check( xml.GetAttrib(MCD_T("g2")) == MCD_T(">") );

	// FindElem Tag Name Test
	StartCheckZone( MCD_T("FindElem Tag Name Test") );
	xml.SetDoc( NULL );
	xml.AddElem( MCD_T("R") );
	xml.AddChildElem( MCD_T("N"), MCD_T("A") );
	xml.AddChildElem( MCD_T("Name"), MCD_T("B") );
	xml.AddChildElem( MCD_T("Na"), MCD_T("C") );
	xml.AddChildElem( MCD_T("Nam"), MCD_T("D") );
	xml.ResetChildPos();
	Check( xml.FindChildElem(MCD_T("Name")) );
	Check( xml.GetChildData() == MCD_T("B") );
	Check( xml.FindChildElem(MCD_T("Nam")) );
	Check( xml.GetChildData() == MCD_T("D") );

	// Copy Constructor Heap Test, requires #include <afx.h>
#if ! defined(MARKUP_MSXML) && ! defined(MARKUP_STL)
	StartCheckZone( MCD_T("Copy Constructor Heap Test") );
	Check( AfxCheckMemory() );
	CMarkup xmlTest(xml);
	Check( AfxCheckMemory() );
	xmlTest.AddElem( MCD_T("AfterCopyEmpty") );
	Check( AfxCheckMemory() );
	xmlTest.SetDoc( NULL );
	xml = xmlTest;
	xml.AddElem( MCD_T("AfterCopyEmpty") );
	Check( AfxCheckMemory() );
#endif // not MSXML

	// CDATA Section Test
	StartCheckZone( MCD_T("CDATA Section Test") );
	xml.SetDoc( NULL );
	Check( xml.AddElem( MCD_T("R") ) );
	Check( xml.AddChildElem( MCD_T("C") ) );
	Check( xml.SetChildData( MCD_T("a]]>b]]>c]]>d"), 1 ) );
	Check( xml.GetChildData() == MCD_T("a]]>b]]>c]]>d") );
	Check( xml.IntoElem() );
	Check( xml.SetData( MCD_T("]]>"), 1 ) );
	Check( xml.GetData() == MCD_T("]]>") );
	MCD_STR strCDATASubDoc = MCD_T("<C><![CDATA[a]]>]]&gt;<![CDATA[a]]></C>");
	Check( xml.AddSubDoc( strCDATASubDoc ) );
	Check( xml.GetData() == MCD_T("a]]>a") );

	// Underscore tag name check
	StartCheckZone( MCD_T("Tag Name Test") );
	xml.SetDoc( NULL );
	Check( xml.AddElem( MCD_T("_Underscore") ) );
	MCD_STR strTagNameDoc = xml.GetDoc();
	Check( xml.SetDoc( strTagNameDoc ) );
	xml.FindElem();
	Check( xml.GetTagName() == MCD_T("_Underscore") );

	// ORDER Test, simple XML example
	StartCheckZone( MCD_T("ORDER Test") );
	xml.SetDoc( NULL );
	Check( xml.AddElem( MCD_T("ORDER") ) );
	Check( xml.IntoElem() );
	Check( xml.AddElem( MCD_T("ITEM") ) );
	Check( xml.AddChildElem( MCD_T("NAME"), MCD_T("carrots") ) );
	Check( xml.AddChildElem( MCD_T("QTY"), MCD_T("1") ) );
	Check( xml.AddChildElem( MCD_T("PRICE"), MCD_T(".98") ) );
	Check( xml.AddChildAttrib( MCD_T("unit"), MCD_T("1 lb") ) );
	Check( xml.AddElem( MCD_T("ITEM") ) );
	Check( xml.AddChildElem( MCD_T("NAME"), MCD_T("onions") ) );
	Check( xml.AddChildElem( MCD_T("QTY"), MCD_T("1") ) );
	Check( xml.AddChildElem( MCD_T("PRICE"), MCD_T("1.10") ) );
	Check( xml.AddChildAttrib( MCD_T("unit"), MCD_T("3 lb bag") ) );
	Check( xml.AddChildElem( MCD_T("SUPPLIER"), MCD_T("Hanover") ) );

	// Create List
	StartCheckZone( MCD_T("List Test") );
	MCD_STR strList;
	xml.ResetPos();
	Check( xml.FindElem( MCD_T("ORDER") ) );
	while ( xml.FindChildElem( MCD_T("ITEM") ) )
	{
		xml.IntoElem();
		xml.FindChildElem( MCD_T("NAME") );
		strList += xml.GetChildData();
		strList += MCD_T("\n");
#if ! defined(MARKUP_MSXML)
		xml.SavePos();
#endif // not MSXML
		xml.OutOfElem();
	}
#if ! defined(MARKUP_MSXML)
	xml.RestorePos();
	Check( xml.GetChildData() == MCD_T("onions") );
#endif // not MSXML
	Check( strList == MCD_T("carrots\nonions\n") );

	// December Test, add and remove five elements repeatedly
	StartCheckZone( MCD_T("December Test") );
	struct TestData { MCD_PCSZ szName; MCD_PCSZ szValue; } td[] =
	{
		{ MCD_T("patridge"), MCD_T("PEARTREE") },
		{ MCD_T("2turtle"), MCD_T("DOVES") },
		{ MCD_T("3french"), MCD_T("HENS") },
		{ MCD_T("4calling"), MCD_T("BIRDS") },
		{ MCD_T("5golden"), MCD_T("RINGS") },
	};
	int nTD;
	xml.SetDoc( MCD_T("") );
	Check( xml.AddElem( MCD_T("RESULT") ) );
	for ( nTD=0; nTD<=4; ++nTD )
	{
		xml.AddChildElem( MCD_T("VAR"), td[nTD].szValue );
		xml.SetChildAttrib( MCD_T("name"), td[nTD].szName );
	}
	for ( nTD=0; nTD<=4; ++nTD )
	{
		xml.ResetPos();
		while ( xml.FindChildElem( MCD_T("VAR") ) )
			if ( xml.GetChildAttrib( MCD_T("name") ) == td[nTD].szName )
			{
				xml.RemoveChildElem();
				break;
			}
		xml.AddChildElem( MCD_T("VAR"), td[nTD].szValue );
		xml.SetChildAttrib( MCD_T("name"), td[nTD].szName );
	}
	for ( nTD=4; nTD>=0; --nTD )
	{
		xml.ResetPos();
		while ( xml.FindChildElem( MCD_T("VAR") ) )
			if ( xml.GetChildAttrib( MCD_T("name") ) == td[nTD].szName )
			{
				xml.RemoveChildElem();
				break;
			}
		xml.ResetChildPos();
		xml.AddChildElem( MCD_T("VAR"), td[nTD].szValue );
		xml.SetChildAttrib( MCD_T("name"), td[nTD].szName );
	}
	// <RESULT>
	// <VAR name="5golden">RINGS</VAR>
	// <VAR name="4calling">BIRDS</VAR>
	// <VAR name="3french">HENS</VAR>
	// <VAR name="2turtle">DOVES</VAR>
	// <VAR name="patridge">PEARTREE</VAR>
	// </RESULT>
	xml.ResetPos();
	for ( nTD=4; nTD>=0; --nTD )
	{
		Check( xml.FindChildElem() );
		Check( xml.GetChildData() == td[nTD].szValue );
		Check( xml.GetChildAttrib( MCD_T("name") ) == td[nTD].szName );
	}

	// Add Insert Test, test siblings created in correct sequence
	MCD_PCSZ aszNums[] = { MCD_T("zero"),MCD_T("one"),MCD_T("two"),MCD_T("three"),MCD_T("four"),MCD_T("five"),MCD_T("six") };
	MCD_STR strInside = MCD_T("_in6");
	StartCheckZone( MCD_T("Insert Test") );
	xml.SetDoc( MCD_T("") );
	xml.AddElem( MCD_T("root") );
	xml.AddChildElem( aszNums[1] );
	xml.ResetChildPos();
	xml.AddChildElem( aszNums[3] );
	xml.ResetChildPos();
	xml.FindChildElem();
	xml.InsertChildElem( aszNums[0] );
	xml.RemoveChildElem();
	xml.InsertChildElem( aszNums[0] );
	xml.FindChildElem();
	xml.AddChildElem( aszNums[2] );
	xml.FindChildElem();
	xml.AddChildElem( aszNums[4] );
	xml.FindChildElem();
	xml.AddChildElem( aszNums[5] );
	xml.ResetChildPos();
	xml.IntoElem();
	xml.FindElem();
	xml.RemoveElem();
	xml.InsertElem( aszNums[0] );
	xml.ResetMainPos();
	xml.AddElem( aszNums[6] );
	xml.IntoElem();
	xml.AddElem( aszNums[1] + strInside );
	xml.ResetMainPos();
	xml.AddElem( aszNums[3] + strInside );
	xml.ResetMainPos();
	xml.FindElem();
	xml.InsertElem( aszNums[0] + strInside );
	xml.RemoveElem();
	xml.ResetMainPos();
	xml.InsertElem( aszNums[0] + strInside );
	xml.FindElem();
	xml.AddElem( aszNums[2] + strInside );
	xml.FindElem();
	xml.AddElem( aszNums[4] + strInside );
	xml.FindElem();
	xml.AddElem( aszNums[5] + strInside );
	// Should result in the following (indented to illustrate):
	// <root>
	//   <zero/>
	//   <one/>
	//   <two/>
	//   <three/>
	//   <four/>
	//   <five/>
	//   <six>
	//     <zero_in6/>
	//     <one_in6/>
	//     <two_in6/>
	//     <three_in6/>
	//     <four_in6/>
	//     <five_in6/>
	//   </six>
	// </root>
	xml.ResetPos();
	for ( int nIT=0; nIT<7; ++nIT )
	{
		Check( xml.FindChildElem() );
		Check( xml.IntoElem() );
		Check( xml.GetTagName() == aszNums[nIT] );
		if ( nIT == 6 )
		{
			for ( int nITinner=0; nITinner<6; ++nITinner )
			{
				Check( xml.FindChildElem() );
				Check( xml.GetChildTagName() == aszNums[nITinner]+strInside );
			}
		}
		Check( xml.OutOfElem() );
	}

	// Palmer Test
	StartCheckZone( MCD_T("Palmer Test") );
	xml.SetDoc( MCD_T("") );
	Check( xml.AddElem( MCD_T("one") ) );
	Check( xml.AddChildElem( MCD_T("two") ) );
	Check( xml.RemoveChildElem() );
	Check( xml.AddChildElem( MCD_T("three") ) );
	// <one>
	// <three/>
	// </one>
	xml.ResetPos();
	Check( xml.FindChildElem() );
	Check( xml.GetChildTagName() == MCD_T("three") );

	// SetData Test, check empty elements, normal, and CDATA
	StartCheckZone( MCD_T("SetData Test") );
	Check( xml.SetDoc( MCD_T("<?xml version=\"1.0\"?>\r\n<ROOT>data</ROOT>") ) );
	Check( xml.FindElem() );
	xml.SetData( MCD_T("moredata<>&") );
	Check( xml.GetData() == MCD_T("moredata<>&") );
	xml.SetData( MCD_T("n<6"), 1 );
	Check( xml.GetData() == MCD_T("n<6") );
	xml.SetData( MCD_T("") );
	xml.AddChildElem( MCD_T("CHILD") );
	xml.SetChildData( MCD_T("data<>&") );
	Check( xml.GetChildData() == MCD_T("data<>&") );
	xml.SetChildData( MCD_T("n<6"), 1 );
	xml.InsertChildElem( MCD_T("CHILD") );
	xml.IntoElem();
	Check( xml.SetData(MCD_T("")) );
	xml.SetData( MCD_T("final") );
	Check( xml.GetData() == MCD_T("final") );
	xml.FindElem();
	Check( xml.GetData() == MCD_T("n<6") );

	// Car Test, add and replace randomly chosen attributes
	StartCheckZone( MCD_T("Random Car Part Test") );
	struct CarTestData { MCD_PCSZ szLow; MCD_PCSZ szUp; MCD_PCSZ szMix; } aCT[] =
	{
		{ MCD_T("up"), MCD_T("SKY"), MCD_T("Light") },
		{ MCD_T("down"), MCD_T("FLOOR"), MCD_T("Dust") },
		{ MCD_T("left"), MCD_T("DOOR"), MCD_T("Handle") },
		{ MCD_T("right"), MCD_T("SEAT"), MCD_T("Gear") },
		{ MCD_T("back"), MCD_T("TRUNK"), MCD_T("Tread") },
		{ MCD_T("forward"), MCD_T("GRILL"), MCD_T("Motor") },
		{ MCD_T(""), MCD_T(""), MCD_T("") }
	};
	xml.SetDoc( MCD_T("") );
	xml.AddElem( MCD_T("CAR") );
	int nAt, nPart;
	MCD_PCSZ szLow;
	MCD_PCSZ szUp;
	MCD_PCSZ szMix;
	for ( nAt = 0; nAt < 20; ++nAt )
	{
		szLow = aCT[RandInt(6)].szLow;
		szMix = aCT[RandInt(6)].szMix;
		xml.SetAttrib( szLow, szMix );
		Check( xml.GetAttrib(szLow) == szMix );
	}
	for ( nPart=0; nPart<100; ++nPart )
	{
		xml.AddChildElem( aCT[RandInt(6)].szUp );
		for ( nAt = 0; nAt < 8; ++nAt )
		{
			szLow = aCT[RandInt(6)].szLow;
			szMix = aCT[RandInt(6)].szMix;
			xml.SetChildAttrib( szLow, szMix );
			Check( xml.GetChildAttrib(szLow) == szMix );
		}
		szLow = aCT[RandInt(6)].szLow;
		szUp = aCT[RandInt(6)].szUp;
		xml.SetChildAttrib( szLow, szUp );
		Check( xml.GetChildAttrib(szLow) == szUp );
	}
	MCD_STR strCarDoc = xml.GetDoc();
	Check( xml.SetDoc( strCarDoc ) );

	// Car Attrib Speed Test
	const int nPerfTestAttribElems = 10000; // controls size of test
	StartCheckZone( MCD_T("Car Attrib Speed Test") );
	xml.SetDoc( NULL );
	xml.AddElem( MCD_T("CARSPEED") );
	nTimeStart = GetMilliCount();
	for ( nPart=0; nPart<nPerfTestAttribElems; ++nPart )
	{
		xml.AddChildElem( aCT[RandInt(6)].szUp );
		for ( nAt = 0; nAt < 4; ++nAt )
		{
			szLow = aCT[RandInt(6)].szLow;
			szMix = aCT[RandInt(6)].szMix;
			xml.SetChildAttrib( szLow, szMix );
			szLow = aCT[RandInt(6)].szLow;
			szUp = aCT[RandInt(6)].szUp;
			xml.SetChildAttrib( szLow, szUp );
		}
	}
	int nAttribCreateTime = GetMilliSpan( nTimeStart );
	int nPerfAttribLength = 0;
	xml.ResetPos();
	nTimeStart = GetMilliCount();
	MCD_STR strAttribName, strAttribs;
	while ( xml.FindChildElem() )
	{
		xml.IntoElem();
		nAt = 0;
		MCD_STRCLEAR(strAttribs);
		strAttribName = xml.GetAttribName( nAt );
		while ( ! MCD_STRISEMPTY(strAttribName) )
		{
			strAttribs += xml.GetAttrib( strAttribName );
			++nAt;
			strAttribName = xml.GetAttribName( nAt );
			nPerfAttribLength += MCD_STRLENGTH(strAttribName) + 4;
		}
		nPerfAttribLength += MCD_STRLENGTH(xml.GetTagName()) + 5 + MCD_STRLENGTH(strAttribs) + nAt*3 + (nAt-1);
		xml.OutOfElem();
	}
	int nAttribNavTime = GetMilliSpan( nTimeStart );
	m_nAttribParseSpeed = nAttribNavTime? nPerfAttribLength/nAttribNavTime: 0;
	m_nAttribCreateSpeed = nAttribCreateTime? nPerfAttribLength/nAttribCreateTime: 0;

	// SubDoc Test, use subdocument methods
	StartCheckZone( MCD_T("SubDoc Test") );
	MCD_STR strTestAttrib = MCD_T("<<&\"symb>>");
	MCD_STR strSubDoc, strChildSubDoc;
	xml.SetDoc( MCD_T("") );
	Check( xml.AddElem(MCD_T("ORDER")) );
	xml.AddChildElem( MCD_T("ITEM") );
	xml.IntoElem();
	Check( xml.AddChildSubDoc(MCD_T("<?xml version=\"1.0\"?>\r\n<ITEM/>\r\n")) );
	Check( xml.AddChildAttrib(MCD_T("test"), strTestAttrib) );
	Check( xml.IntoElem() );
	Check( xml.AddChildElem(MCD_T("NAME"), MCD_T("carrots")) );
	Check( xml.AddChildElem(MCD_T("QTY"), MCD_T("1")) );
	strSubDoc = xml.GetSubDoc();
	Check( xml.OutOfElem() );
	strChildSubDoc = xml.GetChildSubDoc();
	Check( strSubDoc == strChildSubDoc );
	// Set xml2 from xml subdocument and modify
	Check( xml2.SetDoc(xml.GetChildSubDoc()) );
	Check( xml2.FindElem() );
	Check( xml2.SetAttrib(MCD_T("subtest"), strTestAttrib) );
	Check( xml2.SetAttrib(MCD_T("test"), MCD_T("")) );
	Check( xml2.FindChildElem(MCD_T("QTY")) );
	Check( xml2.RemoveChildElem() );
	strSubDoc = xml2.GetDoc();
#if ! defined(MARKUP_MSXML)
	// MSXML: Invalid subdocument causes first-chance exception
	// It works, but this #ifdef avoids alarming us with the Debug output
	Check( ! xml.AddChildSubDoc(MCD_T("invalidsub<doc>")) );
#endif // not MSXML
	Check( xml.AddChildSubDoc(strSubDoc) );
	Check( xml.IntoElem() );
	Check( xml.RemoveElem() );
	Check( xml.AddSubDoc(strSubDoc) );
	Check( xml.GetAttrib(MCD_T("subtest")) == strTestAttrib );
	Check( xml.OutOfElem() );
	Check( xml.InsertChildSubDoc(strSubDoc) );
	xml.ResetChildPos();
	Check( xml.InsertChildSubDoc(strSubDoc) );
	xml.IntoElem();
	xml.FindChildElem();
	Check( xml.GetChildData() == MCD_T("carrots") );
	// Brannan Test: subdocument with no children getting flagged as empty in 7.0
	xml.ResetChildPos();
	xml.FindElem();
	xml.FindChildElem( MCD_T("QTY") );
	xml.AddChildSubDoc( xml.GetChildSubDoc() );
	Check( xml.GetChildData() == MCD_T("1") );

	// Comments Test, make sure it bypasses declaration, DTD, and comments
	StartCheckZone( MCD_T("Comments Test") );
	MCD_STR strPTDoc =
		MCD_T("<?xml version=\"1.0\"?>\n")
		MCD_T("<!DOCTYPE PARSETEST [\n")
		MCD_T("<!ELEMENT PARSETEST (ITEM*)>\n")
		MCD_T("<!ATTLIST PARSETEST v CDATA \"\" s CDATA \"\">\n")
		MCD_T("<!ELEMENT ITEM ANY>\n")
		MCD_T("<!ATTLIST ITEM note CDATA \"\">\n")
		MCD_T("]>\n")
		MCD_T("<PARSETEST v=\"1\" s=\'6\'>\n")
			MCD_T("<!--- </P>& special chars -->\n")
			MCD_T("<ITEM note=\"Here&apos;s to &quot;us&quot;\"/>\n")
			MCD_T("<ITEM note=\"see data\">Here's to \"us\"</ITEM>\n")
		MCD_T("</PARSETEST>\n")
		;
	Check( xml.SetDoc( strPTDoc ) );
	Check( xml.FindChildElem() );
	Check( xml.GetAttrib( MCD_T("v") ) == MCD_T("1") );
	Check( xml.GetAttribName(0) == MCD_T("v") );
	Check( xml.GetAttribName(1) == MCD_T("s") );
	Check( xml.GetAttribName(2) == MCD_T("") );
	Check( xml.GetChildAttrib(MCD_T("note")) == MCD_T("Here's to \"us\"") );
	Check( xml.IntoElem() );
	Check( xml.FindElem() );
	Check( xml.GetData() == MCD_T("Here's to \"us\"") );

#if ! defined(MARKUP_MSXML)
	// Save Restore Position Test
	StartCheckZone( MCD_T("Save Restore Position Test") );
	xml.SetDoc( NULL );
	xml.AddElem( MCD_T("SavePosTest") );
	Check( ! xml.RestorePos() ); // crash in 6.6 and 7.x when no saved pos yet
	Check( xml.SavePos(MCD_T("\xD7")) ); // crash in 7.0 to 8.2 with non-ASCII
	xml.IntoElem(); // no main position
	xml.SavePos();
	xml.ResetPos();
	xml.RestorePos();
	Check( xml.OutOfElem() );
	Check( xml.GetTagName() == MCD_T("SavePosTest") );
	CMarkup mPosNames;
	int nSavePos;
	const int nSavePosTestSize = 100;
	for ( nSavePos=0; nSavePos<nSavePosTestSize; ++nSavePos )
	{
		// Find an unused random name
		MCD_STR strPosName;
		while ( 1 )
		{
			int nPosNameLen = RandInt(10)+1;
			for ( int nPosNameChar=0; nPosNameChar<nPosNameLen; ++nPosNameChar )
				strPosName += (MCD_CHAR)('A'+RandInt(26));
			if ( ! xml.RestorePos(strPosName) )
				break;
		}
		xml.AddChildElem( strPosName );
		xml.SavePos( strPosName );
		mPosNames.AddElem( MCD_T("P"), strPosName );
	}
	xml2 = xml;
	xml = xml2;
	int nPosNameCount = nSavePos;
	mPosNames.ResetPos();
	for ( nSavePos=0; nSavePos<nPosNameCount; ++nSavePos )
	{
		mPosNames.FindElem();
		MCD_STR strPosName = mPosNames.GetData();
		Check( xml.RestorePos(strPosName) );
		Check( xml.GetChildTagName() == strPosName );

		// Move saved position to TEMP2 child
		Check( xml.IntoElem() );
		Check( xml.AddChildElem( MCD_T("TEMP") ) );
		Check( xml.IntoElem() );
		Check( xml.AddChildElem( MCD_T("TEMP2") ) );
		Check( xml.IntoElem() );
		xml.SavePos( strPosName );
		if ( RandInt(2) ) // 1 in 2
			Check( xml.OutOfElem() );
		if ( RandInt(2) ) // 1 in 2
			Check( xml.OutOfElem() );
		if ( nSavePos % 2 )
			xml.RemoveElem();
	}
	mPosNames.ResetPos();
	for ( nSavePos=0; nSavePos<nPosNameCount; ++nSavePos )
	{
		mPosNames.FindElem();
		MCD_STR strPosName = mPosNames.GetData();
		if ( nSavePos % 2 )
			Check( ! xml.RestorePos(strPosName) );
		else
		{
			Check( xml.RestorePos(strPosName) );
			Check( xml.OutOfElem() );
			Check( xml.OutOfElem() );
			Check( xml.GetTagName() == strPosName );
		}
	}

	// Save Restore Example
	int anSomeData[] = { 10, 30, 50, 20, 90, 0 };
	int nD;
	StartCheckZone( MCD_T("Save Restore Example") );
	xml.SetDoc( NULL );
	xml.AddElem( MCD_T("SavePosExample") );
	xml.IntoElem(); // no main position
	xml.AddElem( MCD_T("Total") );
	xml.SavePos( MCD_T("Total") );
	xml.AddElem( MCD_T("Data") );
	xml.SavePos( MCD_T("Data") );
	for ( nD=0; anSomeData[nD]; ++nD )
	{
		xml.RestorePos( MCD_T("Total") );
		xml.SetData( MCD_STRTOINT(xml.GetData()) + anSomeData[nD] );
		xml.RestorePos( MCD_T("Data") );
		xml.AddChildElem( MCD_T("Value"), anSomeData[nD] );
	}
	xml2.SetDoc( NULL );
	xml2.AddElem( MCD_T("SavePosExample") );
	xml2.IntoElem();
	xml2.AddElem( MCD_T("Total") );
	xml2.AddElem( MCD_T("Data") );
	for ( nD=0; anSomeData[nD]; ++nD )
	{
		xml2.ResetMainPos();
		xml2.FindElem();
		xml2.SetData( MCD_STRTOINT(xml2.GetData()) + anSomeData[nD] );
		xml2.FindElem();
		xml2.AddChildElem( MCD_T("Value"), anSomeData[nD] );
	}
	Check( xml.GetDoc() == xml2.GetDoc() );

	// SetMapSize Test with 4 different maps and random values
	StartCheckZone( MCD_T("SetMapSize Test") );
	xml.SetDoc( MCD_T("") );
	xml.AddElem( MCD_T("MAP") );
	xml.IntoElem();
	Check( xml.SetMapSize( 503 ) );
	Check( xml.SetMapSize( 1009, 1 ) );
	Check( xml.SetMapSize( 10007, 2 ) );
	Check( xml.SetMapSize( 53, 3 ) );
	int nMap, nMapItem, nMapTestVal, nMapItemExtra;
	MCD_CHAR szMapTest[25];
	int anMapTestTotal[4] = { 0,0,0,0 };
	int nValCollisions = 0;
	for ( nMap=0; nMap<4; ++nMap )
	{
		for ( nMapItem=0; nMapItem<100; ++nMapItem )
		{
			nMapTestVal = RandInt(100);
			MCD_SPRINTF( MCD_SSZ(szMapTest), MCD_T("%d"), nMapTestVal );
			anMapTestTotal[nMap] += nMapTestVal;
			if ( xml.RestorePos(szMapTest,nMap) )
			{
				++nValCollisions;
				nMapItemExtra = MCD_STRTOINT(xml.GetAttrib(MCD_T("e")));
				xml.SetAttrib( MCD_T("e"), nMapItemExtra + 1 );
				xml.ResetMainPos();
			}
			else
			{
				xml.AddElem( MCD_T("Item"), nMapTestVal );
				xml.SetAttrib( MCD_T("m"), nMap );
				xml.SavePos( szMapTest, nMap );
			}
		}
	}
	int anMapTestCheck[4] = { 0,0,0,0 };
	int nValCollisionsCheck = 0;
	xml.ResetMainPos();
	while ( xml.FindElem() )
	{
		nMap = MCD_STRTOINT(xml.GetAttrib(MCD_T("m")));
		nMapItemExtra = MCD_STRTOINT(xml.GetAttrib(MCD_T("e")));
		nValCollisionsCheck += nMapItemExtra;
		nMapTestVal = MCD_STRTOINT(xml.GetData());
		anMapTestCheck[nMap] += nMapTestVal*(nMapItemExtra+1);
	}
	for ( nMap=0; nMap<4; ++nMap )
		Check( anMapTestCheck[nMap] == anMapTestTotal[nMap] );
	Check( nValCollisionsCheck == nValCollisions );

	// Prepend XML Declaration test
	// (not implemented in MSXML because modifying XML Declaration is restricted)
	StartCheckZone( MCD_T("Prepend XML Declaration") );
	Check( ! xml.SetDoc( MCD_T("<?xml version=\"1.0\"?>\r\n") ) );
	Check( xml.AddElem( MCD_T("ROOT") ) );
	Check( xml.IntoElem() );
	Check( xml.AddElem( MCD_T("CHILD") ) );
	xml.ResetPos();
	Check( xml.FindElem( MCD_T("ROOT") ) );
	Check( xml.FindChildElem( MCD_T("CHILD") ) );

	// Copy Constructor Test (not MSXML!)
	StartCheckZone( MCD_T("Copy Constructor Test non-MSXML") );
	xml.SetDoc( NULL );
	xml2 = xml;
	xml.AddElem( MCD_T("R") );
	xml.AddChildElem( MCD_T("C") );
	xml2 = xml;
	xml2.FindChildElem();
	Check( xml2.GetChildTagName() == xml.GetChildTagName() );
	xml.IntoElem();
	xml.SavePos();
	xml.RemoveElem();
	xml2 = xml;
	Check( ! xml2.RestorePos() );

	// Ill-formed Markup Test
	StartCheckZone( MCD_T("Ill-formed Markup Test") );
	Check( ! xml.SetDoc( MCD_T("<P>Hello<BR>Hi") ) );
	mResult.SetDoc( xml.GetResult() );
	Check( mResult.FindElem(MCD_T("unended_start_tag")) );
	Check( mResult.FindElem(MCD_T("root_has_sibling")) );
	Check( xml.FindElem( MCD_T("P") ) );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("Hello") );
	Check( xml.FindElem( MCD_T("BR") ) );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("Hi") );
	Check( xml.AddElem( MCD_T("P"), MCD_T("Hola") ) );
	Check( xml.GetData() == MCD_T("Hola") );
	Check( ! xml.SetDoc( MCD_T("<P>Hello<BR>Hi</P>") ) );
	Check( xml.FindElem( MCD_T("P") ) );
	xml.SetDocFlags( xml.MDF_IGNORECASE );
	Check( xml.SetDoc( MCD_T("<A></a>") ) );
	Check( xml.FindElem( MCD_T("a") ) );
	Check( xml.SetAttrib( MCD_T("a1"), MCD_T("V1") ) );
	Check( xml.SetAttrib( MCD_T("A1"), MCD_T("v1") ) );
	Check( ! xml.AddSubDoc( MCD_T("<b>") ) );
	xml.ResetPos();
	Check( xml.FindElem( MCD_T("a") ) );
	Check( xml.GetAttrib(MCD_T("A1")) == MCD_T("v1") );
	Check( xml.GetAttrib(MCD_T("a1")) == MCD_T("v1") );
	Check( xml.FindElem( MCD_T("B") ) );
	xml.SetDocFlags( 0 );
	Check( ! xml.SetDoc( MCD_T("<A><B></C></B></A>") ) );
	Check( xml.FindElem() );
	Check( xml.IntoElem() );
	Check( xml.FindElem( MCD_T("B") ) );
	Check( xml.IntoElem() );
	Check( xml.FindNode() == xml.MNT_LONE_END_TAG );
	Check( xml.GetTagName() == MCD_T("C") );
	Check( xml.GetData() == MCD_T("C") );
	Check( xml.OutOfElem() );
	Check( xml.SetElemContent( MCD_T("data") ) );
	Check( ! xml.InsertSubDoc( MCD_T("<S/><S/>") ) );
	Check( ! xml.SetElemContent( MCD_T("<SC>") ) );
	Check( xml.FindElem( MCD_T("S") ) );

	// Multi-Rooted Subdoc Test
	StartCheckZone( MCD_T("Multi-Rooted Subdoc Test") );
	Check( xml.SetElemContent( MCD_T("<SC><SCC/></SC><SC><SCC/></SC><SC/>") ) );
	Check( xml.FindChildElem( MCD_T("SC") ) );
	Check( xml.SetChildAttrib( MCD_T("asc"), MCD_T("verbose") ) );
	Check( xml.IntoElem() );
	Check( xml.FindChildElem( MCD_T("SCC") ) );
	Check( xml.SetChildAttrib( MCD_T("ascc"), MCD_T("verbose") ) );
	Check( xml.OutOfElem() );
	xml.ResetMainPos();
	Check( xml.FindElem( MCD_T("S") ) );
	Check( xml.FindChildElem( MCD_T("SC") ) );
	Check( xml.SetChildAttrib( MCD_T("asc"), MCD_T("verbose") ) );
	Check( xml.SetChildAttrib( MCD_T("asc2"), 2 ) );
	Check( xml.FindElem( MCD_T("S") ) );
	Check( xml.FindChildElem( MCD_T("SC") ) );
	Check( xml.FindChildElem( MCD_T("SC") ) );
	Check( xml.FindElem( MCD_T("B") ) );

	// Trim and Collapse Whitespace Test
	StartCheckZone( MCD_T("Trim and Collapse Whitespace Test") );
	Check( xml.SetDoc( MCD_T("<T><A a=' o  k ' b='o' c=' ok' d='o\tk' e=' ok' f='' g='\t'>\r\ntwo\r\n\twords\t</A></T>") ) );
	xml.SetDocFlags( xml.MDF_TRIMWHITESPACE );
	Check( xml.FindChildElem() );
	Check( xml.IntoElem() );
	Check( xml.GetAttrib(MCD_T("a")) == MCD_T("o  k") );
	Check( xml.GetAttrib(MCD_T("b")) == MCD_T("o") );
	Check( xml.GetAttrib(MCD_T("c")) == MCD_T("ok") );
	Check( xml.GetAttrib(MCD_T("d")) == MCD_T("o\tk") );
	Check( xml.GetAttrib(MCD_T("e")) == MCD_T("ok") );
	Check( xml.GetAttrib(MCD_T("f")) == MCD_T("") );
	Check( xml.GetAttrib(MCD_T("g")) == MCD_T("") );
	Check( xml.GetData() == MCD_T("two\r\n\twords") );
	Check( xml.IntoElem() );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("two\r\n\twords") );
	Check( xml.OutOfElem() );
	xml.SetDocFlags( xml.MDF_COLLAPSEWHITESPACE );
	Check( xml.GetAttrib(MCD_T("a")) == MCD_T("o k") );
	Check( xml.GetAttrib(MCD_T("b")) == MCD_T("o") );
	Check( xml.GetAttrib(MCD_T("c")) == MCD_T("ok") );
	Check( xml.GetAttrib(MCD_T("d")) == MCD_T("o k") );
	Check( xml.GetAttrib(MCD_T("e")) == MCD_T("ok") );
	Check( xml.GetAttrib(MCD_T("f")) == MCD_T("") );
	Check( xml.GetAttrib(MCD_T("g")) == MCD_T("") );
	Check( xml.GetData() == MCD_T("two words") );
	xml.SetDocFlags( 0 );

	// GetNthAttrib Test
	MCD_STR strAttrib, strValue;
	StartCheckZone( MCD_T("GetNthAttrib Test") );
	Check( xml.SetDoc( MCD_T("<T a0='0' a1 a2='2&apos;'/>") ) );
	Check( ! xml.GetNthAttrib(0,strAttrib,strValue) );
	Check( xml.FindElem() );
	Check( xml.GetNthAttrib(0,strAttrib,strValue) );
	Check( xml.GetAttribName(0) == strAttrib );
	Check( xml.GetAttrib(strAttrib) == strValue );
	Check( xml.GetNthAttrib(1,strAttrib,strValue) );
	Check( xml.GetAttribName(1) == strAttrib );
	Check( xml.GetAttrib(strAttrib) == strValue );
	Check( xml.GetNthAttrib(2,strAttrib,strValue) );
	Check( xml.GetAttribName(2) == strAttrib );
	Check( xml.GetAttrib(strAttrib) == strValue );
	Check( strValue == MCD_T("2'") );

	// Don't mistake end slash on non-quoted value for empty element (see cDminus2)
	StartCheckZone( MCD_T("Non Quoted Attribute Test") );
	Check( xml.SetDoc( MCD_T("<A href=/path/>ok</A>") ) );
	Check( xml.FindElem() );
	Check( xml.GetAttrib(MCD_T("href")) == MCD_T("/path/") );

	// AddElem Flags Test
	StartCheckZone( MCD_T("AddElem Flags Test") );
	xml.SetDoc( NULL );
	xml.AddElem( MCD_T("ROOT"), MCD_T(""), xml.MNF_WITHNOLINES );
	xml.AddChildElem( MCD_T("A"), MCD_T(""), xml.MNF_WITHNOEND|xml.MNF_WITHNOLINES );
	Check( xml.IntoElem() );
	Check( xml.AddElem( MCD_T("A"), MCD_T(""), xml.MNF_WITHNOEND ) );
	Check( xml.AddChildElem( MCD_T("B") ) );
	Check( xml.AddChildElem( MCD_T("B"), MCD_T("D") ) );
	Check( xml.OutOfElem() );
	xml.AddChildElem( MCD_T("BR"), MCD_T(""), xml.MNF_WITHXHTMLSPACE );
	xml.SetChildAttrib( MCD_T("class"), MCD_T("MinorBrk") );
	Check( ! xml.SetDoc( MCD_T("<A>test") ) );
	Check( xml.FindElem() );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("test") );
	Check( ! xml.SetDoc( MCD_T("<A>test\r\n") ) );
	Check( xml.FindElem() );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( TruncToLastEOL(MCD_2PCSZ(xml.GetData())) == MCD_T("test") );
	Check( ! xml.SetDoc( MCD_T("<A>test\r\n  <B>okay") ) );
	Check( xml.FindElem() );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( TruncToLastEOL(MCD_2PCSZ(xml.GetData())) == MCD_T("test") );
	Check( xml.FindElem() );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( TruncToLastEOL(MCD_2PCSZ(xml.GetData())) == MCD_T("okay") );
	xml.ResetMainPos();
	Check( xml.FindElem() );
	Check( xml.SetData(MCD_T("t2")) );
	Check( xml.GetData() == MCD_T("t2") );
	Check( xml.SetData(MCD_T("test3")) );
	Check( xml.GetData() == MCD_T("test3") );
	xml.SetDoc( NULL );
	xml.AddElem( MCD_T("P"), MCD_T(""), xml.MNF_WITHNOLINES );
	xml.IntoElem();
	Check( xml.AddNode( xml.MNT_TEXT, MCD_T("First line") ) );
	Check( xml.AddElem( MCD_T("BR"), MCD_T(""), xml.MNF_WITHNOEND | xml.MNF_WITHNOLINES ) );
	Check( xml.AddNode( xml.MNT_TEXT, MCD_T("Second line") ) );
	Check( xml.GetDoc() == MCD_T("<P>First line<BR>Second line</P>") );
	xml.OutOfElem();
	xml.SetElemContent( MCD_T("First line<BR>Second line") );
	Check( xml.GetDoc() == MCD_T("<P>First line<BR>Second line</P>") );

	// Ill-formed SubDoc Fragment Test
	StartCheckZone( MCD_T("SubDoc Fragment Test") );
	Check( ! xml.SetDoc( MCD_T("<A/><B/>") ) );
	Check( ! xml.SetDoc( MCD_T(" something ") ) );
	Check( ! xml.AddSubDoc( MCD_T("<A>") ) );
	Check( ! xml.AddSubDoc( MCD_T("<B>") ) );
	Check( ! xml.AddSubDoc( MCD_T("</A>") ) ); // lone end tag
	mResult.SetDoc( xml.GetResult() );
	Check( mResult.FindElem(MCD_T("lone_end_tag")) );
	Check( xml.AddSubDoc( MCD_T("<C/>") ) );
	Check( ! xml.SetElemContent( MCD_T("<CC>") ) );
	Check( xml.GetTagName() == MCD_T("C") );
	Check( xml.FindChildElem() );
	Check( xml.GetChildTagName() == MCD_T("CC") );
	Check( xml.SetElemContent( MCD_T("d") ) );
	Check( xml.GetData() == MCD_T("d") );
	Check( ! xml.SetElemContent( MCD_T("<DD>") ) );
	Check( xml.FindChildElem() );
	Check( xml.GetChildTagName() == MCD_T("DD") );

	// Replace element between two text nodes
	StartCheckZone( MCD_T("Replace Element Test") );
	Check( xml.SetDoc( MCD_T("T<A/>T") ) );
	Check( xml.FindElem( MCD_T("A") ) );
	Check( xml.RemoveNode() );
	Check( xml.GetNodeType() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("T") );
	Check( xml.AddNode( xml.MNT_ELEMENT, MCD_T("B") ) );
	Check( xml.SetAttrib( MCD_T("v"), 1 ) );
	Check( xml.GetTagName() == MCD_T("B") );
	Check( xml.GetAttrib( MCD_T("v") ) == MCD_T("1") );
	Check( xml.IntoElem() );
	Check( xml.AddNode( xml.MNT_TEXT, MCD_T("T0") ) );
	Check( xml.AddNode( xml.MNT_ELEMENT, MCD_T("C1") ) );
	Check( xml.AddNode( xml.MNT_TEXT, MCD_T("T1") ) );
	Check( xml.AddNode( xml.MNT_ELEMENT, MCD_T("C2") ) );
	Check( xml.AddNode( xml.MNT_TEXT, MCD_T("T2") ) );
	xml.ResetMainPos();
	Check( xml.FindElem( MCD_T("C1") ) );
	Check( xml.RemoveNode() );
	Check( xml.GetNodeType() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("T0") );
	Check( xml.AddNode( xml.MNT_ELEMENT, MCD_T("C1") ) );
	Check( xml.FindElem( MCD_T("C2") ) );
	Check( xml.RemoveNode() );
	Check( xml.GetNodeType() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("T1") );
	Check( xml.AddNode( xml.MNT_ELEMENT, MCD_T("C2") ) );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("T2") );
	xml.ResetMainPos();
	Check( xml.FindElem( MCD_T("C2") ) );
	Check( xml.IntoElem() );
	Check( xml.AddNode( xml.MNT_ELEMENT, MCD_T("D3") ) );
	Check( xml.AddNode( xml.MNT_TEXT, MCD_T("T0") ) );
	Check( xml.AddNode( xml.MNT_ELEMENT, MCD_T("D4") ) );
	Check( xml.IntoElem() );
	Check( xml.AddNode( xml.MNT_ELEMENT, MCD_T("E1") ) );
	Check( xml.SetData( MCD_T("X") ) );
	Check( xml.OutOfElem() );
	Check( xml.OutOfElem() );
	xml.ResetMainPos();
	Check( xml.FindElem() );
	Check( xml.GetTagName() == MCD_T("C1") );
	Check( xml.IntoElem() );
	Check( xml.AddNode( xml.MNT_TEXT, MCD_T("T1") ) );
	Check( xml.AddNode( xml.MNT_ELEMENT, MCD_T("D2") ) );
	Check( xml.AddNode( xml.MNT_TEXT, MCD_T("T2") ) );
	xml.ResetMainPos();
	Check( xml.FindElem() );
	Check( xml.GetTagName() == MCD_T("D2") );
	xml.ResetMainPos();
	Check( xml.InsertNode( xml.MNT_ELEMENT, MCD_T("D1") ) );
	Check( xml.InsertNode( xml.MNT_TEXT, MCD_T("TEST") ) );
	Check( xml.SetData( MCD_T("T0") ) );
	Check( xml.FindNode() == xml.MNT_ELEMENT );
	Check( xml.SetData( MCD_T("X") ) );
	Check( xml.FindElem( MCD_T("D2") ) );
	xml.ResetMainPos();
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("T0") );
	Check( xml.OutOfElem() );
	xml.ResetMainPos();
	Check( xml.FindElem( MCD_T("C2") ) );
	Check( xml.IntoElem() );
	Check( xml.FindNode() == xml.MNT_ELEMENT );
	Check( xml.GetTagName() == MCD_T("D3") );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("T0") );
	Check( xml.FindNode() == xml.MNT_ELEMENT );
	Check( xml.GetTagName() == MCD_T("D4") );
	Check( xml.FindChildElem() );
	Check( xml.GetChildData() == MCD_T("X") );

	// With Entities Test
	StartCheckZone( MCD_T("With Entities Test") );
	xml.SetDoc(NULL);
	Check( xml.AddElem( MCD_T("A"), MCD_T("&#x20;"), xml.MNF_WITHREFS ) );
	Check( xml.GetData() == MCD_T(" ") );
	Check( xml.SetAttrib( MCD_T("a"), MCD_T("&#x20;"), xml.MNF_WITHREFS ) );
	Check( xml.GetAttrib(MCD_T("a")) == MCD_T(" ") );
	Check( xml.AddChildElem( MCD_T("CH"), MCD_T("&amp;"), xml.MNF_WITHREFS ) );
	Check( xml.GetChildData() == MCD_T("&") );
	Check( xml.SetChildData( MCD_T("&#32;"), xml.MNF_WITHREFS ) );
	Check( xml.GetChildData() == MCD_T(" ") );
	Check( xml.SetChildData( MCD_T("&"), xml.MNF_WITHREFS ) );
	Check( xml.GetChildData() == MCD_T("&") );
	Check( xml.SetChildData( MCD_T("&&"), xml.MNF_WITHREFS ) );
	Check( xml.GetChildData() == MCD_T("&&") );
	Check( xml.SetChildData( MCD_T("&#3 2"), xml.MNF_WITHREFS ) );
	Check( xml.GetChildData() == MCD_T("&#3 2") );
	Check( xml.EscapeText( MCD_T("&#3 2"), xml.MNF_WITHREFS ) == MCD_T("&amp;#3 2") );
	Check( xml.EscapeText( MCD_T("\""), xml.MNF_ESCAPEQUOTES ) == MCD_T("&quot;") );
	Check( xml.EscapeText( MCD_T("\"") ) == MCD_T("\"") );
	Check( xml.EscapeText( MCD_T("&#32;\'"), xml.MNF_WITHREFS|xml.MNF_ESCAPEQUOTES ) == MCD_T("&#32;&apos;") );

	// Node Error Test -- even gibberish will not stop node navigation
	// But there is no guaranteed node parsing system with gibberish
	StartCheckZone( MCD_T("Node Error Test") );
	Check( ! xml.SetDoc( MCD_T("<) <> <*  ><<>>") ) );
	bool bReachedEndOfGibberish = false;
	int nGibberishNodes = 0;
	while ( nGibberishNodes < 100 )
	{
		int nGNType = xml.FindNode();
		if ( nGNType == 0 )
		{
			bReachedEndOfGibberish = true;
			break;
		}
		else if ( nGNType == xml.MNT_NODE_ERROR )
		{
			MCD_STR strJunkNode = xml.GetData();
			Check( ! MCD_STRISEMPTY(strJunkNode) );
		}
		++nGibberishNodes;
	}
	Check( bReachedEndOfGibberish );

	// Document Creation Performance test (ensure document creation speed does not degrade)
	StartCheckZone( MCD_T("Document Creation Performance Test") );
	xml.SetDoc(NULL);
	int nDocPerfBaseTime = 0;
	for ( int nDocPerfTest = 0; nDocPerfTest < 5; ++nDocPerfTest )
	{
		nTimeStart = GetMilliCount();
		int nDocPerfAdds = 1500;
		while ( nDocPerfAdds-- )
			xml.AddElem( MCD_T("elem"), MCD_T("data") );
		int nDocPerfTime = GetMilliSpan( nTimeStart );
		if ( ! nDocPerfTest )
			nDocPerfBaseTime = nDocPerfTime + nDocPerfTime/5; // +20%
		else
			Check( nDocPerfTime < 80 || nDocPerfTime < nDocPerfBaseTime );
	}

#endif // not MSXML

	// Character Reference Test, check various character decoding issues
	StartCheckZone( MCD_T("Character Reference Test") );
	Check( xml.SetDoc(
		MCD_T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
		MCD_T("<CHAR v='C&#34;&#x22;S'>\n")
		MCD_T("<CORE>&#60;&#x3c;&#62;&#x3e;&#38;&#x26;&#39;&#x27;&#34;&#x22;</CORE>\n")
		MCD_T("<SPACE xml:space=\"preserve\">&#32;&#x20;&#9;&#x9;&#10;&#xa;</SPACE>\n")
		MCD_T("<REF>&#20013;&#22269;&#20154;</REF>\n")
		MCD_T("</CHAR>\n")
		) );
	Check( xml.FindChildElem(MCD_T("CORE")) );
	Check( xml.GetAttrib( MCD_T("v") ) == MCD_T("C\"\"S") );
	Check( xml.GetChildData() == MCD_T("<<>>&&''\"\"") );
	Check( xml.FindChildElem(MCD_T("SPACE")) );
	Check( xml.GetChildData() == MCD_T("  \t\t\n\n") );
	Check( xml.FindChildElem(MCD_T("REF")) );
#if defined(MARKUP_WCHAR)
	Check( xml.GetChildData() == MCD_T("\x4E2D\x56FD\x4EBA") );
#elif ! defined(MARKUP_MSXML) // not WCHAR and not MSXML
#if defined(MARKUP_MBCS)
#if ! defined(MARKUP_WINCONV)
	setlocale( LC_ALL, "C" );
	if ( setlocale(LC_ALL,".936") ) // is GB2312 DBCS code page available?
		Check( xml.GetChildData() == MCD_T("\xD6\xD0\xB9\xFA\xC8\xCB") ); // DBCS
	else
		Check( xml.GetChildData() == MCD_T("&#20013;&#22269;&#20154;") ); // unmodified
	setlocale( LC_ALL, "" ); // reset to ACP
#endif // not WINCONV
#else // not MBCS
	// UTF-8 (note: MSXML converts chinese character reference to UCS-2, but not UTF-8)
	Check( xml.GetChildData() == MCD_T("\xE4\xB8\xAD\xE5\x9B\xBD\xE4\xBA\xBA") );
#endif // not MBCS
#endif // not WCHAR and not MSXML

#if defined(MARKUP_MBCS)
	// GB2312 Test, check getting and setting of sample GB2312 chars
	StartCheckZone( MCD_T("GB2312 Test") );
	MCD_STR strSampleGB2312Chars = MCD_T("\xD6\xD0\xB9\xFA\xC8\xCB");
	Check( xml.SetDoc(
		MCD_T("<?xml version=\"1.0\" encoding=\"GB2312\"?>\n")
		MCD_T("<CHAR>\xD6\xD0\xB9\xFA\xC8\xCB</CHAR>")
		) );
	Check( xml.FindElem() );
	Check( xml.GetData() == strSampleGB2312Chars );
	Check( xml.SetAttrib(MCD_T("v"),strSampleGB2312Chars) );
	Check( xml.GetAttrib(MCD_T("v")) == strSampleGB2312Chars );
#endif // MBCS

	// Empty Data Test
	StartCheckZone( MCD_T("Empty Data") );
	xml.SetDoc( NULL );
	Check( xml.AddElem(MCD_T("A"),MCD_T("data")) );
	Check( xml.SetData(MCD_T("")) );
	Check( xml.AddChildElem(MCD_T("B"),MCD_T("data")) );
	Check( xml.SetChildData(MCD_T("")) );
	Check( xml.IntoElem() );
	Check( xml.IntoElem() );
	Check( xml.AddElem(MCD_T("C"),MCD_T("data")) );
	Check( xml.OutOfElem() );
	Check( xml.OutOfElem() );
	Check( xml.GetChildTagName() == MCD_T("B") );
	Check( xml.GetTagName() == MCD_T("A") );

	// Depth First Traversal Test, loop through all elements
	StartCheckZone( MCD_T("Depth First Traversal Test") );
	xml.SetDoc( MCD_T("<A><B><C/><C/><C><D/></C></B><B><C/></B></A>") );
	MCD_STR strListOfTagNames;
	bool bFinished = false;
	if ( xml.FindElem() )
		strListOfTagNames = MCD_2PCSZ(xml.GetTagName());
	if ( ! xml.FindChildElem() )
		bFinished = true;
	while ( ! bFinished )
	{
		// Process Element
		xml.IntoElem();
		strListOfTagNames += MCD_2PCSZ(xml.GetTagName());

		// Next element (depth first)
		bool bFound = xml.FindChildElem();
		while ( ! bFound && ! bFinished )
		{
			if ( xml.OutOfElem() )
				bFound = xml.FindChildElem();
			else
				bFinished = true;
		}
	}
	Check( strListOfTagNames == MCD_T("ABCCCDBC") );

	// Depth First Traversal Test 2, include root in loop
	StartCheckZone( MCD_T("Depth First Traversal Test 2") );
	MCD_STRCLEAR( strListOfTagNames );
	bFinished = false;
	xml.ResetPos();
	if ( ! xml.FindElem() )
		bFinished = true;
	while ( ! bFinished )
	{
		// Process element
		MCD_STR strTag = MCD_2PCSZ(xml.GetTagName());
		strListOfTagNames += strTag;

		// Next element (depth first)
		bool bFound = xml.FindChildElem();
		while ( ! bFound && ! bFinished )
		{
			if ( xml.OutOfElem() )
				bFound = xml.FindChildElem();
			else
				bFinished = true;
		}
		if ( bFound )
			xml.IntoElem();
	}
	Check( strListOfTagNames == MCD_T("ABCCCDBC") );

	// Load/Save Test
	StartCheckZone( MCD_T("Load/Save Test") );
	MCD_PCSZ_FILENAME pszLSFileName = MCD_T_FILENAME("CMarkupRunTest.xml");
	m_bLSFileLoaded = xml.Load( pszLSFileName ) ? true: false;
	if ( m_bLSFileLoaded )
	{
		// Load/Save
		xml.FindElem();
		Check( xml.Save(pszLSFileName) );
		Check( xml2.Load(pszLSFileName) );
		Check( xml2.FindElem() );
		Check( xml2.GetTagName() == xml.GetTagName() );
	}

	// Node Test, navigate/modify comments and other nodes
	StartCheckZone( MCD_T("Node Test") );
	strPTDoc =
		MCD_T("<?xml version=\"1.0\"?>\n")

		// To get MSXML to preserve whitespace in mixed content
		// you can use a DTD and an xml:space attribute
		// otherwise MSXML would not have a whitespace node between </B> <I>
		// See "White Space Handling" in the XML Specification
		// Also note the mixed content declaration of ITEM
		MCD_T("<!DOCTYPE PARSETEST [\n")
		MCD_T("<!ELEMENT PARSETEST (ITEM*)>\n")
		MCD_T("<!ATTLIST PARSETEST v CDATA '' s CDATA ''>\n")
		MCD_T("<!ELEMENT ITEM (#PCDATA|B|I)*>\n")
		MCD_T("<!ATTLIST ITEM note CDATA '' xml:space (default|preserve) 'preserve'>\n")
		MCD_T("<!ELEMENT B ANY>\n")
		MCD_T("<!ELEMENT I ANY>\n")
		MCD_T("]>\n")

		MCD_T("<!--tightcomment-->\n")
		MCD_T("<PARSETEST v=\"1\" s=\'6\'>\n")
			MCD_T("<!-- mid comment -->\n")
			MCD_T("<ITEM note=\"hi\"/>\n")
			MCD_T("<ITEM note=\"see data\">hi</ITEM>\n")
			MCD_T("<ITEM> mixed <B>content</B> <I>okay</I></ITEM>\n")
		MCD_T("</PARSETEST>\n")
		MCD_T("<!-- end comment -->\n")
		;
	Check( xml.SetDoc(strPTDoc) );
	Check( xml.FindNode() == xml.MNT_PROCESSING_INSTRUCTION );
	Check( xml.GetData() == MCD_T("xml version=\"1.0\"") );
	Check( xml.FindNode(xml.MNT_COMMENT) );
	Check( xml.GetData() == MCD_T("tightcomment") );
	Check( xml.SetData( MCD_T("comment 1 changed") ) );
	Check( xml.GetData() == MCD_T("comment 1 changed") );
	Check( xml.FindNode(xml.MNT_EXCLUDE_WHITESPACE) == xml.MNT_ELEMENT );
	Check( xml.GetTagName() == MCD_T("PARSETEST") );
	Check( xml.IntoElem() );
	Check( xml.FindNode(xml.MNT_EXCLUDE_WHITESPACE) == xml.MNT_COMMENT );
	Check( xml.GetData() == MCD_T(" mid comment ") );
	Check( xml.FindNode(xml.MNT_EXCLUDE_WHITESPACE) == xml.MNT_ELEMENT );
	Check( xml.FindNode(xml.MNT_EXCLUDE_WHITESPACE) == xml.MNT_ELEMENT );
	Check( xml.FindNode(xml.MNT_EXCLUDE_WHITESPACE) == xml.MNT_ELEMENT );
	Check( xml.IntoElem() );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T(" mixed ") );
	Check( xml.FindNode() == xml.MNT_ELEMENT );
	Check( xml.GetTagName() == MCD_T("B") );
	Check( xml.IntoElem() );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("content") );
	Check( xml.FindNode() == 0 );
	Check( xml.OutOfElem() );
	Check( xml.FindNode() == xml.MNT_WHITESPACE );
	Check( xml.GetData() == MCD_T(" ") );
	Check( xml.FindNode() == xml.MNT_ELEMENT );
	Check( xml.GetTagName() == MCD_T("I") );
	Check( xml.IntoElem() );
	Check( xml.FindNode() == xml.MNT_TEXT );
	Check( xml.GetData() == MCD_T("okay") );
	Check( xml.FindNode() == 0 );
	Check( xml.OutOfElem() );
	Check( xml.FindNode() == 0 );
	Check( xml.OutOfElem() );

	// Create a document xml2 by copying all nodes of document xml
	// Resulting document xml2 differs only by attributes and CRLF instead of just LF
	xml2.SetDoc( NULL );
	xml.ResetPos();
	bool bBypassWhitespace = false;
	while ( 1 )
	{
		int nType = xml.FindNode();
		if ( nType == 0 )
		{
			if ( ! xml.OutOfElem() )
				break;
			xml2.OutOfElem();
		}
		else
		{
			if ( bBypassWhitespace && nType == xml.MNT_WHITESPACE )
				bBypassWhitespace = false;
			else
			{
				if ( nType == xml.MNT_ELEMENT )
				{
					xml2.AddNode( nType, xml.GetTagName() );
					xml.IntoElem();
					xml2.IntoElem();
				}
				else
				{
					xml2.AddNode( nType, xml.GetData() );
					if ( nType & ( xml.MNT_PROCESSING_INSTRUCTION|xml.MNT_COMMENT|xml.MNT_DOCUMENT_TYPE ) )
					{
						// Bypass whitespace on nodes that automatically add it
						xml2.FindNode( xml2.MNT_WHITESPACE );
						bBypassWhitespace = true;
					}
				}
			}
		}
	}
	// Create a document representing depth first traversal of nodes excluding whitespace
	xml3.SetDoc( NULL );
	xml3.AddElem( MCD_T("NodeTraversal") );
	xml2.ResetPos();
	while ( 1 )
	{
		int nType = xml2.FindNode();
		if ( nType == 0 )
		{
			if ( ! xml2.OutOfElem() )
				break;
		}
		else if ( nType != xml2.MNT_WHITESPACE )
		{
			if ( nType == xml2.MNT_ELEMENT )
				xml3.AddChildElem( MCD_T("Node"), xml2.GetTagName() );
			else
				xml3.AddChildElem( MCD_T("Node"), xml2.GetData() );
			xml3.AddChildAttrib( MCD_T("type"), xml2.GetNodeType() );
			if ( nType == xml2.MNT_ELEMENT )
				xml2.IntoElem();
		}
	}
	// Now double check node traversal in xml3 against original xml
	// This helps verify xml --> xml2 node by node copy
	// and xml2 --> xml3 node traversal transformation into elements
	xml.ResetPos();
	xml3.ResetPos();
	while ( 1 )
	{
		int nType = xml.FindNode();
		if ( nType == 0 )
		{
			if ( ! xml.OutOfElem() )
				break;
		}
		else if ( nType != xml.MNT_WHITESPACE )
		{
			if ( Check(xml3.FindChildElem(),MCD_T("missing element in traversal double check"))==-1 )
				break;
			if ( Check(nType==MCD_STRTOINT(xml3.GetChildAttrib(MCD_T("type"))),MCD_T("wrong type in traversal double check"))==-1 )
				break;
			if ( nType == xml.MNT_ELEMENT )
				xml.IntoElem();
		}
	}
	// Add element and remove it using RemoveNode
	// Note that AddElem adds a CRLF (whitespace) after the element
	// which is removed as a separate node
	xml.ResetPos();
	xml.FindElem();
	xml.InsertChildElem( MCD_T("ITEM"), MCD_T("RemoveNode") );
	xml.IntoElem();
	xml.RemoveNode();
	if ( xml.FindNode( xml.MNT_WHITESPACE ) )
		xml.RemoveNode();
	// Remove all whitespace between nodes
	xml3.ResetPos();
	while ( 1 )
	{
		int nType = xml3.FindNode( xml3.MNT_WHITESPACE | xml3.MNT_ELEMENT );
		if ( nType == 0 )
		{
			if ( ! xml3.OutOfElem() )
				break;
		}
		else if ( nType == xml3.MNT_WHITESPACE )
		{
			Check( xml3.RemoveNode(), MCD_T("RemoveNode()") );
		}
		else // element
		{
			xml3.IntoElem();
		}
	}


	MCD_CHAR szResults[100];
	if ( m_nErrorCount )
	{
		MCD_SPRINTF( MCD_SSZ(szResults), MCD_T("%d errors, "), m_nErrorCount );
		m_strResult += szResults;
	}
	MCD_PCSZ pszCharType = MCD_T("b");
	if ( sizeof(MCD_CHAR) == 2 )
		pszCharType = MCD_T("w");
	else if ( sizeof(MCD_CHAR) == 4 )
		pszCharType = MCD_T("dw");
	MCD_SPRINTF( MCD_SSZ(szResults), MCD_T("%d checks, perf %s/ms: create %d, attrib %d, parse %d, attrib %d"),
		m_nTotalChecks, pszCharType, m_nCreateSpeed, m_nAttribCreateSpeed, m_nParseSpeed, m_nAttribParseSpeed );
	m_strResult += szResults;
	if ( m_nWriterSpeed )
	{
		MCD_SPRINTF( MCD_SSZ(szResults), MCD_T("\r\nfile mode perf b/ms: writer %d, reader %d"), m_nWriterSpeed, m_nReaderSpeed );
		m_strResult += szResults;
	}
	m_strResult += MCD_T("\r\n");
	if ( ! m_bLSFileLoaded )
		m_strResult += MCD_T("File I/O tests skipped\r\n");
	return 0;
}

void CMarkupTest::LoadParse( MCD_CSTR_FILENAME pszPath )
{
	// Load and parse with CMarkup
	#ifdef MARKUP_MSXML
	CMarkupMSXML xml;
	#else
	CMarkup xml;
	#endif

	int nTimeStart = GetMilliCount();
	bool bResult = xml.Load( pszPath );
	m_strLoadResult = xml.GetResult();
	m_nLoadMilliseconds = GetMilliSpan( nTimeStart );

	// Display results
	MCD_CHAR szResult[100];
	if ( bResult )
	{
		MCD_SPRINTF( MCD_SSZ(szResult), MCD_T("Loaded and parsed in %d milliseconds"), m_nLoadMilliseconds );
	}
	else
	{
		MCD_SPRINTF( MCD_SSZ(szResult), MCD_T("Load or parse error (after %d milliseconds)"), m_nLoadMilliseconds );
	}
	m_strResult = szResult;
	MCD_STR strError = xml.GetError();
	if ( ! MCD_STRISEMPTY(strError) )
	{
		m_strResult += MCD_T("\r\n");
		m_strResult += strError;
	}
}
