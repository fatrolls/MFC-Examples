// CaptionPainterEx.h: interface for the CCaptionPainterEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAPTIONPAINTEREX_H__BDB658D3_C3BF_11D1_9AA6_0060B017334D__INCLUDED_)
#define AFX_CAPTIONPAINTEREX_H__BDB658D3_C3BF_11D1_9AA6_0060B017334D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PaintCap.h"

class CCaptionPainterEx : public CCaptionPainter  
{
public:
	CCaptionPainterEx();
	virtual ~CCaptionPainterEx();

	void PaintCaption(BOOL bActive, const PAINTCAP* pc);

	//String format: App name | doc name
	void TitleText(CString title){m_Title = title;}
	void TitleText(const CString *title = NULL){m_pTitle = title;}

protected:
	void CreateFonts();

	CFont		m_fontCaption;			// normal system font for active caption
	CFont		m_fontAcme;				// "ACME" company font (same active/inactive)

	CString			m_Title;
	const CString*	m_pTitle;
};

#endif // !defined(AFX_CAPTIONPAINTEREX_H__BDB658D3_C3BF_11D1_9AA6_0060B017334D__INCLUDED_)
