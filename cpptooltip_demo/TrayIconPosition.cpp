// TrayIconPosition.cpp: implementation of the CTrayIconPosition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "TrayIconPosition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrayIconPosition::CTrayIconPosition()
{
	m_hWndOfIconOwner = NULL;
	m_iTrayIconID = -1;
	m_prDefaultPrecision = High;
	m_iPrecisions[0] = 60; //seconds for low precision mode
	m_iPrecisions[1] = 30; //seconds for medium precision mode
	m_iPrecisions[2] = 10; //seconds for high precision mode

	m_osVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx( &m_osVer );
}

CTrayIconPosition::~CTrayIconPosition()
{

}

void CTrayIconPosition::InitializePositionTracking(HWND hwndOfIconOwner, int iIconID)
{
	m_hWndOfIconOwner = hwndOfIconOwner;
	m_iTrayIconID = iIconID;
}

BOOL CTrayIconPosition::GetTrayIconPosition(CPoint &point, Precision prPrec)
{
	if(m_hWndOfIconOwner == NULL || m_iTrayIconID == -1)
	{
		return -1;
	}

	//let's find the time from last tray icon position calculation
	int iTotalSec = (int)(m_tLastUpdate - CTime::GetCurrentTime()).GetTotalSeconds();
	if(iTotalSec < 0)
	{
		iTotalSec = -iTotalSec;
	}

	Precision prec;
	if(prPrec == Default)
	{
		prec = m_prDefaultPrecision;
	}
	else
	{
		prec = prPrec;
	}

	BOOL bUpdateRequired = FALSE;
	if(prec == Low && iTotalSec > m_iPrecisions[0]	  ||
	   prec == Medium && iTotalSec > m_iPrecisions[1] ||
	   prec == High && iTotalSec > m_iPrecisions[2]	    )
	   {
		bUpdateRequired = TRUE;
	   }

	if(bUpdateRequired)
	{
		m_rtRectangleOfTheTray = GetTrayWndRect();
		
		if(FindOutPositionOfIcon(AfxGetApp()->LoadIcon(IDI_BLANK_BLACK)) == TRUE)
		{
			//we were able to find position of icon in tray - that's GREAT!
			m_tLastUpdate = CTime::GetCurrentTime();
			point = m_ptPosition;
			return TRUE;
		}
		else
		{
			//We were unable to locate our icon - this is not a tragedy - usually there is a solution:

			if(m_osVer.dwPlatformId == VER_PLATFORM_WIN32_NT && m_osVer.dwMajorVersion >= 5)
			{
				//We're under Win XP
				//It's quite possible that icon is hidden now let's return Left-Center point of tray - it's most likely WinXP hide-tray-icons button.
				point = m_rtRectangleOfTheTray.CenterPoint();
				point.x = m_rtRectangleOfTheTray.left + 6;
			}
			else
			{
				//we're not under XP - I have no idea why but we were unable to locate our icon - let's retunr center of the tray area
				point = m_rtRectangleOfTheTray.CenterPoint();
			}
			return FALSE;
		}
		
	}
	else
	{
		point = m_ptPosition;
	}

	return TRUE;
}

/*
	This class performs check of current position of tray icon olny from time to time.
	You can decide if you want low , med or high precision.
	Default values of precisions are:
	Low - 60 seconds
	Med - 30 seconds
	High - 10 secods

	For example Low precision at 60 seconds means that this class make a full calculation
	of tray icon and this value expires in next 60 seconds. If application will request
	position of tray icon in time shorter than 60 seconds - there will be no recalculation
	and previous calculated value will be used.
*/
void CTrayIconPosition::SetPrecisionTimeOuts(int iLowSec, int iMedSec, int iHighSec)
{
	m_iPrecisions[0] = iLowSec;
	m_iPrecisions[1] = iMedSec;
	m_iPrecisions[2] = iHighSec;
}


/*
	This function and GetTrayWndRect() are not written by me - I found this code on codeproject - not remember exacly where.
	I was forced to modify this code a bit since some assumptions taken by author were going too far.
*/
BOOL CALLBACK CTrayIconPosition::FindTrayWnd(HWND hwnd, LPARAM lParam)
{    
	TCHAR szClassName[256];
    GetClassName(hwnd, szClassName, 255);    // Did we find the Main System Tray? If so, then get its size and quit
	if (_tcscmp(szClassName, _T("TrayNotifyWnd")) == 0)    
	{        
		CRect *pRect = (CRect*) lParam;
        ::GetWindowRect(hwnd, pRect);
        return FALSE;    
	}    
	
	//Oryginal code I found on Internet were seeking here for system clock and it was assumming that clock is on the right side of tray.
	//After that calculated size of tray was adjusted by removing space occupied by clock.
	//This is not a good idea - some clocks are ABOVE or somewhere else on the screen. I found that is far safer to just ignore clock space.
	
	return TRUE;
}

CRect CTrayIconPosition::GetTrayWndRect()
{    
	CRect rect(0,0,0,0);
    HWND hWnd = FindWindow(_T("Shell_TrayWnd"), NULL);
    if (hWnd)    
	{        
		::GetWindowRect(hWnd, rect);        
		EnumChildWindows(hWnd, CTrayIconPosition::FindTrayWnd, (LPARAM)&rect);    
	}    
	else    
	{        
		int nWidth  = GetSystemMetrics(SM_CXSCREEN);
        int nHeight = GetSystemMetrics(SM_CYSCREEN);
        rect.SetRect(nWidth-40, nHeight-20, nWidth, nHeight);
    }    
	return rect;
}

//as mentioned in article Shell_NotifyIcon likes to alter icons while putting them to system tray
//so even black icon can be not in 100 black
BOOL CTrayIconPosition::CheckIfColorIsBlackOrNearBlack(COLORREF crColor)
{
	BOOL bColorIsBlack = FALSE;
	for(int iRed=0;iRed<4;iRed++)
	{
		for(int iGreen=0;iGreen<4;iGreen++)
		{
			for(int iBlue=0;iBlue<4;iBlue++)
			{
				if(crColor == RGB(iRed,iGreen,iBlue))
				{
					bColorIsBlack = TRUE;
				}
			}
		}
	}
	
	return bColorIsBlack;
}

BOOL CTrayIconPosition::FindOutPositionOfIcon(HICON icon)
{
	//First: let's set a BLANK icon in the tray.
	  NOTIFYICONDATA nid; 
	  nid.cbSize = sizeof(nid); 
	  nid.hWnd = m_hWndOfIconOwner; 
	  nid.uID = m_iTrayIconID; 
	  nid.uFlags = NIF_ICON; 
	  nid.hIcon = icon;
	  Shell_NotifyIcon(NIM_MODIFY, &nid);
	  BOOL bWeFoundIt = FALSE;
  
	  HDC hdcScreen = GetDC(NULL);

//since tray window can be strethed verticaly let's scan this area in few steps starting from the bottom to the top.
for(int iy = m_rtRectangleOfTheTray.bottom-3; iy > m_rtRectangleOfTheTray.top; iy--)
{
	  int iNoOfPixelsInLine=0;
	  for(int ix=m_rtRectangleOfTheTray.left;ix<m_rtRectangleOfTheTray.right;ix++)
	  {
		  COLORREF crPixel = GetPixel(hdcScreen, ix, iy);
		  COLORREF crPixel2 = GetPixel(hdcScreen, ix, iy-2);
		  COLORREF crPixel3 = GetPixel(hdcScreen, ix, iy+2);
		  if(CheckIfColorIsBlackOrNearBlack(crPixel)  && CheckIfColorIsBlackOrNearBlack(crPixel2)  && CheckIfColorIsBlackOrNearBlack(crPixel3))
		  {
			  iNoOfPixelsInLine++;
		  }
		  else
		  {
			  iNoOfPixelsInLine = 0;
		  }

		  if(iNoOfPixelsInLine > 8)
		  {
			//well I think we found it!
			m_ptPosition.x = ix-1;
			m_ptPosition.y = iy-6;
			bWeFoundIt = TRUE;
			break;
		  }
	  }

	  if(bWeFoundIt)
	  {
		  break;
	  }
}
	  ReleaseDC(NULL, hdcScreen);

	return bWeFoundIt;
}

void CTrayIconPosition::RestoreTrayIcon(HICON icon)
{
	  NOTIFYICONDATA nid; 
	  nid.cbSize = sizeof(nid); 
	  nid.hWnd = m_hWndOfIconOwner; 
	  nid.uID = m_iTrayIconID; 
	  nid.uFlags = NIF_ICON; 
	  nid.hIcon = icon;
	  Shell_NotifyIcon(NIM_MODIFY, &nid);	
}

void CTrayIconPosition::Invalidate()
{
	m_tLastUpdate = CTime(2000,1,1,1,1,1);
}
