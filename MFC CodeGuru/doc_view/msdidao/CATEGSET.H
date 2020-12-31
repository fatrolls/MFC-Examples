// CategSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCategoriesSet DAO recordset

extern TABLESET CategoriesTable;

class CCategoriesSet : public CDAORecordset
{
public:
	CCategoriesSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCategoriesSet)

// Field/Param Data
	//{{AFX_FIELD(CCategoriesSet, CDAORecordset)
	long	m_CategoryID;
	CString	m_CategoryName;
	CString	m_Description;
	//}}AFX_FIELD
	CDaoBitmap m_Picture;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategoriesSet)
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
