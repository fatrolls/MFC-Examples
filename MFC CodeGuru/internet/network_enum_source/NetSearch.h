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

#ifndef NetSearch_h
#define NetSearch_h

#include "Network.h"

template <class T>
class CNetSearch : public CNetwork {
	typedef BOOL (T::*NsFnc)(NETRESOURCE &);

	T *			m_pTheObject;
	NsFnc		m_NsFnc;

	public:		// construction
		CNetSearch() : m_pTheObject(0), m_NsFnc(0) {}

		void	Create(T * pObj, NsFnc fnc) {
					ASSERT(pObj != 0);
					ASSERT(fnc != 0);
					m_pTheObject = pObj;
					m_NsFnc = fnc;
				}

	protected:	// overridables
		virtual BOOL	OnHitResource(NETRESOURCE & rNetRC) {
							return (m_pTheObject->*m_NsFnc)(rNetRC);
						}

		virtual BOOL	NetError(DWORD dwErrorCode, LPCTSTR lpszFunction) {
							switch(dwErrorCode) {
								case ERROR_BAD_NETPATH:
								case ERROR_NO_NETWORK:
									// minor errors: continue enumeration
									return TRUE;
							}
							// serious error: break enumeration
							return CNetwork::NetError(dwErrorCode, lpszFunction);
						}
};

#endif	// NetSearch_h
