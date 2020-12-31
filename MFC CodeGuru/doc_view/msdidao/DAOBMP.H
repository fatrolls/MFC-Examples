// DaoBmp.h : header file
//

// this class is only to read bitmap, not to write it !

/////////////////////////////////////////////////////////////////////////////
// CDaoBitmap long binary

#pragma pack(1)
typedef struct tagPOINT16 // for short point
{
  unsigned short x;
  unsigned short y;
} POINT16;

typedef struct tagOBJECTHEADER
{
  WORD    Signature;	// Type signature (0x1c15)
  WORD    HeaderSize;   // Size of header (sizeof(struct OBJECTHEADER) + cchName + cchClass)
  LONG    ObjectType;   // OLE Object type code (OT_STATIC, OT_LINKED, OT_EMBEDDED)
  WORD    NameLen;	// Count of characters in object name (CchSz(szName) + 1)
  WORD    ClassLen;	// Count of characters in class name (CchSz(szClass) + 1)
  WORD    NameOffset;   // Offset of object name in structure (sizeof(OBJECTHEADER))
  WORD    ClassOffset;  // Offset of class name in structure (ibName + cchName)
  POINT16 ObjectSize;   // Original size of object (see code below for value)
  //BYTE  OleInfo[];	// Name and Class of object, stored as "Name\0Class\0"
} OBJECTHEADER;

typedef struct tagOLEHEADER
{
  LONG Version;		// 0x00000501
  LONG Format;
  LONG Len;		// Length of OleInfo[]
  //BYTE OleInfo[];	// Format name "PBrush\0"
} OLEHEADER;

typedef struct tagDIBOBJECTINFO
{
  BYTE BitMap[2];     // 'BM' signature
  LONG Size;	      // size of DIBOBJECTINFO + BITMAPINFO + BitmapData
  LONG val2;	      // ?
  LONG val3;	      // size of DIBOBJECTINFO + BITMAPINFO
} DIBOBJECTINFO;

#pragma pack()

#define CHECKSUM_SIGNATURE 0xFE05AD00L

/////////////////////////////////////////////////////////////////////////////
// the longbinary contains
//
// OBJECTHEADER+OleInfo[]
//
// OLEHEADER+OleInfo[]
//
// Buffer[?] until "BM"
//
// DIBOBJECTINFO
//
// BITMAPINFO
//
// BitmapData
//
// DWORD CheckSum

class CDaoBitmap : public CLongBinary
{
private:
  BYTE		*m_pData;
public:
   CDaoBitmap();
  ~CDaoBitmap();

  // attributes
  OBJECTHEADER	*m_pObject;
  BYTE		*m_pName;
  BYTE		*m_pClass;

  OLEHEADER	*m_pOleHeader;
  BYTE		*m_pOleInfo;

  DIBOBJECTINFO	*m_pDib;
  BITMAPINFO	*m_pBmInfo;
  DWORD		m_CheckSum;

  HBITMAP	m_hBitmap;

  // operations
  BOOL		Init();
  BOOL		Lock();
  void		Unlock();
  HANDLE	CopyToClipboard(HWND hWnd);
  CBitmap	*GetBitmap(CDC *pDC);
  DWORD		Width();
  DWORD		Height();
};
