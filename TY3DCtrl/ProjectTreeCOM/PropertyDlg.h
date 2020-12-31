// PropertyDlg.h : Declaration of the CPropertyDlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>

using namespace ATL;

#include "ProjectTreeCOM_i.h"
#include "PropertyList.h"
#include "LayerTree.h"
// CPropertyDlg

class CPropertyDlg : 
	public CDialogImpl<CPropertyDlg>
{
public:
	CPropertyDlg(ILayerInfoPtr layerInfo):mLayerInfo(layerInfo)
	{
	}

	~CPropertyDlg()
	{
	}
    enum { IDD = IDD_PROPERTYDLG };
private:
    ILayerInfoPtr mLayerInfo;
    CFont m_BoldFont;
    CStatic m_prop;

    CTabCtrl m_tabProp;
    CPropertyListCtrl m_listLayerProp;
    CPropertyListCtrl m_listSymbolProp;


BEGIN_MSG_MAP(CPropertyDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDOK, BN_CLICKED, OnClickedOK)
	COMMAND_HANDLER(IDCANCEL, BN_CLICKED, OnClickedCancel)
    //COMMAND_ID_HANDLER(IDOK, OnOK)
    //COMMAND_ID_HANDLER(IDCANCEL, OnCancel)

    NOTIFY_HANDLER(IDC_TABPROP, TCN_SELCHANGE, OnTcnSelchangePropertiesTab)
    REFLECT_NOTIFICATIONS()
	//CHAIN_MSG_MAP(CDialogImpl<CPropertyDlg>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//CDialogImpl<CPropertyDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);

        CenterWindow();

        // set icons
        HICON hIcon = (HICON)::LoadImage((HINSTANCE) _AtlBaseModule.m_hInst, MAKEINTRESOURCE(IDR_PROJECTTREECTRL), 
            IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
        SetIcon(hIcon, TRUE);
        HICON hIconSmall = (HICON)::LoadImage((HINSTANCE) _AtlBaseModule.m_hInst, MAKEINTRESOURCE(IDR_PROJECTTREECTRL), 
            IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
        SetIcon(hIconSmall, FALSE);

        LOGFONT lf = { 0 };
        ::GetObject(GetFont(), sizeof(lf), &lf);
        lf.lfWeight = FW_BOLD;
        m_BoldFont.CreateFontIndirect(&lf);


        m_prop.Attach(GetDlgItem(IDC_PROPTITLE));
        m_prop.SetFont(m_BoldFont);

        m_tabProp.Attach(GetDlgItem(IDC_TABPROP));
        TCITEM item = { 0 };
        item.mask = TCIF_TEXT;   
        item.pszText = _T("图层");
        m_tabProp.InsertItem(0, &item);
        item.pszText = _T("符号");
        m_tabProp.InsertItem(1, &item);
        m_tabProp.SetCurSel(0);

        InitLayerProp();
        InitSymbolProp();
        m_listLayerProp.ShowWindow(true);
        m_listSymbolProp.ShowWindow(false);
		bHandled = TRUE;
		return 1;  // Let the system set the focus
	}

    void InitLayerProp()
    {
        m_listLayerProp.SubclassWindow(GetDlgItem(IDC_LISTLAYERPROP));

        m_listLayerProp.SetExtendedListStyle(PLS_EX_CATEGORIZED);
        m_listLayerProp.AddItem( PropCreateCategory(_T("常规"), 1) );
        m_listLayerProp.AddItem( PropCreateSimple(_T("图层名"), mLayerInfo->GetLayerName()) );
        m_listLayerProp.AddItem( PropCreateSimple(_T("图层路径"), mLayerInfo->GetLayerPath()) );

        m_listLayerProp.AddItem( PropCreateCategory(_T("字段"), 2) );
        VARIANT names, types;
        mLayerInfo->GetFields(&names, &types);
        SAFEARRAY* psaName = names.parray;
        SAFEARRAY* psaType = types.parray;
        if (psaName && psaType)
        {
            BSTR* pNameArr = NULL;
            SafeArrayAccessData(psaName, (void**)&pNameArr);
            BSTR* pTypeArr = NULL;
            SafeArrayAccessData(psaType, (void**)&pTypeArr);
            if (pNameArr && pTypeArr)
            {  
                for (int i = 0; i < psaName->rgsabound[0].cElements; i++)
                {
                    ATL::CString strName(pNameArr[i]);
                    ATL::CString strType(pTypeArr[i]);

                    m_listLayerProp.AddItem( PropCreateSimple(strName, strType) );                     
                }
            }

            SafeArrayUnaccessData(psaName);
            SafeArrayUnaccessData(psaType);

        }
        VariantClear(&names);
        VariantClear(&types);

        m_listLayerProp.AddItem( PropCreateCategory(_T("范围"), 3) );
        double left;
        double top;
        double right;
        double bottom;
        mLayerInfo->GetEnvelop(&left, &top, &right, &bottom);
        m_listLayerProp.AddItem( PropCreateSimple(_T("左"), left) );
        m_listLayerProp.AddItem( PropCreateSimple(_T("右"), right) );
        m_listLayerProp.AddItem( PropCreateSimple(_T("上"), top) );
        m_listLayerProp.AddItem( PropCreateSimple(_T("下"), bottom) );

    }
    void InitSymbolProp()
    {
        m_listSymbolProp.SubclassWindow(GetDlgItem(IDC_LISTSYMBOLPROP));

        m_listSymbolProp.SetExtendedListStyle(PLS_EX_CATEGORIZED);
    }
	LRESULT OnClickedOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnClickedCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

    
    LRESULT OnTcnSelchangePropertiesTab(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
    {
        // TODO: 在此添加控件通知处理程序代码
        int CurSel = m_tabProp.GetCurSel();

        switch(CurSel)
        {
        case 0:
            m_listLayerProp.ShowWindow(true);
            m_listSymbolProp.ShowWindow(false);
            break;
        case 1:
            m_listLayerProp.ShowWindow(false);
            m_listSymbolProp.ShowWindow(true);
            break;
        default: ;
        }

        return 0;
    }

};


