// ==========================================================================
// 							Class Implementation : COXDiffFileHeader
// ==========================================================================

// Header file : OXDFlHdr.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "oxdflhdr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXDiffFileHeader, CObject)

/////////////////////////////////////////////////////////////////////////////
// Definition of static members


// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:

COXDiffFileHeader::COXDiffFileHeader(CString sSignature)
	: m_sSignText(sSignature) 
	{
	}

CString COXDiffFileHeader::GetSignature() const
	{
	return m_sSignText;
	}

void COXDiffFileHeader::ReadHeader(CFile* pFile)
	{
	ASSERT_VALID(pFile);

	CArchive readArchive(pFile, CArchive::load);

	Read(readArchive);
	readArchive.Close();
	}

void COXDiffFileHeader::WriteHeader(CFile* pFile)
	{
	ASSERT_VALID(pFile);

	CArchive writeArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
	Write(writeArchive);

	writeArchive.Flush();
	writeArchive.Close();
	}

void COXDiffFileHeader::Serialize(CArchive& ar)
	{
	ASSERT_VALID(this);
	if (ar.IsStoring())
		Write(ar);
	else
		Read(ar);
	ASSERT_VALID(this);
	}
	
void COXDiffFileHeader::Read(CArchive& ar, BOOL bReportLogicalErrors /* = TRUE */)
{
	ASSERT_VALID(this);
	char pszSignature[255 + 1];  
	

	if (ar.Read(pszSignature, m_sSignText.GetLength()) != (UINT)m_sSignText.GetLength())
	{
	    TRACE(_T("*** COXDiffFileHeader::Read : End Of File reached while reading signature\n"));
		AfxThrowArchiveException(CArchiveException::endOfFile);
	}
	pszSignature[m_sSignText.GetLength()] = '\0';

	// ... Transfering to data members
	CString sSignature = CString(pszSignature);
	if (sSignature != m_sSignText)
	{
	    TRACE(_T("*** COXDiffFileHeader::Read : Invalid signature\n"));
		if (bReportLogicalErrors)
			AfxThrowArchiveException(CArchiveException::badSchema);
	}

	ASSERT_VALID(this);
}

void COXDiffFileHeader::Write(CArchive& ar)
	{                                     
	ASSERT_VALID(this);

	ar.Write((LPCTSTR)m_sSignText, m_sSignText.GetLength());

	ASSERT_VALID(this);
	}

COXDiffFileHeader::COXDiffFileHeader(const COXDiffFileHeader& HdrSrc)
	{
	ASSERT_VALID(&HdrSrc);
	
	m_sSignText = HdrSrc.m_sSignText;
	ASSERT_VALID(this);
	}
    
COXDiffFileHeader& COXDiffFileHeader::operator=(const COXDiffFileHeader& HdrSrc)
	{
	ASSERT_VALID(this);
	ASSERT_VALID(&HdrSrc);
	
	if(this==&HdrSrc)
		return *this;
		
	m_sSignText = HdrSrc.m_sSignText;
	ASSERT_VALID(this);
	
	return *this;
	}
	

COXDiffFileHeader::~COXDiffFileHeader()
	{
	}

// protected:

// private:

// Diagnostics ---------------------------------------------------------------
#ifdef _DEBUG
void COXDiffFileHeader::AssertValid() const
	{
	CObject::AssertValid();
	}

void COXDiffFileHeader::Dump(CDumpContext& dc) const
	{
	CObject::Dump(dc);               
	
	dc << "\nm_sSignText : " << m_sSignText << "\n";
	}
#endif //_DEBUG

// ==========================================================================
