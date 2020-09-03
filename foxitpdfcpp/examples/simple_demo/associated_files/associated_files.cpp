
// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to associate files with PDF.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#include <map>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_filespec.h"
#include "../../../include/pdf/fs_pdfassociatefiles.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace pdf::graphics;
using namespace pdf::objects;
using namespace annots;

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
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  WString output_directory = output_path + L"associated_files/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  // Get information about associated files from PDF document.
  WString input_file = input_path + L"AF_Catalog_Page_Annot.pdf";
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }

    AssociatedFiles associated_files(doc);
    
    PDFDictionary* doc_catalog_dict = doc.GetCatalog();
    int count = associated_files.GetAssociatedFilesCount(doc_catalog_dict);
    printf("The catalog dictionary of \"AF_Catalog_Page_Annot.pdf\" has %d associated files.\n", count);
    FileSpec filespec = associated_files.GetAssociatedFile(doc_catalog_dict, 0);
    printf("The file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"af_1.txt");

    PDFPage page = doc.GetPage(0);
    PDFDictionary* page_dict = page.GetDict();
    count = associated_files.GetAssociatedFilesCount(page_dict);
    printf("The page dictionary of \"AF_Catalog_Page_Annot.pdf\" has %d associated files.\n", count);
    filespec = associated_files.GetAssociatedFile(page_dict, 0);
    printf("The file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"af_2.txt");

    Annot annot = page.GetAnnot(0);
    PDFDictionary* annot_dict = annot.GetDict();
    count = associated_files.GetAssociatedFilesCount(annot_dict);
    printf("The annot dictionary of \"AF_Catalog_Page_Annot.pdf\" has %d associated files.\n", count);
    filespec = associated_files.GetAssociatedFile(annot_dict, 0);
    printf("The file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"af_4.txt");
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }
  catch(...) {
    cout << "Unknown Exception" << endl;
     err_ret = 1;
  }

  input_file = input_path + L"AF_ImageXObject_FormXObject.pdf";
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }

    AssociatedFiles associated_files(doc);

    PDFPage page = doc.GetPage(0);
    page.StartParse(PDFPage::e_ParsePageNormal, NULL, false);
    
    POSITION pos = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeImage);
    GraphicsObject* image_x_object = page.GetGraphicsObject(pos);
    PDFDictionary* image_x_object_dict = ((ImageObject*)image_x_object)->GetStream()->GetDictionary();
    int count = associated_files.GetAssociatedFilesCount(image_x_object_dict);
    printf("The image x object of \"AF_ImageXObject_FormXObject.pdf\" has %d associated files.\n", count);
    FileSpec filespec = associated_files.GetAssociatedFile(image_x_object_dict, 0);
    printf("The file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"af_5.txt");

    pos = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeFormXObject);
    GraphicsObject* form_x_object = page.GetGraphicsObject(pos);
    PDFDictionary* form_x_object_dict = ((FormXObject*)form_x_object)->GetStream()->GetDictionary();
    count = associated_files.GetAssociatedFilesCount(form_x_object_dict);
    printf("The form x object of \"AF_ImageXObject_FormXObject.pdf\" has %d associated files.\n", count);
    filespec = associated_files.GetAssociatedFile(form_x_object_dict, 0);
    printf("The file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"af_6.txt");
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
   err_ret = 1;
  }
  catch(...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  input_file = input_path + L"AF_MarkedContent.pdf";
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }

    AssociatedFiles associated_files(doc);

    PDFPage page = doc.GetPage(0);
    page.StartParse(PDFPage::e_ParsePageNormal, NULL, false);

    POSITION pos = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeText);
    GraphicsObject* text_object = page.GetGraphicsObject(pos);
    int count = associated_files.GetAssociatedFilesCount(text_object);
    printf("The text object of \"AF_MarkedContent.pdf\" has %d associated files.\n", count);
    FileSpec filespec = associated_files.GetAssociatedFile(text_object, 0);
    printf("The first file name is \"%s\".\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"bitmap.bmp");

    filespec = associated_files.GetAssociatedFile(text_object, 1);
    printf("The second file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"text.txt");
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }
  catch(...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  // Associate files with objects in PDF document.
  input_file = input_path + L"AssociateTestFile.pdf";
  try{
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }

    AssociatedFiles associated_files(doc);

    //Create filespec with 1.txt
    FileSpec filespec_txt(doc);
    filespec_txt.SetAssociteFileRelationship(AssociatedFiles::e_RelationshipSource);
    filespec_txt.SetFileName(L"1.txt");
    DateTime dateTime(2017, 9, 15, 17, 20, 20, 0, 8, 0);
    filespec_txt.SetDescription("text");
    filespec_txt.Embed(input_path +  L"1.txt");
    filespec_txt.SetCreationDateTime(dateTime);
    filespec_txt.SetModifiedDateTime(dateTime);
    filespec_txt.SetSubtype();

    //Associate 1.txt with catalog dictionary.
    {
      PDFObject* catalog_dict = doc.GetCatalog();
      associated_files.AssociateFile(catalog_dict, filespec_txt);
      printf("Associate a text file with catalog dictionary.\n");
      FileSpec filespec_catalog = associated_files.GetAssociatedFile(catalog_dict, 0);
      filespec_catalog.ExportToFile(output_directory + L"catalog.txt");
    }

    PDFPage page = doc.GetPage(0);
    page.StartParse();

    //Associate 1.txt with page dictionary.
    {
      associated_files.AssociateFile(page, filespec_txt);
      printf("Associate a text file with page.\n");

      FileSpec filespec_page = associated_files.GetAssociatedFile(page.GetDict(), 0);
      filespec_page.ExportToFile(output_directory + L"page.txt");
    }

    //Associate 1.txt with annotation dictionary.
    {
      RectF rect(100, 50, 220, 100);
      Annot annot = page.AddAnnot(Annot::e_Note, rect);
      annot.ResetAppearanceStream();
      associated_files.AssociateFile(annot, filespec_txt);
      printf("Associate a text file with annotation.\n");
      FileSpec filespec_annot = associated_files.GetAssociatedFile(annot.GetDict(), 0);
      filespec_annot.ExportToFile(output_directory + L"annotation.txt");
    }

    //Create filespec with 2.jpg image.
    FileSpec filespec_jpg(doc);
    filespec_jpg.SetAssociteFileRelationship(AssociatedFiles::e_RelationshipSource);
    filespec_jpg.SetFileName(L"2.jpg");
    filespec_jpg.SetDescription("jpeg");
    filespec_jpg.Embed(input_path +  L"2.jpg");
    filespec_jpg.SetCreationDateTime(dateTime);
    filespec_jpg.SetModifiedDateTime(dateTime);
    filespec_jpg.SetSubtype();

    //Associate 2.jpg with marked content.
    {
      PDFDictionary* page_dict = page.GetDict();
      PDFDictionary* resource_dict = (PDFDictionary*)page_dict->GetElement("Resources");
      if (!resource_dict) return 1;

      POSITION position = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeText);
      GraphicsObject* text_object = page.GetGraphicsObject(position);
      if (text_object) {
        MarkedContent* markcontent = text_object->GetMarkedContent();
        if (!markcontent) return 1;

        if (markcontent->GetItemCount() == 0) {
          markcontent->AddItem("Associated");
        }
        associated_files.AssociateFile(text_object, 0, resource_dict, "textobject", filespec_jpg);
        page.GenerateContent();

        printf("Associate a jpeg file with markcontent.\n");

        FileSpec filespec_text_object = associated_files.GetAssociatedFile(text_object, 0);
        filespec_text_object.ExportToFile(output_directory + L"textobject.jpg");
      }
    }

    //Associate 2.jpg with image object.
    {
      POSITION position = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeImage);
      ImageObject* image_oject = (ImageObject*)page.GetGraphicsObject(position);
      if (image_oject) {
        associated_files.AssociateFile(image_oject, filespec_jpg);
        printf("Associate a jpeg file with image xobject.\n");

        FileSpec filespec_image_oject = associated_files.GetAssociatedFile(image_oject->GetStream()->GetDictionary(), 0);
        filespec_image_oject.ExportToFile(output_directory + L"image_x_object.jpg");
      }
    }

    //Associate 2.jpg with form XObject.
    {
      POSITION position = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeFormXObject);
      FormXObject* form_x_object = (FormXObject*)page.GetGraphicsObject(position);
      if (form_x_object) {
        associated_files.AssociateFile(form_x_object, filespec_jpg);
        printf("Associate a jpeg file with form xobject.\n");

        FileSpec filespec_form_x_object = associated_files.GetAssociatedFile(form_x_object->GetStream()->GetDictionary(), 0);
        filespec_form_x_object.ExportToFile(output_directory + L"form_x_object.jpg");
      }
    }

    // Save PDF file
    WString newPdf = output_directory + L"associated_files.pdf";
    doc.SaveAs(newPdf, PDFDoc::e_SaveFlagNoOriginal);
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
