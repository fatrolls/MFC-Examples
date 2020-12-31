// IOCPBuffer.h: interface for the CIOCPBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOCPBUFFER_H__87DEF694_32D6_4F21_8FF5_E16184A9CDC3__INCLUDED_)
#define AFX_IOCPBUFFER_H__87DEF694_32D6_4F21_8FF5_E16184A9CDC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*
 * This Class is used to pass around the buffer and the operation that 
 * is done asynchronously. 
 *
 */
#include "IOCPS.h"

class CIOCPBuffer   
{
public:
	void Init();	
	PBYTE GetPayLoadBuffer();
	BOOL CreatePackage(BYTE Type, UINT iFilesize,UINT iBufferSize, const BYTE *const pData);
	BOOL GetPackageInfo(BYTE &Type, BYTE &key, CString &stxt);
	BOOL CreatePackage(BYTE Type, BYTE key,  CString stxt);
	BOOL GetPackageInfo(BYTE &Type,BYTE &key1,BYTE &key2,BYTE &key3, CString &stxt);
	// Used with overlapped.. 
	OVERLAPPED			m_ol;
	BOOL Flush(UINT nBytesToRemove);
	POSITION GetPosition();
	void SetPosition(POSITION pos);    
	WSABUF * GetWSABuffer();
	// sets the SequenceNumber of this object. 
	void SetSequenceNumber(int nr);
	// Get The sequensNumber of the buffer object. 
	int GetSequenceNumber();
	// Setup Different Types in buffer. 
	void SetupWrite();
	void SetupRead();
	void SetupZeroByteRead();
	int GetOperation();
	void SetOperation(int op);
	void EmptyUsed();
	UINT Use(UINT nSize);
	UINT GetUsed();
	//UINT GetSize();
	BOOL IsValid();
	// DUMP the buffer. (For Debug)
	void DUMP();
	// Write different types of variabels to the buffer
	BOOL AddData(const BYTE * pData,UINT nSize);
	BOOL AddData(const char * pData,UINT nSize);
	BOOL AddData(BYTE data);
	BOOL AddData(UINT data);
	BOOL AddData(unsigned short data);
	
	//  Create different type of Packages in the Buffer..
	BOOL CreatePackage(CString stxt);
	BOOL CreatePackage(BYTE Type,CString stxt);
	BOOL CreatePackage(BYTE Type,UINT nData, CString stxt);
	BOOL CreatePackage(BYTE Type);
    BOOL CreatePackage(BYTE Type,BYTE key1,BYTE key2,BYTE key3, CString stxt);
	//
	// Get information from the Package.. 
	//
	// Reurns the Pakage size if possible -1 if error. 
	UINT GetPackageSize();
	// Gets The package Type returns 255 if error. 
	BYTE GetPackageType();
	// Reads the info from a package created with CreatePackage(CString stxt);
	BOOL GetPackageInfo(CString &stxt);
	// Reads the info from a package created with CreatePackage(BYTE Type,CString stxt);
	BOOL GetPackageInfo(BYTE &Type, CString &stxt);
	// Reads the info from a package created with CreatePackage(BYTE Type,CString stxt);
	BOOL GetPackageInfo(BYTE &Type,UINT &nData, CString &stxt);
	// returns A pointer to the Buffer 
	PBYTE GetBuffer();
	CIOCPBuffer();
	virtual ~CIOCPBuffer();
	
private:
	int m_iSequenceNumber;
	// The Type of Operation. 
    int		m_Operation;
	// Size of the Buffer 
	//UINT	m_nSize;
	// number of bytes that are Used. 
	UINT    m_nUsed;
	// The buffer. 
	BYTE m_Buffer[MAXIMUMPACKAGESIZE];
	//Holds the Buffer Used for send/receive
	WSABUF m_wsabuf;
	// Used to remove the buffer from the queue. 
	POSITION m_pPos;
};

#endif // !defined(AFX_IOCPBUFFER_H__87DEF694_32D6_4F21_8FF5_E16184A9CDC3__INCLUDED_)
