#pragma once


// CAnnotGenerateDlg dialog
class IAnnotPropertyUITab;
class CFreetextGenerateDlg : public CDialogEx, public IAnnotPropertyUITab
{
  DECLARE_DYNAMIC(CFreetextGenerateDlg)

public:
  CFreetextGenerateDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~CFreetextGenerateDlg();
  void UpdateDialog(Annot pAnnot, CWnd* pWnd);
  void EnableWindowDlg(BOOL bEnable);

  // Dialog Data
  enum { IDD = IDD_FREETEXT_GENERAL_DIALOG };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:
  afx_msg void OnEnKillfocusAuthorEdit();
  afx_msg void OnEnKillfocusSubjectEdit();

  Annot m_FreeTextAnnot;
  CWnd* m_pWnd;
  CString m_strAuthor;
  CString m_strSubject;
};
