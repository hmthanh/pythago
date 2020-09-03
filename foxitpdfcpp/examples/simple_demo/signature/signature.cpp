// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to add, sign and verify signature
// in PDF document.
//
// NOTE: before using this demo, user should ensure that openssl environment has been prepared:
// a. user should ensure all the openssl header files included by "#include" can be found. (In Windows, User can
//    change project setting "VC++ Directories" -> "Include Directories" or directly change the path
//    used in "#include".)
// b. user should ensure openssl library has been put in the specified path and can be linked to.
//   1. For Windows,
//       Please search "libeay32.lib" in this file to check the specified path. Or user can directly
//       change the path used to link to "libeay32.lib". If use dynamic library of openssl, user may
//       need to put dll library of openssl to the folder where ".exe" file is generated before running demo.
//   2. For Linux and Mac, user should put the "libssl.a" and "libcrypto.a"
//      in the directory "../../../lib".

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

// Include openssl header files
#include "../../../include/openssl/rsa.h"
#include "../../../include/openssl/evp.h"
#include "../../../include/openssl/objects.h"
#include "../../../include/openssl/x509.h"
#include "../../../include/openssl/err.h"
#include "../../../include/openssl/pem.h"
#include "../../../include/openssl/ssl.h"
#include "../../../include/openssl/pkcs12.h"
#include "../../../include/openssl/rand.h"
#include "../../../include/openssl/pkcs7.h"

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

WString output_directory = output_path + L"signature/";

#if !defined(WIN32) && !defined(_WIN64)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

#if defined(WIN32) || defined(_WIN64)
#include "openssl/applink.c"
#pragma  comment(lib,"../../../lib/libeay32.lib")
#endif

// Used for implementing SignatureCallback.
class DigestContext {
public:
  DigestContext(ReaderCallback* file_read_callback, const uint32* byte_range_array, uint32 byte_range_array_size)
    : file_read_callback_(file_read_callback)
    , byte_range_array_(byte_range_array)
    , byte_range_array_size_(byte_range_array_size) {}
  ~DigestContext() {}

  ReaderCallback* GetFileReadCallback() {
    return file_read_callback_;
  }
  uint32 GetByteRangeSize() {
    return byte_range_array_size_;
  }
  uint32 GetByteRangeElement(int32 index) {
    if (!byte_range_array_) return 0;
    return byte_range_array_[index];
  }

  SHA_CTX sha_ctx_;

protected:
  ReaderCallback* file_read_callback_;
  const uint32* byte_range_array_;
  uint32 byte_range_array_size_;
};

// Implementation of pdf::SignatureCallback
class SignatureCallbackImpl : public pdf::SignatureCallback {
public:
  SignatureCallbackImpl(string subfilter)
    : sub_filter_(subfilter)
    , digest_context_(NULL) {}
  ~SignatureCallbackImpl();

  virtual void Release() {
    delete this;
  }
  virtual bool StartCalcDigest(const ReaderCallback* file, const uint32* byte_range_array,
    uint32 size_of_array, const Signature& signature, const void* client_data);
  virtual Progressive::State ContinueCalcDigest(const void* client_data, const PauseCallback* pause);
  virtual String GetDigest(const void* client_data);
  virtual String Sign(const void* digest, uint32 digest_length, const wchar_t* cert_path,
    const WString& password, Signature::DigestAlgorithm digest_algorithm,
    void* client_data);
  virtual String Sign(const void* digest, uint32 digest_length, IFX_FileStream* cert_file_stream,
      const WString& password, Signature::DigestAlgorithm digest_algorithm,
      void* client_data);
  virtual uint32 VerifySigState(const void* digest, uint32 digest_length,
    const void* signed_data, uint32 signed_data_len,
    void* client_data);
  virtual bool IsNeedPadData() {return false;}
  virtual CertValidity CheckCertificateValidity(const wchar_t* cert_path, const WString& cert_password, void* client_data) {
    // User can check the validity of input certificate here.
    // If no need to check, just return e_CertValid.
    return foxit::pdf::SignatureCallback::e_CertValid;
  }

protected:
  bool GetTextFromFile(unsigned char *plainString);

  unsigned char* PKCS7Sign(const wchar_t* cert_file_path, String cert_file_password,
                           String plain_text, int& signed_data_size);
  bool PKCS7VerifySignature(String signed_data, String plain_text);
  bool ParseP12File(const wchar_t* cert_file_path, String cert_file_password,
                    EVP_PKEY** pkey, X509** x509, STACK_OF(X509)** ca);
  ASN1_INTEGER* CreateNonce(int bits);

private:
  string sub_filter_;
  DigestContext* digest_context_;

  string cert_file_path_;
  string cert_file_password_;
};

#define FREE_CERT_KEY if(pkey)\
                        EVP_PKEY_free(pkey);\
                      if(x509)\
                        X509_free(x509);\
                      if(ca)\
                        sk_X509_free(ca);\

void InitializeOpenssl() {
  SSLeay_add_all_algorithms();
}

SignatureCallbackImpl::~SignatureCallbackImpl() {
  if (digest_context_) {
    delete digest_context_;
    digest_context_ = NULL;
  }
}

bool SignatureCallbackImpl::GetTextFromFile(unsigned char* file_buffer) {
  if (!digest_context_ || !digest_context_->GetFileReadCallback()) return false;
  ReaderCallback* file_read = digest_context_->GetFileReadCallback();
  file_read->ReadBlock(file_buffer, digest_context_->GetByteRangeElement(0), digest_context_->GetByteRangeElement(1));
  file_read->ReadBlock(file_buffer + (digest_context_->GetByteRangeElement(1)-digest_context_->GetByteRangeElement(0)),
    digest_context_->GetByteRangeElement(2), digest_context_->GetByteRangeElement(3));
  return true;
}

bool SignatureCallbackImpl::StartCalcDigest(const ReaderCallback* file, const uint32* byte_range_array,
  uint32 size_of_array, const Signature& signature, const void* client_data) {
  if (digest_context_) {
    delete digest_context_;
    digest_context_ = NULL;
  }
  digest_context_ = new DigestContext(const_cast<ReaderCallback*>(file), byte_range_array, size_of_array);
  if(!SHA1_Init(&digest_context_->sha_ctx_)) {
    delete digest_context_;
    digest_context_ = NULL;
    return false;
  }
  return true;
}

Progressive::State SignatureCallbackImpl::ContinueCalcDigest(const void* client_data, const PauseCallback* pause) {
  if (!digest_context_) return Progressive::e_Error;

  uint32 file_length = digest_context_->GetByteRangeElement(1) + digest_context_->GetByteRangeElement(3);
  unsigned char* file_buffer = (unsigned char*)malloc(file_length);
  if (!file_buffer || !GetTextFromFile(file_buffer)) return Progressive::e_Error;

  SHA1_Update(&digest_context_->sha_ctx_, file_buffer, file_length);
  free(file_buffer);
  return Progressive::e_Finished;
}

String SignatureCallbackImpl::GetDigest(const void* client_data) {
  if (!digest_context_) return "";
  unsigned char* md = reinterpret_cast<unsigned char*>(OPENSSL_malloc((SHA_DIGEST_LENGTH)*sizeof(unsigned char)));
  if (1 != SHA1_Final(md, &digest_context_->sha_ctx_))
    return "";
  String digest = String(reinterpret_cast<const char*>(md), SHA_DIGEST_LENGTH);
  OPENSSL_free(md);
  return digest;
}

String SignatureCallbackImpl::Sign(const void* digest, uint32 digest_length, const wchar_t* cert_path,
                            const WString& password, Signature::DigestAlgorithm digest_algorithm,
                            void* client_data) {
  if (!digest_context_) return "";
  String plain_text;
  if ("adbe.pkcs7.sha1" == sub_filter_) {
    plain_text = String((const char*)digest, digest_length);
  }
  int signed_data_length = 0;
  unsigned char* signed_data_buffer = PKCS7Sign(cert_path, String::FromUnicode(password),
                                                plain_text, signed_data_length);
  if (!signed_data_buffer) return "";

  String signed_data = String((const char*)signed_data_buffer, signed_data_length);
  free(signed_data_buffer);
  return signed_data;
}

String SignatureCallbackImpl::Sign(const void* digest, uint32 digest_length, IFX_FileStream* file_stream,
    const WString& password, Signature::DigestAlgorithm digest_algorithm,
    void* client_data) {
    return "";
}

uint32 SignatureCallbackImpl::VerifySigState(const void* digest, uint32 digest_length,
                                         const void* signed_data, uint32 signed_data_len, void* client_data) {
  // Usually, the content of a signature field is contain the certification of signer.
  // But we can't judge this certification is trusted.
  // For this example, the signer is ourself. So when using api PKCS7_verify to verify,
  // we pass NULL to it's parameter <i>certs</i>.
  // Meanwhile, if application should specify the certificates, we suggest pass flag PKCS7_NOINTERN to
  // api PKCS7_verify.
  if (!digest_context_) return Signature::e_StateVerifyErrorData;
  String plain_text;
  unsigned char* file_buffer = NULL;
  if ("adbe.pkcs7.sha1" == sub_filter_) {
    plain_text = String(reinterpret_cast<const char*>(digest), digest_length);
  } else {
    return Signature::e_StateUnknown;
  }

  String signed_data_str = String(reinterpret_cast<const char*>(signed_data), signed_data_len);
  bool ret = PKCS7VerifySignature(signed_data_str, plain_text);
  if (file_buffer) free(file_buffer);
  //this function is only used to verify the intergrity of a signature.
  return ret ? Signature::e_StateVerifyNoChange : Signature::e_StateVerifyChange;

}

ASN1_INTEGER* SignatureCallbackImpl::CreateNonce(int bits) {
  unsigned char buf[20];
  int len = (bits - 1) / 8 + 1;
  // Generating random byte sequence.
  if (len > (int)sizeof(buf)) {
    return NULL;
  }
  if (RAND_bytes(buf, len) <= 0) {
    return NULL;
  }
  // Find the first non-zero byte and creating ASN1_INTEGER object.
  int i = 0;
  for (i = 0; i < len && !buf[i]; ++i) ;
  ASN1_INTEGER* nonce = NULL;
  if (!(nonce = ASN1_INTEGER_new())) {
    ASN1_INTEGER_free(nonce);
    return NULL;
  }
  OPENSSL_free(nonce->data);
  // Allocate at least one byte.
  nonce->length = len - i;
  if (!(nonce->data = reinterpret_cast<unsigned char*>(OPENSSL_malloc(nonce->length + 1)))) {
    ASN1_INTEGER_free(nonce);
    return NULL;
  }
  memcpy(nonce->data, buf + i, nonce->length);
  return nonce;
}

bool SignatureCallbackImpl::ParseP12File(const wchar_t* cert_file_path, String cert_file_password,
                                     EVP_PKEY** pkey, X509** x509, STACK_OF(X509)** ca) {
  FILE* file = NULL;
#if defined(_WIN32) || defined(_WIN64)
  _wfopen_s(&file, cert_file_path, L"rb");
#else
  file = fopen(String::FromUnicode(cert_file_path), "rb");
#endif  // defined(_WIN32) || defined(_WIN64)
  if (!file) {
    return false;
  }

  PKCS12* pkcs12 = d2i_PKCS12_fp(file, NULL);
  fclose (file);
  if (!pkcs12) {
    return false;
  }

  if (!PKCS12_parse(pkcs12, (const char*)cert_file_password, pkey, x509, ca)) {
    return false;
  }

  PKCS12_free(pkcs12);
  if (!pkey)
    return false;
  return true;
}

unsigned char* SignatureCallbackImpl::PKCS7Sign(const wchar_t* cert_file_path, String cert_file_password,
                                            String plain_text, int& signed_data_size) {
  PKCS7* p7 = NULL;
  EVP_PKEY* pkey = NULL;
  X509* x509 = NULL;
  STACK_OF(X509)* ca = NULL;
  if(!ParseP12File(cert_file_path, cert_file_password, &pkey, &x509, &ca))
    return NULL;

  p7 = PKCS7_new();
  PKCS7_set_type(p7, NID_pkcs7_signed);
  PKCS7_content_new(p7, NID_pkcs7_data);

  // Application should not judge the sign algorithm with the content's length.
  // Here, just for convenient;
  if (plain_text.GetLength() > 32)
    PKCS7_ctrl(p7, PKCS7_OP_SET_DETACHED_SIGNATURE, 1, NULL);

  PKCS7_SIGNER_INFO* signer_info = PKCS7_add_signature(p7, x509, pkey, EVP_sha1());
  PKCS7_add_certificate(p7, x509);

  for (int i = 0; i< sk_num(CHECKED_STACK_OF(X509,ca)); i++)
    PKCS7_add_certificate(p7, (X509*)sk_value(CHECKED_STACK_OF(X509,ca), i));

  // Set source data to BIO.
  BIO* p7bio = PKCS7_dataInit(p7, NULL);
  BIO_write(p7bio, plain_text.GetBuffer(1), plain_text.GetLength());
  PKCS7_dataFinal(p7, p7bio);

  FREE_CERT_KEY;
  BIO_free_all(p7bio);
  // Get signed data.
  unsigned long der_length = i2d_PKCS7(p7, NULL);
  unsigned char* der = reinterpret_cast<unsigned char*>(malloc(der_length));
  memset(der, 0, der_length);
  unsigned char* der_temp = der;
  i2d_PKCS7(p7, &der_temp);
  PKCS7_free(p7);
  signed_data_size = der_length;
  return (unsigned char*)der;
}

bool SignatureCallbackImpl::PKCS7VerifySignature(String signed_data, String plain_text) {
  // Retain PKCS7 object from signed data.
  BIO* vin = BIO_new_mem_buf((void*)signed_data.GetBuffer(1), signed_data.GetLength());
  PKCS7* p7 = d2i_PKCS7_bio(vin, NULL);
  STACK_OF(PKCS7_SIGNER_INFO) *sk = PKCS7_get_signer_info(p7);
  int sign_count = sk_PKCS7_SIGNER_INFO_num(sk);

  int length = 0;
  bool bSigAppr = false;
  unsigned char *p = NULL;
  for(int i=0;i<sign_count; i++) {
    PKCS7_SIGNER_INFO* sign_info = sk_PKCS7_SIGNER_INFO_value(sk,i);

    BIO *p7bio = BIO_new_mem_buf((void*)plain_text.GetBuffer(1), plain_text.GetLength());
    X509 *x509= PKCS7_cert_from_signer_info(p7,sign_info);
    if(1 == PKCS7_verify(p7, NULL, NULL,p7bio, NULL, PKCS7_NOVERIFY))
      bSigAppr = true;
    BIO_free(p7bio);
  }
  PKCS7_free(p7);
  BIO_free(vin);
  return bSigAppr;
}

////////////////////////

String DateTimeToString(const DateTime& datetime) {
  String ret_string;
  ret_string.Format("%d/%d/%d-%d:%d:%d %s%d:%d", datetime.year, datetime.month, datetime.day, datetime.hour,
    datetime.minute, datetime.second, datetime.utc_hour_offset > 0 ? "+" : "-", datetime.utc_hour_offset,
    datetime.utc_minute_offset);
  return ret_string;
}

DateTime GetLocalDateTime() {
  time_t t = time(NULL);
#if (WINAPI_PARTITION_APP || WINAPI_PARTITION_PC_APP) || \
  (defined(_WIN32) || defined(_WIN64)) && _FX_COMPILER_ != _FX_VC6_
  struct tm _Tm;
  localtime_s(&_Tm, &t);
  struct tm* rime = &_Tm;
  _tzset();
  long time_zone = NULL;
  _get_timezone(&time_zone);
  int timezone_hour = time_zone / 3600 * -1;
  int timezone_minute = (abs(time_zone) % 3600) / 60;
#elif defined(__linux__)
  struct tm* rime = localtime(&t);
  tzset();
  int timezone_hour = __timezone / 3600 * -1;
  int timezone_minute = ((int)abs(__timezone) % 3600) / 60;
#elif defined(__APPLE__)
  struct tm* rime = localtime(&t);
  tzset();
  int timezone_hour = timezone / 3600 * -1;
  int timezone_minute = ((int)abs(timezone) % 3600) / 60;
#endif
  DateTime datetime;
  datetime.year = static_cast<uint16>(rime->tm_year + 1900);
  datetime.month = static_cast<uint16>(rime->tm_mon + 1);
  datetime.day = static_cast<uint16>(rime->tm_mday);
  datetime.hour = static_cast<uint16>(rime->tm_hour);
  datetime.minute = static_cast<uint16>(rime->tm_min);
  datetime.second = static_cast<uint16>(rime->tm_sec);
  datetime.utc_hour_offset = timezone_hour;
  datetime.utc_minute_offset = timezone_minute;

  return datetime;
}

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
Signature AddSiganture(PDFPage pdf_page, const char* sub_filter) {
  float page_height = pdf_page.GetHeight();
  float page_width = pdf_page.GetWidth();
  RectF new_sig_rect(0, (float)(page_height*0.9), (float)(page_width*0.4), page_height);
  // Add a new signature to page.
  Signature new_sig = pdf_page.AddSignature(new_sig_rect);
  if (new_sig.IsEmpty()) return Signature();
  // Set values for the new signature.
  new_sig.SetKeyValue(Signature::e_KeyNameSigner, L"Foxit PDF SDK");
  String new_value;
  new_value.Format("As a sample for subfilter \"%s\"", sub_filter);
  new_sig.SetKeyValue(Signature::e_KeyNameReason, (const wchar_t*)WString::FromLocal(new_value));
  new_sig.SetKeyValue(Signature::e_KeyNameContactInfo, L"support@foxitsoftware.com");
  new_sig.SetKeyValue(Signature::e_KeyNameDN, L"CN=CN,MAIL=MAIL@MAIL.COM");
  new_sig.SetKeyValue(Signature::e_KeyNameLocation, L"Fuzhou, China");
  new_value.Format("As a sample for subfilter \"%s\"", sub_filter);
  new_sig.SetKeyValue(Signature::e_KeyNameText, (const wchar_t*)WString::FromLocal(new_value));
  DateTime sign_time = GetLocalDateTime();
  new_sig.SetSignTime(sign_time);
  WString image_file_path = input_path + L"FoxitLogo.jpg";
  Image image((const wchar_t*)image_file_path);
  new_sig.SetImage(image, 0);
  // Set appearance flags to decide which content would be used in appearance.
  uint32 ap_flags = Signature::e_APFlagLabel | Signature::e_APFlagSigner |
                    Signature::e_APFlagReason | Signature::e_APFlagDN |
                    Signature::e_APFlagLocation | Signature::e_APFlagText |
                    Signature::e_APFlagSigningTime | Signature::e_APFlagBitmap;
  new_sig.SetAppearanceFlags(ap_flags);

  return new_sig;
}

void AdobePPKLiteSignature(PDFDoc pdf_doc, bool use_default) {
  const char* filter = "Adobe.PPKLite";
  const char* sub_filter = "adbe.pkcs7.detached";


  if (!use_default) {
    InitializeOpenssl();
    sub_filter = "adbe.pkcs7.sha1";
    SignatureCallbackImpl* sig_callback = new SignatureCallbackImpl(sub_filter);
    Library::RegisterSignatureCallback(filter, sub_filter, sig_callback);
  } 

  printf("Use signature callback object for filter \"%s\" and sub-filter \"%s\"\r\n",
    filter, sub_filter);
  PDFPage pdf_page = pdf_doc.GetPage(0);
  // Add a new signature to first page.
  Signature new_signature = AddSiganture(pdf_page, sub_filter);
  // Set filter and subfilter for the new signature.
  new_signature.SetFilter(filter);
  new_signature.SetSubFilter(sub_filter);
  bool is_signed = new_signature.IsSigned();
  uint32 sig_state = new_signature.GetState();
  printf("[Before signing] Signed?:%s\t State:%s\r\n",
          is_signed? "true" : "false",
          TransformSignatureStateToString(sig_state).c_str());

  // Sign the new signature.
  WString signed_pdf_path = output_directory + L"signed_newsignature.pdf";
  if (use_default)
    signed_pdf_path = output_directory + L"signed_newsignature_default_handler.pdf";

  WString cert_file_path = input_path + L"foxit_all.pfx";
  WString cert_file_password = L"123456";
  // Cert file path will be passed back to application through callback function FSSignatureCallback::Sign().
  // In this demo, the cert file path will be used for signing in callback function FSSignatureCallback::Sign().
  new_signature.StartSign((const wchar_t*)cert_file_path, cert_file_password,
                          Signature::e_DigestSHA1, (const wchar_t*)signed_pdf_path, NULL, NULL);
  printf("[Sign] Finished!\r\n");
  is_signed = new_signature.IsSigned();
  sig_state = new_signature.GetState();
  printf("[After signing] Signed?:%s\tState:%s\r\n",
          is_signed? "true" : "false",
          TransformSignatureStateToString(sig_state).c_str());

  // Open the signed document and verify the newly added signature (which is the last one).
  printf("Signed PDF file: %s\r\n", (const char*)String::FromUnicode(signed_pdf_path));
  PDFDoc signed_pdf_doc((const wchar_t*)signed_pdf_path);
  ErrorCode error_code = signed_pdf_doc.Load(NULL);
  if (foxit::e_ErrSuccess !=error_code ) {
    printf("Fail to open the signed PDF file.\r\n");
    return;
  }
  // Get the last signature which is just added and signed.
  int sig_count = signed_pdf_doc.GetSignatureCount();
  Signature signed_signature = signed_pdf_doc.GetSignature(sig_count-1);
  // Verify the intergrity of signature.
  signed_signature.StartVerify(NULL, NULL);
  printf("[Verify] Finished!\r\n");
  is_signed = signed_signature.IsSigned();
  sig_state = signed_signature.GetState();
  printf("[After verifying] Signed?:%s\tState:%s\r\n",
          is_signed? "true" : "false",
          TransformSignatureStateToString(sig_state).c_str());
}

#if (defined(__linux__) && defined(__x86_64__)) || defined(__APPLE__) || defined(_WIN64)
#define FORMAT_UINT32 "%u"
#else
#define FORMAT_UINT32 "%lu"
#endif

void CheckSignatureInfo(PDFDoc pdf_doc) {
  int sig_count = pdf_doc.GetSignatureCount();
  if (sig_count<1) {
    printf("No signature in current PDF file.\r\n");
    return;
  }
  for (int i = 0; i < sig_count; i++) {
    printf("Signature index: %d\r\n", i);
    Signature signature = pdf_doc.GetSignature(i);
    if (signature.IsEmpty()) continue;
    bool is_signed = signature.IsSigned();
    printf("Signed?:%s\r\n", is_signed? "true":"false");
    uint32 sig_state = signature.GetState();
    printf("State:%s\r\n", TransformSignatureStateToString(sig_state).c_str());

    annots::Widget widget_annot = signature.GetControl(0).GetWidget();
    printf("Object number " FORMAT_UINT32 " of related widget annotation's dictionary\r\n", widget_annot.GetDict()->GetObjNum());

    String filter = signature.GetFilter();
    printf("Filter:%s\r\n",(const char*)filter);
    String sub_filter = signature.GetSubFilter();
    printf("Sub-filter:%s\r\n", (const char*)sub_filter);
    if (is_signed){
      DateTime sign_time = signature.GetSignTime();
      String time_str = DateTimeToString(sign_time);
      printf("Sign Time:%s\r\n", (const char*)time_str);
    }
    WString key_value;
    key_value = signature.GetKeyValue(Signature::e_KeyNameSigner);
    printf("Signer:%s\r\n", (const char*)String::FromUnicode(key_value));
    key_value = signature.GetKeyValue(Signature::e_KeyNameLocation);
    printf("Location:%s\r\n", (const char*)String::FromUnicode(key_value));
    key_value = signature.GetKeyValue(Signature::e_KeyNameReason);
    printf("Reason:%s\r\n", (const char*)String::FromUnicode(key_value));
    key_value = signature.GetKeyValue(Signature::e_KeyNameContactInfo);
    printf("Contact Info:%s\r\n", (const char*)String::FromUnicode(key_value));
    key_value = signature.GetKeyValue(Signature::e_KeyNameDN);
    printf("DN:%s\r\n", (const char*)String::FromUnicode(key_value));
    key_value = signature.GetKeyValue(Signature::e_KeyNameText);
    printf("Text:%s\r\n", (const char*)String::FromUnicode(key_value));
  }
}

int main(int argc, char *argv[]) {
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"AboutFoxit.pdf";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library.
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  printf("Input file path: %s\r\n", (const char*)String::FromUnicode(input_file));
  try {
    for (int i = 0; i < 2; i++) {
      PDFDoc pdf_doc(input_file);
      pdf_doc.StartLoad(NULL, false, NULL);

      // Check information of existed signature(s) in PDF file if there's any signature in the PDF file.
      CheckSignatureInfo(pdf_doc);
      // Add new signature, sign it and verify it with filter "Adobe.PPKLite" and different subfilter.
    
      AdobePPKLiteSignature(pdf_doc, i > 0 ? true : false);
      CheckSignatureInfo(pdf_doc);
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

