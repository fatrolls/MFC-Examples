#include "stdafx.h"
#include "DropFiles.h"

CDropFiles::CDropFiles()
{
	m_pBuff = NULL;
	m_nBuffSize = 0;
}
CDropFiles::~CDropFiles()
{
	delete m_pBuff;
}
void CDropFiles::AddFile(const CString &sFile)
{
	m_aFiles.Add(sFile);
}
void CDropFiles::CreateBuffer()
{
	// CreateBuffer must be called once, when all Files are added!!!
	ASSERT(m_pBuff == NULL);
	ASSERT(m_nBuffSize == 0);

	for(int i=0;i<m_aFiles.GetSize();i++){
		m_nBuffSize += m_aFiles[i].GetLength()+1;
	}

	m_nBuffSize += sizeof(DROPFILES)+2;
	m_nBuffSize = (m_nBuffSize/32 + 1)*32;

	int nBuffSize = 0;

	m_pBuff = new char[m_nBuffSize];

	ZeroMemory(m_pBuff, m_nBuffSize);
	((DROPFILES*)m_pBuff)->pFiles = sizeof(DROPFILES);

	char* pCurrent = m_pBuff + sizeof(DROPFILES);

	for(i=0;i<m_aFiles.GetSize();i++){
		strcpy(pCurrent,(LPCTSTR)m_aFiles[i]);
		pCurrent += m_aFiles[i].GetLength(); 
		*pCurrent = 0;
		pCurrent++;
	}

	//check buffer bound
	ASSERT(pCurrent - m_nBuffSize - 1 <= m_pBuff);

}

void* CDropFiles::GetBuffer() const
{
	ASSERT(m_pBuff);
	return (void *)m_pBuff;
}
int	CDropFiles::GetBuffSize() const
{
	ASSERT(m_nBuffSize);
	return m_nBuffSize;
}

