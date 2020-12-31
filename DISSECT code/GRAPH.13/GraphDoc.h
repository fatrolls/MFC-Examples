// GraphDoc.h : interface of the CGraphDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CGraphDoc : public CDocument
{
protected: // create from serialization only
        CGraphDoc();
        DECLARE_DYNCREATE(CGraphDoc)

// Attributes
public:
        CArray<int,int> m_intArray;

// Operations
public:
        void SetValue(int i0, int i1, int i2, int i3, int i4,
                      int i5, int i6, int i7, int i8, int i9);
// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CGraphDoc)
        public:
        virtual BOOL OnNewDocument();
        virtual void Serialize(CArchive& ar);
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CGraphDoc();
#ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
        //{{AFX_MSG(CGraphDoc)
        afx_msg void OnGraphData1();
        afx_msg void OnGraphData2();
        afx_msg void OnGraphData3();
        afx_msg void OnUpdateGraphData1(CCmdUI* pCmdUI);
        afx_msg void OnUpdateGraphData2(CCmdUI* pCmdUI);
        afx_msg void OnUpdateGraphData3(CCmdUI* pCmdUI);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

