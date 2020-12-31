// dlgdata class. 
// does all the work on converting an internal dialog template
// from a resource back to the .RC script file. 
// wo do the best we can to make it compatible with MS/VC resource
// resource editor.


#define UBUTTON 0x0080
#define UEDIT   0x0081
#define USTATIC 0x0082
#define ULB     0x0083
#define USCB    0x0084
#define UCBB    0x0085

class DlgData
{
	


public:

	//
	// functions
	//
	BOOL DumpDialog( PVOID pDlg );
	DlgData();
	DlgData(LPCTSTR szFileName,LPCTSTR szResName,DWORD dwResId);
	~DlgData();

	//
	// data
	//
	

private:
	BOOL DumpDlgTemplate(LPVOID lpDlg);
	BOOL DumpDlgTemplateEX(LPVOID lpDlg);

	//
	// functions
	//
	
	void GetRCType(  DWORD dwStyle,
                            DWORD_RC_DESCRIPTIONS * flgtbl,
							unsigned maxFlags, 
                            PSTR pszBuffer,
							unsigned cbLen );

	void GetBitfieldsAsString(  DWORD dwStyle,
                            DWORD_FLAG_DESCRIPTIONS *, unsigned maxFlags, 
                            PSTR pszBuffer, unsigned cbLen );

	PWORD GetDlgEmbeddedString( PWORD pwsz,
							   PSTR pszBuffer,
								unsigned cbLen );

	LPTSTR GetDlgItemClassIdAsString( WORD classId );
	LPDLGITEMTEMPLATE DumpDialogItem( LPDLGITEMTEMPLATE pDlgItemTemplate );
	LPDLGITEMTEMPLATEEX DumpDialogItemEX( LPDLGITEMTEMPLATEEX pDlgItemTemplateEX );

	//
	// data
	//
	LPCTSTR m_pszFileName;
	LPCTSTR m_pszResName;
	DWORD   m_dwResId;
	HANDLE m_hDlgFile;
	CStringArray m_defineCards;
	
};