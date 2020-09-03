
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
 * @file fs_pdfcompliance.h
 * @brief Header file for PDF compliance related classes and methods.
 */

#ifndef FS_PDFCOMPLIANCE_H_
#define FS_PDFCOMPLIANCE_H_

#include "fs_compliancecommon.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/**
 * @brief Add-on namespace.
 */
namespace addon {
/**
 * @brief Compliance namespace.
 */
namespace compliance {
/**
 * This class can be used to convert the PDF version of a PDF file. Currently, support to convert to PDF 1.3/1.4/1.5/1.6/1.7.
 * Please ensure @link ComplianceEngine @endlink has been initialized successfully.
 * 
 * @see @link ComplianceEngine @endlink
 */
class PDFCompliance FS_FINAL : public Base {
 public:
  /** @brief Constructor. */
   PDFCompliance();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDFCompliance(FS_HANDLE handle);
  /** @brief Destructor. */
  ~PDFCompliance();
  /**
   * @brief Constructor, with another PDF compliance object.
   *
   * @param[in] other  Another PDF compliance object.
   */
  PDFCompliance(const PDFCompliance& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another PDF compliance object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDFCompliance& operator = (const PDFCompliance& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another PDF compliance object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PDFCompliance& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another PDF compliance object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PDFCompliance& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Convert a PDF file to a specified PDF version.
   *
   * @param[in] src_pdf_path        A complete path of source PDF file to be converted. This should not be an empty string.
   * @param[in] saved_pdf_path      A complete path for saving the converted PDF file. This should not be an empty string.
   * @param[in] convert_to_version  An integer that specifies the PDF version to convert to, for example value 14 means version "1.4",
   *                                value 15 means "1.5", and etc. Currently, only support version values 13, 14, 15, 16, and 17.
   *                                Specially, when version value is 13 (which means PDF 1.3):
   *                                <ul>
   *                                <li>if source PDF file contains transparency data, it will be converted to PDF 1.4 instead of PDF 1.3 (not support transparency).
   *                                    And user can check hit data in the returned @link ResultInformation @endlink object for more details.</li>
   *                                <li>if source PDF file does not contain any transparency data, it will be converted to PDF 1.3 as expected.</li>
   *                                </ul>
   * @param[in] progress_callback   Progress callback which is implemented by user and can be used to get progress data.
   *                                This can be <b>NULL</b>. Default value: <b>NULL</b>.
   *
   * @return A @link ResultInformation @endlink object.
   */
  ResultInformation ConvertPDFFile(const wchar_t* src_pdf_path, const wchar_t* saved_pdf_path,
                                   int convert_to_version, ProgressCallback* progress_callback = NULL);

};

}  // namespace compliance
}  // namespace addon
}  // namespace foxit

#endif  // FS_PDFCOMPLIANCE_H_

