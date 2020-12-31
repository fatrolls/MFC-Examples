wininet实现ftp客户端关于传输进度的分析2004-07-18 21:14 wininet提供了接口FtpGetFile实现从ftp服务器下载文件；提供了接口FtpPutFile实现把文件上传到ftp服务器上。通过这两个接口，我们能够完成基本的ftp文件传输客户端功能。但是在传输的同时，我们希望知道当前大概传输了多少，传输完整个文件大概需要多长时间，当前进度是多少，大概还有多长时间才能传输完毕。
单纯依靠这两个接口，我们无法实现这个功能。仔细翻阅msdn，发现wininet还提供了这样一个接口：InternetSetStatusCallback。该函数就是设置文件传输的回调函数，其原型如下：
INTERNET_STATUS_CALLBACKInternetSetStatusCallback(  HINTERNEThInternet,  INTERNET_STATUS_CALLBACKlpfnInternetCallback);该接口为internet会话设置一个状态回调函数：lpfnInternetCallback，该回调函数的原型声明如下：
void CALLBACKInternetStatusCallback(  HINTERNEThInternet,  DWORD_PTRdwContext,  DWORDdwInternetStatus,  LPVOIDlpvStatusInformation,  DWORDdwStatusInformationLength);通过这个回调函数，我们可以实现对当前传输进度的控制：可以统计出到目前已经传输了多少字节，并且计算出传输速率，从而可以得知大概还剩下多少时间。
下面这个类就是实现对ftp文件传输客户端的封装：
 
//////////////////////////////////////////////////////////////////////////
// 模块名称：文件传输状态控制
// 模块功能：实现对界面时时报告当前文件传输的进度状态，并且实现上传和下载
//             文件的客户端功能。
// 文件名称：ftpclientctrl.h
//________________________________________________________________________
#ifndef _WININET_
#include <wininet.h>
#endif
 
class CFtpClientCtrl 
{
public:
CFtpClientCtrl();
virtual ~CFtpClientCtrl();
enum
{
        ftp_begin,              // 对于该事件，wparam = ftp_begin，lparam表示要传输的文件大小
        ftp_transfer,    // 对于该事件，wparam = ftp_transfer，lParam表示已经传输的大小
        ftp_end                 // 对于该事件，wparam = ftp_end，lparam表示结果，0--失败，1--成功
};
 
// 设置ftp服务器的连接参数
BOOL     SetServerParam(    LPCTSTR lpszIpAddr,   // IP地址
                                           LPCTSTR lpszUser,      // 登录名称
                                           LPCTSTR lpszPwd,      // 登录口令
                                           WORD    wPort = INTERNET_DEFAULT_FTP_PORT,     // FTP服务器端口
                                           LPCTSTR lpszProxyName = NULL,    // 代理名称
                                           LPCTSTR lpszProxyPwd = NULL);     // 代理口令
 
// 开始下载文件
BOOL     BeginDownload(     HWND hWnd,                     // 接收消息的窗口
                                           LPCTSTR lpszRemote,  // 远程文件名称
                                           LPCTSTR lpszLocal,     // 保存本地的文件
                                           DWORD dwFileType = FTP_TRANSFER_TYPE_UNKNOWN);      // 文件传输
BOOL     BeginDownload(     DWORD dwThread,                    // 接收消息的线程
                                           LPCTSTR lpszRemote,  // 远程文件名称
                                           LPCTSTR lpszLocal,     // 保存本地的文件
                                           DWORD dwFileType = FTP_TRANSFER_TYPE_UNKNOWN);      // 文件传输
// 开始上传文件
BOOL     BeginUpload(  HWND hWnd,                     // 接收消息的窗口
                                           LPCTSTR lpszRemote,  // 远程文件名称
                                           LPCTSTR lpszLocal,     // 本地文件名称
                                           DWORD dwFileType = FTP_TRANSFER_TYPE_UNKNOWN);      // 文件传输
BOOL     BeginUpload(  DWORD dwThread,                    // 接收消息的线程
                                           LPCTSTR lpszRemote,  // 远程文件名称
                                           LPCTSTR lpszLocal,     // 本地文件名称
                                           DWORD dwFileType = FTP_TRANSFER_TYPE_UNKNOWN);      // 文件传输
// 结束传输文件
BOOL     EndFtpFile();
 
// 得到当前ftp的会话句柄
HINTERNET  GetCurrentSession() const{return m_hSession;}
// 得到当前的连接句柄
HINTERNET  GetCurrentConnect() const{return m_hConnect;}
// 获取远程文件名称
LPCTSTR             GetCurrentRemoteFile() const{return m_szRemote;}
// 获取本地文件名称
LPCTSTR             GetCurrentLocalFile() const{return m_szLocal;}
// 获取当前传输的文件类型
DWORD        GetCurrentFileType() const{return m_dwFileType;}
// 获取当前传输接收消息窗口
HWND           GetCurrentFtpWnd() const{return m_hWnd;}
// 获取当前传输接收消息线程
DWORD        GetCurrentFtpThread() const{return m_dwThread;}
// 获取当前已经传输的大小
DWORD        GetCurrentFtpSize() const{return m_dwCurrentFtpSize;}
// 递增已经传输的大小
DWORD        IncreaseFtpSize(DWORD dwStep);
// 注册一个消息
void        RegisterMsgHandle(UINT uMsgHandle){m_uMsgHandle = uMsgHandle;}
// 获取已经注册的消息
UINT             GetRegisterMsgHandle() const{return m_uMsgHandle;}
// 获取文件总长度
DWORD        GetTotalFileSize() const{return m_dwTotalFileSize;}
// 清除FTP
void        ClearFtpSession();
// 设置FTP传输方向
void        SetFtpDirect(BOOL bDownload = TRUE){m_bFtpDirect = bDownload;}
// 获取FTP传输方向
BOOL            GetFtpDirect() const{return m_bFtpDirect;}
// 判断文件类型是否是ASCII
static BOOL           IsFileAscii(LPCTSTR lpszFile);
protected:
// 获取远程文件的大小
DWORD GetRemoteFileSize();
// 获取本地文件的大小
DWORD GetLocalFileSize();
// 下载文件
BOOL     DownloadFile(       LPCTSTR lpszRemote,  // 远程文件名称
                                           LPCTSTR lpszLocal,     // 保存本地的文件
                                           DWORD dwFileType = FTP_TRANSFER_TYPE_UNKNOWN);      // 文件传输
// 上传文件
BOOL     UploadFile(     LPCTSTR lpszRemote,  // 远程文件名称
                                    LPCTSTR lpszLocal,     // 保存本地的文件
                                    DWORD dwFileType = FTP_TRANSFER_TYPE_UNKNOWN);      // 文件传输
protected:
HINTERNET  m_hSession;          // 应用于InternetOpen
HINTERNET  m_hConnect;         // 应用于InternetConnect
 
TCHAR          m_szFtpSrvIp[24]; // FTP服务器的ip地址
TCHAR          m_szFtpSrvUser[32];    // FTP服务器的登录用户
TCHAR          m_szFtpSrvPwd[32];    // FTP服务器的登录口令
TCHAR          m_szProxyName[64];    // 代理的名称
TCHAR          m_szProxyPwd[32];             // 代理的口令
WORD           m_wFtpSrvPort;           // FTP服务器的监听端口
 
HANDLE        m_hFtpThread;             // FTP传输的线程句柄
DWORD        m_dwFtpThread;          // FTP传输的线程编号
 
TCHAR          m_szRemote[MAX_PATH];          // 远程文件
TCHAR          m_szLocal[MAX_PATH];             // 本地文件
DWORD        m_dwFileType;             // 传输的文件类型
 
HWND           m_hWnd;                     // 接收传输进度消息的窗口
DWORD        m_dwThread;        // 接收传输进度消息的线程
 
DWORD        m_dwCurrentFtpSize;    // 当前传输的大小
DWORD        m_dwTotalFileSize;       // 文件总大小
 
UINT             m_uMsgHandle;     // 消息句柄，由外界定义
 
BOOL            m_bFtpDirect;       // 传输方向，TRUE为下载，FALSE为上传，默认为TRUE
 
public:
DWORD        m_dwFtpHead;      // FTP传输头--自从InternetConnect之后发送的次数
private:
BOOL            m_bTransfering;    // 是否正在传输
};
 
//////////////////////////////////////////////////////////////////////////
// 模块名称：文件传输状态控制
// 模块功能：实现对界面时时报告当前文件传输的进度状态，并且实现上传和下载
//             文件的客户端功能。
// 文件名称：ftpclientctrl.cpp
//________________________________________________________________________
#include "FtpClientCtrl.h"
#pragma comment(lib, "wininet.lib")
#define INTERNET_STATUS_USER_INPUT_REQUIRED         0x00000040
#define INTERNET_STATUS_DETECTING_PROXY               80
 
 
#define FTP_FILE_ASCII_COUNT      12
LPCTSTR g_lpszAsciiFileFtp[FTP_FILE_ASCII_COUNT] =
{
_T(".txt"),
_T(".ini"),
_T(".c"),
_T(".cpp"),
_T(".h"),
_T(".hpp"),
_T(".bat"),
_T(".html"),
_T(".java"),
_T(".htm"),
_T(".jav"),
_T(".doc")
};
 
//////////////////////////////////////////////////////////////////////////
// 名称：IsFtpAscii
// 描述：经验判断一个要进行文件传输的文件是否是ASCII方式的
// 原型：BOOL IsFtpAscii(LPCTSTR lpszExt)    // 文件后缀
// 参数：
//             [in] lpszExt：要判断的文件的后缀名称
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
BOOL IsFtpAscii(LPCTSTR lpszExt)
{
if(lpszExt == NULL)
        return FALSE;
for(int nIndex = 0; nIndex < FTP_FILE_ASCII_COUNT; nIndex ++)
{
        if(_tcsicmp(lpszExt, g_lpszAsciiFileFtp[nIndex]) == 0)
               return TRUE;
}
return FALSE;
}// End IsFtpAscii
// IsFtpAscii结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：FormatFtpError
// 描述：获取系统的错误描述
// 原型：void FormatFtpError(DWORD dwError,      // 错误码
//                                                LPTSTR *lpMsg)   // 描述信息
// 参数：
//             [in] dwError：要查询的系统错误码
//             [out] *lpMsg：获取得到的错误描述信息，在使用结束后，请调用LocalFree
//                                  来释放该空间
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
static void FormatFtpError(    DWORD dwError,        // 系统错误码
                                                  LPTSTR *lpMsg)   // 错误描述
{
if(lpMsg == NULL)return;
if(dwError > INTERNET_ERROR_BASE)
{
        // 对于Internet的错误，要特殊处理
        DWORD dwBufLen = 0;
        InternetGetLastResponseInfo(&dwError, NULL, &dwBufLen);
        LPTSTR pMsg = (LPTSTR)LocalAlloc(LMEM_ZEROINIT, dwBufLen + 1);
        InternetGetLastResponseInfo(&dwError, pMsg, &dwBufLen);
        *lpMsg = pMsg;
}
else
{
        // 查询普通的错误
        FormatMessage(    FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                    FORMAT_MESSAGE_IGNORE_INSERTS |
                                   FORMAT_MESSAGE_FROM_SYSTEM,
                                    NULL,
                                    dwError,
                                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                    (LPSTR)lpMsg,
                                    0,
                                    NULL);
}
}// End FormatFtpError
// FormatFtpError结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：FtpCtrl_CallbackStatus
// 描述：文件传输过程中的状态回调函数，用于报告当前文件传输的进度等消息
// 原型：void CALLBACK FtpCtrl_CallbackStatus(     HINTERNET hInternet,// 句柄
//                                                                            DWORD dwContext, // 上下文
//                                                                            DWORD dwInternetStatus, // 状态
//                                                                            LPVOID lpvStatusInformation,// 信息
//                                                                            DWORD dwStatusInformationLength)
// 参数：
//             [in] hInternet：Internet连接的句柄，从InternetOpen中得到
//             [in] dwContext：自定义的上下文数据
//             [in] dwInternetStatus：当前回调的状态
//             [in] lpvStatusInformation：当前回调的信息，根据dwInternetStatus的不同
//                                         状态代表不同的意思
//             [in] dwStatusInformationLength：回调信息lpvStatusInformation的长度
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
void CALLBACK FtpCtrl_CallbackStatus(     HINTERNET hInternet,
                                                                DWORD dwContext,
                                                                DWORD dwInternetStatus,
                                                                LPVOID lpvStatusInformation,
                                                                DWORD dwStatusInformationLength)
{
// 获取上下文信息
CFtpClientCtrl *pcFtpMsg = reinterpret_cast<CFtpClientCtrl*>(dwContext);
if(pcFtpMsg == NULL)
{
        return;
}
LPDWORD pdwInformation(NULL);
TRACE("FtpCtrl_CallbackStatus's Internet Status is %d/n", dwInternetStatus);
// 查询当前文件传输状态
switch(dwInternetStatus)
{
case INTERNET_STATUS_RESOLVING_NAME:      // 10
        TRACE("Looking up the IP address for %s/n", (LPCTSTR)lpvStatusInformation);
        break;
case INTERNET_STATUS_NAME_RESOLVED:        // 11
        TRACE("Name resolved %s/n", (LPCTSTR)lpvStatusInformation);
        break;
case INTERNET_STATUS_CONNECTING_TO_SERVER:       // 20
        // lpvStatusInformation是一个SOCKADDR的指针
        TRACE("Connecting to server--%s.../n", (LPCTSTR)lpvStatusInformation);
        break;
case INTERNET_STATUS_CONNECTED_TO_SERVER:  // 21
        // lpvStatusInformation是一个SOCKADDR的指针
        TRACE("Connected to server--%s/n", (LPCTSTR)lpvStatusInformation);
        break;
case INTERNET_STATUS_SENDING_REQUEST:           // 30
        TRACE("Sending request/n");
        break;
case INTERNET_STATUS_REQUEST_SENT:                  // 31
        {
               // 发送数据到服务器
               if(!pcFtpMsg->GetFtpDirect())
               {
                      // 只有当处于上传状态的时候，才处理
                      if(pcFtpMsg->m_dwFtpHead > 0 && pcFtpMsg->m_dwFtpHead < 5)
                      {
                             // 5这个值是一个经验值，具体为什么，由于没有深入研究rfc的协议
                             // 所以还不知道，将来如果知道原因，可以补充上
                             pcFtpMsg->m_dwFtpHead ++;
                      }
                      pdwInformation = (LPDWORD)lpvStatusInformation;
                      if(pcFtpMsg->m_dwFtpHead == 5)
                      {
                             DWORD dwCurrentSize = pcFtpMsg->IncreaseFtpSize(*pdwInformation);
                             TRACE("本次发送的数据大小为: %d，总共数据为：%d/n", *pdwInformation,
                                    dwCurrentSize);
                             if(pcFtpMsg->GetCurrentFtpWnd() != NULL)
                             {
                                    // 首先的第一选择是给窗口发送消息
                                    ::PostMessage(       pcFtpMsg->GetCurrentFtpWnd(),
                                                                pcFtpMsg->GetRegisterMsgHandle(),
                                                                CFtpClientCtrl::ftp_transfer,
                                                                dwCurrentSize);
                             }
                             else if(pcFtpMsg->GetCurrentFtpThread() != 0)
                             {
                                    ::PostThreadMessage(pcFtpMsg->GetCurrentFtpThread(),
                                                                       pcFtpMsg->GetRegisterMsgHandle(),
                                                                       CFtpClientCtrl::ftp_transfer,
                                                                       dwCurrentSize);
                             }
                      }// End if 5，经验值
               }// end if 文件上传
        }
        break;
case INTERNET_STATUS_RESPONSE_RECEIVED:        // 41
        {
               // 从服务器接收到的响应
               if(pcFtpMsg->GetFtpDirect())
               {
                      // 只有当处于下载状态的时候，才处理
                      pdwInformation = (LPDWORD)lpvStatusInformation;
                      if(pcFtpMsg->m_dwFtpHead > 0 && pcFtpMsg->m_dwFtpHead < 6)
                      {
                             // 6这个值是一个经验值，具体为什么，由于没有深入研究rfc的协议
                             // 所以还不知道，将来如果知道原因，可以补充上
                             pcFtpMsg->m_dwFtpHead ++;
//                                  TRACE("在连接之后第%d次接收数据！/n", pcFtpMsg->m_dwFtpHead);
                      }
                      if(pcFtpMsg->m_dwFtpHead == 6)
                      {
                             DWORD dwCurrentSize = pcFtpMsg->IncreaseFtpSize(*pdwInformation);
                             TRACE("Response received: %d, TotalReceived is %d/n",
                                    *pdwInformation, dwCurrentSize);
                             if(pcFtpMsg->GetCurrentFtpWnd() != NULL)
                             {
                                    ::PostMessage(       pcFtpMsg->GetCurrentFtpWnd(),
                                                                pcFtpMsg->GetRegisterMsgHandle(),
                                                                CFtpClientCtrl::ftp_transfer,
                                                                dwCurrentSize);
                             }
                             else if(pcFtpMsg->GetCurrentFtpThread() != 0)
                             {
                                    ::PostThreadMessage(pcFtpMsg->GetCurrentFtpThread(),
                                                                       pcFtpMsg->GetRegisterMsgHandle(),
                                                                       CFtpClientCtrl::ftp_transfer,
                                                                       dwCurrentSize);
                             }
                      }// End if 6，经验值
               }// End if 文件下载
        }
        break;
case INTERNET_STATUS_RECEIVING_RESPONSE:             // 40
        // 等待服务器的响应，lpvStatusInformation = NULL
        TRACE("等待服务器的响应！/n");
        break;
case INTERNET_STATUS_CTL_RESPONSE_RECEIVED:              // 42
case INTERNET_STATUS_PREFETCH:                                 // 43
case INTERNET_STATUS_CLOSING_CONNECTION:           // 50
        TRACE("Closing connection/n");
        break;
case INTERNET_STATUS_CONNECTION_CLOSED:                    // 51
        TRACE("Connection closed/n");
        break;
case INTERNET_STATUS_HANDLE_CREATED:                    // 60
        {
               LPINTERNET_ASYNC_RESULT ptIAR =
                      reinterpret_cast<LPINTERNET_ASYNC_RESULT>(lpvStatusInformation);
               if(hInternet == pcFtpMsg->GetCurrentConnect())
               {
                      TRACE("Connect Handle Created!/n");
                      pcFtpMsg->m_dwFtpHead = 1;
               }
               else if(hInternet == pcFtpMsg->GetCurrentSession())
               {
                      TRACE("Session handle created!/n");
               }
        }
        break;
case INTERNET_STATUS_HANDLE_CLOSING:                    // 70
        pcFtpMsg->m_dwFtpHead = 0;
        TRACE("Handle closed with dif %d!/n",
               pcFtpMsg->GetCurrentFtpSize() - pcFtpMsg->GetTotalFileSize());
        break;
case INTERNET_STATUS_DETECTING_PROXY:                  // 80
        TRACE("Detecting proxy/n");
        break;
case INTERNET_STATUS_REQUEST_COMPLETE:               // 100
        // 一个异步操作已经完成，lpvStatusInformation是INTERNET_ASYNC_RESULT的指针
        {
               LPINTERNET_ASYNC_RESULT ptIAR =
                      reinterpret_cast<LPINTERNET_ASYNC_RESULT>(lpvStatusInformation);
               TRACE("一个异步操作完成，错误为：%d，结果为：%d/n",
                      ptIAR->dwError, ptIAR->dwResult);
        }
        break;
case INTERNET_STATUS_REDIRECT:                                  // 110
        TRACE("HTTP request redirected to /n");
        break;
case INTERNET_STATUS_INTERMEDIATE_RESPONSE:             // 120
        TRACE("Received intermediate status message from the server./n");
        break;
case INTERNET_STATUS_STATE_CHANGE:                         // 200
        TRACE("'Moved between a secure and a nonsecure site/n");
        {
               LPDWORD pdwRead = (LPDWORD)lpvStatusInformation;
               switch(*pdwRead)
               {
               case INTERNET_STATE_CONNECTED:                  // 0x00000001
                      TRACE("Connected state moved between secure and nonsecure site/n");
                      break;
               case INTERNET_STATE_DISCONNECTED:            // 0x00000002
                      TRACE("Disconnected from network/n");
                      break;
               case INTERNET_STATE_DISCONNECTED_BY_USER:   // 0x00000010
                      TRACE("Disconnected by user request/n");
                      break;
               case INTERNET_STATE_IDLE:                        // 0x00000100
                      TRACE("No network requests are being made (by Wininet)./n");
                      break;
               case INTERNET_STATE_BUSY:                       // 0x00000200
                      TRACE("Network requests are being made (by Wininet)./n");
                      break;
               case INTERNET_STATUS_USER_INPUT_REQUIRED:    // 0x00000040
                      TRACE("The request requires user input to complete/n");
                      break;
               default:
                      break;
               }
        }
        break;
default:
        break;
}
}// End Ftp_CallbackStatus
// Ftp_CallbackStatu结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：FtpClientDnloadThread
// 描述：文件传输——下载客户端线程
// 原型：DWORD WINPAI FtpClientDnloadThread(LPVOID pParam)     // 入口参数
// 参数：
//             [in] pParam：下载文件的入口参数
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
DWORD WINAPI FtpClientDnloadThread(LPVOID pParam)     // 入口参数
{
CFtpClientCtrl *pcFtpMsg = reinterpret_cast<CFtpClientCtrl*>(pParam);
if(pcFtpMsg == NULL)
{
        return -1;
}
 
// 获取文件
BOOL bRet = FtpGetFile(      pcFtpMsg->GetCurrentConnect(),
                                           pcFtpMsg->GetCurrentRemoteFile(),
                                           pcFtpMsg->GetCurrentLocalFile(),
                                           FALSE,
                                           FILE_ATTRIBUTE_NORMAL,
                                           pcFtpMsg->GetCurrentFileType() |
                                           INTERNET_FLAG_RELOAD |
                                           INTERNET_FLAG_RESYNCHRONIZE,
                                           (DWORD)pcFtpMsg);
LPTSTR lpMsg = NULL;
DWORD dwErr = GetLastError();
FormatFtpError(dwErr, &lpMsg);
TRACE("FtpGetFile Error with %d--%s/n", dwErr, lpMsg);
LocalFree(lpMsg);
lpMsg = NULL;
 
if(pcFtpMsg->GetCurrentFtpWnd() != NULL)
{
        ::PostMessage(       pcFtpMsg->GetCurrentFtpWnd(),
                                    pcFtpMsg->GetRegisterMsgHandle(),
                                    CFtpClientCtrl::ftp_end,
                                    dwErr);
}
else if(pcFtpMsg->GetCurrentFtpThread() != 0)
{
        ::PostThreadMessage(pcFtpMsg->GetCurrentFtpThread(),
                                           pcFtpMsg->GetRegisterMsgHandle(),
                                           CFtpClientCtrl::ftp_end,
                                           dwErr);
}
pcFtpMsg->ClearFtpSession();
 
TRACE("FtpGetFile Thread with id 0x%x end!/n", GetCurrentThreadId());
 
if(!bRet)
        return -1;
 
return 0;
}// End FtpClientDnloadThread
// FtpClientDnloadThread结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：FtpClientUploadThread
// 描述：文件传输——上传文件线程
// 原型：DWORD WINAPI FtpClientUploadThread(LPVOID pParam)     // 入口参数
// 参数：
//             [in] pParam：上传文件需要的参数
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
DWORD WINAPI FtpClientUploadThread(LPVOID pParam)
{
CFtpClientCtrl *pcFtpMsg = reinterpret_cast<CFtpClientCtrl*>(pParam);
if(pcFtpMsg == NULL)
{
        return -1;
}
 
// 上传文件
BOOL bRet = FtpPutFile(      pcFtpMsg->GetCurrentConnect(),
                                           pcFtpMsg->GetCurrentLocalFile(),
                                           pcFtpMsg->GetCurrentRemoteFile(),
                                           pcFtpMsg->GetCurrentFileType() |
                                           INTERNET_FLAG_RESYNCHRONIZE,
                                           (DWORD)pcFtpMsg);
LPTSTR lpMsg = NULL;
DWORD dwErr = GetLastError();
FormatFtpError(dwErr, &lpMsg);
TRACE("FtpPutFile Error with %d--%s/n", dwErr, lpMsg);
LocalFree(lpMsg);
lpMsg = NULL;
if(pcFtpMsg->GetCurrentFtpWnd() != NULL)
{
        ::PostMessage(       pcFtpMsg->GetCurrentFtpWnd(),
                                    pcFtpMsg->GetRegisterMsgHandle(),
                                    CFtpClientCtrl::ftp_end,
                                    dwErr);
}
else if(pcFtpMsg->GetCurrentFtpThread() != 0)
{
        ::PostThreadMessage(pcFtpMsg->GetCurrentFtpThread(),
                                           pcFtpMsg->GetRegisterMsgHandle(),
                                           CFtpClientCtrl::ftp_end,
                                           dwErr);
}
 
pcFtpMsg->ClearFtpSession();
TRACE("FtpPutFile Thread with id 0x%x end!/n", GetCurrentThreadId());
if(!bRet)
{
        return -1;
}
return 0;
}// End FtpClientUploadThread
// FtpClientUploadThread结束
//////////////////////////////////////////////////////////////////////////
 
CFtpClientCtrl::CFtpClientCtrl()
               :m_wFtpSrvPort(INTERNET_DEFAULT_FTP_PORT)
               ,m_hSession(NULL)
               ,m_hConnect(NULL)
               ,m_hFtpThread(NULL)
               ,m_dwFtpThread(0)
               ,m_dwCurrentFtpSize(0)
               ,m_hWnd(NULL)
               ,m_dwFileType(FTP_TRANSFER_TYPE_UNKNOWN)
               ,m_uMsgHandle(0)
               ,m_bFtpDirect(TRUE)
               ,m_dwFtpHead(0)
               ,m_bTransfering(FALSE)
{
::ZeroMemory(m_szFtpSrvIp, 24);
::ZeroMemory(m_szFtpSrvPwd, 32);
::ZeroMemory(m_szFtpSrvUser, 32);
::ZeroMemory(m_szProxyName, 64);
::ZeroMemory(m_szProxyPwd, 32);
::ZeroMemory(m_szRemote, MAX_PATH);
::ZeroMemory(m_szLocal, MAX_PATH);
}
 
CFtpClientCtrl::~CFtpClientCtrl()
{
InternetCloseHandle(m_hConnect);
InternetCloseHandle(m_hSession);
}
 
//////////////////////////////////////////////////////////////////////////
// 名称：SetServerParam
// 描述：设置文件传输的FTP服务器参数，包括服务器的地址、端口、用户和，口令等
// 原型：BOOL SetServerParam(LPCTSTR lpszIpAddr,     // 服务器地址
//                                                LPCTSTR lpszUser,             // 用户
//                                                LPCTSTR lpszPwd,             // 口令
//                                                WORD wPort,                     // 端口
//                                                LPCTSTR lpszProxyName,   // 代理名称
//                                                LPCTSTR lpszProxyPwd)    // 代理口令
// 参数：
//             [in] lpszIpAddr：FTP服务器的地址
//             [in] lpszUser：FTP服务器的用户名称
//             [in] lpszPwd：FTP服务器的用户口令
//             [in] wPort：FTP服务器的侦听端口
//             [in] lpszProxyName：FTP服务器的代理用户
//             [in] lpszProxyPwd：FTP服务器的代理对应口令
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
BOOL CFtpClientCtrl::SetServerParam(LPCTSTR lpszIpAddr,
                                                         LPCTSTR lpszUser,
                                                         LPCTSTR lpszPwd,
                                                         WORD wPort,
                                                         LPCTSTR lpszProxyName,
                                                         LPCTSTR lpszProxyPwd)
{
if(    lpszIpAddr == NULL ||
        lpszUser == NULL ||
        lpszPwd == NULL ||
        wPort == 0)
        return FALSE;
::ZeroMemory(m_szFtpSrvIp, 24);
_sntprintf(m_szFtpSrvIp, 24, _T("%s"), lpszIpAddr);
::ZeroMemory(m_szFtpSrvUser, 32);
_sntprintf(m_szFtpSrvUser, 32, _T("%s"), lpszUser);
::ZeroMemory(m_szFtpSrvPwd, 32);
_sntprintf(m_szFtpSrvPwd, 32, _T("%s"), lpszPwd);
m_wFtpSrvPort = wPort;
::ZeroMemory(m_szProxyName, 64);
_sntprintf(m_szProxyName, 64, _T("%s"), lpszProxyName);
::ZeroMemory(m_szProxyPwd, 32);
_sntprintf(m_szProxyPwd, 32, _T("%s"), lpszProxyPwd);
 
return TRUE;
}// End SetServerParam
// SetServerParam结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：DownloadFile
// 描述：下载文件
// 原型：BOOL DownloadFile(     LPCTSTR lpszRemote,  // 远程文件
//                                                LPCTSTR lpszLocal,     // 本地文件
//                                                DWORD dwFileType)   // 文件类型
// 参数：
//             [in] lpszRemote：要下载的文件名称
//             [in] lpszLocal：文件下载后保存到本地的路径
//             [in] dwFileType：文件传输的方式
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
BOOL CFtpClientCtrl::DownloadFile(LPCTSTR lpszRemote,
                                                    LPCTSTR lpszLocal,
                                                    DWORD dwFileType)
{
::ZeroMemory(m_szRemote, MAX_PATH);
_sntprintf(m_szRemote, MAX_PATH, _T("%s"), lpszRemote);
::ZeroMemory(m_szLocal, MAX_PATH);
_sntprintf(m_szLocal, MAX_PATH, _T("%s"), lpszLocal);
m_dwFileType = dwFileType;
m_dwFtpHead = 0;
m_bFtpDirect = TRUE;
// 设置文件传输方式
if(dwFileType == FTP_TRANSFER_TYPE_UNKNOWN)
{
        LPCTSTR lpszExt = _tcsrchr(lpszRemote, '.');
        if(IsFtpAscii(lpszExt))
               m_dwFileType = FTP_TRANSFER_TYPE_ASCII;
        else
               m_dwFileType = FTP_TRANSFER_TYPE_BINARY;
}
// 获取远程文件的大小，有的时候不能成功
m_dwTotalFileSize = GetRemoteFileSize();
TRACE("Remote File size is %d/n", m_dwTotalFileSize);
m_dwCurrentFtpSize = 0;
LPTSTR lpMsg = NULL;      // 错误信息
// 打开Internet连接
m_hSession = InternetOpen( _T("Ftp_Ctrl"),
                                                  INTERNET_OPEN_TYPE_DIRECT,
                                                  m_szProxyName,
                                                  m_szProxyPwd,
                                                  INTERNET_FLAG_NO_CACHE_WRITE);
if(m_hSession == NULL)
{
        FormatFtpError(GetLastError(), &lpMsg);
        TRACE("InternetOpen Error with %s/n", lpMsg);
        LocalFree(lpMsg);
        lpMsg = NULL;
        return FALSE;
}
// 设置状态回调函数
if(InternetSetStatusCallback(m_hSession, FtpCtrl_CallbackStatus) ==
        INTERNET_INVALID_STATUS_CALLBACK)
{
        FormatFtpError(GetLastError(), &lpMsg);
        TRACE("InternetSetStatusCallback Error with %s/n", lpMsg);
        LocalFree(lpMsg);
        lpMsg = NULL;
        InternetCloseHandle(m_hSession);
        return FALSE;
}
// 连接到对方
m_hConnect = InternetConnect(   m_hSession,
                                                         m_szFtpSrvIp,
                                                         m_wFtpSrvPort,
                                                         m_szFtpSrvUser,
                                                         m_szFtpSrvPwd,
                                                         INTERNET_SERVICE_FTP,
                                                         INTERNET_FLAG_PASSIVE |
                                                         INTERNET_FLAG_EXISTING_CONNECT,
                                                         (DWORD)this);
if(m_hConnect == NULL)
{
        FormatFtpError(GetLastError(), &lpMsg);
        TRACE("InternetConnect Error with %s/n", lpMsg);
        LocalFree(lpMsg);
        lpMsg = NULL;
        InternetCloseHandle(m_hSession);
        return FALSE;
}
if(m_hWnd != NULL)
{
        // 发送消息，开始下载了
        ::PostMessage(       m_hWnd, m_uMsgHandle,
                                    (WPARAM)ftp_begin, (LPARAM)m_dwTotalFileSize);
}
else if(m_dwThread != 0)
{
        ::PostThreadMessage(m_dwThread, m_uMsgHandle,
                                           (WPARAM)ftp_begin, (LPARAM)m_dwTotalFileSize);
}
// 创建文件下载线程
m_hFtpThread = CreateThread(NULL,
                                                  0,
                                                  FtpClientDnloadThread,
                                                  this,
                                                  0,
                                                  &m_dwFtpThread);
if(m_hFtpThread == NULL)
{
        FormatFtpError(GetLastError(), &lpMsg);
        TRACE("CreateThread Error with %s/n", lpMsg);
        LocalFree(lpMsg);
        InternetCloseHandle(m_hConnect);
        InternetCloseHandle(m_hSession);
        return FALSE;
}
m_bTransfering = TRUE;
return TRUE;
}// End DownloadFile
// DownloadFile结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：BeginDownload
// 描述：开始下载文件
// 原型：BOOL BeginDownload(HWND hWnd,   // 接收消息的窗口
//                                                LPCTSTR lpszRemote,  // 远程文件
//                                                LPCTSTR lpszLocal,     // 本地文件
//                                                DWORD dwFileType)   // 文件类型
// 参数：
//             [in] hWnd：用于接收文件传输状态报告的窗口句柄
//             [in] lpszRemote：要下载的文件名称，保存在服务器上的
//             [in] lpszLocal：文件下载后保存到本地的路径
//             [in] dwFileType：文件传输的方式
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
BOOL CFtpClientCtrl::BeginDownload(HWND hWnd,
                                                     LPCTSTR lpszRemote,
                                                     LPCTSTR lpszLocal,
                                                     DWORD dwFileType)
{
if(    lpszRemote == NULL ||
        lpszLocal == NULL ||
        (dwFileType != FTP_TRANSFER_TYPE_BINARY &&
        dwFileType != FTP_TRANSFER_TYPE_ASCII &&
        dwFileType != FTP_TRANSFER_TYPE_UNKNOWN) ||
        hWnd == NULL)
        return FALSE;
 
if(m_bTransfering)
        return FALSE;
m_hWnd = hWnd;
 
return DownloadFile(lpszRemote,
                                    lpszLocal,
                                    dwFileType);
}// End BeginDownload
// BeginDownload结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：BeginDownload
// 描述：开始下载文件
// 原型：BOOL BeginDownload(DWORD dwThread, // 接收消息的线程
//                                                LPCTSTR lpszRemote,  // 远程文件
//                                                LPCTSTR lpszLocal,     // 本地文件
//                                                DWORD dwFileType)   // 文件类型
// 参数：
//             [in] dwThread：用于接收文件传输状态报告的线程句柄
//             [in] lpszRemote：要下载的文件名称，保存在服务器上的
//             [in] lpszLocal：文件下载后保存到本地的路径
//             [in] dwFileType：文件传输的方式
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
BOOL CFtpClientCtrl::BeginDownload(DWORD dwThread,
                                                     LPCTSTR lpszRemote,
                                                     LPCTSTR lpszLocal,
                                                     DWORD dwFileType)
{
if(    lpszRemote == NULL ||
        lpszLocal == NULL ||
        (dwFileType != FTP_TRANSFER_TYPE_BINARY &&
        dwFileType != FTP_TRANSFER_TYPE_ASCII &&
        dwFileType != FTP_TRANSFER_TYPE_UNKNOWN) ||
        dwThread == 0)
        return FALSE;
if(m_bTransfering)
        return FALSE;
m_dwThread = dwThread;
return DownloadFile(lpszRemote,
                                    lpszLocal,
                                    dwFileType);
}// End BeginDownload
// BeginDownload结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：UploadFile
// 描述：上传文件
// 原型：BOOL UploadFile(   LPCTSTR lpszRemote,  // 远程文件
//                                                LPCTSTR lpszLocal,     // 本地文件
//                                                DWORD dwFileType)   // 文件类型
// 参数：
//             [in] lpszRemote：上传后保存的文件名称
//             [in] lpszLocal：要上传的本地文件路径
//             [in] dwFileType：文件传输的方式
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
BOOL CFtpClientCtrl::UploadFile(LPCTSTR lpszRemote,
                                                  LPCTSTR lpszLocal,
                                                  DWORD dwFileType)
{
m_dwFtpHead = 0;
m_bFtpDirect = FALSE;
::ZeroMemory(m_szRemote, MAX_PATH);
_sntprintf(m_szRemote, MAX_PATH, _T("%s"), lpszRemote);
::ZeroMemory(m_szLocal, MAX_PATH);
_sntprintf(m_szLocal, MAX_PATH, _T("%s"), lpszLocal);
m_dwFileType = dwFileType;
// 设置文件传输的方式
if(dwFileType == FTP_TRANSFER_TYPE_UNKNOWN)
{
        LPCTSTR lpszExt = _tcsrchr(lpszLocal, '.');
        if(IsFtpAscii(lpszExt))
               m_dwFileType = FTP_TRANSFER_TYPE_ASCII;
        else
               m_dwFileType = FTP_TRANSFER_TYPE_BINARY;
}
// 计算本地文件的大小，只要该文件存在，就能够得到大小
m_dwTotalFileSize = GetLocalFileSize();
if(m_dwTotalFileSize == (DWORD)-1)
{
        m_dwTotalFileSize = 0;
        return FALSE;
}
TRACE("Local File size is %d/n", m_dwTotalFileSize);
m_dwCurrentFtpSize = 0;
LPTSTR lpMsg = NULL;      // 消息描述
// 打开Internet连接会话
m_hSession = InternetOpen( _T("Ftp_Ctrl"),
                                                 INTERNET_OPEN_TYPE_DIRECT,
                                                  m_szProxyName,
                                                  m_szProxyPwd,
                                                  INTERNET_FLAG_NO_CACHE_WRITE);
if(m_hSession == NULL)
{
        FormatFtpError(GetLastError(), &lpMsg);
        TRACE("InternetOpen Error with %s/n", lpMsg);
        LocalFree(lpMsg);
       lpMsg = NULL;
        return FALSE;
}
// 设置文件传输状态回调函数
if(InternetSetStatusCallback(m_hSession, FtpCtrl_CallbackStatus) ==
        INTERNET_INVALID_STATUS_CALLBACK)
{
        FormatFtpError(GetLastError(), &lpMsg);
        TRACE("InternetSetStatusCallback Error with %s/n", lpMsg);
        LocalFree(lpMsg);
        lpMsg = NULL;
        InternetCloseHandle(m_hSession);
        return FALSE;
}
// 开始建立文件传输的连接
m_hConnect = InternetConnect(   m_hSession,
                                                         m_szFtpSrvIp,
                                                         m_wFtpSrvPort,
                                                         m_szFtpSrvUser,
                                                         m_szFtpSrvPwd,
                                                        INTERNET_SERVICE_FTP,
                                                         INTERNET_FLAG_PASSIVE |
                                                         INTERNET_FLAG_EXISTING_CONNECT,
                                                         (DWORD)this);
if(m_hConnect == NULL)
{
        FormatFtpError(GetLastError(), &lpMsg);
        TRACE("InternetConnect Error with %s/n", lpMsg);
        LocalFree(lpMsg);
        lpMsg = NULL;
        InternetCloseHandle(m_hSession);
        return FALSE;
}
// 发送消息，通知界面开始传输了
if(m_hWnd != NULL)
{
        ::PostMessage(       m_hWnd, m_uMsgHandle,
               (WPARAM)ftp_begin, (LPARAM)m_dwTotalFileSize);
}
else if(m_dwThread != 0)
{
        ::PostThreadMessage(m_dwThread, m_uMsgHandle,
               (WPARAM)ftp_begin, (LPARAM)m_dwTotalFileSize);
}
 
// 创建文件上传线程
m_hFtpThread = CreateThread(NULL,
                                                  0,
                                                  FtpClientUploadThread,
                                                  this,
                                                  0,
                                                  &m_dwFtpThread);
if(m_hFtpThread == NULL)
{
        FormatFtpError(GetLastError(), &lpMsg);
        TRACE("CreateThread Error with %s/n", lpMsg);
        LocalFree(lpMsg);
        InternetCloseHandle(m_hConnect);
        InternetCloseHandle(m_hSession);
        return FALSE;
}
m_bTransfering = TRUE;
return TRUE;
}// End UploadFile
// UploadFile结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：BeginUpload
// 描述：开始文件上传
// 原型：BOOL BeginUpload(HWND hWnd,       // 用于接收消息的窗口句柄
//                                         LPCTSTR lpszRemote,  // 上传后保存的文件名称
//                                         LPCTSTR lpszLocal,     // 要上传的文件
//                                         DWORD dwFileType)   // 文件传输类型
// 参数：
//             [in] hWnd：接收文件上传状态报告的窗口句柄
//             [in] lpszRemote：文件上传后在服务器端保存的文件名称
//             [in] lpszLocal：要上传的本地文件路径
//             [in] dwFileType：文件上传的类型
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
BOOL CFtpClientCtrl::BeginUpload(HWND hWnd,
                                                   LPCTSTR lpszRemote,
                                                   LPCTSTR lpszLocal,
                                                   DWORD dwFileType)
{
if(    lpszRemote == NULL ||
        lpszLocal == NULL ||
        (dwFileType != FTP_TRANSFER_TYPE_BINARY &&
        dwFileType != FTP_TRANSFER_TYPE_ASCII &&
        dwFileType != FTP_TRANSFER_TYPE_UNKNOWN) ||
        hWnd == NULL)
        return FALSE;
if(m_bTransfering)
        return FALSE;
m_hWnd = hWnd;
 
return UploadFile(   lpszRemote,
                                    lpszLocal,
                                    dwFileType);
}// End BeginUpload
// BeginUpload结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：BeginUpload
// 描述：开始文件上传
// 原型：BOOL BeginUpload(DWORD dwThread,      // 用于接收消息的线程句柄
//                                         LPCTSTR lpszRemote,  // 上传后保存的文件名称
//                                         LPCTSTR lpszLocal,     // 要上传的文件
//                                         DWORD dwFileType)   // 文件传输类型
// 参数：
//             [in] dwThread：接收文件上传状态报告的线程句柄
//             [in] lpszRemote：文件上传后在服务器端保存的文件名称
//             [in] lpszLocal：要上传的本地文件路径
//             [in] dwFileType：文件上传的类型
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
BOOL CFtpClientCtrl::BeginUpload(DWORD dwThread,
                                                   LPCTSTR lpszRemote,
                                                   LPCTSTR lpszLocal,
                                                   DWORD dwFileType)
{
if(    lpszRemote == NULL ||
        lpszLocal == NULL ||
        (dwFileType != FTP_TRANSFER_TYPE_BINARY &&
        dwFileType != FTP_TRANSFER_TYPE_ASCII &&
        dwFileType != FTP_TRANSFER_TYPE_UNKNOWN) ||
        dwThread == 0)
        return FALSE;
if(m_bTransfering)
        return FALSE;
m_dwThread = dwThread;
return UploadFile(   lpszRemote,
                                    lpszLocal,
                                    dwFileType);
}// End BeginUpload
// BeginUpload结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：EndFtpFile
// 描述：结束文件传输进行的操作
// 原型：BOOL EndFtpFile()
// 参数：
//    
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
BOOL CFtpClientCtrl::EndFtpFile()
{
if(m_hConnect)
{
        InternetCloseHandle(m_hConnect);
        m_hConnect = NULL;
}
return TRUE;
}// End EndFtpFile
// EndFtpFile结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：ClearFtpSession
// 描述：清除文件传输会话资源
// 原型：void ClearFtpSession()
// 参数：
//    
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
void CFtpClientCtrl::ClearFtpSession()
{
if(m_hConnect != NULL)
{
        InternetCloseHandle(m_hConnect);
        m_hConnect = NULL;
}
if(m_hSession != NULL)
{
        InternetCloseHandle(m_hSession);
        m_hSession = 0;
}
m_hWnd = NULL;
m_dwThread = 0;
m_bTransfering = FALSE;
}
 
//////////////////////////////////////////////////////////////////////////
// 名称：IncreaseFtpSize
// 描述：在文件传输过程中，设置实际已经传输的文件大小
// 原型：DWORD IncreaseFtpSize(DWORD dwStep)       // 本地大小
// 参数：
//             [in] dwStep：本次状态中传输的大小
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
DWORD CFtpClientCtrl::IncreaseFtpSize(DWORD dwStep)
{
if(m_dwCurrentFtpSize < m_dwTotalFileSize)
        m_dwCurrentFtpSize += dwStep;
return m_dwCurrentFtpSize;
}// End IncreaseFtpSize
// IncreaseFtpSize结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：GetRemoteFileSize
// 描述：获取远程文件的大小
// 原型：DWORD GetRemoteFileSize()
// 参数：
//    
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
DWORD CFtpClientCtrl::GetRemoteFileSize()
{
if(m_szRemote == NULL)
{
        return 0;
}
LPTSTR lpMsg = NULL;
// 开始连接网络
HINTERNET hInternet = InternetOpen(      _T("Ftp_Ctrl"),
                                                                INTERNET_OPEN_TYPE_DIRECT,
                                                                m_szProxyName,
                                                                m_szProxyPwd,
                                                               INTERNET_FLAG_NO_CACHE_WRITE);//INTERNET_FLAG_ASYNC
if(hInternet == NULL)
{
        FormatFtpError(GetLastError(), &lpMsg);
        TRACE("InternetOpen Error With %d--%s/n", GetLastError(), lpMsg);
        LocalFree(lpMsg);
        return 0;
}
// 连接
HINTERNET hConnect = InternetConnect( hInternet,
                                                                       m_szFtpSrvIp,
                                                                       m_wFtpSrvPort,
                                                                       m_szFtpSrvUser,
                                                                       m_szFtpSrvPwd,
                                                                       INTERNET_SERVICE_FTP,
                                                                       INTERNET_FLAG_PASSIVE |
                                                                       INTERNET_FLAG_EXISTING_CONNECT,
                                                                       0);
if(hConnect == NULL)
{
        FormatFtpError(GetLastError(), &lpMsg);
        TRACE("InternetConnect Error With %d--%s/n", GetLastError(), lpMsg);
        LocalFree(lpMsg);
        InternetCloseHandle(hInternet);
        return 0;
}
 
// 打开文件
HINTERNET hFile = FtpOpenFile(       hConnect,
                                                         m_szRemote,
                                                         GENERIC_READ,
                                                         m_dwFileType |
                                                         INTERNET_FLAG_RELOAD |
                                                         INTERNET_FLAG_RESYNCHRONIZE,
                                                         0);
if(hFile == NULL)
{
        FormatFtpError(GetLastError(), &lpMsg);
        TRACE("FtpOpen Error With %d--%s/n", GetLastError(), lpMsg);
        LocalFree(lpMsg);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return 0;
}
typedef DWORD (WINAPI *FtpGetFileSize_Proc)(HINTERNET, LPDWORD);
HINSTANCE hInst = LoadLibrary("wininet.dll");
if(hInst == NULL)
{
        TRACE("Load Library failed!/n");
        InternetCloseHandle(hFile);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return 0;
}
FtpGetFileSize_Proc pfnFtpGetFileSize =
        (FtpGetFileSize_Proc)GetProcAddress(hInst, "FtpGetFileSize");
if(pfnFtpGetFileSize == NULL)
{
        TRACE("Get Proc FtpGetFileSize Failed!/n");
        InternetCloseHandle(hFile);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        FreeLibrary(hInst);
        return 0;
}
DWORD dwSize = pfnFtpGetFileSize(hFile, NULL);
FreeLibrary(hInst);
InternetCloseHandle(hFile);
InternetCloseHandle(hConnect);
InternetCloseHandle(hInternet);
return dwSize;
}// End GetRemoteFileSize
// GetRemoteFileSize结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：GetLocalFileSize
// 描述：获取本地文件的大小
// 原型：DWORD GetLocalFileSize()
// 参数：
//    
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
DWORD CFtpClientCtrl::GetLocalFileSize()
{
HANDLE hFile = CreateFile(  m_szLocal,
                                                  0,
                                                  0,
                                                  NULL,
                                                  OPEN_EXISTING,
                                                  FILE_ATTRIBUTE_NORMAL,
                                                  NULL);
if(hFile == INVALID_HANDLE_VALUE)
{
        return -1;
}
DWORD dwSize = GetFileSize(hFile, NULL);
CloseHandle(hFile);
 
return dwSize;
}// End GetLocalFileSize
// GetLocalFileSize结束
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
// 名称：IsFileAscii
// 描述：判断文件的传输方式是否为ASCII
// 原型：BOOL IsFileAscii(LPCTSTR lpszFile)   // 文件名称
// 参数：
//             [in] lpszFile：要判断的文件名称
// 备注：
//
// 修改记录
//             日期              版本                            修改人                         修改内容
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  2003/09/08      V2.00                 wjr                创建
//________________________________________________________________________
BOOL CFtpClientCtrl::IsFileAscii(LPCTSTR lpszFile)   // 文件名称
{
if(lpszFile == NULL)
        return FALSE;
LPCTSTR lpszExt = _tcsrchr(lpszFile, '.');  // 得到文件后缀
return IsFtpAscii(lpszExt);
}// End IsFileAscii
// IsFileAscii结束
//////////////////////////////////////////////////////////////////////////
 
使用方法：
// 注册文件传输控件必要的参数
m_cFtpCtrl.SetServerParam( szNmsIp),             // 网管服务器地址
                                           szFtpUser,      // ftp服务器用户
                                           szFtpPwd);     // ftp服务器口令
m_cFtpCtrl.RegisterMsgHandle(WM_ FTP_PROGRESS);
 
        // 设置文件传输控件的传输方向
        m_cFtpCtrl.SetFtpDirect(FALSE);
 
        if(!m_cFtpCtrl.BeginUpload(  GetSafeHwnd(),
                                                         m_strRemote,
                                                         m_strLocalFile))
        {
               AfxMessageBox(_T("文件开始上传失败！"));
               PostMessage(WM_CLOSE);
               return TRUE;
              }
              