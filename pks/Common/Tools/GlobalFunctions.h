#ifndef _DECLARE_GLOBAL_FUNCTION

#define _DECLARE_GLOBAL_FUNCTION

#define NUM_SCALES				14
#define NUM_SCALARS				22
#define APPOBJ					((CLifeTunerApp*)AfxGetApp())
#define NUM_SPANSTRINGS			7

#include "..\..\Common\GlobalConstants.h"

BOOL FindControlEdge(CWnd* pWnd, CDC *dcControl, COLORREF colToSkip, HRGN &hRgn);
void DisplayLastError();

int RoundUpEx(int nNumber);
int RoundDownEx(int nNumber);
double GetRoundedValue(double dValue);

int FindGraphScaleYEx(int nMin, int nMax);
int FindGraphScaleXEx(int nMin, int& nNextHigher);
UINT RoundEx(long double dValue);

CString FormatNumberString(CString csNumberString);
CString UnFormatNumberString(CString csFormattedString);

int MessageBoxEng(CWnd* pWnd,
				  UINT nMsgID, 
				  UINT nMsgType, 
				  LPCTSTR lpszMsgTitle,
				  LPCTSTR lpszMsgExtra);

BOOL IsFieldEmpty(LPCTSTR lpszText);
BOOL IsValidAge(CString csDOB, CString csCurrentDate, int& nAge);
BOOL IsValidDate(CString csDate, CString& csRetMsg);
BOOL IsFieldTypeValid(UINT nType, LPCTSTR lpszText);
BOOL IsDateGreaterThanTheSystemDate(CString csDate);

int GetCurrentYear();
int GetCurrentMonth();
int GetCurrentDay();

HBITMAP LoadGIFEng(HINSTANCE hInstance, LPCTSTR lpGIFName, CBitmap* pBmp);

void PaintRectEx(CDC* pDC, int x, int y, int w, int h, COLORREF color);
void PaintGradiantRectEx(CDC *pDC, const RECT &rect,COLORREF clrFrom, COLORREF clrTo, 
                       BOOL hori, BOOL ascend);
#endif