
// PDFReaderView.cpp : implementation of the CPDFReaderView class
//

#include "PDFReader\source\stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PDFReader.h"
#endif

#include "MainFrm.h"

#include "PDFReaderDoc.h"
#include "PDFReaderView.h"
#include "FindDlg.h"
#include "SliderButton.h"
#include "PDFReader/Reader/PageGotoButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4482)

#define RENDER_BACKGROUND_COLOR RGB(178,200,187)
#define RENDER_PAGE_COLOR 0xFFFFFFFF
#define IDC_ANNOT_TEXT_EDIT 12345
#define PER_UPDATE_NUM 50
#define AUTOSCROLL_TIMER_ID 1
// CPDFReaderView

IMPLEMENT_DYNCREATE(CPDFReaderView, CView)

BEGIN_MESSAGE_MAP(CPDFReaderView, CView)
  //{{AFX_MSG_MAP(CPDFDisplayView)
  ON_WM_HSCROLL()
  ON_WM_VSCROLL()
  ON_WM_MOUSEWHEEL()
  ON_WM_ERASEBKGND()
  ON_WM_SIZE()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_RBUTTONDOWN()
  ON_WM_RBUTTONUP()
  ON_WM_RBUTTONDBLCLK()
  ON_WM_LBUTTONDBLCLK()
  ON_WM_MOUSEMOVE()
  ON_WM_CHAR()
  ON_WM_KEYDOWN()
  ON_WM_KEYUP()
  ON_WM_TIMER()
  ON_COMMAND(ID_PDF_ZOOM_IN, &CPDFReaderView::OnZoomIn)
  ON_COMMAND(ID_PDF_ZOOM_OUT, &CPDFReaderView::OnZoomOut)
  ON_COMMAND(ID_FILE_PRINT, &CPDFReaderView::OnFilePrint)
  ON_COMMAND(ID_FILE_SAVE, &CPDFReaderView::OnFileSave)
  ON_COMMAND(ID_FILE_SAVE_AS, &CPDFReaderView::OnFileSaveAs)
  ON_COMMAND(ID_PDF_HANDLE, &CPDFReaderView::OnPDFHand)
  ON_COMMAND(ID_PDF_SELECT, &CPDFReaderView::OnPDFSelect)
  ON_COMMAND(ID_PDF_SEARCH, &CPDFReaderView::OnPDFSearch)
  ON_COMMAND(ID_SLIDER_BUTTON, &CPDFReaderView::OnSlider)
  ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CPDFReaderView::OnUpdateFileSaveAs)
  ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CPDFReaderView::OnUpdateFileSave)
  ON_UPDATE_COMMAND_UI(ID_PDF_HANDLE, &CPDFReaderView::OnUpdatePDFHand)
  ON_UPDATE_COMMAND_UI(ID_PDF_SELECT, &CPDFReaderView::OnUpdatePDFSelect)
  ON_UPDATE_COMMAND_UI(ID_PDF_SEARCH, &CPDFReaderView::OnUpdatePDFSearch)
  ON_UPDATE_COMMAND_UI(ID_PDF_ZOOM_IN, &CPDFReaderView::OnUpdateZoomIn)
  ON_UPDATE_COMMAND_UI(ID_PDF_ZOOM_OUT, &CPDFReaderView::OnUpdateZoomOut)
  ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, &CPDFReaderView::OnUpdateFilePrint)
  ON_COMMAND(ID_FIRST_PAGE, &CPDFReaderView::OnFirstPage)
  ON_COMMAND(ID_PREV_PAGE, &CPDFReaderView::OnPrevPage)
  ON_COMMAND(ID_CURRENT_PAGE, &CPDFReaderView::OnGotoPage)
  ON_COMMAND(ID_NEXT_PAGE, &CPDFReaderView::OnNextPage)
  ON_COMMAND(ID_LAST_PAGE, &CPDFReaderView::OnLastPage)
  ON_UPDATE_COMMAND_UI(ID_FIRST_PAGE, &CPDFReaderView::OnUpdateFirstPage)
  ON_UPDATE_COMMAND_UI(ID_PREV_PAGE, &CPDFReaderView::OnUpdatePrevPage)
  ON_UPDATE_COMMAND_UI(ID_NEXT_PAGE, &CPDFReaderView::OnUpdateNextPage)
  ON_UPDATE_COMMAND_UI(ID_LAST_PAGE, &CPDFReaderView::OnUpdateLastPage)
  //}}AFX_MSG_MAP

  ON_WM_CTLCOLOR()
  ON_COMMAND(ID_PDF_ROTATE_CW, &CPDFReaderView::OnCWRotae)
  ON_COMMAND(ID_PDF_ROTATE_ACW, &CPDFReaderView::OnACWRotation)
  // Standard printing commands
  ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPDFReaderView::OnFilePrintPreview)
  ON_WM_CONTEXTMENU()

  ON_COMMAND(ID_ANNOT_FREETEXT, &CPDFReaderView::OnAnnotFreetext)
  ON_COMMAND(ID_ANNOT_HIGHLIGHT, &CPDFReaderView::OnAnnotHighlight)
  ON_COMMAND(ID_ANNOT_NOTES, &CPDFReaderView::OnAnnotNotes)
  ON_COMMAND(ID_ANNOT_LINK, &CPDFReaderView::OnAnnotLink)
  ON_COMMAND(ID_ANNOT_UNDERLINE, &CPDFReaderView::OnAnnotUnderline)
  ON_COMMAND(ID_TOOL_ANNOTSELECT, &CPDFReaderView::OnToolAnnotselect)
  ON_UPDATE_COMMAND_UI(ID_ANNOT_FREETEXT, &CPDFReaderView::OnUpdateAnnotFreetext)
  ON_UPDATE_COMMAND_UI(ID_ANNOT_HIGHLIGHT, &CPDFReaderView::OnUpdateAnnotHighlight)
  ON_UPDATE_COMMAND_UI(ID_ANNOT_NOTES, &CPDFReaderView::OnUpdateAnnotNotes)
  ON_UPDATE_COMMAND_UI(ID_ANNOT_LINK, &CPDFReaderView::OnUpdateAnnotLink)
  ON_UPDATE_COMMAND_UI(ID_ANNOT_UNDERLINE, &CPDFReaderView::OnUpdateAnnotUnderline)
  ON_UPDATE_COMMAND_UI(ID_TOOL_ANNOTSELECT, &CPDFReaderView::OnUpdateToolAnnotselect)
  ON_WM_SETCURSOR()
  ON_WM_MBUTTONDOWN()
  ON_WM_DESTROY()
  ON_WM_SETFOCUS()
  ON_COMMAND(ID_WM_XFA_COPY, &CPDFReaderView::OnCopy)
  ON_COMMAND(ID_WM_XFA_CUT, &CPDFReaderView::OnCut)
  ON_COMMAND(ID_WM_XFA_SELECTALL, &CPDFReaderView::OnSelectAll)
  ON_COMMAND(ID_WM_XFA_DESELECT, &CPDFReaderView::OnDeSelect)
  ON_COMMAND(ID_WM_XFA_PASTE, &CPDFReaderView::OnPaste)
  ON_COMMAND(ID_WM_XFA_DELETE, &CPDFReaderView::OnDelete)
  ON_COMMAND(ID_WM_XFA_UNDO, &CPDFReaderView::OnUndo)
  ON_COMMAND(ID_WM_XFA_REDO, &CPDFReaderView::OnRedo)
  ON_COMMAND(ID_WM_XFA_TEXTSTYLE_BOLD, &CPDFReaderView::OnBold)
  ON_COMMAND(ID_WM_XFA_TEXTSTYLE_ITALIC, &CPDFReaderView::OnItalic)
  ON_COMMAND(ID_WM_XFA_TEXTSTYLE_UNDERLINE, &CPDFReaderView::OnUnderLine)
  ON_COMMAND(ID_WM_XFA_TEXTSTYLE_SUPERSCRIPT, &CPDFReaderView::OnSuperScript)
  ON_COMMAND(ID_WM_XFA_TEXTSTYLE_SUBSCRIPT, &CPDFReaderView::OnSubScript)
  ON_COMMAND(ID_WM_XFA_TEXTSTYLE_CLEARSTYLE, &CPDFReaderView::OnClearStyle)
END_MESSAGE_MAP()

// CPDFReaderView construction/destruction

CPDFReaderView::CPDFReaderView()
    : m_pTimerCallback(NULL)
    , m_nLogPixelX(0)
    , m_nLogPixelY(0)
    , m_Rotate(e_Rotation0)
    , m_fZoom(1.0)
    , m_bScrollFlag(TRUE)
    , m_bRatateChange(TRUE)
    , m_bZoomChange(TRUE)
    , m_nCurPageIndex(0)
    , m_nBoxPage(-1)
    , m_nStartPageIndex(-1)
    , m_nEndPageIndex(-1)
    , m_nTextPagePage(0)
    , m_eCurPageLinkType(CReader_Page::NOLINK)
    , m_DrawingAnnotType((Annot::Type)-1)
    , m_OperatorType(UNKNOWN)
    , m_bFixedAutoScroll(FALSE)
    , m_nStartCharIndex(-1)
    , m_nEndCharIndex(-1)
    , m_bLButtonDown(FALSE)
    , m_pAnnotPropertyDlg(NULL)
    , m_pEdit(NULL)
    , m_strFreetextContent(_T(""))
    , m_pFreeTextAnnotEditFont(NULL)
    , m_bAnnotIsEdit(FALSE)
    , m_eUnicodeSupportType(NOT_CHECK_SUPPORT)
    , m_bPrepareLabels(FALSE) {
  m_fLastZoom = m_fZoom;

  m_Horzsi.nMin = 0;
  m_Horzsi.nMax = 0;
  m_Horzsi.nPage = 0;
  m_Horzsi.cbSize = sizeof(SCROLLINFO);
  m_Horzsi.fMask = SIF_ALL;
  m_Horzsi.nPos = 0;
  m_Horzsi.nTrackPos = 0;

  //vertical scroll bar
  m_Vertsi.nMin = 0;
  m_Vertsi.nMax = 0;
  m_Vertsi.nPage = 0;
  m_Vertsi.cbSize = sizeof(SCROLLINFO);
  m_Vertsi.fMask = SIF_ALL;
  m_Vertsi.nPos = 0;
  m_Vertsi.nTrackPos = 0;
}

CPDFReaderView::~CPDFReaderView()
{
  if (m_pEdit) {
    delete m_pEdit;
    m_pEdit = NULL;
  }

  if (m_pFreeTextAnnotEditFont) {
    delete m_pFreeTextAnnotEditFont;
    m_pFreeTextAnnotEditFont = NULL;
  }

  if (m_pAnnotPropertyDlg) {
    delete m_pAnnotPropertyDlg;
    m_pAnnotPropertyDlg = NULL;
  }
}

BOOL CPDFReaderView::PreCreateWindow(CREATESTRUCT& cs){
  return CView::PreCreateWindow(cs);
}

void CPDFReaderView::OnInitialUpdate() {
  CView::OnInitialUpdate();
  if (!m_pFreeTextAnnotEditFont)
    m_pFreeTextAnnotEditFont = new CFont();
  CPDFReaderDoc* document = GetDocument();
  SetScrollInfo(SB_HORZ, &m_Horzsi);
  SetScrollInfo(SB_VERT, &m_Vertsi);
}

void CPDFReaderView::DisplayCaret(int pageIndex, BOOL bVisible, const foxit::RectF& pRtAnchor) {
  m_CaretInfo.bVisible = bVisible;
  if (bVisible) {
    m_CaretInfo.rtAnchor = pRtAnchor;
    m_CaretInfo.nPageIndex = pageIndex;

    CRect rtCaret;
    DocToWindow(pageIndex, pRtAnchor, rtCaret);
    ::DestroyCaret();
    ::CreateCaret(m_hWnd, (HBITMAP)0, 0, (int)rtCaret.Height());
    ::SetCaretPos ((int)rtCaret.left, (int)rtCaret.top);
    ::ShowCaret(m_hWnd);
  } else {
    ::DestroyCaret();
    ::HideCaret(m_hWnd);
  }
}

CRect CPDFReaderView::GetPageRect(int page_index)
{
  if(m_vecPageToDisplay.empty())
    return CRect(0,0,0,0);

  std::vector<PageToDisplay>::iterator i;
  for (i = m_vecPageToDisplay.begin(); i != m_vecPageToDisplay.end(); i++) 
  {
    if(i->page_index == page_index)
    {
      CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(i->page_index);
      float width = 0, height = 0;
      if (m_Rotate == e_Rotation0 || m_Rotate == e_Rotation180) 
      {
        height = pReaderPage->GetPageHeight() * m_fZoom;
        width = pReaderPage->GetPageWidth() * m_fZoom;
      } 
      else 
      {
        height = pReaderPage->GetPageWidth() * m_fZoom;
        width = pReaderPage->GetPageHeight() * m_fZoom;
      }
      RECT rcPage = {i->cx, i->cy, i->cx + width, i->cy + height};
      RECT rc;
      this->GetClientRect(&rc);
      rcPage.left = max(rc.left, rcPage.left);
      rcPage.right = min(rc.right,rcPage.right);
      rcPage.top = max(rc.top, rcPage.top);
      rcPage.bottom = min(rc.bottom, rcPage.bottom);
      return rcPage;
    }
  }
  return CRect(0,0,0,0);
}

void CPDFReaderView::OnDraw(CDC* pDC)
{
  if (!HasAviliableDoc()) {
    return;
  }
  if (m_bZoomChange || m_bScrollFlag || m_bRatateChange) {
    m_nLogPixelX = pDC->GetDeviceCaps(LOGPIXELSX);  //screen resolution
    m_nLogPixelY = pDC->GetDeviceCaps(LOGPIXELSY);
    InitScrollSize(m_nLogPixelX, m_nLogPixelY);
    SetVisiblePageByScrollPos();
    m_bScrollFlag = FALSE;
    m_bZoomChange = FALSE;
    m_bRatateChange = FALSE;
  }
  if (!m_vecPageToDisplay.empty()) {
    std::vector<PageToDisplay>::iterator i;
    CDC dcMem;
    CBitmap bm;
    CRect rc;

    dcMem.CreateCompatibleDC(pDC);
    this->GetClientRect(&rc);

    bm.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
    HBITMAP hOldbmp = (HBITMAP)::SelectObject(dcMem.GetSafeHdc(), (HBITMAP) bm.GetSafeHandle());

    dcMem.FillSolidRect(0, 0, rc.Width(), rc.Height(), RENDER_BACKGROUND_COLOR);

    for (i = m_vecPageToDisplay.begin(); i != m_vecPageToDisplay.end(); i++) {
      CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(i->page_index);
      float width = 0, height = 0;
      if (m_Rotate == e_Rotation0 || m_Rotate == e_Rotation180) {
        height = pReaderPage->GetPageHeight() * m_fZoom;
        width = pReaderPage->GetPageWidth() * m_fZoom;
      } else {
        height = pReaderPage->GetPageWidth() * m_fZoom;
        width = pReaderPage->GetPageHeight() * m_fZoom;
      }

      //Shadows on the surface of the page

      int cyTemp = (int) i->cy;
      RenderPageByGE(&dcMem, (int)i->page_index, (int)width, (int)height, i->cx, cyTemp);

      int nShadow = GetDocument()->GetPageShadowWidth();
      CRect rcShadowRight((int)(i->cx + width), cyTemp + nShadow, (int)(i->cx + width + nShadow),
                          (int)(cyTemp + height + nShadow));
      dcMem.FillSolidRect(&rcShadowRight, RGB(74, 86, 104));
      CRect rcShadowBottom(i->cx + nShadow, (int) (cyTemp + height), (int) (i->cx + width),
        (int) (cyTemp + height + nShadow));
      dcMem.FillSolidRect(&rcShadowBottom, RGB(74, 86, 104));
    }

    if (GetOperatorType() == DRAWINGANNOT) {
      if (m_DrawingAnnotType == Annot::e_Highlight || m_DrawingAnnotType == Annot::e_Underline) {
        if((m_nStartCharIndex >= 0) && (m_nEndCharIndex >= 0))
          DrawSelectText(&dcMem);
      } else {
        CRect rect(m_StartPt, m_EndPt);
        rect.NormalizeRect();
        if (!rect.IsRectEmpty() && IsInPageRect(m_StartPt) && IsInPageRect(m_EndPt)) {
          CBrush br;
          CPen pen;
          pen.CreatePen(PS_SOLID, 1, RGB(74, 86, 104));
          br.CreateStockObject(NULL_BRUSH);
          HGDIOBJ OldBr = dcMem.SelectObject(&pen);
          HGDIOBJ OldPen = dcMem.SelectObject(&br);
          rect.NormalizeRect();
          dcMem.Rectangle(rect);

          dcMem.SelectObject(&OldBr);
          dcMem.SelectObject(&OldPen);
        }
      }
    } else if (GetOperatorType() == ANNOTSELECT) {
      DoAnnotDrawBorder(&dcMem);
    } else if (GetOperatorType() == TextPage && (m_nStartCharIndex >= 0) && (m_nEndCharIndex >= 0)) {
      DrawSelectText(&dcMem);
    } else if (m_OperatorType == AUTOSCROLL) {
      DrawAutoScrollReminder(&dcMem);
    }
    DrawFindText(&dcMem);

    pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, SRCCOPY);

    bm.DeleteObject();
    DeleteObject(hOldbmp);
    dcMem.DeleteDC();

	TriggerPageAction();
  }
}

void CPDFReaderView::DrawAutoScrollReminder(CDC * pDC) {
  CRect rect(m_StartPt.x - 20,m_StartPt.y -20,m_StartPt.x+20,m_StartPt.y+20);
  Gdiplus::Bitmap bmp(rect.right, rect.bottom);

  Gdiplus::Graphics* graph = Gdiplus::Graphics::FromImage(&bmp);
  graph->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
  Gdiplus::Pen pen(Gdiplus::Color(222, 156, 83));
  pen.SetWidth(3);
  pen.SetEndCap(Gdiplus::LineCapArrowAnchor);
  Gdiplus::SolidBrush brush(Gdiplus::Color(222, 211, 140));

  Gdiplus::PointF pt(20, 20);
  graph->DrawEllipse(&pen, pt.X - 10.0f, pt.Y - 10.0f, 20.f, 20.f);
  graph->FillEllipse(&brush, Gdiplus::RectF(pt.X - 5.0f, pt.Y - 5.0f, 10, 10));

  Gdiplus::PointF points_left[] = {Gdiplus::PointF(pt.X - 14, pt.Y + 7), Gdiplus::PointF(pt.X - 14, pt.Y - 7),
                                   Gdiplus::PointF(pt.X - 19, pt.Y)};
  graph->FillPolygon(&brush, points_left, 3);
  Gdiplus::PointF points_right[] = {Gdiplus::PointF(pt.X + 14, pt.Y + 7), Gdiplus::PointF(pt.X + 14, pt.Y - 7),
                                    Gdiplus::PointF(pt.X + 19, pt.Y)};
  graph->FillPolygon(&brush, points_right, 3);
  Gdiplus::PointF bottom_points[] = {Gdiplus::PointF(pt.X - 7, pt.Y + 14), Gdiplus::PointF(pt.X + 7, pt.Y + 14),
                                     Gdiplus::PointF(pt.X, pt.Y + 19)};
  graph->FillPolygon(&brush, bottom_points, 3);
  Gdiplus::PointF top_points[] = {Gdiplus::PointF(pt.X - 7, pt.Y - 14), Gdiplus::PointF(pt.X + 7, pt.Y - 14),
                                  Gdiplus::PointF(pt.X, pt.Y - 19)};
  graph->FillPolygon(&brush, top_points, 3);
  float length = (float)sqrt(pow(float(m_EndPt.x - m_StartPt.x), 2.0f) + pow(float(m_EndPt.y - m_StartPt.y), 2.0f));
  if (length > 3) {
    Gdiplus::PointF EndPt;
    EndPt.X = (m_EndPt.x - m_StartPt.x) / length * 20.0f + pt.X;
    EndPt.Y = (m_EndPt.y - m_StartPt.y) / length * 20.0f + pt.Y;
    pen.SetColor(Gdiplus::Color(137, 190, 178));
    pen.SetWidth(5);
    graph->DrawLine(&pen, pt, EndPt);
  }
  Gdiplus::Graphics graphics(pDC->m_hDC);
  graphics.DrawImage(&bmp, rect.left, rect.top, rect.right, rect.bottom);
  delete graph;
}

void CPDFReaderView::DrawTextRect(CDC * pDc, const foxit::RectF & rect,int nPageIndex) {
  foxit::Matrix matrix = GetPageMatrix(nPageIndex);
  foxit::RectF rc = rect;
  matrix.TransformRect(rc);
  if (rc.bottom<rc.top && !GetDocument()->isDynamicXFA()) {
    float temp = rc.bottom;
    rc.bottom = rc.top;
    rc.top = temp;
  }
  COLORREF clrSrc = RGB(246, 185, 77);

  (GetDocument()->isDynamicXFA() ? rc.top : rc.bottom) += abs(rc.top - rc.bottom) *0.05f * m_fZoom;

  int nSavedDC = pDc->SaveDC();//Save the original DC.

  int nWidth = (int) abs(rc.right - rc.left); //The width of the semitransparent zone.
  int nHeight = (int) abs(rc.top - rc.bottom); // The height of the semitransparent zone.

                                              //Copy the screen: create a new DC to copy the target area.
  CDC bmpDC;
  bmpDC.CreateCompatibleDC(pDc);

  //Create a base bitmap
  CBitmap bmp;
  bmp.CreateCompatibleBitmap(pDc, nWidth, nHeight);
  CBitmap* pOldBmp = (CBitmap*) bmpDC.SelectObject(&bmp);
  bmpDC.BitBlt(0, 0, nWidth, nHeight, pDc, (int) rc.left, GetDocument()->isDynamicXFA() ? (int) rc.bottom:(int) rc.top, SRCCOPY);

  //Retrieve the bitmap data from bmpDC and save the data to a BYTE array(pbtPixels).
  HDC hDIBDC = CreateCompatibleDC(NULL);
  BITMAPINFO hdr;
  ZeroMemory(&hdr, sizeof(BITMAPINFO));
  hdr.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  hdr.bmiHeader.biWidth = nWidth;
  hdr.bmiHeader.biHeight = nHeight;
  hdr.bmiHeader.biPlanes = 1;
  hdr.bmiHeader.biBitCount = 32;
  //Here we use a 32-bit bitmap. Because the structure of it is relatively fixed, and each pixel is presented by 4 bytes and no extra bytes need to be added to the trail of each line.
  //However, to a 24-bit bitmap, extra bytes need to be added to the trail of each line in order to make sure that the count of bytes of each line is an integer multiple of 4.
  //If you want to reduce the overhead and the count of bytes, you can choose to use a 24-bit bitmap. But you have to add some more codes for the extra judgment.

  BYTE * pbtPixels = NULL;
  HBITMAP hDIBitmap = CreateDIBSection(hDIBDC, (BITMAPINFO  *) &hdr, DIB_RGB_COLORS, (void **) &pbtPixels, NULL, 0);
  HBITMAP hOldBmp = (HBITMAP) SelectObject(hDIBDC, hDIBitmap);
  BitBlt(hDIBDC, 0, 0, nWidth, nHeight, bmpDC.m_hDC, 0, 0, SRCCOPY);
  SelectObject(hDIBDC, hOldBmp);

  int nPixelSize = 4;//Each pixel needs 4 bytes to store.

  BYTE btSR = GetRValue(clrSrc);
  BYTE btSG = GetGValue(clrSrc);
  BYTE btSB = GetBValue(clrSrc);

  for (int i = 0; i < nHeight; i++) {
    for (int j = 0; j < nWidth; j++) {

      BYTE btB = pbtPixels[i * nWidth * nPixelSize + j * nPixelSize];
      BYTE btG = pbtPixels[i * nWidth * nPixelSize + j * nPixelSize + 1];
      BYTE btR = pbtPixels[i * nWidth * nPixelSize + j * nPixelSize + 2];

      btB = (btSB + btB) >> 1;
      btG = (btSG + btG) >> 1;
      btR = (btSR + btR) >> 1;

      pbtPixels[i * nWidth * nPixelSize + j * nPixelSize] = btB;
      pbtPixels[i * nWidth * nPixelSize + j * nPixelSize + 1] = btG;
      pbtPixels[i * nWidth * nPixelSize + j * nPixelSize + 2] = btR;
    }
  }

  //Draw the final semitransparent graph to the target area.
  SetDIBitsToDevice(pDc->GetSafeHdc(), (int) rc.left, GetDocument()->isDynamicXFA() ? (int) rc.bottom : (int) rc.top, nWidth, nHeight,
                    0, 0, 0, nHeight, (void*) pbtPixels, (BITMAPINFO*) &hdr, DIB_RGB_COLORS);

  // Release the resource
  bmpDC.SelectObject(pOldBmp);
  bmp.DeleteObject();
  bmpDC.DeleteDC();
  DeleteObject(hDIBDC);
  DeleteObject(hDIBitmap);
  pDc->RestoreDC(nSavedDC);//Restore the original DC.
  pbtPixels = NULL;
}

void CPDFReaderView::DrawSelectText(CDC* pDC) {
  if(m_nTextPagePage <= m_nEndPageIndex && m_nTextPagePage >= m_nStartPageIndex)
  for (size_t i = 0; i < m_vSelectRectInfo.size(); i++) {
    DrawTextRect(pDC, m_vSelectRectInfo[i].text_rect,m_nTextPagePage);
  }
}

void CPDFReaderView::DrawFindText(CDC * pDC) {
  for (size_t i = 0; i < m_vSearchRect.size(); i++) {
    DrawTextRect(pDC, m_vSearchRect[i],m_nCurPageIndex);
  }
}

bool CPDFReaderView::GetSelectTextCharIndex(const CPoint & point, int & index) {
  foxit::Matrix pageMatrix = GetPageMatrix(m_nTextPagePage);
  index = -1;
  foxit::Matrix deviceMatrix;
  deviceMatrix.SetReverse(pageMatrix);
  foxit::PointF pt(float(point.x), float(point.y));
  deviceMatrix.TransformPoint(pt.x, pt.y);
  try{

  foxit::pdf::TextPage textPage(GetDocument()->GetPDFDocument().GetPage(m_nTextPagePage));
  index = textPage.GetIndexAtPos(pt.x, pt.y, 25);
  }
  catch (const foxit::Exception& )
  {
    return false;
  }
  return index != -1;
}

// CPDFReaderView printing

void CPDFReaderView::OnZoom(float zoom) {
  if (m_bZoomChange)
    return;
  m_fLastZoom = m_fZoom;
  m_fZoom = zoom;
  m_bZoomChange = TRUE;
  Invalidate();
}

void CPDFReaderView::OnFilePrint() {
  CPDFReaderDoc* pReaderDoc = (CPDFReaderDoc*) GetDocument();
  AdditionalAction additionalAction(pReaderDoc->GetPDFDocument());
  additionalAction.DoJSAction(AdditionalAction::e_TriggerDocWillPrint);

  CString strDoc = m_pDocument->GetTitle();
  CPrintDialog dlg(FALSE, PD_ALLPAGES | PD_COLLATE | PD_PAGENUMS | PD_HIDEPRINTTOFILE | PD_NOSELECTION);
  LPPRINTDLG pPrintDlg = &dlg.m_pd;
  dlg.m_pd.nMinPage = dlg.m_pd.nFromPage = 1;
  dlg.m_pd.nMaxPage = dlg.m_pd.nToPage = pReaderDoc->GetPageCount();
  if (dlg.DoModal() == IDOK) {
    int from_page, to_page;
    if (dlg.PrintAll()) {
      from_page = dlg.m_pd.nMinPage;
      to_page = dlg.m_pd.nMaxPage;
    } else if (dlg.PrintRange()) {
      from_page = dlg.GetFromPage();
      to_page = dlg.GetToPage();
    } else if (dlg.PrintSelection()) {
      from_page = to_page = GetCurVisiblePageIndex() + 1;
    }

    BOOL bDefaults = dlg.GetDefaults();
    BOOL bPrintCollate = dlg.PrintCollate();
    LPDEVMODE pDevMode = dlg.GetDevMode();
    short dmOrientation = pDevMode->dmOrientation; // DMORIENT_LANDSCAPE
    short dmPaperSize = pDevMode->dmPaperSize;
    short dmPaperLength = pDevMode->dmPaperLength;
    short dmPaperWidth = pDevMode->dmPaperWidth;
    int nCopies = dlg.GetCopies() > 0 ? dlg.GetCopies() : 1;
    CString csDriverName = dlg.GetDeviceName();
    CString strDescription;

    strDescription.Format(_T("Your default printer is %s on %s using %s.\n"),
        (LPCTSTR) dlg.GetDeviceName(),
        (LPCTSTR) dlg.GetPortName(),
        (LPCTSTR) dlg.GetDriverName());
    TRACE(strDescription);

    HDC printHDC = dlg.CreatePrinterDC();
    if (NULL == printHDC) return;
    DOCINFO docInfo;
    docInfo.cbSize = sizeof(DOCINFO);
    docInfo.fwType = 0;
    docInfo.lpszDatatype = NULL;
    docInfo.lpszOutput = NULL;
    docInfo.lpszDocName = strDoc;

    if (StartDoc(printHDC, &docInfo) <= 0) return;

    int paper_width = GetDeviceCaps(printHDC, HORZRES);
    int paper_height = GetDeviceCaps(printHDC, VERTRES);

    CString str;
    int start_index = from_page - 1;
    int end_index = from_page - 1 + (to_page - from_page + 1)*nCopies;
    int iStep = to_page - from_page + 1;
    for (int i = start_index; i < end_index; i++) {
      int page_index = bPrintCollate ? start_index + (i - start_index)%iStep : start_index + (i - start_index)/nCopies;
      CReader_Page *pPage = (CReader_Page *) (pReaderDoc->GetPage(page_index));

      Rotation page_rotation = e_Rotation0;
      if (!GetDocument()->isDynamicXFA())
        page_rotation = pPage->GetPDFPage().GetRotation();

      // Calculate the page actual size
      float zoom_scale = GetScale();
      CRect window_rect(0, (int) (pPage->GetPageHeight()*zoom_scale + 0.5f), (int) (pPage->GetPageWidth()*zoom_scale + 0.5f), 0);
      foxit::RectF page_rect(0, 0, 0, 0);
      WindowToDocForPrint(page_index, window_rect, page_rect);
      float page_width = 0, page_height = 0;
      if (page_rotation == 0 || page_rotation == 2) {
        page_height = (page_rect.bottom - page_rect.top);
        page_width = (page_rect.right - page_rect.left);
      } else {
        page_height = (page_rect.bottom - page_rect.top);
        page_width = (page_rect.right - page_rect.left);
      }
      int logpixelsx = GetDeviceCaps(printHDC, LOGPIXELSX);
      int logpixelsy = GetDeviceCaps(printHDC, LOGPIXELSY);
      int page_actual_width = (int) (page_width / 72 * logpixelsx + 0.5f);
      int page_actual_height = (int) (page_height / 72 * logpixelsy + 0.5f);
      if (StartPage(printHDC) <= 0) {
        str.Format(_T("one error occured when start the page %d"), page_index);
        MessageBox(str);
        return;
      }
      // Compare page size with paper size and do some adjustment to page size if necessary to
      // ensure the whole page can be contained in the paper.
      if (paper_width >= page_actual_width && paper_height >= page_actual_height) {
        page_actual_width = page_actual_width;
        page_actual_height = page_actual_height;
      } else if (paper_width < page_actual_width ){
        float temp_factor = (float)paper_width / (float)page_actual_width;
        page_actual_width = page_actual_width;
        page_actual_height = (int)(page_actual_height * temp_factor + 0.5);
      } else if (paper_height < page_actual_height) {
        float temp_factor = (float)paper_height / (float)page_actual_height;
        page_actual_width = (int)(page_actual_width * temp_factor + 0.5);
        page_actual_height = paper_height ;
      }
      // Calculate the position in the paper where the page's left-top corner will be drawn.
      int start_pos_x = (int)((paper_width - page_actual_width) / 2 + 0.5);
      int start_pos_y = (int)((paper_height - page_actual_height) / 2 + 0.5);

    if (GetDocument()->isDynamicXFA())
    {
      RenderPage(CDC::FromHandle(printHDC),page_index,page_actual_width,page_actual_height,start_pos_x,start_pos_y);
    }
    else
    {
      int tile_count = page_actual_height/1024;
      int last_tile_height = page_actual_height - 1024 * (tile_count -1);
      int per_tile_height = page_actual_height/tile_count;
      for(int i=0; i<tile_count; i++)
      {    
        if(i != tile_count-1)
        {
         RenderPageTile(CDC::FromHandle(printHDC), 
          page_index, 
          page_actual_width, 
          page_actual_height, 
          page_actual_width,
          per_tile_height,
          start_pos_x, 
          start_pos_y + i*per_tile_height,
          start_pos_x,
          start_pos_y - i*per_tile_height);
        }
        else
        {
           RenderPageTile(CDC::FromHandle(printHDC), 
          page_index, 
          page_actual_width, 
          page_actual_height, 
          page_actual_width,
          last_tile_height,
          start_pos_x, 
          start_pos_y +  (tile_count-1)*per_tile_height,
          start_pos_x,
          start_pos_y - (tile_count-1)*per_tile_height);
        }
      }
    }
      if (EndPage(printHDC) <= 0) {
        str.Format(_T("one error occured when close the page %d"), page_index);
        MessageBox(str);
        return;
      }

    }//end for
    EndDoc(printHDC);
    if (!DeleteDC(printHDC))// delete printDC
      MessageBox(_T("can not delete the printer"));
  }
  additionalAction.DoJSAction(AdditionalAction::e_TriggerDocPrinted);
}

void CPDFReaderView::OnZoomIn() {
  if (m_bZoomChange)
    return;
  m_fLastZoom = m_fZoom;
  m_fZoom *= 1.2f;
  if (m_fZoom >= kDefaultMaxZoomFactor) {
    m_fZoom = kDefaultMaxZoomFactor;
  }
  if (m_fLastZoom == m_fZoom)
    return;
  m_bZoomChange = TRUE;
  CMainFrame* pFrame = (CMainFrame*) theApp.GetFrameByDoc(GetDocument());
  pFrame->GetZoomSliderButton()->SetValue(m_fZoom, false);
  Invalidate();
}

void CPDFReaderView::OnZoomOut() {
  if (m_bZoomChange)
    return;
  m_fLastZoom = m_fZoom;
  m_fZoom /= 1.2f;
  if (m_fZoom < kDefaultMinZoomFactor) {
    m_fZoom = kDefaultMinZoomFactor;
  }
  if (m_fLastZoom == m_fZoom)
    return;
  m_bZoomChange = TRUE;
  CMainFrame* pFrame = (CMainFrame*) theApp.GetFrameByDoc(GetDocument());
  pFrame->GetZoomSliderButton()->SetValue(m_fZoom, false);
  Invalidate();
}

void CPDFReaderView::OnUpdateZoomIn(CCmdUI * pCmdUI) {
  if (m_fZoom == kDefaultMaxZoomFactor)
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);
}

void CPDFReaderView::OnUpdateZoomOut(CCmdUI * pCmdUI) {
  if (m_fZoom == kDefaultMinZoomFactor)
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);
}

void CPDFReaderView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar) {
  GetScrollInfo(SB_HORZ, &m_Horzsi);
  switch (nSBCode) {
  case SB_LINERIGHT:
  {
    m_Horzsi.nPos = m_Horzsi.nPos + m_Horzsi.nPage;
    SetScrollInfo(SB_HORZ, &m_Horzsi);
    SetVisiblePageByScrollPos();
    Invalidate();
    break;
  }
  case SB_LINELEFT:
  {
    m_Horzsi.nPos = m_Horzsi.nPos - m_Horzsi.nPage;
    SetScrollInfo(SB_HORZ, &m_Horzsi);
    SetVisiblePageByScrollPos();
    Invalidate();
    break;
  }
  case SB_THUMBTRACK: //position of drag scroll box
  case SB_THUMBPOSITION: //position of release mouse
  {
    SCROLLINFO si;
    GetScrollInfo(SB_HORZ, &si, SIF_TRACKPOS);//nPos only has 16bit , nTrackPos is 32bit
    nPos = si.nTrackPos;
    m_Horzsi.nPos = nPos;
    SetScrollInfo(SB_HORZ, &m_Horzsi);
    SetVisiblePageByScrollPos();
    Invalidate();
    break;
  }
  case SB_PAGERIGHT:
  {
    m_Horzsi.nPos = (int) (m_Horzsi.nPos + m_Horzsi.nMax * 0.2);
    SetScrollInfo(SB_HORZ, &m_Horzsi);
    SetVisiblePageByScrollPos();
    Invalidate();
    break;
  }
  case SB_PAGELEFT:
  {
    m_Horzsi.nPos = (int) (m_Horzsi.nPos - m_Horzsi.nMax * 0.2);
    SetScrollInfo(SB_HORZ, &m_Horzsi);
    SetVisiblePageByScrollPos();
    Invalidate();
    break;
  }
  }
}

void CPDFReaderView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar) {
  GetScrollInfo(SB_VERT, &m_Vertsi);
  switch (nSBCode) {
  case SB_LINEDOWN:
  {
    m_Vertsi.nPos = (int) (m_Vertsi.nPos + m_Vertsi.nPage*0.2);
    if (m_Vertsi.nPos + (int) m_Vertsi.nPage > m_Vertsi.nMax) {
      m_Vertsi.nPos = m_Vertsi.nMax - m_Vertsi.nPage;
    }
    SetScrollInfo(SB_VERT, &m_Vertsi);
    SetVisiblePageByScrollPos();
    Invalidate();
    break;
  }
  case SB_LINEUP:
  {
    m_Vertsi.nPos = (int) (m_Vertsi.nPos - m_Vertsi.nPage*0.2);
    SetScrollInfo(SB_VERT, &m_Vertsi);
    SetVisiblePageByScrollPos();
    Invalidate();
    break;
  }
  case SB_THUMBTRACK: // position of drag scroll box
  case SB_THUMBPOSITION: // position of release mouse
  {
    SCROLLINFO si;
    GetScrollInfo(SB_VERT, &si, SIF_TRACKPOS);//nPos only has 16bit , nTrackPos is 32bit
    nPos = si.nTrackPos;
    m_Vertsi.nPos = nPos;
    SetScrollInfo(SB_VERT, &m_Vertsi);
    SetVisiblePageByScrollPos();
    Invalidate();
    break;
  }
  case SB_PAGEDOWN:
  {
    m_Vertsi.nPos = (int) (m_Vertsi.nPos + m_Vertsi.nMax*0.002);
    SetScrollInfo(SB_VERT, &m_Vertsi);
    SetVisiblePageByScrollPos();
    Invalidate();
    break;
  }
  case SB_PAGEUP:
  {
    m_Vertsi.nPos = (int) (m_Vertsi.nPos - m_Vertsi.nMax*0.002);
    SetScrollInfo(SB_VERT, &m_Vertsi);
    SetVisiblePageByScrollPos();

    Invalidate();
    break;
  }
  }
}

BOOL CPDFReaderView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point) {
  if (!HasAviliableDoc())
    return TRUE;
  if (MK_CONTROL == nFlags) {
    if (zDelta < 0) {
      OnZoomOut();
    } else {
      OnZoomIn();
    }
    return TRUE;
  }

  CReader_Page* pReaderPage = (CReader_Page*)GetPage(point,m_fZoom);

  MovePage(zDelta);
  DisplayCaret(m_CaretInfo.nPageIndex, m_CaretInfo.bVisible, m_CaretInfo.rtAnchor);
  Invalidate();

  return TRUE;
}

BOOL CPDFReaderView::OnEraseBkgnd(CDC * pDC) {
  return TRUE;
}

void CPDFReaderView::OnSize(UINT nType, int cx, int cy) {
  CView::OnSize(nType, cx, cy);
  DisplayCaret(m_CaretInfo.nPageIndex, m_CaretInfo.bVisible, m_CaretInfo.rtAnchor);
  if (m_bScrollFlag == FALSE) {
      m_fLastZoom = m_fZoom;
      m_bScrollFlag = TRUE;
      Invalidate();
      return;
  }
}

BOOL CPDFReaderView::IsInPageRect(CPoint point)
{
  CReader_Page* pPage = GetPage(point,m_fZoom);
  if (!pPage) {
    return false;
  }

  PDFPage pdf_page = pPage->GetPDFPage();
  if (pdf_page.IsEmpty()) {
    return false;
  }

  foxit::RectF rectFBox = pdf_page.GetBox(PDFPage::e_MediaBox);
  if (rectFBox.IsEmpty()) {
    float page_width = pdf_page.GetWidth();
    float page_height = pdf_page.GetHeight();
    rectFBox = foxit::RectF(0, 0, page_width, page_height);
  }
  foxit::Matrix matrix = GetPageMatrix(pPage->GetPageIndex());
  matrix.TransformRect(rectFBox);
  if (rectFBox.bottom<rectFBox.top) {
    float temp = rectFBox.bottom;
    rectFBox.bottom = rectFBox.top;
    rectFBox.top = temp;
  }

  if (point.x > rectFBox.left && point.x < rectFBox.right && point.y > rectFBox.top && point.y < rectFBox.bottom) {
    return true;
  }
  return false;
}

void CPDFReaderView::DoAnnotButtonDown(CPoint point) {
  m_CurPt = point;
  CReader_Page* pReaderPage = GetPage(m_CurPt,m_fZoom);
  if (!pReaderPage) return;
  Annot new_focus_annot = pReaderPage->GetAnnotAtPoint(point, GetPageMatrix(pReaderPage->GetPageIndex()));
  /// Can not select e_Watermark
  if (!new_focus_annot.IsEmpty() && new_focus_annot.GetType() == Annot::Type::e_Watermark) return;

  if (m_FocusAnnot != new_focus_annot && m_pAnnotPropertyDlg) {
    m_pAnnotPropertyDlg->ChangeFocusAnnot(new_focus_annot);
    m_pAnnotPropertyDlg->UpdateDialog(this);
  }
  m_FocusAnnot = new_focus_annot;

  m_EndPt = m_StartPt = point;
}

void CPDFReaderView::DoAnnotLButtonUp(CPoint point) {
  m_EndPt = point;

  if (!m_FocusAnnot.IsEmpty() && m_FocusAnnot.GetType() != Annot::e_Underline
      && m_FocusAnnot.GetType() != Annot::e_Highlight
      && m_EndPt != m_StartPt) {
    //foxit::RectF rectAnnot = m_FocusAnnot.GetRect();
    CReader_Page* pReaderPage = GetPage(m_CurPt,m_fZoom);
    if (!pReaderPage) return;
    CRect annotWindowsRect;
    GetAnnotWindowRect(m_FocusAnnot,annotWindowsRect);

    CRect annotWindowsRectOffset = annotWindowsRect;
    int x = m_EndPt.x-m_StartPt.x;
    int y = m_EndPt.y -m_StartPt.y;
    annotWindowsRectOffset.OffsetRect(x, y);
   
    foxit::RectF rcDoc;
    AnnotWindowRectToDocRect(m_FocusAnnot,annotWindowsRectOffset,rcDoc);

    m_FocusAnnot.Move(rcDoc);
    GetDocument()->SetModifiedFlag();
  }
  Invalidate();
}

void CPDFReaderView::GetAnnotWindowRect(Annot annot,CRect& rcWindow)
{
    int pageIndex = annot.GetPage().GetIndex();
    foxit::Matrix page_matrix;
    if(GetPageDisplayMatrix(pageIndex,page_matrix))
    {
        foxit::RectI annot_display_rect = annot.GetDeviceRect(page_matrix);

        rcWindow.SetRect((int) (annot_display_rect.left), (int)(annot_display_rect.bottom ), 
            (int)(annot_display_rect.right), (int)(annot_display_rect.top));
        rcWindow.NormalizeRect();
    }
    else 
        rcWindow.SetRect(0,0,0,0);
}

void CPDFReaderView::AnnotWindowRectToDocRect(Annot annot,const CRect rcWindow, foxit::RectF & rcDoc)
{
    foxit::RectF crView; 
    int pageIndex = annot.GetPage().GetIndex();
    foxit::Matrix page_matrix ;
    if(!GetPageDisplayMatrix(pageIndex,page_matrix))
    {
        rcDoc.Reset();
        return;
    }
    foxit::Matrix annot_matrix = annot.GetDisplayMatrix(page_matrix);
    foxit::Matrix  mt;
    mt.SetReverse(annot_matrix);
    rcDoc = foxit::RectF(float(rcWindow.left), float(rcWindow.top), float(rcWindow.right), float(rcWindow.bottom));
    mt.TransformRect(rcDoc);
    //Note always have NoRotate&NoZoom behavior.
    if(annot.GetFlags() & Annot::e_FlagNoRotate || annot.GetFlags() & Annot::e_FlagNoZoom ||  annot.GetType() == Annot::e_Note)
    { 
        WindowToDoc(pageIndex, rcWindow, crView);
        int nRotation = m_Rotate;
        int nPageRotate = 0;
        nPageRotate = annot.GetPage().GetRotation();
        nRotation = (nRotation + nPageRotate) % 4;

        int nx = rcDoc.Height();
        int ny = rcDoc.Width();
        switch (nRotation)
        {
        case 0:
        {
            rcDoc.top = crView.top;
            rcDoc.left = crView.left;
            rcDoc.bottom = rcDoc.top - nx;
            rcDoc.right = rcDoc.left + ny;
        }
        break;
        case 1:
        {
            rcDoc.top = crView.bottom;
            rcDoc.left = crView.left;
            rcDoc.bottom = rcDoc.top - nx;
            rcDoc.right = rcDoc.left + ny;
        }
        break;
        case 2:
        {
            rcDoc.top = crView.bottom;
            rcDoc.left = crView.right;
            rcDoc.bottom = rcDoc.top - nx;
            rcDoc.right = rcDoc.left + ny;
        }
        break;
        case 3:
        {
            rcDoc.top = crView.top;
            rcDoc.left = crView.right;
            rcDoc.bottom = rcDoc.top - nx;
            rcDoc.right = rcDoc.left + ny;
        }
        break;
        }
    }
}

void char2wchar_t(char *c, wchar_t **wc)
{
  int len = (int)(strlen(c) + 1);
  int converted = 0;
  *wc=(wchar_t*)malloc(len*sizeof(wchar_t));
  memset(*wc, 0, len*sizeof(wchar_t));

  int wclen = MultiByteToWideChar(CP_ACP, 0, c, len, NULL, 0);
  if (wclen > len * (int)sizeof(wchar_t)) {
    wclen = len* sizeof(wchar_t);
  }
  MultiByteToWideChar(CP_ACP, 0, c, len, *wc, wclen);
}

void CPDFReaderView::DoLinkAnnotLButtonDblClk(Link link, CPoint point) {
  Action action = link.GetAction();
  DoAction(action);
}

void CPDFReaderView::DoFreetextAnnotLButtonDblClk(FreeText freetext, CPoint point) {
  if (!m_pEdit) {
    m_pEdit = new CEdit;
    m_pEdit->Create(ES_AUTOVSCROLL|ES_WANTRETURN | ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
      CRect(0, 0, 0, 0), this, IDC_ANNOT_TEXT_EDIT);
  }

  m_pFreeTextAnnotEditFont->Detach();

  DefaultAppearance defaultAppearance = ((FreeText)m_FocusAnnot).GetDefaultAppearance();

  if (!defaultAppearance.font.IsEmpty()) {
    foxit::WString fontName = defaultAppearance.font.GetName();
    if (fontName.GetLength() > 0) {
      m_pFreeTextAnnotEditFont->CreatePointFont(int(defaultAppearance.text_size*10.f), fontName);
      m_pEdit->SetFont(m_pFreeTextAnnotEditFont,TRUE);
    }
  }
  CRect annotWinRect;
  DocToWindow(m_FocusAnnot.GetPage().GetIndex(), FreeText(m_FocusAnnot).GetInnerRect(), annotWinRect);
  annotWinRect.NormalizeRect();
  m_pEdit->MoveWindow(annotWinRect);
  m_pEdit->ShowWindow(SW_SHOW);

  foxit::WString wstrContent = m_FocusAnnot.GetContent();
  if (wstrContent.GetLength() > 0) {
    m_strFreetextContent = wstrContent;
    m_pEdit->SetWindowTextW(wstrContent);
  }
  m_pEdit->SetSel(0, -1);
  m_bAnnotIsEdit = TRUE;
}

void CPDFReaderView::DoAnnotLButtonDblClk(CPoint point) {
  CReader_Page* pReaderPage = GetPage(m_CurPt,m_fZoom);
  if (!pReaderPage) return;
  Annot pdf_annot = pReaderPage->GetAnnotAtPoint(point, GetPageMatrix(pReaderPage->GetPageIndex()));
  if (pdf_annot.IsEmpty()) return;
  CString message;
  Annot::Type annotType = pdf_annot.GetType();
  if (annotType == Annot::e_Link) {
    DoLinkAnnotLButtonDblClk((Link)pdf_annot, point);
  } else if (annotType == Annot::e_FreeText) {
    DoFreetextAnnotLButtonDblClk((FreeText)pdf_annot, point);
  }
}

void CPDFReaderView::DoPageLinkLButtonDown(CPoint point) {
  switch (m_eCurPageLinkType) {
    case CReader_Page::ANNOTLINK: {
      DoAction(m_CurrentAnnotLink.GetAction());
    } break;
    case CReader_Page::TEXTLINK: {
      foxit::WString uri = m_CurrentTextLink.GetURI();
      CString info;
      info.Format(
        _T("The document is trying to connect to:\r\n%s\r\nIf you trust the site,choose YES.If you don't trust ")
        _T("the ")
        _T("site, choose NO"),
        (const wchar_t*)uri);
      if (IDYES == AfxMessageBox(info, MB_YESNO | MB_ICONQUESTION)) {
        ShellExecute(NULL, _T("open"), (const wchar_t*)uri, NULL, NULL, SW_SHOW);
      }
    } break;
  }
}

void CPDFReaderView::DoAnnotDrawBorder(CDC* pDC) {
  if (m_FocusAnnot.IsEmpty()) return;
  DWORD crBorder = RGB(255, 0, 0);
  DWORD crRect = RGB(255, 0, 0);
  CReader_Page* pReaderPage = GetPage(m_CurPt,m_fZoom);
  if (!pReaderPage) return;

  CRect annotWindowsRect; 
  GetAnnotWindowRect(m_FocusAnnot,annotWindowsRect);
  annotWindowsRect.NormalizeRect();

  HPEN hPen = ::CreatePen(PS_SOLID, 1, crBorder);
  HPEN hOldPen = (HPEN)::SelectObject(pDC->GetSafeHdc(), hPen);
  LOGBRUSH lb;
  lb.lbStyle = BS_HOLLOW;
  lb.lbColor = crRect;
  lb.lbHatch = 0;
  HBRUSH hBrush = ::CreateBrushIndirect(&lb);
  HBRUSH hOldBrush = (HBRUSH)::SelectObject(pDC->GetSafeHdc(), hBrush);
  ::Rectangle(pDC->GetSafeHdc(), annotWindowsRect.left, annotWindowsRect.top, annotWindowsRect.right, annotWindowsRect.bottom);
  ::SelectObject(pDC->GetSafeHdc(), hOldBrush);
  ::DeleteObject(hBrush);
  ::SelectObject(pDC->GetSafeHdc(), hOldPen);
  ::DeleteObject(hPen);
}

void CPDFReaderView::OnAnnotTextEditKillFocus() {
  CString str;
  m_pEdit->GetWindowTextW(str);
  if (!m_FocusAnnot.IsEmpty() && str != m_strFreetextContent) {
    wchar_t* wstrContent = str.GetBuffer(str.GetLength());
    str.ReleaseBuffer(str.GetLength());
    m_FocusAnnot.SetContent(wstrContent);
    m_FocusAnnot.ResetAppearanceStream();
    Invalidate();
  } else if (!m_FocusAnnot.IsEmpty()) {
    Invalidate();
  }
  m_pEdit->ShowWindow(SW_HIDE);
  m_bAnnotIsEdit = FALSE;
}

void CPDFReaderView::DoAnnotMouseMove(UINT nFlags, CPoint point) {
  if (!m_bLButtonDown)
    return;
  if (m_DrawingAnnotType == Annot::e_Highlight || m_DrawingAnnotType == Annot::e_Underline) {
    if (m_nStartCharIndex == -1) {
      GetSelectTextCharIndex(point, m_nStartCharIndex);
      return;
    }
    int index;
    if (GetSelectTextCharIndex(point, index)) {
      m_nEndCharIndex = index;
    if (m_nEndCharIndex == m_nStartCharIndex) {
      return;
    }

      PrepareSelectdata();
      Invalidate();
    }
  } else {
    if (IsInPageRect(point)) {
      CReader_Page* pPageStart = GetPage(m_StartPt, m_fZoom);
      CReader_Page* pPageEnd = GetPage(point, m_fZoom);
      if (!pPageStart || !pPageEnd) {
        return;
      }
      if (pPageStart->GetPageIndex() == pPageEnd->GetPageIndex()) {
        m_EndPt = point;
        Invalidate();
      }
    }
  }

}

void CPDFReaderView::DoSelectMouseMove(UINT nFlags, CPoint point) {
  if (!m_bLButtonDown)
    return;
  if (m_nStartCharIndex == -1) {
    GetSelectTextCharIndex(point, m_nStartCharIndex);
    return;
  }
  int index;
  if (GetSelectTextCharIndex(point, index)) {
    m_nEndCharIndex = index;
    PrepareSelectdata();
    Invalidate();
  }
}

void CPDFReaderView::ShowAnnotSelectContextMenu(const CPoint & point) {
  if (m_FocusAnnot.IsEmpty())
    return;
  if (IsAnnotRelatedToField(m_FocusAnnot))
    return;
  CMenu popup_menu;
  popup_menu.CreatePopupMenu();
  bool bIsCanChange = IsAnnotSupportedToChangeProperty(m_FocusAnnot);
  if (bIsCanChange)
    popup_menu.AppendMenu(MF_STRING, ANNOT_ITEM_PROPERTIES, _T("Properties"));
  Annot::Type nType = m_FocusAnnot.GetType();
  foxit::uint32 annot_flags = m_FocusAnnot.GetFlags();
  BOOL is_locked = annot_flags & Annot::e_FlagLocked ? TRUE : FALSE;
  if (!is_locked && bIsCanChange)
    popup_menu.AppendMenu(MF_STRING, ANNOT_ITEM_DELETE, _T("Delete"));

  if (popup_menu.GetMenuItemCount() == 0)
    return;

  CPoint temp_point = point;
  CRect annot_windwos_rect;
  //DocToWindow(m_FocusAnnot.GetPage().GetIndex(), m_FocusAnnot.GetRect(), annot_windwos_rect);
  CReader_Page* pReaderPage = GetPage(m_CurPt,m_fZoom);
  if (!pReaderPage) return;
  GetAnnotWindowRect(m_FocusAnnot,annot_windwos_rect);
  annot_windwos_rect.NormalizeRect();

  annot_windwos_rect.InflateRect(3, 3);
  ClientToScreen(&temp_point);
  int ret = popup_menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, temp_point.x, temp_point.y, this);
  switch (ret) {
    case ANNOT_ITEM_PROPERTIES:
      if (!m_pAnnotPropertyDlg) {
        m_pAnnotPropertyDlg = new CAnnotPropertyDlg(m_FocusAnnot);
        m_pAnnotPropertyDlg->Create(IDD_ANNOT_PROPERTY_DIALOG, this);
      } else {
        m_pAnnotPropertyDlg->ChangeFocusAnnot(m_FocusAnnot);
      }
      m_pAnnotPropertyDlg->UpdateDialog(this);
      m_pAnnotPropertyDlg->ShowWindow(TRUE);
      break;
    case ANNOT_ITEM_DELETE:
      if (IDOK == this->MessageBox(_T("Do you want to delete this annotation?"), _T("Question"), MB_OKCANCEL)) {
        m_FocusAnnot.GetPage().RemoveAnnot(m_FocusAnnot);
    GetDocument()->SetModifiedFlag();
        m_FocusAnnot = Annot();
        InvalidateRect(annot_windwos_rect);
      }
      break;
    default:
      break;
  }
  popup_menu.DestroyMenu();
}

void CPDFReaderView::ShowTextPageContextMeun(const CPoint & point) {
  CReader_Page* pPage = GetPage(point,m_fZoom);
  if (!pPage || pPage->GetPageIndex() != m_nTextPagePage)
    return;
  foxit::PointF pt;
  WindowToDoc(m_nTextPagePage, point, pt);
  bool bNeedShowContextMenu = false;
  for (size_t i = 0; i < m_vSelectRectInfo.size(); i++) {
    foxit::RectF rect = m_vSelectRectInfo[i].text_rect;
    if (pt.x >= rect.left && pt.x <= rect.right && pt.y >= rect.bottom && pt.y <= rect.top) {
      bNeedShowContextMenu = true;
      break;
    }
  }
  if (!bNeedShowContextMenu) return;
  CMenu menu;
  menu.CreatePopupMenu();
  menu.AppendMenu(MF_STRING, TEXT_ITEM_COPY, _T("Copy to Clipboard"));
  CPoint screenPt = point;
  ClientToScreen(&screenPt);
  switch (menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, screenPt.x, screenPt.y, this)) {
    case TEXT_ITEM_COPY:
     return SetClipboardData(m_wsSelectText);
  }
}

void CPDFReaderView::DoAction(Action action) {
  CString message;
  if (action.IsEmpty()) return;
  Action::Type actionType = action.GetType();
  switch (actionType) {
    case Action::e_TypeGoto:
      return GotoDestination(((GotoAction)action).GetDestination());
    case Action::e_TypeGoTo3DView:
      message = _T("Action Type: GoTo3DView.");
      break;
    case Action::e_TypeGoToE:
      message = _T("Action Type: GoToE.");
      break;
    case Action::e_TypeGoToR:
      message = _T("Action Type: GoToR.");
      break;
    case Action::e_TypeHide:
      message = _T("Action Type: Hide.");
      break;
    case Action::e_TypeImportData:
      message = _T("Action Type: Import Data.");
      break;
    case Action::e_TypeJavaScript:
      message = _T("Action Type: Java script.");
      break;
    case Action::e_TypeLaunch: {
      message = _T("Action Type: Lanuch.\r\n");
      LaunchAction launchAction = (LaunchAction)action;
      foxit::WString fileName = launchAction.GetFileSpec().GetFileName();
      message += (const wchar_t*)fileName;
    } break;
    case Action::e_TypeMovie:
      message = _T("Action Type: Movie.");
      break;
    case Action::e_TypeNamed: {
      message = _T("Action Type: Named.\r\n");
      NamedAction pNamedAction = (NamedAction)action;
      foxit::String strName = pNamedAction.GetName();
      message += (const wchar_t*)foxit::WString::FromLocal(strName);
    } break;
    case Action::e_TypeRendition:
      message = _T("Action Type: Rendition.");
      break;
    case Action::e_TypeResetForm:
      message = _T("Action Type: Reset Form.");
      break;
    case Action::e_TypeSetOCGState:
      message = _T("Action Type: Set OCG State.");
      break;
    case Action::e_TypeSound:
      message = _T("Action Type: Sound.");
      break;
    case Action::e_TypeSubmitForm: {
      message = _T("Action Type: Submit form.\r\n");
      SubmitFormAction submitform_action = (SubmitFormAction)action;
      foxit::String strURL = submitform_action.GetURL();
      message += (const wchar_t*)foxit::WString::FromLocal(strURL);
    } break;
    case Action::e_TypeThread:
      message = _T("Action Type: Thread.");
      break;
    case Action::e_TypeTrans:
      message = _T("Action Type: Trans.");
      break;
    case Action::e_TypeUnknown:
      message = _T("Action Type: Unknown.");
      break;
    case Action::e_TypeURI: {
      foxit::String uri = ((URIAction)action).GetURI();
      foxit::WString wsUri = foxit::WString::FromLocal(uri);
      CString info;
      info.Format(
          _T("The document is trying to connect to:\r\n%s\r\nIf you trust the site,choose YES.If you don't trust ")
          _T("the ")
          _T("site, choose NO"),
          (const wchar_t*)wsUri);
      if (IDYES == AfxMessageBox(info, MB_YESNO | MB_ICONQUESTION)) {
        ShellExecute(NULL, _T("open"), (const wchar_t*)wsUri, NULL, NULL, SW_SHOW);
      }
      return;
    } break;
    default:
      break;
  }
  AfxMessageBox(message);
}

void CPDFReaderView::SetClipboardData(foxit::WString ws_text) {
  ::OpenClipboard(NULL);
  ::EmptyClipboard();
  foxit::uint32 bufLen = 0;

  if (IsSupportUnicodeSel()) {
    bufLen = ws_text.GetLength();
    HGLOBAL hMem;
    hMem = ::GlobalAlloc(0, bufLen * 2 + 32);

    wchar_t* pMem = (wchar_t*)::GlobalLock(hMem);
    memset(pMem, 0, bufLen * 2 + 32);

    if (pMem == NULL) {
      AfxMessageBox(_T("Can not open Clipboard"));
      return;
    }

    wcscpy(pMem, (LPCWSTR)ws_text);

    ::GlobalUnlock(hMem);
    DWORD LastError = GetLastError();

    HANDLE hh = ::SetClipboardData(CF_UNICODETEXT, hMem);
  } else {
    foxit::String utf8_text = ws_text.UTF8Encode();
    HGLOBAL hMem;
    hMem = ::GlobalAlloc(0, utf8_text.GetLength() + 32);

    char* pMem = (char*)::GlobalLock(hMem);
    memset(pMem, 0, utf8_text.GetLength() + 32);

    if (pMem == NULL) {
      AfxMessageBox(_T("Can not open Clipboard"));
      return;
    }

    strcpy(pMem, (const char*)utf8_text);

    ::GlobalUnlock(hMem);
    DWORD ret = GetLastError();
    HANDLE hh = ::SetClipboardData(CF_TEXT, hMem);
  }

  CloseClipboard();
}

BOOL CPDFReaderView::IsSupportUnicodeSel() {
  if (m_eUnicodeSupportType == NOT_CHECK_SUPPORT) {
    DWORD dwVersion = ::GetVersion();
    DWORD dwWindowsMajorVersion = (DWORD) (LOBYTE(LOWORD(dwVersion)));
    DWORD dwWindowsMinorVersion = (DWORD) (HIBYTE(LOWORD(dwVersion)));

    if (dwVersion >= 0x80000000)
      m_eUnicodeSupportType = NOT_SUPPORT_UNICODE;
    else
      m_eUnicodeSupportType = SUPPORT_UNICODE;
  }

  return (m_eUnicodeSupportType == SUPPORT_UNICODE) ? TRUE : FALSE;
}

void CPDFReaderView::PrepareSelectdata() {
  m_wsSelectText.Empty();
  m_vSelectRectInfo.clear();
  if (m_nEndPageIndex < m_nTextPagePage || m_nTextPagePage < m_nStartPageIndex)
    return;
  foxit::pdf::TextPage textPage(GetDocument()->GetPDFDocument().GetPage(m_nTextPagePage));
  int startIndex = min(m_nStartCharIndex,m_nEndCharIndex);
  int endIndex = max(m_nStartCharIndex, m_nEndCharIndex);
  int count = textPage.GetTextRectCount(startIndex, endIndex-startIndex+1);
  m_wsSelectText = textPage.GetChars(startIndex, endIndex-startIndex+1);

  TRACE("PrepareSelectdata: %d, %d, %d\n", startIndex, endIndex, count);
  for (int i = 0; i < count; i++) {
    TextRectInfo text_rectinfo;
    text_rectinfo.text_rect = textPage.GetTextRect(i);
    text_rectinfo.baseline_rotation = textPage.GetBaselineRotation(i);
    m_vSelectRectInfo.push_back(text_rectinfo);
  }

}

static foxit::uint32 FWL_WinKeyFlag2FWL(UINT dwWinFlag)
{
  foxit::uint32 dwFWLFlag = 0;
  if (dwWinFlag & MK_CONTROL) {
    dwFWLFlag |= Filler::e_EventFlagControlKey;
  }
  if (dwWinFlag & MK_LBUTTON) {
    dwFWLFlag |= Filler::e_EventFlagLeftButtonDown;
  }

  if (dwWinFlag & MK_MBUTTON) {
    dwFWLFlag |= Filler::e_EventFlagMiddleButtonDown;
  }

  if (dwWinFlag & MK_RBUTTON) {
    dwFWLFlag |= Filler::e_EventFlagRightButtonDown;
  }

  if (dwWinFlag & MK_SHIFT) {
    dwFWLFlag |= Filler::e_EventFlagShiftKey;
  }

  return dwFWLFlag;
}

void CPDFReaderView::OnLButtonDown(UINT nFlags, CPoint point) {
  m_bLButtonDown = TRUE;

  CReader_Page* pPage = GetPage(point,m_fZoom);
  if(m_bAnnotIsEdit) {
    CRect rc;
    m_pEdit->GetWindowRect(&rc);
    ScreenToClient(&rc);
    if (!rc.PtInRect(point)) {
      OnAnnotTextEditKillFocus();
      m_pEdit->ShowWindow(SW_HIDE);
      m_bAnnotIsEdit = FALSE;
    }
  }

  OperatorType operatorType = GetOperatorType();
  switch (operatorType) {
    case DRAWINGANNOT:
      if (IsInPageRect(point)) {
        if (m_DrawingAnnotType == Annot::e_Underline || m_DrawingAnnotType == Annot::e_Highlight) {
          if (pPage) {
            m_nTextPagePage = GetPage(point, m_fZoom)->GetPageIndex();
          } else {
            m_nTextPagePage = 0;
          }
          GetSelectTextCharIndex(point, m_nStartCharIndex);
          m_nEndCharIndex = -1;
          Invalidate();
        }
        m_StartPt = point;
      }
      break;
    case ANNOTSELECT:
      DoAnnotButtonDown(point);
      break;
    case HAND: {
      m_StartPt = point;
    }
      break;
    case TextPage: {
      GetSelectTextCharIndex(point, m_nStartCharIndex);
      if (pPage) {
        m_nTextPagePage = GetPage(point,m_fZoom)->GetPageIndex();
      } else {
        m_nTextPagePage = 0;
      }
      m_nEndCharIndex = -1;
      Invalidate();
      break;
    }
    case AUTOSCROLL: {
      SetOperatorType(UNKNOWN);
      Invalidate();
    }
  }

  if (pPage) {
    if (GetDocument()->isDynamicXFA()) {
      WindowToDoc(pPage->GetPageIndex(), point, m_ptPop);
      if (m_FocusXFAWidget.IsEmpty() == false) {
         if (XFAWidget::e_HitTestAreaClient !=  m_FocusXFAWidget.OnHitTest(m_ptPop))
             m_FocusXFAWidget = pPage->GetXFAPage().GetWidgetAtDevicePoint(GetPageMatrix(pPage->GetPageIndex()), foxit::PointF(float(point.x), float(point.y)), 10);
      } else
          m_FocusXFAWidget = pPage->GetXFAPage().GetWidgetAtDevicePoint(GetPageMatrix(pPage->GetPageIndex()), foxit::PointF(float(point.x), float(point.y)), 10);

      if (!m_FocusXFAWidget.IsEmpty())
        m_FocusXFAWidget.OnLButtonDown(m_ptPop, FWL_WinKeyFlag2FWL(nFlags));
      else {
        GetDocument()->GetXFADoc().KillFocus();
        Invalidate();
      }
    } else {
      foxit::PointF pointf;
      WindowToDoc(pPage->GetPageIndex(), point, pointf);
      Filler formfiller = GetDocument()->GetFormFiller();
      if (formfiller.IsEmpty()) return;
      m_FocusAnnot = pPage->GetPDFPage().GetAnnotAtPoint(pointf, 20);

      formfiller.OnLButtonDown(pPage->GetPDFPage(), pointf, FWL_WinKeyFlag2FWL(nFlags));
    }

    if ((m_OperatorType == HAND || m_OperatorType == AUTOSCROLL || m_OperatorType == UNKNOWN) &&
        (!m_CurrentTextLink.IsEmpty() || !m_CurrentAnnotLink.IsEmpty())) {
      DoPageLinkLButtonDown(point);
    }
  }
  CView::OnLButtonDown(nFlags, point);
}

void CPDFReaderView::OnLButtonUp(UINT nFlags, CPoint point) {
  m_bLButtonDown = FALSE;

  OperatorType operatorType = GetOperatorType();
  switch (operatorType) {
    case DRAWINGANNOT: {
      CReader_Page* pStartReaderPage = GetPage(m_StartPt, m_fZoom);
      if (!pStartReaderPage) {
        return;
      }
      if (m_DrawingAnnotType == Annot::e_Highlight || m_DrawingAnnotType == Annot::e_Underline) {
        /*if (!m_vSelectRectInfo.size())
          return;*/
    if (!IsInPageRect(point) || m_nStartCharIndex == -1 || !m_vSelectRectInfo.size()) {
      return;
        }

        pStartReaderPage->AddAnnot(m_DrawingAnnotType, m_vSelectRectInfo);
    GetDocument()->SetModifiedFlag();
    m_nStartCharIndex = m_nEndCharIndex = -1;
      } else {
        if (m_StartPt == point) {
          return;
        }
        CRect rect(m_StartPt, point);
        rect.NormalizeRect();
        if (rect.Width() < 1.0f || rect.Height() < 1.0f)
          return;

        foxit::RectF annotRectF(0,0,0,0) ;
        WindowToDoc(pStartReaderPage->GetPageIndex(), rect, annotRectF);
        
        if(m_DrawingAnnotType == Annot::e_Note)
        {  
            //note need adjust real doc rectangle
            foxit::RectF annotTempRectF(0,0,0,0) ;
            CPoint pt(rect.left,rect.top);
            foxit::PointF  ptDoc;
            WindowToDoc(pStartReaderPage->GetPageIndex(), pt, ptDoc);

            float icon_length = annotRectF.Height() > annotRectF.Width() ? annotRectF.Width() : annotRectF.Height();
            annotTempRectF.left = ptDoc.x ;
            annotTempRectF.bottom = ptDoc.y - icon_length ;
            annotTempRectF.right = annotTempRectF.left + icon_length ;
            annotTempRectF.top = annotTempRectF.bottom + icon_length ;
            annotRectF = annotTempRectF;
        }
        pStartReaderPage->AddAnnot(m_DrawingAnnotType, annotRectF);
        GetDocument()->SetModifiedFlag();
      }
      m_StartPt.SetPoint(0, 0);
      m_EndPt.SetPoint(0, 0);
      m_vSelectRectInfo.clear();
      Invalidate();
      return;
    }
    break;
    case ANNOTSELECT: {
      DoAnnotLButtonUp(point);
    }  break;
  }

  if (!m_bAnnotIsEdit) {
    ReleaseCapture();
  }

  CReader_Page* pPage = GetPage(point,m_fZoom);
  if (pPage) {
    foxit::PointF pointf;
    WindowToDoc(pPage->GetPageIndex(), point, pointf);
    if (GetDocument()->isDynamicXFA()) {
      if (m_FocusXFAWidget.IsEmpty() == false) {
        if (XFAWidget::e_HitTestAreaClient != m_FocusXFAWidget.OnHitTest(pointf))
          m_FocusXFAWidget = pPage->GetXFAPage().GetWidgetAtDevicePoint(GetPageMatrix(pPage->GetPageIndex()), foxit::PointF(float(point.x), float(point.y)), 10);
      } else 
          m_FocusXFAWidget = pPage->GetXFAPage().GetWidgetAtDevicePoint(GetPageMatrix(pPage->GetPageIndex()), foxit::PointF(float(point.x), float(point.y)), 10);

      if (!m_FocusXFAWidget.IsEmpty()) {
        m_FocusXFAWidget.OnLButtonUp(pointf, FWL_WinKeyFlag2FWL(nFlags));
      } else {
        GetDocument()->GetXFADoc().KillFocus();
      }
    } else {
        foxit::PointF pointf;
        WindowToDoc(pPage->GetPageIndex(), point, pointf);
        Filler form_filler = GetDocument()->GetFormFiller();
        if (form_filler.IsEmpty()) return;
        m_FocusAnnot = pPage->GetPDFPage().GetAnnotAtPoint(pointf, 20);
        if(form_filler.IsEmpty()) return;
        form_filler.OnLButtonUp(GetDocument()->GetPDFDocument().GetPage(pPage->GetPageIndex()), pointf, FWL_WinKeyFlag2FWL(nFlags));
    }
  }

  CView::OnLButtonUp(nFlags, point);
}

void CPDFReaderView::OnMouseMove(UINT nFlags, CPoint point) {
  OperatorType operatorType = GetOperatorType();
  switch (operatorType) {
    case DRAWINGANNOT:
      return DoAnnotMouseMove(nFlags, point);
    case TextPage:
      return DoSelectMouseMove(nFlags, point);
    case HAND: {
      if (m_bLButtonDown) {
        MovePage(m_StartPt, point);
        m_StartPt = point;
        Invalidate();
        break;
      }
    }
    case AUTOSCROLL: {
      if (!m_bFixedAutoScroll)
        m_EndPt = point;
    } break;
  }

  CReader_Page* pPage = GetPage(point,m_fZoom);
  if (pPage) {
    foxit::PointF pointf;
    WindowToDoc(pPage->GetPageIndex(), point, pointf);

    if (GetDocument()->isDynamicXFA()) {
      XFAWidget xfa_widget = pPage->GetXFAPage().GetWidgetAtDevicePoint(GetPageMatrix(pPage->GetPageIndex()), foxit::PointF(float(point.x), float(point.y)), 10);

      if (m_FocusXFAWidget.IsEmpty() == false) {
          if (XFAWidget::e_HitTestAreaClient != m_FocusXFAWidget.OnHitTest(pointf))
              xfa_widget = pPage->GetXFAPage().GetWidgetAtDevicePoint(GetPageMatrix(pPage->GetPageIndex()), foxit::PointF(float(point.x), float(point.y)), 10);
          else
              xfa_widget = m_FocusXFAWidget;
      } else
          xfa_widget = pPage->GetXFAPage().GetWidgetAtDevicePoint(GetPageMatrix(pPage->GetPageIndex()), foxit::PointF(float(point.x), float(point.y)), 10);

      if (!xfa_widget.IsEmpty()) {
        xfa_widget.OnMouseMove(pointf, FWL_WinKeyFlag2FWL(nFlags));
      }
      if (!xfa_widget.IsEmpty()&&xfa_widget != m_HoverXFAWidget && !m_HoverXFAWidget.IsEmpty()) {
        m_HoverXFAWidget.OnMouseExit();
        XFAWidget old_hover_xfawidget = m_HoverXFAWidget;
        m_HoverXFAWidget = xfa_widget;
        if (xfa_widget != old_hover_xfawidget && !xfa_widget.IsEmpty()) {
          xfa_widget.OnMouseEnter();
        }
      }
    } else {
      Filler form_filler = GetDocument()->GetFormFiller();
      if (form_filler.IsEmpty()) return;

      form_filler.OnMouseMove(GetDocument()->GetPDFDocument().GetPage(pPage->GetPageIndex()), pointf, FWL_WinKeyFlag2FWL(nFlags));
    }

    if (m_OperatorType == HAND || m_OperatorType == AUTOSCROLL || m_OperatorType == UNKNOWN) {
      m_CurrentTextLink = pPage->GetTextLinkAtPos(pointf);
      if (!m_CurrentTextLink.IsEmpty()) {
        m_eCurPageLinkType = CReader_Page::TEXTLINK;
        m_CurrentAnnotLink = Link();
      } else {
        m_CurrentAnnotLink = pPage->GetAnnotLinkAtPos(pointf);
        if (!m_CurrentAnnotLink.IsEmpty()) {
          m_eCurPageLinkType = CReader_Page::ANNOTLINK;
          m_CurrentTextLink = TextLink();
        } else {
          m_eCurPageLinkType = CReader_Page::NOLINK;
          m_CurrentAnnotLink = Link();
          m_CurrentTextLink = TextLink();
        }
      }
    }
  }

  CView::OnMouseMove(nFlags, point);
}

void CPDFReaderView::OnLButtonDblClk(UINT nFlags, CPoint point) {
  m_CurPt = point;
  OperatorType operatorType = GetOperatorType();
  if (operatorType == ANNOTSELECT) {
    DoAnnotLButtonDblClk(point);
  }

  CReader_Page* pPage = GetPage(point,m_fZoom);
  if (pPage) {
    foxit::PointF pointf;
    WindowToDoc(pPage->GetPageIndex(), point, pointf);
    if (GetDocument()->isDynamicXFA()) {
      m_FocusXFAWidget = pPage->GetXFAPage().GetWidgetAtDevicePoint(GetPageMatrix(pPage->GetPageIndex()), foxit::PointF(float(point.x), float(point.y)), 10);
      if (!m_FocusXFAWidget.IsEmpty())
        m_FocusXFAWidget.OnLButtonDoubleClick(pointf, FWL_WinKeyFlag2FWL(nFlags));
    } else {
      Filler form_filler = GetDocument()->GetFormFiller();
      if(form_filler.IsEmpty()) return;

      form_filler.OnLButtonDoubleClick(pPage->GetPDFPage(), pointf, FWL_WinKeyFlag2FWL(nFlags));
    }
  }
  CView::OnLButtonDblClk(nFlags, point);
}

void CPDFReaderView::OnRButtonDown(UINT nFlags, CPoint point) {
  OperatorType operatorType = GetOperatorType();
  switch (operatorType) {
  case ANNOTSELECT:
    DoAnnotButtonDown(point);
    break;
  case AUTOSCROLL:
    SetOperatorType(UNKNOWN);
    Invalidate();
    break;
  }

  CReader_Page* pPage = GetPage(point,m_fZoom);
  if (pPage) {
    foxit::PointF pointf;
    WindowToDoc(pPage->GetPageIndex(), point, pointf);
    if (GetDocument()->isDynamicXFA()) {
      m_FocusXFAWidget = pPage->GetXFAPage().GetWidgetAtDevicePoint(GetPageMatrix(pPage->GetPageIndex()), foxit::PointF(float(point.x), float(point.y)), 10);
      if (!m_FocusXFAWidget.IsEmpty())
        m_FocusXFAWidget.OnRButtonDown(pointf, FWL_WinKeyFlag2FWL(nFlags));
    }
  }
  CView::OnRButtonDown(nFlags, point);
}

void CPDFReaderView::OnRButtonUp(UINT nFlags, CPoint point) {
  switch (GetOperatorType()) {
    case ANNOTSELECT:
      return ShowAnnotSelectContextMenu(point);
    case TextPage:
      return ShowTextPageContextMeun(point);
  };

  CReader_Page* pPage = GetPage(point,m_fZoom);
  if (pPage) {
    foxit::PointF pointf;
    WindowToDoc(pPage->GetPageIndex(), point, pointf);
    if (GetDocument()->isDynamicXFA()) {
      m_FocusXFAWidget = pPage->GetXFAPage().GetWidgetAtDevicePoint(GetPageMatrix(pPage->GetPageIndex()), foxit::PointF(float(point.x), float(point.y)), 10);

      if (!m_FocusXFAWidget.IsEmpty())
        m_FocusXFAWidget.OnRButtonUp(pointf, FWL_WinKeyFlag2FWL(nFlags));
    }
  }
}

void CPDFReaderView::OnUpdateFileSaveAs(CCmdUI * pCmdUI) {
  if (!HasAviliableDoc())
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);
}

void CPDFReaderView::OnUpdateFileSave(CCmdUI * pCmdUI) {
  if (HasAviliableDoc() && GetDocument()->IsModified())
    pCmdUI->Enable(TRUE);
  else
    pCmdUI->Enable(FALSE);
}

void CPDFReaderView::OnUpdateFilePrint(CCmdUI* pCmdUI) {
  if (HasAviliableDoc())
    pCmdUI->Enable(TRUE);
  else
    pCmdUI->Enable(FALSE);
}

void CPDFReaderView::OnFileSaveAs() {
  GetDocument()->SaveAs();
}

void CPDFReaderView::OnFileSave() {
  GetDocument()->Save();
  GetDocument()->SetModifiedFlag(FALSE);
}

void CPDFReaderView::OnFirstPage() {
  SetVisiblePageByIndex(0);
  Invalidate();
}

void CPDFReaderView::OnPrevPage() {
  SetVisiblePageByIndex(m_nCurPageIndex - 1);
  Invalidate();
}

void CPDFReaderView::OnGotoPage() {
  if (!HasAviliableDoc())
    return;
  CMainFrame* pFrame = (CMainFrame*) theApp.GetFrameByDoc(GetDocument());
  CPageComboBox* pBox = pFrame->GetPageGotoButton()->GetComboBox();
  switch (pBox->GetChangeType()) {
    case CPageComboBox::EDIT_CHANGE: {
      CString pageIndex;
      pBox->GetWindowText(pageIndex);
      int nIndex = _ttoi(pageIndex);
      if (nIndex < 1)
        nIndex = 1;
      if (nIndex > GetDocument()->GetPageCount())
        nIndex = GetDocument()->GetPageCount();
      SetVisiblePageByIndex(nIndex - 1);
      Invalidate();
    } break;
    case CPageComboBox::SEL_CHANGE: {
      SetVisiblePageByIndex(pBox->GetCurSel());
      Invalidate();
    } break;
  }
  pBox->ResetChangeType();
}

void CPDFReaderView::OnNextPage() {
  SetVisiblePageByIndex(m_nCurPageIndex + 1);
  Invalidate();
}

void CPDFReaderView::OnLastPage() {
  SetVisiblePageByIndex(GetDocument()->GetPageCount());
  Invalidate();
}

void CPDFReaderView::OnUpdateFirstPage(CCmdUI * pCmdUI) {
  if (m_nCurPageIndex == 0)
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);
}

void CPDFReaderView::OnUpdatePrevPage(CCmdUI * pCmdUI) {
  if (m_nCurPageIndex == 0)
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);
}

void CPDFReaderView::OnUpdateNextPage(CCmdUI * pCmdUI) {
  if (m_nCurPageIndex == GetDocument()->GetPageCount() - 1)
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);
}

void CPDFReaderView::OnUpdateLastPage(CCmdUI * pCmdUI) {
  if (m_nCurPageIndex == GetDocument()->GetPageCount() - 1)
    pCmdUI->Enable(FALSE);
  else
    pCmdUI->Enable(TRUE);
}

void CPDFReaderView::OnUpdatePDFSearch(CCmdUI * pCmdUI) {
  if (!HasAviliableDoc()) {
    pCmdUI->Enable(FALSE);
  } else {
    pCmdUI->Enable(TRUE);
    if (m_OperatorType == TEXTSEARCH)
      pCmdUI->SetCheck(TRUE);
    else
      pCmdUI->SetCheck(FALSE);
  }
}

void CPDFReaderView::OnUpdatePDFSelect(CCmdUI * pCmdUI) {
  if (!HasAviliableDoc()) {
    pCmdUI->Enable(FALSE);
  } else {
    pCmdUI->Enable(TRUE);
    if (m_OperatorType == TextPage)
      pCmdUI->SetCheck(TRUE);
    else
      pCmdUI->SetCheck(FALSE);
  }
}

void CPDFReaderView::OnUpdatePDFHand(CCmdUI * pCmdUI) {
  if (!HasAviliableDoc()) {
    pCmdUI->Enable(FALSE);
  } else {
    pCmdUI->Enable(TRUE);
    if (m_OperatorType == HAND)
      pCmdUI->SetCheck(TRUE);
    else
      pCmdUI->SetCheck(FALSE);
  }
}

void CPDFReaderView::OnPDFSelect() {
  if (m_OperatorType != TextPage) {
    SetOperatorType(TextPage);
  } else {
    SetOperatorType(UNKNOWN);
  }
}

void CPDFReaderView::OnPDFSearch() {
  SetOperatorType(TEXTSEARCH);
  FindDlg dlg(this);
  dlg.DoModal();
  SetOperatorType(UNKNOWN);
}

void CPDFReaderView::OnPDFHand() {
  if (m_OperatorType != HAND) {
    SetOperatorType(HAND);
  } else {
    SetOperatorType(UNKNOWN);
  }
}

void CPDFReaderView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
  AFXPrintPreview(this);
#endif
}

BOOL CPDFReaderView::OnPreparePrinting(CPrintInfo* pInfo)
{
  CPDFReaderDoc* pReaderDoc = (CPDFReaderDoc*) GetDocument();
  AdditionalAction additionalAction(pReaderDoc->GetPDFDocument());
  additionalAction.DoJSAction(AdditionalAction::e_TriggerDocWillPrint);

  //pInfo->m_pPD->m_pd.Flags = PD_ALLPAGES | PD_COLLATE | PD_PAGENUMS | PD_USEDEVMODECOPIES | PD_HIDEPRINTTOFILE | PD_NOSELECTION;
  DWORD dwFlags = PD_COLLATE | PD_HIDEPRINTTOFILE;
  if (pInfo->m_pPD->m_pd.Flags & PD_USEDEVMODECOPIES)
  {
    TRACE(L"PD_USEDEVMODECOPIES\n");
  }

  if (pInfo->m_pPD->m_pd.Flags & PD_USEDEVMODECOPIESANDCOLLATE)
  {
    pInfo->m_pPD->m_pd.Flags &= ~PD_USEDEVMODECOPIESANDCOLLATE;
    TRACE(L"PD_USEDEVMODECOPIESANDCOLLATE\n");
  }
  if (pInfo->m_pPD->m_pd.Flags & PD_COLLATE)
  {
    TRACE(L"PD_COLLATE\n");
  }

  pInfo->m_pPD->m_pd.Flags |= dwFlags;
  pInfo->m_pPD->m_pd.nMinPage = pInfo->m_pPD->m_pd.nFromPage = 1;
  pInfo->m_pPD->m_pd.nMaxPage = pInfo->m_pPD->m_pd.nToPage = pReaderDoc->GetPageCount();

  LPDEVMODE lpDevMode;
  PRINTDLG pd = pInfo->m_pPD->m_pd;
  if(AfxGetApp()->GetPrinterDeviceDefaults(&pd)) {
    lpDevMode =(LPDEVMODE)GlobalLock(pd.hDevMode);
    if(lpDevMode) {
      lpDevMode->dmPaperSize = DMPAPER_A4;
      lpDevMode->dmOrientation = DMORIENT_LANDSCAPE;
    }
    GlobalUnlock(pd.hDevMode);
  }

  //DoPreparePrinting( pInfo );

  // default preparation
  return DoPreparePrinting(pInfo);
}

void CPDFReaderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
  // TODO: add extra initialization before printing
}

void CPDFReaderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
  // TODO: add cleanup after printing
}

void CPDFReaderView::OnRButtonDblClk(UINT nFlags, CPoint point) {
}

void CPDFReaderView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {

  if (GetDocument()->isDynamicXFA()) {
    if (!m_FocusXFAWidget.IsEmpty()) {
      m_FocusXFAWidget.OnChar(nChar, nFlags);
    }
  } else {
    Filler form_filler = GetDocument()->GetFormFiller();
    if(form_filler.IsEmpty()) return;
      form_filler.OnChar(nChar, nFlags);
      //Widget widget_annot = (Widget)m_FocusAnnot;
      //if (widget_annot.IsEmpty() || widget_annot.GetType() != Annot::e_Widget)
      //  return;
      //Field pFormField = widget_annot.GetField();
      //if (pFormField.IsEmpty()) return;
      //AdditionalAction additionalAction(pFormField);
      //additionalAction.DoJSAction(AdditionalAction::e_TriggerFieldValueChanged);
  }
  CView::OnChar(nChar, nRepCnt, nFlags);
}

static DWORD FWL_VirtKey2FWL()
{
  DWORD dwFWLFlag = 0;
  if (GetKeyState(VK_CONTROL) < 0) {
    dwFWLFlag |= (1 << 0);
  }
  if (GetKeyState(VK_SHIFT) < 0) {
    dwFWLFlag |= (1 << 2);
  }
  return dwFWLFlag;
}

void CPDFReaderView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
  if (GetDocument()->isDynamicXFA()) {
    if (!m_FocusXFAWidget.IsEmpty())
      m_FocusXFAWidget.OnKeyDown(nChar, FWL_VirtKey2FWL());
  }
  CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPDFReaderView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
  if (GetDocument()->isDynamicXFA()) {
    if (!m_FocusXFAWidget.IsEmpty())
      m_FocusXFAWidget.OnKeyUp(nChar, FWL_VirtKey2FWL());
  }

  CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

HBRUSH CPDFReaderView::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor) {
  return HBRUSH();
}

void CPDFReaderView::OnACWRotation() {
  if (!HasAviliableDoc())
    return;
  m_Rotate = Rotation(m_Rotate - 1) < 0 ? e_Rotation270 : Rotation(m_Rotate - 1);
  m_bRatateChange = TRUE;
  Invalidate();
}

void CPDFReaderView::OnCWRotae() {
  if (!HasAviliableDoc())
    return;
  m_Rotate = Rotation(m_Rotate + 1) > 3 ? e_Rotation0 : Rotation(m_Rotate + 1);
  m_bRatateChange = TRUE;
  Invalidate();
}

void CPDFReaderView::OnTimer(UINT_PTR nIDEvent) {
  if (!HasAviliableDoc())
    return;
  switch(GetOperatorType()) {
  case AUTOSCROLL:
    MovePage(m_EndPt, CPoint(m_EndPt.x + (m_StartPt.x - m_EndPt.x) / 5,
                             m_EndPt.y + (m_StartPt.y - m_EndPt.y) / 5));
    POINT point;
    ::GetCursorPos(&point);
    ScreenToClient(&point);
    CReader_Page* pPage = GetPage(CPoint(point.x,point.y),m_fZoom);
    if (pPage) {
      foxit::PointF pdfPt;
      WindowToDoc(pPage->GetPageIndex(), CPoint(point.x, point.y), pdfPt);
      m_CurrentTextLink = pPage->GetTextLinkAtPos(pdfPt);
      if (!m_CurrentTextLink.IsEmpty()) {
        m_eCurPageLinkType = CReader_Page::TEXTLINK;
        m_CurrentAnnotLink = Link();
      } else {
        m_CurrentAnnotLink = pPage->GetAnnotLinkAtPos(pdfPt);
        if (!m_CurrentAnnotLink.IsEmpty()) {
          m_eCurPageLinkType = CReader_Page::ANNOTLINK;
          m_CurrentTextLink = TextLink();
        } else {
          m_eCurPageLinkType = CReader_Page::NOLINK;
          m_CurrentAnnotLink = Link();
          m_CurrentTextLink = TextLink();
        }
      }
     if (m_eCurPageLinkType) {
       ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_POINT));
     } else {
       ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_HAND));
     }
    }
    Invalidate();
  }
}

void CPDFReaderView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
}

// CPDFReaderView diagnostics
#ifdef _DEBUG
void CPDFReaderView::AssertValid() const
{
  CView::AssertValid();
}

void CPDFReaderView::Dump(CDumpContext& dc) const
{
  CView::Dump(dc);
}

CPDFReaderDoc* CPDFReaderView::GetDocument() const // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPDFReaderDoc)));
  return (CPDFReaderDoc*)m_pDocument;
}
#endif //_DEBUG

// CPDFReaderView message handlers
BOOL CPDFReaderView::HasAviliableDoc() const {
  return GetDocument()->HasLoadDocument();
}

bool CPDFReaderView::IsVisiblePage(int index) {
  if (!m_vecPageToDisplay.empty()) {
    for (std::vector<PageToDisplay>::iterator i = m_vecPageToDisplay.begin(); i != m_vecPageToDisplay.end(); i++) {
      if (i->page_index == index) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

int CPDFReaderView::GetCurVisiblePageIndex() {
  return m_nCurPageIndex;
}

Rotation CPDFReaderView::GetRotate() {
  return m_Rotate;
}

float CPDFReaderView::GetScale() {
  return m_fZoom;
}

int CPDFReaderView::GetPageSpace() {
  return GetDocument()->GetPageSpace();
}

void CPDFReaderView::InitScrollSize(int nLogPixelX, int nLogPixelY) {
  if (!HasAviliableDoc()) return;

  if (m_bRatateChange) {
    GetDocument()->UpdatePDFPages(nLogPixelX, nLogPixelY, m_Rotate);
    m_bRatateChange = FALSE;
  }

  CRect rc;
  GetClientRect(&rc);
  GetScrollInfo(SB_VERT, &m_Vertsi, SIF_ALL);
  GetScrollInfo(SB_HORZ, &m_Horzsi, SIF_ALL);

  POINT mousePt;
  if (GetAsyncKeyState(VK_CONTROL) == 0 ) {
    CRect rect;
    GetClientRect(&rect);
    mousePt.x = (rect.left + rect.right) / 2;
    mousePt.y = (rect.top + rect.bottom) / 2;
  } else {
    ::GetCursorPos(&mousePt);
    ScreenToClient(&mousePt);
  }

  CReader_Page* pPage = GetPage(mousePt,m_bZoomChange ? m_fLastZoom:m_fZoom);

  int index = m_nCurPageIndex;
  if (pPage != 0)
    index = pPage->GetPageIndex();
  else
    pPage = GetDocument()->GetPage(index);
  float prevPageRealHeight = 0;
  float curPos = float(m_Vertsi.nPos + mousePt.y);

  float newPos = 0.0f;
  float rate = 0.0f;
  float curPageRealHeight = pPage->GetPageTotalHeightWithSpace(m_fLastZoom);
  float pageHeight = m_Rotate % 2 ? pPage->GetPageWidth() : pPage->GetPageHeight();
  if (index > 0)
    prevPageRealHeight = GetDocument()->GetPage(index - 1)->GetPageTotalHeightWithSpace(m_fLastZoom);

  if (curPos <= prevPageRealHeight + GetPageSpace()) {
    if (index > 0)
      newPos = GetDocument()->GetPage(index - 1)->GetPageTotalHeightWithSpace(m_fZoom) + curPos - prevPageRealHeight;
    else
      newPos = curPos;
  } else {
    rate = (curPos - prevPageRealHeight - GetPageSpace())* (m_fZoom/m_fLastZoom);
    if (index > 0)
      newPos = GetDocument()->GetPage(index - 1)->GetPageTotalHeightWithSpace(m_fZoom) + GetPageSpace() + rate;
    else
      newPos = GetPageSpace() + rate;

  }

  m_Vertsi.fMask = SIF_ALL;
  m_Vertsi.nMax = int(GetDocument()->GetRealHeight(m_fZoom)+0.5f);
  m_Vertsi.nMin = 0;
  m_Vertsi.nPage = rc.Height();

  m_Vertsi.nPos = int(newPos - mousePt.y+0.5f);
  SetScrollInfo(SB_VERT, &m_Vertsi);

  curPos = float(m_Horzsi.nPos + mousePt.x);
  if (curPos < GetPageSpace()) {
    newPos = curPos;
  } else {
    CReader_Page* pPage = GetDocument()->GetPage(index);
    float pageWidth = m_Rotate % 2 ? pPage->GetPageHeight() : pPage->GetPageWidth();
    newPos = GetPageSpace() + (curPos - GetPageSpace()) * (m_fZoom/m_fLastZoom);
  }
  m_Horzsi.fMask = SIF_ALL;
  m_Horzsi.nMax = int(GetDocument()->GetRealWidth(m_fZoom) + 0.5f);
  m_Horzsi.nMin = 0;
  m_Horzsi.nPage = rc.Width();
  m_Horzsi.nPos = int(newPos - mousePt.x+0.5f);
  SetScrollInfo(SB_HORZ, &m_Horzsi);
}

void CPDFReaderView::SetVisiblePageByScrollPos(int vPos) {
  if (!HasAviliableDoc()) return;

  SCROLLINFO si;
  float StartPos = 0, EndPos = 0;
  m_nStartPageIndex = 0;
  m_nEndPageIndex = 0;
  CRect rc(0, 0, 0, 0);
  GetClientRect(&rc);
  if (!vPos) {
    GetScrollInfo(SB_VERT, &si, SIF_ALL);
    StartPos = float(si.nPos);
  } else {
    StartPos = float(vPos);
  }

  EndPos = rc.Height() + StartPos;
  float PrevPos = StartPos;

  GetDocument()->FindVisiblePage(StartPos, EndPos, m_nStartPageIndex, m_nEndPageIndex,m_fZoom);

  CReader_Page* pReaderStartPage = (CReader_Page*) GetDocument()->GetPage(m_nStartPageIndex);
  GetScrollInfo(SB_HORZ, &si, SIF_ALL);

  ReleasePageCacheData(m_nStartPageIndex, m_nEndPageIndex);
  CopyPageDisplayData(m_vecPageToDisplay, m_prev_vecPageToDisplay);
  m_vecPageToDisplay.clear();

  float cy = 0, cx = 0;
  float offsetY = max((rc.Height() - GetDocument()->GetRealHeight(m_fZoom))/2,0);
  int current_page_cy = 0;
  for (int i = m_nStartPageIndex; i <= m_nEndPageIndex; i++) {
    CReader_Page* pPage = GetDocument()->GetPage(i);
    if (!pPage) continue;
    CRect rc;
    GetClientRect(rc);
    float docWidth = GetDocument()->GetRealWidth(m_fZoom);
    if (docWidth < (rc.right - rc.left) ) {
      cx = GetStartXPosWithMargin(i) + GetPageSpace();
    } else {
      float width = m_Rotate % 2 ? pPage->GetPageHeight() : pPage->GetPageWidth();
      cx = -(float) si.nPos + (docWidth - width* m_fZoom)/2;
    }
    cy = pPage->GetPageTotalHeightWithSpace(m_fZoom) - (m_Rotate % 2 ? pPage->GetPageWidth() : pPage->GetPageHeight())*m_fZoom + offsetY;
    PageToDisplay pageToDisplay;
    pageToDisplay.cx = int(cx + 0.5f);
    pageToDisplay.cy = int(cy - PrevPos + 0.5f);
    int client_rect_half_height = rc.Height()/2;
    if (i == m_nStartPageIndex) {
      current_page_cy = pageToDisplay.cy;
      m_nCurPageIndex = m_nStartPageIndex;
    } else {
      if (pageToDisplay.cy<client_rect_half_height && pageToDisplay.cy>current_page_cy){
        current_page_cy = pageToDisplay.cy;
        m_nCurPageIndex = i;
      }
    }
    pageToDisplay.page_index = i;
    m_vecPageToDisplay.push_back(pageToDisplay);
  }
  ResetCurrentPageIndex();
}

void CPDFReaderView::SetVisiblePageByIndex(int nIndex) {
  if (!HasAviliableDoc()) return;

  // Get the whole height of all pages.
  float current_all_pages_height = GetDocument()->GetRealHeight(m_fZoom);

  // Get the total height from first page to the previous page of next visible page.
  float next_visible_page_top_height = 0;
  CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(nIndex-1);
  if (pReaderPage) {
    next_visible_page_top_height = pReaderPage->GetPageTotalHeightWithSpace(m_fZoom);
  }

  SCROLLINFO si;
  GetScrollInfo(SB_VERT, &si, SIF_ALL);

  // Calculate the next position in scroll bar for the top of next visible page
  UINT nNextPos = (UINT)(next_visible_page_top_height/current_all_pages_height * si.nMax);
  if (nNextPos >= si.nMax - si.nPage + 1)
    nNextPos = si.nMax - si.nPage + 1;

  si.nPos = (int) nNextPos;
  SetScrollInfo(SB_VERT, &si);

  SetVisiblePageByScrollPos(nNextPos);
}

void CPDFReaderView::SetVisiblePageByIndex(int nIndex, float fHeight, float fWidth) {
    if (!HasAviliableDoc()) return;

    float fPageTotalHeight = 0;
    UINT nVNextPos = 0;
    CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(nIndex - 1);
    if (pReaderPage) {
      fPageTotalHeight = pReaderPage->GetPageTotalHeightWithSpace(m_fZoom);
    }

    nVNextPos = (UINT) (fPageTotalHeight + fHeight*m_fZoom + 0.5f);

    SCROLLINFO si;
    GetScrollInfo(SB_VERT, &si, SIF_ALL);

    if (nVNextPos >= si.nMax - si.nPage + 1)
      nVNextPos = si.nMax - si.nPage + 1;

    si.nPos = (int) nVNextPos;
    SetScrollInfo(SB_VERT, &si);

    RECT rc;
    this->GetClientRect(&rc);

    float nDocWidth = GetDocument()->GetRealWidth(m_fZoom);
    pReaderPage = GetDocument()->GetPage(nIndex);
    if (nDocWidth > float(rc.right - rc.left) && pReaderPage) {
      float nPageRealWidth = m_Rotate % 2 ? pReaderPage->GetPageHeight() : pReaderPage->GetPageWidth();
      UINT nHNextPos = UINT((nDocWidth - nPageRealWidth*m_fZoom) / 2 + fWidth * m_fZoom + 0.5f);
      SCROLLINFO si;
      GetScrollInfo(SB_HORZ, &si, SIF_ALL);

      if (nHNextPos >= si.nMax - si.nPage + 1)
        nHNextPos = si.nMax - si.nPage + 1;

      si.nPos = (int) nHNextPos;
      SetScrollInfo(SB_HORZ, &si);
    }

    SetVisiblePageByScrollPos(nVNextPos);
}

BOOL CPDFReaderView::ResetCurrentPageIndex()
{
  if (HasAviliableDoc()) {
    CMainFrame* frame = (CMainFrame*) theApp.GetFrameByDoc(GetDocument());
    if (!frame) return false;
    CPageComboBox* pBox = frame->GetPageGotoButton()->GetComboBox();
    if (GetDocument()->GetPageCount() != pBox->GetCount()) {
      m_bPrepareLabels = FALSE;
      pBox->ResetContent();
    }

    if (!m_bPrepareLabels) {
      int pageCount = GetDocument()->GetPageCount();
      if (GetDocument()->isDynamicXFA()) {
        for (int i = 0; i < pageCount; i++) {
          CString pageInfo;
          pageInfo.Format(_T("(%d/%d)"), i + 1, pageCount);
          pBox->AddString(pageInfo);
        }
      } else {
      PageLabels pageLabels(GetDocument()->GetPDFDocument());
      for (int i = 0; i < pageCount; i++) {
        foxit::WString labels = pageLabels.GetPageLabelTitle(i);
        CString pageInfo;
        pageInfo.Format(_T("%ws(%d/%d)"), labels.IsEmpty() ? L"":(const wchar_t*)labels, i + 1, pageCount);
        pBox->AddString(pageInfo);
      }
    }
      m_bPrepareLabels = TRUE;
    }
    pBox->SetCurSel(m_nCurPageIndex);
    GetDocument()->UpdateCurPage(m_nCurPageIndex);
  }

  return TRUE;
}

void CPDFReaderView::MovePage(CPoint curPoint, CPoint toPoint) {
  GetScrollInfo(SB_VERT, &m_Vertsi);
  GetScrollInfo(SB_HORZ, &m_Horzsi);
  CPoint pt;
  pt = toPoint - curPoint;
  m_Vertsi.nPos = m_Vertsi.nPos - pt.y;
  m_Horzsi.nPos = m_Horzsi.nPos - pt.x;

  SetScrollInfo(SB_VERT, &m_Vertsi);
  SetScrollInfo(SB_HORZ, &m_Horzsi);
  SetVisiblePageByScrollPos();
}

void CPDFReaderView::MovePage(short zDelta) {
  GetScrollInfo(SB_VERT, &m_Vertsi);
  m_Vertsi.nPos = m_Vertsi.nPos - zDelta;
  SetScrollInfo(SB_VERT, &m_Vertsi);
  SetVisiblePageByScrollPos();
}

void CPDFReaderView::GotoDestination(Destination pdf_dest) {
  if (pdf_dest.IsEmpty()) return;
  CPDFReaderDoc* pReaderDoc = GetDocument();

  PDFDoc pdf_doc = pReaderDoc->GetPDFDocument();
  int index = pdf_dest.GetPageIndex(pdf_doc);
  if (index<0) return;
  PDFPage pdf_page = pdf_doc.GetPage(index);
  float fWidth = pdf_page.GetWidth();
  float fHeight = pdf_page.GetHeight();
  CReader_Page* pPage = pReaderDoc->GetPage(index);
  float fVRate = 0.0f;
  float fHRate = 0.0f;
  switch (GetRotate() - pdf_page.GetRotation()) {
  case e_Rotation0:
  {
    if (pReaderDoc->isDynamicXFA()) {
      fVRate = pdf_dest.GetBottom() / fHeight;
    } else {
      fVRate = (fHeight - pdf_dest.GetTop()) / fHeight;
    }
    fHRate = pdf_dest.GetLeft() / fWidth;
  } break;
  case e_Rotation90:
  {
    fVRate = pdf_dest.GetLeft() / fWidth;
    if (pReaderDoc->isDynamicXFA()) {
      fHRate = (fHeight - pdf_dest.GetBottom()) / fHeight - 50/fHeight;
    } else {
      fHRate = pdf_dest.GetTop() / fHeight - 50 / fHeight;
    }
  } break;
  case e_Rotation180:
  {
    if (pReaderDoc->isDynamicXFA()) {
      fVRate = (fHeight - pdf_dest.GetBottom()) / fHeight- 50 / fHeight;
    } else {
      fVRate = (pdf_dest.GetTop()) / fHeight - 50 / fHeight;
    }
    fHRate = (fWidth - pdf_dest.GetRight()) / fWidth ;
  } break;
  case e_Rotation270:
    fVRate = (fWidth - pdf_dest.GetLeft()) / fWidth - 50 / fWidth;
    if (pReaderDoc->isDynamicXFA()) {
      fHRate = pdf_dest.GetBottom() / fHeight;
    } else {
      fHRate = (fHeight - pdf_dest.GetTop()) / fHeight;
    }
  }

  SetVisiblePageByIndex(index, fVRate * (GetRotate() % 2 ? pPage->GetPageWidth() : pPage->GetPageHeight()),
                        fHRate * (GetRotate() % 2 ? pPage->GetPageHeight() : pPage->GetPageWidth()));
  Invalidate();
}

float CPDFReaderView::GetStartXPosWithMargin(int nPage) {
  if (!HasAviliableDoc()) return 0;

  CReader_Page* pReaderPage = (CReader_Page*)GetDocument()->GetPage(nPage);
  if (!pReaderPage) return 0.0f;
  CRect rc;
  float width;
  GetClientRect(&rc);
  if (m_Rotate == 1 || m_Rotate == 3)
    width = pReaderPage->GetPageHeight() * m_fZoom;
  else
    width = pReaderPage->GetPageWidth()* m_fZoom;
  return rc.Width() / 2 - width / 2 - GetPageSpace();
}

void CPDFReaderView::RenderPage(CDC * pDC, int Index, int Width, int Height, int cx, int cy) {
  Rotation nRotate = e_Rotation0;
  Renderer renderer(pDC->GetSafeHdc());

  CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(Index);

  if (pReaderPage && !pReaderPage->GetPDFPage().IsEmpty()) {
    pReaderPage->ParsePage(false);
  }

  PDFPage pdfPage = pReaderPage->GetPDFPage();
  XFAPage xfaPage = pReaderPage->GetXFAPage();

  //Clear the canvas with the white color.
  RECT rcPage = {cx, cy, cx + Width, cy + Height};
  HBRUSH hBrush = CreateSolidBrush(RGB(0xff, 0xff, 0xff));
  FillRect(pDC->GetSafeHdc(), &rcPage, hBrush);
  DeleteObject(hBrush);

  int nSaveDC = pDC->SaveDC();
  pDC->IntersectClipRect(&rcPage);

  //Get page transformation matrix.
  foxit::Matrix matrix;
  if (GetDocument()->isDynamicXFA()) {
    matrix = xfaPage.GetDisplayMatrix(cx, cy, Width, Height, nRotate);
    renderer.StartRenderXFAPage(xfaPage, matrix, TRUE, NULL);
  } else {
    matrix = pdfPage.GetDisplayMatrix(cx, cy, Width, Height, nRotate);
    renderer.StartRender(pdfPage, matrix, NULL);
  }

  pDC->RestoreDC(nSaveDC);
}

void CPDFReaderView::RenderPageTile(CDC * pDC, int Index, int pageWidth, int pageHeight, int renderWidth, int renderHeight, int pagecx, int pagecy,int rendercx,int rendercy) 
{
  foxit::RectI rectBitmap;
  rectBitmap.left = 0;
  rectBitmap.right = rectBitmap.left + renderWidth;
  rectBitmap.top = 0;
  rectBitmap.bottom = rectBitmap.top + renderHeight;
  if (rectBitmap.right <= 0 || rectBitmap.bottom <= 0)
    return;
  Bitmap bitmap(rectBitmap.right, rectBitmap.bottom, Bitmap::e_DIBArgb, NULL, 0);
  Renderer render(bitmap, false);

  int render_left = pagecx < 0 ? pagecx : 0;
  int render_top = pagecy<0 ? pagecy:0;
  Rotation render_rotation = m_Rotate;
  int nSaveDC = 0;
  CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(Index);
  if (GetDocument()->isDynamicXFA()) 
  {
    return;
  } 

  if (pReaderPage) 
  {
    pReaderPage->ParsePage(false);
  }

  if (pReaderPage->IsHasTransparency()) {
    bitmap.FillRect(0x00000000, &rectBitmap);
  } else {
    bitmap.FillRect(RENDER_PAGE_COLOR, &rectBitmap);
  }

  nSaveDC = pDC->SaveDC();
  // Get page transformation matrix. Now the bitmap is the device output.
  PDFPage pdfPage = pReaderPage->GetPDFPage();
  foxit::Matrix matrix = pdfPage.GetDisplayMatrix(rendercx, rendercy, pageWidth, pageHeight, render_rotation);
  render.StartRender(pdfPage, matrix, NULL);

  Filler form_filler = GetDocument()->GetFormFiller();
  if(!form_filler.IsEmpty())
    form_filler.Render(pdfPage, matrix, render);

  BITMAPINFO bmi;
  ZeroMemory(&bmi, sizeof(BITMAPINFO));
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = rectBitmap.right;
  bmi.bmiHeader.biHeight = -rectBitmap.bottom;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;
  StretchDIBits(pDC->GetSafeHdc(), (int)pagecx, (int)pagecy, renderWidth, renderHeight, 0, 0, rectBitmap.right,
    rectBitmap.bottom, bitmap.GetBuffer(), &bmi, DIB_RGB_COLORS, SRCCOPY);
  pDC->RestoreDC(nSaveDC);
}

void CPDFReaderView::RenderPageByGE(CDC * pDC, int Index, int Width, int Height, int cx, int cy, bool bIsForPrint/* = false*/) {
  //Clear the canvas with the white color.
  RECT rcPage = {cx, cy, cx + Width, cy + Height};
  if (!bIsForPrint) {
    RECT rc;
    this->GetClientRect(&rc);
    rcPage.left = max(rc.left, rcPage.left);
    rcPage.right = min(rc.right,rcPage.right);
    rcPage.top = max(rc.top, rcPage.top);
    rcPage.bottom = min(rc.bottom, rcPage.bottom);
  }

  HBRUSH hBrush = CreateSolidBrush(RENDER_PAGE_COLOR);
  FillRect(pDC->GetSafeHdc(), &rcPage, hBrush);
  DeleteObject(hBrush);

  foxit::RectI rectBitmap;
  rectBitmap.left = 0;
  rectBitmap.right = rcPage.right - rcPage.left;
  rectBitmap.top = 0;
  rectBitmap.bottom = rcPage.bottom - rcPage.top;
  if (rectBitmap.right <= 0 || rectBitmap.bottom <= 0)
    return;
  Bitmap bitmap(rectBitmap.right, rectBitmap.bottom, Bitmap::e_DIBArgb, NULL, 0);
  Renderer render(bitmap, false);

  int render_left = cx < 0 ? cx : 0;
  int render_top = cy<0 ? cy:0;
  Rotation render_rotation = m_Rotate;
  int nSaveDC = 0;
  CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(Index);
  if (GetDocument()->isDynamicXFA()) {
    XFAPage pXFAPage;
    if (pReaderPage) {
      pXFAPage = pReaderPage->GetXFAPage();
    }
    float fHeight = pXFAPage.GetHeight();
    float fWidth = pXFAPage.GetWidth();

    foxit::Matrix matrix_1 = pXFAPage.GetDisplayMatrix(render_left, render_top, Width, Height, render_rotation);
    bitmap.FillRect(RENDER_PAGE_COLOR, &rectBitmap);

    nSaveDC = pDC->SaveDC();
    render.StartRenderXFAPage(pXFAPage,matrix_1,TRUE, NULL);
  } else {
    if (pReaderPage) {
      pReaderPage->ParsePage(false);
    }

    if (pReaderPage->IsHasTransparency()) {
      bitmap.FillRect(0x00000000, &rectBitmap);
    } else {
      bitmap.FillRect(RENDER_PAGE_COLOR, &rectBitmap);
    }

    nSaveDC = pDC->SaveDC();
    // Get page transformation matrix. Now the bitmap is the device output.
    PDFPage pdfPage = pReaderPage->GetPDFPage();
    foxit::Matrix matrix = pdfPage.GetDisplayMatrix(render_left, render_top, Width, Height, render_rotation);

    render.StartRender(pdfPage, matrix, NULL);

    Filler form_filler = GetDocument()->GetFormFiller();
    if(!form_filler.IsEmpty())
      form_filler.Render(pdfPage, matrix, render);
  }

  BITMAPINFO bmi;
  ZeroMemory(&bmi, sizeof(BITMAPINFO));
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = rectBitmap.right;
  bmi.bmiHeader.biHeight = -rectBitmap.bottom;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;
  StretchDIBits(pDC->GetSafeHdc(), (int)rcPage.left, (int)rcPage.top, rectBitmap.right, rectBitmap.bottom, 0, 0, rectBitmap.right,
    rectBitmap.bottom, bitmap.GetBuffer(), &bmi, DIB_RGB_COLORS, SRCCOPY);
  pDC->RestoreDC(nSaveDC);
}

CReader_Page * CPDFReaderView::GetPage(CPoint point,float fZoom) {
  if (!m_vecPageToDisplay.empty()) {
    std::vector<PageToDisplay>::iterator i;
    for (i = m_vecPageToDisplay.begin(); i != m_vecPageToDisplay.end(); i++) {
      CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(i->page_index);
      float width = 0, height = 0;
      if (m_Rotate == 0 || m_Rotate == 2) {
        height = pReaderPage->GetPageHeight() * fZoom;
        width = pReaderPage->GetPageWidth() * fZoom;
      } else {
        height = pReaderPage->GetPageWidth() * fZoom;
        width = pReaderPage->GetPageHeight() * fZoom;
      }

      RECT rcTemp = {i->cx, (int) i->cy, (int) (i->cx + width), int (i->cy + height)};
      if (point.x >= rcTemp.left && point.x <= rcTemp.right && point.y >= rcTemp.top && point.y <= rcTemp.bottom) {
        return pReaderPage;
      }
    }
  }
  return NULL;
}

foxit::Matrix CPDFReaderView::GetPageMatrix(int nPageIndex) {
  if (!m_vecPageToDisplay.empty()) {
    std::vector<PageToDisplay>::iterator i;
    for (i = m_vecPageToDisplay.begin(); i != m_vecPageToDisplay.end(); i++) {
      CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(i->page_index);
      if (pReaderPage&&pReaderPage->GetPageIndex() == nPageIndex) {
        float width = 0, height = 0;
        if (m_Rotate == 0 || m_Rotate == 2) {
          height = pReaderPage->GetPageHeight() * m_fZoom;
          width = pReaderPage->GetPageWidth() * m_fZoom;
        } else {
          height = pReaderPage->GetPageWidth() * m_fZoom;
          width = pReaderPage->GetPageHeight() * m_fZoom;
        }
        if (GetDocument()->isDynamicXFA())
          return pReaderPage->GetXFAPage().GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);
        else
          return pReaderPage->GetPDFPage().GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);
      }
    }
  }
  return foxit::Matrix();
}

foxit::Matrix CPDFReaderView::GetPageMatrixForPrint(int nPageIndex) {
  CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(nPageIndex);
  if (pReaderPage) {
    float width = 0, height = 0;
    Rotation nRotate = e_Rotation0;
    if (!GetDocument()->isDynamicXFA())
     nRotate = pReaderPage->GetPDFPage().GetRotation();
    if (nRotate == 0 || nRotate == 2) {
      height = pReaderPage->GetPageHeight() * m_fZoom;
      width = pReaderPage->GetPageWidth() * m_fZoom;
    } else {
      height = pReaderPage->GetPageWidth() * m_fZoom;
      width = pReaderPage->GetPageHeight() * m_fZoom;
    }

    if (GetDocument()->isDynamicXFA())
      return GetDocument()->GetXFADoc().GetPage(nPageIndex).GetDisplayMatrix(0, 0 , (int) width, (int) height, m_Rotate);
    else
      return pReaderPage->GetPDFPage().GetDisplayMatrix(0, 0 , (int) width, (int) height, m_Rotate);
  }

  return foxit::Matrix();
}

 bool CPDFReaderView::GetPageDisplayMatrix(int nPageIndex,foxit::Matrix& page_matrix) 
{
    if (!m_vecPageToDisplay.empty()) {
        std::vector<PageToDisplay>::iterator i;
        for (i = m_vecPageToDisplay.begin(); i != m_vecPageToDisplay.end(); i++) {
            CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(i->page_index);
            if (pReaderPage->GetPageIndex() == nPageIndex) {
                float width = 0, height = 0;
                if (m_Rotate == 0 || m_Rotate == 2) {
                    height = pReaderPage->GetPageHeight() * m_fZoom;
                    width = pReaderPage->GetPageWidth() * m_fZoom;
                } else {
                    height = pReaderPage->GetPageWidth() * m_fZoom;
                    width = pReaderPage->GetPageHeight() * m_fZoom;
                }

                foxit::Matrix matrix;
                if (GetDocument()->isDynamicXFA())
                    matrix = GetDocument()->GetXFADoc().GetPage(nPageIndex).GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);
                else
                    matrix = pReaderPage->GetPDFPage().GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);
                page_matrix = matrix;
                return true;
            }
        }
    }
    return false;
}

bool CPDFReaderView::DocToWindow(int nPageIndex, const foxit::RectF & rcDoc, CRect & rcWindow) {
  if (!m_vecPageToDisplay.empty()) {
    std::vector<PageToDisplay>::iterator i;
    for (i = m_vecPageToDisplay.begin(); i != m_vecPageToDisplay.end(); i++) {
      CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(i->page_index);
      if (pReaderPage->GetPageIndex() == nPageIndex) {
        float width = 0, height = 0;
        if (m_Rotate == 0 || m_Rotate == 2) {
          height = pReaderPage->GetPageHeight() * m_fZoom;
          width = pReaderPage->GetPageWidth() * m_fZoom;
        } else {
          height = pReaderPage->GetPageWidth() * m_fZoom;
          width = pReaderPage->GetPageHeight() * m_fZoom;
        }

        foxit::Matrix matrix;
        if (GetDocument()->isDynamicXFA())
          matrix = GetDocument()->GetXFADoc().GetPage(nPageIndex).GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);
        else
          matrix = pReaderPage->GetPDFPage().GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);
        foxit::RectF transformed_rect = rcDoc;
        /*foxit::RectF ret = */matrix.TransformRect(transformed_rect);
        if (transformed_rect.bottom<transformed_rect.top) {
          float temp = transformed_rect.bottom;
          transformed_rect.bottom = transformed_rect.top;
          transformed_rect.top = temp;
        }
        rcWindow.SetRect((int) (transformed_rect.left + 0.5), (int)(transformed_rect.bottom + 0.5), (int)(transformed_rect.right + 0.5), (int)(transformed_rect.top + 0.5));
        return TRUE;
      }
    }
  }
  return FALSE;
}

bool CPDFReaderView::DocToWindow(int nPageIndex, const foxit::PointF & ptDoc, CPoint & ptWindow) {
  if (!m_vecPageToDisplay.empty()) {
    std::vector<PageToDisplay>::iterator i;
    for (i = m_vecPageToDisplay.begin(); i != m_vecPageToDisplay.end(); i++) {
      CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(i->page_index);
      if (pReaderPage->GetPageIndex() == nPageIndex) {
        float width = 0, height = 0;
        if (m_Rotate == 0 || m_Rotate == 2) {
          height = pReaderPage->GetPageHeight() * m_fZoom;
          width = pReaderPage->GetPageWidth() * m_fZoom;
        } else {
          height = pReaderPage->GetPageWidth() * m_fZoom;
          width = pReaderPage->GetPageHeight() * m_fZoom;
        }

        foxit::Matrix matrix;
        if (GetDocument()->isDynamicXFA())
          matrix = GetDocument()->GetXFADoc().GetPage(nPageIndex).GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);
        else
          matrix = pReaderPage->GetPDFPage().GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);
        foxit::PointF transformed_point = ptDoc;
        matrix.TransformPoint(transformed_point.x, transformed_point.y);
        ptWindow.SetPoint((int) (transformed_point.x + 0.5), (int) (transformed_point.y + 0.5));
        return TRUE;
      }
    }
  }
  return FALSE;
}

bool CPDFReaderView::WindowToDoc(int nPageIndex, const CPoint & ptWindow, foxit::PointF & ptDoc) {
  if (!m_vecPageToDisplay.empty()) {
    std::vector<PageToDisplay>::iterator i;
    for (i = m_vecPageToDisplay.begin(); i != m_vecPageToDisplay.end(); i++) {
      CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(i->page_index);
      if (pReaderPage->GetPageIndex() == nPageIndex) {
        float width = 0, height = 0;
        if (m_Rotate == 0 || m_Rotate == 2) {
          height = pReaderPage->GetPageHeight() * m_fZoom;
          width = pReaderPage->GetPageWidth() * m_fZoom;
        } else {
          height = pReaderPage->GetPageWidth() * m_fZoom;
          width = pReaderPage->GetPageHeight() * m_fZoom;
        }

        foxit::Matrix matrix;
        if (GetDocument()->isDynamicXFA())
          matrix = pReaderPage->GetXFAPage().GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);
        else
          matrix = pReaderPage->GetPDFPage().GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);

        foxit::Matrix dstMatrix;
        dstMatrix.SetReverse(matrix);
        ptDoc = foxit::PointF(float(ptWindow.x), float(ptWindow.y));
        dstMatrix.TransformPoint(ptDoc.x, ptDoc.y);
        return TRUE;
      }
    }
  }
  return FALSE;
}

bool CPDFReaderView::WindowToDoc(int nPageIndex, const CRect & rcWindow, foxit::RectF & rcDoc) {
  if (!m_vecPageToDisplay.empty()) {
    std::vector<PageToDisplay>::iterator i;
    for (i = m_vecPageToDisplay.begin(); i != m_vecPageToDisplay.end(); i++) {
      CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(i->page_index);
      if (pReaderPage->GetPageIndex() == nPageIndex) {
        float width = 0, height = 0;
        if (m_Rotate == 0 || m_Rotate == 2) {
          height = pReaderPage->GetPageHeight() * m_fZoom;
          width = pReaderPage->GetPageWidth() * m_fZoom;
        } else {
          height = pReaderPage->GetPageWidth() * m_fZoom;
          width = pReaderPage->GetPageHeight() * m_fZoom;
        }

        foxit::Matrix matrix;
        if (GetDocument()->isDynamicXFA())
          matrix = GetDocument()->GetXFADoc().GetPage(nPageIndex).GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);
        else
          matrix = pReaderPage->GetPDFPage().GetDisplayMatrix(i->cx, (int) i->cy , (int) width, (int) height, m_Rotate);

        foxit::Matrix dstMatrix = matrix;
        dstMatrix.SetReverse(matrix);
        rcDoc = foxit::RectF(float(rcWindow.left), float(rcWindow.top), float(rcWindow.right), float(rcWindow.bottom));
        dstMatrix.TransformRect(rcDoc);
        return TRUE;
      }
    }
  }
  return FALSE;
}

bool CPDFReaderView::WindowToDocForPrint(int nPageIndex, const CRect& rcWindow, foxit::RectF& rcDoc) {
  foxit::Matrix matrix = GetPageMatrixForPrint(nPageIndex);

  foxit::Matrix dstMatrix;
  dstMatrix.SetReverse(matrix);
  rcDoc = foxit::RectF(float(rcWindow.left), float(rcWindow.bottom), float(rcWindow.right), float(rcWindow.top));
  dstMatrix.TransformRect(rcDoc);
  if (rcDoc.bottom<rcDoc.top) {
    float temp = rcDoc.bottom;
    rcDoc.bottom = rcDoc.top;
    rcDoc.top = temp;
  }
  return TRUE;
}

void CPDFReaderView::ReleasePageCacheData(int iPageStart, int iPgaeEnd) {
  if (!m_vecPageToDisplay.empty()) {
    std::vector<PageToDisplay>::iterator i;
    for (i = m_vecPageToDisplay.begin(); i != m_vecPageToDisplay.end(); i++) {
      if (i->page_index < iPageStart || i->page_index > iPgaeEnd) {
        CReader_Page* pReaderPage = (CReader_Page*) GetDocument()->GetPage(i->page_index);
        pReaderPage->ReleaseTempData();
      }
    }
  }
}

void CPDFReaderView::SearchText(int nPageIndex, std::vector<foxit::RectF> rect_array) {
  if (rect_array.size() == 0) {
    AfxMessageBox(_T("No matches were found."));
	return;
  }
  m_vSearchRect.swap(rect_array);
  foxit::RectF rect = m_vSearchRect[0];
  for (size_t i = 1; i < m_vSearchRect.size(); i++) {
    foxit::RectF tmp = m_vSearchRect[i];
    rect.top = max(rect.top, tmp.top);
    rect.right = max(rect.right, tmp.right);
    rect.left = min(rect.left, tmp.left);
    rect.bottom = max(rect.bottom, tmp.bottom);
  }
  PDFDoc pdf_doc = GetDocument()->GetPDFDocument();
  float fWidth = 0.0f, fHeight = 0.0f;

  PDFPage pdf_page;
  if (!GetDocument()->isDynamicXFA())
    pdf_page= pdf_doc.GetPage(nPageIndex);
  CReader_Page* pPage = GetDocument()->GetPage(nPageIndex);
  if (GetDocument()->isDynamicXFA()) {
    fWidth = pPage->GetXFAPage().GetWidth();
    fHeight = pPage->GetXFAPage().GetHeight();
  } else {
    fWidth = pdf_page.GetWidth();
    fHeight = pdf_page.GetHeight();
  }

  float fVRate = 0.0f;
  float fHRate = 0.0f;
  int rotate_page = 0;
  if (!GetDocument()->isDynamicXFA()) {
    rotate_page = pdf_page.GetRotation();
  }
  switch (m_Rotate - rotate_page) {
    case e_Rotation0: {
      fVRate = (GetDocument()->isDynamicXFA() ?rect.top : (fHeight - rect.top)) / fHeight;
      fHRate = rect.left / fWidth;
    } break;
    case e_Rotation90: {
      fVRate = rect.left / fWidth;
      fHRate = (GetDocument()->isDynamicXFA() ? (fHeight - rect.bottom) : rect.bottom) / fHeight;
    } break;
    case e_Rotation180: {
      fVRate = (GetDocument()->isDynamicXFA() ? (fHeight - rect.bottom):rect.bottom) / fHeight;
      fHRate = (fWidth - rect.right) / fWidth;
    } break;
    case e_Rotation270:
      fVRate = (fWidth - rect.right) / fWidth;
      fHRate = (GetDocument()->isDynamicXFA() ? rect.top : (fHeight - rect.top)) / fHeight;
  }
  SetVisiblePageByIndex(nPageIndex, fVRate * (m_Rotate % 2 ? pPage->GetPageWidth() : pPage->GetPageHeight()),
                        fHRate * (m_Rotate % 2 ? pPage->GetPageHeight() : pPage->GetPageWidth()));
  Invalidate();
}

void CPDFReaderView::CleanSearch() {
  m_vSearchRect.clear();
}

void CPDFReaderView::OnAnnotFreetext(){
  SetOperatorType(DRAWINGANNOT);
  m_DrawingAnnotType = Annot::e_FreeText;
}

void CPDFReaderView::OnAnnotHighlight() {
  SetOperatorType(DRAWINGANNOT);
  m_DrawingAnnotType = Annot::e_Highlight;
}

void CPDFReaderView::OnAnnotNotes() {
  SetOperatorType(DRAWINGANNOT);
  m_DrawingAnnotType = Annot::e_Note;
}

void CPDFReaderView::OnAnnotLink() {
  SetOperatorType(DRAWINGANNOT);

  m_DrawingAnnotType = Annot::e_Link;
}

void CPDFReaderView::OnAnnotUnderline()
{
  SetOperatorType(DRAWINGANNOT);

  m_DrawingAnnotType = Annot::e_Underline;
}

void CPDFReaderView::OnSlider() {
  if (!HasAviliableDoc())
    return;
  if (GetAsyncKeyState(VK_LBUTTON) == 0) {
    CString str;
    CMainFrame* pFrame = (CMainFrame*)theApp.GetFrameByDoc(GetDocument());
    OnZoom(pFrame->GetZoomSliderButton()->GetZoomValue());
  }
}

void CPDFReaderView::SetOperatorType(OperatorType operatorType) {
  m_OperatorType = operatorType;

  m_bFixedAutoScroll = FALSE;
  KillTimer(AUTOSCROLL_TIMER_ID);

  // for select
  m_nStartCharIndex = -1;
  m_nEndCharIndex = -1;
  m_vSelectRectInfo.clear();

  // for hand
  m_StartPt.SetPoint(0, 0);
  m_EndPt.SetPoint(0, 0);

  // for annot
  m_CurPt.SetPoint(0, 0);
  m_FocusAnnot = Annot();

  // for page link
  m_CurrentAnnotLink = Link();
  m_CurrentTextLink = TextLink();
  m_eCurPageLinkType = CReader_Page::NOLINK;

  m_bLButtonDown = false;
  Invalidate();
}

CPDFReaderView::OperatorType CPDFReaderView::GetOperatorType() {
  return m_OperatorType;
}

void CPDFReaderView::OnToolAnnotselect(){
  SetOperatorType(ANNOTSELECT);
}

void CPDFReaderView::OnUpdateAnnotFreetext(CCmdUI * pCmdUI) {
  if (GetDocument()->isDynamicXFA()) {
    pCmdUI->Enable(FALSE);
    return;
  }
  if (m_OperatorType == DRAWINGANNOT && m_DrawingAnnotType == Annot::e_FreeText)
    pCmdUI->SetCheck(TRUE);
  else
    pCmdUI->SetCheck(FALSE);
}

void CPDFReaderView::OnUpdateAnnotHighlight(CCmdUI * pCmdUI) {
  if (GetDocument()->isDynamicXFA()) {
    pCmdUI->Enable(FALSE);
    return;
  }
  if (m_OperatorType == DRAWINGANNOT && m_DrawingAnnotType == Annot::e_Highlight)
    pCmdUI->SetCheck(TRUE);
  else
    pCmdUI->SetCheck(FALSE);
}

void CPDFReaderView::OnUpdateAnnotNotes(CCmdUI * pCmdUI) {
  if (GetDocument()->isDynamicXFA()) {
    pCmdUI->Enable(FALSE);
    return;
  }
  if (m_OperatorType == DRAWINGANNOT && m_DrawingAnnotType == Annot::e_Note)
    pCmdUI->SetCheck(TRUE);
  else
    pCmdUI->SetCheck(FALSE);
}

void CPDFReaderView::OnUpdateAnnotLink(CCmdUI * pCmdUI) {
  if (GetDocument()->isDynamicXFA()) {
    pCmdUI->Enable(FALSE);
    return;
  }
  if (m_OperatorType == DRAWINGANNOT && m_DrawingAnnotType == Annot::e_Link)
    pCmdUI->SetCheck(TRUE);
  else
    pCmdUI->SetCheck(FALSE);
}

void CPDFReaderView::OnUpdateAnnotUnderline(CCmdUI * pCmdUI) {
  if (GetDocument()->isDynamicXFA()) {
    pCmdUI->Enable(FALSE);
    return;
  }
  if (m_OperatorType == DRAWINGANNOT && m_DrawingAnnotType == Annot::e_Underline)
    pCmdUI->SetCheck(TRUE);
  else
    pCmdUI->SetCheck(FALSE);
}

void CPDFReaderView::OnUpdateToolAnnotselect(CCmdUI * pCmdUI) {
  if (GetDocument()->isDynamicXFA()) {
    pCmdUI->Enable(FALSE);
    return;
  }
  if (m_OperatorType == ANNOTSELECT)
    pCmdUI->SetCheck(TRUE);
  else
    pCmdUI->SetCheck(FALSE);
}

BOOL CPDFReaderView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {
  // TODO: Add your message handler code here and/or call default
  POINT point;
  ::GetCursorPos(&point);
  ScreenToClient(&point);
  CRect rsClient;
  GetClientRect(&rsClient);
  if (rsClient.PtInRect(point)) {

    if (m_OperatorType == HAND || m_OperatorType == AUTOSCROLL || m_OperatorType == UNKNOWN) {
      if (!m_CurrentTextLink.IsEmpty() || !m_CurrentAnnotLink.IsEmpty()) {
        ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_POINT));
        return TRUE;
      }
    }

    switch (GetOperatorType()) {
    case DRAWINGANNOT:
      if (m_DrawingAnnotType == Annot::e_Highlight || m_DrawingAnnotType == Annot::e_Underline) {
        ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_IBEAM));
      } else {
        ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_CROSS));
      }
      return TRUE;
    case HAND:
      m_bLButtonDown ? ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_CATCH)): ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_HAND));
      return TRUE;
    case TextPage:
      ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_IBEAM));
      return TRUE;
    case ANNOTSELECT:
      ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_SELECTANNOT));
      return TRUE;
    case AUTOSCROLL:
      ::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR_CATCH));
      return TRUE;
    }
  }
  return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CPDFReaderView::OnMButtonDown(UINT nFlags, CPoint point) {
  switch (GetOperatorType()) {
    case AUTOSCROLL: {
      if (m_bFixedAutoScroll) {
        m_bFixedAutoScroll = FALSE;
      } else {
        m_bFixedAutoScroll = TRUE;
      }
      m_EndPt = point;
    } break;
    default:
      SetOperatorType(AUTOSCROLL);
      m_StartPt = point;
      m_EndPt = point;
      Invalidate();
      SetTimer(AUTOSCROLL_TIMER_ID, 1000 / PER_UPDATE_NUM, 0);
  }

  CView::OnMButtonDown(nFlags, point);
}

void CPDFReaderView::OnDestroy() {
  KillTimer(AUTOSCROLL_TIMER_ID);
  CView::OnDestroy();

  // TODO: Add your message handler code here
}

void CPDFReaderView::OnSetFocus(CWnd* pOldWnd) {
  CView::OnSetFocus(pOldWnd);
  theApp.SetMainFrame(this);
  // TODO: Add your message handler code here
}

void CPDFReaderView::OnCopy() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  if (xfaMenu.CanCopy())
    m_wsCopyOrCutString = xfaMenu.Copy();
}

void CPDFReaderView::OnCut() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  if (xfaMenu.CanCut())
    m_wsCopyOrCutString = xfaMenu.Cut();
}

void CPDFReaderView::OnDelete() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  xfaMenu.Delete();
}

void CPDFReaderView::OnSelectAll() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  xfaMenu.SelectAll();
}

void CPDFReaderView::OnDeSelect() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  if (xfaMenu.CanDeSelect())
    xfaMenu.DeSelect();
}

void CPDFReaderView::OnRedo() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  if (xfaMenu.CanRedo())
    xfaMenu.Redo();
}

void CPDFReaderView::OnUndo() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  if (xfaMenu.CanUndo())
    xfaMenu.Undo();
}

void CPDFReaderView::OnPaste() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  if (m_wsCopyOrCutString.GetLength() > 0)
    xfaMenu.Paste(m_wsCopyOrCutString);
}

void CPDFReaderView::OnBold() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  xfaMenu.Bold();
}

void CPDFReaderView::OnItalic() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  xfaMenu.Italic();
}

void CPDFReaderView::OnUnderLine() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  xfaMenu.Underline();
}

void CPDFReaderView::OnSuperScript() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  xfaMenu.Superscript();
}

void CPDFReaderView::OnSubScript() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  xfaMenu.Subscript();
}

void CPDFReaderView::OnClearStyle() {
  WidgetMenu xfaMenu(m_FocusXFAWidget);
  xfaMenu.ClearStyle();
}

void CPDFReaderView::TriggerPageOpenAction(int index) {
  CReader_Page* pPage = GetDocument()->GetPage(index);
  if (!pPage)
    return;

  PDFPage pdf_page = pPage->GetPDFPage();
  AdditionalAction aa(pdf_page);
  if (!aa.IsEmpty())
    aa.DoJSAction(AdditionalAction::e_TriggerPageOpened);
}

void CPDFReaderView::TriggerPageCloseAction(int index) {
  CReader_Page* pPage = GetDocument()->GetPage(index);
  if (!pPage)
    return;

  PDFPage pdf_page = pPage->GetPDFPage();
  AdditionalAction aa(pdf_page);
  if (!aa.IsEmpty())
    aa.DoJSAction(AdditionalAction::e_TriggerPageClosed);
}

void CPDFReaderView::TriggerPageAction() {
  std::vector<int> open_index_vec;
  std::vector<int> close_index_vec;
  for (auto iter = m_vecPageToDisplay.begin(); iter != m_vecPageToDisplay.end(); iter++) {
    if (!IsInPageDisplayVector(iter->page_index, m_prev_vecPageToDisplay)) {
      open_index_vec.push_back(iter->page_index);
    }
  }

  for (auto iter = m_prev_vecPageToDisplay.begin(); iter != m_prev_vecPageToDisplay.end(); iter++) {
    if (!IsInPageDisplayVector(iter->page_index, m_vecPageToDisplay)) {
      close_index_vec.push_back(iter->page_index);
    }
  }

  if (!open_index_vec.empty()) {
    for (int i = 0; i < open_index_vec.size(); i++) {
      TriggerPageOpenAction(open_index_vec[i]);
    }
  }
  if (!close_index_vec.empty()) {
    for (int i = 0; i < close_index_vec.size(); i++) {
      TriggerPageCloseAction(close_index_vec[i]);
    }
  }
}

bool CPDFReaderView::IsInPageDisplayVector(int index, const std::vector<PageToDisplay>& vec) {
  for (auto iter = vec.begin(); iter != vec.end(); iter++) {
    if (iter->page_index == index)
      return true;
  }

  return false;
}

void CPDFReaderView::CopyPageDisplayData(const std::vector<PageToDisplay>& src, std::vector<PageToDisplay>& dest) {
  dest.clear();

  for (auto iter = src.begin(); iter != src.end(); iter++) {
    dest.push_back(*iter);
  }
}
