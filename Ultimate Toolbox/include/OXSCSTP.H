// ==========================================================================
// 							Class Specification : COXSerialCommSetup
// ==========================================================================

// Header file : OXSCSTP.H

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Is derived from CDialog
//	YES Two stage creation (constructor & Initialize())
//	YES	Has a message map
//	YES Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Description :         
//	COXSerialCommSetup class
//		The COXSerialCommSetup is a standard dialog for setting the Serial
//		Communication Configuration settings. This dialog can be popped up
//		with the DoConfigDialog() function of the COXSerialCommConfig class.

// Remark:
//


// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXSCSTP_H_
#define __OXSCSTP_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include "OXSCCFG.H"

// private header
#include "OXRSERCM.H"


/////////////////////////////////////////////////////////////////////////////
class OX_CLASS_DECL COXSerialCommSetup : public CDialog
/////////////////////////////////////////////////////////////////////////////
{
// Data Members
public:
	const CString m_sCommTitle;
    COXSerialCommConfig m_config;

    //{{AFX_DATA(COXSerialCommSetup)
    enum { IDD = IDD_COMMSETUP };
    CString    m_sBaudRate;
    CString    m_sDataBit;
    CString    m_sParity;
    CString    m_sPort;
    CString    m_sStopBit;
    CString    m_sFlowControl;
    //}}AFX_DATA


protected:
private:

// Member Functions
public:
    COXSerialCommSetup(CString sTitle = _T(""), CWnd* pParent = NULL);
	// --- In: sTitle: the title of the dialog box (used default title if ignored)
	//		   pParent: parent window
	// --- Out: none
	// --- Returns: none
	// --- Effect: constructs the dialog object


protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(COXSerialCommSetup)
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    CString BaudRateToString(UINT Val);
    CString ParityToString(BYTE Val);
    CString FlowControlToString(COXSerialCommConfig::EFlowControl eVal);
    UINT BaudRateToVal(CString sString);
    BYTE ParityToVal(CString sString);
    COXSerialCommConfig::EFlowControl FlowControlToVal(CString sString);
private:

};
/////////////////////////////////////////////////////////////////////////////

#endif //__OXSCSTP_H_
