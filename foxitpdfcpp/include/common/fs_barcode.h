/**
 * Copyright (C) 2003-2020, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software
 * Inc.. It is not allowed to distribute any parts of Foxit PDF SDK to third
 * party or public without permission unless an agreement is signed between
 * Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file fs_barcode.h
 * @brief Header file for barcode related definitions and functions.
 */

#ifndef FS_BARCODE_H_
#define FS_BARCODE_H_

#include "fs_common.h"
#include "fs_image.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/**
 * @brief Add-on namespace.
 */
namespace common {
/** This class can be used to generate barcode bitmap.*/
class Barcode FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for barcode format.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Format {
    /** @brief Barcode format: standard 39 code. */
    e_FormatCode39 = 0,
    /** @brief Barcode format: Code128, including EAN128 code. */
    e_FormatCode128 = 1,
    /** @brief Barcode format: EAN-8 code. */
    e_FormatEAN8 = 2,
    /** @brief Barcode format: UPC-A code. */
    e_FormatUPCA = 3,
    /** @brief Barcode format: EAN-13 code. */
    e_FormatEAN13 = 4,
    /** @brief Barcode format: ITF code. */
    e_FormatITF = 5,
    /** @brief Barcode format: PDF-417 code. */
    e_FormatPDF417 = 6,
    /** @brief Barcode format: Quick Response Code. */
    e_FormatQRCode = 7
  } Format;
  
  /**
   * @brief Enumeration for format error correction level of QR Code.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _QRErrorCorrectionLevel {
    /** @brief The capability of recovery from 7% amounts of damage. */
    e_QRCorrectionLevelLow = 0,
    /** @brief The capability of recovery from 15% amounts of damage. */
    e_QRCorrectionLevelMedium = 1,
    /** @brief The capability of recovery from 25% amounts of damage. */
    e_QRCorrectionLevelQuater = 2,
    /** @brief The capability of recovery from 30% amounts of damage. */
    e_QRCorrectionLevelHigh = 3
  } QRErrorCorrectionLevel;
  
  /** @brief Constructor. */
  Barcode();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Barcode(FS_HANDLE handle);

  /** @brief Destructor. */
  ~Barcode();
  /**
   * @brief Constructor, with another barcode object.
   *
   * @param[in] other  Another barcode object.
   */
  Barcode(const Barcode& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another barcode object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Barcode& operator = (const Barcode& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another barcode object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Barcode& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another barcode object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Barcode& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Generate a barcode bitmap with a given information string and specified barcode format.
   *
   * @param[in] info         Information string to be encoded to barcode bitmap. It should not be an empty string.
   * @param[in] format       Barcode format which is used to encode information string.
   *                         Please refer to values starting from @link Barcode::e_FormatCode39 @endlink and
   *                         this should be one of these values.
   * @param[in] unit_width   Unit width for barcode, in pixels. Valid values: from 1 to 5. If input value is below 1,
   *                         1 will be used by default; if input value is above 5, 5 will be used by default.<br>
   *                         Specially, for PDF-417 and QR Code, the minimum value of <i>unit_width</i> and
   *                         <i>unit_height</i> will be used as unit width (compared with valid value range)
   *                         and unit height will be ignored.
   * @param[in] unit_height  Unit height for barcode, in pixels. Valid values: equal to or above 20.
   *                         If input value is below 20, 20 will be used by default.<br>
   *                         Specially, for PDF-417 and QR Code, the minimum value of <i>unit_width</i> and
   *                         <i>unit_height</i> will be used as unit width (compared with valid value range)
   *                         and unit height will be ignored.
   * @param[in] level        (Required only for QR Code) Error correction level. Please refer to values starting from
   *                         @link Barcode::e_QRCorrectionLevelLow @endlink and this should be one of these values.
   *
   * @return A barcode bitmap.
   */
  common::Bitmap GenerateBitmap(const WString& info, Format format, int32 unit_width, int32 unit_height,
                                QRErrorCorrectionLevel level);
};
}  // namespace common
}  // namespace foxit

#endif  // FS_BARCODE_H_
