
#ifndef _INC_SHELLIMAGELIST_H
#define _INC_SHELLIMAGELIST_H

#pragma once

#include <afxtempl.h>

class CShellImageList
{
public:
   class CILIndex
   {
   public:
      CILIndex() : m_iSmallIndex(-1), m_iLargeIndex(-1) {};

      void SetSmallIndex(const int iSmallIndex) { m_iSmallIndex = iSmallIndex; };
      void SetLargeIndex(const int iLargeIndex) { m_iLargeIndex = iLargeIndex; };

      int GetSmallIndex() const { return m_iSmallIndex; };
      int GetLargeIndex() const { return m_iLargeIndex; };

   private:
      int m_iSmallIndex;
      int m_iLargeIndex;
   };

private:
   class CILIcon
   {
   public:
      CILIcon() : m_hLarge(NULL), m_hSmall(NULL) {};

      void SetLargeIcon(const HICON hLarge) { m_hLarge = hLarge; };
      void SetSmallIcon(const HICON hSmall) { m_hSmall = hSmall; };

      HICON GetLargeIcon() const { return m_hLarge; };
      HICON GetSmallIcon() const { return m_hSmall; };

   private:
      HICON    m_hLarge;
      HICON    m_hSmall;
   };

public:
   CShellImageList(const bool fSmall, const bool fLarge);
   virtual  ~CShellImageList();

public:
   int GetImageForExtension(const CString& cszExtension, const bool fSmall=true);
   int GetFolderIcon(const bool fOpenIcon=false, const bool fSmall=true);
   CILIndex AddIcon(const CString& cszExtension, const UINT iSmallBitmap, const UINT iLargeBitmap);
   CImageList* GetSmallImageList() { return m_pSmall; };
   CImageList* GetLargeImageList() { return m_pLarge; };

private:
   void CreateImageList(); 
   int AddBitmapToImageList(const UINT iBitmap, const bool fSmall);
   void GetExtIcon(const CString& szExtension, CILIcon& ilIcon);
   CILIndex AddIcon(const CILIcon& ilIcon, const CString& cszExtension);

private:
   CImageList* m_pSmall;   ///< Imagelist for small icons
   CImageList* m_pLarge;   ///< Imagelist for large icons

   CMap<CString, LPCTSTR, CILIndex, CILIndex> m_mapExt2Index;
};

#endif // _INC_SHELLIMAGELIST_H
