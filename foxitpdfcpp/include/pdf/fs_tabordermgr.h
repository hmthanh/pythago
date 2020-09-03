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
 * @file fs_tabordermgr.h
 * @brief Header file for PDF tab order manager related definitions and classes.
 */

#ifndef FS_TABORDERMGR_H_
#define FS_TABORDERMGR_H_

#include "common/fs_common.h"
#include "pdf/annots/fs_annot.h"
#include "pdf/fs_pdfpage.h"

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
 * Tab order is the order to navigate through annotations on a PDF page by using Tab key in keyboard.
 * This class offers functions to manager the order of moving the keyboard focus among annotations on a PDF page.
 * Tab order manager will ignore following types of annotations:<br>
 * note annotations which are as reply annotations, note annotations which are as state annotations,
 * pop-up annotations, annotations whose flags contain @link annots::Annot::e_FlagHidden @endlink.<br>
 * This class offers functions to get the order type and get annotations one by one in the order type.
 * This class also offers functions to change the order type:
 * <ul>
 * <li>@link TabOrderMgr::SetOrderType @endlink can be used to change the tab order type.
 *     Specially, if the tab order type is changed to @link TabOrderMgr::e_Structure @endlink,
 *     function @link TabOrderMgr::AdjustStructureOrder @endlink could be called to set the order.</li>
 * <li>Function @link TabOrderMgr::AdjustStructureOrder @endlink can be called directly to change the order type
 *     to structure order and set the structure order at the same time.</li>
 * </ul>
 * After @link TabOrderMgr::SetOrderType @endlink being used or calling function
 * @link TabOrderMgr::AdjustStructureOrder @endlink, function @link TabOrderMgr::Reload @endlink should be called;
 * otherwise the annotations' order may not be changed as expected.
 *
 * @see @link PDFPage @endlink
 * @see @link annots::Annot @endlink
 */
class TabOrderMgr FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for tab order type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _OrderType {
    /** @brief None (index order): Annotations are visited in annotation's index across the page.*/
    e_None = 0x0000,
    /** @brief R (row order): Annotations are visited in rows running horizontally across the page.*/
    e_Row = 0x0001,
    /** @brief C (column order): Annotations are visited in columns running vertically up and down the page. */
    e_Column = 0x0002,
    /** @brief S (structure order): Annotations are visited in the order in which they appear in the structure tree. */
    e_Structure = 0x0003
  } OrderType;
  
  /**
   * @brief Constructor, from a PDF page object.
   *
   * @param[in] page  A valid PDF page.
   */
  explicit TabOrderMgr(const PDFPage& page);

  /**
   * @brief Constructor, with another tab order manager object.
   *
   * @param[in] other  Another tab order manager object.
   */
  TabOrderMgr(const TabOrderMgr& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another tab order manager object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TabOrderMgr& operator = (const TabOrderMgr& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another tab order manager object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const TabOrderMgr& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another tab order manager object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const TabOrderMgr& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;
  /** @brief Destructor. */
  ~TabOrderMgr();

  /**
   * @brief Reload the tab order of annotations.
   *
   * @details This function should be called when:
   *          <ul>
   *          <li>any annotation in related PDF page is moved/deleted/added;</li>
   *          <li>related page's rotation is changed;</li>
   *          <li>reading direction of related PDF document is changed;</li>
   *          <li>@link TabOrderMgr::SetOrderType @endlink is used or function
   *              @link TabOrderMgr::AdjustStructureOrder @endlink is called to
   *              change the tab order type or structure order.</li>
   *          </ul>
   *
   * @return None.
   */
  void Reload();

  /**
   * @brief Get the tab order type.
   *
   * @return The tab order type. Please refer to values starting from @link TabOrderMgr::e_None @endlink and
   *         this would be one of these values.
   */
  OrderType GetOrderType() const;

  /**
   * @brief Set the tab order type.
   *
   * @param[in] order_type  The new tab order type. It should be one of following values:
   *                        <ul>
   *                        <li>@link TabOrderMgr::e_None @endlink: means not to use tab order.</li>
   *                        <li>@link TabOrderMgr::e_Row @endlink: means to use row order.</li>
   *                        <li>@link TabOrderMgr::e_Column @endlink: means to use column order.</li>
   *                        <li>@link TabOrderMgr::e_Structure @endlink: means to use struct order and then function
   *                            @link TabOrderMgr::AdjustStructureOrder @endlink could be called to set the order.</li>
   *                        </ul>
   *
   * @return None.
   */
  void SetOrderType(OrderType order_type);

  /**
   * @brief Get the first annotation in current tab order.
   *
   * @return The first annotation. If the return value of function @link annots::Annot::IsEmpty @endlink for
   *         the returned annotation object is <b>true</b>, that means there is no annotation.
   */
  annots::Annot GetFirstAnnot();

  /**
   * @brief Get the last annotation in current tab order.
   *
   * @return The last annotation. If the return value of function @link annots::Annot::IsEmpty @endlink for
   *         the returned annotation object is <b>true</b>, that means there is no annotation.
   */
  annots::Annot GetLastAnnot();

  /**
   * @brief Get the next annotation of specified annotation in current tab order.
   *
   * @param[in] annot  The valid specified annotation.
   *
   * @return The next annotation. If the return value of function @link annots::Annot::IsEmpty @endlink for
   *         the returned annotation object is <b>true</b>, that means the specified annotation is the last annotation
   *         in current tab order.
   */
  annots::Annot GetNextAnnot(const annots::Annot& annot);

  /**
   * @brief Get the previous annotation of specified annotation in current tab order.
   *
   * @param[in] annot  The valid specified annotation.
   *
   * @return The previous annotation. If the return value of function @link annots::Annot::IsEmpty @endlink for
   *         the returned annotation object is <b>true</b>, that means the specified annotation is the first annotation
   *         in current tab order.
   */
  annots::Annot GetPrevAnnot(const annots::Annot& annot);

  /**
   * @brief Adjust the structure order with specified annotations, and tab order type will be set to
   *        @link TabOrderMgr::e_Structure @endlink at the same time.
   *
   * @details This function is used to adjust the annotation order for structure tab order.
   *          First, re-order annotations in the input array according to the order in this array,
   *          and then re-order the reset annotations (which are not included in the input array)
   *          by the reading direction of PDF document.<br>
   *          After this function succeeds, indexes of all annotations in the related PDF page will be changed.
   *
   * @param[in] annot_array  An array of annotations which will be re-ordered first for structure tab order.
   *                         All the annotations in this array should belong to the same page as the one related to
   *                         current tab order manager. These annotations should all be valid and should be
   *                         different from each other.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool AdjustStructureOrder(const annots::AnnotArray& annot_array);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit TabOrderMgr(FS_HANDLE handle =  NULL);
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_TABORDERMGR_H_

