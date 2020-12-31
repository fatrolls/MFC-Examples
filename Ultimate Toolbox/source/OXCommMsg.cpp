// ==========================================================================
//				Class Implementation : COXCommMsg
// ==========================================================================

// Source file : OXCommMsg.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXCommMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// ... Skip templated base class
IMPLEMENT_DYNAMIC(COXCommMsg, CObject)

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
COXCommMsg::EOXArgumentTypes COXCommMsg::m_types[COXCommMsg::m_nArgumentTypesCount] =
	{
	COXCommMsg::ATEmpty,
	COXCommMsg::ATNull,
	COXCommMsg::ATBool,
	COXCommMsg::ATUI1,
	COXCommMsg::ATI2,
	COXCommMsg::ATI4,
	COXCommMsg::ATCy,
	COXCommMsg::ATR4,
	COXCommMsg::ATR8,
	COXCommMsg::ATStr,
	COXCommMsg::ATDate,
	COXCommMsg::ATError,
	COXCommMsg::ATBlob
	};

LPCTSTR COXCommMsg::m_typeNames[COXCommMsg::m_nArgumentTypesCount] =
	{
	_T("Empty"),
	_T("Null"),
	_T("Bool"),
	_T("UI1"),
	_T("I2"),
	_T("I4"),
	_T("Cy"),
	_T("R4"),
	_T("R8"),
	_T("Str"),
	_T("Date"),
	_T("Error"),
	_T("Blob")
	};

WORD COXCommMsg::m_nMagicNumber = 0x01FE;
WORD COXCommMsg::m_nVariantType = 0x0001;

// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:
COXCommMsg::COXCommMsg()
	{
	ASSERT_VALID(this);
	}

void COXCommMsg::Serialize(CArchive& ar)
	{
	// First write magic number
	if (ar.IsLoading())
		{
		WORD nMagicNumber;
		WORD nType;
		ar >> nMagicNumber;
		if (nMagicNumber != m_nMagicNumber)
			{
			TRACE(_T("COXCommMsg::Serialize : Magic number is invalid, throwing CArchiveException\n"));
			AfxThrowArchiveException(CArchiveException::badClass);
			}
		ar >> nType;
		if (nType != m_nVariantType)
			{
			TRACE(_T("COXCommMsg::Serialize : Type is invalid, throwing CArchiveException\n"));
			AfxThrowArchiveException(CArchiveException::badClass);
			}
		}
	else
		{
		ar << m_nMagicNumber;
		ar << m_nVariantType;
		}

	// Call base class implementation
	CArray<COXVariant, COXVariant>::Serialize(ar);
	}

#ifdef _DEBUG
void COXCommMsg::AssertValid() const
	{
	CArray<COXVariant, COXVariant>::AssertValid();
	}

void COXCommMsg::Dump(CDumpContext& dc) const
	{
	CArray<COXVariant, COXVariant>::Dump(dc);
	}
#endif //_DEBUG

COXCommMsg::~COXCommMsg()
	{
	}

// protected:
// private:

// ==========================================================================
