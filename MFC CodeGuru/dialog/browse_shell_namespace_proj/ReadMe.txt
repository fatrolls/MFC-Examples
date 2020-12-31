CShellTree Version 1.02 (any previous unversioned copies are older/inferior)

Selom Ofori (SubRosa) Please see http://chat.carleton.ca/~sofori for updates and 
method descriptions. Thanks to everybody who reported/fixed some of the
bugs and to those who requested features. Created with MSVC 5, tested under win95 OSR2
and WINNT 4


Anybody who is interested in having a ShellFolder tree directly in his
dialog box has probably tried to come to grips with MFCENUM. MFCENUM is pretty
easy to understand, but only if you go through the pain of trying to modify the code 
to work with yours. CShellTree contains the important parts of MFCENUM that deals with
browsing the shell namespace.

CShellTree inherits CTreeCtrl. After you initialize the tree with the Shell Folders
the only other interaction the Shell 'engine' has with the tree control is through 
TVN_ITEMEXPANDING (when the user clicks on the plus sign or double clicks on the folder).

Operations:

	//Initializes the treeview with "mycomputer" etc
	void	PopulateTree();							

	//Initializes the treeview starting with a special folder as root
	//See the SHGetSpecialFolderLocation() for constants and descriptions
	void	PopulateTree(int SpecialFolderID);							

	//Must be called from OnItemExpanding(), message TVN_ITEMEXPANDING
	void	OnFolderExpanding(NMHDR* pNMHDR, LRESULT* pResult);		

	//Frees memory allocated for the shell object. message TVN_DELETEITEM
	void	OnDeleteShellItem(NMHDR* pNMHDR, LRESULT* pResult);		

	//Must be called from OnRclick(). message NM_RCLICK
	void	GetContextMenu(NMHDR* pNMHDR, LRESULT* pResult);			

	//Must be called from OnSelChanged(), message TVN_SELCHANGED
	BOOL	OnFolderSelected(NMHDR* pNMHDR, LRESULT* pResult, CString &szFolderPath);	

	//Enables Folder Images in the tree control.
	void	EnableImages();							

	//Retrieves the path of the Selected Folder.
	BOOL	GetSelectedFolderPath(CString &szFolderPath);			
	
	//Opens the folder of the specified path. Does it's own error checking
	void	TunnelTree(CString szFindPath)

The General Steps are:

1. Include 'shelltree.cpp' and 'shelltree.h' into your project
   Include 'shellpidl.cpp' and 'shellpidl.h' into your project
   Include 'filename.cpp' and 'filename.h' into your project
2. Create a dialog or use an existing dialog ( after you are familar with CShellTree)
3. Add a treecontrol to your dialog.
4. Do not create member variables of the treecontrol using classwizard. Instead open the header
   file of the dialog class and

	#include "Shelltree.h"

then add 

      CShellTree* m_TreeCtl;

to the dialog class.

4b. You can make CShellTree show up in class wizard but it requires deleting your .clw file
    and having classwizard rebuild the class information. Better backup your .clw file before
    you decide to do this.

=============
5. In your OnInitDialog(), a callback to the WM_INITDIALOG message, initialize your treecontrol 

BOOL CTreeExampleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_TreeCtl = (CShellTree*) GetDlgItem(IDC_SHELLTREE); //replace IDC_SHELLTREE with your control's ID
	ASSERT(m_TreeCtl);

	m_TreeCtl->EnableImages();	//enable images
	m_TreeCtl->PopulateTree();	//populate for the with Shell Folders for the first time

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

NOTE: REQUIRED. CShellTree handles the images for you. DO NOT attach an ImageList to CSHellTree. This internal imagelist
      is a handle to the system image list and uses it directly. Using CImageList will result in the 
      system imagelist being destroyed after your application exits.

      the call

		m_TreeCtl->EnableImages(); 

      creates and attaches an image list to the Tree Control

To initialize the ShellFolders you call 

	m_TreeCtl->PopulateTree();

This fills it with the starting folders like "mycomputer","network neighbourhood etc"


============
6. It is very important that you create OnItemExpanding(), a callback to TVN_ITEMEXPANDING.
   Otherwise your tree would be pretty much dead.

void CTreeExampleDlg::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_TreeCtl->OnFolderExpanding(pNMHDR,pResult);
	*pResult = 0;
}

Comments: REQUIRED. The OnFolderExpanding() method of CShellTree does the dirty work of 
          adding folder nodes to the tree control. It takes the same paramters as your 
          OnItemExpanding, so all you have to do is pass the paramters along.


==============
7. If you want a popup menu to be active, create a OnRclick(), a callback to NM_RCLICK. This
   popup is the same as the one in windows explorer. 

void CTreeExampleDlg::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_TreeCtl->GetContextMenu(pNMHDR,pResult);
	*pResult = 0;
}

Comments: Takes the same paramters as OnRclick. All you do is pass on the parameters to
          the GetContextMenu() method of CShellTree. The popup is handled by the system.

==========
8. CShellTree expects you to keep track of the filepath in your OnSelChanged(), a callback to
   TVN_SELCHANGED. CShellTree provides a method 

	OnFolderSelected(NMHDR* pNMHDR, LRESULT* pResult, CString &szFolderPath)

   intended to by called from your OnSelChanged() callback function. The CString object will contain
   the path of that folder selected if FolderSelected() returns TRUE. If it returns FALSE, the
   node selected isn't part of the filesystem and has no path.

   PS: Use this function if you need to set the path in a corresponding combobox or editwindow.

void CTreeExampleDlg::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString SelPath;
	if(m_TreeCtl->OnFolderSelected(pNMHDR,pResult,SelPath))
		MessageBox(SelPath);
	*pResult = 0;
}

comments: The above code displays the path of the Folder selected if it's in the filesystem.

9. You must allow CShellTree to release the memory allocated for the Shellobjects. in your
   OnDeleteItem(), a callback to TVN_DELETEITEM, CShellTree provides a method

	void	OnDeleteShellItem(NMHDR* pNMHDR, LRESULT* pResult);

   You must absolutely call this method or your project will leak memory

void CTreeExampleDlg::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_TreeCtl->OnDeleteShellItem(pNMHDR,pResult);
	*pResult = 0;
}

MISC NOTES:
===========
1. void	CShellTree::TunnelTree(CString szFindPath) requires that you
   implement the TVN_SELCHANGED message handler. TunnelTree will just
   just not work if you do NOT implement it. Works only on folders under "MY COMPUTER"
   This means local drives and mapped network drives. No network neighbourhood or whatever

2. void CShellTree::PopulateTree(int nSpecialFolder) will start the tree at
   a special folder location. See ::ShBrowseForFolder() and ::ShGetSpecialFolderLocation().
   CShellTree::TunnelTree() will not work if you use this method to initialize the tree.

HISTORY:
========
v1.02
- Fixed a skipped initialization of a variable that caused TunnelTree() to crash on WinNT
  if the folder didn't have any subfolders
- Added TunnelTree(CString szFindPath) and PopulateTree(int SpecialFolder) methods
- Implemented a required call to OnDeleteShellItem(); TVN_DELETEITEM, that released the memory
  allocated by that shell folder

========
BONUS: You can get the path of the Selected Node by calling GetSelectedFolderPath(). It will
       return TRUE if the selected Folder is part of the filesystem. Returns false if an item
       hasn't been selected or the Folder is not part of the filesystem. eg. "My Computer"


An Example project called shelltree102.zip is included.
see http://chat.carleton.ca/~sofori for updates and method descriptions