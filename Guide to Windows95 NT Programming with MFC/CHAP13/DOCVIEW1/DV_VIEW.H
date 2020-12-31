///////////////////////////////////////////////////////////////////
// Header  : DV_VIEW.H
//
// Purpose : Interface for the CDocView1View class.
//
// Author  : Rob McGregor - rob_mcgregor@compuserve.com
//
// Date    : 05-12-96
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// The CDocView1View view class

class CDocView1View : public CView
{
protected:
	CDocView1View();
	DECLARE_DYNCREATE(CDocView1View)

// Attributes
public:
   CDocView1Doc* GetDocument();
   
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view

// Implementation
public:
	virtual ~CDocView1View();

   // Message handlers
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

   DECLARE_MESSAGE_MAP();
};       

inline CDocView1Doc* CDocView1View::GetDocument()
{ 
   return (CDocView1Doc*)m_pDocument; 
}

///////////////////////////////////////////////////////////////////
  
