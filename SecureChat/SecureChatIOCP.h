// SecureChatIOCP.h: interface for the SecureChatIOCP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SecureChatIOCP_H__4093193A_D0A0_4E6A_82FA_65B17A1FEB71__INCLUDED_)
#define AFX_SecureChatIOCP_H__4093193A_D0A0_4E6A_82FA_65B17A1FEB71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IOCPS.h"
#include "MyListCtrl.h"

#include "Rijndael.h" // For encryption/decryption 

#define WM_NEW_CONNECTION	WM_APP + 0x1001
#define WM_LOGG_APPEND	WM_NEW_CONNECTION+1
#define WM_DISCONNECT_CLIENT WM_NEW_CONNECTION+2



#define USE_ENCRYPTION
#define MAXIMUMENCRYPSIZE 31*16
#define ENCRYPTION_BLOCKSIZE 16 
#define SERVER_VERSION "Secure Chat 1.0 BETA"
#define USE_SIGNATURE  // Undefine to remove the "man in middle attack" protection  
//#define _IOCPClientMode_  //define this in your project to make SecureChatIOCP act as the client. 


class SecureChatIOCP : public IOCPS  
{

public: 
	// Send the Text message to all. 
	void SendTextMessage(CString msg);
	// Are we connected to someone ? 
	BOOL IsConnected();		
	CCriticalSection m_StatusLock;
	// Used for ::PostMessage
	HWND m_hWnd;

	// The Public Key P.. Used only in ClientMode. 
#ifdef _IOCPClientMode_ 
	DWORD* m_pPublicKeyP;
	UINT m_nSizePublicKey;
	CString m_sUserName; 
#endif

	SecureChatIOCP();
	virtual ~SecureChatIOCP();
	// Send an Error Message to Client. 
	BOOL SendErrorMessageTo(int iClientID, CString sMsg);
	// Send a Message to a Client. 
	BOOL SendTextMessageTo(int iClientID, CString sMsg);
	// The function handling decrypted messsages. 
	inline void ProcessPayload(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	// A client have Disconnected. 
	virtual void NotifyDisconnectedClient(ClientContext *pContext);
	// A new ClientContext is made. 
	virtual void NotifyNewClientContext(ClientContext *pContext);
	// A new Connection has arrived. 
	virtual void NotifyNewConnection(ClientContext *pcontext);
	// A Package have arrived. 
	virtual void NotifyReceivedPackage(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	// The package sucessfully sended. 
	virtual void NotifyWriteCompleted(ClientContext *pContext, DWORD dwIoSize, CIOCPBuffer *pOverlapBuff);
	// An ClientContext is going to be deleted insert more cleanup code if nesseary.  
	virtual void NotifyContextRelease(ClientContext *pContext);
	// Called to do some work. 
	virtual inline void ProcessJob(JobItem *pJob,IOCPS* pServer);
	// Called to add the msg to the log. 
	virtual void AppendLog(CString msg);

protected:	
	// Send an special two buffered package 
	void BuildAndSend(ClientContext *pContext, BYTE _pkgtype, CString str1,CString str2);
	void BuildAndSend(ClientContext *pContext, BYTE _pkgtype, CString str1,UINT nBufferSize2, const BYTE *_pBuff2 );
	void BuildAndSend(ClientContext *pContext, BYTE _pkgtype,  UINT nBufferSize1, const BYTE *_pBuff1,  UINT nBufferSize2, const BYTE *_pBuff2);	
	// Reads the package build with BuildAndSend(..) 
	void ReadPkg(CIOCPBuffer *pBuff, UINT &nSize,BYTE** _pBuff1,  UINT &nSize2,BYTE** _pBuff2, ClientContext *pContext);
	// Computes a signature form Sha1Hash(A+B) and sends it to the client. 
	inline void ComputeAndSendSignature(ClientContext *pContext);	
	// Compute the secure exchanged Session key. 
	inline BOOL ComputeAndSetSessionKey(CIOCPBuffer *pOverlapBuff, int nSize, ClientContext *pContext);
	// Computes the public key (Diffie-Hellman) and sends the key as _keytype (is  PKG_PUBLIC_KEYA or PKG_PUBLIC_KEYB)
	inline void ComputeAndSendPublicKey(ClientContext *pContext, BYTE _keytype);
	// Computes the PublicKeyA and send it (uses ComputeAndSendPublicKey(..))
	inline void ComputeAndSendPublicKeyA(ClientContext* pContext);
	// Computes the PublicKeyB and send it (uses ComputeAndSendPublicKey(..))
	inline void ComputeAndSendPublicKeyB(ClientContext* pContext);
	// Builds a Public key package and sends it to the client. 
	inline void SendPublicKey(ClientContext *pContext, BYTE _keytype, DWORD *_pPublicKey,UINT nPublicKeySize);
	// Reads a Key form package returns NULL if error. 
	inline DWORD* ReadPublicKeyFromBuffer(CIOCPBuffer* pBuff, UINT &nKeySize,ClientContext *pContext);
	// Sends a text message to the Client. 	
	BOOL SendTextMessageTo(ClientContext* pContext, CString sMsg);

	// Encrypt/Decrypt functions.  
	inline int MaxEncyptedPayloadSize(int iMaxLength);	
	CIOCPBuffer* DeCryptBuffer(CIOCPBuffer *pBuff, ClientContext *pContext);
	CIOCPBuffer* EnCryptBuffer(CIOCPBuffer *pBuff, ClientContext *pContext);

	// Package handlers. 	
	void OnPKG_ERRORMSG(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	void OnPKG_TEXT_TO_ALL(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	void OnPKG_USERNAME_PASSWORD(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	void OnPKG_PUBLIC_KEYP(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	void OnPKG_PUBLIC_KEYA(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	void OnPKG_PUBLIC_KEYB(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	void OnPKG_SIGNATURE(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);

private:
	static const DWORD m_DSAKeypubN[64];
#ifndef _IOCPClientMode_
	static const DWORD m_DSAKeypubD[64];
#endif
	static const DWORD m_DSAKeypubE;
};

#endif // !defined(AFX_SecureChatIOCP_H__4093193A_D0A0_4E6A_82FA_65B17A1FEB71__INCLUDED_)
