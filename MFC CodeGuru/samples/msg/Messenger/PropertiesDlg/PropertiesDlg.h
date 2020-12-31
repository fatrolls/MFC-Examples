#ifndef TPROPERTIES_DLG_H
#define TPROPERTIES_DLG_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropertiesDlg.h : header file
//

#ifndef PROPERTIES_TREE_CTRL_H
	#include "PropertiesTreeCtrl.h"
#endif

#include "PropertiesRes.h"
#include "ColourPicker.h"

/////////////////////////////////////////////////////////////////////////////
// CTPropertiesDlg dialog
#define CountOf(array) (sizeof(array)/sizeof(array[0]))
#define COLOR_TEXT "    " // space for color


#ifdef _AFXDLL
#define TWND_BEGIN_MESSAGE_MAP(theClass, baseClass) \
	template <class baseClass> \
	const AFX_MSGMAP* PASCAL theClass##<baseClass>::_GetBaseMessageMap() \
		{ return &baseClass::messageMap; } \
	template <class baseClass> \
	const AFX_MSGMAP* theClass##<baseClass>::GetMessageMap() const \
		{ return &theClass##<baseClass>::messageMap; } \
	template <class baseClass> \
	AFX_DATADEF const AFX_MSGMAP theClass##<baseClass>::messageMap = \
	{ &theClass##<baseClass>::_GetBaseMessageMap, &theClass##<baseClass>::_messageEntries[0] }; \
	template <class baseClass> \
	const AFX_MSGMAP_ENTRY theClass##<baseClass>::_messageEntries[] = \
	{ \

#define DT_BEGIN_MESSAGE_MAP(theClass, baseClass, tempClass) \
	template <class tempClass> \
	const AFX_MSGMAP* PASCAL theClass##<tempClass>::_GetBaseMessageMap() \
		{ return &baseClass##<tempClass>::messageMap; } \
	template <class tempClass> \
	const AFX_MSGMAP* theClass##<tempClass>::GetMessageMap() const \
		{ return &theClass##<tempClass>::messageMap; } \
	template <class tempClass> \
	AFX_DATADEF const AFX_MSGMAP theClass##<tempClass>::messageMap = \
	{ &theClass##<tempClass>::_GetBaseMessageMap, &theClass##<tempClass>::_messageEntries[0] }; \
	template <class tempClass> \
	const AFX_MSGMAP_ENTRY theClass##<tempClass>::_messageEntries[] = \
	{ \

#else
#define TWND_BEGIN_MESSAGE_MAP(theClass, baseClass) \
	template <class baseClass> \
	const AFX_MSGMAP* theClass##<baseClass>::GetMessageMap() const \
		{ return &theClass##<baseClass>::messageMap; } \
	template <class baseClass> \
	AFX_DATADEF const AFX_MSGMAP theClass##<baseClass>::messageMap = \
	{ &baseClass::messageMap, &theClass##<baseClass>::_messageEntries[0] }; \
	template <class baseClass> \
	const AFX_MSGMAP_ENTRY theClass##<baseClass>::_messageEntries[] = \
	{ \

#define DT_BEGIN_MESSAGE_MAP(theClass, baseClass, tempClass) \
	template <class tempClass> \
	const AFX_MSGMAP* theClass##<tempClass>::GetMessageMap() const \
		{ return &theClass##<tempClass>::messageMap; } \
	template <class tempClass> \
	AFX_DATADEF const AFX_MSGMAP theClass##<tempClass>::messageMap = \
	{ &baseClass##<tempClass>::messageMap, &theClass##<tempClass>::_messageEntries[0] }; \
	template <class tempClass> \
	const AFX_MSGMAP_ENTRY theClass##<tempClass>::_messageEntries[] = \
	{ \

#endif


template <class TWnd>
class CTPropertiesDlg : public TWnd
{
protected:
	enum EActionEnum
	{
		PROPERTIES_ACTION_EMPTY = 0,
		PROPERTIES_ACTION_TEXT,
		PROPERTIES_ACTION_COLOR,
		PROPERTIES_ACTION_FONT,
	};
// Construction
public:
	CTPropertiesDlg(UINT nIDTemplate);   // standard constructor

public:
	CTreeCursor & AddColor(CTreeCursor &node,DWORD dwData,LPCSTR szNodeText,COLORREF color,LPCSTR szText = NULL);
	CTreeCursor & AddText(CTreeCursor &node,DWORD dwData,LPCSTR szNodeText,long properties,LPCSTR szText = NULL);
	CTreeCursor & AddText(CTreeCursor &node,DWORD dwData,LPCSTR szNodeText,LPCSTR properties,LPCSTR szText = NULL);
	CTreeCursor & AddFont(CTreeCursor &node,DWORD dwData,LPCSTR szNodeText,LPCSTR properties,LPCSTR szText = NULL);

	CTreeCursor & AddColor(CTreeCursor &node,DWORD dwData,UINT id,COLORREF color);
	CTreeCursor & AddText(CTreeCursor &node,DWORD dwData,UINT id,long properties);
	CTreeCursor & AddText(CTreeCursor &node,DWORD dwData,UINT id,LPCSTR properties);
	CTreeCursor & AddFont(CTreeCursor &node,DWORD dwData,UINT id,LPCSTR properties);

	void GetColor(DWORD index,COLORREF &color);
	void GetText(DWORD index,CString &text);
	void GetText(DWORD index,LPSTR text,int size);
	void GetText(DWORD index,long &text);

public:

// Dialog Data
	//{{AFX_DATA(CTPropertiesDlg)
	enum { IDD = IDD_PROPERTIES_DIALOG };
	CColourPicker	m_ColourPicker;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPropertiesTreeCtrl m_TreeCtrl;

	CString m_NotifyText;
	CString m_NotifyColor;
	CString m_NotifyFont;

	CMap<void *, void *, CString, CString &> m_NotifyTextAssociation;

	// Generated message map functions
	//{{AFX_MSG(CTPropertiesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangePropertiesEdit();
	afx_msg void OnSelChangePropertiesList();
	afx_msg void OnSelChangedPropertiesTreeStatic(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnApplyNow();
	//}}AFX_MSG
	afx_msg LRESULT OnSelEndOK(WPARAM wParam = 0, LPARAM lParam = 0);
	DECLARE_MESSAGE_MAP()

protected:
	virtual void OnNotifyText(CTreeCursor &cursor);
	virtual void OnNotifyFont(CTreeCursor &cursor);
	virtual void OnNotifyColor(CTreeCursor &cursor);
	virtual void OnNotifyApply(BOOL bEnable);

private:
	BOOL m_IsDisableApplyNotify;

	void HideControls();
	void ShowControl(UINT controlId,BOOL bShow);
	void ShowControls(UINT textId,UINT controlId);

	void AddTextAssociation(CTreeCursor &cursor,LPCSTR szText,LPCSTR szDefText);
	void SetTextAssociation(CTreeCursor &cursor);


	static int CALLBACK FontEnumProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, 
		int FontType, CWnd* pWnd );

};


/////////////////////////////////////////////////////////////////////////////
// CTPropertiesDlg dialog

template <class TWnd>
CTPropertiesDlg<TWnd>::CTPropertiesDlg(UINT nIDTemplate)
	: TWnd(nIDTemplate)
{
	//{{AFX_DATA_INIT(CTPropertiesDlg)
	//}}AFX_DATA_INIT

	m_NotifyText = "Enter text";
	m_NotifyColor = "Choose color";
	m_NotifyFont = "Choose font";

	m_IsDisableApplyNotify = FALSE;
}


template <class TWnd>
void CTPropertiesDlg<TWnd>::DoDataExchange(CDataExchange* pDX)
{
	TWnd::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPropertiesDlg)
	DDX_Control(pDX, IDC_PROPERTIES_COMBO, m_ColourPicker);
	//}}AFX_DATA_MAP
}


TWND_BEGIN_MESSAGE_MAP(CTPropertiesDlg, TWnd)
	//{{AFX_MSG_MAP(CTPropertiesDlg)
	ON_EN_CHANGE(IDC_PROPERTIES_EDIT, OnChangePropertiesEdit)
	ON_CBN_SELCHANGE(IDC_PROPERTIES_LIST, OnSelChangePropertiesList)
	ON_NOTIFY(TVN_SELCHANGED, IDC_PROPERTIES_TREE_STATIC, OnSelChangedPropertiesTreeStatic)
	ON_BN_CLICKED(ID_APPLY_NOW, OnApplyNow)
	//}}AFX_MSG_MAP
    ON_MESSAGE(CPN_SELENDOK,     OnSelEndOK)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPropertiesDlg message handlers

template <class TWnd>
int CALLBACK CTPropertiesDlg<TWnd>::FontEnumProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, 
		int FontType, CWnd* pWnd)
{
	lpntme,FontType;

	CComboBox *pComboBox = (CComboBox *)pWnd;

	if(pComboBox->FindStringExact(0,(LPCTSTR)lpelfe->elfFullName) == CB_ERR )
	{
		pComboBox->AddString((LPCTSTR)lpelfe->elfFullName);
	}
 	return 1;
}

template <class TWnd>
BOOL CTPropertiesDlg<TWnd>::OnInitDialog() 
{
	TWnd::OnInitDialog();
	
	// TODO: Add extra initialization here

	CWindowDC dc(this);
	LOGFONT logfont;

	logfont.lfCharSet = DEFAULT_CHARSET;
	logfont.lfFaceName[0] = '\0';
	logfont.lfPitchAndFamily = 0;

	EnumFontFamiliesEx( dc.m_hDC, &logfont, (FONTENUMPROC)FontEnumProc, 
			(LPARAM) GetDlgItem(IDC_PROPERTIES_LIST), 0 );


	HideControls();
	m_ColourPicker.SetTrackSelection(TRUE);
	m_TreeCtrl.SubclassDlgItem(IDC_PROPERTIES_TREE_STATIC,this);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}





/////////////////////// Notification ///////////////////////////
template <class TWnd>
void CTPropertiesDlg<TWnd>::OnNotifyText(CTreeCursor &cursor)
{
	CString str;

	HideControls();
	ShowControls(IDC_PROPERTIES_STATIC,IDC_PROPERTIES_EDIT);

	SetTextAssociation(cursor);

	m_IsDisableApplyNotify = TRUE;
	m_TreeCtrl.GetProperties(cursor,str);
	GetDlgItem(IDC_PROPERTIES_EDIT)->SetWindowText(str);
	m_IsDisableApplyNotify = FALSE;
}

template <class TWnd>
void CTPropertiesDlg<TWnd>::OnNotifyFont(CTreeCursor &cursor)
{
	CString str;

	HideControls();
	ShowControls(IDC_PROPERTIES_STATIC,IDC_PROPERTIES_LIST);

	SetTextAssociation(cursor);

	m_TreeCtrl.GetProperties(cursor,str);
	CComboBox *pComboBox = (CComboBox *)GetDlgItem(IDC_PROPERTIES_LIST);
	int index = pComboBox->FindStringExact(0,str);
	if(index != CB_ERR)
	{
		pComboBox->SetCurSel(index);
	}
}

template <class TWnd>
void CTPropertiesDlg<TWnd>::OnNotifyColor(CTreeCursor &cursor)
{
	COLORREF colorText, color;

	HideControls();
	ShowControls(IDC_PROPERTIES_STATIC,IDC_PROPERTIES_COMBO);

	SetTextAssociation(cursor);

	m_TreeCtrl.GetProperties(cursor,colorText,color);
	m_ColourPicker.SetBkColour(color);

}

template <class TWnd>
void CTPropertiesDlg<TWnd>::OnNotifyApply(BOOL bEnable)
{
	if(m_IsDisableApplyNotify)
		return;

	CWnd *pWnd;

	pWnd = GetDlgItem(ID_APPLY_NOW);
	if(pWnd != NULL)
	{
		pWnd->EnableWindow(bEnable);
	}

	pWnd = GetParent();
	if(pWnd != NULL && bEnable)
	{
		pWnd->PostMessage(PSM_CHANGED, (WPARAM)GetSafeHwnd());
	}
}

/////////////////// Controls ///////////////
template <class TWnd>
void CTPropertiesDlg<TWnd>::ShowControls(UINT textId,UINT controlId)
{
	ShowControl(textId,TRUE);
	ShowControl(controlId,TRUE);
}

template <class TWnd>
void CTPropertiesDlg<TWnd>::ShowControl(UINT controlId,BOOL bShow)
{
	CWnd *pWnd = GetDlgItem(controlId);

	if(pWnd == NULL)
		return;

	if(bShow == FALSE)
	{
		pWnd->ShowWindow(SW_HIDE);
		pWnd->EnableWindow(FALSE);
	}
	else
	{
		pWnd->EnableWindow(TRUE);
		pWnd->ShowWindow(SW_SHOW);
	}
}

template <class TWnd>
void CTPropertiesDlg<TWnd>::HideControls()
{
	static UINT cId [] = 
	{
		IDC_PROPERTIES_COMBO,
		IDC_PROPERTIES_LIST,
		IDC_PROPERTIES_EDIT,
		IDC_PROPERTIES_STATIC,
	};
	int i;

	for(i = 0;i < CountOf(cId);i ++)
	{
		ShowControl(cId[i],FALSE);
	}

}

////////////////////// properties ////////////////////////
template <class TWnd>
void CTPropertiesDlg<TWnd>::SetTextAssociation(CTreeCursor &cursor)
{
	CString str;
	if(m_NotifyTextAssociation.Lookup(cursor,str))
	{
		GetDlgItem(IDC_PROPERTIES_STATIC)->SetWindowText(str);
	}
}


template <class TWnd>
void CTPropertiesDlg<TWnd>::AddTextAssociation(CTreeCursor &cursor,LPCSTR szText,LPCSTR szDefText)
{
	CString str;

	if(szText == NULL)
		str = szDefText;
	else 
		str = szText;
	m_NotifyTextAssociation.SetAt(cursor,str);
}


template <class TWnd>
CTreeCursor &CTPropertiesDlg<TWnd>::AddColor(CTreeCursor &node,
									   DWORD dwData,
									   LPCSTR szNodeText,
									   COLORREF color,
									   LPCSTR szText)
{
	CTreeCursor cursor;

	cursor = node.AddTail(szNodeText);
	cursor.SetData(dwData);
	m_TreeCtrl.AddProperties(cursor,szNodeText,COLOR_TEXT,PROPERTIES_ACTION_COLOR,(DWORD)(-1),color);

	AddTextAssociation(cursor,szText,m_NotifyColor);

	return cursor;
}

template <class TWnd>
CTreeCursor &CTPropertiesDlg<TWnd>::AddText(CTreeCursor &node,
									  DWORD dwData,
									  LPCSTR szNodeText,
									  long properties,
									  LPCSTR szText)
{
	CTreeCursor cursor;

	cursor = node.AddTail(szNodeText);
	cursor.SetData(dwData);
	m_TreeCtrl.AddProperties(cursor,szNodeText,properties,PROPERTIES_ACTION_TEXT);

	AddTextAssociation(cursor,szText,m_NotifyText);

	return cursor;
}

template <class TWnd>
CTreeCursor &CTPropertiesDlg<TWnd>::AddText(CTreeCursor &node,
									  DWORD dwData,
									  LPCSTR szNodeText,
									  LPCSTR properties,
									  LPCSTR szText)
{
	CTreeCursor cursor;

	cursor = node.AddTail(szNodeText);
	cursor.SetData(dwData);
	m_TreeCtrl.AddProperties(cursor,szNodeText,properties,PROPERTIES_ACTION_TEXT);

	AddTextAssociation(cursor,szText,m_NotifyText);

	return cursor;
}

template <class TWnd>
CTreeCursor &CTPropertiesDlg<TWnd>::AddFont(CTreeCursor &node,
									  DWORD dwData,
									  LPCSTR szNodeText,
									  LPCSTR properties,
									  LPCSTR szText)
{
	CTreeCursor cursor;

	cursor = node.AddTail(szNodeText);
	cursor.SetData(dwData);
	m_TreeCtrl.AddProperties(cursor,szNodeText,properties,PROPERTIES_ACTION_FONT);

	AddTextAssociation(cursor,szText,m_NotifyFont);

	return cursor;
}


template <class TWnd>
void CTPropertiesDlg<TWnd>::GetColor(DWORD index,COLORREF &color)
{
	COLORREF ha;
	m_TreeCtrl.GetProperties(index,ha,color);
}

template <class TWnd>
void CTPropertiesDlg<TWnd>::GetText(DWORD index,CString &text)
{
	m_TreeCtrl.GetProperties(index,text);
}

template <class TWnd>
void CTPropertiesDlg<TWnd>::GetText(DWORD index,LPSTR text,int size)
{
	m_TreeCtrl.GetProperties(index,text,size);
}

template <class TWnd>
void CTPropertiesDlg<TWnd>::GetText(DWORD index,long &text)
{
	m_TreeCtrl.GetProperties(index,text);
}

////////////////////// handlers ////////////////////
template <class TWnd>
void CTPropertiesDlg<TWnd>::OnChangePropertiesEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here

	CString str;
	CTreeCursor cursor = m_TreeCtrl.GetSelectedItem();
	CWnd *pWnd = GetDlgItem(IDC_PROPERTIES_EDIT);
	
	pWnd->GetWindowText(str);
	m_TreeCtrl.ModifyProperties(cursor,str);
	OnNotifyApply(TRUE);
}

template <class TWnd>
void CTPropertiesDlg<TWnd>::OnSelChangePropertiesList() 
{
	// TODO: Add your control notification handler code here
	int index;
	CString str;
	CTreeCursor cursor = m_TreeCtrl.GetSelectedItem();
	CComboBox *pComboBox = (CComboBox *)GetDlgItem(IDC_PROPERTIES_LIST);
	
	index = pComboBox->GetCurSel();
	pComboBox->GetLBText(index,str);
	m_TreeCtrl.ModifyProperties(cursor,str);
	OnNotifyApply(TRUE);
}

template <class TWnd>
LRESULT CTPropertiesDlg<TWnd>::OnSelEndOK(WPARAM wParam, LPARAM lParam)
{
	wParam,lParam;

	CTreeCursor cursor = m_TreeCtrl.GetSelectedItem();
	COLORREF color = m_ColourPicker.GetBkColour();
	
	m_TreeCtrl.ModifyProperties(cursor,(DWORD)(-1),color);
	OnNotifyApply(TRUE);
	
	return NULL;
}

template <class TWnd>
void CTPropertiesDlg<TWnd>::OnSelChangedPropertiesTreeStatic(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	CTreeCursor cursor = m_TreeCtrl.GetSelectedItem();
	long action = 0;
	
	if(m_TreeCtrl.GetAction(cursor,action))
	{
		switch(action)
		{
		case PROPERTIES_ACTION_EMPTY:
			HideControls();
			break;
		case PROPERTIES_ACTION_TEXT:
			OnNotifyText(cursor);
			break;
		case PROPERTIES_ACTION_COLOR:
			OnNotifyColor(cursor);
			break;
		case PROPERTIES_ACTION_FONT:
			OnNotifyFont(cursor);
			break;
		default:
			ASSERT(0);
		}
	}
	else
	{
		HideControls();
	}
		
	
	*pResult = 0;
}

template <class TWnd>
void CTPropertiesDlg<TWnd>::OnApplyNow() 
{
	// TODO: Add your control notification handler code here
	OnNotifyApply(FALSE);
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif 
