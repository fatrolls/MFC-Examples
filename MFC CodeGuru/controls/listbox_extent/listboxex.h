//
// CListBoxEx.h	v1.0
//

#ifndef _LISTBOX_EX_H
#define _LISTBOX_EX_H

#include <afxwin.h>

class CListBoxEx : public CListBox
{
public:
	//virtual functions
	virtual int AddString( LPCTSTR sString );
	virtual int DeleteString( UINT nIndex );
	virtual int InsertString( int nIndex, LPCTSTR lpszItem );
	virtual void ResetContent();
	virtual int Dir( UINT attr, LPCTSTR lpszWildCard );

private:
	//helpers
	LONG GetExtentForString( LPCTSTR sText );
	LONG GetExtentForEntireControl();
};


#endif
