// ==========================================================================
// 							Class Specification : CMeasureSheet
// ==========================================================================

// Header file : MeasSht.h


//=================== Dundas Software     ===================================
//
// //////////////////////////////////////////////////////////////////////////                       
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from COXDockPropertySheet

//	YES	Is a Cwnd.                     
//	YES	Two stage creation (constructor & Create())
//	YES	Has a message map
//	NO  Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class combines the functionality of a tabbed property sheet and a 
//	dockable dialog bar

// Remark:
//	

// Prerequisites (necessary conditions):
//	

/////////////////////////////////////////////////////////////////////////////
#ifndef __MEASSHT_H__
#define __MEASSHT_H__

#include "OXDckPSh.h"
#include "measpage.h"
#include "sctpage.h"

class CMeasureSheet : public COXDockPropertySheet
{
// Data Members

public:
	CMeasurePage	m_measurePage;
	CSectionPage	m_sectionPage;

	//{{AFX_DATA(CMeasureSheet)
	//}}AFX_DATA

protected:

private:

// Member Functions
public:
	CMeasureSheet();  
//	BOOL Create(CWnd* pParentWnd, UINT nStyle);
	void AddOnePage();

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeasureSheet)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMeasureSheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:


};

#endif //__MEASSHT_H__
