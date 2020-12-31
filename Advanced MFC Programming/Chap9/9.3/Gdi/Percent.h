#if !defined(AFX_PERCENT_H__1DC82DF4_1E20_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_PERCENT_H__1DC82DF4_1E20_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPercent : public CStatic
{
public:
	CPercent();
	void SetPercentage(int nPer)
	{
		if(m_nRange != 0)m_nCurPos=nPer*m_nRange/100;
		Invalidate();
	}
	void SetPosition(int nPos){m_nCurPos=nPos; Invalidate();}
	void SetRange(int nRange){m_nRange=nRange;}
	//{{AFX_VIRTUAL(CPercent)
	//}}AFX_VIRTUAL

public:
	virtual ~CPercent();

protected:
	int m_nRange;
	int m_nCurPos;
	//{{AFX_MSG(CPercent)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_PERCENT_H__1DC82DF4_1E20_11D1_9C9A_444553540000__INCLUDED_)
