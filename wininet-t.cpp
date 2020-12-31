
 #include <windows.h>
    #include <wininet.h>
    #include <iostream.h>
 
    DWORD WINAPI WorkerFunction( LPVOID ); 
    HINTERNET g_hOpen, g_hConnect;
 
    typedef struct 
    {
        CHAR* pHost;
        CHAR* pUser;
        CHAR* pPass;
    } PARM;
 
    void main()
    {
        CHAR    szHost[] = "localhost";
        CHAR    szUser[] = "JoeB";
        CHAR    szPass[] = "test";
        CHAR    szLocalFile[] = "localfile";
        CHAR    szRemoteFile[] = "remotefile";
        DWORD   dwExitCode;
        DWORD   dwTimeout;
        PARM    threadParm;
 
        g_hOpen = 0;
        if ( !( g_hOpen = InternetOpen ( "FTP sample", 
                                         LOCAL_INTERNET_ACCESS, 
                                         NULL, 
                                         0, 
                                         0 ) ) )
        {         
            cerr << "Error on InternetOpen: " << GetLastError() << endl;
            return ;
        }
 
        // Create a worker thread 
        HANDLE   hThread; 
        DWORD    dwThreadID;
        threadParm.pHost = szHost;
        threadParm.pUser = szUser;
        threadParm.pPass = szPass;
 
        hThread = CreateThread(
                      NULL,            // Pointer to thread security attributes 
                      0,               // Initial thread stack size, in bytes 
                      WorkerFunction,  // Pointer to thread function 
                      &threadParm,     // The argument for the new thread
                      0,               // Creation flags 
                      &dwThreadID      // Pointer to returned thread identifier 
                  );    
 
        // Wait for the call to InternetConnect in worker function to complete
        dwTimeout = 5000; // in milliseconds
        if ( WaitForSingleObject ( hThread, dwTimeout ) == WAIT_TIMEOUT )
        {
            cout << "Can not connect to server in " 
                 << dwTimeout << " milliseconds" << endl;
            if ( g_hOpen )
    InternetCloseHandle ( g_hOpen );
            // Wait until the worker thread exits
            WaitForSingleObject ( hThread, INFINITE );
            cout << "Thread has exited" << endl;
            return ;
        }
     
        // The state of the specified object (thread) is signaled
        dwExitCode = 0;
        if ( !GetExitCodeThread( hThread, &dwExitCode ) )
        {
            cerr << "Error on GetExitCodeThread: " << GetLastError() << endl;
            return ;
        }
 
        CloseHandle (hThread);
        if ( dwExitCode )
        // Worker function failed
           return ;
     
        if ( !FtpGetFile ( g_hConnect, 
                           szRemoteFile,
                           szLocalFile,
                           FALSE,INTERNET_FLAG_RELOAD, 
                           FTP_TRANSFER_TYPE_ASCII,
                           0 ) )
        {
            cerr << "Error on FtpGetFile: " << GetLastError() << endl;
            return ;
        }
 
        if ( g_hConnect )
            InternetCloseHandle( g_hConnect );
        if ( g_hOpen )
            InternetCloseHandle( g_hOpen );
 
        return ;
    }
 
    /////////////////// WorkerFunction ////////////////////// 
    DWORD WINAPI 
    WorkerFunction(
        IN LPVOID vThreadParm
    )
    /*
    Purpose:
        Call InternetConnect to establish a FTP session  
    Arguments:
        vThreadParm - points to PARM passed to thread
    Returns:
        returns 0  
    */ 
    {
        PARM* pThreadParm;
        // Initialize local pointer to void pointer passed to thread
        pThreadParm = (PARM*)vThreadParm;
        g_hConnect = 0;
     
        if ( !( g_hConnect = InternetConnect (
                                 g_hOpen, 
                                 pThreadParm->pHost,
                                 INTERNET_INVALID_PORT_NUMBER,
                                 pThreadParm->pUser,
 pThreadParm->pPass,
                                 INTERNET_SERVICE_FTP, 
                                 0,
                                 0 ) ) )
        {
            cerr << "Error on InternetConnnect: " << GetLastError() << endl;
            return 1; // failure
        }
        
        return 0;  // success
    }
 
 
 #include "stdafx.h"     
 #include "windows.h"  
 #include <Sensapi.h>    
 #include <iostream>  
 #include <Wininet.h>  
   
 #pragma comment(lib, "Sensapi.lib")  
 #pragma comment(lib, "Wininet.lib")  
   
 using namespace  std;  
   
 int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])    
 {    
     BOOL isConnect;  
     DWORD dw;  
     isConnect = ::IsNetworkAlive( &dw );  
     while (1)  
     {  
         if(isConnect)  
             cout << "IsNetworkAlive连接" <<endl;  
         else  
             cout << "IsNetworkAlive未连接" <<endl;   
         cout<< "---------------------------------" <<endl;  
   
   
   
         DWORD dw2;  
         BOOL ret = InternetGetConnectedState(&dw2, 0);  
         if (ret)  
             cout << "InternetGetConnectedState连接" <<endl;  
         else  
             cout << "InternetGetConnectedState未连接" <<endl;  
         cout<< "**********************************"  <<endl;  
           
   
         BOOL bConnected = InternetCheckConnection(_T("http://www.baidu.com"), FLAG_ICC_FORCE_CONNECTION, 0);  
         if (bConnected)  
             cout << "InternetCheckConnection连接" <<endl;  
         else  
             cout << "InternetCheckConnection未连接" <<endl;  
         cout<< "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"  <<endl;  
   
         //IsDestinationReachable(_T("http://www.google.com"), )   
   
   
         cout<<endl<<endl<<endl;  
         Sleep(1000);  
   
     }  
     getchar();  
     return 1;    
 }   

