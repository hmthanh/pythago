// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do bitmap transformation,
// such as flipping, stretching, and so on.

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
#include "../../../include/common/fs_image.h"

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

void SaveBitmap(Bitmap bitmap, WString file_path) {
  Image image;
  image.AddFrame(bitmap);
  image.SaveAs(file_path);
}

int main(int argc, char *argv[])
{
  int err_ret = 0;
  WString input_file = input_path + L"Foxit.bmp";
  
  WString output_directory = output_path + L"bitmap_transform/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try{
    Image image(input_file);
    Bitmap bitmap = image.GetFrameBitmap(0);

    int width = bitmap.GetWidth();
    int height = bitmap.GetHeight();

    // Stretch bitmap.
    Bitmap stretch_bitmap = bitmap.StretchTo(width / 2, height * 2, Bitmap::e_Downsample, NULL);
    WString output_file = output_directory + L"stetch_bitmap_Foxit.bmp";
    SaveBitmap(stretch_bitmap, output_file);

    // Transform bitmap.
    int left, top;
    Bitmap transform_bitmap = bitmap.TransformTo(foxit::Matrix(width * 2.0f, 0.f, 0.f, height / 2.0f, 0.f, 0.f),
      Bitmap::e_Downsample, left, top, NULL);
    output_file = output_directory + L"transform_bitmap_Foxit.bmp";
    SaveBitmap(transform_bitmap, output_file);

    // Vertical and horizontal flip bitmap.
    Bitmap flip_bitmap = bitmap.Flip(true, true);
    output_file = output_directory + L"flip_horz_vert_Foxit.bmp";
    SaveBitmap(flip_bitmap, output_file);

    // Swap the X and Y axis, and then vertical and horizontal flip bitmap.
    Bitmap swap_xy_bitmap = bitmap.SwapXY(true, true, NULL);
    output_file = output_directory + L"swap_xy_flip_horz_vert_Foxit.bmp";
    SaveBitmap(swap_xy_bitmap, output_file);

    // Calculate the bounding box according to the given background color.
    RectI rect = bitmap.CalculateBBoxByColor(0xFFFDFDFD);
    Bitmap clone_bitmap;
    if (rect.Height() > 0 && rect.Width() > 0) {
      clone_bitmap = bitmap.Clone(&rect);
      output_file = output_directory + L"calculate_bbox_by_color_0xFFFDFDFD_foxit.bmp";
      SaveBitmap(clone_bitmap,output_file);
    } else {
      printf(
        "[Warning] The result of bounding box (according to the given background color) is an empty rectangle.\r\n");
    }

    // Detect the bounding box of content according to the given color difference between content and margin.
    rect = bitmap.DetectBBoxByColorDiffer(20, 64);
    if (rect.Height() > 0 && rect.Width() > 0) {
      clone_bitmap = bitmap.Clone(&rect);
      output_file = output_directory + L"detect_bbox_by color_differ_20_64_Foxit.bmp";
      SaveBitmap(clone_bitmap,output_file);
    } else {
      printf(
        "[Warning] The result of bounding box (according to the given color difference between content and margin)"
        " is an empty rectangle.\r\n");
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