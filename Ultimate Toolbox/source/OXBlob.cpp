// ==========================================================================
//				Class Implementation : COXBlob
// ==========================================================================

// Source file : OXBlob.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXBlob.h"

#include <afxdb.h>	// For CLongBinary

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Definition of static functions
IMPLEMENT_DYNAMIC(COXBlob, CByteArray);

// Data members -------------------------------------------------------------
// protected:
// private:
	
// Member functions ---------------------------------------------------------
// public:
COXBlob::COXBlob(const CLongBinary& lbSrc)
	:
	CByteArray()
	{
	SetSize(lbSrc.m_dwDataLength);
	ASSERT((lbSrc.m_dwDataLength == 0) || (GetData() != NULL));
	BYTE* pData = (BYTE*)::GlobalLock(lbSrc.m_hData);
	ASSERT(pData != NULL);
	memcpy(GetData(), pData, lbSrc.m_dwDataLength);
	::GlobalUnlock(lbSrc.m_hData);
	}

COXBlob& COXBlob::operator=(const CLongBinary& lbSrc)
	{
	SetSize(lbSrc.m_dwDataLength);
	ASSERT((lbSrc.m_dwDataLength == 0) || (GetData() != NULL));
	BYTE* pData = (BYTE*)::GlobalLock(lbSrc.m_hData);
	ASSERT(pData != NULL);
	memcpy(GetData(), pData, lbSrc.m_dwDataLength);
	::GlobalUnlock(lbSrc.m_hData);
	return *this;
	}


BOOL COXBlob::ReadRaw(LPCTSTR pszPath)
	{
	CFileStatus fileStatus;
	if (!CFile::GetStatus(pszPath, fileStatus))
		{
		TRACE(_T("COXBlob::ReadRaw : Specified file does not exist (%s)\n"), pszPath);
		return FALSE;
		}

	// Read as a only dimensional array of unsigned bytes
	BOOL bSuccess = TRUE;

	// Fill with the actual data
	SetSize(fileStatus.m_size);
	TRY
		{
		CFile file(pszPath, CFile::modeRead | CFile::shareDenyNone);
		file.Read(GetData(), fileStatus.m_size);
		file.Close();
		}
	CATCH(CFileException, px)
		{
		TRACE(_T("COXBlob::ReadRaw : Catching File exception\n"));
		bSuccess = FALSE;
		}
	END_CATCH

	if (!bSuccess)
		// Clean up after failure
		RemoveAll();

	return bSuccess;
	}

BOOL COXBlob::WriteRaw(LPCTSTR pszPath)
	{
	BOOL bSuccess = TRUE;

	TRY
		{
		CFile file(pszPath, CFile::modeWrite | CFile::modeCreate | CFile::shareDenyWrite);
		file.Write(GetData(), GetSize());
		file.Close();
		}
	CATCH(CFileException, px)
		{
		TRACE(_T("COXBlob::WriteRaw : Catching File exception\n"));
		bSuccess = FALSE;
		}
	END_CATCH
	
	return bSuccess;;
	}

// protected:
BOOL COXBlob::CopyVariant(LPCVARIANT pSrc)
	// --- In  : pSrc : Pointer to the source variant
	// --- Out : 
	// --- Returns : Whether it succeeded or not
	// --- Effect : Copies the contents of the source variant to this blob object
	//				The supported types are VT_EMPTY and 1-dim (VT_UI1 | VT_ARRAY)
	{
	if (V_VT(pSrc) == VT_EMPTY)
		{
		// Empty variant, just clear the blob
		RemoveAll();
		return TRUE;
		}

	if (V_VT(pSrc) != (VT_UI1 | VT_ARRAY) ||
		SafeArrayGetDim(V_ARRAY(pSrc)) != 1)
		{
		TRACE(_T("COXBlob::CopyVariant : Input variant not a one dimensional array of bytes.\n"));
		return FALSE;
		}

	DWORD lSize;
	long lLower, lUpper;
	void* pDest;

	// ... Make sure that it is an array of BYTEs
	ASSERT(SafeArrayGetElemsize(V_ARRAY(pSrc)) == 1);
	// ... Get the lower and upper bound
	COXVariant::CheckError(SafeArrayGetLBound(V_ARRAY(pSrc), 1, &lLower));
	COXVariant::CheckError(SafeArrayGetUBound(V_ARRAY(pSrc), 1, &lUpper));
	lSize = (DWORD)(lUpper - lLower + 1);
	// ... Get a pointer to the actual data and copy it
	COXVariant::CheckError(SafeArrayAccessData(V_ARRAY(pSrc), &pDest));
	SetSize(lSize);
	memcpy(GetData(), pDest, lSize);
	COXVariant::CheckError(SafeArrayUnaccessData(V_ARRAY(pSrc)));

	return TRUE;
	}

// private:
// ==========================================================================
