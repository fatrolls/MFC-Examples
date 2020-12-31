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
        //if ( dwStyle & flgtbl[i].flag )
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

// Displays all the fields of a dialog control.  Returns the next address
// following the control's data.
LPDLGITEMTEMPLATE DlgData::DumpDialogItem( LPDLGITEMTEMPLATE pDlgItemTemplate )
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
        //printf( "  *** Dialog item not visible ***\n" );
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
			wsprintf(szNumbers,"%hu",wTitleID);
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
		wsprintf(szNumbers,"%hu",pDlgItemTemplate->id);
		strcat(szDlgFileData,"ID");
		strcat(szDlgFileData,szNumbers);
		strcat(szDlgFileData,",");

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
			//strcat(szDlgFileData,",");
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
				//strcpy(szDlgFileData,"Button ");
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
			wsprintf(szNumbers,"%hu",wTitleID);
			strcat(szDlgFileData,"IDR_R");
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
		wsprintf(szNumbers,"%hu",pDlgItemTemplate->id);
		strcat(szDlgFileData,"IDC_C");
		strcat(szDlgFileData,szNumbers);
		strcat(szDlgFileData,",");

			// coordinates
		wsprintf(szNumbers,"%hd,%hd,%hd,%hd",
							pDlgItemTemplate->x,
							pDlgItemTemplate->y,
							pDlgItemTemplate->cx,
							pDlgItemTemplate->cy);
		strcat(szDlgFileData,szNumbers);

		strcat(szDlgFileData,",");

		if (strlen(szDlgControlStyles) != 0)
		{
			//strcat(szDlgFileData,",");
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
			//strcat(szDlgFileData,",");
			strcat(szDlgFileData,szDlgItemStyles);
			//strcat(szDlgFileData,",");
		}

		
		


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

    // Return value is next byte after the DLGITEMTEMPLATE and its
    // variable len  fields     
    return (LPDLGITEMTEMPLATE)pCreationData;
}

// Displays all the fields of a dialog template, and then calls DumpDialogItem
// to display all the controls.
BOOL DlgData::DumpDialog( PVOID pDlg )
{
    LPDLGTEMPLATE pDlgTemplate = (LPDLGTEMPLATE)pDlg;
    LPCTSTR m_DIALOG = "IDD_RESVIEWDLG DIALOG DISCARDABLE ";
	LPCTSTR m_STYLE = "STYLE ";
    CHAR szDlgFileData[512];
	CHAR szDlgStyles[512];
	CHAR szNumbers[40];
    PWORD pMenu, pClass, pTitle, pPointSize, pTypeface;
    CHAR szAnsiString[256];
    RECT rectDlg;
    UINT i;
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
        //
        // Start out by printing all the fixed fields in the DLGTEMPLATE
        //          
        // dialog header
		// 
		strcpy(szDlgFileData,m_DIALOG);
		
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
        

        //printf( "extended style: %08X\n", pDlgTemplate->dwExtendedStyle );          

        

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
                                                
                //printf( "Menu Name: %s\n", szAnsiString );
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
                //printf( "Class ID: %d\n", (signed short)*pClass++ );
            else
            {
                pClass = GetDlgEmbeddedString(  pClass, szAnsiString,
                                                sizeof(szAnsiString) );
                                                
                //printf( "Class Name: %s\n", szAnsiString );
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
                                            
            //printf( "Title: %s\n", szAnsiString );
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
                                            
            //printf( "Font: %u point %s\n", *pPointSize, szAnsiString );
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

            //printf( "  ----\n" );   // Print separator for next item

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
                //printf( "  *** Item not within dialog ***\n" );
			}
                
            pDlgItemTemplate = DumpDialogItem( pDlgItemTemplate );
        }
    }
    else    // Left as an exercise for the reader... :-)
	{
		//printf( "DLGTEMPLATEEX type not yet handled\n" );
		strcpy(szDlgFileData,"//*** DLGTEMPLATEEX type not yet handled ***\r\n");
		if(!WriteFile( m_hDlgFile, szDlgFileData,
						strlen(szDlgFileData),
						&dwBytesWritten, NULL ) )
			{
				AfxMessageBox("Error Writing DLG");
				return FALSE;
			}
		return FALSE;

	}

	strcpy(szDlgFileData,"END\r\n");
		if(!WriteFile( m_hDlgFile, szDlgFileData,
						strlen(szDlgFileData),
						&dwBytesWritten, NULL ) )
			{
				AfxMessageBox("Error Writing DLG");
				return FALSE;
			}
		return FALSE;
        
    CloseHandle( m_hDlgFile );        
    return TRUE;
}


//
// find first matching RC Type
//
void DlgData::GetRCType(  DWORD dwStyle,
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
        //if ( dwStyle & flgtbl[i].flag )
		if ( dwsave == flgtbl[i].flag )
        {
            pszBuffer += wsprintf( pszBuffer, "%s", flgtbl[i].name );
			return;
		}
	}

}
