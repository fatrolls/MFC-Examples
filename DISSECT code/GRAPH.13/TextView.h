// TextView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextView view

class CTextView : public CView
{
protected:
        CTextView();           // protected constructor used by dynamic creation
        DECLARE_DYNCREATE(CTextView)

// Attributes
public:

// Operations
public:

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CTextView)
        protected:
        virtual void OnDraw(CDC* pDC);      // overridden to draw this view
        //}}AFX_VIRTUAL

// Implementation
protected:
        virtual ~CTextView();
#ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
#endif

        // Generated message map functions
protected:
        //{{AFX_MSG(CTextView)
                // NOTE - the ClassWizard will add and remove member functions here.
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
