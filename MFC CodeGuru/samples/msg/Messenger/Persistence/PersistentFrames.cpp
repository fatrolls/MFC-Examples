/* @doc
 *
 * @module PersistentFrames.cpp - CPersistentFrameWnd & CPersistentMDIFrameWnd classes |
 *
 * Implementation for CPersistentFrameWnd and CPersistentFrameWnd classes
 *
 * Copyright (c)1997 David Carballo, All Right Reserved
 *
 * @end
 *
 * Created October 1997
 * Revised: -
 * Written by David Carballo
 * Internet: fibeto@redestb.es
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 */


/*---------------------------------------------------------------------------
   I include "stdafx.h" in all MFC project files.
   I include "PersistentFrames.h" because it contains classes definition
---------------------------------------------------------------------------*/
#include "stdafx.h"

// FIX Q138722 & Q151446 
#ifndef __AFXPRIV_H__
	#include <afxpriv.h>
#endif	// __AFXPRIV_H__
// END FIX Q138722 & Q151446

#ifndef __PERSISTENTFRAMES_H_
	#include "PersistentFrames.h"
#endif	// __PERSISTENTFRAMES_H_

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static TCHAR BASED_CODE szSection[] = _T("Settings");
static TCHAR szFormat[] = _T("%u,%u,%d,%d,%d,%d,%d,%d,%d,%d");

// FIX Q138722 & Q151446
#if _MFC_VER == 0x0400 || _MFC_VER == 0x0410 

void CleanUpControlBarState(CDockState& state); 

#endif 
// END FIX Q138722 & Q151446

static BOOL ReadWindowPlacement(LPWINDOWPLACEMENT pwp,LPCSTR szWindowPos);
static void WriteWindowPlacement(LPWINDOWPLACEMENT pwp,LPCSTR szWindowPos);

IMPLEMENT_DYNAMIC(CPersistentFrameWnd, CFrameWnd)

BEGIN_MESSAGE_MAP(CPersistentFrameWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CPersistentFrameWnd)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPersistentFrameWnd::CPersistentFrameWnd()
{
}

/*---------------------------------------------------------------------------

  mfunc		Implementation for message WM_CLOSE.
  
  comm		This functions writes the current size and position to the
			application INI (or registry entry if specified with
			SetRegistryKey).

  end

Modifies: -
---------------------------------------------------------------------------*/
void CPersistentFrameWnd::OnClose() 
{
	// before it is destroyed, save the position of the window
	WINDOWPLACEMENT wp;
	wp.length = sizeof wp;
	if (GetWindowPlacement(&wp))
	{
		CRuntimeClass* pRuntimeClass = GetRuntimeClass();

		wp.flags = 0;
		if (IsZoomed())
			wp.flags |= WPF_RESTORETOMAXIMIZED;
		// and write it to the .INI file
		WriteWindowPlacement(&wp,pRuntimeClass->m_lpszClassName);
	}

	SaveBarState(szSection);


	// FIX Q138722 & Q151446
	#if _MFC_VER == 0x0400 || _MFC_VER == 0x0410

		CDockState state;
		state.LoadState(szSection);

		CleanUpControlBarState(state);

		state.SaveState(szSection);

	#endif
	// END FIX Q138722 & Q151446

	CFrameWnd::OnClose();
}

/*---------------------------------------------------------------------------

  @mfunc	Shows the window as it was the last time the app was executed.

  @parm     UINT | nCmdShow | The command that specifies the show option if
			it is the first time the app runs or if there are some error 
			reading the old size and position.
  
  @comm		Replace your call to m_pMainWnd->ShowWindow(m_nCmdShow) in your
			application InitInstance for a call to 
			m_pMainWnd->InitialShowWindow(m_nCmdShow)

  @end

Modifies: -
---------------------------------------------------------------------------*/
void CPersistentFrameWnd::InitialShowWindow(UINT nCmdShow)
{
	WINDOWPLACEMENT wp;
	CRuntimeClass* pRuntimeClass = GetRuntimeClass();

	LoadBarState(szSection);
	if (!ReadWindowPlacement(&wp,pRuntimeClass->m_lpszClassName))
	{
		ShowWindow(nCmdShow);
		return;
	}
	if (nCmdShow != SW_SHOWNORMAL)
		wp.showCmd = nCmdShow;
	SetWindowPlacement(&wp);
	ShowWindow(wp.showCmd);
}


IMPLEMENT_DYNAMIC(CPersistentMDIFrameWnd, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CPersistentMDIFrameWnd, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CPersistentMDIFrameWnd)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CPersistentMDIFrameWnd::CPersistentMDIFrameWnd()
{
}

/*---------------------------------------------------------------------------

  mfunc		Implementation for message WM_CLOSE.
  
  comm		This functions writes the current size and position to the
			application INI (or registry entry if specified with
			SetRegistryKey).

  end

Modifies: -
---------------------------------------------------------------------------*/
void CPersistentMDIFrameWnd::OnClose() 
{
	// before it is destroyed, save the position of the window
	WINDOWPLACEMENT wp;

	wp.length = sizeof wp;
	if (GetWindowPlacement(&wp))
	{
		CRuntimeClass* pRuntimeClass = GetRuntimeClass();

		if (IsZoomed())
			wp.flags |= WPF_RESTORETOMAXIMIZED;
		// and write it to the .INI file
		WriteWindowPlacement(&wp,pRuntimeClass->m_lpszClassName);
	}

	SaveBarState(szSection);

	// FIX Q138722 & Q151446
	#if _MFC_VER == 0x0400 || _MFC_VER == 0x0410

		CDockState state;
		state.LoadState(szSection);

		CleanUpControlBarState(state);

		state.SaveState(szSection);

	#endif
	// END FIX Q138722 & Q151446

	CMDIFrameWnd::OnClose();
}

/*---------------------------------------------------------------------------

  @mfunc	Shows the window as it was the last time the app was executed.

  @parm     UINT | nCmdShow | The command that specifies the show option if
			it is the first time the app runs or if there are some error 
			reading the old size and position.
  
  @comm		Replace your call to m_pMainWnd->ShowWindow(m_nCmdShow) in your
			application InitInstance for a call to 
			m_pMainWnd->InitialShowWindow(m_nCmdShow)

  @end

Modifies: -
---------------------------------------------------------------------------*/
void CPersistentMDIFrameWnd::InitialShowWindow(UINT nCmdShow)
{
	WINDOWPLACEMENT wp;
	CRuntimeClass* pRuntimeClass = GetRuntimeClass();

	LoadBarState(szSection);
	if (!ReadWindowPlacement(&wp,pRuntimeClass->m_lpszClassName))
	{
		ShowWindow(nCmdShow);
		return;
	}
	if (nCmdShow != SW_SHOWNORMAL)
		wp.showCmd = nCmdShow;
	SetWindowPlacement(&wp);
	ShowWindow(wp.showCmd);
}

/*---------------------------------------------------------------------------

  func		Reads the old size and position for a window.
  
  param		LPWINDOWPLACEMENT | pwp | Pointer to structure that will receive
			the old size and position.

---------------------------------------------------------------------------*/
BOOL ReadWindowPlacement(LPWINDOWPLACEMENT pwp,LPCSTR szWindowPos)
{
	CString strBuffer = AfxGetApp()->GetProfileString(szSection, szWindowPos);
	if (strBuffer.IsEmpty())
		return FALSE;

	WINDOWPLACEMENT wp;
	int nRead = _stscanf(strBuffer, szFormat,
		&wp.flags, &wp.showCmd,
		&wp.ptMinPosition.x, &wp.ptMinPosition.y,
		&wp.ptMaxPosition.x, &wp.ptMaxPosition.y,
		&wp.rcNormalPosition.left, &wp.rcNormalPosition.top,
		&wp.rcNormalPosition.right, &wp.rcNormalPosition.bottom);

	if (nRead != 10)
		return FALSE;

	wp.length = sizeof wp;
	*pwp = wp;
	return TRUE;
}

/*---------------------------------------------------------------------------

  func		Write a window placement to settings section of app's ini file
  
  param		LPWINDOWPLACEMENT | pwp | Pointer to structure to write.

  end

Modifies: -
---------------------------------------------------------------------------*/
void WriteWindowPlacement(LPWINDOWPLACEMENT pwp,LPCSTR szWindowPos)
// write a window placement to settings section of app's ini file
{
	TCHAR szBuffer[sizeof("-32767") * 8 + sizeof("65535") * 2];

	wsprintf(szBuffer, szFormat,
		pwp->flags, pwp->showCmd,
		pwp->ptMinPosition.x, pwp->ptMinPosition.y,
		pwp->ptMaxPosition.x, pwp->ptMaxPosition.y,
		pwp->rcNormalPosition.left, pwp->rcNormalPosition.top,
		pwp->rcNormalPosition.right, pwp->rcNormalPosition.bottom);
	AfxGetApp()->WriteProfileString(szSection, szWindowPos, szBuffer);
}


// FIX Q138722 & Q151446
#if _MFC_VER == 0x0400 || _MFC_VER == 0x0410 

void CleanUpControlBarState(CDockState& state)
{
    for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++)
    {
        CControlBarInfo* pInfo1 = (CControlBarInfo*)state.m_arrBarInfo[i];

        for (int j = 0; j < state.m_arrBarInfo.GetSize(); j++)
        {
            if (i == j)
                continue;

            CControlBarInfo* pInfo2 =
                (CControlBarInfo*)state.m_arrBarInfo[j];

            if (pInfo1->m_uMRUDockID == pInfo2->m_nBarID)
                continue;

            int nSize = pInfo2->m_arrBarID.GetSize();
            for (int k = 0; k < nSize - 1; k++)
            {
                if ((LONG)pInfo2->m_arrBarID[k] ==
                    (LONG)pInfo1->m_nBarID + 0x10000)

                    pInfo2->m_arrBarID[k] = NULL;
            }
        }
    }

    for (i = 0; i < state.m_arrBarInfo.GetSize(); i++)
    {
        CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];

        int nSize = pInfo->m_arrBarID.GetSize();
        for (int j = 0; j < nSize - 1; j++)
        {
            if (pInfo->m_arrBarID[j]==NULL)
                continue;

            for (int k = j + 1; k < nSize; k++)
            {
                if (pInfo->m_arrBarID[k]==NULL)
                    continue;

                if (pInfo->m_arrBarID[k]==pInfo->m_arrBarID[j])
                    pInfo->m_arrBarID[k] = NULL;
            }
        }

        while ((nSize!=0) && (pInfo->m_arrBarID[nSize-1]==NULL))
        {
            nSize--;
            pInfo->m_arrBarID.RemoveAt(nSize);
        }
        if (nSize)
            pInfo->m_arrBarID.InsertAt(nSize, (void*)NULL);
    }



} 
// END FIX Q138722 & Q151446

#endif 