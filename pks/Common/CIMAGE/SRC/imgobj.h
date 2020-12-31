// imgobj.h : interface of the CImageObject class
// (c) Troels K.
// MFC wrapper for CImage
// - brings CImage in line with MFC by bringing in CObject
// - utilize CArchive

#ifndef __IMGOBJ_H__
#define __IMGOBJ_H__

#include "..\..\cimage\include\cimage.h"

/////////////////////////////////////////////////////////////////////////////
// CImageObject

class CImageObject : public CImage, public CObject
{
protected:
	CString m_strFileName;
public:
   CImageObject();
   CImageObject(HBITMAP, int BPP = -1);

// Implementation
public:
   virtual void Serialize(CArchive&);
   virtual void Close(void);

// Operations
public:
   BOOL CreateFromFile(LPCTSTR filename);
	BOOL Save(LPCTSTR filename);
	BOOL Read(CStdioFile*);
   BOOL Write(CStdioFile*);
   BOOL MakeBitmap(CBitmap*);
   CString GetFilePath() const;
   static enum cximage_type GetType(LPCTSTR filename);
   static enum cximage_type GetType(const CFile*);

	BOOL Draw(CDC*, int xDst = 0, int yDst = 0, int cxDst = -1, int cyDst = -1, 
                   int xSrc = 0, int ySrc = 0, int cxSrc = -1, int cySrc = -1);
   BOOL Draw(CDC*, const POINT&);
   BOOL Draw(CDC*, const RECT&);
   BOOL Draw(CDC*, const RECT& dst, const RECT& src);
};

#include "imgobj.inl"

/////////////////////////////////////////////////////////////////////////////

#endif // __IMGOBJ_H__
