#include "PDFReader/Source/stdafx.h"
#include "FindDlg.h"
#include "PDFReader.h"
#include "PDFReaderDoc.h"
#include "PDFReaderView.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(FindDlg, CDialog)

FindDlg::FindDlg(CPDFReaderView* pView, CWnd* pParent /* = NULL*/)
    : CDialog(IDD_FINDDLG, pParent)
    , m_pPDFReaderView(pView)
    , m_bMatchCase(FALSE)
    , m_bWholeWord(FALSE)
    , m_strFindWhat(_T(""))
    , m_nDirection(-1)
    , m_nCurPageIndex(-1)
    , m_nCurFlags(TextSearch::e_SearchNormal | TextSearch::e_SearchConsecutive)
    , m_strLastKey(_T(""))
    , m_nLastDirection(-1)
    , m_nLastFindCharIndex(-1)
    , m_nLastFlags(TextSearch::e_SearchNormal | TextSearch::e_SearchConsecutive) {
  if (pView)
    m_nCurPageIndex = pView->GetCurVisiblePageIndex();
}

FindDlg::~FindDlg() {}

void FindDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT_FINDTEXT, m_strFindWhat);
  DDX_Radio(pDX, IDC_RADIO_DOWN, m_nDirection);
  DDX_Check(pDX, IDC_CHECK_MATCHWHOLE, m_bWholeWord);
  DDX_Check(pDX, IDC_CHECK_MATCHCASE, m_bMatchCase);
}

BEGIN_MESSAGE_MAP(FindDlg, CDialog)
  ON_COMMAND(IDC_BUTTON_CANCLE, &FindDlg::OnCancel)
  ON_EN_CHANGE(IDC_EDIT_FINDTEXT, &FindDlg::OnEnChangeEditFindtext)
  ON_BN_CLICKED(IDC_BUTTON_FIND_NEXT, &FindDlg::OnBnClickedButtonFindNext)
END_MESSAGE_MAP()

// FindDlg message handlers
void FindDlg::OnOk() {
  UpdateData(TRUE);
  Find();
}

BOOL FindDlg::OnInitDialog() {
  CDialog::OnInitDialog();
  SetWindowText(_T("Find"));
   ((CButton *) GetDlgItem(IDC_RADIO_DOWN))->SetCheck(1);
  ((CButton *) GetDlgItem(IDC_CHECK_MATCHWHOLE))->SetCheck(1);
  //GetDlgItem(IDC_BUTTON_FIND_NEXT)->SetFocus();
  m_font.CreateFont(20, 0, 0, 0, FW_LIGHT, FALSE,
                    FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                    DEFAULT_PITCH | FF_SWISS, _T("Helvetica"));
  ((CEdit*)GetDlgItem(IDC_EDIT_FINDTEXT))->SetFont(&m_font);
  GetDlgItem(IDC_EDIT_FINDTEXT)->SetFocus();
  return FALSE;
}

BOOL FindDlg::PreTranslateMessage(MSG* pMsg) {
  if (WM_KEYFIRST == WM_KEYDOWN)  // <= pMsg->message && pMsg->message <= WM_KEYLAST
    if (pMsg->wParam == VK_RETURN) {
      HWND hWnd = ::GetFocus();
      int m_nID = ::GetDlgCtrlID(hWnd);
      if (m_nID == IDC_EDIT_FINDTEXT) {
        UpdateData(TRUE);

		Find();

		m_strLastKey = m_strFindWhat;
		m_nLastFlags = m_nCurFlags;
		m_nLastDirection = m_nDirection;

        return TRUE;
      }
    }

  return CDialog::PreTranslateMessage(pMsg);
}

void FindDlg::OnCancel() {
  m_pPDFReaderView->CleanSearch();
  m_pPDFReaderView->Invalidate();
  CDialog::OnCancel();
}

void FindDlg::Find() {
  m_nCurFlags = TextSearch::e_SearchNormal | TextSearch::e_SearchConsecutive;
  if (m_bMatchCase)
    m_nCurFlags |= TextSearch::e_SearchMatchCase;
  if (m_bWholeWord)
    m_nCurFlags |= TextSearch::e_SearchMatchWholeWord;

  int nFindPageIndex = -1;
  int nRectIndex = -1;
  bool bFind = false;

  if (m_strFindWhat.IsEmpty())
    return;
  if (m_strLastKey == m_strFindWhat && m_nCurFlags == m_nLastFlags && m_nLastDirection == m_nDirection) {
    bFind = (m_nDirection == 0) ? m_TextSearch.FindNext() : m_TextSearch.FindPrev();
  } else {
    m_TextSearch = TextSearch();
    m_pPDFReaderView->GetDocument()->isDynamicXFA();
    CPDFReaderDoc* pDoc = m_pPDFReaderView->GetDocument();
    if (pDoc->isDynamicXFA())
      m_TextSearch = TextSearch(pDoc->GetXFADoc(),NULL);
    else
      m_TextSearch = TextSearch(pDoc->GetPDFDocument(),NULL);
    m_TextSearch.SetPattern(m_strFindWhat.GetBuffer());
    m_strFindWhat.ReleaseBuffer();
    m_TextSearch.SetSearchFlags(m_nCurFlags);
    if (m_nDirection == 0) {
      m_TextSearch.SetStartPage(m_pPDFReaderView->GetCurVisiblePageIndex());
      m_TextSearch.SetEndPage(pDoc->GetPageCount()-1);
      bFind = m_TextSearch.FindNext();
      if (m_nLastFindCharIndex != -1) {
        int nFindCharIndex = m_TextSearch.GetMatchStartCharIndex();
        int nFindPageIndex = m_TextSearch.GetMatchPageIndex();
        while (bFind && nFindPageIndex == m_pPDFReaderView->GetCurVisiblePageIndex() && nFindCharIndex <= m_nLastFindCharIndex) {
           bFind = m_TextSearch.FindNext();
           nFindCharIndex = m_TextSearch.GetMatchStartCharIndex();
           nFindPageIndex = m_TextSearch.GetMatchPageIndex();
        }
      }
    } else {
      m_TextSearch.SetStartPage(m_pPDFReaderView->GetCurVisiblePageIndex());
      m_TextSearch.SetEndPage(0);
      bFind = m_TextSearch.FindPrev();
      if (m_nLastFindCharIndex != -1) {
        int nFindCharIndex = m_TextSearch.GetMatchStartCharIndex();
        int nFindPageIndex = m_TextSearch.GetMatchPageIndex();
        while (bFind && nFindPageIndex == m_pPDFReaderView->GetCurVisiblePageIndex() && nFindCharIndex >= m_nLastFindCharIndex) {
          bFind = m_TextSearch.FindPrev();
          nFindCharIndex = m_TextSearch.GetMatchStartCharIndex();
          nFindPageIndex = m_TextSearch.GetMatchPageIndex();
        }
      }
    }
    if (!bFind) {
      m_pPDFReaderView->CleanSearch();
      m_pPDFReaderView->Invalidate();
      AfxMessageBox(_T("The following specified text was not found:")+m_strFindWhat);
      m_nLastFindCharIndex = -1;
      return;
    }
  }
  if (!bFind) {
    AfxMessageBox(_T("Find compeleted!"));
    m_nLastFindCharIndex = -1;
    return;
  }

  nFindPageIndex = m_TextSearch.GetMatchPageIndex();
  m_nLastFindCharIndex = m_TextSearch.GetMatchStartCharIndex();
  std::vector<foxit::RectF> rect_vector;
  foxit::RectFArray matched_rects = m_TextSearch.GetMatchRects();
  for (int i = 0; i < matched_rects.GetSize(); i++) {
    rect_vector.push_back(matched_rects[i]);
  }
  m_pPDFReaderView->SearchText(nFindPageIndex,rect_vector);

}

void FindDlg::OnEnChangeEditFindtext() {
  // TODO: If this is a RICHEDIT control, the control will not
  // send this notification unless you override the CDialog::OnInitDialog()
  // function and call CRichEditCtrl().SetEventMask()
  // with the ENM_CHANGE flag ORed into the mask.

  // TODO: Add your control notification handler code here
  UpdateData(TRUE);
}

void FindDlg::OnBnClickedButtonFindNext() {
  // TODO: Add your control notification handler code here
  UpdateData(TRUE);
  Find();
  m_strLastKey = m_strFindWhat;
  m_nLastFlags = m_nCurFlags;
  m_nLastDirection = m_nDirection;
}

