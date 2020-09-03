// NoteAppearanceDlg.cpp : implementation file
//

#include "PDFReader.h"
#include "AnnotAppearanceDlg.h"
#include "afxdialogex.h"


// CNoteAppearanceDlg dialog

IMPLEMENT_DYNAMIC(CAnnotAppearanceDlg, CDialogEx)

CAnnotAppearanceDlg::CAnnotAppearanceDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(CAnnotAppearanceDlg::IDD, pParent)
  , m_pWnd(NULL)
  , m_nOpacity(0) {}

CAnnotAppearanceDlg::~CAnnotAppearanceDlg() {}

void CAnnotAppearanceDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_COLOR_BUTTON, m_colorCtrl);
  DDX_Text(pDX, IDC_OPACITY_EDIT, m_nOpacity);
  DDX_Control(pDX, IDC_OPACITY_SLIDER, m_opacitySliderCtrl);
  DDX_Control(pDX, IDC_NOTETYPE_COMBO, m_noteTypeCtrl);
}


BEGIN_MESSAGE_MAP(CAnnotAppearanceDlg, CDialogEx)
  ON_BN_CLICKED(IDC_COLOR_BUTTON, &CAnnotAppearanceDlg::OnBnClickedColorButton)
  ON_EN_CHANGE(IDC_OPACITY_EDIT, &CAnnotAppearanceDlg::OnEnChangeOpacityEdit)
  ON_NOTIFY(NM_CUSTOMDRAW, IDC_OPACITY_SLIDER, &CAnnotAppearanceDlg::OnNMCustomdrawOpacitySlider)
  ON_CBN_SELENDCANCEL(IDC_NOTETYPE_COMBO, &CAnnotAppearanceDlg::OnCbnSelendcancelNotetypeCombo)
END_MESSAGE_MAP()

int CAnnotAppearanceDlg::GetSelFromNoteStyle(const char* noteStyle) {
  if ( 0 == strcmp("Check", noteStyle)) {
    return 0;
  } else if (0 == strcmp("Circle", noteStyle)) {
    return 1;
  } else if (0 == strcmp("Comment", noteStyle)) {
    return 2;
  } else if (0 == strcmp("Cross", noteStyle)) {
    return 3;
  } else if (0 == strcmp("Help", noteStyle)) {
    return 4;
  } else if (0 == strcmp("Insert", noteStyle)) {
    return 5;
  } else if (0 == strcmp("Key", noteStyle)) {
    return 6;
  } else if ( 0 == strcmp("NewParagraph", noteStyle)) {
    return 7;
  } else if ( 0 == strcmp("Note", noteStyle)) {
    return 8;
  } else if ( 0 == strcmp("Paragraph", noteStyle)) {
    return 9;
  } else if ( 0 == strcmp("RightArrow", noteStyle)) {
    return 10;
  } else if ( 0 == strcmp("RightPointer", noteStyle)) {
    return 11;
  } else if ( 0 == strcmp("Star", noteStyle)) {
    return 12;
  }else if ( 0 == strcmp("UpArrow", noteStyle)) {
    return 13;
  }else if ( 0 == strcmp("UpLeftArrow", noteStyle)) {
    return 14;
  }
  return 0;
}

char* CAnnotAppearanceDlg::GetNoteStyleFromSel(int nSel)
{
  switch(nSel) {
  case 0:
    return "Check";
  case 1:
    return "Circle";
  case 2:
    return "Comment";
  case 3:
    return "Cross";
  case 4:
    return "Help";
  case 5:
    return "Insert";
  case 6:
    return "Key";
  case 7:
    return "NewParagraph";
  case 8:
    return "Note";
  case 9:
    return "Paragraph";
  case 10:
    return "RightArrow";
  case 11:
    return "RightPointer";
  case 12:
    return "Star";
  case 13:
    return "UpArrow";
  case 14:
    return "UpLeftArrow";
  }
  return "";
}

void CAnnotAppearanceDlg::UpdateDialog(Annot annot, CWnd* pWnd)
{
  if (annot.IsEmpty() && !pWnd) {
    return;
  }
  
  m_Annot = annot;
  m_pWnd = pWnd;

  //Color
  foxit::RGB borderColor = m_Annot.GetBorderColor();
  COLORREF crRGB = RGB((borderColor >>16) &0xff, (borderColor >>8) &0xff, (borderColor) &0xff);
  m_colorCtrl.SetFaceColor(crRGB);

  if (m_Annot.IsMarkup()) {
    float fOpacity = ((Markup)m_Annot).GetOpacity();
    m_nOpacity = (int)(fOpacity * 100.0f + 0.5);
    m_opacitySliderCtrl.SetPos(m_nOpacity);
    CString strNoteOpacity;
    strNoteOpacity.Format(_T("%d"), m_nOpacity);
    GetDlgItem(IDC_OPACITY_EDIT)->SetWindowTextW(strNoteOpacity);
  GetDlgItem(IDC_OPACITY_STATIC)->ShowWindow(SW_SHOW);
  GetDlgItem(IDC_OPACITY_SLIDER)->ShowWindow(SW_SHOW);
  GetDlgItem(IDC_OPACITY_EDIT)->ShowWindow(SW_SHOW);
  GetDlgItem(IDC_OPACITYPERCENT_STATIC)->ShowWindow(SW_SHOW);

    UpdateData(FALSE);
  } else {
    GetDlgItem(IDC_OPACITY_STATIC)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_OPACITY_SLIDER)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_OPACITY_EDIT)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_OPACITYPERCENT_STATIC)->ShowWindow(SW_HIDE);
  }

  Annot::Type annotType = m_Annot.GetType();
  if (annotType == Annot::e_Note) {
  m_noteTypeCtrl.SetCurSel(GetSelFromNoteStyle(((Note)m_Annot).GetIconName()));
  m_noteTypeCtrl.ShowWindow(SW_SHOW);
    GetDlgItem(IDC_NOTETYPE_STATIC)->ShowWindow(SW_SHOW);
  } else {
    m_noteTypeCtrl.ShowWindow(SW_HIDE);
    GetDlgItem(IDC_NOTETYPE_STATIC)->ShowWindow(SW_HIDE);
  }

  UpdateData(FALSE);
}

// CNoteAppearanceDlg message handlers
void CAnnotAppearanceDlg::OnBnClickedColorButton()
{
  CColorDialog colorDlg;
  if( colorDlg.DoModal() == IDOK ) {
    COLORREF crRGB;
    foxit::RGB crFSRgb = 0;
    crRGB = colorDlg.GetColor();
    BYTE R = GetRValue(crRGB);
    BYTE G = GetGValue(crRGB);
    BYTE B = GetBValue(crRGB);
    COLORREF temp = RGB(B, G, R);
    temp = temp | 0xff000000;
    crFSRgb = temp;

    m_Annot.SetBorderColor(crFSRgb);
    m_Annot.ResetAppearanceStream();
    m_pWnd->Invalidate();

    m_colorCtrl.SetFaceColor(crRGB);
  }
}

BOOL CAnnotAppearanceDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();
  m_opacitySliderCtrl.SetRange(0, 100);
  m_colorCtrl.m_bTransparent = FALSE;
  m_colorCtrl.m_bDontUseWinXPTheme = TRUE;
  return TRUE; 
}

void CAnnotAppearanceDlg::EnableWindowDlg(BOOL bEnable)
{
  GetDlgItem(IDC_COLOR_BUTTON)->EnableWindow(bEnable);
  GetDlgItem(IDC_OPACITY_EDIT)->EnableWindow(bEnable);
  GetDlgItem(IDC_OPACITY_SLIDER)->EnableWindow(bEnable);
  GetDlgItem(IDC_NOTETYPE_COMBO)->EnableWindow(bEnable);
}

void CAnnotAppearanceDlg::OnEnChangeOpacityEdit()
{
  UpdateData(TRUE);

  if (m_nOpacity > 100) {
    m_nOpacity = 100;
    UpdateData(FALSE);
  }

  float fOpacity = (float)m_nOpacity;
  fOpacity = fOpacity / 100;
  Markup markup_annot = (Markup)(m_Annot);
  if (!markup_annot.IsEmpty()) {
    markup_annot.SetOpacity(fOpacity);
  }
  markup_annot.ResetAppearanceStream();

  m_opacitySliderCtrl.SetPos(m_nOpacity);
  m_pWnd->Invalidate();
}


void CAnnotAppearanceDlg::OnNMCustomdrawOpacitySlider(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
  int nPos = m_opacitySliderCtrl.GetPos();
  m_nOpacity = nPos;
  UpdateData(FALSE);
  OnEnChangeOpacityEdit();
  *pResult = 0;
}


void CAnnotAppearanceDlg::OnCbnSelendcancelNotetypeCombo() {
  int nSel = m_noteTypeCtrl.GetCurSel();

  char* iconName = GetNoteStyleFromSel(nSel);
  Note pnote_annot = (Note)m_Annot;
  if (!pnote_annot.IsEmpty()) {
    pnote_annot.SetIconName(iconName);
    pnote_annot.ResetAppearanceStream();
  }
  
  m_pWnd->Invalidate();
}
