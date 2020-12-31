// BarView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBarView view

class CBarView : public CView
{
protected:
        CBarView();           // protected constructor used by dynamic creation
        DECLARE_DYNCREATE(CBarView)

// Attributes
public:

// Operations
public:

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CBarView)
        protected:
        virtual void OnDraw(CDC* pDC);      // overridden to draw this view
        //}}AFX_VIRTUAL

// Implementation
protected:
        virtual ~CBarView();
#ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
#endif

        // Generated message map functions
protected:
        //{{AFX_MSG(CBarView)
                // NOTE - the ClassWizard will add and remove member functions here.
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
