// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do PDF page organization,
// such as inserting, removing, and so on.

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
#include "../../../include/pdf/graphics/fs_pdfgraphicsobject.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace graphics;

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

WString output_directory = output_path + L"page_organization/";

void AddTextObjects(PDFPage page, const wchar_t* content) {
  POSITION position = page.GetLastGraphicsObjectPosition(GraphicsObject::e_TypeText);
  TextObject* text_object = TextObject::Create();

  text_object->SetFillColor(0xFFAAAAAA);
  text_object->SetStrokeColor(0xFFF68C21);

  // Prepare text state
  TextState state;
  state.font_size = 64.0f;
  state.font = Font(Font::e_StdIDTimes);
  state.textmode = TextState::e_ModeFillStrokeClip;

  text_object->SetTextState(page, state, false, 750);

  // Set content
  text_object->SetText(content);
  page.InsertGraphicsObject(position, text_object);

  // Transform to center
  RectF rect = text_object->GetRect();
  float offset_x = (page.GetWidth() - (rect.right - rect.left)) / 2;
  float offset_y = (page.GetHeight() - (rect.top - rect.bottom)) / 2;
  text_object->Transform(Matrix(1, 0, 0, 1, offset_x, offset_y), false);

  // Generator content
  page.GenerateContent();
}

bool InsertPage() {
  WString input_file = input_path + L"page_organization_123.pdf";
  PDFDoc doc = PDFDoc(input_file);
  ErrorCode code = doc.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), code);
    return false;
  }

  PDFPage page = doc.InsertPage(-1);
  AddTextObjects(page, L"insert in first");
  page = doc.InsertPage(2);
  AddTextObjects(page, L"insert in 2 (based 0)");
  page = doc.InsertPage(doc.GetPageCount());
  AddTextObjects(page, L"insert in last");
  WString output_file = output_directory + L"insert_page.pdf";
  doc.SaveAs(output_file, PDFDoc::e_SaveFlagNormal);
  cout << "Insert pages." << endl;
  return true;
}

bool RemovePage() {
  WString input_file = input_path + L"page_organization_123.pdf";
  PDFDoc doc = PDFDoc(input_file);
  ErrorCode code = doc.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), code);
    return false;
  }

  while (doc.GetPageCount() > 1) {
    doc.RemovePage(0);
  }
  WString output_file = output_directory + L"remove_all_pages_exceptt_the_last_page.pdf";
  doc.SaveAs(output_file,  PDFDoc::e_SaveFlagNormal);
  cout << "Remove pages." << endl;
  return true;
}

// You can implement the functionality of exporting pages by creating an empty document
// and importing part of the source document into the empty document.
// You can also import the target document as a source document
// to implement the copy page functionality.
bool ImportPage() {
  WString file_dest = input_path + L"page_organization_123.pdf";
  WString file_src = input_path + L"page_organization_abc.pdf";
  PDFDoc doc_dest = PDFDoc(file_dest);
  ErrorCode code = doc_dest.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(file_dest), code);
    return false;
  }
  PDFDoc doc_src = PDFDoc(file_src);
  code = doc_src.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(file_src), code);
    return false;
  }
  // Import page from PDFDoc object.
  Range import_ranges(0);
  import_ranges.AddSingle(doc_src.GetPageCount()-1);
  Progressive progressive =
    doc_dest.StartImportPages(-1,  doc_src, PDFDoc::e_ImportFlagNormal, "abc", import_ranges, NULL);
  while (progressive.Continue() != Progressive::e_Finished) {
  }
  WString output_file = output_directory + L"page_organization_abc_to_123_import_pages.pdf";
  doc_dest.SaveAs(output_file, PDFDoc::e_SaveFlagNormal);

  doc_dest = PDFDoc(file_dest);
  code = doc_dest.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(file_dest), code);
    return false;
  }
  // Import page from file path.
  progressive = doc_dest.StartImportPagesFromFilePath(-1, file_src, "", PDFDoc::e_ImportFlagNormal, "abc",
    import_ranges, NULL);
  while (progressive.Continue() != Progressive::e_Finished) {
  }
  output_file = output_directory + L"abc_to_123_import_pages_form_filepath.pdf";
  doc_dest.SaveAs(output_file,PDFDoc::e_SaveFlagNormal);
  cout << "Import pages." << endl;
  return true;
}

bool MovePages()
{
  WString input_file = input_path + L"page_organization_123.pdf";
  WString input_file1 = input_path + L"page_organization_abc.pdf";
  // Move page
  PDFDoc doc = PDFDoc(input_file);
  ErrorCode code = doc.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), code);
    return false;
  }
  int count = doc.GetPageCount();
  PDFPage page = doc.GetPage(0);
  doc.MovePageTo(page, doc.GetPageCount() - 1);
  WString output_file1 = output_directory + L"move_first_page_to_last.pdf";
  doc.SaveAs(output_file1, PDFDoc::e_SaveFlagNormal);

  doc = PDFDoc(input_file1);
  code = doc.Load();
  if (code != foxit::e_ErrSuccess) {
    return false;
  }
  Range page_set;
  for (int i = 0; i < count / 2; i++)
    page_set.AddSingle(2 * i);
  doc.MovePagesTo(page_set, doc.GetPageCount() - 1);
  WString output_file = output_directory + L"move_pages.pdf";
  doc.SaveAs(output_file, PDFDoc::e_SaveFlagNormal);
  cout << "Move pages." << endl;
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
  WString input_file = input_path + L"page_organization_123.pdf";
  WString input_file1 = input_path + L"page_organization_abc.pdf";
  SdkLibMgr sdk_lib_mgr;
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    if (!(InsertPage() && RemovePage() && ImportPage() && MovePages())) {
      return 1;
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
