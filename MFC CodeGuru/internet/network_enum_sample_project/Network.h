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

#ifndef Network_h
#define Network_h


#include <winnetwk.h>


#pragma message("network library is linking with \"mpr.lib\"")
#pragma comment(lib, "mpr.lib")


class CNetwork {
	LPTSTR			m_pszError ;

	public:		// constants
		#define _BIT(n)		(1<<n)
		enum {
			GLOBALNET	= _BIT(0),		// search the entire network
			CONNECTED	= _BIT(1),		// search only currently connected resources
			REMEMBERED	= _BIT(2),		// search only "persistent" connections

			TYPE_ANY	= _BIT(3),		// search all types of resources
			TYPE_DISK	= _BIT(4),		// search all disk resources
			TYPE_PRINT	= _BIT(5),		// search all print resources

			SEARCHDEFAULT	= _BIT(0) | _BIT(3)
		} ;
		#undef _BIT

	protected:		// construction/destruction
		CNetwork() ;		// make this class a base-class.

	public:
		virtual ~CNetwork() ;

	public:		// attributes
		LPCTSTR		GetErrorString() const ;

		// The following functions can be used in your overridden
		// "OnHitResource()" member-function (see below), to
		// determine the type of the resource.
		
		// NOTE: Only one of these functions can return TRUE.
		BOOL			IsServer( NETRESOURCE & ) const ;
		BOOL			IsDomain( NETRESOURCE & ) const ;
		BOOL			IsShare( NETRESOURCE & ) const ;
		BOOL			IsGeneric( NETRESOURCE & ) const ;
		
		// The following functions will simplify the LPNETRESOURCE access:
		LPCTSTR			GetLocalName( NETRESOURCE & ) const ;
		LPCTSTR			GetRemoteName( NETRESOURCE & ) const ;
		LPCTSTR			GetComment( NETRESOURCE & ) const ;
		LPCTSTR			GetProvider( NETRESOURCE & ) const ;
		BOOL			IsConnectable( NETRESOURCE & ) const ;


	public:		// operations
			// Enumerate the network. See OnHitResource() and NetError() below.
		BOOL		Enumerate(
						DWORD dwFlags = CNetwork::SEARCHDEFAULT
					);

			// Add a connection to the network.
			// If you want to connect to a local drive ("H:" for instance),
			// you have to fill out the "lpLocalName" of <NetRC> (if this
			// member is NULL or empty).
			// <dwFlags> can be set to "CONNECT_UPDATE_PROFILE" to make the
			// connection persistent (i.e. reconnect when the user logs on).
			// if <UserName> is NULL, it defaults to the current user.
			// if <Password> is NULL, it defaults to the <Username>'s password.
			// This function calls NetError() (see below) and returns FALSE
			// if the connection fails; TRUE on success.
			// See WNetAddConnection2() in the online-help for more details
		BOOL		AddConnection(
						NETRESOURCE & NetRC,
						DWORD Flags = 0,
						LPTSTR UserName = 0,
						LPTSTR Password = 0
					);

		
			// Cancel a network-connection. Returns TRUE on success; FALSE on
			// failure. The NetError() method (see below) will be called on
			// failure. For further information see WNetCancelConnection2()
			// in the online-help.
		BOOL		CancelConnection(
						LPTSTR szName,
						DWORD dwFlags = CONNECT_UPDATE_PROFILE,
						BOOL ForceDisconnect = FALSE
					);
		BOOL		CancelConnection(
						NETRESOURCE & NetRC,
						DWORD dwFlags = CONNECT_UPDATE_PROFILE,
						BOOL ForceDisconnect = FALSE
					);

	protected:	// overridables
			// OnHitResource will be called whenever the enumerator finds
			// a net resource. See "Enumerate()" above.
		virtual BOOL	OnHitResource( NETRESOURCE & ) = 0;

			// Override the NetError() method, if you want to handle
			// errors in a different way than the default. Normally
			// NetError() retrieves a human readable error-reason and
			// stores this in "m_pszError" (see GetErrorString() above).
			// The default-implementation of NetError() returns FALSE
			// always. This will cause the enumerator to break off the
			// enumeration. You can handle minor errors (such as
			// ERROR_BAD_NETPATH) in your derived class and return TRUE
			// to continue the enumeration with the next resource:
			//		BOOL CMyNetImpl :: NetError(DWORD dwErrNo, LPCTSTR pszFnc) {
			//			if( dwErrNo == ERROR_BAD_NETPATH )
			//				// minor error: a resource is not accessible at this time
			//				// return with next resource ...
			//				return TRUE;
			//			else
			//				// serious error: break off the enumeration
			//				return CNetwork::NetError(dwErrNo, pszFnc);
			//		}
		virtual BOOL	NetError( DWORD dwErrNo, LPCTSTR pszFunction );

	private:	// implementation
		BOOL			Enumerate( LPNETRESOURCE, DWORD );
} ;





//////////////////////////////////////////////////////////////////////////////
// CNetwork -- inlining ...

inline LPCTSTR CNetwork :: GetErrorString() const {
	return m_pszError ;
}

inline BOOL CNetwork :: CancelConnection(NETRESOURCE & rNetRC, DWORD dwFlags, BOOL bForce) {
	return CancelConnection(rNetRC.lpLocalName, dwFlags, bForce);
}

inline BOOL CNetwork :: IsServer( NETRESOURCE & rNetRC_p ) const {
	return (rNetRC_p.dwDisplayType == RESOURCEDISPLAYTYPE_SERVER)
			? TRUE : FALSE ;
}
inline BOOL CNetwork :: IsDomain( NETRESOURCE & rNetRC_p ) const {
	return (rNetRC_p.dwDisplayType == RESOURCEDISPLAYTYPE_DOMAIN)
			? TRUE : FALSE ;
}

inline BOOL CNetwork :: IsShare( NETRESOURCE & rNetRC_p ) const {
	return (rNetRC_p.dwDisplayType == RESOURCEDISPLAYTYPE_SHARE)
			? TRUE : FALSE ;
}

inline BOOL CNetwork :: IsGeneric( NETRESOURCE & rNetRC_p ) const {
	return (rNetRC_p.dwDisplayType == RESOURCEDISPLAYTYPE_GENERIC)
			? TRUE : FALSE ;
}

inline LPCTSTR CNetwork :: GetLocalName( NETRESOURCE & rNetRC_p ) const {
	return rNetRC_p.lpLocalName ;
}

inline LPCTSTR CNetwork :: GetRemoteName( NETRESOURCE & rNetRC_p ) const {
	return rNetRC_p.lpRemoteName ;
}

inline LPCTSTR CNetwork :: GetComment( NETRESOURCE & rNetRC_p ) const {
	return rNetRC_p.lpComment ;
}

inline LPCTSTR CNetwork :: GetProvider( NETRESOURCE & rNetRC_p ) const {
	return rNetRC_p.lpProvider ;
}

inline BOOL CNetwork :: IsConnectable( NETRESOURCE & rNetRC_p ) const {
	return (
		(rNetRC_p.dwScope == RESOURCE_GLOBALNET)
				&&
		(RESOURCEUSAGE_CONNECTABLE == (rNetRC_p.dwUsage & RESOURCEUSAGE_CONNECTABLE))
	) ? TRUE : FALSE ;
}

#endif	// Network_h