// DaoSet.h : interface of the CDAORecordset class
//
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
  char* FieldID;		// field name
  short Type;			// field type
  short Len;			// length for text only
  BOOL  bRequired;		// TRUE when required
  BOOL  bAllowZero;		// TRUE when zero allowing
} TABLEFIELD;			// table field infos

typedef struct
{
  int nFields;			// number of fields for this key
  LPCSTR* FieldInfoName;	// field name array
  LPCSTR strName;		// key name
  BOOL bPrimary;		// true for primary key
  BOOL bUnique;			// true if unique
  BOOL bRequired;		// true if requiered
} TABLEKEY;			// table key infos

typedef struct
{
  LPCSTR lpcsTableName;		// table name
  TABLEFIELD *pFieldInfo;	// table field infos
  TABLEKEY *pKeyInfo;		// table key infos
} TABLESET;			// table record set info

class CDAORecordset : public CDaoRecordset
{
public:
	CDAORecordset(CDaoDatabase* pDatabase = NULL);
	~CDAORecordset();
	DECLARE_DYNAMIC(CDAORecordset);

	// Attributes
	int m_OpenCount;
	CString m_strKey;
	CDaoTableDefInfo m_TableDefInfo;
	long GetRecordCount();

	// Overrides
	virtual void Open(int nOpenType = AFX_DAO_USE_DEFAULT_TYPE, LPCTSTR lpszSQL = NULL, int nOptions = 0);
	virtual void Close();
};

extern LPCSTR lpcsPrimaryKey;
