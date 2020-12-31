WinINet 学习笔记
学习了一周的WinINet，先在对其做一个总结。本文分为以下几个内容

一 WinINet是干什么的？
二 如果完成一个基本的WinINet操作流程
三 如何异步完成，异步操作的好处。
四 unicode以及mutilbyte
五 代码样例

一 WinINet是微软开发的一个库，可以完成http ftp客户端的工作。让程序员从复杂的协议中节省大量体力。

二 我会用了http, ftp类似。用WinINet完成一个http下载需要以下步骤 。 下面这个是同步操作（也就是一步步操作，每个函数执行完才会返回一个结果的意思）

     1   InternetOpen      Initializes an application's use of the WinINet functions.
                   需要的话 InternetSetOption 设置代理服务器地址以及端口。
                   http：    ip:port 或者 http=http://ip:port
                   socks：SOCKS=ip:port
     2   InternetConnect    关联目标地址或者域名以及服务ip

     3   HttpOpenRequest   关联要下载的内容名字
                   InternetSetOption 设置用户名密码

     4   HttpSendRequest     这步就是用HttpOpenRequest 的返回值（已经关联了上面的所有信息）发送出去，第一次用了网络。向目标服务器或者代理服务器。

     5   HttpQueryInfo
            该函数查询返回值，不参与网络操作。可以查询服务器的返回信息，比如目标文件的大小，该文件是否存在，代理服务返回了要求用户名，密码等等（这几个最常用），还有很多信息。

     6   InternetReadFile
            很普通的读函数，就是下载文件。不知道是否和底层网络同步，底层会不会提前下载呢？

     7   InternetCloseHandle 释放资源

三    异步操作，比较复杂的。   为什么需要异步操作呢？ 因为涉及到网络操作，某些函数在操作中可能需要时间，如果一直不返回（比如1秒）时，这时主线程要结束程序，岂不就出现意想不到的结果了，但是如果每个函数都能够瞬间返回，然后通过WaitForMultipleObjects或者WaitForSingleObject等待结果的出现（此时就不会操作那个消耗1秒的函数了，而这个1秒函数正是要用到系统资源HINTERNET的）。

       异步操作的目的上如，原理呢？ 其实原理就是注册一个函数，在这里叫InternetStatusCallback，因为微软写得底层代码要用到，所以必须格式统一。一旦有结果来了就通过事件通知我们，WaitForSingleObject函数就可以走了。比如等到了HINTERNET创建或者命令发送成功等结果。然后我们就可以第一时间安全的使用了。
      API 函数如果名字最后可以带EX，那么带ex的就是异步操作的。

四 一定要注意，凡是有unicode和mutilbyte函数的一定要统一，最好都用mutilbyte的。


五： 代码如下：
// crt_assert.c
// compile with: /c
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#include <iostream>

#include "winsock2.h"
#include <string>
#include <Wininet.h>
#include <windows.h>
#include <fstream>　//要使用文件输入输出流必须的头文件
using namespace std;
#define __HTTP_VERB_GET    "GET"
#define __HTTP_VERB_POST "POST"
#define __HTTP_ACCEPT_TYPE "*/*"
#define __HTTP_ACCEPT "Accept: */*\r\n"
#define __SIZE_HTTP_BUFFER    100000
#define __SIZE_HTTP_RESPONSE_BUFFER    100000
#define __SIZE_HTTP_HEAD_LINE    2048

void CALLBACK InternetStatusCallback(

                                    HINTERNET hInternet,
                                    DWORD dwContext,
                                    DWORD dwInternetStatus,
                                    LPVOID lpvStatusInformation,
                                    DWORD dwStatusInformationLength);
HANDLE hEvent[3];

HINTERNET hFile;
HINTERNET hNet;
HINTERNET hSession,hConnect,hRequest;
int WaitExitEvent()
{
    //return 1;
    DWORD dwRet = ::WaitForMultipleObjects(3, hEvent, FALSE, 30000);//INFINITE);
    int x=-1;
    switch (dwRet)
    {
        //句柄被创建事件或者读数据请求成功完成事件
    case WAIT_OBJECT_0:
        x=0;
        cout<<"WAIT_OBJECT_0"<<endl;
        //句柄被关闭事件
        break;
    case WAIT_OBJECT_0+1:
        x=1;
        cout<<"WAIT_OBJECT_1"<<endl;
        //用户要求终止子线程事件或者发生错误事件
        break;
    case WAIT_OBJECT_0+2:
        x=2;
        cout<<"WAIT_OBJECT_2"<<endl;
        
        break;
    default:
        cout<<"WaitForMultipleObjects time out"<<endl;
        return -1;

    }
    return x;
}

// 支持代理设置， 是否异步设置； 采用事件驱动
void WinINet3(bool setProxy, bool ASYNC)
{
    hSession=NULL;
    hConnect=NULL;
    hRequest=NULL;
    for (int i = 0; i < 3; i++) 
    { 
        hEvent[i] = CreateEvent( 
            NULL,   // default security attributes
            FALSE, // auto-reset event object
            FALSE, // initial state is nonsignaled
            NULL); // unnamed object

        if (hEvent[i] == NULL) 
        { 
            printf("CreateEvent error: %d\n", GetLastError() ); 
            ExitProcess(0); 
        } 
    } 
    char *url = "http://down.360safe.com/setup.exe";
    char *pip = "down.360safe.com";
    char *paim = "/setup.exe";



    //   step 1
    if(ASYNC)    cout<<"异步模式"<<endl;
   // setProxy =false;
    if(setProxy)
    {
        cout<<"代理模式"<<endl;
        if(ASYNC)
          hSession = InternetOpen("name",
        INTERNET_OPEN_TYPE_DIRECT,//|INTERNET_OPEN_TYPE_PROXY,// INTERNET_OPEN_TYPE_PROXY,
        NULL,NULL,INTERNET_FLAG_ASYNC); // 异步
        else
          hSession = InternetOpen("name",INTERNET_OPEN_TYPE_PROXY,NULL,NULL,0); // 同步
    }
    else
    {
        if(ASYNC)
            hSession = InternetOpen("name",INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,INTERNET_FLAG_ASYNC); // 异步
        else
            hSession = InternetOpen("name",INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0); // 同步
    }
    if(!hSession){
        DWORD er = ::GetLastError();
        cout<<"InternetOpen error"<<endl;//, "Err", MB_OK);
        return;
    }
    if(ASYNC)
    {
        //Sleep(500);
        INTERNET_STATUS_CALLBACK res = ::InternetSetStatusCallback(hSession,InternetStatusCallback);
        if(res == INTERNET_INVALID_STATUS_CALLBACK)
        {
            cout<<"InternetSetStatusCallback failed, so return "<<endl;
            return ;    
        }
        else
        {
            cout<<"InternetSetStatusCallback succeed, so go on "<<endl;

        }
        //Sleep(500);
    }
    
    char   strProxyList[MAX_PATH],   strUsername[64],   strPassword[64];
    strcpy(strProxyList,   "SOCKS=58.56.87.2:1080"); //   写上socks怎么就无效了呢？？？SOCKS5=172.18.132.27:1080
    strcpy(strUsername,   "user01"); 
    strcpy(strPassword,   "baidu"); 
    INTERNET_PROXY_INFO proxy;
    proxy.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
    proxy.lpszProxy    = strProxyList;
    proxy.lpszProxyBypass = NULL;
    if( setProxy &&!InternetSetOption(hSession,INTERNET_OPTION_PROXY ,&proxy,sizeof(INTERNET_PROXY_INFO)))
    {
        cout<<"InternetSetOption failed"<<endl;
        return ;
    }
    
    // step 2
    //如果明确知道需要认证，第4，5个参数可以输入用户名，密码"administrator","password"
    //第2，3个参数为目标主机IP、端口号(不是代理服务器的参数)
    hConnect = InternetConnect(hSession,pip,INTERNET_DEFAULT_HTTP_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,INTERNET_FLAG_RELOAD,0);
    if(!ASYNC &&!hConnect){
        cout<<"同步，InternetConnect error"<<endl;//, "Err", MB_OK);
        return;
    }
    if( ASYNC&& hConnect== NULL)// 异步 需要等待   竟然直接创建好了
    {
        int er = GetLastError();
        DWORD dwError = ::GetLastError();
        if (dwError != ERROR_IO_PENDING) 
        {
            cout<<"CHttpDownload::OpenInternetConnection| 连接失败" <<endl;
            return ;
        }
        else //
        {
            cout<<"hConnect == NULL, so run WaitExitEvent"<<endl;
            WaitExitEvent(); // 等待成功创建 // 这里应该等待   这里应该显示一次呀
            ::ResetEvent(hEvent[0]);
            ::ResetEvent(hEvent[1]);
            ::ResetEvent(hEvent[2]);
        }
    }
    cout<<"step 2 :InternetConnect secced"<<endl;

    // ::InternetSetStatusCallback(hConnect,InternetStatusCallback);
    
    // step 3!!!
    char   szHead[] = "Accept: */*\r\n\r\n";
    char **p = new char*[2];*p = szHead;*(p+1) = NULL;

    //hRequest = HttpOpenRequest(hConnect,"GET","download/BaiduHi_1.0_Beta2.exe",NULL,NULL,/*(const char **)p*/NULL,0/*INTERNET_FLAG_NO_COOKIES|INTERNET_FLAG_RELOAD*/,0); // no request;
    CONST TCHAR *szAcceptType=__HTTP_ACCEPT_TYPE;
    hRequest = ::HttpOpenRequest(hConnect,
        "GET",
        paim,
        HTTP_VERSION,
        "",
        &szAcceptType,
        INTERNET_FLAG_RELOAD|INTERNET_FLAG_KEEP_CONNECTION|INTERNET_FLAG_NO_CACHE_WRITE,
        0);
    
    //::HttpAddRequestHeaders( hRequest, __HTTP_ACCEPT, strlen(__HTTP_ACCEPT), HTTP_ADDREQ_FLAG_REPLACE);
    /*_hHTTPRequest=::HttpOpenRequest(    _hHTTPConnection,
        __HTTP_VERB_GET, // HTTP Verb
        szURI, // Object Name
        HTTP_VERSION, // Version
        "", // Reference
        &szAcceptType, // Accept Type
        INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_CACHE_WRITE,
        0); // context call-back point
    */
    if (!ASYNC&& !hRequest){
        cout<<"同步，HttpOpenRequest error"<<endl;//, "Err", MB_OK);
        return;
    }
    if( ASYNC&& hRequest== NULL)// 异步 需要等待
    {
        int er = GetLastError();
        DWORD dwError = ::GetLastError();
        if (dwError != ERROR_IO_PENDING) 
        {
            cout<<"CHttpDownload::OpenInternetConnection| 连接失败" <<endl;
            return ;
        }
        else //
        {
            cout<<"hRequest == NULL, so run WaitExitEvent"<<endl;
            WaitExitEvent(); // 等待成功创建
            ::ResetEvent(hEvent[0]);
            ::ResetEvent(hEvent[1]);
            ::ResetEvent(hEvent[2]);
        }
    }
    //Sleep(10000);
    cout << "step 3 : HttpOpenRequest success"<<endl;
    //::InternetSetStatusCallback(hRequest,InternetStatusCallback);
    //////////////////////////////////////////////
    if (setProxy )
    {
        // InternetSetOption 不要异步等待
        if( !InternetSetOption(hRequest,INTERNET_OPTION_PROXY_USERNAME ,strUsername,strlen(strUsername)+1))
        {
            cout<<"InternetSetOption Username failed"<<endl;
            return ;
        }
        if( !InternetSetOption(hRequest,INTERNET_OPTION_PROXY_PASSWORD ,strPassword,strlen(strPassword)+1))
        {
            cout<<"InternetSetOption Password failed"<<endl;
            return ;
        }
    }
    // step 4
    //HttpSendRequest(hRequest,NULL,0,NULL,0);
    //Sleep(3000);
    ::ResetEvent(hEvent[0]);
    ::ResetEvent(hEvent[1]);
    ::ResetEvent(hEvent[2]);
    if(!::HttpSendRequest(hRequest,NULL,0,NULL,0)) // 为什么失败？？？
    {
        //Sleep(3000);
        if(!ASYNC)// 同步
        {
            DWORD dwError = ::GetLastError();
              cout<<"同步，HttpSendRequest failed, GetLastError=="<<dwError<<endl;
            return ;
        
        }
        else
        {
            Sleep(3000);
            DWORD dwError = ::GetLastError();
            cout<<"dwError =="<<dwError<<endl;
            if (dwError != ERROR_IO_PENDING) 
            {
                cout<<"dwError != ERROR_IO_PENDING, so quit,dwError =="<<dwError<<endl;
                return ;
            }
            else //
            {
                cout<<"HttpSendRequest, so run WaitExitEvent"<<endl;
                Sleep(3000);
                //if(WaitExitEvent()!=2)//; // 等待成功创建 等待是否不对？？？
                {
                       cout<<"had not recv complete event, so quit"<<endl;
                    // return ;
                }
            }
        }
        
    }
    Sleep(3000);
    cout << "step 4: HttpSendRequest success!"<<endl;

    int bufh[1000];
    DWORD dwLen,dwIndex;
    /*if(!::HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, bufh, &dwLen, &dwIndex))// 这句话？？？
    {
        //return E_FAIL;
        return;
    }
*/
    // 判断状态码；
    char m_dwStatusCode[90];
    DWORD dwStatusSize = sizeof(m_dwStatusCode);
    /*if (FALSE == ::HttpQueryInfo(hRequest,   // 查询失效？？
        HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
        &m_dwStatusCode,
        &dwStatusSize,
        NULL))   //获取返回状态码
    {
        return ;
    }
    //判断状态码是不是 200
    //if (HTTP_STATUS_OK != m_dwStatusCode)
    {
        //return ;
    }
*/

    DWORD dwByteToRead = 0;
    DWORD dwSizeOfRq = 4;
    DWORD dwBytes = 0;
    //这三个值分别存储文件的大小，HttpQueryInfo内容的大小和总共读取的字节数。
    //HttpQueryInfo(hRequest, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, (LPVOID)&dwByteToRead, &dwSizeOfRq, NULL);
    //需要说明的是 HttpQueryInfo 并不进行网络操作，因此它不需要进行异步操作的处理。 
    if (!HttpQueryInfo(hRequest, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, (LPVOID)&dwByteToRead, &dwSizeOfRq, NULL))
    { // 这里失败了？？？
        
        DWORD dwError = ::GetLastError();
        cout<<"HttpQueryInfo failed, so return， GetLastError() =="<<dwError<<endl;
        return ;
    }
    FILE * pFile = fopen("e://baidu01.exe", "wb" );
    //ofstream mfile("out.txt");//定义文件输出流ouf，并关联到out.txt
    int i=0;
    DWORD leftB = dwByteToRead;
    cout<<"开始下载"<<endl;
    if( !ASYNC) // 同步下载
    {
        while(true)
        {
            const int MAX_BUFFER_SIZE = 65536;
            unsigned long nSize = 0;
            char szBuffer[MAX_BUFFER_SIZE+2];
            int num = MAX_BUFFER_SIZE;
            if( leftB < num);
            num = leftB;
            BOOL bRet = ::InternetReadFile(hRequest, szBuffer, num, &nSize); // 异步 需要等待

            leftB -= nSize;
            cout<<i++<<" size: "<<nSize<<endl;
            if(!bRet || nSize <= 0)
                break;
            fwrite(szBuffer, sizeof(char), nSize, pFile);
        }
    }
    else // 异步下载
    {
        INTERNET_BUFFERS i_buf = {0};
        i_buf.dwStructSize = sizeof(INTERNET_BUFFERS);
        i_buf.lpvBuffer = new TCHAR[10242];
        i_buf.dwBufferLength = 10240;
         for( DWORD i=0;i<dwByteToRead;)
        {
            //重置读数据事件
            ::ResetEvent( hEvent[0]);
            int num = 10240;
            if(dwByteToRead-i<10240)
            {
                num = dwByteToRead-i;
                   i_buf.dwBufferLength = dwByteToRead-i;
            }
            if (FALSE == ::InternetReadFileEx(hRequest,
                &i_buf,
                IRF_ASYNC,
                NULL))
            {
                if (ERROR_IO_PENDING == ::GetLastError())
                {
                    if ( NULL)//WaitExitEvent()!=2)
                    {
                        delete[] i_buf.lpvBuffer;
                        return ;
                    }
                }
                else 
                {
                    cout<<"down failed,so return"<<endl;
                    delete[] i_buf.lpvBuffer;
                    return ;
                }
            }
            else
            {
                //在网络传输速度快，步长较小的情况下，
                //InternetReadFileEx 经常会直接返回成功，
                //因此要判断是否发生了用户要求终止子线程事件。
                cout<<"网络很好，InternetReadFileEx返回true"<<endl;

                // 暂不考虑用户退出
            }
            i += i_buf.dwBufferLength; // 最后一次写多了！！！
            fwrite(i_buf.lpvBuffer, sizeof(char), i_buf.dwBufferLength, pFile);
            cout<<"i== "<<i<<endl;
            //保存数据
             //通知主线程下载进度
                    
        }
    }
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hSession);
    cout<<"success download file"<<endl;
    
    return;
}

int main( void )
{
    
    WinINet3(true,true);
    return 1;
}

void OnInternetHandleCreated(HINTERNET hInternet, LPINTERNET_ASYNC_RESULT lpInetStatusResult)
{
    if(NULL == lpInetStatusResult)
    {
        //ATLASSERT( 0 );
        return;
    }
    hFile = HINTERNET(lpInetStatusResult->dwResult);
    HINTERNET    hInet = HINTERNET(lpInetStatusResult->dwResult);
    DWORD        dwInetHandleType;
    DWORD        dwTypeLen = sizeof(dwInetHandleType);

    InternetQueryOption( hInet, INTERNET_OPTION_HANDLE_TYPE, &dwInetHandleType, &dwTypeLen);
    switch(dwInetHandleType) 
    {
    case INTERNET_HANDLE_TYPE_CONNECT_HTTP:
        //CloseInternetConnection(); //   这里是何意？？？？ 通过回调 设置httpConnect
        hConnect = hInet;     // 
        break;
    case INTERNET_HANDLE_TYPE_HTTP_REQUEST:
        //CloseInternetFile();    //    这里是何意？？    通过回调 设置httpFile
        hRequest = hInet;    //
        break; 
    default:
        break;
    }
    cout<<"OnInternetHandleCreated, so ::SetEvent(hEvent[0])"<<endl;
    // HANDLE已创建事件（异步控制）
    ::SetEvent(hEvent[0]);
}
void OnInternetRequestComplete(HINTERNET hInternet, LPINTERNET_ASYNC_RESULT lpInetStatusResult)
{

    if( lpInetStatusResult == NULL )
    {
        //ATLASSERT( 0 );
        return;
    }
    cout<<"OnInternetRequestComplete, so ::SetEvent(hEvent[2])"<<endl;
    // 激发请求完成事件（异步控制）
    ::SetEvent(hEvent[0]);
}

void CALLBACK InternetStatusCallback(
                                    HINTERNET hInternet,
                                    DWORD_PTR dwContext,
                                    DWORD dwInternetStatus,
                                    LPVOID lpvStatusInformation,
                                    DWORD dwStatusInformationLength
                                    )
{
    cout<<"进入回调"<<endl;
    switch (dwInternetStatus)
    {
    case INTERNET_STATUS_RESOLVING_NAME:
        break;
    case INTERNET_STATUS_NAME_RESOLVED:
        break;
    case INTERNET_STATUS_CONNECTING_TO_SERVER:
        break;
    case INTERNET_STATUS_CONNECTED_TO_SERVER:
        break;
    case INTERNET_STATUS_SENDING_REQUEST:
        break;
    case INTERNET_STATUS_REQUEST_SENT:
        break;
    case INTERNET_STATUS_RECEIVING_RESPONSE:
        break;
    case INTERNET_STATUS_RESPONSE_RECEIVED:
        break;
    case INTERNET_STATUS_CLOSING_CONNECTION:
        break;
    case INTERNET_STATUS_CONNECTION_CLOSED:
        break;
    case INTERNET_STATUS_HANDLE_CREATED:
        cout<<"回调是INTERNET_STATUS_HANDLE_CREATED"<<endl;
        OnInternetHandleCreated(hInternet, LPINTERNET_ASYNC_RESULT(lpvStatusInformation)); // 传递了HINTERNET 这是精髓呀
        break;
    case INTERNET_STATUS_HANDLE_CLOSING:
        break;
    case INTERNET_STATUS_REQUEST_COMPLETE:
        cout<<"回调是INTERNET_STATUS_REQUEST_COMPLETE"<<endl;
        OnInternetRequestComplete(hInternet, LPINTERNET_ASYNC_RESULT(lpvStatusInformation));
        break;
    case INTERNET_STATUS_REDIRECT:
    case INTERNET_STATUS_INTERMEDIATE_RESPONSE:
    case INTERNET_STATUS_STATE_CHANGE:
    default:
        break;
    }
}

谢谢！
