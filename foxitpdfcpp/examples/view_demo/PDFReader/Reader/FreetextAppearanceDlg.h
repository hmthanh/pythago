#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CFreetextAppearanceDlg dialog
class IAnnotPropertyUITab;
class CFreetextAppearanceDlg : public CDialogEx, public IAnnotPropertyUITab
{
  DECLARE_DYNAMIC(CFreetextAppearanceDlg)

 public:
  CFreetextAppearanceDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~CFreetextAppearanceDlg();
  void EnableWindowDlg(BOOL bEnable);

// Dialog Data
  enum { IDD = IDD_FREETEXT_AP_DIALOG };
  void UpdateDialog(Annot pAnnot,CWnd* pWnd);

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  DECLARE_MESSAGE_MAP()

 private:
  afx_msg void OnDeltaposThicknessSpin(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnEnChangeBorderwidthEdit();
  afx_msg void OnNMCustomdrawFreetextopacitySlider(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnEnChangeFreetextopacityEdit();
  afx_msg void OnCbnSelchangeFreetextlinestyleCombo();
  afx_msg void OnBnClickedFreetextcolorButton();
  afx_msg void OnBnClickedFreetextfillcolorButton();
  afx_msg void OnCbnSelchangeBorderstypeCombo();

  void InitCalloutBorderstyle(int nSel, BorderInfo& borderInfo);
  void UpdateThicknessControl(BOOL bIsEnable);
  void UpdateBorderStyleControl(BOOL bIsEnable);
  void UpdateColorControl(BOOL bIsEnable);
  void UpdateLineStyleControl(BOOL bIsEnable);

  FreeText m_FreeTextAnnot;
  CWnd* m_pWnd;
  int m_nThickness;
  CComboBox m_borderStyleCtrl;
  CMFCButton m_color;
  CMFCButton m_fillColor;
  int m_nOpacity;
  BOOL m_bIsFirstSet;
  CSliderCtrl m_OpacitySplider;
  CComboBox m_lineEndingStyleCtrl;

 public:
  virtual BOOL OnInitDialog();
};
