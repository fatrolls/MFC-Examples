// ex24dView.cpp : implementation of the CEx24dView class
//

#include "stdafx.h"
#include "ex24d.h"

#include "ex24dDoc.h"
#include "ex24dView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx24dView

IMPLEMENT_DYNCREATE(CEx24dView, CView)

BEGIN_MESSAGE_MAP(CEx24dView, CView)
   //{{AFX_MSG_MAP(CEx24dView)
   ON_COMMAND(ID_BANKOLE_LOAD, OnBankoleLoad)
   ON_UPDATE_COMMAND_UI(ID_BANKOLE_LOAD, OnUpdateBankoleLoad)
   ON_COMMAND(ID_BANKOLE_TEST, OnBankoleTest)
   ON_UPDATE_COMMAND_UI(ID_BANKOLE_TEST, OnUpdateBankoleTest)
   ON_COMMAND(ID_BANKOLE_UNLOAD, OnBankoleUnload)
   ON_UPDATE_COMMAND_UI(ID_BANKOLE_UNLOAD, OnUpdateBankoleUnload)
   ON_COMMAND(ID_CLOCKOLE_CREATEALARM, OnClockoleCreatealarm)
   ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_CREATEALARM, OnUpdateClockoleCreatealarm)
   ON_COMMAND(ID_CLOCKOLE_LOAD, OnClockoleLoad)
   ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_LOAD, OnUpdateClockoleLoad)
   ON_COMMAND(ID_CLOCKOLE_REFRESHTIME, OnClockoleRefreshtime)
   ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_REFRESHTIME, OnUpdateClockoleRefreshtime)
   ON_COMMAND(ID_CLOCKOLE_UNLOAD, OnClockoleUnload)
   ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_UNLOAD, OnUpdateClockoleUnload)
   ON_COMMAND(ID_DLLOLE_GETDATA, OnDlloleGetdata)
   ON_UPDATE_COMMAND_UI(ID_DLLOLE_GETDATA, OnUpdateDlloleGetdata)
   ON_COMMAND(ID_DLLOLE_LOAD, OnDlloleLoad)
   ON_UPDATE_COMMAND_UI(ID_DLLOLE_LOAD, OnUpdateDlloleLoad)
   ON_COMMAND(ID_DLLOLE_UNLOAD, OnDlloleUnload)
   ON_UPDATE_COMMAND_UI(ID_DLLOLE_UNLOAD, OnUpdateDlloleUnload)
   ON_COMMAND(ID_EXCELOLE_EXECUTE, OnExceloleExecute)
   ON_UPDATE_COMMAND_UI(ID_EXCELOLE_EXECUTE, OnUpdateExceloleExecute)
   ON_COMMAND(ID_EXCELOLE_LOAD, OnExceloleLoad)
   ON_UPDATE_COMMAND_UI(ID_EXCELOLE_LOAD, OnUpdateExceloleLoad)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx24dView construction/destruction

CEx24dView::CEx24dView()
{
   // TODO: add construction code here

}

CEx24dView::~CEx24dView()
{
}

BOOL CEx24dView::PreCreateWindow(CREATESTRUCT& cs)
{
   // TODO: Modify the Window class or styles here by modifying
   //  the CREATESTRUCT cs

   return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx24dView drawing

void CEx24dView::OnDraw(CDC* pDC)
{
    CEx24dDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
	pDC->TextOut(0, 0, "Uses COleDispatchDriver.");
	pDC->TextOut(0, 25, "Run this program from the debugger to see test output.");
	pDC->TextOut(0, 50, "Components must be built and registered prior to loading.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx24dView diagnostics

#ifdef _DEBUG
void CEx24dView::AssertValid() const
{
   CView::AssertValid();
}

void CEx24dView::Dump(CDumpContext& dc) const
{
   CView::Dump(dc);
}

CEx24dDoc* CEx24dView::GetDocument() // non-debug version is inline
{
   ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx24dDoc)));
   return (CEx24dDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx24dView message handlers

void CEx24dView::OnBankoleLoad() 
{
   if(!m_bank.CreateDispatch("Ex24a.Bank")) {
		AfxMessageBox("Ex24a.Bank component not found");
		return;
   }
/*  works for an EXE component only if the interface is registered
   // {923011E3-CBEB-11CE-B337-88EA36DE9E4E}
   static const IID IID_IBank =
   { 0x923011e3, 0xcbeb, 0x11ce, { 0xb3, 0x37, 0x88, 0xea, 0x36, 0xde, 0x9e, 0x4e } };
   LPDISPATCH p;
   HRESULT hr = m_bank.m_lpDispatch->QueryInterface(IID_IBank, (void**) &p);
   TRACE("OnBankoleLoad -- QueryInterface result = %x\n", hr);
*/
}

void CEx24dView::OnUpdateBankoleLoad(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_bank.m_lpDispatch == NULL);
}

void CEx24dView::OnBankoleTest() 
{
   m_bank.Deposit(20.0);
   m_bank.Withdrawal(15.0);
   TRACE("new balance = %f\n", m_bank.GetBalance());
}

void CEx24dView::OnUpdateBankoleTest(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_bank.m_lpDispatch != NULL);
}

void CEx24dView::OnBankoleUnload() 
{
   m_bank.ReleaseDispatch();
}

void CEx24dView::OnUpdateBankoleUnload(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_bank.m_lpDispatch != NULL);
}

void CEx24dView::OnClockoleCreatealarm() 
{
	CAlarmDialog dlg;
	if (dlg.DoModal() == IDOK) {
		COleDateTime dt(1995, 12, 23, dlg.m_nHours, dlg.m_nMinutes, 
			dlg.m_nSeconds);
		LPDISPATCH pAlarm = m_clock.CreateAlarm(dt);
		m_alarm.AttachDispatch(pAlarm);  // releases prior object!
		m_clock.RefreshWin();
	}
}

void CEx24dView::OnUpdateClockoleCreatealarm(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_clock.m_lpDispatch != NULL);
}

void CEx24dView::OnClockoleLoad() 
{
   if(!m_clock.CreateDispatch("Ex24c.Document")) {
		AfxMessageBox("Ex24c.Document component not found");
		return;
   }
   m_clock.SetFigure(0, COleVariant("XII"));
   m_clock.SetFigure(1, COleVariant("III"));
   m_clock.SetFigure(2, COleVariant("VI"));
   m_clock.SetFigure(3, COleVariant("IX"));
   OnClockoleRefreshtime();
   m_clock.ShowWin();
}

void CEx24dView::OnUpdateClockoleLoad(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_clock.m_lpDispatch == NULL);
}

void CEx24dView::OnClockoleRefreshtime() 
{
   COleDateTime now = COleDateTime::GetCurrentTime();
   m_clock.SetTime(now);
   m_clock.RefreshWin();
}

void CEx24dView::OnUpdateClockoleRefreshtime(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_clock.m_lpDispatch != NULL);
}

void CEx24dView::OnClockoleUnload() 
{
   m_clock.ReleaseDispatch();
}

void CEx24dView::OnUpdateClockoleUnload(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_clock.m_lpDispatch != NULL);
}

void CEx24dView::OnDlloleGetdata() 
{
   m_auto.DisplayDialog();
   COleVariant vaData = m_auto.GetTextData();
   ASSERT(vaData.vt == VT_BSTR);
   CString strTextData = vaData.bstrVal;
   long lData = m_auto.GetLongData();
   TRACE("CEx24dView::OnDlloleGetdata -- long = %ld, text = %s\n",
         lData, strTextData);
}

void CEx24dView::OnUpdateDlloleGetdata(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_auto.m_lpDispatch != NULL);
}

void CEx24dView::OnDlloleLoad() 
{
   if(!m_auto.CreateDispatch("Ex24b.Auto")) {
		AfxMessageBox("Ex24b.Auto component not found");
		return;
   }
   m_auto.SetTextData(COleVariant("test"));  // testing
   m_auto.SetLongData(79);  // testing
	// verify dispatch interface
    // {A9515AD7-5B85-11D0-848F-00400526305B}
	static const IID IID_IEx24bAuto =
	{ 0xa9515ad7, 0x5b85, 0x11d0, { 0x84, 0x8f, 0x0, 0x40, 0x5, 0x26, 0x30, 0x5b } };
	LPDISPATCH p;
	HRESULT hr = m_auto.m_lpDispatch->QueryInterface(IID_IEx24bAuto, 
		(void**) &p);
	TRACE("OnDlloleLoad -- QueryInterface result = %x\n", hr);
	p->Release();
}

void CEx24dView::OnUpdateDlloleLoad(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_auto.m_lpDispatch == NULL);
}

void CEx24dView::OnDlloleUnload() 
{
   m_auto.ReleaseDispatch();
}


void CEx24dView::OnUpdateDlloleUnload(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_auto.m_lpDispatch != NULL);
}

void CEx24dView::OnExceloleExecute() 
{
   LPDISPATCH pRange, pWorkbooks;
    
   CWnd* pWnd = CWnd::FindWindow("XLMAIN", NULL);
   if (pWnd != NULL) {
     TRACE("Excel window found\n");
     pWnd->ShowWindow(SW_SHOWNORMAL);
     pWnd->UpdateWindow();
     pWnd->BringWindowToTop();
   }

   m_app.SetSheetsInNewWorkbook(1);
   
   VERIFY(pWorkbooks = m_app.GetWorkbooks());
   m_workbooks.AttachDispatch(pWorkbooks);

   LPDISPATCH pWorkbook = NULL;
   if (m_workbooks.GetCount() == 0) {
      // Add returns a Workbook pointer, but we
      //  don't have a Workbook class
      pWorkbook = m_workbooks.Add(); // Save the pointer for
                                     //  later release
   }
   LPDISPATCH pWorksheets = m_app.GetWorksheets();
   ASSERT(pWorksheets != NULL);
   m_worksheets.AttachDispatch(pWorksheets);
   LPDISPATCH pWorksheet = m_worksheets.GetItem(COleVariant((short) 1));

   m_worksheet.AttachDispatch(pWorksheet);
   m_worksheet.Select();

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A1")));
   m_range[0].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A2")));
   m_range[1].AttachDispatch(pRange);
   
   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A3")));
   m_range[2].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A3"), 
	   COleVariant("C5")));
   m_range[3].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A6")));
   m_range[4].AttachDispatch(pRange);
   
   m_range[4].SetValue(COleVariant(COleDateTime(1994, 4, 24, 15, 47, 8)));
   // retrieve the stored date and print it as a string
   COleVariant vaTimeDate = m_range[4].GetValue();
   TRACE("returned date type = %d\n", vaTimeDate.vt);
   COleVariant vaTemp;
   vaTemp.ChangeType(VT_BSTR, &vaTimeDate);
   CString str = vaTemp.bstrVal;
   TRACE("date = %s\n", (const char*) str);

   m_range[0].SetValue(COleVariant("test string"));
   
   COleVariant vaResult0 = m_range[0].GetValue();
   if (vaResult0.vt == VT_BSTR) {
     CString str = vaResult0.bstrVal;
     TRACE("vaResult0 = %s\n", (const char*) str);
   }

   m_range[1].SetValue(COleVariant(3.14159));
   
   COleVariant vaResult1 = m_range[1].GetValue();
   if (vaResult1.vt == VT_R8) {
     TRACE("vaResult1 = %f\n", vaResult1.dblVal);
   }
   
   m_range[2].SetFormula(COleVariant("=$A2*2.0"));
   
   COleVariant vaResult2 = m_range[2].GetValue();
   if (vaResult2.vt == VT_R8) {
     TRACE("vaResult2 = %f\n", vaResult2.dblVal);
   }

   COleVariant vaResult2a = m_range[2].GetFormula();
   if (vaResult2a.vt == VT_BSTR) {
     CString str = vaResult2a.bstrVal;
     TRACE("vaResult2a = %s\n", (const char*) str);
   }
   
   m_range[3].FillRight();
   m_range[3].FillDown();
   
// cleanup  
    if (pWorkbook != NULL) {
	    pWorkbook->Release();
   }
}

void CEx24dView::OnUpdateExceloleExecute(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_app.m_lpDispatch != NULL);
}

void CEx24dView::OnExceloleLoad() 
{   // if Excel is already running, attach to it, otherwise start it
   LPDISPATCH pDisp;
   LPUNKNOWN pUnk;
   CLSID clsid;
   TRACE("Entering CEx24dView::OnExcelLoad\n");
   BeginWaitCursor();
   ::CLSIDFromProgID(L"Excel.Application.8", &clsid); // from registry
   if(::GetActiveObject(clsid, NULL, &pUnk) == S_OK) {
      VERIFY(pUnk->QueryInterface(IID_IDispatch,
            (void**) &pDisp) == S_OK);
      m_app.AttachDispatch(pDisp);
      pUnk->Release();
      TRACE(" attach complete\n");
  } 
   else {
	   if(!m_app.CreateDispatch("Excel.Application.8")) {
			AfxMessageBox("Excel 97 program not found");
	   }
       TRACE(" create complete\n");
   }
   EndWaitCursor();
}

void CEx24dView::OnUpdateExceloleLoad(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_app.m_lpDispatch == NULL);
}
