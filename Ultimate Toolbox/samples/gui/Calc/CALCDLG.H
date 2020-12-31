// calcdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalculator dialog

#include "oxshape.h"

enum Operator { OpNone, OpAdd, OpSubtract, OpMultiply, OpDivide };
enum CalcError { ErrNone, ErrDivideByZero };

class CCalculator : public CDialog, public COXShape
{
private:
	BOOL	m_bTrackMove;
	CPoint	m_ptMouse, m_ptLast;
	long	m_accum;
	long	m_operand;
	BOOL	m_bOperandAvail;
	HACCEL	m_hAccel;
	Operator m_operator;
	CalcError m_errorState;

private:
	HWND GetHWND() { return m_hWnd; } 
	void SetTotal(double dbTotal);
	void SetOpTotal();
	void InvertTracker(CPoint point);

	// helper functions
	void PerformOperation();
	void ClickedNumber(long lNum);
	void UpdateDisplay();
	void SetOperand(long nNewValue);

// Construction
public:
	CCalculator(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCalculator)
	enum { IDD = IDD_CALCULATOR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalculator)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalculator)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	afx_msg void OnClear();
	afx_msg void OnDiv();
	afx_msg void OnEqual();
	afx_msg void OnMul();
	afx_msg void OnSub();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnAbout();
	afx_msg void OnNumber(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
