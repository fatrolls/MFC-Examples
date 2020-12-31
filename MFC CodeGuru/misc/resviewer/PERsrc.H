//==========================================
// Matt Pietrek
// Microsoft Systems Journal, January 1998
// Program: DlgDump.EXE
// FILE: MSJPERsrc.H
//==========================================
#ifndef __MSJPEResources_h__
#define __MSJPEResources_h__

class PERsrcTbl;
class PERsrcType;

//=============================================================================
// PERsrcTbl represents one instance of a particular type of resource in an
// executable (for example, the "CHOOSECOLOR" dialog in the DIALOG section
//=============================================================================

class PERsrcInst
{
    public:

    DWORD Id(void)      { return m_IdOrNameOffset; }
    BOOL  IsNamed()     { return (BOOL)(m_IdOrNameOffset & 0x80000000); }
    BOOL  Name( PSTR pszBuffer, unsigned cbBuffer );
    
    DWORD Size(void)    { return m_pRsrcDataEntry->Size; }
    DWORD CodePage(void){ return m_pRsrcDataEntry->CodePage; }          

    PVOID GetData();
    
    ~PERsrcInst(){}     // Destructor must be publicly visible

    private:
    
    friend class PERsrcType;

    PERsrcInst( DWORD rsrcDataRVA, DWORD rsrcStartRVA,
                DWORD loadAddress, DWORD fileDelta,
                unsigned rsrcTblIdx, DWORD IdOrNameOffset );


    DWORD                           m_rsrcDataRVA;
    DWORD                           m_rsrcStartRVA;
    DWORD                           m_loadAddress;
    DWORD                           m_fileDelta;
    unsigned                        m_rsrcTblIdx;
    DWORD                           m_IdOrNameOffset;
    
    PIMAGE_RESOURCE_DATA_ENTRY      m_pRsrcDataEntry;
};

typedef PERsrcInst * PPERsrcInst;


//=============================================================================
// PERsrcDir is a base class to PERsrcTbl and PERsrcType.  It's essentially
// a wrapper for the IMAGE_RESOURCE_DIRECTORY structure defined in WINNT.H
//=============================================================================

class PERsrcDir
{
    protected:

    PERsrcDir(  DWORD rsrcDirRVA, DWORD rsrcStartRVA,
                DWORD loadAddress, DWORD fileDelta );
    ~PERsrcDir( ){};

    void InitPointerMembers(void);
            
    DWORD Characteristics() { return m_pRsrcDirHdr->Characteristics; }
    DWORD TimeDateStamp()   { return m_pRsrcDirHdr->TimeDateStamp; }
    WORD  MajorVersion()    { return m_pRsrcDirHdr->MajorVersion;   }
    WORD  MinorVersion()    { return m_pRsrcDirHdr->MinorVersion;   }
    WORD  NumberOfNamedEntries() {return m_pRsrcDirHdr->NumberOfNamedEntries;}
    WORD  NumberOfIdEntries()    {return m_pRsrcDirHdr->NumberOfIdEntries;}

    DWORD NumberOfEntries(){ return m_nEntries; }
    
    PIMAGE_RESOURCE_DIRECTORY_ENTRY GetResourceEntryByName( LPCTSTR pszName );
    PIMAGE_RESOURCE_DIRECTORY_ENTRY GetResourceEntryById( WORD Id );

    DWORD                           m_rsrcDirRVA;
    DWORD                           m_rsrcStartRVA;
    DWORD                           m_loadAddress;
    DWORD                           m_fileDelta;
    DWORD                           m_nEntries;

    PIMAGE_RESOURCE_DIRECTORY       m_pRsrcDirHdr;
    PIMAGE_RESOURCE_DIRECTORY_ENTRY m_pRsrcDirEntries;
    PIMAGE_RESOURCE_DIRECTORY_ENTRY m_pRsrcIdDirEntries;
};

//=============================================================================
// PERsrcTbl represents one particular type of resource in an executable
// (for instance, BITMAPs, or DIALOGs)
//=============================================================================

class PERsrcType : public PERsrcDir
{
    public:
    
    PPERsrcInst GetNextResourceInst( PPERsrcInst );
    PPERsrcInst GetResourceInstByName( PSTR pszName );
    PPERsrcInst GetResourceInstById( WORD Id );
    
    DWORD Id(void)      { return m_IdOrNameOffset; }
    BOOL  IsNamed()     { return (BOOL)(m_IdOrNameOffset & 0x80000000); }
    BOOL  Name( PSTR pszBuffer, unsigned cbBuffer );

    ~PERsrcType( ){}    // Destructor must be publicly visible

    private:

    friend class PERsrcTbl;

    PERsrcType( DWORD rsrcDirRVA,   DWORD rsrcStartRVA,
                DWORD loadAddress,  DWORD fileDelta,
                unsigned rsrcTblIdx,DWORD IdOrNameOffset  );
                
    
    DWORD BurrowDownOneDirLevel( DWORD offsetToDir );

    unsigned                        m_rsrcTblIdx;
    DWORD                           m_IdOrNameOffset;
};

typedef PERsrcType * PPERsrcType;


//=============================================================================
// PERsrcTbl represents the entire collection of resources in an executable
//=============================================================================

class PERsrcTbl : public PERsrcDir
{
    public:

    PERsrcTbl( LPCTSTR pszFilename );
    ~PERsrcTbl( );
    
    PPERsrcType GetNextResourceType( PPERsrcType );
    PPERsrcType GetResourceTypeByName( LPCTSTR pszName );
    PPERsrcType GetResourceTypeById( WORD Id );
    
    private:
    
    HANDLE      m_hFile;
    HANDLE      m_hFileMapping;
    PVOID       m_pMemoryMappedFileBase;
};

#endif


