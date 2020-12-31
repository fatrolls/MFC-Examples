// ==========================================================================
//				Inline Implementation : COXBlob
// ==========================================================================

// Source file : OXBlob.inl

// Source : R.Mortelmans
// Creation Date : 	   7th March 1996
// Last Modification : 7th March 1996
			  
// //////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Definition of static members

// Member functions ---------------------------------------------------------
// public:
inline COXBlob::COXBlob()
	{
	}

inline COXBlob::COXBlob(const COXBlob& blobSrc)
	{
	Copy(blobSrc);
	}

inline COXBlob::COXBlob(const CByteArray& arrSrc)
	{
	Copy(arrSrc);
	}

inline COXBlob::COXBlob(const VARIANT& varSrc)
	{
	CopyVariant(&varSrc);
	}

inline COXBlob::COXBlob(LPCVARIANT pSrc)
	{
	CopyVariant(pSrc);
	}

inline COXBlob::COXBlob(const COleVariant& varSrc)
	{
	CopyVariant(&varSrc);
	}

inline COXBlob::COXBlob(const COXVariant& varSrc)
	{
	CopyVariant(&varSrc);
	}

inline COXBlob& COXBlob::operator=(const COXBlob& blobSrc)
	{
	if(this==&blobSrc)
		return *this;
	Copy(blobSrc);
	return *this;
	}

inline COXBlob& COXBlob::operator=(const CByteArray& arrSrc)
	{
	Copy(arrSrc);
	return *this;
	}

inline COXBlob& COXBlob::operator=(const VARIANT& varSrc)
	{
	CopyVariant(&varSrc);
	return *this;
	}

inline COXBlob& COXBlob::operator=(LPCVARIANT pSrc)
	{
	CopyVariant(pSrc);
	return *this;
	}

inline COXBlob& COXBlob::operator=(const COleVariant& varSrc)
	{
	CopyVariant(&varSrc);
	return *this;
	}

inline COXBlob& COXBlob::operator=(const COXVariant& varSrc)
	{
	CopyVariant(&varSrc);
	return *this;
	}

inline COXBlob::~COXBlob()
	{
	}

// protected:
// private:

// ==========================================================================
