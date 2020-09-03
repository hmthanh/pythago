#pragma once

class CPDFReaderDoc;
class CDocCreationDlg : public CDialogEx {
  DECLARE_DYNAMIC(CDocCreationDlg)

 public:
  CDocCreationDlg(CPDFReaderDoc* doc, CWnd* pParent = NULL);  // standard constructor
  virtual ~CDocCreationDlg();

  // Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_PROPERTYDLG_CREATION };
#endif

 protected:
  void InitMetadata(const wchar_t* key, int nID);
  void InitDateTime(bool bCreation, int nID);
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  virtual BOOL OnInitDialog();

  DECLARE_MESSAGE_MAP()

 private:
  CPDFReaderDoc* m_pReaderDoc;
};

class CDocViewerPrefsDlg : public CDialogEx {
  DECLARE_DYNAMIC(CDocViewerPrefsDlg)

 public:
  CDocViewerPrefsDlg(CPDFReaderDoc* doc, CWnd* pParent = NULL);  // standard constructor
  virtual ~CDocViewerPrefsDlg();

  // Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_PROPERTYDLG_INITIAL_VIEW };
#endif

 protected:
  void InitUIVisibility(DocViewerPrefs::ViewerPref ui_item, int nID);
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  virtual BOOL OnInitDialog();
  DECLARE_MESSAGE_MAP()

 private:
  CPDFReaderDoc* m_pReaderDoc;
};

// CDocSecurityDlg dialog

class CDocSecurityDlg : public CDialogEx {
  DECLARE_DYNAMIC(CDocSecurityDlg)

 public:
  CDocSecurityDlg(CPDFReaderDoc* doc, CWnd* pParent = NULL);  // standard constructor
  virtual ~CDocSecurityDlg();

  // Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_PROPERTYDLG_SECURITY };
#endif

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  virtual BOOL OnInitDialog();

  DECLARE_MESSAGE_MAP()

 private:
  CPDFReaderDoc* m_pReaderDoc;
};

// CDocPropertyDlg dialog

class CDocPropertyDlg : public CDialogEx {
  DECLARE_DYNAMIC(CDocPropertyDlg)

 public:
  CDocPropertyDlg(CPDFReaderDoc* doc, CWnd* pParent = NULL);  // standard constructor
  virtual ~CDocPropertyDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_PROPERTYDLG };
#endif

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support

  afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
  DECLARE_MESSAGE_MAP()
  virtual void OnOK();
  virtual void OnCancel();

 private:
  //  CButton m_ctrlTab;
  CTabCtrl m_ctrlTab;
  CDocCreationDlg m_wndCreationDlg;
  CDocSecurityDlg m_wndSecurityDlg;
  CDocViewerPrefsDlg m_wndViewPrefsDlg;
  CDialog* m_pDialog[3];
  int m_nCurSelTab;
  CString m_csFilepath;
  virtual BOOL OnInitDialog();
};
