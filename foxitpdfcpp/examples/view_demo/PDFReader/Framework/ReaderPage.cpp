#include "PDFReader/Framework/ReaderPage.h"

CReader_Page::~CReader_Page() {
}

PDFPage CReader_Page::GetPDFPage() {
  return m_PDFPage;
}

XFAPage CReader_Page::GetXFAPage() {
  return m_XFAPage;
}

void CReader_Page::SetPDFPage(PDFPage pdf_page) {
  m_PDFPage = pdf_page;
}

void CReader_Page::SetXFAPage(XFAPage xfa_page) {
  m_XFAPage = xfa_page;
}

BOOL CReader_Page::ParsePage(bool bReparse /*= false*/) {
  if (m_PDFPage.IsEmpty()) return FALSE;
  try {
    if (m_PDFPage.IsParsed() && !bReparse) return TRUE;
    m_PDFPage.StartParse(PDFPage::e_ParsePageNormal, NULL, bReparse);
    m_bHasTransparency = m_PDFPage.HasTransparency();
    return TRUE;
  } catch (const foxit::Exception&) {
    AfxMessageBox(_T("Failed to parse page"), MB_ICONWARNING);
  }
  return FALSE;
}

int CReader_Page::GetPageIndex() {
  return m_nIndex;
}

void CReader_Page::InitPageinks() {
  if (m_PageLinks.IsEmpty()) {
    ParsePage(false);
    // TODO: need to adjust later
    //m_PageLinks = PageTextLinks(m_PDFPage);
    //m_vTextLinks.clear();
    //m_vAnnotLink.clear();
    //int textLinkCount = m_PageLinks.GetTextLinkCount();
    //for (int i = 0; i < textLinkCount; i++) {
    //  m_vTextLinks.push_back(m_PageLinks.GetTextLink(i));
    //}
    //int annotLinkCount = m_PageLinks.GetLinkAnnotCount();
    //for (int i = 0; i < annotLinkCount; i++) {
    //  m_vAnnotLink.push_back(m_PageLinks.GetLinkAnnot(i));
    //}
  }
}

TextLink CReader_Page::GetTextLinkAtPos(const foxit::PointF& pt) {
  if (m_PDFPage.IsEmpty()) return TextLink();
  InitPageinks();
  int textLinkCount = m_vTextLinks.size();
  for (int i = 0; i < textLinkCount; i++) {
    TextLink text_link = m_vTextLinks[i];
    foxit::RectFArray rects = text_link.GetRects();
    for (int index = 0; index < rects.GetSize(); index++) {
      foxit::RectF rect = rects[index];
      if (rect.bottom <= pt.y && rect.top >= pt.y && rect.left <= pt.x && rect.right >= pt.x) {
        return text_link;
      }
    }
  }
  return TextLink();
}

Link CReader_Page::GetAnnotLinkAtPos(const foxit::PointF& pt) {
  if (m_PDFPage.IsEmpty()) return Link();
  InitPageinks();
  int annotLinkCount = m_vAnnotLink.size();
  for (int i = 0; i < annotLinkCount; i++) {
    Link link_annot = m_vAnnotLink[i];
    foxit::RectF rect = link_annot.GetRect();
    if (rect.bottom <= pt.y && rect.top >= pt.y && rect.left <= pt.x && rect.right >= pt.x) {
      return link_annot;
    }
  }
  return Link();
}

void CReader_Page::SetPageIndex(int nIndex) {
  m_nIndex = nIndex;
}
void CReader_Page::SetPageHeight(float fHeight) {
  m_fHeight = fHeight;
}
void CReader_Page::SetPageWidth(float fWidth) {
  m_fWidth = fWidth;
}
void CReader_Page::SetPageTotalHeightWithOutSpace(float fTotalHeight) {
  m_fTotalHeight = fTotalHeight;
}

float CReader_Page::GetPageTotalHeightWithSpace(float zoom) {
  return m_fTotalHeight* zoom + (m_nIndex +1)* DEFAULT_PAGESPACE;
}

float CReader_Page::GetPageHeight() {
  return m_fHeight;
}
float CReader_Page::GetPageWidth() {
  return m_fWidth;
}

BOOL CReader_Page::IsHasTransparency() {
  return m_bHasTransparency;
}

BOOL CReader_Page::AddAnnot(Annot::Type annotType, std::vector<TextRectInfo> text_rectinfo) {
  if (m_PDFPage.IsEmpty()) return false;

  Annot new_annot = m_PDFPage.AddAnnot(annotType, foxit::RectF(0,0,0,0));
  new_annot.SetFlags(Annot::e_FlagPrint);

  foxit::FloatArray dashPattern;
  dashPattern.Add(1.0);
  dashPattern.Add(1.0);
  BorderInfo border;
  border.Set(3.0, BorderInfo::e_Dashed, -1, 5, dashPattern);
  new_annot.SetBorderInfo(border);
  new_annot.SetBorderColor(0xFF0000);

  foxit::WString wsAnnotType;
  switch (annotType) {
  case Annot::e_Underline:
    wsAnnotType = L"UnderLine";
    SetTextMarkupProperties((TextMarkup)new_annot, text_rectinfo);
    new_annot.SetBorderColor(0x00FF00);
    break;
  case Annot::e_Highlight:
    wsAnnotType = L"Highlight";
    SetTextMarkupProperties((TextMarkup)new_annot, text_rectinfo);
    ((Highlight)new_annot).SetBorderColor(0x00FFF0);
    ((Highlight)new_annot).SetOpacity(0.5f);
    break;
  }

  new_annot.SetContent(wsAnnotType);

  foxit::DateTime dateTime = foxit::DateTime::GetLocalTime();
  new_annot.SetModifiedDateTime(dateTime);
  if (new_annot.IsMarkup()) {
    Markup markup_annot = (Markup)new_annot;
    markup_annot.SetTitle(wsAnnotType);
    markup_annot.SetSubject(wsAnnotType);
    markup_annot.SetOpacity(1.0f);

    markup_annot.SetCreationDateTime(dateTime);
  }

  new_annot.ResetAppearanceStream();

  return TRUE;
}

void CReader_Page::ReleaseTempData() {
  //m_PageLinks = PageLinks();
  m_vAnnotLink.clear();
  m_vTextLinks.clear();
}

void CReader_Page::SetTextMarkupProperties(TextMarkup textmark_annot, std::vector<TextRectInfo> text_rectinfo) {
  if (textmark_annot.IsEmpty()) return;

  int info_count = text_rectinfo.size();
  QuadPointsArray quadpoints_array;
  for (int i = 0; i < info_count; i++) {
    foxit::RectF pieceRect = text_rectinfo[i].text_rect;
    QuadPoints quadpoints;
    if (text_rectinfo[i].baseline_rotation == e_Rotation0
       || text_rectinfo[i].baseline_rotation == e_Rotation180)  {
        // As rotation = 0, or 180, to draw in the bottom of piece.
      quadpoints.first = foxit::PointF(pieceRect.left, pieceRect.top);
      quadpoints.second = foxit::PointF(pieceRect.right, pieceRect.top);
      quadpoints.third = foxit::PointF(pieceRect.left, pieceRect.bottom);
      quadpoints.fourth = foxit::PointF(pieceRect.right, pieceRect.bottom);
    } else {
      // As rotation = 90, or 270, to draw in the left side of piece.
      quadpoints.first = foxit::PointF(pieceRect.right, pieceRect.top);
      quadpoints.second = foxit::PointF(pieceRect.right, pieceRect.bottom);
      quadpoints.third = foxit::PointF(pieceRect.left, pieceRect.top);
      quadpoints.fourth = foxit::PointF(pieceRect.left, pieceRect.bottom);
    }
    quadpoints_array.Add(quadpoints);
  }
  textmark_annot.SetQuadPoints(quadpoints_array);
}

void CReader_Page::SetFreeTextProperties(FreeText freetext_annot, foxit::RectF rectAnnot) {
  if (freetext_annot.IsEmpty()) return;

  freetext_annot.SetFillColor(0xFFFFFF);
  freetext_annot.SetAlignment(e_AlignmentLeft);
  freetext_annot.SetIntent("FreeTextCallout");

  float width = rectAnnot.Width();
  float height = rectAnnot.Height();

  freetext_annot.SetInnerRect(foxit::RectF(rectAnnot.left + width/2, rectAnnot.bottom + height/2, rectAnnot.right, rectAnnot.top));
  freetext_annot.SetCalloutLineEndingStyle(Markup::e_EndingStyleOpenArrow);
  foxit::PointFArray callout_points;
  foxit::PointF point = foxit::PointF(rectAnnot.left - 3, rectAnnot.bottom - 3);
  callout_points.Add(point);
  point = foxit::PointF(rectAnnot.left + width/4, rectAnnot.top - height/4);
  callout_points.Add(point);
  point = foxit::PointF(rectAnnot.left + width/2, rectAnnot.top - height/4);
  callout_points.Add(point);
  freetext_annot.SetCalloutLinePoints(callout_points);

  foxit::common::Font new_font(L"SimSun", foxit::common::Font::e_StyleFixedPitch, foxit::common::Font::e_CharsetGB2312, 400);
  DefaultAppearance defaultAppearance((DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor),
                                      new_font, 12, 0x00ff00);

  freetext_annot.SetDefaultAppearance(defaultAppearance);
}

void CReader_Page::SetLinkAnnotProperties(Link link_annot) {
  if (link_annot.IsEmpty()) return;

  link_annot.SetHighlightingMode(Annot::e_HighlightingOutline);

  URIAction new_action = (URIAction)Action::Create(link_annot.GetPage().GetDocument(), Action::e_TypeURI);
  new_action.SetURI("www.google.com");
  new_action.SetTrackPositionFlag(TRUE);
  link_annot.SetAction(new_action);
}

Annot CReader_Page::GetAnnotAtPoint(CPoint point, foxit::Matrix matrix) {
  foxit::PointF point_annot;
  point_annot.x = float(point.x);
  point_annot.y = float(point.y);
  return m_PDFPage.GetAnnotAtDevicePoint(point_annot, 10, &matrix);
}

BOOL CReader_Page::AddAnnot(Annot::Type annotType, foxit::RectF rectAnnot) {
  if (m_PDFPage.IsEmpty()) return false;

  Annot new_annot = m_PDFPage.AddAnnot(annotType, rectAnnot);
  new_annot.SetFlags(Annot::e_FlagPrint );

  foxit::FloatArray dashPattern;
  dashPattern.Add(1.0);
  dashPattern.Add(1.0);
  BorderInfo border;
  border.Set(3.0, BorderInfo::e_Dashed, -1, 5, dashPattern);
  new_annot.SetBorderInfo(border);
  new_annot.SetBorderColor(0xFF0000);

  foxit::WString wsAnnotType;
  switch(annotType) {
  case Annot::e_FreeText:
    wsAnnotType = L"FreeText";
    SetFreeTextProperties((FreeText)new_annot, rectAnnot);
    break;
  case Annot::e_Link:
    wsAnnotType = L"Link";
    SetLinkAnnotProperties((Link)new_annot);
    break;
  case  Annot::e_Note:
    wsAnnotType = L"Note";
    ((Note)new_annot).SetIconName("Comment");
    break;
  default :
    wsAnnotType = L"Annot";
    break;
  }

  new_annot.SetContent(wsAnnotType);

  foxit::DateTime dateTime = foxit::DateTime::GetLocalTime();
  new_annot.SetModifiedDateTime(dateTime);
  if (new_annot.IsMarkup()) {
    Markup markup_annot = (Markup)new_annot;
    markup_annot.SetTitle(wsAnnotType);
    markup_annot.SetSubject(wsAnnotType);
    markup_annot.SetOpacity(1.0f);

    markup_annot.SetCreationDateTime(dateTime);
  }

  new_annot.ResetAppearanceStream();

  return TRUE;
}
