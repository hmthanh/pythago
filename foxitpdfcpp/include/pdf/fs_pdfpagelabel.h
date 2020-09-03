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
 * @file fs_pdfpagelabel.h
 * @brief Header file for PDF page labels related definitions and classes.
 */

#ifndef FS_PDFPAGELABEL_H_
#define FS_PDFPAGELABEL_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/objects/fs_pdfobject.h"
#include "pdf/objects/fs_pdfnumbertree.h"

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
 * Each page in a PDF document is identified by an integer page index that expresses the page's relative position
 * within the document. In addition, a document may optionally define page labels (PDF 1.3) to
 * identify each page visually on the screen or in print. Page label titles and page indices need not coincide:
 * the indexes are fixed, running consecutively through the document starting from 0 for the first page,
 * but the label titles can be specified in any way that is appropriate for the particular document.
 * For example, if the document begins with 12 pages of front matter numbered in roman numerals and
 * the remainder of the document is numbered in arabic, the first page would have a page index of 0 and
 * a page label title of i, the twelfth page would have index 11 and label title xii, and
 * the thirteenth page would have index 12 and label title 1.<br>
 * For purposes of page labeling, a document can be divided into labeling ranges, each of which is a series of
 * consecutive pages using the same numbering system. Pages within a range are numbered sequentially
 * in ascending order. A page's label (as numbering format), consists of a numeric portion based on
 * its position within its labeling range, optionally preceded by a label prefix denoting the range itself.
 * For example, the pages in an appendix might be labeled with decimal numeric portions prefixed with the string A-;
 * the resulting page labels would be A-1, A-2, and so on. Please refer to Section 8.3.1 "Page Labels"
 * in <PDF Reference 1.7> for more details.<br>
 * This class can be used to get page label full title directly, get information of a page label (as numbering format),
 * set or add a new page label, and so on.
 */
class PageLabels FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for page label style.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Style {
    /**
   @brief Page label style: no numbering style.
   @details This means page labels consist solely of a label prefix with no numeric portion.
     */
    e_None = 0,
    /** @brief Page label style: decimal Arabic numerals. */
    e_DecimalNums = 1,
    /** @brief Page label style: uppercase roman numerals. */
    e_UpperRomanNums = 2,
    /** @brief Page label style: lowercase roman numerals. */
    e_LowerRomanNums = 3,
    /**
   @brief Page label style: uppercase letters
   @details If this style is used, A to Z will be used for the first 26 pages, AA to ZZ will be used for the next 26,
            and so on.
     */
    e_UpperLetters = 4,
    /**
   @brief Page label style: lowercase letters
   @details If this style is used, a to z will be used for the first 26 pages, aa to zz will be used for the next 26,
            and so on.
     */
    e_LowerLetters = 5
  } Style;
  
  /**
   * @brief Constructor, from a PDF document object.
   *
   * @details If there exists page labeling range information in the specified PDF document,
   *          this function is just to construct a page labels object to be associated with these information.
   *          If there is no such information in the specified PDF document, the constructed page labels object
   *          can be used to set page labeling range information to PDF document.
   *
   * @param[in] document  A valid PDF document object.
   */
  explicit PageLabels(const PDFDoc& document);
  /** @brief Destructor. */
  ~PageLabels();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PageLabels(FS_HANDLE handle);
  /**
   * @brief Constructor, with another page labels object.
   *
   * @param[in] other  Another page labels object.
   */
  PageLabels(const PageLabels& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another page labels object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PageLabels& operator= (const PageLabels& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another page labels object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PageLabels& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another page labels object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PageLabels& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the full page label title for a page specified by page index.
   *
   * @details This function can help to get the full page label title of a specified page index directly, and
   *          user does not need to take care about which page labeling range this page belongs to.<br>
   *          Only when related PDF document does not have any page labeling range information,
   *          this function would return empty string for each valid page index.
   *
   * @param[in] page_index  A page index. Valid range: from 0 to (<i>count</i>-1). <i>count</i> is the page count of
   *                        related PDF document, and can be retrieved by function @link PDFDoc::GetPageCount @endlink.
   *
   * @return The page label full title string.
   */
  WString GetPageLabelTitle(int page_index) const;

  /**
   * @brief Check if there is a page label (as numbering format) defined with specified page index.
   *
   * @details For each page labeling range, the page label (as numbering format) is defined with
   *          its starting page index.
   *
   * @param[in] page_index  A page index. Valid range: from 0 to (<i>count</i>-1). <i>count</i> is the page count of
   *                        related PDF document, and can be retrieved by function @link PDFDoc::GetPageCount @endlink.
   *
   * @return <b>true</b> means there exists a page label defined with input page index,
   *         while <b>false</b> means there is no page label defined with input page index.
   */
  bool HasPageLabel(int page_index);

  /**
   * @brief Get the numbering style to be used for the numeric portion in the page label (as numbering format)
   *        of a specified page index.
   *
   * @details This function is only useful when input page index has a page label -- that means the page index is
   *          the starting page index of a page labeling range. Function @link PageLabels::HasPageLabel @endlink can be used
   *          to check if the page index has a page label.
   *          If input page index does not have page label, this function will return -1.
   *
   * @param[in] page_index  The page index which is the starting page index of a page labeling range.
   *                        Valid range: from 0 to (<i>count</i>-1). <i>count</i> is the page count of
   *                        related PDF document, and can be retrieved by function @link PDFDoc::GetPageCount @endlink.
   *
   * @return The numbering style. Please refer to values starting from @link PageLabels::e_None @endlink and
   *         this would be one of these values.<br>
   *         -1 means input page index does not have page label.
   */
  Style GetPageLabelStyle(int page_index) const;
  /**
   * @brief Get the label prefix string in the page label (as numbering format) of a specified page index.
   *
   * @details This function is only useful when input page index has a page label -- that means the page index is
   *          the starting page index of a page labeling range. Function @link PageLabels::HasPageLabel @endlink can be used
   *          to check if the page index has a page label.
   *          If input page index does not have page label, this function will return empty string.
   *
   * @param[in] page_index  The page index which is the starting page index of a page labeling range.
   *                        Valid range: from 0 to (<i>count</i>-1). <i>count</i> is the page count of
   *                        related PDF document, and can be retrieved by function @link PDFDoc::GetPageCount @endlink.
   *
   * @return The label prefix string. Empty string means no prefix string is used or
   *         input page index does not have page label. Function @link PageLabels::HasPageLabel @endlink can be used
   *          to check if input page index has a page label.
   */
  WString GetPageLabelPrefix(int page_index) const;
  /**
   * @brief Get the value of the numeric portion for the first page label in the page label (as numbering format)
   *        of a specified page index.
   *
   * @details Subsequent pages are numbered sequentially from this value until the next page labeling range appears.
   *          This value must be greater than or equal to 1.<br>
   *          This function is only useful when input page index has a page label -- that means the page index is
   *          the starting page index of a page labeling range. Function @link PageLabels::HasPageLabel @endlink can be used
   *          to check if the page index has a page label.
   *          If input page index does not have page label, this function will return -1.
   *
   * @param[in] page_index  The page index which is the starting page index of a page labeling range.
   *                        Valid range: from 0 to (<i>count</i>-1). <i>count</i> is the page count of
   *                        related PDF document, and can be retrieved by function @link PDFDoc::GetPageCount @endlink.
   *
   * @return The value of the numeric portion for the first page label in specified labeling range,
   *         which would be greater than or equal to 1.
   *         -1 means no first label number is defined or input page index does not have page label.
   *         Function @link PageLabels::HasPageLabel @endlink can be used to check if input page index has a page label.
   */
  int GetPageLabelStart(int page_index) const;

  /**
   * @brief Set a page label (as numbering format) defined with a page index which is the starting page index of the range.
   *
   * @details <ul>
   *          <li>If no any page labeling range in the related PDF document, this function will set input page index as
   *              the starting page of a new page labeling range and use input values as page label (as numbering format)
   *              for this new range. Pages following the specified page will be in the same labeling range,
   *              until the next page labeling range appears. Specially, in this case, if input page index is not 0,
   *              this function will also add a new page label for index 0, with no label style, no prefix,
   *              first label number = 1, by default -- this is required in Section 8.3.1 "Page Labels"
   *              in <PDF reference 1.7>.</li>
   *          <li>If these is no page label for input page index, this function will set input page index as
   *              the starting page of a new page labeling range and use input values as page label (as numbering format)
   *              for this new range. Pages following the specified page will be in the same labeling range,
   *              until the next page labeling range appears.</li>
   *          <li>If there exists a page label for input page index, this function will
   *              replace the old page label (as numbering format) with input values.</li>
   *          </ul>
   *
   * @param[in] page_index          The page index which is the starting page index of a page labeling range.
   *                                Valid range: from 0 to (<i>count</i>-1). <i>count</i> is the page count of
   *                                related PDF document, and can be retrieved by function
   *                                @link PDFDoc::GetPageCount @endlink.
   * @param[in] label_style         The numbering style to be used for the numeric portion in the page labeling range.
   *                                Please refer to values starting from @link PageLabels::e_None @endlink and
   *                                this should be one of these values.
   * @param[in] first_label_number  The value of the numeric portion for the first page label
   *                                in the page labeling range. It should be greater than or equal to 1.
   *                                If the input value is invalid, Foxit PDF SDK will use 1 by default.
   * @param[in] prefix_string       The label prefix string for page labels in the labeling range.
   *                                This can be an empty string which means not use prefix string.
   *                                Default value : an empty string.
   *
   * @return None.
   */
  void SetPageLabel(int page_index, Style label_style, int first_label_number, const WString& prefix_string = WString());

  /**
   * @brief Remove a page label (as numbering format) defined with a specified page index.
   *
   * @details After the specified page label is removed, the related labeling range will be merged to
   *          the previous page labeling range sequence.<br>
   *          As required in Section 8.3.1 "Page Labels" in <PDF reference 1.7>, a page label defined with
   *          page index 0 is required. So user is recommended not to remove the page label of page index 0 singly.
   *
   * @param[in] page_index  The page index which is the starting page index of a page labeling range.
   *                        Valid range: from 0 to (<i>count</i>-1). <i>count</i> is the page count of
   *                        related PDF document, and can be retrieved by function @link PDFDoc::GetPageCount @endlink.
   *                        Not recommend to remove the page label defined with page index 0 singly
   *                        as required in Section 8.3.1 "Page Labels" in <PDF reference 1.7>,
   *
   * @return None.
   */
  void RemovePageLabel(int page_index);

  /**
   * @brief Remove all page labels.
   *
   * @return None.
   */
  void RemoveAll();

  /**
   * @brief Get the page labels number tree.
   *
   * @return The page labels number tree.
   */
  objects::PDFNumberTree GetNumberTree();

};
}  // namespace pdf
}  // namespace foxit
#endif  //  FS_PDFPAGELABEL_H_

