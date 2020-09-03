// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to extract attached files from PDF files and
// add files as attachments to PDF files.

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
#include "../../../include/pdf/fs_filespec.h"
#include "../../../include/pdf/fs_pdfattachments.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace annots;
using foxit::pdf::annots::Line;

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

String DateTimeToString(const DateTime& datetime) {
  String s_datetime;
  s_datetime.Format((const char*)"%d/%d/%d-%d:%d:%d %s%d:%d", datetime.year, datetime.month, datetime.day, datetime.hour,
    datetime.minute, datetime.second, datetime.utc_hour_offset > 0 ? "+" : "-", datetime.utc_hour_offset,
    datetime.utc_minute_offset);
  return s_datetime;
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

int main(int argc, char *argv[])
{
  int err_ret = 0;
  WString input_file = input_path + L"attachment.pdf";

  WString output_directory = output_path + L"attachment/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  WString file_info = output_directory + L"attachMent_info.txt";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library.
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    PDFDoc doc=PDFDoc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }

    {
      // Get information of attachments.
      Attachments attachments(doc);
      TextDoc text_doc(file_info, L"w+b");
      int count = attachments.GetCount();
      for (int i = 0; i < count; i++) {
        WString key = attachments.GetKey(i);
        text_doc.Write("key:\t\t%s\r\n", (const char*)String::FromUnicode(key));

        FileSpec file_spec = attachments.GetEmbeddedFile(key);
        if (!file_spec.IsEmpty()) {
          WString name = file_spec.GetFileName();
          text_doc.Write("Name:\t\t%s\r\n", (const char*)String::FromUnicode(name));
          text_doc.Write("Size:\t\t%d\r\n", file_spec.GetFileSize());
          text_doc.Write("Is embedded:\t%s\r\n", file_spec.IsEmbedded() ? "true" : "false");
          text_doc.Write("Creation time:\t%s\r\n", (const char*)DateTimeToString(file_spec.GetCreationDateTime()));
          text_doc.Write("Modified time:\t%s\r\n", (const char*)DateTimeToString(file_spec.GetModifiedDateTime()));
          text_doc.Write("\r\n");

          if (file_spec.IsEmbedded()) {
            WString exFilePath = output_directory + name;
            bool bExportStatus = file_spec.ExportToFile(exFilePath);
            cout << (const char*)String::FromUnicode(name) << " ExportToFile " << (bExportStatus ? "successful" : "failed") << endl;
          }
        }
      }
    }
    {
      // Remove all attachments
      Attachments attachment(doc);
      attachment.RemoveAllEmbeddedFiles();
      WString newPdf = output_directory + L"attachment_remove.pdf";
      doc.SaveAs(newPdf, PDFDoc::e_SaveFlagNoOriginal);
      cout << "Remove all attachments." << endl;

    }
    {
      WString text_path = input_path + L"AboutFoxit.pdf";
      Attachments attachment(doc);
      // Add a new attachment to PDF document.
      attachment.AddFromFilePath(L"OriginalAttachmentsInfo", text_path);
      WString newPdf = output_directory + L"attachment_add.pdf";
      doc.SaveAs(newPdf, PDFDoc::e_SaveFlagNoOriginal);
      cout << "Add a new attachment to PDF document." << endl;
    }

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
