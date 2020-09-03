// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to import annotations from FDF/XFDF files
// and export annotations to FDF/XFDF files.

#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/annots/fs_annot.h"
#include "../../../include/pdf/interform/fs_pdfform.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace annots;
using namespace actions;

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

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"fdf/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library.
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    {
      // Import FDF file
      WString input_file = input_path + L"AboutFoxit.pdf";
      WString fdf_file = input_path + L"AnnotationData.fdf";
      pdf::PDFDoc pdf_doc(input_file);
      ErrorCode error_code = pdf_doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }

      fdf::FDFDoc fdf_doc(fdf_file);
      pdf_doc.ImportFromFDF(fdf_doc, PDFDoc::e_Annots);
      WString output_file = output_directory + L"AboutFoxit_importFDF.pdf";
      pdf_doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);
    }

    {
       // Import FDF file
       WString input_file = input_path + L"AboutFoxit.pdf";
       WString fdf_file = input_path + L"AnnotationData.fdf";
       pdf::PDFDoc pdf_doc(input_file); 
       ErrorCode error_code = pdf_doc.Load();
       if (error_code != foxit::e_ErrSuccess) {
         printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
         return 1;
       }

       FILE* file = NULL;
#if defined(_WIN32) || defined(_WIN64)
       fopen_s(&file, (const char*)(const char*)String::FromUnicode(fdf_file), "rb+");
#else
       file = fopen((const char*)(const char*)String::FromUnicode(fdf_file), "rb+");
#endif
       fseek(file, 0, SEEK_END);
       size_t file_size = (size_t)ftell(file);
       char* buffer = (char*)malloc(file_size * sizeof(char));
       memset(buffer, 0 , file_size);

       fseek(file, 0, SEEK_SET);
       fread(buffer, sizeof(char), file_size, file);
       fclose(file);

       fdf::FDFDoc fdf_doc(buffer, file_size);
       pdf_doc.ImportFromFDF(fdf_doc, PDFDoc::e_Annots);
       WString output_file = output_directory + L"AboutFoxit_importFDF_FromMemory.pdf";
       pdf_doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);
       free(buffer);
    }

    {
      // Export FDF file
      WString input_file = input_path + L"AnnotationDataExport.pdf";
      WString output_fdf = output_directory + L"AnnotationDataExport_fdf.fdf";

      pdf::PDFDoc pdf_doc(input_file);
      ErrorCode error_code = pdf_doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }

      fdf::FDFDoc fdf_doc(foxit::fdf::FDFDoc::e_FDF);
      pdf_doc.ExportToFDF(fdf_doc, pdf::PDFDoc::e_Annots);

      fdf_doc.SaveAs(output_fdf);

    }
    {
      // Export XFDF file
      WString input_file = input_path + L"AnnotationDataExport.pdf";
      WString output_xfdf = output_directory + L"AnnotationDataExport_xfdf.xfdf";

      pdf::PDFDoc pdf_doc(input_file);
      ErrorCode error_code = pdf_doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }

      fdf::FDFDoc fdf_doc(foxit::fdf::FDFDoc::e_XFDF);
      pdf_doc.ExportToFDF(fdf_doc, pdf::PDFDoc::e_Annots);

      fdf_doc.SaveAs(output_xfdf);
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
