#pragma once

#include "FTPclient.h"

namespace nsFTP
{
namespace nsView
{

class CFTPFirewallTypeComboBox : public CComboBox
{
   DECLARE_DYNAMIC(CFTPFirewallTypeComboBox)
   DECLARE_MESSAGE_MAP()
public:
   CFTPFirewallTypeComboBox();
   virtual ~CFTPFirewallTypeComboBox();

   void GetFirewallType(CFirewallType& firewallType) const;
   void SetFirewallType(const CFirewallType& firewallType);

protected:
   int SetItemDataPtr(int iIndex, CFirewallType* pFirewallType);
   const CFirewallType* GetItemDataPtr(int iIndex) const;

   virtual void PreSubclassWindow();

private:
   TFirewallTypeVector  m_vFirewallType;
};

};
};
