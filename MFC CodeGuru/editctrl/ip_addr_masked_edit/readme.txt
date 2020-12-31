IPTest.exe demonstrates an MFC-based custom control which is very
similar to the one used in the Windows NT 4.0 "Network" applet in
Control Panel.  The custom control can be used in a dialog or a
property page; I haven't tried it in a form.

The control is provided free of charge with the caveat that no
warranty is expressed or implied.  Feel free to email me if you
discover any nasty bugs.  Comments and suggestions are welcome, too!

Joseph A. Dziedzic
dziedzic@ma.ultranet.com


Changes from the original (September 1997) version:

1) The control now validates fields as data is entered for values
   greater than 255.  If you want to defer validation until
   DDX time (the old mode of operation), specify the style bit
   IPAS_NOVALIDATE (defined in IPAddr.h) when creating the control.

2) The DDX_IPAddr routine has been moved into IPAddr.cpp.  You can
   use this default implementation, or write your own.  There is a
   version that works with an array of bytes as well as a string of
   "."-separated fields.

3) A few tweaks were made so the control matches the one used in
   Windows 95/NT's Network Control Panel applet.  Specifically,
   space is now accepted as an indication to move to the next
   address field; focus is advanced to the next address field as
   soon as three numeric characters have been entered in a field.

4) The control now has a Create method to allow dynamic creation.

5) A number of bugs were fixed including: handling of the Delete key
   and use of the control on a property page.

6) The structure named IPADDR (used to pass IP addresses in Windows
   messages) was renamed to avoid a conflict with a typedef in the
   include file ras.h; the structure is now called IPA_ADDR.  (Most
   users of the control won't notice this change.)

7) The messages to and from the control were renamed from IPMxxx
   to IPAMxxx to avoid conflicts with the IE 4 common controls DLL.


How to Use the IP Address Custom Control

(See IPTestDlg.h and IPTestDlg.cpp for the code outlined below)

Add a custom control to a dialog resource; size the control to
90 x 13 Dialog Units.  Set the Class to "IPAddr" and the style
to 0x50810000 (WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP).
Include the low-order bit to disable immediate field validation.

Edit the dialog class definition (.h) file as follows:

  Add a member variable after the closing }}AFX_DATA line:

	unsigned char m_nAddr[4];

  Add the following lines after the DECLARE_MESSAGE_MAP macro:

	private:
		CIPAddrCtl* m_pIPAddrCtl;

Edit the dialog class implementation (.cpp) file as follows:

  Add the following lines after the closing }}AFX_DATA_INIT line:
	m_pIPAddrCtl = NULL;
	memset(m_nAddr, 0, 4);

  Add the following lines after the call to CDialog::DoDataExchange in the
  dialog class implementation of ::DoDataExchange:

	// Can't hack DDX_Control'ing the IP Address control since the control code subclasses the control behind our back
	// Fortunately, that means we can do *one* GetDlgItem call and salt away the returned CWnd-derived
	// object pointer for use during the entire dialog
	if (NULL == m_pIPAddrCtl)
		m_pIPAddrCtl = (CIPAddrCtl*) GetDlgItem(IDC_IPADDR);
	ASSERT(NULL != m_pIPAddrCtl);

  Add the following line after the closing }}AFX_DATA_MAP line:

	DDX_IPAddr(pDX, IDC_IPADDR, m_nAddr);

Note:  Default implementations of DDX_IPAddr are supplied in ipaddr.cpp.  You can
write your own if the default ones are not adequate for your needs.  There are two
DDX routines, one which accepts an array of bytes, and another which accepts a
reference to a CString.
