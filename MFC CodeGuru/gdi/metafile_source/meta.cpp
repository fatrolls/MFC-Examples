// metaex.cpp - Code for CMetaFile
#include "stdafx.h"
#include "meta.h"

IMPLEMENT_SERIAL(CMetaFile, CObject, VERSIONABLE_SCHEMA|METAFILE_VERSION)

CMetaFile::CMetaFile() : CMetaFileDC()
{
	m_emf = NULL;
	::ZeroMemory(&m_aldusMFHeader, sizeof(m_aldusMFHeader));
}

CMetaFile::~CMetaFile()
{
	if (m_emf)
		::DeleteEnhMetaFile(m_emf);
}

BOOL CMetaFile::Read(CFile *file)
{
	DWORD   		dwIsAldus;
	METAHEADER		mfHeader;
  	DWORD    		dwSize;
	DWORD			seekpos;

	if (file->Read(&dwIsAldus, sizeof(dwIsAldus)) != sizeof(dwIsAldus))
		return FALSE;
	
	if (dwIsAldus != ALDUSKEY) {
		// A windows metafile, not a placeable wmf 
		seekpos = 0;
		::ZeroMemory(&m_aldusMFHeader, sizeof(m_aldusMFHeader));
	}
	else {  
		// This is a placeable metafile 
	        // Convert the placeable format into something that can
	        // be used with GDI metafile functions 
		file->Seek(0, CFile::begin);
		if (file->Read(&m_aldusMFHeader, ALDUSMFHEADERSIZE) != ALDUSMFHEADERSIZE)
			return FALSE;
		seekpos = ALDUSMFHEADERSIZE;
	}
	file->Seek(seekpos, CFile::begin);
	// Read the metafile header 
	if (file->Read(&mfHeader, sizeof(mfHeader)) != sizeof(mfHeader))
		return FALSE;
	// At this point we have a metafile header regardless of whether
	// the metafile was a windows metafile or a placeable metafile
	// so check to see if it is valid.  There is really no good
	// way to do this so just make sure that the mtType is either
	// 1 or 2 (memory or disk file) 
	if ((mfHeader.mtType != 1) && (mfHeader.mtType != 2)) 
		return FALSE;
	// Allocate memory for the metafile bits 
	dwSize = mfHeader.mtSize * 2;
	BYTE* lpMFBits = new BYTE [dwSize];
	if (lpMFBits == NULL)
		return FALSE;
	// Seek to the metafile bits 
	file->Seek(seekpos, CFile::begin);
	// Read metafile bits and create
	// the enhanced metafile
	if (file->Read(lpMFBits, dwSize) == dwSize)
		m_emf = ::SetWinMetaFileBits(dwSize, lpMFBits, NULL, NULL);
	// Done with the bit data	
	delete [] lpMFBits;

	return m_emf ? TRUE : FALSE;
}

BOOL CMetaFile::Read(LPCTSTR lpszFileName)
{
	try {
		// Open the file
		CFile file(lpszFileName, CFile::modeRead);
		return Read(&file);
	}	
	catch(CFileException *e) {
		e->ReportError();
	}
	return FALSE;
}

void CMetaFile::Display(CDC *pDC, CRect &r, METAALIGNMENT align)
{
	// Check for valid enhanced metafile
	if (!m_emf)
		return;
	// Set the bounding rectangle
	// Thios may be changed by the
	// alignment code to preserve
	// aspect ratio, etc.
	CRect rectBounds = r;
	// Set alignment
	// We can only do this if we can
	// get the size of the metafile
	// This should be possible for
	// metafiles with Aldus headers
	if (m_aldusMFHeader.inch) {
		// Get the logical size of the metafile
		CSize size;
		size.cx = 254 * (m_aldusMFHeader.bbox.right - m_aldusMFHeader.bbox.left) 
				/ m_aldusMFHeader.inch;
		size.cy = 254 * (m_aldusMFHeader.bbox.bottom - m_aldusMFHeader.bbox.top) 
				/ m_aldusMFHeader.inch;
		// We now have the logical size
		// of the metafile.  We can use
		// this to create a rectangle
		// in which to display it - with
		// the correct alignment
		FitPicture(rectBounds, size, align);
	}
	// Play metafile
	pDC->PlayMetaFile(m_emf, rectBounds);
}

// Fit the metafile by altering the rectangle
// passed accordingly.  Returns true if the
// picture needs stretching
void CMetaFile::FitPicture(CRect& r, CSize& size, METAALIGNMENT align)
{
	CRect rectPrev = r;

	// First, sort out the height
	// of the rectangle
	switch (align) {
	case AlignTopLeft:
	case AlignTopCentre:
	case AlignTopRight:
		r.bottom = r.top + size.cy;
		break;
	case AlignMiddleLeft:
	case AlignMiddleCentre:
	case AlignMiddleRight:
		r.top = (r.bottom + r.top - size.cy) / 2;
		r.bottom = r.top + size.cy;
		break;
	case AlignBottomLeft:
	case AlignBottomCentre:
	case AlignBottomRight:
		r.top = r.bottom - size.cy;
		break;
	case AlignFit:
		// Make as large as possible, but keep aspect ratio.
		if (((r.right - r.left) * size.cy) > ((r.bottom - r.top) * size.cx)) {
			// Picture is taller. 
			// Adjust left and right and leave 
			// top and bottom alone.
			int w = (size.cx * (r.bottom - r.top)) / size.cy;
			r.left = (r.left + r.right - w) / 2;
			r.right = r.left + w;
		}
		else {
			int h = (size.cy * (r.right - r.left)) / size.cx;
			r.top = (r.top + r.bottom - h) / 2;
			r.bottom = r.top + h;
		}
		return;
	case AlignStretch:
		return;
	}

	// Sort out the rectangle width
	switch (align) {
	case AlignTopLeft:
	case AlignMiddleLeft:
	case AlignBottomLeft:
		r.right = r.left + size.cx;
		break;
	case AlignTopCentre:
	case AlignMiddleCentre:
	case AlignBottomCentre:
		r.left = (r.right + r.left - size.cx) / 2;
		r.right = r.left + size.cx;
		break;
	case AlignTopRight:
	case AlignMiddleRight:
	case AlignBottomRight:
		r.left = r.right - size.cx;
		break;
	}
	if (rectPrev.left > r.left)
		r.left = rectPrev.left;
	if (rectPrev.right < r.right)
		r.right = rectPrev.right;
	if (rectPrev.top > r.top)
		r.top = rectPrev.top;
	if (rectPrev.bottom < r.bottom)
		r.bottom = rectPrev.bottom;
	return;
}

void CMetaFile::Serialize(CArchive& archive)
{
	if (archive.IsStoring()) {
		// Save
		// Archive the header
		archive.Write(&m_aldusMFHeader, sizeof(m_aldusMFHeader));
		// We need to save the raw
		// bits of the metafile
		// We should save the size
		// of these bits first
		UINT nSize = 0;
		if (m_emf) {
			// Get size of metafile
			nSize = ::GetEnhMetaFileBits(m_emf, 0, NULL);
			// Now get the bits and save
			BYTE* pBits = new BYTE [nSize];
			if (pBits) {
				// Get metafile bits
				::GetEnhMetaFileBits(m_emf, nSize, pBits);
				// Write to archive
				archive << nSize;
				archive.Write(pBits, nSize);
				// Free memory
				delete [] pBits;
			}
			else {
				nSize = 0;
				archive << nSize;
			}
		}
		else {
			// Empty
			archive << nSize;
		}
	}
	else {
		// Load
		// Get the header
		archive.Read(&m_aldusMFHeader, sizeof(m_aldusMFHeader));
		// Get the metafile bits size
		UINT nSize;
		archive >> nSize;
		if (nSize) {
			// Allocate a buffer
			//BYTE* pBits = (BYTE *)GlobalAllocPtr(GHND, nSize);
			BYTE* pBits = new BYTE [nSize];
			if (pBits) {
				// Read bits
				archive.Read(pBits, nSize);
				// Set metafile
				m_emf = ::SetEnhMetaFileBits(nSize, pBits);
			}
			else {
				// Allocation error
				// Seek past bit data
				CFile* pFile = archive.GetFile();
				if (pFile)
					pFile->Seek(nSize, CFile::current);
			}
		}
	}
}

void CMetaFile::Clear()
{
	if (m_emf) {
		::DeleteEnhMetaFile(m_emf);
		m_emf = NULL;
		::ZeroMemory(&m_aldusMFHeader, sizeof(m_aldusMFHeader));
	}
}

bool CMetaFile::IsEmpty()
{
	return !m_emf;
}

bool CMetaFile::IsMetafile(CFile * pFile)
{
	pFile->Seek(0, CFile::begin);
	DWORD dwIsAldus;
	DWORD dwSeekPos = 0;
	if (pFile->Read(&dwIsAldus, sizeof(dwIsAldus)) != sizeof(dwIsAldus))
		return false;
	if (dwIsAldus == ALDUSKEY) {
		// This is a placeable metafile 
	        // Convert the placeable format into something that can
	        // be used with GDI metafile functions 
		pFile->Seek(0, CFile::begin);
		ALDUSMFHEADER aldusMFHeader;
		if (pFile->Read(&aldusMFHeader, ALDUSMFHEADERSIZE) != ALDUSMFHEADERSIZE)
			return false;
		dwSeekPos = ALDUSMFHEADERSIZE;
	}
	pFile->Seek(dwSeekPos, CFile::begin);
	METAHEADER mfHeader;
	//read the metafile header 
	if (pFile->Read(&mfHeader, sizeof(mfHeader)) != sizeof(mfHeader))
		return false;
	// Check header bytes
	return (mfHeader.mtType == 1 || mfHeader.mtType == 2);
}
