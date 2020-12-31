
// =================================================================
//  class: CMyAccessControl
//  File:  MyAccessControl.cpp
//  
//  Purpose:
//
//	 Override the default Server access control class
//       
// ===================================================================
// Ultimate TCP-IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================

// in the stdafx we defined two macro the 
// MYACCESS_CONTROL_HEADER and CUT_ACCESSCONTROL_BASE_CLASS
// The CUT_ACCESSCONTROL_BASE_CLASS will define the base class which the 
// m_aclObj	 is instantiated from
// this public variabl of CUT_WSServer class will control 
// who has access to the server 
// it also define the mechanism in approving the client as if we should accept the connection 
// or reject it
#include "stdafx.h"
#include "MyAccessControl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyAccessControl::CMyAccessControl()
{

}

CMyAccessControl::~CMyAccessControl()
{

}
//	If you want to control mechanism of delaying and approving the connection 
//	you can override this function 
// 
//
time_t	CMyAccessControl::OnCalcTempBlockTime(in_addr &ipAddress, long lBlockCounter, time_t timeBlockOldExpiry)
{
	return CUT_AccessControl::OnCalcTempBlockTime(ipAddress, lBlockCounter, timeBlockOldExpiry);
}
