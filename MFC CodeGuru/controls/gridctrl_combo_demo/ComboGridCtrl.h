// ComboGridCtrl.h: interface for the CComboGridCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMBOGRIDCTRL_H__EC89C9C0_01A5_11D2_AB4A_5C7377000000__INCLUDED_)
#define AFX_COMBOGRIDCTRL_H__EC89C9C0_01A5_11D2_AB4A_5C7377000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GridCtrl.h"

class CComboGridCtrl : public CGridCtrl  
{
public:
	CComboGridCtrl();
	virtual ~CComboGridCtrl();

protected:
    virtual void OnEditCell(int nRow, int nCol, UINT nChar);

    //{{AFX_MSG(CComboGridCtrl)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_COMBOGRIDCTRL_H__EC89C9C0_01A5_11D2_AB4A_5C7377000000__INCLUDED_)
