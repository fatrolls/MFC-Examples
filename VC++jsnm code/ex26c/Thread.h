// Thread.h (EX26C)

extern int g_nIndent;
extern CLSID g_clsid; // for the Text server

UINT WriteThreadProc(LPVOID pParam);
UINT ReadThreadProc(LPVOID pParam);
void ReadStorage(LPSTORAGE pStg);
void ReadDirectory(const char* szPath, LPSTORAGE pStg);
