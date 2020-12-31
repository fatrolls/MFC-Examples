/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1997 by Joerg Koenig and the ADG mbH, Mannheim, Germany
// All rights reserved
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    J.Koenig@adg.de                 (company site)
//    Joerg.Koenig@rhein-neckar.de    (private site)
/////////////////////////////////////////////////////////////////////////////

// last revised $Date: 3.02.98 20:27 $

#include "stdafx.h"
#include "Network.h"

/////////////////////////////////////////////////////////////////////////////
// local helper classes CNetworkError and CNetworkBreak - used for exceptions.

class CNetworkBreak {
	public:
		CNetworkBreak(BOOL bRet) : m_bRet(bRet) {}

		BOOL m_bRet;
};

class CNetworkError : public CNetworkBreak {
	public:
		CNetworkError(BOOL bRet) : CNetworkBreak(bRet) {}
};



/////////////////////////////////////////////////////////////////////////////
CNetwork :: CNetwork()
	: m_pszError( 0 )
{
}

CNetwork :: ~CNetwork() {
	delete [] m_pszError ;
}


BOOL CNetwork :: Enumerate( DWORD dwFlags_p ) {
	BOOL bRet;
	try {
		bRet = Enumerate(0, dwFlags_p);
	} catch( CNetworkBreak err ) {
		bRet = err.m_bRet;
	}

	return bRet;
}

BOOL CNetwork :: AddConnection(
						NETRESOURCE & rNetRC,
						DWORD dwFlags,		// = 0
						LPTSTR szUserName,	// = NULL
						LPTSTR szPassword	// = NULL
				) {
	DWORD dwResult = WNetAddConnection2(&rNetRC, szUserName, szPassword, dwFlags);
	if( dwResult != NO_ERROR )
		NetError(GetLastError(), TEXT("WNetAddConnection2"));
	return (dwResult==NO_ERROR) ? TRUE : FALSE;
}

BOOL CNetwork :: CancelConnection(
						LPTSTR szName,
						DWORD dwFlags,		// = CONNECT_UPDATE_PROFILE
						BOOL bForce			// = FALSE
				) {
	DWORD dwResult = WNetCancelConnection2(szName, dwFlags, bForce);
	if( dwResult != NO_ERROR )
		NetError(GetLastError(), TEXT("WNetCancelConnection2"));
	return (dwResult==NO_ERROR) ? TRUE : FALSE;
}

BOOL CNetwork :: Enumerate( LPNETRESOURCE lpNetRC_p, DWORD dwFlags_p ) {
	HANDLE hEnum = 0;
	DWORD dwScope = RESOURCE_GLOBALNET ;
	if( dwFlags_p & CONNECTED )			dwScope = RESOURCE_CONNECTED ;
	else if( dwFlags_p & REMEMBERED )	dwScope = RESOURCE_REMEMBERED ;
	// else GLOBALNET ...

	DWORD dwType = RESOURCETYPE_ANY ;
	if( dwFlags_p & TYPE_DISK )			dwType = RESOURCETYPE_DISK ;
	else if( dwFlags_p & TYPE_PRINT )	dwType = RESOURCETYPE_PRINT ;
	// else TYPE_ANY ...

	DWORD dwResult =	WNetOpenEnum(
							dwScope,		// scope of enumeration
							dwType,			// resource types to list
							0,				// enumerate all resources
							lpNetRC_p,		// pointer to resource structure (NULL at first time)
							&hEnum			// handle to resource
						) ;

	if( dwResult != NO_ERROR )
		return NetError(dwResult, TEXT("WNetOpenEnum"));

	DWORD dwBuffer = 16384 ;		// 16K is reasonable size
	DWORD dwEntries = 0xFFFFFFFF ;	// enumerate all possible entries
	LPNETRESOURCE lpnrLocal = 0;

	BOOL bRet = TRUE;

	try {
		do {
			// first allocate buffer for NETRESOURCE structures ...
			lpnrLocal = (LPNETRESOURCE) GlobalAlloc( GPTR, dwBuffer ) ;

			dwResult =	WNetEnumResource(
							hEnum,		// resource-handle
							&dwEntries,
							lpnrLocal,
							&dwBuffer
						) ;

			if( dwResult == NO_ERROR ) {
				for( register DWORD i = 0 ; i < dwEntries ; i++ ) {
					if( ! OnHitResource( lpnrLocal[i] ) ) {
						TRACE0("CNetwork::Enumerate(): OnHitResource() breaks enumeration\n");
						throw CNetworkBreak(FALSE) ;
					}
					if( RESOURCEUSAGE_CONTAINER == 
							(lpnrLocal[i].dwUsage & RESOURCEUSAGE_CONTAINER) &&
							lpnrLocal[i].dwDisplayType != RESOURCEDISPLAYTYPE_SERVER ) 
						if( !Enumerate( &lpnrLocal[i], dwFlags_p ) ) {
							TRACE0( "CNetwork::Enumerate(): recursiv call failed\n" );
							throw CNetworkBreak(FALSE);
						} 

				}
			} else if( dwResult != ERROR_NO_MORE_ITEMS ) {
				throw CNetworkError(NetError(dwResult, TEXT("WNetEnumResource")));
			}
		} while( dwResult != ERROR_NO_MORE_ITEMS );
	} catch( CNetworkError err ) {
		bRet = err.m_bRet;
	}

	if( lpnrLocal )
		GlobalFree((HGLOBAL) lpnrLocal) ;
	
	WNetCloseEnum(hEnum) ;

	return bRet;
}


BOOL CNetwork :: NetError( DWORD dwErrorCode, LPCTSTR lpszFunction ) { 
	if( m_pszError == 0 ) {
		m_pszError = new TCHAR [512] ;
		m_pszError[0] = TEXT('\0') ;
	}

	char buf[ 256 ] ;
	buf[0] = TEXT('\0') ;
 
 
	if (dwErrorCode != ERROR_EXTENDED_ERROR) {
		// The following code performs standard error-handling.
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, dwErrorCode,
					  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					  buf, 256, 0);
		wsprintf(m_pszError, TEXT("%s failed; Result is %ld (\"%s\")"),
			lpszFunction, dwErrorCode, buf );
	} else {
		// The following code performs error-handling when the
		// ERROR_EXTENDED_ERROR return value indicates that WNetGetLastError
		// can retrieve additional information.
		DWORD dwLastError;
		TCHAR szDescription[256];
		TCHAR szProvider[256];
		DWORD dwResult =	WNetGetLastError(
								&dwLastError,
								szDescription,  // buffer for error description
								sizeof(szDescription), 
								szProvider,     // buffer for provider name
								sizeof(szProvider)
							);

		if(dwResult != NO_ERROR) {
			wsprintf(m_pszError,
				TEXT("WNetGetLastError failed; error %ld"), dwResult);
		} else {
	        szDescription[_tcsclen(szDescription)-2] = TEXT('\0');  //remove cr/nl characters
			wsprintf(m_pszError,
				TEXT("%s failed with code %ld (\"%s\")"),
				szProvider, dwLastError, szDescription);
		}
	}

	TRACE1(TEXT("CNetwork: %s\n"), m_pszError);

	return FALSE;
} 
