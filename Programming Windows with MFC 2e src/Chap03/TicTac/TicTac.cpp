#include <afxwin.h>
#include "TicTac.h"

CMyApp myApp;

/////////////////////////////////////////////////////////////////////////
// CMyApp member functions

BOOL CMyApp::InitInstance ()
{
    m_pMainWnd = new CMainWindow;
    m_pMainWnd->ShowWindow (m_nCmdShow);
    m_pMainWnd->UpdateWindow ();
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// CMainWindow message map and member functions

BEGIN_MESSAGE_MAP (CMainWindow, CWnd)
    ON_WM_PAINT ()
    ON_WM_LBUTTONDOWN ()
    ON_WM_LBUTTONDBLCLK ()
    ON_WM_RBUTTONDOWN ()
END_MESSAGE_MAP ()

const CRect CMainWindow::m_rcSquares[9] = {
    CRect ( 16,  16, 112, 112),
    CRect (128,  16, 224, 112),
    CRect (240,  16, 336, 112),
    CRect ( 16, 128, 112, 224),
    CRect (128, 128, 224, 224),
    CRect (240, 128, 336, 224),
    CRect ( 16, 240, 112, 336),
    CRect (128, 240, 224, 336),
    CRect (240, 240, 336, 336)
};

CMainWindow::CMainWindow ()
{
    m_nNextChar = EX;
    ::ZeroMemory (m_nGameGrid, 9 * sizeof (int));

	//
	// Register a WNDCLASS.
	//
    CString strWndClass = AfxRegisterWndClass (
        CS_DBLCLKS,										// Class style
        AfxGetApp ()->LoadStandardCursor (IDC_ARROW),   // Class cursor
        (HBRUSH) (COLOR_3DFACE + 1),					// Background brush
        AfxGetApp ()->LoadStandardIcon (IDI_WINLOGO)	// Class icon
    );

	//
	// Create a window.
	//
    CreateEx (0, strWndClass, _T ("Tic-Tac-Toe"),
        WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL);

	//
	// Size the window.
	//
    CRect rect (0, 0, 352, 352);
    CalcWindowRect (&rect);

    SetWindowPos (NULL, 0, 0, rect.Width (), rect.Height (),
        SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);
}

void CMainWindow::PostNcDestroy ()
{
    delete this;
}

void CMainWindow::OnPaint ()
{
    CPaintDC dc (this);
    DrawBoard (&dc);    
}

void CMainWindow::OnLButtonDown (UINT nFlags, CPoint point)
{
	//
	// Do nothing if it's O's turn, if the click occurred outside the
	// tic-tac-toe grid, or if a nonempty square was clicked.
	//
    if (m_nNextChar != EX)
        return;

    int nPos = GetRectID (point);
    if ((nPos == -1) || (m_nGameGrid[nPos] != 0))
        return;

	//
	// Add an X to the game grid and toggle m_nNextChar.
	//
    m_nGameGrid[nPos] = EX;
    m_nNextChar = OH;

	//
	// Draw an X on the screen and see if either player has won.
	//
    CClientDC dc (this);
    DrawX (&dc, nPos);
    CheckForGameOver ();
}

void CMainWindow::OnRButtonDown (UINT nFlags, CPoint point)
{
	//
	// Do nothing if it's X's turn, if the click occurred outside the
	// tic-tac-toe grid, or if a nonempty square was clicked.
	//
    if (m_nNextChar != OH)
        return;

    int nPos = GetRectID (point);
    if ((nPos == -1) || (m_nGameGrid[nPos] != 0))
        return;

	//
	// Add an O to the game grid and toggle m_nNextChar.
	//
    m_nGameGrid[nPos] = OH;
    m_nNextChar = EX;

	//
	// Draw an O on the screen and see if either player has won.
	//
    CClientDC dc (this);
    DrawO (&dc, nPos);
    CheckForGameOver ();
}

void CMainWindow::OnLButtonDblClk (UINT nFlags, CPoint point)
{
	//
	// Reset the game if one of the thick black lines defining the game
	// grid is double-clicked with the left mouse button.
	//
    CClientDC dc (this);
    if (dc.GetPixel (point) == RGB (0, 0, 0))
        ResetGame ();
}

int CMainWindow::GetRectID (CPoint point)
{
	//
	// Hit-test each of the grid's nine squares and return a rectangle ID
	// (0-8) if (point.x, point.y) lies inside a square.
	//
    for (int i=0; i<9; i++) {
        if (m_rcSquares[i].PtInRect (point))
            return i;
    }
    return -1;
}

void CMainWindow::DrawBoard (CDC* pDC)
{
	//
	// Draw the lines that define the tic-tac-toe grid.
	//
    CPen pen (PS_SOLID, 16, RGB (0, 0, 0));
    CPen* pOldPen = pDC->SelectObject (&pen);

    pDC->MoveTo (120, 16);
    pDC->LineTo (120, 336);

    pDC->MoveTo (232, 16);
    pDC->LineTo (232, 336);

    pDC->MoveTo (16, 120);
    pDC->LineTo (336, 120);

    pDC->MoveTo (16, 232);
    pDC->LineTo (336, 232);

	//
	// Draw the Xs and Os.
	//
    for (int i=0; i<9; i++) {
        if (m_nGameGrid[i] == EX)
            DrawX (pDC, i);
        else if (m_nGameGrid[i] == OH)
            DrawO (pDC, i);
    }
    pDC->SelectObject (pOldPen);
}

void CMainWindow::DrawX (CDC* pDC, int nPos)
{
    CPen pen (PS_SOLID, 16, RGB (255, 0, 0));
    CPen* pOldPen = pDC->SelectObject (&pen);

    CRect rect = m_rcSquares[nPos];
    rect.DeflateRect (16, 16);
    pDC->MoveTo (rect.left, rect.top);
    pDC->LineTo (rect.right, rect.bottom);
    pDC->MoveTo (rect.left, rect.bottom);
    pDC->LineTo (rect.right, rect.top);

    pDC->SelectObject (pOldPen);
}

void CMainWindow::DrawO (CDC* pDC, int nPos)
{
    CPen pen (PS_SOLID, 16, RGB (0, 0, 255));
    CPen* pOldPen = pDC->SelectObject (&pen);
    pDC->SelectStockObject (NULL_BRUSH);

    CRect rect = m_rcSquares[nPos];
    rect.DeflateRect (16, 16);
    pDC->Ellipse (rect);

    pDC->SelectObject (pOldPen);
}

void CMainWindow::CheckForGameOver ()
{
    int nWinner;

	//
	// If the grid contains three consecutive Xs or Os, declare a winner
	// and start a new game.
	//
    if (nWinner = IsWinner ()) {
        CString string = (nWinner == EX) ?
            _T ("X wins!") : _T ("O wins!");
        MessageBox (string, _T ("Game Over"), MB_ICONEXCLAMATION | MB_OK);
        ResetGame ();
    }

	//
	// If the grid is full, declare a draw and start a new game.
	//
    else if (IsDraw ()) {
        MessageBox (_T ("It's a draw!"), _T ("Game Over"),
            MB_ICONEXCLAMATION | MB_OK);
        ResetGame ();
    }
}

int CMainWindow::IsWinner ()
{
    static int nPattern[8][3] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        0, 3, 6,
        1, 4, 7,
        2, 5, 8,
        0, 4, 8,
        2, 4, 6
    };

    for (int i=0; i<8; i++) {
        if ((m_nGameGrid[nPattern[i][0]] == EX) &&
            (m_nGameGrid[nPattern[i][1]] == EX) &&
            (m_nGameGrid[nPattern[i][2]] == EX))
            return EX;

        if ((m_nGameGrid[nPattern[i][0]] == OH) &&
            (m_nGameGrid[nPattern[i][1]] == OH) &&
            (m_nGameGrid[nPattern[i][2]] == OH))
            return OH;
    }
    return 0;
}

BOOL CMainWindow::IsDraw ()
{
    for (int i=0; i<9; i++) {
        if (m_nGameGrid[i] == 0)
            return FALSE;
    }
    return TRUE;
}

void CMainWindow::ResetGame ()
{
    m_nNextChar = EX;
    ::ZeroMemory (m_nGameGrid, 9 * sizeof (int));
    Invalidate ();
}
