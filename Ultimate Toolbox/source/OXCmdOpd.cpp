// ==========================================================================
// 							Class Implementation : COXCommandOptionDesc
// ==========================================================================

// Source file : OXCmdOpd.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      

// //////////////////////////////////////////////////////////////////////////
// Example: 
//  BOOL CMyApp::InitInstance()
//		{
//		COXCommandOptionDesc codOption1(_T("RUN"), 0, _T("Automatically run sumpn"));
//		COXCommandOptionDesc codOption2(_T("EMF"), COD_ARGOK | COD_REP_LAST, _T("Gimme a file"));
//		}
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXCmdOpd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXCommandOptionDesc, CObject)

#define new DEBUG_NEW

COXCommandOptionDesc::COXCommandOptionDesc()
	{
	}

COXCommandOptionDesc::COXCommandOptionDesc(LPCTSTR psczOptionName, int iFlags,
										   LPCTSTR psczDescription,
										   LPCTSTR psczAbbr /* = _T("") */)
	: m_sOptionName(psczOptionName),
	m_nFlags(iFlags),
	m_sDescription(psczDescription),
	m_sAbbr(psczAbbr)
	{
	m_sOptionName.MakeUpper();
	m_sAbbr.MakeUpper();
	}

COXCommandOptionDesc::COXCommandOptionDesc(const COXCommandOptionDesc& OptDescSrc)
	: m_sOptionName(OptDescSrc.m_sOptionName),
	m_nFlags(OptDescSrc.m_nFlags),
	m_sDescription(OptDescSrc.m_sDescription),
	m_sAbbr(OptDescSrc.m_sAbbr)
	{
	}
	
COXCommandOptionDesc& COXCommandOptionDesc::operator=(const COXCommandOptionDesc& OptDescSrc)
{
	if(this==&OptDescSrc)
		return *this;
		
	m_sOptionName =		OptDescSrc.m_sOptionName;
	m_nFlags = 			OptDescSrc.m_nFlags;
	m_sDescription = 	OptDescSrc.m_sDescription;
	m_sAbbr = 			OptDescSrc.m_sAbbr;

	return *this;
}

COXCommandOptionDesc::~COXCommandOptionDesc()
	{
	}
