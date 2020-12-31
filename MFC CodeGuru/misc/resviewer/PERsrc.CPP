//==========================================
// Matt Pietrek
// Microsoft Systems Journal, January 1998
// Program: DlgDump.EXE
// FILE: MSJPERsrc.CPP
//==========================================
#include "stdafx.h"
#include <windows.h>
#include "PERsrc.H"

// Helper function that copies the length prefixed unicode strings used
// in resources into an ANSI (8 bit character) buffer.
static BOOL GetRsrcDirStrAsAnsi(PIMAGE_RESOURCE_DIR_STRING_U pImgRsrcDirStr,
                                PSTR pszBuffer, unsigned cbBuffer )
{
    WORD cChars = pImgRsrcDirStr->Length;
    LPWSTR pwsz = pImgRsrcDirStr->NameString;

    // Copy one character at a time, tossing out the high BYTE of the source        
    while ( cChars && cbBuffer )
    {
        *pszBuffer++ = (char)*pwsz++;
        cChars--;
        cbBuffer--;
    }

    // Null terminate the destination ANSI string       
    if ( cbBuffer )
        *pszBuffer = 0;         // We didn't fill up the output buffer
    else
        *(pszBuffer-1) = 0;     // Output buffer is full.  Truncate it.

    return TRUE;

}

//=============================================================================
// Methods for the PERsrcInst class
//=============================================================================

PERsrcInst::PERsrcInst( DWORD rsrcDataRVA, DWORD rsrcStartRVA,
                        DWORD loadAddress, DWORD fileDelta,
                        unsigned rsrcTblIdx, DWORD IdOrNameOffset )
{
    m_rsrcDataRVA = rsrcDataRVA;
    m_rsrcStartRVA = rsrcStartRVA;
    m_loadAddress = loadAddress;
    m_fileDelta = fileDelta;
    m_rsrcTblIdx = rsrcTblIdx;
    m_IdOrNameOffset = IdOrNameOffset;
        
    m_pRsrcDataEntry = (PIMAGE_RESOURCE_DATA_ENTRY)(  m_loadAddress
                                                    + m_rsrcDataRVA
                                                    + m_fileDelta );
}

BOOL PERsrcInst::Name( PSTR pszBuffer, unsigned cbBuffer )
{
    if ( 0x80000000 & m_IdOrNameOffset )
    {   
        // If it's a named resource, the low 31 bits of the NameOffset field 
        // contain a pointer to a length prefixed unicode string
        // (that is, a IMAGE_RESOURCE_DIR_STRING_U structure)
        PIMAGE_RESOURCE_DIR_STRING_U pu = (PIMAGE_RESOURCE_DIR_STRING_U)
                                            ( m_loadAddress
                                            + m_rsrcStartRVA
                                            + (m_IdOrNameOffset & 0x7FFFFFFF)
                                            + m_fileDelta );

        return GetRsrcDirStrAsAnsi( pu, pszBuffer, cbBuffer );
    }
    else
        return FALSE;
}

// Return a pointer to the raw data for this resource instance          
PVOID PERsrcInst::GetData()
{
    return (PVOID)(m_loadAddress +m_pRsrcDataEntry->OffsetToData +m_fileDelta);
}

//=============================================================================
// Methods for the PERsrcDir class (the lowest level class)
//=============================================================================

PERsrcDir::PERsrcDir(   DWORD rsrcDirRVA,
                        DWORD rsrcStartRVA,
                        DWORD loadAddress,
                        DWORD fileDelta )
{
    m_rsrcDirRVA = rsrcDirRVA;
    m_rsrcStartRVA = rsrcStartRVA;
    m_loadAddress = loadAddress;
    m_fileDelta = fileDelta;

    // Allow for 0's to be passed as constructor arguments.  The PERsrcTbl
    // class needs to do initialization before it's ready to init the pointers
    if ( m_rsrcDirRVA )
        InitPointerMembers();   
}

// Helper method that uses the constructor params to create ptrs to various
// parts of the IMAGE_RESOURCE_DIRECTORY
void PERsrcDir::InitPointerMembers( void )
{
    // m_pRsrcDirHdr points to the IMAGE_RESOURCE_DIRECTORY
    m_pRsrcDirHdr =
        (PIMAGE_RESOURCE_DIRECTORY)(m_loadAddress + m_rsrcDirRVA + m_fileDelta);
    
    // m_pRsrcDirEntries points to the first element in the array of 
    // IMAGE_RESOURCE_DIRECTORY_ENTRY's
    m_pRsrcDirEntries = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(m_pRsrcDirHdr + 1 );

    // m_pRsrcDirEntries points to the first non-named element in the array of 
    // IMAGE_RESOURCE_DIRECTORY_ENTRY's.  These entries always follow the
    // named entries
    m_pRsrcIdDirEntries = m_pRsrcDirEntries
                        + m_pRsrcDirHdr->NumberOfNamedEntries;
    
    m_nEntries =    m_pRsrcDirHdr->NumberOfNamedEntries
                +   m_pRsrcDirHdr->NumberOfIdEntries;
}

PIMAGE_RESOURCE_DIRECTORY_ENTRY
PERsrcDir::GetResourceEntryByName( LPCTSTR pszName )
{
    if ( IsBadStringPtr(pszName, 0x7FFFFFFF) )  // Validate input name
        return 0;

    PIMAGE_RESOURCE_DIRECTORY_ENTRY pCurr;

    // Iterate through each of the named entries in this directory...   
    for ( pCurr = m_pRsrcDirEntries; pCurr < m_pRsrcIdDirEntries; pCurr++ )
    {   
        // Get the name of this resource instance
        PIMAGE_RESOURCE_DIR_STRING_U pu = (PIMAGE_RESOURCE_DIR_STRING_U)
                                        ( m_loadAddress
                                        + m_rsrcStartRVA
                                        + pCurr->NameOffset
                                        + m_fileDelta );

        char szCurrRsrcName[256];
        GetRsrcDirStrAsAnsi( pu, szCurrRsrcName, sizeof(szCurrRsrcName) );

        // Compare the resource instance name to the input name
        if ( 0 == strcmp( szCurrRsrcName, pszName ) )
            return pCurr;
    }

    return 0;
}

PIMAGE_RESOURCE_DIRECTORY_ENTRY
PERsrcDir::GetResourceEntryById( WORD Id )
{
    // Point to the first "By Id" entry (which always follow any named entries)
    PIMAGE_RESOURCE_DIRECTORY_ENTRY pCurr = m_pRsrcIdDirEntries;

    // Compare each resource instance Id to the input Id...
    for ( unsigned i=0; i < NumberOfIdEntries(); i++, pCurr++ )
    {
        if ( Id == pCurr->Id )
            return pCurr;
    }
    
    return 0;
}

//=============================================================================
// Methods for the PERsrcType class (mid-level class, e.g., Dialogs, Icons...)
//=============================================================================

PERsrcType::PERsrcType( DWORD rsrcTypeRVA,  DWORD rsrcStartRVA,
                        DWORD loadAddress,  DWORD fileDelta,
                        unsigned rsrcTblIdx,DWORD IdOrNameOffset )
                        : PERsrcDir( rsrcTypeRVA, rsrcStartRVA,
                                     loadAddress, fileDelta )
{
    m_rsrcTblIdx = rsrcTblIdx;
    m_IdOrNameOffset = IdOrNameOffset;
}

PPERsrcInst
PERsrcType::GetNextResourceInst( PPERsrcInst pPrev )
{
    unsigned nextIndex = 0;
    
    if ( 0 == pPrev )
        nextIndex = 0;
    else
    {   
        // Are we at the end of the enumeration?  Bail out if so.
        if ( pPrev->m_rsrcTblIdx >= (m_nEntries-1) )
        {
            delete pPrev;   // Remember to clean up!
            return 0;
        }
        
        // Not at the final entry, so get index of next entry       
        nextIndex = pPrev->m_rsrcTblIdx + 1;
    }

    // Using the entry index, navigate through the directory that always
    // seems to have one entry, and seperates the resource instance from
    // the IMAGE_RESOURCE_DIRECTORY_ENTRY that tells where it lives.
    // Don't ask... it's a long story...
    DWORD rsrcInstRVA =
        BurrowDownOneDirLevel(m_pRsrcDirEntries[nextIndex].OffsetToDirectory);

    // Finally we can create a new PERsrcInst...                                    
    PPERsrcInst pNext;
    pNext = new PERsrcInst( rsrcInstRVA,
                            m_rsrcStartRVA,
                            m_loadAddress,
                            m_fileDelta,
                            nextIndex,
                            m_pRsrcDirEntries[nextIndex].Name );

    delete pPrev;   // Remember to delete the prior enumeration instance!
    
    return pNext;
}

PPERsrcInst
PERsrcType::GetResourceInstByName( PSTR pszName )
{
    PIMAGE_RESOURCE_DIRECTORY_ENTRY p;
    
    p = GetResourceEntryByName( pszName );  // PERsrcDir base class method
    
    if ( !p )
        return 0;

    // See PERsrcInst::GetNextResourceInst for details on this following code
    DWORD rsrcInstRVA =
        BurrowDownOneDirLevel( p->OffsetToDirectory );

    return new PERsrcInst(  rsrcInstRVA,
                            m_rsrcStartRVA,
                            m_loadAddress,
                            m_fileDelta,
                            p - m_pRsrcDirEntries,
                            p->Name );
}

PPERsrcInst
PERsrcType::GetResourceInstById( WORD Id )
{
    PIMAGE_RESOURCE_DIRECTORY_ENTRY p;
    
    p = GetResourceEntryById( Id ); // PERsrcDir base class method
    
    if ( !p )
        return 0;
        
    // See PERsrcInst::GetNextResourceInst for details on this following code
    DWORD rsrcInstRVA =
        BurrowDownOneDirLevel( p->OffsetToDirectory );

    return new PERsrcInst(  rsrcInstRVA,
                            m_rsrcStartRVA,
                            m_loadAddress,
                            m_fileDelta,
                            p - m_pRsrcDirEntries,
                            p->Name );
}

// Helper routine that navigates through the directory that always seems to
// have one entry, and sits between the resource directory and the
// IMAGE_RESOURCE_DIRECTORY_ENTRY that tells where it lives.
DWORD PERsrcType::BurrowDownOneDirLevel( DWORD offsetToDir )
{
    PIMAGE_RESOURCE_DIRECTORY pStupidDir = (PIMAGE_RESOURCE_DIRECTORY)
                ( offsetToDir + m_rsrcStartRVA + m_loadAddress+ m_fileDelta );
                                    
    PIMAGE_RESOURCE_DIRECTORY_ENTRY pStupidEntry =
                        (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pStupidDir + 1);

    return pStupidEntry->OffsetToData + m_rsrcStartRVA;
}
    
BOOL PERsrcType::Name( PSTR pszBuffer, unsigned cbLen)
{
    // See PERsrcInst::Name for details - The code is similar
    if ( 0x80000000 & m_IdOrNameOffset )
    {
        PIMAGE_RESOURCE_DIR_STRING_U pu = (PIMAGE_RESOURCE_DIR_STRING_U)
                                            ( m_loadAddress
                                            + m_rsrcStartRVA
                                            + (m_IdOrNameOffset & 0x7FFFFFFF)
                                            + m_fileDelta );

        return GetRsrcDirStrAsAnsi( pu, pszBuffer, cbLen );
    }
    else
        return FALSE;
}

//=============================================================================
// Methods for the PERsrcTbl class (the class representing all resources in
// an executable)
//=============================================================================

PERsrcTbl::PERsrcTbl( LPCTSTR pszFileName ) : PERsrcDir( 0, 0, 0, 0 )
{
    m_pMemoryMappedFileBase = 0;
    m_hFileMapping = 0;

    //
    // The following stretch of code is just going through the gyrations
    // to create a memory mapped file for the executable name passed in.
    // Note that if anything fails along the way, the code doesn't clean
    // up, since the destructor will clean up everything from whatever
    // state the constructor leaves things in.
    //
    m_hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)0);
                    
    if ( m_hFile == INVALID_HANDLE_VALUE )
        return;
    
    m_hFileMapping = CreateFileMapping(m_hFile, NULL, PAGE_READONLY, 0, 0,NULL);
    if ( m_hFileMapping == 0 )
        return;

    m_pMemoryMappedFileBase = (PCHAR)MapViewOfFile(m_hFileMapping,FILE_MAP_READ,
                                                    0, 0, 0);
    if ( m_pMemoryMappedFileBase == 0 )
        return;

    //
    // Finally... We have a memory mapped file.  Let's now check to make
    // sure it's a valid PE file.
    //
    PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)m_pMemoryMappedFileBase;
    if ( IMAGE_DOS_SIGNATURE != pDosHdr->e_magic )
        return;

    if ( pDosHdr->e_lfarlc < 0x40 ) // Theoretically, this field must be >=
        return;                     // 0x40 for it to be a non-DOS executable


    PIMAGE_NT_HEADERS pNTHdr =
        (PIMAGE_NT_HEADERS)((DWORD)m_pMemoryMappedFileBase + pDosHdr->e_lfanew);
    

    if ( IsBadReadPtr( pNTHdr, sizeof(IMAGE_NT_HEADERS) ) )
        return;

    if ( IMAGE_NT_SIGNATURE != pNTHdr->Signature )
        return;

    //
    // It's a valid PE file.  Now make sure that there's resouces, and if
    // so, set up the remaining member variables.
    //          
    m_loadAddress = (DWORD)m_pMemoryMappedFileBase; 

    m_rsrcStartRVA = pNTHdr->OptionalHeader
                        .DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE]
                        .VirtualAddress;

    if ( !m_rsrcStartRVA )
        return;

    m_rsrcDirRVA = m_rsrcStartRVA;
            
    // Find the section header for the resource section.  We need to know
    // the section header info so that we can calculate the delta between
    // the resource RVA, and its actual offset in the memory mapped file.
    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION( pNTHdr );

    for ( unsigned i=0; i < pNTHdr->FileHeader.NumberOfSections; i++ )
    {
        DWORD sectStartRVA = pSection->VirtualAddress;
        DWORD sectEndRVA = sectStartRVA + pSection->Misc.VirtualSize;
        
        if ( (m_rsrcStartRVA >= sectStartRVA) && (m_rsrcStartRVA < sectEndRVA))
            break;
                
        pSection++;
    }
    
    m_fileDelta = pSection->PointerToRawData - pSection->VirtualAddress;

    InitPointerMembers();   // We can FINALLY initialize the ptr variables...
}

PERsrcTbl::~PERsrcTbl( )
{
    if ( m_pMemoryMappedFileBase )
        UnmapViewOfFile(m_pMemoryMappedFileBase);

    if ( m_hFileMapping )
        CloseHandle( m_hFileMapping );

    if ( m_hFile != INVALID_HANDLE_VALUE )
        CloseHandle( m_hFile );   
}

PPERsrcType
PERsrcTbl::GetNextResourceType( PPERsrcType pPrev )
{   
    if ( !m_rsrcStartRVA )
        return 0;

    unsigned nextIndex = 0;
    
    if ( 0 == pPrev )
        nextIndex = 0;
    else
    {   
        // At the end of the enumeration?
        if ( pPrev->m_rsrcTblIdx >= (m_nEntries-1) )
        {
            delete pPrev;   // Clean up final instance in the enumeration
            return 0;
        }

        // Not the final instance, so get index of next entry       
        nextIndex = pPrev->m_rsrcTblIdx + 1;
    }

    PPERsrcType pNext;
    pNext = new PERsrcType( m_pRsrcDirEntries[nextIndex].OffsetToDirectory
                                +  m_rsrcStartRVA,
                            m_rsrcStartRVA,
                            m_loadAddress,
                            m_fileDelta,
                            nextIndex,
                            m_pRsrcDirEntries[nextIndex].Name );
    delete pPrev;
    
    return pNext;
}

PPERsrcType PERsrcTbl::GetResourceTypeByName( LPCTSTR pszName )
{
    if ( !m_rsrcStartRVA )
        return 0;

    PIMAGE_RESOURCE_DIRECTORY_ENTRY p;
    
    p = GetResourceEntryByName( pszName );  // PERsrcDir base class method
    
    if ( !p )
        return 0;
        
    return new PERsrcType(  p->OffsetToDirectory + m_rsrcStartRVA,
                            m_rsrcStartRVA,
                            m_loadAddress,
                            m_fileDelta,
                            p - m_pRsrcDirEntries,
                            p->Name );
}

PPERsrcType PERsrcTbl::GetResourceTypeById( WORD Id )
{
    if ( !m_rsrcStartRVA )
        return 0;

    PIMAGE_RESOURCE_DIRECTORY_ENTRY p;
    
    p = GetResourceEntryById( Id ); // PERsrcDir base class method
    
    if ( !p )
        return 0;
        
    return new PERsrcType(  p->OffsetToDirectory + m_rsrcStartRVA,
                            m_rsrcStartRVA,
                            m_loadAddress,
                            m_fileDelta,
                            p - m_pRsrcDirEntries,
                            p->Name );

}


