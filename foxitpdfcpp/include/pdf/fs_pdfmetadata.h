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
 * @file fs_pdfmetadata.h
 * @brief Header file for PDF metadata related definitions and classes.
 */

#ifndef FS_PDFMETADATA_H_
#define FS_PDFMETADATA_H_

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
/**
 * In PDF document, metadata information is stored in document's Info dictionary or in metadata stream (represented
 * in Extensible Markup Language, known as XML). When a key exists in both Info dictionary and metadata stream,
 * the latest modified one will be used.<br>
 * This class is constructed from PDF document object and is used to get or set metadata information
 * from both document's Info dictionary and metadata stream.
 */
class Metadata FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, from a PDF document object.
   *
   * @details If there exists metadata information in the specified PDF document,
   *          this function is just to construct a metadata object to be associated with these information.
   *          If there is no such information in the specified PDF document, the constructed metadata object
   *          can be used to set metadata information to PDF document.
   *
   * @param[in] document  A valid PDF document object.
   */
  explicit Metadata(const PDFDoc& document);

  /**
   * @brief Constructor, with another metadata object.
   *
   * @param[in] other  Another metadata object.
   */
  Metadata(const Metadata& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another metadata object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Metadata& operator = (const Metadata& other);

  /** @brief Destructor. */
  ~Metadata();

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another metadata object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Metadata& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another metadata object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Metadata& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Check whether the related PDF document has a specified metadata key or not.
   *
   * @param[in] key  The metadata key to be checked.
   *
   * @return <b>true</b> means the related PDF document has the specified metadata key,
   *         while <b>false</b> means the related PDF document does not have the specified metadata key.
   */
  bool HasKey(const wchar_t* key) const;

  /**
   * @brief Get creation date time.
   *
   * @return Creation date time. If no creation date time can be found, a date and time object with all values 0 will be returned.
   */
  DateTime GetCreationDateTime() const;

  /**
   * @brief Get modified date time.
   *
   * @return Modified date time. If no modified date time can be found, a date and time object with all values 0 will be returned.
   */
  DateTime GetModifiedDateTime() const;

  /**
   * @brief Set creation date time.
   *
   * @param[in] date_time  New creation date time. Please refer to comment of class @link foxit::DateTime @endlink to check
   *                       the valid range for each member.
   *
   * @return None.
   */
  void SetCreationDateTime(const DateTime& date_time);

  /**
   * @brief Set modified date time.
   *
   * @param[in] date_time  New modified date time. Please refer to comment of class @link foxit::DateTime @endlink to check
   *                       the valid range for each member.
   *
   * @return None.
   */
  void SetModifiedDateTime(const DateTime& date_time);

  /**
   * @brief Get metadata value(s).
   *
   * @details For a metadata key, it may contain single or multiple values.
   *
   * @param[in] key  Metadata key string. It should not be an empty string.
   *                 Currently it can be one of the following keys:<br>
   *                 "Title", "Author", "Subject", "Keywords", "Creator", "Producer", "Trapped",
   *                 "CreationDate", "ModDate", "pdfaid".<br>
   *                 It can also be some other custom information keys if they're supported by the PDF file.<br>
   *                 For "CreationDate" and "ModDate", user is recommended to use functions
   *                 @link Metadata::GetCreationDateTime @endlink and @link Metadata::GetModifiedDateTime @endlink to
   *                 get the date information.
   *
   * @return An string array of metadata value(s).
   */
  WStringArray GetValues(const wchar_t* key) const;

  /**
   * @brief Set metadata value(s).
   *
   * @details This function is used to set single or multiple values to a specified metadata key:
   *          <ul>
   *          <li>For metadata keys "Author" and "Keywords", they can contain single or multiple values.</li>
   *          <li>For metadata key "pdfaid" which means the PDFA file version, the length of its value string is
   *              always 2, such as "2a", "1a", etc. So, only the first two characters of the first element
   *              in parameter <i>valueArray</i> will be used.</li>
   *          <li>For rest pre-defined keys, they do not support multiple values. So all the elements in
   *              parameter <i>value_array</i> will be put into one string and connected by ";".
   *              Then this string will be treated as a single value.</li>
   *          </ul>
   *
   * @param[in] key          Metadata key string. It should not be an empty string.
   *                         Currently it can be one of the following keys:<br>
   *                         "Title", "Author", "Subject", "Keywords", "Creator", "Producer", "Trapped",
   *                         "CreationDate", "ModDate", "pdfaid".<br>
   *                         It can also be some other custom information keys if they're supported by the PDF file.<br>
   *                         For "CreationDate" and "ModDate", user is recommended to use
   *                         @link Metadata::SetCreationDateTime @endlink and @link Metadata::SetModifiedDateTime @endlink
   *                         to set the date information.
   * @param[in] value_array  An string array of metadata value(s).
   *
   * @return None.
   */
  bool SetValues(const wchar_t* key, const WStringArray& value_array);

  /**
   * @brief Get customer keys from metadata.
   *
   * @details In Info dictionary and metadata stream, they have some standard keys which have same feature
   *          but different name. For this case, Foxit PDF SDK will use the standard key names in Info dictionary.
   *          Besides these standard keys, other keys will be treated as customer keys.
   *
   * @return An string array of customer keys.
   */
  WStringArray GetCustomerKeys();

  /**
   * @brief Remove a specified customer key (along with related value).
   *
   * @param[in] key  A customer key string. It should not be an empty string.
   *                 This should be one of the keys retrieved from function @link Metadata::GetCustomerKeys @endlink.
   *
   * @return None.
   */
  void RemoveCustomerKey(const wchar_t* key);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Metadata(FS_HANDLE handle =  NULL);
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PDFMETADATA_H_

