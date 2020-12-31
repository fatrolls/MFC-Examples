// ==========================================================================
// 							Class Specification : COXCommandLineException
// ==========================================================================

// Header file : oxcmdlex.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CException

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO  Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class encapsulates a new exception for Command line parsing

// Remark:
//		

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////
#ifndef __CMDLEXCEPTION_H__
#define __CMDLEXCEPTION_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class COXCommandOptions;

class OX_CLASS_DECL COXCommandLineException : public CException
{
DECLARE_DYNAMIC(COXCommandLineException)
    
// Data members -------------------------------------------------------------
public:

protected:
 	CString m_sErrMsg;
   
private:

// Member functions ---------------------------------------------------------
public:
    COXCommandLineException(LPCTSTR pszcError, COXCommandOptions* pCmdOpt = NULL);
	// --- In  : pszcError : the actual Errormessage 
	//			 pCmdOpt : the command option object that parses the command line.
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state
	//				This constructor will expand the error message with some
	//				extra information concerning the command line being parsed	

	virtual BOOL GetErrorMessage(LPTSTR lpszError, UINT nMaxError, UINT* pnHelpContext = NULL );
	// --- In  : see CException::GetErrorMessage()
	// --- Out : 
	// --- Returns : TRUE if string available, otherwise FALSE
	// --- Effect : retrieves the error string if available

	BOOL WriteToStdErr();
	// --- In  : 
	// --- Out : 
	// --- Returns : TRUE if write was successful, otherwise FALSE
	// --- Effect : Writes the error message to the STDERR (for use in CONSOLE programs)


protected:      

private:
		
};

#endif
// ==========================================================================
