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
 * @file fs_pdfattachments.h
 * @brief Header file for PDF attachments related definitions and classes.
 */

#ifndef FS_PDFATTACHMENTS_H_
#define FS_PDFATTACHMENTS_H_

#include "common/fs_common.h"
#include "pdf/fs_filespec.h"
#include "pdf/objects/fs_pdfnametree.h"

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
 * In application, document's embedded files are known as PDF attachments. This class offers a more convenient way,
 * than class @link objects::PDFNameTree @endlink, to get/set embedded files (also known as attachment files)
 * in EmbeddedFiles name tree of a PDF document.
 *
 * @see @link PDFDoc @endlink
 * @see @link objects::PDFNameTree @endlink
 */
class Attachments FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, with parameters. from a PDF document object and an EmbeddedFiles name tree (if any).
   *
   * @details <ul>
   *          <li>If no name tree object is specified, this function will construct the attachments object from
   *              PDF document:
   *              if there exists EmbeddedFiles name tree in the PDF document, this function is just to construct
   *              an attachments object to be associated with the name tree; If there is no such name tree in
   *              PDF document, the constructed attachments object can be used to create such name tree
   *              in PDF document and add some embedded files to the name tree.</li>
   *          <li>If an EmbeddedFiles name tree is specified, this function will construct the attachments object from
   *              the name tree, along with the related PDF document.</li>
   *          </ul>
   *
   * @param[in] doc       A valid PDF document object.
   * @param[in] nametree  A PDF name tree object that represents an EmbeddedFiles name tree.
   *                      If this PDF name tree object is constructed by default constructor and
   *                      has not been set any value, that means the attachments object will be constructed from
   *                      PDF document; otherwise, please ensure it belongs to the PDF document
   *                      specified by parameter <i>doc</i>.
   *                      Default value: a PDF name tree object by default constructor and not set any value.
   */
  explicit Attachments(const PDFDoc& doc, const objects::PDFNameTree& nametree = foxit::pdf::objects::PDFNameTree());
   /** @brief Destructor. */
  ~Attachments();
  /**
   * @brief Constructor, with another attachments object.
   *
   * @param[in] other  Another attachments object.
   */
  Attachments(const Attachments& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another attachments object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Attachments& operator = (const Attachments& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another attachments object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Attachments& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another attachments object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Attachments& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the count of attachments.
   *
   * @return The count of attachments.
   */
  int GetCount();

  /**
   * @brief Get the key of an attachment defined in the EmbeddedFiles name tree, by index.
   *
   * @param[in] index  Index of the key string to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Attachments::GetCount @endlink.
   *
   * @return A key string.
   */
  WString GetKey(int index);

  /**
   * @brief Get the attachment (as file specification object) of a specified key.
    *
   * @param[in] key  Key string. It should not be an empty string.
   *
   * @return A file specification object.
   */
  FileSpec GetEmbeddedFile(const WString& key);

  /**
   * @brief Set an embedded attachment (as file specification object) for a specified key.
   *
   * @param[in] key        Key string. It should not be an empty string.
   *                       This name should have existed in current PDF document.
   * @param[in] file_spec  A file specification object to be set to the key's value. It should be valid and
   *                       should has been embedded to the same PDF document as current attachments object.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetEmbeddedFile(const WString& key, const FileSpec& file_spec);

  /**
   * @brief Add an embedded attachment (as file specification object) with new key name.
   *
   * @details All attachments in EmbeddedFiles name tree are ordered by their keys.
   *          When a new attachment is added, Foxit PDF SDK will find a suitable place in the name tree to add it.
   *          After adding successfully, the indexes of some old keys may be changed.
   *
   * @param[in] key        New key string. If this is an empty string, the name of input <i>file_spec</i> will be
   *                       used as the new key. This new key should not have existed in the PDF document to which
   *                       current attachments object belongs.
   * @param[in] file_spec  A file specification object to be added with new key. It should be valid and
   *                       should has been embedded to the same PDF document as current attachments object.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool AddEmbeddedFile(const WString& key, const FileSpec& file_spec);

  /**
   * @brief Add a new attachment from specified file path with new key name.
   *
   * @details All attachments in EmbeddedFiles name tree are ordered by their keys.
   *          When a new attachment is added, Foxit PDF SDK will find a suitable place in the name tree to add it.
   *          After adding successfully, the indexes of some old keys may be changed.
   *
   * @param[in] key        New key string. If this is an empty string, the name of input <i>file_spec</i> will be
   *                       used as the new key. This new key should not have existed in the PDF document to which
   *                       current attachments object belongs.
   * @param[in] file_path  A file path to specify a file to be embedded to the PDF document and
   *                       also added to EmbeddedFiles name tree.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool AddFromFilePath(const WString& key, const wchar_t* file_path);

  /**
   * @brief Remove an attachment by key.
   *
   * @details If the input key does not exist in EmbeddedFiles name tree,
   *          this function will return <b>true</b> directly.
   *
   * @param[in] key  Key string. This should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveEmbeddedFile(const WString& key);

  /**
   * @brief Remove all attachments.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveAllEmbeddedFiles();

  /**
   * @brief Extract an attachment and save it to a specified file path.
   *
   * @param[in] key            Key string. This should not be an empty string.
   * @param[in] dst_file_path  A file path, to which the data of attachment will be saved.
   *                           This should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ExtractEmbeddedFileTo(const WString& key, const wchar_t* dst_file_path);

  /**
   * @brief Get the EmbeddedFiles name tree.
   *
   * @return The EmbeddedFiles name tree.
   */
  objects::PDFNameTree GetNameTree() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Attachments(FS_HANDLE handle =  NULL);
};
}  // namespace pdf
}  // namespace foxit

#endif  // FS_PDFATTACHMENTS_H_

