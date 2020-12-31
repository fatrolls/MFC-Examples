#if !defined(AFX_TESTSET_H__CFCF5300_AEA9_11D1_9811_00A024DFE858__INCLUDED_)
#define AFX_TESTSET_H__CFCF5300_AEA9_11D1_9811_00A024DFE858__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestSet DAO recordset

class CTestSet : public CDaoRecordset
{
public:
	CTestSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTestSet)

// Field/Param Data
	//{{AFX_FIELD(CTestSet, CDaoRecordset)
	short	m_test_number;
	CString	m_test_string;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSET_H__CFCF5300_AEA9_11D1_9811_00A024DFE858__INCLUDED_)
