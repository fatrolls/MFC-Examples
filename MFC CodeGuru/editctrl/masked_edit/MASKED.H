// MaskEd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaskEdit class

class CMaskEdit : public CEdit
{
  DECLARE_DYNAMIC(CMaskEdit)

// Constructors
public:
  CMaskEdit();

// Attributes
  BOOL m_bUseMask;
  BOOL m_isdate; //added this
  CString m_str; //added this
  CString m_strMask;
  CString m_strLiteral;
  CString m_strValid;
  BOOL m_bMaskKeyInProgress;

// Operations
  BOOL CheckChar(UINT nChar);
  void SetMask(LPCSTR lpMask, LPCSTR lpLiteral = NULL, LPCSTR lpValid = NULL);
  void SendChar(UINT nChar);

// Implementation
public:

protected:
  // Generated message map functions
  //{{AFX_MSG(CMaskEdit)
  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

class CDateEdit : public CMaskEdit
{
  DECLARE_DYNAMIC(CDateEdit)

// Constructors
public:
  CDateEdit();

// Implementation
public:
  void SetDate(COleDateTime& Date);
  COleDateTime GetDate();

protected:
  // Generated message map functions
  //{{AFX_MSG(CDateEdit)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

class CTimeEdit : public CMaskEdit
{
  DECLARE_DYNAMIC(CTimeEdit)

// Constructors
public:
  CTimeEdit();

// Implementation
public:
  void SetTime(COleDateTime& Date);
  COleDateTime GetTime();

protected:
  // Generated message map functions
  //{{AFX_MSG(CTimeEdit)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

void AFXAPI DDX_OleDate(CDataExchange* pDX, int nIDC, CDateEdit& rControl, COleDateTime& Date);
//added the line below
void AFXAPI DDX_OleDate(CDataExchange* pDX, int nIDC, CTimeEdit& rControl, COleDateTime& Date);
