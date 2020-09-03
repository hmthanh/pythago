// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do LTV verification (using default callback) in PDF document.

// Include header files.
#include <iostream>
#include <time.h>
#include <ctime>
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
#include "../../../include/pdf/fs_ltvverifier.h"

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

WString output_directory = output_path + L"ltv/";

#define FREE_ETSIRFC316TSA_SERVER_NAME L"FreeTSAServer"
#define FREE_ETSIRFC316TSA_SERVER_URL L"http://ca.signfiles.com/TSAServer.aspx"

#define PKCS7_SIGNATURE_FILTER "Adobe.PPKLite"
#define PKCS7_SIGNATURE_SUBFILTER "adbe.pkcs7.detached"


FILE* OpenFileWrapper(const char* file_name, const char* file_mode) {
  FILE* ret_file = NULL;
#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&ret_file, (const char*)file_name, (const char*)file_mode);
#else
  ret_file = fopen((const char*)file_name, (const char*)file_mode);
#endif
  return ret_file;
}

string TransformSignatureStateToString(uint32 sig_state) {
  string state_str;
  if (sig_state & Signature::e_StateUnknown)
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

void PKCS7Signature(const WString& input_pdf_path, const WString& signed_pdf_path) {
  PDFDoc pdf_doc(input_pdf_path);
  pdf_doc.StartLoad();
  PDFPage pdf_page = pdf_doc.GetPage(0);
  float page_width = pdf_page.GetWidth();
  float page_height = pdf_page.GetHeight();
  RectF new_sig_rect((page_width / 2 - 50.0f), (page_height / 2 - 50.0f), (page_width / 2 + 50.0f), (page_height / 2 + 50.0f));
  Signature new_signature = pdf_page.AddSignature(new_sig_rect);
  new_signature.SetFilter(PKCS7_SIGNATURE_FILTER);
  new_signature.SetSubFilter(PKCS7_SIGNATURE_SUBFILTER);

  //String new_value;
  new_signature.SetKeyValue(Signature::e_KeyNameSigner, L"Foxit PDF SDK");
  new_signature.SetKeyValue(Signature::e_KeyNameContactInfo, L"support@foxitsoftware.com");
  new_signature.SetKeyValue(Signature::e_KeyNameDN, L"CN=CN,MAIL=MAIL@MAIL.COM");
  new_signature.SetKeyValue(Signature::e_KeyNameLocation, L"Fuzhou, China");
  String new_value;
  new_value.Format("As a sample for subfilter \"%s\" ", PKCS7_SIGNATURE_SUBFILTER);
  new_signature.SetKeyValue(Signature::e_KeyNameReason, (const wchar_t*)WString::FromLocal(new_value));
  new_signature.SetKeyValue(Signature::e_KeyNameText, (const wchar_t*)WString::FromLocal(new_value));
  DateTime sign_time = DateTime::GetLocalTime();
  new_signature.SetSignTime(sign_time);
  // Set appearance flags to decide which content would be used in appearance.
  uint32 ap_flags = Signature::e_APFlagLabel | Signature::e_APFlagSigner |
    Signature::e_APFlagReason | Signature::e_APFlagDN |
    Signature::e_APFlagLocation | Signature::e_APFlagText |
    Signature::e_APFlagSigningTime;
  new_signature.SetAppearanceFlags(ap_flags);

  WString cert_path = input_path + L"foxit_all.pfx";
  WString cert_password = L"123456";
  Progressive sign_progressive = new_signature.StartSign(cert_path, cert_password, Signature::e_DigestSHA256, signed_pdf_path);
  if (sign_progressive.GetRateOfProgress() != 100) {
    if (Progressive::e_Finished != sign_progressive.Continue()) {
      printf("[Failed] Fail to sign the new CAdES signature.\r\n");
      return;
    }
  }
}

// Here, the implementation of TrustedCertStoreCallback is very simple : 
// trust all input certificate(s) when this callback function is triggered during LTV verification.
// User can improve the implementation of the callback class TrustedCertStoreCallback or choose not to use TrustedCertStoreCallback.
class MyTrustedCertStoreCallback : public TrustedCertStoreCallback {
public:
  MyTrustedCertStoreCallback() {}
  ~MyTrustedCertStoreCallback() {}

  virtual bool IsCertTrusted(const String& cert) {
    return true;
  }
  
  virtual bool IsCertTrustedRoot(const String& cert) {
    return true;
  }
};

void UseLTVVerifier(const PDFDoc& pdf_doc, bool is_to_add_dss) {
  // Here use default RevocationCallback, so no need to call LTVVerifier::SetRevocationCallback
  LTVVerifier ltv_verifier(pdf_doc, true, true, false, LTVVerifier::e_SignatureCreationTime);

  // Use implemented TrustedCertStoreCallback to trust some cerificates during LTV verification.
  // Here, the implementation of TrustedCertStoreCallback is very simple : 
  // trust all input certificate(s) when this callback function is triggered during LTV verification.
  // User can improve the implementation of the callback class TrustedCertStoreCallback or choose not to use TrustedCertStoreCallback.
  MyTrustedCertStoreCallback my_callback;
  ltv_verifier.SetTrustedCertStoreCallback(&my_callback);

  ltv_verifier.SetVerifyMode(LTVVerifier::e_VerifyModeAcrobat);

  SignatureVerifyResultArray sig_verify_result_array = ltv_verifier.Verify();
  for (size_t i = 0; i < sig_verify_result_array.GetSize(); i++) {
    SignatureVerifyResult sig_verify_result = sig_verify_result_array.GetAt(i);
    String signature_name = sig_verify_result.GetSignatureName();
    uint32 sig_state = sig_verify_result.GetSignatureState();
    SignatureVerifyResult::LTVState ltv_state = sig_verify_result.GetLTVState();
    string ltv_state_str;
    switch (ltv_state) {
      case SignatureVerifyResult::e_LTVStateInactive:
        ltv_state_str = "inactive";
        break;
      case SignatureVerifyResult::e_LTVStateEnable:
        ltv_state_str = "enabled";
        break;
      case SignatureVerifyResult::e_LTVStateNotEnable:
        ltv_state_str = "not enabled";
        break;
    }
    printf("Signature name:%s, signature state: %s, LTV state: %s\r\n",
           signature_name.GetBuffer(signature_name.GetLength()),
           TransformSignatureStateToString(sig_state).c_str(),
           ltv_state_str.c_str());
    signature_name.ReleaseBuffer();
  }

  if (is_to_add_dss) {
    for (size_t i = 0; i < sig_verify_result_array.GetSize(); i++) {
      if (sig_verify_result_array.GetAt(i).GetSignatureState() & Signature::e_StateVerifyValid)
        ltv_verifier.AddDSS(sig_verify_result_array.GetAt(i));
    }
  }
}

void DoLTV(const WString& signed_pdf_path, const WString& saved_ltv_pdf_path) {
  // Use default SignatureCallback for signing a time stamp signature with filter "Adobe.PPKLite" and subfilter "ETSI.RFC3161",
  // so no need to register a custom signature callback.

  TimeStampServerMgr::Initialize();
  TimeStampServer timestamp_server = TimeStampServerMgr::AddServer(FREE_ETSIRFC316TSA_SERVER_NAME, FREE_ETSIRFC316TSA_SERVER_URL, L"", L"");
  TimeStampServerMgr::SetDefaultServer(timestamp_server);

  PDFDoc pdf_doc(signed_pdf_path);
  pdf_doc.StartLoad();
  // Add DSS
  printf("== Before Add DSS ==\r\n");
  UseLTVVerifier(pdf_doc, true);

  // Add DTS
  PDFPage pdf_page = pdf_doc.GetPage(0);
  // The new time stamp signature will have default filter name "Adobe.PPKLite" and default subfilter name "ETSI.RFC3161".
  Signature timestamp_signature = pdf_page.AddSignature(RectF(), L"", Signature::e_SignatureTypeTimeStamp);
  Progressive sign_progressive = timestamp_signature.StartSign(L"", L"", Signature::e_DigestSHA256, saved_ltv_pdf_path);
  if (sign_progressive.GetRateOfProgress() != 100)
    sign_progressive.Continue();

  // Check saved file.
  PDFDoc check_pdf_doc(saved_ltv_pdf_path);
  check_pdf_doc.StartLoad();
  // Just LTV veify.
  printf("== After Add DSS ==\r\n");
  UseLTVVerifier(check_pdf_doc, false);

  TimeStampServerMgr::Release();
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
    // Add a PKCS7 signature and sign it.
    WString signed_pdf_path = output_directory + input_file_name.Left(input_file_name.GetLength()-4) + L"_signed.pdf";
    PKCS7Signature(input_file_path, signed_pdf_path);

    // Do LTV
    WString saved_ltv_pdf_path = signed_pdf_path.Left(signed_pdf_path.GetLength() - 4) + L"_ltv.pdf";
    DoLTV(signed_pdf_path, saved_ltv_pdf_path);

  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  } catch(...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}

