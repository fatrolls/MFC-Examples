#if !defined(AFX_RSOLE_H__18FE2117_F229_11D1_8F3C_0080C82231F1__INCLUDED_)
#define AFX_RSOLE_H__18FE2117_F229_11D1_8F3C_0080C82231F1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RSOle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RSOle DAO recordset

class RSOle : public CDaoRecordset
{
public:
	RSOle(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(RSOle)

// Field/Param Data
	//{{AFX_FIELD(RSOle, CDaoRecordset)
	long	m_ID;
	CString	m_SomeText;
	CByteArray	m_Images;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RSOle)
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

#endif // !defined(AFX_RSOLE_H__18FE2117_F229_11D1_8F3C_0080C82231F1__INCLUDED_)
