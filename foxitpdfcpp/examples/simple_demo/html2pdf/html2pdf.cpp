// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to convert url web pages or html files to PDF document.

// Include Foxit SDK header files.
#if defined(_WIN32) || defined(_WIN64) || defined (__APPLE__)

#include<string.h>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/addon/conversion/fs_convert.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;

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
  SdkLibMgr() : is_initialize_(false) {};
  ErrorCode Initialize() {
    ErrorCode error_code = Library::Initialize(sn, key);
    if (error_code != foxit::e_ErrSuccess) {
      printf("Library Initialize Error: %d\n", error_code);
    } else {
      is_initialize_ = true;
    }
    return error_code;
  }
  ~SdkLibMgr() {
    if (is_initialize_)
      Library::Release();
  }
private:
  bool is_initialize_;
};

#define HTML2PDFMSG       printf("Please make sure the key %s is valid and it has value.\n", (FX_LPCSTR)argv_key); \
                          printf("Usage: html2pdf_xxx <-html <The url or html path>> <-o <output pdf path>> ...\nPlease try 'html2pdf_xxx --help' for more information.\n");

bool AnalysisParameter(int argc, char* argv[], foxit::addon::conversion::HTML2PDFSettingData& pdf_setting_data, WString& url_or_html, WString& engine_path, WString& cookies_path, WString& output_path, int& timeout) {
  for (int i = 1; i < argc; i = i + 2) {
    String argv_key = String(argv[i]);
    String argv_value;
    if (argc <= i + 1) {
      HTML2PDFMSG
      return false;
    }
    argv_value = String(argv[i + 1]);
    if (argv_key.Equal("-w")) pdf_setting_data.page_width = FX_atof(argv_value);
    else if (argv_key.Equal("-h")) pdf_setting_data.page_height = FX_atof(argv_value);
    else if (argv_key.Equal("-r")) pdf_setting_data.rotate_degrees = (foxit::common::Rotation)FXSYS_atoi(argv_value);
    else if (argv_key.Equal("-ml")) pdf_setting_data.page_margin.left = FX_atof(argv_value);
    else if (argv_key.Equal("-mr")) pdf_setting_data.page_margin.right = FX_atof(argv_value);
    else if (argv_key.Equal("-mt")) pdf_setting_data.page_margin.top = FX_atof(argv_value);
    else if (argv_key.Equal("-mb")) pdf_setting_data.page_margin.bottom = FX_atof(argv_value);
    else if (argv_key.Equal("-scale")) pdf_setting_data.is_to_page_scale = argv_value.EqualNoCase("yes") ? true : false;
    else if (argv_key.Equal("-link")) pdf_setting_data.is_convert_link = argv_value.EqualNoCase("yes") ? true : false;
    else if (argv_key.Equal("-tag")) pdf_setting_data.is_generate_tag = argv_value.EqualNoCase("yes") ? true : false;
    else if (argv_key.Equal("-mode")) pdf_setting_data.page_mode = (foxit::addon::conversion::HTML2PDFSettingData::HTML2PDFPageMode)FXSYS_atoi(argv_value);
    else if (argv_key.Equal("-engine")) engine_path = CFX_WideString::FromUTF8(argv_value);
    else if (argv_key.Equal("-cookies")) cookies_path = CFX_WideString::FromUTF8(argv_value);
    else if (argv_key.Equal("-o")) output_path = CFX_WideString::FromUTF8(argv_value);
    else if (argv_key.Equal("-html")) url_or_html = CFX_WideString::FromUTF8(argv_value);
    else if (argv_key.Equal("-timeout")) timeout = FXSYS_atoi(argv_value);
    else {
      HTML2PDFMSG
      return false;
    }
  }

  return true;
}

int main(int argc, char *argv[]) {
  if (argc > 1 && String(argv[1]).Equal("--help")) {
      cout << "Usage:" << endl << "html2pdf_xxx <-html <The url or html path>> <-o <output pdf path>> <-engine <htmltopdf engine path>>" << endl <<
          " [-w <page width>] [-h <page height>] [-ml <margin left>] [-mr <margin right>] [-mt <margin top>] [-mb <margin bottom>] [-r <page rotate degree>] [-mode <page mode>] [-scale <whether scale page>]" << endl <<
          " [-link <whether convert link>] [-tag <whether generate tag>] [-cookies <cookies file path>] [-timeout <timeout>]" << endl << endl <<
          "-html The url or html file path. for examples '-html www.foxitsoftware.com'" << endl <<
          "-o The output pdf path." << endl <<
          "-engine The html to pdf engine path." << endl <<
          "-w The page width." << endl <<
          "-h The page height." << endl <<
          "-r The page roate degree. '0' means 0 degree, '1' means 90 degree, '2' means 180 degree, '3' means 270 degree." << endl <<
          "-ml The page margin distance of left." << endl <<
          "-mr The page margin distance of right." << endl <<
          "-mt The page margin distance of top." << endl <<
          "-mb The page margin distance of bottom." << endl <<
          "-mode The page mode. 0 means single page mode and 1 means multiple mode" << endl <<
          "-scale Whether scale page. 'yes' means scale page, 'no' means no need to scale." << endl <<
          "-link Whether covert link. 'yes' means convert link, 'no' means no need to covert." << endl <<
          "-tag Whether generate tag. 'yes' means generate tag, 'no' means no need to generate." << endl <<
          "-cookies The cookies file path." << endl <<
          "-timeout The timeout of loading webpages." << endl;
    return 0;
  }

  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }
  WString output_directory = output_path + L"html2pdf/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  WString url_or_html = input_path + L"AboutFoxit.html";

  // "engine_path" is the path of the engine file "fxhtml2pdf" which is used to converting html to pdf. Please refer to Developer Guide for more details.
  WString engine_path = L"";

  // "cookies_path" is the path of the cookies file exported from the web pages that you want to convert. Please refer to Developer Guide for more details.
  WString cookies_path = L"";

  WString output_path = output_directory + L"html2pdf_result.pdf";

  int time_out = 15;

  try {
    foxit::addon::conversion::HTML2PDFSettingData pdf_setting_data;
    pdf_setting_data.is_to_page_scale = true;
    pdf_setting_data.is_convert_link = true;
    pdf_setting_data.is_generate_tag = true;
    pdf_setting_data.rotate_degrees = foxit::common::e_Rotation0;
    pdf_setting_data.page_height = 640;
    pdf_setting_data.page_width = 900;
    pdf_setting_data.page_mode = foxit::addon::conversion::HTML2PDFSettingData::e_PageModeSinglePage;

    if (!AnalysisParameter(argc, argv, pdf_setting_data, url_or_html, engine_path, cookies_path, output_path, time_out)) return 1;
    foxit::addon::conversion::Convert::FromHTML(url_or_html, engine_path, cookies_path, pdf_setting_data, output_path, time_out);

    cout << "Convert HTML to PDF successfully." << endl;
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  } catch (...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}
#endif

