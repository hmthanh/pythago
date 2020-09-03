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
 * @brief Header file for PDF siganture related definitions and classes.
 */

#ifndef FS_SIGNATURE_H_
#define FS_SIGNATURE_H_

#include "common/fs_common.h"
#include "common/file/fs_file.h"
#include "common/fs_image.h"
#include "pdf/interform/fs_pdfform.h"

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
/**
 * A digital signature (PDF 1.3) can be used to authenticate the identity of a user and the document's contents.
 * It stores information about the signer and the state of the document when it was signed. The signature is
 * contained in a signature field, as a type of form field, so class @link Signature @endlink is derived from
 * class @link interform::Field @endlink.
 * A signature object can be retrieved/added by following functions:
 * <ul>
 * <li>To be counted and retrieved as a signature object directly from PDF document, please use functions
 *     @link pdf::PDFDoc::GetSignatureCount @endlink and @link PDFDoc::GetSignature @endlink. </li>
 * <li>To be counted and retrieved as a signature field, please use functions
 *     @link interform::Form::GetFieldCount @endlink and @link interform::Form::GetField @endlink when field type is
 *     @link interform::Field::e_TypeSignature @endlink.</li>
 * <li>To add a new signature, please use function @link PDFPage::AddSignature @endlink.</li>
 * <li>To remove a signature, please use function @link PDFDoc::RemoveSignature @endlink.</li>
 * </ul>
 * In a signature, filter and sub filter keys are used to specify the filter and sub filter of
 * signature callback object which will be used to sign and verify the signature. Foxit PDF SDK has default
 * signature callbacks for following filter and sub filter:
 * <ul>
 * <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.detached"</li>
 * <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.sha1"</li>
 * <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.CAdES.detached"</li>
 * <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.RFC3161"</li>
 * </ul>
 * For sub filter "ETSI.CAdES.detached" and sub filter "ETSI.RFC3161", please ensure a default time stmap server has been
 * set to @link TimeStampServerMgr @endlink if default signature callbacks for them will be used to do signing.
 * For other filter and sub filter or if user wants to use customized signature callback for above filter and sub filter,
 * user should prepare customized signature callback and register the callback to Foxit PDF SDK by function
 * @link common::Library::RegisterSignatureCallback @endlink.<br>
 * This class offers functions to get/set signature information/properties, sign or verify a signature, and so on.
 * For example:
 * <ul>
 * <li>To sign an unsigned signature, please use functions @link Signature::StartSign @endlink.
 *     When signing a signature successfully, user is strongly recommended to close current document and
 *     then open the signed PDF document and then do following operation.</li>
 * <li>To verify the integrity of a signed signature, please use functions @link Signature::StartVerify @endlink.
       To check if a signed signature is valid or not, please refer to class @link LTVVerifier @endlink. </li>
 * <li>To retrieve signature dictionary directly, please use function @link Signature::GetSignatureDict @endlink.</li>
 * </ul>
 * Before signing an unsigned signature, user can call following functions to set information for signing and
 * signed appearance:<br>
 * <ul>
 * <li>For using default Foxit appearance template, related information can be set by
 *     @link Signature::SetAppearanceFlags @endlink, @link Signature::SetSignTime @endlink, @link Signature::SetKeyValue @endlink,
 *     @link Signature::SetBitmap @endlink, @link Signature::SetImage @endlink.</li>
 * <li>For using customized appearance, please set appearance stream content by function
 *     @link Signature::SetAppearanceContent @endlink.</li>
 * </ul>
 * If an unsigned signature has been set some information for signing, but the document is saved directly or
 * closed without signing the signature, these data (including filter and sub filter) will be lost
 * in the saved document or in the closed document. When the document is opened again, the unsigned signature needs
 * to be specified at least filter and sub filter for signing; otherwise, this signature cannot be signed.
 *
 * @see @link interform::Field @endlink
 * @see @link interform::Form @endlink
 * @see @link PDFDoc @endlink
 * @see @link PDFPage @endlink
 * @see @link TimeStampServerMgr @endlink
 * @see @link LTVVerifier @endlink
 */
class Signature FS_FINAL : public interform::Field {
 public:
  /**
   * @brief Enumeration for signature states.
   *
   * @details Values of this enumeration can be used alone or in combination.<br>
   *          These values can be divided into four parts:
   *          <ul>
   *          <li>Values starting from @link Signature::e_StateUnknown @endlink (with same prefix name) represent signed state,
   *              before signature is verified successfully.</li>
   *          <li>Values starting from @link Signature::e_StateVerifyValid @endlink (with same prefix name) represent
   *              the verified state of a signature.</li>
   *          <li>Values starting from @link Signature::e_StateVerifyIssueValid @endlink (with same prefix name) represent
   *              the verified state of issue for a signature, with more details.</li>
   *          <li>Values starting from @link Signature::e_StateVerifyTimestampNone @endlink (with same prefix name) represent
   *              the verified state for time stamp, with more details.</li>
   *          </ul>
   */
  typedef enum _States {
    /** @brief Unknown signature. */
    e_StateUnknown = 0x80000000,
    /** @brief Signature does not have any data for signing. */
    e_StateNoSignData = 0x00000200,
    /** @brief Unsigned signature.*/
    e_StateUnsigned = 0x00000001,
    /** @brief Signed signature. */
    e_StateSigned = 0x00000002,
    /** @brief Verification state of a signature is valid. */
    e_StateVerifyValid = 0x00000004,
    /** @brief Verification state of a signature is invalid. */
    e_StateVerifyInvalid = 0x00000008,
    /** @brief Signature data is destroyed (that means the signature data cannot be parsed properly). */
    e_StateVerifyErrorData = 0x00000010,
    /** @brief Unsupported signature. */
    e_StateVerifyNoSupportWay = 0x00000020,
    /** @brief Non expected byte range. */
    e_StateVerifyErrorByteRange = 0x00000040,
    /** @brief The document has been changed within the scope of the signature. (This indicates that signature is invalid.) */
    e_StateVerifyChange = 0x00000080,
    /** @brief Signature cannot be trusted (containing aggression). */
    e_StateVerifyIncredible = 0x00000100,
    /** @brief The document has not been changed within the scope of the signature. */
    e_StateVerifyNoChange = 0x00000400,
    /** @brief Verification state of the issuer is valid. */
    e_StateVerifyIssueValid = 0x00001000,
    /** @brief Verification state of the issuer is unknown. */
    e_StateVerifyIssueUnknown = 0x00002000,
    /** @brief Certificate for verifying issuer is revoked. */
    e_StateVerifyIssueRevoke = 0x00004000,
    /** @brief Certificate for verifying issuer is expired. */
    e_StateVerifyIssueExpire = 0x00008000,
    /** @brief Not check the issuer. */
    e_StateVerifyIssueUncheck = 0x00010000,
    /** @brief The verified issue is current issuer. */
    e_StateVerifyIssueCurrent = 0x00020000,
    /** @brief No time stamp or not check time stamp. */
    e_StateVerifyTimestampNone = 0x00040000,
    /** @brief The signature is a time stamp signature. */
    e_StateVerifyTimestampDoc = 0x00080000,
    /** @brief Verification state of the time stamp is valid. */
    e_StateVerifyTimestampValid = 0x00100000,
    /** @brief Verification state of the time stamp is invalid. */
    e_StateVerifyTimestampInvalid = 0x00200000,
    /** @brief Verification state of the time stamp is expired. */
    e_StateVerifyTimestampExpire = 0x00400000,
    /** @brief Verification state of the time stamp issuer is unknown. */
    e_StateVerifyTimestampIssueUnknown = 0x00800000,
    /** @brief Verification state of the time stamp issuer is valid */
    e_StateVerifyTimestampIssueValid = 0x01000000,
    /** @brief Verification state of the time stamp time is valid, since the times is before the expiration date. */
    e_StateVerifyTimestampTimeBefore = 0x02000000,
    /** @brief Cannot get verify relevant information. */
    e_StateCertCannotGetVRI = 0x04000000,
    /** @brief The document has been changed outside of signature scope, but the changed is permitted. */
    e_StateVerifyChangeLegal = 0x08000000,
    /** @brief The document has been changed outside of signature scope, and the changed invalidate the signature. */
    e_StateVerifyChangeIllegal = 0x10000000
  } States;
  
  /**
   * @brief Enumeration for signature appearance flags.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _APFlags {
    /** @brief If set, show Foxit flag on signature appearance. */
    e_APFlagFoxitFlag = 0x0001,
    /** @brief If set, show label on signature appearance. */
    e_APFlagLabel = 0x0002,
    /** @brief If set, show reason on signature appearance. */
    e_APFlagReason = 0x0004,
    /** @brief If set, show signing time on signature appearance. */
    e_APFlagSigningTime = 0x0008,
    /** @brief If set, show distinguish name on signature appearance. */
    e_APFlagDN = 0x0010,
    /** @brief If set, show location on signature appearance. */
    e_APFlagLocation = 0x0020,
    /** @brief If set, show signer on signature appearance. */
    e_APFlagSigner = 0x0040,
    /** @brief If set, show bitmap on signature appearance. */
    e_APFlagBitmap = 0x0080,
    /** @brief If set, show text content on signature appearance. */
    e_APFlagText = 0x0100
  } APFlags;
  
  /**
   * @brief Enumeration for signature key name.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _KeyName {
    /** @brief Signature key name: signer. */
    e_KeyNameSigner = 0,
    /** @brief Signature key name: location. */
    e_KeyNameLocation = 1,
    /** @brief Signature key name: reason. */
    e_KeyNameReason = 2,
    /** @brief Signature key name: contact information. */
    e_KeyNameContactInfo = 3,
    /** @brief Signature key name: distinguish name. */
    e_KeyNameDN = 4,
    /** @brief Signature key name: text content. */
    e_KeyNameText = 5
  } KeyName;
  
  /**
   * @brief Enumeration for signature digest algorithm.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _DigestAlgorithm {
    /** @brief Signature digest algorithm: sha1 algorithm. */
    e_DigestSHA1 = 0,
    /** @brief Signature digest algorithm: sha256 algorithm. */
    e_DigestSHA256 = 1,
    /** @brief Signature digest algorithm: sha384 algorithm. */
    e_DigestSHA384 = 2,
    /** @brief Signature digest algorithm: sha512 algorithm. */
    e_DigestSHA512 = 3
  } DigestAlgorithm;
  
  /**
   * @brief Enumeration for signature type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _SignatureType {
    /** @brief Signature type: ordinary. */
    e_SignatureTypeOrdinary = 0,
    /** @brief Signature type: time stamp. */
    e_SignatureTypeTimeStamp = 3
  } SignatureType;
  
  /**
   * @brief Enumeration for PAdES level.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PAdESLevel {
    /** @brief Not a PAdES signature. */
    e_PAdESLevelNotPAdES = 0,
    /** @brief PAdES level: none. */
    e_PAdESLevelNone = 1,
    /** @brief PAdES level: B-B. */
    e_PAdESLevelBB = 2,
    /** @brief PAdES level: B-T. */
    e_PAdESLevelBT = 3,
    /** @brief PAdES level: B-LT. */
    e_PAdESLevelBLT = 4,
    /** @brief PAdES level: B-LTA. */
    e_PAdESLevelBLTA = 5
  } PAdESLevel;
  
  /**
   * @brief Enumeration for signature document permission.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _DocPermission {
    /** @brief No restriction. */
    e_DocPermUnrestricted = 0,
    /**
   @brief No changes to the PDF document (which is signed by the signture) are permitted.
          Any change to this kind of PDF document will invalidate the signature.
     */
    e_DocPermNoChangesAllowed = 1,
    /** 
   @brief Permitted changes are filling in forms, instantiating page templates, and signing.
          Other changes will invalidate the signature.
     */
    e_DocPermFillingFormAndSigning = 2,
    /**
   @brief Permitted changes are the same as for 2, as well as annotation creation, deletion, and modification.
   		Other changes will invalidate the signature.
     */
    e_DocPermFillingFormSigningAndAnnotating = 3
  } DocPermission;
  
  /**
   * @brief Enumeration for signature FieldMDP("MDP" means modification detection and prevention) action type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _FieldMDPAction {
    /** @brief No Field MDP action. */
    e_FieldMDPActionNone = 0,
    /**
   @brief All form fields' flags will be set read-only.
     */
    e_FieldMDPActionAll = 1,
    /**
   @brief Specified form fields' flags will be set read-only.
   @note "Specified form fields" can be get/set by functions @link Signature::GetFieldMDPActionFields @endlink
         and @link Signature::SetFieldMDPActionFields @endlink. Please refer to these functions for more details.
     */
    e_FieldMDPActionInclude = 2,
    /**
   @brief Flags of form fields (except specified form fields) will be set read-only.
   @note "Specified form fields" can be get/set by functions @link Signature::GetFieldMDPActionFields @endlink
         and @link Signature::SetFieldMDPActionFields @endlink. Please refer to these functions for more details.
     */
    e_FieldMDPActionExclude = 3
  } FieldMDPAction;
  
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] field  Parent class object.
   */
  explicit Signature(const interform::Field& field);

  /**
   * @brief Constructor, from signature field dictionary.
   *
   * @param[in] document        A valid PDF document.
   * @param[in] sig_field_dict  A PDF dictionary which represents a signature field.
   *                            It should belong to the PDF document specified by parameter <i>document</i>;
   */
  Signature(const foxit::pdf::PDFDoc& document, foxit::pdf::objects::PDFDictionary* sig_field_dict);

  /** @brief Destructor. */
  ~Signature() {}

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Check whether current signature is signed or not.
   *
   * @return <b>true</b> means current signature is signed, and <b>false</b> means not.
   */
  bool IsSigned();

  /**
   * @brief Set document permission for current signature.
   *
   * @details This function is only useful for an unsigned signature. If this function is used for a signed signature, nothing will be done.<br>
   *          Some notes about the permission value:
   *          <ul>
   *          <li>If any permission value except @link Signature::e_DocPermUnrestricted @endlink is set to current unsigned signature,
   *              then adding new signature will fail when current signature is a signed signature.</li>
   *          <li>If permission value @link Signature::e_DocPermFillingFormAndSigning @endlink or @link Signature::e_DocPermFillingFormSigningAndAnnotating @endlink
   *              is set to current unsigned signature, then FieldMDP action would be @link Signature::e_FieldMDPActionInclude @endlink and
   *              current signature field's flag would be read-only when current signature is a signed signature.</li>
   *          </ul>
   *
   * @param[in] permission The document permission. Please refer to values
   *                       starting from @link Signature::e_DocPermUnrestricted @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetDocPermission(DocPermission permission);

  /**
   * @brief Get document permission for current signature.
   *
   * @details <ul>
   *          <li>If permission value is not @link Signature::e_DocPermUnrestricted @endlink, that means adding new signature will fail when current signature is signed</li>
   *          <li>If permission value is @link Signature::e_DocPermFillingFormAndSigning @endlink or @link Signature::e_DocPermFillingFormSigningAndAnnotating @endlink,
   *              that means current signature field's flag is read-only when current signature is signed.</li>
   *          </ul>
   *
   * @return The document permission.Please refer to values
   *         starting from @link Signature::e_DocPermUnrestricted @endlink and this should be one of these values.
   */
  DocPermission GetDocPermission();

  /**
   * @brief Set FieldMDP("MDP" means modification detection and prevention) action names array.
   *
   * @details This function is only useful for an unsigned signature. If this function is used for a signed signature, nothing will be done.<br>
   *          If current signature is signed, this function is invalidate.
   *
   * @param[in] action       FieldMDP action type.Please refer to values starting from @link Signature::e_FieldMDPActionNone @endlink
   *                         and this should be one of these values.<br>
   *                         <ul>
   *                         <li>If this value is @link Signature::e_FieldMDPActionNone @endlink, that means no FieldMDP action will be used.</li>
   *                         <li>If this value is @link Signature::e_FieldMDPActionAll @endlink, parameter <i>field_array</i> will be ignored
   *                             and all fields will be included in the object digest (and hence do not permit changes after current signature is signed).</li>
   *                         <li>If this value is @link Signature::e_FieldMDPActionInclude @endlink, that means only flags of form fields specified by
   *                             parameter <i>field_array</i> will be set read-only and these fields will be included in the object digest
   *                             (and hence do not permit changes after current signature is signed).</li>
   *                         <li>If this value is @link Signature::e_FieldMDPActionExclude @endlink, that means flags of form fields (except those specified by
   *                             parameter <i>field_array</i>) will be set read-only and these fields are included in the object digest
   *                             (and hence do not permit changes after current signature is signed).</li>
   *                         </ul>
   * @param[in] field_array  A field name array used for FieldMDP action.
   *
   * @return None.
   */
  void SetFieldMDPActionFields(const FieldMDPAction& action, const WStringArray& field_array);

  /**
   * @brief Get FieldMDP("MDP" means modification detection and prevention) action type.
   *
   * @return FieldMDP action type. Please refer to values starting from @link Signature::e_FieldMDPActionNone @endlink
   *         and this should be one of these values.
   */
  FieldMDPAction GetFieldMDPAction();

  /**
   * @brief Get the field name array which is used for FieldMDP action.
   *
   * @details Returned field name array is associated to the FieldMDP action (which can be checked by function @link Signature::GetFieldMDPAction @endlink):
   *         <ul>
   *         <li>If FieldMDP action type is @link Signature::e_FieldMDPActionNone @endlink, returned field name array is uselss.</li>
   *         <li>If FieldMDP action type is @link Signature::e_FieldMDPActionAll @endlink, returned field name array will contain name of all form fields.</li>
   *         <li>If FieldMDP action type is @link Signature::e_FieldMDPActionInclude @endlink, returned field name array specifies form fields whose flags are read-only
   *             when current signature is signed.</li>
   *         <li>If FieldMDP action type is @link Signature::e_FieldMDPActionExclude @endlink, returned field name array specifies form fields whose flags are not read-only
   *             (but rest fields' flags are read-only) when current signature is a signed signature.</li>
   *         </ul>
   *
   * @return FieldMDP action field name array. 

   */
  WStringArray GetFieldMDPActionFields();

  /**
   * @brief Start signing current signature if current signature is unsigned.
   *
   * @details This function is used for an unsigned signature. Filter and sub filter keys of current signature specify
   *          the name of signature callback object which will be used to sign current signature. So before signing,
   *          please ensure current signature has valid filter and sub filter string values. If the filter and sub filter
   *          are one of following strings that means to use the default signature callback in Foxit PDF SDK:
   *          <ul>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.sha1"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.CAdES.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.RFC3161"</li>
   *          </ul>
   *          For sub filter "ETSI.CAdES.detached" and sub filter "ETSI.RFC3161", please ensure a default time stmap server has been
   *          set to @link TimeStampServerMgr @endlink if default signature callbacks for them will be used to do signing.
   *          For other filter and sub filter or if user wants to use customized signature callback for above filter and sub filter,
   *          please ensure a customized signature callback has been registered to Foxit PDF SDK by function
   *          @link common::Library::RegisterSignatureCallback @endlink.<br>
   *          It may take a long time to sign a signature, so Foxit PDF SDK uses a progressive process to do this.
   *
   * @param[in] cert_path          A full path of a certificate file (including file name and extension),
   *                               which will be used for signing. This can be an empty string if not necessary
   *                               in custom signature callback. When this file path is not empty, it should
   *                               be a valid path.<br>
   *                               If default signature callback is to be used for signing current signature,
   *                               this can be a PFX certificate file.
   * @param[in] cert_password      A password string used to open the cert file. If this is an empty string,
   *                               that means no password is required.
   * @param[in] digest_algorithm   The algorithm of message digest for signed data. Please refer to values
   *                               starting from @link Signature::e_DigestSHA1 @endlink and this should be one of these values.
   * @param[in] save_path          A full PDF file path for saving the signing result. The signed document would be
   *                               saved to another PDF file.
   * @param[in] client_data        A user-defined object, which will be passed to call back functions in
   *                               @link SignatureCallback @endlink. This is useless if the default callback object
   *                               will be used to sign current signature. Default value: <b>NULL</b>.
   * @param[in] pause              Pause object which decides if the signing process needs to be paused. This can be
   *                               <b>NULL</b> which means not to pause during the signing process. If this is
   *                               not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                               Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   *
   * @note This function does not support to save signed PDF document directly to the PDF file which is used to
   *       construct the related PDF document of current signature. In order to do so, user is recommended to
   *       do as following steps:<br>
   *       Assume that the related PDF document object is constructed from a PDF file named "org.pdf".
   *       <ol>
   *       <li>Use current function to save the signed result to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that the related PDF document object has destructed -- which is equal to "close document".</li>
   *       <li>Remove "org.pdf" and rename "temp.tmp" to "org.pdf".</li>
   *       </ol>
   *       Then user can open the signed PDF document to do other operation.
   */
  common::Progressive StartSign(const wchar_t* cert_path, const WString& cert_password,
                                DigestAlgorithm digest_algorithm, const char* save_path,
                                const void* client_data = NULL, common::PauseCallback* pause = NULL);

  /**
   * @brief Start signing current signature if current signature is unsigned.
   *
   * @details This function is used for an unsigned signature. Filter and sub filter keys of current signature specify
   *          the name of signature callback object which will be used to sign current signature. So before signing,
   *          please ensure current signature has valid filter and sub filter string values. If the filter and sub filter
   *          are one of following strings that means to use the default signature callback in Foxit PDF SDK:
   *          <ul>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.sha1"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.CAdES.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.RFC3161"</li>
   *          </ul>
   *          For sub filter "ETSI.CAdES.detached" and sub filter "ETSI.RFC3161", please ensure a default time stmap server has been
   *          set to @link TimeStampServerMgr @endlink if default signature callbacks for them will be used to do signing.
   *          For other filter and sub filter or if user wants to use customized signature callback for above filter and sub filter,
   *          please ensure a customized signature callback has been registered to Foxit PDF SDK by function
   *          @link common::Library::RegisterSignatureCallback @endlink.<br>
   *          It may take a long time to sign a signature, so Foxit PDF SDK uses a progressive process to do this.
   *
   * @param[in] cert_file_stream   A @link foxit::common::file::StreamCallback @endlink object which is implemented by user
   *                               to access content of a certificate file which will be used for signing.
   *                               This can be <b>NULL</b> if not necessary in custom signature callback.<br>
   *                               If default signature callback is to be used for signing current signature,
   *                               a PFX certificate file can be used.
   * @param[in] cert_password      A password string used to open the cert file. If this is an empty string,
   *                               that means no password is required.
   * @param[in] digest_algorithm   The algorithm of message digest for signed data. Please refer to values
   *                               starting from @link Signature::e_DigestSHA1 @endlink and this should be one of these values.
   * @param[in] save_path          A full PDF file path for saving the signing result. The signed document would be
   *                               saved to another PDF file.
   * @param[in] client_data        A user-defined object, which will be passed to call back functions in
   *                               @link SignatureCallback @endlink. This is useless if the default callback object
   *                               will be used to sign current signature. Default value: <b>NULL</b>.
   * @param[in] pause              Pause object which decides if the signing process needs to be paused. This can be
   *                               <b>NULL</b> which means not to pause during the signing process. If this is
   *                               not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                               Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   *
   * @note This function does not support to save signed PDF document directly to the PDF file which is used to
   *       construct the related PDF document of current signature. In order to do so, user is recommended to
   *       do as following steps:<br>
   *       Assume that the related PDF document object is constructed from a PDF file named "org.pdf".
   *       <ol>
   *       <li>Use current function to save the signed result to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that the related PDF document object has destructed -- which is equal to "close document".</li>
   *       <li>Remove "org.pdf" and rename "temp.tmp" to "org.pdf".</li>
   *       </ol>
   *       Then user can open the signed PDF document to do other operation.
   */
  common::Progressive StartSign(foxit::common::file::StreamCallback* cert_file_stream, const WString& cert_password,
      DigestAlgorithm digest_algorithm, const char* save_path,
      const void* client_data = NULL, common::PauseCallback* pause = NULL);

  /**
   * @brief Start signing current signature if current signature is unsigned.
   *
   * @details This function is used for an unsigned signature. Filter and sub filter keys of current signature specify
   *          the name of signature callback object which will be used to sign current signature. So before signing,
   *          please ensure current signature has valid filter and sub filter string values. If the filter and sub filter
   *          are one of following strings that means to use the default signature callback in Foxit PDF SDK:
   *          <ul>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.sha1"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.CAdES.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.RFC3161"</li>
   *          </ul>
   *          For other filter and sub filter or if user wants to use customized signature callback for above filter and sub filter,
   *          please ensure a customized signature callback has been registered to Foxit PDF SDK by function
   *          @link common::Library::RegisterSignatureCallback @endlink.<br>
   *          It may take a long time to sign a signature, so Foxit PDF SDK uses a progressive process to do this.
   *
   * @param[in] cert_path          A full path of a certificate file (including file name and extension),
   *                               which will be used for signing. This can be an empty string if not necessary
   *                               in custom signature callback. When this file path is not empty, it should
   *                               be a valid path.<br>
   *                               If default signature callback is to be used for signing current signature,
   *                               this can be a PFX certificate file.
   * @param[in] cert_password      A password string used to open the cert file. If this is an empty string,
   *                               that means no password is required.
   * @param[in] digest_algorithm   The algorithm of message digest for signed data. Please refer to values
   *                               starting from @link Signature::e_DigestSHA1 @endlink and this should be one of these values.
   * @param[in] save_path          A full PDF file path for saving the signing result. The signed document would be
   *                               saved to another PDF file.
   * @param[in] client_data        A user-defined object, which will be passed to call back functions in
   *                               @link SignatureCallback @endlink. This is useless if the default callback object
   *                               will be used to sign current signature. Default value: <b>NULL</b>.
   * @param[in] pause              Pause object which decides if the signing process needs to be paused. This can be
   *                               <b>NULL</b> which means not to pause during the signing process. If this is
   *                               not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                               Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   *
   * @note This function does not support to save signed PDF document directly to the PDF file which is used to
   *       construct the related PDF document of current signature. In order to do so, user is recommended to
   *       do as following steps:<br>
   *       Assume that the related PDF document object is constructed from a PDF file named "org.pdf".
   *       <ol>
   *       <li>Use current function to save the signed result to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that the related PDF document object has destructed -- which is equal to "close document".</li>
   *       <li>Remove "org.pdf" and rename "temp.tmp" to "org.pdf".</li>
   *       </ol>
   *       Then user can open the signed PDF document to do other operation.
   */
   common::Progressive StartSign(const wchar_t* cert_path, const WString& cert_password,
      DigestAlgorithm digest_algorithm, const wchar_t* save_path,
      const void* client_data = NULL, common::PauseCallback* pause = NULL);

  /**
   * @brief Start signing current signature if current signature is unsigned.
   *
   * @details This function is used for an unsigned signature. Filter and sub filter keys of current signature specify
   *          the name of signature callback object which will be used to sign current signature. So before signing,
   *          please ensure current signature has valid filter and sub filter string values. If the filter and sub filter
   *          are one of following strings that means to use the default signature callback in Foxit PDF SDK:
   *          <ul>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.sha1"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.CAdES.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.RFC3161"</li>
   *          </ul>
   *          For other filter and sub filter or if user wants to use customized signature callback for above filter and sub filter,
   *          please ensure a customized signature callback has been registered to Foxit PDF SDK by function
   *          @link common::Library::RegisterSignatureCallback @endlink.<br>
   *          It may take a long time to sign a signature, so Foxit PDF SDK uses a progressive process to do this.
   *
   * @param[in] cert_file_stream   A @link foxit::common::file::StreamCallback @endlink object which is implemented by user
   *                               to access content of a certificate file which will be used for signing.
   *                               This can be <b>NULL</b> if not necessary in custom signature callback.<br>
   *                               If default signature callback is to be used for signing current signature,
   *                               a PFX certificate file can be used.
   * @param[in] cert_password      A password string used to open the cert file. If this is an empty string,
   *                               that means no password is required.
   * @param[in] digest_algorithm   The algorithm of message digest for signed data. Please refer to values
   *                               starting from @link Signature::e_DigestSHA1 @endlink and this should be one of these values.
   * @param[in] save_path          A full PDF file path for saving the signing result. The signed document would be
   *                               saved to another PDF file.
   * @param[in] client_data        A user-defined object, which will be passed to call back functions in
   *                               @link SignatureCallback @endlink. This is useless if the default callback object
   *                               will be used to sign current signature. Default value: <b>NULL</b>.
   * @param[in] pause              Pause object which decides if the signing process needs to be paused. This can be
   *                               <b>NULL</b> which means not to pause during the signing process. If this is
   *                               not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                               Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   *
   * @note This function does not support to save signed PDF document directly to the PDF file which is used to
   *       construct the related PDF document of current signature. In order to do so, user is recommended to
   *       do as following steps:<br>
   *       Assume that the related PDF document object is constructed from a PDF file named "org.pdf".
   *       <ol>
   *       <li>Use current function to save the signed result to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that the related PDF document object has destructed -- which is equal to "close document".</li>
   *       <li>Remove "org.pdf" and rename "temp.tmp" to "org.pdf".</li>
   *       </ol>
   *       Then user can open the signed PDF document to do other operation.
   */
   common::Progressive StartSign(foxit::common::file::StreamCallback* cert_file_stream, const WString& cert_password,
       DigestAlgorithm digest_algorithm, const wchar_t* save_path,
       const void* client_data = NULL, common::PauseCallback* pause = NULL);

  /**
   * @brief Start signing current signature if current signature is unsigned.
   *
   * @details This function is used for an unsigned signature. Filter and sub filter keys of current signature specify
   *          the name of signature callback object which will be used to sign current signature. So before signing,
   *          please ensure current signature has valid filter and sub filter string values. If the filter and sub filter
   *          are one of following strings that means to use the default signature callback in Foxit PDF SDK:
   *          <ul>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.sha1"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.CAdES.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.RFC3161"</li>
   *          </ul>
   *          For sub filter "ETSI.CAdES.detached" and sub filter "ETSI.RFC3161", please ensure a default time stmap server has been
   *          set to @link TimeStampServerMgr @endlink if default signature callbacks for them will be used to do signing.
   *          For other filter and sub filter or if user wants to use customized signature callback for above filter and sub filter,
   *          please ensure a customized signature callback has been registered to Foxit PDF SDK by function
   *          @link common::Library::RegisterSignatureCallback @endlink.<br>
   *          It may take a long time to sign a signature, so Foxit PDF SDK uses a progressive process to do this.
   *
   * @param[in] cert_path          A full path of a certificate file (including file name and extension),
   *                               which will be used for signing. This can be an empty string if not necessary
   *                               in custom signature callback. When this file path is not empty, it should
   *                               be a valid path.<br>
   *                               If default signature callback is to be used for signing current signature,
   *                               this can be a PFX certificate file.
   * @param[in] cert_password      A password string used to open the cert file. If this is an empty string,
   *                               that means no password is required.
   * @param[in] digest_algorithm   The algorithm of message digest for signed data. Please refer to values
   *                               starting from @link Signature::e_DigestSHA1 @endlink and this should be one of these values.
   * @param[in] stream_callback    A @link foxit::common::file::StreamCallback @endlink object which is implemented by user to save the signing result.
   *                               The signed document would be saved to another PDF file.
   * @param[in] client_data        A user-defined object, which will be passed to call back functions in
   *                               @link SignatureCallback @endlink. This is useless if the default callback object
   *                               will be used to sign current signature. Default value: <b>NULL</b>.
   * @param[in] pause              Pause object which decides if the signing process needs to be paused. This can be
   *                               <b>NULL</b> which means not to pause during the signing process. If this is
   *                               not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                               Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   *
   * @note This function does not support to save signed PDF document directly to the PDF file which is used to
   *       construct the related PDF document of current signature. In order to do so, user is recommended to
   *       do as following steps:<br>
   *       Assume that the related PDF document object is constructed from a PDF file named "org.pdf".
   *       <ol>
   *       <li>Use current function to save the signed result to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that the related PDF document object has destructed -- which is equal to "close document".</li>
   *       <li>Remove "org.pdf" and rename "temp.tmp" to "org.pdf".</li>
   *       </ol>
   *       Then user can open the signed PDF document to do other operation.
   */
  common::Progressive StartSign(const wchar_t* cert_path, const foxit::WString& cert_password,
                                foxit::pdf::Signature::DigestAlgorithm digest_algorithm, foxit::common::file::StreamCallback* stream_callback,
                                const void* client_data = NULL, foxit::common::PauseCallback* pause = NULL);

  /**
   * @brief Start signing current signature if current signature is unsigned.
   *
   * @details This function is used for an unsigned signature. Filter and sub filter keys of current signature specify
   *          the name of signature callback object which will be used to sign current signature. So before signing,
   *          please ensure current signature has valid filter and sub filter string values. If the filter and sub filter
   *          are one of following strings that means to use the default signature callback in Foxit PDF SDK:
   *          <ul>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.sha1"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.CAdES.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.RFC3161"</li>
   *          </ul>
   *          For sub filter "ETSI.CAdES.detached" and sub filter "ETSI.RFC3161", please ensure a default time stmap server has been
   *          set to @link TimeStampServerMgr @endlink if default signature callbacks for them will be used to do signing.
   *          For other filter and sub filter or if user wants to use customized signature callback for above filter and sub filter,
   *          please ensure a customized signature callback has been registered to Foxit PDF SDK by function
   *          @link common::Library::RegisterSignatureCallback @endlink.<br>
   *          It may take a long time to sign a signature, so Foxit PDF SDK uses a progressive process to do this.
   *
   * @param[in] cert_file_stream   A @link foxit::common::file::StreamCallback @endlink object which is implemented by user
   *                               to access content of a certificate file which will be used for signing.
   *                               This can be <b>NULL</b> if not necessary in custom signature callback.<br>
   *                               If default signature callback is to be used for signing current signature,
   *                               a PFX certificate file can be used.
   * @param[in] cert_password      A password string used to open the cert file. If this is an empty string,
   *                               that means no password is required.
   * @param[in] digest_algorithm   The algorithm of message digest for signed data. Please refer to values
   *                               starting from @link Signature::e_DigestSHA1 @endlink and this should be one of these values.
   * @param[in] stream_callback    A @link foxit::common::file::StreamCallback @endlink object which is implemented by user to save the signing result.
   *                               The signed document would be saved to another PDF file.
   * @param[in] client_data        A user-defined object, which will be passed to call back functions in
   *                               @link SignatureCallback @endlink. This is useless if the default callback object
   *                               will be used to sign current signature. Default value: <b>NULL</b>.
   * @param[in] pause              Pause object which decides if the signing process needs to be paused. This can be
   *                               <b>NULL</b> which means not to pause during the signing process. If this is
   *                               not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                               Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   *
   * @note This function does not support to save signed PDF document directly to the PDF file which is used to
   *       construct the related PDF document of current signature. In order to do so, user is recommended to
   *       do as following steps:<br>
   *       Assume that the related PDF document object is constructed from a PDF file named "org.pdf".
   *       <ol>
   *       <li>Use current function to save the signed result to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that the related PDF document object has destructed -- which is equal to "close document".</li>
   *       <li>Remove "org.pdf" and rename "temp.tmp" to "org.pdf".</li>
   *       </ol>
   *       Then user can open the signed PDF document to do other operation.
   */
   common::Progressive StartSign(foxit::common::file::StreamCallback* cert_file_stream, const foxit::WString& cert_password,
      foxit::pdf::Signature::DigestAlgorithm digest_algorithm, foxit::common::file::StreamCallback* stream_callback,
      const void* client_data = NULL, foxit::common::PauseCallback* pause = NULL);

  /**
   * @brief Start verifying the intergrity of current signature if current signature is signed.
   *
   * @details This function is used for a signed signature. Filter and sub filter keys of current signature specify
   *          the name of signature callback object which will be used to verify current signature. So before verifying,
   *          please ensure: the necessary signature callback object has been registered by function
   *          @link common::Library::RegisterSignatureCallback @endlink. If the filter and sub filter of current signed signature
   *          are one of following strings that means to use the default signature callback in Foxit PDF SDK and
   *          user does not need to register one for them:
   *          <ul>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.sha1"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.CAdES.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.RFC3161"</li>
   *          </ul>
   *          It may take a long time to verify a signature, so Foxit PDF SDK uses a progressive process to do this.<br>
   *          From 7.0, this function is only used to verify the intergrity of a signature. To check if a signature is valid or not,
   *          please refer to class @link LTVVerifier @endlink.
   *
   * @param[in] client_data  A user-defined object, which will be passed to call back functions in
   *                         @link SignatureCallback @endlink. This is useless if the default callback object will be
   *                         used to verify current signature. Default value: <b>NULL</b>.
   * @param[in] pause        Pause object which decides if the verifying process needs to be paused.
   *                         This can be <b>NULL</b> which means not to pause during the verifying process.
   *                         If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                         Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartVerify(const void* client_data = NULL, common::PauseCallback* pause = NULL);

  /**
   * @brief Get certificate information.
   *
   * @details This function is used for a signed signature.
   *          Currently, this function only supports for iOS and android platform.
   *
   * @param[in] key  Certificate key string. Currently it can be one of the following keys:<br>
   *                 <ul>
   *                 <li>"SerialNumber"</li>
   *                 <li>"Issuer"</li>
   *                 <li>"Subject"</li>
   *                 <li>"ValidPeriodFrom"</li>
   *                 <li>"ValidPeriodTo"</li>
   *                 </ul>
   *
   * @return Certificate information string.
   *
   * @note For "ValidPeriodFrom" or "ValidPeriodTo" key, timezone value will not be computed in.
   */
  String GetCertificateInfo(const char* key);

  /**
   * @brief Get the byte ranges data, including 4 elements.
   *
   * @details This function is used for a signed signature to retrieve its byte range for digest calculation.
   *          The array of byte ranges contains 4 elements. These 4 elements are always in pairs of
   *          integers (starting byte offset, length in bytes), describing the exact byte range
   *          for the digest calculation.<br>
   *          Please refer to <PDF Reference 1.7> Section 8.7 Digital Signatures for more details.
   *
   * @param[out] out_byte_range_array  Output parameter that receives data of byte ranges.
   *                                   Please ensure this array can contain 4 elements.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool GetByteRangeArray(uint32 out_byte_range_array[4]);

  /**
   * @brief Get current state.
   *
   * @details <ul>
   *          <li>Before verifying a signature, this function is to get the state about if current signature is signed
   *              or if current signature is lack of data for signing.</li>
   *          <li>After verifying a signature, this function is to get the verified state -- which indicates that
   *              the verified signature is signed; if the verified signature is still unsigned, this function will
   *              get the unsigned state instead.</li>
   *          </ul>
   *
   * @return The value of signature state. Please refer to values starting from @link Signature::e_StateUnknown @endlink and
   *         this would be one or combination of them.<br>
   *         Specially, if the returned state is @link Signature::e_StateNoSignData @endlink,
   *         that means current signature has no data for signing, and please at least call function
   *         @link Signature::SetKeyValue @endlink to set necessary filter and sub filter to current signature.
   *         Use can also call following functions to set other data for signing and signed appearance before calling
   *         function @link Signature::StartSign @endlink:<br>
   *         <ul>
   *         <li>For using default Foxit appearance template, related information can be set by
   *             @link Signature::SetAppearanceFlags @endlink, @link Signature::SetSignTime @endlink,
   *             @link Signature::SetKeyValue @endlink, @link Signature::SetBitmap @endlink, @link Signature::SetImage @endlink.</li>
   *         <li>For using customized appearance, please set appearance stream content by function
   *             @link Signature::SetAppearanceContent @endlink.</li>
   *         </ul>
   */
  uint32 GetState();

  /**
  * @brief Clear the data and appearance if current signature is singed and verified valid.
  *
  * @details This function is used for a signed and valid signature.<br>
  *          Attention: From 7.0, this function is only used to verify the intergrity of a signature.
  *          To check if a signature is valid or not, please refer to class @link LTVVerifier @endlink.
  *
  * @return <b>true</b> means clear the data and appearance successfully, while <b>false</b> means no need to
  *         clear data and appearance or any error.
  */
  bool ClearSignedData();

  /**
  * @brief Get the PDF document, which current signature belongs to.
  *
  * @return A PDF document object.
  */
  PDFDoc GetDocument();

  /**
   * @brief Get the PDF document in the signed version in which current signature was signed.
   *
   * @details This function is useful when a PDF document has benn signed by serveral signatures and user wants to
   *          get the PDF document in which one signature is signed. 
   *
   * @param[in] file_path   The full path of the original opened PDF document which current signature belongs to. It should not be an empty string.
   *
   * @return A PDF document object in singed version in which current signature was signed.
   *         The returned PDF document may represent a differenct PDF document from current PDF document where current signature is retrieved., or is just current PDF document.
   *         User should ensure to keep current PDF document object valid when reading or operating signed version document.
   *         Please ensure the returned document object has been loaded successfully, before using most functions in class @link PDFDoc @endlink.
   *
   */
  PDFDoc GetSignedVersionDocument(const wchar_t* file_path);

  /**
  * @brief Get signature appearance flags.
  *
  * @details Signature appearance flags indicate which information will be shown.
  *          Currently, this is only useful after @link Signature::SetAppearanceFlags @endlink is set successfully.
  *          For a signature gotten from PDF document, the return value of this function would be useless.
  *
  * @return Signature appearance flags. Please refer to values starting from @link Signature::e_APFlagFoxitFlag @endlink and
  *         this would be one or a combination of these values.
  */
  uint32 GetAppearanceFlags();

  /**
  * @brief Set signature appearance flags.
  *
  * @details This function is recommended to be used before calling function @link Signature::StartSign @endlink for
  *          an unsigned signature. <br>
  *          Signature appearance flags indicate which information will be shown in the signed appearance.
  *          If customized appearance content has been set by function @link Signature::SetAppearanceContent @endlink,
  *          appearance flags will be ignored.<br>
  *          If current signature is a time stamp signature, this function will do nothing.
  *
  * @param[in] appearance_flags  Signature appearance flags. Please refer to values starting from
  *                              @link Signature::e_APFlagFoxitFlag @endlink and this should be
  *                              one or a combination of these values.
  *
  * @return None.
  */
  void SetAppearanceFlags(uint32 appearance_flags);

  /**
  * @brief Set customized appearance content (as low level drawing operation commands)
  *        for signed signature appearance.
  *
  * @details This function can only be used for an unsigned signature before calling function
  *          @link Signature::StartSign @endlink for the unsigned signature.<br>
  *          Once customized appearance content is set, it will be used as the signed appearance. In this case,
  *          appearance flags set by @link Signature::SetAppearanceFlags @endlink will be ignored and
  *          related informations will not be used in appearance -- these information are set by:
  *          @link Signature::SetSignTime @endlink, @link Signature::SetKeyValue @endlink (except filter and sub-filter),
  *          @link Signature::SetBitmap @endlink, @link Signature::SetImage @endlink.<br>
  *          If current signature is a time stamp signature, this function will do nothing.
  *
  * @param[in] appearance_content  Customized appearance content. This should be sequence of drawing operation commands
  *                                to be used for the appearance, for example "10 10 m 20 10 l S". Please refer to
  *                                <PDF Reference 1.7> P196 for more details.
  *
  * @return None.
  */
  void SetAppearanceContent(const String& appearance_content);

  /**
  * @brief Get time of signing.
  *
  * @return A date and time object that receives the signing time.
  *         If no signing time is found, this function will return a date and time object with all values 0.
  */
  DateTime GetSignTime();

  /**
  * @brief Set time of signing.
  *
  * @details This function is recommended to be used before calling function @link Signature::StartSign @endlink for
  *          an unsigned signature.
  *
  * @param[in] sign_time  The signing time.
  *
  * @return None.
  */
  void SetSignTime(const DateTime& sign_time);

  /**
   * @brief Get filter.
   *
   * @details Filter and sub filter are used to specify which registered signature callback object will be used to
   *          sign/verify current signature.
   *
   * @return Filter string.
   */
  String GetFilter();
  /**
   * @brief Set filter.
   *
   * @details Filter and sub filter are used to specify which registered signature callback object will
   *          be used to sign/verify current signature. User could should set filter and sub filter to
   *          use default signature callback in Foxit PDF SDK, or use other filter and sub fitler but please
   *          ensure that a signature callback object with non-default filter and sub filter should has been
   *          registered in Foxit PDF SDK before signing or verifying current signature.
   *          Filter and sub filter for default signature callback are:
   *          <ul>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.sha1"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.CAdES.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.RFC3161"</li>
   *          </ul>
   *
   * @param[in] filter  String for filter. It cannot be an empty string.
   *
   * @return None.
   */
  void SetFilter(const char* filter);

  /**
   * @brief Get sub filter.
   *
   * @details Filter and sub filter are used to specify which registered signature callback object will be used to
   *          sign/verify current signature.
   *
   * @return Sub filter string.
   */
  String GetSubFilter();
  /**
   * @brief Set sub filter.
   *
   * @details Filter and sub filter are used to specify which registered signature callback object will
   *          be used to sign/verify current signature. User could should set filter and sub filter to
   *          use default signature callback in Foxit PDF SDK, or use other filter and sub fitler but please
   *          ensure that a signature callback object with non-default filter and sub filter should has been
   *          registered in Foxit PDF SDK before signing or verifying current signature.
   *          Filter and sub filter for default signature callback are:
   *          <ul>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.sha1"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.CAdES.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.RFC3161"</li>
   *          </ul>
   *
   * @param[in] sub_filter  String for sub filter.
   *
   * @return None.
   */
  void SetSubFilter(const char* sub_filter);

  /**
   * @brief Get the string value for specified key name.
   *
   * @details This function is used to get string value of some key in signature dictionary, such as "Reason",
   *          "Location" and so on. Specially,
   *
   * @param[in] key  Key name. Please refer to values starting from @link Signature::e_KeyNameSigner @endlink and
   *                 this should be one of these values.
   *
   * @return The string value.
   */
  WString GetKeyValue(KeyName key);

  /**
   * @brief Set the string value for specified key name.
   *
   * @details This function is recommended to be used before calling function @link Signature::StartSign @endlink for
   *          an unsigned signature.<br>
   *          This function is used to set string value of some key in signature dictionary, such as signer, reason,
   *          location and so on.<br>
   *          If current signature is a time stamp signature, this function will do nothing.
   *
   * @param[in] key    Key name. Please refer to values starting from @link Signature::e_KeyNameSigner @endlink and
   *                   this should be one of these values.
   * @param[in] value  New string value.
   *
   * @return None.
   */
  void SetKeyValue(KeyName key, const wchar_t* value);

  /**
   * @brief Get a bitmap which is used for the signature appearance.
   *
   * @return The bitmap used in appearance. If the return value of function @link common::Bitmap::IsEmpty @endlink for
   *         the returned bitmap object is <b>true</b>, that means no bitmap is used in appearance or there is any error.
   */
  common::Bitmap GetBitmap();

  /**
   * @brief Set a bitmap for the signature appearance.
   *
   * @details This function is recommended to be used before calling function @link Signature::StartSign @endlink for
   *          an unsigned signature. If customized appearance content has been set by function
   *          @link Signature::SetAppearanceContent @endlink, the bitmap will not be used in signed appearance.<br>
   *          If current signature is a time stamp signature, this function will do nothing.
   *
   * @param[in] bitmap  A bitmap to be set to the appearance. It should be valid.
   *
   * @return None.
   */
  void SetBitmap(const common::Bitmap& bitmap);

  /**
   * @brief Set an image for the signature appearance, with a specified frame index.
   *
   * @details This function is recommended to be used before calling function @link Signature::StartSign @endlink for
   *          an unsigned signature. If customized appearance content has been set by function
   *          @link Signature::SetAppearanceContent @endlink, the image will not be used in signed appearance.<br>
   *          Input image may contain multiple frames, and only one frame of the image can be set to current signature.<br>
   *          If current signature is a time stamp signature, this function will do nothing.
   *
   * @param[in] image        An image. One of its frames will be set to current signature. This image contains at least
   *                         one frame and the image type should not be @link common::Image::e_Unknown @endlink.
   * @param[in] frame_index  Frame index. Valid range: from 0 to (<i>count</i>-1).
   *                         <i>count</i> is returned by function @link common::Image::GetFrameCount @endlink.
   *
   * @return None.
   */
  void SetImage(const common::Image& image, int frame_index);

  /**
   * @brief Set an image for the signature appearance, with a specified frame index.
   *
   * @details This function is recommended to be used before calling function @link Signature::StartSign @endlink for
   *          an unsigned signature. If customized appearance content has been set by function
   *          @link Signature::SetAppearanceContent @endlink, the image will not be used in signed appearance.<br>
   *          Input image may contain multiple frames, and only one frame of the image can be set to current signature.<br>
   *          If current signature is a time stamp signature, this function will do nothing.
   *
   * @param[in] file_path    A full path of an existing image file. It should not be an empty string.
   * @param[in] frame_index  Frame index. Valid range: from 0 to (<i>count</i>-1).
   *                         <i>count</i> is returned by function @link common::Image::GetFrameCount @endlink
   *                         of input image file.
   *
   * @return None.
   */
  void SetImage(const char* file_path, int frame_index);

  /**
   * @brief Set an image for the signature appearance, with a specified frame index.
   *
   * @details This function is recommended to be used before calling function @link Signature::StartSign @endlink for
   *          an unsigned signature. If customized appearance content has been set by function
   *          @link Signature::SetAppearanceContent @endlink, the image will not be used in signed appearance.<br>
   *          Input image may contain multiple frames, and only one frame of the image can be set to current signature.<br>
   *          If current signature is a time stamp signature, this function will do nothing.
   *
   * @param[in] file_path    A full path of an existing image file. It should not be an empty string.
   * @param[in] frame_index  Frame index. Valid range: from 0 to (<i>count</i>-1).
   *                         <i>count</i> is returned by function @link common::Image::GetFrameCount @endlink
   *                         of input image file.
   *
   * @return None.
   */
  void SetImage(const wchar_t* file_path, int frame_index);

  /**
   * @brief Get signature dictionary.
   *
   * @details Signature dictionary is a part of signature field dictionary.
   *
   * @return The signature dictionary.
   */
  objects::PDFDictionary* GetSignatureDict() const;

  /**
  * @brief Set the default length of signature contents which represents signature value (known as signed data).
  *
  * @details This function can only be used before function @link Signature::StartSign @endlink
  *          for an unsigned signature.<br>
  *          Signature contents represent the signature value (known as signed data).
  *          When initializing the signature field, the signature contents will be initialized with
  *          the default length 7942. When using custom signature callback to sign and verify an unsigned signature,
  *          user can call this function to change the default length of signature contents. In this case,
  *          user should also ensure that the length of returned signed data in callback function
  *          @link SignatureCallback::Sign @endlink should not be larger than the default length set by this function.
  *
  * @param[in] default_length  The default length of the signature value (known as signed data), in bytes.
  *                            It should not be less than 4098.
  *
  * @return None.
  */
  void SetDefaultContentsLength(uint32 default_length);

  /**
   * @brief Get the count of certificates in current signature's certificate chain.
   *
   * @details This function is recommended to be used before verifying a signature.
   *          When sub filter of current signature is "adbe.x509.rsa_sha1", application needs to call this function to
   *          get the count of certificates in certificate chain and then call function @link Signature::GetCert @endlink
   *          to get verified public certificate before verifying signature.
   *
   * @return The count of certificates.
   */
  int32 GetCertCount() const;

  /**
   * @brief Get a certificate from current signature's certificate chain by index.
   *
   * @details This function is recommended to be used before verifying a signature.
   *          When sub filter of current signature is "adbe.x509.rsa_sha1", application needs to call this function to
   *          get verified public certificate before verifying signature.
   *          The first certificate in certificate chain is the signing certificate, and it can be used to
   *          verify the signature.
   *
   * @param[in] index  The index of certificate to be gotten. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Signature::GetCertCount @endlink.
   *
   * @return A certificate.
   */
  WString GetCert(int32 index) const;

  /**
   * @brief Set a certificate chain.
   *
   * @details This function is recommended to be used before signing an unsigned signature.
   *          When the signature sub filter is "adbe.x509.rsa_sha1", users need to call this function to
   *          set the cert chain to the signature. For other sub filter, this function will return directly without
   *          doing anything.
   *
   * @param[in] cert_chain  A string array that represents the certificate chain.
   *
   * @return None.
   */
  void SetCertChain(const WStringArray& cert_chain);

  /**
   * @brief Get signature type.
   *
   * @return Signature type. Please refer to values starting from
   *         @link Signature::e_SignatureTypeOrdinary @endlink and this would be one of these values.
   */
  SignatureType GetSignatureType();

  /**
   * @brief Check if current signature is a time stamp signature.
   *
   * @return <b>true</b> means current signature is a time stamp signature, while <b>false</b> means not.
   */
  bool IsTimeStamp();

  /**
   * @brief Get PAdES level.
   *
   * @return PAdES level. Please refer to values starting from
   *         @link Signature::e_PAdESLevelNotPAdES @endlink and this would be one of these values.
   */
  PAdESLevel GetPAdESLevel();

#ifndef __EMSCRIPTEN_RENDER__
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Signature(FS_HANDLE handle = NULL);
#endif
};

/**
 * This class represent a callback object to sign or verify signature.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user,
 * in order to sign or verify signature in a customized way.<br>
 * User can set register customized signature callback object to Foxit PDF SDK by function
 * @link common::Library::RegisterSignatureCallback @endlink with filter and sub filter as the callback name.
 *
 * @see @link common::Library @endlink
 */
class SignatureCallback {
 public:
  /**
  * @brief Enumeration for certificate validity.
  *
  * @details Values of this enumeration should be used alone.
  */
  typedef enum _CertValidity {
    /** @brief Certificate is valid. */
    e_CertValid = 0,
    /** @brief Certificate is expired. */
    e_CertExpired = 1,
    /** @brief Certificate is unsupport type. */
    e_CertUnsupportType = 2,
    /** @brief Certificate's data is error. */
    e_CertDataError = 3,
    /** @brief Certificate's password is wrong. */
    e_CertInvalidPassword = 4,
    /** @brief Certificate's path is wrong. */
    e_CertInvalidPath = 5,
    /** @brief Certificate is not set to sign a signature. */
    e_CertNotSet = 6,
    /** @brief Certificate's private key cannot be gotten. */
    e_CertCannotGetPrivateKey = 7
  } CertValidity;
  

  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function used to start a custom digest calculation, mainly to initialize the calculation process.
   *
   * @param[in] file              When signing a signature, this represents the source file object to be signed.<br>
   *                              When verifying a signature field, this represents the source file object
   *                              to be verified.
   * @param[in] byte_range_array  A byte range array of the signed document(not the source document).<br>
   *                              Elements in this array always be in pairs of offset-size values in order of:
   *                              offset,size,offset,size...
   * @param[in] size_of_array     Count of elements in the byte range array <i>byte_range_array</i>.
   * @param[in] signature         A signature object.
   * @param[in] client_data       A user-defined object, which is passed by user from function
   *                              @link Signature::StartSign @endlink, @link Signature::StartVerify @endlink.
   *
   * @return <b>true</b> means the calculation process is successfully started and then
   *         @link SignatureCallback::ContinueCalcDigest @endlink will be triggered to continue the calculation process.
   *         <b>false</b> means fail to start a calculation process.
   */
  virtual bool StartCalcDigest(const common::file::ReaderCallback* file, const uint32* byte_range_array,
                               uint32 size_of_array, const Signature& signature, const void* client_data) = 0;

  /**
   * @brief A callback function used to continue the custom digest calculation process.
   *
   * @param[in] pause        Pause object which decides if the calculation process needs to be paused.
   *                         If this is <b>NULL</b>, it means not to pause during the calculation process.
   *                         If this is not <b>NULL</b>, please check the the return value of
   *                         function NeedToPauseNow() of this input parameter and decide when to pause
   *                         the calculation process.
   * @param[in] client_data  A user-defined object, which is passed by user from function
   *                         @link Signature::StartSign @endlink or @link Signature::StartVerify @endlink.
   *
   * @return @link common::Progressive::e_Finished @endlink means the rendering is finished
   *         successfully.<br>
   *         @link common::Progressive::e_ToBeContinued @endlink means the calculation
   *         process is not finished yet and callback function @link SignatureCallback::ContinueCalcDigest @endlink
   *         would be triggered again to continue the process.<br>
   *         @link common::Progressive::e_Error @endlink means any error occurs.
   */
  virtual common::Progressive::State ContinueCalcDigest(const void* client_data,
                                                          const common::PauseCallback* pause) = 0;

  /**
   * @brief A callback function used to get the digest after the calculation process is finished.
   *
   * @details This callback function will be triggered when the calculation process is finished successfully.
   *
   * @param[in] client_data  A user-defined object, which is passed by user from function
   *                         @link Signature::StartSign @endlink or @link Signature::StartVerify @endlink.
   *
   * @return The digest string.
   *         If there is any error, please return an empty string.
   */
  virtual String GetDigest(const void* client_data) = 0;

  /**
   * @brief A callback function used to do signing and return the signed data.
   *
   * @details Host application provides this callback function for custom sign mechanism.
   *          This callback function would be triggered during the signature signing process.
   *
   * @param[in] digest            The digest data buffer, for source file buffer to be signed.
   * @param[in] digest_length     The size of digest data buffer.
   * @param[in] cert_path         The certificate file path, which will be used for signing.
   * @param[in] cert_password     The password string, used to open the cert file. If this is an empty string,
   *                              that means no password is required.
   * @param[in] digest_algorithm  The algorithm of message digest for signed data. Please refer to values
   *                              starting from @link Signature::e_DigestSHA1 @endlink and this would be one of these values.
   * @param[in] client_data       A user-defined object, which is passed by user from function
   *                              @link Signature::StartSign @endlink or @link Signature::StartVerify @endlink.
   *
   * @return Signed data. If there is any error, please return an empty string.<br>
   *         The length of returned signed data should be within the default length of signature contents
   *         which is 7942 by default or specified by fucntion @link Signature::SetDefaultContentsLength @endlink
   *         before signing the unsigned signature.
   */
  virtual String Sign(const void* digest, uint32 digest_length, const wchar_t* cert_path,
                      const WString& cert_password, Signature::DigestAlgorithm digest_algorithm,
                      void* client_data) = 0;

  /**
   * @brief A callback function used to do signing and return the signed data.
   *
   * @details Host application provides this callback function for custom sign mechanism.
   *          This callback function would be triggered during the signature signing process.
   *
   * @param[in] digest            The digest data buffer, for source file buffer to be signed.
   * @param[in] digest_length     The size of digest data buffer.
   * @param[in] cert_file_stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user
   *                              to access content of a certificate file which will be used for signing.
   * @param[in] cert_password     The password string, used to open the cert file. If this is an empty string,
   *                              that means no password is required.
   * @param[in] digest_algorithm  The algorithm of message digest for signed data. Please refer to values
   *                              starting from @link Signature::e_DigestSHA1 @endlink and this would be one of these values.
   * @param[in] client_data       A user-defined object, which is passed by user from function
   *                              @link Signature::StartSign @endlink or @link Signature::StartVerify @endlink.
   *
   * @return Signed data. If there is any error, please return an empty string.<br>
   *         The length of returned signed data should be within the default length of signature contents
   *         which is 7942 by default or specified by fucntion @link Signature::SetDefaultContentsLength @endlink
   *         before signing the unsigned signature.
   */
  virtual String Sign(const void* digest, uint32 digest_length, foxit::common::file::StreamCallback* cert_file_stream,
      const WString& cert_password, Signature::DigestAlgorithm digest_algorithm,
      void* client_data) = 0;

  /**
   * @brief A callback function used to verify the integrity of a signature and return the verify state.
   *
   * @details Host application provides this callback function for custom sign mechanism.
   *          This callback function would be triggered during the signature verifying process.<br>
   *          From 7.0, this callback function is only used to verify the intergrity of a signature.
   *          Please check the comment about return value for more details.
   *
   * @param[in] digest           The digest data buffer, for source file buffer to be verified.
   * @param[in] digest_length    The size of digest data buffer.
   * @param[in] signed_data      The signed data buffer.
   * @param[in] signed_data_len  The size of signed data buffer.
   * @param[in] client_data      A user-defined object, which is passed by user from function
   *                             @link Signature::StartSign @endlink or @link Signature::StartVerify @endlink.
   *
   * @return Verify state:
   *         <ul>
   *         <li>Please return @link Signature::e_StateVerifyNoChange @endlink alone to indicate that
   *             the document has not been changed within the scope of the signature.</li>
   *         <li>Otherwise, please return @link Signature::e_StateVerifyChange @endlink alone or combined with other error state value.</li>
   *         </ul>
   */
  virtual uint32 VerifySigState(const void* digest, uint32 digest_length,
                                const void* signed_data, uint32 signed_data_len,
                                void* client_data) = 0;

  /**
   * @brief A callback function used to check whether to return all contents with padding zero or not, when callback function
   *        @link SignatureCallback::VerifySigState @endlink is called.
   *
   * @return <b>true</b> means to return all data in contents steam (including padding zero),
   *         while <b>false</b> means to return contents data without padding zero in stream end.
   */
  virtual bool IsNeedPadData() = 0;

  /**
   * @brief A callback function used to check the validity of a certificate.
   *
   * @details This callback function will be triggered when function @link Signature::StartSign @endlink is called.
   *          If no need to check the certificate, value @link SignatureCallback::e_CertValid @endlink can
   *          be returned directly.
   *
   * @param[in] cert_path      A full path of a certificate file (including file name and extension),
   *                           which will be used for signing. This is passed by user from function
   *                           @link Signature::StartSign @endlink.
   * @param[in] cert_password  A password string used to open the cert file. If this is an empty string,
   *                           that means no password is required.This is passed by user from function
   *                           @link Signature::StartSign @endlink.
   * @param[in] client_data    A user-defined object, which is passed by user from function
   *                           @link Signature::StartSign @endlink.
   *
   * @return Certificate validity. Please refer to values starting from @link SignatureCallback::e_CertValid @endlink
   *         and it should be one of these values.
   */
  virtual CertValidity CheckCertificateValidity(const wchar_t* cert_path, const WString& cert_password, void* client_data) = 0;

 protected:
  ~SignatureCallback() {}
};

class TimeStampServer;

/**
 * Time stamp server manager is used to manage some time stamp servers. The default time stamp server in this manager will
 * be used in default signature callback for filter "Adobe.PPKLite" with sub filter "ETSI.CAdES.detached" and
 * filter "Adobe.PPKLite" with sub filter "ETSI.RFC3161". So before signing or verifying signatures in these filter-subfitler pair
 * by using default signature callback in Foxit PDF SDK, please ensure time stamp server manager is initialized and a default time stamp server is set.
 */
class TimeStampServerMgr FS_FINAL : public Object {
 public:
  /**
   * @brief Initialize time stamp server manager.
   *
   * @details This function should be called first before any other functions in @link TimeStampServerMgr @endlink can be called.
   *
   * @return @link foxit::e_ErrSuccess @endlink means success.<br>
   *         For more information about error code values, please refer to values starting from @link foxit::e_ErrSuccess @endlink.
   */
  static ErrorCode Initialize();
  /**
   * @brief Release time stamp server manager.
   *
   * @details User can call this function to release time stamp server manager when no need to use it any more.
   *          After this function is called, if user wants to use time stamp server manager again, please call function
   *          @link TimeStampServerMgr::Initialize @endlink again.
   *
   * @return None.
   */
  static void Release();

  /**
   * @brief Get time stamp server count.
   *
   * @return Server count.
   */
  static int GetServerCount();
  /**
   * @brief Get time stamp server with specified index.
   *
   * @param[in] index  Time stamp server index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link TimeStampServerMgr::GetServerCount @endlink.
   *
   * @return A time stamp server object.
   */
  static TimeStampServer GetServer(int index);
  /**
   * @brief Get the index of a speicified time stamp server object.
   *
   * @param[in] server  A time stamp server object.
   *
   * @return Index of specified time stamp server object.
   */
  static int GetServerIndex(const TimeStampServer& server);

  /**
   * @brief Get default time stamp server object.
   *
   * @return A time stamp server object which is the default one.
   */
  static TimeStampServer GetDefaultServer();
  /**
   * @brief Set default time stamp server object by index.
   *
   * @param[in] index  Index of a time stamp server to be set as default one.Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link TimeStampServerMgr::GetServerCount @endlink.
   *
   * @return None.
   */
  static void SetDefaultServer(int index);
  /**
  * @brief Set default time stamp server object by index.
  *
  * @param[in] server  A time stamp server object to be set as default server.
  *                    If input server object is invalid, this function wil throw
  *                    exception @link foxit::e_ErrNotFound @endlink.
  *
  * @return None.
  */
  static void SetDefaultServer(const TimeStampServer& server);

  /**
   * @brief Add a time stamp server to the manager.
   *
   * @param[in] server_name  Name of time stamp server. It should not be an empty string.
   * @param[in] server_url   URL of time stamp server. It should not be an empty string.
   * @param[in] user_name    User name for the time stamp server. If no need, please pass an empty string.
   * @param[in] password     Password for the time stamp server. If no need, please pass an empty string.
   *
   * @return The newly added time stamp server object.
   */
  static TimeStampServer AddServer(const WString& server_name, const WString& server_url, const WString& user_name, const WString& password);
  /**
   * @brief Remove a time stamp server from the manager, by index.
   *
   * @param[in] index  Index of the time stamp server which is to be removed from the manager.
   *
   * @return None.
   */
  static void RemoveServer(int index);
  /**
   * @brief Remove a time stamp server from the manager, by index.
   *
   * @param[in] server  A time stamp server object to be removed from the manager.
   *                    If input server object is invalid, this function will do nothing
   *                    and return directly.
   *
   * @return None.
   */
  static void RemoveServer(const TimeStampServer& server);
};

/**
 * This class represents time stamp server. It can be used to send time stamp request and then get the message.
 */
class TimeStampServer FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for the result of sending time stamp request.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _SendRequestResult {
    /** @brief Send request successfully. */
    e_SendResultSuccess = 0,
    /** @brief Fail to create socket during sending request process. */
    e_SendResultFailToCreateSocket = 1,
    /** @brief Fail to connect during sending request process. */
    e_SendResultFailToConnect = 2,
    /** @brief Fail to send data during sending request process. */
    e_SendResultFailToSendData = 3,
    /** @brief Fail to receive data during sending request process. */
    e_SendResultFailToReceiveData = 4,
    /** @brief Fail to request during sending request process. */
    e_SendResultFailToRequest = 5,
    /** @brief Fail to get data during sending request process. */
    e_SendResultFailToGetData = 6,
    /** @brief Out of memory during sending request process. */
    e_SendResultOutOfMemory = 7
  } SendRequestResult;
  

  /**
   * @brief Constructor, with another time stamp server object.
   *
   * @param[in] other  Another time stamp server object.
   */
  TimeStampServer(const TimeStampServer& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another time stamp server object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TimeStampServer& operator = (const TimeStampServer& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another time stamp server object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const TimeStampServer& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another time stamp server object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const TimeStampServer& other) const;

  /** @brief Destructor. */
  ~TimeStampServer();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Send time stamp request.
   *
   * @param[in] request  Time stamp request to be sent. It should not be an empty string.
   *
   * @return Result value of the seding request process. Please refer to values starting from
   *         @link TimeStampServer::e_SendResultSuccess @endlink and this would be one of these values.
   */
  SendRequestResult SendTimeStampRequest(const String& request);
  /**
   * @brief Get time stamp message.
   *
   * @details This function is to get the time stamp message after function @link TimeStampServer::SendTimeStampRequest @endlink runs successfully.
   *
   * @return Time stamp message.
   */
  String GetTimeStampMessage();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit TimeStampServer(FS_HANDLE handle);

};

}  // namespace pdf
}  // namespace foxit
#endif  // FS_SIGNATURE_H_

