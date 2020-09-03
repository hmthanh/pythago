#pragma once

class CPDFReaderView;
class FindDlg : public CDialog {
  DECLARE_DYNAMIC(FindDlg)

 public:
  FindDlg(CPDFReaderView* pView, CWnd* pParent = NULL);  // standard constructor
  virtual ~FindDlg();

  // Dialog Data
#ifdef AFX_DESIGN_TIME
  // Dialog Data
  enum { IDD = IDD_FINDDLG };
#endif
  CPDFReaderView* m_pPDFReaderView;

  TextSearch m_TextSearch;
  BOOL m_bMatchCase;
  BOOL m_bWholeWord;
  CString m_strFindWhat;
  int m_nDirection;

  int m_nCurPageIndex;
  foxit::uint32 m_nCurFlags;

  CString m_strLastKey;
  int m_nLastDirection;
  int m_nLastFindCharIndex;
  foxit::uint32 m_nLastFlags;

  CFont m_font;

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  virtual void OnOk();
  virtual BOOL OnInitDialog();
  virtual void OnCancel();

  void Find();
  DECLARE_MESSAGE_MAP()
 public:
  afx_msg void OnEnChangeEditFindtext();
  afx_msg void OnBnClickedButtonFindNext();
};