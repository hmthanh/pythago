// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do encryption and decryption for a PDF file
// by using password security method, custom security method, Foxit DRM security method, certificate security method
// or Microsoft RMS security method.
//
// NOTE: For Linux and Mac, before using this demo, user should ensure that openssl environment has been prepared:
//       user should ensure all the openssl header files included by "#include" can be found and
//       put the "libssl.a" and "libcrypto.a" in the directory "../../../lib".

#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_security.h"

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

WString output_directory = output_path + L"security/";

#if defined(_WIN32) || defined(_WIN64)
#include <WinCrypt.h>
#define PSL_ALL_PERMISSION 4294967292
#define PSL_NO_PERMISSION 4294963392
#define PSL_ENCODING_TYPE PKCS_7_ASN_ENCODING | X509_ASN_ENCODING
#define PSL_SEED_LENGTH 20
#define PSL_PDFKEY_LENGTH 16

class PSLCryptLib {
public:
  PSLCryptLib();
  virtual ~PSLCryptLib();

public:
  HMODULE GetCrypt32();
  HMODULE GetAdvapi32();

  // Crypt32
  BOOL CryptMsgUpdate(HCRYPTMSG hCryptMsg, const BYTE *pbData, DWORD cbData, BOOL fFinal);

  BOOL CryptMsgGetParam(void *hCryptMsg, DWORD dwParamType, DWORD dwIndex, void *pvData, DWORD *pcbData);

  BOOL CryptMsgClose(HCRYPTMSG hCryptMsg);

  DWORD CryptMsgCalculateEncodedLength(DWORD dwMsgEncodingType, DWORD dwFlags, DWORD dwMsgType,
    void const *pvMsgEncodeInfo, OPTIONAL LPSTR pszInnerContentObjID, DWORD cbData);

  HCRYPTMSG CryptMsgOpenToEncode(DWORD dwMsgEncodingType, DWORD dwFlags, DWORD dwMsgType, void const *pvMsgEncodeInfo,
    OPTIONAL LPSTR pszInnerContentObjID, OPTIONAL PCMSG_STREAM_INFO pStreamInfo);

  BOOL CertGetIntendedKeyUsage(DWORD dwCertEncodingType, PCERT_INFO pCertInfo, BYTE *pbKeyUsage, DWORD cbKeyUsage);

  BOOL CertDeleteCertificateFromStore(IN PCCERT_CONTEXT pCertContext);

  BOOL CertFreeCertificateContext(IN PCCERT_CONTEXT pCertContext);

  PCCERT_CONTEXT CertCreateCertificateContext(IN DWORD dwCertEncodingType, IN const BYTE *pbCertEncoded,
    IN DWORD cbCertEncoded);

  // Advapi32
  BOOL CryptAcquireContextA(HCRYPTPROV *phProv, LPCSTR szContainer, LPCSTR szProvider, DWORD dwProvType, DWORD dwFlags);

  BOOL CryptCreateHash(HCRYPTPROV hProv, ALG_ID Algid, HCRYPTKEY hKey, DWORD dwFlags, HCRYPTHASH *phHash);

  BOOL CryptHashData(HCRYPTHASH hHash, CONST BYTE *pbData, DWORD dwDataLen, DWORD dwFlags);

  BOOL CryptGetHashParam(HCRYPTHASH hHash, DWORD dwParam, BYTE *pbData, DWORD *pdwDataLen, DWORD dwFlags);

  BOOL CryptDestroyHash(HCRYPTHASH hHash);

  BOOL CryptReleaseContext(HCRYPTPROV hProv, DWORD dwFlags);

  BOOL CryptGenRandom(HCRYPTPROV hProv, DWORD dwLen, BYTE *pbBuffer);

  HMODULE LoadCrypt32();
  HMODULE LoadCryptui();
  HMODULE LoadAdvapi32();

private:
  HMODULE m_hCrypt32;
  HMODULE m_hCryptui;
  HMODULE m_hAdvapi32;

  BOOL m_bCrypt32Loaded;
  BOOL m_bCryptuiLoaded;
  BOOL m_bAdvapi32Loaded;
};

#if defined(_MSC_VER) && _MSC_VER < 1300
#include "wincrypt.h"
#endif
#define PSL_PASSWORD_MAXLEN 32

/* ------------------------------ PSLCryptLib ------------------------------ */
PSLCryptLib::PSLCryptLib()
    : m_hCrypt32(NULL)
    , m_hCryptui(NULL)
    , m_hAdvapi32(NULL)
    , m_bCrypt32Loaded(FALSE)
    , m_bCryptuiLoaded(FALSE)
    , m_bAdvapi32Loaded(FALSE) {}

PSLCryptLib::~PSLCryptLib() {
  if (m_hCrypt32) {
    ::FreeLibrary(m_hCrypt32);
    m_hCrypt32 = NULL;
  }

  if (m_hCryptui) {
    ::FreeLibrary(m_hCryptui);
    m_hCryptui = NULL;
  }

  if (m_hAdvapi32) {
    ::FreeLibrary(m_hAdvapi32);
    m_hAdvapi32 = NULL;
  }
}

HMODULE PSLCryptLib::LoadCrypt32() {
  if (!m_bCrypt32Loaded) {
    m_hCrypt32 = ::LoadLibraryW(L"crypt32.dll");
    m_bCrypt32Loaded = TRUE;
  }

  return m_hCrypt32;
}

HMODULE PSLCryptLib::LoadCryptui() {
  if (!m_bCryptuiLoaded) {
    m_hCryptui = ::LoadLibraryW(L"cryptui.dll");
    m_bCryptuiLoaded = TRUE;
  }

  return m_hCryptui;
}

HMODULE PSLCryptLib::LoadAdvapi32() {
  if (!m_bAdvapi32Loaded) {
    m_hAdvapi32 = ::LoadLibraryW(L"advapi32.dll");
    m_bAdvapi32Loaded = TRUE;
  }

  return m_hAdvapi32;
}

HMODULE PSLCryptLib::GetCrypt32() {
  return LoadCrypt32();
}

HMODULE PSLCryptLib::GetAdvapi32() {
  return LoadAdvapi32();
}

#define PSL_MAKEFUNC_CRYPTLIB(dllfunc, funcname, clare, params, rettype, defval) \
  \
typedef \
  rettype(WINAPI *Type_##funcname)##clare; \
  \
rettype PSLCryptLib::funcname##clare \
{ \
    if (HMODULE hModule = PSLCryptLib::##dllfunc()) { \
      if (Type_##funcname proc = (Type_##funcname)::GetProcAddress(hModule, #funcname)) { \
        return proc##params; \
      } \
    } \
    return defval; \
  \
}

// Crypt32

PSL_MAKEFUNC_CRYPTLIB(GetCrypt32, CryptMsgUpdate, (HCRYPTMSG hCryptMsg, const BYTE *pbData, DWORD cbData, BOOL fFinal),
                      (hCryptMsg, pbData, cbData, fFinal), BOOL, FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetCrypt32, CryptMsgGetParam,
                      (void *hCryptMsg, DWORD dwParamType, DWORD dwIndex, void *pvData, DWORD *pcbData),
                      (hCryptMsg, dwParamType, dwIndex, pvData, pcbData), BOOL, FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetCrypt32, CryptMsgClose, (HCRYPTMSG hCryptMsg), (hCryptMsg), BOOL, FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetCrypt32, CryptMsgCalculateEncodedLength,
                      (DWORD dwMsgEncodingType, DWORD dwFlags, DWORD dwMsgType, void const *pvMsgEncodeInfo,
                       OPTIONAL LPSTR pszInnerContentObjID, DWORD cbData),
                      (dwMsgEncodingType, dwFlags, dwMsgType, pvMsgEncodeInfo, pszInnerContentObjID, cbData), DWORD, 0)

PSL_MAKEFUNC_CRYPTLIB(GetCrypt32, CryptMsgOpenToEncode,
                      (DWORD dwMsgEncodingType, DWORD dwFlags, DWORD dwMsgType, void const *pvMsgEncodeInfo,
                       OPTIONAL LPSTR pszInnerContentObjID, OPTIONAL PCMSG_STREAM_INFO pStreamInfo),
                      (dwMsgEncodingType, dwFlags, dwMsgType, pvMsgEncodeInfo, pszInnerContentObjID, pStreamInfo),
                      HCRYPTMSG, NULL)

PSL_MAKEFUNC_CRYPTLIB(GetCrypt32, CertGetIntendedKeyUsage,
                      (DWORD dwCertEncodingType, PCERT_INFO pCertInfo, BYTE *pbKeyUsage, DWORD cbKeyUsage),
                      (dwCertEncodingType, pCertInfo, pbKeyUsage, cbKeyUsage), BOOL, FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetCrypt32, CertDeleteCertificateFromStore, (IN PCCERT_CONTEXT pCertContext), (pCertContext),
                      BOOL, FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetCrypt32, CertFreeCertificateContext, (IN PCCERT_CONTEXT pCertContext), (pCertContext), BOOL,
                      FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetCrypt32, CertCreateCertificateContext,
                      (IN DWORD dwCertEncodingType, IN const BYTE *pbCertEncoded, IN DWORD cbCertEncoded),
                      (dwCertEncodingType, pbCertEncoded, cbCertEncoded), PCCERT_CONTEXT, NULL)

// Advapi32
PSL_MAKEFUNC_CRYPTLIB(GetAdvapi32, CryptAcquireContextA,
                      (HCRYPTPROV * phProv, LPCSTR szContainer, LPCSTR szProvider, DWORD dwProvType, DWORD dwFlags),
                      (phProv, szContainer, szProvider, dwProvType, dwFlags), BOOL, FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetAdvapi32, CryptCreateHash,
                      (HCRYPTPROV hProv, ALG_ID Algid, HCRYPTKEY hKey, DWORD dwFlags, HCRYPTHASH *phHash),
                      (hProv, Algid, hKey, dwFlags, phHash), BOOL, FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetAdvapi32, CryptHashData,
                      (HCRYPTHASH hHash, CONST BYTE *pbData, DWORD dwDataLen, DWORD dwFlags),
                      (hHash, pbData, dwDataLen, dwFlags), BOOL, FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetAdvapi32, CryptGetHashParam,
                      (HCRYPTHASH hHash, DWORD dwParam, BYTE *pbData, DWORD *pdwDataLen, DWORD dwFlags),
                      (hHash, dwParam, pbData, pdwDataLen, dwFlags), BOOL, FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetAdvapi32, CryptDestroyHash, (HCRYPTHASH hHash), (hHash), BOOL, FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetAdvapi32, CryptReleaseContext, (HCRYPTPROV hProv, DWORD dwFlags), (hProv, dwFlags), BOOL,
                      FALSE)

PSL_MAKEFUNC_CRYPTLIB(GetAdvapi32, CryptGenRandom, (HCRYPTPROV hProv, DWORD dwLen, BYTE *pbBuffer),
                      (hProv, dwLen, pbBuffer), BOOL, FALSE)

#define PSL_PERMISSION_LENGTH 4
#define PSL_SEEDBUF_LENGTH PSL_SEED_LENGTH + PSL_PERMISSION_LENGTH

bool MakeEnvelope(PSLCryptLib* pCryptLib, PCERT_INFO* pCertArray, int nCertCount, uint32 nPermission, uint8* pSeed,
  uint8*& pbEncodedBlob, uint32& cbEncodedBlob) {
    if (!pCryptLib)
      return false;

    HCRYPTPROV hcp = NULL;
    BOOL bRet = pCryptLib->CryptAcquireContextA(&hcp, NULL, NULL, 1, 0);
    if (!bRet)
      return false;

    // Initialize the symmetric-encryption algorithm identifier structure.
    CRYPT_ALGORITHM_IDENTIFIER ContentEncryptAlgorithm;
    DWORD ContentEncryptAlgSize = sizeof(ContentEncryptAlgorithm);
    memset(&ContentEncryptAlgorithm, 0, ContentEncryptAlgSize);

    // Initialize the necessary members. This particular OID does not need any parameters.
    // Some OIDs, however, will require that the other members be initialized.
    ContentEncryptAlgorithm.pszObjId = szOID_RSA_RC4;

    // Initialize the CMSG_ENVELOPED_ENCODE_INFO structure.
    CMSG_ENVELOPED_ENCODE_INFO EnvelopedEncodeInfo;
    memset(&EnvelopedEncodeInfo, 0, sizeof(CMSG_ENVELOPED_ENCODE_INFO));
    EnvelopedEncodeInfo.cbSize = sizeof(CMSG_ENVELOPED_ENCODE_INFO);
    EnvelopedEncodeInfo.hCryptProv = (HCRYPTPROV)hcp;
    EnvelopedEncodeInfo.ContentEncryptionAlgorithm = ContentEncryptAlgorithm;
    EnvelopedEncodeInfo.pvEncryptionAuxInfo = NULL;
    EnvelopedEncodeInfo.cRecipients = nCertCount;
    EnvelopedEncodeInfo.rgpRecipients = pCertArray;

    // Get the size of the encoded message BLOB.
    cbEncodedBlob = pCryptLib->CryptMsgCalculateEncodedLength(PSL_ENCODING_TYPE,     // message encoding type
      0,                     // flags
      CMSG_ENVELOPED,        // message type
      &EnvelopedEncodeInfo,  // pointer to structure
      NULL,                  // inner content OID
      24);                   // size of content
    if (cbEncodedBlob == 0) {
      pCryptLib->CryptReleaseContext(hcp, 0);
      return false;
    }

    // Allocate memory for the encoded BLOB.
    pbEncodedBlob = (uint8*)malloc(cbEncodedBlob);
    if (!pbEncodedBlob) {
      pCryptLib->CryptReleaseContext(hcp, 0);
      return false;
    }

    // Open a message to encode.
    HCRYPTMSG hMsg = pCryptLib->CryptMsgOpenToEncode(PSL_ENCODING_TYPE,     // encoding type
      0,                     // flags
      CMSG_ENVELOPED,        // message type
      &EnvelopedEncodeInfo,  // pointer to structure
      NULL,                  // inner content OID
      NULL);                 // stream information (not used)

    if (hMsg == NULL) {
      pCryptLib->CryptReleaseContext(hcp, 0);
      free(pbEncodedBlob);
      return false;
    }

    // Data to be Encrypted
    uint8 szSeedBuf[PSL_SEEDBUF_LENGTH] = {0};
    memcpy(szSeedBuf, pSeed, PSL_SEED_LENGTH);

    *(szSeedBuf + PSL_SEED_LENGTH) = HIBYTE(HIWORD(nPermission));
    *(szSeedBuf + PSL_SEED_LENGTH + 1) = LOBYTE(HIWORD(nPermission));
    *(szSeedBuf + PSL_SEED_LENGTH + 2) = HIBYTE(LOWORD(nPermission));

    if (nPermission == PSL_ALL_PERMISSION)
      *(szSeedBuf + PSL_SEED_LENGTH + 3) = LOBYTE(LOWORD(nPermission)) | 0x03;
    else
      *(szSeedBuf + PSL_SEED_LENGTH + 3) = LOBYTE(LOWORD(nPermission)) | 0x01;

    int lasterr = GetLastError();
    // Update the message with the data.
    bRet = pCryptLib->CryptMsgUpdate(hMsg, szSeedBuf, PSL_SEEDBUF_LENGTH, true);
    if (!bRet) {
      pCryptLib->CryptMsgClose(hMsg);
      pCryptLib->CryptReleaseContext(hcp, 0);
      free(pbEncodedBlob);

      return false;
    }

    // Get the resulting message.
    bRet = pCryptLib->CryptMsgGetParam(hMsg, CMSG_CONTENT_PARAM, 0, pbEncodedBlob, (DWORD*)&cbEncodedBlob);

    if (!bRet) {
      pCryptLib->CryptMsgClose(hMsg);
      pCryptLib->CryptReleaseContext(hcp, 0);
      free(pbEncodedBlob);

      return false;
    }

    // Clean up.
    pCryptLib->CryptMsgClose(hMsg);
    pCryptLib->CryptReleaseContext(hcp, 0);
    return true;
}

void CreateSeed(PSLCryptLib* pCryptLib, uint8* pSeed) {
  HCRYPTPROV hcp = NULL;
  pCryptLib->CryptAcquireContextA(&hcp, NULL, NULL, 1, 0);

  DWORD dwErrCode = GetLastError();
  if (dwErrCode == NTE_BAD_KEYSET) {
    pCryptLib->CryptAcquireContextA(&hcp, NULL, NULL, 1, CRYPT_DELETEKEYSET);
    pCryptLib->CryptAcquireContextA(&hcp, NULL, NULL, 1, CRYPT_NEWKEYSET);
  }

  if (hcp) {
    pCryptLib->CryptGenRandom(hcp, PSL_SEED_LENGTH, pSeed);
    pCryptLib->CryptReleaseContext(hcp, 0);
  }
}

void GetPDFKeyFromEnvelopes(PSLCryptLib* pCryptLib, String* pEnvelopes, int envelopesCount, const uint8* pSeed,
  bool bEncryptMeta, uint8* pPDFKey) {
    if (!pCryptLib)
      return;
    // Calculate encryption key
    HCRYPTPROV hcp = NULL;

    // Acquire Context http://support.microsoft.com/kb/238187/zh-cn
    if (!pCryptLib->CryptAcquireContextA(&hcp, "Container", NULL, PROV_RSA_FULL, 0)) {
      if (GetLastError() == NTE_BAD_KEYSET) {
        if (!pCryptLib->CryptAcquireContextA(&hcp, ("Container"), NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
          // Error ...
          DWORD dwErrorCode = GetLastError();
          // TRACE(_T("\nERROR CODE: %d\r\n") , dwErrorCode);
        }
      }
    }

    if (!hcp)
      return;

    HCRYPTHASH hash = NULL;
    pCryptLib->CryptCreateHash(hcp, (4 << 13) | 4, 0, 0, &hash);

    pCryptLib->CryptHashData(hash, pSeed, 20, 0);

    for (int i = 0, sz = envelopesCount; i < sz; i++) {
      String envelop = pEnvelopes[i];
      pCryptLib->CryptHashData(hash, (BYTE*)envelop.GetBuffer(envelop.GetLength()), envelop.GetLength(), 0);
    }

    if (!bEncryptMeta) {
      uint32 tag = 0xffffffff;
      pCryptLib->CryptHashData(hash, (const BYTE*)&tag, 4, 0);
    }

    DWORD size = 20;
    pCryptLib->CryptGetHashParam(hash, 2, pPDFKey, &size, 0);

    pCryptLib->CryptDestroyHash(hash);
    pCryptLib->CryptReleaseContext(hcp, 0);
}

bool GetCertificateInfo(const char* certFilePath, StringArray& envelopes, String& initialKey, bool bEncryptMetaData,
  int len) {
    FILE* fpCert = NULL;
    fopen_s(&fpCert, certFilePath, "rb");
    if (!fpCert) {
      return false;
    }
    fseek(fpCert, 0, SEEK_END);
    long cbData = ftell(fpCert);
    uint8* pbData = new uint8[cbData];
    fseek(fpCert, 0, SEEK_SET);
    fread(pbData, sizeof(char), cbData, fpCert);
    fclose(fpCert);

    PSLCryptLib cryptLib;

    PCCERT_CONTEXT pTempCertContext = cryptLib.CertCreateCertificateContext(PSL_ENCODING_TYPE, pbData, cbData);
    if (!pTempCertContext)
      return false;

    BYTE usage;
    cryptLib.CertGetIntendedKeyUsage(pTempCertContext->dwCertEncodingType, pTempCertContext->pCertInfo, &usage, 1);
    if ((usage & CERT_DATA_ENCIPHERMENT_KEY_USAGE) != CERT_DATA_ENCIPHERMENT_KEY_USAGE && usage != 0) {
      cryptLib.CertFreeCertificateContext(pTempCertContext);
      return false;
    }
    SYSTEMTIME st;
    FILETIME crtTime;
    ::GetLocalTime(&st);
    ::SystemTimeToFileTime(&st, &crtTime);
    if (::CompareFileTime(&crtTime, &(pTempCertContext->pCertInfo->NotBefore)) < 0 ||
      ::CompareFileTime(&crtTime, &(pTempCertContext->pCertInfo->NotAfter)) > 0) {
        cryptLib.CertFreeCertificateContext(pTempCertContext);
        return false;
    }

    uint8 Seed[PSL_SEED_LENGTH];
    CreateSeed(&cryptLib, Seed);

    uint8* pbEncodedBlob = NULL;
    uint32 cbEncodedBlob = 0;
    PCERT_INFO pCertInfo = pTempCertContext->pCertInfo;
    if (!MakeEnvelope(&cryptLib, &pCertInfo, 1, 0xfffff8c4, Seed, pbEncodedBlob, cbEncodedBlob))
      return false;
    cryptLib.CertFreeCertificateContext(pTempCertContext);

    String tempEnvolops[1];
    tempEnvolops[0] = String((const char*)pbEncodedBlob, cbEncodedBlob);
    uint8 PDFKey[128];
    GetPDFKeyFromEnvelopes(&cryptLib, tempEnvolops, 1, Seed, bEncryptMetaData, PDFKey);
    envelopes.Add(tempEnvolops[0]);
    initialKey = String((const char*)PDFKey, len);
    free(pbEncodedBlob);
    delete[] pbData;

    return true;
}
#else

#include "../../../include/openssl/bio.h"
#include "../../../include/openssl/evp.h"
#include "../../../include/openssl/objects.h"
#include "../../../include/openssl/pem.h"
#include "../../../include/openssl/pkcs12.h"
#include "../../../include/openssl/pkcs7.h"
#include "../../../include/openssl/sha.h"
#include "../../../include/openssl/stack.h"
#include "../../../include/openssl/x509.h"

bool GetCertificateInfo(const char* certFilePath, StringArray& envelopes, String& initialKey, bool bEncryptMetaData, int len)
{
  PKCS7        *p7;
  char        *p;

  FILE* fpCert = fopen(certFilePath, "rb");
  if (!fpCert) {
    return FALSE;
  }

  fseek(fpCert, 0, SEEK_END);
  long cbData =  ftell(fpCert);
  char* pbData = (char*)malloc(cbData);
  fseek(fpCert, 0, SEEK_SET);
  fread(pbData, sizeof(char), cbData, fpCert);
  fclose(fpCert);

  char random[24] = {0};
  memset(random,0xff,24);
  for(int i = 0; i<20; i++)
    random[i] = rand();

  ERR_load_BIO_strings();
  OpenSSL_add_all_algorithms();

  p=pbData;
  X509 *x509_Cert=X509_new();

  d2i_X509(&x509_Cert,(const unsigned char **)&p,cbData);
  p7=PKCS7_new();
  PKCS7_set_type(p7,NID_pkcs7_enveloped);
  EVP_CIPHER *evp_cipher = (EVP_CIPHER *)EVP_des_ede3_cbc();

  PKCS7_set_cipher(p7,evp_cipher);
  PKCS7_add_recipient(p7,x509_Cert);
  BIO *p7bio = PKCS7_dataInit(p7, NULL);
  BIO_write(p7bio,random,24);
  BIO_flush(p7bio);
  PKCS7_dataFinal(p7, p7bio);
  unsigned char* derTmp;
  int derLen = i2d_PKCS7(p7,NULL);
  unsigned char * der  = (unsigned char*)malloc(derLen);
  derTmp = der;
  derLen = i2d_PKCS7(p7,(unsigned char **)&derTmp);
  BIO_free_all(p7bio);
  PKCS7_free(p7);
  unsigned char* envelopmem = der;

  int mem_size = 20;
  if (32 == len) mem_size = 32;
  unsigned char* initmem = new unsigned char[mem_size];
  memset(initmem, 0, sizeof(unsigned char)*mem_size);
  if (32 != len) {
    SHA_CTX c;
    SHA1_Init(&c);
    SHA1_Update(&c, random, 20);
    SHA1_Update(&c, envelopmem, derLen);
    if(!bEncryptMetaData)
    {
      uint32 tag = 0xffffffff;
      SHA1_Update(&c, &tag, sizeof(uint32));
    }
    SHA1_Final(initmem,&c);
  } else { //len=32, which means AES-256
    SHA256_CTX c;
    SHA256_Init(&c);
    SHA256_Update(&c, random, 20);
    SHA256_Update(&c, envelopmem, derLen);
    if(!bEncryptMetaData)
    {
      uint32 tag = 0xffffffff;
      SHA256_Update(&c, &tag, sizeof(uint32));
    }
    SHA256_Final(initmem,&c);
  }

  uint8* tinitialKey = new uint8[len + 1];
  memset(tinitialKey, 0, len + 1);
  memcpy(tinitialKey, initmem, len);
  initialKey = String((const char*)tinitialKey, len);
  delete[] tinitialKey;
  delete[] initmem;

  String envelopesTmp((const char*)envelopmem, derLen);
  envelopes.Add(envelopesTmp);
  free(der);
  free(pbData);
  X509_free(x509_Cert);
  return TRUE;
}

#define RELEASE_MEM               if (p12) PKCS12_free(p12); \
                                  if (pkey )EVP_PKEY_free(pkey); \
                                  if (x509) X509_free(x509); \
                                  if (ca) sk_free((struct stack_st*)ca); \
                                  if (p7bio) BIO_free_all(p7bio); \
                                  if (p7) PKCS7_free(p7);

bool GetDecryptionKeyFromClientData(const void* clientData, const void* envelopeBuf, uint32 envelopeLen, void*& keyBuf,
  uint32* keyLen) {
    if (!keyBuf && keyLen)
      *keyLen = 0;
    if (!clientData || !envelopeBuf || envelopeLen < 1 || !keyLen || (keyBuf && *keyLen < 1))
      return false;

    char* pfxFile = (char*)clientData;
    const char* password = "123456";
    // Initialize the environment of the openssl.
    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();

    // Open the certificate file.
    FILE* fp = NULL;
    if (!(fp = fopen(pfxFile, "rb")))
      return false;

    // Retain PKCS12 object from certificate file.
    PKCS12* p12 = d2i_PKCS12_fp(fp, NULL);
    fclose(fp);
    if (!p12)
      return false;

    // Retain pkey, X509 certificate, certificate chains.
    EVP_PKEY* pkey = NULL;
    X509* x509 = NULL;
    STACK_OF(X509)* ca = NULL;
    if (!PKCS12_parse(p12, password, &pkey, &x509, &ca)) {
      PKCS12_free(p12);
      return false;
    }

    PKCS7* p7 = d2i_PKCS7(NULL, (const unsigned char**)&envelopeBuf, envelopeLen);
    BIO* p7bio = PKCS7_dataDecode(p7, pkey, NULL, x509);
    if (!p7bio) {
      PKCS12_free(p12);
      PKCS7_free(p7);
      return false;
    }
    *keyLen = (int)BIO_ctrl_pending(p7bio);
    if (*keyLen <= 0) {
      RELEASE_MEM
      return false;
    }

    keyBuf = malloc(*keyLen);
    if (!keyBuf) {
      RELEASE_MEM
      return false;
    }

    *keyLen = BIO_read(p7bio, keyBuf, *keyLen);

    RELEASE_MEM
    return true;
}

class CertificateSecurityEvent : public CertificateSecurityCallback {
public:
  CertificateSecurityEvent(
    const char* filepath)
    : filepath_(filepath) {
  }

  virtual ~CertificateSecurityEvent() {}
  virtual void Release() {
    delete this;
  }
  virtual String GetDecryptionKey(const void* envelopeBuf, uint32 envelopeLen) {
    uint8* keyBuf = NULL;
    uint32 keyLen = 0;

    bool ret = GetDecryptionKeyFromClientData((void*)filepath_.c_str(), envelopeBuf, envelopeLen, (void* &)keyBuf, &keyLen);

    if (!ret)
      return "";
    String strKeyBuf = String((const char*)keyBuf, keyLen);
    free(keyBuf);
    return strKeyBuf;
  }

private:
  string filepath_;
};
#endif

bool CertificateSecurity(WString input_file) {
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return false;
    }

    // Do encryption.
    StringArray envelopes;
    String initial_key;
    WString cert_file_path = input_path + L"foxit.cer";
    if (!GetCertificateInfo((const char*)String::FromUnicode(cert_file_path), envelopes, initial_key, true, 16)) {
      printf("[Failed] Cannot get certificate information from %s\r\n", (const char*)String::FromUnicode(cert_file_path));
      return false;
    }
    CertificateSecurityHandler handler;
    CertificateEncryptData encrypt_data(true, SecurityHandler::e_CipherAES, envelopes);
    handler.Initialize(encrypt_data, initial_key);

    doc.SetSecurityHandler(handler);
    WString output_file = output_directory + L"certificate_encrypt.pdf";
    doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);

#if !defined(_WIN32) && !defined(_WIN64)
    // Do decryption.
    CertificateSecurityEvent* callback = new CertificateSecurityEvent((const char*)String::FromUnicode(input_path + L"foxit_all.pfx"));
    Library::RegisterSecurityCallback("Adobe.PubSec", callback);
#endif

    PDFDoc encrypted_doc(output_file);
    error_code = encrypted_doc.Load(NULL);
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(output_file), error_code);
      return false;
    }

    output_file = output_directory + L"certificate_decrypt.pdf";
    encrypted_doc.RemoveSecurity();
    encrypted_doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);

#if !defined(_WIN32) && !defined(_WIN64)
    Library::UnregisterSecurityCallback("Adobe.PubSec");
#endif
    } catch (const Exception& e) {
      cout << e.GetMessage() << endl;
      return false;
    }
    catch(...)
    {
      cout << "Unknown Exception" << endl;
      return false;
    }
    return true;
}

class DRMSecurityEvent : public DRMSecurityCallback {
public:
  DRMSecurityEvent(const char* file_id, const String& initialize_key)
    : file_id_(file_id)
    , initialize_key_(initialize_key) {}

  virtual ~DRMSecurityEvent() {}

  virtual void Release() {
    delete this;
  }
  virtual bool IsOwner(const PDFDoc& doc, const char* subFilter) {
    return TRUE;
  }
  virtual uint32 GetUserPermissions(const PDFDoc& doc, const char* subFilter) {
    return 0xFFFFFFFC;
  }
  virtual SecurityHandler::CipherType GetCipherType(const PDFDoc& doc, const char* subFilter) {
    return SecurityHandler::e_CipherAES;
  }
  virtual uint32 GetKeyLength(const PDFDoc& doc, const char* subFilter) {
    return 16;
  }
  virtual String GetFileID(const PDFDoc& doc, const char* subFilter) {
    return file_id_.c_str();
  }
  virtual String GetInitialKey(const PDFDoc& doc, const char* subFilter) {
    return initialize_key_;
  }

private:
  DRMSecurityEvent(const DRMSecurityEvent&);
  DRMSecurityEvent& operator=(const DRMSecurityEvent&);
  string file_id_;
  String initialize_key_;
};

bool FoxitDRMDecrypt(WString input_file) {
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return false;
    }

    // Do encryption.
    DRMSecurityHandler handler = DRMSecurityHandler();
    const char* file_id = "Simple-DRM-file-ID";
    String initialize_key = "Simple-DRM-initialize-key";
    DRMEncryptData encrypt_data(true, "Simple-DRM-filter", SecurityHandler::e_CipherAES, 16, true, 0xfffffffc);
    handler.Initialize(encrypt_data, file_id, initialize_key);
    doc.SetSecurityHandler(handler);

    WString output_file = output_directory + L"foxit_drm_encrypt.pdf";
    doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);

    // Do decryption.
    DRMSecurityEvent* callback = new DRMSecurityEvent(file_id, initialize_key);
    Library::RegisterSecurityCallback("FoxitDRM", callback);
    PDFDoc encrypted_doc(output_file);
    error_code = encrypted_doc.Load(NULL);
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(output_file), error_code);
      return false;
    }

    output_file = output_directory + L"foxit_drm_decrypt.pdf";

    encrypted_doc.RemoveSecurity();
    encrypted_doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);

    Library::UnregisterSecurityCallback("FoxitDRM");
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    return false;
  }
  catch(...)
  {
    cout << "Unknown Exception" << endl;
    return false;
  }
  return true;
}

class CustomSecurityEvent : public CustomSecurityCallback {
public:
  CustomSecurityEvent() {}

  virtual ~CustomSecurityEvent() {}

  virtual void Release() {
    delete this;
  }

  virtual void* CreateContext(const char* filter, const char* sub_filter, const char* encrypt_info) {
    return NULL;
  }

  virtual bool ReleaseContext(void* context) {
    return true;
  }

  virtual uint32 GetUserPermissions(const void* context, uint32 user_permission) {
    return 0xffffffc;
  }

  virtual bool IsOwner(const void* context) {
    return true;
  }
  virtual SecurityHandler::CipherType GetCipher(const void* context) {
    return SecurityHandler::e_CipherAES;
  }

  virtual String GetEncryptKey(const void* context) {
    return String("key");
  }

  virtual uint32 GetDecryptedSize(const void* context, uint32 data_size) {
    return data_size;
  }

  virtual void* StartDecryptor(const void* context, int obj_number, int gen_number) {
    return NULL;
  }

  virtual String DecryptData(const void* decryptor, const void* enc_data_buf, uint32 enc_data_length) {
    char* decrypted_data = (char*)malloc(enc_data_length);
    for (uint32 i = 0; i < enc_data_length; i++)
      ((char*)decrypted_data)[i] = ((char*)enc_data_buf)[i] + 1;
    String data = String(decrypted_data, enc_data_length);
    free(decrypted_data);
    return data;
  }

  virtual String FinishDecryptor(void* decryptor) {
    return "";
  }

  virtual uint32 GetEncryptedSize(const void* context, int obj_number, int gen_number, const void* src_buffer,
    uint32 src_length) {
      return src_length;
  }

  virtual bool EncryptData(const void* context, int obj_number, int gen_number, const void* src_buffer,
    uint32 src_length, void* dst_bufffer, uint32* dst_length) {
      for (uint32 i = 0; i < src_length; i++)
        ((char*)dst_bufffer)[i] = ((char*)src_buffer)[i] - 1;
      *dst_length = src_length;
      return true;
  }

private:
  CustomSecurityEvent(const CustomSecurityEvent&);
  CustomSecurityEvent& operator=(const CustomSecurityEvent&);
};

bool CustomSecurity(WString input_file) {
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return false;
    }

    // Do encryption.
    CustomSecurityEvent* callback = new CustomSecurityEvent();
    CustomSecurityHandler handler = CustomSecurityHandler();
    const char* encrypt_info = "Foxit simple demo custom security";
    CustomEncryptData encrypt_data(true, "Custom", "foxit-simple-demo");
    handler.Initialize(encrypt_data, callback, encrypt_info);
    doc.SetSecurityHandler(handler);
    WString output_file = output_directory + L"custom_encrypt.pdf";
    doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);

    // Do decryption.
    Library::RegisterSecurityCallback("Custom", callback);
    PDFDoc encrypted_doc(output_file);

    error_code = encrypted_doc.Load(NULL);
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(output_file), error_code);
      return false;
    }

    output_file = output_directory + L"custom_decrypt.pdf";
    encrypted_doc.RemoveSecurity();
    encrypted_doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);

    Library::UnregisterSecurityCallback("Custom");
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    return false;
  }
  catch(...)
  {
    cout << "Unknown Exception" << endl;
    return false;
  }
  return true;
}

class RMSSecrutiyCallback : public RMSSecurityCallback {
public:
  RMSSecrutiyCallback(const char* key)
    : key_(key) {}

  virtual ~RMSSecrutiyCallback(){};
  virtual void Release() {
    delete this;
  }
  virtual void* CreateContext(const char* filter, const char* subFilter, const char* encryptInfo) {
    return NULL;
  }
  virtual bool ReleaseContext(void* context) {
    return TRUE;
  }
  virtual uint32 GetUserPermissions(const void* context, uint32 userPermission) {
    return 0xffffffc;
  }
  virtual bool IsOwner(const void* context) {
    return TRUE;
  }
  virtual SecurityHandler::CipherType GetCipher(const void* context) {
    return SecurityHandler::e_CipherAES;
  }
  virtual String GetEncryptKey(const void* context) {
    return key_;
  }
  virtual uint32 GetDecryptedSize(const void* context, uint32 dataSize) {
    return dataSize;
  }
  virtual void* StartDecryptor(const void* context, int objNum, int genNum) {
    return NULL;
  }
  virtual String DecryptData(const void* decryptor, const void* encDataBuf, uint32 encDataLen) {
    char* decryptedData = (char*)malloc(encDataLen);
    for (uint32 i = 0; i < encDataLen; i++)
      ((char*)decryptedData)[i] = ((char*)encDataBuf)[i] + 5;
    String data = String(decryptedData, encDataLen);
    free(decryptedData);
    return data;
  }
  virtual String FinishDecryptor(void* decryptor) {
    return "";
  }
  virtual uint32 GetEncryptedSize(const void* context, int objNum, int genNum, const void* srcBuf, uint32 srcLen) {
    return srcLen;
  }
  virtual bool EncryptData(const void* context, int objNum, int genNum, const void* srcBuf, uint32 srcLen, void* dstBuf,
    uint32* dstLen) {
      for (uint32 i = 0; i < srcLen; i++)
        ((char*)dstBuf)[i] = ((char*)srcBuf)[i] - 5;
      *dstLen = srcLen;
      return TRUE;
  }

private:
  String key_;
};

bool RMSSecurity(WString input_file) {
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return false;
    }

    // Do encryption.
    RMSSecrutiyCallback* callback = new RMSSecrutiyCallback("Simple-RMS-encrpty-key");
    RMSSecurityHandler handler;
    foxit::StringArray server_eul_list;
    server_eul_list.Add("WM-1");
    server_eul_list.Add("This document has been encrypted by RMS encryption.");
    server_eul_list.Add("WM-2");
    server_eul_list.Add("Just for simple demo rms security.");
    RMSEncryptData encrypt_data(true, "PubishLicense_0123", server_eul_list, 1);
    handler.Initialize(encrypt_data, callback);
    doc.SetSecurityHandler(handler);
    WString output_file = output_directory + L"rms_encrypt.pdf";
    doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);

    // Do decryption.
    Library::RegisterSecurityCallback("MicrosoftIRMServices", callback);
    PDFDoc encrypted_doc(output_file);

    error_code = encrypted_doc.Load(NULL);
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(output_file), error_code);
      return false;
    }

    output_file = output_directory + L"rms_decrypt.pdf";
    encrypted_doc.RemoveSecurity();
    encrypted_doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);

    Library::UnregisterSecurityCallback("Simple-RMS-encrpty-key");
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    return false;
  }
  catch(...)
  {
    cout << "Unknown Exception" << endl;
    return false;
  }
  return true;
}

bool StdSecurity(WString input_file) {
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return false;
    }

    // Do encryption.
    StdSecurityHandler handler;
    StdEncryptData encrypt_data(true, 0xfffffffc, SecurityHandler::e_CipherAES, 16);
    handler.Initialize(encrypt_data, String("user"), String("owner"));
    doc.SetSecurityHandler(handler);

    WString output_file = output_directory + L"std_encrypt_userpwd[user]_ownerpwd[owner].pdf";
    doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);

    // Do decryption.
    PDFDoc encrypted_doc(output_file);
    error_code = encrypted_doc.Load("owner");
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(output_file), error_code);
      return false;
    }
    encrypted_doc.RemoveSecurity();
    output_file = output_directory + L"std_decrypt.pdf";
    encrypted_doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    return false;
  }
  catch(...)
  {
    cout << "Unknown Exception" << endl;
    return false;
  }
  return true;
}

bool SecurityImpl(WString pdf_file) {
  bool bIsOK = true;
  if (!CertificateSecurity(pdf_file)) {
    bIsOK = false;
  }
  if (!FoxitDRMDecrypt(pdf_file)) {
      bIsOK = false;
  }
  if (!CustomSecurity(pdf_file)) {
      bIsOK = false;
  }
  if (!RMSSecurity(pdf_file)) {
      bIsOK = false;
  }
  if (!StdSecurity(pdf_file)) {
      bIsOK = false;
  }

  return bIsOK;
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
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  if (!SecurityImpl(input_file)) {
    return 1;
  }

  printf("Security demo test.\r\n");
  return err_ret;
}
