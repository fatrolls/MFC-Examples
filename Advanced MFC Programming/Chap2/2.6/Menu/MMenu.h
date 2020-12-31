#if !defined(__MMENU_H__)
#define __MMENU_H__

#define MENUTYPE_SMILE		0
#define MENUTYPE_QUESTION	1

class MCMenu : public CMenu
{
protected:
	CBitmap m_bmpQuestion;
	CBitmap m_bmpQuestionSel;
	CBitmap m_bmpSmile;
	CBitmap m_bmpSmileSel;

public:
	MCMenu();
	virtual ~MCMenu();
	virtual void MeasureItem(LPMEASUREITEMSTRUCT);
	virtual void DrawItem(LPDRAWITEMSTRUCT);
};

#endif