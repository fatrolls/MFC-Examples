// imgobj.cpp : implementation of the CImageDoc class
//

#include "stdafx.h"
#include "helpers.h"
#include "imgobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static const char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageObject

void CImageObject::Close(void)
{
   CImage::Close();
   m_strFileName.Empty();
}

/*static*/ enum cximage_type CImageObject::GetType(LPCTSTR filename)
{
   static const struct tagMAP
   {
      enum { ENUM_count = 2 };
      LPCTSTR ext[ENUM_count];
   } aMap[] =
   {
      { _T(".bmp" ), NULL },
      { _T(".gif" ), NULL },
      { _T(".jpg" ), _T(".jpeg") },
      { _T(".png" ), NULL },
      { _T(".ico" ), NULL },
      { _T(".tiff"), _T(".tif") },
   };
   C_ASSERT(ENUM_cimage_format_enumcount == _countof(aMap));

   TCHAR ext[_MAX_PATH];
   enum cximage_type type = ENUM_cimage_format_empty;

   C_ASSERT(ENUM_cimage_format_enumcount == _countof(aMap));
   _tsplitpath(filename, NULL, NULL, NULL, ext);
   for (int i = 0; (i < _countof(aMap)) && (ENUM_cimage_format_empty == type); i++)
   {
      for (int j = 0; (j < tagMAP::ENUM_count) && (ENUM_cimage_format_empty == type); j++)
      {
         if ( (aMap[i].ext[j] != NULL) && (0 == lstrcmpi(aMap[i].ext[j], ext)) )
         {
            type = (enum cximage_type)i;
         }
      }
   }
   return type;
}

/*static*/ enum cximage_type CImageObject::GetType(const CFile* pFile)
{
   return CImageObject::GetType(pFile->GetFilePath());
}

BOOL CImageObject::CreateFromFile(LPCTSTR filename)
{
   BOOL bOK = CImage::CreateFromFile(filename, GetType(filename));
   if (bOK)
   {
      m_strFileName = filename;
   }
   return bOK;
}

BOOL CImageObject::Save(LPCTSTR filename)
{
   enum cximage_type type = GetType(filename);
   BOOL bOK = (type != ENUM_cimage_format_empty);
   if (bOK)
   {
      LPTSTR temp = _ttempnam(GetTempPath(), _T("img"));
      if (temp != NULL)
      {
         bOK = CImage::Save(temp, type);
         if (bOK)
         {
            bOK = MoveFile(temp, filename, TRUE);
         }
         if (!bOK)
         {
            _tunlink(temp);
         }
         free(temp);
      }
      else
      {
         bOK = CImage::Save(filename, type);
      }
   }
   if (bOK)
   {
      m_strFileName = filename;
   }
   return bOK;
}

void CImageObject::Serialize(CArchive& ar)
{
   BOOL bOK;
   CStdioFile* pFile = (CStdioFile*)ar.GetFile();
	ASSERT_KINDOF(CStdioFile, pFile);

   if (ar.IsStoring())	
   {	
      bOK = Write(pFile);
   } 
	else 
   {	
      bOK = Read(pFile);
      if (bOK)
      {
         bOK = ((GetWidth() > 0) && (GetHeight() > 0));
         if(0)if (ENUM_cimage_format_bmp == GetFileType())
         {
            SetBkColor(RGB(0x00,0x80, 0x80));
         }
      }
		//AfxMessageBox(CString(m_image.GetLastError()));
   }
   if (!bOK)
   {
		AfxThrowArchiveException(CArchiveException::generic);
   }
}

/////////////////////////////////////////////////////////////////////////////
