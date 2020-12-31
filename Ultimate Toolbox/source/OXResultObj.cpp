// ==========================================================================
//				Class Implementation : COXResultObj
// ==========================================================================

// Source file : OXResultObj.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXResultObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXResultObj, CObject)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
// Data members -------------------------------------------------------------
// protected:

// private:
	
// Member functions ---------------------------------------------------------
// public:

COXResultObj::COXResultObj()
	:
	m_defaultPart()
	{
	ASSERT_VALID(this);
	}

COXResultObj::COXResultObj(const COXResultPart& resultPart)
	:
	m_defaultPart(resultPart)
	{
	ASSERT_VALID(&resultPart);
	ASSERT_VALID(this);
	}

COXResultObj::COXResultObj(const COXResultObj& result)
	:
	m_defaultPart()
	{
	ASSERT_VALID(&result);
	// ... This object is still empty, so appending the specified object
	//     is the same as copying it
	Append(result);
	ASSERT_VALID(this);
	}

COXResultObj& COXResultObj::operator=(const COXResultObj& result)
	{
	ASSERT_VALID(&result);

	if(this==&result)
		return *this;
		
	// Empty the object and append the specified object
	Empty();
	Append(result);

	ASSERT_VALID(this);
	return *this;
	}

void COXResultObj::operator+=(const COXResultPart& resultPart)
	{
	ASSERT_VALID(this);
	Add(resultPart);
	ASSERT_VALID(this);
	}

void COXResultObj::operator+=(const COXResultObj& result)
	{
	ASSERT_VALID(&result);
	Append(result);
	ASSERT_VALID(this);
	}

COXResultPart& COXResultObj::GetDefaultPart()
	{
	ASSERT_VALID(this);
	ASSERT_VALID(&m_defaultPart);
	return m_defaultPart;
	}

COXResultPart COXResultObj::GetDefaultPart() const
	{
	ASSERT_VALID(this);
	ASSERT_VALID(&m_defaultPart);
	return m_defaultPart;
	}

void COXResultObj::SetDefaultPart(const COXResultPart& defaultPart)
	{
	ASSERT_VALID(this);
	ASSERT_VALID(&defaultPart);
	m_defaultPart = defaultPart;
	ASSERT_VALID(this);
	}

void COXResultObj::Empty()
	{
	ASSERT_VALID(this);
	RemoveAll();
	ASSERT_VALID(this);
	}

BOOL COXResultObj::IsEmpty() const
	{
	ASSERT_VALID(this);
	return (GetSize() == 0);
	}

COXResultPart& COXResultObj::GetMostSeverePart()
	{
	ASSERT_VALID(this);
	if (IsEmpty())
		{
		// ... Trying to directly access an item while the list is empty,
		//     returning default part
		return m_defaultPart;
		}

	ASSERT(!IsEmpty());
	COXResultPart* pResultItem = &ElementAt(0);
	for (int nIndex = 1; nIndex < GetSize(); nIndex++)
		{
		if (ElementAt(nIndex).GetSeverityEx() > pResultItem->GetSeverityEx())
			pResultItem = &ElementAt(nIndex);
		}

	ASSERT_VALID(this);
	ASSERT_KINDOF(COXResultPart, pResultItem);
	ASSERT_VALID(pResultItem);
	return *pResultItem;
	}

COXResultPart COXResultObj::GetMostSeverePart() const
	{
	ASSERT_VALID(this);
	if (IsEmpty())
		{
		// ... Trying to directly access an item while the list is empty,
		//     returning default item
		return m_defaultPart;
		}

	COXResultPart resultPart;
	ASSERT(!IsEmpty());
	resultPart = GetAt(0);
	for (int nIndex = 1; nIndex < GetSize(); nIndex++)
		{
		if (GetAt(nIndex).GetSeverityEx() > resultPart.GetSeverityEx())
			resultPart = GetAt(nIndex);
		}

	ASSERT_VALID(this);
	ASSERT_KINDOF(COXResultPart, &resultPart);
	ASSERT_VALID(&resultPart);
	return resultPart;
	}

COXResultPart* COXResultObj::operator->()
	{
	return &GetMostSeverePart();
	}

void COXResultObj::Serialize(CArchive& ar)
	{
	ASSERT_VALID(this);

	// Call base class implementation first
	CObject::Serialize(ar);

	// ... No extra members to serialize

	ASSERT_VALID(this);
	}

#ifdef _DEBUG
void COXResultObj::AssertValid() const
	{
	CObject::AssertValid();
	ASSERT_VALID(&m_defaultPart);
	}

void COXResultObj::Dump(CDumpContext& dc) const
	{
	CObject::Dump(dc);
	}
#endif //_DEBUG

COXResultObj::~COXResultObj()
	{
	}

// protected:
// private:

// ==========================================================================
