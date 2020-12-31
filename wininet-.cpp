
VC 利用WinInet类实现HTTP或者FTP资源多线程下载(1)  
2009-05-19 15:45:55
      /*
           2009.10.27更新, 由于看到这篇文章读者访问量较大, 特花了一天时间在原来的基础上更新了下, 主要是将原有的实现进行精简, 将所有的实现封装到类中实现, 方便程序调试和扩展, 并且加入了互斥对象操作, 使多线程在下载速度等临界区资源的操作上更加安全, 对中途异常结束线程提供了更好的管理.
          类采用线程技术完成http ftp下载, 已经过测试, 将在第二篇博客中提供测试程序, 欢迎下载测试.
          作者: 博云
          博客: http://yiyunscu.blog.163.com
           */
       /*
2009.5.10
类采用线程技术完成http下载
作者: 博云
博客: http://yiyunscu.blog.163.com
*/
#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H


#include "afx.h"
#include "WININET.H"
#include "SpecStrings.h"


#include "afxwin.h"
#include "Afxinet.h"


#include "afxdisp.h"
#include "Shlwapi.h"
#include "atlconv.h"
#ifndef DLL_API 
#define DLL_API _declspec(dllimport)
#endif


enum ERROR_CODE
{
RETURN_SUCCESS = 0x100,//操作成功
RETURN_BAD_URL = 0x101,//链接地址错误
RETURN_TIMEOUT = 0x102,//访问超时
RETURN_NETLINK_ERROR = 0x103,//网络连接错误
RETURN_NOT_FOUND = 0x104,//下载文件不存在
RETURN_CODE_ERROR = 0x105,//密码错误
RETURN_FILE_ERROR = 0x106,//本地文件错误
RETURN_THREADCLOSE_ERROR = 0x107,//结束线程错误
RETURN_THREAD_EXIT_OK = 0x108,//线程正常退出
RETURN_QUEST_ERROR = 0x109,//多线程续下载请求服务器失败
RETURN_NOT_HTTPORFTP_QUEST = 0x110,//非HTTP或者FTP请求
RETURN_FILESIZE_ERROR = 0x111,//获取文件大小失败
RETURN_UNKNOWN_ERROR = 0x112//未知错误 
};


class DLL_API CDownloadThread
{
public:
CDownloadThread();
virtual ~CDownloadThread();
public:
/******************************************************************************
函数名称:
GetURLFileInfo
参数:
lpFileURL 下载文件链接, 传入前赋值, 不能为NULL
filename 下载文件名, 为函数运行返回, 不用在传入前赋值
nLen 下载文件长度, 为函数运行返回, 不用在传入前赋值
功能:
获取下载链接的文件信息
*****************************************************************************/
ERROR_CODE GetURLFileInfo(LPCTSTR lpFileURL, char *sourceFileName, DWORD &nLen);
/*****************************************************************************************************
函数名称:
MultiThread
参数:
lpSaveFileName 下载文件的保存文件名, 传入前赋值, 可以为NULL, 此时程序以获取下载文件名保存
nLen 下载文件长度, 为函数运行返回, 传入前赋值, 可以为NULL, 此时程序以运行目录下的downloads目录保存
功能:
下载文件
*****************************************************************************************************/


ERROR_CODE MultiThreadDownloadFile(int threadCount, LPCTSTR lpSaveFileName, LPCTSTR lpSaveDirectory);
/****************************************************************************************************
函数名称:
SetTimeOut
参数:
ConnectTimeOut 连接超时, 以秒计
SendTimeOut 发送超时, 以秒计
RecTimeOut 接收超时, 以秒计
功能:
设置下载超时
*****************************************************************************************************/
void SetTimeOut(DWORD ConnectTimeOut, DWORD SendTimeOut, DWORD RecTimeOut, DWORD QueryTimeOut);


//清除临时资源
void CleanTempSource();
//强制关闭下载, 并调用CleanTempSource清除临时资源
ERROR_CODE TerminateDownload();


int GetThreadCount() const;//获取最大下载线程数
float GetDownLoadSpeed() const;//获取下载速度
DWORD GetNowFileSize() const;//获取当前已下载文件大小
COleDateTimeSpan GetElapsedTime() const;//获取下载用时


private:
int nMaxThreadCount;
BOOL m_bForceReload;
//关闭事件标志
BOOL bExit;


//Internet会话
CInternetSession *session;
COleDateTime startTime;//开始时间
COleDateTimeSpan elapsed;//耗时


BOOL DownLoadComplete;//下载完成标志
ERROR_CODE ReturnCode;
BOOL StartFlag;//开始下载标志


//协议类型
DWORD dwType;


//功能函数
void URLDecodeToGB(CString &source);
void UTF8ToGB(CString &szstr);  //UTF-8转化成GB2312 


//下载文件信息
LPCTSTR m_url;
CString m_RedirectUrl;
CString m_filename;
CString m_SaveFileName;


CString m_SaveDirectory;//下载文件保存目录, 如"download\"
CString m_SourceDirectory;  //下载文件保存目录, 如"download"


DWORD m_filelength;



DWORD  m_infoStatusCode;
float  m_transferRate;
    
DWORD dwRecTimeOut;
DWORD dwSendTimeOut;
DWORD dwConnectTimeOut; 
DWORD dwDownFileSize;
DWORD dwPartFileSize;
DWORD dwQueryTimeOut;


//线程句柄
HANDLE hQuery;//获取信息句柄
HANDLE *hDownloadArray;     //下载线程句柄组
HANDLE hMerge;//合并文件句柄
HANDLE hMutex;//互斥互斥对象
HANDLE hShare;


//多线程下载中每个线程起始下载字节
DWORD m_StartByte;
DWORD m_EndByte;
int m_threadIndex;


//获取文件信息线程
static DWORD WINAPI GetDownloadFileInfoThread(LPVOID lpParameter);
//合并文件线程
static DWORD WINAPI MergerFile(LPVOID lpParameter);


//HTTP下载函数
ERROR_CODE GetHttpFile(LPCTSTR lpSaveFile, DWORD bStartBytes, DWORD bEndBytes);
//FTP下载函数
ERROR_CODE GetFtpFile(LPCTSTR lpSaveFile, DWORD bStartBytes, DWORD bEndBytes);


//重定向检查
ERROR_CODE OpenRedirectHttpURL(CString &strOldLocation, CInternetSession *session); 
//设置超时线程, 因为微软中的超时设置存在BUG, 需要采线程技术解决
//设置连接超时线程
static DWORD WINAPI SetConnectionTimeOut(LPVOID lpParameter);
//设置发送超时线程
static DWORD WINAPI SetSendTimeOut(LPVOID lpParameter);
//设置接收超时线程
static DWORD WINAPI SetRecTimeOut(LPVOID lpParameter);


//下载线程
static DWORD WINAPI DownloadFileThread(LPVOID lpParameter);
/*************************************************************************   
*   
*   函数名称：   
*       CreateSourceDirectory()   
* 
*参数:
*LPCTSTR lpDirectoryPath
*若为NULL, 则创建在程序运行目录下的downloads文件下, 否则创建为lpDirectoryPath目录下
*
*   说明:   
*       //创建临时资源文件夹
*   返回文件夹目录   
*   
*************************************************************************/
void CreateSourceDirectory(LPCTSTR lpDirectoryPath);
DWORD GetProtocalType() const;
};
#endif
上面是头文件定义, 下面是cpp文件:
#define DLL_API _declspec(dllexport)


#include "DownloadThread.h"


#define BUFFER_SIZE 4095
const TCHAR szHeaders[] = _T("Accept: */*\r\nUser-Agent:  Mozilla/4.0 (compatible; MSIE 5.00; Windows 98)\r\n");//////////////////////////////////////////////////////////////////////// Construction/Destruction//////////////////////////////////////////////////////////////////////CDownloadFile::CDownloadFile(){    m_TimeOut = 0;    m_bForceReload = true;    m_dwThreadID = 0;    m_hNotify = NULL;    m_dwMsgID = 0;    m_wFileID = 0;}CDownloadFile::~CDownloadFile(){}


//////////////////////////////////////////////////////////////////////// Construction/Destruction//////////////////////////////////////////////////////////////////////


#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib,"WinInet.lib") 
#pragma comment(lib, "Shlwapi.lib")


CDownloadThread::CDownloadThread()
{
nMaxThreadCount = 2;
m_filelength = 0;
dwQueryTimeOut = 30000;


dwConnectTimeOut = 4000;    //默认连接超时为4s
dwSendTimeOut = 4000;//默认发送超时为4s
dwRecTimeOut = 30000;//默认接收超时为30s
m_bForceReload = true; 
dwDownFileSize = 0;
m_transferRate = 0.0;
bExit = false;
DownLoadComplete = false;
StartFlag = false;


m_RedirectUrl.Empty();


m_filename.Empty();
m_filelength = 0;


hQuery = NULL;//获取信息句柄
hDownloadArray = NULL;     //下载线程句柄组
hMerge = NULL;
hMutex = NULL;
m_threadIndex = 1;


session = NULL;
m_SaveFileName.Empty();
m_SourceDirectory.Empty();
hShare = NULL;
}


CDownloadThread::~CDownloadThread()
{
TerminateDownload();
m_filename.ReleaseBuffer();
m_SaveFileName.ReleaseBuffer();
m_SaveDirectory.ReleaseBuffer();
m_SourceDirectory.ReleaseBuffer();
}


DWORD CDownloadThread::GetProtocalType() const
{
return dwType;
}


void CDownloadThread::SetTimeOut(DWORD ConnectTimeOut, DWORD SendTimeOut, DWORD RecTimeOut, DWORD QueryTimeOut)
{
if(RecTimeOut > 0)
dwRecTimeOut = RecTimeOut;
if(ConnectTimeOut > 0)
dwConnectTimeOut = ConnectTimeOut;
if(SendTimeOut > 0)
dwSendTimeOut = SendTimeOut;
if(QueryTimeOut > 0)
dwQueryTimeOut = QueryTimeOut;
}


ERROR_CODE CDownloadThread::GetURLFileInfo(LPCTSTR lpFileURL, char *sourceFileName, DWORD &nLen)
{
memset(sourceFileName, 0, sizeof(sourceFileName));
nLen = 0;
//关闭资源
TerminateDownload();
//开启获取下载文件信息线程
ERROR_CODE bRet = RETURN_UNKNOWN_ERROR;    
if(!::PathIsURL(lpFileURL))    
{        
return bRet;    
}      
m_url = lpFileURL;
m_RedirectUrl = m_url;
CString strServer,strObject;
CString strAgentCaption =  _T("Multithread Download") ;   
INTERNET_PORT nPort;    
DWORD dwFlags = 0;


InternetGetConnectedState(&dwFlags, 0);    
session = new CInternetSession(strAgentCaption, 1, (dwFlags & INTERNET_CONNECTION_PROXY) == INTERNET_CONNECTION_PROXY ? INTERNET_OPEN_TYPE_PRECONFIG : INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);    
AfxParseURL(lpFileURL, dwFlags, strServer, strObject, nPort);    


dwType = dwFlags;


//设置连接超时
HANDLE hConn, hSend, hRec; 
DWORD threadID = 0;
hConn = CreateThread(NULL, 0, SetConnectionTimeOut, this, 0, &threadID);
hSend = CreateThread(NULL, 0, SetSendTimeOut, this, 0, &threadID);
hRec = CreateThread(NULL, 0, SetRecTimeOut, this, 0, &threadID);
//Sleep(1000);
DWORD res1 = WaitForSingleObject(hConn, dwConnectTimeOut);
DWORD res2 = WaitForSingleObject(hSend, dwSendTimeOut);
DWORD res3 = WaitForSingleObject(hRec, dwRecTimeOut);
if(res1 == WAIT_TIMEOUT || res2 == WAIT_TIMEOUT || res3 == WAIT_TIMEOUT) 
{
bRet = RETURN_TIMEOUT;
return bRet;
}


hQuery = CreateThread(NULL, 0, GetDownloadFileInfoThread, this, 0, &threadID);
if(WAIT_TIMEOUT == WaitForSingleObject(hQuery, INFINITE))
{
ReturnCode = RETURN_TIMEOUT;
CloseHandle(hQuery);
return ReturnCode;
}
else
ReturnCode = RETURN_SUCCESS;
nLen = m_filelength;
strcpy(sourceFileName, m_filename);
return ReturnCode;
}
ERROR_CODE CDownloadThread::MultiThreadDownloadFile(int threadCount, LPCTSTR lpSaveFileName, LPCTSTR lpSaveDirectory)
{
if(ReturnCode != RETURN_SUCCESS)
return ReturnCode;

CreateSourceDirectory(lpSaveDirectory);
if(lpSaveFileName == NULL)
m_SaveFileName = m_filename;
else
m_SaveFileName = lpSaveFileName;


startTime = COleDateTime::GetCurrentTime();
dwDownFileSize = 0;


m_StartByte = 0;
if(threadCount < 2)
nMaxThreadCount = 2;
else
nMaxThreadCount = threadCount;
int count = GetThreadCount();


bExit = false;
StartFlag = false;
dwPartFileSize = m_filelength / nMaxThreadCount;
m_EndByte = dwPartFileSize;
hDownloadArray = new HANDLE[count];
memset(hDownloadArray, NULL, sizeof(HANDLE) * count);
DWORD threadID = 0;
m_threadIndex = 1;


//开启下载线程
for(int i = 0; i < count; i ++)
{
hDownloadArray[i] = CreateThread(NULL, 0, DownloadFileThread, this, 0, &threadID);
//Sleep(1000);
}


//创建互斥对象
//主线程拥有互斥对象
hMutex = CreateMutex(NULL, TRUE, "Share");
hShare = CreateMutex(NULL, TRUE, "ShareParameter");
//释放互斥对象, 以便下载线程使用
ReleaseMutex(hMutex);
ReleaseMutex(hShare);
Sleep(1000);


if(hDownloadArray != NULL)
//因为下载线程之间存在互斥对象资源, 所以调用等待多个线程句柄函数
WaitForMultipleObjects(nMaxThreadCount, hDownloadArray, TRUE, INFINITE);
for(int j = 0; j < count; j ++)
{
CloseHandle(hDownloadArray[j]);
hDownloadArray[j] = NULL;
}


if(hDownloadArray != NULL)
{
delete [] hDownloadArray;
hDownloadArray = NULL;
}

if(!bExit && ReturnCode == RETURN_SUCCESS)
{
//开启线程进行文件合并
hMerge = CreateThread(NULL, 0, MergerFile, this, 0, &threadID);
WaitForSingleObject(hMerge, INFINITE);
CloseHandle(hMerge);
if(ReturnCode == RETURN_SUCCESS)
DownLoadComplete = true;
else
DownLoadComplete = false;
}
return ReturnCode;
}


void CDownloadThread::CreateSourceDirectory(LPCTSTR lpDirectoryPath)
{
SECURITY_ATTRIBUTES security;//文件夹属性
TCHAR Buffer[MAX_PATH]; 

security.nLength = sizeof(SECURITY_ATTRIBUTES);
security.lpSecurityDescriptor = NULL;
security.bInheritHandle = FALSE;
CString   sPath;
//目录为空, 则默认为程序运行所在目录下的\downloads
if(lpDirectoryPath == NULL)
{
GetModuleFileName(AfxGetInstanceHandle(), Buffer, MAX_PATH + 1);
sPath = Buffer; 
int   nPos;   
nPos = sPath.ReverseFind(_T('\\'));   
sPath = sPath.Left(nPos);
}
else
sPath = lpDirectoryPath;
   
sPath = sPath + "\\downloads";
m_SourceDirectory = sPath;
if(!PathFileExists(sPath))
CreateDirectory(sPath, &security);
sPath = sPath + "\\";
m_SaveDirectory = sPath;
sPath.ReleaseBuffer();
}


DWORD WINAPI CDownloadThread::MergerFile(LPVOID lpParameter)
{
BOOL res = true;
CDownloadThread *downloadthread = (CDownloadThread *)lpParameter;
CFile bFile, sFile;
CString tempFile;
char buffer[4096] = {0};
DWORD nLen, nTotalSize = 0;
DWORD nRead;
CString filename;
filename.Format("%s%s", downloadthread->m_SaveDirectory, downloadthread->m_SaveFileName);


bFile.Open(filename, CFile::modeCreate | CFile::modeWrite);
for(int i = 0; i < downloadthread->GetThreadCount(); i ++)
{
tempFile.Format("%s_%d.td", filename, i + 1);
if(!PathFileExists(tempFile))
{
res = false;
bFile.Close();
DeleteFile(filename);
break;
}
if(!res)
break;
sFile.Open(tempFile, CFile::modeRead);
nLen = sFile.GetLength();
nTotalSize += nLen;
nRead = 0;
while(true)
{
if(nLen == sFile.GetPosition())
break;
nRead = sFile.Read(buffer, 4095);
buffer[nRead] = 0;
bFile.Write(buffer, nRead);
};
sFile.Close();
//删除临时文件
DeleteFile(tempFile);
}
if(res)
bFile.Close();
return 0;
}



VC 利用WinInet类实现HTTP或者FTP资源多线程下载(2)  
2009-05-19 16:17:53
     接着上一篇的开始写(已于2009/11/15日更新)。 
ERROR_CODE CDownloadThread::TerminateDownload()
{
int i;
bExit = true;
char tempFile[255] = {0};


ERROR_CODE ret = RETURN_THREAD_EXIT_OK;
if(hQuery != NULL)
{
WaitForSingleObject(hQuery, INFINITE);
if(!CloseHandle(hQuery))
ret = RETURN_THREADCLOSE_ERROR;
hQuery = NULL;
}


if(hDownloadArray != NULL)
{
//睡眠2s
Sleep(2000);
//因为下载线程之间存在互斥对象资源, 所以调用等待多个线程句柄函数
if(hDownloadArray != NULL)
{
//因为下载线程之间存在互斥对象资源, 所以调用等待多个线程句柄函数
WaitForMultipleObjects(nMaxThreadCount, hDownloadArray, TRUE, INFINITE);
for(i = 0; i < nMaxThreadCount; i ++)
{
if(!CloseHandle(hDownloadArray[i]))
ret = RETURN_THREADCLOSE_ERROR;
hDownloadArray[i] = NULL;
}
delete [] hDownloadArray;
hDownloadArray = NULL;
}
}


if(hShare != NULL)
{
if(!CloseHandle(hShare))
ret = RETURN_THREADCLOSE_ERROR;
hShare = NULL;
}


if(hMutex != NULL)
{
if(!CloseHandle(hMutex))
ret = RETURN_THREADCLOSE_ERROR;
hMutex = NULL;
}


//释放会话指针
if(session != NULL)
{
session->Close();
delete session;
session = NULL;
}
if(hMerge != NULL)
{
WaitForSingleObject(hMerge, INFINITE);
CloseHandle(hMerge);
hMerge = NULL;
}
CleanTempSource();
return ret;
}


void CDownloadThread::CleanTempSource()
{
char tempFile[255] = {0};
sprintf(tempFile, "%s%s", m_SaveDirectory, m_SaveFileName);
if(PathFileExists(tempFile))
{
DeleteFile(tempFile);
}
for(int i = 0; i < GetThreadCount(); i ++)
{
sprintf(tempFile, "%s%s_%d.td", m_SaveDirectory, m_SaveFileName, i + 1);
if(PathFileExists(tempFile))
{
DeleteFile(tempFile);
}
}
//如果文件夹为空, 则删除文件夹
RemoveDirectory(m_SourceDirectory);
}


int CDownloadThread::GetThreadCount() const
{
return nMaxThreadCount;
}


ERROR_CODE CDownloadThread::OpenRedirectHttpURL(CString &strOldLocation, CInternetSession *session)
{    
ERROR_CODE bRet = RETURN_UNKNOWN_ERROR;
CHttpFile *pFile = NULL;    
CHttpConnection* pServer = NULL;    
CString strServerName,strObject;    
INTERNET_PORT nPort = 0;    
DWORD dwServiceType = 0;        
if(!AfxParseURL(strOldLocation, dwServiceType, strServerName, strObject, nPort) || dwServiceType != INTERNET_SERVICE_HTTP)    
{        
bRet = RETURN_BAD_URL;      
return bRet;    
}        
pServer = session->GetHttpConnection(strServerName, nPort);        
pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,        
strObject, NULL, 1, NULL, NULL, INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_AUTO_REDIRECT);    
pFile->AddRequestHeaders(szHeaders);    
pFile->SendRequest();        
DWORD dwRet;    
pFile->QueryInfoStatusCode(dwRet);        
// if access was denied, prompt the user for the password
if(dwRet == HTTP_STATUS_DENIED)    
{        
DWORD dwPrompt;        
dwPrompt = pFile->ErrorDlg(NULL, ERROR_INTERNET_INCORRECT_PASSWORD,
FLAGS_ERROR_UI_FLAGS_GENERATE_DATA | FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS, NULL);
// if the user cancelled the dialog, bail out               
if(dwPrompt != ERROR_INTERNET_FORCE_RETRY)
{                       
pFile->Close();            
delete pFile;            
pServer->Close();            
delete pServer; 
bRet = RETURN_CODE_ERROR;
return bRet;        
}                
pFile->SendRequest();        
pFile->QueryInfoStatusCode(dwRet);    
}
// were we redirected?    
// these response status codes come from WININET.H        
if(dwRet == HTTP_STATUS_MOVED || dwRet == HTTP_STATUS_REDIRECT || dwRet == HTTP_STATUS_REDIRECT_METHOD)   
{        
CString strNewLocation;        
pFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, strNewLocation);        
int nPlace = strNewLocation.Find(_T("Location: "));        
if (nPlace == -1)        
{            
pFile->Close();            
delete pFile;            
pServer->Close();            
delete pServer; 
bRet = RETURN_NOT_FOUND;
return bRet;        
}            
strNewLocation = strNewLocation.Mid(nPlace + 10);        
nPlace = strNewLocation.Find('\n');        
if (nPlace > 0)            
strNewLocation = strNewLocation.Left(nPlace);        
strOldLocation = strNewLocation;    
}
//访问页面不存在
if(dwRet == HTTP_STATUS_REQUEST_TIMEOUT || dwRet == HTTP_STATUS_GATEWAY_TIMEOUT)
{
pFile->Close();    
delete pFile;    
pServer->Close();    
delete pServer;
bRet = RETURN_TIMEOUT;
return bRet;
}
if(dwRet == HTTP_STATUS_NOT_FOUND)
{
pFile->Close();    
delete pFile;    
pServer->Close();    
delete pServer;
bRet = RETURN_NOT_FOUND;
return bRet;
}
if(dwRet == HTTP_STATUS_OK)   
{        
bRet = RETURN_SUCCESS;    
}    
// close up the redirected site    
pFile->Close();    
delete pFile;    
pServer->Close();    
delete pServer;    
return bRet;
}


DWORD WINAPI CDownloadThread::GetDownloadFileInfoThread(LPVOID lpParameter)
{
CDownloadThread *downloadthread = (CDownloadThread *)lpParameter;
ERROR_CODE bRet = RETURN_UNKNOWN_ERROR;
if(downloadthread->dwType == AFX_INET_SERVICE_HTTP)
{
CHttpFile* pFile = NULL;
CString strRangeQuest;
strRangeQuest.Format(_T("%sRange: bytes=%d-\r\n"), szHeaders, 0);    
DWORD dwCount = 0;    
try    
{        
DWORD dwFlags = INTERNET_FLAG_TRANSFER_BINARY |INTERNET_FLAG_DONT_CACHE |INTERNET_FLAG_PRAGMA_NOCACHE;  
if(downloadthread->m_bForceReload) 
{            
dwFlags |= INTERNET_FLAG_RELOAD;        
}
//重定向时发现链接文件可能不存在或者需要密码无法访问, 则返回
bRet = (ERROR_CODE)downloadthread->OpenRedirectHttpURL(downloadthread->m_RedirectUrl, downloadthread->session);
if(bRet != RETURN_SUCCESS)
{
downloadthread->session->Close();
return bRet;
}         
pFile = (CHttpFile*)(downloadthread->session)->OpenURL(downloadthread->m_RedirectUrl, 1, dwFlags, strRangeQuest, -1);
}    
catch(CInternetException* e)   
{ 
TCHAR   szCause[MAX_PATH] = {0};        
e->GetErrorMessage(szCause, MAX_PATH);        
e->Delete();        
delete pFile;        
pFile = NULL;               
return bRet;    
} 
COleDateTime startTime = COleDateTime::GetCurrentTime();    
DWORD dwHttpFileSize = 0;
DWORD dwStatusCode;
if(pFile)    
{  
try 
{ 
pFile->QueryInfoStatusCode(dwStatusCode);
if(pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, dwHttpFileSize))
{
downloadthread->m_filelength = dwHttpFileSize;
downloadthread->m_filename = pFile->GetFileName();
downloadthread->URLDecodeToGB(downloadthread->m_filename);
bRet = RETURN_SUCCESS;
}
else
{
bRet = RETURN_QUEST_ERROR;
}
}
catch(CInternetException *e)
{
e->Delete();
pFile->Close();
}
}
else
{
bRet = RETURN_FILESIZE_ERROR;
}
pFile->Close();
delete pFile;
}
else if(downloadthread->dwType == AFX_INET_SERVICE_FTP)
{
DWORD dwCount = 0;       
DWORD dwFtpFileSize = 0;
CInternetFile *pFile = NULL;
CFtpConnection *pFtpConn = NULL; 
try    
{        
CString strServerName, strUserName, strObject, strPassword;        
INTERNET_PORT nPort = 0;        
DWORD dwServiceType = 0;        
CString strRestPointCommand;            
if(!AfxParseURLEx(downloadthread->m_url, dwServiceType, strServerName, strObject, nPort,
strUserName, strPassword) || dwServiceType != INTERNET_SERVICE_FTP)        
{            
bRet = RETURN_QUEST_ERROR; 
return bRet;
}               
if(strUserName.IsEmpty())            
pFtpConn = downloadthread->session->GetFtpConnection(strServerName, NULL, NULL, nPort, downloadthread->m_bForceReload);        
else            
pFtpConn = downloadthread->session->GetFtpConnection(strServerName, strUserName, strPassword, nPort, downloadthread->m_bForceReload);        
   
strRestPointCommand.Format(_T("REST %d\r\n"), 0);            //strRestPointCommand.Format( _T("ls") );            
//false代表不要求服务器返回数据
if(!FtpCommand((*pFtpConn), FALSE, FTP_TRANSFER_TYPE_ASCII, strRestPointCommand, 0, 0))            
{                
bRet = RETURN_QUEST_ERROR; 
return bRet;            
}  
if(pFtpConn)       
{  
downloadthread->URLDecodeToGB(strObject);
pFile = pFtpConn->OpenFile(strObject);   
COleDateTime startTime = COleDateTime::GetCurrentTime();
if(pFile)
{
try 
{ 
dwFtpFileSize = FtpGetFileSize((*pFile), 0);
if(dwFtpFileSize > 0)
{
downloadthread->m_filelength = dwFtpFileSize;
downloadthread->m_filename = pFile->GetFileName();
downloadthread->URLDecodeToGB(downloadthread->m_filename);
bRet = RETURN_SUCCESS;
}
else
{
bRet = RETURN_QUEST_ERROR;
}
}
catch(CInternetException *e)
{
e->Delete();
pFile->Close();
}
}
else
{
bRet = RETURN_QUEST_ERROR;
}
pFile->Close();
delete pFile;
pFtpConn->Close();
delete pFtpConn;
}    
}
catch(CInternetException* e)    
{ 
TCHAR   szCause[MAX_PATH] = {0};        
e->GetErrorMessage(szCause, MAX_PATH);        
e->Delete();        
pFile->Close();    
delete pFile;
pFtpConn->Close();
delete pFtpConn;
bRet = RETURN_FILESIZE_ERROR;
return bRet;    
}
}
else
bRet = RETURN_NOT_HTTPORFTP_QUEST;
return bRet;
}


void CDownloadThread::URLDecodeToGB(CString &source)
{
wchar_t szwchar = 0;
CString szResult = "";
CString szrst;
char hex[2] = ""; 
char ch;
int ix = 0; 
BOOL SpecialChar = false;
LPCTSTR url = (LPCTSTR)source;
//将%后面的字符进行编码, 非%后的除了+号改变外其它不变
while(ch = *(url + ix))
{
if(ch == '%')
{
hex[0] = *(url + ix + 1); 
hex[1] = *(url + ix + 2);
if(isxdigit(hex[0]) && isxdigit(hex[1]))
{
szwchar = 0;
sscanf(hex, "%x", &szwchar);
szrst += (char)szwchar; //若为汉字, 则(char)szwchar为负数, 此时对应存储为补码
}
ix += 3;
SpecialChar = true;
}
else
{
//转化前面的特殊字符
if(SpecialChar)
{
UTF8ToGB(szrst);
//szrst.Format("%s", szrst);
szResult += szrst;
SpecialChar = false;
szrst = "";
}


//空格转化
if(ch == '+')
szResult += " ";
else
szResult += ch;
ix ++;
}
}
source = szResult;;
}


//UTF-8转化成GB2312 
void CDownloadThread::UTF8ToGB(CString &szstr)
{
WCHAR* strSrc = NULL;
TCHAR* szRes = NULL;
//MultiByteToWideChar()的第四个形参设为-1,即可返回所需的短字符数组空间的大小
//UTF8转化成Unicode
int i = MultiByteToWideChar(CP_UTF8, 0, szstr.GetBuffer(szstr.GetLength()), -1, NULL, 0);
strSrc = new WCHAR[i + 1];
ZeroMemory(strSrc, (i + 1) * sizeof(WCHAR));
MultiByteToWideChar(CP_UTF8, 0, szstr.GetBuffer(szstr.GetLength()), -1, strSrc, i);
szstr.ReleaseBuffer();
//Unicode 转化成 GB2312 


//WideCharToMultiByte()的第四个形参设为-1,即可返回所需的短字符数组空间的大小
i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
szRes = new TCHAR[i + 1];
ZeroMemory(szRes, (i + 1) * sizeof(TCHAR));
WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);
szstr = szRes;
if(strSrc != NULL)
{
delete [] strSrc;
strSrc = NULL;
}
if(szRes != NULL)
{
delete [] szRes;
szRes = NULL;
}
}


DWORD CDownloadThread::GetNowFileSize() const 
{
return dwDownFileSize;
}


float CDownloadThread::GetDownLoadSpeed() const
{
return m_transferRate;
}


DWORD WINAPI CDownloadThread::SetConnectionTimeOut(LPVOID lpParameter)
{
CDownloadThread *downloadthread = (CDownloadThread *)lpParameter;
downloadthread->session->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, downloadthread->dwConnectTimeOut);
return 1;
}


DWORD WINAPI CDownloadThread::SetSendTimeOut(LPVOID lpParameter)
{
CDownloadThread *downloadthread = (CDownloadThread *)lpParameter;
downloadthread->session->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, downloadthread->dwSendTimeOut);
return 1;
}


DWORD WINAPI CDownloadThread::SetRecTimeOut(LPVOID lpParameter)
{
CDownloadThread *downloadthread = (CDownloadThread *)lpParameter;
downloadthread->session->SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT, downloadthread->dwRecTimeOut);
return 1;
}


COleDateTimeSpan CDownloadThread::GetElapsedTime() const
{
if(StartFlag)
return (COleDateTime::GetCurrentTime() - startTime);
else
return COleDateTimeSpan(0, 0, 0, 0);
}


DWORD WINAPI CDownloadThread::DownloadFileThread(LPVOID lpParameter)
{
CDownloadThread *downloadthread = (CDownloadThread *)lpParameter;
//等待互斥对象
WaitForSingleObject(downloadthread->hMutex, INFINITE);

DWORD StartByte = downloadthread->m_StartByte;
DWORD EndByte = downloadthread->m_EndByte;
int threadIndex = downloadthread->m_threadIndex;
downloadthread->m_threadIndex ++;
downloadthread->m_StartByte = downloadthread->m_EndByte;
downloadthread->m_EndByte = downloadthread->m_StartByte + downloadthread->dwPartFileSize;


if(threadIndex == downloadthread->GetThreadCount())
{
EndByte = downloadthread->m_filelength;
}

//创建时指定文件大小
CString FileName;
FileName.Format("%s%s_%d.td", downloadthread->m_SaveDirectory, downloadthread->m_SaveFileName, threadIndex);

CFile tmpFile;
tmpFile.Open(FileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyWrite | CFile::typeBinary);
tmpFile.SetLength(EndByte - StartByte);
tmpFile.Close();


//释放互斥对象
ReleaseMutex(downloadthread->hMutex);
//调用下载函数
DWORD type = downloadthread->GetProtocalType();
if(type == AFX_INET_SERVICE_HTTP)
downloadthread->ReturnCode = (ERROR_CODE)downloadthread->GetHttpFile(FileName, StartByte, EndByte - 1);
else if(type == AFX_INET_SERVICE_FTP)
downloadthread->ReturnCode = (ERROR_CODE)downloadthread->GetFtpFile(FileName, StartByte, EndByte - 1);
return 1;
}


//HTTP下载函数
ERROR_CODE CDownloadThread::GetHttpFile(LPCTSTR lpSaveFile, DWORD bStartBytes, DWORD bEndBytes)
{
StartFlag = true;
ERROR_CODE bRet;

CFile m_TmpFile;    
CFileException fileException;            
CHttpFile* pFile = NULL;
try    
{        
DWORD dwFlags = INTERNET_FLAG_TRANSFER_BINARY |INTERNET_FLAG_DONT_CACHE |INTERNET_FLAG_PRAGMA_NOCACHE;  
if(m_bForceReload) 
{            
dwFlags |= INTERNET_FLAG_RELOAD;        
}        
//Here Find URLFile Redirect.//
//重定向时发现链接文件可能不存在或者需要密码无法访问, 则返回
bRet = (ERROR_CODE)OpenRedirectHttpURL(m_RedirectUrl, session);
if(bRet != RETURN_SUCCESS)
{
return bRet;
}

CString strRangeQuest;     
//确定下载的字节流
strRangeQuest.Format(_T("%sRange: bytes=%d-%d\r\n"), szHeaders, bStartBytes, bEndBytes); 
//参数dwHeadersLength为-1时发送到服务器的数据头长度在strRangeQuest不为空时将自动计算
pFile = (CHttpFile*)session->OpenURL(m_RedirectUrl, 1, dwFlags, strRangeQuest, -1);
}    
catch(CInternetException* e)   
{        
TCHAR   szCause[MAX_PATH] = {0};        
e->GetErrorMessage(szCause, MAX_PATH);        
e->Delete();        
pFile->Close();
bRet = RETURN_QUEST_ERROR;
return bRet;    
}    
DWORD dwHttpFileSize = 0;

if(pFile)    
{  
if(!m_TmpFile.Open(lpSaveFile, CFile::modeReadWrite | CFile::shareDenyWrite | CFile::typeBinary, &fileException))    
{        
return bRet;    
}
m_TmpFile.SeekToBegin();
BYTE buffer[BUFFER_SIZE + 1] = {0};        
try 
{   
UINT nRead = 0;            
if(pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, dwHttpFileSize))
{
//请求下载字节长度与服务器返回不一致
//最后一次请求长度检查, 相差限制为1
if(abs(dwHttpFileSize - (bEndBytes - bStartBytes + 1)) > 1)
{
m_TmpFile.Close();
bRet = RETURN_QUEST_ERROR;
return bRet;
}
}
while(!bExit)            
{                
nRead = pFile->Read(buffer, BUFFER_SIZE);
if(nRead > 0)                
{  
buffer[nRead] = 0;                    
m_TmpFile.Write(buffer, nRead);   

//等待互斥对象
WaitForSingleObject(hShare, INFINITE);
dwDownFileSize += nRead;
elapsed = COleDateTime::GetCurrentTime() - startTime;                    
double dSecs = elapsed.GetTotalSeconds();                    

if(dSecs > 0.0)                   
{                                               
m_transferRate = (float) (dwDownFileSize / 1024.0 / dSecs );                                            
}                    
else                    
{                                          
m_transferRate = (float) (dwDownFileSize / 1024.0 );                   
} 
//释放互斥对象
ReleaseMutex(hShare);
}
else
break;
}
//若用户中途退出，则关闭写文件
if(bExit)
{
m_TmpFile.Close();
pFile->Close();
delete pFile;
bRet = RETURN_THREAD_EXIT_OK;
return bRet;
}
else
{
pFile->Close(); 
delete pFile;
m_TmpFile.Close();
bRet = RETURN_SUCCESS; 
}
}
catch (CFileException *e)        
{            
TCHAR   szCause[MAX_PATH] = {0};            
e->GetErrorMessage(szCause, MAX_PATH);                       
e->Delete();            
pFile->Close();           
m_TmpFile.Close();
delete pFile;
bRet = RETURN_FILE_ERROR;
return bRet;        
}                        
}         
return bRet;
}


//FTP下载函数
ERROR_CODE CDownloadThread::GetFtpFile(LPCTSTR lpSaveFile, DWORD bStartBytes, DWORD bEndBytes)
{
StartFlag = true;
ERROR_CODE bRet;   
CFile m_TmpFile;    


CFileException fileException;        

CFtpConnection *pFtpConn = NULL;    
CInternetFile *pFile = NULL;    
try    
{    
CString strServerName,strObject,strUserName,strPassword;        
INTERNET_PORT nPort = 0;        
DWORD dwServiceType = 0;        
CString strRestPointCommand;            
if(!AfxParseURLEx(m_RedirectUrl, dwServiceType, strServerName, strObject, nPort,
strUserName, strPassword) || dwServiceType != INTERNET_SERVICE_FTP)        
{            
bRet = RETURN_NOT_HTTPORFTP_QUEST; 
return bRet;
}        
if(strUserName.IsEmpty())            
pFtpConn = session->GetFtpConnection(strServerName, NULL, NULL, nPort, m_bForceReload);        
else            
pFtpConn = session->GetFtpConnection(strServerName,strUserName, strPassword, nPort, m_bForceReload);      
//指定下载片断的起始位置       
strRestPointCommand.Format(_T("REST %d\r\n"), bStartBytes);           
//false代表不要求服务器返回数据
if(!FtpCommand((*pFtpConn), FALSE, FTP_TRANSFER_TYPE_ASCII, strRestPointCommand, 0, 0))            
{                
bRet = RETURN_QUEST_ERROR;                
return bRet;            
}                   
if(pFtpConn)       
{     
URLDecodeToGB(strObject);
pFile = pFtpConn->OpenFile(strObject);        
}    
}
catch(CInternetException* e)    
{        
TCHAR   szCause[MAX_PATH] = {0};        
e->GetErrorMessage(szCause, MAX_PATH);        
e->Delete();        
pFile->Close(); 
delete pFile;
return bRet;    
}
//线程下载文件片断大小
DWORD dwFtpFileSize = bEndBytes - bStartBytes + 1;
DWORD dwFileSize = 0;
DWORD dwCount = 0;
if(pFile)    
{        
BYTE buffer[BUFFER_SIZE + 1] = {0};   
if(!m_TmpFile.Open(lpSaveFile, CFile::modeReadWrite | CFile::shareDenyWrite | CFile::typeBinary,
&fileException))    
{        
bRet = RETURN_FILE_ERROR;       
return bRet;    
}  
m_TmpFile.SeekToBegin();
try 
{
UINT nRead = 0; 
//如果片断大小小于BUFFER_SIZE, 则下载片断大小即可
if(dwFtpFileSize < BUFFER_SIZE && !bExit)
{
nRead = pFile->Read(buffer, dwFtpFileSize);
if(nRead > 0 && dwFtpFileSize == nRead)
{
buffer[nRead] = 0;
m_TmpFile.Write(buffer, nRead);


//等待互斥对象
WaitForSingleObject(hShare, INFINITE);
COleDateTimeSpan elapsed = COleDateTime::GetCurrentTime() - startTime;        
double dSecs = elapsed.GetTotalSeconds();                     
if(dSecs > 0.0)                    
{                        
dwDownFileSize += nRead; 
dwCount += nRead;
m_transferRate = (float)(dwDownFileSize / 1024.0 / dSecs);                  
}                  
else                  
{                           
m_transferRate = (float)(dwCount / 1024.0);       
}
//释放互斥对象
ReleaseMutex(hShare);
}
else
{
m_TmpFile.Close();
pFile->Close();
delete pFile;
bRet = RETURN_FILE_ERROR;
return bRet;
}
}
else
{
while(!bExit && (dwFtpFileSize - dwCount >= BUFFER_SIZE))            
{                
nRead = pFile->Read(buffer, BUFFER_SIZE);
if(nRead > 0)                
{                              
buffer[nRead] = 0;
m_TmpFile.Write(buffer, nRead);  

//等待互斥对象
WaitForSingleObject(hShare, INFINITE);
COleDateTimeSpan elapsed = COleDateTime::GetCurrentTime() - startTime;        
double dSecs = elapsed.GetTotalSeconds();                     
if(dSecs > 0.0)                    
{                        
dwDownFileSize += nRead; 
dwCount += nRead;
m_transferRate = (float)(dwDownFileSize / 1024.0 / dSecs);                  
}                  
else                  
{                           
m_transferRate = (float)(dwCount / 1024.0);       
}
//释放互斥对象
ReleaseMutex(hShare);
}
else
break;
}


if(!bExit && dwFtpFileSize > dwCount)
{
nRead = pFile->Read(buffer, dwFtpFileSize - dwCount);
if(nRead > 0 && dwFtpFileSize - dwCount == nRead)
{
buffer[nRead] = 0;
m_TmpFile.Write(buffer, nRead);  

//等待互斥对象
WaitForSingleObject(hShare, INFINITE);
COleDateTimeSpan elapsed = COleDateTime::GetCurrentTime() - startTime;        
double dSecs = elapsed.GetTotalSeconds();                     
if(dSecs > 0.0)                    
{                        
dwDownFileSize += nRead; 
dwCount += nRead;
m_transferRate = (float)(dwDownFileSize / 1024.0 / dSecs);                  
}                  
else                  
{                           
m_transferRate = (float)(dwCount / 1024.0);       
}
//释放互斥对象
ReleaseMutex(hShare);
}
else
{
m_TmpFile.Close();
bRet = RETURN_FILE_ERROR;
} 
}
//若用户中途退出，则关闭写文件
if(bExit)
{
m_TmpFile.Close();
bRet = RETURN_THREAD_EXIT_OK;
pFile->Close();
delete pFile;
return bRet;
}
else
{
pFile->Close();  
delete pFile;
m_TmpFile.Close();
bRet = RETURN_SUCCESS;
}
}  
}
catch (CFileException *e)       
{            
TCHAR   szCause[MAX_PATH] = {0};            
e->GetErrorMessage(szCause, MAX_PATH);                       
e->Delete();
            pFile->Close();                        
m_TmpFile.Close(); 
delete pFile;
}                         
}    
return bRet;
}


/*在下载函数启动后，获取链接资源文件名和大小，然后根据指定下载线程数量指定下载线程中文件片断的起始下载字节流，HTTP中更容易控制，因为HTTP下载中允许向HTTP服务器发送下载文件片断的起始字节流，通过构造HTTP请求头实现，如指定下载0-100字节的数据构造如下：
//确定下载的字节流   
       strRangeQuest.Format(_T("%sRange: bytes=%d-%d\r\n"), szHeaders, 0, 100); 
       //参数dwHeadersLength为-1时发送到服务器的数据头长度在strRangeQuest不为空时将自动计算
       pFile = (CHttpFile*)session->OpenURL(strTmpURL, 1, dwFlags, strRangeQuest, -1);
不过，FTP只能指定下载文件片断的开始字节，下载长度需要程序根据下载线程数量进行确定，通过向FTP服务器发送REST命令即可达到，如：
 //指定下载片断的起始位置从100字节处开始下载       
        strRestPointCommand.Format(_T("REST %d\r\n"), 100);           
  //false代表不要求服务器返回数据
        FtpCommand((*pFtpConn), FALSE, FTP_TRANSFER_TYPE_ASCII, strRestPointCommand, 0, 0)；
*/
                   
                                                                                               
