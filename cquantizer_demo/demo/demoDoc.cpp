// demoDoc.cpp : implementation of the CDemoDoc class
//

#include "stdafx.h"
#include "demo.h"

#include "MainFrm.h"
#include "demoDoc.h"
#include "DlgRotate.h"
#include "DlgResample.h"
#include "DlgDecBpp.h"
#include "DlgIncBpp.h"
#include "Quantize.h"

#include "ximage.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**************************************/
// CDemoDoc

IMPLEMENT_DYNCREATE(CDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_STRETCH_MODE, OnStretchMode)
	ON_UPDATE_COMMAND_UI(ID_STRETCH_MODE, OnUpdateStretchMode)
	ON_COMMAND(ID_TRANSFORM_ELLIPSE, OnTransformEllipse)
	ON_COMMAND(ID_WINDOW_DUPLICATE, OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_CXIMAGE_FLIP, OnCximageFlip)
	ON_COMMAND(ID_CXIMAGE_MIRROR, OnCximageMirror)
	ON_COMMAND(ID_CXIMAGE_NEGATIVE, OnCximageNegative)
	ON_COMMAND(ID_CXIMAGE_GRAYSCALE, OnCximageGrayscale)
	ON_COMMAND(ID_CXIMAGE_ROTATE, OnCximageRotate)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMIN, OnUpdateViewZoomin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMOUT, OnUpdateViewZoomout)
	ON_COMMAND(ID_VIEW_NORMALVIEWING11, OnViewNormalviewing11)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NORMALVIEWING11, OnUpdateViewNormalviewing11)
	ON_COMMAND(ID_CXIMAGE_SETTRANSPARENCY, OnCximageSettransparency)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_SETTRANSPARENCY, OnUpdateCximageSettransparency)
	ON_COMMAND(ID_CXIMAGE_REMOVETRANSPARENCY, OnCximageRemovetransparency)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_REMOVETRANSPARENCY, OnUpdateCximageRemovetransparency)
	ON_COMMAND(ID_CXIMAGE_RESAMPLE, OnCximageResample)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_FLIP, OnUpdateCximageFlip)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_GRAYSCALE, OnUpdateCximageGrayscale)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_MIRROR, OnUpdateCximageMirror)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_NEGATIVE, OnUpdateCximageNegative)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_RESAMPLE, OnUpdateCximageResample)
	ON_UPDATE_COMMAND_UI(ID_CXIMAGE_ROTATE, OnUpdateCximageRotate)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORM_ELLIPSE, OnUpdateTransformEllipse)
	ON_COMMAND(ID_CXIMAGE_DECREASEBPP, OnCximageDecreasebpp)
	ON_COMMAND(ID_CXIMAGE_INCREASEBPP, OnCximageIncreasebpp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**************************************/
// CDemoDoc construction/destruction
CDemoDoc::CDemoDoc()
{
	image = NULL;
	m_WaitingClick = stretchMode = FALSE;
	for (int i=0;i<MAX_UNDO_LEVELS;i++) imageUndo[i]=NULL;
	m_UndoLevel=0;
	m_ZoomFactor=1;
	QueryPerformanceFrequency(&m_swFreq);
	m_etime = 0.0;
	hThread=hProgress=0;
}
/**************************************/
CDemoDoc::~CDemoDoc()
{
	// stop the elaborations
	if (image) image->SetEscape(1);
	// stop the progress bar
	if (hProgress){
		ResumeThread(hProgress); //wake up!
		WaitForSingleObject(hProgress,500);
		CloseHandle(hProgress);
	}
	if (hThread){
		WaitForSingleObject(hThread,500);
		CloseHandle(hThread);
	}
	// free objects
	delete image;
	for (int i=0;i<MAX_UNDO_LEVELS;i++) delete imageUndo[i];

}
/**************************************/
BOOL CDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	image = NULL;

	return TRUE;
}
/**************************************/
// CDemoDoc serialization
void CDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())	{ } 
	else { }
}
/**************************************/
// CDemoDoc diagnostics
#ifdef _DEBUG
void CDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}
/**************************************/
void CDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
/**************************************/
// CDemoDoc commands
static CString FindExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(i+1);
		}
	}
	return CString("");
}
/**************************************/
BOOL CDemoDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CString filename(lpszPathName);
	CString ext(FindExtension(filename));
	ext.MakeLower();
	if (ext == "") return FALSE;

	int type = 0;
	if (ext == "bmp")					type = CXIMAGE_FORMAT_BMP;
#if CXIMAGE_SUPPORT_JPG
	else if (ext=="jpg"||ext=="jpeg")	type = CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_GIF
	else if (ext == "gif")				type = CXIMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_PNG
	else if (ext == "png")				type = CXIMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
	else if (ext=="mng"||ext=="jng")	type = CXIMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
	else if (ext == "ico")				type = CXIMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
	else if (ext=="tiff"||ext=="tif")	type = CXIMAGE_FORMAT_TIF;
#endif
	else return FALSE;

	Stopwatch(0);
	image = new CxImage(filename, type);
	Stopwatch(1);

	if (!image->IsValid()){
		AfxMessageBox(image->GetLastError());
		delete image;
		image = NULL;
		return FALSE;
	}

	UpdateAllViews(NULL,WM_USER_NEWIMAGE);

	//multiple images (TIFF/ICO)
	if (image->GetNumFrames()>1){
		CString s;
		s.Format("File with %d images. Read all?",image->GetNumFrames());
		if (AfxMessageBox(s,MB_OKCANCEL)==IDOK){
			
			int j; // points to the document name
			for(j=strlen(filename)-1;j>=0;j--){
				if (filename[j]=='\\'){	j++; break;	}
			}
			// create the documents for the other images
			for(int i=1;i<image->GetNumFrames();i++){
				CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL);
				if (NewDoc)	{
					CxImage *newImage = new CxImage();
					newImage->SetFrame(i);
					newImage->ReadFile(filename,type);
					NewDoc->image = newImage;
					CString s;
					s.Format("%s (%d)",filename.Mid(j),i+1);
					NewDoc->SetTitle(s);
					NewDoc->UpdateAllViews(NULL,WM_USER_NEWIMAGE);
				}
			}
		}
	}

	return TRUE;
}
/**************************************/
BOOL CDemoDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	CString filename(lpszPathName);
	CString ext(FindExtension(filename));
	ext.MakeLower();
	if (ext == "") return FALSE;

	int type = 0;
	if (ext == "bmp")					type = CXIMAGE_FORMAT_BMP;
#if CXIMAGE_SUPPORT_JPG
	else if (ext=="jpg"||ext=="jpeg")	type = CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_GIF
	else if (ext == "gif")				type = CXIMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_PNG
	else if (ext == "png")				type = CXIMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
	else if (ext == "mng")				type = CXIMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
	else if (ext == "ico")				type = CXIMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
	else if (ext=="tiff"||ext=="tif")	type = CXIMAGE_FORMAT_TIF;
#endif
	else return FALSE;

	bool retval;
	Stopwatch(0);
	retval = image->SaveFile(filename, type);
	Stopwatch(1);
	UpdateStatusBar();
	if (retval) return TRUE;
	AfxMessageBox(image->GetLastError());

	return FALSE;
}
/**************************************/
BOOL CDemoDoc::DoSave(LPCTSTR pszPathName, BOOL bReplace /*=TRUE*/)
{
	if (!image)	return FALSE;

	CString newName = pszPathName;
	BOOL bModified = IsModified();

	BOOL bSaveAs = FALSE;
	if (newName.IsEmpty()) bSaveAs = TRUE;
	else if (!theApp.GetWritableType(image->GetType()))	bSaveAs = TRUE;

	if (bSaveAs){
		newName = m_strPathName;
		if (bReplace && newName.IsEmpty()){
			newName = m_strTitle;
			int iBad = newName.FindOneOf(_T(" #%;/\\"));    // dubious filename
			if (iBad != -1)	newName.ReleaseBuffer(iBad);

			// append the default suffix if there is one
			newName += theApp.GetExtFromType(image->GetType()).Mid(1,4);
		}

		int nDocType = image->GetType();
		if (!theApp.PromptForFileName(newName, 
			bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, &nDocType))
		{
			return FALSE;       // don't even try to save
		}
	}

	BeginWaitCursor();
	if (!OnSaveDocument(newName)){
		if (pszPathName == NULL){
			// be sure to delete the file
			TRY 
			{
				CFile::Remove(newName);
			}
			CATCH_ALL(e)
			{
				TRACE0("Warning: failed to delete file after failed SaveAs\n");
			}
			END_CATCH_ALL
		}
		EndWaitCursor();
		return FALSE;
	}

	EndWaitCursor();
	if (bReplace) {
		// Reset the title and change the document name
		SetPathName(newName, TRUE);
		ASSERT(m_strPathName == newName); // must be set
	}
	else // SaveCopyAs
	{
		SetModifiedFlag(bModified);
	}
	return TRUE;        // success
}
/**************************************/
#define EPSILON (0.0000001)

int CDemoDoc::ComputePixel(float x, float y, float &x1, float &y1)
{
  double r, nn;

  if (x==0 && y==0) {
	 x1 = x;
	 y1 = y;
	 return 1;
  }

  nn = sqrt(x*x + y*y);
  r =  (fabs(x) > fabs(y)) ? fabs(nn/x): fabs(nn/y);

  x1 = (float)(r*x);
  y1 = (float)(r*y);

  return 1;
}
/**************************************/
void CDemoDoc::ComputeNewImage(void)
{
  CWaitCursor wait;
  DWORD x, y, x1, y1;
  float fx, fy, xmid, ymid, ar;
  CxImage *image2 = new CxImage(image);

  xmid = (float) (image->GetWidth()/2.0);
  ymid = (float) (image->GetHeight()/2.0);
  ar = (float)(image->GetHeight())/(float)(image->GetWidth());
  for (y=0; y<image->GetHeight(); y++) {
	 for (x=0; x<image->GetWidth(); x++) {
		ComputePixel(ar*(x-xmid), y-ymid, fx, fy);
		x1 = (int)(xmid+fx/ar);
		y1 = (int)(ymid+fy);
		if (image->IsInside(x1, y1))
		  image2->SetPixelColor(x, y, image->GetPixelColor(x1, y1));
		else {
			if (image2->GetNumColors()==0){
				image2->SetPixelColor(x, y,RGB(255,255,255));
			} else {
				image2->SetPixelIndex(x, y,(BYTE)image2->GetTransIndex());
			}
		}
	 }
  }
  delete image;
  image = image2;
  UpdateAllViews(NULL);
}
/**************************************/
void CDemoDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(image==0 || hThread));
}
/**************************************/
void CDemoDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(0);
//	pCmdUI->Enable((image != NULL)); //&& theApp.GetWritableType(image->GetType()));
}
/**************************************/
void CDemoDoc::OnStretchMode() 
{
	stretchMode = !stretchMode;
	UpdateAllViews(NULL);
}
/**************************************/
void CDemoDoc::OnUpdateStretchMode(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(stretchMode);
}
/**************************************/
void CDemoDoc::OnUpdateCximageFlip(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageGrayscale(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageMirror(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageNegative(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageResample(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
void CDemoDoc::OnUpdateCximageRotate(CCmdUI* pCmdUI) 
{	if(image==0 || hThread) pCmdUI->Enable(0);}
/**************************************/
void CDemoDoc::OnUpdateTransformEllipse(CCmdUI* pCmdUI) 
{
	if (image==NULL) pCmdUI->Enable(0);
}
/**************************************/
void CDemoDoc::OnTransformEllipse() 
{
	SubmitUndo();
	ComputeNewImage();
	UpdateAllViews(NULL);
}
/**************************************/
void CDemoDoc::OnWindowDuplicate() 
{
	CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 

	if (NewDoc)	{
		CxImage *newImage = new CxImage(image);
		newImage->Copy(image);

		NewDoc->image = newImage;

		CString s;
		s.Format("Copy %d of %s",((CDemoApp*)AfxGetApp())->m_nDocCount++,GetTitle());
		NewDoc->SetTitle(s);
		NewDoc->UpdateAllViews(0,WM_USER_NEWIMAGE);
	}
}
/**************************************/
void CDemoDoc::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	if (image==NULL) pCmdUI->Enable(0);
}
/**************************************/
void CDemoDoc::OnEditCopy() 
{
	HANDLE hDIB=image->CopyToHandle();

	if (::OpenClipboard(AfxGetApp()->m_pMainWnd->GetSafeHwnd())) {
		if(::EmptyClipboard()) {
			if (::SetClipboardData(CF_DIB,hDIB) == NULL ) {
				AfxMessageBox( "Unable to set Clipboard data" );
			}
		}
	}
	CloseClipboard();
}
/**************************************/
void CDemoDoc::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	if(image==0 || hThread) pCmdUI->Enable(0);
	else pCmdUI->Enable(m_UndoLevel>0);

	CString s;
	s.Format("Undo (%d)\tCtrl+Z",m_UndoLevel);
	pCmdUI->SetText(s);
}
/**************************************/
void CDemoDoc::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	if(image==0 || hThread) pCmdUI->Enable(0);
	else pCmdUI->Enable((m_UndoLevel<(MAX_UNDO_LEVELS))&&
				   (imageUndo[m_UndoLevel]!=0));
}
/**************************************/
void CDemoDoc::OnEditUndo() 
{
	m_UndoLevel--;
	CxImage* tmp = image;
	image=imageUndo[m_UndoLevel];
	imageUndo[m_UndoLevel]=tmp;

	UpdateAllViews(0,WM_USER_NEWIMAGE);
	UpdateStatusBar();
}
/**************************************/
void CDemoDoc::OnEditRedo() 
{
	CxImage* tmp = image;
	image=imageUndo[m_UndoLevel];
	imageUndo[m_UndoLevel]=tmp;
	m_UndoLevel++;

	UpdateAllViews(0,WM_USER_NEWIMAGE);
	UpdateStatusBar();
}
/**************************************/
void CDemoDoc::SubmitUndo()
{
	if (m_UndoLevel>=MAX_UNDO_LEVELS){	// Max Undo reached
		delete imageUndo[0];			// discard the early undo
		for(int i=1;i<MAX_UNDO_LEVELS;i++){
			imageUndo[i-1]=imageUndo[i]; //shift the history
		}
		imageUndo[MAX_UNDO_LEVELS-1]=0;	// clear the undo slot
		m_UndoLevel=MAX_UNDO_LEVELS-1;  // reposition at last level
	}
	// we must clear the "redo" history when a new action is performed
	for (int i=m_UndoLevel;i<MAX_UNDO_LEVELS;i++){
		if (imageUndo[i]){
			delete imageUndo[i];
			imageUndo[i]=0;
		}
	}
	// save the actual image in the undo history
	if (image->IsValid()){
		imageUndo[m_UndoLevel] = new CxImage(image);
		imageUndo[m_UndoLevel]->Copy(image);
		m_UndoLevel++;
	}
}
/**************************************/
unsigned long _stdcall RunProgressThread(void *lpParam)
{
	CDemoDoc *pDoc = (CDemoDoc *)lpParam;
	long n;
	POSITION pos;
	CView *pView;
	while((n=pDoc->image->GetProgress())<100){
		Sleep(333);
		if(pDoc->image->GetEscape()) break;
		pos = pDoc->GetFirstViewPosition();
		pView = pDoc->GetNextView(pos);
		if (pView) SendMessage(pView->m_hWnd, WM_USER_PROGRESS,n,0);
	}
	pos = pDoc->GetFirstViewPosition();
	pView = pDoc->GetNextView(pos);
	if (pView) SendMessage(pView->m_hWnd, WM_USER_PROGRESS,100,0);
	Sleep(111);
	pos = pDoc->GetFirstViewPosition();
	pView = pDoc->GetNextView(pos);
	if (pView) SendMessage(pView->m_hWnd, WM_USER_NEWIMAGE,0,0);
	pDoc->hProgress = 0;
	return 0;
}
/**************************************/
unsigned long _stdcall RunCxImageThread(void *lpParam)
{
	CDemoDoc *pDoc = (CDemoDoc *)lpParam;
	if (pDoc==NULL) return 0;
	if (pDoc->image==NULL) return 0;

	 //prepare for elaboration
	pDoc->image->SetProgress(0);
	pDoc->image->SetEscape(0);

	pDoc->SubmitUndo();
	
	DWORD dwID; // auxilary thread for progress bar
	pDoc->hProgress = CreateThread(NULL,0,RunProgressThread,pDoc,0,&dwID);

	pDoc->Stopwatch(0);

	switch (pDoc->m_MenuCommand)
	{
//	case ID_FILE_OPEN:
//		pDoc->image->ReadFile(*(CString*)pDoc->m_fp[0],(int)pDoc->m_fp[1]);
//		break;
	case ID_CXIMAGE_FLIP:
		pDoc->image->Flip();
		break;
	case ID_CXIMAGE_MIRROR:
		pDoc->image->Mirror();
		break;
	case ID_CXIMAGE_NEGATIVE:
		pDoc->image->Negative();
		break;
	case ID_CXIMAGE_GRAYSCALE:
		pDoc->image->GrayScale();
		break;
	case ID_CXIMAGE_ROTATE:
		pDoc->image->Rotate((float)(long)pDoc->m_fp[0]/1000);
		break;
	case ID_CXIMAGE_RESAMPLE:
		pDoc->image->Resample((long)pDoc->m_fp[0],(long)pDoc->m_fp[1],(int)pDoc->m_fp[2]);
		break;
	case ID_CXIMAGE_INCREASEBPP:
		pDoc->image->IncreaseBpp((long)pDoc->m_fp[0]);
		break;
	case ID_CXIMAGE_DECREASEBPP:
		{
			long bit=(long)pDoc->m_fp[0];
			long method=(long)pDoc->m_fp[1];
			bool errordiffusion=((long)pDoc->m_fp[2])!=0;
			long colors=(long)pDoc->m_fp[3];
			RGBQUAD* ppal = NULL;
			if (method==1){
				switch (bit){
				/*case 1:
					{
						CQuantizer q(2,8);
						q.ProcessImage(pDoc->image->GetDIB());
						ppal=(RGBQUAD*)calloc(2*sizeof(RGBQUAD),1);
						q.SetColorTable(ppal);
						break;
					}*/
				case 4:
					{
						CQuantizer q(colors,8);
						q.ProcessImage(pDoc->image->GetDIB());
						ppal=(RGBQUAD*)calloc(16*sizeof(RGBQUAD),1);
						q.SetColorTable(ppal);
						break;
					}
				case 8:
					{
						CQuantizer q(colors,(colors>16?7:8));
						q.ProcessImage(pDoc->image->GetDIB());
						ppal=(RGBQUAD*)calloc(256*sizeof(RGBQUAD),1);
						q.SetColorTable(ppal);
					}
				}
				pDoc->image->DecreaseBpp(bit,errordiffusion,ppal,colors);
			} else pDoc->image->DecreaseBpp(bit,errordiffusion,0);

			if (ppal) free(ppal);
			break;
		}
	}

	pDoc->Stopwatch(1);

	pDoc->image->SetProgress(100);

	pDoc->hThread=0;
	return 0;
}
/**************************************/
void CDemoDoc::OnCximageFlip() 
{
	m_MenuCommand=ID_CXIMAGE_FLIP;
	hThread=CreateThread(NULL,0,RunCxImageThread,this,0,&dwThreadID);
}
/**************************************/
void CDemoDoc::OnCximageMirror() 
{
	m_MenuCommand=ID_CXIMAGE_MIRROR;
	hThread=CreateThread(NULL,0,RunCxImageThread,this,0,&dwThreadID);
}
/**************************************/
void CDemoDoc::OnCximageNegative() 
{
	m_MenuCommand=ID_CXIMAGE_NEGATIVE;
	hThread=CreateThread(NULL,0,RunCxImageThread,this,0,&dwThreadID);
}
/**************************************/
void CDemoDoc::OnCximageGrayscale() 
{
	m_MenuCommand=ID_CXIMAGE_GRAYSCALE;
	hThread=CreateThread(NULL,0,RunCxImageThread,this,0,&dwThreadID);
}
/**************************************/
void CDemoDoc::OnCximageDecreasebpp() 
{
	if (image==NULL) return;
	DlgDecBpp dlg;
	dlg.m_bit=4;
	dlg.m_maxcolors = 256;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_DECREASEBPP;
		m_fp[0]=(void *)dlg.m_bit;
		m_fp[1]=(void *)dlg.m_method;
		m_fp[2]=(void *)dlg.m_errordiffusion;
		m_fp[3]=(void *)dlg.m_maxcolors;
		hThread=CreateThread(NULL,0,RunCxImageThread,this,0,&dwThreadID);
	}
}
/**************************************/
void CDemoDoc::OnCximageIncreasebpp() 
{
	if (image==NULL) return;
	DlgIncBpp dlg;
	dlg.m_bit=24;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_INCREASEBPP;
		m_fp[0]=(void *)dlg.m_bit;
		hThread=CreateThread(NULL,0,RunCxImageThread,this,0,&dwThreadID);
	}
}
/**************************************/
void CDemoDoc::OnCximageRotate() 
{
	if (image==NULL) return;
	DlgRotate dlg;
	dlg.m_angle=(float)12.345;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_ROTATE;
		m_fp[0]=(void *)(long)(dlg.m_angle*1000);
		hThread=CreateThread(NULL,0,RunCxImageThread,this,0,&dwThreadID);
	}
}
/**************************************/
void CDemoDoc::OnCximageResample() 
{
	if (image==NULL) return;
	
	DlgResample dlg;
	dlg.m_factor=(float)2;
	dlg.m_fast = 1;
	if (dlg.DoModal()==IDOK){
		m_MenuCommand=ID_CXIMAGE_RESAMPLE;
		m_fp[0]=(void *)(long)(image->GetWidth() * dlg.m_factor);
		m_fp[1]=(void *)(long)(image->GetHeight() * dlg.m_factor);
		m_fp[2]=(void *)dlg.m_fast;
		hThread=CreateThread(NULL,0,RunCxImageThread,this,0,&dwThreadID);
	}
}
/**************************************/
void CDemoDoc::UpdateStatusBar()
{
	if (image){
		CStatusBar& statusBar = ((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetStatusBar();
		CString s;
		s.Format("(%dx%dx%d)",image->GetWidth(),image->GetHeight(),image->GetBpp());
		statusBar.SetPaneText(3, s);
		s.Format("Time (s): %.3f",m_etime);
		statusBar.SetPaneText(2, s);

		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->GetProgressBar().SetPos(0);
	}
}
/**************************************/
void CDemoDoc::OnViewZoomin() 
{
	if (m_ZoomFactor>=16) return;
	m_ZoomFactor*=2;
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}
/**************************************/
void CDemoDoc::OnViewZoomout() 
{
	if (m_ZoomFactor<=0.0625) return;
	m_ZoomFactor/=2;
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}
/**************************************/
void CDemoDoc::OnUpdateViewZoomin(CCmdUI* pCmdUI) 
{
	if (stretchMode) pCmdUI->Enable(0);
	if (m_ZoomFactor>=8) pCmdUI->Enable(0);
}
/**************************************/
void CDemoDoc::OnUpdateViewZoomout(CCmdUI* pCmdUI) 
{
	if (stretchMode) pCmdUI->Enable(0);
	if (m_ZoomFactor<=0.125) pCmdUI->Enable(0);
}
/**************************************/
void CDemoDoc::OnViewNormalviewing11() 
{
	m_ZoomFactor=1;
	UpdateAllViews(NULL,WM_USER_NEWIMAGE);
}
/**************************************/
void CDemoDoc::OnUpdateViewNormalviewing11(CCmdUI* pCmdUI) 
{
	if (stretchMode) pCmdUI->Enable(0);
	if (m_ZoomFactor==1) pCmdUI->Enable(0);
}
/**************************************/
void CDemoDoc::OnUpdateCximageSettransparency(CCmdUI* pCmdUI) 
{
	if (image && hThread==0) pCmdUI->Enable(image->GetNumColors());
	else pCmdUI->Enable(0);
}
/**************************************/
void CDemoDoc::OnUpdateCximageRemovetransparency(CCmdUI* pCmdUI) 
{
	if (image && hThread==0) pCmdUI->Enable(image->GetNumColors());
	else pCmdUI->Enable(0);
}
/**************************************/
void CDemoDoc::OnCximageRemovetransparency() 
{
	if (image) image->SetTransIndex(-1);
	UpdateAllViews(NULL);
}
/**************************************/
void CDemoDoc::OnCximageSettransparency() 
{
	m_WaitingClick=TRUE;
}
/**************************************/
void CDemoDoc::Stopwatch(int start0stop1)
{
	if (start0stop1==0)	QueryPerformanceCounter(&m_swStart);
	else {
		QueryPerformanceCounter(&m_swStop);
		if (m_swFreq.LowPart==0 && m_swFreq.HighPart==0) m_etime = -1;
		else {
			m_etime = (float)(m_swStop.LowPart - m_swStart.LowPart);
			if (m_etime < 0) m_etime += 2^32;
			m_etime /= (m_swFreq.LowPart+m_swFreq.HighPart * 2^32);
		}
	}
}
/**************************************/


