// LBTabDemoView.cpp : implementation of the CLBTabDemoView class
//

#include "stdafx.h"
#include "LBTabDemo.h"

#include "LBTabDemoDoc.h"
#include "LBTabDemoView.h"
#include "LBTabDemoPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoView

IMPLEMENT_DYNCREATE(CLBTabDemoView, CView)

BEGIN_MESSAGE_MAP(CLBTabDemoView, CView)
	//{{AFX_MSG_MAP(CLBTabDemoView)
	ON_COMMAND(ID_DEMO_STACK, OnDemoStack)
	ON_COMMAND(ID_DEMO_UNSTACK, OnDemoUnstack)
	ON_COMMAND(ID_COMMON_TAB, OnCommonTab)
	ON_COMMAND(ID_COMMON_TAB_STACK, OnCommonTabStack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoView construction/destruction

CLBTabDemoView::CLBTabDemoView()
{
	// TODO: add construction code here

}

CLBTabDemoView::~CLBTabDemoView()
{
}

BOOL CLBTabDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoView drawing

void CLBTabDemoView::OnDraw(CDC* pDC)
{
	CLBTabDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoView diagnostics

#ifdef _DEBUG
void CLBTabDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CLBTabDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLBTabDemoDoc* CLBTabDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLBTabDemoDoc)));
	return (CLBTabDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoView message handlers

void CLBTabDemoView::OnDemoStack() 
{
CLBTabDemoPropSheet sheet("Stack of tabs with CLBTabCtrl");
CPropertyPage page1(IDD_PROPPAGE1),page2(IDD_PROPPAGE2),page3(IDD_PROPPAGE3),
			  page4(IDD_PROPPAGE4),page5(IDD_PROPPAGE5);

	sheet.AddPage(&page1);
	sheet.AddPage(&page2);
	sheet.AddPage(&page3);
	sheet.AddPage(&page4);
	sheet.AddPage(&page5);

	//To switch off the 'autoraising' feature uncomment the next line 

	//	sheet.m_TabCtrlEx.SetAutoRaising(false);

	sheet.DoModal();
}

void CLBTabDemoView::OnDemoUnstack() 
{
CLBTabDemoPropSheet sheet("Line of Tabs  with CLBTabCtrl");

CPropertyPage page1(IDD_PROPPAGE1),page2(IDD_PROPPAGE2),page3(IDD_PROPPAGE3),
			  page4(IDD_PROPPAGE4),page5(IDD_PROPPAGE5);

	sheet.AddPage(&page1);
	sheet.AddPage(&page2);
	sheet.AddPage(&page3);
	sheet.AddPage(&page4);
	sheet.AddPage(&page5);



	sheet.EnableStackedTabs(FALSE);

	//To switch off the 'autoraising' feature uncomment the next line 

	//sheet.m_TabCtrlEx.SetAutoRaising(false);

	sheet.DoModal();
	
}

void CLBTabDemoView::OnCommonTab() 
{
CPropertySheet sheet("Line of Tabs  with common CTabCtrl");;

CPropertyPage page1(IDD_PROPPAGE1),page2(IDD_PROPPAGE2),page3(IDD_PROPPAGE3),
			  page4(IDD_PROPPAGE4),page5(IDD_PROPPAGE5);

	sheet.AddPage(&page1);
	sheet.AddPage(&page2);
	sheet.AddPage(&page3);
	sheet.AddPage(&page4);
	sheet.AddPage(&page5);

	sheet.EnableStackedTabs(FALSE);
	sheet.DoModal();
}

void CLBTabDemoView::OnCommonTabStack() 
{
CPropertySheet sheet("Stack of Tabs  with common CTabCtrl");;

CPropertyPage page1(IDD_PROPPAGE1),page2(IDD_PROPPAGE2),page3(IDD_PROPPAGE3),
			  page4(IDD_PROPPAGE4),page5(IDD_PROPPAGE5);

	sheet.AddPage(&page1);
	sheet.AddPage(&page2);
	sheet.AddPage(&page3);
	sheet.AddPage(&page4);
	sheet.AddPage(&page5);

	sheet.DoModal();
	
}
