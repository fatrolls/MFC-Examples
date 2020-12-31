// DlgResEdit.cpp : implementation file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

#include "stdafx.h"
#include "ResFile.h"
#include "DlgResEdit.h"

#include "OXResourceFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgResEdit dialog


CDlgResEdit::CDlgResEdit(COXResourceFile* pResFile, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgResEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgResEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pResFile = pResFile;
}

void CDlgResEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgResEdit)
	DDX_Control(pDX, IDC_DUMP, m_ctlDump);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgResEdit, CDialog)
	//{{AFX_MSG_MAP(CDlgResEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgResEdit message handlers

BOOL CDlgResEdit::OnInitDialog() 
	{
	CDialog::OnInitDialog();

	// ... set 10 point Courier font
	if (m_fontCourier.CreatePointFont(100, _T("Courier")))
		m_ctlDump.SetFont(&m_fontCourier, FALSE);

	DumpResContents();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	}

void CDlgResEdit::DumpResContents()
	{
	const BYTE LOWER_PRINTABLE = 32;
	const BYTE UPPER_PRINTABLE = 126;
	const UINT LINE_SIZE = 16;
	const UINT TEXT_POS0 = 6 + 2 + LINE_SIZE * (2 + 1) + 2;
	const UINT CH_PER_LINE = TEXT_POS0 + LINE_SIZE + 2;

	BYTE lpBuffer[LINE_SIZE];
	CString sTemp;
	BYTE nTemp;
	int p, ptext, i, nBytesRead;

	DWORD_PTR nFileLen = (DWORD_PTR)m_pResFile->GetLength();
	ASSERT(nFileLen);
	UINT nMax = ((UINT)((nFileLen - 1) / LINE_SIZE + 1)) * CH_PER_LINE;
	CString sOutput(_T(' '), nMax);

	m_pResFile->SeekToBegin();
	for (UINT nLinePos0 = 0; nLinePos0 < nMax; nLinePos0 += CH_PER_LINE)
		{
		p = nLinePos0;
		ptext = p + TEXT_POS0;

		sTemp.Format(_T("%06x"), m_pResFile->GetPosition());
		for (i = 0; i < 6; i++)	sOutput.SetAt(p++, sTemp[i]);

		p += 2; // leave two space
		nBytesRead = m_pResFile->Read(lpBuffer, LINE_SIZE);
		for (i = 0; i < nBytesRead; i++)
			{
			nTemp = lpBuffer[i];
			sTemp.Format(_T("%02X"), nTemp);
			sOutput.SetAt(p++, sTemp[0]);
			sOutput.SetAt(p++, sTemp[1]);
			p++; // leave one space
			if (i == LINE_SIZE / 2 - 1) p++; // leave one more space after half block

			if (nTemp >= LOWER_PRINTABLE && nTemp <= UPPER_PRINTABLE)
				{
				sTemp.Format(_T("%c"), nTemp);
				sOutput.SetAt(ptext++, sTemp[0]);
				}
			else
				sOutput.SetAt(ptext++, _T('.'));
			}

		sOutput.SetAt(nLinePos0 + CH_PER_LINE - 2, _T('\r'));
		sOutput.SetAt(nLinePos0 + CH_PER_LINE - 1, _T('\n'));
		}

	m_ctlDump.SetWindowText(sOutput);
	}