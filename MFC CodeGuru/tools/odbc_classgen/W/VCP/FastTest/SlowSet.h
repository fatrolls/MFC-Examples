#if !defined(AFX_SLOWSET_H__7137DCA1_B77C_11D1_AE72_0004AC31E75C__INCLUDED_)
#define AFX_SLOWSET_H__7137DCA1_B77C_11D1_AE72_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SlowSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSlowSet recordset

class CSlowSet : public CRecordset
{
public:
	CSlowSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSlowSet)

// Field/Param Data
	//{{AFX_FIELD(CSlowSet, CRecordset)
	CString	m_CODE;
	CString	m_NAME;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlowSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLOWSET_H__7137DCA1_B77C_11D1_AE72_0004AC31E75C__INCLUDED_)
