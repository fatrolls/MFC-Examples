


#ifndef _SYSTRAY_ICON_H_
#define _SYSTRAY_ICON_H_

class SystrayIcon : public CObject
{
private:

	HICON*			m_phIcon;
	NOTIFYICONDATA	m_NotifyIcon;
	
public:

	SystrayIcon( CWnd* pWnd, UINT unCallbackMsg,
				 LPCTSTR szTip, HICON* pIconList );
	
	virtual ~SystrayIcon();

    void SetState( HICON hIcon );
	void SetState( int id  = 0, char* cpToolTip = "" );    
};

#endif // _SYSTRAY_ICON_H_
