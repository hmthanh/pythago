#pragma once

/////////////////////////////////////////////////////////////////////////////
// CZoomSliderCtrl window

class CZoomSliderButton;

class CZoomSliderEdit :public CEdit {
public:
  CZoomSliderEdit(CZoomSliderButton& btnSlider);
public:
  CZoomSliderButton& m_btnSlider;
public:
  virtual ~CZoomSliderEdit();
  virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnKillFocus(CWnd* pNewWnd);
  DECLARE_MESSAGE_MAP()
private:
  CString m_strLastText;
};

class CZoomSliderCtrl : public CSliderCtrl {
  // Construction
 public:
  CZoomSliderCtrl(CZoomSliderButton& btnSlider);

 public:
  CZoomSliderButton& m_btnSlider;

 public:
  virtual ~CZoomSliderCtrl();
  virtual void SetPos(int nPos);

 protected:
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
class CZoomSliderButton : public CMFCToolBarButton {
  DECLARE_SERIAL(CZoomSliderButton)

 public:
  CZoomSliderButton();
  CZoomSliderButton(UINT uiId, int iImage = -1, DWORD dwStyle = 0, int iSliderWidth = 0, int iEditWidth = 0);

  virtual ~CZoomSliderButton();
  CEdit* GetEdit() { return &m_wndEdit; }

  void SetRange(int iMin, int iMax);
  void SetValue(float iValue, BOOL bNotify = TRUE);
  void SetValueFromSlider(int iValue, BOOL bNotify = TRUE);

  float GetZoomValue();

  int GetPos(UINT uiCmd);

  // Overrides:
  virtual void Serialize(CArchive& ar);
  virtual void CopyFrom(const CMFCToolBarButton& src);
  virtual SIZE OnCalculateSize(CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
  virtual void OnShow(BOOL bShow);
  virtual void OnChangeParentWnd(CWnd* pWndParent);
  virtual void OnMove();
  virtual void OnSize(int iSize);


  virtual HWND GetHwnd() {
    return m_wndSlider.GetSafeHwnd();
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
  // Attributes:
 public:
  CZoomSliderCtrl m_wndSlider;
  CZoomSliderEdit m_wndEdit;
  int m_nWidth;
  int m_nEditWidth;
  int m_nSliderWidth;
  DWORD m_dwStyle;
  int m_nMin;
  int m_nMax;
  int m_nValue;
};
