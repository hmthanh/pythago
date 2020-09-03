
// PDFReader.h : main header file for the PDFReader application
//
#pragma once
#include "PDFReader/Source/stdafx.h"
#include "PDFReader/Source/util.h"
#ifndef __AFXWIN_H__
  #error "include 'stdafx.h' before including this file for PCH"
#endif

#include "PDFReader/Resource/resource.h"       // main symbols

class ActionHandler: public foxit::ActionCallback {
 public:
  virtual void Release();
  virtual bool InvalidateRect(const PDFDoc& pdfDoc, int pageIndex, const foxit::RectF& pdfRect);
  virtual int GetCurrentPage(const PDFDoc& pdfDoc) ;
  virtual void SetCurrentPage(const PDFDoc& pdfDoc, int pageIndex);
  virtual Rotation GetPageRotation(const PDFDoc& pdfDoc, int pageIndex);
  virtual bool SetPageRotation(const PDFDoc& pdfDoc, int pageIndex, Rotation rotation);
  virtual bool ExecuteNamedAction(const PDFDoc& pdfDoc, const char* namedAction);
  virtual bool SetDocChangeMark(const PDFDoc& pdfDoc, bool changeMark);
  virtual bool GetDocChangeMark(const PDFDoc& pdfDoc);
  virtual int GetOpenedDocCount();
  virtual PDFDoc GetOpenedDoc(int index);
  virtual bool Beep(int type);
  virtual foxit::WString Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_value,
                           const wchar_t* label, bool is_password);
  virtual foxit::WString GetFilePath(const PDFDoc& document);
  virtual bool Print(const PDFDoc& document, bool is_ui,
                     const Range& page_set, bool is_silent ,
                     bool is_shrunk_to_fit, bool is_printed_as_image,
                     bool is_reversed, bool is_to_print_annots);
  virtual bool SubmitForm(const PDFDoc& document, void* form_data, foxit::uint32 length, const char* url);
  virtual bool LaunchURL(const char* URL);
  virtual foxit::WString BrowseFile();
  virtual Language GetLanguage();
  virtual int Alert(const wchar_t* msg, const wchar_t* title, int type, int icon);
  virtual foxit::IdentityProperties  GetIdentityProperties();
  virtual foxit::WString PopupMenu(const foxit::MenuListArray& menus);
  virtual foxit::WString GetAppInfo(AppInfoType type);
  virtual bool MailData(void* data, MailType dataType, bool bUI,
                        const wchar_t* cTo, const wchar_t* cSubject,
                        const wchar_t* cCC, const wchar_t* cBCC, const wchar_t* cMsg);
  virtual foxit::uint32 VerifySignature(const PDFDoc& document, const Signature& pdf_signature);

};

class XFAAppProviderHandler: public AppProviderCallback {
 public:
  virtual void Release();
  virtual foxit::WString GetAppInfo(AppInfo app_info);
  virtual void Beep(BeepType type);
  virtual MsgBoxButtonID MsgBox(const wchar_t* message, const wchar_t* title = NULL, MsgBoxIconType icon_type = e_MsgBoxIconError, MsgBoxButtonType button_type = e_MsgBtnTypeOK);
  virtual foxit::WString Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_answer = NULL, bool is_mask = TRUE);
  virtual ReaderCallback* DownLoadUrl(const wchar_t* url);
  virtual foxit::WString PostRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* content_type, const wchar_t* encode, const wchar_t* header);
  virtual bool PutRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* encode);
  virtual foxit::WString LoadString(StringID string_id);
  virtual foxit::WStringArray ShowFileDialog(const wchar_t* string_title, const wchar_t* string_filter, bool is_openfile_dialog = TRUE);
};

// CPDFReaderApp:
// See PDFReader.cpp for the implementation of this class

class CPDFReaderApp : public CWinAppEx
{
 public:
  CPDFReaderApp();
  virtual ~CPDFReaderApp();
  void SetMainFrame(CView* pView);
  void SetMainFrame(CDocument* pDoc);
  void AddFrame(CWnd* pFrame);
  void RemoveFrame(CWnd* pFrame);
  void AddDocument(CDocument* pDoc);
  CWnd* GetFrameByDoc(CDocument* pDoc);
  CDocument* GetDocByFrame(CWnd* frame);
  CRecentFileList* GetRecentFileList();
  bool IsHadOpenDocumentSucessful();

  virtual BOOL InitInstance();
  virtual int ExitInstance();
  bool GetCommondInfoFromDlg(CCommandLineInfo* line_info);
  virtual void PreLoadState();
  virtual void LoadCustomState();
  virtual void SaveCustomState();

  afx_msg void OnAppAbout();
  afx_msg void OnFileNewFrame();
  afx_msg void OnFileNew();
  DECLARE_MESSAGE_MAP()

 public:
  // Implementation
  COleTemplateServer m_server;
  // Server object for document creation
  BOOL  m_bHiColorIcons;

 protected:
  CMultiDocTemplate* m_pDocTemplate;
  CArray<CWnd*> m_pFrameArray;
  CMapPtrToPtr m_mapDocToFrame;

  Gdiplus::GdiplusStartupInput m_GdiplusStartupInput;

  ULONG_PTR m_GdiplusToken;

 private:
  XFAAppProviderHandler* m_pXFAAppProviderHandler;
};

extern CPDFReaderApp theApp;
