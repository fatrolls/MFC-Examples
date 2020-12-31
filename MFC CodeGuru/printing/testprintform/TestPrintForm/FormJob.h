// FormJob.h: interface for the CFormJob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMJOB_H__F2067439_101A_11D2_8432_0000B43382FE__INCLUDED_)
#define AFX_FORMJOB_H__F2067439_101A_11D2_8432_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CFormJob  
{
public:
	enum { pfoStatic = 0, pfoEdit, pfoLine, pfoRect, pfoFrame, pfoImage, pfoRadio, pfoCheck, pfoVLine, pfoHLine, pfoSubForm };
	enum { bdrNoBorder = 0, bdrSingle = 1, bdrDouble = 2, bdrDot = 3 };

	class CPrintFormObject
	{
	public:
		void Input(CString &cs);
		void Print(CDC * pDC, CPoint offset);
		CFont * CreateFont(CFont &ft, CDC * pDC, const int iDiv);
		CPrintFormObject();
		virtual ~CPrintFormObject();
		CRect		rc;
		char		cId[64];
		char		cCond[64];
		char		cId2[64];
		bool		bBold, bItalic, bUnderline;
		char		cFont[64];
		int			iSize;
		int			iType;
		int			iBack;
		COLORREF	crBack, crFront, crBdr;
		int			exInfo;
		int			iBorder, iBorderSize;
		UINT		uiTextFormat;
		bool		bSelected;
	};

	CPrintFormObject cPrintObject;

	void Clear();
	bool LoadPage(const char * cFileName, const char * cPageName);
	CFormJob();
	virtual ~CFormJob();

	CString			csPageName, csScriptFile;
	CRect			rcPage;
	CStringArray	csObjectArray;



public:
	bool HasSubForm(CString &csName, CSize &szItem);
	void Print(CDC * pDC);
	int GetPrintObjectCount();
	bool SelectPrintObject(const int idx);
	static void Parse2String(CString &src, CString &name, CString &value);
	static void GetNextValue(CString &src, CString &value);
	static CString RGBTOHEX(COLORREF cr);
	static COLORREF HEXTORGB(CString cs);
};

#endif // !defined(AFX_FORMJOB_H__F2067439_101A_11D2_8432_0000B43382FE__INCLUDED_)
