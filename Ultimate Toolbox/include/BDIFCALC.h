// ==========================================================================
// 					Class Specification : COXBinDiffCalculator
// ==========================================================================

// Header file : bdifcalc.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CObject

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO 	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class can be used to compute the binary differnce between two files
//   (the original and the updated file)
//   A third file that contains the difference is generated then.
//   	difference = updated - original
// 	Using the difference file and the original one, the updated file can be
//   computed
//		updated = original + difference
//	This class can be used by supplying the names of the files directly
//  An alternative use is that three CFile-derived objects are created and
//   opened and than passed as parameter.  This permits other media besides
//   disk access (e.g. CMemFile for in-memory computation)

// Remark:
//	The progress of the computation is routed to an object of a COXDiffProgress
//   derived object.  The default implementation writes to the console
//	 using cprintf.  You can derive a class from COXDiffProgress and override
//	 the virtual functions Init(), Adjust(), Abort() and Close().
//	The new progreesbar will be used after a call to ReplaceProgressBar()

// Prerequisites (necessary conditions):
//		***

/////////////////////////////////////////////////////////////////////////////

#ifndef __BDIFCALC_H__
#define __BDIFCALC_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

// By #defining BDEXTR as 1, a reduced, decode-only version is created
// If BDEXTR is not defined or 0, a complete version is created.
#ifndef BDEXTR
#define BDEXTR      0
#endif

class COXDiffProgress;
class COXDiffFileHeader;

class OX_CLASS_DECL COXBinDiffCalculator : public CObject
{
DECLARE_DYNAMIC(COXBinDiffCalculator)
// Data members -------------------------------------------------------------
public:
	static const double m_cMinMeanChunkLen;
	static const double m_cMaxMeanChunkLen;
	static const double m_cBigChunkLen;
	static const TCHAR* m_cFileHeader;
	static const BOOL m_cDropEOL;
	static const DWORD m_cBufSiz;
	static const WORD m_cMinMatchLen;
	static const WORD m_cMinEqualRunLen;

	static const BYTE m_cTagSmallDiff;
	static const BYTE m_cTagMediumDiff;
	static const BYTE m_cTagLargeDiff;
	static const BYTE m_cTagSmallNearCopy;
	static const BYTE m_cTagMediumNearCopy;
	static const BYTE m_cTagLargeNearCopy;
	static const BYTE m_cTagSmallDistantCopy;
	static const BYTE m_cTagMediumDistantCopy;
	static const BYTE m_cTagLargeDistantCopy;
	static const BYTE m_cTagSmallFarCopy;
	static const BYTE m_cTagMediumFarCopy;
	static const BYTE m_cTagLargeFarCopy;
	static const BYTE m_cTagEOF;

	static const DWORD m_cSmallSize;
	static const DWORD m_cMediumSize;
	static const DWORD m_cLargeSize;
	static const DWORD m_cNearDistance;
	static const DWORD m_cDistantDistance;
	static const DWORD m_cMaxStrLen;

protected:
#if ! BDEXTR
// The following structures are not needed in extraction program */

// Tree node: has 3 pointers: a pointer to lesser, and greater or equal nodes
// The third pointer is a linked list pointer: the root node of the tree is also
// the head of the linked list. The linked list is not built in a special order:
// nodes are added to it in order of occurence. The tree is a binary tree.

struct COXTreeNode
 	{
  	LONG		filPos;
  	BYTE*		bytes;
  	COXTreeNode*	pGE;  /* Greater or equal */
  	COXTreeNode*	pLT;  /* Less than */
	COXTreeNode() { bytes = new BYTE[m_cMinMatchLen]; }
	~COXTreeNode() { delete[] bytes; }
 	};

// Match block structure: for each match found between the two files, we
// encode the positions in the two files and the length of the match.

struct COXMatchBlock
	{
	LONG			len;
	LONG			orgFilPos;
	LONG			derivedFilPos;
	LONG			distance; /* = orgFilPos - derivedFilPos */
	COXMatchBlock*	pNxt;
	};

struct COXByteAttribs
	{
	DWORD	 sum;
	double sumSquares;
	double mean;
	double stdDev;

	// ... Last file position where a byte was encountered, for all bytes. 
	//     Initialized to -1 ('before' the first FILE position).
	LONG lastPos;

	// ... Count of occurences
	LONG cnt;
	};

	COXTreeNode* 		m_LstFreeTreeNode;
	COXMatchBlock* 		m_LstFreeMatchBlock;

#endif /* ! BDEXTR */

	COXDiffProgress*	m_pProgressBar;

private:
	
// Member functions ---------------------------------------------------------
public:
	COXBinDiffCalculator();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state

#if ! BDEXTR
	void SubtractFiles(LPCTSTR orgFilNam, LPCTSTR derivedFilNam, LPCTSTR diffFilNam,
		COXDiffFileHeader* pHeader = NULL);
	// --- In  : orgFilNam : Full path of the original file
	//			 derivedFilNam : Full path of the updated file
	//			 diffFilNam : Full path of the difference file
	// --- Out : 
	// --- Returns :
	// --- Effect : Calculates the binary differences between the 
	//				original and updated file and writes it 
	//				in the difference file
#endif // ! BDEXTR

	void AddFiles(LPCTSTR orgFilNam, LPCTSTR derivedFilNam, LPCTSTR diffFilNam,
		COXDiffFileHeader* pHeader = NULL);
	// --- In  : orgFilNam : Full path of the original file
	//			 derivedFilNam : Full path of the updated file
	//			 diffFilNam : Full path of the difference file
	// --- Out : 
	// --- Returns :
	// --- Effect : Applies the binary difference to the original file
	//				writes the updated file

#if ! BDEXTR
	virtual void SubtractFiles(CFile* pOrgFil, CFile* pDerivedFil, CFile* pDiffFil,
		COXDiffFileHeader* pHeader = NULL);
	// --- In  : orgFilNam : Pointer to OPENED file (Read)
	//			 derivedFilNam : Pointer to OPENED file (Read)
	//			 diffFilNam : Pointer to OPENED file (Create/Read/Write)
	// --- Out : 
	// --- Returns :
	// --- Effect : Calculates the binary differences between the 
	//				original and updated file and writes it 
	//				in the difference file
#endif // ! BDEXTR

	virtual void AddFiles(CFile* pOrgFil, CFile* pDerivedFil, CFile* pDiffFil,
		COXDiffFileHeader* pHeader = NULL);
	// --- In  : orgFilNam : Pointer to OPENED file (Read)
	//			 derivedFilNam : Pointer to OPENED file (Create/Read/Write)
	//			 diffFilNam : Pointer to OPENED file (Read)
	// --- Out : 
	// --- Returns :
	// --- Effect : Applies the binary difference to the original file
	//				writes the updated file

	void ReplaceProgressBar(COXDiffProgress* pProgressBar);
	// --- In  : pProgressBar : The new progress bar to use
	// --- Out : 
	// --- Returns :
	// --- Effect : Replaces the standard progress bar by 
	//				 another (COXDiffProgress derived)
	//				This will be automatically deleted when
	//				 this COXBinDiffCalculator is destructed

#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

	virtual ~COXBinDiffCalculator();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object

protected:
	void CopyFileChars(LONG count, CFile* pInFile, CFile* pOutFile, LONG& sum);
	LONG ReadLongNBytes(CFile* pFile,int n);
#if ! BDEXTR
	void WriteLongNBytes(LONG x, CFile* pFile,int n);
	void ScanFile(CFile* pFile, COXByteAttribs* byteTable);
	int FindDelimiter(CFile* pFile, double minMeanChunkLen, double maxMeanChunkLen);
	void DeleteTreeNode(COXTreeNode* pTreeNode);
	COXTreeNode* NewTreeNode();
	void FreeTreeNode(COXTreeNode* pTreeNode);
	int CmpNode(COXTreeNode* pNode1, CFile* pFil1, COXTreeNode* pNode2,
		CFile* pFil2, int delim, LONG* pEqualLen);
	void FindBestMatch(COXTreeNode*  pOrgTreeRoot,
		COXTreeNode** ppOrgTreeNode, CFile* pOrgFil, COXTreeNode*  pDerivedTreeNode,
        CFile* pDerivedFil, int delim, LONG* pMatchLen);
	void AddTreeNode(COXTreeNode** ppTreeRoot, CFile* pFile, 
		int delim, COXTreeNode* pNewNode);
	COXTreeNode* BuildTree(CFile* pFile, int delim, LONG& OrgSum);
	void ExtendMatch(LONG& OrgFilPos, CFile* pOrgFil,
		 LONG& DerivedFilPos, CFile* pDerivedFil, LONG& MatchLen);
	void DeleteMatchBlocks(COXMatchBlock* pBlock);
	COXMatchBlock* NewMatchBlock(void);
	void FreeMatchBlock(COXBinDiffCalculator::COXMatchBlock* pMatchBlock);
	void AddMatch(COXTreeNode* pOrgTreeNode, 
			CFile* pOrgFil, COXTreeNode* pDerivedTreeNode, 
			CFile* pDerivedFil, LONG matchLen, COXMatchBlock** ppMatchLst);
	void ShrinkMatchList(COXMatchBlock** ppMatchLst);
	COXMatchBlock* MatchFiles(COXTreeNode* pOrgTreeRoot,CFile* pOrgFil,
		CFile* pDerivedFil, int delim, LONG& DerivedSum);
	void DumpDiff(COXMatchBlock* pMatchLst, CFile* pDerivedFil, CFile* pDiffFil);

#endif // ! BDEXTR

private:
                   
};

#endif	// __BDIFCALC_H__
// ==========================================================================
