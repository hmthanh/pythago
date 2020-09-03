#include "PDFReader\Source\stdafx.h"
#include "PDFReader\Reader\MainFrm.h"
#include "PDFReader\DockablePane\OutlineDockablePane.h"
#include "PDFReader\Resource\Resource.h"
#include "PDFReader\Reader\PDFReader.h"
#include "PDFReader\Reader\PDFReaderDoc.h"
#include "PDFReader\Reader\PDFReaderView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define OUTLINE_VIEW_TREE_ID 4
#define OUTLINE_FILL_TREE_TIMER 0xff01

/////////////////////////////////////////////////////////////////////////////
// COutlineViewTree


COutlineViewTree::COutlineViewTree(CMainFrame * pFrame) :m_pFrame(pFrame) {}
COutlineViewTree::~COutlineViewTree() {}


BEGIN_MESSAGE_MAP(COutlineViewTree, CTreeCtrl)
  ON_WM_PAINT()
  ON_NOTIFY_REFLECT(TVN_SELCHANGED, &COutlineViewTree::OnTvnSelchanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlineViewTree message handlers


BOOL COutlineViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
  BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

  NMHDR* pNMHDR = (NMHDR*) lParam;
  ASSERT(pNMHDR != NULL);

  if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL) {
    GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
  }
  return bRes;
}

/////////////////////////////////////////////////////////////////////////////
// COutlineView

COutlineView::COutlineView(CMainFrame* pFrame):m_pFrame(pFrame) ,m_wndOutlineView(pFrame) , m_bHasFill(FALSE)
{
}

void COutlineView::ConvertToTabbedDocument(BOOL bActiveTabOnly) {}

COutlineView::~COutlineView()
{
}


BEGIN_MESSAGE_MAP(COutlineView, CDockablePane)
  ON_WM_CREATE()
  ON_WM_SIZE()
  ON_WM_CONTEXTMENU()
  ON_WM_SETFOCUS()
  ON_WM_CLOSE()
  ON_WM_TIMER()
  ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int COutlineView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CDockablePane::OnCreate(lpCreateStruct) == -1)
    return -1;

  CRect rectDummy;
  rectDummy.SetRectEmpty();

  // Create view:
  const DWORD dwViewStyle = TVS_DISABLEDRAGDROP| LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT & ~LBS_COMBOBOX & ~TVS_SHOWSELALWAYS;

  if (!m_wndOutlineView.Create(dwViewStyle, rectDummy, this, OUTLINE_VIEW_TREE_ID))
  {
    TRACE0("Failed to create outline view\n");
    return -1;      // fail to create
  }

  m_wndOutlineView.ModifyStyle(TVS_CHECKBOXES, 0);
  m_wndOutlineView.ModifyStyle(0, TVS_CHECKBOXES);
  m_wndOutlineView.SelectItem(NULL);

  OnChangeVisualStyle();
  AdjustLayout();
  SetTimer(OUTLINE_FILL_TREE_TIMER, 100, NULL);
  return 0;
}

void COutlineView::OnSize(UINT nType, int cx, int cy)
{
  CDockablePane::OnSize(nType, cx, cy);
  AdjustLayout();
}

void COutlineView::FillOutlineView()
{
  CPDFReaderDoc* pReaderDoc = (CPDFReaderDoc*)theApp.GetDocByFrame(m_pFrame);
  if (!pReaderDoc || !pReaderDoc->HasLoadDocument())
    return;
  PDFDoc pdf_doc = pReaderDoc->GetPDFDocument();
  Bookmark root_bookmark = pdf_doc.GetRootBookmark();
  AddOutlineItem(root_bookmark, 0);
  m_bHasFill = TRUE;
}

void COutlineView::AddOutlineItem(Bookmark parent_bookmark, HTREEITEM hParent) {
  if (parent_bookmark.IsEmpty())
    return;
  Bookmark child_bookmark = parent_bookmark.GetFirstChild();
  HTREEITEM hChild = 0;
  while (!child_bookmark.IsEmpty()) {
    foxit::WString title = child_bookmark.GetTitle();
    hChild = m_wndOutlineView.InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE, CString((const wchar_t*)title), 0, 1, 0, 0, 0, hParent,hChild);
    m_wndOutlineView.SetItemState(hChild, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK);
    m_wndOutlineView.SetItemData(hChild, child_bookmark);

    AddOutlineItem(child_bookmark, hChild);
    child_bookmark = child_bookmark.GetNextSibling();
  }
}

void COutlineView::OnContextMenu(CWnd* pWnd, CPoint point)
{
  CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndOutlineView;
  ASSERT_VALID(pWndTree);

  if (pWnd != pWndTree)
  {
    CDockablePane::OnContextMenu(pWnd, point);
    return;
  }

  if (point != CPoint(-1, -1))
  {
    // Select clicked item:
    CPoint ptTree = point;
    pWndTree->ScreenToClient(&ptTree);

    UINT flags = 0;
    HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
    if (hTreeItem != NULL)
    {
      pWndTree->SelectItem(hTreeItem);
    }
  }

  pWndTree->SetFocus();
}

void COutlineView::AdjustLayout()
{
  if (GetSafeHwnd() == NULL)
  {
    return;
  }

  CRect rectClient;
  GetClientRect(rectClient);

  m_wndOutlineView.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
  Invalidate();
}

void COutlineView::OnPaint()
{
  CPaintDC dc(this); // device context for painting
  CRect rectTree;
  m_wndOutlineView.GetWindowRect(rectTree);
  ScreenToClient(rectTree);

  // rectTree.InflateRect(1, 1);
  dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void COutlineView::OnSetFocus(CWnd* pOldWnd)
{
  CDockablePane::OnSetFocus(pOldWnd);

  //m_wndOutlineView.SetFocus();
}

void COutlineView::OnChangeVisualStyle()
{
  m_OutlineViewImages.DeleteImageList();

  UINT uiBmpId[] = {IDB_OUTLINE_BITMAP, IDB_OUTLINE_SEL_BITMAP};
  for (int i = 0; i < 2; i++) {
    CBitmap bmp;
    if (!bmp.LoadBitmap(uiBmpId[i])) {
      TRACE(_T("Can't load bitmap: %x\n"), uiBmpId[i]);
      ASSERT(FALSE);
      return;
    }

    BITMAP bmpObj;
    bmp.GetBitmap(&bmpObj);

    UINT nFlags = ILC_MASK;

    nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;
    if (i == 0)
      m_OutlineViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
    m_OutlineViewImages.Add(&bmp, RGB(255, 0, 255));
  }

  m_wndOutlineView.SetImageList(&m_OutlineViewImages, TVSIL_NORMAL);
}

void COutlineViewTree::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) {
  LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
  *pResult = 1;
  HTREEITEM item = GetSelectedItem();

  CPDFReaderDoc* pReaderDoc = (CPDFReaderDoc*) theApp.GetDocByFrame(m_pFrame);
  POSITION pos = pReaderDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) pReaderDoc->GetNextView(pos);
  ASSERT(pos == NULL);
  ASSERT(pView != NULL);
  Bookmark bookmark = GetItemData(item);
  Action bookmark_action;
  try {
    bookmark_action = bookmark.GetAction();
  } catch (const foxit::Exception&) {
    return;
  }
  if (!bookmark_action.IsEmpty()) {
    pView->DoAction(bookmark_action);
  } else {
    Destination bookmark_dest = bookmark.GetDestination();
    pView->GotoDestination(bookmark_dest);
  }
}

void COutlineViewTree::OnPaint() {
  CPaintDC dc(this);  // device context for painting

  CDC memDC;
  memDC.CreateCompatibleDC(&dc);
  CRect rcClient;
  GetClientRect(&rcClient);
  memDC.FillRect(rcClient, NULL);
  CBitmap bitmap;
  bitmap.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
  memDC.SelectObject(&bitmap);

  CRgn rgn;
  rgn.CreateRectRgnIndirect(&rcClient);
  memDC.SelectClipRgn(&rgn);
  rgn.DeleteObject();
  CWnd::DefWindowProc(WM_PAINT, (WPARAM)memDC.m_hDC, 0);

  HTREEITEM hItem = GetFirstVisibleItem();
  while (hItem) {
    UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED;
    Bookmark bookmark = GetItemData(hItem);
    foxit::RGB color = bookmark.GetColor();
    int r = color << 8 >> 24;
    int g = color << 16 >> 24;
    int b = color << 24 >> 24;
    foxit::uint32 style = bookmark.GetStyle();

    CFont font;
    font.CreateFont(16, 0, 0, 0, style & Bookmark::e_StyleBold ? FW_BOLD : FW_MEDIUM, style & Bookmark::e_StyleItalic,
                    FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                    DEFAULT_PITCH | FF_SWISS, _T("Helvetica"));

    memDC.SetTextColor((GetItemState(hItem, selflag) & selflag) ? RGB(255, 255, 255) : RGB(r, g, b));
    CString strItem = GetItemText(hItem);
    CRect rectText;
    GetItemRect(hItem, &rectText, TRUE);
    CRect rect;
    GetItemRect(hItem, &rect, FALSE);

    rectText.right = rect.right;
    rectText.top = rect.top;
    rectText.bottom = rect.bottom;

    CBrush brush;
    brush.CreateSolidBrush(GetItemState(hItem, selflag) & selflag ? RGB(69, 137, 148) : GetSysColor(COLOR_WINDOW));
    DeleteObject(&brush);
    memDC.SelectObject(&brush);
    memDC.FillRect(rectText, &brush);
    if (GetItemState(hItem, selflag) & selflag) {
      CPen pen;
      pen.CreatePen(PS_JOIN_ROUND | PS_SOLID, 1, RGB(69, 137, 148));

      memDC.SelectObject(pen);
      memDC.SelectObject(CBrush::FromHandle((HBRUSH) GetStockObject(NULL_BRUSH)));
      memDC.Rectangle(rect);
    }

    memDC.SetBkColor((GetItemState(hItem, selflag) & selflag) ? RGB(246, 139, 36) : GetSysColor(COLOR_WINDOW));
    memDC.SetBkMode(TRANSPARENT);
    memDC.SelectObject(font);
    DeleteObject(&font);

    memDC.TextOut(rectText.left, rectText.top, strItem);
    hItem = GetNextVisibleItem(hItem);
  }
  dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), &memDC, rcClient.left, rcClient.top, SRCCOPY);
}

Bookmark COutlineViewTree::GetItemData(HTREEITEM hItem) const {
  typedef std::vector<Bookmark>::size_type vsize_type;
  vsize_type value = (vsize_type)(CTreeCtrl::GetItemData(hItem));
  return m_vBookmarks[value-1];
}

BOOL COutlineViewTree::SetItemData(HTREEITEM hItem, Bookmark bookmark) {
  typedef std::vector<Bookmark>::size_type vsize_type;
  vsize_type value = CTreeCtrl::GetItemData(hItem);
  if (value>0) {
    m_vBookmarks[value-1] = bookmark;
  } else {
    m_vBookmarks.push_back(bookmark);
    value = m_vBookmarks.size();
    CTreeCtrl::SetItemData(hItem, (DWORD_PTR)(value));
  }
  return TRUE;
}


void COutlineView::OnTimer(UINT_PTR nIDEvent) {
  if (nIDEvent == OUTLINE_FILL_TREE_TIMER && IsVisible()) {
    if (!m_bHasFill)
      FillOutlineView();
    AdjustLayout();

    KillTimer(OUTLINE_FILL_TREE_TIMER);
  }
  CRect clientRect;
  GetClientRect(&clientRect);
  m_nSlideDelta = max(clientRect.Height(),clientRect.Width())+10;
  return CDockablePane::OnTimer(nIDEvent);
}

void COutlineView::OnShowWindow(BOOL bShow, UINT nStatus) {
  if (!m_bHasFill)
    FillOutlineView();
  CDockablePane::OnShowWindow(bShow, nStatus);
}
