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
 * @file fs_pdfdoc.h
 * @brief Header file for PDF document related definitions and classes.
 */

#ifndef FS_PDFDOC_H_
#define FS_PDFDOC_H_

#include "common/fs_common.h"
#include "common/file/fs_file.h"
#ifndef __EMSCRIPTEN_RENDER__
#include "pdf/fs_bookmark.h"
#include "pdf/fs_headerfooter.h"
#endif
#include "pdf/fs_pdfpage.h"
#ifndef __EMSCRIPTEN_RENDER__
#include "pdf/fs_readingbookmark.h"
#endif
#include "pdf/objects/fs_pdfobject.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
namespace fdf {
#ifndef __EMSCRIPTEN_RENDER__
class FDFDoc;
#endif
}  // namespace fdf
namespace pdf {
// forward declaration
namespace actions {
class Action;
}  // namespace actions
namespace interform {
class Form;
}  // namespace interform;
class ReadingBookmark;
class SecurityHandler;
class StdEncryptData;
class CertificateEncryptData;
class DRMEncryptData;
class CustomEncryptData;
class RMSEncryptData;

/** This class represents wrapper data, which is used for a wrapped PDF document. */
class WrapperData FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  WrapperData()
      : version(0) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] version      Wrapper version.
   * @param[in] type         Wrapper type to indicate a type of the current wrapper file.
   * @param[in] app_id       Application identity to indicate applications to open this wrapper data.
   * @param[in] uri          URI for consumers to get more information.
   * @param[in] description  Description for wrapper file to show applications or confront users prompt information.
   */
  WrapperData(int version, const wchar_t* type, const wchar_t* app_id, const wchar_t* uri, const wchar_t* description)
      : version(version)
      , type(type)
      , app_id(app_id)
      , uri(uri)
      , description(description) {}

  /**
   * @brief Constructor, with another wrapper data object.
   *
   * @param[in] wrapper_data  Another wrapper data object.
   */
  WrapperData(const WrapperData& wrapper_data)
      : version(wrapper_data.version)
      , type(wrapper_data.type)
      , app_id(wrapper_data.app_id)
      , uri(wrapper_data.uri)
      , description(wrapper_data.description) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] wrapper_data  Another wrapper data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  WrapperData& operator = (const WrapperData& wrapper_data) {
    version = wrapper_data.version;
    type = wrapper_data.type;
    app_id = wrapper_data.app_id;
    uri = wrapper_data.uri;
    description = wrapper_data.description;
    return *this;
  }

  /**
   * @brief Set value.
   *
   * @param[in] version      Wrapper version.
   * @param[in] type         Wrapper type to indicate a type of the current wrapper file.
   * @param[in] app_id       Application identity to indicate applications to open this wrapper data.
   * @param[in] uri          URI for consumers to get more information.
   * @param[in] description  Description for wrapper file to show applications or confront users prompt information.
   *
   * @return None.
   */
  void Set(int version, const wchar_t* type, const wchar_t* app_id, const wchar_t* uri, const wchar_t* description) {
    this->version = version;
    this->type = type;
    this->app_id = app_id;
    this->uri = uri;
    this->description = description;
  }

  /** @brief Wrapper version. */
  int version;
  /** @brief Wrapper type to indicate a type of the current wrapper file.*/
  WString type;
  /** @brief Application identity to indicate applications to open this wrapper data.*/
  WString app_id;
  /** @brief The URI for consumers to get more information.*/
  WString uri;
  /** @brief Description for wrapper file to show applications or confront users prompt information. */
  WString description;
};

/** This class represents payload data, which is used for a PDF 2.0 wrapped PDF document. */
class PayLoadData FS_FINAL {
 public:
  /** @brief Constructor. */
  PayLoadData()
      : version(0.0f)
      , file_size (0){}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] version        The version number of the cryptographic filter used to encrypt the encrypted payload referenced by this dictionary.
   * @param[in] crypto_filter  The name of the cryptographic filter used to encrypt the encrypted payload document.
   * @param[in] file_name      The payload file name.
   * @param[in] file_size      The payload file size.
   * @param[in] description    Description for payload file to show applications or confront users prompt information.
   */
  PayLoadData(float version, const wchar_t* crypto_filter, const wchar_t* file_name,
        foxit::int64 file_size,
        const wchar_t* description)
      : version(version)
      , crypto_filter(crypto_filter)
      , file_name(file_name)
      , file_size(file_size)
      , description(description) 
  {}

  /**
   * @brief Constructor, with another payload data object.
   *
   * @param[in] payload_data  Another payload data object.
   */
  PayLoadData(const PayLoadData& payload_data)
    : version(payload_data.version)
    , crypto_filter(payload_data.crypto_filter)
    , file_name(payload_data.file_name)
    , file_size(payload_data.file_size)
    , description(payload_data.description)
    {}

  /**
   * @brief Assign operator.
   *
   * @param[in] payload_data  Another payload data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PayLoadData& operator=(const PayLoadData& payload_data) {
    version = payload_data.version;
    crypto_filter = payload_data.crypto_filter;
    description = payload_data.description;
    file_name = payload_data.file_name;
    file_size = payload_data.file_size;
    return *this;
  }

  /**
   * @brief Set value.
   *
   * @param[in] version        The version number of the cryptographic filter used to encrypt the encrypted payload referenced by this dictionary.
   * @param[in] crypto_filter  The name of the cryptographic filter used to encrypt the encrypted payload document.
   * @param[in] file_name      The payload file name.
   * @param[in] file_size      The payload file size.
   * @param[in] description    Description for payload file to show applications or confront users prompt information.
   */
  void Set(float version, const wchar_t* crypto_filter, const wchar_t* file_name,
       int64 file_size,
       const wchar_t* description) {
    this->version = version;
    this->crypto_filter = crypto_filter;
    this->file_name = file_name;
    this->file_size = file_size;
    this->description = description;
  }

  /** @brief The version number of the cryptographic filter used to encrypt the encrypted payload referenced by this dictionary. */
  float version;
  /** @brief The name of the cryptographic filter used to encrypt the encrypted payload document. */
  WString crypto_filter;
  /** @brief The payload file name.*/
  WString file_name;
  /** @brief The payload file size.*/
  int64 file_size;
  /** @brief Description for payload file to show applications or confront users prompt information.*/
  WString description;
};

/**
 * This class represents page basic information, such as page width, page height, and page rotation.
 * This is used as the return type of function @link PDFDoc::GetPageBasicInfo @endlink.
 */
class PageBasicInfo FS_FINAL : public Object {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] width     Page width.
   * @param[in] height    Page height.
   * @param[in] rotation  Page rotation. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                      this should be one of these values except @link common::e_RotationUnknown @endlink.
   */
  PageBasicInfo(float width, float height, common::Rotation rotation)
      : width(width)
      , height(height)
      , rotation(rotation) {}

  /** @brief Constructor. */
  PageBasicInfo()
      : width(0)
      , height(0)
      , rotation(CommonDefines::e_RotationUnknown) {}
  /**
   * @brief Constructor, with another page basic information object.
   *
   * @param[in] page_info  Another page basic information object.
   */
  PageBasicInfo(const PageBasicInfo& page_info)
      : width(page_info.width)
      , height(page_info.height)
      , rotation(page_info.rotation) {}
  /**
   * @brief Assign operator.
   *
   * @param[in] page_info  Another page basic information object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PageBasicInfo& operator = (const PageBasicInfo& page_info) {
    width = page_info.width;
    height = page_info.height;
    rotation = page_info.rotation;
    return *this;
  }
  /**
   * @brief Set value.
   *
   * @param[in] width     Page width.
   * @param[in] height    Page height.
   * @param[in] rotation  Page rotation. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                      this should be one of these values except @link common::e_RotationUnknown @endlink.
   *
   * @return None.
   */
  void Set(float width, float height, common::Rotation rotation) {
    this->width = width;
    this->height = height;
    this->rotation = rotation;
  }

  /** @brief Page width. */
  float width;
  /** @brief Page height. */
  float height;
  /**
   * @brief Page rotation. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *        this should be one of these values.
   */
  common::Rotation rotation;
};

/**
 * This class represents embeded font data which is retrieved from a PDF document.
 * Please refer to function @link PDFDoc::GetEmbeddedFontData @endlink.
 */
class EmbeddedFontData FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  EmbeddedFontData() {}

  /**
   * @brief Constructor, with another embedded font data object.
   *
   * @param[in] other  Another unembedded font data object.
   */
  EmbeddedFontData(const EmbeddedFontData& other)
      : nonstandard_font_name_array(other.nonstandard_font_name_array)
      , standard_font_name_array(other.standard_font_name_array) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another embedded font data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  EmbeddedFontData& operator=(const EmbeddedFontData& other) {
    nonstandard_font_name_array = other.nonstandard_font_name_array;
    standard_font_name_array = other.standard_font_name_array;
    return *this;
  }

  /** @brief Font name array of embedded fonts which cannot be replaced by system fonts if they are to be unembeded. */
  WStringArray nonstandard_font_name_array;
  /** @brief Font name array of embedded fonts which are standard fonts and can be replaced by system fonts if they are to be unembedded. */
  WStringArray standard_font_name_array;
};

/**
 * A PDF document object can be constructed with an existing PDF file from file path, memory buffer,
 * a custom implemented @link common::file::ReaderCallback @endlink object and an input file stream. And then call function
 * @link pdf::PDFDoc::Load @endlink or @link PDFDoc::StartLoad @endlink to load document content.
 * This class offers functions to retrieve different part of a PDF document. For example:
 * <ul>
 * <li>To retrieve pages, please use functions @link pdf::PDFDoc::GetPageCount @endlink and @link PDFDoc::GetPage @endlink.</li>
 * <li>To retrieve bookmark, such as function @link pdf::PDFDoc::GetRootBookmark @endlink, @link PDFDoc::CreateRootBookmark @endlink, etc.</li>
 * <li>To retrieve some document's dictionaries (in low-level), such as functions
 *     @link pdf::PDFDoc::GetCatalog @endlink, @link PDFDoc::GetTrailer @endlink, etc.</li>
 * <li>To retrieve reading bookmark, such as functions @link PDFDoc::GetReadingBookmarkCount @endlink,
 *     @link PDFDoc::GetReadingBookmark @endlink, etc.</li>
 * <li>To check if a PDF document has interactive form, please use function @link PDFDoc::HasForm @endlink.</li>
 * <li>To check if a PDF document has header-footer, please use function @link PDFDoc::HasHeaderFooter @endlink.
 *     To modify header-footer, please refer to functions such as @link pdf::PDFDoc::AddHeaderFooter @endlink, @link PDFDoc::UpdateHeaderFooter @endlink,
 *     and @link PDFDoc::RemoveAllHeaderFooters @endlink.</li>
 * </ul>
 * This class also offers functions for features, such as saving current document as another PDF file,
 * importing pages from another PDF file, setting security handler in order to save encrypted PDF file, and so on.<br>
 * This class object can also be used to construct objects of other classes in order to access specified information
 * in PDF document:
 * <ul>
 * <li>To access form, please construct a @link interform::Form @endlink object with PDF document object.</li>
 * <li>To access additional actions, please construct an @link actions::AdditionalAction @endlink object with PDF document object.</li>
 * <li>To access viewer preferences information, please construct a @link DocViewerPrefs @endlink object with PDF document object.
 * <li>To access metadata information, please construct a @link Metadata @endlink object with PDF document object.</li>
 * <li>To manage page labels information, please construct a @link PageLabels @endlink object with PDF document object.</li>
 * <li>To search among a PDF file, please construct a @link TextSearch @endlink object with PDF document object.</li>
 * <li>To access layers, please construct a @link LayerTree @endlink object with PDF document object.
 *     And to render layers, please constructor a @link LayerContext @endlink object with PDF document object.</li>
 * <li>To construct a new @link FileSpec @endlink object.</li>
 * <li>To manage associated files, please construct an @link AssociatedFiles @endlink object with PDF document object.</li>
 * <li>To access name tree, please construct a @link objects::PDFNameTree @endlink object with PDF document object. Specially,
 *     for EmbeddedFiles name tree, an @link Attachments @endlink object can be constructed with PDF document object,
 *     for convenient use.</li>
 * </li>
 * <li>To do redaction, please construct a @link addon::Redaction @endlink object with PDF document object.</li>
 * </ul>
 *
 * @see @link interform::Form @endlink
 * @see @link actions::AdditionalAction @endlink
 * @see @link DocViewerPrefs @endlink
 * @see @link Metadata @endlink
 * @see @link PageLabels @endlink
 * @see @link TextSearch @endlink
 * @see @link LayerTree @endlink
 * @see @link LayerContext @endlink
 * @see @link FileSpec @endlink
 * @see @link AssociatedFiles @endlink
 * @see @link objects::PDFNameTree @endlink
 * @see @link Attachments @endlink
 * @see @link addon::Redaction @endlink
 */
class PDFDoc FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for the type of current used password in a PDF document.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PasswordType {
    /** @brief The password is invalid. */
    e_PwdInvalid   =  0,
    /** @brief No password is used in PDF document. */
    e_PwdNoPassword  =  1,
    /** @brief A user password is used in PDF document. */
    e_PwdUser  =  2,
    /** @brief An owner password is used in PDF document. */
    e_PwdOwner  =  3
  } PasswordType;
  
  /**
   * @brief Enumeration for encryption type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _EncryptType {
    /** @brief Unknown encryption type. */
    e_EncryptUnknown   =  -1,
    /** @brief No encryption pattern. */
    e_EncryptNone   =  0,
    /** @brief Encryption type: password, which is the standard encryption. */
    e_EncryptPassword  =  1,
    /** @brief Encryption type: digital certificate encryption. */
    e_EncryptCertificate  =  2,
    /** @brief Encryption type: Foxit DRM encryption. */
    e_EncryptFoxitDRM  =  3,
    /** @brief Encryption type: customized encryption. */
    e_EncryptCustom  =  4,
    /** @brief Encryption type: Microsoft RMS encryption. */
    e_EncryptRMS  =  5,
    /** @brief (Reserved, currently, this value is not used.) Encryption type: Foxit connected PDF DRM encryption. */
    e_EncryptCDRM  =  6
  } EncryptType;
  
  /**
   * @brief Enumeration for user access permissions in a PDF document.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _UserPermissions {
    /**
   @brief Print PDF document with normal mode. (Bit 3 in permission value)
   @details If user wants to print a higher quality level of PDF document, please set current value with
            value @link PDFDoc::e_PermPrintHigh @endlink together.
     */
    e_PermPrint = 0x0004,
    /**
   @brief Modify PDF contents. (Bit 4 in permission value)
   @details If this value is set, user can modify contents of PDF document by operations other than those controlled by
            values @link PDFDoc::e_PermAnnotForm @endlink, @link PDFDoc::e_PermFillForm @endlink and
            @link PDFDoc::e_PermAssemble @endlink.
     */
    e_PermModify  = 0x0008,
    /**
   @brief Extract PDF contents. (Bit 5 in permission value)
   @details If this value is set, user can copy or otherwise extract text and graphics from the document
            by operations other than that controlled by value @link PDFDoc::e_PermExtractAccess @endlink.
     */
    e_PermExtract = 0x0010,
    /**
   @brief Operate text annotations and fill in interactive form fields. (Bit 6 in permission value)
   @details If value @link PDFDoc::e_PermModify @endlink is also set,
            user can create or modify interactive form fields (including signature fields).
     */
    e_PermAnnotForm = 0x0020,
    /**
   @brief Fill PDF form. (Bit 9 in permission value)
   @details If this value is set, user can fill in interactive form fields (including signature fields),
            even if value @link PDFDoc::e_PermAnnotForm @endlink is not used.
     */
    e_PermFillForm = 0x0100,
    /**
   @brief Disabilities support. (Bit 10 in permission value)
   @details If this value is set, user can extract text and graphics in support of accessibility
            to users with disabilities or for other purposes.
     */
    e_PermExtractAccess = 0x0200,
    /**
   @brief Assemble PDF document. (Bit 11 in permission value)
   @details If this value is set, it enables to assemble the document
            (Insert, rotate, or delete pages and create bookmarks or thumbnail images),
            regardless if value @link PDFDoc::e_PermModify @endlink is set or not.
     */
    e_PermAssemble = 0x0400,
    /**
   @brief Print PDF document with higher qualities. (Bit 12 in permission value)
   @details If this value is not set (and value @link PDFDoc::e_PermPrint @endlink is set),
            printing is limited to a low-level representation of the appearance, possibly of degraded quality.
     */
    e_PermPrintHigh = 0x0800
  } UserPermissions;
  
  /**
   @brief Enumeration for PDF document saving flags.
   @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _SaveFlags {
    /** @brief Save document normally, without using any special flag. This can only be used alone.*/
    e_SaveFlagNormal      =  0,
    /**
   @brief Save document incrementally.
   @details This can be used alone or be combined with other saving flags except @link PDFDoc::e_SaveFlagNormal @endlink.
            Especially, if this is combined with @link PDFDoc::e_SaveFlagNoOriginal @endlink,
            only the increment data will be saved.
     */
    e_SaveFlagIncremental    =  0x0001,
    /**
   @brief Save document without original data or unchanged objects.
   @details This can be used alone or be combined with other saving flags except @link PDFDoc::e_SaveFlagNormal @endlink.
            Especially, if this is combined with @link PDFDoc::e_SaveFlagIncremental @endlink,
            only the increment data will be saved.
     */
    e_SaveFlagNoOriginal    =  0x0002,
    /**
   @brief Save document by using XRef stream.
   @details This can be used alone or be combined with other saving flags except @link PDFDoc::e_SaveFlagNormal @endlink.
     */
    e_SaveFlagXRefStream    =  0x0008,
    /**
   @brief Save document as a linearized file.
   @details This should be used alone and cannot be used with other saving flags.
            This can only be used for function @link pdf::PDFDoc::SaveAs @endlink or @link PDFDoc::StartSaveAs @endlink.
     */
    e_SaveFlagLinearized    =  0x1000,
    /**
   @brief Save document with removing redundant PDF objects.
   @details This can be used alone or be combined with @link PDFDoc::e_SaveFlagNoOriginal @endlink or @link PDFDoc::e_SaveFlagXRefStream @endlink.
            This can only be used for function @link pdf::PDFDoc::SaveAs @endlink or @link PDFDoc::StartSaveAs @endlink.
    */
    e_SaveFlagRemoveRedundantObjects = 0x0010
  } SaveFlags;
  
  /**
   * @brief Enumeration for flags used for importing pages.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _ImportPageFlags {
    /** @brief Import pages normally.*/
    e_ImportFlagNormal      =  0,
    /** @brief Import pages with layers. */
    e_ImportFlagWithLayers    =  0x0001,
    /**
   @brief Import pages without cloning stream objects into memory.
   @details This flags is only useful when the source PDF document has not been encrypted.
            If this flag is used for importing pages, it will reduce memory overhead.
     */
    e_ImportFlagShareStream    =  0x0002
  } ImportPageFlags;
  
  /**
   * @brief Enumeration for options used for extracting pages.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _ExtractPagesOptions {
    /** @brief If set, that means annotations related to extracted pages will be extracted as well.*/
    e_ExtractPagesOptionAnnotation =  0x0001,
    /** @brief If set, that means structure tree will be extracted as well. */
    e_ExtractPagesOptionStructureTree =  0x0002,
    /** @brief If set, that means Javascript will be extracted as well. */
    e_ExtractPagesOptionJavascript = 0x0004,
    /** @brief If set, that means OCProperties will be extracted as well. */
    e_ExtractPagesOptionOCProperties = 0x0008,
    /**
     * @brief If set, that means to use @link PDFDoc::e_SaveFlagXRefStream @endlink saving flag
     *        for the result file in order to reduce the size of result file.
     */
    e_ExtractPagesOptionObjectStream = 0x0010,
    /** @brief If set, that means attachment files will be extracted as well. */
    e_ExtractPagesOptionAttachFiles = 0x0020
  } ExtractPagesOptions;
  
  /**
   * @brief Enumeration for options used for inserting a PDF document to another.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _InsertDocOptions {
    /** @brief If set, that means attachments will be inserted to target document as well. */
    e_InsertDocOptionAttachments =  0x0001
  } InsertDocOptions;
  
  /**
   * @brief Enumeration for display mode which specifies how the document should be displayed when opened.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _DisplayMode {
    /** @brief When document is opened, neither document outlines nor thumbnail images are visible. */
    e_DisplayUseNone = 0,
    /** @brief When document is opened, document outlines (bookmarks) are visible. */
    e_DisplayUseOutlines = 1,
    /** @brief When document is opened, thumbnail images are visible. */
    e_DisplayUseThumbs = 2,
    /**
     * @brief When document is opened, full-screen mode, with no menu bar, window controls,
     *        or any other windows are visible.
     */
    e_DisplayFullScreen = 3,
    /** @brief When document is opened, optional content group panels are visible. */
    e_DisplayUseOC = 4,
    /** @brief When document is opened, attachment panels are visible. */
    e_DisplayUseAttachment = 5
  } DisplayMode;
  
  /**
   * @brief Enumeration for data type used to decide which object(s) will be imported from or exported to
   *        FDF/XFDF document.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _DataType {
    /** @brief If set, form fields are to imported from or exported to FDF/XFDF document.*/
    e_Forms      =  0x0001,
    /** @brief If set, annotations (except link annotations) are to imported from or exported to FDF/XFDF document. */
    e_Annots   =  0x0002,
    /** @brief (Reserved, not supported yet) If set, only link annotations are to imported from or exported to XFDF document. */
    e_Links     =  0x0004
  } DataType;
  
  /**
   * @brief Enumeration for wrapper type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WrapperType {
    /** @brief Normal document.*/
    e_WrapperNone =  0,
    /** @brief Foxit wrapper document.*/
    e_WrapperFoxit =  1,
    /** @brief PDF 2.0 wrapper document. */
    e_WrapperPDFV2 =  2
  } WrapperType;
  

  /**
   * @brief Constructor.
   *
   * @details This constructor is to construct a new PDF document (without any data).
   *          The file version value would be 17 (as PDF version 1.7) by default.
   */
  PDFDoc();

  /**
   * @brief Constructor, from an existing PDF file path.
   *
   * @details After constructing such a PDF document object, please ensure the document object has been loaded
   *          before using most functions in class @link PDFDoc @endlink.
   *
   * @param[in] path  A full path of an existing PDF file. It should not be an empty string.
   */
  explicit PDFDoc(const char* path);

  /**
   * @brief Constructor, from an existing PDF file path.
   *
   * @details After constructing such a PDF document object, please ensure the document object has been loaded
   *          before using most functions in class @link PDFDoc @endlink.
   *
   * @param[in] path  A full path of an existing PDF file. It should not be an empty string.
   */
  explicit PDFDoc(const wchar_t* path);

  /**
   * @brief Constructor, from a memory buffer.
   *
   * @details After constructing such a PDF document object, please ensure the document object has been loaded
   *          before using most functions in class @link PDFDoc @endlink.
   *
   * @param[in] buffer  A memory buffer, containing the serialized document. The PDF document data should be
   *                    fully loaded in this memory buffer. It should not be <b>NULL</b>.
   * @param[in] size    The size of memory buffer. It should be above 0.
   */
  explicit PDFDoc(const void* buffer, size_t size);

  /**
   * @brief Constructor, with a file read callback object.
   *
   * @details After constructing such a PDF document object, please ensure the document object has been loaded
   *          before using most functions in class @link PDFDoc @endlink.
   *
   * @param[in] file_read  A @link common::file::ReaderCallback @endlink object which is implemented by user to
   *                       load a PDF document. It should not be <b>NULL</b>.
   *                       If the input callback object is an @link common::file::AsyncReaderCallback @endlink object, and is_async is <b>true</b>
   *                       that means the PDF document will be loaded by asynchronous method; otherwise,
   *                       the document will be loaded in common way.
   * @param[in] is_async   Whether the input @link common::file::ReaderCallback @endlink object is for asynchronously loading or not.
   *                       Default value: <b>false</b>.
   */
  explicit PDFDoc(common::file::ReaderCallback* file_read, bool is_async = false);
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDFDoc(FS_HANDLE handle);
  /** @brief Destructor. */
  ~PDFDoc();

  /**
   * @brief Constructor, with another PDF document object.
   *
   * @param[in] other  Another PDF document object.
   */
  PDFDoc(const PDFDoc& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another PDF document object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDFDoc& operator = (const PDFDoc& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another PDF document object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PDFDoc& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another PDF document object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PDFDoc& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get file size.
   *
   * @return File size.
   */
  uint64 GetFileSize();

  /**
   * @brief Check if current PDF document is a linearized file.
   *
   * @details <ul>
   *          <li>If current document object is constructed with an @link common::file::AsyncReaderCallback @endlink object, this function can be
   *              used before or after the document is loaded successfully. Specially, if this function is called
   *              before document is loaded successfully, application should ensure the first 1024 bytes of
   *              the PDF file is available; otherwise, this function will call the callback function
   *              @link common::file::AsyncReaderCallback::AddDownloadHint @endlink to notify application the range of data
   *              which should be downloaded by application then, and then this function will throw exception
   *              @link foxit::e_ErrDataNotReady @endlink.</li>
   *          <li>If current document object is constructed from other methods or with a common @link common::file::ReaderCallback @endlink object,
   *              this function can only be used after the document is loaded successfully; otherwise,
   *              exception @link foxit::e_ErrUnknownState @endlink will be thrown.</li>
   *          </ul>
   *
   * @return <b>true</b> means current PDF document is a linearized file,
   *         and <b>false</b> means current PDF document is not a linearized file.
   */
  bool IsLinearized() const;
  
  /**
   * @brief Check if current PDF document is a Tagged PDF file.
   *
   * @return <b>true</b> means current PDF document is a Tagged PDF file,
   *         and <b>false</b> means current PDF document is not a Tagged PDF file.
   */
  bool IsTaggedPDF() const;

  /**
   * @brief Load current document content by using a specified password.
   *
   * @details If current PDF document object is constructed with an AsyncReaderCallback which means to
   *          do asynchronous loading, this function may return @link foxit::e_ErrDataNotReady @endlink.
   *          In this case, user should prepare data for specified range informed by callback function
   *          @link common::file::AsyncReaderCallback::AddDownloadHint @endlink and then call this function again.
   *
   * @param[in] password  The password string, used to load current document content. The password can be either
   *                      user password or owner password. If current document is not encrypted by password,
   *                      just pass an empty string. Default value: an empty string.
   *
   * @return @link foxit::e_ErrSuccess @endlink means success. <br>
   *         @link foxit::e_ErrFile @endlink means there is any error occurs when accessing to current document content.<br>
   *         @link foxit::e_ErrPassword @endlink means input password is wrong.<br>
   *         @link foxit::e_ErrFormat @endlink means the format of current document content is not PDF or the file is corrupted.<br>
   *         @link foxit::e_ErrSecurityHandler @endlink means current PDF document is encrypted by some unsupported security handler.<br>
   *         @link foxit::e_ErrCertificate @endlink means current PDF document is encrypted by digital certificate and
   *         current user does not have the correct certificate.<br>
   *         For other error code value, please refer to values starting from @link foxit::e_ErrSuccess @endlink for more details.
   */
  ErrorCode Load(const String& password = "");

  /**
   * @brief Load current document content by using a specified password.
   *
   * @details If current PDF document object is constructed with an AsyncReaderCallback which means to
   *          do asynchronous loading, this function may return @link foxit::e_ErrDataNotReady @endlink.
   *          In this case, user should prepare data for specified range informed by callback function
   *          @link common::file::AsyncReaderCallback::AddDownloadHint @endlink and then call this function again.
   *
   * @param[in] password  The password string, used to load current document content. The password can be either
   *                      user password or owner password. If current document is not encrypted by password,
   *                      just pass an empty string. Default value: an empty string.
   *
   * @return @link foxit::e_ErrSuccess @endlink means success. <br>
   *         @link foxit::e_ErrFile @endlink means there is any error occurs when accessing to current document content.<br>
   *         @link foxit::e_ErrPassword @endlink means input password is wrong.<br>
   *         @link foxit::e_ErrFormat @endlink means the format of current document content is not PDF or the file is corrupted.<br>
   *         @link foxit::e_ErrSecurityHandler @endlink means current PDF document is
   *         encrypted by some unsupported security handler.<br>
   *         @link foxit::e_ErrCertificate @endlink means current PDF document is encrypted by digital certificate and
   *         current user does not have the correct certificate.<br>
   *         For other error code value, please refer to values starting from @link foxit::e_ErrSuccess @endlink for more details.
   */
  ErrorCode LoadW(const WString& password = WString());

  /**
   * @brief Start to loading current document content by using a specified password.
   *
   * @details It may take a long time to loading document content, so this function uses a progressive process to
   *          do this.<br>
   *          When using this function, parameter <i>is_cache_stream</i> can be used to decide whether to
   *          load stream content into memory or not:
   *          <ul>
   *          <li>Loading stream content into memory will improve performance for frequent access, however,
   *              it will also consume a lot of memory space.</li>
   *          <li>Not to load stream content into memory, that means to leave stream content on file system,
   *              and read them when needed. This may reduce the performance a little bit, but greatly reduce
   *              the memory consumption, especially when the file is big.</li>
   *          </ul>
   *
   * @param[in] password         A password string, used to load current document content. The password can be
   *                             either user password or owner password. If current document is not encrypted
   *                             by password, just pass an empty string. Default value: an empty string.
   * @param[in] is_cache_stream  <b>true</b> means to load stream content into memory, and <b>false</b> means not to
   *                             load stream content into memory and just leave stream content on file system and
   *                             read them when needed. Please refer to "Details" part about the difference between
   *                             these two modes. Default value: <b>true</b>.
   * @param[in] pause            Pause object which decides if the loading process needs to be paused.
   *                             This can be <b>NULL</b> which means not to pause during the parsing process.
   *                             If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                             Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartLoad(const String& password = "", bool is_cache_stream = true,
                                common::PauseCallback* pause = NULL);
  /**
   * @brief Start to loading current document content by using a specified password.
   *
   * @details It may take a long time to loading document content, so this function uses a progressive process to
   *          do this.<br>
   *          When using this function, parameter <i>is_cache_stream</i> can be used to decide whether to
   *          load stream content into memory or not:
   *          <ul>
   *          <li>Loading stream content into memory will improve performance for frequent access, however,
   *              it will also consume a lot of memory space.</li>
   *          <li>Not to load stream content into memory, that means to leave stream content on file system,
   *              and read them when needed. This may reduce the performance a little bit, but greatly reduce
   *              the memory consumption, especially when the file is big.</li>
   *          </ul>
   *
   * @param[in] password         A password string, used to load current document content. The password can be
   *                             either user password or owner password. If current document is not encrypted
   *                             by password, just pass an empty string. Default value: an empty string.
   * @param[in] is_cache_stream  <b>true</b> means to load stream content into memory, and <b>false</b> means not to
   *                             load stream content into memory and just leave stream content on file system and
   *                             read them when needed. Please refer to "Details" part about the difference between
   *                             these two modes. Default value: <b>true</b>.
   * @param[in] pause            Pause object which decides if the loading process needs to be paused.
   *                             This can be <b>NULL</b> which means not to pause during the parsing process.
   *                             If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                             Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartLoadW(const WString& password = WString(), bool is_cache_stream = true,
                                common::PauseCallback* pause = NULL);

  /**
   * @brief Get the page index of the fist available page.
   *
   * @details This is useful for a linearized PDF document because in a linearized PDF document
   *          the first available page may not be the first page.<br>
   *          This function can be used only when document is loaded successfully.
   *
   * @return Page index of the first available page.
   */
  int GetFirstAvailPageIndex() const;

  /**
   * @brief Check whether current PDF document is an XFA document.
   *
   * @details Currently, Foxit PDF SDK does not fully support XFA document. When loading an XFA document,
   *          Foxit PDF SDK may only load the XFA wrapper level, and cannot have access to the real XFA content.
   *          Foxit PDF SDK does not support to insert/import/remove/move pages in an XFA document yet.
   *
   * @return <b>true</b> means current document is an XFA document,
   *         while <b>false</b> means current document is not an XFA document.
   */
  bool IsXFA() const;

  /**
   * @brief Check whether current document is an encrypted file or not.
   *
   * @return <b>true</b> means current document is an encrypted file,
   *         while <b>false</b> means current document is not an encrypted file.
   */
  bool IsEncrypted() const;

  /**
   * @brief Clear the cache used during rendering, to reduce the memory usage.
   *
   * @return None.
   */
  void ClearRenderCache();

  /**
   * @brief Get the type of current used password.
   *
   * @details This function is useful after loading a PDF document, in order to get the type of the password
   *          which was used in the loading process.<br>
   *          If current document is a new one (not loading from existed PDF file), this function will return
   *          @link PDFDoc::e_PwdNoPassword @endlink.<br>
   *          If current document is constructed from an existing file but has not been loaded yet,
   *          this function will return @link PDFDoc::e_PwdInvalid @endlink.
   *
   * @return Password type. Please refer to values starting from @link PDFDoc::e_PwdInvalid @endlink and
   *         this would be one of these values.
   */
  PasswordType GetPasswordType() const;

  /**
   * @brief Get the encryption type.
   *
   * @return Encryption type. Please refer to values starting from @link PDFDoc::e_EncryptNone @endlink and
   *         this would be one of these values.
   */
  EncryptType GetEncryptionType() const;

  /**
   * @brief Check the type of a specified password.
   *
   * @details This function can be used to check the type of any password string, including the password string
   *          used for loading document content.<br>
   *          For some PDF document, it have user password and owner password at the same time and these two passwords
   *          are same. But current function can only return one type for such password. In this case, functions
   *          @link PDFDoc::IsUserPassword @endlink and @link PDFDoc::IsOwnerPassword @endlink can help to do more check.
   *
   * @param[in] password  A password string to be detected.
   *
   * @return Password type. Please refer to values starting from @link PDFDoc::e_PwdInvalid @endlink and
   *         this would be one of these values.
   */
  PasswordType CheckPassword(const String& password);

  /**
   * @brief Check the type of a specified unicode password.
   *
   * @details This function can be used to check the type of any password string, including the password string
   *          used for loading document content.<br>
   *          For some PDF document, it have user password and owner password at the same time and these two passwords
   *          are same. But current function can only return one type for such password. In this case, functions
   *          @link PDFDoc::IsUserPassword @endlink and @link PDFDoc::IsOwnerPassword @endlink can help to do more check.
   *
   * @param[in] password  A unicode password string to be detected.
   *
   * @return Password type. Please refer to values starting from @link PDFDoc::e_PwdInvalid @endlink and
   *         this would be one of these values.
   */
  PasswordType CheckPassword(const foxit::WString& password);

  /**
   * @brief Check if input password is the user password of current PDF document.
   *
   * @param[in] password  A password string to be detected.
   *
   * @return <b>true</b> means input password is the user password of current PDF document, while <b>false</b> means
   *         input password is not the user password of current PDF document.
   */
  bool IsUserPassword(const String& password);

  /**
   * @brief Check if input password is the user password of current PDF document.
   *
   * @param[in] password  A password string to be detected.
   *
   * @return <b>true</b> means input password is the user password of current PDF document, while <b>false</b> means
   *         input password is not the user password of current PDF document.
   */
  bool IsUserPassword(const foxit::WString& password);

  /**
   * @brief Check if input password is the owner password of current PDF document.
   *
   * @param[in] password  A password string to be detected.
   *
   * @return <b>true</b> means input password is the owner password of current PDF document, while <b>false</b> means
   *         input password is not the owner password of current PDF document.
   */
  bool IsOwnerPassword(const String& password);

  /**
   * @brief Check if input password is the owner password of current PDF document.
   *
   * @param[in] password  A password string to be detected.
   *
   * @return <b>true</b> means input password is the owner password of current PDF document, while <b>false</b> means
   *         input password is not the owner password of current PDF document.
   */
  bool IsOwnerPassword(const foxit::WString& password);

  /**
   * @brief Get the user password based on owner password.
   *
   * @details This function is useful when current document is encrypted by password.
   *
   * @param[in] owner_password  Owner password string.
   *
   * @return The user password string.
   */
  String GetUserPassword(const String& owner_password);
#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Get encrypt data of standard encryption (known as password encryption).
   *
   * @details This function is useful when current document is encrypted by password.
   *
   * @return The encrypt data of standard encryption.
   */
  StdEncryptData GetStdEncryptData() const;

  /**
   * @brief Get encrypt data of certificate encryption.
   *
   * @details This function is useful when current document is encrypted by certificate.
   *
   * @return The encrypt data of certificate encryption.
   */
  CertificateEncryptData GetCertificateEncryptData() const;

  /**
   * @brief Get encrypt data of Foxit DRM encryption.
   *
   * @details This function is useful when current document is encrypted by Foxit DRM.
   *
   * @return The encrypt data of Foxit DRM encryption.
   */
  DRMEncryptData GetDRMEncryptData() const;

  /**
   * @brief Get encrypt data of custom encryption.
   *
   * @details This function is useful when current document is encrypted by custom.
   *
   * @return The encrypt data of custom encryption.
   */
  CustomEncryptData GetCustomEncryptData() const;

  /**
   * @brief Get encrypt data of RMS encryption.
   *
   * @details This function is useful when current document is encrypted by RMS.
   *
   * @return The encrypt data of RMS encryption.
   *
   * @note If module "RMS" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using RMS related functions and
   *       this function will throw exception @link foxit::e_ErrNoRMSModuleRight @endlink.
   */
  RMSEncryptData GetRMSEncryptData() const;
#endif
  /**
   * @brief Save current PDF document as another PDF file.
   *
   * @details If current document is loaded from an existing PDF file and a different file version has been set
   *          by @link PDFDoc::SetFileVersion @endlink before saving, Foxit PDF SDK will ignore
   *          @link PDFDoc::e_SaveFlagIncremental @endlink
   *          in parameter <i>save_flags</i> and use the file version in saved PDF file.
   *
   * @param[in] file_path   A full path for the new saved PDF file. It should not be an empty string.
   * @param[in] save_flags  Document saving flags. Please refer to values starting from @link PDFDoc::e_SaveFlagNormal @endlink
   *                        and this can be one or combination of these values.
   *                        Default value: @link PDFDoc::e_SaveFlagNormal @endlink.
   *
   * @return <b>true</b> means the saving is successfully finished, while <b>false</b> means failure.
   *
   * @note This function does not support to save current PDF document object just back to the PDF file which is used to
   *       construct current PDF object. In order to do so, user is recommended to do as following steps:<br>
   *       Assume that current PDF object is constructed from a PDF file named "org.pdf".
   *       <ol>
   *       <li>Use current function to save current PDF object to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that current PDF object has destructed -- which is equal to "close document".</li>
   *       <li>Remove "org.pdf" and rename "temp.tmp" to "org.pdf".</li>
   *       </ol>
   *       Then user can open the saved PDF file to do other operation.
   */
  bool SaveAs(const char* file_path, uint32 save_flags = PDFDoc::e_SaveFlagNormal);

  /**
   * @brief Save current PDF document as another PDF file.
   *
   * @details If current document is loaded from an existing PDF file and a different file version has been set
   *          by @link PDFDoc::SetFileVersion @endlink before saving, Foxit PDF SDK will ignore
   *          @link PDFDoc::e_SaveFlagIncremental @endlink
   *          in parameter <i>save_flags</i> and use the file version in saved PDF file.
   *
   * @param[in] file_path   A full path for the new saved PDF file. It should not be an empty string.
   * @param[in] save_flags  Document saving flags. Please refer to values starting from @link PDFDoc::e_SaveFlagNormal @endlink
   *                        and this can be one or combination of these values.
   *                        Default value: @link PDFDoc::e_SaveFlagNormal @endlink.
   *
   * @return <b>true</b> means the saving is successfully finished, while <b>false</b> means failure.
   *
   * @note This function does not support to save current PDF document object just back to the PDF file which is used to
   *       construct current PDF object. In order to do so, user is recommended to do as following steps:<br>
   *       Assume that current PDF object is constructed from a PDF file named "org.pdf".
   *       <ol>
   *       <li>Use current function to save current PDF object to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that current PDF object has destructed -- which is equal to "close document".</li>
   *       <li>Remove "org.pdf" and rename "temp.tmp" to "org.pdf".</li>
   *       </ol>
   *       Then user can open the saved PDF file to do other operation.
   */
  bool SaveAs(const wchar_t* file_path, uint32 save_flags = PDFDoc::e_SaveFlagNormal);

  /**
   * @brief Start to save current PDF document as another PDF file.
   *
   * @details It may take a long time to saving PDF document, so this function uses a progressive process to do this.<br>
   *          If current document is loaded from an existing PDF file and a different file version has been set
   *          by @link PDFDoc::SetFileVersion @endlink before saving, Foxit PDF SDK will ignore
   *          @link PDFDoc::e_SaveFlagIncremental @endlink
   *          in parameter <i>save_flags</i> and use the file version in saved PDF file.
   *
   * @param[in] file_path   A full path for the new saved PDF file. It should not be an empty string.
   * @param[in] save_flags  Document saving flags. Please refer to values starting from @link PDFDoc::e_SaveFlagNormal @endlink
   *                        and this can be one or combination of these values.
   *                        Default value: @link PDFDoc::e_SaveFlagNormal @endlink.
   * @param[in] pause       Pause callback object which decides if the parsing process needs to be paused.
   *                        This can be <b>NULL</b> which means not to pause during the parsing process.
   *                        If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                        Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   *
   * @note This function does not support to save current PDF document object just back to the PDF file which is used to
   *       construct current PDF object. In order to do so, user is recommended to do as following steps:<br>
   *       Assume that current PDF object is constructed from a PDF file named "org.pdf".
   *       <ol>
   *       <li>Use current function to save current PDF object to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that current PDF object has destructed -- which is equal to "close document".</li>
   *       <li>Remove "org.pdf" and rename "temp.tmp" to "org.pdf".</li>
   *       </ol>
   *       Then user can open the saved PDF file to do other operation.
   */
  common::Progressive StartSaveAs(const char* file_path,
                                  uint32 save_flags = PDFDoc::e_SaveFlagNormal,
                                  common::PauseCallback* pause = NULL);

  /**
   * @brief Start to save current PDF document as another PDF file.
   *
   * @details It may take a long time to saving PDF document, so this function uses a progressive process to do this.<br>
   *          If current document is loaded from an existing PDF file and a different file version has been set
   *          by @link PDFDoc::SetFileVersion @endlink before saving, Foxit PDF SDK will ignore
   *          @link PDFDoc::e_SaveFlagIncremental @endlink
   *          in parameter <i>save_flags</i> and use the file version in saved PDF file.
   *
   * @param[in] file_path   A full path for the new saved PDF file. It should not be an empty string.
   * @param[in] save_flags  Document saving flags. Please refer to values starting from @link PDFDoc::e_SaveFlagNormal @endlink
   *                        and this can be one or combination of these values.
   *                        Default value: @link PDFDoc::e_SaveFlagNormal @endlink.
   * @param[in] pause       Pause callback object which decides if the parsing process needs to be paused.
   *                        This can be <b>NULL</b> which means not to pause during the parsing process.
   *                        If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                        Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   *
   * @note This function does not support to save current PDF document object just back to the PDF file which is used to
   *       construct current PDF object. In order to do so, user is recommended to do as following steps:<br>
   *       Assume that current PDF object is constructed from a PDF file named "org.pdf".
   *       <ol>
   *       <li>Use current function to save current PDF object to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that current PDF object has destructed -- which is equal to "close document".</li>
   *       <li>Remove "org.pdf" and rename "temp.tmp" to "org.pdf".</li>
   *       </ol>
   *       Then user can open the saved PDF file to do other operation.
   */
  common::Progressive StartSaveAs(const wchar_t* file_path,
                                  uint32 save_flags = PDFDoc::e_SaveFlagNormal,
                                  common::PauseCallback* pause = NULL);

  /**
   * @brief Start to save current PDF document as another PDF file.
   *
   * @details It may take a long time to saving PDF document, so this function uses a progressive process to do this.<br>
   *          If current document is loaded from an existing PDF file and a different file version has been set
   *          by @link PDFDoc::SetFileVersion @endlink before saving, Foxit PDF SDK will ignore
   *          @link PDFDoc::e_SaveFlagIncremental @endlink
   *          in parameter <i>save_flags</i> and use the file version in saved PDF file.
   *
   * @param[in] file        A @link common::file::WriterCallback @endlink object which is implemented by user to save a PDF document.
   * @param[in] save_flags  Document saving flags. Please refer to values starting from @link PDFDoc::e_SaveFlagNormal @endlink
   *                        and this can be one or combination of these values.
   *                        Default value: @link PDFDoc::e_SaveFlagNormal @endlink.
   * @param[in] pause       Pause callback object which decides if the parsing process needs to be paused.
   *                        This can be <b>NULL</b> which means not to pause during the parsing process.
   *                        If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                        Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   *
   * @note This function does not support to save current PDF document object just back to the PDF file which is used to
   *       construct current PDF object. In order to do so, user is recommended to do as following steps:<br>
   *       Assume that current PDF object is constructed from a PDF file named "org.pdf".
   *       <ol>
   *       <li>Use current function to save current PDF object to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that current PDF object has destructed -- which is equal to "close document".</li>
   *       <li>Remove "org.pdf" and rename "temp.tmp" to "org.pdf".</li>
   *       </ol>
   *       Then user can open the saved PDF file to do other operation.
   */
  common::Progressive StartSaveAs(foxit::common::file::WriterCallback* file,
                                  foxit::uint32 save_flags = PDFDoc::e_SaveFlagNormal,
                                  foxit::common::PauseCallback* pause = NULL);
#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Get bookmark root node.
   *
   * @return A bookmark object that represents the root bookmark.
   *         If there is no bookmark in current PDF document, this function will return a bookmark object which's function
   *         @link Bookmark::IsEmpty @endlink returns <b>true</b>.
   */
  Bookmark GetRootBookmark();

  /**
   * @brief Create new bookmark root node.
   *
   * @details If current PDF document already has the bookmark root node, this function will remove
   *          the old bookmark tree and create a new root node instead.
   *
   * @return A bookmark object that represents the root bookmark.
   */
  Bookmark CreateRootBookmark();

  /**
   * @brief Remove a specified bookmark.
   *
   * @param[in] bookmark  The valid bookmark that would be deleted.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveBookmark(const Bookmark& bookmark);

  /**
   * @brief Check whether current PDF document has layer (known as "Optional content group" in <PDF reference 1.7>) or not.
   *
   * @return <b>true</b> means current document has layer.
   *         <b>false</b> means current document does not have layer.
   */
  bool HasLayer() const;

  /**
   * @brief Check whether current document has header-footer.
   *
   * @return <b>true</b> means current document has header-footer,
   *         while <b>false</b> means current document does not have header-footer.
   */
  bool HasHeaderFooter();

  /**
   * @brief Get the editable header footer object.
   *
   * @details A PDF document may have been added header-footer sereral times, but only one of these header-footer can be editable.
   *          This function is to retreive the editable header-footer.
   *
   * @return A header-footer object that represents the editable header-footer.
   */
  HeaderFooter GetEditableHeaderFooter();

  /**
   * @brief Add new header-footer.
   *
   * @details A PDF document can be added header-footer sereral times. When a new header-footer is added, the old ones will not be removed
   *          but be covered by the new one if the old ones appear in the same place as new one.
   *
   * @param[in] headerfooter  A valid header-footer object to be added to current document.
   *
   * @return None.
   */
  void AddHeaderFooter(const HeaderFooter& headerfooter);

  /**
   * @brief Update header-footer.
   *
   * @details A PDF document can be added header-footer sereral times. When a header-footer is updated to the document,
   *          the old ones which appear in the same place with the new one will all be removed and then the new one will be added.
   *
   * @param[in] headerfooter  A valid header-footer object to be updated to current document.
   *
   * @return None.
   */
  void UpdateHeaderFooter(const HeaderFooter& headerfooter);

  /**
   * @brief Remove all header-footers.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveAllHeaderFooters();
#endif
  /**
   * @brief Get the count of pages.
   *
   * @return The count of page.
   */
  int GetPageCount() const;

  /**
   * @brief Get a PDF page by index.
   *
   * @details If current PDF document object is constructed with an AsyncReaderCallback which means to
   *          do asynchronous loading, this function may throw exception @link foxit::e_ErrDataNotReady @endlink.
   *          In this case, user should prepare data for specified range informed by callback function
   *          @link common::file::AsyncReaderCallback::AddDownloadHint @endlink and then call this function again.
   *
   * @param[in] index  The page index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFDoc::GetPageCount @endlink.
   *
   * @return A PDF page object.
   */
  PDFPage GetPage(int index);

  /**
   * @brief Get the display mode.
   *
   * @details Display mode specifies how the document should be displayed when opened.
   *
   * @return Display mode value. Please refer to values starting from @link PDFDoc::e_DisplayUseNone @endlink and
   *         this would be one of these values.
   */
  DisplayMode GetDisplayMode() const;

  /**
   * @brief Set the display mode.
   *
   * @details Display mode specifies how the document should be displayed when opened.
   *
   * @param[in] display_mode  Display mode value. Please refer to values starting from @link PDFDoc::e_DisplayUseNone @endlink
   *                          and this should be one of these values.
   *
   * @return None.
   */
  void SetDisplayMode(DisplayMode display_mode);

  /**
   * @brief Get the catalog dictionary.
   *
   * @return The catalog dictionary.
   */
  objects::PDFDictionary* GetCatalog() const;

  /**
   * @brief Get the trailer dictionary.
   *
   * @return The trailer dictionary.
   */
  objects::PDFDictionary* GetTrailer() const;

  /**
   * @brief Get the information dictionary.
   *
   * @details Document's information dictionary contains metadata for the document.
   *
   * @return The information dictionary.
   */
  objects::PDFDictionary* GetInfo() const;

  /**
   * @brief Get the encrypt dictionary.
   *
   * @return The encrypt dictionary.
   */
  objects::PDFDictionary* GetEncryptDict() const;

  /**
   * @brief Get the dictionary of "Pages".
   *
   * @return The dictionary of "Pages".
   */
  objects::PDFDictionary* GetPagesDict() const;

  /**
   * @brief Get an indirect object by indirect object number.
   *
   * @param[in] object_number  The indirect object number. It should be above 0.
   *
   * @return A @link objects::PDFObject @endlink object that receives the indirect PDF object. <b>NULL</b> means not found.
   */
  objects::PDFObject* GetIndirectObject(uint32 object_number);

  /**
   * @brief Add a PDF object to current PDF document, to be an indirect object.
   *
   * @details <ul>
   *          <li>If input PDF object is a direct object (whose indirect object number is 0),
   *              this functions will change it to be an indirect object and add to PDF document.
   *              Then return the new indirect object number.</li>
   *          <li>If input PDF object is already an indirect object (whose indirect object number is above 0),
   *              this function will not add it into document again.
   *              The return value will be its own indirect object number.</li>
   *          </ul>
   *
   * @param[in] pdf_object  A @link objects::PDFObject @endlink object. It should not be <b>NULL</b>.
   *
   * @return The new indirect object number. It would be above 0.
   */
  uint32 AddIndirectObject(objects::PDFObject* pdf_object);

  /**
   * @brief Delete an indirect object by indirect object number.
   *
   * @param[in] object_number  The indirect object number. It should be above 0.
   *
   * @return None.
   */
  void DeleteIndirectObject(uint32 object_number);

  /**
   * @brief Get user access permissions.
   *
   * @return User access permission. Please refer to values starting from @link PDFDoc::e_PermPrint @endlink and
   *         this would be one of these values.
   */
  uint32 GetUserPermissions() const;

  /**
   * @brief Check whether current document is a wrapper file or not.
   *
   * @return <b>true</b> means current document is a wrapper file,
   *         while <b>false</b> means current document is not a wrapper file.
   */
  bool IsWrapper() const;

  /**
   * @brief Get Wrapper type.
   *
   * @return The wrapper type. Please refer to values starting from @link PDFDoc::e_WrapperNone @endlink and
   *         this would be one or combination of its values.
   */
  WrapperType GetWrapperType() const;

  /**
   * @brief Get wrapper data if current document's wrapper type is @link PDFDoc::e_WrapperFoxit @endlink.
   *
   * @return The wrapper data. If no wrapper data can be found or current document's wrapper type is not
   *         @link PDFDoc::e_WrapperFoxit @endlink, a wrapper data object with value 0 and empty strings will be returned.
   */
  WrapperData GetWrapperData() const;

  /**
   * @brief Get wrapper offset if current document's wrapper type is @link PDFDoc::e_WrapperFoxit @endlink.
   *
   * @return The wrapper offset. If no wrapper data can be found or current document's wrapper type is not
   *         @link PDFDoc::e_WrapperFoxit @endlink, -1 will be returned.
   */
  int64 GetWrapperOffset() const;

  /**
   * @brief Get payload data if current document's wrapper type is @link PDFDoc::e_WrapperPDFV2 @endlink.
   *
   * @return The payload data. If no wrapper data can be found or current document's wrapper type is not
   *         @link PDFDoc::e_WrapperPDFV2 @endlink, a payload data object with value 0 and empty strings will be returned.
   */
  PayLoadData GetPayLoadData();

  /**
   * @brief Start to get payload file.
   *
   * @details It may take a long time to getting payload document, so this function uses a progressive process to do this.
   *
   * @param[in]  payload_file  A WriterCallback callback object. User should implement the callback function
   *                           in this callback object in order that this callback object can be used to save payload file.
   * @param[in]  pause         Pause callback object which decides if the parsing process needs to be paused.
   *                           This can be <b>NULL</b> which means not to pause during the parsing process.
   *                           If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                           Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartGetPayloadFile(foxit::common::file::WriterCallback* payload_file, common::PauseCallback* pause = NULL);

  /**
   * @brief Save current PDF document as a wrapper file.
   *
   * @details PDF wrapper is an extended standard, and it helps to hint some information to viewers.<br>
   *          PDF wrapper consists of
   *          <ul>
   *          <li>wrapper type: it is an identity string, </li>
   *          <li>wrapper offset: it tells the end of original data, </li>
   *          <li>wrapper template: it is the content of wrapper document. </li>
   *          </ul>
   *          This function uses the current size of file
   *          which is specified by <i>file_path</i> to set wrapper offset.
   *
   * @param[in] file_path         A full path of a PDF file.
   *                              Current PDF document will be saved into this PDF file as a wrapper file.
   * @param[in] wrapper_data      Wrapper data. If this is <b>NULL</b>, no wrapper data is used.
   *                              Default value: <b>NULL</b>.
   * @param[in] user_permissions  User permissions for the wrapper document. Pass 0xFFFFFFFC if no special permissions
   *                              is needed. Please refer to values starting from @link PDFDoc::e_PermPrint @endlink and
   *                              this should be one or combination of these values. Default value: 0xFFFFFFFC.
   * @param[in] owner_password    Owner password. If this is an empty string, parameter <i>user_permissions</i> will
   *                              be ignored. Default value: an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SaveAsWrapperFile(const wchar_t* file_path, const WrapperData* wrapper_data = NULL,
                         uint32 user_permissions = 0xFFFFFFFC, const char* owner_password = "");

  /**
   * @brief Start to save current PDF document as a wrapper document with a payload document (defined in PDF 2.0).
   *
   * @details It may take a long time to saving PDF document, so this function uses a progressive process to do this.<br>
   *          If current document is loaded from an existing PDF file and a different file version has been set
   *          by @link PDFDoc::SetFileVersion @endlink before saving, Foxit PDF SDK will ignore
   *          @link PDFDoc::e_SaveFlagIncremental @endlink in parameter <i>save_flags</i> and
   *          use the file version in saved PDF file.
   *
   * @param[in] file_path          A full path for the new saved PDF file. It should not be an empty string.
   * @param[in] payload_file_path  A full path of a PDF document which will be used as payload document.
   *                               It should not be an empty string.
   * @param[in] crypto_filter      The name of the cryptographic filter used to encrypt the encrypted payload document. 
   * @param[in] description        Description for wrapper file to show applications or confront users prompt information.
   * @param[in] version            The version number of the cryptographic filter used to encrypt the encrypted payload referenced by this dictionary.
   * @param[in] save_flags         Document saving flags. Please refer to values starting from
   *                               @link PDFDoc::e_SaveFlagNormal @endlink and this can be one or combination of these values.
   *                               Default value: @link PDFDoc::e_SaveFlagNormal @endlink.
   * @param[in] pause              Pause callback object which decides if the parsing process needs to be paused.
   *                               This can be <b>NULL</b> which means not to pause during the parsing process.
   *                               If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                               Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartSaveAsPayloadFile(const wchar_t* file_path, const wchar_t* payload_file_path,
                                             const wchar_t* crypto_filter, const wchar_t* description, float version,
                                             uint32 save_flags = PDFDoc::e_SaveFlagNormal,
                                             common::PauseCallback* pause = NULL);
  /**
   * @brief Check whether current PDF document has interactive form (also known as AcroForm).
   *
   * @details If current PDF document object is constructed with an AsyncReaderCallback which means to
   *          do asynchronous loading, this function may throw exception @link foxit::e_ErrDataNotReady @endlink.
   *          In this case, user should prepare data for specified range informed by callback function
   *          @link common::file::AsyncReaderCallback::AddDownloadHint @endlink and then call this function again.
   *
   * @return <b>true</b> means current document has interactive form.
   *         <b>false</b> means current document does not have interactive form.
   */
  bool HasForm() const;

  /**
   * @brief Get the count of reading bookmarks.
   *
   * @return The count of reading bookmarks.
   */
  int GetReadingBookmarkCount();
#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Get a reading bookmark by index.
   *
   * @param[in] index  The index of reading bookmarks. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFDoc::GetReadingBookmarkCount @endlink.
   *
   * @return The reading bookmark object with specified index.
   */
  ReadingBookmark GetReadingBookmark(int index);

  /**
   * @brief Insert a reading bookmark to current PDF document.
   *
   * @param[in] reading_bookmark_index  A reading bookmark index.<br>
   *                                    If <i>reading_bookmark_index</i> is less than 0, the new reading bookmark will
   *                                    be inserted to the first.<br>
   *                                    If <i>reading_bookmark_index</i> is equal to or larger than the count of
   *                                    reading bookmarks, the new reading bookmark will be inserted to the end.
   * @param[in] title                   Title string for new reading bookmark and should not an empty string.
   * @param[in] dest_page_index         The index of destination page.
   *
   * @return A new reading bookmark object.
   */
  ReadingBookmark InsertReadingBookmark(int reading_bookmark_index, const WString& title, int dest_page_index);

  /**
   * @brief Remove a reading bookmark from current PDF document.
   *
   * @param[in] reading_bookmark  A valid reading bookmark to be removed.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveReadingBookmark(const ReadingBookmark& reading_bookmark);

  /**
   * @brief Get the count of signature.
   *
   * @return The count of signature.
   */
  int GetSignatureCount();

  /**
   * @brief Get a signature by index.
   *
   * @param[in] index  The index of signature. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFDoc::GetSignatureCount @endlink.
   *
   * @return The signature object.
   */
  foxit::pdf::Signature GetSignature(int index);

  /**
   * @brief Remove a signature.
   *
   * @param[in] signature  A valid signature to be removed.
   *
   * @return None.
   */
  void RemoveSignature(const foxit::pdf::Signature& signature);
#endif
  /**
   * @brief Insert a new blank PDF page to document, by index.
   *
   * @param[in] index   The page index for new page.<br>
   *                    If parameter <i>index</i> is less than 0, the new page will be inserted to the first. <br>
   *                    If parameter <i>index</i> is equal to or larger than current page count,
   *                    the new page will be inserted to the end.
   * @param[in] width   Width of new page (unit is 1/72 inch).
   * @param[in] height  Height of new page (unit is 1/72 inch).
   *
   * @return A new PDF page object which represents a blank page.
   */
  PDFPage InsertPage(int index, float width, float height);
  /**
   * @brief Insert a new blank PDF page to document, by index.
   *
   * @param[in] index  The page index for new page.<br>
   *                   If parameter <i>index</i> is less than 0, the new page will be inserted to the first. <br>
   *                   If parameter <i>index</i> is equal to or larger than current page count,
   *                   the new page will be inserted to the end.
   * @param[in] size   Size type of new page. Please refer to values starting from @link PDFPage::e_SizeLetter @endlink and
   *                   this should be one of these values. Default value: @link PDFPage::e_SizeLetter @endlink.
   *
   * @return A new PDF page object, which represents a blank page.
   */
  PDFPage InsertPage(int index, foxit::pdf::PDFPage::Size size = PDFPage::e_SizeLetter);

  /**
   * @brief Remove a PDF page by page index.
   *
   * @param[in] index  The page index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFDoc::GetPageCount @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemovePage(int index);
  /**
   * @brief Remove a specified PDF page.
   *
   * @details Once the specified PDF page is removed successfully, the page object cannot be used any more.
   *
   * @param[in] page  A PDF page object that represents the PDF page to be removed. The page should be
   *                  in current PDF document.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemovePage(const foxit::pdf::PDFPage& page);

  /**
   * @brief Move a specified page to a new index position.
   *
   * @details If the specified page is successfully moved to the new index position, page index of all the pages
   *          between the new index and old index of the specified page will be changed as well.
   *
   * @param[in] page        A PDF page to be moved. It should be in current PDF document.
   * @param[in] dest_index  Index of the destination position in page array.
   *                        Valid range: from 0 to (<i>count</i>-1).
   *                        <i>count</i> is returned by function @link PDFDoc::GetPageCount @endlink.<br>
   *                        If parameter <i>dest_index</i> is just the same as the page index of parameter <i>page</i>,
   *                        no change will be done and this function will return <b>true</b> directly.
   *
   * @return <b>true</b> means success or no need to move current page, while <b>false</b> means failure.
   */
  bool MovePageTo(const PDFPage& page, int dest_index);

  /**
   * @brief Move one or more pages (specified by index) to a new index position.
   *
   * @details If move only one page, this function just has the same feature as function
   *          @link PDFDoc::MovePageTo @endlink.<br>
   *          If move more than one page, these page will keep the order defined in parameter <i>page_range</i>
   *          and be moved to the destination index position as a whole.<br>
   *          After this function is successful, indexes of moved pages will be changed and indexes of the rest pages
   *          may be affected as well.
   *
   * @param[in] page_range   A range object which should at least contain one valid range.
   *                         All the related pages will keep the order (specified by this range)
   *                         and be moved as a whole. If there exist duplicated indexes in the range,
   *                         only the last occurrence will be useful.
   * @param[in] dest_index   Index of the destination position, based on current page array.
   *                         Valid range: from 0 to (<i>count</i>-1).
   *                         <i>count</i> is returned by function @link PDFDoc::GetPageCount @endlink.<br>
   *
   * @return <b>true</b> means success or no need to move current page, while <b>false</b> means failure.
   */
  bool MovePagesTo(const common::Range& page_range, int dest_index);

  /**
   * @brief Start to import pages from another PDF document (via file path).
   *
   * @details It may take a long time to importing pages, so Foxit PDF SDK uses a progressive process to do this.<br>
   *          Signed signatures in the pages of source PDF document will not be imported into current PDF document.<br>
   *          Currently, Foxit PDF SDK does not support to do the importing if either current PDF document or
   *          the source PDF document contains XFA.<br>
   *          From Foxit PDF SDK 7.1, user is strongly recommended to use functions @link PDFDoc::StartExtractPages @endlink and
   *          @link PDFDoc::InsertDocument @endlink together, instead of current function. Execution efficiency of importing pages
   *          has been optimized in new functions.
   *
   * @param[in] dest_index     A page index in current PDF document. This is used to specify where
   *                           the imported pages will be inserted. If parameter <i>dest_index</i> is less than 0,
   *                           the imported pages will be inserted to the first. <br>
   *                           If parameter <i>dest_index</i> is equal to or larger than current page count,
   *                           the imported pages will be inserted to the end.
   * @param[in] src_file_path  A full path of an existing PDF file as the source PDF document
   *                           Some pages will be imported from this PDF file to current PDF document.
   * @param[in] password       A password string used to load source PDF document content.
   *                           The password can be either user password or owner password. If source PDF document is
   *                           not encrypted by password, just pass an empty string.
   * @param[in] flags          Options for importing pages. Please refer to values starting from
   *                           @link PDFDoc::e_ImportFlagNormal @endlink and this can be one or a combination of these values.
   *                           Default value: @link PDFDoc::e_ImportFlagNormal @endlink.
   * @param[in] layer_name     The name of non-selectable label or the prefix name of the non-selectable label
   *                           to be shown in layer panel of application. Default value: an empty string.<br>
   *                           If parameter <i>flags</i> contains @link PDFDoc::e_ImportFlagWithLayers @endlink,
   *                           this should not be empty and should be a valid string.
   *                           If parameter <i>flags</i> does not contain @link PDFDoc::e_ImportFlagWithLayers @endlink,
   *                           this string will be ignored.
   *                           <ul>
   *                           <li>If all the pages of source PDF document is to be imported to current document,
   *                               all layers from source document will be grouped under a non-selectable label,
   *                               and this string will be directly used as the label. </li>
   *                           <li>If only part of pages of source PDF document is to be imported to current document,
   *                               layers in the same page will be grouped under a single non-selectable label,
   *                               and this string will be used as the prefix name of the label.
   *                               The label will be like "layerName_Page_X". </li>
   *                           </ul>
   * @param[in] page_range    A range object to specify which pages is to be imported. If this range object is
   *                          constructed by default constructor and not set any value, all pages in the source
   *                          document will be imported.
   *                          Default value: a range object by default constructor and not set any value.
   * @param[in] pause         Pause object which decides if the importing process needs to be paused.
   *                          This can be <b>NULL</b> which means not to pause during the parsing process.
   *                          If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                          Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartImportPagesFromFilePath(int dest_index,
                                                   const wchar_t* src_file_path, const String& password,
                                                   uint32 flags = PDFDoc::e_ImportFlagNormal, const char* layer_name = "",
                                                   const common::Range& page_range = common::Range(),
                                                   common::PauseCallback* pause = NULL);
  /**
   * @brief Start to import pages from another PDF document (via file path).
   *
   * @details It may take a long time to importing pages, so Foxit PDF SDK uses a progressive process to do this.<br>
   *          Signed signatures in the pages of source PDF document will not be imported into current PDF document.<br>
   *          Currently, Foxit PDF SDK does not support to do the importing if either current PDF document or
   *          the source PDF document contains XFA.<br>
   *          From Foxit PDF SDK 7.1, user is strongly recommended to use functions @link PDFDoc::StartExtractPages @endlink and
   *          @link PDFDoc::InsertDocument @endlink together, instead of current function. Execution efficiency of importing pages
   *          has been optimized in new functions.
   *
   * @param[in] dest_index     A page index in current PDF document. This is used to specify where
   *                           the imported pages will be inserted. If parameter <i>dest_index</i> is less than 0,
   *                           the imported pages will be inserted to the first. <br>
   *                           If parameter <i>dest_index</i> is equal to or larger than current page count,
   *                           the imported pages will be inserted to the end.
   * @param[in] src_file_path  A full path of an existing PDF file as the source PDF document
   *                           Some pages will be imported from this PDF file to current PDF document.
   * @param[in] password       A password string used to load source PDF document content.
   *                           The password can be either user password or owner password. If source PDF document is
   *                           not encrypted by password, just pass an empty string.
   * @param[in] flags          Options for importing pages. Please refer to values starting from
   *                           @link PDFDoc::e_ImportFlagNormal @endlink and this can be one or a combination of these values.
   *                           Default value: @link PDFDoc::e_ImportFlagNormal @endlink.
   * @param[in] layer_name     The name of non-selectable label or the prefix name of the non-selectable label
   *                           to be shown in layer panel of application. Default value: an empty string.<br>
   *                           If parameter <i>flags</i> contains @link PDFDoc::e_ImportFlagWithLayers @endlink,
   *                           this should not be empty and should be a valid string.
   *                           If parameter <i>flags</i> does not contain @link PDFDoc::e_ImportFlagWithLayers @endlink,
   *                           this string will be ignored.
   *                           <ul>
   *                           <li>If all the pages of source PDF document is to be imported to current document,
   *                               all layers from source document will be grouped under a non-selectable label,
   *                               and this string will be directly used as the label. </li>
   *                           <li>If only part of pages of source PDF document is to be imported to current document,
   *                               layers in the same page will be grouped under a single non-selectable label,
   *                               and this string will be used as the prefix name of the label.
   *                               The label will be like "layerName_Page_X". </li>
   *                           </ul>
   * @param[in] page_range     A range object to specify which pages is to be imported. If this range object is
   *                           constructed by default constructor and not set any value, all pages in the source
   *                           document will be imported.
   *                           Default value: a range object by default constructor and not set any value.
   * @param[in] pause          Pause object which decides if the importing process needs to be paused.
   *                           This can be <b>NULL</b> which means not to pause during the parsing process.
   *                           If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                           Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartImportPagesFromFilePath(int dest_index,
                                                   const wchar_t* src_file_path, const WString& password,
                                                   uint32 flags = PDFDoc::e_ImportFlagNormal, const char* layer_name = "",
                                                   const common::Range& page_range = common::Range(),
                                                   common::PauseCallback* pause = NULL);
  /**
   * @brief Start to import pages from another PDF document (via PDF document object).
   *
   * @details It may take a long time to importing pages, so Foxit PDF SDK uses a progressive process to do this.<br>
   *          Signed signatures in the pages of source PDF document will not be imported into current PDF document.<br>
   *          Currently, if either current PDF document or the source PDF document contains XFA,
   *          not support to do the importing.<br>
   *          From Foxit PDF SDK 7.1, user is strongly recommended to use functions @link PDFDoc::StartExtractPages @endlink and
   *          @link PDFDoc::InsertDocument @endlink together, instead of current function. Execution efficiency of importing pages
   *          has been optimized in new functions.
   *
   * @param[in] dest_index   A page index in current PDF document. This is used to specify where the imported pages
   *                         will be inserted: If parameter <i>dest_index</i> is less than 0,
   *                         the imported pages will be inserted to the first. <br>
   *                         If parameter <i>dest_index</i> is equal to or larger than current page count,
   *                         the imported pages will be inserted to the end.
   * @param[in] src_doc      A PDF document object which is the source PDF document. Pages in this document will be
   *                         imported to current PDF document. Please keep this source PDF document object valid
   *                         until current document will not be saved any more or is closed.
   * @param[in] flags        Options for importing pages. Please refer to values starting from
   *                         @link PDFDoc::e_ImportFlagNormal @endlink and this can be one or a combination of these values.
   *                         Default value: @link PDFDoc::e_ImportFlagNormal @endlink.
   * @param[in] layer_name   The name of non-selectable label or the prefix name of the non-selectable label
   *                         to be shown in layer panel of application. Default value: an empty string.<br>
   *                         If parameter <i>flags</i> contains @link PDFDoc::e_ImportFlagWithLayers @endlink,
   *                         this should not be empty and should be a valid string.
   *                         If parameter <i>flags</i> does not contain @link PDFDoc::e_ImportFlagWithLayers @endlink,
   *                         this string will be ignored.
   *                         <ul>
   *                         <li>If all the pages of source PDF document is to be imported to current document,
   *                             all layers from source document will be grouped under a non-selectable label,
   *                             and this string will be directly used as the label. </li>
   *                         <li>If only part of pages of source PDF document is to be imported to current document,
   *                             layers in the same page will be grouped under a single non-selectable label,
   *                             and this string will be used as the prefix name of the label.
   *                             The label will be like "layerName_Page_X". </li>
   *                         </ul>
   * @param[in] page_range   A range object to specify which pages is to be inserted. If this range object is
   *                         constructed by default constructor and not set any value, all pages in the source
   *                         document will be imported.
   *                         Default value: a range object by default constructor and not set any value.
   * @param[in] pause        Pause object which decides if the importing process needs to be paused.
   *                         This can be <b>NULL</b> which means not to pause during the parsing process.
   *                         If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                         Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartImportPages(int dest_index, const PDFDoc& src_doc,
                                       uint32 flags = PDFDoc::e_ImportFlagNormal, const char* layer_name = "",
                                       const common::Range& page_range = common::Range(),
                                       common::PauseCallback* pause = NULL);

  /**
   * @brief Start to extract pages from current PDF document.
   *
   * @details It may take a long time to extracting pages, so Foxit PDF SDK uses a progressive process to do this.
   *
   * @param[in] file_path   A full path for the new saved PDF file which is used to save the extracted pages. It should not be an empty string.
   * @param[in] options     Options for extracting pages. Please refer to values starting from
   *                        @link PDFDoc::e_ExtractPagesOptionAnnotation @endlink and this can be one or a combination of these values.
   *                        0 means no option is used. 
   * @param[in] page_range  A range object to specify which pages are to be extracted. If this range object is
   *                        constructed by default constructor and not set any value, all pages in the current
   *                        document will be extracted.
   *                        Default value: a range object by default constructor and not set any value.
   * @param[in] pause       Pause object which decides if the extracting process needs to be paused.
   *                        This can be <b>NULL</b> which means not to pause during the parsing process.
   *                        If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                        Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartExtractPages(const char* file_path, uint32 options, const common::Range& page_range = common::Range(),
      common::PauseCallback* pause = NULL);

  /**
   * @brief Start to extract pages from current PDF document.
   *
   * @details It may take a long time to extracting pages, so Foxit PDF SDK uses a progressive process to do this.
   *
   * @param[in] file_path   A full path for the new saved PDF file which is used to save the extracted pages. It should not be an empty string.
   * @param[in] options     Options for extracting pages. Please refer to values starting from
   *                        @link PDFDoc::e_ExtractPagesOptionAnnotation @endlink and this can be one or a combination of these values.
   *                        0 means no option is used. 
   * @param[in] page_range  A range object to specify which pages are to be extracted. If this range object is
   *                        constructed by default constructor and not set any value, all pages in the current
   *                        document will be extracted.
   *                        Default value: a range object by default constructor and not set any value.
   * @param[in] pause       Pause object which decides if the extracting process needs to be paused.
   *                        This can be <b>NULL</b> which means not to pause during the parsing process.
   *                        If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                        Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartExtractPages(const wchar_t* file_path, uint32 options, const common::Range& page_range = common::Range(),
      common::PauseCallback* pause = NULL);

  /**
   * @brief Start to extract pages from current PDF document.
   *
   * @details It may take a long time to extracting pages, so Foxit PDF SDK uses a progressive process to do this.
   *
   * @param[in] file        A @link common::file::WriterCallback @endlink object which is implemented by user to
   *                        store the data of all the extracted pages in custom method.
   * @param[in] options     Options for extracting pages. Please refer to values starting from
   *                        @link PDFDoc::e_ExtractPagesOptionAnnotation @endlink and this can be one or a combination of these values.
   *                        0 means no option is used. 
   * @param[in] page_range  A range object to specify which pages are to be extracted. If this range object is
   *                        constructed by default constructor and not set any value, all pages in the current
   *                        document will be extracted.
   *                        Default value: a range object by default constructor and not set any value.
   * @param[in] pause       Pause object which decides if the extracting process needs to be paused.
   *                        This can be <b>NULL</b> which means not to pause during the parsing process.
   *                        If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                        Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartExtractPages(foxit::common::file::WriterCallback* file, uint32 options, const foxit::common::Range& page_range = common::Range(),
                                        foxit::common::PauseCallback* pause = NULL);

  /**
   * @brief Insert another PDF document to the specified location of current PDF document.
   *
   * @param[in] dest_index  A page index in current PDF document. This is used to specify where to insert the pages from <i>src_doc</i>:
   *                        If parameter <i>dest_index</i> is less than 0, these pages will be inserted to the first. <br>
   *                        If parameter <i>dest_index</i> is equal to or larger than current page count,
   *                        these pages will be inserted to the end.
   * @param[in] src_doc     A PDF document object which represents the PDF document to be inserted to current PDF document.
   *                        All the pages in this document will be inserted to current PDF document. 
   *                        Please keep this source PDF document object valid until current document will not be saved any more or is closed.
   * @param[in] options     Options for inserting a PDF document. Please refer to values starting from
   *                        @link PDFDoc::e_InsertDocOptionAttachments @endlink and this can be one or a combination of these values.
   *                        0 means no option is used. 
   *
   * @return None.
   */
  void InsertDocument(int dest_index, const PDFDoc& src_doc, uint32 options);

#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Import form fields and annotations from a FDF/XFDF document.
   *
   * @details For more details about the type of PDF object available for exporting,
   *          please refer to Page 22 of "XML Forms Data Format Specification".
   *
   * @param[in] fdf_doc     A valid FDF/XFDF document object, from which form fields and annotations will be imported.
   * @param[in] types       Used to decide which kind of data will be imported. Please refer to values starting from
   *                        @link PDFDoc::e_Forms @endlink and this can be one or a combination of these values.
   *                        Default value: (@link PDFDoc::e_Forms @endlink | @link PDFDoc::e_Annots @endlink).
   * @param[in] page_range  A range object that specifies some pages. Data (in specified types) from FDF/XFDF document will
   *                        be imported to these specified pages. If this range object is constructed by default constructor
   *                        and not set any value, that means data (in specified types) from FDF/XFDF document will be imported
   *                        to related PDF pages whose index have been defined in FDF/XFDF document.<br>
   *                        This parameter is only useful when parameter <i>types</i> contains @link PDFDoc::e_Annots @endlink.<br>
   *                        Default value: a range object by default constructor and not set any value.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ImportFromFDF(const fdf::FDFDoc& fdf_doc, int types = pdf::PDFDoc::e_Forms | pdf::PDFDoc::e_Annots, const common::Range& page_range = common::Range());

  /**
   * @brief Export form fields and annotations to a FDF/XFDF document.
   *
   * @details For more details about the type of PDF object available for exporting,
   *          please refer to Page 22 of "XML Forms Data Format Specification".
   *
   * @param[in] fdf_doc     A valid FDF/XFDF document object, to which form fields and annotations will be exported.
   * @param[in] types       Used to decide which kind of data will be exported. Please refer to values starting from
   *                        @link PDFDoc::e_Forms @endlink and this can be one or a combination of these values.
   *                        Default value: (@link PDFDoc::e_Forms @endlink | @link PDFDoc::e_Annots @endlink).
   * @param[in] page_range  A range object that specifies some pages. Data (in specified types) in these pages will
   *                        be exported to FDF/XFDF document. If this range object is constructed by default constructor
   *                        and not set any value, that means all the data (in specified types) of current document
   *                        will be exported to FDF/XFDF document.<br>
   *                        This parameter is only useful when parameter <i>types</i> contains @link PDFDoc::e_Annots @endlink.<br>
   *                        Default value: a range object by default constructor and not set any value.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ExportToFDF(const fdf::FDFDoc& fdf_doc, int types = pdf::PDFDoc::e_Forms | pdf::PDFDoc::e_Annots, const common::Range& page_range = common::Range());

  /**
   * @brief Export specified annotation to a FDF/XFDF document.
   *
   * @param[in] pdf_annot     A valid PDF annotation object to be exported to the FDF/XFDF document.
   * @param[in] fdf_doc       A valid FDF/XFDF document object, to which the specified annotation will be exported.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ExportAnnotToFDF(const annots::Annot& pdf_annot,const fdf::FDFDoc& fdf_doc);
#endif
  /**
   * @brief Get PDF header identifying the version of the PDF specification to which the file conforms.
   *
   * @return The PDF header string. It would be like "PDF-1.4", "PDF-1.5" and etc.
   */
  String GetHeader() const;

  /**
   * @brief Get PDF file version stored in PDF header section.
   *
   * @return The file version. For example value 14 means version "1.4", value 15 means "1.5", and etc.
   */
  int GetFileVersion();

  /**
   * @brief Set the PDF file version which will be stored in PDF header section of the saved PDF file.
   *
   * @details The new file version will not affect on current document directly, but will be used in the saved PDF file
   *          in function @link pdf::PDFDoc::SaveAs @endlink or @link PDFDoc::StartSaveAs @endlink. This function does not check
   *          whether the PDF content matches the specified version.<br>
   *          If user wants to do compliance conversion about PDF version, please refer to module "Compliance"
   *          and use class @link addon::compliance::PDFCompliance @endlink.
   *
   * @param[in] version  An integer that specifies the file version, for example value 14 means version "1.4",
   *                     value 15 means "1.5", and etc. This value should be from 10 to 17 or 20 and
   *                     be equal or greater than current version of current PDF file.
   *
   * @return None.
   */
  void SetFileVersion(int version);

  /**
   * @brief Set a PDF security handler for encryption, such as standard encryption(password),
   *        certificate encryption, and so on.
   *
   * @param[in] handler  A PDF security handler object.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note If module "RMS" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using RMS related functions and
   *       this function will throw exception @link foxit::e_ErrNoRMSModuleRight @endlink.
   */
  bool SetSecurityHandler(const SecurityHandler& handler);

  /**
   * @brief Get current PDF security handler of current document.
   *
   * @return The PDF security handler object.
   *
   * @note If module "RMS" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using RMS related functions and
   *       this function will throw exception @link foxit::e_ErrNoRMSModuleRight @endlink.
   */
  SecurityHandler GetSecurityHandler();

  /**
   * @brief Remove the security handler from current document, so that the later saved document will be unencrypted.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note If module "RMS" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using RMS related functions and
   *       this function will throw exception @link foxit::e_ErrNoRMSModuleRight @endlink.
   */
  bool RemoveSecurity();

  /**
   * @brief Count all the PDF fonts used in current PDF document.
   *
   * @details This function will enumerate all the font resources used for pages, annotations, and interactive form.
   *
   * @return The count of fonts.
   */
  int GetFontCount();

  /**
   * @brief Get a font by index.
   *
   * @param[in] index  The index of PDF font. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFDoc::GetFontCount @endlink.
   *
   * @return A font object.
   */
  common::Font GetFont(int index);

  /**
   * @brief Get the action to be performed when the document is opened.
   *
   * @return An Action object.
   */
  actions::Action GetOpenAction();

  /**
   * @brief Set the action to be performed when the document is opened.
   *
   * @param[in] action  A valid action to be set. Currently only support following types as the new action:<br>
   *                    @link actions::Action::e_TypeGoto @endlink, @link actions::Action::e_TypeURI @endlink,
   *                    @link actions::Action::e_TypeJavaScript @endlink, @link actions::Action::e_TypeNamed @endlink,
   *                    @link actions::Action::e_TypeSubmitForm @endlink, @link actions::Action::e_TypeResetForm @endlink,
   *                    @link actions::Action::e_TypeHide @endlink, @link actions::Action::e_TypeImportData @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetOpenAction(actions::Action& action);

  /**
   * @brief Remove the action to be performed when the document is opened.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveOpenAction();

  /**
   * @brief Perform JavaScript actions when the document is opened.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool DoJSOpenAction();

  /**
   * @brief Check whether current PDF document is a portfolio file or not.
   *
   * @return <b>true</b> means current PDF document is a portfolio file, while <b>false</b> means not.
   */
  bool IsPortfolio();

  /**
   * @brief Get the basic information of a page specified by index.
   *
   * @details This function can quickly get the basic information of a PDF page without getting that PDF page object.
   *          If current PDF document object is constructed with an AsyncReaderCallback which means to
   *          do asynchronous loading, this function may throw exception @link foxit::e_ErrDataNotReady @endlink.
   *          In this case, user should prepare data for specified range informed by callback function
   *          @link common::file::AsyncReaderCallback::AddDownloadHint @endlink and then call this function again.
   *
   * @param[in] index  The page index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFDoc::GetPageCount @endlink.
   *
   * @return A page basic information object which contains the basic information of specified page.
   */
  PageBasicInfo GetPageBasicInfo(int index);

  /**
   * @brief Get embedded font data.
   *
   * @return The embedded font data.
   */
  EmbeddedFontData GetEmbeddedFontData();

#ifdef _SUPPORTWEBSDK_
  objects::PDFStream* CreateIcon(String imgStream,int width, int height);
#endif
  /**
   * @brief Create DSS information in current PDF document.
   *
   * @details If current PDF document already has DSS information, this function will do nothing and return directly.
   *
   * @return None.
   */
  void CreateDSS();

};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PDFDOC_H_

