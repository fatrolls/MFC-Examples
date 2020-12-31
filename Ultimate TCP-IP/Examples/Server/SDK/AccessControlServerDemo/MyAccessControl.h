// MyAccessControl.h: interface for the CMyAccessControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMyAccessControl_H__657B8A3B_F207_11D4_A978_0050BAAAE90D__INCLUDED_)
#define AFX_CMyAccessControl_H__657B8A3B_F207_11D4_A978_0050BAAAE90D__INCLUDED_


#ifndef MY_UT_ACCESS_CONTROL_CLASS_BASE
#define MY_UT_ACCESS_CONTROL_CLASS_BASE CMyAccessControl
#endif 


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UT_AccessControl.h"

class CMyAccessControl : public CUT_AccessControl  
{
public:
	CMyAccessControl();
	virtual ~CMyAccessControl();

protected:
	// Called in the AddTempBlockedAddress function to calculate the expiration time of the block
	virtual time_t	OnCalcTempBlockTime(in_addr &ipAddress, long lBlockCounter, time_t timeBlockOldExpiry);
};

#endif // !defined(AFX_CMyAccessControl_H__657B8A3B_F207_11D4_A978_0050BAAAE90D__INCLUDED_)
