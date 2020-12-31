// CompleteSet.h : header file
//

#ifndef _COMPLETESET_H
#define _COMPLETESET_H

/////////////////////////////////////////////////////////////////////////////
// CCompleteSet DAO recordset

class CCompleteSet : public CDaoRecordset
{
public:
	CCompleteSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCompleteSet)

// Field/Param Data
	//{{AFX_FIELD(CCompleteSet, CDaoRecordset)
	long	m_lID;
	CString	m_strCity;
	CString	m_strState;
	CString	m_strFrequency;
	CString	m_strInput;
	CString	m_strCallsign;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompleteSet)
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

#endif
