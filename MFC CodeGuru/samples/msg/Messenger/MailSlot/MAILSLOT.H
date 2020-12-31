/*
Module : MAILSLOT.H
Purpose: Defines the interface for a wrapper class for Win32 Mailslots
Created: PJN / MSLOT/1 / 18-06-1997
History: None

Copyright (c) 1997 by PJ Naughter.  
All rights reserved.

*/

#ifndef __MAILSLOT_H__
#define __MAILSLOT_H__
                      

class CServerMailslot : public CObject
{
public:
//Constructors / Destructors
  CServerMailslot();
  ~CServerMailslot();

//Operations
  BOOL  Open(LPCTSTR lpName,
             DWORD nMaxMessageSize = 0,
             DWORD lReadTimeout = 0,
             LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL);
  BOOL  Read(LPVOID lpBuffer,
             DWORD nNumberOfBytesToRead,
             LPDWORD lpNumberOfBytesRead);
  BOOL  MessageWaiting();
  DWORD MessageCount();
  DWORD SizeOfWaitingMessage();
  DWORD MaximumMessageSize();
  BOOL  SetReadTimeout(DWORD lReadTimeout);
  BOOL  GetCreationTime(LPFILETIME lpCreationTime);
  BOOL  GetLastAccessTime(LPFILETIME lpLastAccessTime);
  BOOL  GetLastWriteTime(LPFILETIME lpLastWriteTime);
  BOOL  Close();
  BOOL  IsOpen() const;

//if you really must have access to the internal handle then here
//it is. You should only use this as a last resource
  HANDLE GetHandle() { return m_hMailslot; };


//Diagnostics / Debug support
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  HANDLE m_hMailslot;
};


class CClientMailslot : public CObject
{
public:
//Constructors / Destructors
  CClientMailslot();
  ~CClientMailslot();

//Operations
  BOOL Open(LPCTSTR lpComputerOrDomainName,
            LPCTSTR lpName,
            LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL);
  BOOL Write(LPCVOID lpBuffer,
             DWORD nNumberOfBytesToWrite,
             LPDWORD lpNumberOfBytesWritten);	
  BOOL Close();
  BOOL IsOpen() const;

//if you really must have access to the internal handle then here
//it is. You should only use this as a last resource
  HANDLE GetHandle() { return m_hMailslot; };


//Diagnostics / Debug support
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif


protected:
  HANDLE m_hMailslot;
};


#endif //__MAILSLOT_H__