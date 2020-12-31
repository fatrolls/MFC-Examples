// ECommentPane.h: interface for the ECommentPane class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_ECOMMENTPANE_H__B7BA3966_D957_4AC6_9CA2_38975CBE8B42__INCLUDED_
#define AFX_ECOMMENTPANE_H__B7BA3966_D957_4AC6_9CA2_38975CBE8B42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHoverButton;
class EPropWnd;

class ECommentPane : public CWnd
{

private:

//	int m_nDesign;	//0=hoverbutton on left, 1=single large button

public:

	EPropWnd* m_pPropWnd;

	class ICommentHost
	{
	public:
		virtual CString GetCurrentComment( CString& sObjectName )
		{
			return "";
		}
	};

	DECLARE_MESSAGE_MAP();
	DECLARE_DYNCREATE(ECommentPane);

protected:

	ICommentHost* m_pCommentHost;
//	CHoverButton* m_pHoverButton;

//	CString m_sComment;
//	bool m_bMinimized;



public:

	ECommentPane();
	virtual ~ECommentPane();

protected:

	//{{AFX_MSG(ECommentPane)
	afx_msg void OnPaint();
//	afx_msg void OnMinimizeButton();
	afx_msg void OnLButtonUp( UINT, CPoint );
	//}}AFX_MSG

public:

//	virtual BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

//	void SetComment( const CString& sComment );
	void SetCommentHost( ICommentHost* pCommentHost );

	
	int GetHeight( int nColumnWidth );
};

#endif // !defined(AFX_ECOMMENTPANE_H__B7BA3966_D957_4AC6_9CA2_38975CBE8B42__INCLUDED_)
