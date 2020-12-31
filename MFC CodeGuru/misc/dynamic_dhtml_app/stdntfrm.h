// stdntfrm.h: interface for the CStudentForm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STDNTFRM_H__B0992847_E20B_11D1_ABF7_44455354616F__INCLUDED_)
#define AFX_STDNTFRM_H__B0992847_E20B_11D1_ABF7_44455354616F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "StudentSet.h"

class CStudentForm : public CHTMLForm  
{
public:
	CStudentForm();
	virtual ~CStudentForm();
	void DisplayData();

protected:
	virtual void ExecuteCmd(LPCTSTR lpszCmd);
	virtual void OnLoad(IHTMLElementCollection* pCollection);
	IHTMLInputTextElement* m_pStudentID;
	IHTMLInputTextElement* m_pName;
	IHTMLInputTextElement* m_pGradYear;
	CStudentSet m_StudentSet;

};

#endif // !defined(AFX_STDNTFRM_H__B0992847_E20B_11D1_ABF7_44455354616F__INCLUDED_)
