/**
 * Copyright (C) 2003-2020, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It is not allowed to
 * distribute any parts of Foxit PDF SDK to third party or public without permission unless an agreement
 * is signed between Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file fs_security.h
 * @brief Header file for security related definitions and classes.
 */

#ifndef FS_SECURITY_H_
#define FS_SECURITY_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/**
 * @brief PDF namespace.
 */
namespace pdf {
// forward declaration
class CustomSecurityCallback;
class RMSSecurityCallback;

/**
 * Class @link SecurityHandler @endlink is the base class that represents a security hander used for encrypting PDF document.
 * It has following derived classes:
 * <ul>
 * <li> Class @link StdSecurityHandler @endlink is used for password encryption. </li>
 * <li> Class @link CertificateSecurityHandler @endlink is used for certificate encryption.</li>
 * <li> Class @link DRMSecurityHandler @endlink is used for DRM encryption.</li>
 * <li> Class @link CustomSecurityHandler @endlink is used for custom encryption.</li>
 * <li> Class @link RMSSecurityHandler @endlink is used for RMS encryption.</li>
 * </ul>
 * To set a security handler to a PDF document, please call function @link PDFDoc::SetSecurityHandler @endlink,
 * then the security handler will take effect in later saving process. To get the security handler
 * used for a PDF document, please call function @link PDFDoc::SetSecurityHandler @endlink.
 *
 * @see @link StdSecurityHandler @endlink
 * @see @link CertificateSecurityHandler @endlink
 * @see @link DRMSecurityHandler @endlink
 * @see @link CustomSecurityHandler @endlink
 * @see @link RMSSecurityHandler @endlink
 * @see @link PDFDoc @endlink
 */
class SecurityHandler : public Base {
 public:
  /**
   * @brief Enumeration for Encryption Algorithm.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _CipherType {
    /** @brief Not use encryption algorithm. */
    e_CipherNone = 0,
    /** @brief Use RC4 encryption algorithm, with the key length between 5 bytes and 16 bytes. */
    e_CipherRC4 = 1,
    /**
   @brief Use AES encryption algorithm, with the key length be 16 bytes (as AES-128) or
          32 bytes (as AES-256, only supported in PDF 2.0).
     */
    e_CipherAES = 2
  } CipherType;
  
  /** @brief Constructor. */
  SecurityHandler();
#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Constructor, with another security handler object.
   *
   * @param[in] other  Another security handler object.
   */
  SecurityHandler(const SecurityHandler& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit SecurityHandler(FS_HANDLE handle);

  /** @brief Destructor. */
  virtual ~SecurityHandler();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another security handler object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  SecurityHandler& operator = (const SecurityHandler& other);
#endif
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another security handler object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const SecurityHandler& other);
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another security handler object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const SecurityHandler& other);

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the encryption type of current security handler.
   *
   * @return The encryption type. If current security handler object does not represent any specified type of
   *         security handler, it would return @link PDFDoc::e_EncryptUnknown @endlink.
   */
  virtual PDFDoc::EncryptType GetSecurityType();

};

/** This class represents some data used for class @link StdSecurityHandler @endlink. */
class StdEncryptData FS_FINAL {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] is_encrypt_metadata  <b>true</b> means to encrypt metadata, and <b>false</b> means not to
   *                                 encrypt metadata.
   * @param[in] user_permissions     The user permissions. Please refer to values starting from
   *                                 @link PDFDoc::e_PermPrint @endlink and this should be one or combination of these values.
   * @param[in] cipher               Cipher type. Please refer to values starting from
   *                                 @link SecurityHandler::e_CipherRC4 @endlink and this should be one of these values except
   *                                 @link SecurityHandler::e_CipherNone @endlink.
   * @param[in] key_length           The key length, in bytes.
   *                                 <ul>
   *                                 <li>For @link SecurityHandler::e_CipherRC4 @endlink cipher,
   *                                     this value should be between 5 and 16. The preferred one should be 16.</li>
   *                                 <li>For @link SecurityHandler::e_CipherAES @endlink cipher,
   *                                     this value should be 16 (as AES-128) or
   *                                     32 (as AES-256, only supported in PDF 2.0).</li>
   *                                 </ul>
   */
  StdEncryptData(bool is_encrypt_metadata, uint32 user_permissions, SecurityHandler::CipherType cipher,
                 int key_length) {
    this->is_encrypt_metadata = is_encrypt_metadata;
    this->user_permissions = user_permissions;
    this->cipher = cipher;
    this->key_length = key_length;
  }

  /** @brief Constructor. */
  StdEncryptData()
      : is_encrypt_metadata(true)
      , user_permissions(0)
      , cipher(SecurityHandler::e_CipherNone)
      , key_length(0) {}

  /** @brief Destructor. */
  ~StdEncryptData() {}

  /**
   * @brief Constructor, with another standard encrypt data object.
   *
   * @param[in] other  Another standard encrypt data object.
   */
  StdEncryptData(const StdEncryptData& other) {
    is_encrypt_metadata = other.is_encrypt_metadata;
    user_permissions = other.user_permissions;
    cipher = other.cipher;
    key_length = other.key_length;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another standard encrypt data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  StdEncryptData& operator = (const StdEncryptData& other) {
    is_encrypt_metadata = other.is_encrypt_metadata;
    user_permissions = other.user_permissions;
    cipher = other.cipher;
    key_length = other.key_length;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another standard encrypt data object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const StdEncryptData& other) const {
    return (is_encrypt_metadata == other.is_encrypt_metadata &&
            user_permissions == other.user_permissions &&
            cipher == other.cipher &&
            key_length == other.key_length);
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another standard encrypt data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const StdEncryptData& other) const {
    return !(is_encrypt_metadata == other.is_encrypt_metadata &&
             user_permissions == other.user_permissions &&
             cipher == other.cipher &&
             key_length == other.key_length);
  }

  /**
   * @brief Set value.
   *
   * @param[in] is_encrypt_metadata  <b>true</b> means to encrypt metadata, and <b>false</b> means not to
   *                                 encrypt metadata.
   * @param[in] user_permissions     The user permissions. Please refer to values starting from
   *                                 @link PDFDoc::e_PermPrint @endlink and this should be one or combination of these values.
   * @param[in] cipher               Cipher type. Please refer to values starting from
   *                                 @link SecurityHandler::e_CipherRC4 @endlink and this should be one of these values except
   *                                 @link SecurityHandler::e_CipherNone @endlink.
   * @param[in] key_length           The key length, in bytes.
   *                                 <ul>
   *                                 <li>For @link SecurityHandler::e_CipherRC4 @endlink cipher,
   *                                     this value should be between 5 and 16. The preferred one should be 16.</li>
   *                                 <li>For @link SecurityHandler::e_CipherAES @endlink cipher,
   *                                     this value should be 16 (as AES-128) or
   *                                     32 (as AES-256, only supported in PDF 2.0).</li>
   *                                 </ul>
   *
   * @return None.
   */
  void Set(bool is_encrypt_metadata, uint32 user_permissions, SecurityHandler::CipherType cipher, int key_length) {
    this->is_encrypt_metadata = is_encrypt_metadata;
    this->user_permissions = user_permissions;
    this->cipher = cipher;
    this->key_length = key_length;
  }

  /**
   * @brief A boolean value to decide whether to encrypt metadata or not. <b>true</b> means to encrypt metadata,
   *        and <b>false</b> means not to encrypt metadata.
   */
  bool is_encrypt_metadata;
  /**
   * @brief The user permissions. Please refer to values starting from @link PDFDoc::e_PermPrint @endlink and
   *        this should be one or combination of these values.
   */
  uint32 user_permissions;
  /**
   * @brief Cipher type. Please refer to values starting from @link SecurityHandler::e_CipherRC4 @endlink and
   *        this should be one of these values except @link SecurityHandler::e_CipherNone @endlink
   */
  SecurityHandler::CipherType cipher;
  /**
   * @brief The key length, in bytes.
   *        <ul>
   *        <li>For @link SecurityHandler::e_CipherRC4 @endlink cipher,
   *            this value should be between 5 and 16. The preferred one should be 16.</li>
   *        <li>For @link SecurityHandler::e_CipherAES @endlink cipher,
   *            this value should be 16 (as AES-128) or 32 (as AES-256, only supported in PDF 2.0).</li>
   *        </ul>
   */
  int key_length;
};

/**
 * This class represents a standard security handler, used for password encryption.
 *
 * @see @link SecurityHandler @endlink
 */
class StdSecurityHandler FS_FINAL : public SecurityHandler {
 public:
  /**
   * @brief (Only for AES-256) Enumeration for modify flag used to decide which security data or password will be modified
   *        during encryption process
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _ModifyFlag {
    /** @brief If set, user permissions and "is encrypt metadata" values (which are defined in @link StdEncryptData @endlink) will be modified during encryption process. */
    e_ModifyPermission = 0x01,
    /** @brief If set, user password and owner password will be modified during encryption process. */
    e_ModifyUserPassword = 0x02,
    /** @brief If set, only owner password will be modified during encryption process. */
    e_ModifyOwnerPassword = 0x04
  } ModifyFlag;
  

  /** @brief Constructor. */
  StdSecurityHandler();
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] other  Parent class object.
   */
  explicit StdSecurityHandler(const foxit::pdf::SecurityHandler& other);

  /**
   * @brief (Not support AES-256) Initialize current standard security handler.
   *
   * @param[in] user_password        A user password, which is used to open the PDF document.
   *                                 This can be empty when parameter <i>owner_password</i> is not empty.
   * @param[in] owner_password       An owner password, which is used to take ownership of the PDF document.
   *                                 This can be empty when parameter <i>user_password</i> is not empty.
   * @param[in] encrypt_data         A standard encrypt data object. In the encryption data, cipher type should not be
   *                                 @link SecurityHandler::e_CipherNone @endlink, or @link SecurityHandler::e_CipherAES @endlink
   *                                 with key length 32 (that means not support AES-256).
   *                                 Please refer to comment of class @link StdEncryptData @endlink to ensure the validation of
   *                                 each member.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Initialize(const StdEncryptData& encrypt_data, const String& user_password, const String& owner_password);

  /**
   * @brief (Only for AES-256) Initialize current standard security handler.
   *
   * @param[in] user_password        A user password, which is used to open the PDF document.
   *                                 This can be empty when parameter <i>owner_password</i> is not empty.
   * @param[in] owner_password       An owner password, which is used to take ownership of the PDF document.
   *                                 This can be empty when parameter <i>user_password</i> is not empty.
   * @param[in] encrypt_data         A standard encrypt data object. In the encryption data, cipher type should be
   *                                 @link SecurityHandler::e_CipherAES @endlink and key length should be 32.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool InitializeW(const StdEncryptData& encrypt_data, const WString& user_password, const WString& owner_password);

  /**
   * @brief (Only for AES-256) Set modify flags to decide which security data or password will be modified during encryption process.
   *
   * @details Modify flags are useful only when a PDF document has been encrypted by AES-256 and current @link StdSecurityHandler @endlink object
   *          is to be used to modify some security data or password for this PDF document. For other case, these modify flags
   *          will be ignored during encryption process. Security data and passwords are set through function <i>StdSecurityHandler::InitializeW</i>.
   *          If this function has not been called by current @link StdSecurityHandler @endlink object, that means to
   *          modify all the security data and password by default.
   *
   * @param[in] modify_flags  Modify flags used to decide which security data or password will be modified during encryption process.
   *                          Please refer to values starting from @link StdSecurityHandler::e_ModifyPermission @endlink
   *                          and this should be one or combination of these values.
   *
   * @return None.
   */
  void SetAES256ModifyFlags(uint32 modify_flags);
};

/** This class represents some data used for class @link CertificateSecurityHandler @endlink. */
class CertificateEncryptData FS_FINAL {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] is_encrypt_metadata  <b>true</b> means to encrypt metadata, and <b>false</b> means not to encrypt metadata.
   * @param[in] cipher               Cipher type. Please refer to values starting from
   *                                 @link SecurityHandler::e_CipherRC4 @endlink and this should be one of these values except
   *                                 @link SecurityHandler::e_CipherNone @endlink.
   * @param[in] envelopes            A string array which specifies an array of certificate envelopes.
   *                                 This array should contains one or more envelopes.
   */
  CertificateEncryptData(bool is_encrypt_metadata, SecurityHandler::CipherType cipher, const StringArray& envelopes) {
    this->is_encrypt_metadata = is_encrypt_metadata;
    this->cipher = cipher;
    this->envelopes = envelopes;
  }

  /** @brief Constructor. */
  CertificateEncryptData()
    : is_encrypt_metadata(true)
    , cipher(SecurityHandler::e_CipherNone) {}

  /** @brief Destructor. */
  ~CertificateEncryptData() {}

  /**
   * @brief Constructor, with another certificate encrypt data object.
   *
   * @param[in] other  Another certificate encrypt data object.
   */
  CertificateEncryptData(const CertificateEncryptData& other) {
    is_encrypt_metadata = other.is_encrypt_metadata;
    cipher = other.cipher;
    envelopes = other.envelopes;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another certificate encrypt data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  CertificateEncryptData& operator = (const CertificateEncryptData& other) {
    is_encrypt_metadata = other.is_encrypt_metadata;
    cipher = other.cipher;
    envelopes = other.envelopes;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another certificate encrypt data object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const CertificateEncryptData& other) const {
    if (is_encrypt_metadata == other.is_encrypt_metadata && cipher == other.cipher) {
      if (envelopes.GetSize() == other.envelopes.GetSize()) {
        for (size_t i=0; i<envelopes.GetSize(); i++) {
          if (envelopes[i] != other.envelopes[i]) return false;
        }
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another certificate encrypt data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const CertificateEncryptData& other) const {
    if (!(is_encrypt_metadata == other.is_encrypt_metadata && cipher == other.cipher)) {
      if (envelopes.GetSize() == other.envelopes.GetSize()) {
        if (envelopes.GetSize() == 0) return false;
        for (size_t i=0; i<envelopes.GetSize(); i++) {
          if (envelopes[i] == other.envelopes[i]) return false;
        }
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Set value.
   *
   * @param[in] is_encrypt_metadata  <b>true</b> means to encrypt metadata, and <b>false</b> means not to encrypt metadata.
   * @param[in] cipher               Cipher type. Please refer to values starting from
   *                                 @link SecurityHandler::e_CipherRC4 @endlink and this should be one of these values except
   *                                 @link SecurityHandler::e_CipherNone @endlink.
   * @param[in] envelopes            A string array which specifies an array of certificate envelopes.
   *                                 This array should contains one or more envelopes.
   *
   * @return None.
   */
  void Set(bool is_encrypt_metadata, SecurityHandler::CipherType cipher, const StringArray& envelopes) {
    this->is_encrypt_metadata = is_encrypt_metadata;
    this->cipher = cipher;
    this->envelopes =envelopes;
  }

  /**
   * @brief A boolean value to decide whether to encrypt metadata or not. <b>true</b> means to encrypt metadata,
   *        and <b>false</b> means not to encrypt metadata.
   */
  bool is_encrypt_metadata;
  /**
   * @brief Cipher type. Please refer to values starting from @link SecurityHandler::e_CipherRC4 @endlink and
   *        this should be one of these values except @link SecurityHandler::e_CipherNone @endlink.
   */
  SecurityHandler::CipherType cipher;
  /**
   * @brief A string array which specifies an array of certificate envelopes.
   *        This array should contains one or more envelopes.
   */
  StringArray envelopes;
};

#if (_FX_OS_ == _FX_IOS_ || _FX_OS_ == _FX_ANDROID_ || defined(SWIG)) && !defined(_SWIG_JAVA_) && !defined(_SWIG_DOTNET_) && !defined(_OC_) && !defined(_SWIG_MACOC_)
/** This class represents data of an envelope which would be used in certificate encryption. */
class Envelope : public Base {
 public:
  /**
   * @brief Constructor, from a buffer of envelope data which represents PKCS#12 in binary.
   *
   * @param[in] buffer  A buffer of envelope data which represents PKCS#12 in binary.
   * @param[in] size    The size of the buffer.
   */
  Envelope(const void* buffer, size_t size);
  /**
   * @brief Constructor, from an existing certificate file path.
   *
   * @param[in] certFilePath  A full path of an existing certificate file(.cer file). It should not be an empty string.
   */
  Envelope(const char* certFilePath);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Envelope(FS_HANDLE handle);
  /** @brief Constructor, with another envelope object. */
  Envelope(const Envelope& other);
  /** @brief Equal operator. */
  bool operator==(const Envelope& other) const;
  /** @brief Not equal operator. */
  bool operator!=(const Envelope& other) const;

  /**
   * @brief Get the decryption key
   *
   * @param[in] p12FilePath  A full path of a .p12 file. It should not be an empty string.
   * @param[in] password     The password string for .p12 file.
   *
   * @return The decryption key.
   */
  String GetDecryptionKey(const char* p12FilePath, const String& password);

};

/** @brief An array of envelope objects. */
typedef CFX_ArrayTemplate<Envelope> EnvelopeArray;

#endif

/**
 * This class represents a certificate security handler, used for certificate encryption.
 *
 * @see @link SecurityHandler @endlink
 */
class CertificateSecurityHandler FS_FINAL : public SecurityHandler {
 public:
  /** @brief Constructor. */
  CertificateSecurityHandler();
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] other  Parent class object.
   */
  explicit CertificateSecurityHandler(const foxit::pdf::SecurityHandler& other);

#if (_FX_OS_ == _FX_IOS_ || _FX_OS_ == _FX_ANDROID_ || defined(SWIG)) && !defined(_SWIG_JAVA_) && !defined(_SWIG_DOTNET_) && !defined(_OC_) && !defined(_SWIG_MACOC_)
  /**
   * @brief Initialize current certificate security handler.
   *
   * @param[in] envelopes            An array of envelopes.
   * @param[in] cipher               Cipher type. Please refer to values starting from
   *                                 @link SecurityHandler::e_CipherRC4 @endlink and this should be one of these values except
   *                                 @link SecurityHandler::e_CipherNone @endlink.
   * @param[in] is_encrypt_metadata  <b>true</b> means to encrypt metadata, and <b>false</b> means not to
   *                                 encrypt metadata.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Initialize(foxit::pdf::EnvelopeArray envelopes, foxit::pdf::SecurityHandler::CipherType cipher, bool is_encrypt_metadata);
#endif  // (_FX_OS_ == _FX_IOS_ || _FX_OS_ == _FX_ANDROID_ || defined(SWIG)) && !defined(_SWIG_JAVA_) && !defined(_SWIG_DOTNET_) && !defined(_OC_) && !defined(_SWIG_MACOC_)

  /**
   * @brief Initialize current certificate security handler.
   *
   * @param[in] encrypt_data  A certificate encrypt data object. In the encryption data, cipher type should not be
   *                          @link SecurityHandler::e_CipherNone @endlink.
   * @param[in] encrypt_key   The key for encryption.<br>
   *                          For @link SecurityHandler::e_CipherRC4 @endlink cipher, the length of
   *                          encryption key should be between 5 and 16.
   *                          For @link SecurityHandler::e_CipherAES @endlink cipher, the length of
   *                          encryption key should be 16 or 32.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Initialize(const CertificateEncryptData& encrypt_data, const String& encrypt_key);
};

/** This class represents some data used for class @link DRMSecurityHandler @endlink. */
class DRMEncryptData FS_FINAL {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] is_encrypt_metadata  <b>true</b> means to encrypt metadata, and <b>false</b> means not to
   *                                 encrypt metadata
   * @param[in] sub_filter           The sub filter name that specifies the syntax of the encryption dictionary contents.
   * @param[in] cipher               Cipher type. Please refer to values starting from
   *                                 @link SecurityHandler::e_CipherRC4 @endlink and this should be one of these values except
   *                                 @link SecurityHandler::e_CipherNone @endlink.
   * @param[in] key_length           The key length, in bytes.<br>
   *                                 For @link SecurityHandler::e_CipherRC4 @endlink cipher,
   *                                 this value should be between 5 and 16.<br>
   *                                 For @link SecurityHandler::e_CipherAES @endlink cipher,
   *                                 this value should be 16 or 32.
   * @param[in] is_owner             <b>true</b> means current user is owner, and <b>false</b> means current user
   *                                 is not owner.
   * @param[in] user_permissions     The user permissions. Please refer to values starting from
   *                                 @link PDFDoc::e_PermPrint @endlink and this can be one or combination of these values.
   */
  DRMEncryptData(bool is_encrypt_metadata, const String& sub_filter, SecurityHandler::CipherType cipher,
    int key_length, bool is_owner, uint32 user_permissions) {
      this->is_encrypt_metadata = is_encrypt_metadata;
      this->sub_filter = sub_filter;
      this->cipher = cipher;
      this->key_length = key_length;
      this->is_owner = is_owner;
      this->user_permissions = user_permissions;
  }

  /** @brief Constructor. */
  DRMEncryptData()
    : is_encrypt_metadata(true)
    , sub_filter("")
    , cipher(SecurityHandler::e_CipherNone)
    , key_length(0)
    , is_owner(false)
    , user_permissions(0) {}

  /** @brief Destructor. */
  ~DRMEncryptData() {}

  /**
   * @brief Constructor, with another DRM encrypt data object.
   *
   * @param[in] other  Another DRM encrypt data object.
   */
  DRMEncryptData(const DRMEncryptData& other) {
    is_encrypt_metadata = other.is_encrypt_metadata;
    sub_filter = other.sub_filter;
    cipher = other.cipher;
    key_length = other.key_length;
    is_owner = other.is_owner;
    user_permissions = other.user_permissions;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another DRM encrypt data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  DRMEncryptData& operator = (const DRMEncryptData& other) {
    is_encrypt_metadata = other.is_encrypt_metadata;
    sub_filter = other.sub_filter;
    cipher = other.cipher;
    key_length = other.key_length;
    is_owner = other.is_owner;
    user_permissions = other.user_permissions;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another DRM encrypt data object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const DRMEncryptData& other) const {
    return (is_encrypt_metadata == other.is_encrypt_metadata &&
      sub_filter == other.sub_filter &&
      cipher == other.cipher && key_length == other.key_length &&
      is_owner == other.is_owner &&
      user_permissions == other.user_permissions);
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another DRM encrypt data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const DRMEncryptData& other) const {
    return !(is_encrypt_metadata == other.is_encrypt_metadata &&
      sub_filter == other.sub_filter &&
      cipher == other.cipher && key_length == other.key_length &&
      is_owner == other.is_owner &&
      user_permissions == other.user_permissions);
  }

  /**
   * @brief Set value.
   *
   * @param[in] is_encrypt_metadata  <b>true</b> means to encrypt metadata, and <b>false</b> means not to
   *                                 encrypt metadata
   * @param[in] sub_filter           The sub filter name that specifies the syntax of the encryption dictionary contents.
   * @param[in] cipher               Cipher type. Please refer to values starting from
   *                                 @link SecurityHandler::e_CipherRC4 @endlink and this should be one of these values except
   *                                 @link SecurityHandler::e_CipherNone @endlink.
   * @param[in] key_length           The key length, in bytes.<br>
   *                                 For @link SecurityHandler::e_CipherRC4 @endlink cipher,
   *                                 this value should be between 5 and 16.<br>
   *                                 For @link SecurityHandler::e_CipherAES @endlink cipher,
   *                                 this value should be 16 or 32.
   * @param[in] is_owner             <b>true</b> means current user is owner, and <b>false</b> means current user
   *                                 is not owner.
   * @param[in] user_permissions     The user permissions. Please refer to values starting from
   *                                 @link PDFDoc::e_PermPrint @endlink and this can be one or combination of these values.
   *
   * @return None.
   */
  void Set(bool is_encrypt_metadata, const String& sub_filter, SecurityHandler::CipherType cipher,
    int key_length, bool is_owner, uint32 user_permissions) {
      this->is_encrypt_metadata = is_encrypt_metadata;
      this->sub_filter = sub_filter;
      this->cipher = cipher;
      this->key_length = key_length;
      this->is_owner = is_owner;
      this->user_permissions = user_permissions;
  }

  /**
   * @brief A boolean value to decide whether to encrypt metadata or not. <b>true</b> means to encrypt metadata,
   *        and <b>false</b> means not to encrypt metadata.
   */
  bool is_encrypt_metadata;
  /** @brief The sub filter name that specifies the syntax of the encryption dictionary contents.*/
  String sub_filter;
  /**
   * @brief Cipher type. Please refer to values starting from @link SecurityHandler::e_CipherRC4 @endlink and
   *        this should be one of these values except @link SecurityHandler::e_CipherNone @endlink.
   */
  SecurityHandler::CipherType cipher;
  /** @brief The key length, in bytes.<br>
   *         For @link SecurityHandler::e_CipherRC4 @endlink cipher, this value should
   *         be between 5 and 16.<br>
   *         For @link SecurityHandler::e_CipherAES @endlink cipher, this value should
   *         be 16 or 32.
   */
  int key_length;
  /**
   * @brief A boolean value to decide whether current user is owner or not. <b>true</b> means current user is owner,
   *        and <b>false</b> means current user is not owner.
   */
  bool is_owner;
  /**
   * @brief The user permissions. Please refer to values starting from @link PDFDoc::e_PermPrint @endlink and
   *        this can be one or combination of these values.
   */
  uint32 user_permissions;
};

/**
 * This class represents a Foxit DRM(Digital Right Management) security handler, used for Foxit DRM encryption.
 *
 * @see @link SecurityHandler @endlink
 */
class DRMSecurityHandler FS_FINAL : public SecurityHandler {
 public:
  /** @brief Constructor function. */
  DRMSecurityHandler();
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] other  Parent class object.
   */
  explicit DRMSecurityHandler(const foxit::pdf::SecurityHandler& other);

  /**
   * @brief Initialize current DRM security handler.
   *
   * @param[in] encrypt_data  A certificate encrypt data object. In the encryption data, cipher type should not be
   *                          @link SecurityHandler::e_CipherNone @endlink.
   * @param[in] file_id       The file identity string.
   * @param[in] initial_key   The user specified initial key for encryption.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Initialize(const DRMEncryptData& encrypt_data, const char* file_id, const String& initial_key);
  /**
   * @brief Get the DRM value for a specified parameter.
   *
   * @param[in] key  A parameter string as the key name. It should not be an empty string.
   *                 Followings are pre-defined key names:
   *                 <ul>
   *                 <li>Issuer: issuer name.</li>
   *                 <li>Creator: creator of this file.</li>
   *                 <li>FileID: file ID.</li>
   *                 <li>FlowCode: flow code for application control.</li>
   *                 <li>Order: order number.</li>
   *                 <li>User: user name.</li>
   *                 <li>ServiceURL: service URL for remote server.</li>
   *                 <li>Vender: vender name.</li>
   *                 </ul>
   *
   * @return The value string for a specified parameter.
   */
  WString GetDRMValue(const char* key);
  /**
   * @brief Set the DRM value for a specified parameter.
   *
   * @param[in] key    A parameter string as the key name. It should not be an empty string.
   *                   Followings are pre-defined key names:
   *                   <ul>
   *                   <li>Issuer: issuer name.</li>
   *                   <li>Creator: creator of this file.</li>
   *                   <li>FileID: file ID.</li>
   *                   <li>FlowCode: flow code for application control.</li>
   *                   <li>Order: order number.</li>
   *                   <li>User: user name.</li>
   *                   <li>ServiceURL: service URL for remote server.</li>
   *                   <li>Vender: vender name.</li>
   *                   </ul>
   * @param[in] value  New value string for specified parameter.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetDRMValue(const char* key, const WString& value);

  /**
   * @brief Verify encryption parameters.
   *
   * @details Foxit DRM maintains a set of encryption parameters for application purpose.
   *          Encryption parameters are stored in PDF file and protected by verification algorithm.
   *          So application can call this function to verify a DRM encrypted PDF document.
   *          If the verification is failed, that means the PDF document might be distorted.
   *
   * @return <b>true</b> means the verification is successful, while <b>false</b> means the verification is failed.
   */
  bool VerifyEncryptionParams();
};

/** This class represents some data used for class @link CustomSecurityHandler @endlink. */
class CustomEncryptData FS_FINAL {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] is_encrypt_metadata  <b>true</b> means to encrypt metadata, and <b>false</b> means not to
   *                                 encrypt metadata.
   * @param[in] filter               The filter name of a custom security callback object. It should not be an empty string.
   * @param[in] sub_filter           The sub filter name that specifies the syntax of the encryption dictionary contents. It should not be an empty string.
   */
  CustomEncryptData(bool is_encrypt_metadata, const String& filter, const String& sub_filter) {
    this->is_encrypt_metadata = is_encrypt_metadata;
    this->filter = filter;
    this->sub_filter = sub_filter;
  }

  /** @brief Constructor. */
  CustomEncryptData()
    : is_encrypt_metadata(true)
    , filter("")
    , sub_filter("") {}

  /** @brief Destructor. */
  ~CustomEncryptData() {};

  /**
   * @brief Constructor, with another custom encrypt data object.
   *
   * @param[in] other  Another custom encrypt data object.
   */
  CustomEncryptData(const CustomEncryptData& other) {
    is_encrypt_metadata = other.is_encrypt_metadata;
    filter = other.filter;
    sub_filter = other.sub_filter;
  }
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another custom encrypt data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  CustomEncryptData& operator = (const CustomEncryptData& other) {
    is_encrypt_metadata = other.is_encrypt_metadata;
    filter = other.filter;
    sub_filter = other.sub_filter;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another custom encrypt data object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const CustomEncryptData& other) const {
    return (is_encrypt_metadata == other.is_encrypt_metadata &&
      filter == other.filter && sub_filter == other.sub_filter);
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another custom encrypt data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const CustomEncryptData& other) const {
    return !(is_encrypt_metadata == other.is_encrypt_metadata &&
      filter == other.filter && sub_filter == other.sub_filter);
  }
  /**
   * @brief Set value.
   *
   * @param[in] is_encrypt_metadata  <b>true</b> means to encrypt metadata, and <b>false</b> means not to
   *                                 encrypt metadata.
   * @param[in] filter               The filter name of a custom security callback object. It should not be an empty string.
   * @param[in] sub_filter           The sub filter name that specifies the syntax of the encryption dictionary contents. It should not be an empty string.
   *
   * @return None.
   */
  void Set(bool is_encrypt_metadata, const String& filter, const String& sub_filter) {
    this->is_encrypt_metadata = is_encrypt_metadata;
    this->filter = filter;
    this->sub_filter = sub_filter;
  }

  /**
   * @brief A boolean value to decide whether to encrypt metadata or not. <b>true</b> means to encrypt metadata,
   *        and <b>false</b> means not to encrypt metadata.
   */
  bool is_encrypt_metadata;
  /** @brief The filter name of a custom security callback object. It should not be an empty string. */
  String filter;
  /** @brief The sub filter name that specifies the syntax of the encryption dictionary contents. It should not be an empty string. */
  String sub_filter;
};

/**
 * This class represents a custom security handler, used for custom encryption.
 *
 * @see @link SecurityHandler @endlink
 */
class CustomSecurityHandler FS_FINAL : public SecurityHandler {
 public:
  /** @brief Constructor. */
  CustomSecurityHandler();
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] other  Parent class object.
   */
  explicit CustomSecurityHandler(const foxit::pdf::SecurityHandler& other);

  /**
   * @brief Initialize current custom security handler.
   *
   * @details If this function is successfully, Foxit PDF SDK will take over the input security callback object and
   *          user should not release this callback object directly anymore; otherwise unexpected crash may occurs
   *          later.<br>
   *          Foxit PDF SDK may release the security callback object by callback function
   *          @link SecurityCallback::Release @endlink, when current security handler is released and find that
   *          the callback object has not been used by other object. So, user is recommended not to use
   *          the security callback object any more, after current security handler is released.
   *
   * @param[in] encrypt_data  A custom encrypt data object.
   * @param[in] callback      A valid @link CustomSecurityCallback @endlink object, which is inherited and implemented
   *                          by user for their own encryption and description algorithm.
   *                          It should not be <b>NULL</b>.
   * @param[in] encrypt_info  The encryption information,which will be stored to document encryption dictionary.
   *                          This can be an empty string. Default value: an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Initialize(const CustomEncryptData& encrypt_data,
                  const CustomSecurityCallback * callback, const char* encrypt_info = "");
};

/** This class represents some data used for class @link RMSSecurityHandler @endlink. */
class RMSEncryptData FS_FINAL {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] is_encrypt_metadata  <b>true</b> means to encrypt metadata, and <b>false</b> means not to
   *                                 encrypt metadata.
   * @param[in] publish_license      The Encoded Publishing License issued from server to the Content publisher,
   *                                 in ASCII encoding. This should not be an empty string.<br>
   *                                 This field contains the publishing license from Microsoft IRM services or
   *                                 a comparable IRM service. The original data of Publishing License should be
   *                                 compressed by Flate compression algorithm at first, and then encoded
   *                                 by Base-64 Encryption algorithm. Foxit PDF SDK offers functions in
   *                                 class @link common::Codec @endlink for Flate compression algorithm and
   *                                 Base-64 Encryption algorithm. Please refer to class @link common::Codec @endlink
   *                                 if necessary.
   * @param[in] server_eul_list      In this string array, the count of strings should be multiply of 2.
   *                                 2 strings are in a pair, and each pair represents content of a dictionary object
   *                                 which is encoded Server EUL.<br>
   *                                 For each pair, the first string is ServerID, and the second one is ServerEUL.
   *                                 The original data of Server ID and Server EUL should be compressed
   *                                 by Flate compression algorithm at first, and then encoded by
   *                                 Base-64 Encryption algorithm. Foxit PDF SDK offers functions in
   *                                 class @link common::Codec @endlink for Flate compression algorithm and
   *                                 Base-64 Encryption algorithm. Please refer to class @link common::Codec @endlink
   *                                 if necessary.<br>
   *                                 An empty array means not use such information.
   * @param[in] irm_version          Microsoft IRM version. It should be above 1. If input version is below 1,
   *                                 Foxit PDF SDK will use 1 as version by default. Default value: 1.0.
   */
  RMSEncryptData(bool is_encrypt_metadata, const char* publish_license, const StringArray& server_eul_list,
                 float irm_version = 1.0) {
    this->is_encrypt_metadata = is_encrypt_metadata;
    this->publish_license = publish_license;
    this->server_eul_list = server_eul_list;
    if (irm_version<1.0)
      this->irm_version = 1.0;
    else
      this->irm_version = irm_version;
  }

  /** @brief Constructor. */
  RMSEncryptData()
    : is_encrypt_metadata(true)
    , publish_license("")
    , irm_version(1.0) {}

  /** @brief Destructor. */
  ~RMSEncryptData() {}

  /**
   * @brief Constructor, with another RMS encrypt data object.
   *
   * @param[in] other  Another RMS encrypt data object.
   */
  RMSEncryptData(const RMSEncryptData& other) {
    is_encrypt_metadata = other.is_encrypt_metadata;
    publish_license = other.publish_license;
    server_eul_list = other.server_eul_list;
    irm_version = other.irm_version;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another RMS encrypt data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  RMSEncryptData& operator = (const RMSEncryptData& other) {
    is_encrypt_metadata = other.is_encrypt_metadata;
    publish_license = other.publish_license;
    server_eul_list = other.server_eul_list;
    irm_version = other.irm_version;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another RMS encrypt data object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const RMSEncryptData& other) const {
    if (is_encrypt_metadata == other.is_encrypt_metadata && publish_license == other.publish_license &&
        fabs(irm_version - other.irm_version) <= FLT_EPSILON) {
      if (server_eul_list.GetSize() == other.server_eul_list.GetSize()) {
        for (size_t i=0; i<server_eul_list.GetSize(); i++) {
          if (server_eul_list[i] != other.server_eul_list[i]) return false;
        }
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another RMS encrypt data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const RMSEncryptData& other) const {
    if (!(is_encrypt_metadata == other.is_encrypt_metadata && publish_license == other.publish_license &&
        fabs(irm_version - other.irm_version) <= FLT_EPSILON)) {
      if (server_eul_list.GetSize() == other.server_eul_list.GetSize()) {
        if (server_eul_list.GetSize() == 0) return false;
        for (size_t i=0; i<server_eul_list.GetSize(); i++) {
          if (server_eul_list[i] == other.server_eul_list[i]) return false;
        }
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Set value.
   *
   * @param[in] is_encrypt_metadata  <b>true</b> means to encrypt metadata, and <b>false</b> means not to
   *                                 encrypt metadata.
   * @param[in] publish_license      The Encoded Publishing License issued from server to the Content publisher,
   *                                 in ASCII encoding. This should not be an empty string.<br>
   *                                 This field contains the publishing license from Microsoft IRM services or
   *                                 a comparable IRM service. The original data of Publishing License should be
   *                                 compressed by Flate compression algorithm at first, and then encoded
   *                                 by Base-64 Encryption algorithm. Foxit PDF SDK offers functions in
   *                                 class @link common::Codec @endlink for Flate compression algorithm and
   *                                 Base-64 Encryption algorithm. Please refer to class @link common::Codec @endlink
   *                                 if necessary.
   * @param[in] server_eul_list      In this string array, the count of strings should be multiply of 2.
   *                                 2 strings are in a pair, and each pair represents content of a dictionary object
   *                                 which is encoded Server EUL.<br>
   *                                 For each pair, the first string is ServerID, and the second one is ServerEUL.
   *                                 The original data of Server ID and Server EUL should be compressed
   *                                 by Flate compression algorithm at first, and then encoded by
   *                                 Base-64 Encryption algorithm. Foxit PDF SDK offers functions in
   *                                 class @link common::Codec @endlink for Flate compression algorithm and
   *                                 Base-64 Encryption algorithm. Please refer to class @link common::Codec @endlink
   *                                 if necessary.<br>
   *                                 An empty array means not use such information.
   * @param[in] irm_version          Microsoft IRM version. It should be above 1. If input version is below 1,
   *                                 Foxit PDF SDK will use 1 as version by default. Default value: 1.0.
   *
   * @return None.
   */
  void Set(bool is_encrypt_metadata, const char* publish_license, const StringArray& server_eul_list,
           float irm_version = 1.0) {
    this->is_encrypt_metadata = is_encrypt_metadata;
    this->publish_license = publish_license;
    this->server_eul_list = server_eul_list;
    if (irm_version<1.0)
      this->irm_version = 1.0;
    else
      this->irm_version = irm_version;
  }

  /**
   * @brief A boolean value to decide whether to encrypt metadata or not. <b>true</b> means to encrypt metadata,
   *        and <b>false</b> means not to encrypt metadata.
   */
  bool is_encrypt_metadata;
  /**
   * @brief The Encoded Publishing License issued from server to the Content publisher, in ASCII encoding.
   *        This should not be an empty string.
   *
   * @details This field contains the publishing license from Microsoft IRM services or a comparable IRM service.
   *          The original data of Publishing License should be compressed by Flate compression algorithm at first,
   *          and then encoded by Base-64 Encryption algorithm. Foxit PDF SDK offers functions in class @link common::Codec @endlink
   *          for Flate compression algorithm and Base-64 Encryption algorithm.
   *          Please refer to class @link common::Codec @endlink if necessary.
   */
  String publish_license;
  /**
   * @brief A string array that contains pairs of strings to represent content of a dictionary object
   *        which is encoded Server EUL.
   *
   * @details In this string array, the count of strings should be multiply of 2. 2 strings are in a pair,
   *          and each pair represents content of a dictionary object which is encoded Server EUL.<br>
   *          For each pair, the first string is ServerID, and the second one is ServerEUL. The original data of
   *          Server ID and Server EUL should be compressed by Flate compression algorithm at first, and then encoded
   *          by Base-64 Encryption algorithm. Foxit PDF SDK offers functions in class @link common::Codec @endlink for
   *          Flate compression algorithm and Base-64 Encryption algorithm.Please refer to class @link common::Codec @endlink
   *          if necessary.<br>
   *          An empty array means not use such information.
   */
  StringArray server_eul_list;
  /**
   * @brief Microsoft IRM version. It should be above 1. If input version is below 1,
   *        Foxit PDF SDK will use 1 as version by default. Default value: 1.0.
   */
  float irm_version;
};

/**
 * This class represents a RMS security handler, used for RMS encryption.
 *
 * @note If module "RMS" is not defined in the license information which is used in function
 *       @link common::Library::Initialize @endlink, that means user has no right in using RMS related functions and
 *       valid RMS security handler would not be constructed successfully and exception
 *       @link foxit::e_ErrNoRMSModuleRight @endlink would be thrown.
 *
 * @see @link SecurityHandler @endlink
 */
class RMSSecurityHandler FS_FINAL : public SecurityHandler {
 public:
  /**
   * @brief Constructor.
   *
   * @note If module "RMS" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using RMS related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoRMSModuleRight @endlink.
   */
  RMSSecurityHandler();
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] other  Parent class object.
   *
   * @note If module "RMS" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using RMS related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoRMSModuleRight @endlink.
   */
  explicit RMSSecurityHandler(const foxit::pdf::SecurityHandler& other);

  /**
   * @brief Initialize current Microsoft RMS security handler.
   *
   * @details If this function is successfully, Foxit PDF SDK will take over the input security callback object and
   *          user should not release this callback object directly anymore; otherwise unexpected crash may occurs
   *          later.<br>
   *          Foxit PDF SDK may release the security callback object by callback function
   *          @link SecurityCallback::Release @endlink (inherited from RMSSecurityCallback's parent class),
   *          when current security handler is released and find that the callback object has not
   *          been used by other object. So, user is recommended not to use the security callback object any more,
   *          after current security handler is released.
   *
   * @param[in] encrypt_data  An RMS encrypt data object.
   * @param[in] callback      A valid @link RMSSecurityCallback @endlink object, which is inherited and implemented by user
   *                          for their own encryption and description algorithm. It should not be <b>NULL</b>.
   *
   * @return
   */
  bool Initialize(const RMSEncryptData& encrypt_data, const RMSSecurityCallback* callback);
};

/**
 * This is just the base class for other concrete security callback object. User should not inherit this class directly
 * when implementing a security callback for any type of decryption and encryption. User should inherit
 * any derived callback class of this base class.
 */
class SecurityCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;
  /**
   * @brief Get the encryption type of security callback.
   *
   * @return The encryption type. If current callback object does not represent any specified type of
   *         security callback, it would return @link PDFDoc::e_EncryptUnknown @endlink.
   */
  virtual PDFDoc::EncryptType GetSecurityType() {return PDFDoc::e_EncryptUnknown;}

 protected:
  ~SecurityCallback() {}
};

/**
 * This class represents a callback object for certificate decryption. If user wants to use their own
 * certificate security callback, user should inherit this callback class and implement the pure virtual functions
 * (as callback functions), and then register their own certificate security callback object to Foxit PDF SDK
 * by function @link common::Library::RegisterSecurityCallback @endlink with <i>filter</i> "Adobe.PubSec".
 * Function @link common::Library::UnregisterSecurityCallback @endlink can be called to unregister the security
 * callback object with the registered filter name.
 */
class CertificateSecurityCallback: public SecurityCallback {
 public:
  /**
   * @brief Get the encryption type of current security callback.
   *
   * @note User should not override this function, otherwise there will be unexpected behavior.
   *
   * @return The encryption type. It would always be @link PDFDoc::e_EncryptCertificate @endlink.
   */
  virtual PDFDoc::EncryptType GetSecurityType() FS_OVERRIDE {return PDFDoc::e_EncryptCertificate;}
  /**
   * @brief A callback function used to get the key for decrypting certificate protected PDF document.
   *
   * @param[in] envelope_buffer  A buffer which represents a certificate envelope.
   * @param[in] envelope_length  Length of certificate envelope buffer, in bytes.
   *
   * @note User should implement this callback function.
   *
   * @return The decryption key.
   */
  virtual String GetDecryptionKey(const void* envelope_buffer, uint32 envelope_length) = 0;

 protected:
  ~CertificateSecurityCallback() {}
};

/**
 * This class represents a callback object for Foxit DRM decryption. If user wants to use
 * their own Foxit DRM security callback, user should inherit this callback class and implement
 * the pure virtual functions (as callback functions), and then register their own Foxit DRM security callback object
 * to Foxit PDF SDK by function @link common::Library::RegisterSecurityCallback @endlink with <i>filter</i> "FoxitDRM".
 * Function @link common::Library::UnregisterSecurityCallback @endlink can be called to unregister the security callback object
 * with the registered filter name.
 */
class DRMSecurityCallback: public SecurityCallback {
 public:
  /**
   * @brief Get the encryption type of security callback.
   *
   * @note User should not override this function, otherwise there will be unexpected behavior.
   *
   * @return The encryption type. It would always be @link PDFDoc::e_EncryptFoxitDRM @endlink.
   */
  virtual PDFDoc::EncryptType GetSecurityType() FS_OVERRIDE {return PDFDoc::e_EncryptFoxitDRM;}
  /**
   * @brief A callback function used to check if current user is the owner of the PDF document.
   *
   * @param[in] document    A PDF document object.
   * @param[in] sub_filter  The sub filter name that specifies the syntax of the encryption dictionary contents.
   *
   * @note User should implement this callback function.
   *
   * @return <b>true</b> means current user is the owner of the PDF document, while <b>false</b> means not.
   */
  virtual bool IsOwner(const PDFDoc& document, const char* sub_filter) = 0;
  /**
   * @brief A callback function used to get the current user permissions.
   *
   * @param[in] document    A PDF document object.
   * @param[in] sub_filter  The sub filter name that specifies the syntax of the encryption dictionary contents.
   *
   * @note User should implement this callback function.
   *
   * @return Current user permissions. Please refer to values starting from @link PDFDoc::e_PermPrint @endlink and
   *         this can be one or combination of these values.
   */
  virtual uint32 GetUserPermissions(const PDFDoc& document, const char* sub_filter) = 0;
  /**
   * @brief A callback function used to get the cipher type for encryption algorithm.
   *
   * @param[in] document    A PDF document object.
   * @param[in] sub_filter  The sub filter name that specifies the syntax of the encryption dictionary contents.
   *
   * @note User should implement this callback function.
   *
   * @return The cipher type. Please refer to values starting from @link SecurityHandler::e_CipherNone @endlink and
   *         this should be one of these values.
   */
  virtual SecurityHandler::CipherType GetCipherType(const PDFDoc& document, const char* sub_filter) = 0;
  /**
   * @brief A callback function used to get the length of cipher key.
   *
   * @param[in] document    A PDF document object.
   * @param[in] sub_filter  The sub filter name that specifies the syntax of the encryption dictionary contents.
   *
   * @note User should implement this callback function.
   *
   * @return The key length. <br>
   *         For @link SecurityHandler::e_CipherRC4 @endlink cipher, this value should
   *         be between 5 and 16.<br>
   *         For @link SecurityHandler::e_CipherAES @endlink cipher, this value should be 16 or 32.
   */
  virtual uint32 GetKeyLength(const PDFDoc& document, const char* sub_filter) = 0;
  /**
   * @brief A callback function used to get the file identity string.
   *
   * @param[in] document    A PDF document object.
   * @param[in] sub_filter  The sub filter name that specifies the syntax of the encryption dictionary contents.
   *
   * @note User should implement this callback function.
   *
   * @return The identity string, used to identify the file.
   */
  virtual String GetFileID(const PDFDoc& document, const char* sub_filter) = 0;
  /**
   * @brief A callback function used to get the initial key to decrypt the DRM protected document.
   *
   * @param[in] document    A PDF document object.
   * @param[in] sub_filter  The sub filter name that specifies the syntax of the encryption dictionary contents.
   *
   * @note User should implement this callback function.
   *
   * @return The initial key.
   */
  virtual String GetInitialKey(const PDFDoc& document, const char* sub_filter) = 0;

 protected:
  ~DRMSecurityCallback() {}
};

/**
 * This class represents a callback object for custom decryption and encryption. If user wants to use
 * custom security callback, user should inherit this callback class and implement the pure virtual functions
 * (as callback functions), and then register the custom security callback object to Foxit PDF SDK by function
 * @link common::Library::RegisterSecurityCallback @endlink with with any custom filter name (following the PDF name
 * conventions). Function @link common::Library::UnregisterSecurityCallback @endlink can be called to unregister the
 * security callback object with the registered filter name.
 */
class CustomSecurityCallback: public SecurityCallback {
 public:
  /**
   * @brief Get the encryption type of security callback.
   *
   * @note User should not override this function, otherwise there will be unexpected behavior.
   *
   * @return The encryption type. It would always be @link PDFDoc::e_EncryptCustom @endlink.
   */
  virtual PDFDoc::EncryptType GetSecurityType() FS_OVERRIDE {return PDFDoc::e_EncryptCustom;}
  /**
   * @brief A callback function used to create context for encryption and decryption.
   *
   * @param[in] filter        The filter name of the custom security callback object.
   * @param[in] sub_filter    The sub filter name that specifies the syntax of the encryption dictionary contents.
   * @param[in] encrypt_info  The encryption information of the PDF document.
   *
   * @note User should implement this callback function.
   *
   * @return The encryption context.
   */
  virtual void* CreateContext(const char* filter, const char* sub_filter, const char* encrypt_info) = 0;
  /**
   * @brief A callback function used to release the context for encryption and decryption.
   *
   * @param[in] context  The context for encryption and decryption, returned by callback function
   *                     @link CustomSecurityCallback::CreateContext @endlink.
   *
   * @note User should implement this callback function.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool ReleaseContext(void* context) = 0;
  /**
   * @brief A callback function used to get the user permissions.
   *
   * @param[in] context          The context for encryption and decryption, returned by callback function
   *                             @link CustomSecurityCallback::CreateContext @endlink.
   * @param[in] user_permission  Original permission settings of the document. Please refer to values starting from
   *                             @link PDFDoc::e_PermPrint @endlink and this would be one or combination of these values.
   *
   * @note User should implement this callback function.
   *
   * @return The new user permissions. Please refer to values starting from @link PDFDoc::e_PermPrint @endlink and
   *         this should be one or combination of these values.
   */
  virtual uint32 GetUserPermissions(const void* context, uint32 user_permission) = 0;
  /**
   * @brief A callback function used to check if current user is the owner of the PDF document.
   *
   * @param[in] context  The context for encryption and decryption, returned by callback function
   *                     @link CustomSecurityCallback::CreateContext @endlink.
   *
   * @note User should implement this callback function.
   *
   * @return <b>true</b> means current user is the owner, and <b>false</b> means current user is not the owner.
   */
  virtual bool IsOwner(const void* context) = 0;
  /**
   * @brief A callback function used to get the cipher type.
   *
   * @param[in] context  The context for encryption and decryption, returned by callback function
   *                     @link CustomSecurityCallback::CreateContext @endlink.
   *
   * @note User should implement this callback function.
   *
   * @return The cipher type. Please refer to values starting from @link SecurityHandler::e_CipherNone @endlink and
   *         this should be one of these values.
   */
  virtual SecurityHandler::CipherType GetCipher(const void* context) = 0;
  /**
   * @brief A callback function used to get the encryption key.
   *
   * @param[in] context  The context for encryption and decryption, returned by callback function
   *                     @link CustomSecurityCallback::CreateContext @endlink.
   *
   * @note User should implement this callback function.
   *
   * @return The encryption key.
   */
  virtual String GetEncryptKey(const void* context) = 0;
  /**
   * @brief A callback function used to get the estimated decrypted data size.
   *
   * @param[in] context        The context for encryption and decryption, returned by callback function
   *                           @link CustomSecurityCallback::CreateContext @endlink.
   * @param[in] src_data_size  Size of source data which is to be decrypted.
   *
   * @note User should implement this callback function.
   *
   * @return The estimated decrypted data size.
   */
  virtual uint32 GetDecryptedSize(const void* context, uint32 src_data_size) = 0;
  /**
   * @brief A callback function used to start a decryption.
   *
   * @param[in] context  The context for encryption and decryption, returned by callback function
   *                     @link CustomSecurityCallback::CreateContext @endlink.
   * @param[in] obj_num  The object number for a PDF object.
   * @param[in] gen_num  The generation number for a PDF object.
   *
   * @note User should implement this callback function.
   *
   * @return A decryptor implemented and created by user.
   */
  virtual void* StartDecryptor(const void* context, int obj_num, int gen_num) = 0;
  /**
   * @brief A callback function used to decrypt the encrypted data.
   *
   * @param[in] decryptor           The decryptor implemented and created by user, returned by callback function
   *                                @link CustomSecurityCallback::StartDecryptor @endlink.
   * @param[in] encrypted_data      The buffer which stores the encrypted data.
   * @param[in] encrypted_data_len  The length of encrypted data, in bytes.
   *
   * @note User should implement this callback function.
   *
   * @return The decrypted data content.
   */
  virtual String DecryptData(const void* decryptor, const void* encrypted_data, uint32 encrypted_data_len) = 0;
  /**
   * @brief A callback function used to finish the decryption.
   *
   * @param[in] decryptor  The decryptor implemented and created by user, returned by callback function
   *                       @link CustomSecurityCallback::StartDecryptor @endlink.
   *
   * @note User should implement this callback function.
   *
   * @return The decrypted data content.
   */
  virtual String FinishDecryptor(void* decryptor) = 0;
  /**
   * @brief A callback function used to get the estimated encrypted size.
   *
   * @param[in] context       The context for encryption and decryption, returned by callback function
   *                          @link CustomSecurityCallback::CreateContext @endlink.
   * @param[in] obj_num       The object number for a PDF object.
   * @param[in] gen_num       The generation number for a PDF object.
   * @param[in] src_data      The buffer which stores the plain text to be encrypted.
   * @param[in] src_data_len  The length of the buffer.
   *
   * @note User should implement this callback function.
   *
   * @return The estimated encrypted size.
   */
  virtual uint32 GetEncryptedSize(const void* context, int obj_num, int gen_num,
                                  const void* src_data, uint32 src_data_len) = 0;
  /**
   * @brief A callback function used to get encrypted data.
   *
   * @param[in] context              The context for encryption and decryption, returned by callback function
   *                                 @link CustomSecurityCallback::CreateContext @endlink.
   * @param[in] obj_num              The object number for a PDF object.
   * @param[in] gen_num              The generation number for a PDF object.
   * @param[in] src_data             The buffer which stores the plain text to be encrypted.
   * @param[in] src_data_len         The length of the buffer.
   * @param[out] out_dst_buffer      Output parameter that receives the encrypted content.
   * @param[out] out_dst_buffer_len  Output parameter that receives the length of the encrypted data.
   *
   * @note User should implement this callback function.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool EncryptData(const void* context, int obj_num, int gen_num,
                           const void* src_data, uint32 src_data_len,
                           void* out_dst_buffer, uint32* out_dst_buffer_len) = 0;

  /**
   * @brief A callback function to check if to use stanard crypto method or custom crypto method.
   *
   * @param[in] context  The context for encryption and decryption, returned by callback function
   *                     @link CustomSecurityCallback::CreateContext @endlink.
   *
   * @return <ul>
   *         <li><b>true</b> means to use standard crypto method. In this case, callback functions
   *             @link CustomSecurityCallback::GetDecryptedSize @endlink, @link CustomSecurityCallback::StartDecryptor @endlink,
   *             @link CustomSecurityCallback::DecryptData @endlink, @link CustomSecurityCallback::FinishDecryptor @endlink,
   *             @link CustomSecurityCallback::GetEncryptedSize @endlink, and @link CustomSecurityCallback::EncryptData @endlink will be uselss
   *             and user can just use empy implementation for them.</li>
   *         <li><b>false</b> means use custom crypto method. In this case, please ensure callback functions mentioned above have all been implemented.</li>
   *         </ul>
   */
  virtual bool UseStandardCryptoMethod(const void* context) { return false; }

 protected:
  ~CustomSecurityCallback() {}
};

/**
 * This class represents a callback object for RMS decryption and encryption. If user wants to use
 * RMS security callback, user should inherit this callback class and implement the pure virtual functions
 * (as callback functions), and then register the RMS security callback object to Foxit PDF SDK by function
 * @link common::Library::RegisterSecurityCallback @endlink with <i>filter</i> "MicrosoftIRMServices".
 * Function @link common::Library::UnregisterSecurityCallback @endlink can be called to unregister the security
 * callback object with the registered filter name.
 */
class RMSSecurityCallback: public CustomSecurityCallback {
 public:
  /**
   * @brief Get the encryption type of security callback.
   *
   * @note User should not override this function, otherwise there will be unexpected behavior.
   *
   * @return The encryption type. It would always be @link PDFDoc::e_EncryptRMS @endlink.
   */
  virtual PDFDoc::EncryptType GetSecurityType() FS_OVERRIDE {return PDFDoc::e_EncryptRMS;}

 protected:
  ~RMSSecurityCallback() {}
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_SECURITY_H_

