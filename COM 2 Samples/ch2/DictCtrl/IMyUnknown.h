#ifndef __IMyUnknown_H__
#define __IMyUnknown_H__

typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef int BOOL;

typedef struct _GUID GUID; 

typedef GUID IID;

extern "C" const IID IID_IUnknown = 
		{ 0x00000000, 0x0000, 0x0000,
		{ 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} } ;

class IMyUnknown 
{
public:
	virtual HRESULT	__stdcall  QueryInterface(const IID& iid, void **ppv) = 0 ;
	virtual ULONG	__stdcall  AddRef() = 0; 
	virtual ULONG	__stdcall  Release() = 0;
};

#endif // __IMyUnknown_H__
