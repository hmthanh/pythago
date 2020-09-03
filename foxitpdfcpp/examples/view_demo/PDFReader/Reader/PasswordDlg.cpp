// PasswordDlg.cpp : implementation file
//

#include "PDFReader/Source/Stdafx.h"

#include "PDFReader/Reader/PDFReader.h"
#include "PDFReader/Reader/PasswordDlg.h"

#include "afxdialogex.h"

// CPasswordDlg dialog

IMPLEMENT_DYNAMIC(CPasswordDlg, CDialogEx)

CPasswordDlg::CPasswordDlg(BOOL bHasAskPassword, CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_PASSWORD_DIALOG, pParent)
    , m_bHasAskPassword(bHasAskPassword)
    , m_strPassword(_T("")) {}

CPasswordDlg::~CPasswordDlg() {}

void CPasswordDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_PASSWORD_EDIT, m_ctrlEditPassword);
}

BOOL CPasswordDlg::OnInitDialog() {
  if (!CDialogEx::OnInitDialog())
    return FALSE;
  if (m_bHasAskPassword) {
    SetWindowText(_T("Password error, please input correct password."));
  } else {
    SetWindowText(_T("This file is password protected, please enter a password to open this document."));
  }
  return TRUE;
}

BEGIN_MESSAGE_MAP(CPasswordDlg, CDialogEx)
ON_BN_CLICKED(ID_PASSWORD_OK, &CPasswordDlg::OnBnClickedPasswordOk)
END_MESSAGE_MAP()

// CPasswordDlg message handlers

void CPasswordDlg::OnBnClickedPasswordOk() {
  // TODO: Add your control notification handler code here
  GetDlgItemText(IDC_PASSWORD_EDIT, m_strPassword);
  CDialogEx::OnOK();
}

CString CPasswordDlg::GetPassword() {
  return m_strPassword;
}
