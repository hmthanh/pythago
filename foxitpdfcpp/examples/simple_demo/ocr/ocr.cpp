// Copyright (C) 2001-2018, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do OCR for a PDF page or PDF document.


#if (defined(_WIN32) || defined(_WIN64))

// Include Foxit SDK header files.
//#include <time.h>
#include <iostream>
//#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
//#else
//#include <sys/stat.h>
//#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/addon/ocr/fs_ocr.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace addon::ocr;

static const char* sn = "eUcaj+XFRdwDeV4fx2eGZzF7ZmQiBNInjxfWhiHCIinKYg3KsYgcKg==";
static const char* key = "8f0YFcONvRsJ+nePmKBLSM8bw7bGx79neQeRmlgo13uto3HGtEFz4BLMd5BErJbDU1Nll8omHE6H+Vx20kaMiDQYMDldaA9ctpwcoLODu8yfFtHTm2UseIiHVjqu52IRK18VKf4pLWI6ekSbkAafVjd3XxT8Gv6TtRASa2U4/v/xFR99REZVOqq8tPSQT5b521y1tTBJaTKxB23KwsVuONGlSM8ZH0PiPkjuRmZsfp9aVqpWVSfBMZFqw4+XYbQdImYgzqkq/vgaZ7ApxW0ICzjtIiJ0x/15o+rOFQhMh6+9kSGq4OhjfzY8ZRqTyFQ2dy2SRF+tQKD87bTJUrDkf9mRXbvK+xpDrPpT7dMgTj0R6yjrwJpRt6LcimMv+LvSjbKvAG6KFxn6UMfWVi8bkFM/hzvwRJe/aoyPbYQ72lFMHeYreJNaAKYpO8CBF9mi5KbDDXYNtaoEgUVVukppYbS/wVpdQwlC7J85A9yLmelDEufSbz/RVOwv2LZKHsk6iFgaV4U74YrYiwIT4xE8znliw4xnOd6j+MCBdcmMvOyGKUeNrD7Q042c6Pn5QPGchkmmPuhqwrcnRXYiYEOyMs4LnsdhKSxJk4Q2yoc9b6Fhb8RQbUARzbTfAw9L/ZgooZ2tVhFFJnCFhkU4U76twoB1plg3L2KEAH4smtZjVh0k8uoaDt9JQOk/K5YaKiAI3TPB6AlsaDLguQClqyRsK04OyO/CZkoPsvLoGa1EyBpppKcwOe3PyF4zYuNEQRRZh48L/5loWJPf+ynWj1fR+NcVnTqe8GqFk0vP3uK5C8FaJxKP3a0bekr0tKCfe4yxte4Ej8yo/3plnDz03GXUB+FgsdMINm3rA2UhTNdYjRJtIRNJomCkjQr7GHyEsTq71Q6O0wuOSet0byPcLPPhcXzsSqpWYZ9+opORXE92LCwuHJRZOtuzpjvAphi0kiCRk4dSR0VP8FmL5yNG2M2okeEb8bjXD52ErTBTIAk3VZnh4OOCSfzgpZhoEvr5usjkfyry9BmgX2gWAJYRTUrEgDTXHj5YQ6MT3grfDGYMqKoy7GSpb3tY5zBHzzoJDK/E1VvO+ScyQaJQJ0eHgsgy2QZbCnEB3W4N5M8HqBqNMw+0oUvqw0P1i4uK9XwCGzVyyOXs1czCsWGg8R8Ej51AL+9gXdu7RMdEaP2lTMkOJfScJbzsOkfjxvX5LBrHVZ98XuzZylbeFkVr/gjrvBnfucL9zCmjngYq4RfzDYBOzx31gRuFFAsllK4zFRgtHWSXGXwXim4OJpMVKEuFHO5Oupowvd9cdzRIjGpWzR0=";

static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/ocr/");

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

int main(int argc, char *argv[]) {
  int err_ret = 0;
  WString input_file = input_path + L"AboutFoxit_ocr.pdf";

  WString output_directory = output_path + L"ocr/";
  _mkdir(String::FromUnicode(output_directory));

  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    // "ocr_resource_path" is the path of ocr resources. Please refer to Developer Guide for more details.
    WString ocr_resource_path = L"";

    if (ocr_resource_path.IsEmpty()) {
      std::cout<<"ocr_resource_path is still empty. Please set it with a valid path to OCR resource path."<<std::endl;
      return 1;
    }

    // Initialize OCR engine.
    error_code = OCREngine::Initialize(ocr_resource_path);
    if (error_code != foxit::e_ErrSuccess) {
      switch(error_code){
        case foxit::e_ErrInvalidLicense:
          printf("[Failed] OCR module is not contained in current Foxit PDF SDK keys.\n");
          break;
        default:
          printf("Fail to initialize OCR engine. Error: %d\n", error_code);
          break;
      }
      return 1;
    }
    cout << "OCREngine is initialized." << endl;

    // Set log for OCREngine. (This can be opened to set log file if necessary)
    //OCREngine::SetLogFile(output_directory+L"ocr.log");
    // Set languages.
    OCREngine::SetLanguages(L"English");

    // OCR PDF document, only for search, not editable.
    {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }
      OCR ocr_operator;
      ocr_operator.OCRPDFDocument(doc, false);

      WString save_pdf_path = output_directory + L"ocr_doc_searchable.pdf";
      doc.SaveAs(save_pdf_path, PDFDoc::e_SaveFlagNoOriginal);
    }
    // OCR PDF document, editable.
    {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }
      OCR ocr_operator;
      ocr_operator.OCRPDFDocument(doc, true);

      WString save_pdf_path = output_directory + L"ocr_doc_editable.pdf";
      doc.SaveAs(save_pdf_path, PDFDoc::e_SaveFlagNoOriginal);
    }
    // OCR PDF page, only for search, not editable.
    {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }
      PDFPage page = doc.GetPage(0);
      page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

      OCR ocr_operator;
      ocr_operator.OCRPDFPage(page, false);

      WString save_pdf_path = output_directory + L"ocr_page_searchable.pdf";
      doc.SaveAs(save_pdf_path, PDFDoc::e_SaveFlagNoOriginal);
    }
    // OCR PDF page, editable.
    {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }
      PDFPage page = doc.GetPage(0);
      page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

      OCR ocr_operator;
      ocr_operator.OCRPDFPage(page, true);

      WString save_pdf_path = output_directory + L"ocr_page_editable.pdf";
      doc.SaveAs(save_pdf_path, PDFDoc::e_SaveFlagNoOriginal);
    }

    OCREngine::Release();

    cout << "END: OCR demo." << endl;
  } catch (const Exception& e) {
    switch(e.GetErrCode()){
      case foxit::e_ErrInvalidLicense:
        printf("[Failed] OCR module is not contained in current Foxit PDF SDK keys.\n");
        break;
      default:
        printf("%s\n", (const char*)e.GetMessage());
        break;
    }
    err_ret = 1;
  }
  catch(...)
  {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}

#endif  // (defined(_WIN32) || defined(_WIN64))
