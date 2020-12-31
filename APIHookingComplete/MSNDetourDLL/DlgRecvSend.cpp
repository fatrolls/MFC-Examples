#include "DlgRecvSend.h"

vector<string>emailList;
vector<SOCKET>sessionList;
vector<const char*>chatID;
HWND g_hDlg;
extern int (WINAPI *psend)(SOCKET socket, const char* buffer, int length, int flags);

BOOL CALLBACK DlgProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uiMsg)
	{
	case WM_INITDIALOG:
		::g_hDlg = hDlg;
		SetDlgItemText(hDlg, IDC_CHAT, "Chat message to send goes here");
		SendDlgItemMessage(hDlg, IDC_CHAT, EM_LIMITTEXT, 1600, 0);
		break;
	case WM_QUIT:
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		case IDOK:
			{
				int index = SendDlgItemMessage(hDlg, IDC_CBUSERS, CB_GETCURSEL, 0, 0);
				int textLength = SendDlgItemMessage(hDlg, IDC_CHAT, WM_GETTEXTLENGTH, 0, 0);
				if(textLength == 0)
					break;
				char* emailSelected = new char[128];
				char* packet = new char[textLength+1];
				GetDlgItemText(hDlg, IDC_CHAT, packet, textLength+1);
				SendDlgItemMessage(hDlg, IDC_CBUSERS, CB_GETLBTEXT, index, (LPARAM)emailSelected);
				SOCKET sessionToSendTo = GetSessionFromEmail(emailSelected);
				BuildPacket(sessionToSendTo, packet);
				delete [] emailSelected;
				delete [] packet;
			}
			break;	
		}
		break;
	default: break;
	}
return FALSE;
}

void ParseAndStoreEmail(SOCKET session, const char* buffer)
{
	string email;
	int i = 4; //4 to skip "MSG " part
	while(buffer[i] != ' ')
	{
		email += buffer[i];
		i++;
	}
	if(SearchForDuplicates(session, email.c_str()) != -1)
	{
		emailList.push_back(email);
		sessionList.push_back(session);
		SendDlgItemMessage(::g_hDlg, IDC_CBUSERS, CB_ADDSTRING, NULL,
			(LPARAM)email.c_str());
		SendDlgItemMessage(::g_hDlg, IDC_CBUSERS, CB_SETCURSEL, emailList.size()-1, 0);
	}
}

int SearchForDuplicates(SOCKET session, string email)
{
	for(unsigned int i = 0; i < emailList.size(); i++)
	{
		if(email.compare(emailList[i]) == 0)
		{
			if(session != sessionList[i])
			{
				sessionList[i] = session;
				return -1;
			}
		return -1;
		}
	}
	return 0;
}

string GetEmailFromSession(SOCKET session)
{
	for(unsigned int i = 0; i < sessionList.size(); i++)
	{
		if(session == sessionList[i])
			return emailList[i].c_str();
	}
	return "";
}

SOCKET GetSessionFromEmail(string email)
{
	for(unsigned int i = 0; i < emailList.size(); i++)
	{
		if(email.compare(emailList[i]) == 0)
			return sessionList[i];
	}
	return NULL;
}

void BuildPacket(SOCKET session, const char* message)
{
	char packetSize[8];
	ZeroMemory(packetSize, 8);
	string packetHeader = "MSG 10 N ";
	string packetSettings = "MIME-Version: 1.0\r\nContent-Type: text/plain; charset=UTF-8\r\n";
	packetSettings += "X-MMS-IM-Format: FN=MS%20Shell%20Dlg; EF=; CO=0; CS=0; PF=0\r\n\r\n";
	string packetMessage = message;
	int sizeOfPacket = packetSettings.length() + packetMessage.length();
	_itoa_s(sizeOfPacket, packetSize, 8, 10);
	packetHeader += packetSize;
	packetHeader += "\r\n";
	string fullPacket = packetHeader;
			fullPacket += packetSettings;
			fullPacket += packetMessage;
	psend(session, fullPacket.c_str(), fullPacket.length(), 0);
}