// ComFilDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "ComFilDlg.h"
#include "ProtocolTypes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComFilDlg dialog
IMPLEMENT_DYNCREATE(CComFileDlg, CRootDlg)

CComFileDlg::CComFileDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CComFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CComFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComFileDlg)
	DDX_Control(pDX, IDC_BOUDRATE, m_BoudRate);
	DDX_Control(pDX, IDC_EDITLOG, m_Log);
	DDX_Control(pDX, IDC_BUTTONCLOSE, m_Close);
	DDX_Control(pDX, IDC_BUTTONSEND, m_Send);
	DDX_Control(pDX, IDC_BUTTONOPEN, m_Open);
	DDX_Control(pDX, IDC_STATUS, m_Status);
	DDX_Control(pDX, IDC_COMBOPORT, m_ComboPort);
	DDX_Control(pDX, IDC_EDITFILE, m_EditFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComFileDlg, CRootDlg)
	//{{AFX_MSG_MAP(CComFileDlg)
	ON_BN_CLICKED(IDC_BUTTONBROWSER, OnButtonbrowser)
	ON_BN_CLICKED(IDC_BUTTONCLOSE, OnButtonclose)
	ON_BN_CLICKED(IDC_BUTTONOPEN, OnButtonopen)
	ON_BN_CLICKED(IDC_BUTTONSEND, OnButtonsend)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComFilDlg message handlers

BOOL CComFileDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	
// 初始化供用户选择端口的组合框，默认选择端口COM1
	m_ComboPort.AddString("COM1");
	m_ComboPort.AddString("COM2");
	m_ComboPort.AddString("COM3");
	m_ComboPort.SelectString(0, "COM1");

	// 初始化供用户选择波特率的组合框，默认选择38400   注：通讯双方波特率应该相同
	m_BoudRate.InsertString(-1, "110");
	m_BoudRate.InsertString(-1, "300");
	m_BoudRate.InsertString(-1, "600");
	m_BoudRate.InsertString(-1, "1200");
	m_BoudRate.InsertString(-1, "2400");
	m_BoudRate.InsertString(-1, "9600");
	m_BoudRate.InsertString(-1, "14400");
	m_BoudRate.InsertString(-1, "19200");
	m_BoudRate.InsertString(-1, "38400");
	m_BoudRate.InsertString(-1, "56000");
	m_BoudRate.InsertString(-1, "115200");	
	m_BoudRate.SelectString(0, "38400");

	// 根据端口是否打开设置各个按钮的状态
	BOOL bOpen = FALSE;
	m_Open.EnableWindow(!bOpen);
	m_Send.EnableWindow(bOpen);
	m_Close.EnableWindow(bOpen);

	// 显示当前状态信息
	m_Status.SetWindowText(" 端口关闭 ");
	
	m_pComFile = new CSCSerial(true);
	m_pData = NULL;
	m_hServerThread = NULL;

	return TRUE; 
}

void CComFileDlg::OnButtonbrowser() 
{
	// 打开文件浏览对话框
	CFileDialog dlg(TRUE); 
	if(dlg.DoModal() == IDCANCEL)
	{
		return;
	}
	// 记录用户选择的文件
	m_EditFile.SetWindowText(dlg.GetPathName());	
}

void CComFileDlg::OnButtonclose() 
{
	// 如果端口已经关闭，则返回
	if(!m_pComFile->IsOpen())
		return;

	// 命令服务器线程退出
	m_bThreadExit = TRUE;

	DWORD dwExitCode;
	int n=0;
	while(!::GetExitCodeThread(m_hServerThread, &dwExitCode) && n++ < 20)
	{
		::Sleep(100);
	}
	::TerminateThread(m_hServerThread, 0);
	::CloseHandle(m_hServerThread);
	m_hServerThread = NULL;

	// 关闭COM端口
	m_pComFile->Close();
}

void CComFileDlg::OnButtonopen() 
{
	// 如果端口已经打开，则返回
	if(m_pComFile->IsOpen())
		return;

	// 获取用户选择的端口号
	int nPort = m_ComboPort.GetCurSel() + 1;

	// 获取用户选择的波特率	
	int nRate;
	CString str;
	m_BoudRate.GetWindowText(str);
	nRate = atoi(str);
	if(nRate == 0)	
		nRate = 9600;

	// 尝试打开端口
	if(!m_pComFile->Open(nPort, nRate))
	{
		m_Status.SetWindowText(" 打开端口出错！");
		return;
	}

	// 端口打开成功，显示当前状态信息
	m_Status.SetWindowText(" 端口已经打开 ");

	// 创建服务线程，监测任何到来的数据
	DWORD dwId;
	m_hServerThread = ::CreateThread(NULL, 0, ServerThreadProc, this, 0, &dwId);

	// 根据端口是否打开设置各个按钮的状态
	BOOL bOpen = TRUE;
	m_Open.EnableWindow(!bOpen);
	m_Send.EnableWindow(bOpen);
	m_Close.EnableWindow(bOpen);
}

void CComFileDlg::OnButtonsend() 
{
	// 如果端口已经关闭，则返回
	if(!m_pComFile->IsOpen())
	{
		return;	
	}

	// 检查当前状态，如果不为空闲（IDLE），则返回
	if(m_pComFile->m_nStatus != STATUS_IDLE)
	{
		MessageBox(" 正在接收文件，不能发送！！\r\n");
		return;
	}

	// 检查用户是否输入了要埋入的文件
	CString strFileName;
	m_EditFile.GetWindowText(strFileName);
	if(strFileName.IsEmpty())
	{
		MessageBox(" 输入要发送的文件！！");
		return;
	}

	// 试图访问要埋入的文件
	if(!m_SendFile.Open(strFileName, CFile::modeRead|CFile::shareDenyWrite))
	{
		MessageBox(" 打开文件出错！！！");
		return;
	}

	m_bNeedSend = TRUE;

	// 无效发送按钮，防止禁止用户多次点击
	m_Send.EnableWindow(FALSE);
}

void CComFileDlg::OnDestroy() 
{
	CRootDlg::OnDestroy();
	
	// 关闭端口，关闭事件对象，释放资源
	OnButtonclose();	
	delete m_pComFile;
}

void CComFileDlg::OnBtnClear() 
{
	m_Log.SetWindowText("");
}

void CComFileDlg::AddLog(LPCTSTR lpszString)		// 帮助函数，用于添加日志
{
	// 将字符串lpszString添加到日志窗口中
	CString str;
	m_Log.GetWindowText(str);
	str = lpszString + str;
	m_Log.SetWindowText(str);
}

BYTE CComFileDlg::SendConnect()
{
    // 发送
	CSerialFrame *pFrame;
	if(!m_pComFile->SendCommand(SERIAL_CONNECT))
	{
		AddLog(" 连接服务器失败，用户关闭串口！ \r\n ");
		return 0xff;
	}

	// 等待结果
	pFrame = m_pComFile->ReadData2();
	if(pFrame == NULL)
	{
		AddLog(" 连接服务器失败，对方没有响应！ \r\n ");
		return 0xff;
	}
	if(pFrame->command == SERIAL_ACK)
	{
		m_pComFile->m_nStatus = STATUS_CONNECTED;
		AddLog(" 成功连接到服务器 \r\n");
		return 0;
	}
	else
		return pFrame->command;
}

BYTE CComFileDlg::SendEOF()
{
	// 发送
	CSerialFrame *pFrame;
	if(!m_pComFile->SendCommand(SERIAL_EOF))
	{
		AddLog(" 用户关闭端口，文件发送失败！ \r\n ");
		return 0xff;
	}

	// 等待结果
	pFrame = m_pComFile->ReadData2();
	if(pFrame == NULL)
	{
		AddLog(" 对方没有响应，文件发送失败！ \r\n");
		return 0xff;
	}
	if(pFrame->command == SERIAL_ACK)
	{
		m_pComFile->m_nStatus = STATUS_IDLE;
		AddLog(" 文件发送成功完成 \r\n");
		return 0;
	}
	else
		return pFrame->command;
}

BOOL CComFileDlg::SendFile(CFile &file, CSCSerial *pSerial)
{
    DWORD dwTick = ::GetTickCount();	// 当前运行时间
	int n;								// 帧重发次数
	CString str;						// 临时字符串变量

	//////////////////////////////////////////////////
	// 准备发送文件
	AddLog(" 正在准备发送文件... \r\n");
	// 发送文件大小
	int nFileSize = file.GetLength(); 
	if(!pSerial->SendFileSize(nFileSize))
	{
		AddLog(" 发送文件大小失败！\r\n ");
		return FALSE;
	}


	//////////////////////////////////////////////////
	// 发送文件数据
	char Buffer[1024];			// 数据缓冲区
	int nRead;					// 从文件中每次读取的字节数
	DWORD dwTotalSendLen = 0;	// 总共发送的字节数
	// 初始化序列号为0
	pSerial->m_sequence = 0;
	AddLog(" 正在发送文件数据... \r\n ");

	while(TRUE)
	{
		// 从文件中读取数据到缓冲区
		nRead = file.Read(Buffer, 1024);
		if(nRead <= 0)
		{
			break;
		}

		// 发送缓冲区中的数据
		int nLeft = nRead;	// 剩余的字节数
		int nSendLen;		// 要发送的字节数
		while(nLeft > 0)
		{
			// 发送一个贞，如果发送失败，重试5次
			nSendLen = nLeft > FRAME_SIZE ? FRAME_SIZE : nLeft;
			n=0;
			while(!pSerial->SendFileData(&Buffer[nRead-nLeft], nSendLen) && n++<5)
			{
				if(!pSerial->IsOpen()) // 检查是否用户故意中止
				{
					AddLog(" 发送文件出错，用户关闭串口! \r\n");
					return FALSE;
				}
				str.Format(" 帧重发 %d 次 \r\n", n);
				AddLog(str);

			}
			if(n>=5)
			{
				m_Status.SetWindowText(" 发送文件出错！！！");
				return FALSE;
			}
			
			// 帧发送成功，更新状态变量
			nLeft -= nSendLen;
			dwTotalSendLen += nSendLen;

			// 向用户显示当前文件发送进度
			str.Format(" 已发送：%d KB，剩余：%d KB \r\n", 
							dwTotalSendLen/1024, (nFileSize - dwTotalSendLen)/1024);
			m_Status.SetWindowText(str);
		}
	}
	
	///////////////////////////////////////////////////////
	// 发送结束标志
	BYTE command = SendEOF();
	if(command != 0)	// 出错？
	{
		switch(command) // 检查出错原因
		{
		case SERIAL_TRANSFAILED:
			{
				m_Status.SetWindowText(" 文件传输完毕，但是有错误！ \r\n");
				AddLog(" 文件传输完毕，但是有错误！ \r\n");
			}
			break;
		}
		return FALSE;
	}

	// 文件发送完成，向用户显示用时
	DWORD dwEsp = ::GetTickCount() - dwTick; 
	str.Format(" 文件发送成功完成。[%d KB] 用时: %d 秒", nFileSize/1000, dwEsp/1000);
	AddLog(str);

	return TRUE;
}

DWORD WINAPI ServerThreadProc(LPVOID lpParam)	// 服务线程
{
	// 提高当前线程优先级
	::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);

	// 将处理权交给主窗口类
	CComFileDlg *pDlg = (CComFileDlg *)lpParam;
	pDlg->AddLog("    服务器线程启动... \r\n");
	pDlg->m_bNeedSend = FALSE;
	DWORD dw = pDlg->ServerProc();
	pDlg->AddLog("    服务器线程退出... \r\n");

	pDlg->m_pComFile->SendInit();

	return dw;
}

DWORD CComFileDlg::ServerProc()
{
	CSerialFrame *pFrame;				// 帧指针
	CSCSerial *m_pServer = m_pComFile;	// CSCSerial对象指针（作为服务器用）

	// 状态初始化为IDLE
	m_pServer->m_nStatus = STATUS_IDLE;

	// 禁止线程退出
	m_bThreadExit = FALSE;
	
	// 进入无限循环，处理从COM口接收到的数据
	int n=0;		// 帧重发次数
	while(TRUE)
	{
		// 等待数据的到来
		while((pFrame = m_pServer->ReadFrame()) == NULL)
		{
			if(m_bThreadExit || !m_pComFile->IsOpen())
			{
				AddLog(" 用户请求线程退出 \r\n");
				return 0;
			}

			// 检查是否需要发送文件
			if(m_bNeedSend)
			{
				AddLog(" 正在准备发送文件... \r\n");
				m_pServer->m_nStatus = STATUS_IDLE;
				if(Connect())
				{
					AddLog(" 连接成功 \r\n");
					if(!SendFile(m_SendFile, m_pServer))
					{
						AddLog(" 发送文件失败\r\n");
						m_Status.SetWindowText(" 发送文件失败\r\n");
					}
					else
					{
						AddLog(" 发送文件成功 \r\n");
						m_Status.SetWindowText(" 发送文件成功 \r\n");
					}
				}
				m_pServer->m_nStatus = STATUS_IDLE;
				m_bNeedSend = FALSE;
				if(m_pComFile->IsOpen())
					m_Send.EnableWindow();
			}
		}
		
		// 检查贞大小
		if(pFrame->uDataLen > FRAME_SIZE)
		{
			AddLog(" CServerDlg::ThreadProc() 帧传输出错！\r\n");
			m_pComFile->Purge();
			continue;
		}
		
		// 传输其他字节
		if(pFrame->uDataLen > 0)
		{
			if(!m_pComFile->ReadData(pFrame + 1, pFrame->uDataLen, 500))
			{
				if(m_bThreadExit || !m_pComFile->IsOpen())
				{
					AddLog(" 用户请求线程退出 \r\n");
					return 0;
				}
				m_pComFile->Purge();
				AddLog(" CServerDlg::ThreadProc()  读取数据超时 \r\n");
				continue;  
			}
		}
		
		// 检查效验位
		int nChecksum = pFrame->uChecksum;
		pFrame->uChecksum = 0;
		if(nChecksum != checksum((USHORT*)pFrame, sizeof(CSerialFrame) + pFrame->uDataLen))
		{
			AddLog(" CServerDlg::ThreadProc()  数据效验出错  请求重新传送\r\n");
			
			// 请求重发
			m_pServer->SendRetry();
			continue;
		}
		
		///////////////////////////////////////////////
		// 处理命令

		switch(pFrame->command)
		{
		case SERIAL_CONNECT:		// 连接过程
			{
				if(m_pServer->m_nStatus == STATUS_IDLE || m_pServer->m_nStatus == STATUS_CONNECTED)
				{
					m_pServer->SendAck();
					m_pServer->m_sequence = 0;
					m_pServer->m_nStatus = STATUS_CONNECTED;
					
					AddLog(" 接收到新连接，正准备接收文件... \r\n");
					m_Status.SetWindowText(" 接收到新连接，正准备接收文件... \r\n");
				}
				else
				{
					m_pServer->SendInit();
					m_pServer->m_nStatus = STATUS_IDLE;
					AddLog(" 接收到非法连接，要求初始化 \r\n");
				}
			}
			break;
		case SERIAL_INIT:		// 对方请求重新初始化
			{
				AddLog(" 对方要求重新初始化 \r\n ");
				m_pServer->SendAck();
				m_pServer->m_nStatus = STATUS_IDLE;
			}
			break;
		case SERIAL_SIZE:	// 对方发送文件大小信息，接收到此命令就要进行文件传输
			{
				if(m_pServer->m_nStatus == STATUS_CONNECTED)
				{
					m_dwFileLen = *(DWORD*)(pFrame+1);
					if(m_dwFileLen > 200*1024*1024)
					{
						m_pServer->SendCommand(SERIAL_TOOBIG);
						AddLog(" 文件太大，拒绝接收（应小于200MB） \r\n");
						continue;
					}
					
					// 为文件数据申请内存空间
					m_pData = new BYTE[m_dwFileLen];
					if(m_pData == NULL)
					{
						m_pServer->SendCommand(SERIAL_SYSFAILED);
						AddLog("  内存不足！传输失败 \r\n");
						continue;
					}
					m_pServer->SendAck();
					m_dwRecvLen = 0;
					m_pServer->m_nStatus = STATUS_TRANSFERING;
				}
				else
				{
					m_pServer->SendInit();
					AddLog(" 接收到非法命令，要求初始化 \r\n");	
				}
			}
			break;
		case SERIAL_DATA:   // 读数据
			{
				if(m_pServer->m_nStatus != STATUS_TRANSFERING)
				{
					m_pServer->SendInit();
					AddLog(" 接收到非法命令，要求初始化 \r\n");	
					continue;
				}

				// 定位实际数据
				char *psz = (char*)(pFrame+1);
				if(pFrame->sequence == m_pServer->m_sequence)
				{
					m_pServer->m_sequence++;
					if(m_pData == NULL)  // 检查指针是否有效
					{
						AddLog(" 程序问题，没有准备好传输 \r\n");
						m_pServer->SendInit();
						continue;
					}
					if(!m_pServer->SendAck())
					{
						m_pServer->SendInit();
						m_Status.SetWindowText(" 用户关闭串口，传输非法终止!! ");

						AddLog(" 用户关闭串口，传输非法终止!! ");
						
						delete[] m_pData;
						m_pData = NULL;
						m_dwRecvLen = 0;
						m_dwFileLen = 0;
						continue;
					}

					// 接收数据
					memcpy(&m_pData[m_dwRecvLen], pFrame+1, pFrame->uDataLen);
					m_dwRecvLen += pFrame->uDataLen;

					// 显示文件传输进度
					CString str;
					str.Format("已经接收 【%d KB】，剩余【%d KB】", 
									m_dwRecvLen/1024, (m_dwFileLen-m_dwRecvLen)/1024);
					m_Status.SetWindowText(str);
				}
				else if(pFrame->sequence < m_pServer->m_sequence) // 客户重发的贞，忽略
				{
					m_pServer->SendAck();
					AddLog(" 对方等待时间过短，收到重发贞 \r\n");
					continue;
				}
				else  // 序列号错误？
				{
					AddLog(" 数据序列号出错 要求重新初始化 \r\n");
					// 重新初始化
					m_pServer->SendInit();
					continue;
				}
			}
			break;
			
		case SERIAL_EOF:	// 接收文件结束，开始打印
			{
				if(m_pServer->m_nStatus == STATUS_TRANSFERING)
				{
					if(m_dwRecvLen == m_dwFileLen)
					{
						m_pServer->SendAck();

						// 处理接收到的文件数据
						OnRecvCmp(m_pData, m_dwFileLen);

						delete m_pData;
						m_pData = NULL;
						m_dwFileLen = 0;
							
						AddLog(" 文件传输成功完成！\r\n");	
					}
					else
					{			
						// 请求对方重新传输
						m_pServer->SendCommand(SERIAL_TRANSFAILED);
						m_Status.SetWindowText(" 文件传输完成，但是有错误！\r\n");
						AddLog(" 文件传输出错！\r\n");
					}
					m_pServer->m_nStatus = STATUS_IDLE;
				}
				else
				{
					AddLog(" 接收到非法命令，要求初始化 \r\n");
					m_pServer->SendInit();	
				}
			}
			break;
		default:
			m_Status.SetWindowText(" 接收到非法命令 \r\n");
			AddLog(" 接收到非法命令 \r\n");
			m_pServer->m_nStatus = STATUS_IDLE;
			break;;
		}
	}
	return 0;
}

BOOL CComFileDlg::Connect()
{
BYTE command;  // 命令
	do
	{
		// 发送连接命令
		command = SendConnect();
		if(command != 0)		// 连接失败
		{
			switch(command)		// 查看失败原因
			{
			case SERIAL_INIT:			// 需要初始化，则重新连接
				{
					continue;
				}
				break;
			case SERIAL_VERIFYFAILED:	// 用户验证失败
				{
					MessageBox(" 用户验证失败，请检查读卡器！\r\n");
					AddLog(" 用户验证失败，请检查读卡器！\r\n");
				}
				break;
			default:
				{
					MessageBox(" 连接服务器失败，对方没有响应！\r\n ");
					AddLog(" 连接服务器失败，对方没有响应！\r\n ");
				}
				break;
			}
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	while(TRUE);

	// 不会运行到这里
	return FALSE;
}

void CComFileDlg::OnRecvCmp(PBYTE pData, DWORD dwFileLen)	// 文件接收完毕
{
	CFileDialog dlg(FALSE); 
	if(dlg.DoModal() == IDCANCEL)
	{
		return;
	}

	// 将数据保存到文件
	CFile file;
	if(!file.Open(dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite))
	{
		m_Status.SetWindowText(" 创建文件失败！");
		return;
	}
	file.WriteHuge(pData, dwFileLen);
	file.Close();
}
