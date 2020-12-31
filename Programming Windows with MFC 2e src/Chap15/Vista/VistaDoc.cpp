// VistaDoc.cpp : implementation of the CVistaDoc class
//

#include "stdafx.h"
#include "Vista.h"

#include "VistaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVistaDoc

IMPLEMENT_DYNCREATE(CVistaDoc, CDocument)

BEGIN_MESSAGE_MAP(CVistaDoc, CDocument)
	//{{AFX_MSG_MAP(CVistaDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVistaDoc construction/destruction

CVistaDoc::CVistaDoc()
{
}

CVistaDoc::~CVistaDoc()
{
}

BOOL CVistaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVistaDoc serialization

void CVistaDoc::Serialize(CArchive& ar)
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
// CVistaDoc diagnostics

#ifdef _DEBUG
void CVistaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVistaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVistaDoc commands

BOOL CVistaDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    if (!CDocument::OnOpenDocument (lpszPathName))
        return FALSE;

	//
	// Open the file and create a DIB section from its contents.
	//
    HBITMAP hBitmap = (HBITMAP) ::LoadImage (NULL, lpszPathName,
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    if (hBitmap == NULL) {
		CString string;
		string.Format (_T ("%s does not contain a DIB"), lpszPathName);
		AfxMessageBox (string);
        return FALSE;
	}

    m_bitmap.Attach (hBitmap);

	//
    // Return now if this device doesn't support palettes.
	//
    CClientDC dc (NULL);
    if ((dc.GetDeviceCaps (RASTERCAPS) & RC_PALETTE) == 0)
        return TRUE;

	//
    // Create a palette to go with the DIB section.
	//
    if ((HBITMAP) m_bitmap != NULL) {
        DIBSECTION ds;
        m_bitmap.GetObject (sizeof (DIBSECTION), &ds);

        int nColors;
        if (ds.dsBmih.biClrUsed != 0)
            nColors = ds.dsBmih.biClrUsed;
        else
            nColors = 1 << ds.dsBmih.biBitCount;

		//
        // Create a halftone palette if the DIB section contains more
        // than 256 colors.
		//
        if (nColors > 256)
            m_palette.CreateHalftonePalette (&dc);

		//
        // Create a custom palette from the DIB section's color table
        // if the number of colors is 256 or less.
		//
        else {
            RGBQUAD* pRGB = new RGBQUAD[nColors];

            CDC memDC;
            memDC.CreateCompatibleDC (&dc);
            CBitmap* pOldBitmap = memDC.SelectObject (&m_bitmap);
            ::GetDIBColorTable ((HDC) memDC, 0, nColors, pRGB);
            memDC.SelectObject (pOldBitmap);

            UINT nSize = sizeof (LOGPALETTE) +
                (sizeof (PALETTEENTRY) * (nColors - 1));
            LOGPALETTE* pLP = (LOGPALETTE*) new BYTE[nSize];

            pLP->palVersion = 0x300;
            pLP->palNumEntries = nColors;

            for (int i=0; i<nColors; i++) {
                pLP->palPalEntry[i].peRed = pRGB[i].rgbRed;
                pLP->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
                pLP->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
                pLP->palPalEntry[i].peFlags = 0;
            }

            m_palette.CreatePalette (pLP);
            delete[] pLP;
            delete[] pRGB;
        }
    }
    return TRUE;
}

void CVistaDoc::DeleteContents() 
{
    if ((HBITMAP) m_bitmap != NULL)
        m_bitmap.DeleteObject ();

    if ((HPALETTE) m_palette != NULL)
        m_palette.DeleteObject ();
    
    CDocument::DeleteContents();
}

CBitmap* CVistaDoc::GetBitmap()
{
	return ((HBITMAP) m_bitmap == NULL) ? NULL : &m_bitmap;
}

CPalette* CVistaDoc::GetPalette()
{
	return ((HPALETTE) m_palette == NULL) ? NULL : &m_palette;
}
