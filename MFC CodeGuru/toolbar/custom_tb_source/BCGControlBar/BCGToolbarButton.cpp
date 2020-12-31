// BCGToolbarButton.cpp: implementation of the CBCGToolbarButton class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "BCGToolbarButton.h"
#include "BCGToolBarImages.h"
#include "BCGToolbarMenuButton.h"	// Ugly!

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CBCGToolbarButton, CObject, VERSIONABLE_SCHEMA | 1)

CLIPFORMAT CBCGToolbarButton::m_cFormat = (CLIPFORMAT)::RegisterClipboardFormat (_T("BCGToolbarButton"));

static const int TEXT_MARGIN = 3;
static const int SEPARATOR_WIDTH = 8;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGToolbarButton::CBCGToolbarButton()
{
	m_nID = 0;
	m_nStyle = TBBS_BUTTON;
	m_iImage = -1;
	m_bUserButton = FALSE;
	m_bDragFromCollection = FALSE;
	m_bText = FALSE;
	m_bImage = TRUE;
	m_bWrap = FALSE;

	m_rect.SetRectEmpty ();
}
//*********************************************************************************
CBCGToolbarButton::CBCGToolbarButton(UINT uiID, int iImage, LPCTSTR lpszText, BOOL bUserButton)
{
	m_nID = uiID;
	m_nStyle = TBBS_BUTTON;
	m_iImage = iImage;
	m_strText = (lpszText == NULL) ? _T("") : lpszText;
	m_bUserButton = bUserButton;
	m_bDragFromCollection = FALSE;
	m_bText = FALSE;
	m_bImage = TRUE;
	m_bWrap = FALSE;

	m_rect.SetRectEmpty ();
}
//*********************************************************************************
CBCGToolbarButton::~CBCGToolbarButton()
{
}
//*********************************************************************************
void CBCGToolbarButton::CopyFrom (const CBCGToolbarButton& src)
{
	m_nID			= src.m_nID;
	m_nStyle		= src.m_nStyle;
	m_iImage		= src.m_iImage;
	m_strText		= src.m_strText;
	m_bUserButton	= src.m_bUserButton;
	m_bText			= src.m_bText;
	m_bImage		= src.m_bImage;
	m_bWrap			= src.m_bWrap;
					
	m_bDragFromCollection = FALSE;
}					
//***************************************************************************************
void CBCGToolbarButton::Serialize (CArchive& ar)
{
	CObject::Serialize (ar);

	if (ar.IsLoading ())
	{
		ar >> m_nID;
		ar >> m_nStyle;	
		ar >> m_iImage;	
		ar >> m_strText;	
		ar >> m_bUserButton;
		ar >> m_bDragFromCollection;
		ar >> m_bText;
		ar >> m_bImage;
	}
	else
	{
		ar << m_nID;		
		ar << m_nStyle;	
		ar << m_iImage;	
		ar << m_strText;
		ar << m_bUserButton;
		ar << m_bDragFromCollection;
		ar << m_bText;
		ar << m_bImage;
	}
}
//***************************************************************************************
CLIPFORMAT CBCGToolbarButton::GetClipboardFormat ()
{
	return m_cFormat;
}
//***************************************************************************************
CBCGToolbarButton* CBCGToolbarButton::CreateFromOleData  (COleDataObject* pDataObject)
{
	ASSERT (pDataObject != NULL);
	ASSERT (pDataObject->IsDataAvailable (CBCGToolbarButton::m_cFormat));

	CBCGToolbarButton* pButton = NULL;

	try
	{
		//-------------------------------------
		// Get file refering to clipboard data:
		//-------------------------------------
		CFile* pFile = pDataObject->GetFileData (GetClipboardFormat ());
		if (pFile == NULL)
		{
			return FALSE;
		}

		//-------------------------------------------------------
		// Connect the file to the archive and read the contents:
		//-------------------------------------------------------
		CArchive ar (pFile, CArchive::load);

		//----------------------------------------
		// First, read run-time class information:
		//----------------------------------------
		CRuntimeClass* pClass = ar.ReadClass ();
		ASSERT (pClass != NULL);

		pButton = (CBCGToolbarButton*) pClass->CreateObject ();
		ASSERT (pButton != NULL);

		pButton->Serialize (ar);
		ar.Close ();
		delete pFile;

		return pButton;
	}
	catch (COleException* pEx)
	{
		TRACE("CBCGToolbarButton::CreateFromOleData. OLE exception: %x\r\n",
			pEx->m_sc);
		pEx->Delete ();
		return NULL;
	}
	catch (CArchiveException* pEx)
	{
		TRACE("CBCGToolbarButton::CreateFromOleData. Archive exception\r\n");
		pEx->Delete ();
		return FALSE;
	}
	catch (CNotSupportedException *pEx)
	{
		TRACE("CBCGToolbarButton::CreateFromOleData. \"Not Supported\" exception\r\n");
		pEx->Delete ();
		return FALSE;
	}

	if (pButton != NULL)
	{
		delete pButton;
	}

	return NULL;
}
//***************************************************************************************
void CBCGToolbarButton::OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
								BOOL bHorz, BOOL bCustomizeMode, BOOL bHighlight)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (this);
	ASSERT_VALID (pImages);

	CSize sizeImage = pImages->GetImageSize ();

	int x = rect.left;
	int y = bHorz ? rect.top : rect.bottom - sizeImage.cy;

	int iTextLen = IsDrawText () ? 
		(pDC->GetTextExtent (m_strText).cx + 2 * TEXT_MARGIN) : 0;

	int dx = bHorz ? rect.Width () - iTextLen : rect.Width ();
	int dy = bHorz ? rect.Height () : rect.Height () - iTextLen;

	// determine offset of bitmap (centered within button)
	CPoint ptImageOffset;
	ptImageOffset.x = (dx - sizeImage.cx - 1) / 2;
	ptImageOffset.y = (dy - sizeImage.cy) / 2;

	if (!bHorz)
	{
		ptImageOffset.y = -ptImageOffset.y;
	}

	CPoint ptTextOffset (TEXT_MARGIN, TEXT_MARGIN);

	if (IsDrawText ())
	{
		TEXTMETRIC tm;
		pDC->GetTextMetrics (&tm);

		if (bHorz)
		{
			ptTextOffset.y = (dy - tm.tmHeight) / 2;
		}
		else
		{
			ptTextOffset.x = (dx - tm.tmHeight) / 2;
		}
	}

	if (m_nStyle & (TBBS_PRESSED | TBBS_CHECKED))
	{
		// pressed in or checked

		ptImageOffset.x ++;
		ptImageOffset.y ++;

		ptTextOffset.x ++;

		if (bHorz)
		{
			ptTextOffset.y ++;
		}
		else
		{
			ptTextOffset.y --;
		}
	}

	BOOL bImageIsReady = FALSE;

	if ((m_nStyle & TBBS_PRESSED) || !(m_nStyle & TBBS_DISABLED) ||
					bCustomizeMode)
	{
		if (IsDrawImage () && pImages != NULL)
		{
			pImages->Draw (pDC, x, y, ptImageOffset, m_iImage);
		}

		if (bCustomizeMode || m_nStyle & TBBS_PRESSED)
		{
			bImageIsReady = TRUE;
		}
	}

	if (!bImageIsReady)
	{
		BOOL bDisabled = !bCustomizeMode &&
			(m_nStyle & TBBS_DISABLED);
		BOOL bIndeterminate = !bCustomizeMode &&
			(m_nStyle & TBBS_INDETERMINATE);

		if (!bHighlight)
		{
			bHighlight = !(m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE));
		}

		if (IsDrawImage () && pImages != NULL)
		{
			pImages->Draw (pDC, x, y, ptImageOffset, 
							m_iImage, !bHighlight, bDisabled);
		}
	}

	if (IsDrawText ())
	{
		if (IsDrawImage ())
		{
			if (bHorz)
			{
				ptTextOffset.x += sizeImage.cx + TEXT_MARGIN;
			}
			else
			{
				ptTextOffset.y += sizeImage.cy + TEXT_MARGIN;
			}
		}

		pDC->ExtTextOut (x + ptTextOffset.x, 
						bHorz ?
							rect.top + ptTextOffset.y :
							rect.bottom - ptTextOffset.y,
						ETO_CLIPPED,
						&rect, m_strText, NULL);
	}
}
//***********************************************************************************
int CBCGToolbarButton::OnCalculateSize (
								CDC* pDC,
								const CSize& sizeDefault,
								BOOL bHorz)
{
	int iSize = 0;

	if (m_nStyle & TBBS_SEPARATOR)
	{
		iSize += SEPARATOR_WIDTH;
	}
	else
	{
		if (IsDrawImage ())
		{
			iSize += (bHorz ? sizeDefault.cx : sizeDefault.cy);
		}

		if (IsDrawText () && !m_strText.IsEmpty ())
		{
			iSize += pDC->GetTextExtent (m_strText).cx + 2 * TEXT_MARGIN;
		}
	}

	ASSERT (iSize > 0);
	return iSize;
}
//************************************************************************************
BOOL CBCGToolbarButton::PrepareDrag (COleDataSource& srcItem)
{
	try
	{
		CSharedFile globFile;
		CArchive ar (&globFile,CArchive::store);

		//---------------------------------
		// Save run-time class information:
		//---------------------------------
		CRuntimeClass* pClass = GetRuntimeClass ();
		ASSERT (pClass != NULL);

		ar.WriteClass (pClass);

		//---------------------
		// Save button context:
		//---------------------
		Serialize (ar);
		ar.Close();

		srcItem.CacheGlobalData (GetClipboardFormat (), globFile.Detach());
	}
	catch (COleException* pEx)
	{
		TRACE("CBCGToolbarButton::PrepareDrag. OLE exception: %x\r\n",
			pEx->m_sc);
		pEx->Delete ();
		return FALSE;
	}
	catch (CArchiveException* pEx)
	{
		TRACE("CBCGToolbarButton::PrepareDrag. Archive exception\r\n");
		pEx->Delete ();
		return FALSE;
	}

	return TRUE;
}
