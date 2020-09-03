#pragma once

#include "PDFReader/Framework/interface/IApp.h"
#include "pdf/annots/fs_annot.h"

struct TextRectInfo {
  foxit::RectF text_rect;
  foxit::common::Rotation baseline_rotation;
};


class CReader_Page {
public:
  enum LinkType {
    NOLINK =0,
    ANNOTLINK = 1,
    TEXTLINK = 2
  };
 public:
  CReader_Page()
      : m_nIndex(0)
      , m_fHeight(0)
      , m_fWidth(0)
      , m_fTotalHeight(0)
      , m_bHasTransparency(FALSE) {}

  virtual ~CReader_Page();

  PDFPage GetPDFPage();
  XFAPage GetXFAPage();

  void SetPDFPage(PDFPage pdf_page);
  void SetXFAPage(XFAPage xfa_page);

  BOOL ParsePage(bool bReparse);

  int GetPageIndex();

  void InitPageinks();
  TextLink GetTextLinkAtPos(const foxit::PointF& pt);
  Link GetAnnotLinkAtPos(const foxit::PointF& pt);
  void SetPageIndex(int nIndex);
  void SetPageHeight(float fHeight);
  void SetPageWidth(float fWidth);
  void SetPageTotalHeightWithOutSpace(float fTotalHeight);

  float GetPageTotalHeightWithSpace(float zoom);
  float GetPageHeight();
  float GetPageWidth();
  BOOL IsHasTransparency();
  BOOL AddAnnot(Annot::Type annotType, std::vector<TextRectInfo> text_rectinfo);
  BOOL AddAnnot(Annot::Type annotType, foxit::RectF rectAnnot);
  Annot GetAnnotAtPoint(CPoint point, foxit::Matrix matrix);

  void ReleaseTempData();

 protected:
  int m_nIndex;
  float m_fHeight;
  float m_fWidth;
  float m_fTotalHeight;
  BOOL m_bHasTransparency;
  std::vector<Link> m_vAnnotLink;
  std::vector<TextLink> m_vTextLinks;
  PageTextLinks m_PageLinks;

  PDFPage m_PDFPage;
  XFAPage m_XFAPage;

private:
  void SetTextMarkupProperties(TextMarkup pTextMarkupAnnot, std::vector<TextRectInfo> text_rectinfo);
  void SetFreeTextProperties(FreeText pFreeTextAnnot, foxit::RectF rectAnnot);
  void SetLinkAnnotProperties(Link pLinkAnnot);

  friend class CReader_Document;
};