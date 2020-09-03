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
 * @file fs_psi.h
 * @brief Header file for PSI (pressure sensitive ink) related definitions and classes.
 */

#ifndef FS_PSI_H_
#define FS_PSI_H_

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
// forward declaration
class PSI;

/**
 * This class represents a callback object for refreshing a region for PSI.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 * An implemented @link PSICallback @endlink object can be set to a PSI object by function @link PSI::SetCallback @endlink.
 */
class PSICallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;
  /**
   * @brief A callback function used to refresh a specified region for PSI.
   *
   * @param[in] psi   A PSI object.
   * @param[in] rect  Rectangle of the refresh region.
   *
   * @return None.
   */
  virtual void Refresh(PSI psi, const RectF& rect) = 0;

 protected:
  ~PSICallback() {}
};

/**
 * PSI, "pressure sensitive ink", is specially defined for manual signature, and usually works together with
 * a handwriting board or for a touchscreen. PSI contains private coordinates, and a canvas is created
 * in its coordinates. Canvas limits operating area and generates appearance of PSI.<br>
 * PSI is independent of PDF, and can even be used directly in the device screen. If user wants to save a PSI object
 * to PDF file, please call function @link PSI::ConvertToPDFAnnot @endlink. This function will convert PSI data to
 * a PSInk annotation (as a Foxit custom annotation type) and insert the PSInk annotation to the specified position
 * in a PDF page.
 *
 * @see @link annots::PSInk @endlink
 */
class PSI FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, with a bitmap as canvas.
   *
   * @param[in] bitmap    A bitmap used as canvas. It should be created with @link common::Bitmap::e_DIBArgb @endlink format.
   *                      User should ensure this bitmap to keep valid until current PSI object is released.
   * @param[in] simulate  Used to decide whether to turn on simulation of PSI or not:<br>
   *                      <b>true</b> means to turn on simulation, and <b>false</b> means to turn off simulation.<br>
   *                      It can simulate handwriting weights by writing speed when simulation is on.
   */
  PSI(common::Bitmap& bitmap, bool simulate);

  /**
   * @brief Constructor, with specified width and height for canvas.
   *
   * @param[in] width     Width of PSI canvas in device coordinate system. This shall be greater than 0.
   * @param[in] height    Height of PSI canvas in device coordinate system. This shall be greater than 0.
   * @param[in] simulate  Used to decide whether to turn on simulation of PSI or not:<br>
   *                      <b>true</b> means to turn on simulation, and <b>false</b> means to turn off simulation.<br>
   *                      It can simulate handwriting weights by writing speed when simulation is on.
   */
  PSI(int width, int height, bool simulate);

  /**
   * @brief Constructor, with another PSI object.
   *
   * @param[in] other  Another PSI object.
   */
  PSI(const PSI& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another PSI object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PSI& operator = (const PSI& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another PSI object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PSI& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another PSI object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PSI& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;
  /** @brief Destructor. */
  ~PSI();

  /**
   * @brief Set a callback object for refreshing.
   *
   * @param[in] callback  A callback object @link PSICallback @endlink which is implemented by user.
   *                      Please ensure that the callback object keeps valid until
   *                      the life-cycle of current PSI object ends.
   *
   * @return None.
   */
  void SetCallback(PSICallback* callback);

  /**
   * @brief Set ink color.
   *
   * @details This should be set before adding first point to PSI object.
   *          If not set, the default value 0x000000 will be used.
   *
   * @param[in] color  Ink color. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetColor(RGB color);

  /**
   * @brief Set ink diameter.
   *
   * @details This should be set before adding first point to PSI object.
   *          If not set, the default value 10 will be used.
   *
   * @param[in] diameter  Ink diameter. This should be bigger than 1.
   *
   * @return None.
   */
  void SetDiameter(int diameter);

  /**
   * @brief Set ink opacity.
   *
   * @details This should be set before adding first point to PSI object.
   *          If not set, the default value 1.0 will be used.
   *
   * @param[in] opacity  Ink opacity. Valid range: from 0.0 to 1.0.
   *                     0.0 means full transparency and 1.0 means full opaque.
   *
   * @return None.
   */
  void SetOpacity(float opacity);

  /**
   * @brief Add a point.
   *
   * @param[in] point     A point in canvas coordinate system.
   * @param[in] type      Point type. This should be one of following values:
   *                      @link common::Path::e_TypeMoveTo @endlink, @link common::Path::e_TypeLineTo @endlink,
   *                      @link common::Path::e_TypeLineToCloseFigure @endlink,
   * @param[in] pressure  Pressure value for this point. Valid range: from 0.0 to 1.0.
   *
   * @return None.
   */
  void AddPoint(const PointF& point, common::Path::PointType type, float pressure);

  /**
   * @brief Get contents rectangle.
   *
   * @return Contents rectangle, in device coordinate system.
   *         If current PSI object does not contain a valid path,
   *         a RectF object with all 0 values would be returned.
   */
  RectF GetContentsRect();

  /**
   * @brief Get the canvas bitmap.
   *
   * @return Canvas bitmap.
   */
  common::Bitmap GetBitmap();

  /**
   * @brief Convert a PSI object to a PSInk annotation and insert the PSInk annotation to a PDF page.
   *
   * @details Actually, this function is to convert the path data of current PSI to a PSInk annotation,
   *          ignoring the canvas bitmap.<br>
   *          Before calling this function, user should ensure that current PSI object has contained a valid path
   *          (whose last point's type is @link common::Path::e_TypeLineToCloseFigure @endlink.
   *          Otherwise, the conversion will be failed and this function will throw exception
   *          @link foxit::e_ErrInvalidData @endlink.
   *
   * @param[in] page        A valid PDF page object, to which the PSI is expected to inserted.
   * @param[in] annot_rect  A rectangle to specify the position in the PDF page,
   *                        where the new PSInk annotation will be inserted.
   *                        It should be valid in [PDF coordinate system] (@ref PDFPage).
   * @param[in] rotate      Rotation value. Currently, it can only be @link common::e_Rotation0 @endlink.
   *
   * @return A new PSInk annotation object.
   *
   * @note User do not need to call function @link annots::Annot::ResetAppearanceStream @endlink (inherited from
   *       PSInk's parent class) to reset the appearance of PSInk annotation after this conversion.
   */
  annots::PSInk ConvertToPDFAnnot(const PDFPage& page, const RectF& annot_rect, common::Rotation rotate);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PSI(FS_HANDLE handle =  NULL);

};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PSI_H_

