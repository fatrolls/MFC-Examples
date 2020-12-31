// DlgSpatilQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "mapdemo.h"
#include "DlgSpatilQuery.h"
#include "mapdemoDlg.h"

// CDlgSpatilQuery 对话框

IMPLEMENT_DYNAMIC(CDlgSpatilQuery, CDialog)

CDlgSpatilQuery::CDlgSpatilQuery( IMXObjectPtr & pMap, CWnd* pParent)
	: CDialog(CDlgSpatilQuery::IDD, pParent)
	, m_dis(0)
    , m_pMap(pMap)
{

}

CDlgSpatilQuery::~CDlgSpatilQuery()
{
    if (m_pMap)
    {
        m_pMap.Release();
    }
}

void CDlgSpatilQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SRCSET, m_cmbSrcSet);
	DDX_Control(pDX, IDC_COMBO_OPSET, m_cmbOpSet);
	DDX_Control(pDX, IDC_COMBO_OPTYPE, m_cmbOpType);
	DDX_Text(pDX, IDC_EDIT_DIS, m_dis);
	DDX_Control(pDX, IDC_COMBO_UNIT, m_cmbUnit);
}


BEGIN_MESSAGE_MAP(CDlgSpatilQuery, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgSpatilQuery::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_OPSET, &CDlgSpatilQuery::OnCbnSelchangeComboOpset)
	ON_CBN_SELCHANGE(IDC_COMBO_OPTYPE, &CDlgSpatilQuery::OnCbnSelchangeComboOptype)
END_MESSAGE_MAP()


// CDlgSpatilQuery 消息处理程序

void CDlgSpatilQuery::OnBnClickedOk()
{
 
	if(NULL == m_pMap)
    {
        return;
    }
    IMXLayersPtr playrs = m_pMap->Getlayers();//获取图层列表
    if (playrs == NULL)
    {
        return;
    }

	UpdateData();
	int n = 0;
	if((n = m_cmbSrcSet.GetCurSel()) < 0)
	{
		return;
	}
    //操作数据集
	int m = m_cmbOpSet.GetCurSel();
	IMXDatasetPtr ds = NULL;
	if(m == 0)
	{//选择集
        IMXVectLayerPtr pSelLayer = NULL;
        for(int i = 0,n = playrs->GetLayerCount();i < n;i++)
        {
            IMXLayerPtr pLayer = playrs->GetLayer(i);//根据索引获取图层

            if(pLayer->GetLayerType() != mxLayerVector)//是否为矢量图层
                continue;
            IMXVectLayerPtr pVectLayer = pLayer;
            if (pVectLayer->GetSelectFeatureCount() > 0)
            {
                pSelLayer = pVectLayer;//所选图层
                break;
            }
            pLayer.Release();
            pVectLayer.Release();
        }
        if (pSelLayer)
        {	
            ds = pSelLayer->GetSelectFeatures();//获取选择集
            pSelLayer.Release();
        }

	}
	else
	{//图层名
		CString strOpLayer;
		m_cmbOpSet.GetLBText(m, strOpLayer);
		IMXVectLayerPtr pOpLayer = playrs->GetLayerByName(strOpLayer.GetString());//根据名称获取图层
		if(NULL == pOpLayer)
        { 
            return;
        }
		ds = pOpLayer->SearchAllFeature();//查询所有图元
        pOpLayer.Release();
	}
	//查询选择集
	CString strSrcLayer;
	m_cmbSrcSet.GetLBText(n,strSrcLayer);
	IMXVectLayerPtr pSrcLayer = playrs->GetLayerByName(strSrcLayer.GetString());//根据名称获取图层
	if(NULL == pSrcLayer)
    {
        return;
    }
    //清除所有选择集
    for(int i = 0,n = playrs->GetLayerCount();i < n;i++)
    {
        IMXLayerPtr pLayer = playrs->GetLayer(i);//根据索引获取图层

        if(pLayer->GetLayerType() != mxLayerVector)//是否为矢量图层
            continue;
        IMXVectLayerPtr pVectLayer = pLayer;
        pVectLayer->RemoveAllSelect();//清空选择集
        pLayer.Release();
        pVectLayer.Release();
    }
    //查询结果放在选择集中
	int t = m_cmbOpType.GetCurSel();
	MXSearchTypeConstants sc = (MXSearchTypeConstants)m_cmbOpType.GetItemData(t);
	if(sc == mxSearchTypeDistanceWithIn)
	{
		MXMapUnit u = (MXMapUnit)m_cmbUnit.GetCurSel();
		IMXFeaturePtr ft = NULL;
		while(ft = ds->GetNext())
		{//遍历初始选择集的每个图元
			IMXDatasetPtr ds2 = pSrcLayer->SearchByDistance(ft, m_dis, u);//按距离查询
			IMXFeaturePtr ft2 = NULL;
			while(ft2 = ds2->GetNext())
			{//遍历结果集的每个图元
				pSrcLayer->SelectFeature(ft2->GetGeoId());//选择图元
			    ft2.Release();
			}
            ds2.Release();
			ft.Release();
		}
	}
	else
	{
		IMXFeaturePtr ft = NULL;
 
		while(ft = ds->GetNext())
		{//遍历初始选择集的每个图元
			IMXDatasetPtr ds2 = pSrcLayer->SearchByFeature(ft,_T(""),sc);//根据图元进行空间查询
			IMXFeaturePtr ft2 = NULL;
			while(ft2 = ds2->GetNext())
			{//遍历结果集的每个图元
				pSrcLayer->SelectFeature(ft2->GetGeoId());//选择图元
				ft2.Release();
			}
            ds2.Release();
			ft.Release();
		}
 
	}
    ds.Release();
    pSrcLayer.Release();
	m_pMap->FreshExtern();//刷新选择图元
	OnOK();
}
BOOL CDlgSpatilQuery::OnInitDialog()
{
	CDialog::OnInitDialog();
  
	int n = m_cmbOpType.AddString(L"Intersects(相交)");
	m_cmbOpType.SetItemData(n,mxSearchTypeIntersects);
 
	n = m_cmbOpType.AddString(L"Contains(包含)");
	m_cmbOpType.SetItemData(n,mxSearchTypeContains);
 
	n = m_cmbOpType.AddString(L"Within(內部)");
	m_cmbOpType.SetItemData(n,mxSearchTypeWithin);
    
 	n = m_cmbOpType.AddString(L"Touches(相邻)");
	m_cmbOpType.SetItemData(n,mxSearchTypeTouches);
 
	n = m_cmbOpType.AddString(L"Disjoint(相离)");
	m_cmbOpType.SetItemData(n,mxSearchTypeDisjoint);
     
	n = m_cmbOpType.AddString(L"DisanceWithIn(距离范围内)");
	m_cmbOpType.SetItemData(n,mxSearchTypeDistanceWithIn);
	m_cmbOpType.SetCurSel(0);
 
    //MXMapUnit
 	m_cmbUnit.AddString(L"英里");// mxUnitMile = 0,
 	m_cmbUnit.AddString(L"公里");//mxUnitKilometer = 1,
 	m_cmbUnit.AddString(L"英寸");//mxUnitInch = 2,
 	m_cmbUnit.AddString(L"毫米");//mxUnitMillimeter = 3,
 	m_cmbUnit.AddString(L"厘米");//mxUnitCentimeter = 4,
 	m_cmbUnit.AddString(L"米");  //mxUnitMeter = 5, 
	m_cmbUnit.AddString(L"度");  //mxUnitDegree = 6
	m_cmbUnit.AddString(L"海里");//mxUnitDegree = 6

	m_cmbUnit.SetCurSel(1);

	CheckDlgButton(IDC_CHECK_SELECT,TRUE);
 
	m_cmbOpSet.AddString(L"选择集");
    
    if (m_pMap)
    {
        IMXLayersPtr playrs = m_pMap->Getlayers();//获取图层列表
        if (playrs != NULL)
        {
            for(int i = 0,n = playrs->GetLayerCount();i < n;i++)
            {
                IMXLayerPtr pLayer = playrs->GetLayer(i);//根据索引获取图层

                if(pLayer->GetLayerType() != mxLayerVector)//是否为矢量图层
                    continue;
                m_cmbOpSet.AddString(pLayer->GetLayerName());

                m_cmbSrcSet.AddString(pLayer->GetLayerName());
                pLayer.Release();
            }
        }
        playrs.Release();
    }
	m_cmbOpSet.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSpatilQuery::OnCbnSelchangeComboOpset()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgSpatilQuery::OnCbnSelchangeComboOptype()
{
	int nSel = m_cmbOpType.GetCurSel();
	if(nSel < 0)return;
	MXSearchTypeConstants sc = (MXSearchTypeConstants)m_cmbOpType.GetItemData(nSel);
	if(sc == mxSearchTypeDistanceWithIn)
	{
		GetDlgItem(IDC_EDIT_DIS)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_UNIT)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_DIS)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_UNIT)->EnableWindow(FALSE);
	}
}
