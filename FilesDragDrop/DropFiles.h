// DropFiles.h
#ifndef BS_CDropFiles_H
#define BS_CDropFiles_H
#include <shlobj.h>
#include <afxcoll.h>
class CDropFiles
{
	public:
		CDropFiles();
		~CDropFiles();

		void	AddFile(const CString &sFile);
		void	CreateBuffer();

		void*	GetBuffer() const;
		int		GetBuffSize() const;


	private:

		CStringArray m_aFiles;
		
		char *m_pBuff;
		int	 m_nBuffSize;
};
#endif