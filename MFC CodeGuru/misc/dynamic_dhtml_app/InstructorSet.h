#if !defined(AFX_INSTRUCTORSET_H__B0992843_E20B_11D1_ABF7_44455354616F__INCLUDED_)
#define AFX_INSTRUCTORSET_H__B0992843_E20B_11D1_ABF7_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InstructorSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInstructorSet recordset

class CInstructorSet : public CRecordset
{
public:
	CInstructorSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CInstructorSet)

// Field/Param Data
	//{{AFX_FIELD(CInstructorSet, CRecordset)
	CString	m_InstructorID;
	CString	m_Name;
	CString	m_RoomNo;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstructorSet)
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

#endif // !defined(AFX_INSTRUCTORSET_H__B0992843_E20B_11D1_ABF7_44455354616F__INCLUDED_)
