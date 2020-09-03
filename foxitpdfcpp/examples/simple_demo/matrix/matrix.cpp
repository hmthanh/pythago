// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file is a demo to demonstrate how to use matrix to translate, scale... objects.

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
#include "../../../include/pdf/objects/fs_pdfobject.h"

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
WString output_directory = output_path + L"matrix/";

class SdkLibMgr {
public:
  SdkLibMgr() : isInitialize(false){};
  ErrorCode Initialize() {
    ErrorCode error_code = Library::Initialize(sn, key);
    if (error_code != foxit::e_ErrSuccess) {
      printf("Library Initialize Error: %d\n", error_code);
    } else {
      isInitialize = true;
    }
    return error_code;

  }
  ~SdkLibMgr(){
    if(isInitialize)
      Library::Release();
  }
private:
  bool isInitialize;
};
int main(int argc, char *argv[])
{
  int err_ret = 0;
  WString input_file = input_path + L"SamplePDF.pdf";
  WString output_directory = output_path + L"matrix/";
  WString file_info = output_directory + L"matrix_info.txt";

#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  SdkLibMgr spSdkLibMgr;
  // Initialize library.
  ErrorCode error_code = spSdkLibMgr.Initialize();
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
    // Get and parse page.
    PDFPage page = doc.GetPage(0);
    page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);
    POSITION pos = page.GetFirstGraphicsObjectPosition();
    int flag = 0;
    while(pos) {
      if(flag == (2 | 4))
        break;
      graphics::GraphicsObject* obj = page.GetGraphicsObject(pos);
      pos = page.GetNextGraphicsObjectPosition(pos);
      graphics::GraphicsObject::Type type = obj->GetType();
      float start_x = 0;
      // Get one TextObject or one ImageObject.
      if(type == graphics::GraphicsObject::e_TypeText && !(flag & 2)) {
        graphics::TextObject* text_obj = (graphics::TextObject*)obj;
        WString text = text_obj->GetText();
        if(text.Compare(L"Foxit Software Incorporated") != 0){
          continue;
        }
        start_x = 400.0f;
        flag |= 2;
      } else if(type == graphics::GraphicsObject::e_TypeImage && !(flag & 4)) {
        start_x = 150.0f;
        flag |= 4;
      }else{
        continue;
      }

      // Now we have found the TextObject or the ImageObject, transform them.
      graphics::GraphicsObject* clone_obj1 = obj->Clone();
      Matrix matrix = clone_obj1->GetMatrix();
      // Translate the matrix in vertical direction.
      matrix.Translate(0, 150);
      clone_obj1->SetMatrix(matrix);
      page.InsertGraphicsObject(NULL, clone_obj1);

      graphics::GraphicsObject* clone_obj2 = obj->Clone();
      matrix = clone_obj2->GetMatrix();
      float d = matrix.d;
      float e = matrix.e;
      float f = matrix.f;
      // Translate it to the original point(0,0) first
      matrix.Translate(-e, -f);
      // Rotate the matrix 90 degree in anticlockwise direction.
      matrix.Rotate(1.57f);
      //Page rotation should be considered, assume that the current page rotation is 0.
      float distance = d;
      if(type == graphics::GraphicsObject::e_TypeText)
      {
        RectF obj_rect = obj->GetRect();
        distance = obj_rect.top - obj_rect.bottom;
      }
      // Translate it to the specific coordinate(start_x,400)
      matrix.Translate(distance + start_x , 400);
      clone_obj2->SetMatrix(matrix);
      page.InsertGraphicsObject(NULL, clone_obj2);

      graphics::GraphicsObject* clone_obj3 = obj->Clone();
      matrix = clone_obj3->GetMatrix();
      // Translate it to the original point(0,0) first
      matrix.Translate(-e, -f);
      // Magnify the matrix 1.5 times in both horizontal and vertical directions.
      matrix.Scale(1.5, 1.5);
      // Translate it to the specific coordinate(start_x,600)
      matrix.Translate(start_x, 600.0f);
      clone_obj3->SetMatrix(matrix);
      page.InsertGraphicsObject(NULL, clone_obj3);

      graphics::GraphicsObject* clone_obj4 = obj->Clone();
      matrix = clone_obj4->GetMatrix();
      // Translate it to the original point(0,0) first
      matrix.Translate(-e, -f);
      // Skews the x axis by an angle 0.5 and the y axis by an angle 0.5.
      matrix.Shear(0.5, 0.5);
      // Translate it to the specific coordinate(start_x,800)
      matrix.Translate(start_x, 800.0f);
      clone_obj4->SetMatrix(matrix);
      page.InsertGraphicsObject(NULL, clone_obj4);
    }
    // Generate the page content
    page.GenerateContent();

    // Save the pdf document
    doc.SaveAs(output_directory + L"/MatrixTransformResult.pdf");
    cout << "Matrix demo." << endl;

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