// Serial.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "Serial.h"
#include "ProtocolTypes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable: 4800)

/////////////////////////////////////////////////////////////////////////////
// CSerial

IMPLEMENT_DYNCREATE(CSerial, CCmdTarget)

CSerial::CSerial(bool bNeedThread)
{
	m_hCom = INVALID_HANDLE_VALUE;
	m_bExit = false;
	m_hThread = NULL;
    m_dwMaskEvent = DEFAULT_COM_MASK_EVENT;
	m_dwNotifyNum = 0;
	m_dcb.DCBlength = sizeof(DCB);
	m_hNotifyWnd = NULL;
    // 初始化重叠结构
	ZeroMemory(&m_ReadOL, sizeof(m_ReadOL));
    ZeroMemory(&m_WriteOL, sizeof(m_WriteOL));
	ZeroMemory(&m_WaitOL, sizeof(m_WaitOL));
	m_ReadOL.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_WaitOL.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    m_WriteOL.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_bNeedThread = bNeedThread ;
}

CSerial::~CSerial()
{
	// 关闭串口
	Close();
	// 释放事件对象
	::CloseHandle(m_ReadOL.hEvent);
	::CloseHandle(m_WaitOL.hEvent);
	::CloseHandle(m_WriteOL.hEvent);
}


BEGIN_MESSAGE_MAP(CSerial, CCmdTarget)
	//{{AFX_MSG_MAP(CSerial)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerial message handlers

void CSerial::Close()
{
	if (!IsOpen())
		return;

	if (m_bNeedThread)
	{
		m_bExit = true;
		SetEvent(m_WaitOL.hEvent);
		DWORD dwCode;
		int n = 0;
		do{
			Sleep(10);
			if (n ++ > 5)
				break;
		}while(!GetExitCodeThread(m_hThread, &dwCode));
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	CloseHandle(m_hCom);
	m_hCom = INVALID_HANDLE_VALUE;
}

bool CSerial::IsOpen()
{
   return m_hCom != INVALID_HANDLE_VALUE;
}

void CSerial::OnBreak()
{
   if (IsWindow(m_hNotifyWnd))
	   SendMessage(m_hNotifyWnd, WM_COM_BREAK, 0, 0);
}

void CSerial::OnCTS()
{
	if (IsWindow(m_hNotifyWnd))
	{
		DWORD dwStatus;
		if (GetCommModemStatus(m_hCom, &dwStatus))
			SendMessage(m_hNotifyWnd, WM_COM_CTS, 0, dwStatus&MS_CTS_ON? 1:0);
	}
}

void CSerial::OnDSR()
{
     if (IsWindow(m_hNotifyWnd))
	{
		DWORD dwStatus;
		if (GetCommModemStatus(m_hCom, &dwStatus))
			SendMessage(m_hNotifyWnd, WM_COM_DSR, 0, dwStatus&MS_DSR_ON? 1:0);
	}
}

void CSerial::OnError()
{
	DWORD dwError;
	ClearCommError(m_hCom, &dwError, NULL);
	if (IsWindow(m_hNotifyWnd))
		SendMessage(m_hNotifyWnd, WM_COM_ERROR, 0, dwError);
}

void CSerial::OnReceive()
{
    if (IsWindow(m_hNotifyWnd))
		SendMessage(m_hNotifyWnd, WM_COM_RECEIVE, 0, 0);
}

void CSerial::OnRing()
{
    if(IsWindow(m_hNotifyWnd))
		SendMessage(m_hNotifyWnd, WM_COM_RING, 0, 0);
}

void CSerial::OnRLSD()
{
     if(::IsWindow(m_hNotifyWnd))
		::SendMessage(m_hNotifyWnd, WM_COM_RLSD, 0, 0);
}

void CSerial::OnTXEmpty()
{
     if(::IsWindow(m_hNotifyWnd))
		::SendMessage(m_hNotifyWnd, WM_COM_TXEMPTY, 0, 0);
}

bool CSerial::Open(DWORD dwPort, DWORD dwBaudRate)
{
	if (dwPort < 1 || dwPort > 1024)
		return false;
	if (!OpenCommPort(dwPort))
		return false;
	// 采用默认设置
	// 设置输入输出缓冲区大小
    if (!SetupComm(m_hCom, 4096, 4096))
        return false;
	// 设置超时
    COMMTIMEOUTS co;
	if (!GetCommTimeouts(m_hCom, &co))
		return false;
	co.ReadIntervalTimeout = 0;
	co.ReadTotalTimeoutMultiplier = 1;
	co.ReadTotalTimeoutConstant = 1000;
	co.WriteTotalTimeoutMultiplier = 1;
	co.WriteTotalTimeoutConstant = 1000;
	if (!SetCommTimeouts(m_hCom, &co))
		return false;
    // 清空输入输出缓冲区
	if (!PurgeComm(m_hCom, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR))
		return false;
	return SetState(dwBaudRate);
}

bool CSerial::OpenCommPort(DWORD dwPort)
{
	if (m_hCom != INVALID_HANDLE_VALUE)
		return false;
    ZeroMemory(m_szComm, 16);
	strcpy(m_szComm, "\\\\.\\COM");
    char szPort[5] = { 0 };
	ltoa(dwPort, szPort, 10);
	strcat(m_szComm, szPort);
    m_hCom = CreateFile(m_szComm, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (m_hCom == INVALID_HANDLE_VALUE)
		return false;
	if (m_bNeedThread)
	{
		DWORD dwID;
		m_bExit = false;
		m_hThread = CreateThread(NULL, 0, SerialThreadProc, this, 0, &dwID);
		if (m_hThread == NULL)
		{
			CloseHandle(m_hCom);
			m_hCom = INVALID_HANDLE_VALUE;
			return false;
		}
	}
    return true;
}

bool CSerial::SetState(DWORD dwBaudRate, DWORD dwByteSize, DWORD dwPatity, DWORD dwStopBits)
{
	if (!IsOpen())
		return false;

	if (!GetCommState(m_hCom, &m_dcb))
		return false;
	m_dcb.BaudRate = dwBaudRate;
	m_dcb.ByteSize = (UCHAR)dwByteSize;
	m_dcb.StopBits =  (UCHAR)dwStopBits;
	m_dcb.Parity = (UCHAR)dwPatity;
	if (dwPatity != NOPARITY)
        m_dcb.fParity = true;
	return (bool)SetCommState(m_hCom, &m_dcb);
}

bool CSerial::Purge(DWORD dwFlags)
{
    if(!IsOpen())
		return false;

	return ::PurgeComm(m_hCom, dwFlags);
}

DWORD CSerial::Read(LPVOID Buffer, DWORD dwBufferLen, DWORD dwWaitTime)
{
	if(!IsOpen())
		return 0;
    COMSTAT stat;
	DWORD dwError;
    // 有错误发生！
	if (ClearCommError(m_hCom, &dwError, &stat) && dwError > 0)
	{
        // 清除缓冲区，清除所有抛出的读操作
		Purge(PURGE_RXABORT|PURGE_RXCLEAR);
		return 0;
	}
    //如果输入缓冲区没有数据
	if (stat.cbInQue)
		return 0;
	
	DWORD dwRead = 0;
	if (dwBufferLen = stat.cbInQue)
		dwBufferLen = stat.cbInQue;

	if (!ReadFile(m_hCom, Buffer, dwBufferLen, &dwRead, &m_ReadOL))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			//等待操作完成
			WaitForSingleObject(m_ReadOL.hEvent, dwWaitTime);
            if(!GetOverlappedResult(m_hCom, &m_ReadOL, &dwRead, FALSE))
			{
				if (GetLastError() != ERROR_IO_INCOMPLETE)
					dwRead = 0;
			}
		}
		else
			dwRead = 0;
	}
	return dwRead;
}

bool CSerial::ReadData(PVOID Buffer, DWORD dwReadLen, DWORD dwWaitTime)
{
    if(!IsOpen())
		return false;

	COMSTAT Stat;
	DWORD dwError;
	BOOL bError = FALSE;  // 
	DWORD dwRead = 0;

	while(TRUE)
	{
		// 检查是否有错误发生
		if(::ClearCommError(m_hCom, &dwError, &Stat))
		{
			if(dwError > 0)
			{
	    		 bError = TRUE;  
			}
			
			//等待输入缓冲有足够的数据， 才开始读取
			// 查看输入缓冲区中的数据长度
			if(Stat.cbInQue >= dwReadLen)
			{
				// 读取输入缓冲区中的数据
				dwRead = Read(Buffer, dwReadLen, dwWaitTime);
				break;
			}
			else
			{
				::Sleep(10);
			 	dwWaitTime -= 10;
			}
		}
		else
		{
			return FALSE;
		}

		if(dwWaitTime <= 0)
			return FALSE;
	}


	if(dwRead == dwReadLen && !bError)
		return TRUE;
	else
		return FALSE;
}

CSerialFrame* CSCSerial::ReadFrame()
{
    CSerialFrame *pFrame = (CSerialFrame *)m_Buffer;
	if(CSerial::ReadData(m_Buffer, sizeof(CSerialFrame), 100))
		return pFrame;
	else
		return NULL;
}

TCHAR *CSerial::ReadString(TCHAR *szBuffer, DWORD dwBufferLen, DWORD dwWaitTime)
{
	DWORD dwRead = Read(szBuffer, dwBufferLen - 1, dwWaitTime);
	szBuffer[dwRead] = '\0';
	return szBuffer;
}

DWORD WINAPI CSerial::SerialThreadProc(LPVOID pParam)
{
    CSerial* pThis = (CSerial*)pParam;
	return pThis->ThreadProc();
}

DWORD CSerial::ThreadProc()
{
	//设置串口响应的消息掩码
	if (!SetCommMask(m_hCom, m_dwMaskEvent))
	{
		MessageBox(m_hNotifyWnd, "设置串口事件响应掩码失败", "错误", 0);
		return -1;
	}

	DWORD dwError, dwMask, dwTrans;
	COMSTAT Stat;

	while(!m_bExit)
	{
		dwMask = 0;
		if (!WaitCommEvent(m_hCom, &dwMask, &m_WaitOL))
		{
			if (GetLastError() == ERROR_IO_PENDING)
				GetOverlappedResult(m_hCom, &m_WaitOL, &dwTrans, TRUE);
			else
				continue;
		}
		switch(dwMask)
		{
			case EV_RXCHAR:
				{
					// 有数据进来，  获取数据大小
					::ClearCommError(m_hCom, &dwError, &Stat);
					if(Stat.cbInQue >= m_dwNotifyNum)
					{
						OnReceive();
					}
				}
				break;
			
			case EV_TXEMPTY:		// 输出缓冲区中的最后一个字符被发送了
				OnTXEmpty();
				break;
			case EV_CTS:			// clear-to-send信号改变
				OnCTS();
				break;

			case EV_DSR:			// data-set-ready信号改变
				OnDSR();
				break;

			case EV_RING:		
				OnRing();
				break;

			case EV_RLSD:		
				OnRLSD();
				break;

			case EV_BREAK:
				OnBreak();
				break;

			case EV_ERR:
				OnError();
				break;
			default:
				continue;
		}
	}
    return 0;
}

bool CSerial::SetBreak(bool bOn)
{
   if(!IsOpen())
	   return false;
   
   return EscapeCommFunction(m_hCom, bOn?SETBREAK:CLRBREAK);
}

BOOL CSerial::SetBufferSize(DWORD dwInputSize, DWORD dwOutputSize)
{
	return IsOpen() ? ::SetupComm(m_hCom, dwInputSize, dwOutputSize) : FALSE;
}

BOOL CSerial::SetDTR(BOOL OnOrOff)
{
	return IsOpen() ? ::EscapeCommFunction(m_hCom, OnOrOff ? SETDTR:CLRDTR): FALSE;
}

void CSerial::SetMaskEvent(DWORD dwMask)
{
	m_dwMaskEvent = dwMask;
}

BOOL CSerial::SetRTS(BOOL OnOrOff)
{
	return IsOpen() ? ::EscapeCommFunction(m_hCom, OnOrOff ? SETRTS:CLRRTS):FALSE;
}

void CSerial::SetNotifyNum(DWORD dwNum)
{
	m_dwNotifyNum = dwNum;
}

BOOL CSerial::SetTimeouts(LPCOMMTIMEOUTS lpCO)
{
	return IsOpen() ? ::SetCommTimeouts(m_hCom, lpCO) : FALSE;
}

void CSerial::SetWnd(HWND hWnd)
{
	m_hNotifyWnd = hWnd;
}

DWORD CSerial::Write(LPVOID Buffer, DWORD dwBufferLen)
{
	if(!IsOpen())
		return 0;


	COMSTAT Stat;
	DWORD dwError;
	// 有错误发生！
	if(::ClearCommError(m_hCom, &dwError, &Stat) && dwError > 0)
	{
		// 清除缓冲区，清除所有抛出的读操作
		::PurgeComm(m_hCom, PURGE_TXABORT|PURGE_TXCLEAR);
		return 0;
	}

	DWORD dwWrite = 0;
	if(!::WriteFile(m_hCom, Buffer, dwBufferLen, &dwWrite, &m_WriteOL))
	{
		if( ::GetLastError() == ERROR_IO_PENDING)
		{
			::GetOverlappedResult(m_hCom, &m_WriteOL, &dwWrite, TRUE);
		}
	}
	return dwWrite;
}

DWORD CSerial::WriteString(LPTSTR szBuffer)
{
	return Write(szBuffer, strlen(szBuffer));
}

//////////////////////////////////////////////////////////////////////
// CSCSerial Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSCSerial::CSCSerial(bool bNeedThread)
:CSerial(bNeedThread)
{
	//设置接收到数据通知的最小大小， 为数据帧头大小， 因为接收到的数据都是包含帧头， 后面跟着数据， 可能没有数据
    SetNotifyNum(sizeof(CSerialFrame));
	//设置串口通知事件为接收数据， break, 输出缓冲清空事件
	SetMaskEvent(EV_RXCHAR | EV_BREAK | EV_TXEMPTY);
	m_nStatus = STATUS_IDLE;
	m_sequence = 0;
}

CSCSerial::~CSCSerial()
{

}

CSerialFrame* CSCSerial::ReadData2()
{
	CSerialFrame* pFrame = (CSerialFrame*)m_Buffer;
	int nCheckSum;
	if (CSerial::ReadData(m_Buffer, sizeof(CSerialFrame), 100))
	{
		//如果数据长度大于最大尺寸， 错误数据
		if (pFrame->uDataLen > FRAME_SIZE)
		{
			Purge();
			return NULL;
		}
		//如果后面跟着数据
		if (pFrame->uDataLen > 0)
		{   //读取数据失败
			if (!CSerial::ReadData(pFrame+1, pFrame->uDataLen, 600))
			{
				Purge();
				return NULL;
			}
		}
        nCheckSum= pFrame->uChecksum;
		pFrame->uChecksum = 0;
		//如果校验和错误， 表示数据已经被破坏， 发出重发命令
		if (nCheckSum != checksum((USHORT*)pFrame, sizeof(CSerialFrame)+pFrame->uDataLen))
		{
			SendRetry();
			return NULL;
		}
		return pFrame;
	}
	else
	{
		Purge();
		return NULL;
	}
}

bool CSCSerial::SetAbort()
{
	CSerialFrame frame, ack;
	ZeroMemory(&frame, sizeof(frame));
	frame.command = SERIAL_ABORT;
	frame.uDataLen = 0;
	frame.uChecksum = checksum((USHORT*)&frame,sizeof(frame));
	
	if (CSerial::Write(&frame, sizeof(frame)) != sizeof(frame))
		return false;

	if (CSerial::ReadData(&ack, sizeof(ack), 1500))
	{
		int nCheckSum = ack.uChecksum;
		ack.uChecksum = 0;
		if (nCheckSum != checksum((USHORT*)&ack, sizeof(ack)))
			return false;
		if (ack.command == SERIAL_ACK)
			return true;
		else
			return false;
	}
	else
		return false;
}

BOOL CSCSerial::SendAck()
{
	CSerialFrame frame;

	memset(&frame, 0, sizeof(frame));

	frame.command = SERIAL_ACK;
	frame.uDataLen = 0;

	frame.uChecksum = checksum((USHORT*)&frame, sizeof(frame));

	if(CSerial::Write(&frame, sizeof(frame)) != sizeof(frame))
			return FALSE;

	return TRUE;
}

BOOL CSCSerial::SendCommand(BYTE command)
{
	CSerialFrame frame;

	memset(&frame, 0, sizeof(frame));

	frame.command = command;
	frame.uDataLen = 0;

	frame.uChecksum = checksum((USHORT*)&frame, sizeof(frame));

	if(CSerial::Write(&frame, sizeof(frame)) != sizeof(frame))
			return FALSE;
	return TRUE;
}

BOOL  CSCSerial::SendData(LPVOID Buffer, int nBufferLen)
{
	if(nBufferLen > FRAME_SIZE)
		return FALSE;

	CSerialFrame *pFrame = (CSerialFrame *)m_Buffer;
	memset(pFrame, 0, sizeof(CSerialFrame));

	// 构建贞
	pFrame->command = SERIAL_DATA;
	pFrame->uDataLen = nBufferLen;
	pFrame->sequence = m_sequence;
	memcpy(pFrame + 1, Buffer, nBufferLen);

	pFrame->uChecksum = checksum((USHORT*)pFrame, sizeof(CSerialFrame) + nBufferLen);

	if(CSerial::Write(pFrame, sizeof(CSerialFrame) + nBufferLen) 
			!= sizeof(CSerialFrame) + nBufferLen)
		return FALSE;
	return TRUE;
}

BOOL CSCSerial::SendEOF()
{
	// 构建数据帧
	CSerialFrame frame, ack;
	memset(&frame, 0, sizeof(frame));

	frame.command = SERIAL_EOF;
	frame.uDataLen = 0;

	// 计算校验和
	frame.uChecksum = checksum((USHORT*)&frame, sizeof(frame));
	
	// 发送数据帧
	if(CSerial::Write(&frame, sizeof(frame)) != sizeof(frame))
		return FALSE;
	
	// 接收对方的“确认”消息
	if(CSerial::ReadData(&ack, sizeof(ack), 1500))
	{
		// 检查效验和
		int nChecksum = ack.uChecksum;
		ack.uChecksum = 0;
		if(nChecksum != checksum((USHORT*)&ack, sizeof(ack)))
			return FALSE;
		
		if(ack.command == SERIAL_ACK)
		{
			return TRUE;
		}
		else
			return FALSE;
	}
	
	return FALSE;
}

BOOL CSCSerial::SendFileData(LPVOID Buffer, int nBufferLen)
{
	if(nBufferLen > FRAME_SIZE)
		return FALSE;

	CSerialFrame *pFrame = (CSerialFrame *)m_Buffer;
	memset(pFrame, 0, sizeof(CSerialFrame));

	// 构建贞
	pFrame->command = SERIAL_DATA;
	pFrame->uDataLen = nBufferLen;
	pFrame->sequence = m_sequence;
	memcpy(pFrame + 1, Buffer, nBufferLen);

	pFrame->uChecksum = checksum((USHORT*)pFrame, sizeof(CSerialFrame) + nBufferLen);



	while(TRUE)
	{
		CSerialFrame ack;
		if(CSerial::Write(pFrame, sizeof(CSerialFrame) + nBufferLen) 
			!= sizeof(CSerialFrame) + nBufferLen)
			return FALSE;
		
		if(CSerial::ReadData(&ack, sizeof(ack), 1500))
		{
			// 检查效验和
			int nChecksum = ack.uChecksum;
			ack.uChecksum = 0;
			if(nChecksum != checksum((USHORT*)&ack, sizeof(ack)))
				return FALSE;

			if(ack.command == SERIAL_ACK)
			{
				m_sequence++;
				return TRUE;
			}
			else if(ack.command == SERIAL_ERROR)
				continue;
			else
				return FALSE;
		}
		else
			return FALSE;
	}
	return FALSE;
}

BOOL CSCSerial::SendFileSize(DWORD dwSize)
{

	char buff[sizeof(CSerialFrame) + sizeof(DWORD)];
	memset(buff, 0, sizeof(CSerialFrame) + sizeof(DWORD));


	CSerialFrame *pFrame = (CSerialFrame *)buff;
	CSerialFrame recv;

	// build frame
	pFrame->command = SERIAL_SIZE;
	pFrame->uDataLen = sizeof(DWORD);
	*(DWORD*)(pFrame + 1) = dwSize;

	pFrame->uChecksum = checksum((USHORT*)pFrame, sizeof(CSerialFrame) + sizeof(DWORD));
	
	
	// send it
	if(CSerial::Write(pFrame, sizeof(CSerialFrame) + sizeof(DWORD)) 
						!= sizeof(CSerialFrame) + sizeof(DWORD))
		return FALSE;
	
	// wait for ack
	if(CSerial::ReadData(&recv, sizeof(recv), 1500))
	{
		// 检查效验和
		int nChecksum = recv.uChecksum;
		recv.uChecksum = 0;
		if(nChecksum != checksum((USHORT*)&recv, sizeof(recv)))
			return FALSE;
		
		if(recv.command == SERIAL_ACK)
			return TRUE;
		else
			return FALSE;
	}
	return FALSE;
}

BOOL CSCSerial::SendInit()
{ 
	m_nStatus = STATUS_IDLE; 
	return SendCommand(SERIAL_INIT); 
	
}

BOOL CSCSerial::SendRetry()
{
	CSerialFrame frame;

	memset(&frame, 0, sizeof(frame));

	frame.command = SERIAL_ERROR;
	frame.uDataLen = 0;

	frame.uChecksum = checksum((USHORT*)&frame, sizeof(frame));

	if(CSerial::Write(&frame, sizeof(frame)) != sizeof(frame))
			return FALSE;

	return TRUE;
}

