// SecureChatIOCP.cpp: implementation of the SecureChatIOCP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SecureChat.h"
#include "iocps.h"
#include "SecureChatIOCP.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




const DWORD SecureChatIOCP::m_DSAKeypubN[64] = {
		0xf99223fb, 0x625e88c9, 0x1fa77dc9, 0x3c6361c3, 0xe9a92919, 0xf4bfa25b, 
		0x4247b58c, 0xbdc1cec1, 0x25b0b4fd, 0x88ea361d, 0xb1909686, 0xf59c6edc, 
		0x0a99bffa, 0x33c2b433, 0xfe66ce05, 0xc01e773a, 0x5ad01646, 0x787a48ce, 
		0x5b95cc4a, 0xcd63c5b8, 0x9432cc06, 0xa830a077, 0x8e80cc90, 0x8cd27948, 
		0x8bd1c5a6, 0x635f7a31, 0xd7e1d3f0, 0x3987eea5, 0x2c20433d, 0x5f7e5927, 
		0xca9f9c36, 0xb8d903f8, 0x6467e423, 0xe9a7d14f, 0x058d0a7c, 0x7efb3413, 
		0x373851ad, 0xa801a2b3, 0x383c337f, 0xf6d967b6, 0x91e2194a, 0x877c1fca, 
		0x722d981a, 0x73563cf6, 0x527c7db2, 0xc63f5829, 0x59780705, 0x26440988, 
		0x1ae803bc, 0x612ac808, 0xed5217e2, 0xb6fde648, 0xd9425a87, 0x5a9cadf5, 
		0x6010b36d, 0x42934058, 0x16d6c677, 0xea80ed00, 0x23299845, 0x73ca6dfe, 
		0x5b9697e8, 0xeb0e49a3, 0x9266b8d1, 0x8820e5ed, };
	

// The private Key is only existing in Server.
#ifndef _IOCPClientMode_
const DWORD SecureChatIOCP::m_DSAKeypubD[64] = {
			0xfd52a66b, 0x52ca6690, 0xf265a0f1, 0x08ba2a83, 0x7341150b, 0x06452c7d, 
			0x9fe3f0e2, 0x733d56c7, 0xbdc9ab4d, 0xaf91094e, 0xc3c97caf, 0x36b126a1, 
			0x28072f0b, 0x9eaddf59, 0x2f36a3e9, 0x465dccb9, 0x8a6cf32a, 0x105da5fa, 
			0x961d488a, 0x225371f4, 0x9e786282, 0xe9e86eb3, 0xb73d6a77, 0x61570378, 
			0x38961f7f, 0x7de9e518, 0x898a709e, 0x351f0f62, 0xbf61f92e, 0x4a40940a, 
			0xc04e03ae, 0xd796d66f, 0xed9a9816, 0x9bc53634, 0x5908b1a8, 0xff5222b7, 
			0x7a258bc8, 0xc5566c77, 0x7ad2ccff, 0x4f3b9a79, 0xb696bb87, 0xafa81531, 
			0xf6c91011, 0xf78ed34e, 0x8c52fe76, 0xd97f901b, 0x3ba55a03, 0xc42d5bb0, 
			0x674557d2, 0x40c73005, 0xf38c0fec, 0x79fe9985, 0xe62c3c5a, 0xe7131ea3, 
			0x400b2248, 0xd70cd590, 0x0f39d9a4, 0x47009e00, 0xc21bbad9, 0xa286f3fe, 
			0x92646545, 0x9cb43117, 0x0c447b36, 0x5ac09949, 
	};
#endif
	
const DWORD SecureChatIOCP::m_DSAKeypubE = 3;
	
	
	
SecureChatIOCP::SecureChatIOCP()
{
#ifdef _IOCPClientMode_ 
		m_pPublicKeyP=NULL;
		m_nSizePublicKey=0;
		m_sUserName="";
#endif
}
	
SecureChatIOCP::~SecureChatIOCP()
{
#ifdef _IOCPClientMode_ 
	m_StatusLock.Lock();
	if ( m_pPublicKeyP!=NULL )
	{
			delete [] m_pPublicKeyP;
			m_pPublicKeyP=NULL;
	}
	m_StatusLock.Unlock();
#endif
}

void SecureChatIOCP::AppendLog(CString msg)
{
	
	TRACE("%s\r\n",msg);
	
	int nLen = msg.GetLength();
	if ( nLen>=0 && m_hWnd!=NULL )
	{
		
		char *pBuffer = new char[nLen+1]; 
		strcpy(pBuffer,(const char*)msg);
		pBuffer[nLen]='\0';
		BOOL bRet=FALSE;
		bRet=::PostMessage(m_hWnd, WM_LOGG_APPEND, 0, (LPARAM) pBuffer);
		if(!bRet)
			delete[] pBuffer;
	}
}


/*
* This functions defines what should be done when A job from the work queue is arrived. 
* (not used). 
*/
void SecureChatIOCP::ProcessJob(JobItem *pJob,IOCPS* pServer)
{
	//SecureChatIOCP* pthis= reinterpret_cast<SecureChatIOCP*>(pServer);
}

void SecureChatIOCP::NotifyNewConnection(ClientContext *pcontext)
{
	unsigned int *pBuffer= new unsigned int;
	if(pBuffer!=NULL)
	{
		*pBuffer=pcontext->m_Socket;
		::PostMessage(m_hWnd, WM_NEW_CONNECTION, 0, (LPARAM) pBuffer);
	}

#ifdef _IOCPClientMode_ 

	m_StatusLock.Lock();
	pcontext->m_ContextLock.Lock();
	pcontext->m_pPublickey=m_pPublicKeyP;
	pcontext->m_nPublicKeySize=m_nSizePublicKey;
	pcontext->m_sUsername=m_sUserName;
	pcontext->m_ContextLock.Unlock();
	m_StatusLock.Unlock();

	AppendLog("Sending public key P..");
	m_StatusLock.Lock();
	SendPublicKey(pcontext,PKG_PUBLIC_KEYP,m_pPublicKeyP,m_nSizePublicKey);
	m_StatusLock.Unlock();

#endif
}

void SecureChatIOCP::NotifyWriteCompleted(ClientContext *pContext, DWORD dwIoSize, CIOCPBuffer *pOverlapBuff)
{
	// The pOverlapBuff Buffer are Successfully sended.
	// If we sended an error message Kill the connection  
	if ( pContext && pOverlapBuff->GetPackageType()== PKG_ERRORMSG )
	{
		DisconnectClient(pContext->m_Socket);
	}

}
void SecureChatIOCP::NotifyDisconnectedClient(ClientContext *pContext)
{
	if ( pContext!=NULL && pContext->m_Socket!=INVALID_SOCKET )
	{
		pContext->m_ContextLock.Lock();
		pContext->m_bGotSessionKey=FALSE;
		unsigned int *pBuffer= new unsigned int;
		if(pBuffer!=NULL&&m_hWnd!=NULL)
		{
			*pBuffer=pContext->m_Socket;
			::PostMessage(m_hWnd, WM_DISCONNECT_CLIENT, 0, (LPARAM) pBuffer);
		}else
		{
			delete pBuffer;
			pBuffer=NULL;		

		}
		CString msg;
		CTime  tm= CTime::GetCurrentTime();
		msg.Format("[%s] %s Disconnected. (%s)",tm.Format("%H:%M:%S"),pContext->m_sUsername,GetHostAddress(pContext->m_Socket));
		AppendLog(msg);
		TRACE("Client %i is disconnected\r\n",pContext->m_ID);	

		pContext->m_ContextLock.Unlock();
	
		// We can not Lock m_ContextMapLock inside pContext->m_ContextLock lock -> leads do deadlock.. 
#ifndef _IOCPClientMode_	
		SendTextMessage(msg);
#endif
		// Clean The memory. 
		NotifyNewClientContext(pContext);
		

	}
}

void SecureChatIOCP::NotifyNewClientContext(ClientContext *pContext)
{
	pContext->m_ContextLock.Lock();
	pContext->m_sUsername="";
	pContext->m_sUsername.FreeExtra();
	pContext->m_nPublicKeySize=0;
	pContext->m_pPublickey=NULL;
	pContext->m_bUpdateList=FALSE;
	pContext->m_bGotSessionKey=FALSE;
	// Init the hash struct used for digital signing. 
	memset(&(pContext->m_csha1Hash),0,sizeof(pContext->m_csha1Hash));
	pContext->m_cCryptLib.SHA1_Start(&(pContext->m_csha1Hash));
	pContext->m_ContextLock.Unlock();
}

void SecureChatIOCP::NotifyContextRelease(ClientContext *pContext)
{
	//
	// Remove the Public key if we are in server mode. 
	//
#ifndef _IOCPClientMode_	
	pContext->m_ContextLock.Lock();
	if ( pContext->m_pPublickey!=NULL )
	{
		delete[] pContext->m_pPublickey;
		pContext->m_pPublickey=NULL;
	}
	pContext->m_ContextLock.Unlock();
#endif

}

inline void SecureChatIOCP::ProcessPayload(CIOCPBuffer *pOverlapBuff, int nSize, ClientContext *pContext)
{

	BYTE PackageType=pOverlapBuff->GetPackageType();
	switch ( PackageType) 
	{
	case PKG_TEXT_TO_ALL:
		OnPKG_TEXT_TO_ALL(pOverlapBuff,nSize,pContext);
		break;

	case PKG_USERNAME_PASSWORD:
		OnPKG_USERNAME_PASSWORD(pOverlapBuff,nSize,pContext);
		break; 
	}
}

void SecureChatIOCP::NotifyReceivedPackage(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext)
{

	// No Context? Why do the work ? 
	if ( pContext==NULL )
	{
		AppendLog("pContext==NULL) in NotifyReceivedPackage"); 
		return; 
	}
	// No Connection ?? Why do the work ? 
	if ( pContext->m_Socket==INVALID_SOCKET )
	{
		//AppendLog("pContext->m_Socket==INVALID_SOCKET in NotifyReceivedPackage"); 
		return; 
	}

	BYTE PackageType=pOverlapBuff->GetPackageType();

	switch (PackageType)
	{
	case PKG_ERRORMSG:
		OnPKG_ERRORMSG(pOverlapBuff,nSize,pContext);
		break;

	case PKG_ENCRYPTED:
		{
			//pContext->m_bGotSessionKey=FALSE;
			if(! pContext->m_bGotSessionKey )
			{
				SendErrorMessageTo(pContext->m_Socket,"Server> Session key Not available, you are not authorized");
				CString msg; 
				msg.Format("Client %x (%s) not Authorized",pContext->m_Socket,GetHostAddress(pContext->m_Socket));
				AppendLog(msg);
				break;
			}
			CIOCPBuffer *pDecryptedPKG=DeCryptBuffer(pOverlapBuff,pContext);

			if ( !pDecryptedPKG )
			{
				AppendLog("SECURITY RISK: Warning could not decrypt the clients message.. The remote client may be try to hack your system.");
				DisconnectClient(pContext->m_Socket);
			}else
			{
				// Process it
				ProcessPayload(pDecryptedPKG,pDecryptedPKG->GetUsed(),pContext);
			}
			if ( pDecryptedPKG )
				ReleaseBuffer(pDecryptedPKG);
			break;
		}

#ifdef _IOCPClientMode_ // Handle the package sent from server

	case PKG_PUBLIC_KEYA:
		OnPKG_PUBLIC_KEYA(pOverlapBuff,nSize,pContext);
		break;

	case PKG_SIGNATURE:
		OnPKG_SIGNATURE(pOverlapBuff,nSize,pContext);
		break;
#else  // Handle the package sent from clients. 

	case PKG_PUBLIC_KEYP:
		OnPKG_PUBLIC_KEYP(pOverlapBuff,nSize,pContext);
		break; 

	case PKG_PUBLIC_KEYB:
		OnPKG_PUBLIC_KEYB(pOverlapBuff,nSize,pContext);
		break;

#endif 

	};

}


/*
* Called when a package with user data have arrived.. 
*
*
*/
inline void SecureChatIOCP::OnPKG_ERRORMSG(CIOCPBuffer *pOverlapBuff, int nSize, ClientContext *pContext)
{
	BYTE PayloadType= 255;
	CString sTxtErr;

	PBYTE pPayload=pOverlapBuff->GetPayLoadBuffer();
	pPayload++;

	if( nSize>=MINIMUMPACKAGESIZE+2)
		memcpy(&PayloadType,pPayload,1);

	pPayload++;
	// Assumes that we already have a null termination. 
	if( nSize >=MINIMUMPACKAGESIZE+2 )
		sTxtErr=pPayload;

	pContext->m_sUsername=sTxtErr;
	pContext->m_bUpdateList=TRUE;

	AppendLog(sTxtErr);
}



inline void SecureChatIOCP::OnPKG_TEXT_TO_ALL(CIOCPBuffer *pOverlapBuff, int nSize, ClientContext *pContext)
{

	CString sTxt;
	nSize=pOverlapBuff->GetPackageSize();

	PBYTE pPayload=pOverlapBuff->GetPayLoadBuffer();
	pPayload++;

	// Assumes that we already have a null termination. 
	if( nSize >=0 )
		sTxt=pPayload;

#ifndef _IOCPClientMode_
	AppendLog(pContext->m_sUsername+">"+sTxt);
	SendTextMessage(pContext->m_sUsername+" >"+sTxt);
#else
	AppendLog(sTxt);
#endif

}

inline void SecureChatIOCP::OnPKG_USERNAME_PASSWORD(CIOCPBuffer *pOverlapBuff, int nSize, ClientContext *pContext)
{
	BYTE PayloadType= 255;
	PBYTE pBuff1=NULL;
	PBYTE pBuff2=NULL;
	UINT nBuffSize=0;
	UINT nBuffSize2=0;
	// Read the Package
	ReadPkg(pOverlapBuff,nBuffSize,&pBuff1,nBuffSize2,&pBuff2,pContext);
	if ( pBuff1!=NULL )
	{
		pContext->m_sUsername=pBuff1;
		pContext->m_bUpdateList=TRUE;
		//FIXME: Send Notification to all Users and send 
		// User list to Client. 
		AppendLog("Secure connection established.");
		AppendLog(pContext->m_sUsername+ ", joined Channel..");
		SendTextMessage(pContext->m_sUsername+ ", joined Channel..");


	}
}


/*
* Handle the Public Key P according to Diffie-Hellman 
* key exchange procedure.  	
*  
* Send the respons as Public Key P. 
* 
*/

inline void SecureChatIOCP::OnPKG_PUBLIC_KEYP(CIOCPBuffer *pOverlapBuff, int nSize, ClientContext *pContext)
{	

	UINT  nKeySize=0;
	// read the public key from the buffer. 
	DWORD* pKey=ReadPublicKeyFromBuffer(pOverlapBuff,nKeySize,pContext);
	if ( pKey ) 
	{
		pContext->m_ContextLock.Lock();

		// Make sure that the Public key P is accepted for year 2005, _MINPUBLICKEYPSIZE_ = 1024 bits. 
		// FIXME:  What if the public key P is not prime ? is the security broken ? 
		UINT nPubKeyBitLength= pContext->m_cCryptLib.BNBitLength(pKey,nKeySize);
		if (  nPubKeyBitLength < _MINPUBLICKEYPSIZE_)
		{
			SendErrorMessageTo(pContext->m_Socket,"Error PKG_PUBLIC_KEYP not accepted!, Size to small Minimum 1024 bits. ");
			pContext->m_ContextLock.Unlock();
			return; 
		}

		// We must make a copy of the public key P. 
		// FIXME: allocate data on the heap is bad (hmm change later) 
		DWORD* pPublicKeyP=NULL;
		pPublicKeyP= new DWORD[nKeySize];
		if ( pPublicKeyP )
		{
			memcpy(pPublicKeyP,pKey,nKeySize*sizeof(DWORD));
		}else
		{
			AppendLog("Error pPublicKeyP=NULL, not enough memory");
			DisconnectClient(pContext->m_Socket);
			pContext->m_ContextLock.Unlock();
		}

		// allocate data on the heap is bad (hmm change later) 
		if ( pContext->m_pPublickey )
			delete[] pContext->m_pPublickey;

		pContext->m_pPublickey = pPublicKeyP;

		// Generate private key.. (just a Random nr) 
		pContext->m_cCryptLib.BNMakeRandomNr(pContext->m_Privatekey,_PRIVATEKEYSIZE_);

		pContext->m_bGotSessionKey=FALSE;

		pContext->m_nPublicKeySize=nKeySize;

		pContext->m_sUsername="Public key Accepted.";

		// Compute And Send Public Key A. 
		// FIXME : Should post this part into the 
		// IOCP for fair cpu clock distribution.
		// Takes about ~40ms.. 
		ComputeAndSendPublicKeyA(pContext);

		pContext->m_ContextLock.Unlock();

	} else
	{
		AppendLog("OnPKG_PUBLIC_KEYP Failed Package error");
	}

}



/*
* ComputeAndSendPublicKey(ClientContext *pContext, BYTE _keytype)
*
* The Function computes the punlic key according to Diffie-Hellman algorithm 
* The Function also hash the Computed key for digital signing later on.. 
*
* _keytype is PKG_PUBLIC_KEYA or PKG_PUBLIC_KEYB
*
* Observe that the function assumes that private random key a is 
* already Initialized. 
*
*/
void SecureChatIOCP::ComputeAndSendPublicKey(ClientContext *pContext, BYTE _keytype)
{
	// Be safe or no need to do the work 
	if ( !pContext || !pContext->m_pPublickey || pContext->m_Socket==INVALID_SOCKET)
		return;

	DWORD bnPublicKeyAB[_PRIVATEKEYSIZE_];
	DWORD bnG[_PRIVATEKEYSIZE_];
	UINT nPublicKeySize=_PRIVATEKEYSIZE_;

	// Lock The  context. (we are going to access private members. 
	pContext->m_ContextLock.Lock();

	pContext->m_cCryptLib.BNSetEqualdw(bnG,5,_PRIVATEKEYSIZE_);
	// A= g^ a mod(p). 
	pContext->m_cCryptLib.BNModExp(bnPublicKeyAB, bnG, pContext->m_Privatekey, pContext->m_pPublickey,nPublicKeySize);
	// Hash it for Digital Signing (later on)..
	pContext->m_cCryptLib.SHA1_Hash((PBYTE)bnPublicKeyAB,_PRIVATEKEYSIZE_*4,&pContext->m_csha1Hash);
	pContext->m_ContextLock.Unlock();

	// Send the public key. 
	SendPublicKey (pContext,_keytype,bnPublicKeyAB,nPublicKeySize);
}


/*
* Compute and send Public key A. 	
*/
void SecureChatIOCP::ComputeAndSendPublicKeyA(ClientContext *pContext)
{
	ComputeAndSendPublicKey(pContext,PKG_PUBLIC_KEYA);	
}


/*
* Compute and send Public keyB. 	
*/
void SecureChatIOCP::ComputeAndSendPublicKeyB(ClientContext *pContext)
{
	ComputeAndSendPublicKey(pContext,PKG_PUBLIC_KEYB);
}

/*
* This function Build a package of type 	
*
* [obligatory headersize|Headertype (_keytype)| public key size (nPublicKeySize) | Publickey ( * obligatory headersize|Headertype (_keytype)| public key size (nPublicKeySize) | Publickey] 
*
* and sends it to client. 
*/
void SecureChatIOCP::SendPublicKey(ClientContext *pContext, BYTE _keytype, DWORD *_pPublicKey, UINT nPublicKeySize)
{

	CIOCPBuffer *pBuff=AllocateBuffer(IOWrite);
	if( !pBuff )
	{
		AppendLog("SendPublicKey FAILED pBuff=NULL");
		return;
	}

	UINT nPayLoadLen=sizeof(DWORD)+sizeof(BYTE)+nPublicKeySize*sizeof(DWORD);

	pBuff->EmptyUsed();
	// Size Header
	pBuff->AddData(nPayLoadLen);
	// Payload type 
	pBuff->AddData((BYTE)_keytype);
	// The size of nPublicKey
	pBuff->AddData(nPublicKeySize);	
	// add the public key. 
	pBuff->AddData((PBYTE)_pPublicKey,nPublicKeySize*4);
	ASend(pContext,pBuff);

}

/*
* Please see BuildAndSend(ClientContext *pContext, BYTE _pkgtype, UINT nBufferSize1, BYTE *_pBuff1, UINT nBufferSize2, BYTE *_pBuff2)
*
*
*/

void SecureChatIOCP::BuildAndSend(ClientContext *pContext, BYTE _pkgtype, CString str1, CString str2)
{
	BuildAndSend(pContext,_pkgtype,str1.GetLength(),(PBYTE)str1.GetBuffer(str1.GetLength()),str2.GetLength(),(PBYTE)str2.GetBuffer(str1.GetLength()));
}

void SecureChatIOCP::BuildAndSend(ClientContext *pContext, BYTE _pkgtype, CString str1,UINT nBufferSize2, const BYTE *_pBuff2 )
{
	BuildAndSend(pContext,_pkgtype,str1.GetLength(),(PBYTE)str1.GetBuffer(str1.GetLength()),nBufferSize2,_pBuff2);
}



/*
* This function Build a package of type 	
*
* [obligatory headersize|Headertype (_keytype)| buff1 size| buff1 |buff2 size| buff2 ]
* and sends it to client. 
*/

void SecureChatIOCP::BuildAndSend(ClientContext *pContext, BYTE _pkgtype, UINT nBufferSize1,const BYTE *_pBuff1, UINT nBufferSize2, const BYTE *_pBuff2)
{

	if ( !pContext->m_bGotSessionKey )
	{
		AppendLog("BuildAndSend FAILED, no Session key..");
		return;
	}

	UINT nPayLoadLen=sizeof(BYTE)+sizeof(UINT)+nBufferSize1+sizeof(UINT)+nBufferSize2+2; // two null termination. 

	if ( nPayLoadLen > MAXIMUMPAYLOADSIZE)
	{
		AppendLog("BuildAndSend FAILED, nPayLoadLen > MAXIMUMPAYLOADSIZE");
		return;
	}

	if ( nPayLoadLen > MaxEncyptedPayloadSize(MAXIMUMPAYLOADSIZE-1) )
	{
		AppendLog("BuildAndSend FAILED, nPayLoadLen > MaxEncyptedPayloadSize");
		return;  
	}


	CIOCPBuffer *pBuff=AllocateBuffer(IOWrite);
	if ( !pBuff )
	{
		AppendLog("BuildAndSend FAILED pBuff=NULL");
		return;
	}

	pBuff->EmptyUsed();
	// Size Header
	pBuff->AddData(nPayLoadLen);
	// Payload type 
	pBuff->AddData((BYTE)_pkgtype);
	// The size of the buffer
	pBuff->AddData(nBufferSize1);	
	// add the buffer. 
	pBuff->AddData(_pBuff1,nBufferSize1);
	pBuff->AddData((BYTE)0);
	// The size of the buffer
	pBuff->AddData(nBufferSize2);	
	// add the buffer. 
	pBuff->AddData(_pBuff2,nBufferSize2);
	pBuff->AddData((BYTE)0);
	// Encrypt the data.. 
	pBuff=EnCryptBuffer(pBuff,pContext);
	ASend(pContext,pBuff);
}



/*
* ReadPublicKeyFromBuffer(CIOCPBuffer *pBuff, UINT &nKeySize,ClientContext *pContext)
*	
* Reads public key from buffer pBuff. (Reads the packages created with SendPublicKey(..)
* 
* Output: 
* - Returns a Pointer to the public key. (if Successfull). 
* - nKeySize the size (in DWORD) of the key. 
*
*/

DWORD* SecureChatIOCP::ReadPublicKeyFromBuffer(CIOCPBuffer *pBuff, UINT &nKeySize,ClientContext *pContext)
{
	DWORD* pKey=NULL;
	nKeySize=0;
	UINT nSize=pBuff->GetUsed();
	PBYTE pPayload=pBuff->GetPayLoadBuffer()+1; // Point to the nKeySize

	if ( nSize>=MINIMUMPACKAGESIZE+4 )
	{
		memcpy(&nKeySize,pPayload,4);
	}
	else
	{
		SendErrorMessageTo(pContext->m_Socket,"Error PKG_PUBLIC_KEYX not accepted!, Size to small.");
		return NULL;
	}
	// If the keysize is reasonable size 0 < x < 4000 bits. 
	if( nKeySize>0 && nKeySize < (MAXIMUMPAYLOADSIZE-4-1)/4) 
	{
		pPayload+=sizeof(UINT);
		pKey=(DWORD*)pPayload;
	}
	else
	{
		SendErrorMessageTo(pContext->m_Socket,"Error PKG_PUBLIC_KEYX not accepted!");
	}

	return pKey;
}

/*
*	Reads a package created with BuildAndSend(..)
*
*
*/
void SecureChatIOCP::ReadPkg(CIOCPBuffer *pBuff, UINT &nSize, BYTE **_pBuff1, UINT &nSize2, BYTE **_pBuff2, ClientContext *pContext)
{


	pBuff->DUMP();

	nSize=0;
	nSize2=0;
	*_pBuff1=NULL;
	*_pBuff2=NULL;
	UINT nPkgSize=pBuff->GetUsed();
	if ( nPkgSize > MAXIMUMPACKAGESIZE )
	{

		return;
	}

	PBYTE pPayload=pBuff->GetPayLoadBuffer()+1; // Point to the nSize

	if ( nPkgSize>=MINIMUMPACKAGESIZE+sizeof(nSize))
	{
		memcpy(&nSize,pPayload,sizeof(nSize));
	}
	else
	{
		SendErrorMessageTo(pContext->m_Socket,"Error PKG not accepted!, Size to small.");
		return;
	}

	// If the nSize of the buffer is reasonable size 0 < x < 4000 bits. 
	if ( nSize>0 && nSize < (MAXIMUMPAYLOADSIZE-sizeof(nSize)-1)) 
	{
		pPayload+=sizeof(nSize);
		*_pBuff1=pPayload;
	}
	else
	{
		SendErrorMessageTo(pContext->m_Socket,"Error PKG not accepted! Username is Empty.");
		return;
	}

	pPayload+=nSize+1; // Size of the buffer and the null termination. 

	if ( nPkgSize>=MINIMUMPACKAGESIZE+sizeof(nSize)+nSize+sizeof(nSize))
	{
		memcpy(&nSize2,pPayload,sizeof(nSize2));
	}
	else
	{
		SendErrorMessageTo(pContext->m_Socket,"Error PKG not accepted!, Size to small.");
		return;
	}


	// If the nSize of the buffer is reasonable size 0 < x < 4000 bits. 
	if ( nSize2>0 && nSize2 < (MAXIMUMPAYLOADSIZE-sizeof(nSize)-1-nSize-sizeof(nSize))) 
	{
		pPayload+=sizeof(nSize2);
		*_pBuff2=pPayload;
	}
	else
	{
		SendErrorMessageTo(pContext->m_Socket,"Error PKG not accepted!");
		return; 
	}

}



/*
* The function computes the session key of size _PRIVATEKEYSIZE_ according to Diffie-Hellman algorithm, 
* given that:
*
*
* - pOverlapBuff contains the public key A or public Key B
* - The private key is already randomly generated. 
* The CRijndael is used with 256bit key and a CBC with a chain of 128bits
* 
* The function returns TRUE is successfull, FALSE if not. 
* 
*/


BOOL SecureChatIOCP::ComputeAndSetSessionKey(CIOCPBuffer *pOverlapBuff, int nSize, ClientContext *pContext)
{

	UINT  nKeySize=0;
	DWORD bnSessionKey[_PRIVATEKEYSIZE_];

	// read the public key from the buffer. 
	DWORD* pKey=ReadPublicKeyFromBuffer(pOverlapBuff,nKeySize,pContext);

	// if we have a key 
	if ( pKey )
	{
		pContext->m_ContextLock.Lock();

		// Hash PublicKeyA or B for Digital Signing (later on).. 
		pContext->m_cCryptLib.SHA1_Hash((PBYTE)pKey,nKeySize*4,&pContext->m_csha1Hash);
		// S= A^ b mod(p). 
		pContext->m_cCryptLib.BNModExp(bnSessionKey, pKey, pContext->m_Privatekey, pContext->m_pPublickey,nKeySize);

		// Use the Session key.. (we do not trust it until we check the signature.)
		pContext->m_cCryptor.MakeKey((const char * )bnSessionKey,(const char * )(bnSessionKey+8),32,16);

		pContext->m_ContextLock.Unlock();

		return TRUE; 
	}
	return FALSE; 
}


/*
* 
* The Function Computes The KeyB Accourding to Diffie-Hellman 
* Algorithm The Function also Adds The the Computed key into the
* Hashvalue for digital signing. 
*
*/
void SecureChatIOCP::ComputeAndSendSignature(ClientContext *pContext)
{
	// Be Safe 
	if( !pContext )
		return;
#ifndef _IOCPClientMode_

	// FIXME: Change later. 
	const UINT nSize=sizeof(m_DSAKeypubD)/4;
	DWORD S[nSize];
	int iRet=0;


	pContext->m_ContextLock.Lock();

	// Finish the Hash of public key A and key B. 
	DWORD aHashValue[_HASHSIZE_/4];

	pContext->m_cCryptLib.BNSetZero(aHashValue,_HASHSIZE_/4);
	pContext->m_cCryptLib.BNSetZero(S,nSize);


	pContext->m_cCryptLib.SHA1_Finish((unsigned char*)aHashValue,&pContext->m_csha1Hash);

	TRACE("aHashValue %s \r\n",pContext->m_cCryptLib.BNPrintC(aHashValue,_HASHSIZE_/4));

	// FIXME: REMOVE LATER: 
	/*	
	CString stmp;
	stmp.Format("aHashValue %s \r\n",pContext->m_cCryptLib.BNPrintC(aHashValue,_HASHSIZE_/4));
	AppendLog(stmp);*/

	//  Compute hash^d mod n
	iRet=pContext->m_cCryptLib.BNModExp(S,aHashValue,m_DSAKeypubD,m_DSAKeypubN,nSize);	

	pContext->m_sUsername="Sending signature.";

	AppendLog("Sending signature..");

	pContext->m_bUpdateList=TRUE;

	pContext->m_ContextLock.Unlock();

	SendPublicKey(pContext,PKG_SIGNATURE,S,nSize);
#endif

}





/*
* Handle the Signaature accourding to RSA alghorithm, 
*  
*/
inline void SecureChatIOCP::OnPKG_SIGNATURE(CIOCPBuffer *pOverlapBuff, int nSize, ClientContext *pContext)
{	


	// Be safe
	if ( !pContext || !pContext->m_pPublickey || !pOverlapBuff )
		return;

	// FIXME: Change later. Size of is BAD can give different answer (depends on compilation)
	const UINT nPubkeySize=sizeof(m_DSAKeypubN)/4;
	DWORD aRefHashValue[nPubkeySize];
	DWORD aPubKeyE[nPubkeySize];
	int iRet=0;


	// Finish the Hash of public key A and key B. 
	DWORD aHashValue[_HASHSIZE_/4];

	// read the signature from the buffer. 
	UINT  nKeySize=0;
	DWORD* pSig=ReadPublicKeyFromBuffer(pOverlapBuff,nKeySize,pContext);

	// If we have a signature Check it. 
	if ( pSig && nKeySize == nKeySize)
	{
		pContext->m_ContextLock.Lock();

		pContext->m_cCryptLib.BNSetZero(aRefHashValue,nPubkeySize);
		pContext->m_cCryptLib.BNSetEqualdw(aPubKeyE,m_DSAKeypubE,nPubkeySize);

		// Compute the hash value. 
		pContext->m_cCryptLib.SHA1_Finish((unsigned char*)aHashValue,&pContext->m_csha1Hash);


		TRACE("aHashValue %s \r\n",pContext->m_cCryptLib.BNPrintC(aHashValue,_HASHSIZE_/4));

		//  Compute y=(S)^e mod n ptmp2=e=3. 
		iRet=pContext->m_cCryptLib.BNModExp(aRefHashValue,pSig,aPubKeyE,m_DSAKeypubN,nPubkeySize);

		// Check if signature was correct..
		if ( iRet >= 0 && pContext->m_cCryptLib.BNIsEqual(aRefHashValue,aHashValue,_HASHSIZE_/4))
		{
			pContext->m_bGotSessionKey=TRUE;
			AppendLog("Signature verified..");
			AppendLog("Secure connection established.");

			// We have Secure Connection to the server. 

			// Send the user name and password..
			BuildAndSend(pContext,PKG_USERNAME_PASSWORD,pContext->m_sUsername,"dummy");		

		} 
		else
		{
			AppendLog("Signature verfication failed.");
			SendErrorMessageTo(pContext->m_Socket,"Error Signature not accepted!");
			pContext->m_ContextLock.Unlock();	
		}
		pContext->m_ContextLock.Unlock();

	}
	else
	{
		AppendLog("Signature verfication failed. (incorrect package)");
		SendErrorMessageTo(pContext->m_Socket,"Error Signature not accepted!");
	}

}




/*
* Handle the Public Key A according to Diffie-Hellman 
* key exchange procedure.  	
*  
* Send the respons as Public Key P. 
* 
*/
inline void SecureChatIOCP::OnPKG_PUBLIC_KEYA(CIOCPBuffer *pOverlapBuff, int nSize, ClientContext *pContext)
{	

	// Be safe
	if ( !pContext || !pContext->m_pPublickey || !pOverlapBuff )
		return;

	pContext->m_ContextLock.Lock();
	// Generate private key.. (just a Random nr) 
	pContext->m_cCryptLib.BNMakeRandomNr(pContext->m_Privatekey,_PRIVATEKEYSIZE_);
	pContext->m_ContextLock.Unlock();

	if ( ComputeAndSetSessionKey(pOverlapBuff,nSize,pContext) )
	{
		AppendLog("Received public key A..");
		// Compute And Send Public Key B. 
		// FIXME : Should post this part into the 
		// IOCP for fair cpu clock distribution.
		// Takes about ~40ms.. 
		ComputeAndSendPublicKeyB(pContext);

		// if USE_SIGNATURE is defined here we do not set the m_bGotSessionKey to true, even if 
		// the session key is exchanged. Because we 
		// Are not protected from "Man in middle attacks". 
#ifndef USE_SIGNATURE
		pContext->m_ContextLock.Lock();
		pContext->m_bGotSessionKey=TRUE;
		// We have Secure Connection to the server. 
		// Send the user name and password..
		BuildAndSend(pContext,PKG_USERNAME_PASSWORD,pContext->m_sUsername,"dummypwd");
		pContext->m_ContextLock.Unlock();
		AppendLog("Secure connection established.");		
#endif
	}
}


/*
* Handle the Public Key B according to Diffie-Hellman 
* key exchange procedure.  	
*  
* Send the respons as Public Key P. 
* 
*/
inline void SecureChatIOCP::OnPKG_PUBLIC_KEYB(CIOCPBuffer *pOverlapBuff, int nSize, ClientContext *pContext)
{	

	// Be safe
	if ( !pContext || !pContext->m_pPublickey || !pOverlapBuff)
		return;

	if ( ComputeAndSetSessionKey(pOverlapBuff,nSize,pContext) )
	{
		// The Server is not Protected from "man in middle attack"
		// the server should authorize the client by a password or something 
		// else. 
		pContext->m_ContextLock.Lock();
		pContext->m_bGotSessionKey=TRUE;
		pContext->m_ContextLock.Unlock();


		// Compute and send Signature. . 
		// FIXME : Should post this part into the 
		// IOCP for fair cpu clock distribution.
		// Takes about > 500ms.. 
#ifdef USE_SIGNATURE
		ComputeAndSendSignature(pContext);
#endif
	}
}




/* 
* EnCryptBuffer(CIOCPBuffer *pBuff, ClientContext *pContext)
* 
* Encrypts The buffer with the Rijndael, Cipher Block Chaining (CBC) cipher. 
* designed by Joan Daemen and Vincent Rijmen as a candidate algorithm for the AES
* The cipher operates on 16 byte blocks and 256 bits keylength. 
*
* The function also computes an CRC16 (two bytes) checksum and add it to the buffer 
* to recognize incorrect decryption on the other side. 
* 
* If the buffer size plus the two bytes that come from the CRC16 is not a multiple of 
* 16 bytes (needed for the encryption), random data is added at the end.
*
* Returns NULL if something went wrong or the encrypted buffer. 
*
*/

CIOCPBuffer *SecureChatIOCP::EnCryptBuffer(CIOCPBuffer *pBuff, ClientContext *pContext)
{

	if ( pBuff==NULL || pContext==NULL )
	{
		ReleaseBuffer(pBuff);
		return NULL;
	}
	if ( !pContext->m_bGotSessionKey)
	{
		ReleaseBuffer(pBuff);
		return NULL;
	}

	CIOCPBuffer *pCrypBuff=NULL;

	//
	// Allocate Buffer for the encrypted pkg. 
	//
	pCrypBuff=AllocateBuffer(IOWrite);

	if ( pCrypBuff!=NULL )
	{
		//
		// Compute CRC16
		// 
		unsigned short usCRC16;
		pContext->m_cCryptor.crc16_init(&usCRC16);
		pContext->m_cCryptor.crc16_update(&usCRC16,pBuff->GetBuffer(),pBuff->GetUsed());
		pContext->m_cCryptor.crc16_final(&usCRC16);

		// 
		// Add the CRC16 to the Buffer
		//
		if ( !pBuff->AddData(usCRC16) )
		{
			AppendLog("Error pBuff->AddData(usCRC16) in EnCryptBuffer");
			DisconnectClient(pContext->m_Socket);
			ReleaseBuffer(pCrypBuff);
		}

		//
		//  Check if The Buffer size is a multiple of the blocksize, if not 
		//  add some random nr. 
		// 

		int iBlockSize=16; 
		int iBufferRest=0;
		UINT iBufferLenght=0;
		iBufferLenght=pBuff->GetUsed();
		iBufferRest=iBufferLenght%iBlockSize;

		// How Much is needed to make the buffersize to be a multible of the block size? 
		if ( iBufferRest!=0 )
		{
			iBufferRest=iBlockSize-iBufferRest;
		}
		// add random Numbers at the end so we will have an cryptable buffer. 
		for ( int i=0; i<iBufferRest; i++ )
		{
			if ( !pBuff->AddData((BYTE)(rand()%255)) )
			{
				AppendLog("Error pBuff->AddData((BYTE)(rand()%255) in EnCryptBuffer");
				DisconnectClient(pContext->m_Socket);
				ReleaseBuffer(pCrypBuff);
			}
		}

		// We have a new length. 
		iBufferLenght=pBuff->GetUsed();
		// For the package type. 
		iBufferLenght++;

		//
		// Configure the new package. 
		//
		if ( iBufferLenght+MINIMUMPACKAGESIZE>MAXIMUMPACKAGESIZE )
		{
			AppendLog("Error package to big to fit in the buffer");
			DisconnectClient(pContext->m_Socket);
			ReleaseBuffer(pCrypBuff);
		}
		// Add the size of the buffer to the beging.We will not crypt this part.
		pCrypBuff->AddData(iBufferLenght);
		// Add the Type. 
		pCrypBuff->AddData((BYTE)PKG_ENCRYPTED);

		//
		// Encrypt and add to payload. 
		//
		try
		{	
			pContext->m_ContextLock.Lock();
			pContext->m_cCryptor.ResetChain();	// Because of CBC
			pContext->m_cCryptor.Encrypt((char const*)pBuff->GetBuffer(),(char*)pCrypBuff->GetBuffer()+MINIMUMPACKAGESIZE+1,iBufferLenght-1,1);
			pContext->m_ContextLock.Unlock();
		}
		catch(exception& roException)
		{

			AppendLog("Error Could not encrypt in EnCryptBuffer");
			DisconnectClient(pContext->m_Socket);
			ReleaseBuffer(pCrypBuff);	
			pContext->m_ContextLock.Unlock();
			pCrypBuff=NULL;
			return NULL;

		}

		// add the payload. 
		pCrypBuff->Use(pBuff->GetUsed());

		ReleaseBuffer(pBuff);

		// 
		// Finished... 
		// 
	}else
	{
		AppendLog("Error Could not allocate memory in EnCryptBuffer");
	}
	return pCrypBuff;
}

/* 
* DeCryptBuffer(CIOCPBuffer *pBuff, ClientContext *pContext)
*
* Decrypts the encrypted buffer. (see EnCryptBuffer(..) for more info) 
*
* Returns the decrypted Buffer or return NULL if failed (or CRC16 did not mach)
*
*/

CIOCPBuffer* SecureChatIOCP::DeCryptBuffer(CIOCPBuffer *pBuff, ClientContext *pContext)
{
	if ( pBuff==NULL || pContext==NULL )
		return NULL;

	if ( !pContext->m_bGotSessionKey )
		return NULL;


	CIOCPBuffer *pCrypBuff=NULL;
	//
	// Allocate Buffer for the encrypted pkg. 
	//
	pCrypBuff=AllocateBuffer(IOWrite);
	if ( pCrypBuff!=NULL )
	{


		//
		// Decrypt 
		//

		int iBufferLenght=pBuff->GetPackageSize();
		try
		{
			pContext->m_ContextLock.Lock();
			pContext->m_cCryptor.ResetChain();	// Because of CBC
			pContext->m_cCryptor.Decrypt((char const*)pBuff->GetBuffer()+MINIMUMPACKAGESIZE+1,(char *)pCrypBuff->GetBuffer(),iBufferLenght-1,1);
			pContext->m_ContextLock.Unlock();
		}
		catch(exception& roException)
		{
			AppendLog("Error Could not encrypt in DeCryptBuffer");
			ReleaseBuffer(pCrypBuff);	
			pCrypBuff=NULL;
			return NULL;
		}

		//
		// Get the CRC Data from the Decrypted package and Make a package test. 
		//

		// First we have to tell it that it have a header. 
		pCrypBuff->Use(MINIMUMPACKAGESIZE);

		// Get the PackageSize. 
		iBufferLenght=pCrypBuff->GetPackageSize();

		//
		// Check if the size was correct
		//
		if ( iBufferLenght>MAXIMUMPACKAGESIZE-MINIMUMPACKAGESIZE )
		{
			AppendLog("Error Could not dencrypt in DeCryptBuffer. (the header size was to big)");
			ReleaseBuffer(pCrypBuff);
			return NULL;
		}

		// well we have to tell our buffer that it has the data.
		pCrypBuff->Use(iBufferLenght);


		unsigned short uspkgCRC16;

		// We put the two byte long CRC cheksum at the end of package..
		memcpy(&uspkgCRC16,pCrypBuff->GetBuffer()+MINIMUMPACKAGESIZE+iBufferLenght,sizeof(unsigned short));

		//
		// Compute CRC16
		// 
		unsigned short usCRC16;
		pContext->m_cCryptor.crc16_init(&usCRC16);
		pContext->m_cCryptor.crc16_update(&usCRC16,pCrypBuff->GetBuffer(),pCrypBuff->GetUsed());
		pContext->m_cCryptor.crc16_final(&usCRC16);

		// The package is not Decrypted correctly. 
		if ( uspkgCRC16!=usCRC16 )
		{
			AppendLog("CRC16 cheksum Error. in DeCryptBuffer.");
			ReleaseBuffer(pCrypBuff);
			return NULL;
		}

		// 
		// Finished... 
		// 
	}else
	{
		AppendLog("Error Could not allocate memory in EnCryptBuffer");
		//DisconnectClient(pContext->m_Socket);
	}
	return pCrypBuff;

}



int SecureChatIOCP::MaxEncyptedPayloadSize(int iMaxLength)
{
	//
	// For encryption we need some extra space. . 
	// 

	// We have to make room for another sizeheader,type header  
	// and also The CRC Checksum 
	iMaxLength-=(MINIMUMPACKAGESIZE+sizeof(unsigned short)+1);
	// Furthermore we have to be sure that the maximumsize is 
	// a multipe of the blocksize (16). 
	// e.g a maximum size of 500 or 499 ot 488 results will be increased 
	// to 512 because of encryption algorithm.. The total size of the data 
	// must be a multiple of 16. 
	int iMaxCryptSize=MAXIMUMENCRYPSIZE-MINIMUMPACKAGESIZE-MINIMUMPACKAGESIZE-sizeof(unsigned short)-1;
	//iMaxLength=(iMaxLength>iMaxCryptSize) ? iMaxCryptSize : iMaxLength;
	return min(iMaxLength,iMaxCryptSize);
}


void SecureChatIOCP::SendTextMessage(CString msg)
{
	// FIXME: Should post this into IOCP so it is handled by IOWORKERS. 
	m_ContextMapLock.Lock();

	UINT nSize= m_ContextMap.GetCount();
	if ( m_ContextMap.GetCount()>0 )
	{
		POSITION pos = m_ContextMap.GetStartPosition ();
		// Here we must check if the m_ContextMap.GetCount() is > 0 because 
		// One or more clients can be disconnected handling SendTextMessageTo(..)
		while ( pos != NULL && m_ContextMap.GetCount()>0 ) 
		{

			unsigned int iKey;
			ClientContext *pContext=NULL;
			m_ContextMap.GetNextAssoc (pos, iKey,pContext);
			if ( pContext!=NULL )
			{
				SendTextMessageTo(pContext,msg);
			}
		}
	}
	m_ContextMapLock.Unlock(); 	

}

/*
* Send Message to Client with ID  iClientID	
*
*/
BOOL SecureChatIOCP::SendTextMessageTo(int iClientID, CString sMsg)
{

	BOOL bRet=FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext = FindClient(iClientID);

	if ( pContext == NULL )
	{
		m_ContextMapLock.Unlock();
		return FALSE;
	}

	bRet=SendTextMessageTo(pContext,sMsg); 
	m_ContextMapLock.Unlock();
	return bRet;
}

/*
* Returns true if we have active connections. 
*
*/
BOOL SecureChatIOCP::IsConnected()
{
	UINT nSizeOfConnectedClients=0;
	m_ContextMapLock.Lock();
	nSizeOfConnectedClients=m_ContextMap.GetCount();
	m_ContextMapLock.Unlock();
	return nSizeOfConnectedClients>0;
}


BOOL SecureChatIOCP::SendTextMessageTo(ClientContext* pContext, CString sMsg)
{

	if ( !pContext->m_bGotSessionKey )
	{
		//AppendLog("Client is not authorized");
		return FALSE;
	}

	UINT nBufLen = sMsg.GetLength();
	// Add one to the size header for the null termination byte. 
	nBufLen++;
	// Add one for the Payload type (text)
	nBufLen++;

	if ( nBufLen>=MaxEncyptedPayloadSize(MAXIMUMPAYLOADSIZE-2) )
	{
		AppendLog("SendMessageTo FAILED Message to long for encryption..");
		return FALSE;
	}

	if ( nBufLen>=MAXIMUMPAYLOADSIZE || nBufLen<=0 )
	{
		AppendLog("SendMessageTo FAILED Message to long or zero..");
		return FALSE;
	}

	CIOCPBuffer *pBuff=AllocateBuffer(IOWrite);

	if ( !pBuff )
	{
		AppendLog("SendMessageTo FAILED pOverlapBuff=NULL");
		return FALSE;
	}

	pBuff->EmptyUsed();
	// Size Header
	pBuff->AddData(nBufLen);
	// Payload Header 
	pBuff->AddData((BYTE)PKG_TEXT_TO_ALL);
	// Add the string. 
	int length=sMsg.GetLength();
	pBuff->AddData((PBYTE) sMsg.GetBuffer(length),length);
	//Extra Null Teriminate (for Strings) 
	pBuff->AddData((BYTE)'\0');
	// Encrypt the buffer
	pBuff=EnCryptBuffer(pBuff,pContext);
	// Send it. 
	ASend(pContext,pBuff);
	return TRUE;

}


BOOL SecureChatIOCP::SendErrorMessageTo(int iClientID, CString sMsg)
{
	UINT nBufLen = sMsg.GetLength();
	// Add one to the size header for the null termination byte. 
	nBufLen++;
	// Add one for the message type (encrypted/SessionExchange/ERROR_MESSAGE)..  
	nBufLen++;
	// Add one for the Payload type (text)
	nBufLen++;

	if ( nBufLen>=MAXIMUMPAYLOADSIZE || nBufLen<=0 )
	{
		AppendLog("SendMessageTo FAILED Message to long or zero..");
		return FALSE;
	}

	CIOCPBuffer *pBuff=AllocateBuffer(IOWrite);

	if ( !pBuff )
	{
		AppendLog("SendMessageTo FAILED pOverlapBuff=NULL");
		return FALSE;
	}

	// Make sure that buffer is empty  
	pBuff->EmptyUsed();
	// Size Header
	pBuff->AddData(nBufLen);
	// Message Header
	pBuff->AddData((BYTE)PKG_ERRORMSG);
	// Payload Header 
	pBuff->AddData((BYTE)PKG_ERRORMSG);
	// Add the string. 
	int length=sMsg.GetLength();
	pBuff->AddData((PBYTE) sMsg.GetBuffer(length),length);
	//Extra Null Teriminate (for Strings) 
	pBuff->AddData((BYTE)'\0');
	ASend(iClientID,pBuff);
	return TRUE; 

}



