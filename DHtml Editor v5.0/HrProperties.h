
#pragma once
#include "afxwin.h"

// Dialog to enter properties of a <HR> (horizontal line)

class CHrProperties : public CDialog
{
	DECLARE_DYNCREATE(CHrProperties)

public:
	CHrProperties(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHrProperties();

	enum { IDD = IDD_HR_PROP };

	CString ms_Width;
	CString ms_Color;
	CString ms_Size;
	int   ms32_Shade;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
