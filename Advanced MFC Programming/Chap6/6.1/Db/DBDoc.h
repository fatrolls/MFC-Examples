#include "MLDialog.h"

class CDBDoc : public CDocument
{
protected:
	CMLDialog m_dlgModeless;
	CDBDoc();
	DECLARE_DYNCREATE(CDBDoc)

public:
	//{{AFX_VIRTUAL(CDBDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CDBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CDBDoc)
	afx_msg void OnDialogboxModeless();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
