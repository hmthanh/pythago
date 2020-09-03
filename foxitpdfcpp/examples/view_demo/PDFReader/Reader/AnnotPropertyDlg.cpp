// AnnotPropertyDlg.cpp : implementation file
//

#include "PDFReader.h"
#include "AnnotPropertyDlg.h"
#include "afxdialogex.h"
#include "AnnotAppearanceDlg.h"

// CAnnotPropertyDlg dialog

IMPLEMENT_DYNAMIC(CAnnotPropertyDlg, CDialogEx)

CAnnotPropertyDlg::CAnnotPropertyDlg(Annot pdf_annot, CWnd* pParent /*=NULL*/)
    : CDialogEx(CAnnotPropertyDlg::IDD, pParent)
    , m_bLocked(FALSE)
    , m_FocusAnnot(pdf_annot) {
  memset(m_pAnnotProperty, 0, sizeof(m_pAnnotProperty));
}

CAnnotPropertyDlg::~CAnnotPropertyDlg() {}

void CAnnotPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_ANNOT_PROPERTY_TAB, m_AnnotPropertyTab);
  DDX_Check(pDX, IDC_LOCKANNOT_CHECK, m_bLocked);
}


BEGIN_MESSAGE_MAP(CAnnotPropertyDlg, CDialogEx)
  ON_NOTIFY(NM_THEMECHANGED, IDC_ANNOT_PROPERTY_TAB, &CAnnotPropertyDlg::OnNMThemeChangedAnnotPropertyTab)
  ON_NOTIFY(TCN_SELCHANGE, IDC_ANNOT_PROPERTY_TAB, &CAnnotPropertyDlg::OnTcnSelchangeAnnotPropertyTab)
  ON_BN_CLICKED(IDC_CLOSEANNOTPROPERTY_BUTTON, &CAnnotPropertyDlg::OnBnClickedCloseannotpropertyButton)
  ON_BN_CLICKED(IDC_LOCKANNOT_CHECK, &CAnnotPropertyDlg::OnBnClickedLockannotCheck)
END_MESSAGE_MAP()

// CAnnotPropertyDlg message handlers
void CAnnotPropertyDlg::UpdateDialog(CWnd* pWnd) {
  if (m_FocusAnnot.IsEmpty()) {
    EnableWindowDlg(FALSE);
    GetDlgItem(IDC_LOCKANNOT_CHECK)->EnableWindow(FALSE);
    return;
  } else {
    GetDlgItem(IDC_LOCKANNOT_CHECK)->EnableWindow(TRUE);
  }
  
  HideAllPropertyDlg();
  Annot::Type annotType = m_FocusAnnot.GetType();
  int nItem = m_AnnotPropertyTab.GetCurSel();
  if (annotType == Annot::e_FreeText) {
    
  m_pAnnotProperty[0] = &m_freetextAPDlg;
  m_pAnnotProperty[1] = &m_freetextAnnotGEDlg;
  } else if (annotType == Annot::e_Note
        || annotType == Annot::e_Highlight || annotType == Annot::e_Underline
        || annotType == Annot::e_Link) {
    m_pAnnotProperty[0] = &m_notesAPDlg;
  m_pAnnotProperty[1] = &m_freetextAnnotGEDlg;
  }
  else {
    m_pAnnotProperty[0] = &m_notesAPDlg;
  m_pAnnotProperty[1] = &m_freetextAnnotGEDlg;
  }

  m_AnnotPropertyTab.SetCurSel(nItem);
  m_nSelectTab = m_AnnotPropertyTab.GetCurSel();
  for (int i=0; i<sizeof(m_pAnnotProperty)/sizeof(m_pAnnotProperty[0]); i++) {
    CDialogEx* pItem = m_pAnnotProperty[i];
  if (pItem == NULL)
    continue;
  
  IAnnotPropertyUITab* pAnnotPropertyUITab = dynamic_cast<IAnnotPropertyUITab*>(pItem);
  if (pAnnotPropertyUITab)
      pAnnotPropertyUITab->UpdateDialog(m_FocusAnnot, pWnd);
  
  if (i == m_nSelectTab)
      pItem->ShowWindow(SW_SHOW);
  }

  m_bLocked = m_FocusAnnot.GetFlags() & Annot::e_FlagLocked? TRUE:FALSE;
  EnableWindowDlg(!m_bLocked);

  SetWindowText(_T("Property"));
  UpdateData(FALSE);
}

void CAnnotPropertyDlg::EnableWindowDlg(BOOL bEnable)
{
  if (m_FocusAnnot.IsEmpty()) return;

  int nCurSel = m_AnnotPropertyTab.GetCurSel();
  for (int i=0; i<sizeof(m_pAnnotProperty)/sizeof(m_pAnnotProperty[0]); i++) {
    CDialogEx* pItem = m_pAnnotProperty[i];
  if (pItem == NULL)
    continue;
  
  IAnnotPropertyUITab* pAnnotPropertyUITab = dynamic_cast<IAnnotPropertyUITab*>(pItem);
  if (pAnnotPropertyUITab) {
      pAnnotPropertyUITab->EnableWindowDlg(bEnable);
  }
  }
}

void CAnnotPropertyDlg::HideAllPropertyDlg()
{
  m_freetextAPDlg.ShowWindow(SW_HIDE);
  m_notesAPDlg.ShowWindow(SW_HIDE);
  m_freetextAnnotGEDlg.ShowWindow(SW_HIDE);
}

BOOL CAnnotPropertyDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  m_freetextAPDlg.Create(IDD_FREETEXT_AP_DIALOG, GetDlgItem(IDC_ANNOT_PROPERTY_TAB));
  m_notesAPDlg.Create(IDD_ANNOT_AP_DIALOG, GetDlgItem(IDC_ANNOT_PROPERTY_TAB));
  m_freetextAnnotGEDlg.Create(IDD_FREETEXT_GENERAL_DIALOG, GetDlgItem(IDC_ANNOT_PROPERTY_TAB));

  m_AnnotPropertyTab.InsertItem(0, _T("Appearance"));

  m_AnnotPropertyTab.InsertItem(1, _T("General"));

  CRect rc;
  m_AnnotPropertyTab.GetClientRect(&rc);
  rc.left += 4;
  rc.top += 23;
  rc.right -= 4;
  rc.bottom -= 4;
  m_notesAPDlg.MoveWindow(&rc);
  m_freetextAnnotGEDlg.MoveWindow(&rc);
  m_freetextAPDlg.MoveWindow(&rc);
  m_AnnotPropertyTab.SetCurSel(0);

  m_notesAPDlg.ShowWindow(SW_HIDE);

  return TRUE;
}


void CAnnotPropertyDlg::OnNMThemeChangedAnnotPropertyTab(NMHDR *pNMHDR, LRESULT *pResult)
{
  *pResult = 0;
  int Item = m_AnnotPropertyTab.GetCurSel();
  m_pAnnotProperty[Item]->ShowWindow(TRUE);
}


void CAnnotPropertyDlg::OnTcnSelchangeAnnotPropertyTab(NMHDR *pNMHDR, LRESULT *pResult)
{
  *pResult = 0;
  m_pAnnotProperty[m_nSelectTab]->ShowWindow(SW_HIDE);
  m_nSelectTab = m_AnnotPropertyTab.GetCurSel();
  m_pAnnotProperty[m_nSelectTab]->ShowWindow(SW_SHOW);
}


void CAnnotPropertyDlg::OnBnClickedCloseannotpropertyButton()
{
  ShowWindow(SW_HIDE);
}


void CAnnotPropertyDlg::OnBnClickedLockannotCheck()
{
  UpdateData(TRUE);
  EnableWindowDlg(!m_bLocked);

  int flags = m_FocusAnnot.GetFlags();
  int oldFlags = flags;

  if(m_bLocked) {
    flags |= Annot::e_FlagLocked;
  } else {
    flags &= ~Annot::e_FlagLocked;
  }
  
  m_FocusAnnot.SetFlags(flags);
}

void CAnnotPropertyDlg::ChangeFocusAnnot(Annot pdf_annot) {
  m_FocusAnnot = pdf_annot;
}

