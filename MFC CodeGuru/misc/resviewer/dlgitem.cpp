// Displays all the fields of a dialog control.  Returns the next address
// following the control's data.
LPDLGITEMTEMPLATE DlgData::DumpDialogItem( LPDLGITEMTEMPLATE pDlgItemTemplate )
{
    CHAR szDlgFileData[1024];
	CHAR szDlgItemStyles[1024];
	PWORD pClass, pTitle, pCreationData;
    //char szAnsiString[256];
	BOOL bClass;
	WORD wTitleID;
	CHAR szClassName[256];
	CHAR szTitle[256];
	CHAR szNumbers[40];
	DWORD dwBytesWritten;
	LPTSTR lpData;
	CHAR szquote[] = {0x22,0x00};

	szDlgItemStyles[0] = 0x00;
	szDlgFileData[0] = 0x00;

    // Emite "warning" if the WS_VISIBLE flag isn't set 
    if ( 0 == (pDlgItemTemplate->style & WS_VISIBLE) )
	{
		strcat(szDlgFileData,"//*** Dialog item not visible ***\r\n");
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

	strcpy(szDlgFileData,"CONTROL ");  // assume control
	szClassName[0] = 0x00;
	bClass = FALSE;
    if ( *pClass )
    {
		
        if ( 0xFFFF == *pClass )
        {
			// standard class ie. button static etc..
			bClass = TRUE;
            pClass++;
			lpData = GetDlgItemClassIdAsString(*pClass);
			strcpy(szDlgFileData,lpData);
			strcat(szDlgFileData," ");
			pClass++;  // point to title section
            //printf( "  Class: %s\n", GetDlgItemClassIdAsString(*pClass++) );
        }
        else
        {
			// must be a control
			
			
            pClass = GetDlgEmbeddedString(  pClass, szClassName,
                                            sizeof(szClassName) );
                                            
			
			
            //printf( "  Class: %s\n", szAnsiString );
        }
    }
    else
        pClass++;

	// Following the window class array is the title array
    pTitle = pClass;
	szTitle[0] = 0x00; 
	wTitleID = 0;
    if ( *pTitle )
    {
		
		
        if ( 0xFFFF == *pTitle )
        {
			
            pTitle++;
			wTitleID = (WORD)*pTitle;
			pTitle++;  // point to creation data
            //printf( "  Title resource ID: %u\n", *pTitle++ );
        }
        else
        {
			
            pTitle = GetDlgEmbeddedString(  pTitle, szTitle,
                                            sizeof(szTitle) );
                                            
            //printf( "  Title: %s\n", szAnsiString );
        }
    }
    else
        pTitle++;

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

    //
    // Start out by printing all the fixed fields in the DLGITEMTEMPLATE
    //          
    GetBitfieldsAsString(   pDlgItemTemplate->style,
                         WndStyleFlags, NUMBER_WND_STYLE_FLAGS,
                         szDlgItemStyles, sizeof(szDlgItemStyles) );

	if (bClass)   // standard wnd class
	{
		wsprintf(szNumbers,"%hd,%hd,%hd,%hd",
							pDlgItemTemplate->x,
							pDlgItemTemplate->y,
							pDlgItemTemplate->cx,
							pDlgItemTemplate->cy);
		strcat(szDlgFileData,szNumbers);
		if (strlen(szDlgItemStyles) != 0)
		{
			strcat(szDlgFileData,",");
			strcat(szDlgFileData,szDlgItemStyles);
			strcat(szDlgFileData,"\r\n");
		}


	}
	else
	{ // control of some type
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,szClassName);
		strcat(szDlgFileData,szquote);
		strcat(szDlgFileData,",");
		if (strlen(szDlgItemStyles) != 0)
		{
			//strcat(szDlgFileData,",");
			strcat(szDlgFileData,szDlgItemStyles);
			strcat(szDlgFileData,",");
		}
		wsprintf(szNumbers,"%hd,%hd,%hd,%hd",
							pDlgItemTemplate->x,
							pDlgItemTemplate->y,
							pDlgItemTemplate->cx,
							pDlgItemTemplate->cy);
		strcat(szDlgFileData,szNumbers);
		strcat(szDlgFileData,"\r\n");


	}

	if(!WriteFile(m_hDlgFile,szDlgFileData,
							strlen(szDlgFileData),
							&dwBytesWritten, NULL ) )
	{
		AfxMessageBox("Error Writing DLG");
		return FALSE;
	}
    //printf( "  style: %X (%s)\n", pDlgItemTemplate->style, szDlgItemStyles ); 
    //printf( "  dwExtendedStyle: %X\n", pDlgItemTemplate->dwExtendedStyle); 

    //printf( "  Coords: (%d,%d) - (%d,%d)\n",
      //          pDlgItemTemplate->x, pDlgItemTemplate->y,
      //          pDlgItemTemplate->x + pDlgItemTemplate->cx,
      //          pDlgItemTemplate->y + pDlgItemTemplate->cy );
    //printf( "  id: %d\n", (signed short)pDlgItemTemplate->id);
    
    
    
    
    

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