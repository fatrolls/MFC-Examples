/////////////////////////////////////////////////////////////////////////////
// Printer font

class CPrinterFont : public CFont
{
public:
  TEXTMETRIC m_tm;
  ~CPrinterFont();
  void Create(CDC* pDC);
  void Create(CDC* pDC, int nChar, int Width);
};

/////////////////////////////////////////////////////////////////////////////
// string functions

void ClearSpaces(char* pszBuffer);
void StrPad(char* pszBuffer, int Len);
void StrCenter(char* pszBuffer, int Len);
void StrLeft(char* pszBuffer, int Len);
void StrRight(char* pszBuffer, int Len);

void ClearSpaces(CString& strBuffer);
void ClearAllSpaces(CString& strBuffer);
void StrLeft(CString& strBuffer);
void StrCenter(CString& strBuffer);
void StrRight(CString& strBuffer);
