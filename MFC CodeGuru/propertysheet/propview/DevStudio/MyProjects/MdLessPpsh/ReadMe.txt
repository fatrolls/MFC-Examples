Creating modeless property sheet as "view" inside of the child frame, without view.
This is standard MFC MDI project.

Modeless property page displays all buttons (i.e. OK CANCEL, APPLY and HELP.)
This is quite simple: derive your own class from CPropertySheet.
Override virtual OnInitDialog as follows:

BOOL CModelessPpsh::OnInitDialog() 
{
	m_bModeless = FALSE;
	BOOL bResult = CPropertySheet::OnInitDialog();
	m_bModeless = TRUE;

	return bResult;
}

This will do the trick, fooling CPropertySheet Class into thinking it deals with modeless type. 
The HELP button will be shown only if you handle help commands in your project. For example: ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp), and all the rest.

Ts is only example, I did not deal with View and Document classes.
