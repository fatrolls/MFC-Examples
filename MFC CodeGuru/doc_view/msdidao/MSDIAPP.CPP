// Prosoft MFC extension library.
// Copyright (C) 1993-96 Prosoft/Lanz

#include "stdafx.h"
#include "MSDIApp.h"

/////////////////////////////////////////////////////////////////////////////
// CMDSWinApp

BEGIN_MESSAGE_MAP(CMSDIWinApp, CWinApp)
  //{{AFX_MSG_MAP(CMSDIWinApp)
  // Override file based document commands
  ON_COMMAND(ID_FILE_NEW,  OnFileNew)
  ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
  ON_COMMAND(ID_FILE_PRINT_SETUP, OnFilePrintSetup)
  //}}AFX_MSG_MAP
  // MRU - most recently used file menu
#ifndef WIN32
  ON_COMMAND_EX(ID_FILE_MRU_FILE1, OnOpenRecentFile)
  ON_COMMAND_EX(ID_FILE_MRU_FILE2, OnOpenRecentFile)
  ON_COMMAND_EX(ID_FILE_MRU_FILE3, OnOpenRecentFile)
  ON_COMMAND_EX(ID_FILE_MRU_FILE4, OnOpenRecentFile)
#else
  ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, OnOpenRecentFile)
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSDIWinApp constructor

CMSDIWinApp::CMSDIWinApp()
{
}

CDocument* CMSDIWinApp::OpenDocumentFile(LPCSTR pszPathName)
{
  CDocument* pDoc = NULL;
  POSITION pos = GetFirstDocTemplatePosition();
  ASSERT(pos != NULL);
  // the first doctemplate is the main view of the document
  CDocTemplate* pTemplate = GetNextDocTemplate(pos);
  if (CloseDocument())
  {
    if (pszPathName != NULL)
      // use CString in place of LPCSTR to convert to memory model
      pTemplate->OpenDocumentFile(CString(pszPathName));
    else
      pTemplate->OpenDocumentFile(NULL);
  }
  pos = pTemplate->GetFirstDocPosition();
  if (pos != NULL) pDoc = pTemplate->GetNextDoc(pos);
  return pDoc;
}

void CMSDIWinApp::OnFileNew()
{
  CMSDIWinApp::OpenDocumentFile(NULL);
}

void CMSDIWinApp::OnFileOpen()
{
  // prompt the user (with all document templates)
  CString newName;
  if (!DoPromptFileName(newName, AFX_IDS_OPENFILE,
    OFN_HIDEREADONLY | OFN_CREATEPROMPT, TRUE, NULL)) return;
  CMSDIWinApp::OpenDocumentFile(newName);
}

BOOL CMSDIWinApp::OnOpenRecentFile(UINT nID)
{
  if (CloseDocument())
    return CWinApp::OnOpenRecentFile(nID);
  return TRUE;
}

void CMSDIWinApp::OnFilePrintSetup()
{
  CWinApp::OnFilePrintSetup();
}

/////////////////////////////////////////////////////////////////////////////
// Implementation

#ifndef WIN32
POSITION CMSDIWinApp::GetFirstDocTemplatePosition() const
{
  return m_templateList.GetHeadPosition();
}

CDocTemplate* CMSDIWinApp::GetNextDocTemplate(POSITION& rPosition) const
{
  return (CDocTemplate*)m_templateList.GetNext(rPosition);
}
#endif

BOOL CMSDIWinApp::CloseDocument()
{
  if (CWinApp::SaveAllModified())
  {
    // Find first doc template
    POSITION pos = GetFirstDocTemplatePosition();
    ASSERT(pos != NULL);
    CDocTemplate* pTemplate = GetNextDocTemplate(pos);

    // get the document
    pos = pTemplate->GetFirstDocPosition();
    if (pos != NULL)
    {
      CDocument* pDoc = pTemplate->GetNextDoc(pos);
      // remove Document (only 1 possible)
      if (pDoc) pDoc->OnCloseDocument();
    }
    // I have override this class to make this correction
    ((CMSDITemplate *)pTemplate)->SetUntitleCount(0);

    return TRUE;
  }
  return FALSE;
}

CMSDITemplate* CMSDIWinApp::GetDocTemplate(CRuntimeClass* pViewClass)
{
  CMSDITemplate* pTemplate;
  POSITION pos = GetFirstDocTemplatePosition();
  while (pos != NULL)
  {
    pTemplate = (CMSDITemplate*)GetNextDocTemplate(pos);
    if (pTemplate->GetViewClass() == pViewClass) return pTemplate;
  }
  return NULL;
}

CMSDITemplate* CMSDIWinApp::GetDocTemplate(CView* pView)
{
  CMSDITemplate* pTemplate;
  POSITION pos = GetFirstDocTemplatePosition();
  while (pos != NULL)
  {
    pTemplate = (CMSDITemplate*)GetNextDocTemplate(pos);
    if (pView->IsKindOf(pTemplate->GetViewClass())) return pTemplate;
  }
  return NULL;
}

CDocument* CMSDIWinApp::GetDocument()
{
  CMDIChildWnd* pMDIActive = ((CMDIFrameWnd*)m_pMainWnd)->MDIGetActive();
  if (pMDIActive == NULL) return NULL;
  CDocument* pDoc = pMDIActive->GetActiveDocument();
  return pDoc;
}

CView* CMSDIWinApp::GetView(CRuntimeClass* pViewClass)
{
  CDocument* pDoc = GetDocument();
  if (pDoc == NULL) return NULL;
  CView* pView;
  POSITION pos = pDoc->GetFirstViewPosition();
  while (pos != NULL)
  {
    pView = pDoc->GetNextView(pos);
    if (pView->IsKindOf(pViewClass)) return pView;
  }
  return NULL;
}

CMDIChildWnd* CMSDIWinApp::CreateOrActivateFrame(CRuntimeClass* pViewClass, CDocument* pDoc)
{
  // If a view already exists, then activate the MDI child window containing
  // the view. Otherwise, create a new view.
  if (pDoc != NULL) // only for views with document
  {
    CView* pView = GetView(pViewClass);
    if (pView != NULL)
    {
      pView->GetParentFrame()->ActivateFrame();
      return NULL;
    }
  }

  // find the doc template with this view
  CMSDITemplate* pTemplate = GetDocTemplate(pViewClass);
  if (pTemplate == NULL) return NULL;  // not created
  CMDIChildWnd* pNewFrame =
    (CMDIChildWnd*)(pTemplate->CreateNewFrame(pDoc, NULL));
  if (pNewFrame == NULL) return NULL;  // not created
  pTemplate->InitialUpdateFrame(pNewFrame, pDoc);

  // use the fist string for window title
  CString strTitle;
  pTemplate->GetDocString(strTitle, CDocTemplate::windowTitle);
  pNewFrame->SetWindowText(strTitle);
  return pNewFrame;
}
