
// PDFReaderDoc.h : interface of the CPDFReaderDoc class
//

#pragma once

class CReader_Page;
class CPDFReaderDoc;

class FormFillerAssist: public FillerAssistCallback
{
 public:
  FormFillerAssist(CPDFReaderDoc* pViewerDoc) : m_pViewerDoc(pViewerDoc) {}
  ~FormFillerAssist() {}

  virtual void Release();

  virtual int GetVersion() {return 1;}

  virtual  void Refresh(const PDFPage& page, const foxit::RectF* pdfRect);

  virtual bool  SetTimerCallback(int elapse, TimerCallback* timerFunc, int* timeID);

  virtual bool  KillTimer(int timerID);

  virtual void FocusGotOnControl(const Control& control, const char* filedValue);

  virtual void FocusLostFromControl(const Control& control, const char* filedValue);

 protected:
  CPDFReaderDoc* m_pViewerDoc;
};

class XFADocProvider : public DocProviderCallback
{
 public:
  XFADocProvider(CPDFReaderDoc* pViewerDoc) : m_pViewerDoc(pViewerDoc) {}
  ~XFADocProvider() {}

  virtual void Release();
  virtual void InvalidateRect(int page_index, const foxit::RectF& rect, InvalidateFlag flag);
  virtual void DisplayCaret(int page_index, bool is_visible, const foxit::RectF& rect);
  virtual bool GetPopupPos(int page_index, float min_popup, float max_popup, 
                           const foxit::RectF& rect_widget, foxit::RectF& rect_popup);
  virtual bool PopupMenu(int page_index, const foxit::PointF& rect_popup);
  virtual int GetCurrentPage(const XFADoc& doc);
  virtual void SetCurrentPage(const XFADoc& doc, int current_page_index);
  virtual foxit::WString GetTitle(const XFADoc& doc);
  virtual void SetFocus(XFAWidget& xfaWidget);
  virtual void ExportData(const XFADoc& doc, const foxit::WString& file_path);
  virtual void ImportData(const XFADoc& doc, const foxit::WString& file_path);
  virtual void GotoURL(const XFADoc& doc, const foxit::WString& url);
  virtual void Print(const XFADoc& doc, int start_page_index, int end_page_index, foxit::uint32 options);
  virtual foxit::ARGB GetHighlightColor(const XFADoc& doc);
  virtual bool SubmitData(const XFADoc& doc, const foxit::WString& target, SubmitFormat format, TextEncoding text_encoding, const foxit::WString& content);

  virtual void PageViewEvent(int page_index, foxit::addon::xfa::DocProviderCallback::PageViewEventType page_event);
  virtual void WidgetEvent(const XFAWidget& xfa_widget,WidgetEventType widget_event_type);
  virtual void SetChangeMark(const XFADoc& doc);

 protected:
  CPDFReaderDoc* m_pViewerDoc;
};

class CPDFReaderDoc : public CDocument {
 protected:  // create from serialization only
  CPDFReaderDoc();
  DECLARE_DYNCREATE(CPDFReaderDoc)

  // Attributes
 protected:
  // Operations
 public:
  BOOL LoadPDFDocument(LPCWSTR lpwsFilePath);
  BOOL ReLoadDocument();

  BOOL UpdatePDFPages(int nLogPixelX, int nLogPiexlY, Rotation rotate, bool need_update_page_list = false);

  void FindVisiblePage(float StartPos, float EndPos, int& StartPage, int& EndPage, float zoom);
  PDFDoc GetPDFDocument();
  BOOL HasLoadDocument();
  CString GetFilePath();

  void UpdateCurPage(int index);
  int GetCurPage();

  void Save();
  void SaveAs();

  int GetPageCount();
  void UpdatePageCount();

  CReader_Page* GetPage(int nIndex);

  float GetRealHeight(float zoom);
  float GetRealWidth(float zoom);
  int GetPageShadowWidth();
  int GetPageSpace();

  BOOL isDynamicXFA() {return m_bDynamicXFA;}
  Filler GetFormFiller() {return m_FormFiller;}
  XFADoc GetXFADoc() {return m_XFADoc;}
  Form GetForm() {return m_Form;}

  // Overrides
 public:
  virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
  virtual void OnCloseDocument();
  virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
  virtual void InitializeSearchContent();
  virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif  // SHARED_HANDLERS

  // Implementation
  virtual BOOL IsModified();
  virtual void SetModifiedFlag(BOOL bModified = TRUE);

 public:
  virtual ~CPDFReaderDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

 protected:
  BOOL m_bInitPages;
  BOOL m_bLoadDocument;
  PDFDoc m_PDFDoc;
  XFADoc m_XFADoc;
  Form m_Form;
  FillerAssistCallback* m_pFormFillerAssit;
  Filler m_FormFiller;
  XFADocProvider* m_pXFADocProvider;

  CString m_csFilePath;
  CString m_csPassword;

  CArray<CReader_Page*> m_pPageList;

  int m_nPageSpace;
  int m_nTotalPage;
  int m_nPageShadowWidth;
  float m_fRealHeight;
  float m_fRealWidth;
  int m_nCurPageIndex;
  BOOL m_bDynamicXFA;
  BOOL m_bModified;

  // Generated message map functions
 protected:
  DECLARE_MESSAGE_MAP()

  // Generated OLE dispatch map functions

  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

#ifdef SHARED_HANDLERS
  // Helper function that sets search content for a Search Handler
  void SetSearchContent(const CString& value);
#endif  // SHARED_HANDLERS
 public:
  afx_msg void OnDocumentProperty();
};
