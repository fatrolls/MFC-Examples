#include <stdafx.h>
#include <afxtempl.h>
#include <math.h>

#include "..\..\common\GlobalConstants.h"
#include "GlobalFunctions.h"
#include "..\..\PukamSoft\resource.h"
#include "..\..\PukamSoft\MessageBoxDlg.h"
#include "..\CImage\src\ImgObj.h"

//#include <list>
//using std::list;

int g_nArrayOfScalars[NUM_SCALARS] = 
{
	5,
	10,25,50,
	100,250,500,
	1000,2500,5000,
	10000,25000,50000,
	100000,250000,500000,
	1000000,2500000,5000000,
	10000000,25000000,50000000
};

CString g_csSpanIncludingStrings[NUM_SPANSTRINGS] = 
{
	"0123456789",
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ",
	"01234456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ",
	"0123456789.",
	"0123456789.-",
	"0123456789.-_@abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
	"0123456789-"
};

BOOL FindControlEdge(CWnd* pWnd, CDC *dcControl, COLORREF colToSkip, HRGN &hRgn)
{
	int nCurrentX = 0;
	int nCurrentY = 0;
	int nTempX = 0;
	int nTempY = 0;
	BOOL bStop = FALSE;
	int nDirection = 0;
	int nCurDirection = 0;
	int nFirstX = 0;
	int nFirstY = 0;
	int nXMap = 0;
	int nYMap = 0;
	int nIterate = 0;

	POINT ptTempCoord;			
	CList<POINT, POINT> ptCoord;
	//list<POINT> ptCoord;
	//HRGN hrgnWin;

	
	CRect rcWindow(0,0,0,0);
	CRect rcClient(0,0,0,0);

	//CWnd::GetWindowRect(&rcWindow);
	pWnd->GetWindowRect(&rcWindow);
	pWnd->GetClientRect(&rcClient);
	pWnd->ClientToScreen(&rcClient);
	nXMap = rcClient.left - rcWindow.left;
	nYMap = rcClient.top - rcWindow.top;
	
	nIterate = 0;
	bStop = FALSE;

	nCurrentX = 0;
	nCurrentY = 0;
	
	nDirection = SOUTHEAST;

	nFirstX = 0; //nCurrentX;
	nFirstY = 0; //nCurrentY;
	//colToSkip = dcControl->GetPixel(0, 0);
//	if(colToSkip != 0x00ffffff)
//		colToSkip = RGB(255,0,255);
	while(!bStop) 
	{
		if((dcControl->GetPixel(nCurrentX+1, nCurrentY+1)) != colToSkip)
		{
			bStop = TRUE;

			if(nCurrentX == 0 && nCurrentY == 0)
			{
				return FALSE;
			}
		}
		else 
		{
			nCurrentX++;
			nCurrentY++;
		}
	}

	bStop = FALSE;
//	nFirstX = 0; //nCurrentX;
//	nFirstY = 0; //nCurrentY;

	while(!bStop) 
	{
		nIterate++;

		switch(nDirection) 
		{
			case SOUTHEAST:
				if((dcControl->GetPixel(nCurrentX+1, nCurrentY+1)) != colToSkip) 
				{
					nDirection = EAST;
					continue;
				}
				else 
				{
					nCurrentX++;
					nCurrentY++;
				}
				break;
			case EAST:
				if((dcControl->GetPixel(nCurrentX+1, nCurrentY)) != colToSkip) 
				{
					nDirection = NORTHEAST;
					continue;
				}
				else 
				{
					nCurrentX++;
				}
				break;
			case NORTHEAST:
				if((dcControl->GetPixel(nCurrentX+1, nCurrentY-1)) != colToSkip) 
				{
					nDirection = NORTH;
					continue;
				}
				else 
				{
					nCurrentX++;
					nCurrentY--;
				}
				break;
			case NORTH:
				if((dcControl->GetPixel(nCurrentX, nCurrentY-1)) != colToSkip) 
				{
					nDirection = NORTHWEST;
					continue;
				}
				else 
				{
					nCurrentY--;
				}
				break;
			case NORTHWEST:
				if((dcControl->GetPixel(nCurrentX-1, nCurrentY-1)) != colToSkip) 
				{
					nDirection = WEST;
					continue;
				}
				else 
				{
					nCurrentX--;
					nCurrentY--;
				}
				break;
			case WEST:
				if((dcControl->GetPixel(nCurrentX-1, nCurrentY)) != colToSkip) 
				{
					nDirection = SOUTHWEST;
					continue;
				}
				else 
				{
					nCurrentX--;
				}
				break;
			case SOUTHWEST:
				if((dcControl->GetPixel(nCurrentX-1, nCurrentY+1)) != colToSkip) 
				{
					nDirection = SOUTH;
					continue;
				}
				else 
				{
					nCurrentX--;
					nCurrentY++;
				}
				break;
			case SOUTH:
				if((dcControl->GetPixel(nCurrentX, nCurrentY+1)) != colToSkip) 
				{
					nDirection = SOUTHEAST;
					continue;
				}
				else 
				{
					nCurrentY++;
				}
				break;
		}

		nCurDirection = nDirection;

		if((dcControl->GetPixel(nCurrentX+1, nCurrentY+1)) != colToSkip)
		{
			nDirection = SOUTHEAST;
		}
		if((dcControl->GetPixel(nCurrentX+1, nCurrentY)) != colToSkip)
		{
			nDirection = EAST;
		}
		if((dcControl->GetPixel(nCurrentX+1, nCurrentY-1)) != colToSkip)
		{
			nDirection = NORTHEAST;
		}
		if((dcControl->GetPixel(nCurrentX, nCurrentY-1)) != colToSkip)
		{
			nDirection = NORTH;
		}
		if((dcControl->GetPixel(nCurrentX-1, nCurrentY-1)) != colToSkip)
		{
			nDirection = NORTHWEST;
		}
		if((dcControl->GetPixel(nCurrentX-1, nCurrentY)) != colToSkip)
		{
			nDirection = WEST;
		}
		if((dcControl->GetPixel(nCurrentX-1, nCurrentY+1)) != colToSkip)
		{
			nDirection = SOUTHWEST;
		}
		if((dcControl->GetPixel(nCurrentX, nCurrentY+1)) != colToSkip)
		{
			nDirection = SOUTH;
		}

		POINT ptTemp;

		//ptTemp = (ptCoord.end());
		if(ptCoord.GetCount() > 0)
		{
			ptTemp = ptCoord.GetTail();
		}
		else
		{
			ptTemp.x = 0;
			ptTemp.y = 0;
		}

		if(nCurrentX != ptTemp.x || nCurrentY != ptTemp.y) 
		{
			nTempX = nCurrentX;
			nTempY = nCurrentY;

			switch (nCurDirection) 
			{
				case NORTH:
				case NORTHWEST:
					nTempX++;
					break;
				case NORTHEAST:
				case EAST:
					nTempY++;
					break;
			}

			ptTempCoord.x = nTempX; // + nXMap;
			ptTempCoord.y = nTempY; // + nYMap;
			ptCoord.AddTail(ptTempCoord);
		}

		//dcControl->SetPixel(nCurrentX, nCurrentY, RGB(0, 0, 0));

		if(nFirstX == 0 && nFirstY == 0)
		{
			nFirstX = nCurrentX;
			nFirstY = nCurrentY;
		}
		else if(nCurrentX == nFirstX && nCurrentY == nFirstY)
		{
			break;
		}
	}

	//TRACE("Iterate %d\n", nIterate);

	POINT *ptAll;

	//ptAll = new POINT[ptCoord.size()];
	ptAll = new POINT[ptCoord.GetCount()];

	//int nLen = ptCoord.size();
	int nLen = ptCoord.GetCount();

	for(int idx=0; idx<nLen; idx++) 
	{
		/*ptAll[idx] = ptCoord.front();
		ptCoord.pop_front();*/
		ptAll[idx] = ptCoord.GetHead();
		ptCoord.RemoveHead();
	}

	hRgn = CreatePolygonRgn(ptAll, nLen, ALTERNATE);

	delete []ptAll;

	if(hRgn != NULL) 
	{
		if(pWnd->SetWindowRgn(hRgn, TRUE) != 0)
		{
			return TRUE;
		}
	}

	//MessageBox("Error creating region!");
	return FALSE;
}


void DisplayLastError()
{
	LPVOID lpMsgBuf = NULL;
	unsigned long lError = 0L;
	LPTSTR lpszMessage = 0;

	lError = GetLastError();

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		lError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

	
	lpszMessage = new char[strlen((LPCTSTR)lpMsgBuf)+5];

	sprintf(lpszMessage, "%d : %s", lError, (LPCTSTR)lpMsgBuf);
	MessageBoxEng(NULL,MB_MSG_USERDEFINED_ERROR,MB_OK_BUTTON,"",(LPCTSTR)lpMsgBuf);

	LocalFree( lpMsgBuf );
}

int RoundUpEx(int nNumber)
{
	int nRet = 0;
	int nPower = (int)log10(abs(nNumber));
	int nFactor = 0;

	if(nNumber<0)
	{
		nFactor = (int)floor(nNumber/pow(10,nPower));
	}
	else
	{
		nFactor = (int)ceil(nNumber/pow(10,nPower));
	}

	nRet = (int)(nFactor*pow(10,nPower));
	
	return nRet;
}

int RoundDownEx(int nNumber)
{
	int nRet = 0;
	int nPower = (int)log10(abs(nNumber));
	int nFactor = 0;

	if(nNumber<0)
	{
		nFactor = (int)ceil(nNumber/pow(10,nPower));
	}
	else
	{
		nFactor = (int)floor(nNumber/pow(10,nPower));
	}

	nRet = (int)(nFactor*pow(10,nPower));
	
	return nRet;
}

UINT RoundEx(long double dValue)
{
	if (fmod((double)dValue,1.0) >= 0.5)
	{
		return (UINT)ceil((double)dValue);
	}
	else
	{
		return (UINT)floor((double)dValue);
	}
}

int FindGraphScaleYEx(int nMin, int nMax)
{
	int nRet = 0;
	int nMaxTemp = 0;
	int nMinTemp = 0;
	int nAvg = (abs(nMin)+abs(nMax))/(NUM_SCALES-3);
	int nFound = 0;
	int nFoundIdx = 0;
	
	for(int nIndex=0; nIndex<NUM_SCALARS; nIndex++)
	{
		nMaxTemp = abs(nMax)/g_nArrayOfScalars[nIndex];
		nMinTemp = abs(nMin)/g_nArrayOfScalars[nIndex];

		if(nMaxTemp+nMinTemp <= NUM_SCALES-3)
		{
			nFound = g_nArrayOfScalars[nIndex];
			nFoundIdx = nIndex;
			nRet = nFound;
			while(nAvg < nFound)
			{
				nFound -= g_nArrayOfScalars[--nFoundIdx];
			}
			nRet = nFound+g_nArrayOfScalars[nFoundIdx];
			break;
		}
	}
	return nRet;
}

int FindGraphScaleXEx(int nMin, int& nNextHigher)
{
	int nRet = 60*11/(80-nMin);

	if(nMin%5 == 0)
	{
		nNextHigher = nMin;
	}
	else
	{
		nNextHigher = nMin;
		while(nNextHigher%5 != 0)
		{
			nNextHigher++;
		}
	}
	return nRet;
}

//This is global function. This is to put in Another file
double GetRoundedValue(double dValue)
{
	int nValue = int(dValue);
	double dDiff = dValue - nValue;
	if(dDiff < 0.5)
	{
		return dValue;
	}
	else
	{
		return (dValue + (1 - dDiff));
	}
}

CString UnFormatNumberString(CString csFormattedString)
{
	CString csNumberString = csFormattedString;

	csNumberString.Remove(',');
	csNumberString.TrimLeft();
	csNumberString.TrimRight();

	return csNumberString;
}

CString FormatNumberString(CString csNumberString)
{
	csNumberString.TrimLeft();
	csNumberString.TrimRight();

	if (csNumberString.IsEmpty())
	{
		return csNumberString;
	}
	
	CString csSignString;
	csSignString.Empty();
	
	CString csFormatedNumberString;
	csFormatedNumberString.Empty();
	
	CString csStringToFormat;
	CString csDecimalString;
	
	int nDecimalPtPos;
	
	nDecimalPtPos = csNumberString.Find('.',0);
	
	if (nDecimalPtPos != -1)
	{
		csDecimalString = csNumberString.Mid(nDecimalPtPos);
		csStringToFormat = csNumberString.Mid(0,nDecimalPtPos);
	}
	else
	{
		csStringToFormat = csNumberString;
		csDecimalString.Empty();
	}
	
	if (!csStringToFormat.IsEmpty())
	{
		if (csStringToFormat.GetAt(0) == '-')
		{
			csStringToFormat = csStringToFormat.Mid(1);
			csSignString = "-";
		}
		
		if (csStringToFormat.GetLength() <= 3)
		{
			csFormatedNumberString = csSignString + csStringToFormat + csDecimalString; 
			return csFormatedNumberString;
		}
		
		int nStartIndex;
		
		if ((csStringToFormat.GetLength() % 2) == 0)
		{
			csFormatedNumberString = csStringToFormat.Mid(0,1) + ","; 
			nStartIndex = 1;
		}
		else
		{
			csFormatedNumberString = csStringToFormat.Mid(0,2) + ",";
			nStartIndex = 2;
		}
		
		for(int i = nStartIndex; i < csStringToFormat.GetLength() - 3; i++)
		{
			csFormatedNumberString += csStringToFormat.Mid(i,2) + ",";
			i++;
		}
		
		csFormatedNumberString += csStringToFormat.Mid(csStringToFormat.GetLength() -3,3) + csDecimalString;
		csFormatedNumberString = csSignString + csFormatedNumberString;
	}
	else
	{
		csFormatedNumberString = csDecimalString; 
	}
	
	return csFormatedNumberString;
}

int MessageBoxEng(CWnd* pWnd,
				  UINT nMsgID,
				  UINT nMsgType,
				  LPCTSTR lpszMsgTitle,
				  LPCTSTR lpszMsgExtra)
{
	int nRet = -1;

	CMessageBoxDlg msgBoxDlg(pWnd);
	msgBoxDlg.InitializeMessageBox(nMsgID,
								nMsgType,
								lpszMsgTitle,
								lpszMsgExtra);

	::PostMessage((pWnd->GetParent())->GetSafeHwnd(), WM_USER, MSG_DISABLETOPLEVELWINDOWS, 0L);

	nRet = msgBoxDlg.DoModal();

	::PostMessage((pWnd->GetParent())->GetSafeHwnd(), WM_USER, MSG_ENABLETOPLEVELWINDOWS, 0L);

	return nRet;
}

BOOL IsValidDate(CString csDate, CString& csRetMsg)
{
	int nFound = csDate.Find("/");
	CString csSeperator = "";
	BOOL bFound = FALSE;

	if(nFound != -1)
	{
		csSeperator = "/";
		bFound = TRUE;
	}
	else
	{
		bFound = FALSE;
	}

	if(bFound == TRUE)
	{
		CStringArray csElementArray;
		SplitStringEx(((LPTSTR)(LPCTSTR)csDate),csSeperator,&csElementArray);

		CString csDay = "";
		CString csMonth = "";
		CString csYear = "";

		int nDay = 0;
		int nMonth = 0;
		int nYear = 0;
	
		int nTotalStrings = 0;
		nTotalStrings = csElementArray.GetSize();
		if(nTotalStrings != 3)
		{
			csRetMsg = "Invalid date";
			return FALSE;
		}
		csDay = csElementArray.GetAt(0);
		csMonth = csElementArray.GetAt(1);
		csYear = csElementArray.GetAt(2);
		
		nDay = atoi(csDay);
		nMonth = atoi(csMonth);
		nYear = atoi(csYear);

		CMap<int,int,int,int> mapMonthDay;
		mapMonthDay.InitHashTable(13);

		if(mapMonthDay.IsEmpty())
		{
			mapMonthDay.RemoveAll();
		}
		
		int nFebDay = 0;
		if(((nYear%4 == 0)&&(nYear%100 != 0)) 
			|| (nYear%400 == 0))
		{
			nFebDay = 29;
		}
		else
		{
			nFebDay = 28; 
		}
		
		mapMonthDay.SetAt(0,0);
		mapMonthDay.SetAt(1,31);
		mapMonthDay.SetAt(2,nFebDay);
		mapMonthDay.SetAt(3,31);
		mapMonthDay.SetAt(4,30);
		mapMonthDay.SetAt(5,31);
		mapMonthDay.SetAt(6,30);
		mapMonthDay.SetAt(7,31);
		mapMonthDay.SetAt(8,31);
		mapMonthDay.SetAt(9,30);
		mapMonthDay.SetAt(10,31);
		mapMonthDay.SetAt(11,30);
		mapMonthDay.SetAt(12,31);
		
		if(nDay < 1 || nDay > 31)
		{
			csRetMsg = "Entered DAY is invalid";
			return FALSE;
		}
		if(nMonth < 1 || nMonth > 12)
		{
			csRetMsg = "Entered MONTH is invalid";
			return FALSE;
		}
		else
		{
			int nNoOfDays;
			mapMonthDay.Lookup(nMonth,nNoOfDays);
			if(nDay > nNoOfDays )
			{
				csRetMsg = "Entered DAY is invalid";
				return FALSE;
			}
		}
		if((nYear < 1000) || (nYear > 9999))
		{
			csRetMsg = "Entered YEAR is invalid";
			return FALSE;
		}
	
		mapMonthDay.RemoveAll();
	}
	else
	{
		 csRetMsg = "Invalid date";	
		 return FALSE;
	}

	return TRUE;
}

BOOL IsValidAge(CString csDOB, CString csCurrentDate, int& nAge)
{
	CString csSeperator = "/";

	CStringArray csDOBArray,csCurrentDateArray;
	SplitStringEx(((LPTSTR)(LPCTSTR)csDOB),csSeperator,&csDOBArray);
	SplitStringEx(((LPTSTR)(LPCTSTR)csCurrentDate),csSeperator,&csCurrentDateArray);

	CString csDayDOB = "";
	CString csMonthDOB = "";
	CString csYearDOB = "";
	CString csDayCurrentDate = "";
	CString csMonthCurrentDate = "";
	CString csYearCurrentDate = "";

	csDayDOB = csDOBArray.GetAt(0);
	csMonthDOB = csDOBArray.GetAt(1);
	csYearDOB = csDOBArray.GetAt(2);

	csDayCurrentDate = csCurrentDateArray.GetAt(0);
	csMonthCurrentDate = csCurrentDateArray.GetAt(1);
	csYearCurrentDate = csCurrentDateArray.GetAt(2);

	int nDiffYear = atoi(csYearCurrentDate) - atoi(csYearDOB);
	int nDiffMonth = atoi(csMonthCurrentDate) - atoi(csMonthDOB);
	int nDiffDay = atoi(csDayCurrentDate) - atoi(csDayDOB);

	if((nDiffYear > 70) || (nDiffYear < 21))
	{
		return FALSE;
	}
	else
	{
		if(nDiffYear == 21)
		{
			if(nDiffMonth < 0)
			{
				return FALSE;
			}
			else if(nDiffMonth > 0 )
			{
				nAge = nDiffYear; 
				return TRUE;
			}
			else if(nDiffMonth == 0)
			{
				if(nDiffDay < 0)
				{
					return FALSE;
				}
				else
				{
					nAge = nDiffYear;
					return TRUE;
				}
			}
		}
		if(nDiffYear == 70)
		{
			if(nDiffMonth > 0)
			{
				return FALSE;
			}
			else if(nDiffMonth < 0 )
			{
				nAge = nDiffYear; 
				return TRUE;
			}
			else if(nDiffMonth == 0)
			{
				if(nDiffDay > 0)
				{
					return FALSE;
				}
				else
				{
					nAge = nDiffYear; 
					return TRUE;
				}
			}
		}
	}

	nAge = nDiffYear; 
	return TRUE;
}

BOOL IsFieldEmpty(LPCTSTR lpszText)
{
	return (lstrlen(lpszText) == 0);
}

BOOL IsFieldTypeValid(UINT nType, LPCTSTR lpszText)
{
	BOOL bRet = FALSE;
	CString csText = lpszText;
	
	CString csRet = csText.SpanIncluding(g_csSpanIncludingStrings[nType]);
	if(/*!csRet.IsEmpty() && */(csRet==csText))
	{
		bRet = TRUE;
	}
	
	return bRet;
}

int GetCurrentDay()
{
	SYSTEMTIME systime;
	GetSystemTime(&systime);

	return systime.wDay;
}

int GetCurrentMonth()
{
	SYSTEMTIME systime;
	GetSystemTime(&systime);

	return systime.wMonth;
}

int GetCurrentYear()
{
	SYSTEMTIME systime;
	GetSystemTime(&systime);

	return systime.wYear;
}

BOOL IsDateGreaterThanTheSystemDate(CString csDate)
{
	SYSTEMTIME systime;
	GetSystemTime(&systime);

	COleDateTime SystemDate(systime);

	CString csSeperator = "/";

	CStringArray csDateArray;
	SplitStringEx(((LPTSTR)(LPCTSTR)csDate),csSeperator,&csDateArray);

	int nDay = atoi(csDateArray.GetAt(0));
	int nMonth = atoi(csDateArray.GetAt(1));
	int nYear = atoi(csDateArray.GetAt(2));

	COleDateTime Date(nYear,nMonth,nDay,0,0,0);

	COleDateTimeSpan DateDiff = Date - SystemDate;
	
	if (DateDiff.GetTotalDays() > 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

HBITMAP LoadGIFEng(HINSTANCE hInstance, LPCTSTR lpGIFName, CBitmap* pBmp)
{
	HBITMAP hBmp=NULL;
	CImageObject *pImageObj;

	pImageObj = new CImageObject;

	HRSRC hRes = FindResource(hInstance, lpGIFName, "RT_RCDATA");
	
	if(hRes != NULL)
	{
		if(pImageObj->LoadResource(hRes, ENUM_cimage_format_gif, hInstance))
		{
			pBmp->Detach();

			pImageObj->MakeBitmap(pBmp);

			hBmp = (HBITMAP)(*pBmp);
		}
	}

	if(pImageObj != NULL)
	{
		delete pImageObj;
		pImageObj = 0;
	}

	return hBmp;
}

void PaintRectEx(CDC* pDC, int x, int y, int w, int h, COLORREF color)
{
	CBrush brush(color);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	pDC->PatBlt(x, y, w, h, PATCOPY);
	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();
}

void PaintGradiantRectEx(CDC *pDC, const RECT &rect,COLORREF clrFrom, COLORREF clrTo, 
                       BOOL hori, BOOL ascend)
{
	int cxCap = rect.right - rect.left;
	int cyCap = rect.bottom - rect.top;

	// Get the intensity values for the ending color
	int r1 = GetRValue(clrTo); // red
	int g1 = GetGValue(clrTo); // green
	int b1 = GetBValue(clrTo); // blue
	
	// Get the intensity values for the begining color
	int r2 = GetRValue(clrFrom); // red
	int g2 = GetGValue(clrFrom); // green
	int b2 = GetBValue(clrFrom); // blue

	int r, g, b;

    if(hori) //paint horizontal rect;
    {
	    int x = cxCap;	
	    int w = x;							// width of area to shade
	    int xDelta= max(w/NCOLORSHADES,1);	// width of one shade band


	    while (x >= xDelta) {
		    x -= xDelta;
		    if (r1 > r2)
			    r = r1 - (r1-r2)*(w-x)/w;
		    else
			    r = r1 + (r2-r1)*(w-x)/w;

		    if (g1 > g2)
			    g = g1 - (g1-g2)*(w-x)/w;
		    else
			    g = g1 + (g2-g1)*(w-x)/w;

		    if (b1 > b2)
			    b = b1 - (b1-b2)*(w-x)/w;
		    else
			    b = b1 + (b2-b1)*(w-x)/w;

            if(ascend) // Paint from  left to right;
		        PaintRectEx(pDC, rect.left+x, rect.top, xDelta, cyCap, RGB(r, g, b));
            else               // Paint from  right to left;
                PaintRectEx(pDC, rect.right-x-xDelta, rect.top, xDelta, cyCap, RGB(r, g, b));
	    }
    }
    else    //paint vertical rect;
    {
	    int y = cyCap;	
	    int w = y;							// height of area to shade
	    int yDelta= max(w/NCOLORSHADES,1);	// height of one shade band


	    //while (y >= yDelta) {
        while (y > 0) {
		    y -= yDelta;
		    if (r1 > r2)
			    r = r1 - (r1-r2)*(w-y)/w;
		    else
			    r = r1 + (r2-r1)*(w-y)/w;

		    if (g1 > g2)
			    g = g1 - (g1-g2)*(w-y)/w;
		    else
			    g = g1 + (g2-g1)*(w-y)/w;

		    if (b1 > b2)
			    b = b1 - (b1-b2)*(w-y)/w;
		    else
			    b = b1 + (b2-b1)*(w-y)/w;
		    
            if(ascend) // Paint from  top to bottom;
		        PaintRectEx(pDC, rect.left, rect.top+y, cxCap, yDelta, RGB(r, g, b));
            else       // Paint from  bottom to top;
                PaintRectEx(pDC, rect.left, rect.bottom-y-yDelta, cxCap, yDelta, RGB(r, g, b));
	    }
    }

}