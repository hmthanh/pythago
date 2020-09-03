// FreetextAppearanceDlg.cpp : implementation file
//

#include "PDFReader.h"
#include "AnnotAppearanceDlg.h"
#include "FreetextAppearanceDlg.h"
#include "afxdialogex.h"

#pragma warning(disable : 4482)

// CFreetextAppearanceDlg dialog

IMPLEMENT_DYNAMIC(CFreetextAppearanceDlg, CDialogEx)

CFreetextAppearanceDlg::CFreetextAppearanceDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CFreetextAppearanceDlg::IDD, pParent)
    , m_pWnd(NULL)
    , m_nThickness(0)
    , m_nOpacity(0)
    , m_bIsFirstSet(FALSE) {}

CFreetextAppearanceDlg::~CFreetextAppearanceDlg() {}

void CFreetextAppearanceDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_BORDERWIDTH_EDIT, m_nThickness);
  DDX_Control(pDX, IDC_BORDERSTYPE_COMBO, m_borderStyleCtrl);
  DDX_Control(pDX, IDC_FREETEXTCOLOR_BUTTON, m_color);
  DDX_Control(pDX, IDC_FREETEXTFILLCOLOR_BUTTON, m_fillColor);
  DDX_Text(pDX, IDC_FREETEXTOPACITY_EDIT, m_nOpacity);
  DDX_Control(pDX, IDC_FREETEXTOPACITY_SLIDER, m_OpacitySplider);
  DDX_Control(pDX, IDC_FREETEXTLINESTYLE_COMBO, m_lineEndingStyleCtrl);
}


BEGIN_MESSAGE_MAP(CFreetextAppearanceDlg, CDialogEx)
  ON_NOTIFY(UDN_DELTAPOS, IDC_THICKNESS_SPIN, &CFreetextAppearanceDlg::OnDeltaposThicknessSpin)
  ON_EN_CHANGE(IDC_BORDERWIDTH_EDIT, &CFreetextAppearanceDlg::OnEnChangeBorderwidthEdit)
  ON_NOTIFY(NM_CUSTOMDRAW, IDC_FREETEXTOPACITY_SLIDER, &CFreetextAppearanceDlg::OnNMCustomdrawFreetextopacitySlider)
  ON_EN_CHANGE(IDC_FREETEXTOPACITY_EDIT, &CFreetextAppearanceDlg::OnEnChangeFreetextopacityEdit)
  ON_CBN_SELCHANGE(IDC_FREETEXTLINESTYLE_COMBO, &CFreetextAppearanceDlg::OnCbnSelchangeFreetextlinestyleCombo)
  ON_BN_CLICKED(IDC_FREETEXTCOLOR_BUTTON, &CFreetextAppearanceDlg::OnBnClickedFreetextcolorButton)
  ON_BN_CLICKED(IDC_FREETEXTFILLCOLOR_BUTTON, &CFreetextAppearanceDlg::OnBnClickedFreetextfillcolorButton)
  ON_CBN_SELCHANGE(IDC_BORDERSTYPE_COMBO, &CFreetextAppearanceDlg::OnCbnSelchangeBorderstypeCombo)
END_MESSAGE_MAP()

void CFreetextAppearanceDlg::UpdateDialog(Annot pAnnot,CWnd* pWnd) {
  m_FreeTextAnnot = (FreeText)pAnnot;
  m_pWnd = pWnd;

  if (m_FreeTextAnnot.IsEmpty()){
    return;
  }

  Annot::Type nType = m_FreeTextAnnot.GetType();
  if (nType == Annot::Type::e_FreeText) {
    foxit::String pIntentString = m_FreeTextAnnot.GetIntent();
    if (pIntentString == "FreeTextTypewriter") {
    UpdateThicknessControl(FALSE);
    UpdateBorderStyleControl(FALSE);
    UpdateColorControl(FALSE);
    UpdateLineStyleControl(FALSE);
    }
    else if (pIntentString == "FreeTextCallout")
    {
    UpdateThicknessControl(TRUE);
    UpdateBorderStyleControl(TRUE);
    UpdateColorControl(TRUE);
    UpdateLineStyleControl(TRUE);
    }
    else
    {
    UpdateThicknessControl(TRUE);
    UpdateBorderStyleControl(TRUE);
    UpdateColorControl(TRUE);
    UpdateLineStyleControl(FALSE);
    }
  }
  else {
    UpdateThicknessControl(TRUE);
    UpdateBorderStyleControl(TRUE);
    UpdateColorControl(TRUE);
    UpdateLineStyleControl(TRUE);
  }

  //BorderWidth
  BorderInfo borderInfo = m_FreeTextAnnot.GetBorderInfo();
  m_nThickness = (int)borderInfo.width;

  //BorderStyle
  m_borderStyleCtrl.SetCurSel(borderInfo.style);

  foxit::RGB colorBorder = m_FreeTextAnnot.GetBorderColor();
  COLORREF crRGB = RGB((colorBorder >>16) &0xff, (colorBorder >>8) &0xff, (colorBorder) &0xff);
  m_color.SetFaceColor(crRGB);

  //FillColor
  foxit::RGB crFillArgb = m_FreeTextAnnot.GetFillColor();
  crRGB = RGB((crFillArgb >>16) &0xff, (crFillArgb >>8) &0xff, (crFillArgb) &0xff);
  m_fillColor.SetFaceColor(crRGB);

  float fOpacity = m_FreeTextAnnot.GetOpacity();
  m_nOpacity = (int)(fOpacity * 100.0f + 0.5);
  m_bIsFirstSet = TRUE;
  m_OpacitySplider.SetPos(m_nOpacity);

  if ("FreeTextCallout" == m_FreeTextAnnot.GetIntent()) {
    Markup::EndingStyle calloutLineEndingStyle = m_FreeTextAnnot.GetCalloutLineEndingStyle();
    m_lineEndingStyleCtrl.SetCurSel(calloutLineEndingStyle);
  } else {
    m_lineEndingStyleCtrl.SetCurSel((int)Markup::e_EndingStyleNone);
  }

  UpdateData(FALSE);
}

void CFreetextAppearanceDlg::UpdateThicknessControl(BOOL bIsEnable) {
  GetDlgItem(IDC_THICKNESS_STATIC)->EnableWindow(bIsEnable);
  GetDlgItem(IDC_BORDERWIDTH_EDIT)->ShowWindow(bIsEnable);
  GetDlgItem(IDC_THICKNESS_SPIN)->ShowWindow(bIsEnable);
}

void CFreetextAppearanceDlg::UpdateBorderStyleControl(BOOL bIsEnable) {
  GetDlgItem(IDC_BORDERSTYPE_STATIC)->EnableWindow(bIsEnable);
  GetDlgItem(IDC_BORDERSTYPE_COMBO)->ShowWindow(bIsEnable);
}

void CFreetextAppearanceDlg::UpdateColorControl(BOOL bIsEnable) {
  GetDlgItem(IDC_STATIC)->EnableWindow(bIsEnable);
  GetDlgItem(IDC_FREETEXTCOLOR_BUTTON)->ShowWindow(bIsEnable);
  GetDlgItem(IDC_FREETEXT_FILLCOLOR_STATIC)->ShowWindow(bIsEnable);
  GetDlgItem(IDC_FREETEXTFILLCOLOR_BUTTON)->ShowWindow(bIsEnable);
}

void CFreetextAppearanceDlg::UpdateLineStyleControl(BOOL bIsEnable) {
  GetDlgItem(IDC_FREETEXT_LINESTYPE_STATIC)->EnableWindow(bIsEnable);
  GetDlgItem(IDC_FREETEXTLINESTYLE_COMBO)->ShowWindow(bIsEnable);
}

void CFreetextAppearanceDlg::OnDeltaposThicknessSpin(NMHDR *pNMHDR, LRESULT *pResult) {
  LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

  if (pNMUpDown->iDelta == 1) { //down
    m_nThickness --;
    if (m_nThickness < 1) {
      m_nThickness = 1;
    }
  } else if (pNMUpDown->iDelta == -1) { //up
    m_nThickness ++;
  }

  if (m_nThickness > 12) {
    m_nThickness = 1;
  }

  BorderInfo borderInfo = m_FreeTextAnnot.GetBorderInfo();
  if (borderInfo.width != m_nThickness) {
    borderInfo.width = (float)m_nThickness;
    m_FreeTextAnnot.SetBorderInfo(borderInfo);
    m_FreeTextAnnot.ResetAppearanceStream();
    m_pWnd->Invalidate();
  }

  UpdateData(FALSE);
  *pResult = 0;
}

void CFreetextAppearanceDlg::OnEnChangeBorderwidthEdit()
{
  UpdateData(TRUE);

  if (m_nThickness > 12) {
    m_nThickness = 12;
    UpdateData(FALSE);
  }

  BorderInfo borderInfo = m_FreeTextAnnot.GetBorderInfo();
  if (borderInfo.width != m_nThickness) {
    borderInfo.width = (float)m_nThickness;
    m_FreeTextAnnot.SetBorderInfo(borderInfo);
    m_FreeTextAnnot.ResetAppearanceStream();
    m_pWnd->Invalidate();
  }
}

void CFreetextAppearanceDlg::OnNMCustomdrawFreetextopacitySlider(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
  int nPos = m_OpacitySplider.GetPos();
  if (!m_bIsFirstSet) {
   if(m_nOpacity != nPos){
    m_nOpacity = nPos;
    UpdateData(FALSE);
    OnEnChangeFreetextopacityEdit();
    }
  } else 
    m_bIsFirstSet = FALSE;

  *pResult = 0;
}

void CFreetextAppearanceDlg::OnEnChangeFreetextopacityEdit()
{
  UpdateData(TRUE);

  if (m_nOpacity > 100) {
    m_nOpacity = 100;
    UpdateData(FALSE);
  }

  float fOpacity = (float)m_nOpacity;

  fOpacity = fOpacity / 100;
  m_FreeTextAnnot.SetOpacity(fOpacity);
  m_FreeTextAnnot.ResetAppearanceStream();

  m_pWnd->Invalidate();
  m_OpacitySplider.SetPos(m_nOpacity);
}

void CFreetextAppearanceDlg::OnCbnSelchangeFreetextlinestyleCombo() {
  int nSel = m_lineEndingStyleCtrl.GetCurSel();
  if ("FreeTextCallout" == m_FreeTextAnnot.GetIntent())
    m_FreeTextAnnot.SetCalloutLineEndingStyle((Markup::EndingStyle)nSel);
  m_FreeTextAnnot.ResetAppearanceStream();
  m_pWnd->Invalidate();
}

void CFreetextAppearanceDlg::OnBnClickedFreetextcolorButton() {
  CColorDialog colorDlg;
  if( colorDlg.DoModal() == IDOK ) {
    COLORREF crRGB = colorDlg.GetColor();
    foxit::RGB crSetColor = 0;
    BYTE R = GetRValue(crRGB);
    BYTE G = GetGValue(crRGB);
    BYTE B = GetBValue(crRGB);
    COLORREF temp = RGB(B, G, R);
    temp = temp | 0xff000000;
    crSetColor = temp | crSetColor;
    m_FreeTextAnnot.SetBorderColor(crSetColor);
    m_FreeTextAnnot.ResetAppearanceStream();
    m_color.SetFaceColor(crRGB);
    m_pWnd->Invalidate();
  }
}

void CFreetextAppearanceDlg::OnBnClickedFreetextfillcolorButton()
{
  CColorDialog colorDlg;
  if( colorDlg.DoModal() == IDOK ) {
    COLORREF crRGB = colorDlg.GetColor();
    foxit::RGB crSetColor = 0;
    BYTE R = GetRValue(crRGB);
    BYTE G = GetGValue(crRGB);
    BYTE B = GetBValue(crRGB);
    COLORREF temp = RGB(B, G, R);
    temp = temp | 0xff000000;
    crSetColor = temp | crSetColor;
    m_FreeTextAnnot.SetFillColor(crSetColor);
    m_FreeTextAnnot.ResetAppearanceStream();
    m_fillColor.SetFaceColor(crRGB);
    m_pWnd->Invalidate();
  }
}

void CFreetextAppearanceDlg::InitCalloutBorderstyle(int nSel, BorderInfo& borderInfo)
{
  borderInfo.cloud_intensity = -1;
  borderInfo.dash_phase = 0;
  switch (nSel) {
  case BorderInfo::e_Solid:
    break;
  case BorderInfo::e_Dashed:
    borderInfo.dash_phase = 5;
    borderInfo.dashes.Add(3);
    borderInfo.dashes.Add(3);
  break;
  case BorderInfo::e_Cloudy:
    borderInfo.cloud_intensity = 1;
    break;
  }
  m_FreeTextAnnot.SetBorderInfo(borderInfo);
}

void CFreetextAppearanceDlg::OnCbnSelchangeBorderstypeCombo()
{
  BorderInfo borderInfo = m_FreeTextAnnot.GetBorderInfo();
  foxit::String pIntentString = m_FreeTextAnnot.GetIntent();
  borderInfo.cloud_intensity = 1;

  int nSel = m_borderStyleCtrl.GetCurSel();
  if (borderInfo.style != nSel) {
    borderInfo.style = (BorderInfo::Style)nSel;
    InitCalloutBorderstyle(nSel, borderInfo);
    m_FreeTextAnnot.ResetAppearanceStream();
    m_pWnd->Invalidate();
  }
}

void CFreetextAppearanceDlg::EnableWindowDlg(BOOL bEnable)
{
  GetDlgItem(IDC_BORDERWIDTH_EDIT)->EnableWindow(bEnable);
  GetDlgItem(IDC_THICKNESS_SPIN)->EnableWindow(bEnable);
  GetDlgItem(IDC_BORDERSTYPE_COMBO)->EnableWindow(bEnable);
  GetDlgItem(IDC_FREETEXTCOLOR_BUTTON)->EnableWindow(bEnable);
  GetDlgItem(IDC_FREETEXTFILLCOLOR_BUTTON)->EnableWindow(bEnable);
  GetDlgItem(IDC_FREETEXTLINESTYLE_COMBO)->EnableWindow(bEnable);
  GetDlgItem(IDC_FREETEXTOPACITY_EDIT)->EnableWindow(bEnable);
  GetDlgItem(IDC_FREETEXTOPACITY_SLIDER)->EnableWindow(bEnable);
}

BOOL CFreetextAppearanceDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();
  m_OpacitySplider.SetRange(0, 100);
  m_color.m_bDontUseWinXPTheme = TRUE;
  m_color.m_bTransparent = FALSE;
  m_fillColor.m_bDontUseWinXPTheme = TRUE;
  m_fillColor.m_bTransparent = FALSE;
  return TRUE;
}
