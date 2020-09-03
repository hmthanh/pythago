#include "PDFReader/Source/stdafx.h"
#include "DocPropertyDlg.h"
#include "PDFReader.h"
#include "PDFReaderDoc.h"
#include "afxdialogex.h"

// CDocPropertyDlg dialog

IMPLEMENT_DYNAMIC(CDocPropertyDlg, CDialogEx)

CDocPropertyDlg::CDocPropertyDlg(CPDFReaderDoc* doc, CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_PROPERTYDLG, pParent)
    , m_wndCreationDlg(doc)
    , m_wndSecurityDlg(doc)
    , m_wndViewPrefsDlg(doc) {}

CDocPropertyDlg::~CDocPropertyDlg() {}

void CDocPropertyDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_TAB, m_ctrlTab);
}

void CDocPropertyDlg::OnOK() {
  CDialog::OnOK();
}

void CDocPropertyDlg::OnCancel() {
  CDialog::OnCancel();
}

BOOL CDocPropertyDlg::OnInitDialog() {
  CDialog::OnInitDialog();
  // TODO: Add extra initialization here
  m_wndCreationDlg.Create(IDD_PROPERTYDLG_CREATION, this);
  m_wndSecurityDlg.Create(IDD_PROPERTYDLG_SECURITY, this);
  m_wndViewPrefsDlg.Create(IDD_PROPERTYDLG_INITIAL_VIEW, this);
  m_pDialog[0] = &m_wndCreationDlg;
  m_pDialog[1] = &m_wndSecurityDlg;
  m_pDialog[2] = &m_wndViewPrefsDlg;
  m_ctrlTab.InsertItem(0, _T("Creation"));
  m_ctrlTab.InsertItem(1, _T("Security"));
  m_ctrlTab.InsertItem(2, _T("View preference"));
  CRect rc;
  GetClientRect(&rc);
  rc.left += 10;
  rc.top += 31;
  rc.right -= 10;
  rc.bottom -= 45;
  m_wndCreationDlg.MoveWindow(&rc);
  m_wndSecurityDlg.MoveWindow(&rc);
  m_wndViewPrefsDlg.MoveWindow(&rc);

  m_pDialog[0]->ShowWindow(SW_SHOW);
  m_pDialog[1]->ShowWindow(SW_HIDE);
  m_pDialog[2]->ShowWindow(SW_HIDE);
  m_nCurSelTab = 0;
  return TRUE;
}

void CDocPropertyDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) {
  *pResult = 0;
  m_pDialog[m_nCurSelTab]->ShowWindow(SW_HIDE);
  m_nCurSelTab = m_ctrlTab.GetCurSel();
  m_pDialog[m_nCurSelTab]->ShowWindow(SW_SHOW);
}

BEGIN_MESSAGE_MAP(CDocPropertyDlg, CDialogEx)
ON_COMMAND(IDC_PROPERTY_OK, &CDocPropertyDlg::OnOK)
ON_COMMAND(IDC_PROPERTY_CANCEL, &CDocPropertyDlg::OnCancel)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CDocPropertyDlg::OnSelchangeTab)
END_MESSAGE_MAP()

// CDocPropertyDlg message handlers

IMPLEMENT_DYNAMIC(CDocCreationDlg, CDialogEx)

CDocCreationDlg::CDocCreationDlg(CPDFReaderDoc* doc, CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_PROPERTYDLG_CREATION, pParent)
    , m_pReaderDoc(doc) {}

CDocCreationDlg::~CDocCreationDlg() {}

void CDocCreationDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BOOL CDocCreationDlg::OnInitDialog() {
  GetDlgItem(IDC_CREATION_EDIT_FILES)->SetWindowTextW(m_pReaderDoc->GetFilePath());
  CFileStatus fileStatus;
  CFile::GetStatus(m_pReaderDoc->GetFilePath(), fileStatus);
  CString fileSize;
  fileSize.Format(_T("%0.2f MB (%d Bytes)"), fileStatus.m_size / 1024.0f / 1024.0f, fileStatus.m_size);
  GetDlgItem(IDC_CREATION_STATIC_FILE_SIZE)->SetWindowTextW(fileSize);

  InitMetadata(L"Title", IDC_CREATION_EDIT_TITLE);
  InitMetadata(L"Author", IDC_CREATION_EDIT_AUTHOR);
  InitMetadata(L"Subject", IDC_CREATION_EDIT_SUBJECT);
  InitMetadata(L"Keywords", IDC_CREATION_EDIT_KEYWORDS);
  InitMetadata(L"Creator", IDC_CREATION_STATIC_CREATOR);
  InitMetadata(L"Producer", IDC_CREATION_STATIC_PRODUCER);

  InitDateTime(true, IDC_CREATION_STATIC_CREATED);
  InitDateTime(false, IDC_CREATION_STATIC_MODIFIED);

  float width = 0.0f, height = 0.0f;
  if (m_pReaderDoc->GetPDFDocument().IsXFA()) {
    foxit::addon::xfa::XFAPage pdf_page = m_pReaderDoc->GetXFADoc().GetPage(m_pReaderDoc->GetCurPage());
    width = pdf_page.GetWidth();
    height = pdf_page.GetHeight();
  } else {
    PDFPage pdf_page = m_pReaderDoc->GetPDFDocument().GetPage(m_pReaderDoc->GetCurPage());
    width = pdf_page.GetWidth();
    height = pdf_page.GetHeight();
  }
  CString pageSize;
  pageSize.Format(_T("%0.2f x %0.2f inch"), width / 72.0f, height / 72.0f);
  GetDlgItem(IDC_CREATION_STATIC_PAGE_SIZE)->SetWindowTextW(pageSize);
  CString pageCount;
  pageCount.Format(_T("%d"), m_pReaderDoc->GetPageCount());
  GetDlgItem(IDC_CREATION_STATIC_TOTAL_PAGES)->SetWindowTextW(pageCount);
  return CDialogEx::OnInitDialog();
}

void CDocCreationDlg::InitMetadata(const wchar_t* key, int nID) {
  Metadata metadata(m_pReaderDoc->GetPDFDocument());
  foxit::WStringArray wsValues = metadata.GetValues(key);
  CString all_value;
  size_t wsSize = wsValues.GetSize();
  for (size_t i=0; i<wsSize; i++) {
    all_value.Append(wsValues[i]);
  if (i != wsSize-1 && wcscmp(key, L"Keywords") == 0)
      all_value += L", ";
  }
  GetDlgItem(nID)->SetWindowText(all_value);
}

void CDocCreationDlg::InitDateTime(bool bCreation, int nID) {
  Metadata metadata(m_pReaderDoc->GetPDFDocument());
  foxit::DateTime dateTime;
  if (bCreation) {
    dateTime = metadata.GetCreationDateTime();
  } else {
    dateTime = metadata.GetModifiedDateTime();
  }
  CString dateInfo;
  dateInfo.Format(_T("%d-%d-%d %d:%d:%d %s%d'%d'"), dateTime.year, dateTime.month, dateTime.day, dateTime.hour,
                  dateTime.minute, dateTime.second, dateTime.utc_hour_offset >= 0 ? "+" : "-", dateTime.utc_hour_offset,
                  dateTime.utc_minute_offset);
  GetDlgItem(nID)->SetWindowTextW(dateInfo);
}

BEGIN_MESSAGE_MAP(CDocCreationDlg, CDialogEx)
END_MESSAGE_MAP()

// CDocViewerPrefsDlg dialog

IMPLEMENT_DYNAMIC(CDocViewerPrefsDlg, CDialogEx)

CDocViewerPrefsDlg::CDocViewerPrefsDlg(CPDFReaderDoc* doc, CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_PROPERTYDLG_INITIAL_VIEW, pParent)
    , m_pReaderDoc(doc) {}

CDocViewerPrefsDlg::~CDocViewerPrefsDlg() {}

void CDocViewerPrefsDlg::InitUIVisibility(DocViewerPrefs::ViewerPref ui_item, int nID) {
  DocViewerPrefs viewerPrefs(m_pReaderDoc->GetPDFDocument());
  GetDlgItem(nID)->SetWindowText((viewerPrefs.GetUIDisplayStatus(ui_item) ? _T("Yes") : _T("No")));
}

void CDocViewerPrefsDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BOOL CDocViewerPrefsDlg::OnInitDialog() {
  DocViewerPrefs viewerPrefs(m_pReaderDoc->GetPDFDocument());
  InitUIVisibility(DocViewerPrefs::e_HideToolbar, IDC_STATIC_HIDETOOLBAR);
  InitUIVisibility(DocViewerPrefs::e_HideMenubar, IDC_STATIC_HIDEMEN);
  InitUIVisibility(DocViewerPrefs::e_HideWindowUI, IDC_STATIC_HIDEWIN_UI);
  InitUIVisibility(DocViewerPrefs::e_FitWindow, IDC_STATIC_FITWIDTH);
  InitUIVisibility(DocViewerPrefs::e_CenterWindow, IDC_STATIC_CEN_WIN);
  InitUIVisibility(DocViewerPrefs::e_DisplayDocTitle, IDC_STATIC_DOC_TITLE);

  PDFDoc::DisplayMode mode = viewerPrefs.GetNonFullScreenPageMode();
  //PDFDoc::DisplayMode mode = m_pReaderDoc->GetPDFDocument().GetDisplayMode();
  CString displayMode;
  switch (mode) {
    case PDFDoc::e_DisplayUseNone:
      displayMode = "None";
      break;
    case PDFDoc::e_DisplayUseOutlines:
      displayMode = "Outlines panel";
      break;
    case PDFDoc::e_DisplayUseThumbs:
      displayMode = "Thumbnail panel";
      break;
    case PDFDoc::e_DisplayFullScreen:
      displayMode = "Full screen";
      break;
    case PDFDoc::e_DisplayUseOC:
      displayMode = "Optional content group panel";
      break;
    case PDFDoc::e_DisplayUseAttachment:
      displayMode = "Attachment panel ";
      break;
  }
  GetDlgItem(IDC_INI_VIEW_STATIC_PAGE_MODE)->SetWindowText(displayMode);
  GetDlgItem(IDC_INI_VIEW_STATIC_DIRECTION)->SetWindowText(viewerPrefs.GetReadingDirection() ? _T("left-to-right") : _T("right-to-left"));
  DocViewerPrefs::PrintScale print_scale = viewerPrefs.GetPrintScale();
  if(print_scale == DocViewerPrefs::e_PrintScaleNone)
    GetDlgItem(IDC_INI_VIEW_STATIC_PRINT_SCALE)->SetWindowText(_T("None"));
  else
    GetDlgItem(IDC_INI_VIEW_STATIC_PRINT_SCALE)->SetWindowText(_T("AppDefault"));
  CString copies;
  copies.Format(_T("%d"), viewerPrefs.GetPrintCopies());
  GetDlgItem(IDC_INI_VIEW_STATIC_PRINT_COPIES)->SetWindowText(copies);
  return CDialogEx::OnInitDialog();
}

BEGIN_MESSAGE_MAP(CDocViewerPrefsDlg, CDialogEx)
END_MESSAGE_MAP()

// CDocViewerPrefsDlg message handlers

// CDocSecurityDlg dialog

IMPLEMENT_DYNAMIC(CDocSecurityDlg, CDialogEx)

CDocSecurityDlg::CDocSecurityDlg(CPDFReaderDoc* doc, CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_PROPERTYDLG_SECURITY, pParent)
    , m_pReaderDoc(doc) {}

CDocSecurityDlg::~CDocSecurityDlg() {}

void CDocSecurityDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BOOL CDocSecurityDlg::OnInitDialog() {
  GetDlgItem(IDC_PROPERTYDLG_SEC_COM)->EnableWindow(FALSE);

  PDFDoc pdf_doc  = m_pReaderDoc->GetPDFDocument();
  int type = pdf_doc.GetEncryptionType();
  CString encryotType;
  switch (type) {
    case PDFDoc::e_EncryptUnknown:
      encryotType = "Unknown";
      break;
    case PDFDoc::e_EncryptNone:
      encryotType = "No";
      break;
    case PDFDoc::e_EncryptPassword:
      encryotType = "Password";
      break;
    case PDFDoc::e_EncryptCertificate:
      encryotType = "Digital certificate";
      break;
    case PDFDoc::e_EncryptFoxitDRM:
      encryotType = "Foxit DRM";
      break;
    case PDFDoc::e_EncryptCustom:
      encryotType = "Customized";
      break;
    case PDFDoc::e_EncryptRMS:
      encryotType = "Microsoft RMS";
      break;
  }
  GetDlgItem(IDC_PROPERTYDLG_SEC_COM)->SetWindowText(encryotType);

  type = pdf_doc.GetPasswordType();
  CString passwordType;
  switch (type) {
    case PDFDoc::e_PwdInvalid:
      passwordType = "Invalid";
      break;
    case PDFDoc::e_PwdNoPassword:
      passwordType = "No password";
      break;
    case PDFDoc::e_PwdUser:
      passwordType = "User password";
      break;
    case PDFDoc::e_PwdOwner:
      passwordType = "Owner password";
      break;
  }
  GetDlgItem(IDC_SECURITY_STATIC_SEC_METHOD)->SetWindowText(passwordType);
  if (type == PDFDoc::e_PwdUser) {
    GetDlgItem(IDC_SECURITY_STATIC_USER_PWD)->SetWindowTextW(_T("Yes"));
    GetDlgItem(IDC_SECURITY_STATIC_OWN_PWD)->SetWindowTextW(_T("No"));
  } else if (type == PDFDoc::e_PwdOwner) {
    GetDlgItem(IDC_SECURITY_STATIC_USER_PWD)->SetWindowTextW(_T("No"));
    GetDlgItem(IDC_SECURITY_STATIC_OWN_PWD)->SetWindowTextW(_T("Yes"));
  }

  foxit::uint32 permissions = pdf_doc.GetUserPermissions();
  GetDlgItem(IDC_SECURITY_STATIC_PRINT)->SetWindowText(permissions & PDFDoc::e_PermPrint ? _T("Allowed") : _T("None"));
  if (permissions & PDFDoc::e_PermPrintHigh)
    GetDlgItem(IDC_SECURITY_STATIC_PRINT)->SetWindowText(_T("High Resolution Print"));
  GetDlgItem(IDC_SECURITY_STATIC_MOD_DOC)->SetWindowText(type == PDFDoc::e_PwdOwner || permissions & PDFDoc::e_PermModify ? _T("Allowed") : _T("None"));
  GetDlgItem(IDC_SECURITY_STATIC_CON_EXT)->SetWindowText(type == PDFDoc::e_PwdOwner || permissions & PDFDoc::e_PermExtract ? _T("Allowed") : _T("None"));
  GetDlgItem(IDC_SECURITY_STATIC_FILL_IN_FOR)->SetWindowText(type == PDFDoc::e_PwdOwner || permissions & PDFDoc::e_PermFillForm ? _T("Allowed") : _T("None"));
  GetDlgItem(IDC_SECURITY_STATIC_DOC_ASS)->SetWindowText(type == PDFDoc::e_PwdOwner || permissions & PDFDoc::e_PermAssemble ? _T("Allowed") : _T("None"));

  return CDialogEx::OnInitDialog();

}

BEGIN_MESSAGE_MAP(CDocSecurityDlg, CDialogEx)
END_MESSAGE_MAP()

// CDocSecurityDlg message handlers

