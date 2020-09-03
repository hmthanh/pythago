// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to export data, import data and reset form for
// XFA document.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/interform/fs_pdfform.h"
#include "../../../include/addon/xfa/fs_xfa.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace annots;
using namespace actions;
using namespace interform;
using namespace foxit::addon::xfa;

static const char* sn = "eUcaj+XFRdwDeV4fx2eGZzF7ZmQiBNInjxfWhiHCIinKYg3KsYgcKg==";
static const char* key = "8f0YFcONvRsJ+nePmKBLSM8bw7bGx79neQeRmlgo13uto3HGtEFz4BLMd5BErJbDU1Nll8omHE6H+Vx20kaMiDQYMDldaA9ctpwcoLODu8yfFtHTm2UseIiHVjqu52IRK18VKf4pLWI6ekSbkAafVjd3XxT8Gv6TtRASa2U4/v/xFR99REZVOqq8tPSQT5b521y1tTBJaTKxB23KwsVuONGlSM8ZH0PiPkjuRmZsfp9aVqpWVSfBMZFqw4+XYbQdImYgzqkq/vgaZ7ApxW0ICzjtIiJ0x/15o+rOFQhMh6+9kSGq4OhjfzY8ZRqTyFQ2dy2SRF+tQKD87bTJUrDkf9mRXbvK+xpDrPpT7dMgTj0R6yjrwJpRt6LcimMv+LvSjbKvAG6KFxn6UMfWVi8bkFM/hzvwRJe/aoyPbYQ72lFMHeYreJNaAKYpO8CBF9mi5KbDDXYNtaoEgUVVukppYbS/wVpdQwlC7J85A9yLmelDEufSbz/RVOwv2LZKHsk6iFgaV4U74YrYiwIT4xE8znliw4xnOd6j+MCBdcmMvOyGKUeNrD7Q042c6Pn5QPGchkmmPuhqwrcnRXYiYEOyMs4LnsdhKSxJk4Q2yoc9b6Fhb8RQbUARzbTfAw9L/ZgooZ2tVhFFJnCFhkU4U76twoB1plg3L2KEAH4smtZjVh0k8uoaDt9JQOk/K5YaKiAI3TPB6AlsaDLguQClqyRsK04OyO/CZkoPsvLoGa1EyBpppKcwOe3PyF4zYuNEQRRZh48L/5loWJPf+ynWj1fR+NcVnTqe8GqFk0vP3uK5C8FaJxKP3a0bekr0tKCfe4yxte4Ej8yo/3plnDz03GXUB+FgsdMINm3rA2UhTNdYjRJtIRNJomCkjQr7GHyEsTq71Q6O0wuOSet0byPcLPPhcXzsSqpWYZ9+opORXE92LCwuHJRZOtuzpjvAphi0kiCRk4dSR0VP8FmL5yNG2M2okeEb8bjXD52ErTBTIAk3VZnh4OOCSfzgpZhoEvr5usjkfyry9BmgX2gWAJYRTUrEgDTXHj5YQ6MT3grfDGYMqKoy7GSpb3tY5zBHzzoJDK/E1VvO+ScyQaJQJ0eHgsgy2QZbCnEB3W4N5M8HqBqNMw+0oUvqw0P1i4uK9XwCGzVyyOXs1czCsWGg8R8Ej51AL+9gXdu7RMdEaP2lTMkOJfScJbzsOkfjxvX5LBrHVZ98XuzZylbeFkVr/gjrvBnfucL9zCmjngYq4RfzDYBOzx31gRuFFAsllK4zFRgtHWSXGXwXim4OJpMVKEuFHO5Oupowvd9cdzRIjGpWzR0=";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/");
#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/");
#endif

class SdkLibMgr {
public:
  SdkLibMgr() : is_initialize_(false){};
  ErrorCode Initialize() {
    ErrorCode error_code = Library::Initialize(sn, key);
    if (error_code != foxit::e_ErrSuccess) {
      printf("Library Initialize Error: %d\n", error_code);
    } else {
      is_initialize_ = true;
    }
    return error_code;

  }
  ~SdkLibMgr(){
    if(is_initialize_)
      Library::Release();
  }
private:
  bool is_initialize_;
};

class CFS_XFAAppHandler : public foxit::addon::xfa::AppProviderCallback
{
public:
    CFS_XFAAppHandler() {}
    ~CFS_XFAAppHandler() {}

    virtual void Release() {
        delete this;
    }

    virtual WString GetAppInfo(AppInfo app_info) {
        return L"Foxit SDK";
    }
    virtual void Beep(BeepType type) {}
    virtual AppProviderCallback::MsgBoxButtonID MsgBox(const wchar_t* message, const wchar_t* title = NULL,
        MsgBoxIconType icon_type = e_MsgBoxIconError,
        MsgBoxButtonType button_type = e_MsgBtnTypeOK) {
            return (AppProviderCallback::MsgBoxButtonID)0;
    }
    virtual WString Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_answer = NULL,
        bool is_mask = true) {
            return L"answer";
    }
    virtual common::file::ReaderCallback* DownLoadUrl(const wchar_t* url) {
        return NULL;
    }
    virtual WString PostRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* content_type, const wchar_t* encode, const wchar_t* header) {
        return L"PostRequestUrl";
    }
    virtual bool PutRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* encode) {
        return TRUE;
    }
    virtual WString LoadString(AppProviderCallback::StringID string_id) {
        return L"LoadString";
    }

    virtual WStringArray ShowFileDialog(const wchar_t* string_title, const wchar_t* string_filter, bool is_openfile_dialog = TRUE) {
        return WStringArray();
    }
};

class CFS_XFADocHandler:public foxit::addon::xfa::DocProviderCallback
{
public:
    CFS_XFADocHandler() {}
    ~CFS_XFADocHandler() {}

    virtual void Release(){
        delete this;
    }
    virtual void InvalidateRect(int page_index, const RectF &rect, InvalidateFlag flag) {}
    virtual void DisplayCaret(int page_index, bool is_visible, const RectF &rect) {}
    virtual bool GetPopupPos(int page_index, float min_popup, float max_popup,
        const RectF &rect_widget, RectF &rect_popup) {
            return TRUE;
    }
    virtual bool PopupMenu(int page_index, const PointF& rect_popup) {
        return TRUE;
    }
    virtual int GetCurrentPage(const foxit::addon::xfa::XFADoc& doc) {
        return 0;
    }
    virtual void SetCurrentPage(const foxit::addon::xfa::XFADoc& doc, int current_page_index) {}
    virtual WString GetTitle(const foxit::addon::xfa::XFADoc& doc) {
        return L"title";
    }
    virtual void ExportData(const foxit::addon::xfa::XFADoc& doc, const WString& file_path) {}
    virtual void ImportData(const foxit::addon::xfa::XFADoc& doc, const WString& file_path) {}
    virtual void GotoURL(const foxit::addon::xfa::XFADoc& doc, const WString& url) {}
    virtual void Print(const foxit::addon::xfa::XFADoc& doc, int start_page_index, int end_page_index, uint32 options) {}
    virtual ARGB GetHighlightColor(const foxit::addon::xfa::XFADoc& doc) {
        if(doc.GetType() == foxit::addon::xfa::XFADoc::e_Static) {
            return 0x50FF0000;
        }
        else {
            return 0x500000FF;
        }
    }
    virtual bool SubmitData(const foxit::addon::xfa::XFADoc& doc, const WString& target, SubmitFormat format, TextEncoding text_encoding, const WString& content) {
        return TRUE;
    }
    virtual void SetFocus(foxit::addon::xfa::XFAWidget& xfa_widget) {};
    virtual void PageViewEvent(int page_index, PageViewEventType page_view_event_type) {}
    virtual void SetChangeMark(const foxit::addon::xfa::XFADoc& doc) {}
    virtual void WidgetEvent(const foxit::addon::xfa::XFAWidget& xfa_widget,WidgetEventType widget_event_type) {}
};

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"xfa_form/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    CFS_XFAAppHandler* pXFAAppHandler = new CFS_XFAAppHandler();
    Library::RegisterXFAAppProviderCallback(pXFAAppHandler);
    WString input_file = input_path + L"xfa_dynamic.pdf";
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
    }

    CFS_XFADocHandler* pXFADocHandler = new CFS_XFADocHandler();
    XFADoc xfa_doc(doc, pXFADocHandler);
    xfa_doc.StartLoad(NULL);

    xfa_doc.ExportData(output_directory + L"xfa_form.xml", XFADoc::e_ExportDataTypeXML);
    
    xfa_doc.ResetForm();
    doc.SaveAs(output_directory + L"xfa_dynamic_resetform.pdf");

    xfa_doc.ImportData(output_directory + L"xfa_form.xml");
    doc.SaveAs(output_directory + L"xfa_dynamic_importdata.pdf");
    cout << "Xfa test." << endl;
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }
  catch(...)
  {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}
