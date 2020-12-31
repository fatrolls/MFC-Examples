#if !defined(AFX_BUTTON_H__C2EEA5C1_29BE_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_BUTTON_H__C2EEA5C1_29BE_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CColorButton : public CButton
{
public:
	void SetPalIndex(int nIndex){m_nPalIndex=nIndex;}
	int GetPalIndex(){return m_nPalIndex;}
	CColorButton();
	//{{AFX_VIRTUAL(CColorButton)
	//}}AFX_VIRTUAL

public:
	virtual ~CColorButton();

protected:
	int m_nPalIndex;
	void DrawItem(LPDRAWITEMSTRUCT);
	//{{AFX_MSG(CColorButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CFBButton : public CButton
{
public:
	CFBButton();

	//{{AFX_VIRTUAL(CFBButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

public:
	virtual ~CFBButton();

protected:
	//{{AFX_MSG(CFBButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_BUTTON_H__C2EEA5C1_29BE_11D1_9C9A_444553540000__INCLUDED_)
