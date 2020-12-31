// MIMEContentAgent.h: interface for the CMIMEContentAgent class.
// Author: Wes Clyburn (clyburnw@enmu.edu)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIMECONTENTAGENT_H__74AE0FE2_F4D9_11D1_870E_444553540001__INCLUDED_)
#define AFX_MIMECONTENTAGENT_H__74AE0FE2_F4D9_11D1_870E_444553540001__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// CMIMEContentAgent
// Abstract base class. Content agents support MIME
// content types on behalf of CMIMEMessage
//
class CMIMEContentAgent  
{
public:
	CMIMEContentAgent( int nMIMEType );
	virtual ~CMIMEContentAgent();

	BOOL QueryType( int nContentType );

	virtual BOOL AppendPart( LPCTSTR szContent,
							 LPCTSTR szParameters, 
							 int nEncoding, 
							 BOOL bPath, 
							 CString& sDestination ) = 0;
	virtual CString GetContentTypeString() = 0;

protected:
	virtual CString build_sub_header( LPCTSTR szContent,
									  LPCTSTR szParameters,
									  int nEncoding,
									  BOOL bPath ) = 0;


private:
	int m_nMIMETypeIHandle;
};

#endif // !defined(AFX_MIMECONTENTAGENT_H__74AE0FE2_F4D9_11D1_870E_444553540001__INCLUDED_)
