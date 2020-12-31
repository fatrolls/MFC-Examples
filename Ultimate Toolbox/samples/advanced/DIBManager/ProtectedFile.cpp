#include "stdafx.h"
#include "ProtectedFile.h"

#include "DibManager.h"
#include "MainFrm.h"

#include "OXcmpfl.h"

IMPLEMENT_SERIAL(CProtectedFile, CObject, 1)

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

BOOL CProtectedFile::Open(CFile* pFile)
{
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();

	// to make sure that we are going to work with correct protected file
	// we have to check some additional info that we add to every protected file
	pFile->SeekToBegin();
	CArchive ar(pFile, CArchive::load);
	TRY
	{
		// if we threw an exception then 
		// header of file is of wrong format 
		Serialize(ar);
	}
	CATCH(CArchiveException,e)
	{
		pApp->ErrorNotify(_T("Unknown file format!"));
		return FALSE;
	}
	END_CATCH
	ar.Close();

	// if header is correct then run decryption
	if(RemoveProtection())
	{
		pFile->SetLength(0);
		m_file.SeekToBegin();
		CopyFile(pFile,&m_file);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CProtectedFile::Save(CFile* pFile)
{
	// encrypt file
	if(!SetProtection(pFile))
		return FALSE;

	// set header info to identify file as encrypted when open
	pFile->SetLength(0);
	CArchive ar(pFile, CArchive::store);
	TRY
	{
		Serialize(ar);
	}
	CATCH(CArchiveException,e)
	{
		return FALSE;
	}
	END_CATCH
	ar.Close();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// serialization

void CProtectedFile::Serialize(CArchive& ar)
{
    // Only CObject-derived objects and six data-type
    // primitives are serializable. However, you
    // can cast any data type to a serializable data type,
    // and then you can serialize your data. The serializable
    // data types are

    // BYTE:    8 bits unsigned
    // WORD:    16 bits unsigned
    // LONG:    32 bits unsigned
    // DWORD:   32 bits unsigned
    // float    32 bits
    // double   64 bits, IEEE standard
    
	// we use some control sum to check whether 
	// opened file is encrypted or not
	if (ar.IsStoring())
	{
		// TODO: add storing code here        
		ar << m_dwSignature;

		WORD randNumber;
		WORD m_headLength=(WORD)(rand()%10+5);
		ar << m_headLength;
		WORD m_headMultiplier=(WORD)(rand()%4+1);
		ar << m_headMultiplier;
		DWORD m_headSum=0;
        for(WORD i=0;i<m_headLength;i++)
        {
        	randNumber=(WORD)(rand()%32767);
			ar << randNumber;
			m_headSum+=randNumber*m_headMultiplier;
        }
		ar << m_headSum;

		m_file.SeekToBegin();
		if(!CopyFileToArchive(ar,&m_file))
		{
			AfxThrowArchiveException(CArchiveException::badIndex);
		}
	}
	else
	{
		// TODO: add loading code here
		// check if the data is correct header of encrypted file
		DWORD signature;
		ar >> signature;
		if(signature!=m_dwSignature)
		{ 
			AfxThrowArchiveException(CArchiveException::badIndex);
		}

		WORD randNumber,m_headLength,m_headMultiplier;
		DWORD headSum=0, m_headSum;
		ar >> m_headLength;
		ar >> m_headMultiplier;
        for(WORD i=0;i<m_headLength;i++)
        {
			ar >> randNumber;
			headSum+=randNumber*m_headMultiplier;
        }
		ar >> m_headSum;
		if(m_headSum!=headSum)
		{ 
			AfxThrowArchiveException(CArchiveException::badIndex);
		}

		m_file.SeekToBegin();
		if(!CopyArchiveToFile(ar,&m_file))
		{
			AfxThrowArchiveException(CArchiveException::badIndex);
		}
	}
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

BOOL CProtectedFile::SetProtection(CFile* pFile)
{
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();

	pFile->SeekToBegin();

	// we use either compression and encryption
	// or just copression to protect file
	// by means of delegatin rights to read and write operations
#ifdef _UT_DIBMANAGER_ENCRYPTION
	COXCryptFile EncryptFile(40);
	COXCompressedFile CompressFile;
	EncryptFile.DelegateOpen(&m_file,CFile::modeReadWrite);
	CompressFile.DelegateOpen(&EncryptFile,CFile::modeWrite);
#else
	COXCompressedFile CompressFile;
	CompressFile.DelegateOpen(&m_file,CFile::modeWrite);
#endif
		
	if(!CopyFile(&CompressFile,pFile,TRUE))
	{
		pApp->ErrorNotify(_T("Cannot protect image!"));
		return FALSE;
	}
	return TRUE;
}

BOOL CProtectedFile::RemoveProtection()
{
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();

	//////////////
	// we can try to open file encrypted using 
	// different version of the program 
	// in that case we are not going to read file
	//////////
	// To enable encryption and compression transformations, setup 
	// the encryptfile and compress file with delegation opens and Write state
#ifdef _UT_DIBMANAGER_ENCRYPTION
	COXCompressedFile CompressFile;
	COXCryptFile EncryptFile(40);
	CompressFile.DelegateOpen(&EncryptFile, CFile::modeRead);
	EncryptFile.DelegateOpen(&m_file, CFile::modeRead);
#else
	COXCompressedFile CompressFile;
	CompressFile.DelegateOpen(&m_file, CFile::modeRead);
#endif
		
	CMemFile tmpFile;
	if(!CopyFile(&tmpFile,&CompressFile,TRUE))
	{
		pApp->ErrorNotify(_T("Failed to read file!"));
		return FALSE;
	}

	m_file.SetLength(0);
	tmpFile.SeekToBegin();
	CopyFile(&m_file,&tmpFile);

	return TRUE;
}

BOOL CProtectedFile::CopyFile(CFile* pDestFile, CFile* pSourceFile, BOOL bShowProgress) 
{
	// use buffers
	const int nBufferLength = 2048;
	BYTE pBuffer[nBufferLength + 1];
	int nLengthRead(0);
	BOOL bSuccess = TRUE;

	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	CMainFrame* pMainFrame=(CMainFrame*)pApp->m_pMainWnd;

	if(bShowProgress)
	{
		// initialize progress object to show progress of protecting image
		bShowProgress=pMainFrame->
			IniProgress((WORD)(pSourceFile->GetLength()/nBufferLength),10);
	}

	TRY
	{
		do
		{
			nLengthRead = pSourceFile->Read(pBuffer, nBufferLength);
			pDestFile->Write(pBuffer, nLengthRead);

			if(bShowProgress)
			{
				// after every copy operation call Progress object iterator
				pMainFrame->ShowProgress();
			}
		}
		while (nLengthRead == nBufferLength);	// So while not EOF
	}
	CATCH(CFileException, pxFile)
	{
		TRACE(_T("CDIBManagerDoc::CopyFile : Catching FileException (%XH)\n"),
			pxFile->m_cause);
		bSuccess = FALSE;
	}
	END_CATCH      

	if(bShowProgress)
	{
		pMainFrame->ResetProgress();
	}

	return bSuccess;
}

BOOL CProtectedFile::CopyFileToArchive(CArchive& ar, CFile* pSourceFile, BOOL bShowProgress) 
{
	const int nBufferLength = 2048;
	BYTE pBuffer[nBufferLength + 1];
	int nLengthRead(0);
	BOOL bSuccess = TRUE;

	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	CMainFrame* pMainFrame=(CMainFrame*)pApp->m_pMainWnd;

	if(bShowProgress)
	{
		// initialize progress object to show progress of protecting image
		bShowProgress=pMainFrame->
			IniProgress((WORD)(pSourceFile->GetLength()/nBufferLength),10);
	}

	TRY
	{
		do
		{
			nLengthRead = pSourceFile->Read(pBuffer, nBufferLength);
			ar.Write(pBuffer, nLengthRead);

			if(bShowProgress)
			{
				// after every copy operation call Progress object iterator
				pMainFrame->ShowProgress();
			}
		}
		while (nLengthRead == nBufferLength);	// So while not EOF
	}
	CATCH(CFileException,pxFile)
	{
		TRACE(_T("CDIBManagerDoc::CopyFileToArchive : Catching FileException (%XH)\n"),
			pxFile->m_cause);
		return FALSE;
	}
	END_CATCH      

	if(bShowProgress)
	{
		pMainFrame->ResetProgress();
	}

	return bSuccess;
}

BOOL CProtectedFile::CopyArchiveToFile(CArchive& ar, CFile* pDestFile, BOOL bShowProgress) 
{
	const int nBufferLength = 2048;
	BYTE pBuffer[nBufferLength + 1];
	int nLengthRead(0);
	BOOL bSuccess = TRUE;
	
	CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
	CMainFrame* pMainFrame=(CMainFrame*)pApp->m_pMainWnd;

	if(bShowProgress)
	{
		// initialize progress object to show progress of protecting image
		bShowProgress=pMainFrame->
			IniProgress((WORD)(ar.GetFile()->GetLength()/nBufferLength),10);
	}

	TRY
	{
		do
		{
			nLengthRead = ar.Read(pBuffer, nBufferLength);
			pDestFile->Write(pBuffer, nLengthRead);

			if(bShowProgress)
			{
				// after every copy operation call Progress object iterator
				pMainFrame->ShowProgress();
			}
		}
		while (nLengthRead == nBufferLength);	// So while not EOF
	}
	CATCH(CFileException,pxFile)
	{
		TRACE(_T("CDIBManagerDoc::CopyArchiveToFile : Catching FileException (%XH)\n"),
			pxFile->m_cause);
		return FALSE;
	}
	END_CATCH      

	if(bShowProgress)
	{
		pMainFrame->ResetProgress();
	}

	return bSuccess;
}

