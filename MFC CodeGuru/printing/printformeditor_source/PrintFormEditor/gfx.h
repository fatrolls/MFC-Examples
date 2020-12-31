#ifndef __GFX_GLOBAL_INCLUDE
#define __GFX_GLOBAL_INCLUDE

// TAB SUPPORT

#define GfxAddTabItem(m_ctlTab, nId, pText)\
{\
	TC_ITEM TabCtrlItem;\
	TabCtrlItem.mask = TCIF_TEXT;\
	TabCtrlItem.pszText = pText;\
	m_ctlTab.InsertItem( nId, &TabCtrlItem );\
}

#define GfxTabSupport(numDialog)	CDialog * __gfxTabDialog[numDialog];

#define GfxInitTabSupport(numDialog)	ZeroMemory(__gfxTabDialog, sizeof(CDialog *) * numDialog);

#define GfxSetTabDialog(numDialog, pDialog)	__gfxTabDialog[numDialog] = (CDialog *) pDialog;

#define GfxSwitchTabDialog(numDialog, maxDialog)\
{\
	for (int __gfxT = 0; __gfxT < maxDialog; __gfxT++)\
	{\
		if (__gfxT == numDialog) \
			__gfxTabDialog[__gfxT]->ShowWindow(SW_SHOW); \
		else \
			__gfxTabDialog[__gfxT]->ShowWindow(SW_HIDE); \
	}\
}

#define GfxResizeTabDialog(tab, cx, cy)\
{\
	if (tab.GetSafeHwnd())\
	{\
		tab.SetWindowPos(0,2,2,cx-4,cy-4,SWP_NOZORDER);\
		for (int __gfxT = 0; __gfxT < iNumDialog; __gfxT++)\
		{\
			if (__gfxTabDialog[__gfxT] && __gfxTabDialog[__gfxT]->GetSafeHwnd())\
				__gfxTabDialog[__gfxT]->SetWindowPos(0,2,27,cx-8,cy-34,SWP_NOZORDER);\
		}\
	}\
}


// RECT SUPPORT

bool RectInRect(CRect &rc1, CRect &rc2);

void GfxRectPerDouble(CRect &rc, const double &db);
bool GfxPumpMessage();
bool GfxParseBiText(CString &cs1, CString &cs2, const int id);
void GfxGlobalFree(HGLOBAL hGlobal);
void GfxFormatKm(CString &cs, long lKm);
int GfxGetColumnSubItem(CListCtrl * pList, const int iSub);
CString Format_CFileException(CFileException * e);


#endif
