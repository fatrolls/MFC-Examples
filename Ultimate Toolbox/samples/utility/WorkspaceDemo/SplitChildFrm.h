// ==========================================================================
// 					Class Specification : CSplitChildFrame
// ==========================================================================

// Header file : SplitChildFrm.h


//===============  Dundas Software ==================================
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CMDIChildWnd

//	YES	Is a Cwnd.                     
//	YES	Two stage creation (constructor & Create())
//	YES	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         

// Remark:

// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __SPLITCHILDFRM_H__
#define __SPLITCHILDFRM_H__

class CSplitChildFrame : public CMDIChildWnd
{
DECLARE_DYNCREATE(CSplitChildFrame)
// Data members -------------------------------------------------------------
public:
protected:
	CSplitterWnd m_wndSplitter;

private:
	
// Member functions ---------------------------------------------------------
public:
	CSplitChildFrame();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructs the object

#ifdef _DEBUG
	virtual void AssertValid() const;
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : AssertValid performs a validity check on this object 
	//				by checking its internal state. 
	//				In the Debug version of the library, AssertValid may assert and 
	//				thus terminate the program.
	
	virtual void Dump(CDumpContext& dc) const;
	// --- In  : dc : The diagnostic dump context for dumping, usually afxDump.
	// --- Out : 
	// --- Returns :
	// --- Effect : Dumps the contents of the object to a CDumpContext object. 
	//				It provides diagnostic services for yourself and 
	//				 other users of your class. 
	//				Note  The Dump function does not print a newline character
	//				 at the end of its output. 
#endif

	virtual ~CSplitChildFrame();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of the object

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitChildFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CSplitChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
                   
};

#endif // __SPLITCHILDFRM_H__
// ==========================================================================
