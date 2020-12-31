
// These first two structs represent how the icon information is stored
// when it is bound into a EXE or DLL file. Structure members are WORD
// aligned and the last member of the structure is the ID instead of
// the imageoffset.
#pragma pack( push )
#pragma pack( 2 )
typedef struct tagMEMICONDIRENTRY
{
	BYTE	bWidth;               // Width of the image
	BYTE	bHeight;              // Height of the image (times 2)
	BYTE	bColorCount;          // Number of colors in image (0 if >=8bpp)
	BYTE	bReserved;            // Reserved
	WORD	wPlanes;              // Color Planes
	WORD	wBitCount;            // Bits per pixel
	DWORD	dwBytesInRes;         // how many bytes in this resource?
	WORD	nID;                  // the ID
} MEMICONDIRENTRY, *LPMEMICONDIRENTRY;

typedef struct tagMEMICONDIR 
{
	WORD			idReserved;   // Reserved
	WORD			idType;       // resource type (1 for icons)
	WORD			idCount;      // how many images?
	MEMICONDIRENTRY	idEntries[1]; // the entries for each image
} MEMICONDIR, *LPMEMICONDIR;

// represent how the icon information is stored
// in an ICO file.
typedef struct
{
	BYTE	bWidth;               // Width of the image
	BYTE	bHeight;              // Height of the image (times 2)
	BYTE	bColorCount;          // Number of colors in image (0 if >=8bpp)
	BYTE	bReserved;            // Reserved
	WORD	wPlanes;              // Color Planes
	WORD	wBitCount;            // Bits per pixel
	DWORD	dwBytesInRes;         // how many bytes in this resource?
	DWORD	dwImageOffset;        // where in the file is this image
} ICONDIRENTRY, *LPICONDIRENTRY;

typedef struct 
{
	WORD			idReserved;   // Reserved
	WORD			idType;       // resource type (1 for icons)
	WORD			idCount;      // how many images?
	ICONDIRENTRY	idEntries[1]; // the entries for each image
} ICONDIR, *LPICONDIR;

#define ICONDIRSIZE sizeof(ICONDIR) - sizeof(ICONDIRENTRY)
typedef struct 
{  
     WORD   dlgVer;
	 WORD   signature; 
     DWORD  helpID;
	 DWORD  exStyle;
	 DWORD  style; 
     WORD   cDlgItems;
	 short  x;
	 short  y;
	 short  cx; 
     short  cy; 
     
} DLGTEMPLATEEX, *LPDLGTEMPLATEEX; 


#pragma pack( pop )

//
// item templateEX must be DWORD aligned
//
typedef struct 
{  
     
     DWORD  helpID;
	 DWORD  exStyle;
	 DWORD  style; 
     short  x;
	 short  y;
	 short  cx; 
     short  cy; 
	 WORD   id;
     
} DLGITEMTEMPLATEEX, *LPDLGITEMTEMPLATEEX; 
//
// icon without entries used to get true size w/o entries
//
typedef struct tagMEMICONFILEHDR 
{
	WORD			idReserved;   // Reserved
	WORD			idType;       // resource type (1 for icons)
	WORD			idCount;      // how many images?
} MEMICONFILEHDR, *LPMEMICONFILEHDR;


//
//
//
typedef struct tagRESINFO
{
        DWORD      riType;
        DWORD      riIDNum;
		CHAR       riIDName[255];
}RESINFO, FAR *LPRESINFO, *PRESINFO;
//
//
//

typedef struct tagRESICONINFO
{
	BITMAPINFOHEADER ihHeader;
	RGBQUAD          ihCOlors[1];
	BYTE             ihXOR[1];
	BYTE             ihAND[1];
}RESICONINFO, *LPRESICONINFO;


typedef struct
{
    DWORD   flag;   // specifies the button type i.e CHECHBOX etc..
    LPTSTR  name;   // .RC name
	
} DWORD_RC_DESCRIPTIONS, *LPDWORD_RC_DESCRIPTIONS;

typedef struct
{
    DWORD   flag;
    LPTSTR  name;
} DWORD_FLAG_DESCRIPTIONS, *LPDWORD_FLAG_DESCRIPTIONS;

// input a flag output numeric flag,string of numeric flag 
// seperated by comma
#define FLAG_AS_STRING( f ) f,#f
// Input: a ptr.  Output: the ptr aligned to a DWORD.
#define ALIGN_DWORD( type, p ) ( (type)(((DWORD)p+3) & ~3 ))
