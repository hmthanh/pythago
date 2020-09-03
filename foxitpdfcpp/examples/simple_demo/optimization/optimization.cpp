// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do optimize in PDF documents under a folder.

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
#include "../../../include/addon/optimization/fs_optimization.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace foxit::addon;

static const char* sn = "eUcaj+XFRdwDeV4fx2eGZzF7ZmQiBNInjxfWhiHCIinKYg3KsYgcKg==";
static const char* key = "8f0YFcONvRsJ+nePmKBLSM8bw7bGx79neQeRmlgo13uto3HGtEFz4BLMd5BErJbDU1Nll8omHE6H+Vx20kaMiDQYMDldaA9ctpwcoLODu8yfFtHTm2UseIiHVjqu52IRK18VKf4pLWI6ekSbkAafVjd3XxT8Gv6TtRASa2U4/v/xFR99REZVOqq8tPSQT5b521y1tTBJaTKxB23KwsVuONGlSM8ZH0PiPkjuRmZsfp9aVqpWVSfBMZFqw4+XYbQdImYgzqkq/vgaZ7ApxW0ICzjtIiJ0x/15o+rOFQhMh6+9kSGq4OhjfzY8ZRqTyFQ2dy2SRF+tQKD87bTJUrDkf9mRXbvK+xpDrPpT7dMgTj0R6yjrwJpRt6LcimMv+LvSjbKvAG6KFxn6UMfWVi8bkFM/hzvwRJe/aoyPbYQ72lFMHeYreJNaAKYpO8CBF9mi5KbDDXYNtaoEgUVVukppYbS/wVpdQwlC7J85A9yLmelDEufSbz/RVOwv2LZKHsk6iFgaV4U74YrYiwIT4xE8znliw4xnOd6j+MCBdcmMvOyGKUeNrD7Q042c6Pn5QPGchkmmPuhqwrcnRXYiYEOyMs4LnsdhKSxJk4Q2yoc9b6Fhb8RQbUARzbTfAw9L/ZgooZ2tVhFFJnCFhkU4U76twoB1plg3L2KEAH4smtZjVh0k8uoaDt9JQOk/K5YaKiAI3TPB6AlsaDLguQClqyRsK04OyO/CZkoPsvLoGa1EyBpppKcwOe3PyF4zYuNEQRRZh48L/5loWJPf+ynWj1fR+NcVnTqe8GqFk0vP3uK5C8FaJxKP3a0bekr0tKCfe4yxte4Ej8yo/3plnDz03GXUB+FgsdMINm3rA2UhTNdYjRJtIRNJomCkjQr7GHyEsTq71Q6O0wuOSet0byPcLPPhcXzsSqpWYZ9+opORXE92LCwuHJRZOtuzpjvAphi0kiCRk4dSR0VP8FmL5yNG2M2okeEb8bjXD52ErTBTIAk3VZnh4OOCSfzgpZhoEvr5usjkfyry9BmgX2gWAJYRTUrEgDTXHj5YQ6MT3grfDGYMqKoy7GSpb3tY5zBHzzoJDK/E1VvO+ScyQaJQJ0eHgsgy2QZbCnEB3W4N5M8HqBqNMw+0oUvqw0P1i4uK9XwCGzVyyOXs1czCsWGg8R8Ej51AL+9gXdu7RMdEaP2lTMkOJfScJbzsOkfjxvX5LBrHVZ98XuzZylbeFkVr/gjrvBnfucL9zCmjngYq4RfzDYBOzx31gRuFFAsllK4zFRgtHWSXGXwXim4OJpMVKEuFHO5Oupowvd9cdzRIjGpWzR0=";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/optimization/");
#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/optimization/");
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

class Optimization_Pause : public PauseCallback
{
public:
    Optimization_Pause(int pause_count_limit = 0, bool always_pause = false)
        :pause_count_(0)
        ,pause_count_limit_(pause_count_limit)
        ,always_pause_(always_pause)
    {

    }

    virtual FX_BOOL NeedToPauseNow()
    {
        if (always_pause_) return true;
        if (pause_count_< pause_count_limit_)
        {
            pause_count_ ++;
            return 1;
        }
        else{
            pause_count_ = 0;
            return 0; // This is to test a case: valid PauseCallback but needParseNow() will always return FALSE.
        }
    }

    void  ClearCount()
    {
        pause_count_ = 0;
    }

private:
    int pause_count_limit_;
    int pause_count_;
    bool always_pause_;
};


int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"optimization/";
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
  cout << "Optimized Start : Image Compression." << endl;
  WString input_file = input_path +  L"[Optimize]ImageCompression.pdf";
  try
  {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
          printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_path), error_code);
          return 1;
      }
      Optimization_Pause pause(0, true);
      addon::optimization::OptimizerSettings settings;
      settings.SetOptimizerOptions(foxit::addon::optimization::OptimizerSettings::e_OptimizerCompressImages);
      common::Progressive progressive = addon::optimization::Optimizer::Optimize(doc, settings, &pause);
      Progressive::State progress_state = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == progress_state) {
          progress_state = progressive.Continue();
          int percent = progressive.GetRateOfProgress();
          String res_string;
          res_string.Format("Optimize progress percent: %d %", percent);
          std::cout << res_string << std::endl;
      }
      if (Progressive::e_Finished == progress_state)
      {
          doc.SaveAs(output_directory + L"ImageCompression_Optimized.pdf", foxit::pdf::PDFDoc::e_SaveFlagRemoveRedundantObjects);
      }
  } catch (...) {
    cout << "Unknown Exception" << endl;
    return 1;
  }
  cout << "Optimized Finsih : Image Compression." << endl;

  cout << "Optimized Start : Clean up." << endl;
  input_file = input_path + L"[Optimize]Cleanup.pdf";
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_path), error_code);
      return 1;
    }
    Optimization_Pause pause(0, true);
    addon::optimization::OptimizerSettings settings;
    settings.SetOptimizerOptions(foxit::addon::optimization::OptimizerSettings::e_OptimizerCleanUp);
    settings.SetCleanUpOptions(optimization::OptimizerSettings::e_CleanUpRemoveInvalidBookmarks | optimization::OptimizerSettings::e_CleanUpRemoveInvalidLinks
      | optimization::OptimizerSettings::e_CleanUpUseFlateForNonEncodedStream | optimization::OptimizerSettings::e_CleanUpUseFlateInsteadOfLZW);
    common::Progressive progressive = addon::optimization::Optimizer::Optimize(doc, settings, &pause);
    Progressive::State progress_state = Progressive::e_ToBeContinued;
    while (Progressive::e_ToBeContinued == progress_state) {
      progress_state = progressive.Continue();
      int percent = progressive.GetRateOfProgress();
      String res_string;
      res_string.Format("Optimize progress percent: %d %", percent);
      std::cout << res_string << std::endl;
    }
    if (Progressive::e_Finished == progress_state) {
      doc.SaveAs(output_directory + L"Cleanup_Optimized.pdf", foxit::pdf::PDFDoc::e_SaveFlagRemoveRedundantObjects);
    }
  } catch (...) {
    cout << "Unknown Exception" << endl;
    return 1;
  }
  cout << "Optimized Finsih : Clean up." << endl;

  cout << "Optimized Start : Discard Objects." << endl;
  input_file = input_path + L"[Optimize]DiscardObjects.pdf";
  try {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
          printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_path), error_code);
          return 1;
      }
      Optimization_Pause pause(0, true);
      addon::optimization::OptimizerSettings settings;
      settings.SetOptimizerOptions(foxit::addon::optimization::OptimizerSettings::e_OptimizerDiscardObjects);
      settings.SetDiscardObjectsOptions(optimization::OptimizerSettings::e_DiscardObjectsBookmarks | optimization::OptimizerSettings::e_DiscardObjectsEmbeddedPageThumbnails
          | optimization::OptimizerSettings::e_DiscardObjectsEmbeddedPrintSettings | optimization::OptimizerSettings::e_DiscardObjectsFlattenFormFields 
          | optimization::OptimizerSettings::e_DiscardObjectsFormActions | optimization::OptimizerSettings::e_DiscardObjectsJavaScriptActions);

      common::Progressive progressive = addon::optimization::Optimizer::Optimize(doc, settings, &pause);
      Progressive::State progress_state = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == progress_state) {
          progress_state = progressive.Continue();
          int percent = progressive.GetRateOfProgress();
          String res_string;
          res_string.Format("Optimize progress percent: %d %", percent);
          std::cout << res_string << std::endl;
      }
      if (Progressive::e_Finished == progress_state) {
          doc.SaveAs(output_directory + L"DiscardObjects_Optimized.pdf", foxit::pdf::PDFDoc::e_SaveFlagRemoveRedundantObjects);
      }
  }
  catch (...) {
      cout << "Unknown Exception" << endl;
      return 1;
  }
  cout << "Optimized Finsih : Discard Objects." << endl;
  return err_ret;
}