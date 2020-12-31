/////////////////////////////////////////////////////////////////////////////
// CDocument MAPI support

void CDocument::OnFileSendMail()
{
   ASSERT_VALID(this);
   ASSERT(_afxIsMailAvail);   // update handler always gets called first

   CWaitCursor wait;

   _AFX_MAIL_STATE* pMailState = _afxMailState;
   if (pMailState->m_hInstMail == NULL)
      pMailState->m_hInstMail = ::LoadLibraryA("MAPI32.DLL");

   if (pMailState->m_hInstMail == NULL)
   {
      AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
      return;
   }
   ASSERT(pMailState->m_hInstMail != NULL);

   ULONG (PASCAL *lpfnSendMail)(ULONG, ULONG, MapiMessage*, FLAGS, ULONG);
   (FARPROC&)lpfnSendMail = GetProcAddress(pMailState->m_hInstMail, "MAPISendMail");
   if (lpfnSendMail == NULL)
   {
      AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
      return;
   }
   ASSERT(lpfnSendMail != NULL);

   TCHAR szTempName[_MAX_PATH];
   TCHAR szPath[_MAX_PATH];
   BOOL bRemoveTemp = FALSE;
   if (m_strPathName.IsEmpty() || IsModified())
   {
      // save to temporary path
      VERIFY(GetTempPath(_countof(szPath), szPath) != 0);
      VERIFY(GetTempFileName(szPath, _T("afx"), 0, szTempName) != 0);

      // save it, but remember original modified flag
      BOOL bModified = IsModified();
      BOOL bResult = DoSave(szTempName, FALSE);
      SetModifiedFlag(bModified);
      if (!bResult)
      {
         TRACE0("Warning: file save failed during File.Send Mail.\n");
         return;
      }
      bRemoveTemp = TRUE;
   }
   else
   {
      // use actual file since it isn't modified
      lstrcpyn(szTempName, m_strPathName, _countof(szTempName));
   }
#ifdef _UNICODE
   char szTempNameA[_MAX_PATH];
   _wcstombsz(szTempNameA, szTempName, _countof(szTempNameA));
#endif

   // build an appropriate title for the attachment
   TCHAR szTitle[_MAX_PATH];
   if (!m_strPathName.IsEmpty())
      AfxGetFileName(m_strPathName, szTitle, _countof(szTitle));
   else
   {
      lstrcpyn(szTitle, m_strTitle, _countof(szTitle));
      if (m_strTitle.Find('.') == -1) // no extension
      {
         // append the default suffix if there is one
         CString strExt;
         CDocTemplate* pTemplate = GetDocTemplate();
         if (pTemplate != NULL &&
            pTemplate->GetDocString(strExt, CDocTemplate::filterExt))
         {
            lstrcat(szTitle, strExt);
         }
      }
   }

#ifdef _UNICODE
   char szTitleA[_MAX_PATH];
   _wcstombsz(szTitleA, szTitle, _countof(szTitleA));
#endif

   // prepare the file description (for the attachment)
   MapiFileDesc fileDesc;
   memset(&fileDesc, 0, sizeof(fileDesc));
   fileDesc.nPosition = (ULONG)-1;
#ifdef _UNICODE
   fileDesc.lpszPathName = szTempNameA;
   fileDesc.lpszFileName = szTitleA;
#else
   fileDesc.lpszPathName = szTempName;
   fileDesc.lpszFileName = szTitle;
#endif

   // prepare the message (empty with 1 attachment)
   MapiMessage message;
   memset(&message, 0, sizeof(message));
   message.nFileCount = 1;
   message.lpFiles = &fileDesc;

   // prepare for modal dialog box
   AfxGetApp()->EnableModeless(FALSE);
   HWND hWndTop;
   CWnd* pParentWnd = CWnd::GetSafeOwner(NULL, &hWndTop);

   // some extra precautions are required to use MAPISendMail as it
   // tends to enable the parent window in between dialogs (after
   // the login dialog, but before the send note dialog).
   pParentWnd->SetCapture();
   ::SetFocus(NULL);
   pParentWnd->m_nFlags |= WF_STAYDISABLED;

   int nError = lpfnSendMail(0, (ULONG)pParentWnd->GetSafeHwnd(),
      &message, MAPI_LOGON_UI|MAPI_DIALOG, 0);

   // after returning from the MAPISendMail call, the window must
   // be re-enabled and focus returned to the frame to undo the workaround
   // done before the MAPI call.
   ::ReleaseCapture();
   pParentWnd->m_nFlags &= ~WF_STAYDISABLED;

   pParentWnd->EnableWindow(TRUE);
   ::SetActiveWindow(NULL);
   pParentWnd->SetActiveWindow();
   pParentWnd->SetFocus();
   if (hWndTop != NULL)
      ::EnableWindow(hWndTop, TRUE);
   AfxGetApp()->EnableModeless(TRUE);

   if (nError != SUCCESS_SUCCESS &&
      nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
   {
      AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
   }

   // remove temporary file, if temporary file was used
   if (bRemoveTemp)
      CFile::Remove(szTempName);
}

