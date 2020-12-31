// DaoDoc.h : interface of the CMSDIDaoDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CCategoriesSet;
class CCustomersSet;
// ... ADDALL

int DaoMessageBox(CDaoException* e, UINT nType = MB_OK, UINT nIDHelp = 0);

class CMSDIDaoDoc : public CDocument
{
protected: // create from serialization only
	CMSDIDaoDoc();
	DECLARE_DYNCREATE(CMSDIDaoDoc)

// Attributes
public:
	// the database object, only one
	CDaoDatabase m_db;

// Operations
public:
	BOOL CreateNewDatabase(LPCTSTR lpszPathName);
	virtual void CloseDataBase();

	void CreateTable(LPCSTR lpcsTableName, TABLEFIELD* pFieldInfo, TABLEKEY* pKeyInfo);
	BOOL TableExist(LPCSTR lpszTableName);

	// catégories
	CCategoriesSet *m_pCategoriesSet;
	CCategoriesSet* OpenCategories();
	void CloseCategories();

	// customers
	CCustomersSet *m_pCustomersSet;
	CCustomersSet* OpenCustomers();
	void CloseCustomers();

	// ... ADDALL

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSDIDaoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMSDIDaoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMSDIDaoDoc)
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnTableCategories();
	afx_msg void OnTableCustomers();
	afx_msg void OnFormCateg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

