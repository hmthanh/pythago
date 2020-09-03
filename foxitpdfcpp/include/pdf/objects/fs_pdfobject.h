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
 * @file fs_pdfobject.h
 * @brief Header file for PDF object related definitions and classes.
 */

#ifndef FS_PDFOBJECT_H_
#define FS_PDFOBJECT_H_

#include "common/fs_common.h"
#include "common/file/fs_file.h"

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
class PDFArray;
class PDFDictionary;
class PDFStream;

/**
 * PDF supports eight basic types of objects: <br>
 * "Boolean value", "Integer and real number", "String", "Name",
 * "Array", "Dictionary", "Stream", "The null object". For more details about PDF objects,
 * please refer to Section 3.2 "Objects" in <PDF Reference 1.7>.<br>
 * Class @link PDFObject @endlink is a base class for all kinds of PDF objects. It offers different functions to
 * create different kind of PDF objects. For "Array", "Dictionary" and "Stream" PDF object, please refer to
 * derived classes @link objects::PDFArray @endlink, @link objects::PDFDictionary @endlink and @link PDFStream @endlink.<br>
 * If user wants to make a newly created PDF object to be an indirect object, please call function
 * @link pdf::PDFDoc::AddIndirectObject @endlink.
 *
 * @see @link PDFArray @endlink
 * @see @link PDFDictionary @endlink
 * @see @link PDFStream @endlink
 * @see @link pdf::PDFDoc @endlink
 */
class PDFObject : public Object {
 public:
  /**
   * @brief Enumeration for PDF object type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Type {
    /** @brief Invalid PDF object type. */
    e_InvalidType = 0,
    /** @brief PDF boolean object. */
    e_Boolean = 1,
    /** @brief PDF number object. */
    e_Number = 2,
    /** @brief PDF string object. */
    e_String = 3,
    /** @brief PDF name object. */
    e_Name = 4,
    /** @brief PDF array object. */
    e_Array = 5,
    /** @brief PDF dictionary object. */
    e_Dictionary = 6,
    /** @brief PDF stream object. */
    e_Stream = 7,
    /** @brief PDF null object. */
    e_Null = 8,
    /** @brief PDF reference object. */
    e_Reference = 9
  } Type;
  
  /**
   * @brief Create a PDF object from a boolean value.
   *
   * @param[in] boolean_value  A boolean value.
   *
   * @return A new @link PDFObject @endlink object, whose object type is @link PDFObject::e_Boolean @endlink.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFObject* CreateFromBoolean(bool boolean_value);

  /**
   * @brief Create a PDF object from a float number.
   *
   * @param[in] float_value  A float value.
   *
   * @return A new @link PDFObject @endlink object, whose object type is @link PDFObject::e_Number @endlink.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFObject* CreateFromFloat(float float_value);

  /**
   * @brief Create a PDF object from a integer number.
   *
   * @param[in] integer_value  An integer value.
   *
   * @return A new @link PDFObject @endlink object, whose object type is @link PDFObject::e_Number @endlink.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFObject* CreateFromInteger(int integer_value);

  /**
   * @brief Create a PDF object from string.
   *
   * @param[in] string_value  A string. It should not be an empty string.
   *
   * @return A @link PDFObject @endlink object, whose object type is @link PDFObject::e_String @endlink.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFObject* CreateFromString(const wchar_t* string_value);

  /**
   * @brief Create a PDF object from a string which represents a name.
   *
   * @param[in] name  A string. It should not be an empty string.
   *
   * @return A new @link PDFObject @endlink object, whose object type is @link PDFObject::e_Name @endlink.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFObject* CreateFromName(const char* name);

  /**
   * @brief Create a PDF object from date time.
   *
   * @details PDF defines a standard date format, which closely follows that of the
   *          international standard ASN.1 (Abstract Syntax Notation One), defined in ISO/
   *          IEC 8824 (see the Bibliography). A date is defined as an ASCII string of the form
   *          (D:YYYYMMDDHHmmSSOHH'mm').
   *
   * @param[in] date_time  A date and time object.
   *
   * @return A new @link PDFObject @endlink object, whose object type is @link PDFObject::e_String @endlink.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFObject* CreateFromDateTime(const DateTime& date_time);

  /**
   * @brief Create a reference for an indirect object.
   *
   * @details The indirect object can be retrieved by following methods:
   *          <ul>
   *          <li>Returned by function @link pdf::PDFDoc::GetIndirectObject @endlink.</li>
   *          <li>Returned by function @link pdf::PDFDoc::AddIndirectObject @endlink, when try to add a direct PDF object
   *              to PDF document and make it to be an indirect object.</li>
   *          </ul>
   *
   * @param[in] document       A valid PDF document object.
   * @param[in] object_number  The indirect object number of the indirect PDF object. This should be above 0.
   *
   * @return A new @link PDFObject @endlink object, whose object type is @link PDFObject::e_Reference @endlink.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFObject* CreateReference(PDFDoc document, uint32 object_number);

#if !defined(_SWIG_IOS_) && !defined(_SWIG_MACOC_)
  /**
   * @brief Release a newly created PDF object or a clone PDF object,
   *        which is not related to PDF document or other PDF object and will not be used any more.
   *
   * @details This function should be called only for a newly created PDF object or a cloned PDF object,
   *          which has not been added or set to other PDF object or related to PDF document,
   *          and will not be used any more. Please do not use this function for other case,
   *          otherwise unknown error may occur.
   *
   * @return None.
   */
  void Release();
#endif

  /**
   * @brief Clone current PDF object and get the cloned PDF object.
   *
   * @return A new @link PDFObject @endlink object as the clone result.
   *         Please call @link PDFObject::Release @endlink to release the new object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  PDFObject* CloneObject() const;

  /**
   * @brief Get the type of current PDF object.
   *
   * @return PDF object type. Please refer to values starting from @link PDFObject::e_Boolean @endlink and
   *         this would be one of these values.
   */
  Type GetType() const;

  /**
   * @brief Get the indirect object number of current PDF object.
   *
   * @return The indirect object number. It would be:
   *         <ul>
   *         <li>0 if current PDF object is a direct object.</li>
   *         <li>above 0 if current PDF object is an indirect object.</li>
   *         <li>-1 means there is any error.</li>
   *         </ul>
   */
  uint32 GetObjNum() const;

  /**
   * @brief Get the integer value of current PDF object.
   *
   * @details Only useful when the type of current PDF object is @link PDFObject::e_Number @endlink.
   *
   * @return The integer value. For PDF object in other type, 0 will be returned.
   */
  int GetInteger() const;

  /**
   * @brief Get the float value of current PDF object.
   *
   * @details Only useful when the type of current PDF object is @link PDFObject::e_Number @endlink.
   *
   * @return The float value. For PDF object in other type, 0.0f will be returned.
   */
  float GetFloat() const;

  /**
   * @brief Get the boolean value of current PDF object.
   *
   * @details Only useful when the type of current PDF object is @link PDFObject::e_Boolean @endlink.
   *
   * @return The boolean value. For PDF object in other type, <b>false</b> will be returned.
   */
  bool GetBoolean() const;

  /**
   * @brief Get the matrix value of current PDF object.
   *
   * @details Only useful for PDF object whose type is @link PDFObject::e_Array @endlink and
   *          it has 6 number objects as elements.
   *
   * @return A matrix. If there is any error or current object is in other type,
   *         a matrix with value [0 0 0 0 0 0] will be returned.
   */
  Matrix GetMatrix() const;

  /**
   * @brief Get the rectangle value of current PDF object.
   *
   * @details Only useful for PDF object whose type is @link PDFObject::e_Array @endlink and
   *          it has 4 number objects as elements.
   *
   * @return A rectangle. If there is any error or current object is in other type,
   *         a rectangle with value [0 0 0 0] will be returned.
   */
  RectF GetRect() const;

  /**
   * @brief Get the direct object of current PDF object.
   *
   * @details If the type of current PDF object is @link PDFObject::e_Reference @endlink,
   *          the direct object will be returned.
   *
   * @return The direct PDF object. For PDF object in other type, this function will return current PDF object itself.
   */
  PDFObject* GetDirectObject() const;

  /**
   * @brief Get the date time value of current PDF object.
   *
   * @details Only useful when the type of current PDF objec is @link PDFObject::e_String @endlink
   *          and its content is in PDF standard date format.
   *
   * @return The data time information. If there is any error or current object is in other type,
   *         an empty date and time object will be returned.
   */
  DateTime GetDateTime() const;

  /**
   * @brief Get the name value of current PDF object.
   *
   * @details Only useful when the type of current PDF object is
   *          @link PDFObject::e_Name @endlink or @link PDFObject::e_String @endlink.
   *
   * @return A string that represents the value. If there is any error or current object is in other type,
   *         an empty string will be returned.
   */
  String GetName() const;

  /**
   * @brief Get the string value of current PDF object.
   *
   * @details This function will get the string format for actual value of current PDF object:
   *          <ul>
   *          <li>If object type is @link PDFObject::e_Boolean @endlink,
   *              "true" or "false" string value will be returned, depending on its actual value.</li>
   *          <li>If object type is @link PDFObject::e_Number @endlink,
   *              the value will be represents as a string. For example, "1.5" string is for value 1.5.</li>
   *          <li>If object type is @link PDFObject::e_String @endlink, the string value will
   *              be retrieved directly.</li>
   *          </ul>
   *          If value of current PDF object cannot be converted to a valid string, an empty string will be returned.
   *
   * @return A string.
   */
  String GetString() const;

  /**
   * @brief Get the wide string value of current PDF object.
   *
   * @details This function will get the string format for actual value of current PDF object:
   *          <ul>
   *          <li>If object type is @link PDFObject::e_Boolean @endlink,
   *              "true" or "false" string value will be returned, depending on its actual value.</li>
   *          <li>If object type is @link PDFObject::e_Number @endlink,
   *              the value will be represents as a string. For example, "1.5" string is for value 1.5.</li>
   *          <li>If object type is @link PDFObject::e_String @endlink, the string value will
   *              be retrieved directly.</li>
   *          </ul>
   *          If value of current PDF object cannot be converted to a valid string, an empty string will be returned.
   *
   * @return A string.
   */
  WString GetWideString() const;

  /**
   * @brief Get the PDF array object of current PDF object.
   *
   * @details If the type of current PDF object is @link PDFObject::e_Reference @endlink,
   *          this function will check the direct PDF object of current PDF object.
   *
   * @return A PDF array object. If current PDF object or the direct PDF object is not a PDF array,
   *         <b>NULL</b> will be returned.
   */
  PDFArray* GetArray();

  /**
   * @brief Get the PDF dictionary object of current PDF object.
   *
   * @details If the type of current PDF object is @link PDFObject::e_Reference @endlink,
   *          this function will check the direct PDF object of current PDF object.
   *
   * @return A PDF dictionary object. If current PDF object or the direct PDF object is not a PDF dictionary,
   *         <b>NULL</b> will be returned.
   */
  PDFDictionary* GetDict();

  /**
   * @brief Get the PDF stream object of current PDF object.
   *
   * @details If the type of current PDF object is @link PDFObject::e_Reference @endlink,
   *          this function will check the direct PDF object of current PDF object.
   *
   * @return A PDF stream object. If current PDF object or the direct PDF object is not a PDF stream,
   *         <b>NULL</b> will be returned.
   */
  PDFStream* GetStream();

 protected:
  ~PDFObject() {}

 private:
  PDFObject(const PDFObject&);
  PDFObject &operator = (const PDFObject& object);
};

/**
 * A PDF stream object consists of a direct dictionary object and stream data.
 * For more details, please refer to Section 3.2.7 "Stream Objects" in <PDF Reference 1.7>.<br>
 * Class @link objects::PDFStream @endlink is derived from @link PDFObject @endlink and offers functions to create a new PDF stream object and
 * get/set stream data.
 *
 * @see @link PDFObject @endlink
 */
class PDFStream FS_FINAL : public PDFObject {
 public:
  /**
   * @brief Enumeration for stream filter type.
   *
   * @details Values of this enumeration should be used alone.
   *          The stream filter indicates how the data in the PDF stream must be decoded
   *          before the data is used.
   */
  typedef enum _Filter {
    /** @brief Unknown filter type. */
    e_Unknown = -1,
    /** @brief No need to decode the stream data. */
    e_NoneDecode = 0,
    /**
   @brief Filter type: ASCIIHexDecode, which means to decode data encoded in an ASCII hexadecimal representation,
          reproducing the original binary data.
     */
    e_ASCIIHexDecode = 1,
    /**
   @brief Filter type: ASCII85Decode, which means to decode data encoded in an ASCII base-85 representation,
          reproducing the original binary data.
     */
    e_ASCII85Decode = 2,
    /**
   @brief Filter type: LZWDecode, which means to decompress data encoded using the LZW (Lempel-Ziv-Welch)
          adaptive compression method, reproducing the original text or binary data.
     */
    e_LZWDecode = 3,
    /**
   @brief Filter type: FlateDecode, which means to decompress data encoded using the zlib/deflate compression method,
          reproducing the original text or binary data.
     */
    e_FlateDecode = 4,
    /**
   @brief Filter type: RunLengthDecode, which means to decompress data
          encoded using a byte-oriented run-length encoding algorithm,
          reproducing the original text or binary data (typically monochrome image data,
          or any data that contains frequent long runs of a single byte value).
     */
    e_RunLengthDecode = 5,
    /**
   @brief Filter type: CCITTFaxDecode, which means to decompress data encoded using the CCITT facsimile standard,
          reproducing the original data (typically monochrome image data at 1 bit per pixel).
     */
    e_CCITTFaxDecode = 6,
    /**
   @brief Filter type: JBIG2Decode, which means to decompress data encoded using the JBIG2 standard,
          reproducing the original monochrome (1 bit per pixel) image data (or an approximation of that data).
     */
    e_JBIG2Decode = 7,
    /**
   @brief Filter type: DCTDecode, which means to decompress data encoded using a DCT (discrete cosine transform)
          technique based on the JPEG standard, reproducing image sample data that approximates the original data.
     */
    e_DCTDecode = 8,
    /**
   @brief Filter type: JPXDecode, which means to decompress data encoded using the wavelet-based
          JPEG2000 standard, reproducing the original image data.
     */
    e_JPXDecode = 9,
    /**
   @brief Filter type: Crypt, which means to decrypt data encrypted by a security handler,
          reproducing the original data as it was before encryption.
     */
    e_Crypt = 10
  } Filter;
  
  /**
   * @brief Create a new stream object based on a dictionary.
   *
   * @param[in] dictionary  A PDF dictionary object:
   *                        <ul>
   *                        <li>If this is <b>NULL</b>, PDF stream object will be created based on
   *                            an empty PDF dictionary.</li>
   *                        <li>If this is not <b>NULL</b>, after creating PDF stream object successfully,
   *                            do not call @link PDFObject::Release @endlink for this PDF dictionary object.</li>
   *                        </ul>
   *
   * @return A new @link PDFStream @endlink object.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFStream* Create(PDFDictionary* dictionary);

  /**
   * @brief Get the PDF dictionary object associated to current PDF stream object.
   *
   * @return The stream dictionary.
   */
  PDFDictionary* GetDictionary();

  /**
   * @brief Get the type of stream filter which indicate how the stream data must be decoded before the data is used.
   *
   * @return The type of stream filter. Please refer to values starting from @link PDFStream::e_Unknown @endlink and
   *         this would be one of these values.
   */
  Filter GetStreamFilter();

  /**
   * @brief Get the size of stream data, in bytes.
   *
   * @param[in] is_raw_data  A boolean value that indicates whether to get raw data or not:
   *                         <b>true</b> means to get raw data, and <b>false</b> means
   *                         to get decoded data (original data).
   *
   * @return The data size, in bytes.
   */
  uint64 GetDataSize(bool is_raw_data);

  /**
   * @brief Get stream data.
   *
   * @details When calling this function, user should pass a memory block with enough size to retrieve data.
   *          User is recommended to call function @link PDFStream::GetDataSize @endlink (with same parameter
   *          <i>is_raw_data</i>) to get the expected size, then prepare the memory block, and then
   *          call this function to get data.
   *
   * @param[in] is_raw_data  A boolean value that indicates whether to get raw data or not:
   *                         <b>true</b> means to get raw data, and <b>false</b> means to
   *                         get decoded data (original data).
   * @param[in] size         Size of parameter <i>out_buffer</i>, in bytes.
   *                         It should be equal to or larger than the actual data size.
   * @param[out] out_buffer  A memory block (with enough size) used as output parameter that receives the stream data.
   *                         It should not be <b>NULL</b>.
   *
   * @return <b>true</b> means success, while <b>false</b> means failed.
   */
  bool GetData(bool is_raw_data, size_t size, void* out_buffer);

  /**
   * @brief Set stream data.
   *
   * @param[in] buffer  A memory block that represents the new stream data to be set.
   * @param[in] size    Size of parameter <i>buffer</i>, in bytes.
   *
   * @return None.
   */
  void SetData(const void* buffer, size_t size);

  /**
   * @brief Import stream data.
   *
   * @param[in] file_read      A @link common::file::ReaderCallback @endlink object implemented by user. Foxit PDF SDK will use this to
   *                           read stream data and set to current PDF stream object. User should keep
   *                           this callback valid until the related PDF document is closed or current stream object
   *                           is released because of useless.
   * @param[in] stream_filter  Type of stream filter, which specifies how to decode the data
   *                           which is read through parameter <i>file_read</i>. Please refer to values starting from
   *                           @link PDFStream::e_NoneDecode @endlink and this should be one of these values except
   *                           @link PDFStream::e_Unknown @endlink.
   *
   * @return None.
   */
  void ImportData(common::file::ReaderCallback* file_read, Filter stream_filter);

  /**
   * @brief Export stream data.
   *
   * @details This function provides an efficient way to get the stream data, especially for large stream data.
   *
   * @param[in] is_raw_data  A boolean value that indicates whether to get raw data or not:
   *                         <b>true</b> means to get raw data, and <b>false</b> means to
   *                         get decoded data (original data).
   *
   * @return A @link common::file::ReaderCallback @endlink object which can be used to read stream data.
   *         Please remeber to use callback function Relase() of the returned @link common::file::ReaderCallback @endlink object to
   *         release this @link common::file::ReaderCallback @endlink object when not use it any more.
   *
   * @note If current stream object is released or related PDF document is closed,
   *       do not use returned @link common::file::ReaderCallback @endlink object any more; otherwise, unexpected error or crash will occur.
   */
  common::file::ReaderCallback* ExportData(bool is_raw_data);

 private:
  PDFStream(const PDFStream&);
  PDFStream &operator = (const PDFStream& stream);
};

/**
 * A PDF array object is a one-dimensional collection of objects arranged sequentially.
 * Unlike arrays in many other computer languages, elements in a PDF array can be any combination of numbers,
 * strings, dictionaries, or any other objects, including other arrays.
 * For more details, please refer to  Section 3.2.5 "Array Objects" in <PDF Reference 1.7>.<br>
 * Class @link objects::PDFArray @endlink is derived from @link PDFObject @endlink and offers functions to create a new PDF array object and
 * get/set elements of a PDF array object.
 *
 * @see @link PDFObject @endlink
 */
class PDFArray FS_FINAL : public PDFObject {
 public:
  /**
   * @brief Create a new array object.
   *
   * @return A new @link PDFArray @endlink object.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFArray* Create();

  /**
   * @brief Create a new array object for a matrix.
   *
   * @param[in] matrix  A matrix.
   *
   * @return A new @link PDFArray @endlink object.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFArray* CreateFromMatrix(const Matrix& matrix);

  /**
   * @brief Create a new array object for a rectangle.
   *
   * @param[in] rect  A rectangle.
   *
   * @return A new @link PDFArray @endlink object.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFArray* CreateFromRect(const RectF& rect);

  /**
   * @brief Get the count of elements.
   *
   * @return Element count
   */
  int GetElementCount() const;

  /**
   * @brief Get a specified element by index.
   *
   * @param[in] index  Index of the element to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFArray::GetElementCount @endlink.
   *
   * @return A @link PDFObject @endlink object that receives the specified element.
   */
  PDFObject* GetElement(int index) const;

  /**
   * @brief Add a PDF object to the end of current PDF array object.
   *
   * @param[in] element  A PDF object to be added to current PDF array object. It should not be <b>NULL</b>.
   *
   * @return None.
   */
  void AddElement(PDFObject* element);

  /**
   * @brief Add a boolean value to the end of current PDF array object.
   *
   * @param[in] boolean_value  A boolean value to current PDF array object.
   *
   * @return None.
   */
  void AddBoolean(bool boolean_value);

  /**
   * @brief Add a date time to the end of current PDF array object.
   *
   * @param[in] date_time  A date time to current PDF array object.
   *
   * @return None.
   */
  void AddDateTime(const DateTime& date_time);

  /**
   * @brief Add a float value to the end of current PDF array object.
   *
   * @param[in] float_value  A float value to current PDF array object.
   *
   * @return None.
   */
  void AddFloat(float float_value);

  /**
   * @brief Add an integer value to the end of current PDF array object.
   *
   * @param[in] integer_value  An integer value to current PDF array object.
   *
   * @return None.
   */
  void AddInteger(int integer_value);

  /**
   * @brief Add a matrix to the end of current PDF array object.
   *
   * @param[in] matrix  A matrix to current PDF array object.
   *
   * @return None.
   */
  void AddMatrix(const Matrix& matrix);

  /**
   * @brief Add a rectangle to the end of current PDF array object.
   *
   * @param[in] rect  A rectangle to current PDF array object.
   *
   * @return None.
   */
  void AddRect(const RectF& rect);

  /**
   * @brief Add a string as PDF name object to the end of current PDF array object.
   *
   * @param[in] name  A string to be added as PDF name object to current PDF array object.
   *                  It should not be an empty string.
   *
   * @return None.
   */
  void AddName(const char* name);

  /**
   * @brief Add a string as PDF string object to the end of current PDF array object.
   *
   * @param[in] new_string  A string to be added as PDF string object to current PDF array object.
   *                        It should not be an empty string.
   *
   * @return None.
   */
  void AddString(const wchar_t* new_string);

  /**
   * @brief Insert a PDF object to a specified position in current PDF array object.
   *
   * @param[in] index    Index of the position where parameter <i>element</i> will be inserted to.
   *                     Valid range: from 0 to (<i>count</i>-1).
   *                     <i>count</i> is returned by function @link PDFArray::GetElementCount @endlink.<br>
   *                     If this is below 0 or count of elements in current PDF array is 0,
   *                     parameter <i>element</i> is to be inserted to the first position.<br>
   *                     If this is larger than count of element in current PDF array,
   *                     parameter <i>element</i> is to be added to the end.
   * @param[in] element  A PDF object to be inserted to current PDF array object. It should not be <b>NULL</b>.
   *
   * @return None.
   */
  void InsertAt(int index, PDFObject* element);

  /**
   * @brief Set a new PDF object at a specified position in current PDF array object.
   *
   * @param[in] index    Index of the position where parameter <i>element</i> will be set to.
   *                     Valid range: from 0 to (<i>count</i>-1).
   *                     <i>count</i> is returned by function @link PDFArray::GetElementCount @endlink.
   * @param[in] element  A PDF object to be set to current PDF array object. It should not be <b>NULL</b>.
   *
   * @return None.
   */
  void SetAt(int index, PDFObject* element);

  /**
   * @brief Remove an element in a specified position (by index) from current PDF array object.
   *
   * @param[in] index  Index of the position where the element will be removed.
   *                   Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFArray::GetElementCount @endlink.
   *
   * @return None.
   */
  void RemoveAt(int index);

 private:
  PDFArray(const PDFArray&);
  PDFArray &operator = (const PDFArray& array_object);
};

/**
 * A PDF dictionary object is an associative table containing pairs of objects, known as entries of the dictionary.
 * The first element of each entry is the key, and it must be a PDF name object. The second element is the value,
 * and it can be any kind of PDF object, including another dictionary. In the same dictionary,
 * no two entries should have the same key. For more details, please refer to Section 3.2.6 "Dictionary Objects"
 * in <PDF Reference 1.7>.<br>
 * Class @link objects::PDFDictionary @endlink is derived from @link PDFObject @endlink and offers functions to create a new PDF dictionary object and
 * get/set entries in a PDF dictionary object.
 *
 * @see @link PDFObject @endlink
 */
class PDFDictionary FS_FINAL : public PDFObject {
 public:
  /**
   * @brief Create a new dictionary object.
   *
   * @return A new @link PDFDictionary @endlink object.
   *         Please call function @link PDFObject::Release @endlink to release the created object
   *         if it has not been added/set into PDF document or other PDF object and will not be used any more.
   */
  static PDFDictionary* Create();

  /**
   * @brief Check whether there is an entry with specified key in current dictionary or not.
   *
   * @param[in] key  The key to be checked. It should not be an empty string.
   *
   * @return <b>true</b> means the specified key exist in current dictionary, while <b>false</b> means not.
   */
  bool HasKey(const char* key) const;

  /**
   * @brief Get the value element of an entry with specified key.
   *
   * @param[in] key  The key of the entry. It should not be an empty string.
   *
   * @return A @link PDFObject @endlink object that receives the value with specified key.
   */
  PDFObject* GetElement(const char* key) const;

  /**
   * @brief Move to the position of first or the next entry.
   *
   * @param[in] position  A POSITION that indicates the position of current entry in the dictionary.
   *                      If this is <b>NULL</b> or 0, the position of first entry in the dictionary will be returned.
   *
   * @return A POSITION that represents the position of next entry in the dictionary.
   *         <b>NULL</b> or 0 means current entry is the last in the dictionary.
   */
  POSITION MoveNext(POSITION position);

  /**
   * @brief Get the key of an entry specified by position.
   *
   * @param[in] position  A POSITION that specifies the position of the entry. It should not be <b>NULL</b> or 0.
   *
   * @return The key of the specified entry.
   */
  String GetKey(POSITION position) const;

  /**
   * @brief Get the value element of an entry specified by position.
   *
   * @param[in] position  A POSITION that specifies the position of the entry. It should not be <b>NULL</b> or 0.
   *
   * @return A @link PDFObject @endlink that receives the value element of the specified entry.
   */
  PDFObject* GetValue(POSITION position) const;

  /**
   * @brief Set a direct PDF object (whose object number is always equal to 0) as value element to an entry specified by key.
   *
   * @details If user wants to set indirect PDF object (whose object number is always above 0) to an entry,
   *          please refer to function @link PDFDictionary::SetAtReference @endlink.
   *
   * @param[in] key         The key of the entry, whose value element will be set. It should not be an empty string.
   * @param[in] pdf_object  A @link PDFObject @endlink object which is a direct PDF object (whose object number is always equal to 0) and will be set to the entry.
   *                        It should not be <b>NULL</b>.
   *
   * @return None.
   */
  void SetAt(const char* key, PDFObject* pdf_object);

  /**
   * @brief Set the reference object of an indirect PDF object (whose object number is always above 0) as value element to an entry specified by key.
   *
   * @details If user wants to set direct PDF object (whose object number is always equal to 0) to an entry,
   *          please refer to function @link PDFDictionary::SetAt @endlink.
   *
   * @param[in] key         The key of the entry, whose value element will be set. It should not be an empty string.
   * @param[in] pdf_object  A @link PDFObject @endlink object which is an indirect PDF object (whose object number is always above 0) and
   *                        will be set to the entry by a reference object which refers to this indirect object. It should not be <b>NULL</b>.
   * @param[in] document    A valid PDF document object, to which current PDF dictionary object belongs and
   *                        in which parameter <i>pdf_object</i> is or will be an indirect object.
   *
   * @return None.
   */
  void SetAtReference(const char* key, PDFObject* pdf_object, PDFDoc document);

  /**
   * @brief Set boolean element an entry specified by key.
   *
   * @param[in] key    The key of the entry, whose value element will be set. It should not be an empty string.
   * @param[in] value  A boolean element which will be set to the entry.
   *
   * @return None.
   */
  void SetAtBoolean(const char* key, bool value);

  /**
   * @brief Set a Datetime object as value element to an entry specified by key.
   *
   * @param[in] key    The key of the entry, whose value element will be set. It should not be an empty string.
   * @param[in] value  The date time information which will be set to the entry.
   *
   * @return None.
   */
  void SetAtDateTime(const char* key, const DateTime& value);

  /**
   * @brief Set a float element to an entry specified by key.
   *
   * @param[in] key    The key of the entry, whose value element will be set. It should not be an empty string.
   * @param[in] value  A float value which will be set to the entry.
   *
   * @return None.
   */
  void SetAtFloat(const char* key, float value);

  /**
   * @brief Set a integer element to an entry specified by key.
   *
   * @param[in] key    The key of the entry, whose value element will be set. It should not be an empty string.
   * @param[in] value  An integer value which will be set to the entry.
   *
   * @return None.
   */
  void SetAtInteger(const char* key, int value);

  /**
   * @brief Set a matrix object as value element to an entry specified by key.
   *
   * @param[in] key    The key of the entry, whose value element will be set. It should not be an empty string.
   * @param[in] value  A matrix which will be set to the entry.
   *
   * @return None.
   */
  void SetAtMatrix(const char* key, const Matrix& value);

  /**
   * @brief Set a rectangle object as value element to an entry specified by key.
   *
   * @param[in] key    The key of the entry, whose value element will be set. It should not be an empty string.
   * @param[in] value  A rectangle which will be set to the entry.
   *
   * @return None.
   */
  void SetAtRect(const char* key, const RectF& value);

  /**
   * @brief Set a string (as PDF name object) as value element to an entry specified by key.
   *
   * @param[in] key    The key of the entry, whose value element will be set. It should not be an empty string.
   * @param[in] value  A string which will be set as PDF name object to the entry. It should not be an empty string.
   *
   * @return None.
   */
  void SetAtName(const char* key, const char* value);

  /**
   * @brief Set a string as value element to an entry specified by key.
   *
   * @param[in] key    The key of the entry, whose value element will be set. It should not be an empty string.
   * @param[in] value  A string which will be set as PDF string object to the entry.
   *
   * @return None.
   *
   * @note If to get string value, please call function @link PDFObject::GetString @endlink.
   */
  void SetAtString(const char* key, const char* value);

  /**
   * @brief Set a string as value element to an entry specified by key.
   *
   * @param[in] key    The key of the entry, whose value element will be set. It should not be an empty string.
   * @param[in] value  A wide string which will be set as PDF string object to the entry.
   *
   * @return None.
   *
   * @note If to get string value, please call function @link PDFObject::GetWideString @endlink.
   */
  void SetAtString(const char* key, const wchar_t* value);

  /**
   * @brief Remove an entry specified by key.
   *
   * @param[in] key  The key of the entry to be removed. It should not be an empty string.
   *
   * @return None.
   */
  void RemoveAt(const char* key);

 private:
  PDFDictionary(const PDFDictionary&);
  PDFDictionary &operator = (const PDFDictionary& dictionary);
};

}  // namespace objects
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PDFOBJECT_H_

