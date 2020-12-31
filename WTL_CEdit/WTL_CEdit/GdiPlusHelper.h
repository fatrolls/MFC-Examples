/////////////////////////////////////////////////////////////////////
// This file was created by Ming(2013-05-30).
// You could reach me via 3099jo@163.com.
// Enjoy open source and WTL!
/////////////////////////////////////////////////////////////////////
#ifndef _GDIPLUSHELPER_H_INCLUDE_
#define _GDIPLUSHELPER_H_INCLUDE_

#pragma once
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

namespace GdiPlusHelper
{
	/////////////////////////////////////////////////////////////////////
	// Defined class for GDI Plus Image.
	class CImageHelpers
	{
		// Constructor and destructor.
	public:
		CImageHelpers() : m_pImage(NULL)
		{

		}

		~CImageHelpers()
		{
			if (m_pImage)
			{
				delete m_pImage;
				m_pImage = NULL;
			}

		}

		// Data members.
	public:
		Image*	m_pImage;

		// Operations.
	public:
		// Load image from resource manager.
		Image* Load_Image(ATL::_U_STRINGorID resource, ATL::_U_STRINGorID type = (UINT) 0)
		{
			if (m_pImage)
			{
				delete m_pImage;
			}

			if ( HIWORD(resource.m_lpstr) != NULL )
			{
				m_pImage = new Image(resource.m_lpstr);
				return m_pImage;
			}
			else
			{
				CResource res;
				if( !res.Load(type, resource) ) return NULL;

				DWORD dwSize	= res.GetSize();
				HANDLE hMemory	= ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
				if( hMemory == NULL ) return NULL;

				// Copy resource to memory.
				memcpy(GlobalLock(hMemory), res.Lock(), dwSize);
				GlobalUnlock(hMemory);

				// Create stream that write to image.
				IStream* pStream = NULL;
				CreateStreamOnHGlobal(hMemory, TRUE, &pStream);
				m_pImage = new Image(pStream);
				pStream->Release();
			}

			return m_pImage;
		}

		inline float GetWidth()
		{
			return (float)m_pImage->GetWidth();	
		}

		inline float GetHeight()
		{
			return (float)m_pImage->GetHeight();	
		}
	};

	/////////////////////////////////////////////////////////////////////
	// Defined class for GDI Plus Image.
	class CImageHelper
	{
		// Constructor, destructor and operators.
	public:
		CImageHelper() : m_pImage(NULL)
		{

		}

		~CImageHelper()
		{
			if (m_pImage)
			{
				delete m_pImage;
				m_pImage = NULL;
			}

		}

		CImageHelper& operator= (const CImageHelper& img)
		{
			if (this == &img)
			{
				return *this;
			}

			delete m_pImage;
			m_pImage = img.m_pImage->Clone();
			return *this;
		}

		// Data members.
	public:
		Image*	m_pImage;

		// Operations.
	public:
		// Load image from resource manager.
		Image* Load_Image(ATL::_U_STRINGorID resource, ATL::_U_STRINGorID type = (UINT) 0)
		{
			if (m_pImage)
			{
				delete m_pImage;
			}

			if ( HIWORD(resource.m_lpstr) != NULL )
			{
				m_pImage = new Image(resource.m_lpstr);
				return m_pImage;
			}
			else
			{
				CResource res;
				if( !res.Load(type, resource) ) return NULL;

				DWORD dwSize	= res.GetSize();
				HANDLE hMemory	= ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
				if( hMemory == NULL ) return NULL;

				// Copy resource to memory.
				memcpy(GlobalLock(hMemory), res.Lock(), dwSize);
				GlobalUnlock(hMemory);

				// Create stream that write to image.
				IStream* pStream = NULL;
				CreateStreamOnHGlobal(hMemory, TRUE, &pStream);
				m_pImage = new Image(pStream);
				pStream->Release();
			}

			return m_pImage;
		}

		inline float GetWidth()
		{
			return (float)m_pImage->GetWidth();	
		}

		inline float GetHeight()
		{
			return (float)m_pImage->GetHeight();	
		}
	};


	/////////////////////////////////////////////////////////////////////
	// Defined class for GDI Plus Brush.
	class CBrushHelper
	{
		// Constructor and destructor.
	public:
		CBrushHelper() : m_pBrush(NULL), m_pBitmap(NULL)
		{

		}

		~CBrushHelper()
		{
			DeleteOldBrush();
		}

		// Data members.
	public:
		TextureBrush*	m_pBrush;
		Bitmap*			m_pBitmap;
		CBrush			m_GDIBrush;

		// The sub window will get background brush via parent window painting types.
		enum GET_BRUSH_TYPE
		{
			GET_BY_WM_ERASEBKGND,
			GET_BY_WM_PRINTCLIENT,
			GET_BY_WM_PAINT,
		};

		// Operations.
	public:
		// Delete old brush.
		void DeleteOldBrush()
		{
			if (m_GDIBrush.m_hBrush)
			{
				m_GDIBrush.DeleteObject();
			}
			
			if (m_pBrush)
			{
				delete m_pBrush;
				m_pBrush = NULL;
			}

			if (m_pBitmap)
			{
				delete m_pBitmap;
				m_pBitmap = NULL;
			}
		}

		// Get background brush.
		TextureBrush* GetBackGroundBrush(CWindow Window, CWindow ParentWindow, GET_BRUSH_TYPE brush_type = GET_BY_WM_PAINT)
		{
			if (Window.m_hWnd == NULL || ParentWindow.m_hWnd == NULL)
			{
				return NULL;
			}

			// Delete old brush.
			DeleteOldBrush();

			// Get parent window hdc.
			CRect rcParent;
			ParentWindow.GetWindowRect(&rcParent);
			CClientDC dcParent = ParentWindow;
			CDC dcCompat;
			dcCompat.CreateCompatibleDC(dcParent);
			CBitmap bmpParent;
			bmpParent.CreateCompatibleBitmap(dcParent, rcParent.Width(), rcParent.Height());
			dcCompat.SelectBitmap(bmpParent);

			switch (brush_type)
			{
			default:
			case GET_BY_WM_ERASEBKGND:	{ ParentWindow.SendMessage(WM_ERASEBKGND, (WPARAM) (HDC) dcCompat, 0); break; }
			case GET_BY_WM_PAINT:	{ ParentWindow.SendMessage(WM_PAINT, (WPARAM) (HDC) dcCompat, (LPARAM)(PRF_ERASEBKGND | PRF_CLIENT | PRF_NONCLIENT)); break; }
			case GET_BY_WM_PRINTCLIENT:	{ ParentWindow.SendMessage(WM_PRINTCLIENT, (WPARAM) (HDC) dcCompat, (LPARAM)(PRF_ERASEBKGND | PRF_CLIENT | PRF_NONCLIENT)); break; }
			}

			// Draw parent window image to bitmap.
			CRect rcWindow;
			Window.GetWindowRect(&rcWindow);
			CDC dcWindow;
			dcWindow.CreateCompatibleDC();
			CBitmap bmpWidnow;
			bmpWidnow.CreateCompatibleBitmap(dcCompat, rcWindow.Width(), rcWindow.Height());

			dcWindow.SelectBitmap(bmpWidnow);
			CRect rcSnap = rcWindow;
			::MapWindowPoints(NULL, ParentWindow.m_hWnd, (LPPOINT) (LPRECT) &rcSnap, 2);
			dcWindow.BitBlt(0, 0, rcWindow.Width(), rcWindow.Height(), dcCompat, rcSnap.left, rcSnap.top, SRCCOPY);

			// Create Brush via bitmap.
			m_GDIBrush.CreatePatternBrush(bmpWidnow.m_hBitmap);
			m_pBitmap	= Bitmap::FromHBITMAP(bmpWidnow.m_hBitmap, NULL);
			m_pBrush	= new TextureBrush(m_pBitmap);
			CBrush;

			return m_pBrush;
		}
	};

	/////////////////////////////////////////////////////////////////////
	// Defined class for GDI Plus Font.
	class CFontHelper
	{
		// Constructor, destructor and operator.
	public:
		CFontHelper() : m_Font(NULL)
		{

		}

		~CFontHelper()
		{
			DeleteOldFont();
		}

		// Data members.
	public:
		Font*   m_Font;
	private:
		PrivateFontCollection   m_FontCollection;
		FontFamily              m_FontFamily;

		// Operations.
	public:
		void DeleteOldFont()
		{
			if (m_Font != NULL)
			{
				delete m_Font;
				m_Font = NULL;
			}
		}

		// Load font from resource manager.
		BOOL LoadFont(ATL::_U_STRINGorID resource, ATL::_U_STRINGorID type = _T("ttf"))
		{
			CResource res;
			if( !res.Load(type, resource) ) 
			{
				ATLASSERT(FALSE);
				return FALSE;
			}

			int nSize   = (int)res.GetSize();
			void* data  = res.Lock();

			Gdiplus::Status nResults = m_FontCollection.AddMemoryFont(data, nSize);

			if( nResults != Gdiplus::Ok )
			{
				ATLASSERT(FALSE);
				return FALSE;
			}

			SetFontStyle();
			return TRUE;
		}

		// Modify font style.
		BOOL SetFontStyle(Gdiplus::FontStyle fontstyle = FontStyleRegular, REAL nFontSize = 14.0F)
		{
			int nNumFound = 0;
			m_FontCollection.GetFamilies(1, &m_FontFamily, &nNumFound);

			if (nNumFound <= 0)
			{
				// You need load font first.
				ATLASSERT(FALSE);
				return FALSE;
			}

			// Delete old font.
			DeleteOldFont();
			m_Font = new Font(&m_FontFamily, nFontSize, fontstyle, UnitPixel);

			if (m_Font != NULL)
			{
				return TRUE;
			}
			ATLASSERT(FALSE);
			return FALSE;
		}

		// Turn GDI+ Font to HFONT (ANSI).
		HFONT FontToHFONT_A(HWND m_hWnd)
		{
			if (m_Font == NULL || m_hWnd == NULL)
			{
				ATLASSERT(FALSE);
				return NULL;
			}
			Graphics g(m_hWnd);
			LOGFONTA logFont;

			m_Font->GetLogFontA(&g, &logFont);
			logFont.lfQuality           = CLEARTYPE_QUALITY;
			logFont.lfOutPrecision      = OUT_DEVICE_PRECIS;
			logFont.lfClipPrecision     = CLIP_CHARACTER_PRECIS;
			logFont.lfCharSet           = ANSI_CHARSET;
			logFont.lfPitchAndFamily    = DEFAULT_PITCH;
			return ::CreateFontIndirectA(&logFont);
		}

		// Turn GDI+ Font to HFONT (Unicode).
		HFONT FontToHFONT_W(HWND m_hWnd)
		{
			if (m_Font == NULL || m_hWnd == NULL)
			{
				ATLASSERT(FALSE);
				return NULL;
			}
			Graphics g(m_hWnd);
			LOGFONTW logFont;

			m_Font->GetLogFontW(&g, &logFont);
			logFont.lfQuality           = CLEARTYPE_QUALITY;
			logFont.lfOutPrecision      = OUT_DEVICE_PRECIS;
			logFont.lfClipPrecision     = CLIP_CHARACTER_PRECIS;
			logFont.lfCharSet           = ANSI_CHARSET;
			logFont.lfPitchAndFamily    = DEFAULT_PITCH;
			return ::CreateFontIndirectW(&logFont);
		}
	};
}

#endif // _GDIPLUSHELPER_H_INCLUDE_

