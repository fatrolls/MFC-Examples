
#include "StdAfx.h"
#include "UIDlgBuilder.h"


CControlUI* CDialogBuilder::Create(LPCTSTR pstrXML, IDialogBuilderCallback* pCallback /*= NULL*/)
{
   m_pCallback = pCallback;
   if( !m_xml.Load(pstrXML) ) return NULL;
   // NOTE: The root element is actually discarded since the _Parse() methods is
   //       parsing children and attaching to the current node.
   CMarkupNode root = m_xml.GetRoot();
   return _Parse(&root);
}

CControlUI* CDialogBuilder::CreateFromResource(UINT nRes, IDialogBuilderCallback* pCallback /*= NULL*/)
{
   HRSRC hResource = ::FindResource(CPaintManagerUI::GetResourceInstance(), MAKEINTRESOURCE(nRes), _T("XML"));
   if( hResource == NULL ) return NULL;
   HGLOBAL hGlobal = ::LoadResource(CPaintManagerUI::GetResourceInstance(), hResource);
   if( hGlobal == NULL ) {
      FreeResource(hResource);
      return NULL;
   }
   CStdString sXML;
   sXML.Assign(static_cast<LPCSTR>(::LockResource(hGlobal)), ::SizeofResource(CPaintManagerUI::GetResourceInstance(), hResource));
   sXML.Replace(_T("\\n"), _T("\n"));
   ::FreeResource(hResource);
   return Create(sXML, pCallback);
}

CControlUI* CDialogBuilder::_Parse(CMarkupNode* pRoot, CControlUI* pParent)
{
   CDialogLayoutUI* pStretched = NULL;
   IContainerUI* pContainer = NULL;
   CControlUI* pReturn = NULL;
   for( CMarkupNode node = pRoot->GetChild() ; node.IsValid(); node = node.GetSibling() ) {
      LPCTSTR pstrClass = node.GetName();
      SIZE_T cchLen = _tcslen(pstrClass);
      CControlUI* pControl = NULL;
      switch( cchLen ) {
      case 4:
         if( _tcscmp(pstrClass, _T("List")) == 0 )                  pControl = new CListUI;
         break;
      case 6:
         if( _tcscmp(pstrClass, _T("Canvas")) == 0 )                pControl = new CCanvasUI;
         else if( _tcscmp(pstrClass, _T("Button")) == 0 )           pControl = new CButtonUI;
         else if( _tcscmp(pstrClass, _T("Option")) == 0 )           pControl = new COptionUI;
         break;
      case 7:
         if( _tcscmp(pstrClass, _T("Toolbar")) == 0 )               pControl = new CToolbarUI;
         else if( _tcscmp(pstrClass, _T("TabPage")) == 0 )          pControl = new CTabPageUI;
         else if( _tcscmp(pstrClass, _T("ActiveX")) == 0 )          pControl = new CActiveXUI;
         break;
      case 8:
         if( _tcscmp(pstrClass, _T("DropDown")) == 0 )              pControl = new CDropDownUI;
         break;
      case 9:
         if( _tcscmp(pstrClass, _T("FadedLine")) == 0 )             pControl = new CFadedLineUI;      
         else if( _tcscmp(pstrClass, _T("TaskPanel")) == 0 )        pControl = new CTaskPanelUI;
         else if( _tcscmp(pstrClass, _T("Statusbar")) == 0 )        pControl = new CStatusbarUI;
         else if( _tcscmp(pstrClass, _T("TabFolder")) == 0 )        pControl = new CTabFolderUI;
         else if( _tcscmp(pstrClass, _T("TextPanel")) == 0 )        pControl = new CTextPanelUI;
         break;
      case 10:
         if( _tcscmp(pstrClass, _T("ListHeader")) == 0 )            pControl = new CListHeaderUI;
         else if( _tcscmp(pstrClass, _T("ListFooter")) == 0 )       pControl = new CListFooterUI;
         else if( _tcscmp(pstrClass, _T("TileLayout")) == 0 )       pControl = new CTileLayoutUI;
         else if( _tcscmp(pstrClass, _T("ToolButton")) == 0 )       pControl = new CToolButtonUI;
         else if( _tcscmp(pstrClass, _T("ImagePanel")) == 0 )       pControl = new CImagePanelUI;
         else if( _tcscmp(pstrClass, _T("LabelPanel")) == 0 )       pControl = new CLabelPanelUI;
         break;
      case 11:
         if( _tcscmp(pstrClass, _T("ToolGripper")) == 0 )           pControl = new CToolGripperUI;
         else if( _tcscmp(pstrClass, _T("WhiteCanvas")) == 0 )      pControl = new CWhiteCanvasUI;
         else if( _tcscmp(pstrClass, _T("TitleShadow")) == 0 )      pControl = new CTitleShadowUI;
         break;
      case 12:
         if( _tcscmp(pstrClass, _T("WindowCanvas")) == 0 )          pControl = new CWindowCanvasUI;
         else if( _tcscmp(pstrClass, _T("DialogCanvas")) == 0 )     pControl = new CDialogCanvasUI;
         else if( _tcscmp(pstrClass, _T("DialogLayout")) == 0 )     pControl = new CDialogLayoutUI;
         else if( _tcscmp(pstrClass, _T("PaddingPanel")) == 0 )     pControl = new CPaddingPanelUI;
         else if( _tcscmp(pstrClass, _T("WarningPanel")) == 0 )     pControl = new CWarningPanelUI;
         break;
      case 13:
         if( _tcscmp(pstrClass, _T("SeparatorLine")) == 0 )         pControl = new CSeparatorLineUI;
         else if( _tcscmp(pstrClass, _T("ControlCanvas")) == 0 )    pControl = new CControlCanvasUI;
         else if( _tcscmp(pstrClass, _T("MultiLineEdit")) == 0 )    pControl = new CMultiLineEditUI;
         else if( _tcscmp(pstrClass, _T("ToolSeparator")) == 0 )    pControl = new CToolSeparatorUI;
         break;
      case 14:
         if( _tcscmp(pstrClass, _T("VerticalLayout")) == 0 )        pControl = new CVerticalLayoutUI;
         else if( _tcscmp(pstrClass, _T("SingleLineEdit")) == 0 )   pControl = new CSingleLineEditUI;
         else if( _tcscmp(pstrClass, _T("SingleLinePick")) == 0 )   pControl = new CSingleLinePickUI;
         else if( _tcscmp(pstrClass, _T("NavigatorPanel")) == 0 )   pControl = new CNavigatorPanelUI;
         else if( _tcscmp(pstrClass, _T("ListHeaderItem")) == 0 )   pControl = new CListHeaderItemUI;
         else if( _tcscmp(pstrClass, _T("GreyTextHeader")) == 0 )   pControl = new CGreyTextHeaderUI;
         break;
      case 15:
         if( _tcscmp(pstrClass, _T("ListTextElement")) == 0 )       pControl = new CListTextElementUI;
         else if( _tcscmp(pstrClass, _T("NavigatorButton")) == 0 )  pControl = new CNavigatorButtonUI;      
         else if( _tcscmp(pstrClass, _T("TabFolderCanvas")) == 0 )  pControl = new CTabFolderCanvasUI;      
         break;
      case 16:
         if( _tcscmp(pstrClass, _T("ListHeaderShadow")) == 0 )      pControl = new CListHeaderShadowUI; 
         else if( _tcscmp(pstrClass, _T("HorizontalLayout")) == 0 ) pControl = new CHorizontalLayoutUI;
         else if( _tcscmp(pstrClass, _T("ListLabelElement")) == 0 ) pControl = new CListLabelElementUI;
         else if( _tcscmp(pstrClass, _T("SearchTitlePanel")) == 0 ) pControl = new CSearchTitlePanelUI;
         break;
      case 17:
         if( _tcscmp(pstrClass, _T("ToolbarTitlePanel")) == 0 )  pControl = new CToolbarTitlePanelUI;
         else if( _tcscmp(pstrClass, _T("ListExpandElement")) == 0 ) pControl = new CListExpandElementUI;
         break;
      }
      // User-supplied control factory
      if( pControl == NULL && m_pCallback != NULL ) {
         pControl = m_pCallback->CreateControl(pstrClass);
      }
      ASSERT(pControl);
      if( pControl == NULL ) return NULL;
      // Add children
      if( node.HasChildren() ) {
         _Parse(&node, pControl);
      }
      // Attach to parent
      if( pParent != NULL ) {
         if( pContainer == NULL ) pContainer = static_cast<IContainerUI*>(pParent->GetInterface(_T("Container")));
         ASSERT(pContainer);
         if( pContainer == NULL ) return NULL;
         pContainer->Add(pControl);
      }
      // Process attributes
      if( node.HasAttributes() ) {
         TCHAR szValue[500] = { 0 };
         SIZE_T cchLen = lengthof(szValue) - 1;
         // Set ordinary attributes
         int nAttributes = node.GetAttributeCount();
         for( int i = 0; i < nAttributes; i++ ) {
            pControl->SetAttribute(node.GetAttributeName(i), node.GetAttributeValue(i));
         }
         // Very custom attributes
         if( node.GetAttributeValue(_T("stretch"), szValue, cchLen) ) {
            if( pStretched == NULL ) pStretched = static_cast<CDialogLayoutUI*>(pParent->GetInterface(_T("DialogLayout")));
            ASSERT(pStretched);
            if( pStretched == NULL ) return NULL;
            UINT uMode = 0;
            if( _tcsstr(szValue, _T("move_x")) != NULL ) uMode |= UISTRETCH_MOVE_X;
            if( _tcsstr(szValue, _T("move_y")) != NULL ) uMode |= UISTRETCH_MOVE_Y;
            if( _tcsstr(szValue, _T("move_xy")) != NULL ) uMode |= UISTRETCH_MOVE_X | UISTRETCH_MOVE_Y;
            if( _tcsstr(szValue, _T("size_x")) != NULL ) uMode |= UISTRETCH_SIZE_X;
            if( _tcsstr(szValue, _T("size_y")) != NULL ) uMode |= UISTRETCH_SIZE_Y;
            if( _tcsstr(szValue, _T("size_xy")) != NULL ) uMode |= UISTRETCH_SIZE_X | UISTRETCH_SIZE_Y;
            if( _tcsstr(szValue, _T("group")) != NULL ) uMode |= UISTRETCH_NEWGROUP;
            if( _tcsstr(szValue, _T("line")) != NULL ) uMode |= UISTRETCH_NEWLINE;
            pStretched->SetStretchMode(pControl, uMode);
         }
      }
      // Return first item
      if( pReturn == NULL ) pReturn = pControl;
   }
   return pReturn;
}

