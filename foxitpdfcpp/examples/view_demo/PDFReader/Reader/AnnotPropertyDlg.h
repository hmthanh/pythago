#pragma once

#include "AnnotAppearanceDlg.h"
#include "FreetextAppearanceDlg.h"
#include "FreetextGenerateDlg.h"
#include "afxcmn.h"

// CAnnotPropertyDlg dialog

class CAnnotPropertyDlg : public CDialogEx
{
  DECLARE_DYNAMIC(CAnnotPropertyDlg)

public:
  CAnnotPropertyDlg(Annot pdf_annot, CWnd* pParent = NULL);   // standard constructor
  virtual ~CAnnotPropertyDlg();

// Dialog Data
  enum { IDD = IDD_ANNOT_PROPERTY_DIALOG };

  void  UpdateDialog(CWnd* pWnd);

  void ChangeFocusAnnot(Annot pdf_annot);

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

 private:
  void EnableWindowDlg(BOOL bEnable);
  void HideAllPropertyDlg();
  virtual BOOL OnInitDialog();

  Annot m_FocusAnnot;
  CFreetextAppearanceDlg m_freetextAPDlg;
  CAnnotAppearanceDlg m_notesAPDlg;
  CFreetextGenerateDlg  m_freetextAnnotGEDlg;
  CTabCtrl m_AnnotPropertyTab;
  BOOL m_bLocked;
  CDialogEx* m_pAnnotProperty[3];
  int m_nSelectTab;

 public:
  afx_msg void OnNMThemeChangedAnnotPropertyTab(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnTcnSelchangeAnnotPropertyTab(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnBnClickedCloseannotpropertyButton();
  afx_msg void OnBnClickedLockannotCheck();
};
