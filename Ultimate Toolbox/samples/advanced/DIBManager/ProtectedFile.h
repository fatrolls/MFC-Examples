/////////////////////////////////////////////////////////////////////////////
// ProtectedFile.h
//
// CProtectedFile class definition
//

// comment this definition if we are not going yo supply 
// encryption classes
// if we are going to use encryption make sure you include 
// crypfile.cpp and mdccrypt.cpp files into SourceFiles/UTSourse/ section


class CProtectedFile : public CObject
{
    DECLARE_SERIAL(CProtectedFile)

public:
	// mem file that we associate with 
	CMemFile m_file;
protected:
	// signature that we use in header to check the correctness of opening file
	DWORD m_dwSignature;

public:
	BOOL Open(CFile* pFile);
	BOOL Save(CFile* pFile);
	BOOL CopyFile(CFile* pDestFile, CFile* pSourceFile, BOOL bShowProgress=FALSE);
	BOOL CopyFileToArchive(CArchive& ar, CFile* pSourceFile, BOOL bShowProgress=FALSE);
	BOOL CopyArchiveToFile(CArchive& ar, CFile* pDestFile, BOOL bShowProgress=FALSE);

	void Serialize(CArchive& ar);

protected:
	BOOL SetProtection(CFile* pFile);
	BOOL RemoveProtection();

public:
	CProtectedFile() { m_dwSignature=0x00010001; }
	~CProtectedFile() {}
};