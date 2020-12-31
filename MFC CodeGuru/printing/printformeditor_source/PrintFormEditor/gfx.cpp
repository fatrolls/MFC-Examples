#include "stdafx.h"

#include "gfx.h"



bool RectInRect(CRect &rc1, CRect &rc2)
{
	if (rc1.left>rc2.right || rc1.right<rc2.left || rc1.top>rc2.bottom || rc1.bottom<rc2.top) return false;
	return true;
}


void GfxRectPerDouble(CRect &rc, const double &db)
{
	rc.top = (int)double(rc.top*db);
	rc.bottom = (int)double(rc.bottom*db);
	rc.left = (int)double(rc.left*db);
	rc.right = (int)double(rc.right*db);
}

bool GfxPumpMessage()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
		if (!AfxGetThread()->PumpMessage())
			return false;
	return true;
}

bool GfxParseBiText(CString &cs1, CString &cs2, const int id)
{
	CString cs;
	try 
	{
		cs.LoadString(id);
	}
	catch(CMemoryException &e)
	{
		e.Delete();
		return false;
	}
	int p = cs.Find('\n');
	if (p > 0)
	{
		cs1 = cs.Left(p);
		cs2 = cs.Right(cs.GetLength() - p - 1);
	}
	return true;
}

void GfxGlobalFree(HGLOBAL hGlobal)
{
	if (hGlobal == NULL)
		return;
	// avoid bogus warning error messages from various debugging tools
	ASSERT(GlobalFlags(hGlobal) != GMEM_INVALID_HANDLE);
	UINT nCount = GlobalFlags(hGlobal) & GMEM_LOCKCOUNT;
	while (nCount--) GlobalUnlock(hGlobal);
	// finally, really free the handle
	GlobalFree(hGlobal);
}

void GfxFormatKm(CString &cs, long lKm)
{
	long lMt = lKm%1000;
	lKm /= 1000;
	cs.Format("%d+%03d", lKm, lMt);
}

CString Format_CFileException(CFileException * e)
{
	CString csErr;
	csErr.Format("Errore nel file %s: ", e->m_strFileName);

	if (e->m_cause == CFileException::none)
		csErr += "No error occurred.";
	if (e->m_cause == CFileException::generic)
		csErr += "An unspecified error occurred.";
	if (e->m_cause == CFileException::fileNotFound)
		csErr += "The file could not be located.";
	if (e->m_cause == CFileException::badPath)
		csErr += "All or part of the path is invalid.";
	if (e->m_cause == CFileException::tooManyOpenFiles)
		csErr += "The permitted number of open files was exceeded.";
	if (e->m_cause == CFileException::accessDenied)
		csErr += "The file could not be accessed.";
	if (e->m_cause == CFileException::invalidFile)
		csErr += "There was an attempt to use an invalid file handle.";
	if (e->m_cause == CFileException::removeCurrentDir)
		csErr += "The current working directory cannot be removed.";
	if (e->m_cause == CFileException::directoryFull)
		csErr += "There are no more directory entries.";
	if (e->m_cause == CFileException::badSeek)
		csErr += "There was an error trying to set the file pointer.";
	if (e->m_cause == CFileException::hardIO)
		csErr += "There was a hardware error.";
	if (e->m_cause == CFileException::sharingViolation)
		csErr += "SHARE.EXE was not loaded, or a shared region was locked.";
	if (e->m_cause == CFileException::lockViolation)
		csErr += "There was an attempt to lock a region that was already locked.";
	if (e->m_cause == CFileException::diskFull)
		csErr += "The disk is full.";
	if (e->m_cause == CFileException::endOfFile)
		csErr += "The end of file was reached.";

	return csErr;
}

int GfxGetColumnSubItem(CListCtrl * pList, const int iSub)
{
	LV_COLUMN lv;
	lv.mask = LVCF_SUBITEM;
	pList->GetColumn(iSub, &lv);
	return lv.iSubItem;
}
