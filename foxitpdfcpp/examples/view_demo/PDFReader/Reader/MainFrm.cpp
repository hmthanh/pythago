
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "PDFReader/Source/Stdafx.h"

#include "PDFReader/Reader/PDFReader.h"
#include "PDFReader/Reader/MainFrm.h"
#include "PDFReader/Reader/SliderButton.h"
#include "PDFReader/Reader/PageGotoButton.h"
#include "PDFReaderDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
  ON_WM_CREATE()
  ON_WM_CLOSE()
  ON_WM_CTLCOLOR()
  ON_COMMAND(ID_FILE_CLOSE, &CMainFrame::OnFileClose)
  ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
  ON_COMMAND(ID_VIEW_OUTLINEVIEW, &CMainFrame::OnViewOutlineview)
  ON_UPDATE_COMMAND_UI(ID_VIEW_OUTLINEVIEW, &CMainFrame::OnUpdateViewOutlineview)
  ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnAppExit)
  ON_COMMAND(ID_VIEW_GOTOBAR, &CMainFrame::OnViewGotobar)
  ON_COMMAND(ID_VIEW_TOOLBAR, &CMainFrame::OnViewToolbar)
  ON_UPDATE_COMMAND_UI(ID_VIEW_GOTOBAR, &CMainFrame::OnUpdateViewGotobar)
  ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR, &CMainFrame::OnUpdateViewToolbar)
  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &CMainFrame::OnToolbarReset)
  ON_COMMAND(ID_VIEW_ZOOMBAR, &CMainFrame::OnViewZoombar)
  ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOMBAR, &CMainFrame::OnUpdateViewZoombar)
  ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
  END_MESSAGE_MAP()

static UINT indicators[] =
{
  ID_SEPARATOR,           // status line indicator
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame():m_wndOutlineView(this)
{
  // TODO: add member initialization code here
  theApp.AddFrame(this);
}

CPageGotoButton * CMainFrame::GetPageGotoButton() {
  for (int i = 0; i < m_wndGotoBar.GetCount(); i++) {
    UINT nID;
    UINT dwStyle;
    int iImage;
    m_wndGotoBar.GetButtonInfo(i, nID, dwStyle, iImage);
    if (nID == ID_CURRENT_PAGE) {
      return (CPageGotoButton*) m_wndGotoBar.GetButton(i);
    }
  }
  return NULL;
}

CZoomSliderButton * CMainFrame::GetZoomSliderButton() {
  for (int i = 0; i < m_wndZoomBar.GetCount(); i++) {
    UINT nID;
    UINT dwStyle;
    int iImage;
    m_wndZoomBar.GetButtonInfo(i, nID, dwStyle, iImage);
    if (nID == ID_SLIDER_BUTTON) {
      return (CZoomSliderButton*) m_wndZoomBar.GetButton(i);
    }
  }
  return NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
    return -1;

  if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
      !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
    TRACE0("Failed to create toolbar\n");
    return -1;      // fail to create
  }

  m_wndToolBar.SetWindowText(_T("Tool Bar"));

  if (!m_wndGotoBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY  | CBRS_SIZE_DYNAMIC | CBRS_GRIPPER , ID_VIEW_GOTOBAR) ||
      !m_wndGotoBar.LoadToolBar(IDR_GOTO_BAR)) {
    TRACE0("Failed to create toolbar\n");
    return -1;      // fail to create
  }

  m_wndGotoBar.SetWindowText(_T("Goto Bar"));

  if (!m_wndZoomBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY  | CBRS_GRIPPER , ID_VIEW_ZOOMBAR) ||
      !m_wndZoomBar.LoadToolBar(IDR_ZOOM_TOOLBAR)) {
    TRACE0("Failed to create toolbar\n");
    return -1;      // fail to create
  }

  m_wndZoomBar.SetWindowText(_T("Zoom Bar"));

  m_font.CreateFont(16, 0, 0, 0, FW_LIGHT, FALSE,
                  FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                  DEFAULT_PITCH | FF_SWISS, _T("Times"));

  m_wndZoomBar.ReplaceButton(ID_SLIDER_BUTTON, CZoomSliderButton(ID_SLIDER_BUTTON, -1, 0, 200, 50));
  CZoomSliderButton* pZoomSlider = GetZoomSliderButton();
  pZoomSlider->GetEdit()->SetFont(&m_font);

  m_wndGotoBar.ReplaceButton(ID_CURRENT_PAGE, CPageGotoButton(ID_CURRENT_PAGE, -1, 0, 200));
  CPageGotoButton* pButton = GetPageGotoButton();
  pButton->GetComboBox()->SetFont(&m_font);

  m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
  m_wndGotoBar.EnableDocking(CBRS_ALIGN_ANY);
  m_wndZoomBar.EnableDocking(CBRS_ALIGN_ANY);

  EnableDocking(CBRS_ALIGN_ANY);
  EnableAutoHidePanes(CBRS_ALIGN_ANY);

  DockPane(&m_wndToolBar);
  DockPane(&m_wndGotoBar);
  DockPane(&m_wndZoomBar);
  DockPaneLeftOf(&m_wndZoomBar, &m_wndGotoBar);
  DockPaneLeftOf(&m_wndToolBar, &m_wndZoomBar);
  RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

  // prevent the menu bar from taking the focus on activation
  CMFCPopupMenu::SetForceMenuFocus(FALSE);

  if (!m_wndStatusBar.Create(this))
  {
    TRACE0("Failed to create status bar\n");
    return -1;      // fail to create
  }
  m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
 for (int i = 0; i < sizeof(indicators) / sizeof(UINT); i++) {
    m_wndStatusBar.SetPaneTextColor(i, RGB(20, 68, 106));
    m_wndStatusBar.SetFont(&m_font);
    m_wndStatusBar.SetPaneRect(CRect(0, 0, 100, 20));
  }

  CDockingManager::SetDockingMode(DT_IMMEDIATE);
  EnableAutoHidePanes(CBRS_ALIGN_ANY);

  // create docking windows
  if (!CreateDockingWindows())
  {
    TRACE0("Failed to create docking windows\n");
    return -1;
  }

  m_wndOutlineView.EnableDocking(CBRS_ALIGN_ANY);
  DockPane(&m_wndOutlineView);

  // set the visual manager and style based on persisted value

  // set the visual manager used to draw all user interface elements
  CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

  return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  if( !CFrameWndEx::PreCreateWindow(cs) )
    return FALSE;
  // TODO: Modify the Window class or styles here by modifying
  //  the CREATESTRUCT cs

  return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
  BOOL bNameValid;
  CString strFileView;
  bNameValid = strFileView.LoadString(IDS_OUTLINE_VIEW);
  ASSERT(bNameValid);
  if (!m_wndOutlineView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_OUTLINEVIEW, WS_CHILD | WS_VISIBLE | CBRS_LEFT )) {
    TRACE0("Failed to create Outline View window\n");
    return FALSE; // failed to create
  }

  SetDockingWindowIcons(theApp.m_bHiColorIcons);
  return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
  HICON hOutlineViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_OUTLINE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
  m_wndOutlineView.SetIcon(hOutlineViewIcon, FALSE);

}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
  CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
  CFrameWndEx::Dump(dc);
}
#endif //_DEBUG

// CMainFrame message handlers

void CMainFrame::OnClose() {
  CPDFReaderDoc* pDocument = dynamic_cast<CPDFReaderDoc*>(this->GetActiveDocument());
  if (pDocument && pDocument->IsModified()) {
    if (IDYES == AfxMessageBox(L"Do you want save document?", MB_YESNO | MB_ICONQUESTION)) {
      pDocument->Save();
    }
    
  pDocument->SetModifiedFlag(FALSE);
  }

  theApp.RemoveFrame(this);
  CFrameWndEx::OnClose();
}

HBRUSH CMainFrame::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor) {
  return CFrameWndEx::OnCtlColor(pDC, pWnd, nCtlColor);
}

LRESULT CMainFrame::OnToolbarReset(WPARAM wParam, LPARAM lParam) {
  TRACE(L"OnToolbarReset: %d, %d\n", wParam, lParam);
  return 0;
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
  // base class does the real work

  if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
  {
    return FALSE;
  }

  CWinApp* pApp = AfxGetApp();
  pApp->m_pMainWnd = this;

  return TRUE;
}

void CMainFrame::OnFileClose()
{
  DestroyWindow();
}

void CMainFrame::OnViewOutlineview() {
  BOOL bIsVisible = m_wndOutlineView.IsVisible();
  BOOL bIsDocked = m_wndOutlineView.IsDocked();
  BOOL bIsFloating = m_wndOutlineView.IsFloating();
  BOOL bIsAutoHideMode = m_wndOutlineView.IsAutoHideMode();
  if (m_wndOutlineView.IsVisible()) {
    m_wndOutlineView.ShowPane(FALSE, FALSE, TRUE);
  } else {
    m_wndOutlineView.ShowPane(TRUE, FALSE, FALSE);
  }
  TRACE(L"OnViewOutlineview: IsVisible---[%d], IsDocked---[%d], IsFloating---[%d], IsAutoHideMode---[%d]\n", bIsVisible, bIsDocked, bIsFloating, bIsAutoHideMode);
}

void CMainFrame::OnUpdateViewOutlineview(CCmdUI *pCmdUI) {
  pCmdUI->Enable(TRUE);
  if (m_wndOutlineView.IsVisible())
    pCmdUI->SetCheck(TRUE);
  else
    pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnAppExit() {
  OnClose();
}

void CMainFrame::OnViewGotobar() {
  m_wndGotoBar.ShowPane(!m_wndGotoBar.IsVisible(), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewGotobar(CCmdUI *pCmdUI) {
  pCmdUI->Enable(TRUE);
  if (m_wndGotoBar.IsVisible())
    pCmdUI->SetCheck(TRUE);
  else
    pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnViewToolbar() {
  m_wndToolBar.ShowPane(!m_wndToolBar.IsVisible(), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewToolbar(CCmdUI *pCmdUI) {
  pCmdUI->Enable(TRUE);
  if (m_wndToolBar.IsVisible())
    pCmdUI->SetCheck(TRUE);
  else
    pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnViewZoombar() {
  m_wndZoomBar.ShowPane(!m_wndZoomBar.IsVisible(), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewZoombar(CCmdUI *pCmdUI) {
  pCmdUI->Enable(TRUE);
  if (m_wndZoomBar.IsVisible())
    pCmdUI->SetCheck(TRUE);
  else
    pCmdUI->SetCheck(FALSE);
}

IMPLEMENT_SERIAL(CSelfToolBar,CMFCToolBar,1)

CSelfToolBar::CSelfToolBar() {}

BOOL CSelfToolBar::LoadState(LPCTSTR lpszProfileName, int nIndex, UINT uiID) {
  // not save state of tool bar
   return TRUE;
}

BOOL CSelfToolBar::SaveState(LPCTSTR lpszProfileName, int nIndex, UINT uiID) {
  // not load state of tool bar
  return TRUE;
}
//

void CMainFrame::OnFileOpen() {
  auto pActiveDoc = DYNAMIC_DOWNCAST(CPDFReaderDoc, GetActiveDocument());
  if (pActiveDoc->GetPDFDocument().IsEmpty())
    pActiveDoc->ClearPathName();

  AfxGetApp()->m_pDocManager->OnFileOpen();

  if (AfxGetApp()->GetOpenDocumentCount() > 1) {
    if (pActiveDoc->GetPDFDocument().IsEmpty())
      OnClose();
  }
}
