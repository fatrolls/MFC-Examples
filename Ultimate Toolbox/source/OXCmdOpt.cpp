// ==========================================================================
// 							Class Implementation : COXCommandOptions
// ==========================================================================

// Source file : OXCmdOpt.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"				
#include "OXCmdOpt.h"
#include "OXCmdlex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXCommandOptions, CObject)

#define new DEBUG_NEW

COXCommandOptions::COXCommandOptions()
	{
	}

COXCommandOptions::~COXCommandOptions()
	{
	for (int i = m_CmdOptDescList.GetSize() - 1; i >= 0 ; i--)
		{
		delete m_CmdOptDescList[i];
		}

	ResetMaps();
	}

void COXCommandOptions::ResetMaps()
	{
	POSITION pos = m_Values.GetStartPosition();
	CString sKey;
	CObject* pVal;
	while (pos != NULL)
		{
		m_Values.GetNextAssoc(pos, sKey, pVal);
		delete pVal;
		}	
	
	m_Values.RemoveAll();
	m_AbbrMap.RemoveAll();
	}

void COXCommandOptions::Add(COXCommandOptionDesc* pOptionDesc)
	{
	BOOL bInserted = FALSE;
	COXCommandOptionDesc* pNewOptDesc = new COXCommandOptionDesc(*pOptionDesc);
	
	for (int i = 0; i < m_CmdOptDescList.GetSize(); i++)
		{
		CString sArrayElement = ((COXCommandOptionDesc*)(m_CmdOptDescList[i]))->GetOptName();
		CString sNewElement = pNewOptDesc->GetOptName();
		// Insert with longest GetOptName's first
		// assume this makes a difference to the order of the AbbrMap ???
		if (sNewElement.GetLength() >= sArrayElement.GetLength())
			{
			bInserted = TRUE;
			m_CmdOptDescList.InsertAt(i, pNewOptDesc, 1);
			break;
			}
		}

	if (!bInserted)
		m_CmdOptDescList.Add(pNewOptDesc);
	}

void COXCommandOptions::Add(LPCTSTR pszcOptionName, int iFlags,
							LPCTSTR pszcDescription, LPCTSTR pszcAbbr /* = _T("") */)
	{
	COXCommandOptionDesc Cod(pszcOptionName, iFlags, pszcDescription, pszcAbbr);
	Add(&Cod);
	}

BOOL COXCommandOptions::Remove(LPCTSTR pszcOption)
	{
	CString sOption = pszcOption;
	sOption.MakeUpper();
	CObject* pTmp = NULL;
	
	// what kind of option is it?
	if (m_Values.Lookup(sOption, pTmp))
		{
		// delete the list of values associated with this option
		delete (CMapStringToString*)pTmp;
		}
		
	// Remove the entry from the values list
	m_Values.RemoveKey(sOption);

	// Remove the entry from the abbreviations list
	m_AbbrMap.RemoveKey(sOption);

	BOOL bFound(FALSE);
	for (int i = 0; i < m_CmdOptDescList.GetSize(); i++)
		{
		COXCommandOptionDesc* pOpt = (COXCommandOptionDesc*)m_CmdOptDescList[i];
		if (pOpt->GetOptName() == sOption)
			{
			delete pOpt;
			m_CmdOptDescList.RemoveAt(i);
			bFound = TRUE;
			break;
			}
		}

	return bFound;
	}

// walk through CmdOptDescList, gathering .GetOptName() abbreviations
void COXCommandOptions::BuildAbbrTable()
	{
	CStringArray	Abbray;		// Abbreviation Array :-)
	CUIntArray		Indaray;	// Index Array
	CStringArray	Clash;		// Clash array
	
	// Initialize Abbray with complete option names (and Indaray with pointers)
	// This array is size sorted because CmdOptDescList is size sorted
	for (int i = 0; i < m_CmdOptDescList.GetSize(); i++)
		{
		Abbray.Add(((COXCommandOptionDesc*)(m_CmdOptDescList[i]))->GetOptName());
		Indaray.Add(i);
		CString sReqAbbr = ((COXCommandOptionDesc*)(m_CmdOptDescList[i]))->GetOptAbbr();
		if (sReqAbbr.GetLength())
			{
			Abbray.Add(sReqAbbr);
			Indaray.Add(i);
			}
		}
	
	// Now walk through AbbrMap extending it as we go with abbreviations
    int iAbbr;
	for (iAbbr = 0;iAbbr < Abbray.GetSize(); iAbbr++)
		{
		CString sAbbr = Abbray[iAbbr];
		// Abbr is the name already in the map
		int iNewAbbrLength = sAbbr.GetLength() - 1;
		if (iNewAbbrLength)
			{		// No zero length abbreviations
			// NewAbbr is the name we are trying to add to map
			CString sNewAbbr = sAbbr.GetBufferSetLength(iNewAbbrLength);
			
			// See if sNewAbbr is unique (ignoring all the entries we've already processed)
			BOOL bUnique = TRUE;
			
			int iCmp;
			for (iCmp = iAbbr+ 1; iCmp < Abbray.GetSize(); iCmp++)
				{
				// Is sNewAbbr an abbreviation of sCmp?
				// Assumes that Left() returns all characters (without
				// complaint) in the case that Left() is passed a number
				// larger than the string length.
				CString sCmp = Abbray.GetAt(iCmp).Left(sNewAbbr.GetLength());
				
				if (sCmp == sNewAbbr)
					{
					// sNewAbbr is not unique ... abandon it
					bUnique = FALSE;
					break;
					}
				}
			// Did we previously find a clash that's a substring of sNewAbbr
			if (bUnique)
				{
				for (int iClash = 0; iClash < Clash.GetSize(); iClash++)
					{
					CString sCmp = Clash.GetAt(iClash);
					if (sCmp == sNewAbbr)
						{
						bUnique = FALSE;
						break;
						}
					}
				}
			
			if (bUnique)
				{
				Abbray.Add(sNewAbbr);
				Indaray.Add(Indaray[iAbbr]);
				}
			else
				{
				Clash.Add(sNewAbbr);
				}
			}
		}
	
	ASSERT(Abbray.GetSize() == Indaray.GetSize());
	
	// Hmmm, this will freak if user calls this twice ... handle that case -tab
	ASSERT(m_AbbrMap.GetCount() == 0);
	
	// Now Build AbbrMap from Abbray and Indaray
	for (int j = 0; j < Abbray.GetSize(); j++)
		{
		m_AbbrMap.SetAt(Abbray[j], m_CmdOptDescList[Indaray[j]]);
		}
	}

// 	Construct array of actual parameters based on command line
CString COXCommandOptions::ParseCmdLine(COXCommandLine& cl, CStringList* pRestList /* = NULL */)
	{
	CString sReturn;
	
	// Clear all previous maps and rebuild afterwards
	ResetMaps();
	BuildAbbrTable();

    int iNumArgs = cl.GetNumArgs();
    for (int iArg = 0; iArg < iNumArgs; iArg++)
		{
		if ((cl[iArg][0] == _T('-')) || (cl[iArg][0] == _T('/')))
			{
			CString sToken = cl[iArg].Mid(1);
			sToken.MakeUpper();
			COXCommandOptionDesc* Opt = (COXCommandOptionDesc*)m_AbbrMap[sToken];
			
			if (Opt != NULL)
				{	// Valid switch or abbreviation
				CObject* pTmp = NULL;
				BOOL bIsAlreadyThere = m_Values.Lookup(Opt->GetOptName(), pTmp);
				if (bIsAlreadyThere && (!Opt->IsRepeatable()))
					{
					TCHAR msg[80];
					_stprintf(msg, _T("%s can only be specified once\r\n"), sToken);
					TRACE(msg);
					THROW(new COXCommandLineException(msg, this));
					}
				else if (bIsAlreadyThere && Opt->ReturnsFirstRep())
					{
					// It's already there ... do nothing
					}
				else
					{
					// Either it's not already there or it is already
					// there and repetitions are allowed
						
					// Assign new value to insert to sValue
					if (!Opt->TakesArg())
						{
						m_Values[Opt->GetOptName()] = new CStringList;
						}
					else if (Opt->ReturnsAssociative())
						{
						if (iArg + 2 > iNumArgs - 1)
							{
							TCHAR msg[80];
							_stprintf(msg, _T("%s requires 2 arguments\r\n"), Opt->GetOptName());
							TRACE(msg);
							THROW(new COXCommandLineException(msg, this));
							}

						CMapStringToString* assocmap;
						if (!m_Values.Lookup(Opt->GetOptName(), pTmp))
							{
							assocmap = new CMapStringToString;
							m_Values[Opt->GetOptName()] = assocmap;
							}
						else
							{
							assocmap = (CMapStringToString*)pTmp;
							}

						CString sKey = cl[++iArg];
						(*assocmap)[sKey] = cl[++iArg];						
						}
					else if (Opt->ReturnsArray())
						{
						if (iArg + 1 > iNumArgs - 1)
							{
							TCHAR msg[80];
							_stprintf(msg, _T("%s requires an argument\r\n"), Opt->GetOptName());
							TRACE(msg);
							THROW(new COXCommandLineException(msg, this));
							}

						CStringList* pVals;
						if (!m_Values.Lookup(Opt->GetOptName(), pTmp))
							{
							pVals = new CStringList;
							m_Values[Opt->GetOptName()] = pVals;
							}
						else
							{
							pVals = (CStringList*)pTmp;
							}

						pVals->AddTail(cl[++iArg]);
						}
					else
						{
						// It's not already there and we expect an argument
	
						if ((cl[iArg + 1] == _T("|")) || (cl[iArg + 1][0] == _T('-')) || (cl[iArg + 1][0] == _T('/')))
							{
							TCHAR msg[80];
							_stprintf(msg, _T("%s requires an argument\r\n"), Opt->GetOptName());
							TRACE(msg);
							THROW(new COXCommandLineException(msg, this));
							}

						CObject* pTmp;
						if (m_Values.Lookup(Opt->GetOptName(), pTmp))
							{
							delete pTmp;
							}

						CStringList* pVals = new CStringList;
						pVals->AddTail(cl[++iArg]);
						m_Values[Opt->GetOptName()] = pVals;
						}
					}
				
				}
			else
				{
				TCHAR msg[80];
				_stprintf(msg, _T("%s is not a valid switch\r\n"), sToken);
				TRACE(msg);
				THROW(new COXCommandLineException(msg, this));
				}
			}
		else
			{
			if (pRestList != NULL)
				{
				ASSERT(pRestList->IsKindOf(RUNTIME_CLASS(CStringList)));
				pRestList->AddTail(cl[iArg]);
				}

	        sReturn += cl[iArg] + _T(" ");
			}
		}
	
    // Glue the remaining strings back together
    while (iArg < cl.GetNumArgs())
		{
        sReturn += cl[iArg++] + _T(" ");
		}
    
	return sReturn;
	}

const COXCommandOptionDesc* COXCommandOptions::GetOptionObject(LPCTSTR psczOption) const
	{
	CString sOption(psczOption);
	sOption.MakeUpper();
	BOOL bFound(FALSE);
	COXCommandOptionDesc* pOpt = NULL;
	for (int i = 0; i < m_CmdOptDescList.GetSize(); i++)
		{
		pOpt = (COXCommandOptionDesc*)m_CmdOptDescList[i];
		if (pOpt->GetOptName() == sOption)
			{
			bFound = TRUE;
			break;
			}
		}
	
	return bFound ? pOpt : NULL;
	}

BOOL COXCommandOptions::IsEnabled(LPCTSTR pszcOption) const
	{
	CString sOption = pszcOption;
	sOption.MakeUpper();
	CObject* pTmp;
	return (m_Values.Lookup(sOption, pTmp));
	}

CString COXCommandOptions::GetValue(LPCTSTR pszcOption) const
	{
	CString sOption = pszcOption;
	sOption.MakeUpper();
	COXCommandOptionDesc* pOpt = NULL;
	CObject* pTmp = NULL;
	
	m_AbbrMap.Lookup(sOption, pTmp);
	pOpt = (COXCommandOptionDesc*)pTmp;
	ASSERT(pOpt != NULL && !pOpt->ReturnsArray() && !pOpt->ReturnsAssociative());
	CStringList* pList;
	if (m_Values.Lookup(sOption, pTmp))
		{
		pList = (CStringList*)pTmp;
		
		return pList->GetHead();
		}
	else
		{
		return _T("");
		}
	}

const CStringList* COXCommandOptions::GetValues(LPCTSTR pszcOption) const
	{
	CString sOption = pszcOption;
	sOption.MakeUpper();
	COXCommandOptionDesc* pOpt = NULL;
	CObject* pTmp = NULL;

	m_AbbrMap.Lookup(sOption, pTmp);
	pOpt = (COXCommandOptionDesc*)pTmp;
	ASSERT(pOpt != NULL && pOpt->ReturnsArray());
	if (m_Values.Lookup(sOption, pTmp))
		{
		return (CStringList*)pTmp;
		}
	else
		{
		return NULL;
		}
	}

const CMapStringToString* COXCommandOptions::GetAssocPairs(LPCTSTR pszcOption) const
	{
	CString sOption = pszcOption;
	sOption.MakeUpper();
	COXCommandOptionDesc* pOpt = NULL;
	CObject* pTmp = NULL;

	m_AbbrMap.Lookup(sOption, pTmp);
	pOpt = (COXCommandOptionDesc*)pTmp;
	ASSERT(pOpt != NULL && pOpt->ReturnsAssociative());
	if (m_Values.Lookup(sOption, pTmp))
		{
		return (CMapStringToString*)pTmp;
		}
	else
		{
		return NULL;
		}
	}

CString COXCommandOptions::Usage(LPCTSTR pszcMsg) const
	{
	CString sMsg(pszcMsg);
	
	sMsg += _T("\n");
	
	CString sLine;
	for (int i = 0; i < m_CmdOptDescList.GetSize(); i++)
		{
		COXCommandOptionDesc* pOpt = (COXCommandOptionDesc*)m_CmdOptDescList[i];
		CString sAbbr = pOpt->GetOptAbbr();
		if (sAbbr.GetLength() != 0)
			{
			CString sTmp(_T("(-"));
			sTmp += sAbbr;
			sTmp += _T(")");
			sAbbr = sTmp;
			}

		_stprintf(sLine.GetBuffer(100), _T("-%s\t%s\t%s\n"), pOpt->GetOptName(), sAbbr, pOpt->GetDescription());
		sLine.ReleaseBuffer();
		sMsg += sLine;
		}

	return sMsg; 
	}
		



