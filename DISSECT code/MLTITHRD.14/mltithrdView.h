// mltithrdView.h : interface of the CMltithrdView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MLTITHRDVIEW_H__3C3D7AD2_B569_11D0_968D_444553540000__INCLUDED_)
#define AFX_MLTITHRDVIEW_H__3C3D7AD2_B569_11D0_968D_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMltithrdView : public CView
{
protected: // create from serialization only
        CMltithrdView();
        DECLARE_DYNCREATE(CMltithrdView)

// Attributes
public:
        CMltithrdDoc* GetDocument();
        static UINT ThreadFunc(LPVOID);

// Operations
public:

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CMltithrdView)
        public:
        virtual void OnDraw(CDC* pDC);  // overridden to draw this view
        virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
        protected:
        virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
        virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
        virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CMltithrdView();
#ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
        //{{AFX_MSG(CMltithrdView)
                // NOTE - the ClassWizard will add and remove member functions here.
                //    DO NOT EDIT what you see in these blocks of generated code !
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mltithrdView.cpp
inline CMltithrdDoc* CMltithrdView::GetDocument()
   { return (CMltithrdDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLTITHRDVIEW_H__3C3D7AD2_B569_11D0_968D_444553540000__INCLUDED_)
