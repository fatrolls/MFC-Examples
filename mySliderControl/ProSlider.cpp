 
//CProSliderCtrl .cpp

#include "stdafx.h"
//#include "ProSlider.h"
#include "ProSliderCtrl.h"

IMPLEMENT_DYNAMIC(CProSliderCtrl, CSliderCtrl)
CProSliderCtrl::CProSliderCtrl()
: m_ProBkColor(RGB(51,51,51)),
m_ThClOver(RGB(255,102,0)),
m_ThClOut(RGB(0,204,0)),
m_ThClPre(RGB(153,102,204)),
m_ProgressBarColor(RGB(102,102,204)),
m_ThClDef(m_ThClOut),
m_ProgressStep(10),
m_bBorders(TRUE)
{
 m_bFreezed = FALSE;
 m_bBlink = FALSE;
}

CProSliderCtrl::~CProSliderCtrl()
{

}


BEGIN_MESSAGE_MAP(CProSliderCtrl, CSliderCtrl)
 ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw)
 ON_WM_MOUSEMOVE()
 ON_WM_TIMER()
 ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

 

// CProSliderCtrl message handlers

// Custom control drawing operations
void CProSliderCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
 LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
 switch(pNMCD->dwDrawStage)
 {
 case CDDS_POSTERASE: // After the erasing cycle is complete. 
  *pResult = CDRF_SKIPDEFAULT;
  break;
 case CDDS_POSTPAINT: // After the painting cycle is complete. 
  *pResult = CDRF_DODEFAULT;
  break;
 case CDDS_PREERASE:  // Before the erasing cycle begins.
  *pResult = CDRF_SKIPDEFAULT;
  break;
 case CDDS_PREPAINT:  // Before the painting cycle begins. 
  *pResult = CDRF_NOTIFYITEMDRAW;
  break;
 case CDDS_ITEMPREPAINT: // Before an item is drawn.
  switch(pNMCD->dwItemSpec)
  {
  // Identifies the channel that the slider control's thumb marker slides along. 
  case TBCD_CHANNEL: 
   if(m_bBorders)DrawSliderBorder(pNMCD);
   DrawSliderChannel(pNMCD);
   *pResult = CDRF_SKIPDEFAULT;
   break;
  // Identifies the increment tick marks that appear along the edge of the slider control. 
  case TBCD_TICS: 
   *pResult = CDRF_DODEFAULT;
   break;
  // Identifies the slider control's thumb marker. This is the portion of 
  // the control that the user moves.
  case TBCD_THUMB:
   if(DrawSliderThumb(pNMCD)==S_OK)
    *pResult = CDRF_SKIPDEFAULT;
   else
    *pResult = CDRF_DODEFAULT;
   break;
  default:
   *pResult = CDRF_DODEFAULT;
   break;
  }
  break;
 default:
  *pResult = CDRF_DODEFAULT;
  break;
 }
}

// Gets the lower and upper limits of the range of the progress bar control.
void CProSliderCtrl::_GetRange(int& nLower, int& nUpper)
{
 nLower = m_ProRange.iLow;
 nUpper = m_ProRange.iHigh;
 return;
}
// Sets the minimum and maximum ranges for a progress bar
// control and redraws the bar to reflect the new ranges.
void CProSliderCtrl::_SetRange(short nLower, short nUpper)
{
 m_ProRange.iLow = nLower;
 m_ProRange.iHigh = nUpper;
 return;
}
//Sets the minimum and maximum ranges for a progress bar control and 
// redraws the bar to reflect the new ranges.
void CProSliderCtrl::_SetRange32(int nLower, int nUpper)
{
 m_ProRange.iLow = nLower;
 m_ProRange.iHigh = nUpper;
 return;
}
// Sets the background color for the progress bar. (border color)
COLORREF CProSliderCtrl::_SetBkColor(COLORREF clrNew)
{
    COLORREF m_tmp = m_ProBkColor;
 m_ProBkColor = clrNew;
 int min,max;
 GetRange(min,max);
 CSliderCtrl::SetRange(min,max,TRUE);
 return m_tmp;
}
// Sets the thumb color for the slider control. 
COLORREF CProSliderCtrl::_SetThumbColor(COLORREF clrNew)
{
    COLORREF m_tmp = m_ThClDef;
 m_ThClDef = clrNew;
 int min,max;
 GetRange(min,max);
 CSliderCtrl::SetRange(min,max,TRUE);
 return m_tmp;
}

// Sets the progress bar color.
COLORREF CProSliderCtrl::_SetChColor(COLORREF clrNew)
{
    COLORREF m_tmp = m_ProgressBarColor;
 m_ProgressBarColor = clrNew;
 int min,max;
 GetRange(min,max);
 CSliderCtrl::SetRange(min,max,TRUE);
 return m_tmp;
}

// Gets the current position of the progress bar.
int CProSliderCtrl::_GetPos(void)
{
 return (m_ProgressPos);
}
// Advances the current position of a progress bar control by a specified 
// increment and redraws the bar to reflect the new position.
int CProSliderCtrl::_OffsetPos(int nPos)
{
 int curr = m_ProgressPos;
 m_ProgressPos+= nPos;
 int min,max;
 GetRange(min,max);
 CSliderCtrl::SetRange(min,max,TRUE);
 return(curr);
}
// Sets the current position for a progress bar control and redraws the bar
// to reflect the new position.
int CProSliderCtrl::_SetPos(int nPos)
{
    int curr = m_ProgressPos;
 m_ProgressPos = nPos;
 int min,max;
 GetRange(min,max);
 CSliderCtrl::SetRange(min,max,TRUE);
 return(curr);
}
// Specifies the step increment for a progress bar control.
int CProSliderCtrl::_SetStep(int nStep)
{
 int curr = m_ProgressStep;
 m_ProgressStep = nStep;
 return curr;
}

// Advances the current position for a progress bar control by 
// the step increment and redraws the bar to reflect the new position.
int CProSliderCtrl::_StepIt(void)
{ 
 int curr = m_ProgressPos;
 int min,max;
 GetRange(min,max);
 m_ProgressPos+m_ProgressStep>=max?m_ProgressPos+=m_ProgressStep-max:m_ProgressPos+= m_ProgressStep;
 CSliderCtrl::SetRange(min,max,TRUE);
 return(curr);
}

// Draws the slider window border, internal use only, cannot be accessible
HRESULT CProSliderCtrl::DrawSliderBorder(LPNMCUSTOMDRAW pNMCD)
{
 RECT border;
 GetClientRect(&border);
 CDC *pDC = CDC::FromHandle(pNMCD->hdc);
 RecursiveChannel(pDC,border,m_ProBkColor,TRUE,FALSE,5);
 return S_OK;
}

// Draws the Progress bar, internal use only, cannot be accessible
HRESULT CProSliderCtrl::DrawSliderChannel(LPNMCUSTOMDRAW pNMCD)
{
 CRect crect;
 double rr;
 CDC *pDC = CDC::FromHandle(pNMCD->hdc);
 crect.CopyRect(&pNMCD->rc);
 BOOL Vert=FALSE;
 if(crect.Height()>crect.Width()) Vert=TRUE;
 switch(Vert)
 {
 case TRUE:
  crect.InflateRect(5, 0, 5, 0);
  DrawEdge(pNMCD->hdc, &crect, EDGE_SUNKEN, BF_RECT | BF_ADJUST);
  crect.InflateRect(1, 0, 1, 0);
  if(m_ProRange.iHigh!=0)
  {
   rr= (crect.Height()*m_ProgressPos)/m_ProRange.iHigh;
   crect.bottom =(LONG)rr+9;
  } else crect.bottom=9;
  crect.top = 9;
  RecursiveChannel(pDC,crect,m_ProgressBarColor,TRUE,TRUE);
  break;
 case FALSE:
  crect.InflateRect(0, 5, 0, 5);
  DrawEdge(pNMCD->hdc, &crect, EDGE_SUNKEN, BF_RECT | BF_ADJUST);
  crect.InflateRect(0, 1, 0, 1);
        if(m_ProRange.iHigh!=0)
  {
   rr= (crect.Width()*m_ProgressPos)/m_ProRange.iHigh;
   crect.right =(LONG)rr+9;
  } else crect.right=9;
  crect.left = 9;
  RecursiveChannel(pDC,crect,m_ProgressBarColor,TRUE);
  break;
 }
 return S_OK;
}

// Recursive channel drawer used to generate pastel colors
__inline void CProSliderCtrl::RecursiveChannel(CDC *pDC,
              CRect rc, COLORREF nClr,
              BOOL First/*=FALSE*/,
              BOOL Vertical/*=FALSE*/,
              BYTE StepSize/*=20*/)
{
 CBrush Brush;
 Brush.CreateSolidBrush(nClr);
 HGDIOBJ old = pDC->SelectObject(Brush);
 CPen Pen;
 Pen.CreatePen(PS_SOLID,1,nClr);
 CPen* pOldPen = pDC->SelectObject(&Pen); 
 pDC->RoundRect(rc,CPoint(2,2));
 First?rc.DeflateRect(1,1):Vertical?rc.DeflateRect(1,0):rc.DeflateRect(0,1);
 BYTE r,g,b;
 r = GetRValue(nClr);
 g = GetGValue(nClr);
 b = GetBValue(nClr);
 StepSize+r>=255?r=255:r=StepSize+r; // r+=Stepsize gives warning C4244
 StepSize+g>=255?g=255:g=StepSize+g;
 StepSize+b>=255?b=255:b=StepSize+b;
 if(!rc.IsRectEmpty()) RecursiveRect(pDC,rc,RGB(r,g,b));
 pDC->SelectObject(old);
 pDC->SelectObject(pOldPen);
 ::DeleteObject(Brush);
 ::DeleteObject(Pen);
}

// Recursive slider thumb drawer used to generate pastel colors
HRESULT CProSliderCtrl::DrawSliderThumb(LPNMCUSTOMDRAW pNMCD)
{
 if(pNMCD->uItemState & CDIS_SELECTED)
  this->m_ThClDef = this->m_ThClPre;
 Draw(pNMCD);
 return S_OK;
}

// internal use only
__inline void CProSliderCtrl::Draw(LPNMCUSTOMDRAW pNMCD)
{
 CDC *pDC = CDC::FromHandle(pNMCD->hdc);
 RecursiveRect(pDC,&pNMCD->rc,m_ThClDef,TRUE);
 return;
}

// Used by the Draw function.
__inline void CProSliderCtrl::RecursiveRect(CDC *pDC, CRect rc, COLORREF nClr, BOOL First/*=FALSE*/)
{
 CBrush Brush;
 Brush.CreateSolidBrush(nClr);
 HGDIOBJ old = pDC->SelectObject(Brush);
 CPen Pen;
 Pen.CreatePen(PS_SOLID,1,nClr);
 CPen* pOldPen = pDC->SelectObject(&Pen); 
 pDC->RoundRect(rc,CPoint(2,2));
 First?rc.DeflateRect(1,1):this->GetStyle()&TBS_VERT?rc.DeflateRect(1,0):rc.DeflateRect(0,1);
 BYTE r,g,b;
 r = GetRValue(nClr);
 g = GetGValue(nClr);
 b = GetBValue(nClr);
 if(r<=245) r+=10;
 if(g<=245) g+=10;
 if(b<=245) b+=10;
 if(!rc.IsRectEmpty()) RecursiveRect(pDC,rc,RGB(r,g,b));
 pDC->SelectObject(old);
 pDC->SelectObject(pOldPen);
 ::DeleteObject(Brush);
 ::DeleteObject(Pen);
}

// Catches the mouse movements and sets the Thumb colors
void CProSliderCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
 CRect tRect;
 GetThumbRect(&tRect);
 tRect.InflateRect(2,-2,2,-2);
 if(tRect.PtInRect(point))
 {
  SetThumbColor(m_ThClOver);
 }else 
 {
  SetThumbColor(m_ThClOut);
 }
 CSliderCtrl::OnMouseMove(nFlags, point);
}

// Sets the thumb color and redraws the thumb
void CProSliderCtrl::SetThumbColor(COLORREF nClr)
{
 this->m_ThClDef = nClr;
 int min,max;
 GetRange(min,max);
 CSliderCtrl::SetRange(min,max,TRUE);
}

// Enables/Disables window borders
HRESULT CProSliderCtrl::_EnableBorders(BOOL bEnable/*=TRUE*/)
{
 m_bBorders = bEnable;
 int min,max;
 GetRange(min,max);
 CSliderCtrl::SetRange(min,max,TRUE);
 return S_OK;
}

// Test if the borders are enabled or not
BOOL CProSliderCtrl::_IsEnabled(void)
{
 return m_bBorders;
}

// Used to freeze the slider bar, i.e. not controlable when by the user
// and thumb and the border starts blinking
BOOL CProSliderCtrl::Freeze(void)
{ 
 BOOL Prev= m_bFreezed;
 if(!Prev) // Freeze now
 {
  tmp1 = m_ThClDef;
  tmp2 = m_ProBkColor;
  SetTimer(WM_FREEZE,1000,NULL);
  m_bFreezed = TRUE;

 }else
 {
  KillTimer(WM_FREEZE);
  m_bFreezed = FALSE;
  m_ThClDef = tmp1;
  m_ProBkColor = tmp2;
  int min,max;
  GetRange(min,max);
  CSliderCtrl::SetRange(min,max,TRUE);
 }
 return Prev;
}

// used for freezing operation
void CProSliderCtrl::OnTimer(UINT nIDEvent)
{
 int min,max;
 if(m_bBlink)
  {
   m_ThClDef = RGB(102,102,204);
   m_bBlink = FALSE;
   m_ProBkColor = RGB(102,102,204);
   GetRange(min,max);
   CSliderCtrl::SetRange(min,max,TRUE);
   
  } else 
  {
   m_ThClDef = RGB(204,204,204);
   m_ProBkColor = RGB(204,204,204);
   GetRange(min,max);
   CSliderCtrl::SetRange(min,max,TRUE);   
   m_bBlink = TRUE;   
  }
 CSliderCtrl::OnTimer(nIDEvent);
}


void CProSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
 if(m_bFreezed) return; else
 CSliderCtrl::OnLButtonDown(nFlags, point);
}

 

////////////////////////////////////////调用//////////////////////////////////////////////////////////////////////////

//CDemo2Dlg.h

//CProSliderCtrl m_SliderCtrl;
 
//CDemo2Dlg.cpp

//DDX_Control(pDX, IDC_SLIDER1, m_SliderCtrl);
 
// BOOL CDemo2Dlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
// {
 // // TODO: 在此添加专用代码和/或调用基类
 // NMHDR *pParam = reinterpret_cast<NMHDR*>(lParam);
 // if(pParam->hwndFrom == m_SliderCtrl.m_hWnd)
 // {
  // TCHAR strNum[256];
  // sprintf(strNum,"%d%%",m_SliderCtrl.GetPos(););
  // SetDlgItemText(IDC_EDIT1,strNum);
 // }

 // return CDialog::OnNotify(wParam, lParam, pResult);
// }
 

