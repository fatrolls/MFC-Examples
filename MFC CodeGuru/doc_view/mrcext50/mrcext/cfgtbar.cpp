// cfgtbar.cpp : implementation file
//

#include "mrcstafx.h"
#include "mrcext.h"
#include "cfgTbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMRCCfgToolBar

CMRCCfgToolBar::CMRCCfgToolBar()
{
	m_pBitmapIds = NULL;
	m_nBitmapButtons = 0;
}

CMRCCfgToolBar::~CMRCCfgToolBar()
{
}


BEGIN_MESSAGE_MAP(CMRCCfgToolBar, CToolBar)
	//{{AFX_MSG_MAP(CMRCCfgToolBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TBN_QUERYINSERT,		OnTBNQueryInsert)
	ON_NOTIFY_REFLECT(TBN_QUERYDELETE,		OnTBNQueryDelete)
	ON_NOTIFY_REFLECT(TBN_BEGINADJUST,		OnTBNBeginAdjust)
	ON_NOTIFY_REFLECT(TBN_TOOLBARCHANGE,	OnTBNToolBarChange)
  	ON_NOTIFY_REFLECT(TBN_GETBUTTONINFO,	OnTBNGetButtonInfo)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMRCCfgToolBar message handlers

//-----------------------------------------------------------------------------
BOOL CMRCCfgToolBar::Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID)
//-----------------------------------------------------------------------------
{
	dwStyle |= CCS_ADJUSTABLE;
	return CToolBar::Create(pParentWnd, dwStyle, nID);
}


//-----------------------------------------------------------------------------
void CMRCCfgToolBar::SetBitmapIds(UINT * pIds, int nButtons)
//-----------------------------------------------------------------------------
{
	m_pBitmapIds = pIds;
	m_nBitmapButtons = nButtons;
}


//-----------------------------------------------------------------------------
int CMRCCfgToolBar::FindBitmapIndex(UINT nID)
//-----------------------------------------------------------------------------
{
	ASSERT(m_pBitmapIds != NULL);
	for (int i = 0; i < m_nBitmapButtons ; i++)
	{
		if (m_pBitmapIds[i] == (int)nID)
			return i;
	}
	return -1;
}



//-----------------------------------------------------------------------------
BOOL CMRCCfgToolBar::SetButtons(UINT * lpIDArray, int nIDCount)
// emulate CToolBar::SetButtons()
// If there's a list of Id's set, then we have to look the id's up
// indirectly to get the correct bitmap
//-----------------------------------------------------------------------------
{
	int nImageNo = 0;		// no of image in bitmap (coun
	int nBtn = 0; 			// no of buttons we've actually created (including separators)
							// may not equal no of buttons supplied by user, as id's may not
							// be found

	// add new buttons to the common control
	TBBUTTON button; memset(&button, 0, sizeof(TBBUTTON));
	int iImage = 0;
	for (int i = 0; i < nIDCount; i++)
	{
		button.fsState = TBSTATE_ENABLED;
		if ((button.idCommand = *lpIDArray++) == 0)
		{
			// separator
			button.fsStyle = TBSTYLE_SEP;
			// width of separator includes 8 pixel overlap
			button.iBitmap = 8;
		}
		else
		{
			// a command button with image
			button.fsStyle = TBSTYLE_BUTTON;
			button.iBitmap = iImage++;
			button.iBitmap = FindBitmapIndex(button.idCommand);
			if (button.iBitmap == -1)
			{
				TRACE("Couldn't find bitmap for ID=%d\n",button.idCommand);
				button.iBitmap = 0;
			}

		}
		if (!DefWindowProc(TB_ADDBUTTONS, 1, (LPARAM)&button))
			return FALSE;
	}

	
	
	return TRUE;
}	


//-----------------------------------------------------------------------------
afx_msg void CMRCCfgToolBar::OnTBNGetButtonInfo(NMHDR *pNMHDR, LRESULT * pResult)
// Return information for bitmap indexes in the toolbar
//-----------------------------------------------------------------------------
{
	TBNOTIFY * pTBN = (TBNOTIFY *)pNMHDR;
	
	int nIndex = pTBN->iItem;
	if (nIndex < m_nBitmapButtons)
	{
		*pResult = TRUE;

 	    UINT nButtonId = m_pBitmapIds[nIndex];
 	    pTBN->tbButton.iBitmap = nIndex;
 	    pTBN->tbButton.idCommand = nButtonId;
		pTBN->tbButton.fsState = TBSTATE_ENABLED;
		pTBN->tbButton.fsStyle = TBSTYLE_BUTTON;
		pTBN->tbButton.iString = 0;		
		if (pTBN->pszText != NULL)
		{		
			CString strText;
			if (strText.LoadString(nButtonId))
			{
				char * pTipText = strchr(strText, '\n');   // tool tip is after "\n" in the string
				if (pTipText != NULL)
				{	
					strncpy(pTBN->pszText, pTipText + 1, pTBN->cchText);
           			return;
				}
			}
			TRACE("CMRCCfgToolBar:No Tooltip prompt for ID=%d\n", nButtonId);
			strncpy(pTBN->pszText, "???", pTBN->cchText);
		}
	}
	else 
		*pResult = FALSE;
}



//-----------------------------------------------------------------------------
afx_msg void CMRCCfgToolBar::OnTBNBeginAdjust(NMHDR *pNMHDR, LRESULT * pResult)
//-----------------------------------------------------------------------------
{
}


//-----------------------------------------------------------------------------
afx_msg void CMRCCfgToolBar::OnTBNQueryInsert(NMHDR *pNMHDR, LRESULT * pResult)
//-----------------------------------------------------------------------------
{
	*pResult = TRUE;		// always allow buttons to be inserted
}


//-----------------------------------------------------------------------------
afx_msg void CMRCCfgToolBar::OnTBNQueryDelete(NMHDR *pNMHDR, LRESULT * pResult)
//-----------------------------------------------------------------------------
{
	*pResult = TRUE;		// always allow buttons to be deleted
}

//-----------------------------------------------------------------------------
afx_msg void CMRCCfgToolBar::OnTBNToolBarChange(NMHDR *pNMHDR, LRESULT * pResult)
//-----------------------------------------------------------------------------
{
}


//-----------------------------------------------------------------------------
void CMRCCfgToolBar::Customize()
//-----------------------------------------------------------------------------
{
	GetToolBarCtrl().Customize();
}

