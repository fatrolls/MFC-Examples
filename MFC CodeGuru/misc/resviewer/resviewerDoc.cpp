// resviewerDoc.cpp : implementation of the CResviewerDoc class
//

#include "stdafx.h"
#include "resviewer.h"
#include "resviewerDoc.h"
#include "dlgdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResviewerDoc

IMPLEMENT_DYNCREATE(CResviewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CResviewerDoc, CDocument)
	//{{AFX_MSG_MAP(CResviewerDoc)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResviewerDoc construction/destruction

CResviewerDoc::CResviewerDoc()
{
	// TODO: add one-time construction code here
	m_PeResource = NULL;
	m_currentresID = 0;
	m_currentresType = 0;

}

CResviewerDoc::~CResviewerDoc()
{
	if (m_PeResource)
	{
		delete m_PeResource;
		m_PeResource = NULL;
	}
}

BOOL CResviewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CResviewerDoc serialization

void CResviewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CResviewerDoc diagnostics

#ifdef _DEBUG
void CResviewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CResviewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResviewerDoc commands

BOOL CResviewerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// 
	// when the document is opened get the file name 
	// and create the resource table

	// TODO: Add your specialized creation code here
	m_PeResource = new PERsrcTbl(lpszPathName);
	//UpdateAllViews(
	return TRUE;
}

PERsrcTbl* CResviewerDoc::GetPERsrc()
{
	return m_PeResource;

}

void CResviewerDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_PeResource)
	{
		delete m_PeResource;
		m_PeResource = NULL;
		UpdateAllViews(FALSE);
	}
	CDocument::DeleteContents();
}

BOOL CResviewerDoc::RouteCmdToAllViews (CView* pView, UINT nID, int nCode,
    void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	//
	// ensure all views are receiving messages when idle.
	//

    POSITION pos = GetFirstViewPosition ();

    while (pos != NULL) {
        CView* pNextView = GetNextView (pos);
        if (pNextView != pView) {
            // Cast CView upward to CCmdTarget because OnCmdMsg is
            // erroneously declared protected in CView
            if (((CCmdTarget*) pNextView)->OnCmdMsg (nID, nCode,
                pExtra, pHandlerInfo))
                return TRUE;
        }
    }
    return FALSE;
}


void CResviewerDoc::OnFileSaveAs() 
{

	//
	// on file save, ensure our file type are in the dialog
	// then depending on the type of resource being saved
	// call the appropriate function to save it.
	//

	const CHAR filedialogFilter[] = 
	"Dialogs (*.dlg)|*.dlg|Bitmaps (*.bmp)|*.bmp|Icons (.ico)|*.ico||";
	
	if (m_currentresType == 0)
	{
		AfxMessageBox("Please Select an Item");
		return;
	}

	
	

	// file save as dlg
	CHAR szID [256];
	CHAR szDfltFile[10];


	if (m_currentresID == 0)
		strcpy(szID,m_currentresName);
	else
		itoa(m_currentresID,szID,10);

	if (m_currentresType == (WORD)RT_ICON)
		strcpy(szDfltFile,"ico");
	else
	if (m_currentresType == (WORD)RT_BITMAP)
		strcpy(szDfltFile,"bmp");
	else
	if (m_currentresType == (WORD)RT_DIALOG)
		strcpy(szDfltFile,"dlg");
		
		
	CFileDialog filedialog(FALSE,
							szDfltFile,
							szID,
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							filedialogFilter);
						
	if (filedialog.DoModal() != IDOK)
	{
		return;
	}

	

	PERsrcTbl* RsrcTbl = GetPERsrc();
	
	if (!RsrcTbl)
	{
		return;
	}



	PERsrcType *RsrcType = 
		RsrcTbl->GetResourceTypeById((WORD)m_currentresType);
	if (!RsrcType)
	{
		return;
	}

	PERsrcInst *RsrcInst;

	
	if (m_currentresID)  // got resource ID number?
	{
		RsrcInst = 
			RsrcType->GetResourceInstById((WORD)m_currentresID);
		if (!RsrcInst)
		{
			return;
		}
	}
	else  // got resource name instead
	{
		RsrcInst = 
			RsrcType->GetResourceInstByName(m_currentresName);
		if (!RsrcInst)
		{
			return;
		}
	}


	


	if (m_currentresType == (WORD)RT_BITMAP)
	{

		CreateBMPFile(filedialog.GetPathName(),
					(LPBITMAPINFOHEADER)RsrcInst->GetData());

						
	}
	
	if (m_currentresType == (WORD)RT_ICON)
	{

		CreateICOFile(filedialog.GetPathName(),
					(LPBITMAPINFOHEADER)RsrcInst->GetData(),
					RsrcInst->Size());

						
	}

	if (m_currentresType == (WORD)RT_CURSOR)
	{

		CreateCURFile(filedialog.GetPathName(),
					(LPBITMAPINFOHEADER)RsrcInst->GetData(),
					RsrcInst->Size());

						
	}

	if (m_currentresType == (WORD)RT_DIALOG)
	{

		CreateDLGFile(filedialog.GetPathName(),
					(LPBITMAPINFOHEADER)RsrcInst->GetData(),
					RsrcInst->Size());

						
	}


	delete RsrcType;
	delete RsrcInst;


	
}

void CResviewerDoc::SetCurrentItem(LPRESINFO lpRes)
{
	//
	// set by the tree control who calls this function
	//
	//

	m_currentresType = lpRes->riType;
    m_currentresID = lpRes->riIDNum;
	if (m_currentresID == 0)
	{
		strcpy(m_currentresName,lpRes->riIDName);
	}

}


BOOL CResviewerDoc::CreateBMPFile(LPCTSTR pszFile, LPBITMAPINFOHEADER pbih)
{
	HANDLE hf;                  /* file handle */ 
    BITMAPFILEHEADER hdr;       /* bitmap file-header */ 
    //PBITMAPINFOHEADER pbih;     /* bitmap info-header */ 
    LPBYTE lpBits;              /* memory pointer */ 
    DWORD dwTotal;              /* total count of bytes */ 
    DWORD cb;                   /* incremental count of bytes */ 
    BYTE *hp;                   /* byte pointer */ 
    DWORD dwTmp; 
	DWORD MAXWRITE = 65535; 
	INT iNumColors;

    //pbih =  pbi; 


	
	if (pbih->biBitCount <= 8)
		iNumColors = (1 << pbih->biBitCount);
	else
		iNumColors = 0;

	
	lpBits = (LPBYTE)pbih +  pbih->biSize + 
							 (iNumColors * sizeof(RGBQUAD));
    
    
    
    /* Create the .BMP file. */ 
 
    hf = CreateFile(pszFile, 
                   GENERIC_READ | GENERIC_WRITE, 
                   (DWORD) 0, 
                   (LPSECURITY_ATTRIBUTES) NULL, 
                   CREATE_ALWAYS, 
                   FILE_ATTRIBUTE_NORMAL, 
                   (HANDLE) NULL); 
 
    if (hf == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("Error Creating File"); 
		 return FALSE;
        
	}
 
    hdr.bfType = 0x4d42;        /* 0x42 = "B" 0x4d = "M" */ 
 
    /* Compute the size of the entire file. */ 
 
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
                 pbih->biSize + iNumColors 
                 * sizeof(RGBQUAD) + pbih->biSizeImage); 
 
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 
 
    /* Compute the offset to the array of color indices. */ 
 
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
                    pbih->biSize + iNumColors
                    * sizeof (RGBQUAD); 
 
    /* Copy the BITMAPFILEHEADER into the .BMP file. */ 
 
    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
       (LPDWORD) &dwTmp, (LPOVERLAPPED) NULL)) 
	   {
			AfxMessageBox("Error Writing File"); 
			return FALSE;
			
	   }
 
    /* Copy the BITMAPINFOHEADER and RGBQUAD array into the file. */ 
 
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
                  + iNumColors * sizeof (RGBQUAD), 
                  (LPDWORD) &dwTmp, (LPOVERLAPPED) NULL)) 

	{
		AfxMessageBox("Error Writing File"); 
		return FALSE;

    }
	   
 
    /* Copy the array of color indices into the .BMP file. */ 
 
    dwTotal = cb = pbih->biSizeImage; 
    hp = lpBits; 
    while (cb > MAXWRITE)  { 
            if (!WriteFile(hf, (LPSTR) hp, (int) MAXWRITE, 
                          (LPDWORD) &dwTmp, (LPOVERLAPPED) NULL)) 
			{
				AfxMessageBox("Error Writing File"); 
				return FALSE;

                
			}
            cb-= MAXWRITE; 
            hp += MAXWRITE; 
    } 
    if (!WriteFile(hf, (LPSTR) hp, (int) cb, 
         (LPDWORD) &dwTmp, (LPOVERLAPPED) NULL)) 
	{
		AfxMessageBox("Error Writing File"); 
		return FALSE;
         
	}
 
    /* Close the .BMP file. */ 
 
    if (!CloseHandle(hf)) 
	{

           AfxMessageBox("File Close Failed"); 
		   return FALSE;
	}
 
    
	return TRUE;


}

BOOL CResviewerDoc::CreateICOFile(LPCTSTR pszFile,
								  LPBITMAPINFOHEADER pbi,
								  DWORD RsrcSize)
{
	HANDLE    	hFile;
    DWORD    	dwBytesWritten;
	LPBYTE lpBits = NULL;              /* memory pointer */ 
    DWORD cb;                   /* incremental count of bytes */ 
    BYTE *hp;                   /* byte pointer */ 
    DWORD MAXWRITE = 65535; 
	INT iNumColors;

	ICONDIR id;
	
    // open the file
    if( (hFile = CreateFile( pszFile, GENERIC_WRITE, 0,
							NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
							NULL )) == INVALID_HANDLE_VALUE )
    {
        AfxMessageBox("Error Opening ICO File");
        return FALSE;
    }

	// create the hdr part of the icondirectory
	id.idReserved = 0;
	id.idType = 1;
	id.idCount = 1;


	// Write int out to disk
    if(!WriteFile( hFile, &id,ICONDIRSIZE,
				   &dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing ICO");
		return FALSE;
	}

	    // Did we write a full hdr ?
    if( dwBytesWritten != ICONDIRSIZE)
	{
		AfxMessageBox("Error Writing ICO");
		return FALSE;
	}
        
	
    // Write the ICONDIRENTRY
    
    ICONDIRENTRY    ide;

    // Convert internal format to ICONDIRENTRY
    ide.bWidth = (BYTE)pbi->biWidth;
    ide.bHeight = (BYTE)pbi->biHeight/2;
    ide.bReserved = 0;
    ide.wPlanes = 0;

    ide.wBitCount = 0;
    if( (pbi->biPlanes * pbi->biBitCount) >= 8 )
        ide.bColorCount = 0;
    else
        ide.bColorCount = 1 << (pbi->biPlanes * pbi->biBitCount);

	iNumColors = ide.bColorCount;

    ide.dwBytesInRes = RsrcSize;
	//ide.nID = 0;
	

    ide.dwImageOffset = ICONDIRSIZE +
						sizeof(ICONDIRENTRY);
						//+
						//pbi->biSize +
						//iNumColors * sizeof (RGBQUAD);
						

    // Write the ICONDIRENTRY out to disk
    if( ! WriteFile( hFile, &ide, sizeof( ICONDIRENTRY ), &dwBytesWritten, NULL ) )
        return FALSE;

    // Did we write a full ICONDIRENTRY ?
    if( dwBytesWritten != sizeof( ICONDIRENTRY ) )
        return FALSE;
    


   
    
    /* Copy the BITMAPINFOHEADER and RGBQUAD array into the file. */ 
 
    //if (!WriteFile(hFile, (LPVOID) pbi, sizeof(BITMAPINFOHEADER) 
    //             + iNumColors * sizeof (RGBQUAD), 
    //              (LPDWORD) &dwBytesWritten, (LPOVERLAPPED) NULL)) 

	//{
	//	AfxMessageBox("Error Writing File"); 
	//	return FALSE;

    //}
	   
 
    /* Copy the array of color indices into the .BMP file. */ 
	
	

	
	//lpBits = (LPBYTE)pbi +  pbi->biSize + 
	//						 (iNumColors * sizeof(RGBQUAD));

    //DWORD dwTotal = cb = pbi->biSizeImage; 
	cb = RsrcSize;
    hp = lpBits; 
    while (cb > MAXWRITE)  
	{ 
            if (!WriteFile(hFile, 
							//(LPSTR) hp,
							(LPVOID) pbi,
							(int) MAXWRITE, 
							(LPDWORD) &dwBytesWritten,
							(LPOVERLAPPED) NULL)) 
			{
				AfxMessageBox("Error Writing File"); 
				return FALSE;

                
			}
            cb-= MAXWRITE; 
            hp += MAXWRITE; 
    } 
    if (!WriteFile(hFile,
					//(LPSTR) hp,
					(LPVOID) pbi,
					(int) cb, 
					(LPDWORD) &dwBytesWritten,
					(LPOVERLAPPED) NULL)) 
	{
		AfxMessageBox("Error Writing File"); 
		return FALSE;
         
	}

    CloseHandle( hFile );
    return FALSE;

}


BOOL CResviewerDoc::CreateCURFile(LPCTSTR pszFile, LPBITMAPINFOHEADER pbi, DWORD RsrcSize)
{
	HANDLE    	hFile;
    DWORD    	dwBytesWritten;
	LPBYTE lpBits;              /* memory pointer */ 
    DWORD cb;                   /* incremental count of bytes */ 
    BYTE *hp;                   /* byte pointer */ 
    DWORD MAXWRITE = 65535; 
	INT iNumColors;
	LPBITMAPINFOHEADER lppbi;


	ICONDIR id;
    // open the file
    if( (hFile = CreateFile( pszFile, GENERIC_WRITE, 0,
							NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
							NULL )) == INVALID_HANDLE_VALUE )
    {
        AfxMessageBox("Error Creating CUR File");
        return FALSE;
    }

	// create MEMICONFILEHDR
	id.idReserved = 0;
	id.idType = 2;   // create cursor this time
	id.idCount = 1;

	
	// Write the MEMICONFILEHDR out to disk
    if(!WriteFile( hFile, &id,
				ICONDIRSIZE,
				&dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing ICO");
		return FALSE;
	}

	    // Did we write a full MEMICONFILEHDR ?
    if( dwBytesWritten != ICONDIRSIZE )
	{
		AfxMessageBox("Error Writing ICO");
		return FALSE;
	}
        
    
    // Write the ICONDIRENTRY
    
    ICONDIRENTRY    ide;
	LPBYTE lpB;
   
	lpB = (LPBYTE)pbi;
	lpB += 4;
	lppbi = (LPBITMAPINFOHEADER)lpB;

    // Convert internal format to ICONDIRENTRY
    ide.bWidth = (BYTE)lppbi->biWidth;
    ide.bHeight = (BYTE)lppbi->biHeight/2;
    ide.bReserved = 0;
    ide.wPlanes = 0; //lppbi->biPlanes;  // really x hotspot
    ide.wBitCount = 0; //lppbi->biBitCount;  // really y hotspot
	ide.bColorCount = 0;

    if( (lppbi->biPlanes * lppbi->biBitCount) >= 8 )
        iNumColors = 0;
    else
        iNumColors = 1 << (lppbi->biPlanes * lppbi->biBitCount);

	ide.bColorCount = 0;

    ide.dwBytesInRes = RsrcSize;
	
    ide.dwImageOffset = ICONDIRSIZE +
						sizeof(ICONDIRENTRY);
						
						

    // Write the ICONDIRENTRY out to disk
    if( ! WriteFile( hFile, &ide, sizeof( ICONDIRENTRY ), &dwBytesWritten, NULL ) )
        return FALSE;

    // Did we write a full ICONDIRENTRY ?
    if( dwBytesWritten != sizeof( ICONDIRENTRY ) )
        return FALSE;
    

	
    
    /* Copy the BITMAPINFOHEADER and RGBQUAD array into the file. */ 
 
    if (!WriteFile(hFile, (LPVOID) lpB, sizeof(BITMAPINFOHEADER) 
                  + iNumColors * sizeof (RGBQUAD), 
                  (LPDWORD) &dwBytesWritten, (LPOVERLAPPED) NULL)) 

	{
		AfxMessageBox("Error Writing File"); 
		return FALSE;

    }
	   
 
    /* Copy the array of color indices into the .BMP file. */ 
	
	

	
	lpBits = (LPBYTE)lppbi +  lppbi->biSize + 
							 (iNumColors * sizeof(RGBQUAD));

    //DWORD dwTotal = cb = lppbi->biSizeImage; 
	DWORD dwTotal = cb = RsrcSize; 
    hp = lpBits; 
    while (cb > MAXWRITE)  
	{ 
            if (!WriteFile(hFile, (LPSTR) hp, (int) MAXWRITE, 
                          (LPDWORD) &dwBytesWritten, (LPOVERLAPPED) NULL)) 
			{
				AfxMessageBox("Error Writing File"); 
				return FALSE;

                
			}
            cb-= MAXWRITE; 
            hp += MAXWRITE; 
    } 
    if (!WriteFile(hFile, (LPSTR) hp, (int) cb, 
         (LPDWORD) &dwBytesWritten, (LPOVERLAPPED) NULL)) 
	{
		AfxMessageBox("Error Writing File"); 
		return FALSE;
         
	}

    CloseHandle( hFile );
    return FALSE;

}


BOOL CResviewerDoc::CreateDLGFile(LPCTSTR pszFile,
								  PVOID pdlg,
								  DWORD RsrcSize)
{
	DlgData dlgData(pszFile,m_currentresName,m_currentresID);
	return dlgData.DumpDialog(pdlg);
	//return TRUE;

}