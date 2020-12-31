// ==========================================================================
// 						Class Implementation : COXSerialCommConfig
// ==========================================================================

// Source file : oxsccfg.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXSCCFG.H"
#include "OXSCSTP.H"
#include "OXSRLZR.H"
#include "OXSCCNST.H"

//private headers
#include "OXRSERCM.H"

IMPLEMENT_SERIAL(COXSerialCommConfig, CObject, 1)


COXSerialCommConfig::COXSerialCommConfig() :
m_nPortId(0),
m_nBaudRate(CBR_9600),
m_nByteSize(8),
m_nParity(NOPARITY),
m_nStopBits(ONESTOPBIT),
m_eFlowControl(NONE),
m_nSizeReceivingQueue(DefaultSizeReceivingQueue),
m_nSizeTransmissionQueue(DefaultSizeTransmissionQueue),
m_nCdTimeout(DefaultCdTimeout),
m_nCtsTimeout(DefaultCtsTimeout),
m_nDsrTimeout(DefaultDsrTimeout)
	{
	}

COXSerialCommConfig::COXSerialCommConfig(COXSerialCommConfig& config)
	{
    m_nPortId=config.m_nPortId;
    m_nBaudRate=config.m_nBaudRate;
    m_nByteSize=config.m_nByteSize;
    m_nParity=config.m_nParity;	
    m_nStopBits=config.m_nStopBits;
    m_eFlowControl=config.m_eFlowControl;

    m_nSizeReceivingQueue=config.m_nSizeReceivingQueue;	
    m_nSizeTransmissionQueue=config.m_nSizeTransmissionQueue;
    m_nCdTimeout=config.m_nCdTimeout;			
								
    m_nCtsTimeout=config.m_nCtsTimeout;			
    m_nDsrTimeout=config.m_nDsrTimeout;			
	}

CString COXSerialCommConfig::GetCommName() const
	{
	CString sComX;
	
//	sComX.Format(_T("COM%c"), (char) (m_nPortId + '1'));
	sComX.Format(_T("COM%d"), m_nPortId+1);
	return sComX;
	}

int COXSerialCommConfig::DoConfigDialog(CString sTitle /* = NULL */)
	{
	int					nResult;
	COXSerialCommSetup	dlg(sTitle);
	
	dlg.m_config = *this;
	if ((nResult = dlg.DoModal()) == IDOK)
		*this = dlg.m_config;
	return nResult;
	}

BOOL COXSerialCommConfig::IsPortAvailable() const
	{
	CString		sComX;
	HANDLE		hCommDevice;
	
/*	if (m_nPortId > 8)
        return FALSE;*/
//	sComX.Format(_T("COM%c"), (char)m_nPortId + '1');
	sComX.Format(_T("COM%d"), m_nPortId+1);
	if ((hCommDevice =::CreateFile(sComX,
		GENERIC_READ |
		GENERIC_WRITE,
		0,
		NULL, 
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_SEQUENTIAL_SCAN,
		NULL))
		!= INVALID_HANDLE_VALUE)
		{
		CloseHandle(hCommDevice);
		return TRUE;
		}
	TRACE1("COXSerialCommConfig::IsPortAvailable(): port %s unavailable",sComX);
	return FALSE;
	}

BOOL COXSerialCommConfig::Load(CString sFileName)
	{
    COXSerializer	serializer;
	BOOL			bRetVal = TRUE;
	
	if (sFileName.IsEmpty())
		sFileName.LoadString(IDS_DEFAULTFILE);
    VERIFY(serializer.Initialize(sFileName, this));
    if (!serializer.Load(FALSE))
		{
        if (serializer.m_fileException.m_cause == CFileException::fileNotFound)
			{
            CString sString;
            sString.Format(IDS_MSG_DEFAULT_CONFIG, GetCommName());
            AfxMessageBox(sString, MB_OK | MB_ICONINFORMATION);
			}
		else
			{
            if (!serializer.Load())
				{
				CString sString;
				sString.Format(IDS_MSG_BAD_CONFIG, GetCommName());
                AfxMessageBox(sString, MB_OK | MB_ICONINFORMATION);
                bRetVal = FALSE;
				}
			}
        serializer.Save();
		}
    return bRetVal;
	}

BOOL COXSerialCommConfig::Save(CString sFileName)
	{
	COXSerializer	serializer;
	BOOL			bRetVal = TRUE;
	
	if (sFileName.IsEmpty())
		sFileName.LoadString(IDS_DEFAULTFILE);
    VERIFY(serializer.Initialize(sFileName,this));
    if (!serializer.Save())
		{
        CString sString;
        sString.Format(IDS_MSG_NO_SAVE, GetCommName());
        AfxMessageBox(sString, MB_OK | MB_ICONINFORMATION);
        bRetVal = FALSE;
		}
    return bRetVal;
	}

COXSerialCommConfig& COXSerialCommConfig::operator = (const COXSerialCommConfig& config)
	{
    m_nPortId = config.m_nPortId;
    m_nBaudRate = config.m_nBaudRate;
    m_nByteSize = config.m_nByteSize;
    m_nParity= config.m_nParity;
    m_nStopBits = config.m_nStopBits;
    m_eFlowControl = config.m_eFlowControl;
	
    m_nSizeReceivingQueue = config.m_nSizeReceivingQueue;
    m_nSizeTransmissionQueue = config.m_nSizeTransmissionQueue;
    m_nCdTimeout = config.m_nCdTimeout;
    m_nCtsTimeout = config.m_nCtsTimeout;
    m_nDsrTimeout = config.m_nDsrTimeout;
	
    return *this;
	}

// protected:

void COXSerialCommConfig::Serialize(CArchive& ar)
// --- In: ar: the archive this object has to serialize to or from
// --- Out: none
// --- Returns: none
// --- Effect: reading or writing to the archive depending of
//			   the read/write state of the archive
	{
    CObject::Serialize(ar);
	
    if (ar.IsStoring())
		{
        ar << m_nPortId;
        ar << (WORD)m_nBaudRate;
        ar << m_nByteSize;
        ar << m_nParity;
        ar << m_nStopBits;
        ar << (WORD)m_eFlowControl;
        ar << (WORD)m_nSizeReceivingQueue;
        ar << (WORD)m_nSizeTransmissionQueue;
        ar << (WORD)m_nCdTimeout;
        ar << (WORD)m_nCtsTimeout;
        ar << (WORD)m_nDsrTimeout;
		}
	else
		{
        ar >> m_nPortId;
        WORD tmp;
        ar >> tmp; m_nBaudRate = (UINT) tmp;
        ar >> m_nByteSize;
        ar >> m_nParity;
        ar >> m_nStopBits;
        ar >> tmp; m_eFlowControl = (EFlowControl) tmp;
        ar >> tmp; m_nSizeReceivingQueue = (UINT) tmp;
        ar >> tmp; m_nSizeTransmissionQueue = (UINT) tmp;
        ar >> tmp; m_nCdTimeout = (UINT) tmp;
        ar >> tmp; m_nCtsTimeout = (UINT) tmp;
        ar >> tmp; m_nDsrTimeout = (UINT) tmp;
		}
	}
