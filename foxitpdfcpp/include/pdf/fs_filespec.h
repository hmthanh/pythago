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
 * @file fs_filespec.h
 * @brief Header file for file specification related definitions and classes.
 */

#ifndef FS_FILESPEC_H_
#define FS_FILESPEC_H_

#include "common/fs_common.h"
#include "common/file/fs_file.h"
#include "pdf/fs_pdfassociatefiles.h"
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
class PDFDoc;
/**
 * A PDF file can refer to the contents of another file by using a file specification.
 * File specification can simply represents the file path of another file, or represents the whole content of
 * another file, which is embedded to current PDF file.
 */
class FileSpec FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor.
   *
   * @details This constructor is to construct a new file specification object (without any data).
   *
   * @param[in] document  A valid PDF document object, to which the new file specification object will belongs.
   */
  explicit FileSpec(const PDFDoc& document);

  /**
   * @brief Constructor, from an existing file specification PDF object in a PDF document.
   *
   * @param[in] document    A valid PDF document object, to which the file specification PDF object belongs.
   * @param[in] pdf_object  A valid PDF object which represents an existing file specification object in the PDF document.
   *                        It should be either a dictionary object or a PDF reference object:
   *                        <ul>
   *                        <li>If it is a PDF dictionary object, it should be a file specification dictionary.</li>
   *                        <li>If it is a PDF reference object, it should refer to a file specification dictionary.</li>
   *                        </ul>
   *                        This PDF object can be retrieved from @link objects::PDFNameTree @endlink in type
   *                        @link objects::PDFNameTree::e_EmbeddedFiles @endlink.
   */
  explicit FileSpec(const PDFDoc& document, objects::PDFObject* pdf_object);

  /**
   * @brief Constructor, with another file specification object.
   *
   * @param[in] other  Another file specification object.
   */
  FileSpec(const FileSpec& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another file specification object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  FileSpec& operator = (const FileSpec& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another file specification object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const FileSpec& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another file specification object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const FileSpec& other) const;

  /** @brief Destructor. */
  ~FileSpec();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the file name.
   *
   * @return The file name. If no file name can be found, this function will return an empty string.
   */
  WString GetFileName() const;

  /**
   * @brief Set the file name.
   *
   * @details This function is required for a new file specification object (not constructed from
   *          an existing file specification PDF object).
   *
   * @param[in] file_name  The file name to be set. It should not be an empty string.
   *
   * @return None.
   */
  void SetFileName(const wchar_t* file_name);

  /**
   * @brief (Only supported in PDF 2.0) Get the associated file relationship when current file specification is
   *        used as an associated file.
   *
   * @return The associated file relationship. Please refer to values starting from
   *         @link AssociatedFiles::e_RelationshipSource @endlink and this should be one of these values.
   */
  AssociatedFiles::Relationship GetAssociteFileRelationship() const;

  /**
   * @brief (Only supported in PDF 2.0) Set the associated file relationship when current file specification is
   *        used as an associated file.
   *
   * @details This function is required for a newly created associated file specification object.
   *
   * @param[in] associfile_relationship  The associated file relationship to be set. Please refer to values starting from
   *                                     @link AssociatedFiles::e_RelationshipSource @endlink and this would be one of these values.
   *
   * @return None.
   */
  void SetAssociteFileRelationship(AssociatedFiles::Relationship associfile_relationship);

  /**
   * @brief Get the size of embedded file.
   *
   * @details This function is only useful when current file specification object represents an embedded file.
   *          If current file specification object does not represent an embedded file, this function will
   *          return 0 directly.
   *
   * @return File size of embedded file.
   */
  int64 GetFileSize() const;

  /**
   * @brief Get the file data of embedded file.
   *
   * @return A @link common::file::ReaderCallback @endlink object. User can call functions in class @link common::file::ReaderCallback @endlink to read the file data.
   */
  common::file::ReaderCallback* GetFileData() const;

  /**
   * @brief Embed the whole content of a file which is specified by file path.
   *
   * @details When this function succeeds, the whole content of specified file will be embedded to
   *          the PDF document that current file specification belongs to.
   *
   * @param[in] file_path  A full path of an existing local file.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Embed(const wchar_t* file_path);
  /**
   * @brief (Only support in PDF 2.0) Embed the whole content of a PDF stream object or
   *        a PDF reference object which refers to a PDF stream object,
   *        when current file specification object is used as an associated file.
   *
   * @details When this function succeeds, the whole content of specified PDF stream object will be embedded to
   *          the PDF document that current file specification belongs to.
   *
   * @param[in] pdf_object  A valid PDF object. It should be either a PDF stream object or a PDF reference object
   *                        which refers to a PDF stream object.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Embed(foxit::pdf::objects::PDFObject* pdf_object);

  /**
   * @brief Embed a file by using @link foxit::common::file::StreamCallback @endlink.
   *
   * @details When this function succeeds, please keep input stream callback object valid
   *          until the PDF file (which current file specification belongs to) is saved or closed.
   *
   * @param[in] stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user
   *                    to read the file content.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Embed(foxit::common::file::StreamCallback* stream);

  /**
   * @brief Check whether current file specification object represents an embedded file or not.
   *
   * @return <b>true</b> means current file specification object represent an embedded file.
   *         <b>false</b> means current file specification object does not represent an embedded file.
   */
  bool IsEmbedded() const;
  /**
   * @brief Get the descriptive text associated with current file specification.
   *
   * @return The descriptive text.
   */
  String GetDescription() const;
  /**
   * @brief Set the descriptive text associated with current file specification.
   *
   * @param[in] description  A descriptive text to be set. It should not be an empty string.
   *
   * @return None.
   */
  void SetDescription(const String& description);
  /**
   * @brief Get creation date and time about when the embedded file was created.
   *
   * @details This function is only useful when current file specification object represents an embedded file.
   *          If current file specification object does not represent an embedded file, this function will
   *          return a date and time object will all value 0.
   *
   * @return The creation date time of embedded file.
   */
  DateTime GetCreationDateTime() const;
  /**
   * @brief Set the creation date and time for the embedded file. (Not affect local file)
   *
   * @details This function is only useful when current file specification object represents an embedded file.
   *
   * @param[in] date_time  The creation date and time to be set.
   *
   * @return None.
   */
  void SetCreationDateTime(const DateTime& date_time);
  /**
   * @brief Get modified date and time about when the embedded file was last modified.
   *
   * @details This function is only useful when current file specification object represents an embedded file.
   *          If current file specification object does not represent an embedded file, this function will
   *          return a date and time object will all value 0.
   *
   * @return The modified date time of embedded file.
   */
  DateTime GetModifiedDateTime() const;
  /**
   * @brief Set last modified date and time for the embedded file. (Not affect local file)
   *
   * @details This function is only useful when current file specification object represents an embedded file.
   *
   * @param[in] date_time  The last modified date and time to be set.
   *
   * @return None.
   */
  void SetModifiedDateTime(const DateTime& date_time);
  /**
   * @brief Get the checksum for embedded file.
   *
   * @details This function is only useful when current file specification object represents an embedded file.
   *          A 16-byte string that is the checksum of the bytes of the uncompressed embedded file.
   *          The checksum is calculated by applying the standard MD5 message-digest algorithm
   *          to the bytes of the embedded file stream.<br>
   *          If current file specification object does not represent an embedded file, this function will
   *          return an empty string.
   *
   * @return The checksum string.
   */
  String GetChecksum() const;
  /**
   * @brief Set the checksum for embedded file. (Not affect local file)
   *
   * @details This function is only useful if current file specification object represents an embedded file.<br>
   *          A 16-byte string that is the checksum of the bytes of the uncompressed embedded file.
   *          The checksum is calculated by applying the standard MD5 message-digest algorithm
   *          to the bytes of the embedded file stream.
   *
   * @param[in] checksum  A checksum to be set.
   *
   * @return None.
   */
  void SetChecksum(const String& checksum);

  /**
   * @brief (Only support in PDF 2.0) Get the MIME type value for "Subtype" key for embedded file
   *        when current file specification is used as an associated file.
   *
   * @details This function is only useful when current file specification object represents an embedded file and
   *          used as associated file.
   *
   * @return The subtype string.
   */
  String GetSubtype() const;

  /**
   * @brief (Only support in PDF 2.0) Set the MIME type value for "Subtype" key for embedded file
   *        (Not affect local file) when current file specification is used as an associated file.
   *
   * @details This function is only useful when current file specification object represents an embedded file and
   *          used as associated file.
   *
   * @param[in] subtype  A valid MIME type value. Default value: "application/octet-stream".
   *
   * @return None.
   */
  void SetSubtype(const String& subtype = "application/octet-stream");

  /**
   * @brief Get the PDF dictionary of current file specification.
   *
   * @return A PDF dictionary object.
   */
  objects::PDFDictionary* GetDict() const;

  /**
   * @brief Export the file data that represented in current file specification directly into a file.
   *
   * @param[in] path  A full path of a file to which the data will be saved.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ExportToFile(const wchar_t* path)  const;

  /**
   * @brief Export the file data that represented in current file specification through a stream callback object.
   *
   * @param[in] stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user to save the file data.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ExportToFileStream(foxit::common::file::StreamCallback* stream)  const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit FileSpec(FS_HANDLE handle =  NULL);
};
}  // namespace pdf
}  // namespace foxit
#endif  // namespace foxit

