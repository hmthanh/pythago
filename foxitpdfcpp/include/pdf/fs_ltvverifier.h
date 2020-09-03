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
 * @file fs_signature.h
 * @brief Header file for LTV verifier related definitions and classes.
 */

#ifndef FS_LTVVERIFIER_H_
#define FS_LTVVERIFIER_H_

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
/** This class represents a response for a certificate. */
class Response FS_FINAL : public Object{
 public:
  /**
  * @brief Enumeration for response type.
  *
  * @details Values of this enumeration should be used alone.
  */
  typedef enum _ResponseType {
    /** @brief No response. */
    e_TypeNone = 0,
    /** @brief CRL response. */
    e_TypeCRL = 1,
    /** @brief OCSP response. */
    e_TypeOCSP = 2
  } ResponseType;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] type           Response type. Please refer to values starting from
   *                           @link Response::e_TypeNone @endlink and this should be one of these values.
   * @param[in] response_data  Response content.
   */
  Response(ResponseType type, const String& response_data) {
    this->type = type;
    this->response_data = response_data;
  }

  /** @brief Constructor. */
  Response() : type(Response::e_TypeNone) {}

  /** @brief Destructor. */
  ~Response() {}

  /**
   * @brief Constructor, with another response object.
   *
   * @param[in] other  Another response object.
   */
  Response(const Response& other) {
    type = other.type;
    response_data = other.response_data;
  }

  /**
  * @brief Assign operator.
  *
  * @param[in] other  Another response object, whose value would be assigned to current object.
  *
  * @return Reference to current object itself.
  */
  Response& operator = (const Response& other) {
    type = other.type;
    response_data = other.response_data;
    return *this;
  }

  /**
  * @brief Equal operator.
  *
  * @param[in] other  Another response object. This function will check if current object is equal to this one.
  *
  * @return <b>true</b> means equal, while <b>false</b> means not equal.
  */
  bool operator == (const Response& other) const {
    return (type == other.type && response_data == other.response_data);
  }

  /**
  * @brief Not equal operator.
  *
  * @param[in] other  Another response object. This function will check if current object is not equal to this one.
  *
  * @return <b>true</b> means not equal, while <b>false</b> means equal.
  */
  bool operator != (const Response& other) const {
    return!(*this == other);
  }

  /**
  * @brief Set value.
  *
  * @param[in] type           Response type. Please refer to values starting from
  *                           @link Response::e_TypeNone @endlink and this should be one of these values.
  * @param[in] response_data  Response content.
  *
  * @return None.
  */
  void Set(ResponseType type, const String& response_data) {
    this->type = type;
    this->response_data = response_data;
  }

  /**
   * @brief Response type. Please refer to values starting from @link Response::e_TypeNone @endlink and
   *        this should be one of these values.
   */
  ResponseType type;
  /** @brief Response content. */
  String response_data;
};

/** This class represents a time range, including start time and end time. */
class TimeRange FS_FINAL : public Object{
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] start_time  Start time of current time range.
   * @param[in] end_time    End time of current time range.
   */
  TimeRange(const DateTime& start_time, const DateTime& end_time) {
    this->start_time = start_time;
    this->end_time = end_time;
  }

  /** @brief Constructor. */
  TimeRange() {}

  /** @brief Destructor. */
  ~TimeRange() {}

  /**
   * @brief Constructor, with another time range object.
   *
   * @param[in] other  Another time range object.
   */
  TimeRange(const TimeRange& other) {
    start_time = other.start_time;
    end_time = other.end_time;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another time range object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TimeRange& operator = (const TimeRange& other) {
    start_time = other.start_time;
    end_time = other.end_time;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another time range object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const TimeRange& other) const {
    return (start_time == other.start_time && end_time == other.end_time);
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another time range object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const TimeRange& other) const {
    return!(*this == other);
  }

  /**
   * @brief Set value.
   *
   * @param[in] start_time  Start time of current time range.
   * @param[in] end_time    End time of current time range.
   *
   * @return None.
   */
  void Set(const DateTime& start_time, const DateTime& end_time) {
    this->start_time = start_time;
    this->end_time = end_time;
  }

  /** @brief Start time of current time range. */
  DateTime start_time;
  /** @brief End time of current time range. */
  DateTime end_time;
};

/** This class represents the verify result for a certificate. */
class CertVerifyResult FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for certificate status.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _CertStatus {
    /** @brief This means certificate is valid. */
    e_CertStatusValid = 0,
    /** @brief This means certificate is revoked. */
    e_CertStatusRevoked = 1,
    /** @brief This means certificate is expired. */
    e_CertStatusExpired = 2,
    /** @brief This means certificate status is unknown. */
    e_CertStatusUnknown = 3
  } CertStatus;
  
  /**
   * @brief Enumeration for revocation reason for a certificate.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _RevocationReason {
    /** @brief Revocatoin reason: ceritifcate has no status. */
    e_ReasonNoStatus = -1,
    /** @brief Revocatoin reason: unspecified reason. */
    e_ReasonUnspecified = 0,
    /** @brief Revocatoin reason: key compromise. */
    e_ReasonKeyCompromise = 1,
    /** @brief Revocatoin reason: CA compromise. */
    e_ReasonCACompromise = 2,
    /** @brief Revocatoin reason: affiliation changed. */
    e_ReasonAffiliationChanged = 3,
    /** @brief Revocatoin reason: superseded. */
    e_ReasonSuperseded = 4,
    /** @brief Revocatoin reason: cessation of operation. */
    e_ReasonCessationOfOperation = 5,
    /** @brief Revocatoin reason: certificate hold. */
    e_ReasonCertificateHold = 6,
    /** @brief Revocatoin reason: remove from CRL. */
    e_ReasonRemoveFromCRL = 7,
    /** @brief Revocatoin reason: privilege with drawn. */
    e_ReasonPrivilegeWithDrawn = 8,
    /** @brief Revocatoin reason: AA compromise. */
    e_ReasonAACompromise = 9
  } RevocationReason;
  
  /**
   * @brief Enumeration for response information location.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ResponseInfoLocation {
    /** @brief Location is not set. */
    e_LocationNotSet = 0,
    /** @brief Response information is found in DSS dictionary. */
    e_LocationDSS = 1,
    /** @brief Response information is found in signature content. */
    e_LocationSignature = 2,
    /** @brief Response information is got by online request. */
    e_LocationOnline = 3
  } ResponseInfoLocation;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] cert                               A certificate contnet.
   * @param[in] is_ca                              Indicate if the certificate is a CA certificate.
   * @param[in] is_trusted                         Indicate if the certificate is trusted by user.
   * @param[in] response                           A response for the certificate.
   * @param[in] response_effect_time_range         The time range when the response takes effect.
   * @param[in] revoke_time                        Revoked time got from the response.
   * @param[in] cert_status                        Certificate status. Please refer to values starting from
   *                                               @link CertVerifyResult::e_CertStatusValid @endlink and
   *                                               this should be one of these values.
   * @param[in] reason                             Revocation reason of the certificate. Please refer to values starting from
   *                                               @link CertVerifyResult::e_ReasonNoStatus @endlink and
   *                                               this should be one of these values.
   * @param[in] cert_check_time                    The actual time when this certificate is checked validity.
   *                                               <i>utc_hour_offset</i> and <i>utc_minite_offset</i> of this time object are ignored.
   * @param[in] exist_signature_vri_creation_time  Indicate if creation time of siganture's VRI exists.
   * @param[in] signature_vri_creation_time        Creation time of a signature's VRI. <i>utc_hour_offset</i> and
   *                                               <i>utc_minite_offset</i> of this time object are ignored.
   * @param[in] exist_response_signature_vri_creation_time  Indicate if creation time of response signature's VRI exists.
   * @param[in] response_signature_vri_creation_time        Creation time of response signature's VRI. <i>utc_hour_offset</i> and
   *                                                        <i>utc_minite_offset</i> of this time object are ignored.
   * @param[in] response_info_location             Response information (as revocation information) location where certificate response can be found.
   *                                               Please refer to values starting from @link CertVerifyResult::e_LocationNotSet @endlink
   *                                               and this should be one of these values.
   */
  CertVerifyResult(const String& cert, bool is_ca, bool is_trusted, const Response& response,
                   const TimeRange& response_effect_time_range, const DateTime& revoke_time,
                   CertStatus cert_status, RevocationReason reason,
                   const DateTime& cert_check_time,
                   bool exist_signature_vri_creation_time, const DateTime& signature_vri_creation_time,
                   bool exist_response_signature_vri_creation_time, const DateTime& response_signature_vri_creation_time,
                   ResponseInfoLocation response_info_location) {
    this->cert = cert;
    this->is_ca = is_ca;
    this->is_trusted = is_trusted;
    this->response = response;
    this->response_effect_time_range = response_effect_time_range;
    this->revoke_time = revoke_time;
    this->cert_status = cert_status;
    this->reason = reason;
    this->cert_check_time = cert_check_time;
    this->exist_signature_vri_creation_time = exist_signature_vri_creation_time;
    this->signature_vri_creation_time = signature_vri_creation_time;
    this->exist_response_signature_vri_creation_time = exist_response_signature_vri_creation_time;
    this->response_signature_vri_creation_time = response_signature_vri_creation_time;
    this->response_info_location = response_info_location;
  }

  /** @brief Constructor. */
  CertVerifyResult()
      : is_ca(false)
      , is_trusted(false)
      , cert_status(CertVerifyResult::e_CertStatusUnknown)
      , reason(CertVerifyResult::e_ReasonNoStatus)
      , exist_signature_vri_creation_time(false)
      , exist_response_signature_vri_creation_time(false)
      , response_info_location(CertVerifyResult::e_LocationNotSet) {}

  /** @brief Destructor. */
  ~CertVerifyResult() {}

  /**
  * @brief Constructor, with another response object.
  *
  * @param[in] other  Another response object.
  */
  CertVerifyResult(const CertVerifyResult& other) {
    cert = other.cert;
    is_ca = other.is_ca;
    is_trusted = other.is_trusted;
    response = other.response;
    response_effect_time_range = other.response_effect_time_range;
    revoke_time = other.revoke_time;
    cert_status = other.cert_status;
    reason = other.reason;
    cert_check_time = other.cert_check_time;
    exist_signature_vri_creation_time = other.exist_signature_vri_creation_time;
    signature_vri_creation_time = other.signature_vri_creation_time;
    exist_response_signature_vri_creation_time = other.exist_response_signature_vri_creation_time;
    response_signature_vri_creation_time = other.response_signature_vri_creation_time;
    response_info_location = other.response_info_location;
  }

  /**
  * @brief Assign operator.
  *
  * @param[in] other  Another response object, whose value would be assigned to current object.
  *
  * @return Reference to current object itself.
  */
  CertVerifyResult& operator = (const CertVerifyResult& other) {
    cert = other.cert;
    is_ca = other.is_ca;
    is_trusted = other.is_trusted;
    response = other.response;
    response_effect_time_range = other.response_effect_time_range;
    revoke_time = other.revoke_time;
    cert_status = other.cert_status;
    reason = other.reason;
    cert_check_time = other.cert_check_time;
    exist_signature_vri_creation_time = other.exist_signature_vri_creation_time;
    signature_vri_creation_time = other.signature_vri_creation_time;
    exist_response_signature_vri_creation_time = other.exist_response_signature_vri_creation_time;
    response_signature_vri_creation_time = other.response_signature_vri_creation_time;
    response_info_location = other.response_info_location;
    return *this;
  }

  /**
  * @brief Equal operator.
  *
  * @param[in] other  Another response object. This function will check if current object is equal to this one.
  *
  * @return <b>true</b> means equal, while <b>false</b> means not equal.
  */
  bool operator == (const CertVerifyResult& other) const {
    return (cert == other.cert && is_ca == other.is_ca && is_trusted == other.is_trusted &&
            response == other.response &&
            response_effect_time_range == other.response_effect_time_range &&
            revoke_time == other.revoke_time &&
            cert_status == other.cert_status && reason == other.reason &&
            cert_check_time == other.cert_check_time &&
            exist_signature_vri_creation_time == other.exist_signature_vri_creation_time&&
            signature_vri_creation_time == other.signature_vri_creation_time &&
            exist_response_signature_vri_creation_time == other.exist_response_signature_vri_creation_time &&
            response_signature_vri_creation_time == other.response_signature_vri_creation_time &&
            response_info_location == other.response_info_location);
  }

  /**
  * @brief Not equal operator.
  *
  * @param[in] other  Another response object. This function will check if current object is not equal to this one.
  *
  * @return <b>true</b> means not equal, while <b>false</b> means equal.
  */
  bool operator != (const CertVerifyResult& other) const {
    return!(*this == other);
  }

  /**
   * @brief Set value.
   *
   * @param[in] cert                               A certificate contnet.
   * @param[in] is_ca                              Indicate if the certificate is a CA certificate.
   * @param[in] is_trusted                         Indicate if the certificate is trusted by user.
   * @param[in] response                           A response for the certificate.
   * @param[in] response_effect_time_range         The time range when the response takes effect.
   * @param[in] revoke_time                        Revoked time got from the response.
   * @param[in] cert_status                        Certificate status. Please refer to values starting from
   *                                               @link CertVerifyResult::e_CertStatusValid @endlink and
   *                                               this should be one of these values.
   * @param[in] reason                             Revocation reason of the certificate. Please refer to values starting from
   *                                               @link CertVerifyResult::e_ReasonNoStatus @endlink and
   *                                               this should be one of these values.
   * @param[in] cert_check_time                    The actual time when this certificate is checked validity.
   *                                               <i>utc_hour_offset</i> and <i>utc_minite_offset</i> of this time object are ignored.
   * @param[in] exist_signature_vri_creation_time  Indicate if creation time of siganture's VRI exists.
   * @param[in] signature_vri_creation_time        Creation time of a signature's VRI. <i>utc_hour_offset</i> and
   *                                               <i>utc_minite_offset</i> of this time object are ignored.
   * @param[in] exist_response_signature_vri_creation_time  Indicate if creation time of response signature's VRI exists.
   * @param[in] response_signature_vri_creation_time        Creation time of response signature's VRI.  <i>utc_hour_offset</i> and
   *                                                        <i>utc_minite_offset</i> of this time object are ignored.
   * @param[in] response_info_location             Response information (as revocation information) location where certificate response can be found.
   *                                               Please refer to values starting from @link CertVerifyResult::e_LocationNotSet @endlink
   *                                               and this should be one of these values.
   *
   * @return None.
   */
  void Set(const String& cert, bool is_ca, bool is_trusted, const Response& response,
           const TimeRange& response_effect_time_range, const DateTime& revoke_time,
           CertStatus cert_status, RevocationReason reason,
           const DateTime& cert_check_time,
           bool exist_signature_vri_creation_time, const DateTime& signature_vri_creation_time,
           bool exist_response_signature_vri_creation_time, const DateTime& response_signature_vri_creation_time,
           ResponseInfoLocation response_info_location) {
    this->cert = cert;
    this->is_ca = is_ca;
    this->is_trusted = is_trusted;
    this->response = response;
    this->response_effect_time_range = response_effect_time_range;
    this->revoke_time = revoke_time;
    this->cert_status = cert_status;
    this->reason = reason;
    this->cert_check_time = cert_check_time;
    this->exist_signature_vri_creation_time = exist_signature_vri_creation_time;
    this->signature_vri_creation_time = signature_vri_creation_time;
    this->exist_response_signature_vri_creation_time = exist_response_signature_vri_creation_time;
    this->response_signature_vri_creation_time = response_signature_vri_creation_time;
    this->response_info_location = response_info_location;
  }

  /** @brief A certificate contnet. */
  String cert;

  /** @brief Indicate if the certificate is a CA certificate. */
  bool is_ca;
  /** @brief Indicate if the certificate is truscted by user. */
  bool is_trusted;
  /** @brief A response for the certificate. */
  Response response;
  /** @brief The time range when the response takes effect.*/
  TimeRange response_effect_time_range;
  /** @brief Revoked time got from the response. */
  DateTime revoke_time;
  /**
   * @brief Certificate status. Please refer to values starting from
   *        @link CertVerifyResult::e_CertStatusValid @endlink and
   *        this should be one of these values.
   */
  CertStatus cert_status;
  /**
   * @brief Revocation reason of the certificate. Please refer to values starting from
   *        @link CertVerifyResult::e_ReasonNoStatus @endlink and
   *        this should be one of these values.
   */
  RevocationReason reason;
  /** 
   * @brief The actual time when this certificate is checked validity.
   *        <i>utc_hour_offset</i> and <i>utc_minite_offset</i> of this time object are ignored.
   */
  DateTime cert_check_time;
  /** @brief Indicate if creation time of siganture's VRI exists.*/
  bool exist_signature_vri_creation_time;
  /**
   * @brief Creation time of a signature's VRI. <i>utc_hour_offset</i> and
   *        <i>utc_minite_offset</i> of this time object are ignored.
   */
  DateTime signature_vri_creation_time;
  /** @brief Indicate if creation time of response signature's VRI exists.*/
  bool exist_response_signature_vri_creation_time;
  /**
   * @brief Creation time of response signature's VRI. <i>utc_hour_offset</i> and
   *        <i>utc_minite_offset</i> of this time object are ignored.
   */
  DateTime response_signature_vri_creation_time;
  /**
   * @brief Response information (as revocation information) location where certificate response can be found.
   *        Please refer to values starting from @link CertVerifyResult::e_LocationNotSet @endlink
   *        and this should be one of these values.*/
  ResponseInfoLocation response_info_location;
};

/** This class represents an array of @link CertVerifyResult @endlink objects. */
FSDK_DEFINE_ARRAY(CertVerifyResultArray, CertVerifyResult);

/** This class represents a cert-issuer pair. */
class CertIssuerPair FS_FINAL : public Object{
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] cert    Certificate content.
   * @param[in] issuer  An issuer for the certificate.
   */
  CertIssuerPair(const String& cert, const String& issuer) {
    this->cert = cert;
    this->issuer = issuer;
  }

  /** @brief Constructor. */
  CertIssuerPair() {}

  /** @brief Destructor. */
  ~CertIssuerPair() {}

  /**
  * @brief Constructor, with another cert-issuer pair object.
  *
  * @param[in] other  Another cert-issuer pair object.
  */
  CertIssuerPair(const CertIssuerPair& other) {
    cert = other.cert;
    issuer = other.issuer;
  }

  /**
  * @brief Assign operator.
  *
  * @param[in] other  Another cert-issuer pair object, whose value would be assigned to current object.
  *
  * @return Reference to current object itself.
  */
  CertIssuerPair& operator = (const CertIssuerPair& other) {
    cert = other.cert;
    issuer = other.issuer;
    return *this;
  }

  /**
  * @brief Equal operator.
  *
  * @param[in] other  Another cert-issuer pair object. This function will check if current object is equal to this one.
  *
  * @return <b>true</b> means equal, while <b>false</b> means not equal.
  */
  bool operator == (const CertIssuerPair& other) const {
    return (cert == other.cert && issuer == other.issuer);
  }

  /**
  * @brief Not equal operator.
  *
  * @param[in] other  Another cert-issuer pair object. This function will check if current object is not equal to this one.
  *
  * @return <b>true</b> means not equal, while <b>false</b> means equal.
  */
  bool operator != (const CertIssuerPair& other) const {
    return!(*this == other);
  }

  /**
   * @brief Set value.
   *
   * @param[in] cert    Certificate content.
   * @param[in] issuer  An issuer for the certificate.
   *
   * @return None.
   */
  void Set(const String& cert, const String& issuer) {
    this->cert = cert;
    this->issuer = issuer;
  }

  /** @brief Certificate content. */
  String cert;
  /** @brief An issuer of the certificate. */
  String issuer;
};

/** This class represents information in array type of revocation information. */
class RevocationArrayInfo FS_FINAL : public Object{
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] ocsp_array  An array of OCSP response content.
   * @param[in] crl_array   An array of CRL response content.
   */
  RevocationArrayInfo(const StringArray& ocsp_array, const StringArray& crl_array) {
    this->ocsp_array = ocsp_array;
    this->crl_array = crl_array;
  }

  /** @brief Constructor. */
  RevocationArrayInfo() {}

  /** @brief Destructor. */
  ~RevocationArrayInfo() {}

  /**
   * @brief Constructor, with another revocation array information object.
   *
   * @param[in] other  Another revocation array information object.
   */
  RevocationArrayInfo(const RevocationArrayInfo& other) {
    ocsp_array = other.ocsp_array;
    crl_array = other.crl_array;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another revocation array information object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  RevocationArrayInfo& operator = (const RevocationArrayInfo& other) {
    ocsp_array = other.ocsp_array;
    crl_array = other.crl_array;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another revocation array information object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const RevocationArrayInfo& other) const {
    size_t ocsp_count = ocsp_array.GetSize();
    size_t crl_count = crl_array.GetSize();
    if (ocsp_count != other.ocsp_array.GetSize() || crl_count != crl_array.GetSize())
      return false;
    for (size_t i = 0; i < ocsp_count; i++) {
      if (ocsp_array.GetAt(i) != other.ocsp_array.GetAt(i))
        return false;
    }
    for (size_t i = 0; i < ocsp_count; i++) {
      if (crl_array.GetAt(i) != other.crl_array.GetAt(i))
        return false;
    }
    return true;
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another revocation array information object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const RevocationArrayInfo& other) const {
    return!(*this == other);
  }

  /**
   * @brief Set value.
   *
   * @param[in] ocsp_array  An array of OCSP response content.
   * @param[in] crl_array   An array of CRL response content.
   *
   * @return None.
   */
  void Set(const StringArray& ocsp_array, const StringArray& crl_array) {
    this->ocsp_array = ocsp_array;
    this->crl_array = crl_array;
  }

  /** @brief An array of OCSP response content. */
  StringArray ocsp_array;
  /** @brief An array of CRL response content. */
  StringArray crl_array;
};

/**
 * This class represent a revocation callback object which is used for class @link LTVVerifier @endlink.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 * 
 * @see @link LTVVerifier @endlink
 */
class RevocationCallback {
 public:
  /**
  * @brief A callback function used to release current callback object itself.
  *
  * @return None.
  */
  virtual void Release() = 0;
  
  /**
   * @brief A callback function used to get the cert chain from the signature content.
   *
   * @param[in] signature_content  Signature content.
   *
   * @return An array that represents the cert chain.
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual StringArray GetCertChainFromSignature(const String& signature_content) = 0;

  /**
   * @brief A callback function used to get response online for a certificate.
   *
   * @param[in] cert_issuer_pair  A cert-issuer pair which represents a certificate and an issuer for the certificate.
   * 
   * @return Response for the certificate.
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual Response GetResponseOnLineForSingleCert(const CertIssuerPair& cert_issuer_pair) = 0;

  /**
   * @brief A callback function used to verify whether the OCSP response matches the certificate and
   *        get the verify result for the certificate.
   *
   * @param[in] cert_issuer_pair  A cert-issuer pair which represents a certificate and an issuer for the certificate.
   * @param[in] ocsp_data         OCSP content.
   *
   * @return Certificate verify result that obtained from CRL.
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual CertVerifyResult VerifyOCSP(const CertIssuerPair& cert_issuer_pair, const String& ocsp_data) = 0;

  /**
   * @brief A callback function used to verify whether the CRL response matches the certificate and
   *        get the verify result for the certificate.
   *
   * @param[in] cert_issuer_pair  A cert-issuer pair which represents a certificate and an issuer for the certificate.
   * @param[in] crl_data          CRL content.
   *
   * @return Certificate verify result that obtained from CRL.
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual CertVerifyResult VerifyCRL(const CertIssuerPair& cert_issuer_pair, const String& crl_data) = 0;

  /**
   * @brief A callback function used to judge whether a certificate is a CA certificate.
   *
   * @param[in] cert  Certificate content.
   *
   * @return <b>true</b> means the certificate is a CA certificate, while <b>false</b> means not.
   */
  virtual bool IsCA(const String& cert) = 0;

  /**
   * @brief A callback function used to get the DTS (document time stamp signature) time from signature content.
   *
   * @param[in] signature_content  Signature content.
   *
   * @return DTS time. <i>utc_hour_offset</i> and <i>utc_minite_offset</i> of this time would be ignored.
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual DateTime GetDTSTime(const String& signature_content) = 0;

  /**
   * @brief A callback function used to get the time stamp token content from a signature content.
   *
   * @param[in] signature_content  Signature content.
   *
   * @return Time stamp token content.
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual String GetTSTSignature(const String& signature_content) = 0;

  /**
   * @brief A callback function used to get the time stamp token time from signature content.
   *
   * @param[in] signature_content  Signature content.
   * 
   * @return Time of time stamp token of a signature. <i>utc_hour_offset</i> and <i>utc_minite_offset</i>
   *         of this time would be ignored.
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual DateTime GetTSTTime(const String& signature_content) = 0;

  /**
   * @brief A callback function used to get the cert-issuer pair of OCSP response.
   *
   * @param[in] ocsp_data         OCSP response data.
   * @param[in] trust_cert_chain  The trust cert chain used to find the issuer of the OCSP cert.
   *
   * @return A cert-issuer pair that obtained from OCSP.
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual CertIssuerPair GetOCSPCertAndIssuer(const String& ocsp_data, const StringArray& trust_cert_chain) = 0;

  /**
   * @brief A callback function used to get the produce time of the OCSP response.
   *
   * @param[in] ocsp_data  OCSP response content.
   *
   * @return Produce time of the OCSP response. <i>utc_hour_offset</i> and <i>utc_minite_offset</i>
   *         of this time would be ignored.
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual DateTime GetOCSPProducedAtTime(const String& ocsp_data)  = 0;

  /**
   * @brief A callback function used to get flag which decides if need to check OCSP response.
   *
   * @param[in] ocsp_data  OCSP response content.
   *
   * @return <b>true</b> means need to check OCSP response, while <b>false</b> means no need.
   */
  virtual bool IsOCSPNeedCheck(const String& ocsp_data) = 0;

  /**
   * @brief A callback function used to get the time range that represents validity period of a certificate.
   *
   * @param[in] cert  Certificate content.
   *
   * @return Time range that represents validity period of the certificate.
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual TimeRange GetCertValidTimeRange(const String& cert) = 0;

  /**
   * @brief A callback function used to get the signature content from a OCSP response.
   *
   * @param[in] ocsp_data  OCSP response content.
   *
   * @return Signature content .
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual String GetOCSPSignature(const String& ocsp_data) = 0;

  /**
   * @brief A callback function used to get the signature content from a CRL response.
   *
   * @param[in] crl_data  CRL response content.
   *
   * @return Signature content .
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual String GetCRLSignature(const String& crl_data) = 0;

  /**
   * @brief A callback function used to get the revocation information (in array type) from a signature.
   *
   * @param[in] signature_content  Signature content.
   * 
   * @return Information in array type of revocation information.
   *
   * @note User can throw exception for errors. Please refere to class @link foxit::Exception @endlink and
   *       values starting from @link foxit::e_ErrFile @endlink.
   */
  virtual RevocationArrayInfo GetRevocationInfoFromSignatureData(const String& signature_content) = 0;

  /**
   * @brief A callback function used to check if an issuer matches a certificate.
   *
   * @param[in] cert_issuer_pair  A cert-issuer pair. Issuer in this pair is to be checked
   *                              if it matches the ceritificate in this pair.
   *
   * @return <b>true</b> means issuer matches the certificate, while <b>false</b> means not.
   */
  virtual bool IsIssuerMatchCert(const CertIssuerPair& cert_issuer_pair) = 0;

 protected:
  ~RevocationCallback() {}
};

/**
 * This class represent a callback object as trusted cert store.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.<br>
 * If user wants to trust some certificate during LTV verify process, user can set a customized trusted cert store callback object
 * by function @link LTVVerifier::SetTrustedCertStoreCallback @endlink before doint LTV verifying process.
 *
 * @see @link pdf::LTVVerifier @endlink
 */
class TrustedCertStoreCallback {
 public:
  /**
   * @brief A callback function used to check if input certificate is trusted.
   *
   * @param[in] cert  Certificate content.
   *
   * @return <b>true</b> means input certificate is trusted, while <b>false</b> means input certificated is not trusted.
   */
  virtual bool IsCertTrusted(const String& cert) = 0;

  /**
   * @brief A callback function used to check if input certificate is used as a trusted root.
   *
   * @param[in] cert  Certificate content.
   *
   * @return <b>true</b> means input certificate is used as a trusted root, while <b>false</b> means input certificated is not used as a trusted root.
   */
  virtual bool IsCertTrustedRoot(const String& cert) = 0;

};

class SignatureVerifyResult;
/** This class represents an array of @link pdf::SignatureVerifyResult @endlink objects. */
FSDK_DEFINE_ARRAY(SignatureVerifyResultArray, SignatureVerifyResult)

/**
 * LTV verifier is used to verify signature in LTV work flow.
 * Before use this class to verify signature(s), please ensure verify mode has been set by function
 * @link LTVVerifier::SetVerifyMode @endlink.<br>
 * Foxit PDF SDK has a default revocation callback for LTV verifier. If user wants to
 * use customized revocation callback, please refer to function @link LTVVerifier::SetRevocationCallback @endlink.<br>
 * If user wants to trust some certificates, please refer to function @link LTVVerifier::SetTrustedCertStoreCallback @endlink.<br>
 */
class LTVVerifier FS_FINAL : public Base{
 public:
  /**
  * @brief Enumeration for time type.
  *
  * @details Values of this enumeration should be used alone.
  */
  typedef enum _TimeType {
    /** @brief Use signature creation time. */
    e_SignatureCreationTime = 0,
    /** @brief Use the time of signature time stamp token. */
    e_SignatureTSTTime = 1,
    /** @brief Use current time. */
    e_CurrentTime = 2,
    /**
   @brief Use the creation time of VRI dictionary of a signature.
   @note VRI means "validation-related information".
     */
    e_VRICreationTime = 3
  } TimeType;
  
  /**
   * @brief Enumeration for verifying mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _VerifyMode {
    /** @brief Use ETSI validation process. */
    e_VerifyModeETSI = 0,
    /** @brief Use Acrobat validation process. */
    e_VerifyModeAcrobat = 1
  } VerifyMode;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] document             A valid PDF document object.
   * @param[in] is_verify_signature  (Only available for @link LTVVerifier::e_VerifyModeAcrobat @endlink)
   *                                 Use to decide whether to verify signature validity when verifying signature or note.
   * @param[in] use_expired_tst      (Only available for @link LTVVerifier::e_VerifyModeAcrobat @endlink)
   *                                 Use to decide whether to use expired TST to verify signature or note.
   * @param[in] ignore_doc_info      (Only available for @link LTVVerifier::e_VerifyModeAcrobat @endlink)
   *                                 Use to decide whether to ignore the revocation information in DSS and signature or not.
   * @param[in] time_type            (Only available for @link LTVVerifier::e_VerifyModeAcrobat @endlink)
   *                                 Use to speicify the time type which is expected to be used for verifying.
   *                                 Please refer to values starting from @link LTVVerifier::e_SignatureCreationTime @endlink
   *                                 and this should be one of these values except @link LTVVerifier::e_VRICreationTime @endlink.
   */
  explicit LTVVerifier(const PDFDoc& document, bool is_verify_signature, bool use_expired_tst,
                       bool ignore_doc_info, TimeType time_type);

  /**
   * @brief Constructor, with another LTV verifier object.
   *
   * @param[in] other  Another LTV verifier object.
   */
  LTVVerifier(const LTVVerifier& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another LTV verifier object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  LTVVerifier& operator = (const LTVVerifier& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another LTV verifier object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const LTVVerifier& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another LTV verifier object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const LTVVerifier& other) const;

  /** @brief Destructor. */
  ~LTVVerifier();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set a customized @link pdf::RevocationCallback @endlink object
   *
   * @details If no customized revocation callback is set by this function, Foxit PDF SDK will use a default one.
   *
   * @param[in] callback  A customized revocation callback object, which is implemented based on
   *                      callback class @link pdf::RevocationCallback @endlink. This should not be <b>NULL</b>.
   *
   * @return None.
   */
  void SetRevocationCallback(RevocationCallback* callback);

  /**
   * @brief Set the verifying mode to specify which validation process is to be used.
   *
   * @details Please ensure to set the verify mode before doing verifying.
   *
   * @param[in] mode  The verify mode used for express verify process. Please refer to values starting from
   *                  @link LTVVerifier::e_VerifyModeETSI @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetVerifyMode(VerifyMode mode);

  /**
   * @brief Set a customized @link pdf::TrustedCertStoreCallback @endlink object if user wants to trust some certificates.
   *
   * @details If no trusted cert store callback object is set by this function, no certificate will be trusted during verifying process.
   *
   * @param[in] callback  A customized trusted cert store callback object, which is implemented based on
   *                      callback class @link pdf::TrustedCertStoreCallback @endlink.
   *                      This can be set to <b>NULL</b> which means not to use it.
   */
  void SetTrustedCertStoreCallback(TrustedCertStoreCallback* callback);

  /**
   * @brief Verify all the signatures in the PDF document which is used to constructed current object.
   *
   * @details If verify mode is @link LTVVerifier::e_VerifyModeETSI @endlink, the verifying process will
   *          stop immediately when fail to verify any signature and return verify results
   *          for successfully verified signatures only.
   *          If verify mode is @link LTVVerifier::e_VerifyModeAcrobat @endlink, all the signatures will
   *          be verified and return verify results for all the signatures.
   *
   * @return An array of signature verify results.
   */
  SignatureVerifyResultArray Verify();

  /**
   * @brief Verify the target signature in the PDF document which is used to constructed current object.
   *
   * @param[in] signature  Target signature to be verified.
   *                       If verify mode is @link LTVVerifier::e_VerifyModeETSI @endlink, this function will
   *                       verify signatures until target signature.
   *                       If verify mode is @link LTVVerifier::e_VerifyModeAcrobat @endlink, this function will
   *                       only verify target signature.
   * 
   * @return An array of signature verify result.
   */
  SignatureVerifyResultArray VerifySignature(const Signature& signature);

  /**
   * @brief Add the verify result (as VRI information) of a signature to the DSS.
   *
   * @param[in] signature_verify_result  A signature verify result to be added to DSS.
   *
   * @return None.
   */
  void AddDSS(const SignatureVerifyResult& signature_verify_result);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit LTVVerifier(FS_HANDLE handle = NULL);
};

/** This class represents signature verify result.*/
class SignatureVerifyResult FS_FINAL : public Base{
 public:
  /**
   * @brief Enumeration for LTV state that indicates if a signature is a LTV signature.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _LTVState {
    /** @brief This means LTV is inactive. */
    e_LTVStateInactive = 0,
    /** @brief This means LTV is enabled. */
    e_LTVStateEnable = 1,
    /** @brief This means LTV is not enabled. */
    e_LTVStateNotEnable = 2
  } LTVState;
  

  /**
    * @brief Constructor, with another signature veirfy result object.
    *
    * @param[in] other  Another signature veirfy result object.
    */
  SignatureVerifyResult(const SignatureVerifyResult& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another signature veirfy result object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  SignatureVerifyResult& operator = (const SignatureVerifyResult& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another signature veirfy result object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const SignatureVerifyResult& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another signature veirfy result object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const SignatureVerifyResult& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   * 
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /** @brief Destructor. */
  ~SignatureVerifyResult();

  /**
   * @brief Get signature name.
   *
   * @return Signature name.
   */
  String GetSignatureName();
  /**
   * @brief Get signature hash value.
   *
   * @return Signature hash value.
   */
  String GetSignatureHashValue();
  /**
   * @brief Get signature state.
   *
   * @return Signature state. Please refer to values starting from @link Signature::e_StateUnknown @endlink and
   *         this would be one or combination of them.
   */
  uint32 GetSignatureState();
  /**
   * @brief Get the time that is actually used to check signature.
   *
   * @return The time that is actually used to check signature.
   *         <i>utc_hour_offset</i> and <i>utc_minite_offset</i> of this time would be ignored.
   */
  DateTime GetSignatureCheckTime();
  /**
   * @brief Get the type of the time that is actually used to check siganture.
   *
   * @return Time type. Please refer to values starting from
   *         @link LTVVerifier::e_SignatureCreationTime @endlink and this would be
   *         one of these values
   */
  LTVVerifier::TimeType GetSignatureCheckTimeType();
  /**
   * @brief Get LTV state that indicates if a signature is a LTV signature.
   *
   * @return LTV state.
   */
  LTVState GetLTVState();

  /**
   * @brief Get certificate verify results.
   *
   * @return An array of certificate verify results.
   */
  CertVerifyResultArray GetCertificateVerifyResults();

  /**
   * @brief Get signature verify results for OCSP signature of each certificate.
   *
   * @return An array of signature verify results.
   */
  SignatureVerifyResultArray GetOCSPSigantureVerifyResults();

  /**
   * @brief Get the verify result of time stamp token of this signature
   *
   * @return Verify result of time stamp token of the signature. If the signature does not have any time stamp token,
   *         returned object would be an empty object which can be checked by function @link SignatureVerifyResult::IsEmpty @endlink.
   */
  SignatureVerifyResult GetTSTSignatureVerifyResult();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit SignatureVerifyResult(FS_HANDLE handle = NULL);

};

}  // namespace pdf
}  // namespace foxit
#endif  // FS_LTVVERIFIER_H_

