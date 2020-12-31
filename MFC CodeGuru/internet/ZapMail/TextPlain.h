// TextPlain.h: interface for the CTextPlain class.
// Author: Wes Clyburn (clyburnw@enmu.edu)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTPLAIN_H__333BA6C3_F593_11D1_870E_444553540001__INCLUDED_)
#define AFX_TEXTPLAIN_H__333BA6C3_F593_11D1_870E_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MIMEContentAgent.h"

// CTextPlain
// A MIME content agent that handles the "text/plain"
// content type
//
class CTextPlain : public CMIMEContentAgent  
{
public:
	CTextPlain( int nContentType, UINT nWrapPos = 72 );
	virtual ~CTextPlain();

	virtual BOOL AppendPart( LPCTSTR szContent, LPCTSTR szParameters, int nEncoding, BOOL bPath, CString& sDestination );
	virtual CString GetContentTypeString();

protected:
	UINT m_nWrapPos;

	CString wrap_text( LPCTSTR szText );
	virtual CString build_sub_header( LPCTSTR szContent, LPCTSTR szParameters, int nEncoding, BOOL bPath );
};

#endif // !defined(AFX_TEXTPLAIN_H__333BA6C3_F593_11D1_870E_444553540001__INCLUDED_)
