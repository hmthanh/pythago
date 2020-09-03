// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to add watermarks (in different types)
// into PDF files.

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
#include "../../../include/pdf/fs_watermark.h"

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

void AddTextWatermark(PDFDoc doc, PDFPage page) {
  WatermarkSettings settings;
  settings.flags = WatermarkSettings::e_FlagASPageContents | WatermarkSettings::e_FlagOnTop;
  settings.offset_x = 0;
  settings.offset_y = 0;
  settings.opacity = 90;
  settings.position = common::e_PosTopRight;
  settings.rotation = -45.f;
  settings.scale_x = 1.f;
  settings.scale_y = 1.f;

  WatermarkTextProperties text_properties;
  text_properties.alignment = CommonDefines::e_AlignmentCenter;
  text_properties.color = 0xF68C21;
  text_properties.font_style = WatermarkTextProperties::e_FontStyleNormal;
  text_properties.line_space = 1;
  text_properties.font_size = 12.f;
  text_properties.font = Font(Font::e_StdIDTimesB);

  Watermark watermark(doc, L"Foxit PDF SDK\nwww.foxitsoftware.com", text_properties, settings);
  watermark.InsertToPage(page);

}

void AddBitmapWatermark(PDFDoc doc, PDFPage page, WString bitmap_file) {
  WatermarkSettings settings;
  settings.flags = WatermarkSettings::e_FlagASPageContents | WatermarkSettings::e_FlagOnTop;
  settings.offset_x = 0.f;
  settings.offset_y = 0.f;
  settings.opacity = 60;
  settings.position = common::e_PosCenterLeft;
  settings.rotation = 90.f;

  Image image(bitmap_file);
  Bitmap bitmap = image.GetFrameBitmap(0);
  settings.scale_x = page.GetHeight() * 1.0f / bitmap.GetWidth();
  settings.scale_y = settings.scale_x;
  Watermark watermark(doc, bitmap, settings);
  watermark.InsertToPage(page);
}

void AddImageWatermark(PDFDoc doc, PDFPage page, WString image_file) {
  WatermarkSettings settings;
  settings.flags = WatermarkSettings::e_FlagASPageContents | WatermarkSettings::e_FlagOnTop;
  settings.offset_x = 0.f;
  settings.offset_y = 0.f;
  settings.opacity = 20;
  settings.position = common::e_PosCenter;
  settings.rotation = 0.0f;

  Image image(image_file);
  Bitmap bitmap = image.GetFrameBitmap(0);
  settings.scale_x = page.GetWidth() * 0.618f / bitmap.GetWidth();
  settings.scale_y = settings.scale_x;

  Watermark watermark(doc, image, 0, settings);
  watermark.InsertToPage(page);
}

void AddSingleWatermark(PDFDoc doc, PDFPage page) {
  WatermarkSettings settings;
  settings.flags = WatermarkSettings::e_FlagASPageContents|WatermarkSettings::e_FlagOnTop;
  settings.offset_x = 0.f;
  settings.offset_y = 0.f;
  settings.opacity = 90;
  settings.position = common::e_PosBottomRight;
  settings.rotation = 0.0f;
  settings.scale_x = 0.1f;
  settings.scale_y = 0.1f;

  Watermark watermark(doc, page, settings);
  watermark.InsertToPage(page);
}

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"watermark/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"AboutFoxit.pdf";
  WString output_file = output_directory + L"watermark_add.pdf";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();

    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }
    int page_count = doc.GetPageCount();
    for(int i=0; i<page_count; i++)
    {
      PDFPage page = doc.GetPage(i);
      page.StartParse(PDFPage::e_ParsePageNormal, NULL, false);

      AddTextWatermark(doc, page);
      WString wm_bmp = input_path + L"watermark.bmp";
      AddBitmapWatermark(doc, page,wm_bmp );
      WString wm_image = input_path + L"sdk.png";
      AddImageWatermark(doc, page, wm_image);
      AddSingleWatermark(doc, page);
    }

    doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);
    cout << "Add watermarks to PDF file." << endl;

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
