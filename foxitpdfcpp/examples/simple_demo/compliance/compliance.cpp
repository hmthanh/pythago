// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to verify if a PDF file is PDFA-1a version
// or convert a PDF file to PDFA-1a version.

#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/addon/compliance/fs_compliancecommon.h"
#include "../../../include/addon/compliance/fs_pdfa.h"
#include "../../../include/addon/compliance/fs_pdfcompliance.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace addon;
using namespace compliance;

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

class TextDoc {
public:
  TextDoc(const String& file_name, const String& fill_mode);
  TextDoc(const WString& file_name, const WString& fill_mode);
  ~TextDoc();

  void Write(const char* text_content);
  void Write(const wchar_t* text_content);

private:
  FILE* file_;
};

TextDoc::TextDoc(const String& file_name, const String& file_mode) throw(Exception) : file_(NULL) {
#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, file_name, (const char*)file_mode);
#else
  file_ = fopen((const char*)file_name, (const char*)file_mode);
#endif

  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);

  uint8 temp[] = {0xFF,0xFE};
  fwrite(temp, sizeof(uint8), 2, file_);
  fseek(file_, 0, SEEK_END);

}

TextDoc::TextDoc(const WString& file_name, const WString& file_mode) throw(Exception)  : file_(NULL) {
  String s_file_name = String::FromUnicode(file_name);
  String s_file_mode = String::FromUnicode(file_mode);

#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, (const char*)s_file_name, (const char*)s_file_mode);
#else
  file_ = fopen((const char*)s_file_name, (const char*)s_file_mode);
#endif
  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);

  uint8 temp[] = {0xFF,0xFE};
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
  if (wide_str.IsEmpty()) return ;
  String utf16le_str = wide_str.UTF16LE_Encode(false);
  if (utf16le_str.IsEmpty()) return;
  int length = utf16le_str.GetLength();
  fwrite((const char*)utf16le_str, sizeof(char), length, file_);
}


void OutputPDFAFixupData(ResultInformation result_info, const WString& output_txt_path) {
  TextDoc text_doc(output_txt_path, L"w+b");

  int fixup_count = result_info.GetFixupDataCount();
  char temp_string[128];
#if defined(_WIN32) || defined(_WIN64)
  sprintf_s(temp_string, 128, "== Fixup Data, count:%d ==\r\n", fixup_count);
#else
  sprintf(temp_string, "== Fixup Data, count:%d ==\r\n", fixup_count);
#endif  //defined(_WIN32) || defined(_WIN64)
  text_doc.Write(temp_string);
  for (int i = 0; i<fixup_count; i++) {
    FixupData fixup_data = result_info.GetFixupData(i);
#if defined(_WIN32) || defined(_WIN64)
    sprintf_s(temp_string, 128, "Used count:%d\r\n", fixup_data.used_count);
#else
    sprintf(temp_string, "Used count:%d\r\n", fixup_data.used_count);
#endif  // defined(_WIN32) || defined(_WIN64)
    text_doc.Write(temp_string);

    text_doc.Write("Name:");
    text_doc.Write(fixup_data.name);
    text_doc.Write("\r\n");

    text_doc.Write("Comment:");
    text_doc.Write(fixup_data.comment);
    text_doc.Write("\r\n");

    text_doc.Write("Reason:");
    int reason_count = fixup_data.reasons.GetSize();
    if (reason_count < 1) {
      text_doc.Write("\r\n");
    } else {
      for (int z = 0; z<reason_count; z++) {
        text_doc.Write("\t");
        text_doc.Write(fixup_data.reasons[z]);
        text_doc.Write("\r\n");
      }
    }

#if defined(_WIN32) || defined(_WIN64)
    sprintf_s(temp_string, 128, "State value:%d\r\n", fixup_data.state);
#else
    sprintf(temp_string, "State value:%d\r\n", fixup_data.state);
#endif  // defined(_WIN32) || defined(_WIN64)
    text_doc.Write(temp_string);

    text_doc.Write("\r\n");
  }
}

void OutputPDFAHitData(ResultInformation result_info, const WString& output_txt_path) {
  TextDoc text_doc(output_txt_path, L"w+b");

  int hit_data_count = result_info.GetHitDataCount();
  char temp_string[128];
#if defined(_WIN32) || defined(_WIN64)
  sprintf_s(temp_string, 128, "== Hit Data, count:%d ==\r\n", hit_data_count);
#else
  sprintf(temp_string, "== Hit Data, count:%d ==\r\n", hit_data_count);
#endif  // defined(_WIN32) || defined(_WIN64)
  text_doc.Write(temp_string);
  for (int i = 0; i<hit_data_count; i++) {
    HitData hit_data = result_info.GetHitData(i);
#if defined(_WIN32) || defined(_WIN64)
    sprintf_s(temp_string, 128, "Triggered count:%d\r\n", hit_data.triggered_count);
#else
    sprintf(temp_string, "Triggered count:%d\r\n", hit_data.triggered_count);
#endif  // defined(_WIN32) || defined(_WIN64)
    text_doc.Write(temp_string);

    text_doc.Write("Name:");
    text_doc.Write(hit_data.name);
    text_doc.Write("\r\n");

    text_doc.Write("Comment:");
    text_doc.Write(hit_data.comment);
    text_doc.Write("\r\n");

    text_doc.Write("Trigger value:");
    int trigger_value_count = hit_data.trigger_values.GetSize();
    if (trigger_value_count < 1) {
      text_doc.Write("\r\n");
    } else {
      for (int z = 0; z<trigger_value_count; z++) {
        text_doc.Write("\t");
        text_doc.Write(hit_data.trigger_values[z]);
        text_doc.Write("\r\n");
      }
    }

#if defined(_WIN32) || defined(_WIN64)
    sprintf_s(temp_string, 128, "Check severity:%d\r\nPage index:%d\r\n", hit_data.severity, hit_data.page_index);
#else
    sprintf(temp_string, "Check severity:%d\r\nPage index:%d\r\n", hit_data.severity, hit_data.page_index);
#endif  // defined(_WIN32) || defined(_WIN64)
    text_doc.Write(temp_string);

    text_doc.Write("\r\n");
  }
}


class MyComplianceProgressCallback : public ProgressCallback {
public:
  MyComplianceProgressCallback(const WString& output_txt_file_path);
  ~MyComplianceProgressCallback();

  virtual void Release();
  virtual void UpdateCurrentStateData(int current_rate, const WString& current_state_string);

private:
  TextDoc text_doc_;
};

MyComplianceProgressCallback::MyComplianceProgressCallback(const WString& output_txt_file_path)
  : text_doc_(output_txt_file_path, L"w+b") {}

MyComplianceProgressCallback::~MyComplianceProgressCallback() {}

void MyComplianceProgressCallback::Release() {

}

void MyComplianceProgressCallback::UpdateCurrentStateData(int current_rate, const WString& current_state_string) {
  std::cout << "Current rate:" << current_rate << std::endl;

  char temp_string[32];
#if defined(_WIN32) || defined(_WIN64)
  sprintf_s(temp_string, 32, "Current rate:%d, state str:", current_rate);
#else
  sprintf(temp_string, "Current rate:%d, state str:", current_rate);
#endif  // defined(_WIN32) || defined(_WIN64)
  text_doc_.Write(temp_string);
  text_doc_.Write(current_state_string);
  text_doc_.Write("\r\n");
}

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"compliance/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"AboutFoxit.pdf";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    // "compliance_resource_folder_path" is the path of compliance resource folder. Please refer to Developer Guide for more details.
    WString compliance_resource_folder_path = L"";
    // If you use an authorization key for Foxit PDF SDK, please set a valid unlock code string to compliance_engine_unlockcode for ComplianceEngine.
    // If you use an trial key for Foxit PDF SDK, just keep compliance_engine_unlockcode as an empty string.
    const char* compliance_engine_unlockcode = "";

    if (compliance_resource_folder_path.IsEmpty()) {
      std::cout << "compliance_resource_folder_path is still empty. Please set it with a valid path to compliance resource folder path." << std::endl;
      return 1;
    }
    // Initialize compliance engine.
    ErrorCode error_code = ComplianceEngine::Initialize(compliance_resource_folder_path, compliance_engine_unlockcode);
    if (error_code != foxit::e_ErrSuccess) {
      switch (error_code) {
      case foxit::e_ErrInvalidLicense:
        printf("[Failed] Compliance module is not contained in current Foxit PDF SDK keys.\n");
        break;
      default:
        printf("[Failed] Fail to initialize compliance engine. Error: %d\n", error_code);
        break;
      }
      return 1;
    }
    cout << "ComplianceEngine is initialized." << endl;

    // Set custom temp folder path for ComplianceEngine. 
    //ComplianceEngine::SetTempFolderPath(L"");
    // Set languages. If not set language to ComplianceEngine, "English" will be used as default.
    //ComplianceEngine::SetLanguage("Chinese-Simplified");

    PDFACompliance pdfa_compliance;
    {
      // Verify original PDF file.
      cout << "======== PDFACompliance: Verify before convert ========" << std::endl;
      MyComplianceProgressCallback verify_progress_callback(output_directory + L"0_pdfacompliance_verify_before_convert_progressdata.txt");
      ResultInformation verify_result_info = pdfa_compliance.Verify(PDFACompliance::e_VersionPDFA1a, input_file, 0, -1, &verify_progress_callback);
      OutputPDFAHitData(verify_result_info, output_directory + L"0_pdfacompliance_verify_before_convert_hitdata.txt");
    }

    WString save_pdf_path = output_directory + L"1_pdfacompliance_convert_to_pdf1a.pdf";
    {
      // Convert original PDF file to PDFA-1a version.
      cout << "======== PDFACompliance: Convert ========" << std::endl;
      MyComplianceProgressCallback convert_progress_callback(output_directory + L"1_1_pdfacompliance_convert_progressdata.txt");
      ResultInformation convert_result_info = pdfa_compliance.ConvertPDFFile(input_file, save_pdf_path,
        PDFACompliance::e_VersionPDFA1a, &convert_progress_callback);
      OutputPDFAFixupData(convert_result_info, output_directory + L"1_1_pdfacompliance_convert_pdfa1a_fixupdata.txt");
      OutputPDFAHitData(convert_result_info, output_directory + L"1_1_pdfacompliance_convert_pdfa1a_hitdata.txt");
    }

    {
      // Verify converted result PDF file, which is expected to be PDFA-1a version.
      cout << "======== PDFACompliance: Verify after convert ========" << std::endl;
      MyComplianceProgressCallback verify_progress_callback_2(output_directory + L"1_2_pdfacompliance_verify_after_convert_progressdata.txt");
      ResultInformation verify_result_info_2 = pdfa_compliance.Verify(PDFACompliance::e_VersionPDFA1a, save_pdf_path, 0, -1, &verify_progress_callback_2);
      OutputPDFAHitData(verify_result_info_2, output_directory + L"1_2_pdfacompliance_verify_after_convert_hitdata.txt");
    }

    PDFCompliance pdf_compliance;
    input_file = input_path + L"AF_ImageXObject_FormXObject.pdf";
    {
      // Convert original PDF file to PDF-1.4.
      cout << "======== PDFCompliance: Convert ========" << std::endl;
      MyComplianceProgressCallback convert_progress_callback(output_directory + L"2_pdfcompliance_convert_1_4_progressdata.txt");
      save_pdf_path = output_directory + L"2_pdfcompliance_convert_to_1_4.pdf";
      ResultInformation convert_result_info = pdf_compliance.ConvertPDFFile(input_file, save_pdf_path, 14, &convert_progress_callback);
      OutputPDFAFixupData(convert_result_info, output_directory + L"2_pdfcompliance_convert_1_4_fixupdata.txt");
      OutputPDFAHitData(convert_result_info, output_directory + L"2_pdfcompliance_convert_1_4_hitdata.txt");
    }
    {
      // Convert original PDF file to PDF-1.7.
      cout << "======== PDFCompliance: Convert ========" << std::endl;
      MyComplianceProgressCallback convert_progress_callback(output_directory + L"3_pdfcompliance_convert_1_7_progressdata.txt");
      save_pdf_path = output_directory + L"3_pdfcompliance_convert_to_1_7.pdf";
      ResultInformation convert_result_info = pdf_compliance.ConvertPDFFile(input_file, save_pdf_path, 17, &convert_progress_callback);
      OutputPDFAFixupData(convert_result_info, output_directory + L"3_pdfcompliance_convert_1_7_fixupdata.txt");
      OutputPDFAHitData(convert_result_info, output_directory + L"3_pdfcompliance_convert_1_7_hitdata.txt");
    }
    // Release compliance engine.
    ComplianceEngine::Release();

    cout << "== End: Compliance demo. ==" << endl;

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

