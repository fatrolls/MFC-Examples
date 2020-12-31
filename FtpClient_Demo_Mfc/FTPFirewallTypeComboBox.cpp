#include "stdafx.h"
#include "FTPexample.h"
#include "FTPFirewallTypeComboBox.h"

using namespace nsFTP;
using namespace nsFTP::nsView;

IMPLEMENT_DYNAMIC(CFTPFirewallTypeComboBox, CComboBox)

BEGIN_MESSAGE_MAP(CFTPFirewallTypeComboBox, CComboBox)
END_MESSAGE_MAP()

CFTPFirewallTypeComboBox::CFTPFirewallTypeComboBox()
{
   CFirewallType::GetAllTypes(m_vFirewallType);
}

CFTPFirewallTypeComboBox::~CFTPFirewallTypeComboBox()
{
}

void CFTPFirewallTypeComboBox::GetFirewallType(CFirewallType& firewallType) const
{
   int iCurSel = GetCurSel();
   if( iCurSel != CB_ERR )
   {
      const CFirewallType* pFirewallType = GetItemDataPtr(iCurSel);
      if( pFirewallType!=NULL && reinterpret_cast<INT_PTR>(pFirewallType)!=-1 )
         firewallType = *pFirewallType;
   }
}

void CFTPFirewallTypeComboBox::SetFirewallType(const CFirewallType& firewallType)
{
   for( int i=0; i<GetCount(); i++ )
   {
      const CFirewallType* pFirewallType = GetItemDataPtr(i);
      if( pFirewallType!=NULL && reinterpret_cast<INT_PTR>(pFirewallType)!=-1 && 
          *pFirewallType==firewallType )
      {
         SetCurSel(i);
         return;
      }
   }
   SetCurSel(0);
}

void CFTPFirewallTypeComboBox::PreSubclassWindow() 
{
   int iIndex = CB_ERR;
   for( TFirewallTypeVector::iterator it=m_vFirewallType.begin(); it!=m_vFirewallType.end(); ++it )
   {
      if( *it != CFirewallType::None() )
      {
         iIndex=AddString(it->AsDisplayString().c_str());
         if( iIndex != CB_ERR )
            SetItemDataPtr(iIndex, it.operator->());
      }
   }
   SetCurSel(0);
}

int CFTPFirewallTypeComboBox::SetItemDataPtr(int iIndex, CFirewallType* pFirewallType)
{
   return CComboBox::SetItemDataPtr(iIndex, reinterpret_cast<void*>(pFirewallType));
}

const CFirewallType* CFTPFirewallTypeComboBox::GetItemDataPtr(int iIndex) const
{
   return reinterpret_cast<CFirewallType*>(CComboBox::GetItemDataPtr(iIndex));
}
