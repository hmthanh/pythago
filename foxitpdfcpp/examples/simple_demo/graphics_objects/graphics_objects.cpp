// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to create a PDF document,
// insert the text path and image objects into the created PDF document, copy shading objects,
// and save the file with inserted graphics objects.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/graphics/fs_pdfgraphicsobject.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"

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

class TextDoc {
public:
  TextDoc(const String& file_name, const String& fill_mode);
  TextDoc(const WString& file_name, const WString& fill_mode);
  ~TextDoc();

  void Write(const char* text_content);
  void Write(const wchar_t* text_content);

private:
  FILE * file_;
};

TextDoc::TextDoc(const String& file_name, const String& file_mode) throw(Exception)
  : file_(NULL) {
#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, file_name, (const char*)file_mode);
#else
  file_ = fopen((const char*)file_name, (const char*)file_mode);
#endif

  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);

  uint8 temp[] = { 0xFF, 0xFE };
  fwrite(temp, sizeof(uint8), 2, file_);
  fseek(file_, 0, SEEK_END);
}

TextDoc::TextDoc(const WString& file_name, const WString& file_mode) throw(Exception)
    : file_(NULL) {
  String s_file_name = String::FromUnicode(file_name);
  String s_file_mode = String::FromUnicode(file_mode);

#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, (const char*)s_file_name, (const char*)s_file_mode);
#else
  file_ = fopen((const char*)s_file_name, (const char*)s_file_mode);
#endif
  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);

  uint8 temp[] = { 0xFF, 0xFE };
  fwrite(temp, sizeof(uint8), 2, file_);
  fseek(file_, 0, SEEK_END);
}

TextDoc::~TextDoc() {
  fclose(file_);
  file_ = NULL;
}

void TextDoc::Write(const char* text_content) {
  WString wide_str = WString::FromLocal(text_content);
  Write(wide_str);
}

void TextDoc::Write(const wchar_t* text_content) {
  WString wide_str(text_content);
  if (wide_str.IsEmpty())
    return;
  String utf16le_str = wide_str.UTF16LE_Encode(false);
  if (utf16le_str.IsEmpty()) 
    return;
  int length = utf16le_str.GetLength();
  fwrite((const char*)utf16le_str, sizeof(char), length, file_);
}

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

void AddTextObjects(PDFPage page) {
  POSITION position = page.GetLastGraphicsObjectPosition(GraphicsObject::e_TypeText);
  TextObject* text_object = TextObject::Create();

  text_object->SetFillColor(0xFFFF7F00);

  // Prepare text state
  TextState state;
  state.font_size = 80.0f;
  state.font =  Font(L"Simsun", Font::e_StylesSmallCap, Font::e_CharsetGB2312, 0);
  state.textmode = TextState::e_ModeFill;
  text_object->SetTextState(page, state, false, 750);

  // Set text.
  text_object->SetText(L"Foxit Software");
  POSITION last_position = page.InsertGraphicsObject(position, text_object);

  RectF rect = text_object->GetRect();
  float offset_x = (page.GetWidth() - (rect.right - rect.left)) / 2;
  float offset_y = page.GetHeight() * 0.8f - (rect.top - rect.bottom) / 2;
  text_object->Transform(Matrix(1, 0, 0, 1, offset_x, offset_y), false);

  // Generate content
  page.GenerateContent();

  // Clone a text object from the old text object.
  text_object = reinterpret_cast<TextObject*>(text_object->Clone());

  state.font = Font(Font::e_StdIDTimes);
  state.font_size = 48;
  state.textmode = TextState::e_ModeFillStrokeClip;

  text_object->SetTextState(page, state, true, 750);
  text_object->SetText(L"www.foxitsoftware.com");

  text_object->SetFillColor(0xFFAAAAAA);
  text_object->SetStrokeColor(0xFFF68C21);
  page.InsertGraphicsObject(last_position, text_object);

  rect = text_object->GetRect();
  offset_x = (page.GetWidth() - (rect.right - rect.left)) / 2;
  offset_y = page.GetHeight() * 0.618f - (rect.top - rect.bottom) / 2;
  text_object->Transform(Matrix(1, 0, 0, 1, offset_x, offset_y), false);

  // Generate content again after transformation.
  page.GenerateContent();

  //Show how to get the characters' information of text object.
  int text_object_charcount = text_object->GetCharCount();
  TextDoc text_doc(output_path + L"graphics_objects/text_objects_info.txt", L"wb+");
  String strinfo;
  strinfo.Format("The new text object has %d characters.\n", text_object_charcount);
  text_doc.Write(strinfo);

  for (int i = 0; i < text_object_charcount; i++) {
	//The character's position.
    PointF char_pos = text_object->GetCharPos(i);
    //The character's width.
    float width = text_object->GetCharWidthByIndex(i);
    //The character's height.
    float height = text_object->GetCharHeightByIndex(i);

    String strinfo;
    strinfo.Format("The position of the %d characters is (%f, %f).The width and height of the characters is (%f, %f).\n", i, char_pos.x, char_pos.y, width, height);
    text_doc.Write(strinfo);
  }
}

void AddImageObjects(PDFPage page, WString image_file) {
  POSITION position = page.GetLastGraphicsObjectPosition(GraphicsObject::e_TypeImage);
  Image image(image_file);
  ImageObject* image_object = ImageObject::Create(page.GetDocument());
  image_object->SetImage(image, 0);

  float width = static_cast<float>(image.GetWidth());
  float height = static_cast<float>(image.GetHeight());

  float page_width = page.GetWidth();
  float page_height = page.GetHeight();

  // Please notice the matrix value.
  image_object->SetMatrix(Matrix(width, 0, 0, height, (page_width - width) / 2.0f, (page_height - height) / 2.0f));

  page.InsertGraphicsObject(position, image_object);
  page.GenerateContent();
}

void AddPieces(PDFPage page, ShadingObject* orignal_pieces, const RectF& dst_rect) {
  POSITION position = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeAll);
  ShadingObject* pieces = (ShadingObject*)orignal_pieces->Clone();

  RectF piece_rect = pieces->GetRect();

  // Calculates the transformation matrix between dst_rect and  piece_rect.
  float a = (dst_rect.right - dst_rect.left) / (piece_rect.right - piece_rect.left);
  float d = (dst_rect.top - dst_rect.bottom) / (piece_rect.top - piece_rect.bottom);
  float e = dst_rect.left - piece_rect.left * a;
  float f = dst_rect.top - piece_rect.top * d;

  // Transform rect.
  pieces->Transform(Matrix(a, 0, 0, d, e, f), false);
  page.InsertGraphicsObject(position, pieces);

  page.GenerateContent();
}

void AddPathObjects(PDFPage page, ShadingObject* black_pieces, ShadingObject* white_pieces) {
  POSITION position = page.GetLastGraphicsObjectPosition(GraphicsObject::e_TypePath);
  PathObject* path_object = PathObject::Create();
  Path path;
  float page_width = page.GetWidth();
  float page_height = page.GetHeight();

  float width = min(page_width, page_height) / 20.0f;
  float start_x = (page_width - width * 18.0f) / 2.0f;
  float start_y = (page_height - width * 18.0f) / 2.0f;

  // Draw a chess board
  for (int i = 0; i < 19; i++) {
    float x1 = start_x;
    float y1 = i * width + start_y;

    float x2 = start_x + 18 * width;
    path.MoveTo(PointF(x1, y1));
    path.LineTo(PointF(x2, y1));

    x1 = i * width + start_x;
    y1 = start_y;

    float y2 = 18 * width + start_y;
    path.MoveTo(PointF(x1, y1));
    path.LineTo(PointF(x1, y2));
  }

  int star[3] = {3, 9, 15};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      RectF rect(start_x + star[i] * width - width / 12, start_y + star[j] * width - width / 12,
        start_x + star[i] * width + width / 12, start_y + star[j] * width + width / 12);
      path.AppendEllipse(rect);
    }
  }
  path_object->SetPathData(path);

  path_object->SetFillColor(0xFF000000);
  path_object->SetFillMode(e_FillModeAlternate);
  path_object->SetStrokeState(true);
  path_object->SetStrokeColor(0xFF000000);

  page.InsertGraphicsObject(position, path_object);
  page.GenerateContent();

  // Draw pieces
  PointF pieces_vector[2][8] = {{PointF(3, 3),   PointF(3, 7),   PointF(3, 15),  PointF(13, 2),
    PointF(13, 16), PointF(13, 17), PointF(15, 16), PointF(16, 16)},
  {PointF(11, 16), PointF(12, 14), PointF(14, 4),  PointF(14, 15),
  PointF(15, 3),  PointF(15, 9),  PointF(15, 15), PointF(16, 15)}};
  for (int k = 0; k < 2; k++) {
    for (int i = 0; i < sizeof(pieces_vector[k]) / sizeof(pieces_vector[k][0]); i++) {
      int x = static_cast<int>(pieces_vector[k][i].x);
      int y = static_cast<int>(pieces_vector[k][i].y);
      AddPieces(page, k % 2 ? white_pieces : black_pieces,
        RectF(start_x + x * width - width / 2.f, start_y + y * width - width / 2.f,
        start_x + x * width + width / 2.f, start_y + y * width + width / 2.f));
    }
  }
}

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"graphics_objects/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"graphics_objects.pdf";
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

    // Get original shading objects from PDF page.
    PDFPage original_page = doc.GetPage(0);
    original_page.StartParse(PDFPage::e_ParsePageNormal, NULL, false);
    POSITION position = original_page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeShading);
    if(!position)
      return 1;
    ShadingObject* black_pieces = (ShadingObject*)original_page.GetGraphicsObject(position);
    position = original_page.GetNextGraphicsObjectPosition(position, GraphicsObject::e_TypeShading);
    ShadingObject* white_pieces = (ShadingObject*)original_page.GetGraphicsObject(position);

    // Add a new PDF page and insert text objects.
    PDFPage page = doc.InsertPage(0);
    AddTextObjects(page);

    // Add a new PDF page and insert image objects.
    page = doc.InsertPage(1);
    WString image_file = input_path + L"sdk.png";
    AddImageObjects(page, image_file);

    // Add a new PDF page and insert path objects, and copy shading objects.
    page = doc.InsertPage(2);
    AddPathObjects(page, black_pieces, white_pieces);

    WString output_file = output_directory + L"graphics_objects.pdf";
    doc.SaveAs(output_file, PDFDoc::e_SaveFlagNormal);
    cout << "Add graphics objects to PDF file." << endl;

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
