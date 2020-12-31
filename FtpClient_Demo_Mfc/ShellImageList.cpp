
#include "stdafx.h"
#include "ShellImageList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CShellImageList::CShellImageList(const bool fSmall, const bool fLarge) :
   m_pSmall(NULL),
   m_pLarge(NULL)
{
   ASSERT( fSmall || fLarge );

   if( fSmall )
      m_pSmall = new CImageList();

   if( fLarge )
      m_pLarge = new CImageList();

   CreateImageList();
}

CShellImageList::~CShellImageList()
{
   delete m_pSmall;
   delete m_pLarge;
   m_pSmall = NULL;
   m_pLarge = NULL;
}

void CShellImageList::CreateImageList()
{
   if( m_pSmall )
   {
      m_pSmall->DeleteImageList();

      m_pSmall->Create(16, 16, ILC_MASK|ILC_COLOR32, 5, 32);
      m_pSmall->SetBkColor(CLR_NONE);
   }
 
   if( m_pLarge )
   {
      m_pLarge->DeleteImageList();

      m_pLarge->Create(32, 32, ILC_MASK|ILC_COLOR32, 5, 32);
      m_pLarge->SetBkColor(CLR_NONE);
   }

   m_mapExt2Index.RemoveAll();
}

void CShellImageList::GetExtIcon(const CString& szExtension, CShellImageList::CILIcon& ilIcon)
{
   SHFILEINFO shInfo;

   DWORD dwFlag = SHGFI_USEFILEATTRIBUTES|SHGFI_ICON;

   ZeroMemory(&shInfo, sizeof(shInfo));
   SHGetFileInfo(szExtension, FILE_ATTRIBUTE_NORMAL, &shInfo, sizeof(shInfo), dwFlag|SHGFI_SMALLICON);

   VERIFY( shInfo.hIcon!=NULL );
   ilIcon.SetSmallIcon(shInfo.hIcon);

   ZeroMemory(&shInfo, sizeof(shInfo));
   SHGetFileInfo(szExtension, FILE_ATTRIBUTE_NORMAL, &shInfo, sizeof(shInfo), dwFlag|SHGFI_LARGEICON);

   VERIFY( shInfo.hIcon!=NULL );
   ilIcon.SetLargeIcon(shInfo.hIcon);
}

CShellImageList::CILIndex CShellImageList::AddIcon(const CILIcon& ilIcon, const CString& cszExtension)
{  
   CILIndex ilIndex;
   
   if( m_pSmall )
      ilIndex.SetSmallIndex(m_pSmall->Add(ilIcon.GetSmallIcon()));

   if( m_pLarge )
      ilIndex.SetLargeIndex(m_pLarge->Add(ilIcon.GetLargeIcon()));

   m_mapExt2Index.SetAt(cszExtension, ilIndex);

   return ilIndex;
}

CShellImageList::CILIndex CShellImageList::AddIcon(const CString& cszExtension, const UINT iSmallBitmap, const UINT iLargeBitmap)
{
   CILIndex ilIndex;

   if( iSmallBitmap )
      ilIndex.SetSmallIndex(AddBitmapToImageList(iSmallBitmap, true));
   if( iLargeBitmap )
      ilIndex.SetLargeIndex(AddBitmapToImageList(iLargeBitmap, false));

   m_mapExt2Index.SetAt(cszExtension, ilIndex);

   return ilIndex;
}

int CShellImageList::GetImageForExtension(const CString& cszExtension, const bool fSmall/*=true*/)
{
   CILIndex ilIndex;
   if( !m_mapExt2Index.Lookup(cszExtension, ilIndex) )
   {
      CILIcon  ilIcon;
      GetExtIcon(cszExtension, ilIcon);
      ilIndex = AddIcon(ilIcon, cszExtension);
   }
   
   if( fSmall )
      return ilIndex.GetSmallIndex();
   else
      return ilIndex.GetLargeIndex();
}

int CShellImageList::GetFolderIcon(const bool fOpenIcon, const bool fSmall/*=true*/)
{
   CILIndex ilIndex;
   if( !m_mapExt2Index.Lookup(_T(":\\FOLDER\\:"), ilIndex) )
   {
      DWORD dwFlags = SHGFI_USEFILEATTRIBUTES|SHGFI_DISPLAYNAME|SHGFI_TYPENAME|SHGFI_ICON;

      if( fOpenIcon )
         dwFlags |= SHGFI_OPENICON;
   
      SHFILEINFO shInfo;

      if( m_pSmall )
      {
         ZeroMemory(&shInfo, sizeof(shInfo));
         SHGetFileInfo(NULL, FILE_ATTRIBUTE_DIRECTORY, &shInfo, sizeof(SHFILEINFO), dwFlags|SHGFI_SMALLICON);
         ilIndex.SetSmallIndex(m_pSmall->Add(shInfo.hIcon));
      }

      if( m_pLarge )
      {
         ZeroMemory(&shInfo, sizeof(shInfo));
         SHGetFileInfo(NULL, FILE_ATTRIBUTE_DIRECTORY, &shInfo, sizeof(shInfo), dwFlags|SHGFI_LARGEICON);
         ilIndex.SetLargeIndex(m_pLarge->Add(shInfo.hIcon));
      }

      m_mapExt2Index.SetAt(_T(":\\FOLDER\\:"), ilIndex);
   }

   if( fSmall )
      return ilIndex.GetSmallIndex();
   else
      return ilIndex.GetLargeIndex();
}

int CShellImageList::AddBitmapToImageList(const UINT iBitmap, const bool fSmall)
{
   CBitmap  bitmap;
   int      iIndex=-1;

   if( bitmap.LoadBitmap(iBitmap) )
   {
      if( fSmall && m_pSmall )
         iIndex = m_pSmall->Add(&bitmap, RGB(255,255,255));
      else if( !fSmall && m_pLarge )
         iIndex = m_pLarge->Add(&bitmap, RGB(255,255,255));
      bitmap.DeleteObject();
   }

   return iIndex;
}
