
// PDFReaderDoc.cpp : implementation of the CPDFReaderDoc class
//

#include "PDFReader\source\stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PDFReader.h"
#endif

#include "PDFReaderDoc.h"
#include "MainFrm.h"
#include "PDFReader/Framework/ReaderPage.h"
#include "PDFReader/Reader/PasswordDlg.h"
#include "PDFReader/Reader/DocPropertyDlg.h"
#include "PDFReader/Reader/PDFReaderView.h"

#include "PDFReader/Reader/PageGotoButton.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPDFReaderDoc
// The implementation of class FormFillerAssist.
void FormFillerAssist::Refresh(const PDFPage& page, const foxit::RectF* pdfRect)
{
  POSITION pos = m_pViewerDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) m_pViewerDoc->GetNextView(pos);
  if (!pView) return;

  CRect rect;
  pView->DocToWindow(page.GetIndex(), *pdfRect, rect);
  pView->InvalidateRect(rect, FALSE);
}

void CALLBACK MyTimerCallback(HWND hwnd, UINT, UINT_PTR, DWORD)
{
  CPDFReaderView *pView = (CPDFReaderView *)CWnd::FromHandle(hwnd);
  if(pView && pView->GetTimerCallback())
    pView->GetTimerCallback()->OnTimer(1);
}

void FormFillerAssist::Release() {
    POSITION pos = m_pViewerDoc->GetFirstViewPosition();
    CPDFReaderView* pView = (CPDFReaderView*)m_pViewerDoc->GetNextView(pos);
    if (!pView) {
        delete this;
        return;
    }

    pView->SetTimerCallbakc(NULL);
    delete this;
}

#define TIMERID 1
bool  FormFillerAssist::SetTimerCallback(int elapse, interform::TimerCallback* timerFunc, int* timeID)
{
  POSITION pos = m_pViewerDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) m_pViewerDoc->GetNextView(pos);
  if (!pView) return FALSE;

  pView->SetTimerCallbakc(timerFunc);
  *timeID = TIMERID;
  pView->SetTimer(*timeID, elapse, MyTimerCallback);

  return TRUE;
}

bool  FormFillerAssist::KillTimer(int timerID)
{
  POSITION pos = m_pViewerDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) m_pViewerDoc->GetNextView(pos);
  if (!pView) return FALSE;

  pView->KillTimer(TIMERID);

  return TRUE;
}

void FormFillerAssist::FocusGotOnControl(const Control& control, const char* filedValue) {
}

void FormFillerAssist::FocusLostFromControl(const Control& control, const char* filedValue) {
}

// The implementation of class XFADocProvider.
void XFADocProvider::Release() {
  delete this;
}

void XFADocProvider::InvalidateRect(int page_index, const foxit::RectF& rect, InvalidateFlag flag) {
  POSITION pos = m_pViewerDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) m_pViewerDoc->GetNextView(pos);
  if (!pView) return;

  foxit::Matrix matrix = pView->GetPageMatrix(page_index);
  foxit::RectF newRect = rect;
  matrix.TransformRect(newRect);
  if (newRect.bottom<newRect.top) {
    float temp = newRect.bottom;
    newRect.bottom = newRect.top;
    newRect.top = temp;
  }
  pView->InvalidateRect(CRect(int(newRect.left), int(newRect.top), int(newRect.right), int(newRect.bottom)), FALSE);
}

void XFADocProvider::DisplayCaret(int page_index, bool is_visible, const foxit::RectF& rect) {
  POSITION pos = m_pViewerDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) m_pViewerDoc->GetNextView(pos);
  if (!pView) return;

  pView->DisplayCaret(page_index, is_visible, rect);
}

void XFADocProvider::ExportData(const XFADoc& doc, const foxit::WString& file_path) {
  return;
}

int XFADocProvider::GetCurrentPage(const XFADoc& doc) {
  return m_pViewerDoc->GetCurPage();
}

bool XFADocProvider::GetPopupPos(int page_index, float min_popup, float max_popup, const foxit::RectF& rect_widget, foxit::RectF& rect_popup) {
  POSITION pos = m_pViewerDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) m_pViewerDoc->GetNextView(pos);
  if (!pView) return FALSE;

  CRect rcClient;    
  pView->GetClientRect(rcClient);

  CRect rcShowRect;
  rcShowRect = pView->GetPageRect(page_index);
  rcShowRect.IntersectRect(rcShowRect,rcClient);

  foxit::RectF newRect;
  pView->WindowToDoc(page_index, rcShowRect, newRect);
  

  int top_length = 0;
  int bottom_length = 0;
  int actaul_length = 0;
  bool show_upside =true;
  float fPoupHeight = 0;
  top_length = (int)(newRect.top - rect_widget.top);
  bottom_length = (int)(rect_widget.bottom - newRect.bottom); 

  if (rect_widget.right > newRect.right) 
  {
    float fwidth = rect_widget.Width();
    rect_popup.left -= rect_widget.right - newRect.right; 
    rect_popup.right -= rect_widget.right - newRect.right;
  }
  if (top_length <= 0 && bottom_length <= 0)
  {
    return false;
  }

  if (top_length <= 0)
  {
    actaul_length = bottom_length;
  }
  else if(bottom_length <= 0)
  {
    actaul_length = top_length;
    show_upside = false;
  }
  else if (top_length > bottom_length )
  {
    actaul_length = top_length;
    show_upside = false;
  }
  else 
  {
    actaul_length = bottom_length;
  }


  if (actaul_length<min_popup)
  {
    fPoupHeight = min_popup;
  }
  else if (actaul_length > max_popup)
  {
    fPoupHeight = max_popup;
  }
  else
  {
    fPoupHeight = actaul_length;
  }

  if (!show_upside)
  {
    rect_popup.top = fabs(rect_widget.bottom - rect_widget.top);
    rect_popup.bottom = rect_popup.top + fPoupHeight;
  }
  else
  {
    rect_popup.top = -fPoupHeight;
    rect_popup.bottom = rect_popup.top + fPoupHeight;
  }

  return TRUE;
}

foxit::WString XFADocProvider::GetTitle(const XFADoc& doc) {
  return L"title";
}

void XFADocProvider::SetFocus(XFAWidget& xfaWidget) {
  POSITION pos = m_pViewerDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) m_pViewerDoc->GetNextView(pos);
  if (!pView) return;
  if (xfaWidget.IsEmpty()) return;
  XFAPage xfaPage = xfaWidget.GetXFAPage();
  int pageCount = pView->GetDocument()->GetXFADoc().GetPageCount();
  for (int i = 0; i < pageCount; i++) {
    if (xfaPage == pView->GetDocument()->GetXFADoc().GetPage(i) && i != pView->GetCurVisiblePageIndex()) {
      pView->SetVisiblePageByIndex(i);
      pView->Invalidate();
    }
  }

  pView->SetFocusXFAWidget(xfaWidget);
}

void XFADocProvider::GotoURL(const XFADoc& doc, const foxit::WString& url) {
  POSITION pos = m_pViewerDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) m_pViewerDoc->GetNextView(pos);
  if (!pView) return;

  ShellExecute(*(pView->GetParent()), L"Open", (LPCWSTR)url, NULL, NULL, SW_SHOW);
}

void XFADocProvider::ImportData(const XFADoc& doc, const foxit::WString& file_path) {
  return;
}

bool XFADocProvider::PopupMenu(int page_index, const foxit::PointF& point_popup) {
  POSITION pos = m_pViewerDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) m_pViewerDoc->GetNextView(pos);
  if (!pView) return FALSE;

  CMenu menu;
  menu.CreatePopupMenu();

  menu.AppendMenu(MF_STRING, ID_WM_XFA_CUT, L"Cut");
  menu.AppendMenu(MF_STRING, ID_WM_XFA_COPY, L"Copy");
  menu.AppendMenu(MF_STRING, ID_WM_XFA_PASTE, L"Paste");
  menu.AppendMenu(MF_STRING, ID_WM_XFA_DELETE, L"Delete");
  menu.AppendMenu(MF_STRING, ID_WM_XFA_SELECTALL, L"SelectAll");
  menu.AppendMenu(MF_STRING, ID_WM_XFA_DESELECT, L"DeSelect");
  menu.AppendMenu(MF_STRING, ID_WM_XFA_UNDO, L"Undo");
  menu.AppendMenu(MF_STRING, ID_WM_XFA_REDO, L"Redo");

  CMenu menuStyle;
  menuStyle.CreatePopupMenu();
  menuStyle.AppendMenu(MF_STRING, ID_WM_XFA_TEXTSTYLE_BOLD, L"Bold");
  menuStyle.AppendMenu(MF_STRING, ID_WM_XFA_TEXTSTYLE_ITALIC, L"Italic");
  menuStyle.AppendMenu(MF_STRING, ID_WM_XFA_TEXTSTYLE_UNDERLINE, L"Underline");
  menuStyle.AppendMenu(MF_STRING, ID_WM_XFA_TEXTSTYLE_SUPERSCRIPT, L"Superscript");
  menuStyle.AppendMenu(MF_STRING, ID_WM_XFA_TEXTSTYLE_SUBSCRIPT, L"Subscript");
  menuStyle.AppendMenu(MF_STRING, ID_WM_XFA_TEXTSTYLE_CLEARSTYLE, L"Clear Style");

  menu.InsertMenu(5, MF_BYPOSITION|MF_POPUP|MF_STRING, (UINT)menuStyle.m_hMenu, L"Text Style");

  CPoint pointDevice;
  pView->DocToWindow(page_index, point_popup, pointDevice);

  menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pointDevice.x, pointDevice.y, pView);

  menu.DestroyMenu();
  menuStyle.DestroyMenu();
  return TRUE;
}

void XFADocProvider::Print(const XFADoc& doc, int start_page_index, int end_page_index, foxit::uint32 options) {
  if (options && DocProviderCallback::e_PrintOptionShowDialog) {
    CPrintDialog dlg(FALSE, PD_PAGENUMS | PD_USEDEVMODECOPIES);
    dlg.m_pd.nMinPage = dlg.m_pd.nFromPage = 1;
    dlg.m_pd.nMaxPage = dlg.m_pd.nToPage = end_page_index + 1;
    if (dlg.DoModal() != IDOK) return;
  }

  bool is_static_doc = false;
  if (doc.GetType() == foxit::addon::xfa::XFADoc::e_Static)
    is_static_doc = true;

  PDFDoc pdfdoc = m_pViewerDoc->GetPDFDocument();

  for (int i = start_page_index; i <= end_page_index; i++) {
    XFAPage xfa_page;
    PDFPage pdf_page;
    float width = 0.0f;
    float height = 0.0f;

    if (is_static_doc) {
      pdf_page = pdfdoc.GetPage(i);
      width = pdf_page.GetWidth();
      height = pdf_page.GetHeight();
     }
    else {
      xfa_page = ((XFADoc)doc).GetPage(i);
      width = xfa_page.GetWidth();
      height = xfa_page.GetHeight();
    }

    HDC hdc_print = NULL;  // printer DC handle
    char dev_string[120];  // An array for WIN.INI data
    char *printer = NULL, *driver = NULL;  // Printer name and driver name
    char *port = NULL;  // Port name

    GetProfileStringA("windows", "device", ",,,", dev_string, 120);

    if ((printer = strtok(dev_string, (const char *)",")) && (driver = strtok((char *)NULL, (const char *)", ")) &&
      (port = strtok((char *)NULL, (const char *)", "))) {
        hdc_print = CreateDCA(driver, printer, port, NULL);
    }

    if (!hdc_print) {
      AfxMessageBox(_T("Create Print HDC ERROR!"));
      continue;
    }

    CString strDocTitle = m_pViewerDoc->GetTitle();
    strDocTitle = strDocTitle.Mid(0, strDocTitle.GetLength() - 4);

    CString newDocTitle;
    newDocTitle.Format(_T("%s%d.pdf"), (const TCHAR*)strDocTitle, i);

    DOCINFO doc_info;
    ZeroMemory(&doc_info, sizeof(DOCINFOA));
    doc_info.cbSize = sizeof(DOCINFOA);
    doc_info.lpszDocName = newDocTitle;
    doc_info.lpszOutput = L"";
    doc_info.fwType = 0;

    // Begin a print job by calling the StartDoc function.
    StartDoc(hdc_print, &doc_info);
    // Inform the driver that the application is about to begin sending data.
    StartPage(hdc_print);

    float device_width = (float)GetDeviceCaps(hdc_print, HORZRES);
    float device_height = (float)GetDeviceCaps(hdc_print, VERTRES);
    float x_scale = device_width / width;
    float y_scale = device_height / height;

    float scale = x_scale < y_scale ? x_scale : y_scale;
    float x_offset = 0.0;
    float y_offset = 0.0;
    if (x_scale < y_scale) {
      y_offset = (device_height - scale * height) / 2;
      device_height = scale * height;
    } else {
      x_offset = (device_width - scale * width) / 2;
      device_width = scale * width;
    }

    RECT rect = {(LONG)x_offset, (LONG)y_offset, (LONG)(device_width + x_offset), (LONG)(device_height + y_offset)};
    foxit::Matrix matrix;

    if (!is_static_doc) {
      matrix = xfa_page.GetDisplayMatrix(rect.left, rect.top, (int)device_width, (int)device_height,
      e_Rotation0);
    } else {
      matrix = pdf_page.GetDisplayMatrix(rect.left, rect.top, (int)device_width, (int)device_height,
      e_Rotation0);
    }

    HBRUSH hBrush = CreateSolidBrush(RGB(0xff, 0xff, 0xff));
    FillRect(hdc_print, &rect, hBrush);
    DeleteObject(hBrush);

    Renderer render_print(hdc_print);

    if (!is_static_doc) {
      render_print.StartRenderXFAPage(xfa_page, matrix, FALSE, NULL);
    } else {
      render_print.StartRender(pdf_page, matrix, NULL);
    }
    // Inform the spooler that the page is complete.
    EndPage(hdc_print);
    // Inform the driver that document has ended.
    EndDoc(hdc_print);
    // Release the device context.
    DeleteDC(hdc_print);
  }
}

void XFADocProvider::SetCurrentPage(const XFADoc& doc, int current_page_index) {
  POSITION pos = m_pViewerDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) m_pViewerDoc->GetNextView(pos);
  if (!pView) return;
  pView->SetVisiblePageByIndex(current_page_index);
  pView->Invalidate();
}

foxit::ARGB XFADocProvider::GetHighlightColor(const XFADoc& doc) {
  return 0x50FF0000;
}

bool XFADocProvider::SubmitData(const XFADoc& doc, const foxit::WString& target, SubmitFormat format, TextEncoding text_encoding, const foxit::WString& content) {
  CString strMessage;
  strMessage.Format(_T("The target is : \r\n%s"), (const wchar_t*)target);
  AfxMessageBox(strMessage);
  return TRUE;
}

void XFADocProvider::PageViewEvent(int page_index, foxit::addon::xfa::DocProviderCallback::PageViewEventType page_event) {
  POSITION pos = m_pViewerDoc->GetFirstViewPosition();
  CPDFReaderView* pView = (CPDFReaderView*) m_pViewerDoc->GetNextView(pos);
  if (!pView) return;

  pView->GetDocument()->UpdatePDFPages(pView->m_nLogPixelX, pView->m_nLogPixelY, pView->m_Rotate, true);
  pView->InitScrollSize(pView->m_nLogPixelX, pView->m_nLogPixelY);
  pView->ResetCurrentPageIndex();
}

void XFADocProvider::WidgetEvent(const XFAWidget& xfa_widget,WidgetEventType widget_event_type)
{
  return;
}

void XFADocProvider::SetChangeMark(const XFADoc& doc) {
  m_pViewerDoc->SetModifiedFlag(TRUE);
}

IMPLEMENT_DYNCREATE(CPDFReaderDoc, CDocument)

BEGIN_MESSAGE_MAP(CPDFReaderDoc, CDocument)
  ON_COMMAND(ID_DOCUMENT_PROPERTY, &CPDFReaderDoc::OnDocumentProperty)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CPDFReaderDoc, CDocument)
END_DISPATCH_MAP()

static const IID IID_IPDFReader =
{ 0x935093B6, 0x4FDF, 0x4236, { 0xB0, 0x98, 0xB, 0xFC, 0x28, 0x67, 0x8E, 0x81 } };

BEGIN_INTERFACE_MAP(CPDFReaderDoc, CDocument)
  INTERFACE_PART(CPDFReaderDoc, IID_IPDFReader, Dispatch)
END_INTERFACE_MAP()

// CPDFReaderDoc construction/destruction

CPDFReaderDoc::CPDFReaderDoc()
    : m_bLoadDocument(FALSE)
    , m_pFormFillerAssit(NULL)
    , m_pXFADocProvider(NULL)
    , m_csFilePath(_T(""))
    , m_bInitPages(FALSE)
    , m_nPageSpace(DEFAULT_PAGESPACE)
    , m_nTotalPage(0)
    , m_nPageShadowWidth(4)
    , m_fRealHeight(0.0f)
    , m_fRealWidth(0.0f)
    , m_nCurPageIndex(0)
    , m_bDynamicXFA(FALSE)
    , m_bModified(FALSE) {
  // TODO: add one-time construction code here
  EnableAutomation();
  AfxOleLockApp();
}

CPDFReaderDoc::~CPDFReaderDoc()
{
  for (int i = 0; i < m_pPageList.GetSize(); i++) {
    delete m_pPageList.GetAt(i);
  }
  AfxOleUnlockApp();
}

BOOL CPDFReaderDoc::LoadPDFDocument(LPCWSTR lpwsFilePath) {
  m_csFilePath = lpwsFilePath;
  foxit::WString wsFilePath = lpwsFilePath;
  // Create PDF document
  try {
    m_PDFDoc = PDFDoc(lpwsFilePath);
  } catch (const foxit::Exception& e) {
    AfxMessageBox(CString((const char*)e.GetMessage()), MB_OK | MB_ICONERROR);
    m_PDFDoc = PDFDoc(foxit::FS_HANDLE(NULL));
    if (!theApp.IsHadOpenDocumentSucessful())
      return TRUE;
    return FALSE;
  }

  // Load Document
  foxit::ErrorCode error_code = m_PDFDoc.Load("");

  BOOL bHasAskPassword = FALSE;
  CString password;
  while (error_code == foxit::e_ErrPassword) {
    CPasswordDlg passwordDlg(bHasAskPassword);
    bHasAskPassword = TRUE;
    if(passwordDlg.DoModal()!= IDOK)
      break;
    else {
      password = passwordDlg.GetPassword();
      error_code = m_PDFDoc.LoadW(password.GetBuffer(password.GetLength()));
    }
  }

  if (error_code != foxit::e_ErrSuccess) {
    m_PDFDoc = PDFDoc(foxit::FS_HANDLE(NULL));
    AfxMessageBox(CString(GetErrorMessage(error_code)), MB_OK | MB_ICONERROR);
    if (!theApp.IsHadOpenDocumentSucessful())
      return TRUE;
    return FALSE;
  }

  m_csPassword = password;
  m_bLoadDocument = TRUE;

  bool has_xfa_right = foxit::common::Library::HasModuleLicenseRight(foxit::common::e_ModuleNameXFA);
  bool is_xfa = FALSE;
  XFADoc::Type xfaDocType = (XFADoc::Type)-1;
  try {
    is_xfa = m_PDFDoc.IsXFA();
    if (is_xfa) {
      //has_xfa_right = TRUE;
      if (!has_xfa_right) {
        m_PDFDoc = PDFDoc(foxit::FS_HANDLE(NULL));
        m_bLoadDocument = FALSE;
        AfxMessageBox(CString("You are not authorized to use \"XFA\" add-on module, please contact us for upgrading your license."), MB_OK | MB_ICONERROR);
        if (!theApp.IsHadOpenDocumentSucessful())
          return TRUE;

        return FALSE;
      }
      m_pXFADocProvider = new XFADocProvider(this);
      m_XFADoc = XFADoc(m_PDFDoc, m_pXFADocProvider);
      m_XFADoc.StartLoad(NULL);
      xfaDocType = m_XFADoc.GetType();
    }
  } catch (foxit::Exception e) {
    if (e.GetErrCode() != foxit::e_ErrInvalidLicense && e.GetErrCode() != foxit::e_ErrNoXFAModuleRight) {
      AfxMessageBox(CString(GetErrorMessage(e.GetErrCode())), MB_OK | MB_ICONERROR);
    }
    is_xfa = FALSE;
  }

  if ((is_xfa && xfaDocType == XFADoc::e_Static) || !is_xfa) {
    if(m_PDFDoc.HasForm()) {
      if(!m_pFormFillerAssit) m_pFormFillerAssit = new FormFillerAssist(this);
        m_Form = Form(m_PDFDoc);
        m_FormFiller = Filler(m_Form, m_pFormFillerAssit);
        m_FormFiller.HighlightFormFields(TRUE);
    }
    m_PDFDoc.DoJSOpenAction();
  } else {
    m_bDynamicXFA = TRUE;
  }

  return TRUE;
}

BOOL CPDFReaderDoc::ReLoadDocument() {
  foxit::WString wsFilePath = m_csFilePath;
  m_bLoadDocument = FALSE;
  // Create PDF document
  try {
    m_PDFDoc = PDFDoc(wsFilePath);
  } catch (const foxit::Exception& e) {
    AfxMessageBox(CString((const char*)e.GetMessage()), MB_OK | MB_ICONERROR);
    return FALSE;
  }

  // Load Document
  foxit::ErrorCode error_code = m_PDFDoc.LoadW(m_csPassword.GetBuffer(m_csPassword.GetLength()));

  if (error_code != foxit::e_ErrSuccess) {
    m_PDFDoc = PDFDoc(foxit::FS_HANDLE(NULL));
    AfxMessageBox(CString(GetErrorMessage(error_code)), MB_OK | MB_ICONERROR);
    return FALSE;
  }
  m_bLoadDocument = TRUE;

  bool is_xfa = FALSE;
  XFADoc::Type xfaDocType = (XFADoc::Type)-1;
  try {
    is_xfa = m_PDFDoc.IsXFA();
    if (is_xfa) {
      m_XFADoc = XFADoc(NULL);
      m_pXFADocProvider = NULL;
      m_pXFADocProvider = new XFADocProvider(this);
      m_XFADoc = XFADoc(m_PDFDoc, m_pXFADocProvider);
      m_XFADoc.StartLoad(NULL);
      xfaDocType = m_XFADoc.GetType();
    }
  } catch (foxit::Exception e) {
    if (e.GetErrCode() != foxit::e_ErrInvalidLicense && e.GetErrCode() != foxit::e_ErrNoXFAModuleRight) {
      AfxMessageBox(CString(GetErrorMessage(e.GetErrCode())), MB_OK | MB_ICONERROR);
    }
    is_xfa = FALSE;
  }

  if ((is_xfa && xfaDocType == XFADoc::e_Static) || !is_xfa) {
    if(m_PDFDoc.HasForm()) {
      m_FormFiller = Filler(); 
      m_pFormFillerAssit = NULL;
      m_pFormFillerAssit = new FormFillerAssist(this);
      m_Form = Form(m_PDFDoc);
      m_FormFiller = Filler(m_Form, m_pFormFillerAssit);
      m_FormFiller.HighlightFormFields(TRUE);
    }
    m_PDFDoc.DoJSOpenAction();
  } else {
    m_bDynamicXFA = TRUE;
  } 

  return TRUE;
}

BOOL CPDFReaderDoc::UpdatePDFPages(int nLogPixelX, int nLogPiexlY, Rotation rotate, bool need_update_page_list) {
  m_fRealHeight = 0.0f;
  m_fRealWidth = 0.0f;
  if (!m_bInitPages || need_update_page_list) {
    for (int i = 0; i < m_pPageList.GetSize(); i++) {
      delete m_pPageList.GetAt(i);
    }
    m_pPageList.RemoveAll();
    m_fRealHeight = 0;
    m_fRealWidth = 0;
    if (isDynamicXFA())
      m_nTotalPage = m_XFADoc.GetPageCount();
    else
      m_nTotalPage = m_PDFDoc.GetPageCount();
  }
  for (int i = 0; i < m_nTotalPage; i++) {
    CReader_Page* pReaderPage = (m_bInitPages && !need_update_page_list) ? m_pPageList.GetAt(i) : new CReader_Page();
    PDFPage pdf_page;
    XFAPage xfa_page;
    float fPageWidth = 0;
    float fPageHeight = 0;

    if (isDynamicXFA()) {
      xfa_page = m_XFADoc.GetPage(i);
      fPageWidth = xfa_page.GetWidth();
      fPageHeight = xfa_page.GetHeight();
    }
    else {
      pdf_page = m_PDFDoc.GetPage(i);
      if (pdf_page.IsEmpty()) {
        fPageWidth = 0;
        fPageHeight = 0;
      } else {
        fPageWidth = pdf_page.GetWidth();
        fPageHeight = pdf_page.GetHeight();
      }
  }

  float nWidth = fPageWidth / 72.0f * nLogPixelX + 0.5f;
  float nHeight = fPageHeight / 72.0f * nLogPiexlY + 0.5f;
  if (rotate == e_Rotation90 || rotate == e_Rotation270) {
    m_fRealHeight = m_fRealHeight + nWidth;
    if (nHeight > m_fRealWidth)
      m_fRealWidth = nHeight;
  } else {
    m_fRealHeight = m_fRealHeight + nHeight;
    if (nWidth > m_fRealWidth)
      m_fRealWidth = nWidth;
  }
  pReaderPage->SetPageHeight(nHeight);
  pReaderPage->SetPageWidth(nWidth);
  pReaderPage->SetPageTotalHeightWithOutSpace(m_fRealHeight);
  pReaderPage->SetPDFPage(pdf_page);

  try {
    pReaderPage->SetXFAPage(xfa_page);
  } catch (foxit::Exception&) {}
    pReaderPage->SetPageIndex(i);
    if (!m_bInitPages || need_update_page_list) {
      m_pPageList.Add(pReaderPage);
    }
  }
  m_bInitPages = TRUE;
  return TRUE;
}

void CPDFReaderDoc::FindVisiblePage(float StartPos, float EndPos, int& StartPage, int& EndPage, float zoom) {
  for (int i = 0; i < m_nTotalPage; i++) {
    CReader_Page* pReaderPage = (CReader_Page*)m_pPageList.GetAt(i);
    float fPageTotalHeight = pReaderPage->GetPageTotalHeightWithSpace(zoom);
    if (fPageTotalHeight - StartPos > 1) {
      StartPage = pReaderPage->GetPageIndex();
      if (i != 0) {
        CReader_Page* pReaderPage2 = (CReader_Page*)m_pPageList.GetAt(i - 1);
        StartPos = pReaderPage2->GetPageTotalHeightWithSpace(zoom);
      } else
        StartPos = 0;
      for (int j = i; j < m_nTotalPage; j++) {
        CReader_Page* pReaderPage3 = (CReader_Page*)m_pPageList.GetAt(j);
        float fPageTotalHeight3 = pReaderPage3->GetPageTotalHeightWithSpace(zoom);
        if (fPageTotalHeight3 + GetPageSpace() > EndPos ) {
          EndPage = pReaderPage3->GetPageIndex();

          break;
        } else {
          EndPage = m_nTotalPage - 1;
        }
      }
      break;
    }
  }

  if (EndPage < StartPage) {
    EndPage = m_nTotalPage - 1;
  }
}

PDFDoc CPDFReaderDoc::GetPDFDocument() {
  return m_PDFDoc;
}

BOOL CPDFReaderDoc::HasLoadDocument() {
  return m_bLoadDocument;
}

CString CPDFReaderDoc::GetFilePath() {
  return m_strPathName;
}

void CPDFReaderDoc::UpdateCurPage(int index) {
  m_nCurPageIndex = index;
}

int CPDFReaderDoc::GetCurPage() {
  return m_nCurPageIndex;
}

void CPDFReaderDoc::Save() {
  if (m_FormFiller.IsEmpty() == false)
    m_FormFiller.KillFocus();
  //[make up temporary file name]
  CString szTempSaveFile = m_csFilePath;
  int ret = szTempSaveFile.ReverseFind(L'\\');
  if (ret != -1) {
    szTempSaveFile.Insert(ret + 1, L"~$");
  }

  foxit::WString wsSavePath = szTempSaveFile.GetBuffer();
  szTempSaveFile.ReleaseBuffer();
  bool bSavePro = m_PDFDoc.SaveAs(wsSavePath, PDFDoc::e_SaveFlagNormal);
  if (bSavePro) {
    bSavePro = CopyFile(szTempSaveFile.GetBuffer(), m_csFilePath, FALSE) != 0;
    szTempSaveFile.ReleaseBuffer();
    if (!bSavePro) {

      AfxMessageBox(_T("Save Failed!"));
    }
    else {
     if(!DeleteFile(szTempSaveFile))
       AfxMessageBox(_T("Save Failed!"));
    }
  }

  // reload document handle and update view.
  if (ReLoadDocument()) {
    POSITION pos = GetFirstViewPosition();
    CPDFReaderView* pView = (CPDFReaderView*)GetNextView(pos);
    if (!pView) return;
    
    UpdatePDFPages(pView->m_nLogPixelX, pView->m_nLogPixelY, pView->m_Rotate, true);
    pView->Invalidate();
  }
}

void CPDFReaderDoc::SaveAs() {
  CFileDialog filedlg(FALSE,_T("pdf"),_T("Document"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("PDF files(*.pdf)||"));
  if (filedlg.DoModal() == IDOK) {
    CString path = filedlg.GetPathName();

    foxit::WString wsSavePath = path.GetBuffer();
    path.ReleaseBuffer();
    bool bSavePro = m_PDFDoc.SaveAs(wsSavePath, PDFDoc::e_SaveFlagNormal);
    if (bSavePro) {
      if (!bSavePro) {
        AfxMessageBox(_T("Save Failed!"));
      }
    }
  }
}

int CPDFReaderDoc::GetPageCount() {
  return m_nTotalPage;
}

void CPDFReaderDoc::UpdatePageCount(){
  if (isDynamicXFA())
    m_nTotalPage = GetXFADoc().GetPageCount();
  else
    m_nTotalPage = GetPDFDocument().GetPageCount();
}

CReader_Page * CPDFReaderDoc::GetPage(int nIndex) {
  if (nIndex < 0 || nIndex >= m_pPageList.GetCount())
    return NULL;
  return m_pPageList.GetAt(nIndex);
}

float CPDFReaderDoc::GetRealHeight(float zoom) {
  return m_fRealHeight* zoom + (m_nTotalPage + 1)* m_nPageSpace;
}

float CPDFReaderDoc::GetRealWidth(float zoom) {
  return m_fRealWidth* zoom + 2*m_nPageSpace;
}

int CPDFReaderDoc::GetPageShadowWidth() {
  return m_nPageShadowWidth;
}

int CPDFReaderDoc::GetPageSpace() {
  return m_nPageSpace;
}

BOOL CPDFReaderDoc::OnOpenDocument(LPCTSTR lpszPathName) {
  //String strFilePath = String::CreateFromWideString(lpszPathName);
  //strFilePath.ToUTF8();
  theApp.AddDocument(this);
  return LoadPDFDocument(lpszPathName);
}

void CPDFReaderDoc::OnCloseDocument() {
  if (!m_PDFDoc.IsEmpty()) {
    AdditionalAction additionalAction(m_PDFDoc);
    additionalAction.DoJSAction(AdditionalAction::e_TriggerDocWillClose);

    if (m_pFormFillerAssit) {
        m_pFormFillerAssit = NULL;
    }

    m_FormFiller = Filler();
  }
  CDocument::OnCloseDocument();
}

// CPDFReaderDoc serialization

void CPDFReaderDoc::Serialize(CArchive& ar) {
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPDFReaderDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
  // Modify this code to draw the document's data
  dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

  CString strText = _T("TODO: implement thumbnail drawing here");
  LOGFONT lf;

  CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
  pDefaultGUIFont->GetLogFont(&lf);
  lf.lfHeight = 36;

  CFont fontDraw;
  fontDraw.CreateFontIndirect(&lf);

  CFont* pOldFont = dc.SelectObject(&fontDraw);
  dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
  dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPDFReaderDoc::InitializeSearchContent()
{
  CString strSearchContent;
  // Set search contents from document's data.
  // The content parts should be separated by ";"

  // For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
  SetSearchContent(strSearchContent);
}

void CPDFReaderDoc::SetSearchContent(const CString& value)
{
  if (value.IsEmpty())
  {
    RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
  }
  else
  {
    CMFCFilterChunkValueImpl *pChunk = NULL;
    ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
    if (pChunk != NULL)
    {
      pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
      SetChunkValue(pChunk);
    }
  }
}

#endif // SHARED_HANDLERS

// CPDFReaderDoc diagnostics

#ifdef _DEBUG
void CPDFReaderDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CPDFReaderDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

// CPDFReaderDoc commands
void CPDFReaderDoc::OnDocumentProperty() {
  // TODO: Add your command handler code here
  if (!HasLoadDocument())
    return;
  CDocPropertyDlg dlg(this);
  dlg.DoModal();
}

BOOL CPDFReaderDoc::IsModified() {
  return m_bModified;
}

void CPDFReaderDoc::SetModifiedFlag(BOOL bModified/* = TRUE*/) {
  if (bModified != m_bModified) {
    m_bModified = bModified;
  }
}

