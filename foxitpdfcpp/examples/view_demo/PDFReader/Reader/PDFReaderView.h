
// PDFReaderView.h : interface of the CPDFReaderView class
//

#pragma once

#include "PDFReader\Framework\ReaderPage.h"
#include "PDFReader\Reader\AnnotPropertyDlg.h"

class CPDFReaderDoc;

typedef struct _PageToDisplay {
  int cx;     //the position of horizontal scroll bar
  int cy;     //the position of vertical scroll bar
  int page_index;  //page index
} PageToDisplay;




struct XFA_CARETINFO
{
  XFA_CARETINFO()
    :bVisible(FALSE)
    , nPageIndex(0)
    , bHorz(FALSE) {
  }

  int nPageIndex;
  BOOL bVisible;
  foxit::RectF rtAnchor;
  BOOL bHorz;
};

class CPDFReaderView : public CView
{
 protected: // create from serialization only
  CPDFReaderView();
  DECLARE_DYNCREATE(CPDFReaderView)

// Attributes
public:
  enum UnicodeSupportType {
    SUPPORT_UNICODE = 0,
    NOT_SUPPORT_UNICODE = 1,
    NOT_CHECK_SUPPORT  = 2,
  };
  enum OperatorType{
    UNKNOWN = 0,
    DRAWINGANNOT,
    HAND,
    TextPage ,
    TEXTSEARCH ,
    DRAWINGPSI,
    ANNOTSELECT,
    AUTOSCROLL,
  };
  enum AnnotMenuItem {
    ANNOT_ITEM_PROPERTIES = 1,
    ANNOT_ITEM_DELETE,
  };
  enum TextMenuItem {
    TEXT_ITEM_COPY = 1
  };


  CPDFReaderDoc* GetDocument() const;
  virtual ~CPDFReaderView();

  BOOL HasAviliableDoc() const;

// Operations
public:
  bool IsVisiblePage(int index);
  int GetCurVisiblePageIndex();
  Rotation GetRotate();
  float GetScale();

  int GetPageSpace();
  CRect GetPageRect(int page_index);
  void InitScrollSize(int nLogPixelX, int nLogPixelY);
  void SetVisiblePageByScrollPos(int vPos = 0);
  void SetVisiblePageByIndex(int nIndex);
  void SetVisiblePageByIndex(int nIndex,float nHeight, float nWidth);
  BOOL ResetCurrentPageIndex();
  void MovePage(CPoint curPoint, CPoint toPoint);
  void MovePage(short zDelta);
  void GotoDestination(Destination dest);
  float GetStartXPosWithMargin(int nPage);
  void RenderPage(CDC* pDC, int Index, int Width, int Height, int cx, int cy);
  void RenderPageByGE(CDC* pDC, int Index, int Width, int Height, int cx, int cy, bool bIsForPrint = false);
  void RenderPageByDC(CDC * pDC, int Index, int Width, int Height, int cx, int cy);
  void RenderPageTile(CDC * pDC, int Index, int pageWidth, int pageHeight, int renderWidth, int renderHeight, int cx, int cy,int rendercx,int rendercy);
  CReader_Page* GetPage(CPoint point,float fZoom);
  foxit::Matrix GetPageMatrix(int nPageIndex);
  foxit::Matrix GetPageMatrixForPrint(int nPageIndex);
  bool DocToWindow(int nPageIndex, const foxit::RectF& rcDoc, CRect& rcWindow);
  bool DocToWindow(int nPageIndex, const foxit::PointF& ptDoc, CPoint& ptWindow);
  bool WindowToDoc(int nPageIndex, const CPoint& ptWindow, foxit::PointF& ptDoc);
  bool WindowToDoc(int nPageIndex, const CRect& rcWindow, foxit::RectF& rcDoc);
  bool WindowToDocForPrint(int nPageIndex, const CRect& rcWindow, foxit::RectF& rcDoc);

  void GetAnnotWindowRect(Annot annot,CRect& rcWindow);
  void AnnotWindowRectToDocRect(Annot annot,const CRect rcWindow, foxit::RectF & rcDoc);

  void ReleasePageCacheData(int iPageStart, int iPgaeEnd);
  void SearchText(int nPageIndex, std::vector<foxit::RectF> rect_array);
  void CleanSearch();

  bool GetPageDisplayMatrix(int nPageIndex,foxit::Matrix& page_matrix) ;
  void DoAction(Action action);

  void DisplayCaret(int pageIndex, BOOL bVisible, const foxit::RectF& pRtAnchor);

  TimerCallback* GetTimerCallback() {
    return m_pTimerCallback;
  }
  void SetTimerCallbakc(TimerCallback* timer_callback) {
    m_pTimerCallback = timer_callback;
  }

  void SetFocusXFAWidget(XFAWidget xfa_widget) {
    m_FocusXFAWidget = xfa_widget;
  }

  int m_nLogPixelX;
  int m_nLogPixelY;
  Rotation m_Rotate;

 private:
  void TriggerPageOpenAction(int index);
  void TriggerPageCloseAction(int index);
  void TriggerPageAction();

  bool IsInPageDisplayVector(int index, const std::vector<PageToDisplay>& vec);
  void CopyPageDisplayData(const std::vector<PageToDisplay>& src, std::vector<PageToDisplay>& dest);

protected:
  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnDraw(CDC* pDC);  // overridden to draw this view
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual void OnInitialUpdate();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  void DrawAutoScrollReminder(CDC* pDC);
  void DrawTextRect(CDC* pDC, const foxit::RectF& rect, int nPageIndex);
  void DrawSelectText(CDC* pDC);
  void DrawFindText(CDC* pDC);
  bool GetSelectTextCharIndex(const CPoint& point, int& index);

  TimerCallback* m_pTimerCallback;
  XFAWidget m_FocusXFAWidget;
  foxit::PointF m_ptPop;
  XFAWidget m_HoverXFAWidget;

  XFA_CARETINFO m_CaretInfo;

  SCROLLINFO m_Horzsi;
  SCROLLINFO m_Vertsi;

  float m_fZoom;
  float m_fLastZoom;

  bool m_bScrollFlag;
  bool m_bRatateChange;
  bool m_bZoomChange;
  std::vector<PageToDisplay> m_vecPageToDisplay;
  std::vector<PageToDisplay> m_prev_vecPageToDisplay;

  //for page box
  foxit::RectF m_rPageArea;
  int m_nCurPageIndex;
  int m_nBoxPage;
  int m_nStartPageIndex;  // the first page to ScrollPos
  int m_nEndPageIndex;

  int m_nTextPagePage;
  std::vector<TextRectInfo> m_vSelectRectInfo;
  std::vector<foxit::RectF> m_vSearchRect;
  TextLink m_CurrentTextLink;
  Link m_CurrentAnnotLink;
  CReader_Page::LinkType m_eCurPageLinkType;


protected:
  void OnZoom(float zoom);;

  afx_msg void OnFilePrint();
  afx_msg void OnZoomIn();
  afx_msg void OnZoomOut();

  afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
  afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);

  //{{AFX_MSG(CPDFDisplayView)
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  afx_msg void OnACWRotation();
  afx_msg void OnCWRotae();
  afx_msg void OnTimer(UINT_PTR nIDEvent);

  afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
  afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
  afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
  afx_msg void OnFileSaveAs();
  afx_msg void OnFileSave();

  afx_msg void OnFirstPage();
  afx_msg void OnPrevPage();
  afx_msg void OnGotoPage();
  afx_msg void OnNextPage();
  afx_msg void OnLastPage();

  afx_msg void OnUpdateFirstPage(CCmdUI* pCmdUI);
  afx_msg void OnUpdatePrevPage(CCmdUI* pCmdUI);
  afx_msg void OnUpdateNextPage(CCmdUI* pCmdUI);
  afx_msg void OnUpdateLastPage(CCmdUI* pCmdUI);

  afx_msg void OnUpdatePDFSearch(CCmdUI* pCmdUI);
  afx_msg void OnUpdatePDFSelect(CCmdUI* pCmdUI);
  afx_msg void OnUpdatePDFHand(CCmdUI* pCmdUI);
  afx_msg void OnPDFSelect();
  afx_msg void OnPDFSearch();
  afx_msg void OnPDFHand();
  afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
  afx_msg void OnMButtonDown(UINT nFlags, CPoint point);

  afx_msg void OnFilePrintPreview();
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  DECLARE_MESSAGE_MAP()

  afx_msg void OnAnnotFreetext();
  afx_msg void OnAnnotHighlight();
  afx_msg void OnAnnotNotes();
  afx_msg void OnAnnotLink();
  afx_msg void OnAnnotUnderline();
  afx_msg void OnSlider();
  afx_msg void OnToolAnnotselect();

  afx_msg void OnUpdateAnnotFreetext(CCmdUI* pCmdUI);
  afx_msg void OnUpdateAnnotHighlight(CCmdUI* pCmdUI);
  afx_msg void OnUpdateAnnotNotes(CCmdUI* pCmdUI);
  afx_msg void OnUpdateAnnotLink(CCmdUI* pCmdUI);
  afx_msg void OnUpdateAnnotUnderline(CCmdUI* pCmdUI);
  afx_msg void OnUpdateToolAnnotselect(CCmdUI* pCmdUI);

  afx_msg void OnCopy();
  afx_msg void OnCut();
  afx_msg void OnDelete();
  afx_msg void OnSelectAll();
  afx_msg void OnDeSelect();
  afx_msg void OnUndo();
  afx_msg void OnRedo();
  afx_msg void OnPaste();
  afx_msg void OnBold();
  afx_msg void OnItalic();
  afx_msg void OnUnderLine();
  afx_msg void OnSuperScript();
  afx_msg void OnSubScript();
  afx_msg void OnClearStyle();
  foxit::WString m_wsCopyOrCutString;

private:
  void SetOperatorType(OperatorType operatorType);
  OperatorType CPDFReaderView::GetOperatorType();
  BOOL IsInPageRect(CPoint point);
  void DoAnnotButtonDown(CPoint point);
  void DoAnnotLButtonUp(CPoint point);
  void DoAnnotLButtonDblClk(CPoint point);
  void DoPageLinkLButtonDown(CPoint point);
  void DoAnnotDrawBorder(CDC* pDC);
  void OnAnnotTextEditKillFocus();
  void DoLinkAnnotLButtonDblClk(Link link, CPoint point);
  void DoFreetextAnnotLButtonDblClk(FreeText freetext, CPoint point);

  void DoAnnotMouseMove(UINT nFlags, CPoint point);
  void DoSelectMouseMove(UINT nFlags, CPoint point);
  void ShowAnnotSelectContextMenu(const CPoint& point);
  void ShowTextPageContextMeun(const CPoint& point);

  void SetClipboardData(foxit::WString csText);
  BOOL IsSupportUnicodeSel();

  void PrepareSelectdata();

  Annot::Type  m_DrawingAnnotType;
  OperatorType m_OperatorType;
  CPoint m_StartPt;
  CPoint m_EndPt;
  UINT_PTR m_TimerID;
  BOOL m_bFixedAutoScroll;

  int m_nStartCharIndex;
  int m_nEndCharIndex;
  Annot m_FocusAnnot;
  CPoint m_CurPt;
  BOOL m_bLButtonDown;
  CAnnotPropertyDlg* m_pAnnotPropertyDlg;
  CEdit* m_pEdit;
  CString m_strFreetextContent;
  CFont* m_pFreeTextAnnotEditFont;
  BOOL m_bAnnotIsEdit;
  UnicodeSupportType m_eUnicodeSupportType;
  foxit::WString m_wsSelectText;
  BOOL m_bPrepareLabels;
public:
  afx_msg void OnDestroy();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnMenu();
  afx_msg void OnXfaFlattentopdf();
};

#ifndef _DEBUG  // debug version in PDFReaderView.cpp
inline CPDFReaderDoc* CPDFReaderView::GetDocument() const
   { return reinterpret_cast<CPDFReaderDoc*>(m_pDocument); }
#endif

