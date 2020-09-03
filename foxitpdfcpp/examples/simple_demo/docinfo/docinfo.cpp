// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to get/set attributes of viewer preference
// and values of metadata in a PDF file.

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
#include "../../../include/pdf/fs_pdfdocviewerprefs.h"
#include "../../../include/pdf/fs_pdfmetadata.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace common;
using namespace graphics;
using namespace objects;

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

WString output_directory = output_path + L"docinfo/";

DateTime GetLocalDateTime() {
  time_t t = time(NULL);
#if (WINAPI_PARTITION_APP || WINAPI_PARTITION_PC_APP) || \
  (defined(_WIN32) || defined(_WIN64)) && _FX_COMPILER_ != _FX_VC6_
  struct tm _Tm;
  localtime_s(&_Tm, &t);
  struct tm* rime = &_Tm;
  _tzset();
  long time_zone = NULL;
  _get_timezone(&time_zone);
  int timezone_hour = time_zone / 3600 * -1;
  int timezone_minute = (abs(time_zone) % 3600) / 60;
#elif defined(__linux__)
  struct tm* rime = localtime(&t);
  tzset();
  int timezone_hour = __timezone / 3600 * -1;
  int timezone_minute = ((int)abs(__timezone) % 3600) / 60;
#elif defined(__APPLE__)
  struct tm* rime = localtime(&t);
  tzset();
  int timezone_hour = timezone / 3600 * -1;
  int timezone_minute = ((int)abs(timezone) % 3600) / 60;
#endif
  DateTime datetime;
  datetime.year = static_cast<uint16>(rime->tm_year + 1900);
  datetime.month = static_cast<uint16>(rime->tm_mon + 1);
  datetime.day = static_cast<uint16>(rime->tm_mday);
  datetime.hour = static_cast<uint16>(rime->tm_hour);
  datetime.minute = static_cast<uint16>(rime->tm_min);
  datetime.second = static_cast<uint16>(rime->tm_sec);
  datetime.utc_hour_offset = timezone_hour;
  datetime.utc_minute_offset = timezone_minute;

  return datetime;
}

WString DateTimeToString(const DateTime& datetime) {
  WString ws_datetime;
  ws_datetime.Format((FX_LPCWSTR)L"%d/%d/%d-%d:%d:%d %s%d:%d", datetime.year, datetime.month, datetime.day, datetime.hour,
    datetime.minute, datetime.second, datetime.utc_hour_offset > 0 ? L"+" : L"-", datetime.utc_hour_offset,
    datetime.utc_minute_offset);
  return ws_datetime;
}

class TextDoc {
public:
  TextDoc(const String& file_name, const String& fill_mode);
  TextDoc(const WString& file_name, const WString& fill_mode);
  ~TextDoc();
  void Write(const char* format, ...);
  void Write(int count, const char* prefix, const char* format, ...);

private:
  FILE* file_;
};

TextDoc::TextDoc(const String& file_name, const String& file_mode) throw(Exception) : file_(NULL) {
#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, (const char*)file_name, (const char*)file_mode);
#else
  file_ = fopen((const char*)file_name, (const char*)file_mode);
#endif

  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);
}

TextDoc::TextDoc(const WString& file_name, const WString& file_mode) throw(Exception)  : file_(NULL) {
  String s_file_name = String::FromUnicode(file_name);
  String s_file_mode = String::FromUnicode(file_mode);

#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, (const char*)s_file_name, (const char*)s_file_mode);
#else
  file_ = fopen((const char*)s_file_name, (const char*)s_file_mode);
#endif
  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);
}

TextDoc::~TextDoc() {
  fclose(file_);
  file_ = NULL;
}

void TextDoc::Write(const char* format, ...) {
  va_list vars;
  if (file_) {
    // Get variable list
    va_start(vars, format);
    // Call vfprintf to format log data and output to log file
    vfprintf(file_, format, vars);
    // End variable list
    va_end(vars);
  }
}

void TextDoc::Write(int count, const char * prefix, const char * format, ...) {
  for (int i = 0; i < count; i++) {
    Write("%s", prefix);
  }
  va_list vars;
  if (file_) {
    // Get variable list
    va_start(vars, format);
    // Call vfprintf to format log data and output to log file
    vfprintf(file_, format, vars);
    // End variable list
    va_end(vars);
  }
}

DocViewerPrefs::ViewerPref kUIItems[] = {
  DocViewerPrefs::e_HideToolbar, DocViewerPrefs::e_HideMenubar,
  DocViewerPrefs::e_HideWindowUI, DocViewerPrefs::e_FitWindow,
  DocViewerPrefs::e_CenterWindow, DocViewerPrefs::e_DisplayDocTitle};

const PDFDoc::DisplayMode kDisplayModes[] = {PDFDoc::e_DisplayUseNone,   PDFDoc::e_DisplayUseOutlines,
  PDFDoc::e_DisplayUseThumbs, PDFDoc::e_DisplayFullScreen,
  PDFDoc::e_DisplayUseOC,     PDFDoc::e_DisplayUseAttachment};

const char* kDisplayModeStrings[] = {"UseNone", "UseOutlines", "UseThumbs", "FullScreen", "UseOC", "UseAttachment"};

const char* kBoxItemStrings[] = {"ViewArea", "ViewClip", "PrintArea", "PrintClip"};
const char* GetPageBoxName(PDFPage::BoxType type){
  switch (type) {
  case foxit::pdf::PDFPage::e_MediaBox:
    return "MediaBox";
  case foxit::pdf::PDFPage::e_CropBox:
    return "CropBox";
  case foxit::pdf::PDFPage::e_TrimBox:
    return "TrimBox";
  case foxit::pdf::PDFPage::e_ArtBox:
    return "ArtBox";
  case foxit::pdf::PDFPage::e_BleedBox:
    return "BleedBox";
  }
  return "";
}

const char* GetViewerPrefName(DocViewerPrefs::ViewerPref ui_item) {
  switch(ui_item){
  case DocViewerPrefs::e_HideToolbar:
    return "HideToolbar";
  case DocViewerPrefs::e_HideMenubar:
    return "HideMenubar";
  case DocViewerPrefs::e_HideWindowUI:
    return "HideWindowUI";
  case DocViewerPrefs::e_FitWindow:
    return "FitWindow";
  case DocViewerPrefs::e_CenterWindow:
    return "CenterWindow";
  case DocViewerPrefs::e_DisplayDocTitle:
    return "DisplayDocTitle";
  }
  return "";
}

const char* GetViewerPrefPrintScaleName(DocViewerPrefs::PrintScale ui_item) {
  switch(ui_item) {
  case DocViewerPrefs::e_PrintScaleNone:
    return "PrintScaleNone";
  case DocViewerPrefs::e_PrintScaleAppDefault:
    return "PrintScaleAppDefault";
  }
  return "";
}

void ShowDocViewerPrefsInfo(PDFDoc doc,WString file_name) {
  WString file_info = output_directory + L"DocViewerPrefsInfo_"+ file_name;
  TextDoc text_doc(file_info, L"w+b");

  DocViewerPrefs prefs(doc);
  text_doc.Write("Document viewer preferences information:\r\n");
  // Get UI visibility status.
  for (unsigned int i = 0; i < sizeof(kUIItems) / (sizeof(kUIItems[0])); i++) {
      text_doc.Write("Visibility of %s:\t%s\r\n", GetViewerPrefName(kUIItems[i]), prefs.GetUIDisplayStatus(kUIItems[i]) ? "Yes" : "No");
  }
  // Get display mode for non full-screen mode.
  PDFDoc::DisplayMode mode = prefs.GetNonFullScreenPageMode();
  const char* display_mode = NULL;
  for (unsigned int i = 0; i < sizeof(kDisplayModes) / sizeof(kDisplayModes[i]); i++) {
    if (mode == kDisplayModes[i]) {
      display_mode = kDisplayModeStrings[i];
      break;
    }
  }
  text_doc.Write("None full screen page mode:\t%s\r\n", (const char*)display_mode);
  // Get reading direction.
  text_doc.Write("Reading direction:\t%s\r\n", prefs.GetReadingDirection() ? "left to right" : "right to left");
  // Get the type of area item.
  PDFPage::BoxType type = prefs.GetPrintClip();
  text_doc.Write("The GetPrintClip returned:\t%s\r\n", (const char*)GetPageBoxName(type));
  type = prefs.GetPrintArea();
  text_doc.Write("The GetPrintArea returned:\t%s\r\n", (const char*)GetPageBoxName(type));
  type = prefs.GetViewArea();
  text_doc.Write("The GetViewArea returned:\t%s\r\n", (const char*)GetPageBoxName(type));
  type = prefs.GetViewClip();
  text_doc.Write("The GetViewClip returned:\t%s\r\n", (const char*)GetPageBoxName(type));

  // Get page scaling option.
  text_doc.Write("Page scaling option:\t%s\r\n", GetViewerPrefPrintScaleName(prefs.GetPrintScale()));
  // Get the number of copies to be printed.
  text_doc.Write("The number of copies to be printed:\t%d\r\n", prefs.GetPrintCopies());
  // Get page ranges which allowed to print
  text_doc.Write("Page ranges for printing:\r\n");
  common::Range print_ranges = prefs.GetPrintRange();
  if(!print_ranges.IsEmpty())
  {
    for (int i = 0; i < print_ranges.GetSegmentCount(); i=i+1)
      text_doc.Write("\tfirst:\t%d\tlast:\t%d\r\n", print_ranges.GetSegmentStart(i), print_ranges.GetSegmentEnd(i));

  }
}

void SetDocViewerPrefsInfo(PDFDoc doc) {

  doc.SetDisplayMode(PDFDoc::e_DisplayFullScreen);
  DocViewerPrefs prefs(doc);
  // Set UI visibility status.
  for (unsigned int i = 0; i < sizeof(kUIItems) / (sizeof(kUIItems[0])); i++) {
    prefs.SetUIDisplayStatus(kUIItems[i], true);
  }
  // Set display mode for non full-screen mode.
  prefs.SetNonFullScreenPageMode(PDFDoc::e_DisplayUseOutlines);
  // Set reading direction.
  prefs.SetReadingDirection(false);
  // Set the type of area item.

  prefs.SetViewArea(foxit::pdf::PDFPage::e_CropBox);
  prefs.SetViewClip(foxit::pdf::PDFPage::e_CropBox);
  prefs.SetPrintArea(foxit::pdf::PDFPage::e_CropBox);
  prefs.SetPrintClip(foxit::pdf::PDFPage::e_CropBox);
  // Set page scaling option.
  prefs.SetPrintScale(DocViewerPrefs::e_PrintScaleNone);
  // Set the number of copies to be printed.
  prefs.SetPrintCopies(4);
  common::Range print_range(0, doc.GetPageCount() / 2);
  prefs.SetPrintRange(print_range);
}

const wchar_t* kMetadataItems[] = {L"Title", L"Author", L"Subject", L"Keywords",
    L"Creator", L"Producer", L"CreationDate", L"ModDate"};

void ShowMetaDataInfo(PDFDoc doc,WString file_name) {
  WString output_file = output_directory + L"MetaDataInfo_"+file_name;
  TextDoc text_doc(output_file, L"wb+");
  text_doc.Write("Metadata information:\r\n");
  Metadata metadata(doc);
  for (unsigned int i = 0; i < sizeof(kMetadataItems) / sizeof(kMetadataItems[0]); i++) {
    const wchar_t* item = kMetadataItems[i];
    text_doc.Write("%s: ", (const char*)String::FromUnicode(item));
    foxit::WStringArray value = metadata.GetValues(item);
    for(size_t j=0;j<value.GetSize();j++)
    {
      text_doc.Write("%s",(const char*)String::FromUnicode(value[j]));
    }
    text_doc.Write("\r\n");
  }
}

void SetMetaDataInfo(PDFDoc doc) {

  const wchar_t* kMetadataValues[] = {L"Title set by simple demo", L"Simple demo",
    L"Subject set by simple demo", L"Keywords set by simple demo",
    L"Foxit PDF SDK", L"Foxit"};
  Metadata metadata(doc);
  for (unsigned int i = 0; i < sizeof(kMetadataValues) / sizeof(kMetadataValues[0]); i++) {
    foxit::WStringArray MetadataValues;
    MetadataValues.Add(kMetadataValues[i]);
    metadata.SetValues(kMetadataItems[i], MetadataValues);
  }
  metadata.SetCreationDateTime(GetLocalDateTime());
  metadata.SetModifiedDateTime(GetLocalDateTime());
}

int main(int argc, char *argv[])
{
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
    WString input_file = input_path + L"AboutFoxit.pdf";
    PDFDoc doc(input_file);
    ErrorCode code = doc.Load();
    if (code != foxit::e_ErrSuccess) {
      printf("[Failed] Cannot load PDF document %s.\r\nError Message: %d\r\n", (const char*)String::FromUnicode(input_file), code);
      return 1;
    }
    // Show original information.
    ShowDocViewerPrefsInfo(doc,L"original.txt");
    ShowMetaDataInfo(doc,L"original.txt");

    // Set information.
    SetDocViewerPrefsInfo(doc);
    SetMetaDataInfo(doc);

    // Show new information.
    ShowDocViewerPrefsInfo(doc,L"new.txt");
    ShowMetaDataInfo(doc,L"new.txt");
    WString output_file = output_directory + L"AboutFoxit_docinfo.pdf";
    doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);

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
