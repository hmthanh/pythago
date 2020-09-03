
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
 * @file fs_pdfa.h
 * @brief Header file for PDFA compliance related classes and methods.
 */

#ifndef FS_PDFA_H_
#define FS_PDFA_H_

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
 * This class can be used to verify if a PDF file matches a PDF/A version or convert a PDF file to a PDF/A version.
 * Please ensure @link ComplianceEngine @endlink has been initialized successfully.
 * 
 * @see @link ComplianceEngine @endlink
 */
class PDFACompliance FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for PDF/A version.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Version {
    /** @brief PDF/A-1a. */
    e_VersionPDFA1a = 1,
    /** @brief PDF/A-1b. */
    e_VersionPDFA1b = 2,
    /** @brief PDF/A-2a. */
    e_VersionPDFA2a = 3,
    /** @brief PDF/A-2b. */
    e_VersionPDFA2b = 4,
    /** @brief PDF/A-2u. */
    e_VersionPDFA2u = 5,
    /** @brief PDF/A-3a. */
    e_VersionPDFA3a = 6,
    /** @brief PDF/A-3b. */
    e_VersionPDFA3b = 7,
    /** @brief PDF/A-3u. */
    e_VersionPDFA3u = 8
  } Version;
  

  /** @brief Constructor. */
  PDFACompliance();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDFACompliance(FS_HANDLE handle);
  /** @brief Destructor. */
  ~PDFACompliance();
  /**
   * @brief Constructor, with another PDFA compliance object.
   *
   * @param[in] other  Another PDFA compliance object.
   */
  PDFACompliance(const PDFACompliance& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another PDFA compliance object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDFACompliance& operator = (const PDFACompliance& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another PDFA compliance object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PDFACompliance& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another PDFA compliance object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PDFACompliance& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Verify a PDF file with specified PDFA version.
   *
   * @param[in] verify_version     PDFA version to verify.
   * @param[in] src_pdf_path       A complete path of source PDF file to be verified. This should not be an empty string.
   * @param[in] first_page_index   Index of the first page to be verified, staring from 0. Default value: 0.
   * @param[in] last_page_index    Index of the last page to be verified. If this is -1, that means
   *                               all the pages of the source PDF file will be verified and
   *                               parameter <i>first_page_index</i> would be ignored. Default value: -1.
   * @param[in] progress_callback  Progress callback which is implemented by user and can be used to get progress data.
   *                               This can be <b>NULL</b>. Default value: <b>NULL</b>.
   *
   * @return A @link ResultInformation @endlink object.
   */
  ResultInformation Verify(Version verify_version, const wchar_t* src_pdf_path, 
                           int first_page_index = 0, int last_page_index = -1,
                           ProgressCallback* progress_callback = NULL);

  /**
   * @brief Convert a PDF file with specified PDFA version.
   *
   * @param[in] src_pdf_path        A complete path of source PDF file to be converted. This should not be an empty string.
   * @param[in] saved_pdf_path      A complete path for saving the converted PDF file. This should not be an empty string.
   * @param[in] convert_to_version  PDFA version to convert to.
   * @param[in] progress_callback   Progress callback which is implemented by user and can be used to get progress data.
   *                                This can be <b>NULL</b>. Default value: <b>NULL</b>.
   *
   * @return A @link ResultInformation @endlink object.
   */
  ResultInformation ConvertPDFFile(const wchar_t* src_pdf_path, const wchar_t* saved_pdf_path,
                                   Version convert_to_version, ProgressCallback* progress_callback = NULL);

};

}  // namespace compliance
}  // namespace addon
}  // namespace foxit

#endif  // FS_PDFA_H_

