// DIBManagerDoc.cpp : implementation of the CDIBManagerDoc class
//

#include "stdafx.h"
#include "DIBManager.h"

#include "DIBManagerDoc.h"

#include "MainFrm.h"
#include "DIBManagerView.h"
#include "ChildFrm.h"

#include "ProtectedFile.h"

#include "path.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerDoc

IMPLEMENT_DYNCREATE(CDIBManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CDIBManagerDoc, CDocument)
	//{{AFX_MSG_MAP(CDIBManagerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerDoc construction/destruction

CDIBManagerDoc::CDIBManagerDoc()
{
	// TODO: add one-time construction code here
	m_nDIBNumPage=0;
	m_nXPage=0;
	m_nYPage=0;
}

CDIBManagerDoc::~CDIBManagerDoc()
{
}

BOOL CDIBManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDIBManagerDoc serialization

void CDIBManagerDoc::Serialize(CArchive& ar)
{
	// use built-in functions to save/load DIB file to/from
	// CFile which is associated with CArchive ar
	ar.Flush();
	if(ar.IsStoring())
	{
		m_dib.Write(ar.GetFile());
	}
	else
	{
		m_dib.Read(ar.GetFile());
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerDoc diagnostics

#ifdef _DEBUG
void CDIBManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDIBManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerDoc commands

BOOL CDIBManagerDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL bSuccess=FALSE;

	// try to open or create file  
	CFile m_file;
	TRY
	{
		bSuccess=m_file.Open(lpszPathName,CFile::modeCreate|CFile::modeReadWrite);
	}
	CATCH(CFileException,e)
	{
		TCHAR szCause[255];
        CString strFormatted;
        e->GetErrorMessage(szCause, 255);
        strFormatted = _T("CDIBManagerDoc::OnSaveDocument:exception: ");
        strFormatted += szCause;
        TRACE(strFormatted);
	}
	END_CATCH

	if(!bSuccess)
	{
		AfxMessageBox(_T("Cannot open or create specified file!"),
			MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	if(m_bProtected)
	{
		// if image is protected
		// then try to save image using object of CProtectedFile class
		TRY
		{
			CArchive ar(&m_file, CArchive::store);
			bSuccess=m_dib.Write(ar);
			ar.Close();
			if(!bSuccess)
			{
				AfxMessageBox(_T("Cannot save image!"),MB_OK|MB_ICONEXCLAMATION);
				return FALSE;
			}

			CProtectedFile m_protectedFile;
			bSuccess=m_protectedFile.Save(&m_file);
		}
		CATCH(CFileException,e)
		{
			if(e->m_cause==CFileException::accessDenied)
			{
				e->Delete();
			}
		}
		END_CATCH
	}
	else
	{
		// just save DIB file
		CArchive ar(&m_file, CArchive::store);
		bSuccess=m_dib.Write(ar);
		ar.Close();
	}
	// to get the length of file
	// we have to flush it
	m_file.Flush();
	if(bSuccess)
	{
		// in a case of protection the length of DIB file could change
		// then recalculate it
		COXPathSpec path;
		path.SetPath(lpszPathName);
		path.DoGetInfo();
		m_dwImageSize=path.GetLength();
		m_bInitiallyProtected=m_bProtected;
		m_tf=TF_DIB;
		SetModifiedFlag(FALSE);
	}
	return bSuccess;
}

BOOL CDIBManagerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized creation code here

	return OpenDocument(lpszPathName);
}

BOOL CDIBManagerDoc::OpenDocument(LPCTSTR lpszPathName, TypeFile tf) 
{
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();

	// try to open file on read
	CFile m_file;
	BOOL bSuccess=FALSE;
	TRY
	{
		bSuccess=m_file.Open(lpszPathName,CFile::modeRead);
	}
	CATCH(CFileException, e)
	{
		TCHAR szCause[255];
        CString strFormatted;
        e->GetErrorMessage(szCause, 255);
        strFormatted = _T("CDIBManagerDoc::OpenDocument:exception: ");
        strFormatted += szCause;
        TRACE(strFormatted);

		bSuccess=FALSE;
	}
	END_CATCH

	if(!bSuccess)
	{
		// notify system about error
		// if error happens during loading of system
		// then ErrorNotify() will hide splash window if it is active
		pApp->ErrorNotify(_T("Cannot open file!"));
		return FALSE;
	}

	return OpenDocument(&m_file,CString(lpszPathName),tf);
}

BOOL CDIBManagerDoc::OpenDocument(CFile* m_pFile, CString sFileName, TypeFile tf) 
{
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();

	m_bProtected=FALSE;
	m_bInitiallyProtected=FALSE;

	m_pFile->SeekToBegin();
	// just try to read DIB file
	if(!m_dib.Read(m_pFile))
	{
		// if error happened then suggest that we have to open 
		// protected image
		TRY
		{
			m_pFile->SeekToBegin();
			CProtectedFile m_protectedFile;
			CMemFile tmpFile;
			if(!m_protectedFile.CopyFile(&tmpFile,m_pFile))
				return FALSE;
			if(!m_protectedFile.Open(&tmpFile))
				return FALSE;

			m_bProtected=TRUE;
			m_bInitiallyProtected=TRUE;

			tmpFile.SeekToBegin();
			// try to read DIB file by means of object of CProtectedFile class
			if(!m_dib.Read(&tmpFile))
			{
				// if error happened then assume that file is not of DIB format
				AfxThrowFileException(CFileException::badPath);
			}
		}
		CATCH(CFileException,e)
		{
			if(e->m_cause==CFileException::badPath)
			{
				pApp->ErrorNotify(_T("Unknown file format!"));
			}
			return FALSE;
		}
		END_CATCH
	}

	m_sNameFile=sFileName;
	m_tf=tf;

	COXPathSpec path;
	path.SetPath(m_sNameFile);
	path.DoGetInfo();
	m_dwImageSize=path.GetLength();

	m_dibDither=NULL;
	// if current video color palette is no more than 256 colors and
	// DIB file uses no les than 256 color then create dithered copy
	// of the file to render it on the display (this way we will get
	// better output quality)
	if(CheckUseDithered())
	{
		m_dibDither=m_dib;
		m_dibDither.HalfToneDitherDIB();
	}
	
	return TRUE;
}

BOOL CDIBManagerDoc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// we can save only files of DIB format
	if(m_tf!=TF_DIB)
	{
		SetModifiedFlag(FALSE);
	}

	return CDocument::SaveModified();
}

CPalette* CDIBManagerDoc::GetDIBPalette() 
{
	// depending on the current color palette 
	// return original palette or palette of dithered file
	if(!CheckUseDithered())
	{
		return m_dib.GetPalette();
	}
	else
	{
		return m_dibDither.GetPalette();
	}
}

CSize CDIBManagerDoc::GetDIBSize() 
{

	// depending on the current color palette 
	// return original size or size of dithered file
	if(!CheckUseDithered())
	{
		return m_dib.GetSize();
	}
	else
	{
		return m_dibDither.GetSize();
	}
}

UINT CDIBManagerDoc::CalcDIBNumPage(CDIBManagerView* pView, CDC* pDC) 
{
	// convert logical boundaries of image to corresponding boundaries 
	// for printer taking into account current zoom level
	
	CSize sizeDIB=GetDIBSize();
	CRect rect(0,0,sizeDIB.cx,sizeDIB.cy);
	pView->NormalToScaled(&rect);
	pView->NormalToPrinted(pDC,&rect);

	// calculate the number of page based on the size of print page
	int xPrinterRes=pDC->GetDeviceCaps(HORZRES);
	int yPrinterRes=pDC->GetDeviceCaps(VERTRES);

    m_nXPage=rect.Width()/xPrinterRes;
	if(rect.Width()%xPrinterRes!=0)
	{
		m_nXPage++;
	}
	m_nYPage=rect.Height()/yPrinterRes;
	if(rect.Height()%yPrinterRes!=0)
	{
		m_nYPage++;
	}

	// all pages
    m_nDIBNumPage=m_nXPage*m_nYPage;

    return m_nDIBNumPage;
}

// we would better have such function in COXDIB class
DWORD CDIBManagerDoc::CalcDIBSizeInMemory() 
{
	LPBITMAPINFOHEADER lpBI;   // Pointer to DIB info structure
	DWORD dwDIBSizeInMemory;

	HDIB hDIB=m_dib.MakeCopy();
	if (hDIB==NULL)
	{
		TRACE0("CDIBManagerDoc::CalcDIBSizeInMemory: cannot make copy of DIB handle\n");
		return (DWORD)0;
	}
	 // Get a pointer to the DIB memory, the first of which contains
	 // a BITMAPINFO structure
	lpBI = (LPBITMAPINFOHEADER)::GlobalLock((HGLOBAL) hDIB);
	if (lpBI == NULL)
	{
		TRACE0("CDIBManagerDoc::CalcDIBSizeInMemory: Out of memory\n");
		::GlobalFree((HGLOBAL)hDIB);
		return (DWORD)0;
	}

	// Calculating the size of the DIB is a bit tricky (if we want to
	// do it right).  The easiest way to do this is to call GlobalSize()
	// on our global handle, but since the size of our global memory may have
	// been padded a few bytes, we may end up writing out a few too
	// many bytes to the file (which may cause problems with some apps).
	//
	// So, instead let's calculate the size manually (if we can)
	//
	// First, find size of header plus size of color table.  Since the
	// first DWORD in both BITMAPINFOHEADER and BITMAPCOREHEADER conains
	// the size of the structure, let's use this.

	// Partial Calculation
	dwDIBSizeInMemory=*(LPDWORD)lpBI+m_dib.GetPaletteSize((LPSTR)lpBI);  

	// Now calculate the size of the image
	if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
	{
		// It's an RLE bitmap, we can't calculate size, so trust the
		// biSizeImage field

		dwDIBSizeInMemory+=lpBI->biSizeImage;
	}
	else
	{
		DWORD dwBmBitsSize;  // Size of Bitmap Bits only

		// It's not RLE, so size is Width (DWORD aligned) * Height

		dwBmBitsSize=WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount))*
			lpBI->biHeight;

		dwDIBSizeInMemory+=dwBmBitsSize;
	}

	// Calculate the file size by adding the DIB size to sizeof(BITMAPFILEHEADER)
	dwDIBSizeInMemory+=sizeof(BITMAPFILEHEADER);

	::GlobalUnlock((HGLOBAL)hDIB);
	::GlobalFree((HGLOBAL)hDIB);

	return dwDIBSizeInMemory;
}

BOOL CDIBManagerDoc::CheckUseDithered()
{
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();

	// if current video color palette is no more than 256 colors and
	// DIB file uses no les than 256 color then create dithered copy
	// of the file to render it on the display (this way we will get
	// better output quality)
	return (pApp->m_nColors<=8 && (m_dib.GetNumColors()==0 || m_dib.GetNumColors()==256));
}

