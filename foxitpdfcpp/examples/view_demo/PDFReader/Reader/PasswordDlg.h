#pragma once
#include "afxwin.h"

// CPasswordDlg dialog

class CPasswordDlg : public CDialogEx {
  DECLARE_DYNAMIC(CPasswordDlg)

 public:
  CPasswordDlg(BOOL bHasAskPassword, CWnd* pParent = NULL);  // standard constructor
  virtual ~CPasswordDlg();
  CString GetPassword();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_PASSWORD_DIALOG };
#endif

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  virtual BOOL OnInitDialog();

  CString m_strPassword;
  CEdit m_ctrlEditPassword;
  BOOL m_bHasAskPassword;

 public:
  afx_msg void OnBnClickedPasswordOk();
  DECLARE_MESSAGE_MAP()
};
