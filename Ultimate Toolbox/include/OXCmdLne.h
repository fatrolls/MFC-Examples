// ==========================================================================
// 							Class Specification : COXCommandLine
// ==========================================================================

// Header file : oxcmdlne.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO 	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	Yes	Uses exceptions (same as CFile)

// //////////////////////////////////////////////////////////////////////////

// Desciption :
//		Tokenizes the commandline string and serves them up one by one for
//		COXCommandOptions::ParseCommandLine().  Constructor has two forms, one which
//		takes a CStdioFile pointer to support response files to get arround cmd line
//		limitations, the other takes a Character pointer.

// Remark:

// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////

#ifndef __CMDLINE_H__
#define __CMDLINE_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL COXCommandLine : public CObject
{
DECLARE_DYNAMIC(COXCommandLine)
// Expands any meta chars (*, ?, etc) (well, one day it will :-)
// for files in the current working directory...

// Data members -------------------------------------------------------------
public:

protected:
	CStringArray	m_Tokens;
	int				m_NumTokens;

private:

// Member functions ---------------------------------------------------------
public:
	COXCommandLine(LPCSTR pszCmdLine);
	// --- In  : pszCmdLine : the ANSI command line to be tokenized
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

#ifdef WIN32
	COXCommandLine(LPCWSTR pszCmdLine);
	// --- In  : pszCmdLine : the UNICODE command line to be tokenized
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state
#endif

	COXCommandLine(CStdioFile* pInfile);
	// --- In  : pInfile : The file containing a command line
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	inline int GetNumArgs() const;
	// --- In  :
	// --- Out : 
	// --- Returns : The number of separate command line options in this command line
	// --- Effect : 

	inline CString operator[] (const int iElem) const;
	// --- In  : iElem : index of a Command line option
	// --- Out : 
	// --- Returns : a command line option
	// --- Effect : 

	virtual ~COXCommandLine();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:

private:
	void Tokenize(LPTSTR pszCmdLine);
};

inline int COXCommandLine::GetNumArgs() const
	{
	return m_NumTokens;
	}

inline CString COXCommandLine::operator[] (const int iElem) const
	{
	ASSERT((iElem >= 0) && (iElem <= m_NumTokens));
	return m_Tokens[iElem];
	}

#endif
// ==========================================================================
