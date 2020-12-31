// CustSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomersSet DAO recordset

extern TABLESET CustomersTable;

class CCustomersSet : public CDAORecordset
{
public:
	CCustomersSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCustomersSet)

// Field/Param Data
	//{{AFX_FIELD(CCustomersSet, CDAORecordset)
	CString m_CustomerID;
	CString m_CompanyName;
	CString m_ContactName;
	CString m_ContactTitle;
	CString m_Address;
	CString m_City;
	CString m_Region;
	CString m_PostalCode;
	CString m_Country;
	CString m_Phone;
	CString m_Fax;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomersSet)
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
