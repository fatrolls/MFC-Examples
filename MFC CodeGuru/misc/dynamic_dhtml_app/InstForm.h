// InstForm.h: interface for the InstForm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INSTFORM_H__3C1A9A65_E1BD_11D1_ABF7_F7483CE66979__INCLUDED_)
#define AFX_INSTFORM_H__3C1A9A65_E1BD_11D1_ABF7_F7483CE66979__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "InstructorSet.h"

class CInstForm : public CHTMLForm  
{
public:
	void DisplayData();
	CInstForm();
	virtual ~CInstForm();

protected:
	virtual void ExecuteCmd(LPCTSTR lpszCmd);
	virtual void OnLoad(IHTMLElementCollection* pCollection);
	IHTMLInputTextElement* m_pInst_Id;
	IHTMLInputTextElement* m_pInst_Name;
	IHTMLInputTextElement* m_pInst_Room;
	CInstructorSet m_InstSet;
};

#endif // !defined(AFX_INSTFORM_H__3C1A9A65_E1BD_11D1_ABF7_F7483CE66979__INCLUDED_)
