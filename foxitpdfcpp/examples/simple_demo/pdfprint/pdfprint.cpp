// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to print PDF pages.

#include <time.h>
#include <iostream>

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/graphics/fs_pdfgraphicsobject.h"
#include "../../../include/pdf/fs_pdfpage.h"

#include "../../../include/common/fs_render.h"

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

int main(int argc, char *argv[])
{
  int err_ret = 0;
  WString input_file = input_path + L"annotations.pdf";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    // Load PDF document.
    PDFDoc doc(input_file);
    ErrorCode code = doc.Load();
    if (code != foxit::e_ErrSuccess) {
      printf("[Failed] Cannot load PDF document %s.\r\nError Code: %d\r\n", (const char*)String::FromUnicode(input_file),code);
      return 1;
    }
    HDC hdc_print = NULL;  // Printer DC handle
    char dev_string[120];  // An array for WIN.INI data
    char *printer = NULL, *driver = NULL;  // Printer name and driver name
    char *port = NULL;  // Port name
    char* context = NULL;

    // Retrieve the printer, printer driver, and output-port names from WIN.INI.
    GetProfileStringA("windows", "device", ",,,", dev_string, 120);

    // Parse the string of names, setting ptrs as required.
    // If the string contains the required names, use them to create a device context.
    if ((printer = strtok_s(dev_string, (const char *)",", &context)) && (driver = strtok_s((char *)NULL, (const char *)", ", &context)) &&
      (port = strtok_s((char *)NULL, (const char *)", ", &context))) {
        hdc_print = CreateDCA(driver, printer, port, NULL);
    }

    if (!hdc_print) {
      printf("[Failed] Cannot create HDC for print.\r\n");
      return 1;
    }

    char print_doc_name[128] = "";
    sprintf_s(print_doc_name, "FoxitPDFSDK_PrintingTest_%s", (const char*)String::FromUnicode(input_file));
    DOCINFOA doc_info;
    ZeroMemory(&doc_info, sizeof(DOCINFOA));
    doc_info.cbSize = sizeof(DOCINFOA);
    doc_info.lpszDocName = print_doc_name;
    doc_info.lpszOutput = NULL;
    doc_info.fwType = 0;
    // Begin a print job by calling the StartDoc function.
    int nError = StartDocA(hdc_print, &doc_info);
    if(nError == SP_ERROR) {
      MessageBoxA(NULL, "Error", "Error, Printing", MB_OK | MB_ICONEXCLAMATION);
      return 1;
    }
    int page_count = doc.GetPageCount();
    for (int i=0; i< page_count; i++) {
      PDFPage page = doc.GetPage(i);
      // Parse page.
      page.StartParse(PDFPage::e_ParsePageNormal, NULL, false);

      int width = static_cast<int>(page.GetWidth());
      int height = static_cast<int>(page.GetHeight());

      // Inform the driver that the application is about to begin sending data.
      nError = StartPage(hdc_print);
      if(nError == SP_ERROR) {
        MessageBoxA(NULL, "Error", "Error, Printing", MB_OK | MB_ICONEXCLAMATION);
        return 1;
      }

      float device_width = (float)GetDeviceCaps(hdc_print, HORZRES);
      float device_height = (float)GetDeviceCaps(hdc_print, VERTRES);
      float x_scale = device_width / width;
      float y_scale = device_height / height;

      float scale = x_scale < y_scale ? x_scale : y_scale;
      float x_offset = 0.0;
      float y_offset = 0.0;
      if (x_scale < y_scale) {
        y_offset = (device_height - scale * height) / 2;
        device_height = scale * height;
      } else {
        x_offset = (device_width - scale * width) / 2;
        device_width = scale * width;
      }

      RECT rect = {(LONG)x_offset, (LONG)y_offset, (LONG)(device_width + x_offset), (LONG)(device_height + y_offset)};
      Matrix matrix = page.GetDisplayMatrix(rect.left, rect.top, (int)device_width, (int)device_height,
        e_Rotation0);

      HBRUSH hBrush = CreateSolidBrush(RGB(0xff, 0xff, 0xff));
      FillRect(hdc_print, &rect, hBrush);
      DeleteObject(hBrush);

      Renderer render_print(hdc_print);
      RectI clip_rect(rect.left, rect.top, rect.right, rect.bottom);
      render_print.SetClipRect(&clip_rect);
      render_print.StartRender(page, matrix, NULL);

      // Inform the spooler that the page is complete.
      EndPage(hdc_print);
    }
    // Inform the driver that document has ended.
    EndDoc(hdc_print);
    // Release the device context.
    DeleteDC(hdc_print);
    cout << "Print a PDF file." << endl;

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

