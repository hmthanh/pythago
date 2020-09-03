#include "PDFReader/Source/stdafx.h"
#include "SliderButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CZoomSliderButton, CMFCToolBarButton, 1)

static const int kDefaultHeight = 25;
static const int kDefaultSliderWidth = 220;
static const int kDefaultEditWidth = 25;

static float GetValueFromPos(int iPos, int iMax, int iMin) {
  if (iPos >= (iMax + iMin) / 2.0) {
    double x = pow(double(kDefaultMaxZoomFactor), 2.0/(iMax+iMin));
    return (float)(pow(x, iPos - (iMax + iMin) / 2.0));
  } else {
    double x = pow(1.0 / kDefaultMinZoomFactor, 2.0 / (iMax+iMin));
    return (float)(pow(x, iPos - iMin) * kDefaultMinZoomFactor);
  }
  return 1.0;
}
static int GetPosFromValue(float iValue, int iMax, int iMin) {
  if (iValue >= 1) {
    double x = pow(double(kDefaultMaxZoomFactor), 2.0 / (iMax+iMin));
    return int(log(iValue) / log(x) + (iMax+iMin)/2.0 + 0.5);
  } else {
    double x = pow(1.0 / double(kDefaultMinZoomFactor),  2.0 / (iMax+iMin));
    return int(log(iValue) / log(x) + (iMax + iMin) / 2.0 + 0.5);
  }
  return (iMax + iMin) / 2;
}

CZoomSliderButton::CZoomSliderButton()
    : m_wndSlider(*this)
    , m_wndEdit(*this)
    , m_nEditWidth(kDefaultEditWidth)
    , m_nSliderWidth(kDefaultSliderWidth) 
    , m_dwStyle(WS_CHILD | WS_VISIBLE | TBS_HORZ)
    , m_nMin(0)
    , m_nMax(200)
    , m_nValue(100) {
  m_nWidth = kDefaultEditWidth + kDefaultSliderWidth;
}
//**************************************************************************************
CZoomSliderButton::CZoomSliderButton(UINT uiId, int iImage, DWORD dwStyle, int iSliderWidth, int iEditWidth)
    : CMFCToolBarButton(uiId, iImage)
    , m_wndSlider(*this)
    , m_wndEdit(*this)
    , m_nMin(0)
    , m_nMax(200)
    , m_nValue(100) {
  m_dwStyle = dwStyle | WS_CHILD | WS_VISIBLE | TBS_HORZ;
  m_nSliderWidth = (iSliderWidth == 0) ? kDefaultSliderWidth : iSliderWidth;
  m_nEditWidth = (iEditWidth == 0) ? kDefaultEditWidth : iEditWidth;
  m_nWidth = m_nSliderWidth + m_nEditWidth;
}
//**************************************************************************************
CZoomSliderButton::~CZoomSliderButton() {
  if (m_wndSlider.GetSafeHwnd() != NULL) {
    m_wndSlider.DestroyWindow();
  }
}
//**************************************************************************************
SIZE CZoomSliderButton::OnCalculateSize(CDC* /*pDC*/, const CSize& /*sizeDefault*/, BOOL bHorz) {
  if (!IsVisible()) {
    if (m_wndSlider.GetSafeHwnd() != NULL) {
      m_wndSlider.ShowWindow(SW_HIDE);
    }

    return CSize(0, 0);
  }

  if (bHorz) {
    if (m_wndSlider.GetSafeHwnd() != NULL && !IsHidden()) {
      m_wndSlider.ShowWindow(SW_SHOWNOACTIVATE);
      m_wndSlider.ModifyStyle(TBS_VERT, TBS_HORZ);
      m_wndEdit.ShowWindow(SW_SHOWNOACTIVATE);
      m_wndEdit.ModifyStyle(TBS_VERT, TBS_HORZ);
    }

    return CSize(m_nWidth, kDefaultHeight);
  } else {
    if (m_wndSlider.GetSafeHwnd() != NULL && !IsHidden()) {
      m_wndSlider.ShowWindow(SW_SHOWNOACTIVATE);
      m_wndSlider.ModifyStyle(TBS_HORZ, TBS_VERT);
      m_wndEdit.ShowWindow(SW_SHOWNOACTIVATE);
      m_wndEdit.ModifyStyle(TBS_HORZ, TBS_VERT);
    }

    return CSize(kDefaultHeight, m_nWidth);
  }
}
//**************************************************************************************
void CZoomSliderButton::Serialize(CArchive& ar) {
  CMFCToolBarButton::Serialize(ar);

  if (ar.IsLoading()) {
    ar >> m_nWidth;
    ar >> m_dwStyle;
    ar >> m_nEditWidth;
    ar >> m_nSliderWidth;
    ar >> m_nMin;
    ar >> m_nMax;

    SetRange(m_nMin, m_nMax);
  } else {
    ar << m_nWidth;
    ar << m_dwStyle;
    ar << m_nEditWidth;
    ar << m_nSliderWidth;
    ar << m_nMin;
    ar << m_nMax;
  }
}
//**************************************************************************************
void CZoomSliderButton::OnMove() {
  if (m_wndSlider.GetSafeHwnd() != NULL && (m_wndSlider.GetStyle() & WS_VISIBLE)) {
    m_wndSlider.SetWindowPos(NULL, m_rect.left + 1, m_rect.top + 5, m_nSliderWidth - 2, m_rect.Height() - 2,
                             SWP_NOZORDER | SWP_NOACTIVATE);
    m_wndEdit.SetWindowPos(&m_wndSlider, m_rect.left + m_nSliderWidth + 1, m_rect.top + 7, m_nEditWidth - 2, m_rect.Height() - 5,
                           SWP_NOZORDER | SWP_NOACTIVATE);
  }
}
//**************************************************************************************
void CZoomSliderButton::OnSize(int iSize) {
  m_nSliderWidth = iSize / (m_nWidth) *m_nSliderWidth;
  m_nEditWidth = iSize / (m_nWidth) *m_nEditWidth;
  m_nWidth = iSize;
  m_rect.right = m_rect.left + m_nWidth;

  if (m_wndSlider.GetSafeHwnd() != NULL && (m_wndSlider.GetStyle() & WS_VISIBLE)) {
    m_wndSlider.SetWindowPos(NULL, m_rect.left + 1, m_rect.top + 5, m_nSliderWidth - 2, m_rect.Height() - 2,
                             SWP_NOZORDER | SWP_NOACTIVATE);
    m_wndEdit.SetWindowPos(&m_wndSlider, m_rect.left + m_nSliderWidth + 1, m_rect.top + 7, m_nEditWidth - 2, m_rect.Height() - 5,
                           SWP_NOZORDER | SWP_NOACTIVATE);
  }
}


//**************************************************************************************
void CZoomSliderButton::OnChangeParentWnd(CWnd* pWndParent) {
  if (m_wndSlider.GetSafeHwnd() != NULL) {
    CWnd* pWndParentCurr = m_wndSlider.GetParent();
    ASSERT(pWndParentCurr != NULL);

    if (pWndParent != NULL && pWndParentCurr != NULL && pWndParentCurr->GetSafeHwnd() == pWndParent->GetSafeHwnd()) {
      return;
    }

    m_wndSlider.DestroyWindow();
  }

  if (pWndParent == NULL || pWndParent->GetSafeHwnd() == NULL) {
    return;
  }

  if (!m_wndSlider.Create(m_dwStyle, CRect(m_rect.left + 1, m_rect.top + 5, m_nSliderWidth - 2, m_rect.Height() - 2),
                          pWndParent,m_nID)) {
    ASSERT(FALSE);
    return;
  }

  m_wndSlider.SetRange(m_nMin, m_nMax);
  m_wndSlider.SetPos(GetPosFromValue(m_nValue / 100.f, m_nMax, m_nMin));
  m_wndSlider.SetOwner(pWndParent);

  // For Edit
  if (m_wndEdit.GetSafeHwnd() != NULL) {
    m_wndEdit.DestroyWindow();
  }

  if (!m_wndEdit.Create(m_dwStyle | ES_CENTER,
                        CRect(m_rect.left + m_nSliderWidth + 1, m_rect.top + 7, m_nEditWidth- 2, m_rect.Height() - 5),
                        pWndParent, m_nID)) {
    ASSERT(FALSE);
    return;
  }
  m_wndEdit.SetOwner(pWndParent);
  CString str;
  str.Format(_T("%d%%"), m_nValue);

  m_wndEdit.SetWindowText(str);
}
//**************************************************************************************
void CZoomSliderButton::CopyFrom(const CMFCToolBarButton& s) {
  CMFCToolBarButton::CopyFrom(s);

  const CZoomSliderButton& src = (const CZoomSliderButton&) s;

  m_dwStyle = src.m_dwStyle;
  m_nWidth = src.m_nWidth;
  m_nEditWidth = src.m_nEditWidth;
  m_nSliderWidth = src.m_nSliderWidth;
  m_nMin = src.m_nMin;
  m_nMax = src.m_nMax;
  m_nValue = src.m_nValue;
}
//************************************************************************************
void CZoomSliderButton::SetRange(int iMin, int iMax) {
  m_nMin = iMin;
  m_nMax = iMax;

  if (m_wndSlider.GetSafeHwnd() != NULL) {
    m_wndSlider.SetRange(iMin, iMax, TRUE);
  }
}
//************************************************************************************
void CZoomSliderButton::SetValue(float iValue, BOOL bNotify) {
  m_nValue = int(iValue*100 + 0.5f);
  if (GetHwnd() != NULL) {
    CString str;
    str.Format(_T("%d%%"), m_nValue);
    m_wndEdit.SetWindowText(str);
    m_wndSlider.SetPos(GetPosFromValue(iValue,m_nMax,m_nMin));
  }

  if (bNotify && m_wndSlider.GetSafeHwnd() != NULL) {
    m_wndSlider.GetOwner()->SendMessage(WM_COMMAND, m_nID);
  }

  if (bNotify && m_wndEdit.GetSafeHwnd() != NULL) {
    m_wndEdit.GetOwner()->SendMessage(WM_COMMAND, m_nID);
  }
}
void CZoomSliderButton::SetValueFromSlider(int iPos, BOOL bNotify) {
  m_nValue = int(GetValueFromPos(iPos, m_nMax, m_nMin)*100.f + 0.5f);
  if (GetHwnd() != NULL) {
    CString str;
    str.Format(_T("%d%%"), m_nValue);
    m_wndEdit.SetWindowText(str);
  }

  if (bNotify && m_wndSlider.GetSafeHwnd() != NULL) {
    m_wndSlider.GetOwner()->SendMessage(WM_COMMAND, m_nID);
  }

  if (bNotify && m_wndEdit.GetSafeHwnd() != NULL) {
    m_wndEdit.GetOwner()->SendMessage(WM_COMMAND, m_nID);
  }
}
float CZoomSliderButton::GetZoomValue() {
  return m_nValue / 100.f;
}
//************************************************************************************
int CZoomSliderButton::GetPos(UINT uiCmd) {
  if (m_wndSlider.GetSafeHwnd()) {
    return m_wndSlider.GetPos();
  }
  return -1;
}
//****************************************************************************************
void CZoomSliderButton::OnShow(BOOL bShow) {
  if (m_wndSlider.GetSafeHwnd() != NULL) {
    if (bShow) {
      m_wndSlider.ShowWindow(SW_SHOWNOACTIVATE);
      m_wndEdit.ShowWindow(SW_SHOWNOACTIVATE);
      OnMove();
    } else {
      m_wndSlider.ShowWindow(SW_HIDE);
      m_wndEdit.ShowWindow(SW_HIDE);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// CZoomSliderCtrl

CZoomSliderCtrl::CZoomSliderCtrl(CZoomSliderButton& btnSlider)
  : m_btnSlider(btnSlider) {}

CZoomSliderCtrl::~CZoomSliderCtrl() {}

void CZoomSliderCtrl::SetPos(int nPos) {
  return CSliderCtrl::SetPos(nPos);
}

BEGIN_MESSAGE_MAP(CZoomSliderCtrl, CSliderCtrl)
  ON_WM_MOUSEMOVE()
  ON_WM_KEYDOWN()
  ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomSliderCtrl message handlers

void CZoomSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) {
  int nPos = GetPos();

  CSliderCtrl::OnMouseMove(nFlags, point);

  if ((nFlags & MK_LBUTTON) && GetPos() != nPos) {
    m_btnSlider.SetValueFromSlider(GetPos(), TRUE);
  }
}

void CZoomSliderCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
  int nPos = GetPos();

  CSliderCtrl::OnKeyDown(nChar, nRepCnt, nFlags);

  if (GetPos() != nPos) {
    m_btnSlider.SetValueFromSlider(GetPos(), TRUE);
  }
}

void CZoomSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) {
  CSliderCtrl::OnLButtonUp(nFlags, point);
  if (IsWindowVisible()) {
    m_btnSlider.SetValueFromSlider(GetPos(), TRUE);
  }
}

BEGIN_MESSAGE_MAP(CZoomSliderEdit, CEdit)
  ON_WM_KEYDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_SETFOCUS()
  ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

CZoomSliderEdit::CZoomSliderEdit(CZoomSliderButton& btnSlider)
    : m_btnSlider(btnSlider)
    , m_strLastText(_T("")){}

CZoomSliderEdit::~CZoomSliderEdit() {}

BOOL CZoomSliderEdit::PreTranslateMessage(MSG * pMsg) {
  if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
    CString strZoom;
    GetWindowText(strZoom);
    float i = (float)_ttoi(strZoom);
    if (i < kDefaultMinZoomFactor * 100.f)
      i = kDefaultMinZoomFactor * 100.f;
    if (i > kDefaultMaxZoomFactor * 100.f)
      i = kDefaultMaxZoomFactor * 100.f;
    m_btnSlider.SetValue(i / 100.f);
    SetSel(0, -1);
    GetWindowText(m_strLastText);
    return TRUE;
  }
  return CEdit::PreTranslateMessage(pMsg);
}

void CZoomSliderEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
  CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CZoomSliderEdit::OnLButtonUp(UINT nFlags, CPoint point) {
  CEdit::OnLButtonUp(nFlags, point);
}

void CZoomSliderEdit::OnSetFocus(CWnd * pOldWnd) {
  PostMessage(EM_SETSEL, 0, -1);
  GetWindowText(m_strLastText);
  CEdit::OnSetFocus(pOldWnd);
}

void CZoomSliderEdit::OnKillFocus(CWnd * pNewWnd) {
  SetWindowText(m_strLastText);
  CEdit::OnKillFocus(pNewWnd);
}
