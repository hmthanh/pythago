#ifndef _IREADER_ANNOT_
#define _IREADER_ANNOT_
#include "PDFReader/Framework/interface/IApp.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////
//class  IReader_Annot
/////////////////////////////////////////////////////////////////////////////////////////////////////
class IReader_Page;
class CDataType;
class IReader_AnnotHandler;
class IReader_Annot : public CDataType {
 public:
  virtual ~IReader_Annot() {}

  virtual CString GetDataType() {
    return ANNOTATION;
  }

  virtual FSAnnot* GetPDFAnnot() = 0;

  virtual CString GetType() = 0;

  virtual CString GetSubType() = 0;

  virtual BOOL IsSelected() = 0;

  virtual void SetSelected(BOOL bSelected) = 0;

  virtual BOOL IsCaptured() = 0;

  virtual void SetCaptured(BOOL bCaptured) = 0;

  virtual CRect GetViewBBox() = 0;

  virtual CRect GetInnerRectMargin() = 0;

  virtual BOOL IsLock() = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
class IReader_AnnotHandlerMgr {
 public:
  virtual ~IReader_AnnotHandlerMgr() {}

  virtual IReader_Annot* NewAnnot(FSAnnot* pdfAnnot, IReader_Page* pPage) = 0;

  virtual void Annot_OnLoad(IReader_Annot* pAnnot) = 0;

  virtual CRect Annot_OnGetViewBBox(IReader_Page* pPage, IReader_Annot* pAnnot) = 0;

  // Mouse events
  virtual BOOL Annot_OnHitTest(IReader_Page* pPage, IReader_Annot* pAnnot, const CPoint& point) = 0;

  virtual void RegisterAnnotHandler(IReader_AnnotHandler* pAnnotHandler) = 0;
};

class IReader_AnnotHandler {
 public:
  virtual ~IReader_AnnotHandler() {}
  virtual IReader_Annot* NewAnnot(FSAnnot* pdfAnnot, IReader_Page* pPage) = 0;

  //return  annotation type name,for example: "Line"
  virtual CString GetType() = 0;

  //return AnnotHandler unique identification,for example:"LineAnnotHandler"
  virtual CString GetName() = 0;

  // get position of annotation,it can be real position,also can be zoomed in properly,
  // this position is also UpdateAllViews's reference position.
  virtual CRect GetViewBBox(IReader_Page* pPage, IReader_Annot* pAnnot) = 0;

  virtual BOOL HitTest(IReader_Page* pPage, IReader_Annot* pAnnot, const CPoint& point) = 0;

  //return TRUE means have done,framework doesn't deal with .
  virtual BOOL OnLButtonDown(IReader_Page* pPage, IReader_Annot* pAnnot, UINT nFlags, const CPoint& point) = 0;
  virtual BOOL OnLButtonUp(IReader_Page* pPage, IReader_Annot* pAnnot, UINT nFlags, const CPoint& point) = 0;
  virtual BOOL OnLButtonDblClk(IReader_Page* pPage, IReader_Annot* pAnnot, UINT nFlags, const CPoint& point) = 0;
  virtual BOOL OnMouseMove(IReader_Page* pPage, IReader_Annot* pAnnot, UINT nFlags, const CPoint& point) = 0;
  virtual BOOL OnMouseWheel(IReader_Page* pPage, IReader_Annot* pAnnot, UINT nFlags, short zDelta,
                            const CPoint& point) = 0;
  virtual BOOL OnRButtonDown(IReader_Page* pPage, IReader_Annot* pAnnot, UINT nFlags, const CPoint& point) = 0;
  virtual BOOL OnRButtonUp(IReader_Page* pPage, IReader_Annot* pAnnot, UINT nFlags, const CPoint& point) = 0;
  virtual BOOL OnRButtonDblClk(IReader_Page* pPage, IReader_Annot* pAnnot, UINT nFlags, const CPoint& point) = 0;

  virtual void Annot_OnDraw(IReader_Page* pPage, HDC hDC, IReader_Annot* pAnnot, FSMatrix matrix,
                            const CRect& rcPage) = 0;
};

#endif