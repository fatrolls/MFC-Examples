// ==========================================================================
// 					Class Implementation : COXBinDiffCalculator
// ==========================================================================

// Source file : bdifcalc.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "bdifcalc.h"	// class specification
#include "progress.h"	// progress bar
#include "oxdflhdr.h"	// file header

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXBinDiffCalculator, CObject)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
const double COXBinDiffCalculator::m_cMinMeanChunkLen = 20.0;
const double COXBinDiffCalculator::m_cMaxMeanChunkLen =	80.0;
const double COXBinDiffCalculator::m_cBigChunkLen =	500.0;
const TCHAR* COXBinDiffCalculator::m_cFileHeader = TEXT("BinDiff0001");

// If m_cDropEOL is TRUE, cr and lf are not allowed to function as delimiters
const BOOL COXBinDiffCalculator::m_cDropEOL = FALSE;

const DWORD COXBinDiffCalculator::m_cBufSiz = 		128;
const WORD COXBinDiffCalculator::m_cMinMatchLen =		6;
// ... Must be >= m_cMinMatchLen 
const WORD COXBinDiffCalculator::m_cMinEqualRunLen =	(COXBinDiffCalculator::m_cMinMatchLen+4);

// Tag values. A tag value is encoded in the 4 lowest bits of a tag byte.
// The 4 high bits of the tag byte are used for encoding a value 0-15.
const BYTE COXBinDiffCalculator::m_cTagSmallDiff = 		0;
const BYTE COXBinDiffCalculator::m_cTagMediumDiff =		1;
const BYTE COXBinDiffCalculator::m_cTagLargeDiff = 		2;
const BYTE COXBinDiffCalculator::m_cTagSmallNearCopy =	3;
const BYTE COXBinDiffCalculator::m_cTagMediumNearCopy =	4;
const BYTE COXBinDiffCalculator::m_cTagLargeNearCopy =	5;
const BYTE COXBinDiffCalculator::m_cTagSmallDistantCopy =	6;
const BYTE COXBinDiffCalculator::m_cTagMediumDistantCopy = 7;
const BYTE COXBinDiffCalculator::m_cTagLargeDistantCopy =	8;
const BYTE COXBinDiffCalculator::m_cTagSmallFarCopy =		9;
const BYTE COXBinDiffCalculator::m_cTagMediumFarCopy =	0x0A;
const BYTE COXBinDiffCalculator::m_cTagLargeFarCopy = 	0x0B;
// ... Tags 0x0C,0x0D,0x0E unused.
const BYTE COXBinDiffCalculator::m_cTagEOF =				0x0F;

// Maximum values encodable by different tags.
// 4-bit value (0-15)       is used to encode a value             1 - m_cSmallSize;
// 12-bit value (0-4095)    is used to encode a value  m_cSmallSize+1 - m_cMediumSize;
// 20-bit value (0-1048575) is used to encode a value m_cMediumSize+1 - m_cLargeSize;
const DWORD COXBinDiffCalculator::m_cSmallSize = 		16L;
const DWORD COXBinDiffCalculator::m_cMediumSize = 	(4096L + COXBinDiffCalculator::m_cSmallSize);
const DWORD COXBinDiffCalculator::m_cLargeSize = 		(1048576L + COXBinDiffCalculator::m_cMediumSize);

// Maximum file positions encodable in 2 or 3 bytes
const DWORD COXBinDiffCalculator::m_cNearDistance =	 0xFFFFL;
const DWORD COXBinDiffCalculator::m_cDistantDistance = 0xFFFFFF;

const DWORD COXBinDiffCalculator::m_cMaxStrLen = 255;


// Data members -------------------------------------------------------------
// protected:
	// COXDiffProgress* m_pProgressBar;
	// --- Pointer to the progress bar (may be derived from COXDiffProgress)

// private:
	
// Member functions ---------------------------------------------------------
// public:

COXBinDiffCalculator::COXBinDiffCalculator()
	:
#if ! BDEXTR
	m_LstFreeTreeNode(NULL),
	m_LstFreeMatchBlock(NULL),
#endif /* ! BDEXTR */
	m_pProgressBar(NULL)
	{
	m_pProgressBar = new COXDiffProgress;
	}

#if ! BDEXTR
void COXBinDiffCalculator::SubtractFiles(LPCTSTR orgFilNam, LPCTSTR derivedFilNam, LPCTSTR diffFilNam, 
										 COXDiffFileHeader* pHeader)
	{
	CStdioFile	OrgFil;
	CStdioFile	DerivedFil;
	CStdioFile	DiffFil;

	if (!DiffFil.Open(diffFilNam, CFile:: modeCreate | CFile::modeReadWrite | CFile::typeBinary))
		{
		CString errMsg;

		errMsg = TEXT("Cannot open file ");
		errMsg += diffFilNam;
		ASSERT(m_pProgressBar != NULL);
		m_pProgressBar->Abort(errMsg);
		}

	if (!OrgFil.Open(orgFilNam, CFile::modeRead | CFile::typeBinary | CFile::shareDenyWrite))
		{
		CString errMsg;

		errMsg = TEXT("Cannot open file ");
		errMsg += orgFilNam;
		ASSERT(m_pProgressBar != NULL);
		m_pProgressBar->Abort(errMsg);
		}


	if (!DerivedFil .Open(derivedFilNam, CFile::modeRead | CFile::typeBinary | CFile::shareDenyWrite))
		{
		CString errMsg;

		errMsg = TEXT("Cannot open file ");
		errMsg += derivedFilNam;
		ASSERT(m_pProgressBar != NULL);
		m_pProgressBar->Abort(errMsg);
		}

	SubtractFiles(&OrgFil, &DerivedFil, &DiffFil, pHeader);

	OrgFil.Close();
	DerivedFil.Close();
	DiffFil.Close();
	}

void COXBinDiffCalculator::SubtractFiles(CFile* pOrgFil, CFile* pDerivedFil, CFile* pDiffFil, 
										 COXDiffFileHeader* pHeader)
	{
	COXTreeNode*   pOrgTreeRoot = NULL;
	int          delim;
	COXMatchBlock* pMatchLst = NULL;
	LONG         size;
	LONG         orgSum;
	LONG         orgSize;
	LONG         derivedSum;
	LONG         derivedSize;

	// if no special header was specified, suplly a default header
	BOOL bDefHeader(FALSE);
	if (pHeader == NULL)
		{
		pHeader = new COXDiffFileHeader(m_cFileHeader);
		bDefHeader = TRUE;
		}
	DWORD nBeginHeaderPos = pDiffFil->GetPosition();
	pHeader->WriteHeader(pDiffFil);
	DWORD nEndHeaderPos = pDiffFil->GetPosition();

	orgSize = pOrgFil->GetLength();  
	size = derivedSize = pDerivedFil->GetLength();

	// Write dummy check-data; gets rewritten at end of this procedure
	WriteLongNBytes(0L,pDiffFil,4);
	WriteLongNBytes(0L,pDiffFil,4);
	WriteLongNBytes(0L,pDiffFil,4);
	WriteLongNBytes(0L,pDiffFil,4);  

	orgSum = 0;
	derivedSum = 0;

		// Dummy block
		{
		if (size == 0)	
			{
			int byte;
			BYTE helpByte;
			// ... EOF on diff fil
			pDiffFil->Write(&m_cTagEOF, 1);
			// ... Adjust checksum
			do
				{
				if (pOrgFil->Read(&helpByte, 1) == 1)
					byte = helpByte;
				else
					byte = EOF;
				if (byte != EOF)
					{
					orgSum += byte;
					}
				} while (byte != EOF);
			}
		else
			{
			// Find suitable delimiter
			delim = FindDelimiter(pOrgFil,m_cMinMeanChunkLen,m_cMaxMeanChunkLen);
			if (delim < 0) 
				delim = 0;
			// Build indexed position tree
			pOrgTreeRoot = BuildTree(pOrgFil,delim,orgSum);

			// Match files
			pMatchLst = MatchFiles(pOrgTreeRoot,pOrgFil,pDerivedFil,delim,derivedSum);

			// Write diff file
			DumpDiff(pMatchLst,pDerivedFil,pDiffFil);
			}
		}

	if (pMatchLst != NULL)
		DeleteMatchBlocks(pMatchLst);

	if (pOrgTreeRoot != NULL)
		DeleteTreeNode(pOrgTreeRoot);
	
		
	//  MSDOS has no resource fork: encode extra EOF
	pDiffFil->Write(&m_cTagEOF, 1);

	// Adjust the check-data
	pDiffFil->Seek(nEndHeaderPos - nBeginHeaderPos, CFile::begin);

	WriteLongNBytes(orgSize,pDiffFil,4);
	WriteLongNBytes(orgSum,pDiffFil,4);
	WriteLongNBytes(derivedSize,pDiffFil,4);
	WriteLongNBytes(derivedSum,pDiffFil,4);

	if (bDefHeader)
		delete pHeader;
	}
#endif /* ! BDEXTR */

void COXBinDiffCalculator::AddFiles(LPCTSTR orgFilNam, LPCTSTR derivedFilNam, LPCTSTR diffFilNam,
									COXDiffFileHeader* pHeader)
	{
	CStdioFile	OrgFil;
	CStdioFile	DerivedFil;
	CFile		DiffFil;
	CFileException* pFileEx = new CFileException;
	if (!DiffFil.Open(diffFilNam, CFile::modeRead | CFile::typeBinary | CFile::shareDenyWrite, pFileEx))
		{
		CString errMsg;
		errMsg = TEXT("Cannot open file ");
		errMsg += diffFilNam;
		ASSERT(m_pProgressBar != NULL);
		m_pProgressBar->Abort(errMsg);
		THROW(pFileEx);
		}

	if (!OrgFil.Open(orgFilNam, CFile::modeRead | CFile::typeBinary | CFile::shareDenyWrite, pFileEx))
		{
		CString errMsg;

		errMsg = TEXT("Cannot open file ");
		errMsg += orgFilNam;
		ASSERT(m_pProgressBar != NULL);
		m_pProgressBar->Abort(errMsg);
		THROW(pFileEx);
		} 

	if (!DerivedFil.Open(derivedFilNam, CFile:: modeCreate | CFile::modeReadWrite | CFile::typeBinary, pFileEx))
		{
		CString errMsg;

		errMsg =TEXT(" Cannot open file ");
		errMsg += derivedFilNam;
		ASSERT(m_pProgressBar != NULL);
		m_pProgressBar->Abort(errMsg);
		THROW(pFileEx);
		}

#ifdef WIN32
	pFileEx->Delete();
#else
    delete pFileEx;
#endif             

	AddFiles(&OrgFil, &DerivedFil, &DiffFil, pHeader);

	DerivedFil.Close();
	OrgFil.Close();
	DiffFil.Close();

	}

void COXBinDiffCalculator::AddFiles(CFile* pOrgFil, CFile* pDerivedFil, CFile* pDiffFil, 
									COXDiffFileHeader* pHeader)
	{
	int          c;
	BYTE		 helpByte;
	LONG         blockLen;
	LONG         blockPos;
	int          tag;
	LONG         derivedSize;
	LONG         derivedSum;
	LONG         orgSize;
	LONG         orgSum;
	LONG         checkDerivedSize;
	LONG         checkDerivedSum;
	LONG         checkOrgSize;
	LONG         checkOrgSum;
	LONG         prevDiffPos;
	LONG         diffPos;
	LONG         curPos;

	BOOL bDefHeader(FALSE);
	TRY
		{
		// if no special header was specified, suplly a default header
		if (pHeader == NULL)
			{
			pHeader = new COXDiffFileHeader(m_cFileHeader);
			bDefHeader = TRUE;
			}
	
		pHeader->ReadHeader(pDiffFil);
		}
	CATCH_ALL(e)
		{
		ASSERT(m_pProgressBar != NULL);
		if (bDefHeader)
			delete pHeader;
		m_pProgressBar->Abort(TEXT("Incorrect difference header"));
		THROW_LAST();
		}
	END_CATCH_ALL

	// Read sizes and checksums of original and updated file
	checkOrgSize = ReadLongNBytes(pDiffFil,4);
	checkOrgSum = ReadLongNBytes(pDiffFil,4);
	orgSize = 0;
	orgSum = 0;
	checkDerivedSize = ReadLongNBytes(pDiffFil,4);
	checkDerivedSum = ReadLongNBytes(pDiffFil,4);
	derivedSize = 0;
	derivedSum = 0;

		{
		orgSize += pOrgFil->GetLength();

		ASSERT(m_pProgressBar != NULL);
		m_pProgressBar->Init(0,pOrgFil->GetLength(),TEXT("Checking:"));
		curPos = 0;
		c = EOF;
		while (pOrgFil->Read(&helpByte, 1) == 1)
			{
			c = helpByte;
			if ((curPos & 0xFFF) == 0) 
				if (!m_pProgressBar->Adjust(curPos))
					m_pProgressBar->Abort(TEXT("Aborting"));
			orgSum += c;
			curPos++;
			} 
		pOrgFil->Seek(0L, CFile::begin);
		m_pProgressBar->Close();

		ASSERT(m_pProgressBar != NULL);
		m_pProgressBar->Init(0,pDiffFil->GetLength(),TEXT("Apply diff:"));
		tag = 0;
		prevDiffPos = 0;
		diffPos = 0;
		while (tag != m_cTagEOF && pDiffFil->Read(&helpByte, 1) == 1)
			{
			c = helpByte;
			diffPos++;

			// Adjust bar every 256 bytes
			if (diffPos - prevDiffPos > 0xFF) 
				{
				if (!m_pProgressBar->Adjust(diffPos))
					m_pProgressBar->Abort(TEXT("Aborting"));
				prevDiffPos = diffPos;
				}

			tag = c & 0x0F;
			switch (tag)
				{  
				case m_cTagSmallDiff:
					blockLen = (c >> 4) + 1;
					CopyFileChars(blockLen,pDiffFil,pDerivedFil,derivedSum);
					diffPos += blockLen;
					derivedSize += blockLen;
					break;
				case m_cTagMediumDiff:
					blockLen = (c >> 4);
					if (pDiffFil->Read(&helpByte, 1) == 1)
						c = helpByte;
					else
						c = EOF;
					diffPos++;
					if (c != EOF)
						{
						blockLen = ((blockLen << 8) | c) + m_cSmallSize + 1;
						CopyFileChars(blockLen,pDiffFil,pDerivedFil,derivedSum);
						diffPos += blockLen;
						derivedSize += blockLen;
						}
					break;
				case m_cTagLargeDiff:
					blockLen = (c >> 4);
					if (pDiffFil->Read(&helpByte, 1) == 1)
						c = helpByte;
					else
						c = EOF;
					diffPos++;
					if (c != EOF)
						{
						blockLen = (blockLen << 8) | c;
						if (pDiffFil->Read(&helpByte, 1) == 1)
							c = helpByte;
						else
							c = EOF;
						diffPos++;
						if (c != EOF)
							{
							blockLen = ((blockLen << 8) | c) + m_cMediumSize + 1;
							}
						CopyFileChars(blockLen,pDiffFil,pDerivedFil,derivedSum);
						diffPos += blockLen;
						derivedSize += blockLen;
						}
					break;
				case m_cTagSmallNearCopy:
					blockLen = (c >> 4) + 1;
					blockPos = ReadLongNBytes(pDiffFil,2);
					diffPos += 2;
					pOrgFil->Seek(blockPos, CFile::begin);
					CopyFileChars(blockLen,pOrgFil,pDerivedFil,derivedSum);
					derivedSize += blockLen;
					break;
				case m_cTagMediumNearCopy:
					blockLen = (c >> 4);
					if (pDiffFil->Read(&helpByte, 1) == 1)
						c = helpByte;
					else
						c = EOF;
					diffPos++;
					if (c != EOF)
						{
						blockLen = ((blockLen << 8) | c) + m_cSmallSize + 1;
						blockPos = ReadLongNBytes(pDiffFil,2);
						diffPos += 2;
						pOrgFil->Seek(blockPos, CFile::begin);
						CopyFileChars(blockLen,pOrgFil,pDerivedFil,derivedSum);
						derivedSize += blockLen;
						}
					break;
				case m_cTagLargeNearCopy:
					blockLen = (c >> 4);
					if (pDiffFil->Read(&helpByte, 1) == 1)
						c = helpByte;
					else
						c = EOF;
					diffPos++;
					if (c != EOF)
						{
						blockLen = (blockLen << 8) | c;
						if (pDiffFil->Read(&helpByte, 1) == 1)
							c = helpByte;
						else
							c = EOF;
						diffPos++;
						if (c != EOF)
							{
							blockLen = ((blockLen << 8) | c) + m_cMediumSize + 1;
							blockPos = ReadLongNBytes(pDiffFil,2);
							diffPos += 2;
							pOrgFil->Seek(blockPos, CFile::begin);
							CopyFileChars(blockLen,pOrgFil,pDerivedFil,derivedSum);
							derivedSize += blockLen;
							}
						}
					break;
				case m_cTagSmallDistantCopy:
					blockLen = (c >> 4) + 1;
					blockPos = ReadLongNBytes(pDiffFil,3);
					diffPos += 3;
					pOrgFil->Seek(blockPos, CFile::begin);
					CopyFileChars(blockLen,pOrgFil,pDerivedFil,derivedSum);
					derivedSize += blockLen;
					break;
				case m_cTagMediumDistantCopy:
					blockLen = (c >> 4);
					if (pDiffFil->Read(&helpByte, 1) == 1)
						c = helpByte;
					else
						c = EOF;
					diffPos++;
					if (c != EOF)
						{
						blockLen = ((blockLen << 8) | c) + m_cSmallSize + 1;
						blockPos = ReadLongNBytes(pDiffFil,3);
						diffPos += 3;
						pOrgFil->Seek(blockPos, CFile::begin);
						CopyFileChars(blockLen,pOrgFil,pDerivedFil,derivedSum);
						derivedSize += blockLen;
						}
					break;
				case m_cTagLargeDistantCopy:
					blockLen = (c >> 4);
					if (pDiffFil->Read(&helpByte, 1) == 1)
						c = helpByte;
					else
						c = EOF;
					diffPos++;
					if (c != EOF)
						{
						blockLen = (blockLen << 8) | c;
						if (pDiffFil->Read(&helpByte, 1) == 1)
							c = helpByte;
						else
							c = EOF;
						diffPos++;
						if (c != EOF)
							{
							blockLen = ((blockLen << 8) | c) + m_cMediumSize + 1;
							blockPos = ReadLongNBytes(pDiffFil,3);
							diffPos += 3;
							pOrgFil->Seek(blockPos, CFile::begin);
							CopyFileChars(blockLen,pOrgFil,pDerivedFil,derivedSum);
							derivedSize += blockLen;
							}
						}
					break;
				case m_cTagSmallFarCopy:
					blockLen = (c >> 4) + 1;
					blockPos = ReadLongNBytes(pDiffFil,4);
					diffPos += 4;
					pOrgFil->Seek(blockPos, CFile::begin);
					CopyFileChars(blockLen,pOrgFil,pDerivedFil,derivedSum);
					derivedSize += blockLen;
					break;
				case m_cTagMediumFarCopy:
					blockLen = (c >> 4);
					if (pDiffFil->Read(&helpByte, 1) == 1)
						c = helpByte;
					else
						c = EOF;
					diffPos++;
					if (c != EOF)
						{
						blockLen = ((blockLen << 8) | c) + m_cSmallSize + 1;
						blockPos = ReadLongNBytes(pDiffFil,4);
						diffPos += 4;
						pOrgFil->Seek(blockPos, CFile::begin);
						CopyFileChars(blockLen,pOrgFil,pDerivedFil,derivedSum);
						derivedSize += blockLen;
						}
					break;
				case m_cTagLargeFarCopy:
					blockLen = (c >> 4);
					if (pDiffFil->Read(&helpByte, 1) == 1)
						c = helpByte;
					else
						c = EOF;
					diffPos++;
					if (c != EOF)
						{
						blockLen = (blockLen << 8) | c;
						if (pDiffFil->Read(&helpByte, 1) == 1)
							c = helpByte;
						else
							c = EOF;
						diffPos++;
						if (c != EOF)
							{
							blockLen = ((blockLen << 8) | c) + m_cMediumSize + 1;
							blockPos = ReadLongNBytes(pDiffFil,4);
							diffPos += 4;
							pOrgFil->Seek(blockPos, CFile::begin);
							CopyFileChars(blockLen,pOrgFil,pDerivedFil,derivedSum);
							derivedSize += blockLen;
							}
						}
					break;
				case m_cTagEOF:
					break;
				default:
					ASSERT(m_pProgressBar != NULL);
					m_pProgressBar->Abort(TEXT("Unknown tag in diff file - possibly created by a more recent BinDiff"));
					break;
				}
			}

		m_pProgressBar->Close();

		if (bDefHeader)
			delete pHeader;

		} // End of dummy block

	if (orgSize != checkOrgSize || orgSum != checkOrgSum)
		{
		ASSERT(m_pProgressBar != NULL);
		m_pProgressBar->Abort(TEXT("Original file is not the file the diff was created with."));
		}

	if (derivedSize != checkDerivedSize || derivedSum != checkDerivedSum)
		{
		ASSERT(m_pProgressBar != NULL);
		m_pProgressBar->Abort(TEXT("CRC failure : New derived file is corrupt.\nPatch file could be invalid"));
		}
	}

void COXBinDiffCalculator::ReplaceProgressBar(COXDiffProgress*	pProgressBar)
	{
	// ... Should already have a progress bar
	ASSERT(m_pProgressBar != NULL);
	// ... Not allowed to replace by an empty one
	ASSERT(pProgressBar != NULL);
	delete m_pProgressBar;
	m_pProgressBar = pProgressBar;
	}

#ifdef _DEBUG
void COXBinDiffCalculator::Dump(CDumpContext& dc) const
	{
	CObject::Dump(dc);
	}

void COXBinDiffCalculator::AssertValid() const
	{
	CObject::AssertValid();
	}
#endif

COXBinDiffCalculator::~COXBinDiffCalculator()
	{
	// ... Should always have a progress bar
	ASSERT(m_pProgressBar != NULL);
	delete m_pProgressBar;

	if (m_LstFreeTreeNode != NULL)
		DeleteTreeNode(m_LstFreeTreeNode);

	DeleteMatchBlocks(m_LstFreeMatchBlock);
	}

// protected:
void COXBinDiffCalculator::DeleteTreeNode(COXTreeNode* pTreeNode)
	// --- In  : pTreeNode : The tree node to delete
	// --- Out : 
	// --- Returns : 
	// --- Effect : recursive function.  First deletes its children then deletes itself
	{
	ASSERT(pTreeNode != NULL);

	if (pTreeNode->pGE != NULL)
		DeleteTreeNode(pTreeNode->pGE);

	if (pTreeNode->pLT != NULL)
		DeleteTreeNode(pTreeNode->pLT);

	delete pTreeNode;
	pTreeNode = NULL;
	}

void COXBinDiffCalculator::CopyFileChars(LONG count, CFile* pInFile, CFile* pOutFile, LONG& sum)
	// --- In  : count : The number of bytes to copy
	//			 pInFile : The input file
	//			 pOutFile : The output file
	//			 sum : The previous checksum
	// --- Out : sum :The checksum after to bytes are copied
	// --- Returns :
	// --- Effect : Copies the specified number of bytes from the in file
	//              to the out file and adjusts the checksum
	{
	const UINT nBufferLength = 2048;
	BYTE pBuffer[nBufferLength + 1];
	UINT nLengthToRead;
	UINT nLengthRead;
	BYTE* pByte;                                           
	BYTE* pLastByte;

	while (0 < count)
		{
		// Copy the bytes
		nLengthToRead = nBufferLength < (UINT)count ? nBufferLength : (UINT)count;
		nLengthRead = pInFile->Read(pBuffer, nLengthToRead);
		if (nLengthRead == 0)
			AfxThrowFileException(CFileException::endOfFile);

		pOutFile->Write(pBuffer, nLengthRead);
		count -= nLengthRead;
		// Add all the bytes together (for checksum)
		pByte = pBuffer;
		pLastByte = &pBuffer[nLengthRead - 1];
		while(pByte <= pLastByte)
			sum += *(pByte++);
		}
	}

LONG COXBinDiffCalculator::ReadLongNBytes(CFile* pFile,int n)
	// --- In  : pFile : The input file
	//			 n : The number of bytes to read
	// --- Out : 
	// --- Returns : The number represented by those bytes
	// --- Effect : It is expected that the MOST SIGNIFICANT bytes come FIRST
	{
	LONG x;
	BYTE byte;

	x = 0;
	while (n > 0)
		{
		if (pFile->Read(&byte, 1) == 1)
			x = (x << 8) | byte;
		else
			{
			n = 0;
			TRACE(_T("COXBinDiffCalculator::ReadLongNBytes : EOF Encountered while reading long\n"));
			AfxThrowFileException(CFileException::endOfFile);
			}
		n--;
		}

	return x;
	}


#if ! BDEXTR
void COXBinDiffCalculator::WriteLongNBytes(LONG x, CFile* pFile,int n)
	// --- In  : x : The long number to write
	//			 pFile : The output file
	//			 n : The number of bytes to write
	// --- Out : 
	// --- Returns : 
	// --- Effect : It is expected that the MOST SIGNIFICANT bytes come FIRST
	//				Writes the specified number (x) as a number of bytes (n)
	//			    to the output file
	{
	BYTE byte = 0;
	while (n > 4)
		{
		pFile->Write(&byte, 1);
		n--;
		}

	if (n == 4)
		{
		byte = BYTE((x >> 24) & 0xFF);
		pFile->Write(&byte, 1);
		n--;
		}

	if (n == 3)
		{
		byte = BYTE((x >> 16) & 0xFF);
		pFile->Write(&byte, 1);
		n--;
		}

	if (n == 2)
		{
		byte = BYTE((x >> 8) & 0xFF);
		pFile->Write(&byte, 1);
		n--;
		}

	if (n == 1)
		{
		byte = BYTE(x & 0xFF);
		pFile->Write(&byte, 1);
		}
	}

void COXBinDiffCalculator::ScanFile(CFile* pFile, COXByteAttribs* byteTable)
	// --- In  : pFile : input file
	//			 byteTable : table to store statistical info in
	// --- Out : byteTable : table with statistical info
	// --- Returns : 
	// --- Effect : Makes a statistical scan of the specified file
	// 				Scans file and for each byte 0-255, calculate 
	//				mean distance and standard deviation of the distances 
	//				between occurences of these bytes:
	//
	// E.g. look at byte b in the file:
	//
	// ------b---------b-----b-----------b------b-----b----
	// < d1  ><   d2   >< d3 ><     d4   >< d5  >< d6 >
	// <  7  ><   10   ><  6 ><    12    ><  7  ><  6 >
	// The mean and std.dev. are calculated on distances d1,d2,... for byte b.
	{
	int      		byte;
	BYTE			helpByte;
	DWORD			curPos;
	DWORD 			dist;
	COXByteAttribs* 	pByteAttribs;
	double      	dDist;

	// Initialize tables
	pByteAttribs = byteTable;
	for (byte = 0; byte < 256; byte++)
		{
		pByteAttribs->lastPos = -1L;
		pByteAttribs->sum = 0L;
		pByteAttribs->sumSquares = 0.0;
		pByteAttribs->mean = 0.0;
		pByteAttribs->stdDev = 0.0;
		pByteAttribs->cnt = 0L;
		pByteAttribs++;
		}

	// Scan through file
	pFile->Seek(0L,CFile::begin);
	curPos = 0L;
	do
		{
		// Adjust progress bar every 4 K bytes
		if ((curPos & 0xFFF) == 0)
		if (!m_pProgressBar->Adjust(curPos))
			m_pProgressBar->Abort(TEXT("Aborting"));

		if (pFile->Read(&helpByte, 1) == 1)
			byte = helpByte;
		else
			byte = EOF;
		if (byte != EOF)
			{
			pByteAttribs = &byteTable[byte];
			// ... Calculate distance from last occurrence of this byte
			dDist = dist = curPos - pByteAttribs->lastPos;
			// ... Remember this byte's position
			pByteAttribs->lastPos = curPos;
			pByteAttribs->sum += dist;      
			pByteAttribs->sumSquares += dDist * dDist;

			// ...cnt contains the number of occurrences
			pByteAttribs->cnt++;
			}
		curPos++;
		} while (byte != EOF);

	// Calculate mean and standard deviation for all bytes.
	pByteAttribs = byteTable;
	for (byte = 0; byte < 256; byte++)
		{
		// Make byte 'occur' just after EOF
		dDist = dist = curPos - pByteAttribs->lastPos;
		pByteAttribs->sum += dist;
		pByteAttribs->sumSquares += dDist*dDist;
		pByteAttribs->cnt++;

		// Calculate mean. Bytes that did not occur get mean equal to FILE size
		pByteAttribs->mean =
		(double) pByteAttribs->sum / (double) pByteAttribs->cnt;

		// Calculate standard deviation. We could also use the variance
		// but I like the std. dev. more.
		pByteAttribs->stdDev =
		sqrt(pByteAttribs->sumSquares / (double) pByteAttribs->cnt
			- pByteAttribs->mean*pByteAttribs->mean);

		pByteAttribs++;
		}

	}

int COXBinDiffCalculator::FindDelimiter(CFile* pFile, double minMeanChunkLen, double maxMeanChunkLen)
	// --- In  : pFile : input file
	//			 byteTable
	// --- Out : 
	// --- Returns : 
	// --- Effect : Analyze open file and determine a suitable delimiter 
	//				for chopping the file into chunks. 
	//				This routine changes the current file position.
	{
	int    byte;
	int    bestByte;
	COXByteAttribs byteTable[256];
	LONG   filSiz;

	filSiz = pFile->GetLength();
	ASSERT(m_pProgressBar != NULL);
	m_pProgressBar->Init(0L,filSiz,TEXT("Pass 1 of 3:"));

	ScanFile(pFile,byteTable);

	// Determine best byte
	bestByte = -1;
	while (bestByte == -1
		&& maxMeanChunkLen < m_cBigChunkLen 
		&& maxMeanChunkLen < filSiz)
		{
		COXByteAttribs* pByteAttribs;
		COXByteAttribs* pBestByteAttribs;

		pByteAttribs = byteTable;
		pBestByteAttribs = NULL;
		for (byte = 0; byte < 256; byte++)
			{
#if m_cDropEOL
			if (byte != '\015' && byte != '\012')
#endif
				{
				// Check if chunk length is between minMeanLen and maxMeanLen.
				if (pByteAttribs->mean >= minMeanChunkLen &&  
				pByteAttribs->mean <= maxMeanChunkLen)
					{
					if (bestByte == -1)
						{ 
						bestByte = byte;
						pBestByteAttribs = pByteAttribs;
						}
					else
						{
						// Compare stddev: if it is lower, 
						// the byte is better
						if (pBestByteAttribs->stdDev > pByteAttribs->stdDev)
							{
							bestByte = byte;
							pBestByteAttribs = pByteAttribs;
							}
						}
					}
				}
			pByteAttribs++;
			}
		// Increase allowable chunk length for the case no acceptable delimiter was
		// found: we will loop then
		maxMeanChunkLen += 50;
		}

	m_pProgressBar->Close();

	return(bestByte);

	}

COXBinDiffCalculator::COXTreeNode* COXBinDiffCalculator::NewTreeNode()
	// --- In  : 
	// --- Out : 
	// --- Returns : The new tree node
	// --- Effect : Create a new tree node or reuse one of the free list
	{
	COXTreeNode* pTreeNode;

	if (m_LstFreeTreeNode == NULL)
		{
		pTreeNode = new COXTreeNode();
		}
	else
		{
		pTreeNode = m_LstFreeTreeNode;
		m_LstFreeTreeNode = m_LstFreeTreeNode->pGE;
		}

	pTreeNode->filPos = 0L;
	pTreeNode->pGE = NULL;
	pTreeNode->pLT = NULL;

	return(pTreeNode);
	}

void COXBinDiffCalculator::FreeTreeNode(COXTreeNode* pTreeNode)
	// --- In  : pTreeNode : The node to free
	// --- Out : 
	// --- Returns : 
	// --- Effect : Releases a tree node by putting on the free list
	{
	pTreeNode->pGE = m_LstFreeTreeNode;
	m_LstFreeTreeNode = pTreeNode;
	}
 
int COXBinDiffCalculator::CmpNode(COXTreeNode* pNode1, CFile* pFil1, COXTreeNode* pNode2,
		CFile* pFil2, int delim, LONG* pEqualLen)
	// --- In  : pNode1 :
	//			 pFil1 :
	//			 pNode2 :
	//			 pFil2 :
	//			 delim : The chopping character
	//			 pEqualLen : Number of equal characters encountered.
	// --- Out : 
	// --- Returns : -1, 0, 1 if <, = , >.
	// --- Effect : Compare two tree nodes
	//				Every tree node has m_cMinMatchLen characters of 
	//				the file buffered within the node: first compare these
	//				If all these characters are equal, read characters from 
	//				the associated files and compare these.
	//				If the nodes are different, set equalLen to the 
	//				number of equal characters encountered.
	{
	LONG   pos1;
	BYTE  buf1[m_cBufSiz];
	BYTE* p1;
	LONG   pos2;
	BYTE  buf2[m_cBufSiz];
	BYTE* p2;
	int    result;
	LONG   l;

	pos1 = pNode1->filPos;
	pos2 = pNode2->filPos;
	// ... -2 means: not yet defined
	result = -2; 
	*pEqualLen = 0;

	// First compare the m_cMinMatchLen buffered bytes from both nodes
	p1 = pNode1->bytes;
	p2 = pNode2->bytes;
	l = 0;
	while (l < m_cMinMatchLen && *p1 == *p2 && *p1 != delim /* && *p2 != delim */)
		{
		p1++;
		p2++;
		l++;
		(*pEqualLen)++;
		}

	if (l == m_cMinMatchLen)
		{
		// If no difference was found, we will have to compare both files from
		// m_cMinMatchLen bytes after pos1 and pos2.
		pos1 += m_cMinMatchLen;
		pos2 += m_cMinMatchLen;
		}
	else if (*p1 == delim && *p2 != delim)
		{
		result = -1; // node 1 < node 2 because node 1 is shorter
		}
	else if (*p2 == delim && *p1 != delim)
		{
		result = 1; // node 2 < node 1 because node 2 is shorter
		}
	else if (*p1 == *p2 && *p1 == delim)
		{
		result = 0; // node 1 == node 2: both end in a delimiter at the same time
		}
	else if (*p1 < *p2)
		{
		result = -1; // node 1 < node 2 because a different character found
		}
	else if (*p2 < *p1)
		{
		result = 1; // node 2 < node 1 because a different character found
		}

	// If result is -2, no difference was found in the buffered bytes. Start 
	// reading bytes from the files in chuncks of m_cBufSiz bytes.
	if (result == -2)
		{
		do
			{
			// Read a buffer from file 1. Pad file with delimiter after eof.
			pFil1->Seek(pos1,CFile::begin);
			l = pFil1->Read(buf1,(UINT)m_cBufSiz);
			if (l < m_cBufSiz) 
				buf1[l] = BYTE(delim);
			// Read a buffer from file 2. Pad file with delimiter after eof.
			pFil2->Seek(pos2,CFile::begin);
			l = pFil2->Read(buf2,(UINT)m_cBufSiz);
			if (l < m_cBufSiz) 
				buf2[l] = BYTE(delim);

			// Compare buffers
			p1 = buf1;
			p2 = buf2;
			l = 0;
			while (l < m_cBufSiz && *p1 == *p2 && *p1 != delim /* && *p2 != delim */)
				{
				p1++;
				p2++;
				l++;
				(*pEqualLen)++;
				}

			// If no difference was found: set file positions to read new buffers
			if (l == m_cBufSiz)
				{
				pos1 += m_cBufSiz;
				pos2 += m_cBufSiz;
				}
			else if (*p1 == delim && *p2 != delim)
				{
				result = -1; /* node 1 < node 2  */
				}
			else if (*p2 == delim && *p1 != delim)
				{
				result = 1; /* node 2 < node 1 */
				}
			else if (*p1 == *p2 && *p1 == delim)
				{
				result = 0; /* node 1 == node 2 */
				}
			else if (*p1 < *p2)
				{
				result = -1;
				}
			else if (*p2 < *p1)
				{
				result = 1;
				}
			} while (result == -2);
		}
	return(result);
	}

void COXBinDiffCalculator::FindBestMatch(COXTreeNode*  pOrgTreeRoot,
		COXTreeNode** ppOrgTreeNode, CFile* pOrgFil, COXTreeNode*  pDerivedTreeNode,
        CFile* pDerivedFil, int delim, LONG* pMatchLen)
	// --- In  : pOrgTreeRoot :
	//			 ppOrgTreeNode :
	//			 pOrgFil :
	//			 pDerivedTreeNode :
	//			 pDerivedFil :
	//			 delim :
	//			 pMatchLen :
	// --- Out : 
	// --- Returns : 
	// --- Effect : From a tree with root node pOrgTreeRoot, find the node 
	//				pOrgTreeNode that best matches pDerivedTreeNode. 
	//				Also find length of match.
	{
	int        direction;
	COXTreeNode* pNode;
	LONG       equalLen;

	// Find best location from tree
	*ppOrgTreeNode = NULL;
	pNode = pOrgTreeRoot;
	*pMatchLen = 0L;

	// Descend tree and remember node with longest match
	while (pNode != NULL)
		{
		direction = CmpNode(pDerivedTreeNode,pDerivedFil,pNode,pOrgFil,delim,&equalLen);

		// Remember match if length is greater than previous best
		if (equalLen > *pMatchLen)
			{
			*pMatchLen = equalLen;
			*ppOrgTreeNode = pNode;
			}

		if (direction == -1)
			{
			pNode = pNode->pLT;
			}
		else if (direction == 1)
			{
			pNode = pNode->pGE;
			}
		else /* Node is equal: stop search */
			{
			pNode = NULL;
			}
		}
	}

void COXBinDiffCalculator::AddTreeNode(COXTreeNode** ppTreeRoot, CFile* pFile, 
		int delim, COXTreeNode* pNewNode)
	// --- In  : ppTreeRoot : Root of the tree
	//			 pFile :
	//			 delim : 
	//			 pNewNode : The new node to add
	// --- Out : 
	// --- Returns : 
	// --- Effect : Add new node to index tree and linked list.
	{
	COXTreeNode* pNode;
	COXTreeNode* pPrvNode;
	int        cmp=0;
	LONG       equalLen;  

	// Find location in tree
	pNode = *ppTreeRoot;
	pPrvNode = NULL;
	while (pNode != NULL)
		{
		pPrvNode = pNode;
		cmp = CmpNode(pNewNode,pFile,pNode,pFile,delim,&equalLen);
		if (cmp == -1)
			{
			pNode = pNode->pLT;
			}
		else if (cmp == 1) 
			{
			pNode = pNode->pGE;
			}
		else // There is an equal node: stop looking
			{
			pNode = NULL;
			}
		}

	if (pPrvNode == NULL)
		{
		*ppTreeRoot = pNewNode;
		}
	else
		{
		if (cmp == -1)
			{
			pPrvNode->pLT = pNewNode;
			}
		else if (cmp == 1)
			{
			pPrvNode->pGE = pNewNode;
			}
		else
			{
			FreeTreeNode(pNewNode);
			}
		}
	}

COXBinDiffCalculator::COXTreeNode* COXBinDiffCalculator::BuildTree(CFile* pFile, int delim, LONG& OrgSum)
	// --- In  : pFile :
	//			 delim : 
	//			 OrgSum
	// --- Out : OrgSum
	// --- Returns : 
	// --- Effect : Build index tree: divide file in chunks by using the delimiter.
	//				We also create chunks of strings that contain m_cMinMatchLen 
	//				or more equal bytes.
	{
	COXTreeNode* 	pTreeRoot;
	COXTreeNode* 	pNewNode;
	COXTreeNode* 	pEqualRunNode;
	int        	byte;
	BYTE		helpByte;
	int        	prevByte;
	LONG       	equalByteCnt;
	LONG       	curPos;
	LONG       	prevPos;
	LONG       	len;
	BYTE*     	pByte;

	ASSERT(m_pProgressBar != NULL);
	m_pProgressBar->Init(0L,pFile->GetLength(),TEXT("Pass 2 of 3:"));

	pTreeRoot = NULL;

	curPos = 0;
	prevPos = 0;
	do
		{
		if (curPos - prevPos > 0x3FF) 
			{
			if (!m_pProgressBar->Adjust(curPos))
				m_pProgressBar->Abort(TEXT("Aborting"));
			prevPos = curPos;
			}

		// Restore file position (because it is destroyed by CmpNode)
		pFile->Seek(curPos,CFile::begin);

		// Prepare new node
		pNewNode = NewTreeNode();

		len = 0;
		pNewNode->filPos = curPos;
		pByte = pNewNode->bytes;
		byte = -1;
		equalByteCnt = 0;
		do
			{
			prevByte = byte;
			if (pFile->Read(&helpByte, 1) == 1) 
				{
				byte = helpByte;
				if (byte == prevByte)
					{
					equalByteCnt++;
					}
				else
					{
					// No need to check for m_cMinEqualRunLen or more equal bytes here; 
					// if they were here, they will be added to the tree anyhow. This 
					// loop only executes at most m_cMinMatchLen times.
					equalByteCnt = 1;
					}
				OrgSum += byte;
				*(pByte++) = BYTE(byte);
				}
			else
				{
				byte = EOF;
				*(pByte++) = BYTE(delim);
				}

			len++;
			} while (len < m_cMinMatchLen && byte != delim && byte != EOF);

		while (byte != delim && byte != EOF)
			{
			prevByte = byte;
			if (pFile->Read(&helpByte, 1) == 1) 
				{
				byte = helpByte;
				if (byte == prevByte)
					{
					equalByteCnt++;
					}
				else
					{
					// Check for LONG runs of equal bytes, and add these to 
					// the tree also.
					if (equalByteCnt >= m_cMinEqualRunLen)
						{
						pEqualRunNode = NewTreeNode();
						// Buffered characters consists of m_cMinMatchLen equal bytes
						memset(pEqualRunNode->bytes,prevByte,m_cMinMatchLen);
						// Calculate position of start of run
						pEqualRunNode->filPos = curPos + len - equalByteCnt;
						AddTreeNode(&pTreeRoot,pFile,delim,pEqualRunNode);
						pFile->Seek(curPos+len+1,CFile::begin); // Restore file position
						}
					equalByteCnt = 1;
					}
				OrgSum += byte;
				}
			else
				byte = EOF;
			len++;
			}

		AddTreeNode(&pTreeRoot,pFile,delim,pNewNode);
		curPos += len;
		} while (byte != EOF);

	m_pProgressBar->Close();

	return(pTreeRoot);
	}

void COXBinDiffCalculator::ExtendMatch(LONG& OrgFilPos, CFile* pOrgFil,
		 LONG& DerivedFilPos, CFile* pDerivedFil, LONG& MatchLen)
	// --- In  : OrgFilPos : 
	//			 pOrgFil :
	//			 DerivedFilPos : 
	//			 pDerivedFil : 
	//			 MatchLen : 
	// --- Out : OrgFilPos : 
	//			 DerivedFilPos : 
	//			 MatchLen : 
	// --- Returns : 
	// --- Effect : Extend match in two directions, ignoring delimiters: 
	//				if there is a match of length n at position p and p', 
	//				it can be changed into a match of length n+m+q 
	//				at position p - m and p' - m
	//
	//        <  m   ><   n     ><  q  >
	//                p
	//  ...aaazzzzzzzzxxxxxxxxxxxyyyyyyyccccccccccccccccc    (pOrgFil)
	//  ...bbbzzzzzzzzxxxxxxxxxxxyyyyyyyddddddddddddddddd    (pDerivedFil)
	//                p'
	{
	BYTE buf1[m_cBufSiz];
	BYTE buf2[m_cBufSiz];
	int l;
	LONG step;
	BOOL isDone;
	BYTE* p1;
	BYTE* p2;
	LONG endPos1, endPos2;

	// First, try to read forward and extend match toward the end
	isDone = FALSE;
	endPos1 = OrgFilPos + MatchLen;
	endPos2 = DerivedFilPos + MatchLen;
	while (! isDone)
		{
		step = m_cBufSiz;
		pOrgFil->Seek(endPos1,CFile::begin);
		// ... Eventually shrink step if pOrgFil is too short
		step = (UINT)pOrgFil->Read(buf1,(UINT)step);

		pDerivedFil->Seek(endPos2,CFile::begin);
		// ... Eventually shrink step if derivedFil is too short
		step = (UINT)pDerivedFil->Read(buf2,(UINT)step);

		// ...step < m_cBufSiz if one of the files at eof: stop comparing
		isDone = (step < m_cBufSiz);

		// ... Prepare endPos1 and endPos2 for reading next buffer
		endPos1 += step;
		endPos2 += step;

		p1 = buf1;
		p2 = buf2;
		while (*p1 == *p2 && step > 0)
			{
			p1++;
			p2++;
			step--;
			MatchLen++;
			}

		// ... step > 0 if *p1 != *p2 found: stop comparing
		isDone = isDone || step > 0;
		}

	// Second, try to read backwards and extend the match towards the file start.
	// Stop extending if orgFilPos or derivedFilPos equal 0.
	isDone = FALSE;
	while (OrgFilPos > 0 && DerivedFilPos > 0 && ! isDone)
		{
		// Try to step m_cBufSiz bytes back. If orgFilPos or derivedFilPos is 
		// less than that, reduce the step size accordingly.
		step = m_cBufSiz;
		if (OrgFilPos < step)
			step = OrgFilPos;
		if (DerivedFilPos < step)
			step = DerivedFilPos;

		// ...Jump back 'step' bytes and read two buffers of 'step' bytes.
		(OrgFilPos) -= step;
		pOrgFil->Seek(OrgFilPos,CFile::begin);
		pOrgFil->Read(buf1,(UINT)step);

		DerivedFilPos -= step;
		pDerivedFil->Seek(DerivedFilPos,CFile::begin);
		pDerivedFil->Read(buf2,(UINT)step);

		// ... Put pointers at the end of the buffers 
		p1 = buf1 + step - 1;
		p2 = buf2 + step - 1;

		// ...Run backwards until a difference found or at start of buffer
		l = (int)step;
		while (*p1 == *p2 && l > 0)
			{
			p1--;
			p2--;
			l--;
			// Adjust matchLen for each matched byte.
			MatchLen++;
			}

		isDone = (l > 0);
	
		// Adjust orgFilPos and derivedFilPos: add length of unequal part of buffer
		OrgFilPos += l;
		DerivedFilPos += l;
		}
	}

void COXBinDiffCalculator::DeleteMatchBlocks(COXMatchBlock* pBlock)
	{
	COXMatchBlock* pMatchBlock = pBlock;
	COXMatchBlock* pMatchBlockNext;

	while(pMatchBlock != NULL)
		{
		pMatchBlockNext = pMatchBlock->pNxt;
		delete pMatchBlock;
		pMatchBlock = pMatchBlockNext;
		}
	}

COXBinDiffCalculator::COXMatchBlock* COXBinDiffCalculator::NewMatchBlock(void)
	// --- In  : 
	// --- Out : 
	// --- Returns : The new match block
	// --- Effect : Create a new match block or reuse one of the free list
	{
	COXMatchBlock* pMatchBlock;

	if (m_LstFreeMatchBlock == NULL)
		{
		pMatchBlock = new COXMatchBlock();
		}
	else
		{
		pMatchBlock = m_LstFreeMatchBlock;
		m_LstFreeMatchBlock = m_LstFreeMatchBlock->pNxt;
		}

	pMatchBlock->orgFilPos = 0L;
	pMatchBlock->len = 0L;
	pMatchBlock->derivedFilPos = 0L;
	pMatchBlock->pNxt = NULL;

	return(pMatchBlock);
	}

void COXBinDiffCalculator::FreeMatchBlock(COXBinDiffCalculator::COXMatchBlock* pMatchBlock)
	// --- In  : pMatchBlock : Block to release
	// --- Out : 
	// --- Returns : The new match block
	// --- Effect : Release a match block: put on the free list
	{
	pMatchBlock->pNxt = m_LstFreeMatchBlock;
	m_LstFreeMatchBlock = pMatchBlock;
	}
 
void COXBinDiffCalculator::AddMatch(COXBinDiffCalculator::COXTreeNode* pOrgTreeNode, 
			CFile* pOrgFil, COXBinDiffCalculator::COXTreeNode* pDerivedTreeNode, 
			CFile* pDerivedFil, LONG matchLen, COXBinDiffCalculator::COXMatchBlock** ppMatchLst)
	// --- In  : pOrgTreeNode : 
	//			 pOrgFil : 
	//			 pDerivedTreeNode : 
	//			 pDerivedFil : 
	//			 matchLen : 
	//			 ppMatchLst :
	// --- Out : 
	// --- Returns : 
	// --- Effect : Add new match between pOrgTreeNode and pDerivedTreeNode,
	//				with length matchlen. If the match is LONG enough 
	//				(after extending): add it to the list of matches. 
	//				The list of matches is kept in order of increasing
	//				starting position in derivedFil.
	//				If a new match is added that is completely part of 
	//				an existing match, it is dropped.
	//				If a new match is added that encloses one or more existing 
	//				matches, the enclosed matches are dropped, and the new one 
	//				is added.
	//				The resulting list will only contain matches with different 
	//				derivedFilPos values: if there would be two equal derivedFilPos 
	//				values, one of the two blocks would enclose the other and 
	//				would have been dropped.
	{
	LONG orgFilPos, derivedFilPos;
	LONG distance;
	COXMatchBlock* pMatchBlock;
	COXMatchBlock* pPrvMatchBlock;
	COXMatchBlock* pNxtMatchBlock;
	BOOL dropNewMatch;

	orgFilPos = pOrgTreeNode->filPos;
	derivedFilPos = pDerivedTreeNode->filPos;

	// Pass 1: check if there are matchblocks that enclose the new match
	// (relative to derivedFil), in a way that they are an expansion of this
	// new match block. This saves us expanding this block, because after
	// expansion, it would be the same as the overlapping block.
	// This is done by checking the distance between the positions for
	// orgFil and derivedFil: if the larger block and the smaller block have 
	// the same distance, and the smaller block is part of the larger 
	// one, the smaller will expand to be equal to the larger one.

	distance = orgFilPos - derivedFilPos;

	pMatchBlock = *ppMatchLst;
	dropNewMatch = FALSE;
	while (pMatchBlock != NULL 
		&& pMatchBlock->derivedFilPos <= derivedFilPos 
		&& ! dropNewMatch)
		{
		dropNewMatch =
			(
			// ...pMatchBlock->derivedFilPos <= derivedFilPos 
			//    && Already tested in while condition
			derivedFilPos <= pMatchBlock->derivedFilPos + pMatchBlock->len
			&&
			pMatchBlock->distance == distance
			);
		pMatchBlock = pMatchBlock->pNxt;
		}

	if (! dropNewMatch)
		{
		ExtendMatch(orgFilPos,pOrgFil,derivedFilPos,pDerivedFil,matchLen);

		if (matchLen >= m_cMinMatchLen)
			{
			// Pass 2: check if there are matchblocks that enclose the new match
			// (relative to derivedFil).
			pMatchBlock = *ppMatchLst;
			while (pMatchBlock != NULL 
				&& pMatchBlock->derivedFilPos <= derivedFilPos 
				&& ! dropNewMatch)
				{
				dropNewMatch =
					( 
					// pMatchBlock->derivedFilPos <= derivedFilPos 
					// &&   Already tested in while condition */
					derivedFilPos+matchLen 	<= 
					pMatchBlock->derivedFilPos + pMatchBlock->len 
					);
				pMatchBlock = pMatchBlock->pNxt;
				}

			if (! dropNewMatch)
				{
				// Pass 3: drop all matchblocks from list that are enclosed by the new one
				pMatchBlock = *ppMatchLst;
				pPrvMatchBlock = NULL;
				while (pMatchBlock != NULL)
					{
					pNxtMatchBlock = pMatchBlock->pNxt;
					//...  Check if pMatchBlock completely enclosed by new match
					if
						(
						derivedFilPos <= pMatchBlock->derivedFilPos
						&&
						pMatchBlock->derivedFilPos + pMatchBlock->len <= 
						derivedFilPos+matchLen
						)
						{
						// ...If completely enclosed: remove from list
						if (pPrvMatchBlock == NULL)
							{
							*ppMatchLst = pNxtMatchBlock;
							}
						else
							{
							pPrvMatchBlock->pNxt = pNxtMatchBlock;
							}
						FreeMatchBlock(pMatchBlock);
						}
					else
						{
						pPrvMatchBlock = pMatchBlock;
						}
					pMatchBlock = pNxtMatchBlock;
					}

				// Pass 4: Find location to add match to list; keep list sorted on
				// derivedFilPos.
				pNxtMatchBlock = *ppMatchLst;
				pPrvMatchBlock = NULL;
				while (pNxtMatchBlock != NULL 
					&& pNxtMatchBlock->derivedFilPos < derivedFilPos)
					{
					pPrvMatchBlock = pNxtMatchBlock;
					pNxtMatchBlock = pNxtMatchBlock->pNxt;
					}

				// Add new match
				pMatchBlock = NewMatchBlock();
				pMatchBlock->orgFilPos = orgFilPos;
				pMatchBlock->derivedFilPos = derivedFilPos;
				pMatchBlock->distance = distance;
				pMatchBlock->len = matchLen;
				pMatchBlock->pNxt = pNxtMatchBlock;
				if (pPrvMatchBlock == NULL)
					{
					*ppMatchLst = pMatchBlock;
					}
				else
					{
					pPrvMatchBlock->pNxt = pMatchBlock;
					}
				}
			}
		}
	}

void COXBinDiffCalculator::ShrinkMatchList(COXBinDiffCalculator::COXMatchBlock** ppMatchLst)
	// --- In  : ppMatchLst
	// --- Out : 
	// --- Returns : 
	// --- Effect : Clean up the list of matches: shrink overlapping matches
	//				and drop those that become too short
	{
	COXMatchBlock* pMatchBlock;
	COXMatchBlock* pPrvMatchBlock;
	COXMatchBlock* pNxtMatchBlock;
	LONG distance;

	pPrvMatchBlock = NULL;
	pMatchBlock = *ppMatchLst;
	while (pMatchBlock != NULL)
		{
		pNxtMatchBlock = pMatchBlock->pNxt;
		if (pNxtMatchBlock != NULL)
			{
			// ... distance is maximal length of pMatchBlock without overlap
			distance = pNxtMatchBlock->derivedFilPos - pMatchBlock->derivedFilPos;
			// ... Shrink block if too long
			if (distance < pMatchBlock->len)
				{
				pMatchBlock->len = distance;
				}
			}
		// Drop blocks that become too short.
		if (pMatchBlock->len < m_cMinMatchLen)
			{
			if (pPrvMatchBlock == NULL)
				{
				*ppMatchLst = pNxtMatchBlock;
				}
			else
				{
				pPrvMatchBlock->pNxt = pNxtMatchBlock;
				}
			FreeMatchBlock(pMatchBlock);
			}
		else
			{
			pPrvMatchBlock = pMatchBlock;
			}

		pMatchBlock = pNxtMatchBlock;
		}
	}

COXBinDiffCalculator::COXMatchBlock* COXBinDiffCalculator::MatchFiles(
		COXBinDiffCalculator::COXTreeNode* pOrgTreeRoot,CFile* pOrgFil,
		CFile* pDerivedFil, int delim, LONG& DerivedSum)
	// --- In  : pOrgTreeRoot : 
	//			 pOrgFil : 
	//			 pDerivedFil : 
	//			 delim : 
	//			 DerivedSum
	// --- Out : DerivedSum
	// --- Returns : The matched block
	// --- Effect : Compare chunks from file 2 with tree from file 1
	{
	COXTreeNode*   pOrgTreeNode;
	LONG         matchLen;
	COXMatchBlock* pMatchLst;
	int          byte;
	BYTE		 helpByte;
	int          prevByte;
	LONG         curPos;
	LONG         prevPos;
	COXTreeNode    treeNode;
	COXTreeNode    equalRunNode;
	LONG         len;
	LONG         equalByteCnt;
	BYTE*       pByte;

	ASSERT(m_pProgressBar != NULL);
	m_pProgressBar->Init(0L,pDerivedFil->GetLength(),TEXT("Pass 3 of 3:"));

	pMatchLst = NULL;

	curPos = 0;
	prevPos = 0;
	do
		{
		if (curPos - prevPos > 0x3FF)
			{
			if (!m_pProgressBar->Adjust(curPos))
				m_pProgressBar->Abort(TEXT("Aborting"));
			prevPos = curPos;
			}

		// Restore FILE position (destroyed by FindBestMatch below)
		pDerivedFil->Seek(curPos,CFile::begin);

		// Buffer some characters from the file.
		len = 0;
		treeNode.filPos = curPos;
		pByte = treeNode.bytes;
		byte = -1;
		equalByteCnt = 0;
		do
			{
			prevByte = byte;
			if (pDerivedFil->Read(&helpByte, 1) == 1) 
				{
				byte = helpByte;
				if (byte == prevByte)
					{
					equalByteCnt++;
					}
				else
					{
					// No need to check for m_cMinMatchLen or more equal bytes here; 
					// if they were here, they will be checked against the tree 
					// anyhow. This loop only executes at most m_cMinMatchLen times.
					equalByteCnt = 1;
					}
				DerivedSum += byte;
				*(pByte++) = BYTE(byte);
				}
			else
				{
				byte = EOF;
				*(pByte++) = BYTE(delim);
				}
			len++;
			} while (len < m_cMinMatchLen && byte != delim && byte != EOF);

		while (byte != delim && byte != EOF)
			{
			prevByte = byte;
			if (pDerivedFil->Read(&helpByte, 1) == 1) 
				{
				byte = helpByte;
				if (byte == prevByte)
					{
					equalByteCnt++;
					}
				else
					{
					// Check for LONG runs of equal bytes, and check these against 
					// the tree also.
					if (equalByteCnt >= m_cMinEqualRunLen)
						{
						// ... Buffered characters consists of m_cMinMatchLen equal bytes
						memset(equalRunNode.bytes,prevByte,m_cMinMatchLen);
						// ...Calculate position of start of run
						equalRunNode.filPos = curPos + len - equalByteCnt;
						// Search best match in original tree
						FindBestMatch(pOrgTreeRoot,&pOrgTreeNode,pOrgFil,
		  					&equalRunNode,pDerivedFil,
		  					delim,&matchLen);

						if (pOrgTreeNode != NULL) 
							{
							// Add match to list of matches
							AddMatch(pOrgTreeNode,pOrgFil, 
							&equalRunNode,pDerivedFil,
							matchLen,&pMatchLst);
							}
						pDerivedFil->Seek(curPos+len+1, CFile::begin); /* Restore file position */
						}
					// Reset equal byte count to 1.
					equalByteCnt = 1;
					}
				DerivedSum += byte;
				}
			else
				byte = EOF;
			len++;
			}
		curPos += len;

		// Search best match in original tree
		FindBestMatch(pOrgTreeRoot,&pOrgTreeNode,pOrgFil,
		&treeNode,pDerivedFil,
		delim,&matchLen);

		if (pOrgTreeNode != NULL) 
			{
			// Add match to list of matches
			AddMatch(pOrgTreeNode,pOrgFil, 
			&treeNode,pDerivedFil,
			matchLen,&pMatchLst);
			}

		} while (byte != EOF);

	// Remove overlapping matches
	ShrinkMatchList(&pMatchLst);

	m_pProgressBar->Close();

	return(pMatchLst);
	}

void COXBinDiffCalculator::DumpDiff(COXBinDiffCalculator::COXMatchBlock* pMatchLst, CFile* pDerivedFil, CFile* pDiffFil)
	// --- In  : pMatchLst : 
	//			 pDerivedFil : 
	//			 pDiffFil :
	// --- Out : 
	// --- Returns : 
	// --- Effect : Write diff file
	{
	COXMatchBlock* pMatchBlock;
	LONG len, pos;
	LONG blockPos;
	LONG writeLen;
	LONG blockLen;
	LONG codeLen;
	LONG filSiz;
	LONG nextPos;
	BYTE byte;

	filSiz = pDerivedFil->GetLength();

	// Descend match block list. Resulting FILE is a series of matches and
	// non-matches between original FILE and derived FILE.
	pMatchBlock = pMatchLst;
	len = filSiz;
	pos = 0;

	// Repeat until all bytes of derivedFil have been checked
	while (len > 0)
		{
		// Get next matching position from match block. If there is none,
		// set nextPos beyond eof on derived file.
		// If there are unmatched bytes between the last position written
		// and the next position, write them to the diff file.
		// Possibly there are no unmatched bytes (nextPos == pos), in case
		// of consecutive match blocks.
		nextPos = pMatchBlock != NULL ? pMatchBlock->derivedFilPos : filSiz;
		if (nextPos > pos)
			{
			// There are unmatched bytes: write one or more block of unmatched bytes 
			// from derivedFil
			pDerivedFil->Seek(pos,CFile::begin);
			writeLen = nextPos - pos;
			while (writeLen > 0)
				{
				// If remaining block is small, use tag for small 
				// blocks (1 tag/length byte)
				if (writeLen <= m_cSmallSize)
					{
					blockLen = writeLen;
					codeLen = blockLen - 1; /* Encode length 1-m_cSmallSize by subtr. 1 */
					// ... codeLen: 4 bit value 
					// ... bit 3-0 | Tag 
					byte = BYTE((codeLen <<  4) | m_cTagSmallDiff);
					pDiffFil->Write(&byte, 1);
					}
				// If remaining block is medium size use tag for 
				// medium blocks (2 tag/length bytes)
				else if (writeLen <= m_cMediumSize)
					{
					blockLen = writeLen;
					// ... Encode length m_cSmallSize+1 - m_cMediumSize by subtr. m_cSmallSize+1
					codeLen = blockLen - m_cSmallSize - 1;
					// ... codeLen: 12 bit value
					// ... bit 11-8 | Tag
					byte = BYTE(((codeLen >>  4) & 0xF0) | m_cTagMediumDiff);
					pDiffFil->Write(&byte, 1);
					// ... bit 7-0 
					byte = BYTE((codeLen      ) & 0xFF);
					pDiffFil->Write(&byte, 1);
					}
				else
					{
					// If remaining block is large: write a large block,
					// and then re-check the remaining length
					if (writeLen > m_cLargeSize)
						{
						blockLen = m_cLargeSize;
						}
					else
						{
						blockLen = writeLen;
						}
					// ... Encode length m_cMediumSize+1 - m_cLargeSize by subtracting m_cMediumSize+1
					codeLen = blockLen - m_cMediumSize - 1;
					// ... codeLen: 20 bit value
					// ... bit 19-16 | Tag
					byte = BYTE(((codeLen >> 12) & 0xF0) | m_cTagLargeDiff);
					pDiffFil->Write(&byte, 1);
					// ... bit 15-8
					byte = BYTE((codeLen >>  8) & 0xFF);
					pDiffFil->Write(&byte, 1);
					// ... bit 7-0 
					byte = BYTE((codeLen      ) & 0xFF);
					pDiffFil->Write(&byte, 1);
					}

				writeLen -= blockLen;
				len -= blockLen;

				while (blockLen > 0)
					{
					pDerivedFil->Read(&byte, 1);
					pDiffFil->Write(&byte, 1);
					blockLen--;
					}
				}
			pos = nextPos;
			}

		// Write block of matching bytes: encode them as a count and a file position
		// in the original file.
		if (pMatchBlock != NULL)
			{
			blockPos = pMatchBlock->orgFilPos;
			writeLen = pMatchBlock->len;
			while (writeLen > 0)
				{
				if (writeLen <= m_cSmallSize)
					{
					blockLen = writeLen;
					codeLen = blockLen - 1;
					if (blockPos <= m_cNearDistance)
						{
						// ... codeLen: 4 bit value 
						// ... bit 3-0 | Tag 
						byte = BYTE((codeLen <<  4) | m_cTagSmallNearCopy);
						pDiffFil->Write(&byte, 1);

							// ... blockPos: 16 bit value 
						WriteLongNBytes(blockPos,pDiffFil,2);
						}
					else if (blockPos <= m_cDistantDistance)
						{
						// ... codeLen: 4 bit value 
						// ... bit 3-0 | Tag 
						byte = BYTE((codeLen <<  4) | m_cTagSmallDistantCopy);
						pDiffFil->Write(&byte, 1);

						// ... blockPos: 24 bit value 
						WriteLongNBytes(blockPos,pDiffFil,3);
						}
					else
						{
						// ... codeLen: 4 bit value 
						// ... bit 3-0 | Tag 
						byte = BYTE((codeLen <<  4) | m_cTagSmallFarCopy);
						pDiffFil->Write(&byte, 1);

						// ... blockPos: 32 bit value 
						WriteLongNBytes(blockPos,pDiffFil,4);
						}
					}
				else if (writeLen <= m_cMediumSize)
					{
					blockLen = writeLen;
					codeLen = blockLen - m_cSmallSize - 1;
					if (blockPos <= m_cNearDistance)
						{
						// ... codeLen: 12 bit value
						// ... bit 11-8 | Tag 
						byte = BYTE(((codeLen >>  4) & 0xF0) | m_cTagMediumNearCopy);
						pDiffFil->Write(&byte, 1);
						// ... bit 7-0
						byte = BYTE((codeLen) & 0xFF);
						pDiffFil->Write(&byte, 1);

						// ... blockPos: 16 bit value
						WriteLongNBytes(blockPos,pDiffFil,2);
						}
					else if (blockPos <= m_cDistantDistance)
						{
						// ... codeLen: 12 bit value 
						// ... bit 11-8 | Tag 
						byte = BYTE(((codeLen >>  4) & 0xF0) |m_cTagMediumDistantCopy);
						pDiffFil->Write(&byte, 1);
						// ... bit 7-0 
						byte = BYTE((codeLen) & 0xFF);
						pDiffFil->Write(&byte, 1);

						// ... blockPos: 24 bit value 
						WriteLongNBytes(blockPos,pDiffFil,3);
						}
					else
						{
						// ... codeLen: 12 bit value 
						// ... bit 11-8 | Tag 
						byte = BYTE(((codeLen >>  4) & 0xF0) | m_cTagMediumFarCopy);
						pDiffFil->Write(&byte, 1);
						// ... bit 7-0 
						byte = BYTE((codeLen) & 0xFF);
						pDiffFil->Write(&byte, 1);

						// ... blockPos: 32 bit value 
						WriteLongNBytes(blockPos,pDiffFil,4);
						}
					}
				else
					{
					if (writeLen > m_cLargeSize)
						{
						blockLen = m_cLargeSize;
						}
					else
						{
						blockLen = writeLen;
						}
					codeLen = blockLen - m_cMediumSize - 1;
					if (blockPos <= m_cNearDistance)
						{
						/* codeLen: 20 bit value */
						/* bit 19-16 | Tag */
						byte = BYTE(((codeLen >> 12) & 0xF0) | m_cTagLargeNearCopy);
						pDiffFil->Write(&byte, 1);
						/* bit 15-8 */
						byte = BYTE((codeLen >>  8) & 0xFF);
						pDiffFil->Write(&byte, 1);
						/* bit 7-0 */
						byte = BYTE((codeLen) & 0xFF);
						pDiffFil->Write(&byte, 1);

						/* blockPos: 16 bit value */
						WriteLongNBytes(blockPos,pDiffFil,2);
						}
					else if (blockPos <= m_cDistantDistance)
						{
						/* codeLen: 20 bit value */
						/* bit 19-16 | Tag */
						byte = BYTE(((codeLen >> 12) & 0xF0) | m_cTagLargeDistantCopy);
						pDiffFil->Write(&byte, 1);
						/* bit 15-8 */
						byte = BYTE((codeLen >>  8) & 0xFF);
						pDiffFil->Write(&byte, 1);
						/* bit 7-0 */
						byte = BYTE((codeLen) & 0xFF);
						pDiffFil->Write(&byte, 1);

						/* blockPos: 24 bit value */
						WriteLongNBytes(blockPos,pDiffFil,3);
						}
					else
						{
						/* codeLen: 20 bit value */
						/* bit 19-16 | Tag */
						byte = BYTE(((codeLen >> 12) & 0xF0) | m_cTagLargeFarCopy);
						pDiffFil->Write(&byte, 1);
						/* bit 15-8 */
						byte = BYTE((codeLen >>  8) & 0xFF);
						pDiffFil->Write(&byte, 1);
						/* bit 7-0  */
						byte = BYTE((codeLen) & 0xFF);
						pDiffFil->Write(&byte, 1);

						/* blockPos: 32 bit value */
						WriteLongNBytes(blockPos,pDiffFil,4);
						}
					}
				writeLen -= blockLen;

				// ... A bug that was present in the previous version (if writeLen > m_cLargeSize)
				//     is corrected by the following line
				blockPos += blockLen;

				len -= blockLen;
				pos += blockLen;
				}
			pMatchBlock = pMatchBlock->pNxt;
			}
		}
	pDiffFil->Write(&m_cTagEOF, 1);
	}

#endif // ! BDEXTR

// private:
// ==========================================================================
