// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to save a PDF document as a wrapper file
// and then open the wrapper file.

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
#include "../../../include/common/fs_render.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace common::file;

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

WString output_directory = output_path + L"pdfwrapper/";

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
  fopen_s(&file_, file_name, (const char*)file_mode);
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

void RenderPDF2Img(PDFDoc doc) {
  int page_count = doc.GetPageCount();

  for (int i = 0; i < page_count; i++) {
    PDFPage page = doc.GetPage(i);

    // Parse page.
    page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

    int width = static_cast<int>(page.GetWidth());
    int height = static_cast<int>(page.GetHeight());
    Matrix matrix = page.GetDisplayMatrix(0, 0, width, height, page.GetRotation());

    // Prepare a bitmap for rendering.
    Bitmap bitmap(width, height, foxit::common::Bitmap::e_DIBArgb, NULL, 0);
    bitmap.FillRect(0xFFFFFFFF, NULL);

    // Render page.
    Renderer render(bitmap, false);
    render.StartRender(page, matrix, NULL);
    // Add the bitmap to an image and save the image.
    Image image;
    image.AddFrame(bitmap);
    WString image_name;
    image_name.Format((FX_LPCWSTR)L"AboutFoxit_%d",i);
    image_name = output_directory + image_name + L"_wrapper.jpg";

    if (!image.SaveAs(image_name)) {
      printf("[Failed] Cannot save image file.\r\nPage index: %d", i);
    }
  }

}

class FileReader : public ReaderCallback
{
public:
  FileReader(int64 offset) : file_(NULL)
                           , offset_(offset) {}
  ~FileReader() {}

  bool LoadFile(const char* file_path) {
#if defined(_WIN32) || defined(_WIN64)
    fopen_s(&file_, file_path, "rb");
#else
    file_ = fopen(file_path, "rb");
#endif
    if (!file_) return FALSE;
    return TRUE;
  }

  FILESIZE  GetSize()
  {
    return offset_;
  }

  FX_BOOL ReadBlock(void* buffer, FILESIZE offset, size_t size)
  {
    if (!file_) return 0;
    if(0 != fseek(file_, (long)offset, 0))
      return 0;
    if(0 == fread(buffer, size, 1, file_))
      return 0;
    return 1;
  }

  size_t ReadBlock(void* buffer, size_t size) {
    if (!file_) return false;
    if(0 != fseek(file_, 0, 0))
      return 0;
    return fread(buffer, size, 1, file_);
  }

  void Release() {
    if(file_)
      fclose(file_);
    file_ = NULL;
  }

private:
  FILE* file_;
  int64 offset_;
};

class FileWriter : public WriterCallback
{
public:
  FileWriter(): file_(NULL)
  {}

  ~FileWriter() {}

  bool LoadFile(const char* file_path) {
#if defined(_WIN32) || defined(_WIN64)
    fopen_s(&file_, file_path, "wb");
#else
    file_ = fopen(file_path, "wb");
#endif
    if (!file_) return FALSE;
    return TRUE;
  }

  FILESIZE GetSize() {
    if(!file_) return 0;
    fseek(file_, 0, SEEK_END);
    return (uint32)ftell(file_);
  }

  FX_BOOL Flush() {
    return TRUE;
  }

  FX_BOOL WriteBlock(const void* buffer, FILESIZE offset, size_t size) {
    if(!file_) return FALSE;

    fseek(file_, (long)offset, SEEK_SET);
    uint64 write_size = fwrite(buffer, sizeof(char), size, file_);
    if(write_size == size) {
      return TRUE;
    }

    return FALSE;
  }

  FX_BOOL ReadBlock(void* buffer, FILESIZE offset, size_t size) {
    if(!file_) return FALSE;
    if(0 != fseek(file_, (long)offset, 0)) return false;
    if(0 == fread(buffer, size, 1, file_)) return false;
    return true;
  }

  void Release() {
    if(file_) fclose(file_);
    file_ = NULL;
    delete this;
  }

private:
  FILE* file_;
};

bool OpenWrapperFile(WString file_name) {
  WString file_info = output_directory + L"Wrapperinfo.txt";
  TextDoc text_doc(file_info, L"w+b");

  PDFDoc doc(file_name);
  ErrorCode code = doc.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("[Failed] Cannot load PDF document: %s\r\nError Message: %d\r\n", (const char*)String::FromUnicode(file_name), code);
    return false;
  }
  if(!doc.IsWrapper()){
    printf("[Failed] %s is not a wrapper file.\r\n", (const char*)String::FromUnicode(file_name));
    return false;
  }
  int64 offset = doc.GetWrapperOffset();
  text_doc.Write("offset: %d\r\n", offset);
  WrapperData wrapper_data = doc.GetWrapperData();
  text_doc.Write("version: %d\r\n", wrapper_data.version);
  text_doc.Write("type: %s\r\n", (const char*)String::FromUnicode(wrapper_data.type));
  text_doc.Write("app_id: %s\r\n", (const char*)String::FromUnicode(wrapper_data.app_id));
  text_doc.Write("uri: %s\r\n",(const char*)String::FromUnicode(wrapper_data.uri));
  text_doc.Write("description: %s\r\n", (const char*)String::FromUnicode(wrapper_data.description));

  FileReader file_reader(offset);
  file_reader.LoadFile(String::FromUnicode(file_name));

  PDFDoc doc_real(&file_reader);
  code = doc_real.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("[Failed] Cannot load real PDF document.\r\nError Message: %d\r\n", code);
    return false;
  }

  RenderPDF2Img(doc_real);
  return true;
}

int main(int argc, char *argv[])
{
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"wrapper.pdf";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
     // Load PDF document.
    PDFDoc doc_wrapper(input_file);
    ErrorCode error_code = doc_wrapper.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("[Failed] Cannot load PDF document: %s.\r\nError Code: %d\r\n", (const char*)String::FromUnicode(input_file), error_code);
     return 1;
    }
    // Save the PDF document as a wrapper file.
    WrapperData wrapperData(10, L"Foxit", L"Foxit", L"www.foxitsoftware.com", L"foxit");

    WString output_file = output_directory + L"AboutFoxit_wrapper.pdf";

    PDFDoc doc_real(input_path + L"AboutFoxit.pdf");
    error_code = doc_real.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("[Failed] Cannot load PDF document: %s.\r\nError Code: %d\r\n", (const char*)String::FromUnicode(input_path + L"SamplePDF.pdf"), error_code);
      return 1;
    }
    doc_real.SaveAs(output_file);

    // "0xFFFFFFFC" can be changed to other values defined in enumeration FSUserPermissions.
    doc_wrapper.SaveAsWrapperFile(output_file, &wrapperData, 0xFFFFFFFC);

    // Open the wrapper file.
    if (!OpenWrapperFile(output_file)) {
      return 1;
    }

    cout << "Add wrapper to PDF file." << endl;

    output_file = output_directory + L"AboutFoxit_payloadfile.pdf";
    doc_wrapper.StartSaveAsPayloadFile(output_file, input_path + L"AboutFoxit.pdf", L"Unknown", L"no_description", 1.0, foxit::pdf::PDFDoc::e_SaveFlagIncremental, NULL);

    cout << "Save as payload file." << endl;

    PDFDoc doc_rmsv2(input_path + L"Microsoft IRM protection 2.pdf");

    error_code = doc_rmsv2.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("[Failed] Cannot load PDF document: %s.\r\nError Code: %d\r\n", (const char*)String::FromUnicode(input_path + L"Microsoft IRM protection 2.pdf"), error_code);
      return 1;
    }

    if (foxit::pdf::PDFDoc::e_WrapperPDFV2 == doc_rmsv2.GetWrapperType()) {
      FileWriter* payloadfile = new FileWriter();
      payloadfile->LoadFile(String::FromUnicode(output_directory + L"MicrosoftIRMServices Protected PDF.pdf"));
      doc_rmsv2.StartGetPayloadFile(payloadfile, NULL);
    }

    cout << "Get RMS V2 payload file." << endl;
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

