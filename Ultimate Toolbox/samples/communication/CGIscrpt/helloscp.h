// ==========================================================================
// 					Class Specification : CHelloScript
// ==========================================================================

// Header file : helloscp.h

                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from COXScript

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO 	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	
//   

// Remark:
//		***
// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////

#ifndef __HELLO_H__
#define __HELLO_H__

#include "oxscript.h"

class CHelloScript : public COXScript
{
public:
	CHelloScript();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state
 
	~CHelloScript();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

// Overridable implementations
protected:

    virtual void OnGet(LPCTSTR pszParam);
    virtual void OnPost(LPCTSTR pszType, LPCTSTR pszData);
	virtual void OnRunCommandLine(int argc, char** argv);

};

#endif	// __HELLO_H__
// ==========================================================================

