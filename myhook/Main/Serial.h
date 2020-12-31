#if !defined(AFX_SERIAL_H__756C04AE_85E2_4A6D_91A8_5E03B28AD2B8__INCLUDED_)
#define AFX_SERIAL_H__756C04AE_85E2_4A6D_91A8_5E03B28AD2B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Serial.h : header file
//
//  CSerial类向主窗口发送的消息
#define WM_COM_RECEIVE	WM_USER	+ 301
#define WM_COM_CTS		WM_USER	+ 302		
#define WM_COM_DSR		WM_USER	+ 303
#define WM_COM_RING		WM_USER	+ 304
#define WM_COM_RLSD		WM_USER	+ 306
#define WM_COM_BREAK	WM_USER	+ 307
#define WM_COM_TXEMPTY	WM_USER	+ 308
#define WM_COM_ERROR	WM_USER	+ 309

#define DEFAULT_COM_MASK_EVENT EV_RXCHAR | EV_ERR  \
				| EV_CTS | EV_DSR | EV_BREAK | EV_TXEMPTY | EV_RING | EV_RLSD

/////////////////////////////////////////////////////////////////////////////
// CSerial command target

class CSerial : public CCmdTarget
{
	DECLARE_DYNCREATE(CSerial)

	CSerial(bool bNeedThread = false);           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	virtual DWORD Write(LPVOID Buffer, DWORD dwBufferLen);
	virtual DWORD WriteString(LPTSTR szBuffer);;
	virtual void SetWnd(HWND hWnd);
	virtual BOOL SetTimeouts(LPCOMMTIMEOUTS lpCO);
	virtual void SetNotifyNum(DWORD dwNum);
	virtual void SetMaskEvent(DWORD dwMask);
	virtual BOOL SetDTR(BOOL OnOrOff);
	virtual BOOL SetRTS(BOOL OnOrOff);
	virtual BOOL SetBufferSize(DWORD dwInputSize, DWORD dwOutputSize);;
	virtual bool SetBreak(bool bOn);
	virtual TCHAR * ReadString(TCHAR *szBuffer, DWORD dwBufferLen, DWORD dwWaitTime);
	/*virtual */bool ReadData(PVOID Buffer, DWORD dwBufferLen, DWORD dwWaitTime);
	virtual bool Purge(DWORD dwFlag = PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
	virtual bool Open(DWORD dwPort, DWORD dwBaudRate);
	virtual bool IsOpen();
	virtual void Close();
	virtual bool SetState(DWORD dwBaudRate, DWORD dwByteSize = 8, 
				DWORD dwPatity = NOPARITY, DWORD dwStopBits = ONESTOPBIT);

	virtual DWORD Read(LPVOID Buffer, DWORD dwBufferLen, DWORD dwWaitTime);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerial)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSerial();

	// Generated message map functions
	//{{AFX_MSG(CSerial)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	virtual bool OpenCommPort(DWORD dwPort);
	virtual void OnTXEmpty();
	virtual void OnRLSD();
	virtual void OnRing();
	virtual void OnReceive();
	virtual void OnError();
	virtual void OnDSR();
	virtual void OnCTS();
	virtual void OnBreak();
	HANDLE m_hCom;//打开的com口句柄
	OVERLAPPED m_ReadOL;  //读操作overlapped结构
	OVERLAPPED m_WriteOL; //写操作overlapped结构
	OVERLAPPED m_WaitOL;  //等待操作overlapped结构
	BOOL m_bExit;
	HANDLE m_hThread;
	DCB  m_dcb;           //com端口操作的dcb结构
	DWORD m_dwMaskEvent;  //com口接收事件的掩码
	HWND m_hNotifyWnd;    //关联的窗口
	DWORD m_dwNotifyNum;  //事件通知计数
	char m_szComm[16];    //com口名称
	bool m_bNeedThread;   //是否需要单独的处理线程
private:
	virtual DWORD ThreadProc();
	static DWORD WINAPI SerialThreadProc(LPVOID pParam);
};

/////////////////////////////////////////////////////////////////////////////
// 传输协议中的帧头
struct CSerialFrame
{
	BYTE command;  //命令
	BYTE reserved; //预留
	USHORT sequence;//序列号
	USHORT uChecksum;//校验和
	USHORT uDataLen;//数据长度
};
//传输协议数据帧头的command字段命令
#define SERIAL_CONNECT		0x01		// 请求连接
#define SERIAL_ACK			0x02		// 确认
#define SERIAL_DATA			0x03		// 数据
#define SERIAL_ERROR		0x04		// 出错  要求重发
#define SERIAL_SIZE			0x05		// 数据大小
#define SERIAL_ABORT		0x06		// 终止
#define SERIAL_EOF			0x07		// 结束
#define SERIAL_TOOBIG		0x08		// 文件太大
#define SERIAL_SYSFAILED	0x09		// 系统出错
#define SERIAL_INIT			0x0a		// 初始化
#define SERIAL_GETSTATUS	0x0b		// 获取当前状态
#define SERIAL_TRANSFAILED  0x0c		// 文件传输失败
#define SERIAL_VERIFYFAILED 0x0d		// 用户验证失败
#define SERIAL_DEVICEFAILED 0x10		// 设备出错

// 数据帧大小
#define FRAME_SIZE     156
// 状态
#define STATUS_TRANSFERING	0x03		// 正在传输文件
#define STATUS_IDLE			0x04		// 空闲
#define STATUS_CONNECTED	0x05		// 已经连接



class CSCSerial : public CSerial  
{
public:
	virtual BOOL SendRetry();
    virtual BOOL SendInit();
	virtual BOOL SendFileSize(DWORD dwSize);
	virtual BOOL SendFileData(LPVOID Buffer, int nBufferLen);
	virtual BOOL SendEOF();
	virtual BOOL SendData(LPVOID Buffer, int nBufferLen);
	virtual BOOL SendCommand(BYTE command);
	virtual BOOL SendAck();
	virtual bool SetAbort();
	virtual CSerialFrame* ReadFrame();
	/*virtual */CSerialFrame* ReadData2();
	CSCSerial(bool bNeedThread = false);
	virtual ~CSCSerial();

	char m_Buffer[FRAME_SIZE + sizeof(CSerialFrame) + 1];  //内部缓冲区， 包括数据帧头和数据帧， 这样不用频繁分配内存
	USHORT m_sequence;  //序列号
	int m_nStatus;      // 记录当前状态
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIAL_H__756C04AE_85E2_4A6D_91A8_5E03B28AD2B8__INCLUDED_)
