/////////////////////////////////////////////////////////////////////////////
//
//                           Public Domain.
//
/////////////////////////////////////////////////////////////////////////////
//
//
//  File     :   CTAddIn.cpp
//
//  Author   :   Darren Richards (darrenr@gissing-consulting.co.uk)
//
//  Date     :   20th March 98
//
//  Synopsis :   Implementation of CTAddIn object - where it all happens.
//
////////////////

/////////////////////////////////////////////////////////////////////////////
//
//  includes
//
///////////////

#include "stdafx.h"
#include "CodeTmpl.h"
#include "CTAddIn.h"
#include "PopMenu.h"

/////////////////////////////////////////////////////////////////////////////
//
//  TemplateData comparitors - just to keep STL happy
//
///////////////

bool operator==(TemplateData t1, TemplateData t2)
{
    return true;
}

bool operator<(TemplateData t1, TemplateData t2)
{
    return true;
}

/////////////////////////////////////////////////////////////////////////////
//
//  CCTAddIn implmentaion
//
///////////////

HRESULT CCTAddIn::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime, long dwAddInID, VARIANT_BOOL* bOnConnection)
{
	HRESULT hr      = S_OK;
	m_spApplication = pApp;
	m_dwAddInID     = dwAddInID;

    //
    //  tell devstudio about ourselves
    //

	hr = pApp->SetAddInInfo((long)_Module.GetModuleInstance(), 
		                    static_cast<ICTAddIn*>(this),
                            IDB_TOOLBAR_MEDIUM_CTADDIN,
                            IDB_TOOLBAR_LARGE_CTADDIN,
                            dwAddInID);
    //
    //  add our commands to developer studio
    //

	VARIANT_BOOL bRet;

	if (SUCCEEDED(hr))
	{
		hr = pApp->AddCommand(CComBSTR(_T("CTInsCodeTmpl\nInsert Code Template\nInsert Code Template\nInsert Code Template")),
                              CComBSTR(_T("CTInsCodeTmpl")), 0, dwAddInID, &bRet);
	}

    //
    //  first time round we also wire up our toolbar
    //

	if (bFirstTime)
	{
		if (SUCCEEDED(hr))
		{
			hr = pApp->AddCommandBarButton(dsGlyph, CComBSTR(_T("CTInsCodeTmpl")), dwAddInID);
		}
	}

    //
    //  read in the template definitions from our magic text file
    //

    try
    {
        ReadTmplFile();
    }

    catch(...)
    {
        ATLTRACE("Bang : ReadTmplFile() failed in OnConnection.\r\n");
    }

	*bOnConnection = SUCCEEDED(hr) ? VARIANT_TRUE :VARIANT_FALSE;
	return hr;
}

HRESULT CCTAddIn::OnDisconnection(VARIANT_BOOL bLastTime)
{
	return S_OK;
}

HRESULT CCTAddIn::CTInsCodeTmpl()
{
    try
    {
        //
        //  if the user is pressing control whilst clicking the toolbar 
        //  button then we refresh things by re-reading our template file
        //

        if ( (UINT)GetAsyncKeyState(VK_CONTROL) > 1)
            ReadTmplFile();

        //
        //  get the mouse position so we can put the menu up next to our toolbar button
        //

        POINT pt;
        GetCursorPos(&pt);

        //
        //  create our popup menu, and populate it from our template data
        //

        CPopupMenu mnu(pt);

        VecTemplateDataIter it = m_vecTemplateData.begin();

        int nId = 1;

        while (it != m_vecTemplateData.end())
        {
            if (it->strName.length())
                mnu.AddItem(nId, it->strName.c_str());
            else
                mnu.AddSeparator();

            nId++;
            it++;
        }

        //
        //  display our popup menu (modally)
        //

        nId = mnu.TrackPopup();

        //
        //  if user selected something we insert the template text...
        //

        if (nId > 0)
        {
            CComPtr<IDispatch> spDispTextSel;
            CComPtr<IDispatch> spDispActDoc;

            //
            //  retrieve our references to the editor components  
            //

            m_spApplication->get_ActiveDocument(&spDispActDoc);

            if (spDispActDoc == NULL)
                return S_OK;

            CComQIPtr<ITextDocument,&IID_ITextDocument> spActDoc(spDispActDoc); 

            spActDoc->get_Selection(&spDispTextSel);

            if (spDispTextSel == NULL)
                return S_OK;

            CComQIPtr<ITextSelection,&IID_ITextSelection> spTextSel(spDispTextSel);

            //
            //  remember our starting cursor location
            //

            long lStartLine;
            long lStartColumn;

            spTextSel->get_CurrentLine(&lStartLine);
            spTextSel->get_CurrentColumn(&lStartColumn);

            //
            //  glue the template text into the editor, remember nId is 1-relative
            //

            spTextSel->put_Text(CComBSTR(m_vecTemplateData[nId-1].strText.c_str()));

            //
            //  retrieve the cursor position of where we ended up
            //

            long lEndLine;
            long lEndColumn;

            spTextSel->get_CurrentLine(&lEndLine);
            spTextSel->get_CurrentColumn( &lEndColumn );

            //
            //  hilight the stuff we entered, and smart format it
            //  (primarily 'cos devstudio makes a bit of a mess of it,
            //   if we don't)
            //

            spTextSel->MoveTo(lStartLine, 1, CComVariant(dsMove));
            spTextSel->MoveTo(lEndLine, 1, CComVariant(dsExtend));
            spTextSel->SmartFormat();

            //
            //  restore cursor back to end position
            //

            spTextSel->MoveTo(lEndLine, lEndColumn, CComVariant(dsMove));
        }
    }

    catch(...)
    {
        ATLTRACE("Bang : CTInsCodeTmpl failed.\r\n");
    }

    return S_OK;
}
 
void CCTAddIn::ReadTmplFile()
{
    TemplateData td; // buffer for current template

    enum { PS_Tag, PS_Template } eState = PS_Tag; // parsing state

    //
    //  compose the path for the code template file, which
    //  lives in the SharedIDE directory of devstudio. This is
    //  pointed to by the MS provided environment variable
    //  MSDevDir.
    //

    string strMSDevDir = getenv("MSDevDir");
    string strTmplFile = strMSDevDir + "\\CodeTmpl.txt";

    //
    //  ensure our current template data is cleared down first, so
    //  that we can refresh things on the fly
    //

    m_vecTemplateData.erase(m_vecTemplateData.begin(), m_vecTemplateData.end());

    //
    //  open our template data file...
    //

    ifstream ifs(strTmplFile.c_str());

    //
    //  ...and whilst we still got some left...
    //

    while (ifs)
    {
        char szLine[200] = "\0";

        //
        //  ...pull in the next line
        //

        ifs.getline(szLine, sizeof(szLine));
        string strLine = szLine;

        //
        //  handle it according to parsing state (PS_Tag or PS_Template),
        //  we are either looking for the openning #{ tag or reading
        //  template text for the current template and looking for the
        //  closing #} which terminates a template definition
        //

        if (eState == PS_Tag)
        {
            //
            //  does this line look like an openning #{ tag...
            //

            if (strLine.length() > 2 && strLine.substr(0, 2) == "#{" )
            {
                //
                //  ...yep, grab the template name which immediately follows
                //  the #{ tag, and switch to PS_Template state.
                //

                td.strName = strLine.substr(2);
                td.strText = "";
                eState = PS_Template;
            } 

            //
            //  a pair (or more) of hashes inserts a separator on the popup menu
            //

            else if (strLine.length() > 2 && strLine.substr(0, 2) == "##" )
            {
                td.strName = "";
                td.strText = "";
                m_vecTemplateData.push_back(td);
            }

            // ignore all other rubbish !
        }

        else 
        {
            //
            //  does this line look like a closing #} tag...
            //

            if (strLine.length() >= 2 && strLine.substr(0, 2) == "#}" ) 
            {
                //
                //  ...yep, push current template data into vector, and
                //  switch to PS_Tag state
                //

                m_vecTemplateData.push_back(td);
                eState = PS_Tag;
            }

            else
            {
                //
                //  ...nope, just append the line to our current template definition
                //

                td.strText += strLine;
                td.strText += "\r\n";
            } 

        } // if (eState == PS_Tag)

    } // while (ifs)
}


