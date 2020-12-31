#if !defined(AFX_BLUEBUILDER_H__20050505_A1C5_1D19_C2BA_0080AD509054__INCLUDED_)
#define AFX_BLUEBUILDER_H__20050505_A1C5_1D19_C2BA_0080AD509054__INCLUDED_

#pragma once


class IDialogBuilderCallback
{
public:
   virtual CControlUI* CreateControl(LPCTSTR pstrClass) = 0;
};


class UILIB_API CDialogBuilder
{
public:
   CControlUI* Create(LPCTSTR pstrXML, IDialogBuilderCallback* pCallback = NULL);
   CControlUI* CreateFromResource(UINT nRes, IDialogBuilderCallback* pCallback = NULL);

private:
   CControlUI* _Parse(CMarkupNode* parent, CControlUI* pParent = NULL);

   CMarkup m_xml;
   IDialogBuilderCallback* m_pCallback;
};


#endif // !defined(AFX_BLUEBUILDER_H__20050505_A1C5_1D19_C2BA_0080AD509054__INCLUDED_)

