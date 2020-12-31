class CMyApp : public CWinApp
{
public:
    virtual BOOL InitInstance ();
};

class CIconListBox : public CListBox
{
public:
    virtual BOOL PreCreateWindow (CREATESTRUCT& cs);
    virtual void MeasureItem (LPMEASUREITEMSTRUCT lpmis);
    virtual void DrawItem (LPDRAWITEMSTRUCT lpdis);
    int AddIcon (HICON hIcon);
    void ProjectImage (CDC* pDC, LPRECT pRect, COLORREF clrBackColor);
};

class CMainWindow : public CWnd
{
protected:
    int m_cxChar;
    int m_cyChar;

    CFont m_font;
    CRect m_rcImage;

    CButton m_wndGroupBox;
    CIconListBox m_wndIconListBox;
    CStatic m_wndLabel;

public:
    CMainWindow ();

protected:
    virtual void PostNcDestroy ();

    afx_msg int OnCreate (LPCREATESTRUCT lpcs);
    afx_msg void OnPaint ();
    afx_msg void OnSetFocus (CWnd* pWnd);
    afx_msg void OnDropFiles (HDROP hDropInfo);
    afx_msg void OnSelChange ();

    DECLARE_MESSAGE_MAP ()
};
