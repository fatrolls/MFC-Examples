// OlePpgTest.h - Declaration of COlePpgTest typedef
#include "\Extraview\ExtraClass\MfcAtlPropertyPage.h"
// Definition of CPpgTest (COlePropertyPage derived) class
#include "PpgTest.h"
// typedef that stops OBJECT_ENTRY macro from crying
typedef Extraview::CMfcAtlPropertyPage<&CLSID_PpgTest, CPpgTest> COlePpgTest;
