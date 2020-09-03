#include "PageGotoButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CPageGotoButton, CMFCToolBarButton, 1)

static const int kDefaultHeight = 25;
static const int nDefaultWidth = 200;

CPageGotoButton::CPageGotoButton()
    : m_wndComboBox(*this)
    , m_dwStyle(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL)
    , m_nWidth(nDefaultWidth) {}

CPageGotoButton::CPageGotoButton(UINT uiId, int iImage, DWORD dwStyle, int iWidth)
    : CMFCToolBarButton(uiId, iImage)
    , m_wndComboBox(*this) {
  m_dwStyle = dwStyle | WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL | CBS_DROPDOWNLIST;
  m_nWidth = (iWidth == 0) ? nDefaultWidth: iWidth;
}


CPageGotoButton::~CPageGotoButton() {
  if (m_wndComboBox.GetSafeHwnd() != NULL) {
    m_wndComboBox.DestroyWindow();
  }
}

CPageComboBox * CPageGotoButton::GetComboBox() {
  return &m_wndComboBox;
}

void CPageGotoButton::Serialize(CArchive & ar) {
  CMFCToolBarButton::Serialize(ar);

  if (ar.IsLoading()) {
    ar >> m_nWidth;
    ar >> m_dwStyle;
  } else {
    ar << m_nWidth;
    ar << m_dwStyle;
  }
}

void CPageGotoButton::CopyFrom(const CMFCToolBarButton & s) {
  CMFCToolBarButton::CopyFrom(s);

  const CPageGotoButton& src = (const CPageGotoButton&) s;

  m_dwStyle = src.m_dwStyle;
  m_nWidth = src.m_nWidth;

}

SIZE CPageGotoButton::OnCalculateSize(CDC * pDC, const CSize & sizeDefault, BOOL bHorz) {
  if (!IsVisible()) {
    if (m_wndComboBox.GetSafeHwnd() != NULL) {
      m_wndComboBox.ShowWindow(SW_HIDE);
    }

    return CSize(0, 0);
  }

  if (bHorz) {
    if (m_wndComboBox.GetSafeHwnd() != NULL && !IsHidden()) {
      m_wndComboBox.ShowWindow(SW_SHOWNOACTIVATE);
    }

    return CSize(m_nWidth, kDefaultHeight);
  } else {
    if (m_wndComboBox.GetSafeHwnd() != NULL && !IsHidden()) {
      m_wndComboBox.ShowWindow(SW_SHOWNOACTIVATE);
    }

    return CSize(kDefaultHeight, m_nWidth);
  }
}

void CPageGotoButton::OnShow(BOOL bShow) {
  if (m_wndComboBox.GetSafeHwnd() != NULL) {
    if (bShow) {
      m_wndComboBox.ShowWindow(SW_SHOWNOACTIVATE);
      OnMove();
    } else {
      m_wndComboBox.ShowWindow(SW_HIDE);
    }
  }
}

void CPageGotoButton::OnChangeParentWnd(CWnd * pWndParent) {
  if (m_wndComboBox.GetSafeHwnd() != NULL) {
    CWnd* pWndParentCurr = m_wndComboBox.GetParent();
    ASSERT(pWndParentCurr != NULL);

    if (pWndParent != NULL && pWndParentCurr != NULL && pWndParentCurr->GetSafeHwnd() == pWndParent->GetSafeHwnd()) {
      return;
    }

    m_wndComboBox.DestroyWindow();
  }

  if (pWndParent == NULL || pWndParent->GetSafeHwnd() == NULL) {
    return;
  }

  if (!m_wndComboBox.Create(m_dwStyle, CRect(m_rect.left + 1, m_rect.top + 2, m_rect.Width() - 4, m_rect.Height() - 2),
                          pWndParent, m_nID)) {
    ASSERT(FALSE);
    return;
  }
  m_wndComboBox.SetOwner(pWndParent);

}

void CPageGotoButton::OnMove() {
  if (m_wndComboBox.GetSafeHwnd() != NULL && (m_wndComboBox.GetStyle() & WS_VISIBLE)) {
    m_wndComboBox.SetWindowPos(NULL, m_rect.left + 1, m_rect.top + 2, m_rect.Width()-4, m_rect.Height() - 2,
                             SWP_NOZORDER | SWP_NOACTIVATE);
  }
}

void CPageGotoButton::OnSize(int iSize) {
  m_nWidth = iSize;
  m_rect.right = m_rect.left + m_nWidth;

  if (m_wndComboBox.GetSafeHwnd() != NULL && (m_wndComboBox.GetStyle() & WS_VISIBLE)) {
    m_wndComboBox.SetWindowPos(NULL, m_rect.left + 1, m_rect.top + 2, m_rect.Width() - 4, m_rect.Height() - 2,
                               SWP_NOZORDER | SWP_NOACTIVATE);
  }
}

BEGIN_MESSAGE_MAP(CPageComboBox, CComboBox)
  ON_WM_KEYDOWN()
  ON_WM_LBUTTONUP()
  ON_CONTROL_REFLECT(CBN_EDITCHANGE, &CPageComboBox::OnCbnEditchange)
  ON_CONTROL_REFLECT(CBN_SELCHANGE, &CPageComboBox::OnCbnSelchange)
  ON_CONTROL_REFLECT(CBN_KILLFOCUS, &CPageComboBox::OnCbnKillfocus)
  ON_CONTROL_REFLECT(CBN_SETFOCUS, &CPageComboBox::OnCbnSetfocus)
END_MESSAGE_MAP()

CPageComboBox::CPageComboBox(CPageGotoButton & btnGoto)
    : m_btnGoto(btnGoto)
    , m_ChangeType(UNKNOWN) {

}

CPageComboBox::~CPageComboBox() {}

BOOL CPageComboBox::PreTranslateMessage(MSG * pMsg) {
  if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
    SetEditSel(0, -1);
    m_ChangeType = EDIT_CHANGE;
    GetOwner()->SendMessage(WM_COMMAND, m_btnGoto.m_nID);
    return TRUE;
  }
  return CComboBox::PreTranslateMessage(pMsg);
}

void CPageComboBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {}

void CPageComboBox::OnLButtonUp(UINT nFlags, CPoint point) {
  return CComboBox::OnLButtonUp( nFlags, point);
}


void CPageComboBox::OnCbnEditchange() {
  // TODO: Add your control notification handler code here
}


void CPageComboBox::OnCbnSelchange() {
  // TODO: Add your control notification handler code here
  m_ChangeType = SEL_CHANGE;
  GetOwner()->SendMessage(WM_COMMAND, m_btnGoto.m_nID);
}


void CPageComboBox::OnCbnKillfocus() {
  // TODO: Add your control notification handler code here
}


void CPageComboBox::OnCbnSetfocus() {
  // TODO: Add your control notification handler code here
  SetEditSel(0, -1);
}
