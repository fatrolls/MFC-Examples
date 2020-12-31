// TLabelComboBox.h: interface for the CTLabelList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLABELCOMBOBOX_H__D6C397A2_ECEA_11D1_8540_9B1C6856D236__INCLUDED_)
#define AFX_TLABELCOMBOBOX_H__D6C397A2_ECEA_11D1_8540_9B1C6856D236__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TLabelEdit.h"

class CTLabelList : public CTLabelEdit  
{
public:
	// Overidable
	virtual CWnd* GetEditControl() = NULL;
	// Others..
	virtual BOOL IsEditDestroyable();
	virtual void ShowEdit();
	virtual void Attach(HWND hwnd);
	void Attach(CWnd* pWnd);
	virtual CWnd* GetWindowControl();
	CTLabelList();
	virtual ~CTLabelList();
private:
	CString m_sSeparator;
	HWND m_hWndList;
};

#endif // !defined(AFX_TLABELCOMBOBOX_H__D6C397A2_ECEA_11D1_8540_9B1C6856D236__INCLUDED_)
