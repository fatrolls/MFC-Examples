// metaex.h - Header for CMetaFileEx
#ifndef __CMETAFILE_H__
#define __CMETAFILE_H__

// Placeable metafile data definitions 
typedef struct tagOLDRECT
{
    short left;
    short top;
    short right;
    short bottom;
} OLDRECT;

// Placeable metafile header 
typedef struct {
        DWORD   key;
        WORD	hmf;
        OLDRECT	bbox;
        WORD    inch;
        DWORD   reserved;
        WORD    checksum;
} ALDUSMFHEADER;

#define	METAFILE_VERSION	1
#define	ALDUSKEY		0x9AC6CDD7
#define	ALDUSMFHEADERSIZE	22	// Avoid sizeof is struct alignment >1

// Alignment types
typedef enum {
	AlignNone = -1,
	AlignDefault,
	AlignTopLeft,
	AlignTopCentre,
	AlignTopRight,
	AlignMiddleLeft,
	AlignMiddleCentre,
	AlignMiddleRight,
	AlignBottomLeft,
	AlignBottomCentre,
	AlignBottomRight,
	AlignStretch,
	AlignFit,
} METAALIGNMENT;

class CMetaFile : public CMetaFileDC {
	DECLARE_SERIAL(CMetaFile)
public:
	static bool IsMetafile(CFile* pFile);
	CMetaFile();
	~CMetaFile();
	void Display(CDC* pDC, CRect& r, METAALIGNMENT align = AlignDefault);
	BOOL Read(CFile *file);
	BOOL Read(LPCTSTR lpszFileName);
	void Serialize(CArchive& archive);
	void Clear();
	bool IsEmpty();
private:
	void FitPicture(CRect& r, CSize& size, METAALIGNMENT align);
	ALDUSMFHEADER m_aldusMFHeader;
	HENHMETAFILE m_emf;
};

#endif	// __CMETAFILE_H__
