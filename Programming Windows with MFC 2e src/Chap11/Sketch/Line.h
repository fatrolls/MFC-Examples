#if !defined(AFX_LINE_H__1260AFD5_9CAC_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_LINE_H__1260AFD5_9CAC_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Line.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLine command target

class CLine : public CCmdTarget
{
	DECLARE_SERIAL (CLine)

	CLine();           // protected constructor used by dynamic creation
	CLine (POINT from, POINT to);

// Attributes
public:

// Operations
public:
	void Draw (CDC* pDC);
	virtual ~CLine();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLine)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPoint m_ptFrom;
	CPoint m_ptTo;

	// Generated message map functions
	//{{AFX_MSG(CLine)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINE_H__1260AFD5_9CAC_11D2_8E53_006008A82731__INCLUDED_)
