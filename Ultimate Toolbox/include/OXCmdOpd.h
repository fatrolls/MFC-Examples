// ==========================================================================
// 							Class Specification : COXCommandOptionDesc
// ==========================================================================

// Header file : oxcmdopd.h

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
//		Contains information about a command option, its full name, abbreviations, 
//		description, etc.
//		For detailed explanation, see constructor with parameters.

// Remark:
//		   The option descriptor class, each instance of 
//		   this class represents a valid option to the 
//		   program and some properties about that option.
//		   Can be used by CmdOptions to produce a 
//		   usage message as well as to parse valid options.
// Example: 
//  void CMyApp::CreateValidOptions()
//		{
//		COXCommandOptionDesc codHelp  (_T("HELP"),      NULL,        _T("Prints a help message"));
//		COXCommandOptionDesc codRun   (_T("RUN"),       NULL,        _T("Automatically execute a testcase"));
//		COXCommandOptionDesc codEmf   (_T("EMF"),       COD_LASTARG, _T("MetaFile which specified GDI calls to make"));
//		COXCommandOptionDesc codVerify(_T("VERIFY"),    COD_ARGOK,   _T("Verification option"));
//		COXCommandOptionDesc codDiff  (_T("DIFFERENCE"),COD_FIRSTARG,_T("File to write screen differences to"));
//		COXCommandOptionDesc codCmpScr(_T("CMPSCR"),    COD_FIRSTARG,_T("File to compare screen to"));
//		COXCommandOptionDesc codOutScr(_T("OUTSCR"),    COD_FIRSTARG,_T("File to write actual screen to"));
//		COXCommandOptionDesc codMask  (_T("MASK"),      COD_FIRSTARG,_T("File to mask screen differences with"));
//		COXCommandOptionDesc codCrc   (_T("CRC"),       COD_FIRSTARG,_T("File to read/write CRC code from/to"));
//		COXCommandOptionDesc codGen   (_T("GENERATE"),  NULL,        _T("Interactive session for generating EMF file"));
//		COXCommandOptionDesc codRes   (_T("RES"),       COD_ARRAY,   _T("Resources available"));
//		COXCommandOptionDesc codXList (_T("X"),         COD_ASSOCARRAY,_T("Variable/Value pairs"));
//		}

// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////

#ifndef __CMDOPTD_H__
#define __CMDOPTD_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


const int COD_ARGOK			= 0x1;	// Does option take argument?
const int COD_REPEATOK		= 0x2;	// Is option valid more than once?
const int COD_REP_FIRST		= 0x4;	// Use first if option is repeated
const int COD_REP_LAST		= 0x8;	// Use last if option is repeated
const int COD_REP_ARRAY		= 0x10;	// Build array if option is repeated
const int COD_ASSOCIATIVE	= 0x20;	// Takes two arguments i.e. /X=variable=value
const int COD_FIRSTARG		= COD_ARGOK | COD_REPEATOK | COD_REP_FIRST;
const int COD_LASTARG		= COD_ARGOK | COD_REPEATOK | COD_REP_LAST;
const int COD_ARRAY			= COD_ARGOK | COD_REPEATOK | COD_REP_ARRAY;
const int COD_ASSOCARRAY	= COD_ARGOK | COD_REPEATOK | COD_ASSOCIATIVE;

// Currently allows for COD_REP_FIRST && COD_REP_LAST, and other nonsense combinations.
// This is not correct so pay attention to which flags you are combining !!!!!

class OX_CLASS_DECL COXCommandOptionDesc	: public CObject
{
DECLARE_DYNAMIC(COXCommandOptionDesc)

// Data members -------------------------------------------------------------
public:

protected:
	CString		m_sOptionName;
	int			m_nFlags;
	CString		m_sDescription;
	CString		m_sAbbr;

private:

// Member functions ---------------------------------------------------------
public:
	COXCommandOptionDesc();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	COXCommandOptionDesc(LPCTSTR psczOptionName, int iFlags,
		LPCTSTR psczDescription, LPCTSTR psczAbbr = _T(""));
	// --- In  : psczOptionName : the name of the option, CASE-INSENSITIVE
	//			 iFlags : the flags of the option
	//					COD_ARGOK		Does option take an argument
	//					COD_REPEATOK	Is option valid morethan once?
	//					COD_REP_FIRST	Use first if option is repeated
	//					COD_REP_LAST	Use last if option is repeated (i.e. /l dir1 /l dir2)
	//					COD_REP_ARRAY	Build array if option is repeated
	//					COD_ASSOCIATIVE	Takes two arguments i.e. /D variable=value or /D variable value
	//					COD_FIRSTARG	Takes an argument, is repeatable, and repeats are ignored
	//					COD_LASTARG		Takes an argument, is repeatable, and repeats are ignored
	//					COD_ARRAY		Takes an argument, is repeatable, builds an array
	//									(i.e. The INCLUDE option would use this)
	//					COD_ASSOCARRAY	Takes two arguments, is repeatable, builds associative array	
	//									
	//			 psczDescription : the description of the option, for usage messages
	//			 psczAbbr : the abbreviation of the option.
	//						A DEFINITE abbreviation of the argument, this abbreviation will
	//						be used unless it conflicts with another option's DEFINITE abbreviation.
	//						This can be used to have an abbreviation of I for the INCLUDE option, even
	//						if there is another option which begins with I.
	//						For all options, any UNIQUE shortening of the option name is acceptable.
	//						For example, with an option name of INCLUDE, possible abbreviations would
	//						be I, IN, INC, INCL, INCLU, INCLUD.  Which of these possibilities are
	//						valid, depends on which ones are are unique for a given option set.
	//						The DEFINITE abbreviation need not be a true abbreviation of the option name.
	//						For example, an option name EXPORT, could have a DEFINITE abbreviation
	//						of X even though that is not strictly an abbreviation of the name.
	//
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

    COXCommandOptionDesc(const COXCommandOptionDesc& OptDescSrc);
	// --- In :	OptDescSrc : COXCommandOptionDesc object which will be copied
	// --- Out : 
	// --- Returns :
	// --- Effect : Copy contruction.
	
	COXCommandOptionDesc& operator=(const COXCommandOptionDesc& OptDescSrc);
	// --- In :	OptDescSrc : COXCommandOptionDesc object which will be assign to 'this' COXCommandOptionDesc object
	// --- Out:
	// --- Returns: 
	// --- Effect : Assignment operator

	int TakesArg() const;
	// --- In  :
	// --- Out : 
	// --- Returns : does this option takes arguments or not
	// --- Effect : 

	int IsRepeatable() const;
	// --- In  :
	// --- Out : 
	// --- Returns : can this option appear more than once on a command line
	// --- Effect : 

	int ReturnsFirstRep() const;
	// --- In  :
	// --- Out : 
	// --- Returns : will only the first occurrence of this option be recorded or not 
	// --- Effect : 

	int ReturnsLastRep() const;
	// --- In  :
	// --- Out : 
	// --- Returns : will only the last occurrence of this option be recorded or not 
	// --- Effect : 

	int ReturnsArray() const;
	// --- In  :
	// --- Out : 
	// --- Returns : will the occurrences of this option build an array or not
	// --- Effect : 

	int ReturnsAssociative() const;
	// --- In  :
	// --- Out : 
	// --- Returns : will the occurrences of this option build an associative array or not
	// --- Effect : 

	LPCTSTR GetDescription() const;
	// --- In  :
	// --- Out : 
	// --- Returns : the description of this option
	// --- Effect : 

	CString GetOptName() const;
	// --- In  :
	// --- Out : 
	// --- Returns : the name of this option
	// --- Effect : 

	CString GetOptAbbr() const;
	// --- In  :
	// --- Out : 
	// --- Returns : the DEFINITE abbreviation of this option
	// --- Effect : 

	virtual ~COXCommandOptionDesc();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

private:
};

inline int COXCommandOptionDesc::TakesArg() const
	{
	return m_nFlags & COD_ARGOK;
	}

inline int COXCommandOptionDesc::IsRepeatable() const
	{
	return m_nFlags & COD_REPEATOK;
	}
inline int COXCommandOptionDesc::ReturnsFirstRep() const
	{
	return m_nFlags & COD_REP_FIRST;
	}
inline int COXCommandOptionDesc::ReturnsLastRep() const
	{
	return m_nFlags & COD_REP_LAST;
	}
inline int COXCommandOptionDesc::ReturnsArray() const
	{
	return m_nFlags & COD_REP_ARRAY;
	}
inline int COXCommandOptionDesc::ReturnsAssociative() const
	{
	return m_nFlags & COD_ASSOCIATIVE;
	}
inline LPCTSTR COXCommandOptionDesc::GetDescription() const
	{
	return m_sDescription;
	}

inline CString COXCommandOptionDesc::GetOptName() const
	{
	return m_sOptionName;
	}

inline CString COXCommandOptionDesc::GetOptAbbr() const
	{
	return m_sAbbr;
	}

#endif
// ==========================================================================
