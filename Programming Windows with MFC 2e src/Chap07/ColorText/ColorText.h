#define IDC_RED         100
#define IDC_GREEN       101
#define IDC_BLUE        102

class CColorStatic : public CStatic
{
protected:
    COLORREF m_clrText;
    COLORREF m_clrBack;
    CBrush m_brBkgnd;

public:
    CColorStatic ();
    void SetTextColor (COLORREF clrText);
    void SetBkColor (COLORREF clrBack);

protected:
    afx_msg HBRUSH CtlColor (CDC* pDC, UINT nCtlColor);
    DECLARE_MESSAGE_MAP ()
};

class CMyApp : public CWinApp
{
public:
    virtual BOOL InitInstance ();
};

class CMainWindow : public CFrameWnd
{
protected:
    int m_cxChar;
    int m_cyChar;
    CFont m_font;

    CColorStatic m_wndText;
    CButton m_wndRadioButtonRed;
    CButton m_wndRadioButtonGreen;
    CButton m_wndRadioButtonBlue;
    CButton m_wndGroupBox1;
    CButton m_wndGroupBox2;

public:
    CMainWindow ();

protected:
    afx_msg int OnCreate (LPCREATESTRUCT lpcs);
    afx_msg void OnRedButtonClicked ();
    afx_msg void OnGreenButtonClicked ();
    afx_msg void OnBlueButtonClicked ();

    DECLARE_MESSAGE_MAP ()
};
