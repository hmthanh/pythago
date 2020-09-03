#pragma once
#include "PDFReader/Source/Stdafx.h"

class CStartInterfaceDlg : public CDialogEx {
  DECLARE_DYNAMIC(CStartInterfaceDlg)

 public:
  CStartInterfaceDlg(CWnd* pParent = NULL);  // standard constructor
  virtual ~CStartInterfaceDlg();

  virtual void OnOK();

  bool ShouldExit() {
    return m_bExit;
  }
  CString GetFilePath();

  // Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = ID_START_INTERFACE_DIALOG };
#endif

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  virtual BOOL OnInitDialog();
  bool m_bExit;
  bool m_bHasDrawText;
  bool m_bUseGray;
  CString m_strFilePath;
  CEdit m_ctrlEditFile;
  CStatic m_ctrlLog;
  CStatic m_ctrlOpen;
  CStatic m_ctrlDelete;
  CListBox m_ctrlRecentList;
  CBitmap m_LogBitmap;
  CBitmap m_OpenBitmap;
  CBitmap m_DeleteBitmap;

 public:
  afx_msg void OnLbnSelchangeRecentFileList();
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  afx_msg void OnStnClickedDeleteRecentList();
  afx_msg void OnStnClickedOpenFile();
  afx_msg void OnStnClickedExitApp();
  afx_msg void OnDropFiles(HDROP hDropInfo);
  DECLARE_MESSAGE_MAP()
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};