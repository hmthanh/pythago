// AnnotGenerateDlg.cpp : implementation file
//

#include "PDFReader.h"
#include "AnnotAppearanceDlg.h"
#include "FreetextGenerateDlg.h"
#include "afxdialogex.h"

// CAnnotGenerateDlg dialog

IMPLEMENT_DYNAMIC(CFreetextGenerateDlg, CDialogEx)

CFreetextGenerateDlg::CFreetextGenerateDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(CFreetextGenerateDlg::IDD, pParent)
    , m_pWnd(NULL)
    , m_strAuthor(_T(""))
    , m_strSubject(_T("")) {}

CFreetextGenerateDlg::~CFreetextGenerateDlg() {}

void CFreetextGenerateDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_AUTHOR_EDIT, m_strAuthor);
  DDX_Text(pDX, IDC_SUBJECT_EDIT, m_strSubject);
}


BEGIN_MESSAGE_MAP(CFreetextGenerateDlg, CDialogEx)
  ON_EN_KILLFOCUS(IDC_AUTHOR_EDIT, &CFreetextGenerateDlg::OnEnKillfocusAuthorEdit)
  ON_EN_KILLFOCUS(IDC_SUBJECT_EDIT, &CFreetextGenerateDlg::OnEnKillfocusSubjectEdit)
END_MESSAGE_MAP()

void CFreetextGenerateDlg::UpdateDialog(Annot annot, CWnd* pWnd)
{
  if (annot.IsEmpty()) return;

  m_FreeTextAnnot = annot;

  Markup markup = (Markup)m_FreeTextAnnot;
  if (!markup.IsEmpty()) {
    m_strSubject = markup.GetSubject();
  m_strAuthor = markup.GetTitle();

  foxit::DateTime createTime = markup.GetCreationDateTime();
  CString strCreateTime;
  strCreateTime.Format(_T("%d/%02d/%02d %02d:%02d:%02d"),
    createTime.year, createTime.month, createTime.day, createTime.hour, createTime.minute, createTime.second);
  GetDlgItem(IDC_CREATIONDATE_STATIC)->SetWindowTextW(strCreateTime);
  }
  else {
    m_strSubject = L"";
  m_strAuthor = L"";
  GetDlgItem(IDC_CREATIONDATE_STATIC)->SetWindowTextW(L"0/00/00 00:00:00");
  }

  foxit::DateTime modifyTime = m_FreeTextAnnot.GetModifiedDateTime();
  CString strModifyTime;
  strModifyTime.Format(_T("%d/%02d/%02d %02d:%02d:%02d"),
    modifyTime.year, modifyTime.month, modifyTime.day, modifyTime.hour, modifyTime.minute, modifyTime.second);
  GetDlgItem(IDC_MODDATE_STATIC)->SetWindowTextW(strModifyTime);
  UpdateData(FALSE);
}

void CFreetextGenerateDlg::OnEnKillfocusAuthorEdit() {
  if (m_FreeTextAnnot.IsEmpty()) return;
  UpdateData(TRUE);
  Markup markup = (Markup)m_FreeTextAnnot;
  if (!markup.IsEmpty())
    markup.SetTitle(m_strAuthor.GetBuffer(m_strAuthor.GetLength()));
  m_strAuthor.ReleaseBuffer();
}


void CFreetextGenerateDlg::OnEnKillfocusSubjectEdit() {
  if (m_FreeTextAnnot.IsEmpty()) return;
  UpdateData(TRUE);
  Markup markup = (Markup)m_FreeTextAnnot;
  if (!markup.IsEmpty())
    markup.SetSubject(m_strSubject.GetBuffer(m_strSubject.GetLength()));
  m_strSubject.ReleaseBuffer();
}

void CFreetextGenerateDlg::EnableWindowDlg(BOOL bEnable) {
  GetDlgItem(IDC_AUTHOR_EDIT)->EnableWindow(bEnable);
  GetDlgItem(IDC_SUBJECT_EDIT)->EnableWindow(bEnable);
}