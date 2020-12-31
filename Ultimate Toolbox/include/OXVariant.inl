// ==========================================================================
//				Inline Implementation : COXVariant
// ==========================================================================

// Source file : OXVariant.inl

// Source : R.Mortelmans
// Creation Date : 	   7th March 1996
// Last Modification : 7th March 1996
			  
// //////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Definition of static members

// Member functions ---------------------------------------------------------
// public:
inline COXVariant::COXVariant()
	:
	COleVariant()
	{
	}

inline COXVariant::COXVariant(const VARIANT& varSrc)
	:
	COleVariant(varSrc)
	{
	}

inline COXVariant::COXVariant(LPCVARIANT pSrc)
	:
	COleVariant(pSrc)
	{
	}

inline COXVariant::COXVariant(const COleVariant& varSrc)
	:
	COleVariant(varSrc)
	{
	}

inline COXVariant::COXVariant(const COXVariant& varSrc)
	:
	COleVariant((COleVariant) varSrc)
	{
	}

inline COXVariant::COXVariant(LPCTSTR lpszSrc)
	:
	COleVariant(lpszSrc)
	{
	}

inline COXVariant::COXVariant(CString& strSrc)
	:
	COleVariant(strSrc)
	{
	}

inline COXVariant::COXVariant(BYTE nSrc)
	:
	COleVariant(nSrc)
	{
	}

inline COXVariant::COXVariant(short nSrc, VARTYPE vtSrc /* = VT_I2 */)
	:
	COleVariant(nSrc, vtSrc)
	{
	}

inline COXVariant::COXVariant(long lSrc, VARTYPE vtSrc /* = VT_I4 */)
	:
	COleVariant(lSrc, vtSrc)
	{
	}

inline COXVariant::COXVariant(const COleCurrency& curSrc)
	:
	COleVariant(curSrc)
	{
	}

inline COXVariant::COXVariant(bool bSrc)
	:
	COleVariant((short)bSrc, VT_BOOL)
	{
	}

inline COXVariant::COXVariant(float fltSrc)
	:
	COleVariant(fltSrc)
	{
	}

inline COXVariant::COXVariant(double dblSrc)
	:
	COleVariant(dblSrc)
	{
	}

inline COXVariant::COXVariant(const COleDateTime& timeSrc)
	:
	COleVariant(timeSrc)
	{
	}

inline COXVariant::COXVariant(const CByteArray& arrSrc)
	:
	COleVariant(arrSrc)
	{
	}

inline COXVariant::COXVariant(const CLongBinary& lbSrc)
	:
	COleVariant(lbSrc)
	{
	}

inline COXVariant::COXVariant(LPCTSTR lpszSrc, VARTYPE vtSrc)
	:
	COleVariant(lpszSrc, vtSrc)
	{
	}

inline const COXVariant& COXVariant::operator=(const VARIANT& varSrc)
	{
	COleVariant::operator=(varSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(LPCVARIANT pSrc)
	{
	COleVariant::operator=(pSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(const COXVariant& varSrc)
	{
	COleVariant::operator=(varSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(const COleVariant& varSrc)
	{
	COleVariant::operator=(varSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(const LPCTSTR lpszSrc)
	{
	COleVariant::operator=(lpszSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(const CString& strSrc)
	{
	COleVariant::operator=(strSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(BYTE nSrc)
	{
	COleVariant::operator=(nSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(short nSrc)
	{
	COleVariant::operator=(nSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(long lSrc)
	{
	COleVariant::operator=(lSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(const COleCurrency& curSrc)
	{
	COleVariant::operator=(curSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(bool bSrc)
   {
   vt = VT_BOOL;
   
   if (!bSrc)
      V_BOOL(this) = AFX_OLE_FALSE;
   else
      V_BOOL(this) = AFX_OLE_TRUE;

	return *this;
   }

inline const COXVariant& COXVariant::operator=(float fltSrc)
	{
	COleVariant::operator=(fltSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(double dblSrc)
	{
	COleVariant::operator=(dblSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(const COleDateTime& dateSrc)
	{
	COleVariant::operator=(dateSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(const CByteArray& arrSrc)
	{
	COleVariant::operator=(arrSrc);
	return *this;
	}

inline const COXVariant& COXVariant::operator=(const CLongBinary& lbSrc)
	{
	COleVariant::operator=(lbSrc);
	return *this;
	}

inline COXVariant::~COXVariant()
	{
	}

// protected:
// private:

// ==========================================================================
