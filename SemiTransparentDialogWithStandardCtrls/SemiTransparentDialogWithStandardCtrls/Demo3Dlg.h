#pragma once


// CDemo3Dlg dialog
#include "./Src/ImgDialogBase.h"
#include "afxcmn.h"

class CDemo3Dlg : public CImgDialogBase
{
	DECLARE_DYNAMIC(CDemo3Dlg)

public:
	CDemo3Dlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDemo3Dlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	CTreeCtrl m_ctlTree;
	virtual BOOL OnInitDialog();
};
