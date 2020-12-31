#ifndef __BANK_H__
#define __BANK_H__

// Bank.h : header file
//

#define IMPLEMENT_OLECREATE2(class_name, external_name, \
  l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
  AFX_DATADEF COleObjectFactory class_name::factory(class_name::guid, \
  RUNTIME_CLASS(class_name), TRUE, _T(external_name)); \
  const AFX_DATADEF GUID class_name::guid = \
  { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };


/////////////////////////////////////////////////////////////////////////////
// CBank command target

class CBank : public CCmdTarget
{
	DECLARE_DYNCREATE(CBank)

public:
	double m_dBalance;
	CBank();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBank)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBank();

	// Generated message map functions
	//{{AFX_MSG(CBank)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CBank)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CBank)
	afx_msg double GetBalance();
	afx_msg void SetBalance(double newValue);
	afx_msg double Withdrawal(double dAount);
	afx_msg void Deposit(double dAmount);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __BANK_H__
