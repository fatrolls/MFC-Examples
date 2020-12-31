Microsoft Help Array Generator
(c) Peter Bevilacqua,  1998

//	No warrantee of any kind, express or implied, is included with this
//	software; use at your own risk, responsibility for damages (if any) to
//	anyone resulting from the use of this software rests entirely with the
//	user.

//	Hopefully, this utility will save you hours of tedious work,
//	if you are using context help in your applications.
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// Fixes:
//			Feb 27, 1998
//			- Generate button set as default button.
//			- fixed crash recovery for invalid file selections
//			- replaced richedit control dependency 
//			  with edit control.
//			- Enabled drag and drop for edit control
///////////////////////////////////////////////////////////////

REQUIREMENTS:
	- Microsoft VC++ generated include files (resource.h, resource.hm)
	- requires Richedit control be present on your system (richtx32.ocx)
	- Dialog Resource ID's must have been created as IDD_
	- obvioulsy, make sure you have enable 'help id' for each control
		that you want help for.
	- you must re-compile your .hpj in order for any new
		control id's to be included in the array.

//	This utility will translate and create help arrays for each 
//	dialog resource you have created, as follows:

// Add To Your Include File
// Implementation
protected:
	static DWORD m_dwHelpMap[]
// End Include

DWORD CYourClassName::m_dwHelpMap[] = {
	IDD_ABOUTBOX,	HID_HELP,
	0, 0
};

DWORD CYourClassName::m_dwHelpMap[] = {
	IDD_GRAMMARFILE,	HID_HELP,
	IDC_GRAMMARFILE,	HIDC_GRAMMARFILE,
	IDC_SRENGINE,	HIDC_SRENGINE,
	0, 0
};


//	This is version -1.00, pre-beta-beta, so if you find any
//	bugs or features that may be usefull, please e-mail me
//	Send bug reports, bug fixes, enhancements, requests, 
//	flames, etc.,
//  bscinc@orbonline.net

Have fun...
Peter
