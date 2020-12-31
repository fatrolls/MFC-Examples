/*
 *	$Version:$
 *
 *	$Log:$
 */
class CFileSpec
{
public:
	enum FS_BUILTINS
	{
		FS_EMPTY,								//	Nothing
		FS_APP,									//  Full application path and name
		FS_APPDIR,								//	Application folder
		FS_WINDIR,								//	Windows folder
		FS_SYSDIR,								//	System folder
		FS_TMPDIR,								//	Temporary folder
		FS_DESKTOP,								//	Desktop folder
		FS_FAVOURITES,							//	Favourites folder
		FS_TEMPNAME								//	Create a temporary name
	};

					CFileSpec(FS_BUILTINS spec = FS_EMPTY);
					CFileSpec(LPCTSTR spec);

//	Operations
	BOOL			Exists();

//	Access functions
	CString&		Drive()				{ return m_drive; }
	CString&		Path()				{ return m_path; }
	CString&		FileName()			{ return m_fileName; }
	CString&		Extension()			{ return m_ext; }
	CString			FullPathNoExtension();

					operator LPCTSTR()	{ return GetFullSpec(); }          // as a C string

	CString			GetFullSpec();
	void			SetFullSpec(LPCTSTR spec);
	void			SetFullSpec(FS_BUILTINS spec = FS_EMPTY);
	
	CString			GetFileNameEx();
	void			SetFileNameEx(LPCTSTR spec);

private:
	void			Initialise();
	void			Initialise(FS_BUILTINS spec);
	void			UnLock();
	void			GetShellFolder(LPCTSTR folder);

	CString			m_drive,
					m_path,
					m_fileName,
					m_ext;
};