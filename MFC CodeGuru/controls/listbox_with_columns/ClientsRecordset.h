#if !defined(AFX_CLIENTSRECORDSET_H__226B8182_0B91_11D2_9BA2_967BD4D5D031__INCLUDED_)
#define AFX_CLIENTSRECORDSET_H__226B8182_0B91_11D2_9BA2_967BD4D5D031__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ClientsRecordset.h : header file
//

#include <afxdao.h>

/////////////////////////////////////////////////////////////////////////////
// CClientsRecordset DAO recordset

class CClientsRecordset : public CDaoRecordset
{
public:
	CClientsRecordset(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CClientsRecordset)

// Field/Param Data
	//{{AFX_FIELD(CClientsRecordset, CDaoRecordset)
	long	m_id;
	CString	m_SurName;
	CString	m_SecondName;
	CString	m_Address;
	CString	m_AddrNo;
	CString	m_Phone;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientsRecordset)
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

#endif // !defined(AFX_CLIENTSRECORDSET_H__226B8182_0B91_11D2_9BA2_967BD4D5D031__INCLUDED_)
