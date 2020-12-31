// imgobj.inl : 
//
/////////////////////////////////////////////////////////////////////////////

inline CImageObject::CImageObject() : CImage()
{
}

inline CImageObject::CImageObject(HBITMAP handle, int BPP /*= -1*/) : CImage(handle, BPP)
{
}

inline BOOL CImageObject::Read(CStdioFile* pFile)
{
   return CImage::Read(pFile->m_pStream, GetType(pFile)); 
}

inline BOOL CImageObject::Write(CStdioFile* pFile)
{ 
   return CImage::Write(pFile->m_pStream, GetType(pFile)); 
}

inline BOOL CImageObject::MakeBitmap(CBitmap* bitmap)
{ 
   return bitmap->Attach(CImage::MakeBitmap()); 
}

inline CString CImageObject::GetFilePath() const
{ 
   return m_strFileName; 
}

inline BOOL CImageObject::Draw(CDC* pDC, int xDst, int yDst, int cxDst, int cyDst, 
                                         int xSrc, int ySrc, int cxSrc, int cySrc)
{
   return CImage::Draw(pDC->GetSafeHdc(), xDst, yDst, cxDst, cyDst, xSrc, ySrc, cxSrc, cySrc);
}

inline BOOL CImageObject::Draw(CDC* pDC, const POINT& pt)
{
   return CImage::Draw(pDC->GetSafeHdc(), pt);
}

inline BOOL  CImageObject::Draw(CDC* pDC, const RECT& dst)
{
   return CImage::Draw(pDC->GetSafeHdc(), dst);
}

inline BOOL  CImageObject::Draw(CDC* pDC, const RECT& dst, const RECT& src)
{
   return CImage::Draw(pDC->GetSafeHdc(), dst, src);
}

/////////////////////////////////////////////////////////////////////////////
