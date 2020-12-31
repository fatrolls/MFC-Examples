#pragma once


// CDemo2Dlg dialog
#include "afxcmn.h"
#include "./Src/ImgDialogBase.h"

class CDemo2Dlg : public CImgDialogBase
{
	DECLARE_DYNAMIC(CDemo2Dlg)

public:
	CDemo2Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDemo2Dlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CListCtrl m_lstDemo;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNcDestroy();
};
