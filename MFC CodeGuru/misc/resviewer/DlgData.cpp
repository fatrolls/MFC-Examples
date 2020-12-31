//
// dlgdata.cpp   
// class for parsing dialog templates
//
#include "stdafx.h"
#include "dlgdata.h"



// Style flags common to all wnds

DWORD_FLAG_DESCRIPTIONS WndStyleFlags[] =
{
	FLAG_AS_STRING(WS_POPUP),
	FLAG_AS_STRING(WS_CHILD),         
	FLAG_AS_STRING(WS_MINIMIZE),       
	FLAG_AS_STRING(WS_VISIBLE),        
	FLAG_AS_STRING(WS_DISABLED),       
	FLAG_AS_STRING(WS_CLIPSIBLINGS),   
	FLAG_AS_STRING(WS_CLIPCHILDREN),   
	FLAG_AS_STRING(WS_MAXIMIZE),       
	FLAG_AS_STRING(WS_BORDER),         
	FLAG_AS_STRING(WS_DLGFRAME),       
	FLAG_AS_STRING(WS_VSCROLL),        
	FLAG_AS_STRING(WS_HSCROLL),        
	FLAG_AS_STRING(WS_SYSMENU),        
	FLAG_AS_STRING(WS_THICKFRAME),     
	FLAG_AS_STRING(WS_GROUP),          
	FLAG_AS_STRING(WS_TABSTOP),        
	FLAG_AS_STRING(WS_POPUPWINDOW),
	FLAG_AS_STRING(WS_OVERLAPPEDWINDOW),
	FLAG_AS_STRING(WS_CAPTION),
	FLAG_AS_STRING(WS_CHILDWINDOW),
	FLAG_AS_STRING(WS_MAXIMIZEBOX),
	FLAG_AS_STRING(WS_MINIMIZEBOX),
	FLAG_AS_STRING(WS_OVERLAPPED)
	
};


#define NUMBER_WND_STYLE_FLAGS \
    (sizeof(WndStyleFlags) / sizeof(WndStyleFlags[0]))



/*
 * Extended Window Styles
 */
DWORD_FLAG_DESCRIPTIONS WndEXStyleFlags[] =
{
	FLAG_AS_STRING( WS_EX_DLGMODALFRAME),
	FLAG_AS_STRING( WS_EX_NOPARENTNOTIFY),    
	FLAG_AS_STRING( WS_EX_TOPMOST),           
	FLAG_AS_STRING( WS_EX_ACCEPTFILES),          
	FLAG_AS_STRING( WS_EX_TRANSPARENT),         
	FLAG_AS_STRING( WS_EX_MDICHILD),    
	FLAG_AS_STRING( WS_EX_TOOLWINDOW),           
	FLAG_AS_STRING( WS_EX_WINDOWEDGE),           
	FLAG_AS_STRING( WS_EX_CLIENTEDGE),           
	FLAG_AS_STRING( WS_EX_CONTEXTHELP),           
	FLAG_AS_STRING( WS_EX_RIGHT),                
	FLAG_AS_STRING( WS_EX_LEFT),                  
	FLAG_AS_STRING( WS_EX_RTLREADING),            
	FLAG_AS_STRING( WS_EX_LTRREADING),            
	FLAG_AS_STRING( WS_EX_LEFTSCROLLBAR),        
	FLAG_AS_STRING( WS_EX_RIGHTSCROLLBAR),        
	FLAG_AS_STRING( WS_EX_CONTROLPARENT),         
	FLAG_AS_STRING( WS_EX_STATICEDGE ),          
	FLAG_AS_STRING( WS_EX_APPWINDOW),            
	FLAG_AS_STRING( WS_EX_OVERLAPPEDWINDOW),     
	FLAG_AS_STRING( WS_EX_PALETTEWINDOW)       

};

#define NUMBER_WND_EXSTYLE_FLAGS \
    (sizeof(WndEXStyleFlags) / sizeof(WndEXStyleFlags[0]))


// All style flags used by dialogs
// includes all wnd styles

DWORD_FLAG_DESCRIPTIONS DlgStyleFlags[] = 
{
	FLAG_AS_STRING(WS_POPUP),
	FLAG_AS_STRING(WS_CHILD),         
	FLAG_AS_STRING(WS_MINIMIZE),       
	FLAG_AS_STRING(WS_VISIBLE),        
	FLAG_AS_STRING(WS_DISABLED),       
	FLAG_AS_STRING(WS_CLIPSIBLINGS),   
	FLAG_AS_STRING(WS_CLIPCHILDREN),   
	FLAG_AS_STRING(WS_MAXIMIZE),       
	FLAG_AS_STRING(WS_BORDER),         
	FLAG_AS_STRING(WS_DLGFRAME),       
	FLAG_AS_STRING(WS_VSCROLL),        
	FLAG_AS_STRING(WS_HSCROLL),        
	FLAG_AS_STRING(WS_SYSMENU),        
	FLAG_AS_STRING(WS_THICKFRAME),     
	FLAG_AS_STRING(WS_GROUP),          
	FLAG_AS_STRING(WS_POPUPWINDOW),
	FLAG_AS_STRING(WS_OVERLAPPEDWINDOW),
	FLAG_AS_STRING(WS_TABSTOP),
	FLAG_AS_STRING(WS_CAPTION),
	FLAG_AS_STRING(WS_CHILDWINDOW),
	FLAG_AS_STRING(WS_MAXIMIZEBOX),
	FLAG_AS_STRING(WS_MINIMIZEBOX),
	FLAG_AS_STRING(WS_OVERLAPPED),
	FLAG_AS_STRING(DS_ABSALIGN),
	FLAG_AS_STRING(DS_SYSMODAL),
	FLAG_AS_STRING(DS_LOCALEDIT),
	FLAG_AS_STRING(DS_SETFONT),
	FLAG_AS_STRING(DS_MODALFRAME),
	FLAG_AS_STRING(DS_NOIDLEMSG),
	FLAG_AS_STRING(DS_SETFOREGROUND),
	FLAG_AS_STRING(DS_3DLOOK),
	FLAG_AS_STRING(DS_FIXEDSYS),
	FLAG_AS_STRING(DS_NOFAILCREATE),
	FLAG_AS_STRING(DS_CONTROL),
	FLAG_AS_STRING(DS_CENTER),
	FLAG_AS_STRING(DS_CENTERMOUSE),
	FLAG_AS_STRING(DS_CONTEXTHELP)

};

#define NUMBER_DLG_STYLE_FLAGS \
    (sizeof(DlgStyleFlags) / sizeof(DlgStyleFlags[0]))

DWORD_FLAG_DESCRIPTIONS DlgButtonStyleFlags[] = 
{
	/*
	* Button Control Styles
	*/
	FLAG_AS_STRING(BS_PUSHBUTTON),       
	FLAG_AS_STRING(BS_DEFPUSHBUTTON),    
	FLAG_AS_STRING(BS_CHECKBOX),         
	FLAG_AS_STRING(BS_AUTOCHECKBOX),
	FLAG_AS_STRING(BS_RADIOBUTTON),      
	FLAG_AS_STRING(BS_3STATE),           
	FLAG_AS_STRING(BS_AUTO3STATE),       
	FLAG_AS_STRING(BS_GROUPBOX),         
	FLAG_AS_STRING(BS_USERBUTTON),       
	FLAG_AS_STRING(BS_AUTORADIOBUTTON),  
	FLAG_AS_STRING(BS_OWNERDRAW),        
	FLAG_AS_STRING(BS_LEFTTEXT),         
	FLAG_AS_STRING(BS_TEXT),             
	FLAG_AS_STRING(BS_ICON),             
	FLAG_AS_STRING(BS_BITMAP),           
	FLAG_AS_STRING(BS_LEFT),             
	FLAG_AS_STRING(BS_RIGHT),            
	FLAG_AS_STRING(BS_CENTER),           
	FLAG_AS_STRING(BS_TOP),              
	FLAG_AS_STRING(BS_BOTTOM),          
	FLAG_AS_STRING(BS_VCENTER),          
	FLAG_AS_STRING(BS_PUSHLIKE),         
	FLAG_AS_STRING(BS_MULTILINE),        
	FLAG_AS_STRING(BS_NOTIFY),           
	FLAG_AS_STRING(BS_FLAT),             
	FLAG_AS_STRING(BS_RIGHTBUTTON)   
};

#define NUMBER_DLG_BUTTONSTYLE_FLAGS \
    (sizeof(DlgButtonStyleFlags) / sizeof(DlgButtonStyleFlags[0]))

DWORD_FLAG_DESCRIPTIONS DlgComboBoxStyleFlags[] = 
{
	/*
	* Combo Box styles
	*/
	FLAG_AS_STRING(CBS_SIMPLE),            
	FLAG_AS_STRING(CBS_DROPDOWN),           
	FLAG_AS_STRING(CBS_DROPDOWNLIST),       
	FLAG_AS_STRING(CBS_OWNERDRAWFIXED),     
	FLAG_AS_STRING(CBS_OWNERDRAWVARIABLE),  
	FLAG_AS_STRING(CBS_AUTOHSCROLL),        
	FLAG_AS_STRING(CBS_OEMCONVERT),         
	FLAG_AS_STRING(CBS_SORT),               
	FLAG_AS_STRING(CBS_HASSTRINGS ),        
	FLAG_AS_STRING(CBS_NOINTEGRALHEIGHT),   
	FLAG_AS_STRING(CBS_DISABLENOSCROLL),   
	FLAG_AS_STRING(CBS_UPPERCASE),          
	FLAG_AS_STRING(CBS_LOWERCASE)
};
#define NUMBER_DLG_COMBOBOXSTYLE_FLAGS \
    (sizeof(DlgComboBoxStyleFlags) / sizeof(DlgComboBoxStyleFlags[0]))

DWORD_FLAG_DESCRIPTIONS DlgEditStyleFlags[] = 
{
	/*
	* Edit Control Styles
    */
	FLAG_AS_STRING(ES_LEFT),           
	FLAG_AS_STRING(ES_CENTER),           
	FLAG_AS_STRING(ES_RIGHT),            
	FLAG_AS_STRING(ES_MULTILINE),       
	FLAG_AS_STRING(ES_UPPERCASE),        
	FLAG_AS_STRING(ES_LOWERCASE),        
	FLAG_AS_STRING(ES_PASSWORD),         
	FLAG_AS_STRING(ES_AUTOVSCROLL),      
	FLAG_AS_STRING(ES_AUTOHSCROLL),      
	FLAG_AS_STRING(ES_NOHIDESEL),        
	FLAG_AS_STRING(ES_OEMCONVERT),       
	FLAG_AS_STRING(ES_READONLY),         
	FLAG_AS_STRING(ES_WANTRETURN),       
	FLAG_AS_STRING(ES_NUMBER)
};
#define NUMBER_DLG_EDITSTYLE_FLAGS \
    (sizeof(DlgEditStyleFlags) / sizeof(DlgEditStyleFlags[0]))

DWORD_FLAG_DESCRIPTIONS DlgListBoxStyleFlags[] = 
{
	/*
	* Listbox Styles
	*/
	FLAG_AS_STRING(LBS_NOTIFY),            
	FLAG_AS_STRING(LBS_SORT),              
	FLAG_AS_STRING(LBS_NOREDRAW),          
	FLAG_AS_STRING(LBS_MULTIPLESEL),       
	FLAG_AS_STRING(LBS_OWNERDRAWFIXED),    
	FLAG_AS_STRING(LBS_OWNERDRAWVARIABLE), 
	FLAG_AS_STRING(LBS_HASSTRINGS),        
	FLAG_AS_STRING(LBS_USETABSTOPS),       
	FLAG_AS_STRING(LBS_NOINTEGRALHEIGHT),  
	FLAG_AS_STRING(LBS_MULTICOLUMN),       
	FLAG_AS_STRING(LBS_WANTKEYBOARDINPUT), 
	FLAG_AS_STRING(LBS_EXTENDEDSEL),       
	FLAG_AS_STRING(LBS_DISABLENOSCROLL),   
	FLAG_AS_STRING(LBS_NODATA),            
	FLAG_AS_STRING(LBS_NOSEL),             
	FLAG_AS_STRING(LBS_STANDARD)
};
#define NUMBER_DLG_LISTBOXSTYLE_FLAGS \
    (sizeof(DlgListBoxStyleFlags) / sizeof(DlgListBoxStyleFlags[0]))

DWORD_FLAG_DESCRIPTIONS DlgScrollBarStyleFlags[] = 
{
	/*
	* Scroll Bar Styles
	*/
	FLAG_AS_STRING(SBS_HORZ),                    
	FLAG_AS_STRING(SBS_VERT),                    
	FLAG_AS_STRING(SBS_TOPALIGN),                
	FLAG_AS_STRING(SBS_LEFTALIGN),               
	FLAG_AS_STRING(SBS_BOTTOMALIGN),             
	FLAG_AS_STRING(SBS_RIGHTALIGN),              
	FLAG_AS_STRING(SBS_SIZEBOXTOPLEFTALIGN),     
	FLAG_AS_STRING(SBS_SIZEBOXBOTTOMRIGHTALIGN), 
	FLAG_AS_STRING(SBS_SIZEBOX),                 
	FLAG_AS_STRING(SBS_SIZEGRIP)
};
#define NUMBER_DLG_SCROLLBARSTYLE_FLAGS \
    (sizeof(DlgScrollBarStyleFlags) / sizeof(DlgScrollBarStyleFlags[0]))

DWORD_FLAG_DESCRIPTIONS DlgStaticStyleFlags[] = 
{
	/*
	* Static Control Constants
	*/
	FLAG_AS_STRING(SS_LEFT),             
	FLAG_AS_STRING(SS_CENTER),           
	FLAG_AS_STRING(SS_RIGHT),            
	FLAG_AS_STRING(SS_ICON),             
	FLAG_AS_STRING(SS_BLACKRECT),        
	FLAG_AS_STRING(SS_GRAYRECT),         
	FLAG_AS_STRING(SS_WHITERECT),        
	FLAG_AS_STRING(SS_BLACKFRAME),       
	FLAG_AS_STRING(SS_GRAYFRAME),        
	FLAG_AS_STRING(SS_WHITEFRAME),      
	FLAG_AS_STRING(SS_USERITEM),         
	FLAG_AS_STRING(SS_SIMPLE),           
	FLAG_AS_STRING(SS_LEFTNOWORDWRAP),   
	FLAG_AS_STRING(SS_OWNERDRAW),        
	FLAG_AS_STRING(SS_BITMAP),           
	FLAG_AS_STRING(SS_ENHMETAFILE),      
	FLAG_AS_STRING(SS_ETCHEDHORZ),       
	FLAG_AS_STRING(SS_ETCHEDVERT),       
	FLAG_AS_STRING(SS_ETCHEDFRAME),      
	FLAG_AS_STRING(SS_TYPEMASK),         
	FLAG_AS_STRING(SS_NOPREFIX),         
	FLAG_AS_STRING(SS_NOTIFY),           
	FLAG_AS_STRING(SS_CENTERIMAGE),      
	FLAG_AS_STRING(SS_RIGHTJUST ),       
	FLAG_AS_STRING(SS_REALSIZEIMAGE),    
	FLAG_AS_STRING(SS_SUNKEN),          
	FLAG_AS_STRING(SS_ENDELLIPSIS ),     
	FLAG_AS_STRING(SS_PATHELLIPSIS),     
	FLAG_AS_STRING(SS_WORDELLIPSIS),     
	FLAG_AS_STRING(SS_ELLIPSISMASK)
};
#define NUMBER_DLG_STATICSTYLE_FLAGS \
    (sizeof(DlgStaticStyleFlags) / sizeof(DlgStaticStyleFlags[0]))



DWORD_RC_DESCRIPTIONS RCButtonTypes[] = 
{
	/*
	* button types in .RC
	*/

	BS_GROUPBOX,"GROUPBOX",    // use groupbox
	BS_CHECKBOX | WS_TABSTOP,"CONTROL", // CONTROL for CHECKBOX
	BS_AUTOCHECKBOX,"CONTROL",          // CONTROL for CHECKBOX
	BS_RADIOBUTTON,"CONTROL",    // CONTROL for RADIOBUTTON
	BS_AUTORADIOBUTTON,"CONTROL", // CONTROL for RADIOBUTTON 
	BS_DEFPUSHBUTTON | WS_TABSTOP,"DEFPUSHBUTTON",
	BS_PUSHBUTTON | WS_TABSTOP,"PUSHBUTTON"
	
	
};
#define NUMBER_RC_BUTTON_FLAGS \
    (sizeof(RCButtonTypes) / sizeof(RCButtonTypes[0]))
	
DWORD_RC_DESCRIPTIONS RCStaticTypes[] = 
{
	/*
	* static types in .RC
	*/

	SS_ICON,"ICON",  
	SS_LEFT,"LTEXT",
	SS_RIGHT,"RTEXT",
	SS_CENTER,"CTEXT"
	
};
#define NUMBER_RC_STATIC_FLAGS \
    (sizeof(RCStaticTypes) / sizeof(RCStaticTypes[0]))
//
// start of class
//
DlgData::DlgData()
{
	m_pszFileName = NULL;
}

DlgData::DlgData(LPCTSTR szFileName,LPCTSTR szResName,DWORD dwResId)
{
	// contructor with the name of the file to be saved
	// the resource name or IDD use to create the DIALOG 
	// header.

	m_pszFileName = szFileName;
	m_pszResName = szResName;
	m_dwResId = dwResId;
}

DlgData::~DlgData()
{
	
}
// Helper function that takes a set of flags, and constructs a string that
// contains the names of all the flags that are set
void DlgData::GetBitfieldsAsString(  DWORD dwStyle,
                            DWORD_FLAG_DESCRIPTIONS * flgtbl,
							unsigned maxFlags, 
                            PSTR pszBuffer,
							unsigned cbLen )
{
    if ( !cbLen || !pszBuffer )
        return;
        
    pszBuffer[0] = 0;   // Start it out null terminated
    
    BOOL fAtLeastOneFlag = FALSE;
    
    for ( unsigned i = 0; i < maxFlags; i++ )
    {
		DWORD dwsave = dwStyle & flgtbl[i].flag;
        
		if ( dwsave == flgtbl[i].flag )
        {
            if ( fAtLeastOneFlag )
                pszBuffer += wsprintf(pszBuffer, " | %s",flgtbl[i].name);
            else
            {
                fAtLeastOneFlag = TRUE;
                pszBuffer += wsprintf( pszBuffer, "%s", flgtbl[i].name );
            }
        }       
    }
}

// Helper function that reads a unicode string out of a dialog template,
// and stores the results in an ANSI (8 bit) buffer.  Returns a pointer to
// the byte immediately following the string.
PWORD DlgData::GetDlgEmbeddedString( PWORD pwsz, PSTR pszBuffer, unsigned cbLen )
{
    if ( !cbLen || !pszBuffer )
        return FALSE;
        
    *pszBuffer = 0;
        
    while ( *pwsz )     // Loop through all chars in the unicode string
    {
        if ( cbLen )    // While there's room, copy to the output buffer
            *pszBuffer++ = (BYTE)*pwsz;         
        pwsz++;
    }
    
    // Null terminate the output string
    if ( cbLen )                
        *pszBuffer = 0;         // Space was left over
    else
        *(pszBuffer-1) = 0;     // Wrote to the entire buffer.  Back up and
                                // null out the last character
        
    return pwsz+1;  // return next WORD past the null terminator
}

LPTSTR DlgData::GetDlgItemClassIdAsString( WORD classId )
{
    switch ( classId )
    {
        case 0x0080: return "Button";
        case 0x0081: return "Edit";
        case 0x0082: return "Static";
        case 0x0083: return "Listbox";
        case 0x0084: return "Scrollbar";
        case 0x0085: return "Combobox";
        default: return "unknown";
    }
}

// Input: a ptr.  Output: the ptr aligned to a DWORD.
#define ALIGN_DWORD( type, p ) ( (type)(((DWORD)p+3) & ~3 ))
// Input: a ptr.  Output: the ptr aligned to a WORD.
#define ALIGN_WORD( type, p ) ( (type)(((DWORD)p+1) & ~1 ))

// Displays all the fields of a dialog control.  Returns the next address
// following the control's data.
LPDLGITEMTEMPLATE DlgData::DumpDialogItem( LPDLGITEMTEMPLATE pDlgItemTemplate )
{
	// each dialog item contains a control in the DIALOG.
	// we loop thru this routine for each dialog item contained
	// in the dialog template and write the source for the 
	// control.

    CHAR szDlgFileData[1024];
	CHAR szDlgItemStyles[1024];
	CHAR szDlgControlStyles[512];
	PWORD pClass, pTitle, pCreationData;
    WORD wClassID;
	WORD wTitleID;
	CHAR szClassName[256];
	CHAR szTitle[256];
	CHAR szNumbers[40];
	CHAR szRCType[20];
	DWORD dwBytesWritten;
	
	CHAR szquote[] = {0x22,0x00};

	szDlgControlStyles[0] = 0x00;
	szDlgItemStyles[0] = 0x00;
	szDlgFileData[0] = 0x00;
	szClassName[0] = 0x00;
	szTitle[0] = 0x00; 
	szRCType[0] = 0x00; 
	wTitleID = 0;
	wClassID = 0;

    // Emite "warning" if the WS_VISIBLE flag isn't set 
    if ( 0 == (pDlgItemTemplate->style & WS_VISIBLE) )
	{
		strcpy(szDlgFileData,"//*** Dialog item not visible ***\r\n");
		if(!WriteFile( m_hDlgFile,szDlgFileData,
								strlen(szDlgFileData),
								&dwBytesWritten, NULL ) )
			{
				AfxMessageBox("Error Writing DLG");
				return FALSE;
			}
        
	}

	// Following the fixed DLGITEMTEMPLATE, first up is the window class
    pClass = (PWORD)(pDlgItemTemplate+1);   // ptr math!

	
	// gather the class info
	
    if ( *pClass )
    {
	    if ( 0xFFFF == *pClass )
        {
			// standard class ie. button static etc..
		
            pClass++;
			wClassID = (WORD)*pClass;
			pClass++;  // point to title section
            
        }
        else
        {
			// must be a control
			pClass = GetDlgEmbeddedString(  pClass, szClassName,
                                        sizeof(szClassName) );
        		            
        }
    }
    else
        pClass++;  // next is title

	// Following the window class array is the title array
	// gather title info

    pTitle = pClass;
	
    if ( *pTitle )
    {
		
		
        if ( 0xFFFF == *pTitle )
        {
			
            pTitle++;
			wTitleID = (WORD)*pTitle;
			pTitle++;  // point to creation data
           
        }
        else
        {
			
            pTitle = GetDlgEmbeddedString(  pTitle, szTitle,
                                            sizeof(szTitle) );
                                            
            
        }
    }
    else
        pTitle++;


	
	if (wClassID == 0)
	{
		// we have a control.
		strcpy(szDlgFileData,"CONTROL "); 
		if (wTitleID)  // standard wnd 
		{
			wsprintf(szNumbers,"IDR_R%hu",wTitleID);
			strcat(szDlgFileData,szNumbers);
			strcat(szDlgFileData,",");
		}
		else
		{
			strcat(szDlgFileData,szquote);
			strcat(szDlgFileData,szTitle);
			strcat(szDlgFileData,szquote);
			strcat(szDlgFileData,",");
		} 
		// control id of this item
		wsprintf(szNumbers,"IDC_C%hu",pDlgItemTemplate->id);
		strcat(szDlgFileData,szNumbers);
		strcat(szDlgFileData,",");
		m_defineCards.Add((LPCTSTR)szNumbers); //save for #define

		// class name
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,szClassName);
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,",");

		GetBitfieldsAsString(pDlgItemTemplate->style,
                             WndStyleFlags,
							 NUMBER_WND_STYLE_FLAGS,
                             szDlgItemStyles,
							 sizeof(szDlgItemStyles) );
		// styles
		if (strlen(szDlgItemStyles) != 0)
		{			
			strcat(szDlgFileData,szDlgItemStyles);
			strcat(szDlgFileData,",");
		}

		// coordinates
		wsprintf(szNumbers,"%hd,%hd,%hd,%hd",
							pDlgItemTemplate->x,
							pDlgItemTemplate->y,
							pDlgItemTemplate->cx,
							pDlgItemTemplate->cy);
		strcat(szDlgFileData,szNumbers);
		strcat(szDlgFileData,"\r\n");

	} // end control type


	//
	// process standard window classes here
	//
	if (wClassID != 0)
	{
		// standard window class
		strcpy(szDlgFileData,"Unknown ");
		switch (wClassID)
		{
			case UBUTTON:
				// get styles
				GetBitfieldsAsString(pDlgItemTemplate->style,
									DlgButtonStyleFlags,
									NUMBER_DLG_BUTTONSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
				GetRCType(pDlgItemTemplate->style,
									RCButtonTypes,
									NUMBER_RC_BUTTON_FLAGS,
									szRCType,
									sizeof(szRCType) );
				strcpy(szDlgFileData,szRCType);
				strcat(szDlgFileData," ");
		
				break;
			case UEDIT:
				strcpy(szDlgFileData,"EDITTEXT ");
				// get styles
				GetBitfieldsAsString(pDlgItemTemplate->style,
									DlgEditStyleFlags,
									NUMBER_DLG_EDITSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
		
				break;
			case USTATIC:
				//strcpy(szDlgFileData,"Static ");
				// get styles
				GetBitfieldsAsString(pDlgItemTemplate->style,
									DlgStaticStyleFlags,
									NUMBER_DLG_STATICSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
				GetRCType(pDlgItemTemplate->style,
									RCStaticTypes,
									NUMBER_RC_STATIC_FLAGS,
									szRCType,
									sizeof(szRCType) );
				strcpy(szDlgFileData,szRCType);
				strcat(szDlgFileData," ");
		
				break;
			case ULB:
				strcpy(szDlgFileData,"LISTBOX ");
				// get styles
				GetBitfieldsAsString(pDlgItemTemplate->style,
									DlgListBoxStyleFlags,
									NUMBER_DLG_LISTBOXSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
		
				break;
			case USCB:
				strcpy(szDlgFileData,"SCROLLBAR ");
				// get styles
				GetBitfieldsAsString(pDlgItemTemplate->style,
									DlgScrollBarStyleFlags,
									NUMBER_DLG_SCROLLBARSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
		
				break;
			case UCBB:
				strcpy(szDlgFileData,"COMBOBOX ");
				// get styles
				GetBitfieldsAsString(pDlgItemTemplate->style,
									DlgComboBoxStyleFlags,
									NUMBER_DLG_COMBOBOXSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
		
				break;
		} // end switch
		if (wTitleID)  // standard wnd 
		{
			wsprintf(szNumbers,"IDR_R%hu",wTitleID);
			strcat(szDlgFileData,szNumbers);
			strcat(szDlgFileData,",");
			m_defineCards.Add((LPCTSTR)szNumbers); //save for #define
		}
		else
		{ // no title for COMBOBOX LISTBOX SCROLLBAR or EDITTEXT
			if (wClassID != UCBB && wClassID != USCB &&
				wClassID != ULB  && wClassID != UEDIT)
			{
				strcat(szDlgFileData,szquote);
				strcat(szDlgFileData,szTitle);
				strcat(szDlgFileData,szquote);
				strcat(szDlgFileData,",");
			}

		} 
		// control id of this item
		wsprintf(szNumbers,"IDC_C%hu",pDlgItemTemplate->id);
		strcat(szDlgFileData,szNumbers);
		strcat(szDlgFileData,",");
		m_defineCards.Add((LPCTSTR)szNumbers); //save for #define

		
		if (strncmp(szDlgFileData,"CONTROL",7) == 0)
			//Has to be a CONTROL for the resource editor
		{
			strcat(szDlgFileData,szquote);
			strcat(szDlgFileData,GetDlgItemClassIdAsString(wClassID));
			strcat(szDlgFileData,szquote);
			strcat(szDlgFileData,",");
			if (strlen(szDlgControlStyles) != 0)
			{				
				strcat(szDlgFileData,szDlgControlStyles);
				strcat(szDlgFileData," | ");
			}
			// get styles
			GetBitfieldsAsString(pDlgItemTemplate->style,
								 WndStyleFlags,
								 NUMBER_WND_STYLE_FLAGS,
								 szDlgItemStyles,
								 sizeof(szDlgItemStyles) );
			// windows styles
			
				//strcat(szDlgFileData,",");
			strcat(szDlgFileData,szDlgItemStyles);
			strcat(szDlgFileData,",");
			
			// coords
			wsprintf(szNumbers,"%hd,%hd,%hd,%hd",
							pDlgItemTemplate->x,
							pDlgItemTemplate->y,
							pDlgItemTemplate->cx,
							pDlgItemTemplate->cy);
			strcat(szDlgFileData,szNumbers);

		}
		
		else
		{
			// coordinates before styles
			wsprintf(szNumbers,"%hd,%hd,%hd,%hd",
								pDlgItemTemplate->x,
								pDlgItemTemplate->y,
								pDlgItemTemplate->cx,
								pDlgItemTemplate->cy);
			strcat(szDlgFileData,szNumbers);

			strcat(szDlgFileData,",");

			if (strlen(szDlgControlStyles) != 0)
			{			
				strcat(szDlgFileData,szDlgControlStyles);
				strcat(szDlgFileData," | ");
			}
			// get styles
			GetBitfieldsAsString(pDlgItemTemplate->style,
								 WndStyleFlags,
								 NUMBER_WND_STYLE_FLAGS,
								 szDlgItemStyles,
								 sizeof(szDlgItemStyles) );
			// styles
			if (strlen(szDlgItemStyles) != 0)
			{
				strcat(szDlgFileData,szDlgItemStyles);
			}
		}// end else not cntrl

		

		strcat(szDlgFileData,"\r\n");


		
	} // end classid != 0

	if(!WriteFile(m_hDlgFile,szDlgFileData,
							strlen(szDlgFileData),
							&dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing DLG");
		return FALSE;
	}
    

    pCreationData = pTitle;
    
    // Following the title array is the (optional) creation data.  We won't
    // show it here, because it's usually not meaningful as ASCII text
    if ( *pCreationData )
    {
        // Adjust for the creation data.  *pCreationData is in bytes, rather
        // than WORDs, so we divide by sizeof(DWORD) to make the ptr addition
        // come out correctly
        pCreationData = (PWORD)( (PBYTE)pCreationData + *pCreationData );
		strcpy(szDlgFileData,"//*** Dialog Contains Creation Data ***\r\n");
		if(!WriteFile( m_hDlgFile, szDlgFileData,
								strlen(szDlgFileData),
								&dwBytesWritten, NULL ) )
			{
				AfxMessageBox("Error Writing DLG");
				return FALSE;
			}
    }
    else
        pCreationData++;

    // Return value is next byte after the DLGITEMTEMPLATE and its
    // variable len  fields     
    return (LPDLGITEMTEMPLATE)pCreationData;
}
//
LPDLGITEMTEMPLATEEX DlgData::DumpDialogItemEX( LPDLGITEMTEMPLATEEX pDlgItemTemplateEX )
{
    CHAR szDlgFileData[1024];
	CHAR szDlgItemStyles[1024];
	CHAR szDlgControlStyles[512];
	PWORD pClass, pTitle, pCreationData;
    WORD wClassID;
	WORD wTitleID;
	CHAR szClassName[256];
	CHAR szTitle[256];
	CHAR szNumbers[40];
	CHAR szRCType[20];
	DWORD dwBytesWritten;
	CHAR szquote[] = {0x22,0x00};

	szDlgControlStyles[0] = 0x00;
	szDlgItemStyles[0] = 0x00;
	szDlgFileData[0] = 0x00;
	szClassName[0] = 0x00;
	szTitle[0] = 0x00; 
	szRCType[0] = 0x00; 
	wTitleID = 0;
	wClassID = 0;

    // Emite "warning" if the WS_VISIBLE flag isn't set 
    if ( 0 == (pDlgItemTemplateEX->style & WS_VISIBLE) )
	{
		strcpy(szDlgFileData,"//*** Dialog item not visible ***\r\n");
		if(!WriteFile( m_hDlgFile,szDlgFileData,
								strlen(szDlgFileData),
								&dwBytesWritten, NULL ) )
			{
				AfxMessageBox("Error Writing DLG");
				return FALSE;
			}
        
	}

	// Following the fixed DLGITEMTEMPLATE, first up is the window class
    pClass = (PWORD)(pDlgItemTemplateEX+1);   // ptr math!

	
	// gather the class info
	
    if ( *pClass )
    {
	    if ( 0xFFFF == *pClass )
        {
			// standard class ie. button static etc..
		
            pClass++;
			wClassID = (WORD)*pClass;
			pClass++;  // point to title section
            
        }
        else
        {
			// must be a control
			pClass = GetDlgEmbeddedString(  pClass, szClassName,
                                        sizeof(szClassName) );
        		            
        }
    }
    else
        pClass++;  // next is title

	// Following the window class array is the title array
	// gather title info

    pTitle = pClass;
	
    if ( *pTitle )
    {
		
		
        if ( 0xFFFF == *pTitle )
        {
			
            pTitle++;
			wTitleID = (WORD)*pTitle;
			pTitle++;  // point to creation data
           
        }
        else
        {
			
            pTitle = GetDlgEmbeddedString(  pTitle, szTitle,
                                            sizeof(szTitle) );
                                            
            
        }
    }
    else
        pTitle++;


	
	if (wClassID == 0)
	{
		// we have a control.
		strcpy(szDlgFileData,"CONTROL "); 
		if (wTitleID)  // standard wnd 
		{
			wsprintf(szNumbers,"IDR_R%hu",wTitleID);
			strcat(szDlgFileData,szNumbers);
			strcat(szDlgFileData,",");
			m_defineCards.Add((LPCTSTR)szNumbers); //save for #define
		}
		else
		{
			strcat(szDlgFileData,szquote);
			strcat(szDlgFileData,szTitle);
			strcat(szDlgFileData,szquote);
			strcat(szDlgFileData,",");
		} 
		// control id of this item
		wsprintf(szNumbers,"IDC_C%hu",pDlgItemTemplateEX->id);
		strcat(szDlgFileData,szNumbers);
		strcat(szDlgFileData,",");
		m_defineCards.Add((LPCTSTR)szNumbers); //save for #define

		// class name
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,szClassName);
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,",");

		GetBitfieldsAsString(pDlgItemTemplateEX->style,
                             WndStyleFlags,
							 NUMBER_WND_STYLE_FLAGS,
                             szDlgItemStyles,
							 sizeof(szDlgItemStyles) );
		// styles
		if (strlen(szDlgItemStyles) != 0)
		{
			//strcat(szDlgFileData,",");
			strcat(szDlgFileData,szDlgItemStyles);
			strcat(szDlgFileData,",");
		}

		// coordinates
		wsprintf(szNumbers,"%hd,%hd,%hd,%hd",
							pDlgItemTemplateEX->x,
							pDlgItemTemplateEX->y,
							pDlgItemTemplateEX->cx,
							pDlgItemTemplateEX->cy);
		strcat(szDlgFileData,szNumbers);
		strcat(szDlgFileData,"\r\n");

	} // end control type


	//
	// process standard window classes here
	//
	if (wClassID != 0)
	{
		// standard window class
		strcpy(szDlgFileData,"Unknown ");
		switch (wClassID)
		{
			case UBUTTON:
				// get styles
				GetBitfieldsAsString(pDlgItemTemplateEX->style,
									DlgButtonStyleFlags,
									NUMBER_DLG_BUTTONSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
				GetRCType(pDlgItemTemplateEX->style,
									RCButtonTypes,
									NUMBER_RC_BUTTON_FLAGS,
									szRCType,
									sizeof(szRCType) );
				strcpy(szDlgFileData,szRCType);
				strcat(szDlgFileData," ");
		
				break;
			case UEDIT:
				strcpy(szDlgFileData,"EDITTEXT ");
				// get styles
				GetBitfieldsAsString(pDlgItemTemplateEX->style,
									DlgEditStyleFlags,
									NUMBER_DLG_EDITSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
		
				break;
			case USTATIC:
				
				// get styles
				GetBitfieldsAsString(pDlgItemTemplateEX->style,
									DlgStaticStyleFlags,
									NUMBER_DLG_STATICSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
				GetRCType(pDlgItemTemplateEX->style,
									RCStaticTypes,
									NUMBER_RC_STATIC_FLAGS,
									szRCType,
									sizeof(szRCType) );
				strcpy(szDlgFileData,szRCType);
				strcat(szDlgFileData," ");
		
				break;
			case ULB:
				strcpy(szDlgFileData,"LISTBOX ");
				// get styles
				GetBitfieldsAsString(pDlgItemTemplateEX->style,
									DlgListBoxStyleFlags,
									NUMBER_DLG_LISTBOXSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
		
				break;
			case USCB:
				strcpy(szDlgFileData,"SCROLLBAR ");
				// get styles
				GetBitfieldsAsString(pDlgItemTemplateEX->style,
									DlgScrollBarStyleFlags,
									NUMBER_DLG_SCROLLBARSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
		
				break;
			case UCBB:
				strcpy(szDlgFileData,"COMBOBOX ");
				// get styles
				GetBitfieldsAsString(pDlgItemTemplateEX->style,
									DlgComboBoxStyleFlags,
									NUMBER_DLG_COMBOBOXSTYLE_FLAGS,
									szDlgControlStyles,
									sizeof(szDlgControlStyles) );
		
				break;
		} // end switch

		if (wTitleID)  // standard wnd 
		{
			wsprintf(szNumbers,"IDR_R%hu",wTitleID);
			strcat(szDlgFileData,szNumbers);
			strcat(szDlgFileData,",");
			m_defineCards.Add((LPCTSTR)szNumbers); //save for #define
		}
		else
		{  // no title for COMBOBOX LISTBOX SCROLLBAR or EDITTEXT
			if (wClassID != UCBB && wClassID != USCB &&
				wClassID != ULB  && wClassID != UEDIT)
			{
				strcat(szDlgFileData,szquote);
				strcat(szDlgFileData,szTitle);
				strcat(szDlgFileData,szquote);
				strcat(szDlgFileData,",");
			}
		} 
		// control id of this item
		wsprintf(szNumbers,"IDC_C%hu",pDlgItemTemplateEX->id);
		strcat(szDlgFileData,szNumbers);
		strcat(szDlgFileData,",");
		m_defineCards.Add((LPCTSTR)szNumbers); //save for #define

		// insert after here
		if (strncmp(szDlgFileData,"CONTROL",7) == 0)
			//Has to be a CONTROL for the resource editor
		{
			strcat(szDlgFileData,szquote);
			strcat(szDlgFileData,GetDlgItemClassIdAsString(wClassID));
			strcat(szDlgFileData,szquote);
			strcat(szDlgFileData,",");
			if (strlen(szDlgControlStyles) != 0)
			{				
				strcat(szDlgFileData,szDlgControlStyles);
				strcat(szDlgFileData," | ");
			}
			// get styles
			GetBitfieldsAsString(pDlgItemTemplateEX->style,
								 WndStyleFlags,
								 NUMBER_WND_STYLE_FLAGS,
								 szDlgItemStyles,
								 sizeof(szDlgItemStyles) );
			// windows styles
			
				
			strcat(szDlgFileData,szDlgItemStyles);
			strcat(szDlgFileData,",");
			
			// coords
			wsprintf(szNumbers,"%hd,%hd,%hd,%hd",
							pDlgItemTemplateEX->x,
							pDlgItemTemplateEX->y,
							pDlgItemTemplateEX->cx,
							pDlgItemTemplateEX->cy);
			strcat(szDlgFileData,szNumbers);

		}
		
		else
		{
			// coordinates before styles
			wsprintf(szNumbers,"%hd,%hd,%hd,%hd",
								pDlgItemTemplateEX->x,
								pDlgItemTemplateEX->y,
								pDlgItemTemplateEX->cx,
								pDlgItemTemplateEX->cy);
			strcat(szDlgFileData,szNumbers);

			strcat(szDlgFileData,",");

			if (strlen(szDlgControlStyles) != 0)
			{
				//strcat(szDlgFileData,",");
				strcat(szDlgFileData,szDlgControlStyles);
				strcat(szDlgFileData," | ");
			}
			// get styles
			GetBitfieldsAsString(pDlgItemTemplateEX->style,
								 WndStyleFlags,
								 NUMBER_WND_STYLE_FLAGS,
								 szDlgItemStyles,
								 sizeof(szDlgItemStyles) );
			// styles
			if (strlen(szDlgItemStyles) != 0)
			{
				//strcat(szDlgFileData,",");
				strcat(szDlgFileData,szDlgItemStyles);
				//strcat(szDlgFileData,",");
			}
		}// end else not cntrl
		
		

		strcat(szDlgFileData,"\r\n");


		
	}

	if(!WriteFile(m_hDlgFile,szDlgFileData,
							strlen(szDlgFileData),
							&dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing DLG");
		return FALSE;
	}
    

    pCreationData = pTitle;
    
    // Following the title array is the (optional) creation data.  We won't
    // show it here, because it's usually not meaningful as ASCII text
    if ( *pCreationData )
    {
        // Adjust for the creation data.  *pCreationData is in bytes, rather
        // than WORDs, so we divide by sizeof(DWORD) to make the ptr addition
        // come out correctly
        pCreationData = (PWORD)( (PBYTE)pCreationData + *pCreationData );
		strcpy(szDlgFileData,"//*** Dialog Contains Creation Data ***\r\n");
		if(!WriteFile( m_hDlgFile, szDlgFileData,
								strlen(szDlgFileData),
								&dwBytesWritten, NULL ) )
			{
				AfxMessageBox("Error Writing DLG");
				return FALSE;
			}
    }
    else
        pCreationData++;

    // Return value is next byte after the DLGITEMTEMPLATEEX and its
    // variable len  fields     
    return (LPDLGITEMTEMPLATEEX)pCreationData;
}

//
// Displays all the fields of a dialog template, and then calls DumpDialogItem
// to display all the controls.
BOOL DlgData::DumpDialog( PVOID pDlg )
{
    LPDLGTEMPLATE pDlgTemplate = (LPDLGTEMPLATE)pDlg;
	LPDLGTEMPLATEEX pDlgTemplateEX = (LPDLGTEMPLATEEX)pDlg;
    LPCTSTR szDialog = "IDD_RESVIEWDLG DIALOG DISCARDABLE ";
	LPCTSTR szDialogEX = "IDD_RESVIEWDLG DIALOGEX ";
	LPCTSTR m_STYLE = "STYLE ";
    CHAR szDlgFileData[512];
	DWORD dwBytesWritten;
	CHAR szquote[] = {0x22,0x00};
            
	if (!m_pszFileName)
		return FALSE;

	m_hDlgFile = CreateFile(m_pszFileName, 
                   GENERIC_READ | GENERIC_WRITE, 
                   (DWORD) 0, 
                   (LPSECURITY_ATTRIBUTES) NULL, 
                   CREATE_ALWAYS, 
                   FILE_ATTRIBUTE_NORMAL, 
                   (HANDLE) NULL); 
 
    if (m_hDlgFile == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("Error Creating Dlg File"); 
		 return FALSE;
        
	}

    if ( HIWORD(pDlgTemplate->style) != 0xFFFF ) 
		// Is it a regular DLGTEMPLATE?
    {
        DumpDlgTemplate(pDlg);
    }
    else    // process DLGTEMPLATEEX
	{
		
		DumpDlgTemplateEX(pDlg);

	}
	
	strcpy(szDlgFileData,"END\r\n");

	if(!WriteFile( m_hDlgFile, szDlgFileData,
				strlen(szDlgFileData),
				&dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing DLG");
		return FALSE;
	}

	INT Cards;
	INT Start = 10000;
	Cards = m_defineCards.GetSize();
	if (Cards > 0)
	{
		for (INT x = 0;x<Cards;x++)
		{
			wsprintf(szDlgFileData,"#define %s %d\r\n",
						m_defineCards[x],
						Start);
			if(!WriteFile( m_hDlgFile, szDlgFileData,
				strlen(szDlgFileData),
				&dwBytesWritten, NULL ) )
			{
				AfxMessageBox("Error Writing DLG");
				return FALSE;
			}
			Start++;
		}
	}
        
    CloseHandle( m_hDlgFile );        
    return TRUE;
}


//
// find first matching RC Type
//
void DlgData::GetRCType(  DWORD dwStyle,
                            DWORD_RC_DESCRIPTIONS * flgtbl,
							unsigned maxFlags, 
                            PSTR pszBuffer,
							unsigned cbLen )
{
    if ( !cbLen || !pszBuffer )
        return;
        
    pszBuffer[0] = 0;   // Start it out null terminated
    
    BOOL fAtLeastOneFlag = FALSE;
    
    for ( unsigned i = 0; i < maxFlags; i++ )
    {
		DWORD dwsave = dwStyle & flgtbl[i].flag;
        
		if ( dwsave == flgtbl[i].flag )
        {
            pszBuffer += wsprintf( pszBuffer, "%s", flgtbl[i].name );
			return;
		}
	}

	return;

}


BOOL DlgData::DumpDlgTemplateEX(LPVOID lpDlg)
{
	LPDLGTEMPLATEEX pDlgTemplateEX = (LPDLGTEMPLATEEX)lpDlg;
    
	LPCTSTR szDialogEX = "DIALOGEX ";
	LPCTSTR m_STYLE = "STYLE ";
	LPCTSTR m_EXSTYLE = "EXSTYLE ";
    CHAR szDlgFileData[512];
	CHAR szDlgStyles[512];
	CHAR szNumbers[40];
    PWORD pMenu, pClass, pTitle, pPointSize, pTypeface, pWeight, pItalic;
    CHAR szAnsiString[256];
    RECT rectDlg;
    UINT i;
	DWORD dwBytesWritten;
	CHAR szquote[] = {0x22,0x00};
	// DLGTEMPLATEX 
    // Start out by printing all the fixed fields in the DLGTEMPLATE
    //          
    // dialog header
	// 
	if (m_dwResId == 0)
		wsprintf(szDlgFileData,"IDD_%s",m_pszResName);
	else
		wsprintf(szDlgFileData,"IDD_%d",m_dwResId);
	
	m_defineCards.Add((LPCTSTR)szDlgFileData);

	strcat(szDlgFileData,szDialogEX);
	
	
	wsprintf(szNumbers,"%i,%i,%i,%i ",
							pDlgTemplateEX->x,
							pDlgTemplateEX->y,
							pDlgTemplateEX->cx,
							pDlgTemplateEX->cy);
	// append coords
	strcat(szDlgFileData,szNumbers);
	strcat(szDlgFileData,"\r\n");

	if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing DLG");
		return FALSE;
	}

	GetBitfieldsAsString(   pDlgTemplateEX->style,
                            DlgStyleFlags, NUMBER_DLG_STYLE_FLAGS,
                            szDlgStyles, sizeof(szDlgStyles) );

	strcpy(szDlgFileData,m_STYLE);
	strcat(szDlgFileData,szDlgStyles);
	strcat(szDlgFileData,"\r\n");

	if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing DLG");
		return FALSE;
	}
    

	// windows extended styles

	szDlgStyles[0] = 0x00;

	GetBitfieldsAsString(   pDlgTemplateEX->exStyle,
                            WndEXStyleFlags, NUMBER_WND_EXSTYLE_FLAGS,
                            szDlgStyles, sizeof(szDlgStyles) );

	if (strlen(szDlgStyles) > 0)
	{

		strcpy(szDlgFileData,m_EXSTYLE);
		strcat(szDlgFileData,szDlgStyles);
		strcat(szDlgFileData,"\r\n");

		if(!WriteFile( m_hDlgFile, szDlgFileData,
				strlen(szDlgFileData),
				&dwBytesWritten, NULL ) )
		{
			AfxMessageBox("Error Writing DLG");
			return FALSE;
		}
	}
         

    

    rectDlg.left = rectDlg.top = 0;
    rectDlg.right = pDlgTemplateEX->cx;
    rectDlg.bottom = pDlgTemplateEX->cy;
    
    // Following the fixed DLGTEMPLATE, first up is the menu
	
	
    pMenu = (PWORD)(pDlgTemplateEX + 1);  // ptr math!
	
    if ( *pMenu )
    {
		strcpy(szDlgFileData,"MENU ");

        if ( 0xFFFF == *pMenu )
        {
            pMenu++;
			wsprintf(szNumbers,"%hu",*pMenu);
            strcat(szDlgFileData,szNumbers);
			pMenu++;  // point to class name or ord
        }
        else
        {
            pMenu = GetDlgEmbeddedString(   pMenu, szAnsiString,
                                            sizeof(szAnsiString) );
			strcat(szDlgFileData,szAnsiString);
                                            
            
        }
		strcat(szDlgFileData,"\r\n");
		if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
		{
			AfxMessageBox("Error Writing DLG");
			return FALSE;
		}
    }
    else
        pMenu++;
    
    // Following the menu array is the "window class" array
    pClass = pMenu;
	
    if ( *pClass )
    {
        if ( 0xFFFF == *pClass )
			pClass++;
            
        else
        {
            pClass = GetDlgEmbeddedString(  pClass, szAnsiString,
                                            sizeof(szAnsiString) );
                                            
            
        }
    }
    else
        pClass++;
                
    // Following the window class array is the title array
    pTitle = pClass;
	
    if ( *pTitle )
    {
		strcpy(szDlgFileData,"CAPTION ");
        pTitle = GetDlgEmbeddedString(  pTitle, szAnsiString,
                                        sizeof(szAnsiString) );
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,szAnsiString);
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,"\r\n");
		if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
		{
			AfxMessageBox("Error Writing DLG");
			return FALSE;
		}
                                        
        
    }
    else
        pTitle++;
        
    // Following the title array is the 
	// point size,weight,italic and fontname (if DS_SETFONT
    // is set in pDlgTemplate->Style
    if ( pDlgTemplateEX->style & DS_SETFONT )
    {       
        pPointSize = pTitle;
		pWeight = pPointSize+1;
		pItalic = pWeight+1;
        pTypeface = pItalic+1;
        wsprintf(szNumbers,"%hu, ",*pPointSize);
		strcpy(szDlgFileData,"FONT ");
		strcat(szDlgFileData,szNumbers);

        pTypeface = GetDlgEmbeddedString( pTypeface, szAnsiString,
                                          sizeof(szAnsiString) );
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,szAnsiString);
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,",");
		wsprintf(szNumbers,"%hu,",*pWeight);
		strcat(szDlgFileData,szNumbers);
		if (*pItalic)
		{
			strcat(szDlgFileData,"TRUE");
		}
		else
		{
			strcat(szDlgFileData,"FALSE");
		}

		strcat(szDlgFileData,"\r\n");
		if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
		{
			AfxMessageBox("Error Writing DLG");
			return FALSE;
		}
                                        
    }
    else
        pTypeface = pTitle; 

	// get pointer to first item template
    LPDLGITEMTEMPLATEEX pDlgItemTemplateEX = 
		(LPDLGITEMTEMPLATEEX)pTypeface;
    
	// start of controls

	strcpy(szDlgFileData,"BEGIN\r\n");
	if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing DLG");
		return FALSE;
	}
    // Now iterate through each of the controls, calling DumpDialogItem
    for ( i=0; i < pDlgTemplateEX->cDlgItems; i++ )
    {
        pDlgItemTemplateEX = 
			ALIGN_DWORD(LPDLGITEMTEMPLATEEX, pDlgItemTemplateEX);

        

        // Check that the dialog item is within the bounds of the dialog.
        // If not, emit a warning message
        POINT ctlPt = { pDlgItemTemplateEX->x, pDlgItemTemplateEX->y };
        if ( !PtInRect( &rectDlg, ctlPt ) )
		{
			strcpy(szDlgFileData,"//*** Item not within dialog ***\r\n");
			if(!WriteFile( m_hDlgFile, szDlgFileData,
							strlen(szDlgFileData),
							&dwBytesWritten, NULL ) )
			{
			AfxMessageBox("Error Writing DLG");
			return FALSE;
			}
            
		}
            
        pDlgItemTemplateEX = DumpDialogItemEX( pDlgItemTemplateEX );
    }
		
	return TRUE;


}
BOOL DlgData::DumpDlgTemplate(LPVOID lpDlg)
{
	LPDLGTEMPLATE pDlgTemplate = (LPDLGTEMPLATE)lpDlg;
	
    LPCTSTR szDialog = " DIALOG DISCARDABLE ";
	
	LPCTSTR m_STYLE = "STYLE ";
	LPCTSTR m_EXSTYLE = "EXSTYLE ";
    CHAR szDlgFileData[512];
	CHAR szDlgStyles[512];
	CHAR szNumbers[40];
    PWORD pMenu, pClass, pTitle, pPointSize, pTypeface;
    CHAR szAnsiString[256];
    RECT rectDlg;
    UINT i;
	DWORD dwBytesWritten;
	CHAR szquote[] = {0x22,0x00};
	//
    // Start out by printing all the fixed fields in the DLGTEMPLATE
    //          
    // dialog header
	// 
	if (m_dwResId == 0)
		wsprintf(szDlgFileData,"IDD_%s",m_pszResName);
	else
		wsprintf(szDlgFileData,"IDD_%d",m_dwResId);

	m_defineCards.Add((LPCTSTR)szDlgFileData);  // add to define card
	strcat(szDlgFileData,szDialog);


	wsprintf(szNumbers,"%i,%i,%i,%i ",
							pDlgTemplate->x,
							pDlgTemplate->y,
							pDlgTemplate->cx,
							pDlgTemplate->cy);
	// append coords
	strcat(szDlgFileData,szNumbers);
	strcat(szDlgFileData,"\r\n");

	if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing DLG");
		return FALSE;
	}

	GetBitfieldsAsString(   pDlgTemplate->style,
                            DlgStyleFlags, NUMBER_DLG_STYLE_FLAGS,
                            szDlgStyles, sizeof(szDlgStyles) );

	strcpy(szDlgFileData,m_STYLE);
	strcat(szDlgFileData,szDlgStyles);
	strcat(szDlgFileData,"\r\n");

	if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing DLG");
		return FALSE;
	}
    
	// extended windows styles
	szDlgStyles[0] = 0x00;
	GetBitfieldsAsString(   pDlgTemplate->dwExtendedStyle,
                            WndEXStyleFlags, NUMBER_WND_EXSTYLE_FLAGS,
                            szDlgStyles, sizeof(szDlgStyles) );


	if (strlen(szDlgStyles) > 0)
	{

		strcpy(szDlgFileData,m_EXSTYLE);
		strcat(szDlgFileData,szDlgStyles);
		strcat(szDlgFileData,"\r\n");

		if(!WriteFile( m_hDlgFile, szDlgFileData,
				strlen(szDlgFileData),
				&dwBytesWritten, NULL ) )
		{
			AfxMessageBox("Error Writing DLG");
			return FALSE;
		}
	}

    rectDlg.left = rectDlg.top = 0;
    rectDlg.right = pDlgTemplate->cx;
    rectDlg.bottom = pDlgTemplate->cy;
    
    // Following the fixed DLGTEMPLATE, first up is the menu
	//strcat(szDlgFileData,"MENU ");
	
    pMenu = (PWORD)(pDlgTemplate + 1);  // ptr math!
    if ( *pMenu )
    {
		strcpy(szDlgFileData,"MENU ");

        if ( 0xFFFF == *pMenu )
        {
            pMenu++;
			wsprintf(szNumbers,"%hu",*pMenu);
            strcat(szDlgFileData,szNumbers);
			pMenu++;  // point to class name or ord
        }
        else
        {
            pMenu = GetDlgEmbeddedString(   pMenu, szAnsiString,
                                            sizeof(szAnsiString) );
			strcat(szDlgFileData,szAnsiString);
                                            
            
        }
		strcat(szDlgFileData,"\r\n");
		if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
		{
			AfxMessageBox("Error Writing DLG");
			return FALSE;
		}
    }
    else
        pMenu++;
    
    // Following the menu array is the "window class" array
    pClass = pMenu;
    if ( *pClass )
    {
        if ( 0xFFFF == *pClass )
			pClass++;
           
        else
        {
            pClass = GetDlgEmbeddedString(  pClass, szAnsiString,
                                            sizeof(szAnsiString) );
                                                        
        }
    }
    else
        pClass++;
                
    // Following the window class array is the title array
    pTitle = pClass;
    if ( *pTitle )
    {
		strcpy(szDlgFileData,"CAPTION ");
        pTitle = GetDlgEmbeddedString(  pTitle, szAnsiString,
                                        sizeof(szAnsiString) );
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,szAnsiString);
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,"\r\n");
		if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
		{
			AfxMessageBox("Error Writing DLG");
			return FALSE;
		}                                        
        
    }
    else
        pTitle++;
        
    // Following the title array is the point size and font (if DS_SETFONT
    // is set in pDlgTemplate->Style
    if ( pDlgTemplate->style & DS_SETFONT )
    {       
        pPointSize = pTitle;
        pTypeface = pPointSize+1;
        wsprintf(szNumbers,"%hu, ",*pPointSize);
		strcpy(szDlgFileData,"FONT ");
		strcat(szDlgFileData,szNumbers);

        pTypeface = GetDlgEmbeddedString( pTypeface, szAnsiString,
                                          sizeof(szAnsiString) );
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,szAnsiString);
		strcat(szDlgFileData,szquote);

		strcat(szDlgFileData,"\r\n");
		if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
		{
			AfxMessageBox("Error Writing DLG");
			return FALSE;
		}
	}
                                        
     
    else
        pTypeface = pTitle; 

	// get pointer to first item template
    LPDLGITEMTEMPLATE pDlgItemTemplate = (LPDLGITEMTEMPLATE)pTypeface;
    
	// start of controls

	strcpy(szDlgFileData,"BEGIN\r\n");
	if(!WriteFile( m_hDlgFile, szDlgFileData,
			strlen(szDlgFileData),
			&dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing DLG");
		return FALSE;
	}
    // Now iterate through each of the controls, calling DumpDialogItem
    for ( i=0; i < pDlgTemplate->cdit; i++ )
    {
        pDlgItemTemplate = ALIGN_DWORD(LPDLGITEMTEMPLATE, pDlgItemTemplate);

        // Check that the dialog item is within the bounds of the dialog.
        // If not, emit a warning message
        POINT ctlPt = { pDlgItemTemplate->x, pDlgItemTemplate->y };
        if ( !PtInRect( &rectDlg, ctlPt ) )
		{
			strcpy(szDlgFileData,"//*** Item not within dialog ***\r\n");
			if(!WriteFile( m_hDlgFile, szDlgFileData,
							strlen(szDlgFileData),
							&dwBytesWritten, NULL ) )
			{
			AfxMessageBox("Error Writing DLG");
			return FALSE;
			}
         }
            
        pDlgItemTemplate = DumpDialogItem( pDlgItemTemplate );
    }
    

	return TRUE;

}
