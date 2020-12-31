/* Copyright (c) 1998 Sasha Djolich */
/* For questions or comments, contact the author at djolic@netinfo.ubc.ca */


#pragma once


class CRegistry
{
public:
	enum
	{
		modeCurrentUserPrefs = 0,
		modeDefUserPrefs,
		modeLocalMachineProps,
		
		accessRead  = 0x1,
		accessWrite = 0x2,
	};

// Construction/Destruction
public:
	CRegistry(const char* ApplicationName, int Mode = modeCurrentUserPrefs, int Access = accessRead | accessWrite);
	CRegistry(HKEY Area, const char* RootSection, int Access = accessRead | accessWrite);
	~CRegistry();
	
// Attributes
public:
	void SetRootSection(const char* ApplicationName, int Mode = modeCurrentUserPrefs);
	void SetRootSection(HKEY Area, const char* RootSection);

	void SetAccess(int Access = accessRead | accessWrite);

// Iteration
public:
	POSITION	GetFirstKeyPos();
	CString		GetNextKey(POSITION& Pos);

	POSITION	GetFirstSectionPos();
	CString		GetNextSection(POSITION& Pos);

// Operations
public:
	void Descend(const char* Section);
	void Ascend();

	bool KeyExists(const char* Key);
	bool SectionExists(const char* Section);

	void Store(const char* Key, signed char Value);
	void Store(const char* Key, unsigned char Value);
	void Store(const char* Key, signed short Value);
	void Store(const char* Key, unsigned short Value);
	void Store(const char* Key, signed int Value);
	void Store(const char* Key, unsigned int Value);
	void Store(const char* Key, signed long Value);
	void Store(const char* Key, unsigned long Value);
	void Store(const char* Key, float Value);
	void Store(const char* Key, double Value);
	void Store(const char* Key, const CString& Value);

	void Restore(const char* Key, signed char& Value);
	void Restore(const char* Key, unsigned char& Value);
	void Restore(const char* Key, signed short& Value);
	void Restore(const char* Key, unsigned short& Value);
	void Restore(const char* Key, signed int& Value);
	void Restore(const char* Key, unsigned int& Value);
	void Restore(const char* Key, signed long& Value);
	void Restore(const char* Key, unsigned long& Value);
	void Restore(const char* Key, float& Value);
	void Restore(const char* Key, double& Value);
	void Restore(const char* Key, CString& Value);

private:
	void OpenRoot(HKEY Area, const CString& RootSection, int Access);
	void Close();

	void StoreDWORD(const char* Key, DWORD Value);
	void StoreString(const char* Key, const CString& Value);

	void RestoreDWORD(const char* Key, DWORD& Value);
	void RestoreString(const char* Key, CString& Value);

	HKEY	mRootArea;
	CString mRootSection;
	
	HKEY	mActiveSectionKey;
	CString mActiveSection;

	int		mAccess;
};
