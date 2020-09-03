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
 * @file fs_fdfdoc.h
 * @brief Header file for FDF doucument related definitions and classes.
 */

#ifndef FS_FDFDOC_H_
#define FS_FDFDOC_H_

#include "common/fs_common.h"
#include "common/file/fs_file.h"
#include "pdf/annots/fs_annot.h"
#include "pdf/objects/fs_pdfobject.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/**
 * @brief FDF namespace.
 */
namespace fdf {
/**
 * FDF (Forms Data Format) is a kind of file format, used for interactive form data. FDF can be used
 * when submitting form data to a server, receiving the response, and incorporating it into the interactive form.
 * It can also be used to export form data to stand-alone files that can be stored, transmitted electronically,
 * and imported back into the corresponding PDF interactive form. Besides these, FDF can be used to
 * define a container for annotations that are separated from the PDF document to which they apply.<br>
 * XFDF(XML Forms Data Format) is a version of FDF based on XML. It has similar features with FDF.<br>
 * In a word, FDF and XFDF contain the subset of a PDF document to describe interactive forms and annotations.<br>
 * Class @link FDFDoc @endlink can be used to represent either FDF or XFDF. A FDF document object can be constructed with
 * an existing file from file path, memory buffer, a custom implemented @link common::file::ReaderCallback @endlink object and
 * an input file stream. A FDF document object can also be constructed as a new FDF or XFDF document.
 * This class also offers functions to get or set some information from FDF or XFDF file,
 * and save current FDF/XFDF as another file.<br>
 * To import or export form fields or annotations, please refer to functions @link pdf::PDFDoc::ImportFromFDF @endlink,
 * @link pdf::PDFDoc::ExportToFDF @endlink and @link pdf::PDFDoc::ExportAnnotToFDF @endlink.
 *
 * @see @link pdf::PDFDoc @endlink
 */
class FDFDoc FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for FDF document type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Type {
    /** @brief FDF document type: FDF. */
    e_FDF  =  0,
    /** @brief FDF document type: XFDF. */
    e_XFDF  =  1
  } Type;
  
  
  /**
   * @brief Constructor, with a file read callback object.
   *
   * @param[in] file_read  Pointer to a @link common::file::ReaderCallback @endlink object which is implemented by user to
   *                       load a FDF or XFDF document. It should not be <b>NULL</b>.
   */
  explicit FDFDoc(common::file::ReaderCallback* file_read);

  /**
   * @brief Constructor.
   *
   * @details This constructor is to construct a new FDF document object (without any data).
   *
   * @param[in] type  FDF document type. It should be one of following values: <br>
   *                  @link fdf::FDFDoc::e_FDF @endlink, @link FDFDoc::e_XFDF @endlink
   */
  explicit FDFDoc(Type type);

  /**
   * @brief Constructor, from an existing FDF or XFDF file path.
   *
   * @param[in] path  A full path of an existing FDF/XFDF file. It should not be an empty string.
   */
  explicit FDFDoc(const char* path);

  /**
   * @brief Constructor, from an existing FDF or XFDF file path.
   *
   * @param[in] path  A full path of an existing FDF/XFDF file. It should not be an empty string.
   */
  explicit FDFDoc(const wchar_t* path);

  /**
   * @brief Constructor, from a memory buffer.
   *
   * @param[in] buffer  A memory buffer. The FDF or XFDF file data should be fully loaded in this memory buffer.
   *                    It should not be <b>NULL</b>.
   * @param[in] length  The size of memory buffer. It should be above 0.
   */
  FDFDoc(const void* buffer, size_t length);

  /**
   * @brief Constructor, with another FDF document object.
   *
   * @param[in] other  Another FDF document object.
   */
  FDFDoc(const FDFDoc& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another FDF document object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  FDFDoc& operator = (const FDFDoc& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another FDF document object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const FDFDoc& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another FDF document object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const FDFDoc& other) const;

  /** @brief Destructor. */
  ~FDFDoc();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the type of current document object.
   *
   * @return FDF document type. It would be one of following values: <br>
   *         @link fdf::FDFDoc::e_FDF @endlink, @link FDFDoc::e_XFDF @endlink.
   */
  Type GetType() const;

  /**
   * @brief Get the path of related PDF document
   *
   * @details The path can be either an absolute one, or a relative one.
   *
   * @return File path of related PDF document. Empty string means no such information is found.
   */
  WString GetPDFPath();

  /**
   * @brief Set the path of related PDF document.
   *
   * @param[in] pdf_path  The path of related PDF document. It can be either an absolute path or a relative path.
   *                      It should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetPDFPath(const wchar_t* pdf_path);

  /**
   * @brief Save current document as another FDF or XFDF file.
   *
   * @param[in] file_path  A full path of the new saved FDF or XFDF file. It should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note This function does not support to save current FDF object just back to the FDF or XFDF file which is used to
   *       construct current FDF object. In order to do so, user is recommended to do as following steps:<br>
   *       Assume that current FDF object is constructed from a FDF file named "org.fdf".
   *       <ol>
   *       <li>Use current function to save current FDF object to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that current FDF object has destructed.</li>
   *       <li>Remove "org.fdf" and rename "temp.tmp" to "org.fdf".</li>
   *       </ol>
   */
  bool SaveAs(const char* file_path);

  /**
   * @brief Save current document as another FDF or XFDF file.
   *
   * @param[in] file_path  A full path of the new saved FDF or XFDF file. It should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note This function does not support to save current FDF object just back to the FDF or XFDF file which is used to
   *       construct current FDF object. In order to do so, user is recommended to do as following steps:<br>
   *       Assume that current FDF object is constructed from a FDF file named "org.fdf".
   *       <ol>
   *       <li>Use current function to save current FDF object to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that current FDF object has destructed.</li>
   *       <li>Remove "org.fdf" and rename "temp.tmp" to "org.fdf".</li>
   *       </ol>
   */
  bool SaveAs(const wchar_t* file_path);

  /**
   * @brief Save current document as another FDF or XFDF file.
   *
   * @param[in] file  A @link common::file::WriterCallback @endlink object which is implemented by user to save FDF or XFDF file.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note This function does not support to save current FDF object just back to the FDF or XFDF file which is used to
   *       construct current FDF object. In order to do so, user is recommended to do as following steps:<br>
   *       Assume that current FDF object is constructed from a FDF file named "org.fdf".
   *       <ol>
   *       <li>Use current function to save current FDF object to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that current FDF object has destructed.</li>
   *       <li>Remove "org.fdf" and rename "temp.tmp" to "org.fdf".</li>
   *       </ol>
   */
  bool SaveAs(foxit::common::file::WriterCallback* file);

  /**
   * @brief Get the catalog dictionary.
   *
   * @note If current object represents an XFDF document, this function will return <b>NULL</b>.
   *
   * @return The catalog dictionary.
   */
  pdf::objects::PDFDictionary* GetCatalog() const;

  /**
   * @brief Get the dictionary of "FDF" entry from catalog dictionary.
   *
   * @note If current object represents an XFDF document, this function will return <b>NULL</b>.
   *
   * @return The dictionary of "FDF" entry from catalog dictionary.
   */
  pdf::objects::PDFDictionary* GetFDFDict() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit FDFDoc(FS_HANDLE handle =  NULL);
};
}  // namespace fdf
}  // namespace foxit
#endif  // FS_FDFDOC_H_

