/////////////////////////////////////////////////////////////////////////////
// interface of the COutView class

class COutView : public CEditView
{
protected:
  DECLARE_DYNCREATE(COutView)
  COutView();

// Attributes
protected:

// Operations
public:
  void  WriteTTY(LPCSTR lpszString);
  void  ClearTTY();

// Implementation
public:
  virtual ~COutView();
protected:
	virtual void OnInitialUpdate();

  // Printing support
protected:
  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  // Generated message map functions
protected:
  //{{AFX_MSG(COutView)
  afx_msg void OnDestroy();
  afx_msg void OnChange();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};
