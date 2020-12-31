#define EX 1
#define OH 2

class CMyApp : public CWinApp
{
public:
    virtual BOOL InitInstance ();
};

class CMainWindow : public CWnd
{
protected:
    static const CRect m_rcSquares[9];	// Grid coordinates
    int m_nGameGrid[9];			// Grid contents
    int m_nNextChar;			// Next character (EX or OH)

    int GetRectID (CPoint point);
    void DrawBoard (CDC* pDC);
    void DrawX (CDC* pDC, int nPos);
    void DrawO (CDC* pDC, int nPos);
    void ResetGame ();
    void CheckForGameOver ();
    int IsWinner ();
    BOOL IsDraw ();

public:
    CMainWindow ();

protected:
    virtual void PostNcDestroy ();

    afx_msg void OnPaint ();
    afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk (UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown (UINT nFlags, CPoint point);

    DECLARE_MESSAGE_MAP ()
};
