
#pragma once
#include "afxwin.h"

// Dialog to enter properties of a <TABLE>

class CTableProperties : public CDialog
{
	DECLARE_DYNCREATE(CTableProperties)

public:
	CTableProperties(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTableProperties();

	CString ms_BorderWidth;
	CString ms_BorderColor;
	CString ms_BackgColor;
	CString ms_CellPadding;
	CString ms_CellSpacing;
	CString ms_Width;
	CString ms_Height;
	UINT    mu32_Rules;

	enum { IDD = IDD_TABLE_PROP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	CComboBox mCtrl_ComboRules;
};
