// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to add, sign, verify and get PAdES level of
// a PAdES signature in PDF document.

// Include header files.
#include <iostream>
#include <time.h>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

// Include Foxit SDK header files.
#include "../../../include/pdf/annots/fs_annot.h"
#include "../../../include/common/fs_image.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/fs_signature.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace objects;
using namespace file;


// sn and key information from Foxit PDF SDK's key files are used to initialize Foxit PDF SDK library. 
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

WString output_directory = output_path + L"pades/";

#define TIMESTAMP_SIGNATURE_FILTER "Adobe.PPKLite"
#define TIMESTAMP_SIGNATURE_SUBFILTER "ETSI.RFC3161"
#define FREE_ETSIRFC316TSA_SERVER_NAME L"FreeTSAServer"
#define FREE_ETSIRFC316TSA_SERVER_URL L"http://ca.signfiles.com/TSAServer.aspx"

#define ETSICADES_SIGNATURE_FILTER "Adobe.PPKLite"
#define ETSICADES_SIGNATURE_SUBFILTER "ETSI.CAdES.detached"


#if !defined(WIN32) && !defined(_WIN64)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

string TransformSignatureStateToString(uint32 sig_state) {
  string state_str;
  if (sig_state & Signature::e_TypeUnknown)
    state_str += "Unknown";
  if (sig_state & Signature::e_StateNoSignData) {
    if (state_str.length()>0) state_str += "|";
    state_str += "NoSignData";
  }
  if (sig_state & Signature::e_StateUnsigned) {
    if (state_str.length()>0) state_str += "|";
    state_str += "Unsigned";
  }
  if (sig_state & Signature::e_StateSigned) {
    if (state_str.length()>0) state_str += "|";
    state_str += "Signed";
  }
  if (sig_state & Signature::e_StateVerifyValid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerfiyValid";
  }
  if (sig_state & Signature::e_StateVerifyInvalid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyInvalid";
  }
  if (sig_state & Signature::e_StateVerifyErrorData) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyErrorData";
  }
  if (sig_state & Signature::e_StateVerifyNoSupportWay) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyNoSupportWay";
  }
  if (sig_state & Signature::e_StateVerifyErrorByteRange) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyErrorByteRange";
  }
  if (sig_state & Signature::e_StateVerifyChange) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyChange";
  }
  if (sig_state & Signature::e_StateVerifyIncredible) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIncredible";
  }
  if (sig_state & Signature::e_StateVerifyNoChange) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyNoChange";
  }
  if (sig_state & Signature::e_StateVerifyIssueValid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueValid";
  }
  if (sig_state & Signature::e_StateVerifyIssueUnknown) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueUnknown";
  }
  if (sig_state & Signature::e_StateVerifyIssueRevoke) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueRevoke";
  }
  if (sig_state & Signature::e_StateVerifyIssueExpire) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueExpire";
  }
  if (sig_state & Signature::e_StateVerifyIssueUncheck) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueUncheck";
  }
  if (sig_state & Signature::e_StateVerifyIssueCurrent) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueCurrent";
  }
  if (sig_state & Signature::e_StateVerifyTimestampNone) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampNone";
  }
  if (sig_state & Signature::e_StateVerifyTimestampDoc) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampDoc";
  }
  if (sig_state & Signature::e_StateVerifyTimestampValid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampValid";
  }
  if (sig_state & Signature::e_StateVerifyTimestampInvalid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampInvalid";
  }
  if (sig_state & Signature::e_StateVerifyTimestampExpire) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampExpire";
  }
  if (sig_state & Signature::e_StateVerifyTimestampIssueUnknown) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampIssueUnknown";
  }
  if (sig_state & Signature::e_StateVerifyTimestampIssueValid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampIssueValid";
  }
  if (sig_state & Signature::e_StateVerifyTimestampTimeBefore) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampTimeBefore";
  }
  if (sig_state & Signature::e_StateCertCannotGetVRI) {
    if (state_str.length()>0) state_str += "|";
    state_str += "CertCannotGetVRI";
  }
  return state_str;
}

WString GenerateNewPDFFileName(const WString& org_file_name, const wchar_t* suffix_name) {
  FX_STRSIZE org_length = org_file_name.GetLength();
  WString first_part = org_file_name.Left(org_length - 4);
  WString new_file_path = first_part + suffix_name + L".pdf";
  return new_file_path;}

DateTime GetLocalDateTime() {
  time_t t = time(NULL);
#if (WINAPI_PARTITION_APP || WINAPI_PARTITION_PC_APP) || \
  (defined(_WIN32) || defined(_WIN64)) && _MSC_VER != 1200
  struct tm _Tm;
  localtime_s(&_Tm, &t);
  struct tm* system_time = &_Tm;
  _tzset();
  long time_zone = NULL;
  _get_timezone(&time_zone);
  int timezone_hour = time_zone / 3600 * -1;
  int timezone_minute = (abs(time_zone) % 3600) / 60;
#elif defined(__linux__)
  struct tm* system_time = localtime(&t);
  tzset();
  int timezone_hour = __timezone / 3600 * -1;
  int timezone_minute = ((int)abs(__timezone) % 3600) / 60;
#elif defined(__APPLE__)
  struct tm* system_time = localtime(&t);
  tzset();
  int timezone_hour = timezone / 3600 * -1;
  int timezone_minute = ((int)abs(timezone) % 3600) / 60;
#endif
  DateTime datetime;
  datetime.year = static_cast<uint16>(system_time->tm_year + 1900);
  datetime.month = static_cast<uint16>(system_time->tm_mon + 1);
  datetime.day = static_cast<uint16>(system_time->tm_mday);
  datetime.hour = static_cast<uint16>(system_time->tm_hour);
  datetime.minute = static_cast<uint16>(system_time->tm_min);
  datetime.second = static_cast<uint16>(system_time->tm_sec);
  datetime.utc_hour_offset = timezone_hour;
  datetime.utc_minute_offset = timezone_minute;

  return datetime;
}

const wchar_t* TransformLevel2WideString(Signature::PAdESLevel level) {
  switch (level) {
    case Signature::e_PAdESLevelNotPAdES:
      return L"NotPades";
    case Signature::e_PAdESLevelNone:
      return L"NoneLevel";
    case Signature::e_PAdESLevelBB:
      return L"LevelB";
    case Signature::e_PAdESLevelBT:
      return L"LevelT";
    case Signature::e_PAdESLevelBLT:
      return L"LevelLT";
    case Signature::e_PAdESLevelBLTA:
      return L"LevelLTA";
    default:
      return L"Unknown level value";
  }
}

const char* TransformLevel2String(Signature::PAdESLevel level) {
  switch (level) {
    case Signature::e_PAdESLevelNotPAdES:
      return "NotPades";
    case Signature::e_PAdESLevelNone:
      return "NoneLeve";
    case Signature::e_PAdESLevelBB:
      return "LevelB";
    case Signature::e_PAdESLevelBT:
      return "LevelT";
    case Signature::e_PAdESLevelBLT:
      return "LevelLT";
    case Signature::e_PAdESLevelBLTA:
      return "LevelLTA";
    default:
      return "Unknown level value";
  }
}

void PAdESSign(const WString& input_pdf_path, const WString& signed_pdf_path, Signature::PAdESLevel pades_level) {
  printf("To add a PAdES signature in %s\r\n", TransformLevel2String(pades_level));
  WString cached_signed_pdf_path = signed_pdf_path;
  WString real_signed_pdf_path = signed_pdf_path;
  if (pades_level > Signature::e_PAdESLevelBT) {
    cached_signed_pdf_path = signed_pdf_path.Left(signed_pdf_path.GetLength() - 4) + L"_cache.pdf";
  }

  PDFDoc pdf_doc(input_pdf_path);
  pdf_doc.StartLoad();
  PDFPage pdf_page = pdf_doc.GetPage(0);
  float page_width = pdf_page.GetWidth();
  float page_height = pdf_page.GetHeight();
  RectF new_sig_rect((page_width / 2 - 50.0f), (page_height / 2 - 50.0f), (page_width / 2 + 50.0f), (page_height / 2 + 50.0f));
  Signature new_signature = pdf_page.AddSignature(new_sig_rect);
  new_signature.SetFilter(ETSICADES_SIGNATURE_FILTER);
  new_signature.SetSubFilter(ETSICADES_SIGNATURE_SUBFILTER);

  new_signature.SetKeyValue(Signature::e_KeyNameSigner, L"Foxit PDF SDK");
  new_signature.SetKeyValue(Signature::e_KeyNameContactInfo, L"support@foxitsoftware.com");
  new_signature.SetKeyValue(Signature::e_KeyNameDN, L"CN=CN,MAIL=MAIL@MAIL.COM");
  new_signature.SetKeyValue(Signature::e_KeyNameLocation, L"Fuzhou, China");
  String new_value;
  new_value.Format("As a sample for subfilter \"%s\", in %s ", ETSICADES_SIGNATURE_SUBFILTER, TransformLevel2String(pades_level));
  new_signature.SetKeyValue(Signature::e_KeyNameReason, (const wchar_t*)WString::FromLocal(new_value));
  new_signature.SetKeyValue(Signature::e_KeyNameText, (const wchar_t*)WString::FromLocal(new_value));
  DateTime sign_time = GetLocalDateTime();
  new_signature.SetSignTime(sign_time);
  // Set appearance flags to decide which content would be used in appearance.
  uint32 ap_flags = Signature::e_APFlagLabel | Signature::e_APFlagSigner |
    Signature::e_APFlagReason | Signature::e_APFlagDN |
    Signature::e_APFlagLocation | Signature::e_APFlagText |
    Signature::e_APFlagSigningTime ;
  new_signature.SetAppearanceFlags(ap_flags);

  WString cert_path = input_path + L"foxit_all.pfx";
  WString cert_password = L"123456";
  Progressive sign_progressive = new_signature.StartSign(cert_path, cert_password, Signature::e_DigestSHA256, cached_signed_pdf_path);
  if (sign_progressive.GetRateOfProgress() != 100) {
    if (Progressive::e_Finished != sign_progressive.Continue()) {
      printf("[Failed] Fail to sign the new CAdES signature.\r\n");
      return;
    }
  }

  if (pades_level > Signature::e_PAdESLevelBT) {
    PDFDoc cache_pdf_doc(cached_signed_pdf_path);
    cache_pdf_doc.StartLoad();
    // Here, we only simply create an empty DSS object in PDF document, just as a simple exmaple.
    // In fact, user should use LTVVerifier to add DSS.
    cache_pdf_doc.CreateDSS();

    if (pades_level > Signature::e_PAdESLevelBLT) {
      PDFPage cache_pdf_page = cache_pdf_doc.GetPage(0);
      Signature time_stamp_signature = cache_pdf_page.AddSignature(RectF(), L"", Signature::e_SignatureTypeTimeStamp);
      Progressive sign_ts_progressive = time_stamp_signature.StartSign(L"", L"", Signature::e_DigestSHA256, real_signed_pdf_path);
      if (sign_ts_progressive.GetRateOfProgress() != 100) {
        if (Progressive::e_Finished != sign_ts_progressive.Continue()) {
          printf("[Failed] Fail to sign the new time stamp signature.\r\n");
          return;
        }
      }
    } else {
      cache_pdf_doc.SaveAs(real_signed_pdf_path, PDFDoc::e_SaveFlagIncremental);
    }
  }
}

void PAdESVerify(const WString& check_pdf_path, Signature::PAdESLevel expect_pades_level) {
  PDFDoc check_pdf_doc(check_pdf_path);
  check_pdf_doc.StartLoad();
  printf("To verify level of PAdES signature in file %s\r\n", (const char*)String::FromUnicode(check_pdf_path));

  int sig_count = check_pdf_doc.GetSignatureCount();
  if (0 == sig_count)
    printf("No signature in current PDF file.\r\n");
  bool has_cades_signature = false;
  for (int i = 0; i < check_pdf_doc.GetSignatureCount(); i++) {
    Signature temp_sig = check_pdf_doc.GetSignature(i);
    if (temp_sig.IsEmpty()) continue;
    uint32 sig_org_state = temp_sig.GetState();
    bool is_true = sig_org_state & Signature::e_StateSigned;
    if (!is_true) continue;
    if (temp_sig.GetSubFilter() == ETSICADES_SIGNATURE_SUBFILTER) {
      has_cades_signature = true;
      // Verify PAdES signature.
      Progressive verify_progressive = temp_sig.StartVerify();
      if (100 != verify_progressive.GetRateOfProgress()) {
        if (Progressive::e_Finished != verify_progressive.Continue()) {
          printf("[Failed] Fail to verify a PAdES signature. Signature index:%d\r\n", i);
          continue;
        }
      }
      uint32 sig_state = temp_sig.GetState();
      printf("Signature index: %d, a PAdES signature. State after verifying: %s\r\n", i, TransformSignatureStateToString(sig_state).c_str());

      // Get PAdES level.
      Signature::PAdESLevel actual_level = temp_sig.GetPAdESLevel();
      printf("Signature index:%d, PAdES level:%s, %s\r\n", 
             i, TransformLevel2String(actual_level), 
             actual_level == expect_pades_level?"matching expected level." : "NOT match expected level.");
    }
  }
  if (false == has_cades_signature)
    printf("No PAdES signature in current PDF file.\r\n");
}

int main(int argc, char *argv[]) {
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file_name = L"AboutFoxit.pdf";
  WString input_file_path = input_path + input_file_name;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library.
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  printf("Input file path: %s\r\n", (const char*)String::FromUnicode(input_file_path));
  try {
    TimeStampServerMgr::Initialize();

    Signature::PAdESLevel level = Signature::e_PAdESLevelBB;
    WString signed_pdf_path = output_directory + GenerateNewPDFFileName(input_file_name, TransformLevel2WideString(level));
    PAdESSign(input_file_path, signed_pdf_path, level);
    PAdESVerify(signed_pdf_path, level);

    TimeStampServer timestamp_server = TimeStampServerMgr::AddServer(FREE_ETSIRFC316TSA_SERVER_NAME, FREE_ETSIRFC316TSA_SERVER_URL, L"", L"");
    TimeStampServerMgr::SetDefaultServer(timestamp_server);
    for (level = Signature::e_PAdESLevelBT; level <= Signature::e_PAdESLevelBLTA; level = Signature::PAdESLevel(level+1)) {
      WString signed_pdf_path = output_directory + GenerateNewPDFFileName(input_file_name, TransformLevel2WideString(level));
      PAdESSign(input_file_path, signed_pdf_path, level);
      PAdESVerify(signed_pdf_path, level);
    }

    TimeStampServerMgr::Release();
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  } catch(...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}

