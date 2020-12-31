
In the past time, if you want to copy/move string from one edit control
to another edit control or copy/move string from one edit window of 
foreign application to a edit control, only you can do is copy, cut, 
and paste via clipboard. For such a inconvenience, I implemented a 
CDragEdit control which is based on the standard CEdit control so that 
you can override the existent application's edit control as a drag-drop 
enabled control very easily. Besides that the CDragEdit's drag-drop 
capability is implemented via OLE's UDT (Uniform Data Transfer) so you 
can use its drag-drop to share data with most applications. e.g. 
Visual C++, WordPad, Word, ...,etc.

If you have any question about the CDragEdit, don't hesitate to e-mail to
me.

ysl@springsoft.com.tw
Sam Lu

* Class hierarchy of CDragEdit

CObject
|
+-CCmdTarget
  |
  +-CWnd
    |
    +-CEdit
      |
	  +-CDragEdit


* How to use the CDragEdit ?

. To use a drag edit control in an existing dialog box of your application.

In your dialog definition file, you need to include the "CDragEdit.h" first,
and then declare CDragEdit member variable corresponding to each edit 
control that you want it become a drag-drop enabled control.
After you have declared the CDragEdit variables, you have to use 
DDX_Control() to subclass the standard edit control as a CDragEdit
control in DoDataExchange() and call CDragEdit::Init(), in 
OnInitialDialog(), to initiate the CDragEdit and enable its drag-drop 
capability.

. To use a drag edit control in toolbar.

Calling CDragEdit::Create() to create a drag edit control and then
call CDragEdit::Init() to initiate this edit control and enable
its drag-drop capability.

For example, you want to use two drag edit controls in the CTestDragEDitDlg.
You need to add some codes in your xxxDlg.h and xxxDlg.cpp as below:
//////////////////////
//TestDragEditDlg.h
//////////////////////
#include "CDragEdit.h" //include it in your xxxDlg.h

class CTestDragEditDlg : public CDialog
{
...
// Dialog Data
	//{{AFX_DATA(CTestDragEditDlg)
	enum { IDD = IDD_DRAGEDIT };
	CDragEdit	m_edit2; //declare a CDragEdit variable 
	CDragEdit	m_edit1; //for each edit control
	//}}AFX_DATA
...
}

//////////////////////
//TestDragEditDlg.cpp
//////////////////////
void CTestDragEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDragEditDlg)
	DDX_Control(pDX, IDC_EDIT2, m_edit2); //subclass the standard edit
	DDX_Control(pDX, IDC_EDIT1, m_edit1); //control as a CDragEdit
	//}}AFX_DATA_MAP
}
BOOL CTestDragEditDlg::OnInitDialog() 
{
...
    //You need to initiate CDragEdit first 
	m_edit1.Init();
    m_edit2.Init();
...
}

* How the CDragEdit works ?

As I mentioned, the drag-drop of CDragEdit is implemented via OLE
drag-and-drop. So, I implemented a CDEDropTarget, which is based on
COleDropTarget, and a CDEDataSource, which is based on COleDataSource.
The CDEDropTaregt serves the CDragEdit as a data comsumer and the
CCDEDataSource serves the CDragEdit as a data producer.
Drag-drop data transfers usually begin when the user press the left
button of mouse. So, in CDragEdit, simply handle the WM_LBUTTONDOWN
messagem, coping selected string into a CDEDataSource object using 
CacheGlobalData(), and call CDEDataSource::DoDragDrop() to tranfer 
string to a drop target.
In CDragEdit::Init(), I register this window as a drop target by 
calling CDEDropTarget::Register(). Once a CDragEdit is registered 
with OLE to be a drop target, it becomes eligible to receive 
OnDropEnter(), OnDropOver(), OnDropLeave(), and OnDrop() notifications 
from OLE. In OnDrop(), the CDragEdit will retrieve data with CF_TEXT 
format from COleDataObject and place at the dropped point.

For more information, please refer to the comment of source code.
