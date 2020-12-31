// TLabelComboBox.h: interface for the CTLabelComboBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLABELCOMBOBOX_H__D6C397A4_ECEA_11D1_8540_9B1C6856D236__INCLUDED_)
#define AFX_TLABELCOMBOBOX_H__D6C397A4_ECEA_11D1_8540_9B1C6856D236__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TLabelList.h"

class CTLabelComboBox : public CTLabelList  
{
public:
	virtual CWnd* GetEditControl();
	CTLabelComboBox();
	virtual ~CTLabelComboBox();

};

#endif // !defined(AFX_TLABELCOMBOBOX_H__D6C397A4_ECEA_11D1_8540_9B1C6856D236__INCLUDED_)
