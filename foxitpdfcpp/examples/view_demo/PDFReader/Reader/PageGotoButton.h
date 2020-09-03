#pragma once
#include "afxtoolbarbutton.h"

class CPageGotoButton;
class CPageComboBox : public CComboBox {
 public:
  enum CHANGETYPE { UNKNOWN = -1, SEL_CHANGE, EDIT_CHANGE };
  // Construction
 public:
  CPageComboBox(CPageGotoButton& btnSlider);
  CHANGETYPE GetChangeType() {
    return m_ChangeType;
  }

  void ResetChangeType() {
    m_ChangeType = UNKNOWN;
  }

 public:
  CPageGotoButton& m_btnGoto;

  virtual ~CPageComboBox();
  virtual BOOL PreTranslateMessage(MSG* pMsg);

 protected:
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnCbnEditchange();
  afx_msg void OnCbnSelchange();

  DECLARE_MESSAGE_MAP()
private:
  CHANGETYPE m_ChangeType;
public:
  afx_msg void OnCbnKillfocus();
  afx_msg void OnCbnSetfocus();
};

class CPageGotoButton : public CMFCToolBarButton {
  DECLARE_SERIAL(CPageGotoButton)

 public:
  CPageGotoButton();
  CPageGotoButton(UINT uiId, int iImage = -1, DWORD dwStyle = 0, int iWidth = 0);

  virtual ~CPageGotoButton();
  CPageComboBox* GetComboBox();

  // Overrides:
  virtual void Serialize(CArchive& ar);
  virtual void CopyFrom(const CMFCToolBarButton& src);
  virtual SIZE OnCalculateSize(CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
  virtual void OnShow(BOOL bShow);
  virtual void OnChangeParentWnd(CWnd* pWndParent);
  virtual void OnMove();
  virtual void OnSize(int iSize);
  virtual HWND GetHwnd() {
    return m_wndComboBox.GetSafeHwnd();
  }

  virtual BOOL CanBeStretched() const {
    return TRUE;
  }

  virtual BOOL HaveHotBorder() const {
    return FALSE;
  }

  virtual void OnDraw(CDC* /*pDC*/, const CRect& /*rect*/, CMFCToolBarImages* /*pImages*/, BOOL /*bHorz*/ = TRUE,
                      BOOL /*bCustomizeMode*/ = FALSE, BOOL /*bHighlight*/ = FALSE, BOOL /*bDrawBorder*/ = TRUE,
                      BOOL /*bGrayDisabledButtons*/ = TRUE) {}
protected:
  CPageComboBox m_wndComboBox;
  int m_nWidth;
  DWORD m_dwStyle;
};
