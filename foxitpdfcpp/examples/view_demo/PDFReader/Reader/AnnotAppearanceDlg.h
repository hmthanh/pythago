#pragma once
#include "afxwin.h"
#include "afxcmn.h"

class IAnnotPropertyUITab
{
public:
  virtual void UpdateDialog(Annot pAnnot, CWnd* pWnd){}
  virtual void EnableWindowDlg(BOOL bEnable){}
};

// Note annot appearance dialog
class CAnnotAppearanceDlg : public CDialogEx, public IAnnotPropertyUITab
{
  DECLARE_DYNAMIC(CAnnotAppearanceDlg)

 public:
  CAnnotAppearanceDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~CAnnotAppearanceDlg();
  virtual void UpdateDialog(Annot pAnnot, CWnd* pWnd);
  virtual void EnableWindowDlg(BOOL bEnable);
  virtual BOOL OnInitDialog();
// Dialog Data
  enum { IDD = IDD_ANNOT_AP_DIALOG };

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  DECLARE_MESSAGE_MAP()

 private:
  afx_msg void OnBnClickedColorButton();

  int GetSelFromNoteStyle(const char* noteStyle);
  char* GetNoteStyleFromSel(int nSel);

  Annot m_Annot;
  CWnd* m_pWnd;
  CMFCButton m_colorCtrl;
  int m_nOpacity;
  CSliderCtrl m_opacitySliderCtrl;
  CComboBox m_noteTypeCtrl;

 public:
  afx_msg void OnEnChangeOpacityEdit();
  afx_msg void OnNMCustomdrawOpacitySlider(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnCbnSelendcancelNotetypeCombo();
};
