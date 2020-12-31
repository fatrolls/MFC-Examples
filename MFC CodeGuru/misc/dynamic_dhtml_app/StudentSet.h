#if !defined(AFX_STUDENTSET_H__B0992846_E20B_11D1_ABF7_44455354616F__INCLUDED_)
#define AFX_STUDENTSET_H__B0992846_E20B_11D1_ABF7_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StudentSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStudentSet recordset

class CStudentSet : public CRecordset
{
public:
	CStudentSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CStudentSet)

// Field/Param Data
	//{{AFX_FIELD(CStudentSet, CRecordset)
	long	m_StudentID;
	CString	m_Name;
	int		m_GradYear;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStudentSet)
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

#endif // !defined(AFX_STUDENTSET_H__B0992846_E20B_11D1_ABF7_44455354616F__INCLUDED_)
