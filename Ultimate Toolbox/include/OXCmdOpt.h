// ==========================================================================
// 							Class Specification : COXCommandOptions
// ==========================================================================

// Header file : oxcmdopt.h

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
//		Parses the command line options and
//		answers questions about what was requested.
//		This is the 'workhorse' of the whole thing, contains the list of valid options, the map of
//		abbreviations to options, and the values of arguments to the options.

// Remark:

// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////

#ifndef __CMDOPT_H__
#define __CMDOPT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include "OXCmdOpD.h"
#include "OXCmdLne.h"


class OX_CLASS_DECL COXCommandOptions : public CObject
{
DECLARE_DYNAMIC(COXCommandOptions)

// Data members -------------------------------------------------------------
public:

protected:
	CObArray		m_CmdOptDescList;		// Descriptions of possible command line switches

	CMapStringToOb	m_AbbrMap;			// Points abbreviations to objects

	CMapStringToOb	m_Values;				// Points to actual values from user
	// -RUN is stored as Values[RUN] = 1
	// -EMF=foobar is stored as Values[EMF] = foobar.emf
	// -RES=disk -RES=tape is stored as Values[RES] = "disk\ntape"
	// -x a=b is stored as Values[x] = "a=b"

private:

// Member functions ---------------------------------------------------------
public:
	COXCommandOptions();
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

	void Add(COXCommandOptionDesc* pOptionDesc);
	// --- In  : OptionDesc : An Option Description
	// --- Out : 
	// --- Returns :
	// --- Effect : Add the Option Description to the array
	//				You need not to worry about Option descriptions
	//				going out of scope because they are copied internally
	//				before being added to an option description array.
	
	void Add(LPCTSTR psczOptionName, int iFlags,
		LPCTSTR psczDescription, LPCTSTR psczsAbbr = _T(""));
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
	// --- Effect : Add the Option Description to the array

	BOOL Remove(LPCTSTR pszcOption);
	// --- In  : pszcOption : the option to delete
	// --- Out : 
	// --- Returns : succeeded or not
	// --- Effect : Removes this option from all internal lists

	CString	ParseCmdLine(COXCommandLine& cl, CStringList* pRestList = NULL);
	// --- In  : cl : the Command line object to parse
	//			 pRestList : when provided will contain the strings on the command line
	//						 that aren't flags.  Is actually the same as the return string
	//						 except that the separate parts are stored in a Stringlist.
	// --- Out : 
	// --- Returns : Anything left over on the command line after parsing the valid options
	// --- Effect : Construct array of actual parameters based on command line object
	//				Can throw an COXCommandLineException
		
	const COXCommandOptionDesc* GetOptionObject(LPCTSTR psczOption) const;
	// --- In  : psczOption : the name of the option
	// --- Out : 
	// --- Returns : the option object with pszcOption as NAME.  NULL if not found.
	// --- Effect : 
	
	BOOL IsEnabled(LPCTSTR psczOption) const;
	// --- In  : 
	// --- Out : 
	// --- Returns : Did the option appeared on the command line or not
	// --- Effect : It works for any of the argument forms

	CString GetValue(LPCTSTR psczOption) const;
	// --- In  : 
	// --- Out : 
	// --- Returns : The argument associated with the option
	// --- Effect : It is used with single-occurrence, single-argument options

	const CStringList* GetValues(LPCTSTR psczOption) const;
	// --- In  : 
	// --- Out : 
	// --- Returns : The list of arguments associated with the option
	// --- Effect : It is used with single-argument, multiple-occurrence options

	const CMapStringToString* GetAssocPairs(LPCTSTR psczOption) const;
	// --- In  : 
	// --- Out : 
	// --- Returns : The list of combined arguments associated with the option
	// --- Effect : It is used with options that take two arguments, the first being
	//				a key name, the second the value of of the key.  This is useful
	//				for options that set variables like -Dfoo=bar in a compiler

	CString Usage(LPCTSTR psczMsg) const;
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : prints usage message if StdHandles are available

	virtual ~COXCommandOptions();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:
	// Construct abbreviation map from given OptionDesc's
	void BuildAbbrTable();

	// Reset contents of all maps and lists. Called by destructor
	void ResetMaps();

private:

};

#endif
// ==========================================================================
