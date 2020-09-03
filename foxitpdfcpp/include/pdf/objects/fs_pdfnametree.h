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
 * @file fs_pdfnametree.h
 * @brief Header file for PDF name tree related definitions and classes.
 */

#ifndef FS_PDFNAMETREE_H_
#define FS_PDFNAMETREE_H_

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
 * Name tree is a kind of common data structure in PDF. Name tree serves a similar purpose to PDF dictionary
 * - associating keys and values - but by different means: in the name tree, a key name is treated as
 * an alias of its value object. That means, the value object can be referred to by the key name instead of
 * by reference object.<br>
 * Name tree has following characteristics:<br>
 * <ul>
 * <li>key names in a name tree are ordered and each key name in the same name tree is unique;</li>
 * <li>values associated with the key names may be objects of any type, depending on the purpose of the name tree;</li>
 * <li>name tree can represent an arbitrarily large collection of key-value pairs, which can be looked up efficiently
 *     without requiring the entire data structure to be read from the PDF file.</li>
 * </ul>
 * Class @link PDFNameTree @endlink is used to be associated with an existing name tree with specified type or create one.
 * It offers functions to get key-value pairs in the name tree, and set/add/remove any key-value pair.
 * Currently, class @link PDFNameTree @endlink can be associated with following name trees defined in PDF document:
 * <ul>
 * <li>Destinations name tree (with type @link PDFNameTree::e_Dests @endlink),
 *     which maps name strings to destinations. Values in this name tree should be a destination array
 *     (or a reference object to destination array).</li>
 * <li>JavaScript name tree (with type @link PDFNameTree::e_JavaScript @endlink),
 *     which maps name strings to document-level JavaScript actions. Values in this name tree should be
 *     a javaScript action dictionary (or a reference object to javaScript action dictionary).</li>
 * <li>EmbeddedFiles name tree, with type @link PDFNameTree::e_EmbeddedFiles @endlink, which maps name strings to
 *     file specifications for embedded file streams. Values in this name tree should be
 *     a file specification dictionary (or a reference object to file specification dictionary),
 *     which contains an embedded file stream.</li>
 * </ul>
 * For convenient use about embedded files (known as attachments as well) in a PDF document,
 * please refer to class @link pdf::Attachments @endlink.
 *
 * @see @link pdf::Attachments @endlink
 */
class PDFNameTree FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for name tree type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Type {
    /** @brief "Dests" name tree. */
    e_Dests = 1,
    /** @brief "JavaScript" name tree. */
    e_JavaScript = 2,
    /** @brief "EmbeddedFiles" name tree. */
    e_EmbeddedFiles = 3
  } Type;
  
  /**
   * @brief Constructor, with parameters.
   *
   * @details If there exists name tree with specified type in the PDF document,
   *          this function is just to construct a PDF name tree object to be associated with the name tree.
   *          If there is no such name tree in PDF document, the constructed PDF name tree object can be used
   *          to create such name tree in PDF document and add items to the name tree.
   *
   * @param[in] document  A valid PDF document object.
   * @param[in] type      The type of the name tree. Please refer to values starting from @link PDFNameTree::e_Dests @endlink
   *                      and this should be one of these values.
   */
  PDFNameTree(const PDFDoc& document, Type type);
  /** @brief Constructor.*/
  PDFNameTree();
  /** @brief Destructor. */
  ~PDFNameTree();

  /**
   * @brief Constructor, with another PDF name tree object.
   *
   * @param[in] other  Another PDF name tree object.
   */
  PDFNameTree(const PDFNameTree& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another PDF name tree object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDFNameTree& operator = (const PDFNameTree& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another PDF name tree object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PDFNameTree& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another PDF name tree object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PDFNameTree& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the type of current name tree.
   *
   * @return Type of current name tree. Please refer to values starting from @link PDFNameTree::e_Dests @endlink and
   *         this would be one of these values.
   */
  Type GetType();

  /**
   * @brief Check if the specified key name exists in current name tree.
   *
   * @param[in] name  A string that represents the key name to be checked. It should not be an empty string.
   *
   * @return <b>true</b> means the specified name exists in current name tree,
   *         and <b>false</b> means the specified name does not exist in current name tree.
   */
  bool HasName(const WString& name);

  /**
   * @brief Get the count of elements in current name tree.
   *
   * @return The element count.
   */
  int GetCount();

  /**
   * @brief Get a key name in the name tree, by index.
   *
   * @param[in] index  Index of the key name to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFNameTree::GetCount @endlink.
   *
   * @return A string that represents the key name.
   */
  WString GetName(int index);

  /**
   * @brief Get the value (as PDF object) of a specified key name.
   *
   * @param[in] name  String for a key name. It should not be an empty string.
   *
   * @return A @link PDFObject @endlink object. The type of returned PDF object depends on the purpose of current name tree.
   *         Please refer to comment of class @link PDFNameTree @endlink for more details.
   */
  objects::PDFObject* GetObj(const WString& name);
  /**
   * @brief Set the value (as PDF object) of a specified key name.
   *
   * @param[in] name        String for a key name. It should not be an empty string.
   *                        This name should have existed in current name tree.
   * @param[in] pdf_object  A PDF object to be set as the name's value. It should not be <b>NULL</b>.
   *                        The type of this PDF object should match current name tree; otherwise,
   *                        the input PDF object is invalid. Please refer to comment of class @link PDFNameTree @endlink
   *                        for more details.<br>
   *                        User should not release this PDF object after this function succeeds.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetObj(const WString& name, objects::PDFObject* pdf_object);
  /**
   * @brief Rename an existing key name to a new key name.
   *
   * @param[in] old_name  String for an old key name which is to be renamed. This should not be an empty string.
   *                      This name should have existed in current name tree.
   * @param[in] new_name  String for a new key name. This should not be an empty string.
   *                      This new name should not have existed in current name tree.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Rename(const WString& old_name, const WString& new_name);
  /**
   * @brief Add a new key name with a PDF object as its value.
   *
   * @details All PDF objects in the name tree are ordered by their names. When a new PDF object is added,
   *          Foxit PDF SDK will find a suitable place in the name tree to add it. After adding successfully,
   *          the indexes of some old keys may be changed.
   *
   * @param[in] name        String for a new key name. This should not be an empty string.
   *                        This new name should not have existed in current name tree.
   * @param[in] pdf_object  A PDF object, to be set with the new name. The type of this PDF object should
   *                        match current name tree; otherwise, the input PDF object is invalid.
   *                        Please refer to comment of class @link PDFNameTree @endlink for more details.<br>
   *                        User should not release this PDF object after this function succeeds.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Add(const WString& name, objects::PDFObject* pdf_object);

  /**
   * @brief Remove a key name from current name tree, along with its value (as PDF object).
   *
   * @details If the input name does not exist in current name tree, this function will return <b>true</b> directly.
   *
   * @param[in] name  String for a key name to be removed. This should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveObj(const WString& name);

  /**
   * @brief Remove all key names from current name tree, along with theirs value (as PDF object).
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveAllObjs();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDFNameTree(FS_HANDLE handle);

};

}  // namespace objects
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PDFNAMETREE_H_

