// ex28bSet.h : interface of the Cex28bSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX28BSET_H__E38A6DC5_6F02_11D0_860F_D6B8FDE4DD70__INCLUDED_)
#define AFX_EX28BSET_H__E38A6DC5_6F02_11D0_860F_D6B8FDE4DD70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx28bSet : public CRecordset
{
public:
	CEx28bSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEx28bSet)

// Field/Param Data
	//{{AFX_FIELD(CEx28bSet, CRecordset)
	CString	m_InstructorID;
	CString	m_Name;
	CString	m_RoomNo;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28bSet)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX28BSET_H__E38A6DC5_6F02_11D0_860F_D6B8FDE4DD70__INCLUDED_)
