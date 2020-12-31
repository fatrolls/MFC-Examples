// BaseDataPk.cpp : implementation file
//

#include "stdafx.h"
#include "BaseDataPk.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseDataPk

CBaseDataPk::CBaseDataPk()
{
	 m_curData = COleDateTime::GetCurrentTime();
	 m_lowData.SetStatus(COleDateTime::null);
	 m_highData.SetStatus(COleDateTime::null);
     m_pDataBuddy = NULL;

}
 void CBaseDataPk::SetRange(COleDateTime* dt1,COleDateTime* dt2,BOOL nullvalue,BOOL updatecurvalue)
{
  if (dt1->GetStatus() != COleDateTime::null)
	  m_lowData = *dt1;
  m_highData = *dt2;
	if (nullvalue)
	m_curData.SetStatus(COleDateTime::null);
  else 
	{
	  if (updatecurvalue)
	  m_curData = *dt1;
	}
  if (!nullvalue)
  if (!IsNullDate())
  if (m_curData < m_lowData)
	  m_curData = m_lowData;
  ShowDataControl();
  if (m_pDataBuddy)
	  m_pDataBuddy->SetRange(m_curData.GetStatus() != COleDateTime::null ? &m_curData : &m_lowData ,dt2,nullvalue,updatecurvalue);

 }
 void CBaseDataPk::SetRange(int dayback,int dayafter,BOOL nullvalue,BOOL updatecurvalue)
{
		COleDateTime t1 = COleDateTime::GetCurrentTime();
		COleDateTime t2 = t1;
      	COleDateTimeSpan s1(-dayback,0,0,0);
     	COleDateTimeSpan s2(dayafter,0,0,0);
   t1 += s1;
   t2 += s2;
 SetRange(&t1,&t2,nullvalue,updatecurvalue);
}

 
CBaseDataPk::~CBaseDataPk()
{

}
void CBaseDataPk::ShowDataControl()
{
 if (m_pk.m_hWnd == NULL)
	 return ;
 	  SYSTEMTIME s[3];
	  memset(s,0,sizeof(s));
	 DWORD d =   DateTime_GetSystemtime(m_pk.m_hWnd, &s[2]);
BOOL 	 b = DateTime_SetSystemtime(m_pk.m_hWnd, GDT_NONE,&s[2]);
	 
	 if (m_curData.GetStatus() == COleDateTime::null)
		 d = GDT_NONE;
	 else
	{
 	 s[2].wYear = m_curData.GetYear();
	 s[2].wMonth = m_curData.GetMonth();
	 s[2].wDay  = m_curData.GetDay();
	 d = GDT_VALID;
	}
//	  DateTime_SetRange(m_pk.m_hWnd,GDTR_MIN,&s[2]);
//	  DateTime_SetRange(m_pk.m_hWnd,GDTR_MAX,&s[1]);
//  	 DateTime_SetSystemtime(m_pk.m_hWnd,d,&s[2]);

	  
DWORD range = 0;
  if (m_lowData.GetStatus() != COleDateTime::null)
	{
	 s[0].wYear = m_lowData.GetYear();
	 s[0].wMonth = m_lowData.GetMonth();
	 s[0].wDay  = m_lowData.GetDay();
	 range |= GDTR_MIN;
	}
	 if (m_highData.GetStatus() != COleDateTime::null)
	{
	 s[1].wYear = m_highData.GetYear();
	 s[1].wMonth = m_highData.GetMonth();
	 s[1].wDay  = m_highData.GetDay();
	 range |= GDTR_MAX;
	}
	 if (range)
     b = DateTime_SetRange(m_pk.m_hWnd,range,s);
	 b = DateTime_SetSystemtime(m_pk.m_hWnd,d,&s[2]);
  TRACE1("show data control %s\n",(const char*)m_curData.Format("%d/%m/%Y"));


} 

 BOOL  CBaseDataPk::SetData(UINT idc,CWnd* parent,BOOL empty,BOOL updown)
{
	  	if (!SubclassDlgItem(idc,parent))
		return FALSE;
	static int giafatto = 0;
	if (!giafatto)
	{
		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_DATE_CLASSES;
		::InitCommonControlsEx(&icex);
		giafatto++;
	}
CRect r;
  GetClientRect(r);
DWORD dwstyle = WS_CHILD|WS_VISIBLE;
if (empty)
dwstyle |= DTS_SHOWNONE;
if (updown)
dwstyle |= DTS_UPDOWN;

 m_pk.Create(DATETIMEPICK_CLASS,"",dwstyle,r,this,0);
 if (m_pk.m_hWnd == NULL)
	 return FALSE;
ShowDataControl(); 
if (m_pDataBuddy)
m_pDataBuddy->SetRange(&m_curData,&m_highData,m_curData == COleDateTime::null);
return TRUE;
 
}
BOOL CBaseDataPk::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
		NMHDR* pnmh = (LPNMHDR) lParam;
if (DTN_DATETIMECHANGE == pnmh->code)
{
		LPNMDATETIMECHANGE dtmh = (LPNMDATETIMECHANGE) pnmh;
   if (dtmh->dwFlags == GDT_VALID)
	m_curData.SetDate((int)dtmh->st.wYear,(int)dtmh->st.wMonth,(int)dtmh->st.wDay);
	else
	 m_curData.SetStatus(COleDateTime::null);
 		OnDateChanged(dtmh->dwFlags == GDT_VALID );
 if (m_pDataBuddy)
	{ 
	  COleDateTime* p = m_pDataBuddy->GetCurDate();
	  if (dtmh->dwFlags == GDT_VALID)
		  if (p->GetStatus() == COleDateTime::null)
          *p = m_curData;
	  m_pDataBuddy->SetRange(&m_curData,&m_highData,dtmh->dwFlags != GDT_VALID,FALSE); //p->GetStatus() == COleDateTime::null);
	}
  
}
else
 	TRACE1("NOTIFY CODE %d\n", pnmh->code);
	*pResult = GetParent()->SendMessage(WM_NOTIFY, wParam, lParam);

	 	return TRUE;
}
void CBaseDataPk::OnDateChanged(BOOL valid) 
{
//	SYSTEMTIME s;
 // DateTime_GetSystemtime(m_pk.m_hWnd,&s);
 if (valid)
  TRACE1("ON DATA CHANGED %s\n",(const char*)m_curData.Format("%d/%m/%Y"));
 else
	 TRACE0("NULL DATA\n");
}

BEGIN_MESSAGE_MAP(CBaseDataPk, CStatic)
	//{{AFX_MSG_MAP(CBaseDataPk)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBaseDataPk message handlers


void CBaseDataPk::OnDestroy() 
{
	CStatic::OnDestroy();
	
	// TODO: Add your message handler code here
  if (!IsNullDate())
	  return;
 if (!m_pDataBuddy)
return;
 if (!m_pDataBuddy->IsNullDate())
  m_curData = *(m_pDataBuddy->GetCurDate());
	
}
