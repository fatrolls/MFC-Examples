// ex28bView.cpp : implementation of the CEx28bView class
//

#include "stdafx.h"
#include "ex28b.h"

#include "ex28bSet.h"
#include "ex28bDoc.h"
#include "ex28bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28bView

IMPLEMENT_DYNCREATE(CEx28bView, CRecordView)

BEGIN_MESSAGE_MAP(CEx28bView, CRecordView)
	//{{AFX_MSG_MAP(CEx28bView)
	ON_COMMAND(ID_RECORD_ADD, OnRecordAdd)
	ON_COMMAND(ID_RECORD_CLEARFIELDS, OnRecordClearfields)
	ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
	ON_COMMAND(ID_RECORD_UPDATE, OnRecordUpdate)
	ON_UPDATE_COMMAND_UI(ID_RECORD_UPDATE, OnUpdateRecordUpdate)
	ON_UPDATE_COMMAND_UI(ID_RECORD_DELETE, OnUpdateRecordDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx28bView construction/destruction

CEx28bView::CEx28bView()
	: CRecordView(CEx28bView::IDD)
{
	//{{AFX_DATA_INIT(CEx28bView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CEx28bView::~CEx28bView()
{
}

void CEx28bView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx28bView)
	DDX_FieldText(pDX, IDC_ID, m_pSet->m_InstructorID, m_pSet);
	DDX_FieldText(pDX, IDC_NAME, m_pSet->m_Name, m_pSet);
	DDX_FieldText(pDX, IDC_ROOM, m_pSet->m_RoomNo, m_pSet);
	//}}AFX_DATA_MAP
}

BOOL CEx28bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CEx28bView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_ex28bSet;
	CRecordView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CEx28bView diagnostics

#ifdef _DEBUG
void CEx28bView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CEx28bView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CEx28bDoc* CEx28bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx28bDoc)));
	return (CEx28bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28bView database support
CRecordset* CEx28bView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CEx28bView message handlers

BOOL CEx28bView::OnMove(UINT nIDMoveCommand) 
{
switch (nIDMoveCommand)
    {
      case ID_RECORD_PREV:
           m_pSet->MovePrev();
           if (!m_pSet->IsBOF())
             break;

      case ID_RECORD_FIRST:
           m_pSet->MoveFirst();
           break;

      case ID_RECORD_NEXT:
           m_pSet->MoveNext();
           if (!m_pSet->IsEOF())
             break;
           if (!m_pSet->CanScroll()) {
             // Clear out screen since we're sitting on EOF
             m_pSet->SetFieldNull(NULL);
             break;
           }

      case ID_RECORD_LAST:
           m_pSet->MoveLast();
           break;

      default:
           // unexpected case value
           ASSERT(FALSE);
    }

    // show results of move operation
    UpdateData(FALSE);
    return TRUE;

}

void CEx28bView::OnRecordAdd()
{

	m_pSet->AddNew();
	UpdateData(TRUE);
	if (m_pSet->CanUpdate())  {
	  m_pSet->Update();
	}
	if (!m_pSet->IsEOF())
	{
		m_pSet->MoveLast();
	}
//	m_pSet->Requery(); // for sorted sets
	UpdateData(FALSE);
    
}

void CEx28bView::OnRecordClearfields() 
{
    m_pSet->SetFieldNull(NULL);
    UpdateData(FALSE);
}

void CEx28bView::OnRecordDelete() 
{
	CRecordsetStatus status;
    try {
        m_pSet->Delete();
    }
    catch(CDBException* e) {
        AfxMessageBox(e->m_strError);
        e->Delete();
        m_pSet->MoveFirst(); // lost our place!
        UpdateData(FALSE);
        return;
    }
    m_pSet->GetStatus(status);
	if (status.m_lCurrentRecord == 0) {
		// We deleted last of 2 records
		m_pSet->MoveFirst();
	}
	else {
		m_pSet->MoveNext();
	}
    UpdateData(FALSE);
}

void CEx28bView::OnUpdateRecordDelete(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(!m_pSet->IsEOF());
}

void CEx28bView::OnRecordUpdate() 
{
    m_pSet->Edit();
    UpdateData(TRUE);
    if (m_pSet->CanUpdate()){
      m_pSet->Update();
    }
// should requery if key field changed
}

void CEx28bView::OnUpdateRecordUpdate(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(!m_pSet->IsEOF());
}
