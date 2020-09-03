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
 * @file fs_pdfassociatefiles.h
 * @brief Header file for associated file related definitions and classes.
 */

#ifndef FS_PDFASSOCIATE_H_
#define FS_PDFASSOCIATE_H_

#include "common/fs_common.h"
#include "pdf/annots/fs_annot.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
namespace pdf {
namespace graphics {
class ImageObject;
class FormXObject;
class GraphicsObject;
}  // namespace graphics

namespace objects {
class PDFObject;
}  // namespace objects
class PDFPage;
class FileSpec;

/**
 * In PDF 2.0, a new concept named "Associated files" is defined. Associated files provide a means to
 * associate content in other formats with objects of a PDF file and identify the relationship between
 * the content and the objects. Such associated files are designated using file specification
 * dictionaries (known as file specification). Associated files could be linked to the PDF document's catalog,
 * a page dictionary, graphics objects, structure elements, XObject, DParts, an annotation dictionary and so on.
 * Specially, associated files with graphics objects means to be associated with the marked content item.<br>
 * Class @link AssociatedFiles @endlink is the class for managing associate files. It offers the functions to
 * count/get associate files in PDF dictionary or graphics object, to associate files (represented by @link FileSpec @endlink)
 * with catalog, PDF pages, graphics objects, form XObject objects, annotation objects and so on.<br>
 * Specially, when construct an associated files object with a PDF document,
 * the file version of the related PDF document will be set to 2.0.
 */
class AssociatedFiles FS_FINAL : public Base {
 public:
   /**
    * @brief Enumeration for the relationship between PDF document and the associated file.
    *
    * @details Values of this enumeration should be used alone.
    */
   typedef enum _Relationship {
     /** @brief The relationship is not known or cannot be described by other values. */
     e_RelationshipUnspecified = 0,
     /**
    @brief The relationship is "Source" which means the file specification is the original source material
           for the associated content.
      */
     e_RelationshipSource = 1,
     /**
    @brief The relationship is "Data" which means the file specification represents information used to
           derive a visual presentation - such as for a table or a graph.
      */
     e_RelationshipData = 2,
     /**
    @brief The relationship is "Alternative" which means the file specification is
           an alternative representation of content, for example audio.
      */
     e_RelationshipAlternative = 3,
     /**
    @brief The relationship is "Supplement" which means the file specification represents
           a supplemental representation of the original source or data that may be more easily consumable.
      */
     e_RelationshipSupplement = 4,
     /**
    @brief The relationship is "Encrypted payload" which means the file specification is an encrypted payload document
           that should be displayed to the user if the PDF processor has the cryptographic filter needed to
           decrypt the document.
      */
     e_RelationshipEncryptedPayload = 5,
     /**
    @brief The relationship is "Form data" which means the file specification is the data
           associated with the "AcroForm" dictionary in the PDF file.
      */
     e_RelationshipFormData = 6,
     /**
    @brief The relationship is "Schema" which means the file specification is a schema definition
           for the associated object.
      */
     e_RelationshipSchema = 7
   } Relationship;
   

  /**
   * @brief Constructor, with another associated files object.
   *
   * @param[in] other  Another associated files object.
   */
   AssociatedFiles(const AssociatedFiles& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another associated files object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
   AssociatedFiles& operator = (const AssociatedFiles& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another associated files object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
   bool operator == (const AssociatedFiles& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another associated files object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
   bool operator != (const AssociatedFiles& other) const;

  /**
   * @brief Constructor, with a PDF document.
   *
   * @details When an associated files object is constructed by this constructor, the file version of input PDF document
   *          will be set to 2.0.
   *
   * @param[in] pdf_doc  A valid PDF document object.
   */
  explicit AssociatedFiles(const PDFDoc& pdf_doc);

  /** @brief Destructor. */
  ~AssociatedFiles();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the count of associated files in a PDF dictionary object which represents the dictionary of
   *        an annotation, a PDF page, or other object in PDF document.
   *
   * @param[in] pdf_object  A valid PDF object. It should be either a PDF dictionary object or a PDF reference object
   *                        that refers to a PDF dictionary object.
   *
   * @return The count of associated files.
   */
  int GetAssociatedFilesCount(objects::PDFObject* pdf_object);

  /**
   * @brief Get the count of associated files in a graphics object.
   *
   * @details One or more files may be associated with sections of content in a content stream by enclosing those
   *          sections between the marked content. So, in fact, this function is to count associated files
   *          in the marked content related to the graphics object.
   *
   * @param[in] graphics_object  A valid PDF graphics object.
   *
   * @return The count of associated files.
   */
  int GetAssociatedFilesCount(foxit::pdf::graphics::GraphicsObject* graphics_object);

  /**
   * @brief Get an associated file (represented by @link FileSpec @endlink) in a specified PDF dictionary object, by index.
   *
   * @param[in] pdf_object  A valid PDF object. It should be either a PDF dictionary object or a PDF reference object
   *                        that refers to a PDF dictionary object.
   * @param[in] index       The index of an associated file in the specified PDF dictionary object.
   *                        Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                        @link AssociatedFiles::GetAssociatedFilesCount @endlink with same parameter <i>object</i>.
   *
   * @return A file specification object that represents the expected associated file.
   */
  FileSpec GetAssociatedFile(objects::PDFObject* pdf_object, int index);

  /**
   * @brief Get an associated file a graphics object, by index.
   *
   * @details One or more files may be associated with sections of content in a content stream by enclosing those
   *          sections between the marked content. So, in fact, this function is to get an associated files (specified by index)
   *          in the marked content related to the graphics object.
   *
   * @param[in] graphics_object  A valid PDF graphics object.
   * @param[in] index            The index of an associated file in the specified PDF graphics object.
   *                             Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                             @link AssociatedFiles::GetAssociatedFilesCount @endlink with
   *                             same parameter <i>graphics_object</i>.
   *
   * @return A file specification object that represents the expected associated file.
   */
  FileSpec GetAssociatedFile(foxit::pdf::graphics::GraphicsObject* graphics_object, int index);

  /**
   * @brief Associate a file (represented by @link FileSpec @endlink) with a PDF dictionary object which represents the dictionary of
   *        an annotation, a PDF page, or other object in PDF document.
   *
   * @param[in] pdf_object  A valid PDF object. It should be either a PDF dictionary object or a PDF reference object
   *                        that refers to a PDF dictionary object.
   * @param[in] file_spec   A file specification object to be associated with specified PDF dictionary.
   *                        It should not be an empty string.
   *
   * @return None.
   */
  void AssociateFile(objects::PDFObject* pdf_object, const FileSpec& file_spec);

  /**
   * @brief Associate a file (represented by @link FileSpec @endlink) with a marked content item of a specified graphics object.
   *
   * @param[in] graphics_object          A valid graphics object.
   * @param[in] mark_content_item_index  The index of marked content item in input graphic object to which
   *                                     the specified file specification object is to associated with. Valid range:
   *                                     from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                                     @link graphics::MarkedContent::GetItemCount @endlink of the marked content
   *                                     related to input graphics object.
   * @param[in] current_resource         A resource dictionary of a PDF page to which input graphics object is
   *                                     related. This can also be a PDF reference object that refers to
   *                                     such a PDF dictionary.
   * @param[in] property_name            A property name used in "Properties" dictionary of input resource dictionary.
   *                                     It should not be an empty string.
   * @param[in] file_spec                A file specification object to be associated with specified marked content item of
   *                                     a specified graphics object. It should not be an empty string.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void AssociateFile(foxit::pdf::graphics::GraphicsObject* graphics_object, int mark_content_item_index,
                     foxit::pdf::objects::PDFObject* current_resource, const char* property_name, const foxit::pdf::FileSpec& file_spec);

  /**
   * @brief Associate a file (represented by @link FileSpec @endlink) with a PDF page.
   *
   * @details In fact, this function is equals to associate a file with a PDF page dictionary.
   *
   * @param[in] page       A valid PDF page.
   * @param[in] file_spec  A file specification object to be associated with specified PDF page.
   *                       It should not be an empty string.
   *
   * @return None.
   */
  void AssociateFile(const foxit::pdf::PDFPage& page, const foxit::pdf::FileSpec& file_spec);

  /**
   * @brief Associate a file (represented by @link FileSpec @endlink) with an image graphics object.
   *
   * @details In fact, this function is equals to associate a file with a PDF dictionary of an image graphics object.
   *
   * @param[in] image      An image graphics object. It should not be <b>NULL</b>.
   * @param[in] file_spec  A file specification object to be associated with specified image graphics object.
   *                       It should not be an empty string.
   *
   * @return None.
   */
  void AssociateFile(foxit::pdf::graphics::ImageObject* image, const foxit::pdf::FileSpec& file_spec);

  /**
   * @brief Associate a file (represented by @link FileSpec @endlink) with a form XObject graphics object.
   *
   * @details In fact, this function is equals to associate a file with a PDF dictionary of
   *          a form XObject graphics object.
   *
   * @param[in] form_xobject  A form XObject graphics object. It should not be <b>NULL</b>.
   * @param[in] file_spec     A file specification object to be associated with specified form XObject graphics object.
   *                          It should not be an empty string.
   *
   * @return None.
   */
  void AssociateFile(foxit::pdf::graphics::FormXObject* form_xobject, const foxit::pdf::FileSpec& file_spec);

  /**
   * @brief Associate a file (represented by @link FileSpec @endlink) with a PDF annotation.
   *
   * @details In fact, this function is equals to associate a file with a PDF dictionary of a PDF annotation.
   *
   * @param[in] annot      A valid PDF annotation.
   * @param[in] file_spec  A file specification object to be associated with specified PDF annotation object.
   *                       It should not be an empty string.
   *
   * @return None.
   */
  void AssociateFile(const foxit::pdf::annots::Annot& annot, const foxit::pdf::FileSpec& file_spec);

  /**
   * @brief Remove an associated file (represented by @link FileSpec @endlink) in a specified PDF dictionary object, by index.
   *
   * @param[in] pdf_object  A valid PDF object. It should be either a PDF dictionary object or a PDF reference object
   *                        that refers to a PDF dictionary object.
   * @param[in] index       The index of an associated file in the specified PDF dictionary object.
   *                        Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                        @link AssociatedFiles::GetAssociatedFilesCount @endlink with same parameter <i>object</i>.
   *
   * @return None.
   */
  void RemoveAssociatedFile(objects::PDFObject* pdf_object, int index);

  /**
   * @brief Remove an associated file a graphics object, by index.
   *
   * @details One or more files may be associated with sections of content in a content stream by enclosing those
   *          sections between the marked content. So, in fact, this function is to count associated files
   *          in the marked content related to the graphics object.
   *
   * @param[in] graphics_object  A valid PDF graphics object.
   * @param[in] index            The index of an associated file in the specified PDF graphics object.
   *                             Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                             @link AssociatedFiles::GetAssociatedFilesCount @endlink with
   *                             same parameter <i>graphics_object</i>.
   *
   * @return A file specification object that represents the expected associated file.
   */
  void RemoveAssociatedFile(foxit::pdf::graphics::GraphicsObject* graphics_object, int index);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit AssociatedFiles(FS_HANDLE handle =  NULL);
};
}  // namespace pdf
}  // namespace foxit

#endif

