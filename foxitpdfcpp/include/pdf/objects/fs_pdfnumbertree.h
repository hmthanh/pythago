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
 * @file fs_pdfnumbertree.h
 * @brief Header file for PDF number tree related definitions and classes.
 */

#ifndef FS_PDFNUMBERTREE_H_
#define FS_PDFNUMBERTREE_H_

#include "common/fs_common.h"
#include "pdf/objects/fs_pdfobject.h"

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
 * @brief PDF objects namespace.
 */
namespace objects {
/**
 * Number tree is a kind of common data structure in PDF. A number tree is similar to a number tree, except
 * that keys in a number tree are integers instead of strings and are sorted in ascending numerical order.
 * Number tree has following characteristics:<br>
 * <ul>
 * <li>key integers in a number tree are sorted in ascending numerical order and each key integer
 *     in the same number tree is unique;</li>
 * <li>values associated with the key integers may be objects of any type, depending on the purpose of the number tree;</li>
 * <li>number tree can represent an arbitrarily large collection of key-value pairs, which can be looked up
 *     efficiently without requiring the entire data structure to be read from the PDF file.</li>
 * </ul>
 * Class @link PDFNumberTree @endlink is used to be associated with an existing number tree with specified type or create one.
 * It offers functions to get key-value pairs in the number tree, and set/add/remove any key-value pair.
 * Currently, class @link PDFNumberTree @endlink can be associated with following number tree defined in PDF document:
 * <ul>
 * <li>Page labels number tree (with type @link PDFNumberTree::e_PageLabels @endlink),
 *     which defines the page labeling for the document. The keys in this tree are page indexes;
 *     the corresponding values are page label dictionaries (Please refer to <PDF Renferece 1.7> P594 Section 8.3.1,
 *     "Page Labels"). Each page index denotes the first page in a labeling range to which the specified
 *     page label dictionary applies. The tree must include a value for page index 0.</li>
 * </ul>
 */
class PDFNumberTree FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for number tree type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Type {
    /** @brief "PageLabels" number tree. */
    e_PageLabels = 1
  } Type;
  
  /**
   * @brief Constructor, with parameters.
   *
   * @details If there exists number tree with specified type in the PDF document,
   *          this function is just to construct a PDF number tree object to be associated with the number tree.
   *          If there is no such number tree in PDF document, the constructed PDF number tree object can be used
   *          to create such number tree in PDF document and add items to the number tree.
   *
   * @param[in] document  A valid PDF document object.
   * @param[in] type      The type of the number tree. Please refer to values starting from
   *                      @link PDFNumberTree::e_PageLabels @endlink and this should be one of these values.
   */
  PDFNumberTree(const PDFDoc& document, Type type);
  /** @brief Constructor.*/
  PDFNumberTree();
  /** @brief Destructor. */
  ~PDFNumberTree();

  /**
   * @brief Constructor, with another PDF number tree object.
   *
   * @param[in] other  Another PDF number tree object.
   */
  PDFNumberTree(const PDFNumberTree& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another PDF number tree object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDFNumberTree& operator = (const PDFNumberTree& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another PDF number tree object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PDFNumberTree& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another PDF number tree object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PDFNumberTree& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the type of current number tree.
   *
   * @return Type of current number tree. Please refer to values starting from @link PDFNumberTree::e_PageLabels @endlink and
   *         this would be one of these values.
   */
  Type GetType();

  /**
   * @brief Check if the specified key integer exists in current number tree.
   *
   * @param[in] number  An integer that represents the key to be checked.
   *
   * @return <b>true</b> means the specified integer exists in current number tree,
   *         and <b>false</b> means the specified integer does not exist in current number tree.
   */
  bool HasNumber(int number);

  /**
   * @brief Get the value (as PDF object) of a specified key integer.
   *
   * @param[in] number  An integer as the key.
   *
   * @return A @link PDFObject @endlink object. The type of returned PDF object depends on the purpose of current number tree.
   *         Please refer to comment of class @link PDFNumberTree @endlink for more details.
   */
  objects::PDFObject* GetObj(int number);

  /**
   * @brief Set the value (as PDF object) of a specified key integer. If the key integer does not exist, it will be
   *        added to current number tree with the value.
   *
   * @param[in] number      An integer as the key.
   * @param[in] pdf_object  A PDF object to be set as the key's value. It should not be <b>NULL</b>.
   *                        The type of this PDF object should match current number tree; otherwise,
   *                        the input PDF object is invalid. Please refer to comment of class @link PDFNumberTree @endlink
   *                        for more details.<br>
   *                        User should not release this PDF object after this function succeeds.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetObj(int number, objects::PDFObject* pdf_object);

  /**
   * @brief Remove a key integer from current number tree, along with its value (as PDF object).
   *
   * @details If the input key integer does not exist in current number tree, this function will
   *          return <b>true</b> directly.
   *
   * @param[in] number  An integer as the key to be removed.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveObj(int number);

  /**
   * @brief Remove all key integers from current number tree, along with theirs value (as PDF object).
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveAllObjs();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDFNumberTree(FS_HANDLE handle);

};

}  // namespace objects
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PDFNUMBERTREE_H_

