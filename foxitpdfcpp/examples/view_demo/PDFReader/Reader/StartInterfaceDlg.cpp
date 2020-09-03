#include "PDFReader/Reader/PDFReader.h"
#include "PDFReader/Reader/StartInterfaceDlg.h"

#define INTERFACE_BKCOLOR_GRAY RGB(121,121,121)
#define INTERFACE_BKCOLOR_WHITE  RGB(255, 255, 255)
#define INTERFACE_TEXTCOLOR_WHITE RGB(255,255,255)
#define INTERFACE_TEXTCOLOR_ORANGE RGB(240, 129, 0)

IMPLEMENT_DYNAMIC(CStartInterfaceDlg, CDialogEx)

CStartInterfaceDlg::CStartInterfaceDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(ID_START_INTERFACE_DIALOG, pParent)
    , m_bExit(false)
    , m_bHasDrawText(false)
    , m_bUseGray(false)
    , m_strFilePath(_T("")) {}

CStartInterfaceDlg::~CStartInterfaceDlg() {}

CString CStartInterfaceDlg::GetFilePath() {
  return m_strFilePath;
}

void CStartInterfaceDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_INTERFACE_RECENT_LIST, m_ctrlRecentList);
  DDX_Control(pDX, IDC_INTERFACE_EDIT_FOLDER, m_ctrlEditFile);
  DDX_Control(pDX, IDC_INTERFACE_OPEN_FILE, m_ctrlOpen);
  DDX_Control(pDX, IDC_INTERFACE_DELETE_RECENT, m_ctrlDelete);
  DDX_Control(pDX, IDC_INTERFACE_BITMAP, m_ctrlLog);
}

BOOL CStartInterfaceDlg::OnInitDialog() {
  CDialogEx::OnInitDialog();

  CRecentFileList* pRecentList = theApp.GetRecentFileList();
  if (pRecentList) {
    for (int iMRU = 0; iMRU < pRecentList->GetSize(); iMRU++) {
      CString path = pRecentList->m_arrNames[iMRU];
      if (path.IsEmpty())
        break;
      m_ctrlRecentList.AddString(path);
    }
  }

  HICON hIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON,24, 24, 0);
  SetIcon(hIcon, false);

  m_LogBitmap.LoadBitmap(m_bUseGray ? IDB_LOG_BITMAP_GRAY : IDB_LOG_BITMAP);
  m_ctrlLog.SetBitmap((HBITMAP) m_LogBitmap);
  m_OpenBitmap.LoadBitmap(m_bUseGray ? IDB_OPEN_BITMAP_GRAY : IDB_OPEN_BITMAP);
  m_ctrlOpen.SetBitmap((HBITMAP) m_OpenBitmap);
  m_DeleteBitmap.LoadBitmap(m_bUseGray ? IDB_DELETE_BITMAP_GRAY : IDB_DELETE_BITMAP);
  m_ctrlDelete.SetBitmap((HBITMAP) m_DeleteBitmap);

  return TRUE;
}

BEGIN_MESSAGE_MAP(CStartInterfaceDlg, CDialogEx)
ON_LBN_SELCHANGE(IDC_INTERFACE_RECENT_LIST, &CStartInterfaceDlg::OnLbnSelchangeRecentFileList)
ON_WM_CTLCOLOR()
ON_STN_CLICKED(IDC_INTERFACE_DELETE_RECENT, &CStartInterfaceDlg::OnStnClickedDeleteRecentList)
ON_STN_CLICKED(IDC_INTERFACE_OPEN_FILE, &CStartInterfaceDlg::OnStnClickedOpenFile)
ON_STN_CLICKED(IDC_INTERFACE_EXIT_APP, &CStartInterfaceDlg::OnStnClickedExitApp)
ON_WM_DROPFILES()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CStartInterfaceDlg::OnLbnSelchangeRecentFileList() {
  int curSel = m_ctrlRecentList.GetCurSel();
  if (m_ctrlRecentList.GetCount() <= curSel || curSel < 0)
    return;
  m_ctrlRecentList.GetText(m_ctrlRecentList.GetCurSel(), m_strFilePath);
  if (m_strFilePath.IsEmpty())
    return;
  CDialogEx::OnOK();
}

HBRUSH CStartInterfaceDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
  HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
  COLORREF clr =m_bUseGray ? INTERFACE_BKCOLOR_GRAY : INTERFACE_BKCOLOR_WHITE;
  pDC->SetBkColor(clr);
  pDC->SetTextColor(m_bUseGray ? INTERFACE_TEXTCOLOR_WHITE : INTERFACE_TEXTCOLOR_ORANGE);
  return ::CreateSolidBrush(clr);
}

void CStartInterfaceDlg::OnStnClickedDeleteRecentList() {
  while (m_ctrlRecentList.GetCount() > 0) {
    m_ctrlRecentList.DeleteString(0);
  }
  CRecentFileList* fileList = theApp.GetRecentFileList();
  for (int i = fileList->GetSize() - 1; i >= 0; i--) {
    fileList->Remove(i);
  }
}

void CStartInterfaceDlg::OnStnClickedOpenFile() {
  GetDlgItemText(IDC_INTERFACE_EDIT_FOLDER, m_strFilePath);
  if (m_strFilePath.IsEmpty()) {
    CFileDialog dialog(TRUE, _T("pdf"), NULL, OFN_HIDEREADONLY, _T("PDF Files(*.pdf)|*.pdf||"));
    if (dialog.DoModal() == IDOK)
      m_strFilePath = dialog.GetPathName();
  }
  if (m_strFilePath.IsEmpty())
    return;
  CDialogEx::OnOK();
}

void CStartInterfaceDlg::OnStnClickedExitApp() {
  m_bExit = true;
  CDialogEx::OnCancel();
}

void CStartInterfaceDlg::OnDropFiles(HDROP hDropInfo) {
  CDialogEx::OnDropFiles(hDropInfo);
  TCHAR pName[4096];
  int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
  if (DropCount > 0) {
    int NameSize = DragQueryFile(hDropInfo, 0, NULL, 0);
    DragQueryFile(hDropInfo, 0, pName, ++NameSize);
    m_strFilePath = pName;
    if (m_strFilePath.IsEmpty() || m_strFilePath.GetLength() < 4 ||
        0 != m_strFilePath.Right(4).CompareNoCase(_T(".pdf")))
      return;
    CDialogEx::OnOK();
  }
}

void CStartInterfaceDlg::OnLButtonDown(UINT nFlags, CPoint point) {
  CDialogEx::OnLButtonDown(nFlags, point);
  PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}

void CStartInterfaceDlg::OnOK() {
  GetDlgItemText(IDC_INTERFACE_EDIT_FOLDER, m_strFilePath);
  if (m_strFilePath.IsEmpty())
    return;
  
  DWORD dwAttrib = GetFileAttributes(m_strFilePath);
  if (INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
    CDialogEx::OnOK();
  }
  else {
    AfxMessageBox(L"File path error", MB_OK | MB_ICONERROR);
  }
}
