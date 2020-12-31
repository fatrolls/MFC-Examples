#define BOOL int
#define TRUE 1
#define FALSE 0
#define LPCSTR  LPSTR
typedef char*   LPSTR;
#define UINT int
#define PASCAL _stdcall

#include <iostream.h>

class CObject;

struct CRuntimeClass
{
// Attributes
        LPCSTR m_lpszClassName;
        int m_nObjectSize;
        UINT m_wSchema; // schema number of the loaded class
        CObject* (PASCAL* m_pfnCreateObject)(); // NULL => abstract class
        CRuntimeClass* m_pBaseClass;

        // CRuntimeClass objects linked together in simple list
        static CRuntimeClass* pFirstClass; // start of class list
        CRuntimeClass* m_pNextClass;       // linked list of registered classes
};

struct AFX_CLASSINIT
        { AFX_CLASSINIT(CRuntimeClass* pNewClass); };

#define RUNTIME_CLASS(class_name) \
        (&class_name::class##class_name)

#define DECLARE_DYNAMIC(class_name) \
public: \
        static CRuntimeClass class##class_name; \
        virtual CRuntimeClass* GetRuntimeClass() const;

#define _IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
        static char _lpsz##class_name[] = #class_name; \
        CRuntimeClass class_name::class##class_name = { \
                _lpsz##class_name, sizeof(class_name), wSchema, pfnNew, \
                        RUNTIME_CLASS(base_class_name), NULL }; \
        static AFX_CLASSINIT _init_##class_name(&class_name::class##class_name); \
        CRuntimeClass* class_name::GetRuntimeClass() const \
                { return &class_name::class##class_name; } \

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
        _IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)

class CObject
{
public:
  CObject::CObject()  {
                      }
  CObject::~CObject() {
                      }

  virtual CRuntimeClass* GetRuntimeClass() const;
  BOOL IsKindOf(const CRuntimeClass* pClass) const;

public:
  static CRuntimeClass classCObject;
};

class CCmdTarget : public CObject
{
        DECLARE_DYNAMIC(CCmdTarget)
public:
  CCmdTarget::CCmdTarget()  {
                            }
  CCmdTarget::~CCmdTarget() {
                            }
};

class CWinThread : public CCmdTarget
{
        DECLARE_DYNAMIC(CWinThread)
public:
  CWinThread::CWinThread()  {
                            }
  CWinThread::~CWinThread() {
                            }

  virtual BOOL InitInstance() {
                                return TRUE;
                              }
  virtual int Run() {
                      return 1;
                    }
};

class CWnd;

class CWinApp : public CWinThread
{
        DECLARE_DYNAMIC(CWinApp)
public:
  CWinApp* m_pCurrentWinApp;
  CWnd* m_pMainWnd;

public:
  CWinApp::CWinApp()  {
                        m_pCurrentWinApp = this;
                      }
  CWinApp::~CWinApp() {
                      }

  virtual BOOL InitApplication() {
                                   return TRUE;
                                 }
  virtual BOOL InitInstance()    {
                                   return TRUE;
                                 }
  virtual int Run() {
                      return CWinThread::Run();
                    }
};

class CDocument : public CCmdTarget
{
        DECLARE_DYNAMIC(CDocument)
public:
  CDocument::CDocument()   {
                           }
  CDocument::~CDocument()  {
                           }
};

class CWnd : public CCmdTarget
{
        DECLARE_DYNAMIC(CWnd)
public:
  CWnd::CWnd()   {
                 }
  CWnd::~CWnd()  {
                 }

  virtual BOOL Create();
  BOOL CreateEx();
  virtual BOOL PreCreateWindow();
};

class CFrameWnd : public CWnd
{
        DECLARE_DYNAMIC(CFrameWnd)
public:
  CFrameWnd::CFrameWnd()   {
                           }
  CFrameWnd::~CFrameWnd()  {
                           }
  BOOL Create();
  virtual BOOL PreCreateWindow();
};

class CView : public CWnd
{
        DECLARE_DYNAMIC(CView)
public:
  CView::CView()   {
                   }
  CView::~CView()  {
                   }
};


// global function
CWinApp* AfxGetApp();
