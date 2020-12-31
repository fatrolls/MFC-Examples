// ResizingPropPage.h : header file
//

#ifndef __RESIZINGPROPPAGE_H__
#define __RESIZINGPROPPAGE_H__

class COXLayoutManager;

/////////////////////////////////////////////////////////////////////////////
// CResizingPropPage1 dialog

class CResizingPropPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CResizingPropPage1)

// Construction
public:
	CResizingPropPage1();
	~CResizingPropPage1();

// Dialog Data
	//{{AFX_DATA(CResizingPropPage1)
	enum { IDD = IDD_PAGE1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CResizingPropPage1)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	COXLayoutManager* m_pLayoutManager;

	//{{AFX_MSG(CResizingPropPage1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


class CResizingPropPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CResizingPropPage2)

// Construction
public:
	CResizingPropPage2();
	~CResizingPropPage2();

// Dialog Data
	//{{AFX_DATA(CResizingPropPage2)
	enum { IDD = IDD_PAGE2 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CResizingPropPage2)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	COXLayoutManager* m_pLayoutManager;

	//{{AFX_MSG(CResizingPropPage2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __RESIZINGPROPPAGE_H__
