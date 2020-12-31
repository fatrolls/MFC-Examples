///////////////////////////////////////////////////////////////////////////////
// MSDI MultiSingle window application (only one document in a MDI)

class CMainFrame;
class CMSDITemplate;

class CMSDIWinApp : public CWinApp
{
public:
  CMSDIWinApp();
  CMSDITemplate* GetDocTemplate(CRuntimeClass* pViewClass);
  CMSDITemplate* GetDocTemplate(CView* pView);
  CDocument* GetDocument();
  CView* GetView(CRuntimeClass* pViewClass);

#ifndef WIN32
public:
  POSITION GetFirstDocTemplatePosition() const;
  CDocTemplate* GetNextDocTemplate(POSITION& rPosition) const;
#endif

// Implementation
public:
  virtual BOOL CloseDocument();
  virtual CMDIChildWnd* CreateOrActivateFrame(CRuntimeClass* pViewClass, CDocument* pDoc);
  virtual CDocument* OpenDocumentFile(LPCSTR pszPathName);

  //{{AFX_MSG(CMSDIWinApp)
  afx_msg void OnFileNew();
  afx_msg void OnFileOpen();
  afx_msg void OnFilePrintSetup();
  afx_msg BOOL OnOpenRecentFile(UINT nID);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////
// MultiSingle doc template for MSDI program (only one document in a MDI)

class CMSDITemplate : public CMultiDocTemplate
{
// Constructors
public:
  CMSDITemplate(UINT nIDResource, CRuntimeClass* pDocClass,
    CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass) :
  CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass) {};

  // this override to reset the document counter to 1
  void SetUntitleCount(UINT Count)
    { m_nUntitledCount = Count; };

  // this overrides to retreive the view and doc runtime class
  CRuntimeClass* GetViewClass()
    { return m_pViewClass; }
  CRuntimeClass* GetDocClass()
    { return m_pDocClass; }
};
