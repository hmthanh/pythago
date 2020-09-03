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
 * @file fs_compare.h
 * @brief Header file for comparison related definitions and classes.
 */

#ifndef FS_COMPARE_H_
#define FS_COMPARE_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/fs_pdfpage.h"

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
 * @brief Comparison namespace.
 */
namespace comparison {
/** This class represents the compare result information. */
class CompareResultInfo FS_FINAL : public Object {
 public:
  /**
   * @brief Enumeration for compare result type.
   *
   * @details Values of this enumeration can be used alone.
   */
  typedef enum _CompareResultType {
    /** @brief Result type: unsupported or invalid. */
    e_CompareResultTypeNone = -1,
    /** @brief Result type: delete text. */
    e_CompareResultTypeDeleteText = 0,
    /** @brief Result type: insert text. */
    e_CompareResultTypeInsertText = 1,
    /** @brief Result type: replace text. */
    e_CompareResultTypeReplaceText = 2,
    /** @brief Result type: delete image. */
    e_CompareResultTypeDeleteImage = 6,
    /** @brief Result type: insert image. */
    e_CompareResultTypeInsertImage = 7,
    /** @brief Result type: replace image. */
    e_CompareResultTypeReplaceImage = 8,
    /** @brief Result type: delete path. */
    e_CompareResultTypeDeletePath = 9,
    /** @brief Result type: insert path. */
    e_CompareResultTypeInsertPath = 10,
    /** @brief Result type: replace path. */
    e_CompareResultTypeReplacePath = 11,
    /** @brief Result type: delete shading. */
    e_CompareResultTypeDeleteShading = 12,
    /** @brief Result type: insert shading. */
    e_CompareResultTypeInsertShading = 13,
    /** @brief Result type: replace shading. */
    e_CompareResultTypeReplaceShading = 14,
    /** @brief Result type: delete annotation. */
    e_CompareResultTypeDeleteAnnot = 15,
    /** @brief Result type: insert annotation. */
    e_CompareResultTypeInsertAnnot = 16,
    /** @brief Result type: replace annotation. */
    e_CompareResultTypeReplaceAnnot = 17,
    /** @brief (Reserved, not supported yet) Result type: text attribute change. */
    e_CompareResultTypeTextAttriChange = 18
  } CompareResultType;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] type           Result type. Please refer to values starting from @link CompareResultInfo::e_CompareResultTypeNone @endlink
   *                           and this should be one of these values.
   * @param[in] rect_array     Rectangle array which specifies the location of parameter <i>diff_contents</i> in the PDF page to be compared.
   * @param[in] diff_contents  Different contents as compared result.
   */
  CompareResultInfo(CompareResultType type, RectFArray rect_array, WString diff_contents) {
    this->type = type;
    this->rect_array = rect_array;
    this->diff_contents = diff_contents;
  }

  /** @brief Constructor. */
  CompareResultInfo()
    : type(e_CompareResultTypeNone) {}

  /** @brief Destructor. */
  ~CompareResultInfo() {}

  /**
   * @brief Constructor, with another result information object.
   *
   * @param[in] result_info  Another result information object.
   */
  CompareResultInfo(const CompareResultInfo& result_info) {
    this->type = result_info.type;
    this->rect_array = result_info.rect_array;
    this->diff_contents = result_info.diff_contents;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] result_info  Another result information object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  CompareResultInfo& operator = (const CompareResultInfo& result_info) {
    this->type = result_info.type;
    this->rect_array = result_info.rect_array;
    this->diff_contents = result_info.diff_contents;

    return *this;
  }

  /**
   * @brief Result type. Please refer to values starting from @link CompareResultInfo::e_CompareResultTypeNone @endlink
   *        and this should be one of these values.
   */
  CompareResultType type;

  /** @brief Rectangle array which specifies the location of parameter <i>diff_contents</i> in the PDF page to be compared.*/
  RectFArray rect_array;

  /** @brief Different contents as compared result. */
  WString diff_contents;
};

/** This class represents an array of @link comparison::CompareResultInfo @endlink objects. */
FSDK_DEFINE_ARRAY(CompareResultInfoArray, CompareResultInfo)

/**
 * This class contains all the results of a comparison process, including the results in both base document and compared document.
 * This class is used as the return type of function @link Comparison::DoCompare @endlink.
 *
 * @see @link Comparison @endlink.
 */
class CompareResults FS_FINAL : public Object {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] base_doc_results      Compare results of base document.
   * @param[in] compared_doc_results  Compare results of compared document.
   */
  CompareResults(CompareResultInfoArray base_doc_results, CompareResultInfoArray compared_doc_results)
      : base_doc_results(base_doc_results), compared_doc_results(compared_doc_results) {
  }

  /** @brief Constructor. */
  CompareResults() {}

  /** @brief Destructor. */
  ~CompareResults(){}

  /**
   * @brief Constructor, with another compare result object.
   *
   * @param[in] compare_results  Another compare result object.
   */
  CompareResults(const CompareResults& compare_results)
    : base_doc_results(compare_results.base_doc_results)
    , compared_doc_results(compare_results.compared_doc_results) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] compare_results  Another compare result object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  CompareResults& operator = (const CompareResults& compare_results) {
    base_doc_results = compare_results.base_doc_results;
    compared_doc_results = compare_results.compared_doc_results;

    return *this;
  }

  /**
   * @brief Clear all the result information.
   *
   * @return None.
   */
  void Clear()
  {
      base_doc_results.RemoveAll();
      compared_doc_results.RemoveAll();
  }

  /**
   * @brief A result information array, which contains all the compared results of
   *        a PDF page (which has been compared) in the base document.
   */
  CompareResultInfoArray base_doc_results;

  /**
   * @brief A result information array, which contains all the compared results of
   *        a PDF page (which has been compared) in the compared document.
   */
  CompareResultInfoArray compared_doc_results;
};

/**
 * This class can be used to compare one PDF file (as "base document") with another PDF file (as "compared document") page by page.
 */
class Comparison FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for compare type flags.
   *
   * @details Values of this enumeration can be used alone and some values can be used in combination.
   */
  typedef enum _CompareType {
    /** @brief Compare all content. This value should be used alone. */
    e_CompareTypeAll = 0x00000000,
    /** @brief Compare text only. */
    e_CompareTypeText = 0x00000001
  } CompareType;
  

  /**
   * @brief Constructor, from PDF document object.
   *
   * @param[in] base_doc      A valid PDF document object as base document.
   * @param[in] compared_doc  A valid PDF document object as compared document.
   *
   * @note If module "Comparison" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using compare related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoComparisonModuleRight @endlink.
   */
  explicit Comparison(const pdf::PDFDoc& base_doc, const pdf::PDFDoc& compared_doc);

  /**
   * @brief Constructor, with another comparison object.
   *
   * @param[in] other  Another comparison object.
   */
  Comparison(const Comparison& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Comparison(FS_HANDLE handle);

  /** @brief Destructor. */
  ~Comparison();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another comparison object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Comparison& operator = (const Comparison& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another comparison object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Comparison& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another comparison object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Comparison& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Compare a PDF page of base document with a PDF page in compared document. "base document" and "compared document" means
   *        the PDF documents objects that aredused to construct current object.
   *
   * @param[in] base_page_index      Page index in base document. Valid range: from 0 to (<i>base_page_count</i>-1).
   *                                 <i>base_page_count</i> is returned by function @link pdf::PDFDoc::GetPageCount @endlink for base document.
   * @param[in] compared_page_index  Page index in compared document. Valid range: from 0 to (<i>compared_page_count</i>-1).
   *                                 <i>compared_page_count</i> is returned by function @link pdf::PDFDoc::GetPageCount @endlink for compared document.
   * @param[in] compare_flags        Compare type which specifies what to be compared in PDF pages. Please refer to values starting from
   *                                 @link Comparison::e_CompareTypeAll @endlink and this can be one or combination of some of these values.
   *
   * @return A @link comparison::CompareResults @endlink object.
   */
  CompareResults DoCompare(int base_page_index, int compared_page_index, foxit::uint32 compare_flags);

  /**
   * @brief Compare the base document with compared document (which are used to construct current object)
   *        and then generate a PDF document as comparison result.
   *
   * @details It may take a long time to compare content of two PDF documents and generate the new PDF document.
   *
   * @param[in] compare_flags  Compare type which specifies what to be compared in PDF pages. Please refer to values starting from
   *                           @link Comparison::e_CompareTypeAll @endlink and this can be one or combination of some of these values.
   *
   * @return A @link pdf::PDFDoc @endlink object which represents the PDF document as comparison result.
   */
  pdf::PDFDoc GenerateComparedDoc(foxit::uint32 compare_flags);
};
}  // namespace comparison
}  // namespace addon
}  // namespace foxit

#endif  // FS_COMPARE_H_

