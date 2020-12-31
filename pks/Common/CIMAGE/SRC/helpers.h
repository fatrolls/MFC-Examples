// helpers.h
//

extern BOOL RectBestFit(SIZE extSrc, LPCRECT rcDest, LPRECT rcResult, BOOL bHCenter, BOOL bVCenter, BOOL bFill);
extern CBrush* SelectObject(CDC* pDC, CBrush* brush);
extern CString GetTempPath(void);
extern BOOL MoveFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bOverwrite);
extern BOOL IsFileSystemFile(LPCTSTR lpszPath);
