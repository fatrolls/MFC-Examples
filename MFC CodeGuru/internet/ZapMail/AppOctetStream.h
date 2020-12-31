// AppOctetStream.h: interface for the CAppOctetStream class.
// Author: Wes Clyburn (clyburnw@enmu.edu)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPOCTETSTREAM_H__333BA6C2_F593_11D1_870E_444553540001__INCLUDED_)
#define AFX_APPOCTETSTREAM_H__333BA6C2_F593_11D1_870E_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MIMEContentAgent.h"

// CAppOctetStream
// A MIME content agent that handles the
// "application/octet-stream" content type
//
class CAppOctetStream : public CMIMEContentAgent  
{
public:
	virtual CString GetContentTypeString();
	CAppOctetStream( int nContentType );
	virtual ~CAppOctetStream();

	virtual BOOL AppendPart( LPCTSTR szContent, 
							 LPCTSTR szParameters, 
							 int nEncoding, 
							 BOOL bPath, 
							 CString& sDestination );

protected:
	virtual void attach_file( CStdioFile* pFileAtt, int nEncoding, CString& sDestination );
	virtual CString build_sub_header( LPCTSTR szContent, 
									  LPCTSTR szParameters, 
									  int nEncoding, 
									  BOOL bPath );
};

#endif // !defined(AFX_APPOCTETSTREAM_H__333BA6C2_F593_11D1_870E_444553540001__INCLUDED_)
