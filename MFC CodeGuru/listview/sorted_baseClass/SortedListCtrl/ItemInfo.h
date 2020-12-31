// ItemInfo.h: interface for the CItemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMINFO_H__0104E656_C0A0_11D1_B974_425F59000000__INCLUDED_)
#define AFX_ITEMINFO_H__0104E656_C0A0_11D1_B974_425F59000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CItemInfo  
{
public:
	virtual ~CItemInfo() {};
	CItemInfo (int iItem) : m_iItem(iItem) {};
	int GetItem() {return m_iItem;}

private:

	int m_iItem;

};

#endif // !defined(AFX_ITEMINFO_H__0104E656_C0A0_11D1_B974_425F59000000__INCLUDED_)
