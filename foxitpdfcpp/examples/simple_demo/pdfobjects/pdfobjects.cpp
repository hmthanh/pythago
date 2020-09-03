// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to operate PDF objects directly.

// Include header files.
#include <iostream>
// Include  Foxit SDK header files.
#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/objects/fs_pdfobject.h"
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace objects;

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

#if (defined(__linux__) && defined(__x86_64__)) || defined(__APPLE__) || defined(_WIN64)
#define FORMAT_UINT32 "%u"
#else
#define FORMAT_UINT32 "%lu"
#endif

// This function is to do some operation to PDF object.
void ObjectOperation(PDFDoc document) {
  PDFObject* boolean_object = PDFObject::CreateFromBoolean(true);
  uint32 boolean_object_number= document.AddIndirectObject(boolean_object);

  printf("Object number of new boolean object: " FORMAT_UINT32 "\r\n", boolean_object_number);

  bool boolean_object_value = boolean_object->GetBoolean();
  printf("\tValue of new boolean object: %s\r\n", boolean_object_value?"true":"false");

  PDFObject* float_object = PDFObject::CreateFromFloat(0.1f);
  uint32 float_object_number= document.AddIndirectObject(float_object);
  printf("Object number of new number object (as float): " FORMAT_UINT32 "\r\n", float_object_number);
  float float_object_value = float_object->GetFloat();
  printf("\tValue of new number object (as float): %f\r\n", float_object_value);

  PDFObject* integer_object = PDFObject::CreateFromInteger(1);
  uint32 integer_object_number= document.AddIndirectObject(integer_object);
  printf("Object number of new number object (as integer):" FORMAT_UINT32 "\r\n", integer_object_number);
  int integer_object_value = integer_object->GetInteger();
  printf("\tValue of new number object (as integer): %d\r\n", integer_object_value);

  PDFObject* string_object = PDFObject::CreateFromString(L"foxit");
  uint32 string_object_number= document.AddIndirectObject(string_object);
  printf("Object number of new string object:" FORMAT_UINT32 "\r\n", string_object_number);
  WString string_object_value = string_object->GetWideString();
  wprintf(L"\tValue of new string object: %ls\r\n", (const wchar_t*)string_object_value);

  PDFObject* name_object = PDFObject::CreateFromName("sdk");
  uint32 name_object_number= document.AddIndirectObject(name_object);
  printf("Object number of new name object:" FORMAT_UINT32 "\r\n", name_object_number);
  String name_object_value = name_object->GetName();
  printf("\tValue of new name object: %s\r\n", (const char*)name_object_value);

  DateTime date_time(2017, 9, 27, 19, 36, 6, 0, 8, 0);
  PDFObject* datetime_object = PDFObject::CreateFromDateTime(date_time);
  uint32 datetime_object_number= document.AddIndirectObject(datetime_object);
  printf("Object number of new string object (as date-time): " FORMAT_UINT32 "\r\n", datetime_object_number);
  WString datetime_object_value = datetime_object->GetWideString();
  wprintf(L"\tValue of new string object (as date-time): %ls\r\n", (const wchar_t*)datetime_object_value);

  PDFArray* array = PDFArray::Create();
  PDFObject* boolean_object_reference = PDFObject::CreateReference(document, boolean_object_number);
  uint32 boolean_object_reference_number = boolean_object_reference->GetObjNum();
  printf("Object number of a new reference object to a boolean object:" FORMAT_UINT32 "\r\n", boolean_object_reference_number);
  PDFObject* float_object_reference = PDFObject::CreateReference(document, float_object_number);
  PDFObject* integer_object_reference = PDFObject::CreateReference(document, integer_object_number);
  PDFObject* integer_object_direct = integer_object_reference->GetDirectObject();
  printf("Object number of the direct number object: " FORMAT_UINT32 "\r\n", integer_object_direct->GetObjNum());
  PDFObject* string_object_reference = PDFObject::CreateReference(document, string_object_number);
  PDFObject* name_object_reference = PDFObject::CreateReference(document, name_object_number);
  PDFObject* datetime_object_reference = PDFObject::CreateReference(document, datetime_object_number);

  array->AddElement(boolean_object_reference);
  array->AddElement(float_object_reference);
  array->AddElement(integer_object_reference);
  array->AddElement(string_object_reference);
  array->AddElement(name_object_reference);
  array->AddElement(datetime_object_reference);
  array->AddElement(boolean_object->CloneObject());

  uint32 array_object_number = document.AddIndirectObject(array);
  printf("Object number of array object: " FORMAT_UINT32 "\r\n", array_object_number);
}

// This function is to remove some properties from catalog dictionary.
void RemoveCatalogKey(PDFDoc document) {
  if (document.IsEmpty()) return;

  PDFDictionary* catalog = document.GetCatalog();
  if (NULL == catalog) return;

  const char* key_strings[] = { "Type", "Boolean", "Name", "String", "Array", "Dict"};
  int count = sizeof(key_strings)/sizeof(key_strings[0]);
  for (int i = 0; i < count; i ++) {
    if (catalog->HasKey(key_strings[i]))
      catalog->RemoveAt(key_strings[i]);
  }
}

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"pdfobjects/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"pdfobjects.pdf";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    PDFDoc doc(input_file);
    doc.StartLoad(NULL, false, NULL);

    // Do some operation about PDF object.
    ObjectOperation(doc);
    WString save_pdf_patth = output_directory + L"pdfobjects_addnewobjects.pdf";
    doc.StartSaveAs((const wchar_t*)save_pdf_patth, PDFDoc::e_SaveFlagNoOriginal, NULL);

    // To remove some properties from catalog dictionary.
    RemoveCatalogKey(doc);
    save_pdf_patth = output_directory + L"pdfobjects_removekeyfromcatalog.pdf";
    doc.StartSaveAs((const wchar_t*)save_pdf_patth, PDFDoc::e_SaveFlagNoOriginal, NULL);

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

