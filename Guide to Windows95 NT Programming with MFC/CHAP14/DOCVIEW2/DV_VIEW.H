///////////////////////////////////////////////////////////////////
// Header  : DV_VIEW.H
//
// Purpose : Interface for the CDocView2View class.
//
// Author  : Rob McGregor - rob_mcgregor@compuserve.com
//
// Date    : 05-12-96
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// The CDocView2View view class

class CDocView2View : public CView
{
protected:
	CDocView2View();
	DECLARE_DYNCREATE(CDocView2View)

// Attributes
public:
   CDocView2Doc* GetDocument();
   
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view

// Implementation
public:
	virtual ~CDocView2View();

   virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
   void OnLButtonDown(UINT nFlags, CPoint point);

   DECLARE_MESSAGE_MAP();
};       

inline CDocView2Doc* CDocView2View::GetDocument()
{ 
   return (CDocView2Doc*)m_pDocument; 
}

///////////////////////////////////////////////////////////////////
  
