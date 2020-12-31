// ==========================================================================
// 						Class Implementation : COXSerialCommSetup
// ==========================================================================

// Source file : oxscstp.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXSCSTP.H"
#include "OXSCCNST.H"

COXSerialCommSetup::COXSerialCommSetup(CString sTitle /*= _T("")*/, CWnd* pParent /*=NULL*/)
	: CDialog(COXSerialCommSetup::IDD, pParent),
	m_sCommTitle(sTitle)
	{
    //{{AFX_DATA_INIT(COXSerialCommSetup)
    m_sBaudRate = _T("");
    m_sDataBit = _T("");
    m_sParity = _T("");
    m_sPort = _T("");
    m_sStopBit = _T("");
    m_sFlowControl = _T("");
    //}}AFX_DATA_INIT
	}

void COXSerialCommSetup::DoDataExchange(CDataExchange* pDX)
	{
    if (!pDX->m_bSaveAndValidate)
		{     // if loading
        m_sPort = _T("Com x");
		m_sPort.SetAt(4, (TCHAR)(m_config.m_nPortId + _T('1')));
        m_sBaudRate = BaudRateToString(m_config.m_nBaudRate);
        m_sDataBit = _T("x");
		m_sDataBit.SetAt(0, (TCHAR)(m_config.m_nByteSize + _T('0')));
        m_sParity = ParityToString(m_config.m_nParity);
        m_sStopBit = (m_config.m_nStopBits == ONESTOPBIT) ? _T("1") : _T("2");
        m_sFlowControl = FlowControlToString(m_config.m_eFlowControl);
		}
	
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(COXSerialCommSetup)
    DDX_CBString(pDX, IDC_BAUDRATE, m_sBaudRate);
    DDX_CBString(pDX, IDC_DATABIT, m_sDataBit);
    DDX_CBString(pDX, IDC_PARITY, m_sParity);
    DDX_CBString(pDX, IDC_PORT, m_sPort);
    DDX_CBString(pDX, IDC_STOPBIT, m_sStopBit);
    DDX_CBString(pDX, IDC_FLOWCONTROL, m_sFlowControl);
    //}}AFX_DATA_MAP
	
    if (pDX->m_bSaveAndValidate)
		{     // if saving
        m_config.m_nPortId = (BYTE) (m_sPort[4] - _T('1'));
        m_config.m_nBaudRate = BaudRateToVal(m_sBaudRate);
        m_config.m_nByteSize = (BYTE) (m_sDataBit[0] - _T('0'));
        m_config.m_nParity = ParityToVal(m_sParity);
        m_config.m_nStopBits = (m_sStopBit == _T("1")) ? (BYTE)ONESTOPBIT : (BYTE)TWOSTOPBITS;
        m_config.m_eFlowControl = FlowControlToVal(m_sFlowControl);
		}
	}

BEGIN_MESSAGE_MAP(COXSerialCommSetup, CDialog)
//{{AFX_MSG_MAP(COXSerialCommSetup)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL COXSerialCommSetup::OnInitDialog()
	{
    CDialog::OnInitDialog();
	
	if (!m_sCommTitle.IsEmpty())
		SetWindowText(m_sCommTitle);
	
    CenterWindow();
    return TRUE;
	}

void COXSerialCommSetup::OnOK()
	{
    if (UpdateData(TRUE))
		{
        if (!m_config.IsPortAvailable())
			{
            AfxMessageBox(IDS_MSG_NO_PORT_AVAILABLE, MB_OK | MB_ICONSTOP);
            CWnd* pPort = GetDlgItem(IDC_PORT); ASSERT (pPort != NULL);
            pPort->SetFocus();
			}
        else
            CDialog::OnOK();
		}
	}

CString COXSerialCommSetup::BaudRateToString(UINT nVal)
	{
	CString sString;
	
    if (HIBYTE(nVal) != 0xff)
		{
        sString.Format(_T("%d"), nVal);
		}
	else
		{
        switch (nVal)
			{
            case CBR_110:
				sString.LoadString(IDS_110);
				break;
            case CBR_300:
				sString.LoadString(IDS_300);
				break;
            case CBR_600:
				sString.LoadString(IDS_600);
				break;
            case CBR_1200:
				sString.LoadString(IDS_1200);
				break;
            case CBR_2400:
				sString.LoadString(IDS_2400);
				break;
            case CBR_4800:
				sString.LoadString(IDS_4800);
				break;
            case CBR_9600:
				sString.LoadString(IDS_9600);
				break;
            case CBR_14400:
				sString.LoadString(IDS_14400);
				ASSERT(FALSE); // not to be used (win3.1 bug!)
				break;   
            case CBR_19200:
				sString.LoadString(IDS_19200);
				break;
            case CBR_38400:
				sString.LoadString(IDS_38400);
				break;
            case CBR_56000:
				sString.LoadString(IDS_56000);
				break;
#ifdef WIN32
            case CBR_57600:
				sString.LoadString(IDS_57600);
				break;
            case CBR_115200:
				sString.LoadString(IDS_115200);
				break;
#endif
            case CBR_128000:
				sString.LoadString(IDS_128000);
				break;
            case CBR_256000:
				sString.LoadString(IDS_256000);
				break;
            default:
				sString.LoadString(IDS_9600);
				ASSERT(FALSE);
				break;
			}
		}
    return sString;
	}

CString COXSerialCommSetup::ParityToString(BYTE nVal)
	{
	CString sString;
	
    switch (nVal)
		{
        case NOPARITY:
			sString.LoadString(IDS_NOPARITY);
			break;
        case ODDPARITY:
			sString.LoadString(IDS_ODD);
			break;
        case EVENPARITY:
			sString.LoadString(IDS_EVEN);
			break;
        case MARKPARITY:
			sString.LoadString(IDS_MARK);
			break;
        case SPACEPARITY:
			sString.LoadString(IDS_SPACE);
			break;
        default:
            sString.LoadString(IDS_EVEN);
			ASSERT(FALSE);
			break;
		}
    return sString;
	}

CString COXSerialCommSetup::FlowControlToString(COXSerialCommConfig::EFlowControl eVal)
	{
	CString sString;
	
    switch (eVal)
		{
        case COXSerialCommConfig::NONE:
			sString.LoadString(IDS_NONE);
			break;
        case COXSerialCommConfig::HARDWARE:
			sString.LoadString(IDS_HARDWARE);
			break;
        case COXSerialCommConfig::XON_XOFF:
			sString.LoadString(IDS_XONXOFF);
			break;
        default:
			sString.LoadString(IDS_NONE);
			ASSERT(FALSE);
			break;
		}
    return sString;
	}

UINT COXSerialCommSetup::BaudRateToVal(CString sString)
	{
	CString sTemp;
	UINT nRetVal;
	
	sTemp.LoadString(IDS_14400);
    if (sString == sTemp)
        nRetVal = 14400;                     // to avoid windows 3.1 bug!
    else {
        if (sTemp.LoadString(IDS_110) && sString == sTemp)
            nRetVal = CBR_110;
        else if (sTemp.LoadString(IDS_300) && sString == sTemp)
            nRetVal = CBR_300;
        else if (sTemp.LoadString(IDS_600) && sString == sTemp)
            nRetVal = CBR_600;
        else if (sTemp.LoadString(IDS_1200) && sString == sTemp)
            nRetVal = CBR_1200;
        else if (sTemp.LoadString(IDS_2400) && sString == sTemp)
            nRetVal = CBR_2400;
        else if (sTemp.LoadString(IDS_4800) && sString == sTemp)
            nRetVal = CBR_4800;
        else if (sTemp.LoadString(IDS_9600) && sString == sTemp)
            nRetVal = CBR_9600;
        else if (sTemp.LoadString(IDS_14400) && sString == sTemp)
            nRetVal = CBR_14400;
        else if (sTemp.LoadString(IDS_19200) && sString == sTemp)
            nRetVal = CBR_19200;
        else if (sTemp.LoadString(IDS_38400) && sString == sTemp)
            nRetVal = CBR_38400;
        else if (sTemp.LoadString(IDS_56000) && sString == sTemp)
            nRetVal = CBR_56000;
#ifdef WIN32
        else if (sTemp.LoadString(IDS_57600) && sString == sTemp)
            nRetVal = CBR_57600;
        else if (sTemp.LoadString(IDS_115200) && sString == sTemp)
            nRetVal = CBR_115200;
#endif
        else if (sTemp.LoadString(IDS_128000) && sString == sTemp)
            nRetVal = CBR_128000;
        else if (sTemp.LoadString(IDS_256000) && sString == sTemp)
            nRetVal = CBR_256000;
        else
			{
			ASSERT(FALSE);
            nRetVal = CBR_9600;
			}
		}
    return nRetVal;
	}

BYTE COXSerialCommSetup::ParityToVal(CString sString)
	{
	CString sTemp;
	BYTE nRetVal;
	
    if (sTemp.LoadString(IDS_NOPARITY) && sString == sTemp)
        nRetVal = NOPARITY;
    else if (sTemp.LoadString(IDS_ODD) && sString == sTemp)
        nRetVal = ODDPARITY;
    else if (sTemp.LoadString(IDS_EVEN) && sString == sTemp)
        nRetVal = EVENPARITY;
    else if (sTemp.LoadString(IDS_MARK) && sString == sTemp)
        nRetVal = MARKPARITY;
    else if (sTemp.LoadString(IDS_SPACE) && sString == sTemp)
        nRetVal = SPACEPARITY;
    else
		{
		ASSERT(FALSE);
        nRetVal = EVENPARITY;
		}
    return nRetVal;
	}

COXSerialCommConfig::EFlowControl COXSerialCommSetup::FlowControlToVal(CString sString)
	{
	CString sTemp;
	COXSerialCommConfig::EFlowControl eRetVal;
	
    if (sTemp.LoadString(IDS_NONE) && sString == sTemp)
        eRetVal = COXSerialCommConfig::NONE;
    else if (sTemp.LoadString(IDS_HARDWARE) && sString == sTemp)
        eRetVal = COXSerialCommConfig::HARDWARE;
    else if (sTemp.LoadString(IDS_XONXOFF) && sString == sTemp)
        eRetVal = COXSerialCommConfig::XON_XOFF;
    else
		{
        ASSERT(0);
        eRetVal = COXSerialCommConfig::NONE;
		}
    return eRetVal;
	}
