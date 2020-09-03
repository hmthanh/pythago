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
 * @file fs_annot.h
 * @brief Header file for annotation related definitions and classes.
 */

#ifndef FS_ANNOT_H_
#define FS_ANNOT_H_

#include "common/fs_common.h"
#include "common/file/fs_file.h"
#include "common/fs_image.h"
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
// forward declaration
class PDFPage;
class FileSpec;
namespace actions {
class Action;
}  // namespace actions
namespace annots {
class Note;
class Popup;
}  // namespace annots
namespace interform {
class Field;
class Control;
}  // namespace interform

/**
 * This class represents default appearance data, which is used for free text annotation and form.
 */
class DefaultAppearance FS_FINAL : public Object {
 public:
  /**
   * @brief Enumeration for default appearance flags.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _DefAPFlags {
    /** @brief Indicates property <i>font</i> of @link pdf::DefaultAppearance @endlink is meaningful. */
    e_FlagFont = 0x0001,
    /** @brief Indicates property <i>text color</i> of @link pdf::DefaultAppearance @endlink is meaningful. */
    e_FlagTextColor = 0x0002,
    /** @brief Indicates property <i>text size</i> of @link pdf::DefaultAppearance @endlink is meaningful. */
    e_FlagFontSize = 0x0004
  } DefAPFlags;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] flags       Flags to indicate which properties of default appearance are meaningful.
   *                        Please refer to values starting from @link DefaultAppearance::e_FlagFont @endlink and
   *                        this can be one or a combination of these values.
   * @param[in] font        A valid font object for default appearance when parameter <i>flags</i> includes
   *                        @link DefaultAppearance::e_FlagFont @endlink.
   * @param[in] text_size   Font size for default appearance when parameter <i>flags</i> includes
   *                        @link DefaultAppearance::e_FlagFontSize @endlink. Usually it should be above 0.
   *                        For some objects, the size 0 has special meaning. Please refer to the comment of functions
   *                        which are used to set default appearance data to other object.
   * @param[in] text_color  Text color for default appearance. Format: 0xRRGGBB.
   */
  DefaultAppearance(uint32 flags, const common::Font& font, float text_size, RGB text_color)
    : flags(flags)
    , font(font)
    , text_size(text_size)
    , text_color(text_color) {}

  /** @brief Constructor. */
  DefaultAppearance()
    : flags(0)
    , text_size(0)
    , text_color(0x000000) {}

  /**
   * @brief Constructor, with another default appearance object.
   *
   * @param[in] default_appearance  Another default appearance object.
   */
  DefaultAppearance(const DefaultAppearance& default_appearance)
    : flags(default_appearance.flags)
    , font(default_appearance.font)
    , text_size(default_appearance.text_size)
    , text_color(default_appearance.text_color) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] default_appearance  Another default appearance object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  DefaultAppearance& operator = (const DefaultAppearance& default_appearance) {
    flags = default_appearance.flags;
    font = default_appearance.font;
    text_size = default_appearance.text_size;
    text_color = default_appearance.text_color;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] default_appearance  Another default appearance object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const DefaultAppearance& default_appearance) const {
    return (flags == default_appearance.flags && font == default_appearance.font &&
            fabs(text_size-default_appearance.text_size) <= FLT_EPSILON &&
            text_color == default_appearance.text_color);
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] default_appearance  Another default appearance object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const DefaultAppearance& default_appearance) const  {
    return (flags != default_appearance.flags || font != default_appearance.font ||
            fabs(text_size - default_appearance.text_size) > FLT_EPSILON ||
            text_color != default_appearance.text_color);
  }

  /**
   * @brief Set value.
   *
   * @param[in] flags       Flags to indicate which properties of default appearance are meaningful.
   *                        Please refer to values starting from @link DefaultAppearance::e_FlagFont @endlink and
   *                        this can be one or a combination of these values.
   * @param[in] font        A font for default appearance. Please ensure this is a valid font object
   *                        when parameter <i>flags</i> includes
   *                        @link DefaultAppearance::e_FlagFont @endlink.
   * @param[in] text_size   Font size for default appearance when parameter <i>flags</i> includes
   *                        @link DefaultAppearance::e_FlagFontSize @endlink. Usually it should be above 0.
   *                        For some objects, the size 0 has special meaning. Please refer to the comment of functions
   *                        which are used to set default appearance data to other object.
   * @param[in] text_color  Text color for default appearance. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void Set(uint32 flags, const common::Font& font, float text_size, RGB text_color) {
    this->flags = flags;
    this->font = font;
    this->text_size = text_size;
    this->text_color = text_color;
  }

  /**
  * @brief Flags to indicate which properties of default appearance are meaningful.
  *
  * @details Please refer to values starting from @link DefaultAppearance::e_FlagFont @endlink and
  *          this can be one or a combination of these values.
  *          0 means no property of default appearance is meaningful.
  */
  uint32 flags;
  /**
   * @brief A font for default appearance. It should be a valid font object when it is useful.
   *
   * @note Useful only when <i>flags</i> of current object includes @link DefaultAppearance::e_FlagFont @endlink.
   */
  common::Font font;
  /**
   * @brief Text size for default appearance.
   *
   * @details Usually it should be above 0 when it is useful. For some objects, the size 0 has special meaning.
   *          Please refer to the comment of functions which are used to set default appearance data to other object.
   *
   * @note Useful only when <i>flags</i> of current object includes @link DefaultAppearance::e_FlagFontSize @endlink.
   */
  float text_size;
  /**
   * @brief Text color for default appearance. Format: 0xRRGGBB.
   *
   * @note Useful only when <i>flags</i> of current object includes @link DefaultAppearance::e_FlagTextColor @endlink.
   */
  RGB text_color;
};
/**
 * @brief Annotations namespace.
 */
namespace annots {
/** This class represents annotation border information. */
class BorderInfo FS_FINAL : public Object {
 public:
  /**
   * @brief Enumeration for PDF annotation border style.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Style {
    /** @brief Border style: Solid */
    e_Solid      = 0,
    /**
   @brief Border style: Dashed.
   @details This is only useful for link, free text, line, square, circle, polygon, polyline and screen annotation.
            If this is set to other type annotation, Foxit PDF SDK will change to set border style as
            @link BorderInfo::e_Solid @endlink by default internally.
     */
    e_Dashed     = 1,
    /**
   @brief Border style: Underline.
   @details This is only useful for link annotation. If this is set to other type annotation, Foxit PDF SDK will
            change to set border style as @link BorderInfo::e_Solid @endlink by default internally.
     */
    e_UnderLine  = 2,
    /**
   @brief Border style: Beveled.
   @details Currently, Foxit PDF SDK does not support the annotation appearance of this border style.
            If this is set to any annotation, Foxit PDF SDK will change to set border style as
            @link BorderInfo::e_Solid @endlink by default internally.
     */
    e_Beveled    = 3,
    /**
   @brief Border style: Inset.
   @details Currently, Foxit PDF SDK does not support the annotation appearance of this border style.
            If this is set to any annotation, Foxit PDF SDK will change to set border style as
            @link BorderInfo::e_Solid @endlink by default internally.
     */
    e_Inset      = 4,
    /**
   @brief Border style: Cloudy.
   @details This is only useful for free text, square, circle, and polygon annotations.
            If this is set to other type annotation, Foxit PDF SDK will change to set border style as
            @link BorderInfo::e_Solid @endlink by default internally.
     */
    e_Cloudy     = 5
  } Style;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] width       Border width, in points. This should be a non-negative value.
   *                        If this value is 0, no border is drawn.
   * @param[in] style       Border style. Please refer to values starting from @link BorderInfo::e_Solid @endlink and
   *                        this should be one of these values.
   * @param[in] intensity   Intensity of the cloudy effect. Only useful when parameter <i>style</i> is
   *                        @link BorderInfo::e_Cloudy @endlink. Valid value range: 0 to 2.
   *                        0 means no cloudy border effect.<br>
   *                        If the value is below 0, it will have the same effect as value 0.
   *                        If the value is above 2, it will have the same effect as value 2.
   * @param[in] dash_phase  Dash phase. Only useful when parameter <i>style</i> is
   *                        @link BorderInfo::e_Dashed @endlink.
   * @param[in] dashes      A dash array that represents the dash patterns. The value of each element in this array
   *                        should not be negative. Only useful when <i>style</i> is @link BorderInfo::e_Dashed @endlink.
   */
  BorderInfo(float width, Style style, float intensity, float dash_phase, const FloatArray& dashes) {
    this->width = width;
    this->style = style;
    this->cloud_intensity = intensity;
    this->dash_phase = dash_phase;
    this->dashes = dashes;
  }

  /** @brief Constructor. */
  BorderInfo()
      : width(1.0f)
      , style(BorderInfo::e_Solid)
      , cloud_intensity(0)
      , dash_phase(0) {}

  /** @brief Destructor. */
  ~BorderInfo() {}

  /**
   * @brief Constructor, with another border information object.
   *
   * @param[in] border_info  Another border information object.
   */
  BorderInfo(const BorderInfo& border_info) {
    this->width = border_info.width;
    this->style = border_info.style;
    this->cloud_intensity = border_info.cloud_intensity;
    this->dash_phase = border_info.dash_phase;
    this->dashes = border_info.dashes;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] border_info  Another border information object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  BorderInfo& operator = (const BorderInfo& border_info) {
    this->width = border_info.width;
    this->style = border_info.style;
    this->cloud_intensity = border_info.cloud_intensity;
    this->dash_phase = border_info.dash_phase;
    this->dashes = border_info.dashes;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] border_info  Another border information object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const BorderInfo& border_info) const {
    if (fabs(width - border_info.width) > FLT_EPSILON || style != border_info.style ||
        fabs(cloud_intensity - border_info.cloud_intensity) > FLT_EPSILON ||
        fabs(dash_phase - border_info.dash_phase) > FLT_EPSILON ||
        dashes.GetSize() != border_info.dashes.GetSize())
      return false;
    for (int i=0; i<dashes.GetSize(); i++) {
      if (fabs(dashes[i]-border_info.dashes[i])>FLT_EPSILON)
        return false;
    }
    return true;
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] border_info  Another border information object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const BorderInfo& border_info) const{
    if (fabs(width - border_info.width) > FLT_EPSILON || style != border_info.style ||
      fabs(cloud_intensity - border_info.cloud_intensity) > FLT_EPSILON ||
      fabs(dash_phase - border_info.dash_phase) > FLT_EPSILON ||
      dashes.GetSize() != border_info.dashes.GetSize())
      return true;
    for (int i=0; i<dashes.GetSize(); i++) {
      if (fabs(dashes[i]-border_info.dashes[i])>FLT_EPSILON)
        return true;
    }
    return false;
  }

  /**
   * @brief Set value.
   *
   * @param[in] width       Border width, in points. This should be a non-negative value.
   *                        If this value is 0, no border is drawn.
   * @param[in] style       Border style. Please refer to values starting from @link BorderInfo::e_Solid @endlink and
   *                        this should be one of these values.
   * @param[in] intensity   Intensity of the cloudy effect. Only useful when parameter <i>style</i> is
   *                        @link BorderInfo::e_Cloudy @endlink. Valid value range: 0 to 2.
   *                        0 means no cloudy border effect.<br>
   *                        If the value is below 0, it will have the same effect as value 0.
   *                        If the value is above 2, it will have the same effect as value 2.
   * @param[in] dash_phase  Dash phase. Only useful when parameter <i>style</i> is
   *                        @link BorderInfo::e_Dashed @endlink.
   * @param[in] dashes      A dash array that represents the dash patterns. The value of each element in this array
   *                        should not be negative. Only useful when <i>style</i> is @link BorderInfo::e_Dashed @endlink.
   *
   * @return None.
   */
  void Set(float width, Style style, float intensity, float dash_phase, const FloatArray& dashes) {
    this->width = width;
    this->style = style;
    this->cloud_intensity = intensity;
    this->dash_phase = dash_phase;
    this->dashes = dashes;
  }

  /**
   * @brief Border width, in points.
   *
   * @details This value should not be negative. If this value is 0, no border will be drawn.
   */
  float width;

  /**
   * @brief Border style. Please refer to values starting from @link BorderInfo::e_Solid @endlink and
   *        this should be one of these values. Please also check comment of these values for more details.
   */
  Style style;

  /**
   * @brief Intensity of the cloudy effect.
   *
   * @details This is only useful to free text, square, circle, and polygon annotations
   *          when <i>style</i> of current object is @link BorderInfo::e_Cloudy @endlink.<br>
   *          Suggested value range: 0 to 2. 0 means no cloudy border effect.<br>
   *          For rest value, their effect would be:
   *          <ul>
   *          <li>If the value is below 0, it will have the same effect as value 0. </li>
   *          <li>If the value is above 2, it will have the same effect as value 2.</li>
   *          </ul>   */
  float cloud_intensity;

  /**
   * @brief Dash phase.
   *
   * @details Only useful when <i>style</i> of current object is @link BorderInfo::e_Dashed @endlink.
   */
  float dash_phase;

  /**
   * @brief A dash array that represents the dash patterns.
   *
   * @details Only useful when <i>style</i> of current object is @link BorderInfo::e_Dashed @endlink.<br>
   *          The value of elements in this array should not be negative.<br>
   */
  FloatArray dashes;
};

/**
 * This class represents points of a quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage).
 * The order of points in a quadrilateral should be as follows:
 * <ul>
 * <li>The first point is the point in left-top corner of the quadrilateral.</li>
 * <li>The second point is the point in right-top corner of the quadrilateral.</li>
 * <li>The third point is the point in left-bottom corner of the quadrilateral.</li>
 * <li>The fourth point is the point in right-bottom corner of the quadrilateral.</li>
 * </ul>
 */
class QuadPoints FS_FINAL : public Object {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] first   First point of the quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] second  Second point of the quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] third   Third point of the quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] fourth  Fourth point of the quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage).
   */
  QuadPoints(const PointF& first, const PointF& second, const PointF& third, const PointF& fourth) {
    this->first = first;
    this->second = second;
    this->third = third;
    this->fourth = fourth;
  }

  /** @brief Constructor. */
  QuadPoints() {}

  /**
   * @brief Constructor, with another quadrilateral points object.
   *
   * @param[in] quad_points  Another quadrilateral points object.
   */
  QuadPoints(const QuadPoints& quad_points) {
    first = quad_points.first;
    second = quad_points.second;
    third = quad_points.third;
    fourth = quad_points.fourth;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] quad_points  Another quadrilateral points object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  QuadPoints& operator = (const QuadPoints& quad_points) {
    first = quad_points.first;
    second = quad_points.second;
    third = quad_points.third;
    fourth = quad_points.fourth;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] quad_points  Another quadrilateral points object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const QuadPoints& quad_points) const {
    return (first == quad_points.first && second == quad_points.second &&
            third == quad_points.third && fourth == quad_points.fourth);
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] quad_points  Another quadrilateral points object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const QuadPoints& quad_points) const {
    return (first != quad_points.first || second != quad_points.second ||
            third != quad_points.third || fourth != quad_points.fourth);
  }

  /**
   * @brief Set value.
   *
   * @param[in] first   First point of the quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] second  Second point of the quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] third   Third point of the quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] fourth  Fourth point of the quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @return None.
   */
  void Set(const PointF& first, const PointF& second, const PointF& third, const PointF& fourth) {
    this->first = first;
    this->second = second;
    this->third = third;
    this->fourth = fourth;
  }

  /** @brief First point of quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage). */
  PointF  first;
  /** @brief Second point of quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage). */
  PointF  second;
  /** @brief Third point of quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage). */
  PointF  third;
  /** @brief Fourth point of quadrilateral, in [PDF coordinate system] (@ref pdf::PDFPage). */
  PointF  fourth;
};

/** This class represents an array of @link annots::QuadPoints @endlink objects. */
FSDK_DEFINE_ARRAY(QuadPointsArray, QuadPoints)

/**
 * This class represents icon fit information. Icon fit information is used to specify how to display a button's icon
 * within the annotation rectangle of its associated widget annotation.
 */
class IconFit FS_FINAL : public Object {
 public:
  /**
   @brief Enumeration for the type of icon scaling way.
   @details Values of this enumeration should be used alone.
   */
  typedef enum _ScaleWayType {
    /** @brief Always scale. */
    e_ScaleWayAlways = 1,
    /** @brief Scale only when icon is bigger than annotation rectangle. */
    e_ScaleWayBigger = 2,
    /** @brief Scale only when icon is smaller than annotation rectangle. */
    e_ScaleWaySmaller = 3,
    /** @brief Never scale.*/
    e_ScaleWayNever = 4
  } ScaleWayType;
  

  /** @brief Constructor. */
  IconFit()
      : scale_way_type((ScaleWayType)0)
      , is_proportional_scaling(false)
      , horizontal_fraction(0)
      , vertical_fraction(0)
      , fit_bounds(false) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] type                     The circumstances under which the icon should be scaled inside
   *                                     the annotation rectangle. Please refer to values starting from
   *                                     @link IconFit::e_ScaleWayAlways @endlink and this should be one of these values.
   * @param[in] is_proportional_scaling  Indicates whether use proportional scaling or not.
   *                                     <b>true</b> means to fill the annotation rectangle exactly,
   *                                     without regard to its original aspect ratio (ratio of width to height).<br>
   *                                     <b>false</b> means scale the icon to scale the icon to fit the width or
   *                                     height of the annotation rectangle while maintaining the icon's
   *                                     original aspect ratio.
   * @param[in] horizontal_fraction      The horizontal fraction of left-over space to allocate
   *                                     at the left and bottom of the icon if the icon is scaled proportionally.
   *                                     Valid range: 0.0 to 1.0.
   * @param[in] vertical_fraction        The vertical fraction of left-over space to allocate
   *                                     at the left and bottom of the icon if the icon is scaled proportionally.
   *                                     Valid range: 0.0 to 1.0.
   * @param[in] fit_bounds               Indicates whether to scale button appearance to fit fully within bounds or not.
   *                                     <b>true</b> means that the button appearance should be scaled to fit fully
   *                                     within the bounds of the annotation without taking into consideration
   *                                     the line width of the border.
   */
  IconFit(ScaleWayType type, bool is_proportional_scaling, float horizontal_fraction,
            float vertical_fraction, bool fit_bounds)
      : scale_way_type(type)
      , is_proportional_scaling(is_proportional_scaling)
      , horizontal_fraction(horizontal_fraction)
      , vertical_fraction(vertical_fraction)
      , fit_bounds(fit_bounds) {}

  /**
   * @brief Constructor, with another icon fit object.
   *
   * @param[in] icon_fit  Another icon fit object.
   */
  IconFit(const IconFit& icon_fit)
      : scale_way_type(icon_fit.scale_way_type)
      , is_proportional_scaling(icon_fit.is_proportional_scaling)
      , horizontal_fraction(icon_fit.horizontal_fraction)
      , vertical_fraction(icon_fit.vertical_fraction)
      , fit_bounds(icon_fit.fit_bounds) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] icon_fit  Another icon fit object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  IconFit& operator = (const IconFit& icon_fit) {
    scale_way_type = icon_fit.scale_way_type;
    is_proportional_scaling = icon_fit.is_proportional_scaling;
    horizontal_fraction = icon_fit.horizontal_fraction;
    vertical_fraction = icon_fit.vertical_fraction;
    fit_bounds = icon_fit.fit_bounds;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] icon_fit  Another icon fit object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const IconFit& icon_fit) const {
    return (scale_way_type == icon_fit.scale_way_type &&
            is_proportional_scaling == icon_fit.is_proportional_scaling &&
            fabs(horizontal_fraction - icon_fit.horizontal_fraction) <= FLT_EPSILON &&
            fabs(vertical_fraction - icon_fit.vertical_fraction) <= FLT_EPSILON &&
            fit_bounds == icon_fit.fit_bounds);
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] icon_fit  Another icon fit object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const IconFit& icon_fit) const {
    return (scale_way_type != icon_fit.scale_way_type ||
            is_proportional_scaling != icon_fit.is_proportional_scaling ||
            fabs(horizontal_fraction - icon_fit.horizontal_fraction) > FLT_EPSILON ||
            fabs(vertical_fraction - icon_fit.vertical_fraction) > FLT_EPSILON ||
            fit_bounds != icon_fit.fit_bounds);
  }

  /**
   * @brief Set value.
   *
   * @param[in] type                     The circumstances under which the icon should be scaled inside
   *                                     the annotation rectangle. Please refer to values starting from
   *                                     @link IconFit::e_ScaleWayAlways @endlink and this should be one of these values.
   * @param[in] is_proportional_scaling  Indicates whether use proportional scaling or not.
   *                                     <b>true</b> means to fill the annotation rectangle exactly,
   *                                     without regard to its original aspect ratio (ratio of width to height).<br>
   *                                     <b>false</b> means scale the icon to scale the icon to fit the width or
   *                                     height of the annotation rectangle while maintaining the icon's
   *                                     original aspect ratio.
   * @param[in] horizontal_fraction      The horizontal fraction of left-over space to allocate
   *                                     at the left and bottom of the icon if the icon is scaled proportionally.
   *                                     Valid range: 0.0 to 1.0.
   * @param[in] vertical_fraction        The vertical fraction of left-over space to allocate
   *                                     at the left and bottom of the icon if the icon is scaled proportionally.
   *                                     Valid range: 0.0 to 1.0.
   * @param[in] fit_bounds               Indicates whether to scale button appearance to fit fully within bounds or not.
   *                                     <b>true</b> means that the button appearance should be scaled to fit fully
   *                                     within the bounds of the annotation without taking into consideration
   *                                     the line width of the border.
   *
   * @return None.
   */
  void Set(ScaleWayType type, bool is_proportional_scaling, float horizontal_fraction,
           float vertical_fraction, bool fit_bounds) {
      this->scale_way_type = type;
      this->is_proportional_scaling = is_proportional_scaling;
      this->horizontal_fraction = horizontal_fraction;
      this->vertical_fraction = vertical_fraction;
      this->fit_bounds = fit_bounds;
  }

  /**
   * @brief The circumstances under which the icon should be scaled inside the annotation rectangle.
   *        Please refer to values starting from @link IconFit::e_ScaleWayAlways @endlink and this should be one of these values.
   */
  ScaleWayType scale_way_type;
  /**
   * @brief A boolean value which indicates whether use proportional scaling or not.
   *
   * @details <b>true</b> means to fill the annotation rectangle exactly, without regard to its original aspect ratio
   *          (ratio of width to height).<br>
   *          <b>false</b> means scale the icon to scale the icon to fit the width or height of
   *          the annotation rectangle while maintaining the icon's original aspect ratio.
   */
  bool is_proportional_scaling;
  /**
   * @brief The horizontal fraction of left-over space to allocate at the left and bottom of the icon
   *
   * @details This entry is used only if the icon is scaled proportionally. Valid range: 0.0 to 1.0. <br>   */
  float horizontal_fraction;
  /**
   * @brief The vertical fraction of left-over space to allocate at the left and bottom of the icon
   *
   * @details This entry is used only if the icon is scaled proportionally. Valid range: 0.0 to 1.0. <br>   */
  float vertical_fraction;
  /**
   * @brief A boolean value that indicates whether to scale button appearance to fit fully within bounds or not.
   *
   * @details <b>true</b> indicates that the button appearance should be scaled to fit fully
   *          within the bounds of the annotation without taking into consideration the line width of the border.
   */
  bool fit_bounds;
};

/**
 * An annotation associates an object such as a note, sound, or movie with a location on a page of a PDF document,
 * or provides a way to interact with the user by means of the mouse and keyboard. PDF includes a wide variety of
 * standard annotation types.<br>
 * Class @link Annot @endlink is the base class for all kinds of PDF annotations. It offers the base functions to get/set
 * annotation's common properties, to move an annotation or reset appearance stream of an annotation.
 * For concrete annotation types, please refer to derived classes. To get the count of annotations or
 * get/add/remove an annotation, please refer to class pdf::PDFPage.<br>
 * This class object can also be used to construct objects of other classes in order to do some more operation
 * in annotation or access specified information of annotation:
 * <ul>
 * <li>To access additional actions, please construct an @link actions::AdditionalAction @endlink object with annotation object.
 *     Only a few types of annotations may have additional action. For more details, please refer to
 *     class @link actions::AdditionalAction @endlink.</li>
 * <li>To search text in annotation, please construct a @link pdf::TextSearch @endlink object with annotation object.
 *     The searching can only support some types of annotations. For more details, please refer to
 *     class @link pdf::TextSearch @endlink.</li>
 * </ul>
 *
 * @note Currently, following kind of functions only support note, highlight, underline, strikeout, squiggly, link,
 *       square, circle, free text, stamp, caret, ink, line, polygon, polyline, file attachment, pop-up,
 *       widget, screen, PSInk, redact annotations:
 *       <ul>
 *       <li>All the "set" functions in class @link Annot @endlink.</li>
 *       <li>Functions @link Annot::Move @endlink, @link Annot::ResetAppearanceStream @endlink,
 *           @link Annot::RemoveProperty @endlink.</li>
 *       </ul>
 *
 * @see @link pdf::PDFPage @endlink
 * @see @link actions::AdditionalAction @endlink
 * @see @link pdf::TextSearch @endlink
 */
class Annot : public Base {
 public:
  /**
   * @brief Enumeration for PDF annotation type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Type {
    /** @brief Annotation type: unknown.*/
    e_UnknownType    = 0,
    /**
   @brief Annotation type: note annotation, which is just "Text" annotation -
          one of standard annotation in <PDF reference 1.7>.
     */
    e_Note           = 1,
    /** @brief Annotation type: link annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Link           = 2,
    /** @brief Annotation type: free text annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_FreeText       = 3,
    /** @brief Annotation type: line annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Line           = 4,
    /** @brief Annotation type: square annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Square         = 5,
    /** @brief Annotation type: circle annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Circle         = 6,
    /** @brief Annotation type: polygon annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Polygon        = 7,
    /** @brief Annotation type: polyline annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_PolyLine       = 8,
    /** @brief Annotation type: highlight annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Highlight      = 9,
    /** @brief Annotation type: underline annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Underline      = 10,
    /** @brief Annotation type: squiggly annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Squiggly       = 11,
    /** @brief Annotation type: strikeout annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_StrikeOut      = 12,
    /** @brief Annotation type: stamp annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Stamp          = 13,
    /** @brief Annotation type: caret annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Caret          = 14,
    /** @brief Annotation type: ink annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Ink            = 15,
    /** @brief Annotation type: pressure sensitive ink annotation.*/
    e_PSInk          = 16,
    /** @brief Annotation type: file attachment annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_FileAttachment = 17,
    /** @brief Annotation type: sound annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Sound          = 18,
    /** @brief Annotation type: movie annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Movie          = 19,
    /**
   @brief Annotation type: widget annotation. One of standard annotation in <PDF reference 1.7>.
   @note Foxit PDF SDK treats widget annotation as form control.
     */
    e_Widget         = 20,
    /** @brief Annotation type: screen annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Screen         = 21,
    /** @brief Annotation type: printer's mark annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_PrinterMark    = 22,
    /** @brief Annotation type: trap network annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_TrapNet        = 23,
    /** @brief Annotation type: watermark annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Watermark      = 24,
    /** @brief Annotation type: 3D annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_3D             = 25,
    /** @brief Annotation type: pop-up annotation. One of standard annotation in <PDF reference 1.7>.*/
    e_Popup          = 26,
    /** @brief Annotation type: redact annotation.*/
    e_Redact         = 27
  } Type;
  
  /**
   * @brief Enumeration for PDF annotation flags.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _Flags {
    /**
   @brief Annotation flag: invisible.
   @details If set, do not display the annotation if it does not belong to one of the standard annotation types
            and no annotation handler is available. If clear, display such an non-standard annotation
            using an appearance stream specified by its appearance dictionary, if any.
     */
    e_FlagInvisible      = 0x0001,
    /**
   @brief Annotation flag: hidden.
   @details If set, do not display or print the annotation or allow it to interact with the user,
            regardless of its annotation type or whether an annotation handler is available.
     */
    e_FlagHidden         = 0x0002,
    /**
   @brief Annotation flag: print.
   @details If set, print the annotation when the page is printed. If clear, never print the annotation,
            regardless of whether it is displayed on the screen. This can be useful, for example,
            for annotations representing interactive pushbuttons, which would serve no meaningful purpose
            on the printed page.
     */
    e_FlagPrint          = 0x0004,
    /**
   @brief Annotation flag: no zoom.
   @details If set, do not scale the annotation's appearance to match the magnification of the page.
            The location of the annotation on the page (defined by the upper-left corner of its annotation rectangle)
            remains fixed, regardless of the page magnification. See below for further discussion.
     */
    e_FlagNoZoom         = 0x0008,
    /**
   @brief Annotation flag: no rotate.
   @details If set, do not rotate the annotation's appearance to match the rotation of the page.
            The upper-left corner of the annotation rectangle remains in a fixed location on the page,
            regardless of the page rotation.
     */
    e_FlagNoRotate       = 0x0010,
    /**
   @brief Annotation flag: no view.
   @details If set, do not display the annotation on the screen or allow it to interact with the user.
            The annotation may be printed (depending on the setting of flag
            @link Annot::e_FlagPrint @endlink) but should be considered hidden
            for purposes of on-screen display and user interaction.
     */
    e_FlagNoView         = 0x0020,
    /**
   @brief Annotation flag: read only.
   @details If set, do not allow the annotation to interact with the user. The annotation may be displayed or printed
            (depending on the settings of flags @link Annot::e_FlagNoView @endlink and @link Annot::e_FlagPrint @endlink)
            but should not respond to mouse clicks or change its appearance in response to mouse motions.
   @note This flag is ignored for widget annotations; its function is subsumed by flag
         @link interform::Field::e_FlagReadOnly @endlink of related form field.
     */
    e_FlagReadOnly       = 0x0040,
    /**
   @brief Annotation flag: locked.
   @details If set, do not allow the annotation to be deleted or its properties (including position and size)
            to be modified by the user. However, this flag does not restrict changes to the annotation's contents,
            such as the value of a form field.
     */
    e_FlagLocked         = 0x0080,
    /**
   @brief Annotation flag: toggle no view.
   @details If set, invert the interpretation of the NoView flag for certain events. A typical use is to
            have an annotation that appears only when a mouse cursor is held over it.
     */
    e_FlagToggleNoView   = 0x0100,
    /**
   @brief Annotation flag: locked contents.
   @details If set, do not allow the contents of the annotation to be modified by the user.
            This flag does not restrict deletion of the annotation or changes to other annotation properties,
            such as position and size.
     */
    e_FlagLockedContents = 0x0200
  } Flags;
  
  /**
   * @brief Enumeration for PDF annotation highlighting mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _HighlightingMode {
    /** @brief Highlighting mode: No highlighting. */
    e_HighlightingNone    = 0,
    /** @brief Highlighting mode: Invert, which is to invert the contents of the annotation rectangle. */
    e_HighlightingInvert  = 1,
    /** @brief Highlighting mode: Outline, which is to invert the annotation's border. */
    e_HighlightingOutline = 2,
    /** @brief Highlighting mode: Push, which is to display the annotation's down appearance, if any. */
    e_HighlightingPush    = 3,
    /** @brief Highlighting mode: Toggle. This is only useful for widget annotation. */
    e_HighlightingToggle  = 4
  } HighlightingMode;
  
  /**
   * @brief Enumeration for some PDF annotation property.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Property {
    /** @brief Annotation property: modified date. */
    e_PropertyModifiedDate = 0,
    /**
   @brief Annotation property: creation date.
   @details Only markup annotations can have creation date property.
     */
    e_PropertyCreationDate = 1,
    /** @brief Annotation property: border color. */
    e_PropertyBorderColor  = 2,
    /**
   @brief Annotation property: fill color
   @details Only following types of annotations can have fill color property:<br>
            square, circle, free text, line, polygon, polyline, redact.
     */
    e_PropertyFillColor    = 3
  } Property;
  
  /**
   * @brief Enumeration for annotation's MK dictionary (an appearance characteristics) entry.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MKEntry {
    /** @brief Rotation entry. "R" in MK dictionary. */
    e_MKEntryRotation = 0,
    /** @brief Border color entry. "BC" in MK dictionary. */
    e_MKEntryBorderColor = 1,
    /** @brief Background color entry. "BG" in MK dictionary. */
    e_MKEntryBackgroundColor = 2,
    /**
   @brief Normal caption entry. "CA" in MK dictionary.
   @note Only applicable for widget annotation associated with pushbutton field, check box field or radio button field.
     */
    e_MKEntryNormalCaption = 3,
    /**
   @brief Rollover caption entry. "RC" in MK dictionary.
   @note Only applicable for widget annotation associated with pushbutton field.
     */
    e_MKEntryRolloverCaption = 4,
    /**
   @brief Down caption (or alternate caption) entry. "AC" in MK dictionary.
   @note Only applicable for widget annotation associated with pushbutton field.
     */
    e_MKEntryDownCaption = 5,
    /**
   @brief Normal icon entry. "I" in MK dictionary.
   @note Only applicable for widget annotation associated with pushbutton field.
     */
    e_MKEntryNormalIcon = 6,
    /**
   @brief Rollover icon entry. "RI" in MK dictionary.
   @note Only applicable for widget annotation associated with pushbutton field.
     */
    e_MKEntryRolloverIcon = 7,
    /**
   @brief Down icon (or alternate icon) entry. "IX" in MK dictionary.
   @note Only applicable for widget annotation associated with pushbutton field.
     */
    e_MKEntryDownIcon = 8,
    /**
   @brief Icon fit information entry. "IF" in MK dictionary.
   @note Only applicable for widget annotation associated with pushbutton field.
     */
    e_MKEntryIconFit = 9,
    /**
   @brief Icon and caption relation entry. "TP" in MK dictionary.
   @note Only applicable for widget annotation associated with pushbutton field.
         This is used to specify where to position the text of widget annotation's mk caption
         relative to widget annotation's mk icon.
     */
    e_MKEntryIconCaptionRelation = 10
  } MKEntry;
  
  /**
   * @brief Enumeration for icon and caption relative position in annotation's MK dictionary.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MKIconCaptionRelation {
    /** @brief No icon; captin only. */
    e_MKRelationNoIcon = 0,
    /** @brief No caption; icon only. */
    e_MKRelationNoCaption = 1,
    /** @brief Caption below the icon. */
    e_MKRelationCaptionBelowIcon = 2,
    /** @brief Caption above the icon. */
    e_MKRelationCaptionAboveIcon = 3,
    /** @brief Caption to the right of the icon. */
    e_MKRelationCaptionRight = 4,
    /** @brief Caption to the left of the icon. */
    e_MKRelationCaptionLeft = 5,
    /** @brief Caption overlaid directly on the icon. */
    e_MKRelationCaptionOvrlayOnIcon = 6
  } MKIconCaptionRelation;
  
  /**
   * @brief Enumeration for the type of annotation's appearance.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _AppearanceType {
    /** @brief Annotation's normal appearance. */
    e_AppearanceTypeNormal = 0,
    /** @brief Annotation's rollover appearance. */
    e_AppearanceTypeRollover = 1,
    /** @brief Annotation's down appearance. */
    e_AppearanceTypeDown = 2
  } AppearanceType;
  

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Annot(FS_HANDLE handle);
  /**
   * @brief Constructor, with PDF page and annotation's PDF dictionary.
   *
   * @param[in] page        A valid PDF page.
   * @param[in] annot_dict  An annotation's PDF dictionary. It should represent an annotation and should be
   *                        in the PDF page specified by parameter <i>page</i>.
   */
  Annot(const PDFPage& page, objects::PDFDictionary* annot_dict);
#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Constructor, with another annotation object.
   *
   * @param[in] annot  Another annotation object.
   */
  Annot(const Annot& annot);
#endif
  /** @brief Constructor. */
  Annot() {}
#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Assign operator.
   *
   * @param[in] annot  Another annotation object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Annot& operator = (const Annot& annot);
#endif
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another annotation object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator ==(const Annot& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another annotation object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Annot& other) const;
#ifndef __EMSCRIPTEN_RENDER__
  /** @brief Destructor. */
  virtual ~Annot();
#endif
  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the related PDF page.
   *
   * @return A PDF page object which is the related PDF page.
   */
  PDFPage GetPage() const;
  /**
   * @brief Check if current annotation is a markup annotation.
   *
   * @return <b>true</b> means current annotation is a markup annotation, while <b>false</b> means current annotation
   *         is not a markup annotation.
   */
  bool IsMarkup() const;
  /**
   * @brief Get actual annotation type of current annotation.
   *
   * @return Annotation type. Please refer to values starting from @link Annot::e_Note @endlink and this would be one of these values.
   */
  Type GetType() const;
  /**
   * @brief Get the index of current annotation in the page which current annotation belongs to.
   *
   * @return The index value, starting from 0.
   */
  int GetIndex() const;
  /**
   * @brief Get content.
   *
   * @return Content string.
   */
  WString GetContent() const;
  /**
   * @brief Set content.
   *
   * @details For free text annotation and line annotation (which has enabled caption),
   *          they would show content in their appearance. So for these kind of annotations, this property would
   *          have effect on annotation's appearance. If user wants the effect to be shown in the appearance of
   *          these kind of annotations, please call function @link Annot::ResetAppearanceStream @endlink after
   *          setting new content.
   *
   * @param[in] content  New content string to be set.
   *
   * @return None.
   */
  void SetContent(const WString& content);
  /**
   * @brief Get last modified date time.
   *
   * @return A date and time object that receives the last modified date time.
   *         If there is no modified date time information, a date and time object with all 0 values would be returned.
   */
  DateTime GetModifiedDateTime() const;
  /**
   * @brief Set last modified date time.
   *
   * @param[in] date_time  The data time to be set. It should contain valid date time data.
   *
   * @return None.
   */
  void SetModifiedDateTime(const DateTime& date_time);
  /**
   * @brief Get annotation flags.
   *
   * @return The annotation flags. Please refer to values starting from @link Annot::e_FlagInvisible @endlink and
   *         this would be one or a combination of these values. 0 means no annotation flag.
   */
  uint32 GetFlags() const;
  /**
   * @brief Set annotation flags.
   *
   * @param[in] flags  The annotation flags. It could be 0, or one or a combination of
   *                   values starting from @link Annot::e_FlagInvisible @endlink.
   *
   * @return None.
   */
  void SetFlags(uint32 flags);
  /**
   * @brief Get unique ID.
   *
   * @return Unique ID string.
   */
  WString GetUniqueID() const;
  /**
   * @brief Set unique ID.
   *
   * @param[in] unique_id  New unique ID string to be set.
   *
   * @return None.
   */
  void SetUniqueID(const WString& unique_id);
  /**
   * @brief Get rectangle, in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @return The annotation rectangle.
   *         If there is no rectangle information, a RectF object with all 0 values would be returned.
   */
  RectF GetRect() const;

  /**
   * @brief Get the display matrix, from [PDF coordinate system] (@ref PDFPage) to
   *        targeted device coordinate system.
   *
   * @details Display matrix of current annotation can be used with annotation's rectangle to
   *          calculate the real area of annotation in target device coordinate system.
   *
   * @param[in] page_display_matrix  The transformation matrix. Usually this is returned by function
   *                                 @link PDFPage::GetDisplayMatrix @endlink. 
   *
   * @return The display matrix of current annotation.
   */
  Matrix GetDisplayMatrix(const Matrix& page_display_matrix);

  /**
   * @brief Move current annotation to a new position, specified by a new rectangle
   *        in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @param[in] rect  New rectangle to specify the new position where current annotation is to be moved to.
   *                  It should be valid in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Move(const RectF& rect);
  /**
   * @brief Get border information.
   *
   * @details This property has effect on annotation's appearance. For an annotation which does not
   *          have border information, the default border information will be returned:<br>
   *          border width = 1, border style = @link BorderInfo::e_Solid @endlink,
   *          border cloud intensity = 0, border dash phase = 0, border dashes array is an empty array.
   *          Attention: among supported annotation types (please refer to "Note" comment part of class @link Annot @endlink),
   *          this property will not have effect on appearance of these annotations:
   *          note, highlight, underline, strikeout, squiggly, stamp, caret, popup, file attachment, PSInk, redact.
   *          For ink annotation, only border width will have effect on ink annotation's appearance.
   *
   * @return A border information object that received the border information.
   *         If not find any border information, the default border information will be returned as described
   *         in "Details" part.
   */
  BorderInfo GetBorderInfo() const;
  /**
   * @brief Set border information.
   *
   * @details This property has effect on annotation's appearance. If user wants the new border information has effect
   *          on annotation's appearance, please call function @link Annot::ResetAppearanceStream @endlink after setting
   *          the new border information.<br>
   *          Attention: among supported annotation types (please refer to "Note" comment part of class @link Annot @endlink),
   *          this property will not have effect on appearance of these annotations:
   *          note, highlight, underline, strikeout, squiggly, stamp, caret, popup, file attachment, PSInk, redact.
   *          For ink annotation, only border width will have effect on ink annotation's appearance.
   *
   * @param[in] border  New border information to be set. It should be a valid border information object.
   *                    If any value of parameter <i>border</i> is invalid, this function will fail to set new border
   *                    information to current annotation.
   *
   * @return None.
   */
  void SetBorderInfo(const BorderInfo& border);
  /**
   * @brief Get border color.
   *
   * @details This property has effect on annotation's appearance.
   *
   * @return The border color. Format: 0xRRGGBB.
   *         If no border color can be found, 0x000000 will be returned.
   */
  RGB GetBorderColor() const;
  /**
   * @brief Set border color.
   *
   * @details This property has effect on annotation's appearance. If user wants the new border color has effect on
   *          annotation's appearance, please call function @link Annot::ResetAppearanceStream @endlink after setting the
   *          new border color.
   *
   * @param[in] color  New border color to be set. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetBorderColor(RGB color);
  /**
   * @brief Reset appearance stream.
   *
   * @details Annotation's appearance is stored as stream in PDF document.
   *          When any appearance related property is changed by corresponding setting functions,
   *          if user wants the effect to be shown in annotation's appearance, current function should be called.<br>
   *          Please check "Note" part in the comment of Annot to see which types of annotations can be
   *          reset appearance by current function and also check comment in classes of these annotations to see if
   *          any property is required before resetting appearance stream.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ResetAppearanceStream();
  /**
   * @brief Get annotation rectangle in device coordinate system.
   *
   * @details This is a useful function to get the device rectangle of an annotation,
   *          but not support pop-up annotation.<br>
   *          For the rectangle conversion, the result rectangle is always "normalized", which is
   *          using device coordinate system: left is always smaller than right, and top is always smaller than bottom.
   *
   * @param[in] matrix             A matrix used to transform from [PDF coordinate system] (@ref pdf::PDFPage) to
   *                               device coordinate system. Usually, this is returned by function
   *                               @link pdf::PDFPage::GetDisplayMatrix @endlink and also used for rendering.
   *
   * @return The annotation rectangle in device coordinate system.
   *         If there is no rectangle information, a RectI object with all 0 values would be returned.
   */
  RectI GetDeviceRect(const Matrix& matrix);
  /**
   * @brief Get annotation's dictionary object.
   *
   * @return Annotation's dictionary.
   */
  objects::PDFDictionary* GetDict() const;

  /**
   * @brief Whether current annotation has the specified annotation's property.
   *
   * @param[in] property  Property name. Please refer to values starting from @link Annot::e_PropertyModifiedDate @endlink
   *                      and this should be one of these values.
   *
   * @return <b>true</b> means current annotation has the specified property,
   *         while <b>false</b> means current annotation does not have the specified property.
   */
  bool HasProperty(Property property) const;

  /**
   * @brief Remove a specified annotation's property.
   *
   * @details This function can be used to remove some optional properties of an annotation.
   *          When appearance related property is removed successfully, such as
   *          @link Annot::e_PropertyBorderColor @endlink and @link Annot::e_PropertyFillColor @endlink,
   *          user should call function @link Annot::ResetAppearanceStream @endlink to make effect on
   *          annotation's appearance.
   *
   * @param[in] property  Property name. Please refer to values starting from @link Annot::e_PropertyModifiedDate @endlink
   *                      and this should be one of these values.
   *
   * @return <b>true</b> means remove the specified property successfully, or current annotation supports the property
   *         but does not have the property.<br>
   *         <b>false</b> means current annotation does not support to have the specified property, or
   *         current annotation cannot be removed specified property.
   */
  bool RemoveProperty(Property property);

  /**
   * @brief Get the PDF dictionary of annotation's optional content.
   *
   * @return The PDF dictionary of annotation's optional content.
   */
  objects::PDFDictionary* GetOptionalContent() const;

  /**
   * @brief Get annotation's appearance stream with specified type and state.
   *
   * @details For more details, please refer to "AP" and "AS" entries
   *          in "TABLE 8.15 Entries common to all annotation dictionaries" in <PDF reference 1.7>.
   *
   * @param[in] type              Type of annotation's appearance. Please refer to values starting from
   *                              @link Annot::e_AppearanceTypeNormal @endlink and this should be one of these values.
   * @param[in] appearance_state  Annotation's appearance state, which is used to select
   *                              the applicable appearance stream from an appearance sub-dictionary.
   *                              If this is an empty string, Foxit PDF SDK will choose the appearance state
   *                              specified by the "AS" (Appearance State) entry in the annotation dictionary.
   *
   * @return The specified annotation's appearance stream.
   */
  objects::PDFStream* GetAppearanceStream(AppearanceType type, const char* appearance_state = "") const;
};

/** This class represents an array of annotation objects. */
FSDK_DEFINE_ARRAY(AnnotArray, Annot)

/** This class represents shading color which is used for Type 2 (Axial) Shadings. */
class ShadingColor FS_FINAL : public Object {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] firstcolor   First color used for shading color. Format: 0xAARRGGBB.
   * @param[in] secondcolor  Second color used for shading color. Format: 0xAARRGGBB.
   */
  ShadingColor(ARGB firstcolor, ARGB secondcolor)
      : first_color(firstcolor)
      , second_color(secondcolor) {}

  /** @brief Constructor. */
  ShadingColor()
      : first_color(0xFFFFFFFF)
      , second_color(0xFFFFFFFF) {}

  /**
   * @brief Constructor, with another shading color object.
   *
   * @param[in] shading_color  Another shading color object.
   */
  ShadingColor(const ShadingColor& shading_color)
      : first_color(shading_color.first_color)
      , second_color(shading_color.second_color) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] shading_color  Another shading color object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ShadingColor& operator = (const ShadingColor& shading_color) {
    this->first_color = shading_color.first_color;
    this->second_color = shading_color.second_color;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] shading_color  Another shading color object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const ShadingColor& shading_color) const {
    return (first_color == shading_color.first_color && second_color == shading_color.second_color);
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] shading_color  Another shading color object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const ShadingColor& shading_color) const {
    return (first_color != shading_color.first_color || second_color != shading_color.second_color);
  }

  /**
   * @brief Set value.
   *
   * @param[in] firstcolor   First color used for shading color. Format: 0xAARRGGBB.
   * @param[in] secondcolor  Second color used for shading color. Format: 0xAARRGGBB.
   *
   * @return None.
   */
  void Set(ARGB firstcolor, ARGB secondcolor) {
    this->first_color = firstcolor;
    this->second_color = secondcolor;
  }

  /** @brief First color used for shading. Format: 0xAARRGGBB. */
  ARGB first_color;
  /** @brief Second color used for shading. Format: 0xAARRGGBB. */
  ARGB second_color;
};

/**
 * This class represents a callback object as customized annotation icon provider.
 * All the functions in this class are used as callback functions. Pure virtual functions should be implemented
 * by user and user can also choose to implement some or all the reset virtual functions when necessary.
 * Icon provider can only be used for note, file attachment, stamp annotations. <br>
 * Icon provider's ID and version are treated as the name of the icon provider, so please offer different
 * "ID + version" for different icon providers by callback functions
 * @link IconProviderCallback::GetProviderID @endlink and @link IconProviderCallback::GetProviderVersion @endlink.
 */
class IconProviderCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;
  /**
   * @brief A callback function used to get provider ID.
   *
   * @details Icon provider's ID and version are treated as the name of the icon provider, so please offer different
   *          "ID + version" for different icon providers.
   *
   * @return The provider ID.
   */
  virtual String GetProviderID() {
    return String();
  }
  /**
   * @brief A callback function used to get provider version.
   *
   * @details Icon provider's ID and version are treated as the name of the icon provider, so please offer different
   *          "ID + version" for different icon providers.
   *
   * @return Version string.
   */
  virtual String GetProviderVersion() {
    return String();
  }
  /**
   * @brief A callback function used to check if current icon provider supports icon for a specified type.
   *
   * @param[in] annot_type  The annotation type. It should be one of @link Annot::e_Note @endlink,
   *                        @link Annot::e_FileAttachment @endlink and @link Annot::e_Stamp @endlink.
   * @param[in] icon_name   Icon name of the annotation.
   *
   * @return <b>true</b> means current icon provider supports the specified icon, while <b>false</b> means not support.
   */
  virtual bool HasIcon(Annot::Type annot_type, const char* icon_name) {
    return false;
  }
  /**
   * @brief A callback function used to check if current icon provider supports to change color for a specified type.
   *
   * @param[in] annot_type  The annotation type. It should be one of @link Annot::e_Note @endlink,
   *                        @link Annot::e_FileAttachment @endlink and @link Annot::e_Stamp @endlink.
   * @param[in] icon_name   Icon name of the annotation.
   *
   * @return <b>true</b> means current icon provider supports to change color for a specified icon type,
   *         while <b>false</b> means not support.
   */
  virtual bool CanChangeColor(Annot::Type annot_type, const char* icon_name) {
    return false;
  }
#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief A callback function used to get the icon as PDF page contents for a specified type.
   *
   * @param[in] annot_type  The annotation type. It should be one of @link Annot::e_Note @endlink,
   *                        @link Annot::e_FileAttachment @endlink and @link Annot::e_Stamp @endlink.
   * @param[in] icon_name   Icon name of the annotation.
   * @param[in] color       The icon color of the annotation. Format: 0xAARRGGBB.
   *
   * @return A PDF page object whose content would be used as the icon.
   */
  virtual PDFPage GetIcon(Annot::Type annot_type, const char* icon_name, ARGB color);
#endif
  /**
   * @brief A callback function used to get the shading colors if current icon provider supports for a specified type.
   *        Currently, only support Type-2 shading settings with two color values.
   *
   * @param[in] annot_type          The annotation type. It should be one of @link Annot::e_Note @endlink,
   *                                @link Annot::e_FileAttachment @endlink and @link Annot::e_Stamp @endlink.
   * @param[in] icon_name           Icon name of the annotation.
   * @param[in] referenced_color    Referenced color. Format: 0xRRGGBB.
   * @param[in] shading_index       Index color of shading, starting from 0.
   *                                If shading colors are more than one, this function will be called multiple times.
   * @param[out] out_shading_color  Output parameter that receives the two shading color value.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool GetShadingColor(Annot::Type annot_type, const char* icon_name,
                               RGB referenced_color, int shading_index, ShadingColor& out_shading_color) {
    return false;
  }
  /**
   * @brief A callback function used to get the width for display of a specified icon, in device size(pixel normally).
   *
   *
   * @param[in] annot_type  The annotation type. It should be one of @link Annot::e_Note @endlink,
   *                        @link Annot::e_FileAttachment @endlink and @link Annot::e_Stamp @endlink.
   * @param[in] icon_name   Icon name of the annotation.
   *
   * @return The width for display.
   */
  virtual float GetDisplayWidth(Annot::Type annot_type, const char* icon_name) {
    return 0.0f;
  }
  /**
   * @brief A callback function used to get the height for display of a specified icon, in device size(pixel normally).
   *
   *
   * @param[in] annot_type  The annotation type. It should be one of @link Annot::e_Note @endlink,
   *                        @link Annot::e_FileAttachment @endlink and @link Annot::e_Stamp @endlink.
   * @param[in] icon_name   Icon name of the annotation.
   *
   * @return The height for display.
   */
  virtual float GetDisplayHeight(Annot::Type annot_type, const char* icon_name) {
    return 0.0f;
  }

 protected:
  ~IconProviderCallback() {}
};

class Markup;
/** This class represents an array of markup annotation objects. */
FSDK_DEFINE_ARRAY(MarkupArray, Markup)

/**
 * Markup annotations are used primarily to mark up PDF documents. These annotations have text that
 * appears as part of the annotation and may be displayed in other ways by a viewer application, such as
 * in a Comments pane.<br>
 * Class @link annots::Markup @endlink is derived from class @link Annot @endlink, and is also the base class for all PDF markup annotations.
 * It offers the base functions to get/set markup annotation's common properties.
 * For concrete markup annotation types, please refer to derived classes. <br>
 * Function @link Annot::IsMarkup @endlink can be used to judge if an annotation is a markup annotation.
 *
 * @note Currently, following kind of functions only support note, highlight, underline, strikeout, squiggly,
 *       square, circle, free text, stamp, caret, ink, line, polygon, polyline, file attachment annotations:
 *       <ul>
 *       <li>All the "set" functions in class @link Markup @endlink.</li>
 *       <li>Function @link Annot::ResetAppearanceStream @endlink (inherited from @link Markup @endlink's parent class).</li>
 *       </ul>
 *
 * @see @link Annot @endlink
 */
class Markup : public Annot {
 public:
  /**
   * @brief Enumeration for markup annotation's state model.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _StateModel {
    /** @brief Markup annotation state model: marked. */
    e_StateModelMarked = 1,
    /** @brief Markup annotation state model: review. */
    e_StateModelReview = 2
  } StateModel;
  
  /**
   * @brief Enumeration for markup annotation's state.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _State {
    /**
   @brief (Used for @link Markup::e_StateModelMarked @endlink)
          The annotation has been marked by the user.
     */
    e_StateMarked    = 1,
    /**
   @brief (Used for @link Markup::e_StateModelMarked @endlink)
          The annotation has not been marked by the user.
     */
    e_StateUnmarked  = 2,
    /**
   @brief (Used for @link Markup::e_StateModelReview @endlink)
          The user agrees with the change.
     */
    e_StateAccepted  = 3,
    /**
   @brief (Used for @link Markup::e_StateModelReview @endlink)
          The user disagrees with the change.
     */
    e_StateRejected  = 4,
    /**
   @brief (Used for @link Markup::e_StateModelReview @endlink)
          The change has been cancelled.
     */
    e_StateCancelled = 5,
    /**
   @brief (Used for @link Markup::e_StateModelReview @endlink)
          The change has been completed.
     */
    e_StateCompleted = 6,
    /**
   @brief (Used for @link Markup::e_StateModelReview @endlink)
          The user has indicated nothing about the change.
     */
    e_StateNone      = 7
  } State;
  
  /**
   * @brief Enumeration for line ending style.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _EndingStyle {
    /** @brief No special line ending.*/
    e_EndingStyleNone = 0,
    /** @brief A square filled with the annotation's interior color if any. */
    e_EndingStyleSquare = 1,
    /** @brief A circle filled with the annotation's interior color if any.*/
    e_EndingStyleCircle = 2,
    /** @brief A diamond shape filled with the annotation's interior color if any.*/
    e_EndingStyleDiamond = 3,
    /** @brief Two short lines meeting in an acute angle to form an open arrowhead.*/
    e_EndingStyleOpenArrow = 4,
    /**
   @brief Two short lines meeting in an acute angle as in the OpenArrow style and
          connected by a third line to form a triangular closed arrowhead filled with
          the annotation's interior color if any.
     */
    e_EndingStyleClosedArrow = 5,
    /** @brief A short line at the endpoint perpendicular to the line itself.*/
    e_EndingStyleButt = 6,
    /** @brief Two short lines in the reverse direction from OpenArrow.*/
    e_EndingStyleROpenArrow = 7,
    /** @brief A triangular closed arrowhead in the reverse direction from ClosedArrow.*/
    e_EndingStyleRClosedArrow = 8,
    /** @brief A short line at the endpoint approximately 30 degrees clockwise from perpendicular to the line itself.*/
    e_EndingStyleSlash = 9
  } EndingStyle;
  
  /**
   * @brief Enumeration for annotation's measure type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MeasureType {
    /** @brief Measurement of change along the x axis. */
    e_MeasureTypeX = 0,
    /** @brief Measurement of change along the y axis. */
    e_MeasureTypeY = 1,
    /** @brief Measurement of distance in any direction. */
    e_MeasureTypeD = 2,
    /** @brief Measurement of area. */
    e_MeasureTypeA = 3,
    /** @brief Measurement of angles. */
    e_MeasureTypeT = 4,
    /** @brief Measurement of the slope of a line. */
    e_MeasureTypeS = 5
  } MeasureType;
  

  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Markup(const Annot& annot);
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Markup(FS_HANDLE handle);
  /** @brief Constructor. */
  Markup() {}

  /** @brief Destructor. */
   ~Markup() {}

  /**
   * @brief Get related pop-up annotation.
   *
   * @details Most markup annotations can have a pop-up annotation to show their content, except sound and free text
   *          annotations:
   *          <ul>
   *          <li>For sound annotation, it does not have a pop-up annotation.</li>
   *          <li>For free text annotation, it shows text directly on the page, so no need to have a pop-up annotation.
   *          </li>
   *          </ul>
   *          Though, in some special(or error) PDF document, sound or free text annotation may have
   *          a pop-up annotation, they still do not need a pop-up annotation.<br>
   *
   * @return The related pop-up annotation. If the return value of function @link Annot::IsEmpty @endlink
   *         (inherited from @link Popup @endlink's parent class) for the returned pop-up annotation is <b>true</b>,
   *         that means current markup annotation does not have a pop-up annotation.
   */
   Popup GetPopup();
  /**
   * @brief Set related pop-up annotation.
   *
   * @details Most markup annotations can have a pop-up annotation to show their content, except sound and free text
   *          annotations:<br>
   *          <ul>
   *          <li>For sound annotation, it does not have a pop-up annotation.</li>
   *          <li>For free text annotation, it shows text directly on the page, so no need to have a pop-up annotation.
   *          </li>
   *          </ul>
   *          So, this function does not allow to set pop-up annotation to sound and free text annotation.
   *
   * @param[in] popup  A valid pop-up annotation to be set to current markup annotation.
   *
   * @return None.
   */
   void SetPopup(const Popup& popup);
  /**
   * @brief Get title string.
   *
   * @return Title string.
   */
   WString GetTitle() const;
  /**
   * @brief Set title string.
   *
   * @param[in] title  New title string to be set.
   *
   * @return None.
   */
   void SetTitle(const WString& title);
  /**
   * @brief Get subject string.
   *
   * @return Subject string.
   */
   WString GetSubject() const;
  /**
   * @brief Set subject string.
   *
   * @param[in] subject  New subject string to be set.
   *
   * @return None.
   */
   void SetSubject(const WString& subject);
  /**
   * @brief Get opacity value.
   *
   * @details This property has effect on markup annotation's appearance.
   *
   * @return The opacity value. Valid range: 0.0 to 1.0.
   *         0.0 means full transparency and 1.0 means full opaque.
   */
   float GetOpacity() const;
  /**
   * @brief Set opacity value.
   *
   * @details This property has effect on markup annotation's appearance. If user wants the new opacity value has
   *          effect on annotation's appearance, please call function @link Annot::ResetAppearanceStream @endlink after
   *          setting the new opacity value.
   *
   * @param[in] opacity  The new opacity value. Valid range: 0.0 to 1.0 .
   *                     0.0 means full transparency and 1.0 means full opaque.
   *
   * @return None.
   */
   void SetOpacity(float opacity);
  /**
   * @brief Get intent name.
   *
   * @details Following annotation types have predefined intent name:<br>
   *          <ul>
   *          <li>Free text annotation's predefined intent name: "FreeTextCallout", "FreeTextTypewriter".
   *              If no intent name is used, free text annotation would be shown as a text box.
   *          </li>
   *          <li>Line annotation's predefined intent name: "LineArrow", "LineDimension".
   *              If no intent name is used, line annotation would be shown as a common line.
   *          </li>
   *          <li>Polygon's predefined intent name: "PolygonCloud", "PolygonDimension".
   *              If no intent name is used, polygon annotation would be shown as a common polygon.
   *          </li>
   *          <li>Polyline annotation's predefined intent name: "PolyLineDimension".
   *              If no intent name is used, polyline annotation would be shown as a common polyline.
   *          </li>
   *          </ul>
   *
   * @return The intent name string.
   */
   String GetIntent() const;
  /**
   * @brief Set intent name.
   *
   * @details Following annotation types have predefined intent name:<br>
   *          <ul>
   *          <li>Free text annotation's predefined intent name: "FreeTextCallout", "FreeTextTypewriter".
   *              If no intent name is used, free text annotation would be shown as a text box.
   *          </li>
   *          <li>Line annotation's predefined intent name: "LineArrow", "LineDimension".
   *              If no intent name is used, line annotation would be shown as a common line.<br>
   *              If a line annotation's intent is to be set to "LineArrow", the line annotation's line ending styles
   *              will be @link Markup::e_EndingStyleNone @endlink for start point and
   *              @link Markup::e_EndingStyleOpenArrow @endlink for end point by default.
   *          </li>
   *          <li>Polygon's predefined intent name: "PolygonCloud", "PolygonDimension".
   *              If no intent name is used, polygon annotation would be shown as a common polygon.<br>
   *              If a polygon annotation's intent is to be set to "PolygonCloud", the polygon annotation's
   *              border style will be changed to @link BorderInfo::e_Cloudy @endlink
   *              and border cloud intensity will be set to 2 by default.
   *          </li>
   *          <li>Polyline annotation's predefined intent name: "PolyLineDimension".
   *              If no intent name is used, polyline annotation would be shown as a common polyline.<br>
   *          </li>
   *          </ul>
   *          If supported predefined intent name has been set to corresponding type of annotation, user should call
   *          function @link Annot::ResetAppearanceStream @endlink to make the effect on annotation's appearance.
   *
   * @param[in] intent  New intent name string to be set. If it is an empty string, that means the intent property
   *                    will not be used.<br>
   *                    Some annotation type have predefined intent name, please refer to "Details" part
   *                    for more details. If this string is one of those unsupported intent name, this string will be
   *                    ignored when set to corresponding annotations.
   *
   * @return None.
   */
   void SetIntent(const String& intent);
  /**
   * @brief Get creation date time.
   *
   * @return A date and time object that receives the creation date time.
   *         If there is no creation date time information, a date and time object with all 0 values would be returned.
   */
   DateTime GetCreationDateTime() const;
  /**
   * @brief Set creation date time.
   *
   * @param[in] date_time  The new date time to be set.
   *
   * @return None.
   */
   void SetCreationDateTime(const DateTime& date_time);
  /**
   * @brief Count all replies.
   *
   * @return The count of replies.
   */
   int GetReplyCount();
  /**
   * @brief Get a reply by index.
   *
   * @param[in] index  The index for a specified reply. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Markup::GetReplyCount @endlink.
   *
   * @return A note annotation that represents the specified reply annotation.
   */
   Note GetReply(int index) const;
  /**
   * @brief Add a new reply to the end of reply list.
   *
   * @return A new note annotation that represents the new reply annotation.
   */
   Note AddReply();
  /**
   * @brief Remove a reply by index.
   *
   * @details If specified reply has its own replies, these sub replies will be removed at the same time.
   *
   * @param[in] index  The index for a specified reply to be removed. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Markup::GetReplyCount @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
   bool RemoveReply(int index);
  /**
   * @brief Remove all the replies.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
   bool RemoveAllReplies();

  /**
   * @brief Check whether current markup annotation is in a group or not.
   *
   * @details Markup annotations can be grouped. The group consists of a primary annotation and one or more
   *          subordinate annotations. Some entries in the primary annotation are treated as group attributes
   *          that should apply to the group as a whole; the corresponding entries in the subordinate annotations
   *          should be ignored. These entries are contents, last modification time, fill color/border color,
   *          title, pop-up annotation, creation time, subject, and open status. So user should respect
   *          the group property: when a property of an annotation in group is changed, the other annotations
   *          in the same group should be changed too.<br>
   *          Operations that manipulate any annotation in a group, such as movement, cut, and copy, should be treated
   *          by viewer applications as acting on the entire group.
   *
   * @return <b>true</b> means current markup annotation is in a group.
   *         <b>false</b> means current markup annotation does not belong to any group.
   */
   bool IsGrouped();

  /**
   * @brief Get the header annotation (as primary annotation) of the group that current markup annotation belongs to.
   *
   * @details Markup annotations can be grouped. The group consists of a primary annotation and one or more
   *          subordinate annotations. Some entries in the primary annotation are treated as group attributes
   *          that should apply to the group as a whole; the corresponding entries in the subordinate annotations
   *          should be ignored. These entries are contents, last modification time, fill color/border color,
   *          title, pop-up annotation, creation time, subject, and open status. So user should respect
   *          the group property: when a property of an annotation in group is changed, the other annotations
   *          in the same group should be changed too.<br>
   *          Operations that manipulate any annotation in a group, such as movement, cut, and copy, should be treated
   *          by viewer applications as acting on the entire group.
   *
   * @return The header markup annotation of the group that current markup annotation belongs to.
   *         If the return value of function @link Annot::IsEmpty @endlink (inherited from Markup's parent class)
   *         for the returned markup annotation object is <b>true</b>,
   *         that means current annotation does not belong to a group.
   */
   Markup GetGroupHeader();

  /**
   * @brief Get an element (as markup annotation) from the group that current markup annotation belongs to.
   *
   * @details Markup annotations can be grouped. The group consists of a primary annotation and one or more
   *          subordinate annotations. Some entries in the primary annotation are treated as group attributes
   *          that should apply to the group as a whole; the corresponding entries in the subordinate annotations
   *          should be ignored. These entries are contents, last modification time, fill color/border color,
   *          title, pop-up annotation, creation time, subject, and open status. So user should respect
   *          the group property: when a property of an annotation in group is changed, the other annotations
   *          in the same group should be changed too.<br>
   *          Operations that manipulate any annotation in a group, such as movement, cut, and copy, should be treated
   *          by viewer applications as acting on the entire group.
   *
   * @return An array that contains all the markup annotations in the group.
   *         If current annotation does not belong to a group, this function will return an empty array.
   */
   MarkupArray GetGroupElements();

  /**
   * @brief Ungroup current markup annotation from the group it belongs to.
   *
   * @details <ul>
   *          <li>If current markup annotation is just the group header, this function will
   *              disband the whole group.</li>
   *          <li>If current markup annotation is just a member of a group, this function will only
   *              ungroup current markup annotation from the group it belongs to.</li>
   *          <li>If current markup annotation does not belong to any group, this function will do nothing and
   *              return <b>false</b> directly.</li>
   *          </ul>
   *
   * @return <b>true</b> means success, while <b>false</b> means current markup annotation does not belong to
   *         any group.
   */
   bool Ungroup();

  /**
   * @brief Get the count of state annotations, under a specified state model.
   *
   * @details A markup annotation may have an author-specific state associated with it. The state is not specified
   *          in the annotation itself but in a separate text annotation that refers to the original annotation.<br>
   *          Usually, when state model is @link Markup::e_StateModelMarked @endlink,
   *          the markup annotation only has one state annotation.<br>
   *          When state model is @link Markup::e_StateModelReview @endlink,
   *          the markup annotation can have several state annotations in a chain:
   *          first state annotation refers to the markup annotation, second state annotation refers to the first state
   *          annotation, etc. Just like this:
   *          markup annotation <-- reviewed state1 <-- reviewed state2 ...
   *
   * @param[in] model State model It should be one of following values:
   *                  <ul>
   *                  <li>@link Markup::e_StateModelMarked @endlink</li>
   *                  <li>@link Markup::e_StateModelReview @endlink</li>
   *                  </ul>
   *
   * @return The count of states for the specified state model.
   */
   int GetStateAnnotCount(StateModel model);

  /**
   * @brief Get a state annotation, under a specified state model.
   *
   * @details A markup annotation may have an author-specific state associated with it. The state is not specified
   *          in the annotation itself but in a separate text annotation that refers to the original annotation.<br>
   *          Usually, when state model is @link Markup::e_StateModelMarked @endlink,
   *          the markup annotation only has one state annotation.<br>
   *          When state model is @link Markup::e_StateModelReview @endlink,
   *          the markup annotation can have several state annotations in a chain:
   *          first state annotation refers to the markup annotation, second state annotation refers to the first state
   *          annotation, etc. Just like this:
   *          markup annotation <-- reviewed state1 <-- reviewed state2 ...
   *
   * @param[in] model  State model. It should be one of following values:
   *                   <ul>
   *                   <li>@link Markup::e_StateModelMarked @endlink</li>
   *                   <li>@link Markup::e_StateModelReview @endlink</li>
   *                   </ul>
   * @param[in] index  The index of the state annotation to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Markup::GetStateAnnotCount @endlink with the same
   *                   parameter <i>model</i>.
   *
   * @return The state annotation, represented by a note annotation.
   */
   Note GetStateAnnot(StateModel model, int index);

  /**
   * @brief Add a new state annotation.
   *
   * @details A markup annotation may have an author-specific state associated with it. The state is not specified
   *          in the annotation itself but in a separate text annotation that refers to the original annotation.<br>
   *          Usually, when state model is @link Markup::e_StateModelMarked @endlink,
   *          the markup annotation only has one state annotation.<br>
   *          When state model is @link Markup::e_StateModelReview @endlink,
   *          the markup annotation can have several state annotations in a chain:
   *          first state annotation refers to the markup annotation, second state annotation refers to the first state
   *          annotation, etc. Just like this:
   *          markup annotation <-- reviewed state1 <-- reviewed state2 ...
   *
   * @param[in] model  State model for the new state annotation. It should be one of following values:
   *                   <ul>
   *                   <li>@link Markup::e_StateModelMarked @endlink:
   *                       <ul>
   *                       <li>If current markup annotation already has a state annotation in marked state model,
   *                           this function will set the new state value to the existed marked state model directly
   *                           instead of adding a new one.
   *                       </li>
   *                       <li>If current markup annotation does not have a state annotation in marked state model,
   *                           this function will add a new one.
   *                       </li>
   *                       </ul>
   *                   </li>
   *                   <li>@link Markup::e_StateModelReview @endlink:
   *                       <ul>
   *                       <li>If current markup annotation already has state annotations in reviewed state model,
   *                           this function will add a new one to refer to the last state annotation in reviewed
   *                           state model.
   *                       </li>
   *                       <li>If current markup annotation does not have any state annotation in reviewed state model,
   *                           this function will add a new one to refer to current markup annotation.
   *                       </li>
   *                       </ul>
   *                   </li>
   *                   </ul>
   * @param[in] state  State value for the new state annotation. It should be one of following values:
   *                   <ul>
   *                   <li>If parameter <i>model</i> is @link Markup::e_StateModelMarked @endlink,
   *                       the state should be @link Markup::e_StateMarked @endlink or @link Markup::e_StateUnmarked @endlink.
   *                   </li>
   *                   <li>If parameter <i>model</i> is @link Markup::e_StateModelReview @endlink,
   *                       the state should be @link Markup::e_StateAccepted @endlink, @link Markup::e_StateRejected @endlink,
   *                       @link Markup::e_StateCancelled @endlink, @link Markup::e_StateCompleted @endlink,
   *                       or @link Markup::e_StateNone @endlink.
   *                   </li>
   *                   </ul>
   *
   * @return A new state annotation represented by a note annotation.
   */
   Note AddStateAnnot(StateModel model, State state);

  /**
   * @brief Remove all state annotations.
   *
   * @details State annotation is represented by note annotation, so, to remove state annotations also means to
   *          remove the special note annotations (with its popup if any) from the page.
   *
   * @return <b>true</b> means remove all the state annotations successfully or current annotation does not have any
   *         state annotation, while <b>false</b> means failure.<br>
   */
   bool RemoveAllStateAnnots();

};

/**
 * A note annotation (known as "text" annotation in <PDF reference 1.7>) represents a "sticky note" attached
 * to a point in the PDF document. When closed, the annotation appears as an icon; when open, it displays a
 * pop-up window containing the text of the note in a font and size chosen by the viewer application. <br>
 * A note annotation can also be used as a reply to a markup annotation, or a state annotation:
 * <ul>
 * <li>When as a reply, the note annotation should not be shown alone but together with other replies in the
 *     form of threaded comments. Function @link Note::GetReplyTo @endlink can be used to get the markup annotation,
 *     to which the note annotation replies.</li>
 * <li>When as a state, the note annotation would not be shown alone. Function @link Note::IsStateAnnot @endlink
 *     can be used to judge if a note annotation is used as a state.</li>
 * </ul>
 * Note annotation is a kind of markup annotation, so class @link Note @endlink is derived from
 * class @link Markup @endlink. It offers functions to get/set note annotation's properties and
 * reset appearance of a note annotation.
 *
 * @note For a newly created common note annotation, if user calls function @link Annot::ResetAppearanceStream @endlink
 *       directly without setting any properties, the default appearance will be used:<br>
 *       border color = 0xFFFFFF00 (yellow), opacity = 1.0, icon name = "Comment".
 *
 * @see @link Markup @endlink
 */
class Note FS_FINAL : public Markup {
 public:
   /** @brief Constructor. */
  Note() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Note(const Annot& annot);
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Note(FS_HANDLE handle);
  /** @brief Destructor. */
  ~Note() {}

  /**
   * @brief Get open status.
   *
   * @details Open status is a boolean value that specifies whether a note annotation should initially be
   *          displayed open:
   *          <ul>
   *          <li><b>true</b> means the note annotation should be initially be displayed open.</li>
   *          <li><b>false</b> means the note annotation should be initially be displayed closed.</li>
   *          </ul>
   *
   * @return Open status.
   */
  bool GetOpenStatus() const;
  /**
   * @brief Set open status.
   *
   * @details Open status is a boolean value that specifies whether a note annotation should initially be
   *          displayed open:
   *          <ul>
   *          <li><b>true</b> means the note annotation should be initially be displayed open.</li>
   *          <li><b>false</b> means the note annotation should be initially be displayed closed.</li>
   *          </ul>
   *
   * @param[in] status  The new open status value.
   *
   * @return None.
   */
  void SetOpenStatus(bool status);
  /**
   * @brief Get icon name.
   *
   * @details This property has effect on note annotation's appearance. Note annotation has predefined standard icon
   *          names: <br>
   *          "Check", "Circle", "Comment", "Cross", "Help", "Insert", "Key", "NewParagraph", "Note", "Paragraph",
   *          "RightArrow", "RightPointer", "Star", "UpArrow", "UpLeftArrow".<br>
   *          An empty icon name string means current note annotation would be treated as "Note" icon.<br>
   *
   * @return Icon name string.
   */
  String GetIconName() const;
  /**
   * @brief Set icon name.
   *
   * @details This property has effect on note annotation's appearance. Note annotation has predefined standard icon
   *          names: <br>
   *          "Check", "Circle", "Comment", "Cross", "Help", "Insert", "Key", "NewParagraph", "Note", "Paragraph",
   *          "RightArrow", "RightPointer", "Star", "UpArrow", "UpLeftArrow".<br>
   *          An empty icon name string means current note annotation would be treated as "Note" icon.<br>
   *          For a newly created note annotation, if current function is not called, icon name will be
   *          "Comment" by default.<br>
   *          If user wants the new icon name has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting the new icon name.
   *
   * @param[in] icon_name  New icon name string to be set.
   *
   * @return None.
   */
  void SetIconName(const char* icon_name);
  /**
   * @brief Get the markup annotation, which current note annotation is in reply to.
   *
   * @details This function is only useful when current note annotation is used as a reply.
   *
   * @return A markup annotation object, which current note annotation is in reply to.
   *         If the return value of function @link Annot::IsEmpty @endlink (inherited from Markup's parent class)
   *         for the returned markup annotation object is <b>true</b>, that means current note annotation is not used as a reply.
   */
  Markup GetReplyTo();
  /**
   * @brief Check if current note annotation is used as a state annotation.
   *
   * @return <b>true</b> means current note annotation is used as a state annotation,
   *         while <b>false</b> means current note annotation is just a common note annotation.
   */
  bool IsStateAnnot();

  /**
   * @brief Get the state model.
   *
   * @details This function can only be used when current note annotation is used as a state annotation.
   *          Function @link Note::IsStateAnnot @endlink can be used to check if current note annotation is used as
   *          a state annotation.
   *
   * @return The state model. If function succeeds, the return value would be
   *         @link Markup::e_StateModelMarked @endlink or @link Markup::e_StateModelReview @endlink.<br>
   *         If current note annotation is not a state annotation, this function will return 0.
   */
  StateModel GetStateModel();

  /**
   * @brief Get the state.
   *
   * @details This function can only be used when current note annotation is used as a state annotation.
   *          Function @link Note::IsStateAnnot @endlink can be used to check if current note annotation is used as
   *          a state annotation.
   *
   * @return The state. Please refer to values starting from @link Markup::e_StateMarked @endlink and
   *         this would be one of these values.
   *         If current note annotation is not a state annotation, This function will return 0.
   */
  State GetState();

  /**
   * @brief Set the state.
   *
   * @details This function can only be used when current note annotation is used as a state annotation.
   *          Function @link Note::IsStateAnnot @endlink can be used to check if current note annotation is used as
   *          a state annotation.
   *
   * @param[in] state  New state. It should be one of following values:
   *                   <ul>
   *                   <li>If state model is @link Markup::e_StateModelMarked @endlink,
   *                       the state should be @link Markup::e_StateMarked @endlink or @link Markup::e_StateUnmarked @endlink.
   *                   </li>
   *                   <li>If state model is @link Markup::e_StateModelReview @endlink,
   *                       the state should be @link Markup::e_StateAccepted @endlink, @link Markup::e_StateRejected @endlink,
   *                       @link Markup::e_StateCancelled @endlink, @link Markup::e_StateCompleted @endlink,
   *                        or @link Markup::e_StateNone @endlink.
   *                   </li>
   *                   </ul>
   *                   State model can be gotten by function @link Note::GetStateModel @endlink.
   *
   * @return None.
   */
  void SetState(State state);

};

/**
 * Text markup annotations appear as highlights, underlines, strikeouts, or squiggly lines in the text of a document.
 * Text markup annotations are all markup annotations, so class @link TextMarkup @endlink is derived from
 * class @link Markup @endlink. It is the base class for all PDF text markup annotations. It offers
 * the base functions to get/set text markup annotation's common properties. <br>
 * Especially, for a text markup annotation, quadrilaterals are required. So please ensure that a text markup
 * annotation has valid quadrilaterals before resetting its appearance stream. <br>
 * For concrete text markup annotation types, please refer to derived classes.
 *
 * @see @link Markup @endlink
 */
class TextMarkup: public Markup {
 public:
  /** @brief Constructor. */
  TextMarkup() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit TextMarkup(const Annot& annot);
  /** @brief Destructor. */
  ~TextMarkup() {}

  /**
   * @brief Get quadrilaterals.
   *
   * @details This property has effect on text markup annotation's appearance. The order of points in a quadrilateral
   *          should be:
   *          <ul>
   *          <li>The first point is the point in left-top corner of the quadrilateral.</li>
   *          <li>The second point is the point in right-top corner of the quadrilateral.</li>
   *          <li>The third point is the point in left-bottom corner of the quadrilateral.</li>
   *          <li>The fourth point is the point in right-bottom corner of the quadrilateral.</li>
   *          </ul>
   *
   * @return A quadrilateral points array that receives the quadrilaterals value.
   */
   QuadPointsArray GetQuadPoints() const;
  /**
   * @brief Set quadrilaterals.
   *
   * @details For a text markup annotation, quadrilaterals are required. This property has effect on text markup
   *          annotation's appearance. After setting new quadrilaterals, rectangle of current text markup annotation
   *          will be updated as well. The order of points in a quadrilateral should be:
   *          <ul>
   *          <li>The first point is the point in left-top corner of the quadrilateral.</li>
   *          <li>The second point is the point in right-top corner of the quadrilateral.</li>
   *          <li>The third point is the point in left-bottom corner of the quadrilateral.</li>
   *          <li>The fourth point is the point in right-bottom corner of the quadrilateral.</li>
   *          </ul>
   *          If user wants the new quadrilaterals has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting quadrilaterals.
   *
   * @param[in] quad_points_array  A valid array of quadrilaterals. It should not be an empty array.
   *
   * @return None.
   */
   void SetQuadPoints(const QuadPointsArray& quad_points_array);
};

/**
 * Highlight annotation is a kind of text markup annotation, which is shown as a highlight area for the text
 * in a PDF document.<br>
 * Class @link annots::Highlight @endlink is derived from @link TextMarkup @endlink and offers function to
 * reset appearance stream of a highlight annotation. For a highlight annotation, quadrilaterals are required.
 * So please ensure that a highlight annotation has valid quadrilaterals before resetting its appearance stream;
 * otherwise the highlight annotation cannot be reset appearance stream.
 *
 * @note For a newly created highlight annotation, if user calls function @link Annot::ResetAppearanceStream @endlink
 *       directly after setting required quadrilaterals property and not setting any other properties, the default
 *       appearance will be used:<br>
 *       border width = 1.0, border style = @link BorderInfo::e_Solid @endlink,
 *       border color = 0xFFFFED00 (a kind of yellow), opacity = 1.0,
 *
 * @see @link TextMarkup @endlink
 */
class Highlight FS_FINAL : public TextMarkup {
 public:
  /** @brief Constructor. */
  Highlight() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Highlight(const Annot& annot);
  /** @brief Destructor. */
  ~Highlight() {}
};

/**
 * Underline annotation is a kind of text markup annotation, which is shown as a underline under the text
 * in a PDF document.<br>
 * Class @link annots::Underline @endlink is derived from @link TextMarkup @endlink and offers function to
 * reset appearance stream of a underline annotation. For a underline annotation, quadrilaterals are required.
 * So please ensure that a underline annotation has valid quadrilaterals before resetting its appearance stream;
 * otherwise the underline annotation cannot be reset appearance stream.
 *
 * @note For a newly created underline annotation, if user calls function @link Annot::ResetAppearanceStream @endlink
 *       directly after setting required quadrilaterals property and not setting any other properties, the default
 *       appearance will be used:<br>
 *       border width = 1.0, border style = @link BorderInfo::e_Solid @endlink,
 *       border color = 0xFF339E00 (a kind of green), opacity = 1.0,
 *
 * @see @link TextMarkup @endlink
 */
class Underline FS_FINAL : public TextMarkup {
 public:
  /** @brief Constructor. */
  Underline() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Underline(const Annot& annot);
  /** @brief Destructor. */
  ~Underline() {}
};

/**
 * Strikeout annotation is a kind of text markup annotation, which is shown as a strikeout line in the middle of
 * the text in a PDF document.<br>
 * Class @link annots::StrikeOut @endlink is derived from @link TextMarkup @endlink and offers function to
 * reset appearance stream of a strikeout annotation. For a strikeout annotation, quadrilaterals are required.
 * So please ensure that a strikeout annotation has valid quadrilaterals before resetting its appearance stream;
 * otherwise the strikeout annotation cannot be reset appearance stream.
 *
 * @note For a newly created strikeout annotation, if user calls function @link Annot::ResetAppearanceStream @endlink directly
 *       after setting required quadrilaterals property and not setting any other properties,
 *       the default appearance will be used:<br>
 *       border width = 1.0, border style = @link BorderInfo::e_Solid @endlink,
 *       border color = 0xFFF94244 (a kind of red), opacity = 1.0,
 *
 * @see @link TextMarkup @endlink
 */
class StrikeOut FS_FINAL : public TextMarkup {
 public:
  /** @brief Constructor. */
  StrikeOut() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit StrikeOut(const Annot& annot);
  /** @brief Destructor. */
  ~StrikeOut() {}
};

/**
 * Squiggly annotation is a kind of text markup annotation, which is shown as a squiggly line under the text
 * in a PDF document.<br>
 * Class @link annots::Squiggly @endlink is derived from @link TextMarkup @endlink and offers function to
 * reset appearance stream of a squiggly annotation. For a squiggly annotation, quadrilaterals are required.
 * So please ensure that a squiggly annotation has valid quadrilaterals before resetting its appearance stream;
 * otherwise the squiggly annotation cannot be reset appearance stream.
 *
 * @note For a newly created squiggly annotation, if user calls function @link Annot::ResetAppearanceStream @endlink
 *       directly after setting required quadrilaterals property and not setting any other properties,
 *       the default appearance will be used:<br>
 *       border width = 1.0, border style = @link BorderInfo::e_Solid @endlink,
 *       border color = 0xFF4899FF (a kind of blue), opacity = 1.0,
 *
 * @see @link TextMarkup @endlink
 */
class Squiggly FS_FINAL : public TextMarkup {
 public:
  /** @brief Constructor. */
  Squiggly() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Squiggly(const Annot& annot);
  /** @brief Destructor. */
  ~Squiggly() {}
};

/**
 * A link annotation represents an action to be performed.<br>
 * Class @link annots::Link @endlink is derived from @link Annot @endlink, and offers functions to get/set link annotation's properties and
 * reset appearance stream of a link annotation.
 *
 * @note For a newly created link annotation, if user calls function @link Annot::ResetAppearanceStream @endlink directly
 *       without setting any other properties, the default appearance will be used:<br>
 *       border width = 1.0, border style = @link BorderInfo::e_Solid @endlink,
 *       border color = 0xFFFF0000 (red), opacity = 1.0,
 *       highlighting mode = @link Annot::e_HighlightingNone @endlink.
 *
 * @see @link Annot @endlink
 */
class Link FS_FINAL : public Annot {
 public:
  /** @brief Constructor. */
  Link() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Link(const Annot& annot);
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Link(FS_HANDLE handle);
  /** @brief Destructor. */
   ~Link() {}

  /**
   * @brief Get quadrilaterals.
   *
   * @details The order of points in a quadrilateral should be:
   *          <ul>
   *          <li>The first point is the point in left-top corner of the quadrilateral.</li>
   *          <li>The second point is the point in right-top corner of the quadrilateral.</li>
   *          <li>The third point is the point in left-bottom corner of the quadrilateral.</li>
   *          <li>The fourth point is the point in right-bottom corner of the quadrilateral.</li>
   *          </ul>
   *
   * @return A quadrilateral points array that receives the quadrilaterals value.
   */
  QuadPointsArray GetQuadPoints() const;
  /**
   * @brief Set quadrilaterals.
   *
   * @details This property has effect on the link annotation's appearance.The order of points in a quadrilateral
   *          should be :
   *          <ul>
   *          <li>The first point is the point in left-top corner of the quadrilateral.</li>
   *          <li>The second point is the point in right-top corner of the quadrilateral.</li>
   *          <li>The third point is the point in left-bottom corner of the quadrilateral.</li>
   *          <li>The fourth point is the point in right-bottom corner of the quadrilateral.</li>
   *          </ul>
   *          If user wants the new quadrilaterals has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting quadrilaterals.
   *
   * @param[in] quad_points_array  A valid array of quadrilaterals. It should not be an empty array.
   *
   * @return None.
   */
  void SetQuadPoints(const QuadPointsArray& quad_points_array);

  /**
   * @brief Get highlighting mode.
   *
   * @return Highlighting mode value. Please refer to values starting from @link Annot::e_HighlightingNone @endlink and
   *         this would be one of these values except @link Annot::e_HighlightingToggle @endlink.
   *         -1 means no highlighting mode value is found.
   */
  HighlightingMode GetHighlightingMode();

  /**
   * @brief Set highlighting mode.
   *
   * @param[in] mode  New highlighting mode value. Please refer to values starting from
   *                  @link Annot::e_HighlightingNone @endlink and this should be one of these values except
   *                  @link Annot::e_HighlightingToggle @endlink.
   *
   * @return None.
   */
  void SetHighlightingMode(HighlightingMode mode);

  /**
   * @brief Get action.
   *
   * @return An action object that receives the action data. If the return value of function
   *         @link actions::Action::IsEmpty @endlink for the returned action object is <b>true</b>, that means no action.
   */
  actions::Action GetAction();

  /**
   * @brief Set action.
   *
   * @param[in] action  New action to be set. It should be valid.
   *                    Currently only support following types as the new action:<br>
   *                    @link actions::Action::e_TypeGoto @endlink, @link actions::Action::e_TypeURI @endlink,
   *                    @link actions::Action::e_TypeJavaScript @endlink, @link actions::Action::e_TypeNamed @endlink,
   *                    @link actions::Action::e_TypeGoToR @endlink, @link actions::Action::e_TypeGoToE @endlink,
   *                    @link actions::Action::e_TypeSubmitForm @endlink, @link actions::Action::e_TypeResetForm @endlink,
   *                    @link actions::Action::e_TypeHide @endlink, @link actions::Action::e_TypeLaunch @endlink,
   *                    @link actions::Action::e_TypeImportData @endlink, @link actions::Action::e_TypeRendition @endlink.
   *
   * @return None.
   */
  void SetAction(const actions::Action& action);

  /**
   * @brief Remove action.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveAction();
};

/**
 * Square annotation is a rectangle on the page. Despite the name "square", a square annotation can represent
 * either a square or a rectangle, which means the width and height of the annotation rectangle need not be equal.<br>
 * Square annotation is a kind of markup annotation, so class @link Square @endlink is derived from
 * class @link Markup @endlink, and also offers functions to get/set square annotation's properties and
 * reset appearance stream of a square annotation.
 *
 * @note For a newly created square annotation, if user calls function @link Annot::ResetAppearanceStream @endlink directly
 *       without setting any properties, the default appearance will be used:<br>
 *       border color = 0xFFFF0000 (red), opacity = 1.0,
 *       border width = 2.0, border style = @link BorderInfo::e_Solid @endlink.
 *
 * @see @link Markup @endlink
 */
class Square FS_FINAL : public Markup {
 public:
  /** @brief Constructor. */
  Square() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Square(const Annot& annot);
  /** @brief Destructor. */
  ~Square() {}

  /**
   * @brief Get fill color.
   *
   * @return The fill color. Format: 0xRRGGBB.
   *         If no fill color can be found, 0x000000 will be returned.
   */
  RGB GetFillColor() const;

  /**
   * @brief Set fill color.
   *
   * @param[in] fill_color  New fill color to be set. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetFillColor(RGB fill_color);

  /**
   * @brief Get the inner rectangle.
   *
   * @details For a square annotation, inner rectangle means the actual boundaries of underlying circle.
   *          The inner rectangle could be just the same as or less than the annotation's rectangle,
   *          and should never be larger than annotation's rectangle.
   *
   * @return The inner rectangle.
   */
  RectF GetInnerRect() const;
  /**
   * @brief Set the inner rectangle.
   *
   * @details For a square annotation, inner rectangle means the actual boundaries of underlying circle.
   *          The inner rectangle could be just the same as or less than the annotation's rectangle,
   *          and should never be larger than annotation's rectangle.
   *
   * @param[in] inner_rect  New inner rectangle to be set. It should be same as or less than annotation's rectangle.
   *
   * @return None.
   */
  void SetInnerRect(const RectF& inner_rect);
};

/**
 * Circle annotation is an ellipse on the page. Despite the name "circle", a circle annotation can represent
 * either a circle or a oval, which means the width and height of the annotation rectangle need not be equal.<br>
 * Circle annotation is a kind of markup annotation, so class @link Circle @endlink is derived from
 * class @link Markup @endlink, and also offers functions to get/set circle annotation's properties and
 * reset appearance stream of a circle annotation.
 *
 * @note For a newly created circle annotation, if user calls function @link Annot::ResetAppearanceStream @endlink directly
 *       without setting any properties, the default appearance will be used:<br>
 *       border color = 0xFFFF0000 (red), opacity = 1.0,
 *       border width = 2.0, border style = @link BorderInfo::e_Solid @endlink.
 *
 * @see @link Markup @endlink
 */
class Circle FS_FINAL : public Markup {
 public:
  /** @brief Constructor. */
  Circle() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Circle(const Annot& annot);
  /** @brief Destructor. */
  ~Circle() {}

  /**
   * @brief Get fill color.
   *
   * @return The fill color. Format: 0xRRGGBB.
   *         If no fill color can be found, 0x000000 will be returned.
   */
  RGB GetFillColor() const;

  /**
   * @brief Set fill color.
   *
   * @details If user wants the new fill color has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new fill color.
   *
   * @param[in] fill_color  New fill color to be set. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetFillColor(RGB fill_color);

  /**
   * @brief Get the inner rectangle.
   *
   * @details For a circle annotation, inner rectangle means the actual boundaries of underlying circle.
   *          The inner rectangle could be just the same as or less than the annotation's rectangle,
   *          and should never be larger than annotation's rectangle.
   *
   * @return The inner rectangle.
   */
  RectF GetInnerRect() const;

  /**
   * @brief Set the inner rectangle.
   *
   * @details For a circle annotation, inner rectangle means the actual boundaries of underlying circle.
   *          The inner rectangle could be just the same as or less than the annotation's rectangle,
   *          and should never be larger than annotation's rectangle.<br>
   *          If user wants the new inner rectangle has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new inner rectangle.
   *
   * @param[in] inner_rect  New inner rectangle to be set. It should be same as or less than annotation's rectangle.
   *
   * @return None.
   */
  void SetInnerRect(const RectF& inner_rect);
};

/**
 * A free text annotation displays text directly on the page. So free text annotation does not need a related
 * pop-up annotation to show the text.<br>
 * Free text annotation is a kind of markup annotation, so class @link FreeText @endlink is derived from
 * class @link Markup @endlink, and also offers functions to get/set free text annotation's properties and
 * reset appearance stream of a free text annotation. <br>
 *
 * @note For a newly created free text annotation, if user calls function @link Annot::ResetAppearanceStream @endlink directly
 *       without setting any properties, the default appearance will be used:<br>
 *       border width = 1.0, border style = @link BorderInfo::e_Solid @endlink,
 *       border color = 0xFFFF0000 (red), opacity = 1.0, alignment = 0 (as left-justified),
 *       default appearance flags =
 *       @link DefaultAppearance::e_FlagFont @endlink| @link DefaultAppearance::e_FlagTextColor @endlink|
 *       @link DefaultAppearance::e_FlagFontSize @endlink,
 *       default appearance font is created based on @link common::Font::e_StdIDHelvetica @endlink,
 *       default appearance text size = 12, default appearance text color = 0xFF0000FF (blue).
 *
 * @see @link Markup @endlink
 */
class FreeText FS_FINAL : public Markup {
 public:
  /** @brief Constructor. */
  FreeText() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit FreeText(const Annot& annot);
  /** @brief Destructor. */
  ~FreeText() {}

  /**
   * @brief Get fill color.
   *
   * @details This property has effect on free text annotation's appearance. Fill color is used to fill the background
   *          of text box, and also for some callout line ending styles:<br>
   *          "Square", "Circle", "Diamond", "ClosedArrow", "RClosedArrow".
   *
   * @return The fill color. Format: 0xRRGGBB.
   *         If no fill color can be found, 0x000000 will be returned.
   */
  RGB GetFillColor() const;
  /**
   * @brief Set fill color.
   *
   * @details This property has effect on free text annotation's appearance. Fill color is used to fill the background
   *          of text box, and also for some callout line ending styles:<br>
   *          "Square", "Circle", "Diamond", "ClosedArrow", "RClosedArrow".<br>
   *          If user wants the new fill color has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new fill color.
   *
   * @param[in] fill_color  New fill color to be set. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetFillColor(RGB fill_color);

  /**
   * @brief Get alignment value.
   *
   * @details This property has effect on free text annotation's appearance.
   *
   * @return The alignment value. Please refer to values starting from @link common::e_AlignmentLeft @endlink and
   *         this would be one of these values.
   */
  common::Alignment GetAlignment() const;

  /**
   * @brief Set alignment value
   *
   * @details This property has effect on free text annotation's appearance. If user wants the new alignment has effect
   *          on annotation's appearance, please call function @link Annot::ResetAppearanceStream @endlink after setting
   *          new alignment.
   *
   * @param[in] alignment  The new alignment value. Please refer to values starting from @link common::e_AlignmentLeft @endlink
   *                       and this should be one of these values.<br>
   *                       If other values is used to set, @link common::e_AlignmentLeft @endlink will be used by default.
   *
   * @return None.
   */
  void SetAlignment(common::Alignment alignment);

  /**
   * @brief Get the inner rectangle.
   *
   * @details This property has effect on free text annotation's appearance. For a free text annotation,
   *          inner rectangle is where the annotation's text should be displayed. The inner rectangle could be
   *          just the same as or less than the annotation's rectangle, and should never be larger than
   *          annotation's rectangle.
   *
   * @return The inner rectangle.
   */
  RectF GetInnerRect() const;

  /**
   * @brief Set the inner rectangle.
   *
   * @details This property has effect on free text annotation's appearance. For a free text annotation,
   *          inner rectangle is where the annotation's text should be displayed. The inner rectangle could be
   *          just the same as or less than the annotation's rectangle, and should never be larger than
   *          annotation's rectangle.<br>
   *          If user wants the new inner rectangle has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new inner rectangle.
   *
   * @param[in] inner_rect  New inner rectangle to be set. It should be same as or less than annotation's rectangle.
   *
   * @return None.
   */
  void SetInnerRect(const RectF& inner_rect);

  /**
   * @brief Get default appearance data.
   *
   * @details This property has effect on free text annotation's appearance. Default appearance data can be used in
   *          formatting text.
   *
   * @return The default appearance data.
   */
  DefaultAppearance GetDefaultAppearance();

  /**
   * @brief Set default appearance data.
   *
   * @details This property has effect on free text annotation's appearance. Default appearance data can be used in
   *          formatting text.<br>
   *          If user wants the new default appearance data has effect on annotation's appearance,
   *          please call function @link Annot::ResetAppearanceStream @endlink after setting new default appearance data.
   *
   * @param[in] default_ap  The new default appearance data to be set.
   *                        <i>flags</i> of input data can be used to decide which information is/are to
   *                        be updated with the new data; for those no updated data, they will keep to use old data.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Specially, this function will return <b>false</b>
   *         if the parameter <i>default_ap</i> contains any incorrect value, for example:
   *         <ul>
   *         <li><i>flags</i> of input data includes the @link DefaultAppearance::e_FlagFont @endlink
   *             but <i>font</i> of input data is invalid.</li>
   *         <li><i>flags</i> of input data includes the @link DefaultAppearance::e_FlagFontSize @endlink
   *             but <i>text size</i> of input data is not bigger than zero.</li>
   *         </ul>
   */
  bool SetDefaultAppearance(const DefaultAppearance& default_ap);

  /**
   * @brief Get line ending style of the start point in a callout line.
   *
   * @details Only when the intent name of a free text annotation is "FreeTextCallout",
   *          this free text annotation can have line ending style property, and this property has effect on this kind
   *          of free text annotation's appearance.
   *
   * @return The line ending style of the start point. Please refer to values starting from
   *         @link Markup::e_EndingStyleNone @endlink and this would be one of these values.
   */
  EndingStyle GetCalloutLineEndingStyle() const;

  /**
   * @brief Set line ending style of the start point in a callout line.
   *
   * @details Only when the intent name of a free text annotation is "FreeTextCallout",
   *          this free text annotation can have line ending style property, and this property has effect on this kind
   *          of free text annotation's appearance.<br>
   *          If user wants the new line ending style has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new line ending style.
   *
   * @param[in] ending_style  The line ending style for the start point to be set. Please refer to values starting from
   *                          @link Markup::e_EndingStyleNone @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetCalloutLineEndingStyle(EndingStyle ending_style);

  /**
   * @brief Get a point of callout line points.
   *
   * @details Only when the intent name of a free text annotation is "FreeTextCallout", this free text annotation can
   *          have callout line points property, and this property has effect on this kind of free text annotation's
   *          appearance. For a callout line, it can contain 2 or 3 points:<br>
   *          <ul>
   *          <li> 2 points represent the starting point and ending point of the callout line.</li>
   *          <li> 3 points represent the starting point, knee point, and ending point of the callout line.</li>
   *          </ul>
   *
   * @return A point array that represents the points used for callout line of a callout free text annotation.
   */
  PointFArray GetCalloutLinePoints() const;

  /**
   * @brief Set points for callout line.
   *
   * @details Only when the intent name of a free text annotation is "FreeTextCallout", this free text annotation can
   *          have callout line points property, and this property has effect on this kind of free text annotation's
   *          appearance. For a callout line, it can contain 2 or 3 points:<br>
   *          <ul>
   *          <li> 2 points represent the starting point and ending point of the callout line.</li>
   *          <li> 3 points represent the starting point, knee point, and ending point of the callout line.</li>
   *          </ul>
   *          If user wants the new callout line points has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new callout line points.
   *
   * @param[in] point_array  New point array that specifies the starting point, knee point(if any) and ending point
   *                         of the callout line. The count of elements should be 2 or 3:
   *                         2 points meand starting point and ending point; 3 points means the startign point,
   *                         knee point and ending point.<br>
   *                         If the count of elements is above 3, only the first 3 points will be used to
   *                         set callout line.
   *
   * @return None.
   */
  void SetCalloutLinePoints(const PointFArray& point_array);

  /**
   * @brief Set matrix in default appearance data for text in current free text annotation.
   *
   * @details This property has effect on free text annotation's appearance. This property can be used to
   *          change the skew of text's display.<br>
   *          If user wants the new text matrix has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new text matrix.
   *
   * @param[in] text_matrix  The new text matrix.
   *
   * @return None.
   */
  void SetTextMatrix(const Matrix& text_matrix);

   /**
   * @brief Get matrix in default appearance data for text in current free text annotation.
   *
   * @details This property has effect on free text annotation's appearance. This property can be used to
   *          change the skew of text's display.
   *
   * @return Matrix used for text in default appearance.
   */
  Matrix GetTextMatrix() const;

  /**
   * @brief Get current rotation value (in clockwise).
   *
   * @return Current rotation value (in clockwise). Please refer to values starting from
   *         @link common::e_Rotation0 @endlink and this would be one of these values.
   */
  common::Rotation GetRotation();

   /**
   * @brief Set rotation value (in clockwise).
   *
   * @details This property has effect on free text annotation's appearance. If user wants the new rotation
   *          has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new rotation.

   *
   * @param[in] rotation  New rotation value (in clockwise) to be set to current free text annotation.
   *                      Please refer to values starting from @link common::e_Rotation0 @endlink
   *                      and this should be one of these values except @link common::e_RotationUnknown @endlink.
   *
   * @return None.
   */
  void SetRotation(common::Rotation rotation);

  /**
   * @brief Rotate current annotation from current state with specified rotation value (in clockwise).
   *
   * @param[in] rotation  Rotation value which represents the degree used to rotate current annotation
   *                      from current state in clockwise. Please refer to values starting from
   *                      @link common::e_Rotation0 @endlink and this should be one of these values
   *                      except @link common::e_RotationUnknown @endlink. Specially, if the input value is 
   *                      @link common::e_Rotation0 @endlink (which means not to rotate current annotation),
   *                      current function will do nothing.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  void Rotate(common::Rotation rotation);

};

/**
 * A line annotation displays a single straight line on the page.<br>
 * Line annotation is a kind of markup annotation, so class @link Line @endlink is derived from
 * class @link Markup @endlink, and also offers functions to get/set line annotation's properties and
 * reset appearance stream of a line annotation.<br>
 * For a line annotation, start point and end point are required. So please ensure that a line annotation
 * has valid start point and end point before resetting its appearance stream; otherwise the line annotation cannot
 * be reset appearance stream.
 *
 * @note For a newly created line annotation, if user calls function @link Annot::ResetAppearanceStream @endlink directly
 *       after setting required start point and end point property and not setting any other properties,
 *       the default appearance will be used:<br>
 *       border width = 2.0, border style = @link BorderInfo::e_Solid @endlink,
 *       border color = 0xFFFF0000 (red), opacity = 1,
 *       line starting/ending styles = "None", no caption is enabled.
 *
 * @see @link Markup @endlink
 */
class Line FS_FINAL : public Markup {
 public:
  /**
   * @brief Enumeration for the position type of caption.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _CapPos {
    /** The caption shall be centered inside the line*/
    e_CapPosInline = 0,
    /** The caption shall be on top of the line*/
    e_CapPosTop = 1
  } CapPos;
  

  /** @brief Constructor. */
  Line() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Line(const Annot& annot);
  /** @brief Destructor. */
  ~Line() {}

  /**
   * @brief Get line ending style of the start point.
   *
   * @details This property has effect on line annotation's appearance.
   *
   * @return The line ending style of the start point. Please refer to values starting from
   *         @link Markup::e_EndingStyleNone @endlink and this would be one of these values.
   */
   EndingStyle GetLineStartStyle() const;
  /**
   * @brief Set line ending style of the start point.
   *
   * @details This property has effect on line annotation's appearance.
   *          If user wants the new line ending style has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new line ending style.
   *
   * @param[in] ending_style  The line ending style for the start point to be set. Please refer to values starting from
   *                          @link Markup::e_EndingStyleNone @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetLineStartStyle(EndingStyle ending_style);
  /**
   * @brief Get line ending style of the end point.
   *
   * @details This property has effect on line annotation's appearance.
   *
   * @return The line ending style of the end point. Please refer to values starting from
   *         @link Markup::e_EndingStyleNone @endlink and this would be one of these values.
   */
  EndingStyle GetLineEndStyle() const;
  /**
   * @brief Set line ending style of the end point.
   *
   * @details This property has effect on line annotation's appearance.
   *          If user wants the new line ending style has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new line ending style.
   *
   * @param[in] ending_style  The line ending style for the end point to be set. Please refer to values starting from
   *                          @link Markup::e_EndingStyleNone @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetLineEndStyle(EndingStyle ending_style);

  /**
   * @brief Get fill color for ending styles.
   *
   * @details This property has effect on line annotation's appearance.
   *          Fill color is used for some line ending styles:<br>
   *          "Square", "Circle", "Diamond", "ClosedArrow", "RClosedArrow".
   *
   * @return The fill color of ending styles. Format: 0xRRGGBB.
   *         If no fill color can be found, 0x000000 will be returned.
   */
  RGB GetStyleFillColor() const;

  /**
   * @brief Set fill color for ending styles.
   *
   * @details This property has effect on line annotation's appearance.
   *          Fill color is used for some line ending styles:<br>
   *          "Square", "Circle", "Diamond", "ClosedArrow", "RClosedArrow".<br>
   *          If user wants the new fill color has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new fill color.
   *
   * @param[in] color  New fill color of ending style. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetStyleFillColor(RGB color);

  /**
   * @brief Get the start point.
   *
   * @details Start point and end point are required for a line annotation. They have effect on line annotation's
   *          appearance.
   *
   * @return The start point. A point with value (0, 0) may also mean that no start point is found.
   */
  PointF GetStartPoint() const;
  /**
   * @brief Set the start point.
   *
   * @details Start point and end point are required for a line annotation. They have effect on line annotation's
   *          appearance.<br>
   *          If user wants the new start point has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new start point.
   *
   * @param[in] point  New point that specifies the start point.
   *
   * @return None.
   */
  void SetStartPoint(const PointF& point);

  /**
   * @brief Get the end point.
   *
   * @details Start point and end point are required for a line annotation. They have effect on line annotation's
   *          appearance.
   *
   * @return The end point. A point with value (0, 0) may also mean that no start point is found.
   */
  PointF GetEndPoint() const;
  /**
   * @brief Set the end point.
   *
   * @details Start point and end point are required for a line annotation. They have effect on line annotation's
   *          appearance.<br>
   *          If user wants the new end point has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting new end point.
   *
   * @param[in] point  New point that specifies the end point.
   *
   * @return None.
   */
  void SetEndPoint(const PointF& point);

  /**
   * @brief Check whether the content of current line annotation should be replicated as a caption in the appearance
   *        or not.
   *
   * @return <b>true</b> means the content should be replicated as
   *         a caption in the appearance of current line annotation.
   *         <b>false</b> means not to replicate the content as a caption in the appearance of current lint annotation.
   */
  bool HasCaption() const;
  /**
   * @brief Set the flag which is used to decide whether the content of current line annotation should be replicated
   *        as a caption in the appearance or not.
   *
   * @details This property has effect on line annotation's appearance. If user wants the effect to be shown in
   *          annotation's appearance, please call function @link Annot::ResetAppearanceStream @endlink after this function.
   *
   * @param[in] cap  <b>true</b> means the content should be replicated as a caption in the appearance of
   *                 current line annotation, while <b>false</b> means not.
   *
   * @return None.
   */
  void EnableCaption(bool cap);

  /**
   * @brief Get the position type of caption.
   *
   * @details Only when current line annotation have a caption, this property is meaningful and has effect on line's
   *          annotation's appearance. Function @link Line::HasCaption @endlink can be used to check if current line
   *          annotation should have a caption, and function @link Line::EnableCaption @endlink can be used to change the
   *          status.
   *
   * @return The position type of caption. Please refer to values starting from @link Line::e_CapPosInline @endlink and
   *         this would be one of these values.
   */
  CapPos GetCaptionPositionType() const;
  /**
   * @brief Set the position type of caption.
   *
   * @details Only when current line annotation have a caption, this property is meaningful and has effect on line's
   *          annotation's appearance. Function @link Line::HasCaption @endlink can be used to check if current line
   *          annotation should have a caption, and function @link Line::EnableCaption @endlink can be used to change the
   *          status.<br>
   *          If user wants the effect to be shown in annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after this function.
   *
   * @param[in] cap_position  The position type of caption. Please refer to values starting from
   *                          @link Line::e_CapPosInline @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetCaptionPositionType(CapPos cap_position);
  /**
   * @brief Get caption offset values.
   *
   * @details Caption offset is the offset of caption from its normal position.<br>
   *          Only when current line annotation have a caption, this property is meaningful and has effect on line's
   *          annotation's appearance. Function @link Line::HasCaption @endlink can be used to check if current line
   *          annotation should have a caption, and function @link Line::EnableCaption @endlink can be used to change the
   *          status.
   *
   * @return A Offset object that receives horizontal offset and vertical offset for caption.<br>
   *         A Offset object with value (0, 0) may also mean that no caption offset values can be found.
   */
  Offset GetCaptionOffset() const;
  /**
   * @brief Set caption offset values.
   *
   * @details Caption offset is the offset of caption from its normal position.<br>
   *          Only when current line annotation have a caption, this property is meaningful and has effect on line's
   *          annotation's appearance. Function @link Line::HasCaption @endlink can be used to check if current line
   *          annotation should have a caption, and function @link Line::EnableCaption @endlink can be used to change the
   *          status.<br>
   *          If user wants the effect to be shown in annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after this function.
   *
   * @param[in] offset  New offset values .
   *
   * @return None.
   */
  void SetCaptionOffset(const Offset& offset);

  /**
   * @brief Get the length of leader line.
   *
   * @details Leader lines extend from each endpoint of a line perpendicular to the line itself. A positive value means
   *          that the leader lines appear in the direction that is clockwise when traversing the line from
   *          its start point to its end point; a negative value indicates the opposite direction. Specially,
   *          even the length of leader line is 0, the line annotation can still have leader line extension and
   *          leader line offset. For this case, the direction of leader line is same as positive length value
   *          in order that the direction or position of leader line extension and offset can still be judged.<br>
   *          For more details, please refer to "Line Annotations" in Section 8.4.5 "Annotation Types"
   *          of <PDF reference 1.7> .
   *
   * @return The length of leader line.
   */
  float GetLeaderLineLength() const;
  /**
   * @brief Set the length of leader line.
   *
   * @details Leader lines extend from each endpoint of a line perpendicular to the line itself. A positive value means
   *          that the leader lines appear in the direction that is clockwise when traversing the line from
   *          its start point to its end point; a negative value indicates the opposite direction. Specially,
   *          even the length of leader line is 0, the line annotation can still have leader line extension and
   *          leader line offset. For this case, the direction of leader line is same as positive length value
   *          in order that the direction or position of leader line extension and offset can still be judged.<br>
   *          For more details, please refer to "Line Annotations" in Section 8.4.5 "Annotation Types"
   *          of <PDF reference 1.7> .
   *
   * @param[in] length  The length of leader lines. See details part for more details.
   *                    0 means no leader line.
   *
   * @return None.
   */
  void SetLeaderLineLength(float length);
  /**
   * @brief Get the length of leader line extension.
   *
   * @details Leader line extensions extend from the line proper 180 degrees from the leader lines.<br>
   *          For more details, please refer to "Line Annotations" in Section 8.4.5 "Annotation Types"
   *          of <PDF reference 1.7> .
   *
   * @return The length of leader line extension.
   */
  float GetLeaderLineExtensionLength() const;
  /**
   * @brief Set the length of leader line extension.
   *
   * @details Leader line extensions extend from the line proper 180 degrees from the leader lines.<br>
   *          For more details, please refer to "Line Annotations" in Section 8.4.5 "Annotation Types"
   *          of <PDF reference 1.7> .
   *
   * @param[in] extension_length  The length of leader line extension. It should be a non-negative value.
   *                              0 means no leader line extension.
   *
   * @return None.
   */
  void SetLeaderLineExtensionLength(float extension_length);

  /**
   * @brief Get the length of leader line offset.
   *
   * @details Leader line offset is the amount of empty space between the endpoints of the line annotation and
   *          the beginning of the leader lines.<br>
   *          For more details, please refer to "Line Annotations" in Section 8.4.5 "Annotation Types"
   *          of <PDF reference 1.7> .
   *
   * @return The length of leader line offset.
   */
  float GetLeaderLineOffset() const;
  /**
   * @brief Set the length of leader line offset.
   *
   * @details Leader line offset is the amount of empty space between the endpoints of the line annotation and
   *          the beginning of the leader lines.<br>
   *          For more details, please refer to "Line Annotations" in Section 8.4.5 "Annotation Types"
   *          of <PDF reference 1.7> .
   *
   * @param[in] offset  The length of leader line offset. It should be a non-negative value.
   *                    0 means no leader line extension.
   *
   * @return None.
   */
  void SetLeaderLineOffset(float offset);

  /**
   * @brief Set the scale ratio string for measuring.
   *
   * @details A line annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Scale ratio string expresses the scale radio of the drawing in the region.
   *          Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] ratio  A UTF-8 byte string expressing the scale ratio. The string should be like: "1/4 in = 1 ft",
   *                   indicating that 1/4 inches in default user space is equivalent to 1 foot
   *                   in real-world measurements.
   *
   * @return None.
   */
  void SetMeasureRatio(const String& ratio);

  /**
   * @brief Get the scale ratio string for measuring.
   *
   * @details A line annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Scale ratio string expresses the scale radio of the drawing in the region.
   *          Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @return A UTF-8 byte string that expresses the scale ratio.
   */
  String GetMeasureRatio();

  /**
   * @brief Get the scale ratio Unicode string for measuring.
   *
   * @details A line annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Scale ratio string expresses the scale radio of the drawing in the region.
   *          Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @return A Unicode string that expresses the scale ratio.
   */
  WString GetMeasureRatioW();

  /**
   * @brief Set the label for displaying the units for measuring.
   *
   * @details A line annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this should be one of these values.
   * @param[in] unit          A UTF-8 text string that specifies a label for displaying the units.
   *
   * @return None.
   */
  void SetMeasureUnit(MeasureType measure_type, const String& unit);

  /**
   * @brief Get the label for displaying the units for measuring.
   *
   * @details A line annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this should be one of these values.
   *
   * @return A UTF-8 text string that represents a label for displaying the units.
   */
  String GetMeasureUnit(MeasureType measure_type);

  /**
   * @brief Get the label (in Unicode string) for displaying the units for measuring.
   *
   * @details A line annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this should be one of these values.
   *
   * @return A Unicode string that represents a label for displaying the units.
   */
  WString GetMeasureUnitW(MeasureType measure_type);

  /**
   * @brief Set the conversion factor for measuring.
   *
   * @details A line annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this would be one of these values.
   * @param[in] factor        The conversion factor.
   *
   * @return None.
   */
  void SetMeasureConversionFactor(MeasureType measure_type, float factor);

  /**
   * @brief Get the conversion factor for measuring.
   *
   * @details A line annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this would be one of these values.
   *
   * @return The conversion factor.
   */
  float GetMeasureConversionFactor(MeasureType measure_type);
};

/**
 * An ink annotation represents a freehand "scribble" composed of one or more disjoint paths. <br>
 * Ink annotation is a kind of markup annotation, so class @link Ink @endlink is derived from
 * class @link Markup @endlink, offers functions to get/set ink annotation's properties and also and
 * reset appearance stream of an ink annotation.<br>
 * For a ink annotation, ink list property is required. So please ensure that an ink annotation has
 * valid ink list property before resetting its appearance stream; otherwise the ink annotation cannot be
 * reset appearance stream.
 *
 * @note For a newly created ink annotation, if user calls function @link Annot::ResetAppearanceStream @endlink
 *       (inherited from @link Ink @endlink's parent class) directly after setting required ink list property and
 *       not setting any other properties, the default appearance will be used:<br>
 *       border width = 2.0, border style = @link BorderInfo::e_Solid @endlink,
 *       border color = 0xFFFF0000 (red), opacity = 1.0.
 *
 * @see @link Markup @endlink
 */
class Ink FS_FINAL : public Markup {
 public:
  /** @brief Constructor. */
  Ink() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Ink(const Annot& annot);
  /** @brief Destructor. */
  ~Ink() {}
  /**
   * @brief Get ink list data.
   *
   * @details Ink list property is required for an ink annotation and this property has effect on ink annotation's
   *          appearance. The ink list contains one or more stroked path. <br>
   *          In Foxit PDF SDK, class @link common::Path @endlink is used to represent the ink list data,
   *          but the point types for path object have been specially simplified for ink list.
   *          Only @link common::Path::e_TypeMoveTo @endlink and @link common::Path::e_TypeLineTo @endlink types are
   *          used for points in the ink list:
   *          <ul>
   *          <li>a point with type @link common::Path::e_TypeMoveTo @endlink means that
   *              this point is the start point of a stroked path. Usually the first in path object should be this type.
   *          </li>
   *          <li>a point with type @link common::Path::e_TypeLineTo @endlink means that
   *              this point is in a stroked path, which is started by a point with type
   *              @link common::Path::e_TypeMoveTo @endlink, and when function @link Annot::ResetAppearanceStream @endlink
   *              (inherited from Ink's parent class) is called, Foxit PDF SDK will connect this point with
   *              other points by curves.</li>
   *          </ul>
   *          Operations such as move the ink annotation, or set a new ink path to this annotation will update
   *          the ink path data, so that the previous returned path object would become invalid. In this case,
   *          user should call this function again to obtain the new path object.
   *
   * @return The ink list data. If the return value of function @link common::Path::IsEmpty @endlink for
   *         the returned path object is <b>true</b>, that means no ink list data can be found.
   */
  common::Path GetInkList();

  /**
   * @brief Set ink list data.
   *
   * @details Ink list property is required for an ink annotation and this property has effect on ink annotation's
   *          appearance. The ink list contains one or more stroked path. <br>
   *          In Foxit PDF SDK, class @link common::Path @endlink is used to represent the ink list data,
   *          but the point types for path object have been specially simplified for ink list.
   *          Only @link common::Path::e_TypeMoveTo @endlink and @link common::Path::e_TypeLineTo @endlink types are used for points
   *          in the ink list:
   *          <ul>
   *          <li>a point with type @link common::Path::e_TypeMoveTo @endlink means
   *              that this point is the start point of a stroked path. Usually the first in path object should
   *              be this type.
   *          </li>
   *          <li>a point with type @link common::Path::e_TypeLineTo @endlink means
   *              that this point is in a stroked path, which is started by a point with with type
   *              @link common::Path::e_TypeMoveTo @endlink, and when function @link Annot::ResetAppearanceStream @endlink
   *              (inherited from Ink's parent class) is called, Foxit PDF SDK will connect this point with
   *              other points by curves.</li>
   *          </ul>
   *          Specially, if input parameter <i>ink_list</i> contains bezier points (for example, added by function
   *          @link common::Path::CubicBezierTo @endlink), the control points will be ignored and only the target point will
   *          be used in the ink list data.<br>
   *          User is strongly recommended to pass a valid path object only with point types
   *          @link common::Path::e_TypeMoveTo @endlink and @link common::Path::e_TypeLineTo @endlink.<br>
   *          If user wants the effect to be shown in annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after this function.
   *
   * @param[in] ink_list  New path object which specifies the new list data.
   *
   * @return None.
   */
  void SetInkList(const common::Path& ink_list);
};

/**
 * A stamp annotation displays text or graphics intended to look as if they were stamped on the page with
 * a rubber stamp.<br>
 * A stamp annotation's appearance can be with an icon or a bitmap. Currently, Foxit PDF SDK does not have
 * any default appearance for predefined standard stamp icons, so user should set a customized annotation icon provider
 * to Foxit PDF SDK by function @link common::Library::SetAnnotIconProviderCallback @endlink if the stamp is represented
 * by icon.<br>
 * Stamp annotation is a kind of markup annotation, so class @link Stamp @endlink is derived from
 * class @link Markup @endlink, and also offers functions to get/set stamp annotation's properties and
 * reset appearance stream of a stamp annotation.<br>
 * Before resetting appearance stream of a stamp annotation, please ensure a stamp annotation has been
 * set valid bitmap or image, or it has an icon name with the supported customized annotation icon provider
 * being set to Foxit PDF SDK; otherwise the stamp annotation cannot be reset appearance stream.
 *
 * @note For a newly created stamp annotation, some properties will be set with default values:<br>
 *       opacity = 1.0, icon name = "Draft".<br>
 *       Before calling @link Annot::ResetAppearanceStream @endlink (inherited from @link Stamp @endlink's parent class),
 *       user should ensure to set a bitmap to the stamp by function @link Stamp::SetBitmap @endlink or
 *       @link Stamp::SetImage @endlink, or set a useful customized annotation icon provider to Foxit PDF SDK
 *       by function @link common::Library::SetAnnotIconProviderCallback @endlink.
 *
 * @see @link Markup @endlink
 * @see @link common::Library @endlink
 */
class Stamp FS_FINAL : public Markup {
 public:
  /** @brief Constructor. */
  Stamp() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Stamp(const Annot& annot);
#ifndef __EMSCRIPTEN_RENDER__
  /** @brief Destructor. */
  ~Stamp();
#endif
  /**
   * @brief Get icon name.
   *
   * @details This property may has effect on stamp annotation's appearance when a supported customized annotation
   *          icon provider being set to Foxit PDF SDK. Stamp annotation has predefined standard icon names: <br>
   *          "Approved", "AsIs", "Confidential", "Departmental", "Draft",
   *          "Experimental", "Expired", "Final", "ForComment", "ForPublicRelease",
   *          "NotApproved", "NotForPublicRelease", "Sold", "TopSecret".<br>
   *
   * @return Icon name string.
   */
   String GetIconName() const;
  /**
   * @brief Set icon name.
   *
   * @details This property may has effect on stamp annotation's appearance when a supported customized annotation
   *          icon provider being set to Foxit PDF SDK. Stamp annotation has predefined standard icon names: <br>
   *          "Approved", "AsIs", "Confidential", "Departmental", "Draft",
   *          "Experimental", "Expired", "Final", "ForComment", "ForPublicRelease",
   *          "NotApproved", "NotForPublicRelease", "Sold", "TopSecret".<br>
   *          Once user set a new icon name to current stamp annotation, please ensure the customized icon provider
   *          has been set to Foxit PDF SDK by function @link common::Library::SetAnnotIconProviderCallback @endlink
   *          before function @link Annot::ResetAppearanceStream @endlink (inherited from Stamp's parent class) is called.
   *          For a newly created stamp annotation, if current function is not called,
   *          icon name will be "Draft" by default.<br>
   *          If user wants the new icon name has effect on annotation's appearance, please ensure a supported
   *          customized annotation icon provider has been set to Foxit PDF SDK and then call function
   *          @link Annot::ResetAppearanceStream @endlink after setting the new icon name.
   *
   * @param[in] icon_name  New icon name string to be set. An empty icon name string means icon of current
   *                       stamp annotation would be treated as "Draft".
   *
   * @return None.
   */
  void SetIconName(const char* icon_name);
  /**
   * @brief Set bitmap to current stamp annotation.
   *
   * @details If user wants the new bitmap has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting the new bitmap.
   *
   * @param[in] bitmap  A bitmap to be set to current stamp.
   *
   * @return None.
   */
  void SetBitmap(const common::Bitmap& bitmap);

  /**
   * @brief Set image to current stamp annotation, with a specified frame index.
   *
   * @details Input image may contain multiple frames, and only one frame of the image can be set to current stamp
   *          annotation.<br>
   *          If user wants the new image has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting the new image.
   *
   * @param[in] image        An image. One of its frames will be set to current stamp.
   *                         This image contains at least one frame and the image type should not be
   *                         @link common::Image::e_Unknown @endlink.
   * @param[in] frame_index  Frame index. Valid range: from 0 to (<i>count</i>-1).
   *                         <i>count</i> is returned by function @link common::Image::GetFrameCount @endlink.
   * @param[in] compress     Compress algorithm type used to compress image data.
   *                         Currently, it only supports 2 valid value:<br>
   *                         <ul>
   *                         <li>0: no compress.</li>
   *                         <li>1: do default compress.</li>
   *                         </ul>
   *
   * @return None.
   */
  void SetImage(const common::Image& image, int frame_index, int compress);

  /**
    * @brief Set rotation angle (in clockwise).
    *
    * @details This property has effect on stamp annotation's appearance. If user wants the effect to be shown in
    *          annotation's appearance, please call function @link Annot::ResetAppearanceStream @endlink after this function.
    *
    * @param[in] angle  New rotation angle (in clockwise) to be set to current annotation. Value range: from 0 to 360.
    *
    * @return None.
    */
   void SetRotation(int angle);

   /**
    * @brief Get current rotation angle (in clockwise).
    *
    * @return Current rotation angle (in clockwise). Value range: from 0 to 360.
    */
  int GetRotation();

  /**
   * @brief Rotate current annotation from current state with specified angle degree in clockwise.
   *
   * @param[in] angle  Angle degree value, which is used to rotate current annotation from current state in clockwise.
   *                   Value range: from 0 to 360. Specially, if the input value is 0 or 360 (which means not to
   *                   rotate current annotation), current function will do nothing.
   *
   * @return None.
   */
  void Rotate(int angle);
};

/**
 * A screen annotation specifies a region of a page upon which media clips may be played. It also serves as an object
 * from which actions can be triggered. Usually, rendition action is set to a screen annotation in order that
 * the screen annotation can be used to play media clip.<br>
 * Class @link annots::Screen @endlink is derived from @link Annot @endlink, and offers functions to get/set link annotation's properties and
 * reset appearance stream of a screen annotation. Appearance stream of a screen annotation is used for printing (if possible)
 * and when the related media clip is not being played.
 *
 * @note For a newly created screen annotation, it has no border information and no border color.
 *
 * @see @link Annot @endlink
 */
class Screen FS_FINAL : public Annot {
 public:
  /** @brief Constructor. */
  Screen() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Screen(const Annot& annot);
  /** @brief Destructor. */
  virtual ~Screen() {}

  /**
   * @brief Set image to current screen annotation, with a specified frame index.
   *
   * @details Input image may contain multiple frames, and only one frame of the image can be set to current stamp
   *          annotation.<br>
   *          If user wants the effect to be shown in annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after this function.
   *
   * @param[in] image        An image. One of its frames will be set to current stamp.
   *                         This image contains at least one frame and the image type should not be
   *                         @link common::Image::e_Unknown @endlink.
   * @param[in] frame_index  Frame index. Valid range: from 0 to (<i>count</i>-1).
   *                         <i>count</i> is returned by function @link common::Image::GetFrameCount @endlink.
   * @param[in] compress     Compress algorithm type used to compress image data.
   *                         Currently, it only supports 2 valid value:<br>
   *                         <ul>
   *                         <li>0: no compress.</li>
   *                         <li>1: do default compress.</li>
   *                         </ul>
   *
   * @return None.
   */
  void SetImage(const common::Image& image, int frame_index, int compress);

  /**
   * @brief Get the appearance characteristics dictionary (known as "MK" dictionary as well).
   *
   * @return A PDF dictionary that represents the "MK" dictionary.
   *         If this dictionary is not set to a screen annotation (including current one),
   *         please call function @link objects::PDFObject::Release @endlink
   *         (inherited from @link objects::PDFDictionary @endlink's parent class) to release it.
   */
  pdf::objects::PDFDictionary* GetMKDict() const;

  /**
   * @brief Set the appearance characteristics dictionary (known as "MK" dictionary as well).
   *
   * @param[in] dict  A PDF dictionary that represents the new "MK" dictionary to be set.
   *                  User should not release this dictionary after setting it to a screen annotation.
   */
  void SetMKDict(pdf::objects::PDFDictionary* dict);

  /**
   * @brief Set the rotation of the image used for the appearance of current screen annotation.
   *
   * @details This property has effect on annotation's appearance. If user wants the effect to be shown
   *          in annotation's appearance, please call function @link Annot::ResetAppearanceStream @endlink
   *          after this function.
   *
   * @param[in] rotate  Rotation value. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                    this should be one of these values except @link common::e_RotationUnknown @endlink.
   *
   * @return None.
   */
  void SetRotation(common::Rotation rotate);

  /**
   * @brief Get the rotation of the image used for the appearance of current screen annotation.
   *
   * @return Rotation value of the image. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *         this would be one of these values.
   */
  common::Rotation GetRotation();

  /**
   * @brief Get opacity value.
   *
   * @details This property has effect on annotation's appearance.
   *
   * @return The opacity value. Valid range: 0.0 to 1.0.
   *         0.0 means full transparency and 1.0 means full opaque.
   */
  float GetOpacity() const;
  /**
   * @brief Set opacity value.
   *
   * @details This property has effect on annotation's appearance. If user wants the effect to be shown
   *          in annotation's appearance, please call function @link Annot::ResetAppearanceStream @endlink
   *          after this function.
   *
   * @param[in] opacity  The new opacity value. Valid range: 0.0 to 1.0 .
   *                     0.0 means full transparency and 1.0 means full opaque.
   *
   * @return None.
   */
  void SetOpacity(float opacity);

  /**
   * @brief Get title of current screen annotation.
   *
   * @return The title string.
   */
  WString GetTitle() const;
  /**
   * @brief Set title of current screen annotation.
   *
   * @param[in] title  The title string to be set.
   *
   * @return None.
   */
  void SetTitle(const WString& title);

  /**
   * @brief Get action.
   *
   * @details This function cannot be used to get action which is used as additional action.
   *          If user wants to get any additional action, please refer to class @link actions::AdditionalAction @endlink for more details.
   *
   * @return An action object that receives the action data. If the return value of function
   *         @link actions::Action::IsEmpty @endlink for the returned action object is <b>true</b>, that means no action.
   */
  actions::Action GetAction();
  /**
   * @brief Set action.
   *
   * @details This function cannot be used to set action which is used as additional action.
   *          If user wants to set any additional action, please refer to class @link actions::AdditionalAction @endlink for more details.
   *
   * @param[in] action  New action to be set. It should be valid.
   *                    Currently only support following types as the new action:<br>
   *                    @link actions::Action::e_TypeGoto @endlink,
   *                    @link actions::Action::e_TypeURI @endlink,
   *                    @link actions::Action::e_TypeJavaScript @endlink,
   *                    @link actions::Action::e_TypeNamed @endlink,
   *                    @link actions::Action::e_TypeGoToR @endlink,
   *                    @link actions::Action::e_TypeGoToE @endlink,
   *                    @link actions::Action::e_TypeSubmitForm @endlink,
   *                    @link actions::Action::e_TypeResetForm @endlink,
   *                    @link actions::Action::e_TypeHide @endlink,
   *                    @link actions::Action::e_TypeLaunch @endlink,
   *                    @link actions::Action::e_TypeImportData @endlink,
   *                    @link actions::Action::e_TypeRendition @endlink.
   *
   * @return None.
   */
  void SetAction(const actions::Action& action);
  /**
   * @brief Remove action.
   *
   * @details This function cannot be used to remove action which is used as additional action.
   *          If user wants to remove any additional action, please refer to class @link actions::AdditionalAction @endlink for more details.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  void RemoveAction();
};

/**
 * A polygon annotation displays a closed polygon on the page.<br>
 * Polygon annotation is a kind of markup annotation, so class @link Polygon @endlink is derived from
 * class @link Markup @endlink, and also offers functions to get/set polygon annotation's properties and
 * reset appearance stream of a polygon annotation. <br>
 * For a polygon annotation, vertexes property is required. So please ensure that a polygon annotation
 * has valid vertexes property before resetting its appearance stream; otherwise the polygon annotation cannot
 * be reset appearance stream.
 *
 * @note For a newly created polygon annotation,
 *       if user calls function @link Annot::ResetAppearanceStream @endlink directly
 *       after setting required vertexes property and not setting any other properties, the default appearance will
 *       be used:<br>
 *       border width = 2.0, border style = @link BorderInfo::e_Solid @endlink,
 *       border color = 0xFFFF0000 (red), opacity = 1.0.
 *
 * @see @link Markup @endlink
 */
class Polygon FS_FINAL : public Markup {
 public:
  /** @brief Constructor. */
  Polygon() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Polygon(const Annot& annot);
  /** @brief Destructor. */
  ~Polygon() {}
  /**
   * @brief Get fill color.
   *
   * @details This property has effect on polygon annotation's appearance.
   *
   * @return The fill color. Format: 0xRRGGBB.
   *         If no fill color can be found, 0x000000 will be returned.
   */
  RGB GetFillColor() const;

  /**
   * @brief Set fill color.
   *
   * @details This property has effect on polygon annotation's appearance. If user wants the new fill color has effect
   *          on annotation's appearance, please call function @link Annot::ResetAppearanceStream @endlink after setting
   *          the new fill color.
   *
   * @param[in] fill_color  New fill color to be set. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetFillColor(RGB fill_color);

  /**
   * @brief Get vertexes.
   *
   * @details Vertexes property is required for a polygon annotation and this property has effect on polygon
   *          annotation's appearance.
   *
   * @return A point array that represents the vertexes.
   */
  PointFArray GetVertexes();

  /**
   * @brief Set vertexes.
   *
   * @details Vertexes property is required for a polygon annotation and this property has effect on polygon
   *          annotation's appearance. If user wants the new vertexes have effect on annotation's appearance, please
   *          call function @link Annot::ResetAppearanceStream @endlink after setting the new vertexes.
   *
   * @param[in] vertexes  A valid point array for vertexes. It should contains at least 2 points as vertexes.
   *
   * @return None.
   */
  void SetVertexes(const PointFArray& vertexes);

  /**
   * @brief Set the scale ratio string for measuring.
   *
   * @details A polygon annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Scale ratio string expresses the scale radio of the drawing in the region.
   *          Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] ratio  A UTF-8 byte string expressing the scale ratio. The string should be like: "1/4 in = 1 ft",
   *                   indicating that 1/4 inches in default user space is equivalent to 1 foot
   *                   in real-world measurements.
   *
   * @return None.
   */
  void SetMeasureRatio(const String& ratio);

  /**
   * @brief Get the scale ratio string for measuring.
   *
   * @details A polygon annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Scale ratio string expresses the scale radio of the drawing in the region.
   *          Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @return A UTF-8 byte string that expresses the scale ratio.
   */
  String GetMeasureRatio();

  /**
   * @brief Get the scale ratio Unicode string for measuring.
   *
   * @details A polygon annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Scale ratio string expresses the scale radio of the drawing in the region.
   *          Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @return A Unicode string that expresses the scale ratio.
  */
  WString GetMeasureRatioW();

  /**
   * @brief Set the label for displaying the units for measuring.
   *
   * @details A polygon annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this should be one of these values.
   * @param[in] unit          A UTF-8 text string that specifies a label for displaying the units.
   *
   * @return None.
   */
  void SetMeasureUnit(MeasureType measure_type, const String& unit);

  /**
   * @brief Get the label for displaying the units for measuring.
   *
   * @details A polygon annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this should be one of these values.
   *
   * @return A UTF-8 text string that represents a label for displaying the units.
   */
  String GetMeasureUnit(MeasureType measure_type);

  /**
   * @brief Get the label (in Unicode string) for displaying the units for measuring.
   *
   * @details A polygon annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this should be one of these values.
   *
   * @return A Unicode string that represents a label for displaying the units.
   */
  WString GetMeasureUnitW(MeasureType measure_type);

  /**
   * @brief Set the conversion factor for measuring.
   *
   * @details A polygon annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this would be one of these values.
   * @param[in] factor        The conversion factor.
   *
   * @return None.
   */
  void SetMeasureConversionFactor(MeasureType measure_type, float factor);

  /**
   * @brief Get the conversion factor for measuring.
   *
   * @details A polygon annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this would be one of these values.
   *
   * @return The conversion factor.
   */
  float GetMeasureConversionFactor(MeasureType measure_type);
};

/**
 * A polyline annotation (PDF 1.5) is similar to a polygon, except that the first and last vertex are not
 * implicitly connected. <br>
 * Polyline annotation is a kind of markup annotation, so class @link PolyLine @endlink is derived from
 * class @link Markup @endlink, and also offers functions to get/set polyline annotation's properties and
 * reset appearance stream of a polyline annotation. <br>
 * For a polyline annotation, vertexes property is required. So please ensure that a polyline annotation
 * has valid vertexes property before resetting its appearance stream; otherwise the polyline annotation cannot
 * be reset appearance stream.
 *
 * @note For a newly created polyline annotation,
 *       if user calls function @link Annot::ResetAppearanceStream @endlink directly
 *       after setting required vertexes property and not setting any other properties,
 *       the default appearance will be used:<br>
 *       border width = 2.0, border style = @link BorderInfo::e_Solid @endlink,
 *       border color = 0xFFFF0000 (red), opacity = 1.0.
 *
 * @see @link Markup @endlink
 */
class PolyLine FS_FINAL : public Markup {
 public:
  /** @brief Constructor. */
  PolyLine() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit PolyLine(const Annot& annot);
  /** @brief Destructor. */
  ~PolyLine() {}
  /**
   * @brief Get fill color for some line ending styles.
   *
   * @details This property has effect on polyline annotation's appearance when the line ending style is one of
   *          following styles:<br>
   *          "Square", "Circle", "Diamond", "ClosedArrow", "RClosedArrow".
   *
   * @return The fill color. Format: 0xRRGGBB.
   *         If no fill color can be found, 0x000000 will be returned.
   */
  RGB GetStyleFillColor() const;
  /**
   * @brief Set fill color for some line ending styles.
   *
   * @details This property has effect on polyline annotation's appearance when the line ending style of start point
   *          or end point is one of following styles:<br>
   *          "Square", "Circle", "Diamond", "ClosedArrow", "RClosedArrow".
   *
   * @param[in] fill_color  New fill color to be set. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetStyleFillColor(RGB fill_color);

  /**
   * @brief Get vertexes.
   *
   * @details Vertexes property is required for a polyline annotation and this property has effect on polyline
   *          annotation's appearance.
   *
   * @return A point array that represents the vertexes.
   */
  PointFArray GetVertexes();

  /**
   * @brief Set vertexes.
   *
   * @details Vertexes property is required for a polyline annotation and this property has effect on polyline
   *          annotation's appearance. If user wants the new vertexes have effect on annotation's appearance, please
   *          call function @link Annot::ResetAppearanceStream @endlink after setting the new vertexes.
   *
   * @param[in] vertexes  A valid point array of vertexes. It should contains at least 2 points as vertexes.
   *
   * @return None.
   */
  void SetVertexes(const PointFArray& vertexes);
  /**
   * @brief Get line ending style of the start point.
   *
   * @details This property has effect on polyline annotation's appearance.
   *
   * @return The line ending style of the start point. Please refer to values starting from
   *         @link Markup::e_EndingStyleNone @endlink and this would be one of these values.
   */
  EndingStyle GetLineStartStyle() const;
  /**
   * @brief Set line ending style of the start point.
   *
   * @details This property has effect on polyline annotation's appearance.
   *          If user wants the new line ending style of start point has effect on annotation's appearance,
   *          please call function @link Annot::ResetAppearanceStream @endlink after setting the new line ending style
   *          of start point.
   *
   * @param[in] starting_style  The line ending style for the start point to be set.Please refer to values starting from
   *                            @link Markup::e_EndingStyleNone @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetLineStartStyle(EndingStyle starting_style);
  /**
   * @brief Get line ending style of the end point.
   *
   * @details This property has effect on polyline annotation's appearance.
   *
   * @return The line ending style of the end point. Please refer to values starting from
   *         @link Markup::e_EndingStyleNone @endlink and this would be one of these values.
   */
  EndingStyle GetLineEndStyle() const;
  /**
   * @brief Set line ending style of the end point.
   *
   * @details This property has effect on polyline annotation's appearance.
   *          If user wants the new line ending style of end point has effect on annotation's appearance,
   *          please call function @link Annot::ResetAppearanceStream @endlink after setting the new line ending style
   *          of end point.
   *
   * @param[in] ending_style  The line ending style for the end point to be set. Please refer to values starting from
   *                          @link Markup::e_EndingStyleNone @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetLineEndStyle(EndingStyle ending_style);

   /**
   * @brief Set the scale ratio string for measuring.
   *
   * @details A polyline annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Scale ratio string expresses the scale radio of the drawing in the region.
   *          Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] ratio  A UTF-8 byte string expressing the scale ratio. The string should be like: "1/4 in = 1 ft",
   *                   indicating that 1/4 inches in default user space is equivalent to 1 foot
   *                   in real-world measurements.
   *
   * @return None.
   */
  void SetMeasureRatio(const String& ratio);

  /**
   * @brief Get the scale ratio string for measuring.
   *
   * @details A polyline annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Scale ratio string expresses the scale radio of the drawing in the region.
   *          Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @return A UTF-8 byte string that expresses the scale ratio.
   */
  String GetMeasureRatio();

  /**
   * @brief Get the scale ratio string for measuring.
   *
   * @details A polyline annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Scale ratio string expresses the scale radio of the drawing in the region.
   *          Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @return A Unicode string that expresses the scale ratio.
   */
  WString GetMeasureRatioW();

  /**
   * @brief Set the label for displaying the units for measuring.
   *
   * @details A polyline annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this would be one of these values.
   * @param[in] unit          A UTF-8 text string that specifies a label for displaying the units.
   *
   * @return None.
   */
  void SetMeasureUnit(MeasureType measure_type, const String& unit);

  /**
   * @brief Get the label for displaying the units for measuring.
   *
   * @details A polyline annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this would be one of these values.
   *
   * @return A UTF-8 text string that represents a label for displaying the units.
   */
  String GetMeasureUnit(MeasureType measure_type);

  /**
   * @brief Get the label for displaying the units for measuring.
   *
   * @details A polyline annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this would be one of these values.
   *
   * @return A Unicode string that represents a label for displaying the units.
   */
  WString GetMeasureUnitW(MeasureType measure_type);

  /**
   * @brief Set the conversion factor for measuring.
   *
   * @details A polyline annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this should be one of these values.
   * @param[in] factor        The conversion factor.
   *
   * @return None.
   */
  void SetMeasureConversionFactor(MeasureType measure_type, float factor);

  /**
   * @brief Get the conversion factor for measuring.
   *
   * @details A polyline annotation may have a measure dictionary that specifies an alternate coordinate system
   *          for a region of a page. Please refer to P745 in <PDF Reference 1.7> for more details.
   *
   * @param[in] measure_type  Measure type. Please refer to values starting from
   *                          @link Markup::e_MeasureTypeX @endlink and this should be one of these values.
   *
   * @return The conversion factor.
   */
  float GetMeasureConversionFactor(MeasureType measure_type);
};

/**
 * A caret annotation (PDF 1.5) is a visual symbol that indicates the presence of text edits.<br>
 * Caret annotation is a kind of markup annotation, so class @link Caret @endlink is derived from
 * class @link Markup @endlink, and also offers functions to get/set caret annotation's properties and
 * reset appearance stream of a caret annotation.<br>
 *
 * @note For a newly created caret annotation, if user calls function @link Annot::ResetAppearanceStream @endlink directly
 *       without setting any other properties, the default appearance will be used:<br>
 *       border color = 0xFFA7ABE8 (a kind of purple), opacity = 1.0,
 *
 * @see @link Markup @endlink
 */
class Caret FS_FINAL : public Markup {
 public:
  /** @brief Constructor. */
  Caret() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Caret(const Annot& annot);
  /** @brief Destructor. */
  ~Caret() {}

  /**
   * @brief Get the inner rectangle.
   *
   * @details This property has effect on caret annotation's appearance. For a caret annotation, inner rectangle means
   *          the actual boundaries of underlying caret. The inner rectangle could be just the same as or less than
   *          the annotation's rectangle, and should never be larger than annotation's rectangle.
   *
   * @return The inner rectangle.
   */
  RectF GetInnerRect() const;
  /**
   * @brief Set the inner rectangle.
   *
   * @details This property has effect on caret annotation's appearance. For a caret annotation, inner rectangle means
   *          the actual boundaries of underlying caret. The inner rectangle could be just the same as or less than
   *          the annotation's rectangle, and should never be larger than annotation's rectangle.<br>
   *          If user wants the new inner rectangle have effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting the new inner rectangle.
   *
   * @param[in] inner_rect  New inner rectangle to be set. It should be same as or less than annotation's rectangle.
   *
   * @return None.
   */
  void SetInnerRect(const RectF& inner_rect);
};

/**
 * A file attachment annotation contains a reference to a file, which typically is embedded in the PDF file.<br>
 * File attachment annotation is a kind of markup annotation, so class @link FileAttachment @endlink is derived from
 * class @link Markup @endlink, and also offers functions to get/set file attachment annotation's properties and
 * reset appearance stream of a file attachment annotation.<br>
 *
 * @note For a newly created file attachment annotation, if user calls function @link Annot::ResetAppearanceStream @endlink
 *       directly without setting any properties, the default appearance will be used:<br>
 *       border color = 0xFFFF0000 (red), opacity = 1.0, icon name = "PushPin".
 *
 * @see @link Markup @endlink
 */
class FileAttachment FS_FINAL : public Markup {
 public:
  /** @brief Constructor. */
  FileAttachment() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit FileAttachment(const Annot& annot);
  /** @brief Destructor. */
  ~FileAttachment() {}

  /**
   * @brief Set a file specification, which should specify an embedded file.
   *
   * @param[in] file_spec  A valid file specification object to be set.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetFileSpec(const FileSpec& file_spec);

  /**
   * @brief Get the file specification.
   *
   * @return The file specification object. If the return value of function @link FileSpec::IsEmpty @endlink for
   *         the returned file specification object is <b>true</b>, that means no file specification property can be found.
   */
  FileSpec GetFileSpec();

  /**
   * @brief Get icon name.
   *
   * @details This property has effect on file attachment annotation's appearance. File attachment annotation has
   *          predefined standard icon names: <br>
   *          "Graph", "PushPin", "Paperclip", "Tag".<br>
   *          An empty icon name string means current File attachment annotation would be treated as "PushPin".<br>
   *
   * @return Icon name string.
   */
  String GetIconName() const;

  /**
   * @brief Set icon name.
   *
   * @details This property has effect on file attachment annotation's appearance. File attachment annotation has
   *          predefined standard icon names: <br>
   *          "Graph", "PushPin", "Paperclip", "Tag".<br>
   *          For a newly created file attachment annotation, if current function is not called, icon name will be
   *          "PushPin" by default.<br>
   *          If user wants the new icon name have effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting the new icon name.
   *
   * @param[in] icon_name  New icon name string to be set..
   *
   * @return None.
   */
  void SetIconName(const char* icon_name);
};

/**
 * A pop-up annotation displays text in a pop-up window for entry and editing. It typically does not appear alone
 * but is associated with a markup annotation, its parent annotation, and is used for editing the parent's text. <br>
 * Class @link annots::Popup @endlink is derived from class @link Annot @endlink and also offers functions to get/set pop-up annotation's properties.
 * Pop-up annotation has no appearance stream or associated actions of its own, so function
 * @link Annot::ResetAppearanceStream @endlink will always return <b>false</b> for a pop-up annotation.
 *
 * @see @link Annot @endlink
 */
class Popup FS_FINAL : public Annot {
 public:
  /** @brief Constructor. */
  Popup() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Popup(const Annot& annot);
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Popup(FS_HANDLE handle);
  /** @brief Destructor. */
  ~Popup() {}

  /**
   * @brief Get open status.
   *
   * @details Open status is a boolean value that specifies whether a note annotation should initially be
   *          displayed open:
   *          <ul>
   *          <li><b>true</b> means the note annotation should be initially be displayed open.</li>
   *          <li><b>false</b> means the note annotation should be initially be displayed closed.</li>
   *          </ul>
   *
   * @return Open status.
   */
  bool GetOpenStatus() const;
  /**
   * @brief Set open status.
   *
   * @details Open status is a boolean value that specifies whether a note annotation should initially be
   *          displayed open:
   *          <ul>
   *          <li><b>true</b> means the note annotation should be initially be displayed open.</li>
   *          <li><b>false</b> means the note annotation should be initially be displayed closed.</li>
   *          </ul>
   *
   * @param[in] status  The new open status value.
   *
   * @return None.
   */
  void SetOpenStatus(bool status);

  /**
   * @brief Get related parent markup annotation.
   *
   * @return The related parent markup annotation. If the return value of function @link Annot::IsEmpty @endlink
   *         (inherited from @link Markup @endlink's parent class) for the returned markup annotation is <b>true</b>,
   *         that means current pop-up annotation does not have a markup annotation.
   */
  Markup GetParent();
};
#ifndef __FSDK_NO_PSINK__
/**
 * Class @link PSInk @endlink represents a Foxit custom annotation type, not a standard annotation type, which is used to
 * store data of pressure sensitive ink to PDF page. An existed PSInk annotation can be retrieved from PDF page
 * by functions @link pdf::PDFPage::GetAnnot @endlink and @link pdf::PDFPage::GetAnnotAtPoint @endlink. A new PSInk annotation would be
 * returned by function @link PSI::ConvertToPDFAnnot @endlink, instead of @link pdf::PDFPage::AddAnnot @endlink.<br>
 * Class @link annots::PSInk @endlink is derived from class @link Annot @endlink and also offers functions to
 * get/set annotation's basic properties of a PSInk annotation. Currently, some properties and functions can be
 * changed with a PSInk annotation, but will not have any effect on the appearance of PSInk annotation.
 * These properties include border information, and border color. These functions include
 * @link Annot::RemoveProperty @endlink.<br>
 * Besides, currently Foxit PDF SDK does not support to move a PSInk annotation by function @link Annot::Move @endlink.
 * Since PSInk is not a standard annotation, so is cannot be added to page by function @link pdf::PDFPage::AddAnnot @endlink;
 * instead, PSInk could be converted from a FSPSI object by function @link PSI::ConvertToPDFAnnot @endlink.
 *
 * @see @link pdf::PSI @endlink
 * @see @link pdf::PDFPage @endlink
 * @see @link Annot @endlink
 */
class PSInk FS_FINAL : public Annot {
 public:
  /** @brief Constructor. */
  PSInk() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit PSInk(const Annot& annot);
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PSInk(FS_HANDLE handle);
  /** @brief Destructor. */
  ~PSInk() {}
};
#endif
/**
 * A widget annotation is used to represent the appearance of form fields.<br>
 * Class @link annots::Widget @endlink is derived from class @link Annot @endlink and also offers functions to get/set widget annotation's properties.
 * Functions @link Widget::GetField @endlink and @link Widget::GetControl @endlink can be used to get the associated form field
 * and form control object. If a widget annotation is not associated with any form field or is associated with
 * a signature field, this widget can still get/set properties, but cannot be reset appearance. For these cases,
 * @link Annot::ResetAppearanceStream @endlink (inherited from Widget's parent class) will return <b>false</b> directly.
 *
 * @see @link Annot @endlink
 * @see @link interform::Field @endlink
 * @see @link interform::Control @endlink
 */
class Widget FS_FINAL : public Annot {
 public:
  /** @brief Constructor. */
  Widget() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Widget(const Annot& annot);
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Widget(FS_HANDLE handle);
#ifndef __EMSCRIPTEN_RENDER__
  /** @brief Destructor. */
   ~Widget();
#endif
  /**
   * @brief Get associated form field.
   *
   * @return The associated form field object.
   */
  interform::Field GetField();

  /**
   * @brief Get associated form control.
   *
   * @return  The associated form control object.
   */
  interform::Control GetControl();

  /**
   * @brief Get highlighting mode.
   *
   * @details Highlighting mode is the visual effect to be used when the mouse button is pressed or held down
   *          inside its active area
   *
   * @return Highlighting mode value. Please refer to values starting from @link Annot::e_HighlightingNone @endlink and
   *         this would be one of these values.
   */
  HighlightingMode GetHighlightingMode();

  /**
   * @brief Set highlighting mode.
   *
   * @details Highlighting mode is the visual effect to be used when the mouse button is pressed or held down
   *          inside its active area
   *
   * @param[in] mode  New highlighting mode value. Please refer to values starting from @link Annot::e_HighlightingNone @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
  void SetHighlightingMode(HighlightingMode mode);

  /**
   * @brief Get action.
   *
   * @details This function cannot be used to get action which is used as additional action.
   *          If user wants to get any additional action, please refer to class @link actions::AdditionalAction @endlink for more details.
   *
   * @return An action object that receives the action data. If the return value of function
   *         @link actions::Action::IsEmpty @endlink for the returned action object is <b>true</b>, that means no action.
   */
  actions::Action GetAction();

  /**
   * @brief Set action.
   *
   * @details This function cannot be used to set action which is used as additional action.
   *          If user wants to set any additional action, please refer to class @link actions::AdditionalAction @endlink for more details.
   *
   * @param[in] action  New action to be set. It should be valid.
   *                    Currently only support following types as the new action:<br>
   *                    @link actions::Action::e_TypeGoto @endlink,
   *                    @link actions::Action::e_TypeURI @endlink,
   *                    @link actions::Action::e_TypeJavaScript @endlink,
   *                    @link actions::Action::e_TypeNamed @endlink,
   *                    @link actions::Action::e_TypeGoToR @endlink,
   *                    @link actions::Action::e_TypeGoToE @endlink,
   *                    @link actions::Action::e_TypeSubmitForm @endlink,
   *                    @link actions::Action::e_TypeResetForm @endlink,
   *                    @link actions::Action::e_TypeHide @endlink,
   *                    @link actions::Action::e_TypeLaunch @endlink,
   *                    @link actions::Action::e_TypeImportData @endlink,
   *                    @link actions::Action::e_TypeRendition @endlink.
   *
   * @return None.
   */
  void SetAction(const actions::Action& action);

  /**
   * @brief Remove action.
   *
   * @details This function cannot be used to remove action which is used as additional action.
   *          If user wants to remove any additional action, please refer to class @link actions::AdditionalAction @endlink for more details.
   *
   * @return None.
   */
  void RemoveAction();

  /**
   * @brief Check if a specified entry exists in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *
   * @param[in] mk_entry  An entry in MK dictionary. Please refer to values starting from
   *                      @link Annot::e_MKEntryRotation @endlink and this should be one of these values.
   *
   * @return <b>true</b> means the specified entry exists in the MK dictionary, while <b>false</b> means not.
   */
  bool HasMKEntry(MKEntry mk_entry);
  /**
   * @brief Remove a specified entry from the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *
   * @param[in] mk_entry  An entry in MK dictionary. Please refer to values starting from
   *                      @link Annot::e_MKEntryRotation @endlink and this should be one of these values.
   *
   * @return None.
   */
  void RemoveMKEntry(MKEntry mk_entry);
  /**
   * @brief Get the rotation value in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          The rotation in MK dictionary specifies the degrees by which the widget annotation is rotated
   *          counterclockwise relative to the page.
   *
   * @return The rotation value in MK dictionary. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *         this would be one of these values.
   *         Value @link common::e_RotationUnknown @endlink means no rotation in MK dictionary.
   */
  common::Rotation GetMKRotation() const;
  /**
   * @brief Set the rotation value in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          The rotation in MK dictionary specifies the degrees by which the widget annotation is rotated
   *          counterclockwise relative to the page.
   *
   * @param[in] rotation  The rotation value to be set in MK dictionary. Please refer to values starting from
   *                      @link common::e_Rotation0 @endlink and this should be one of these values except
   *                      @link common::e_RotationUnknown @endlink
   */
  void SetMKRotation(common::Rotation rotation);
  /**
   * @brief Get the border color in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *
   * @return The border color in MK dictionary. Value format: 0xRRGGBB. <br>
   *         0 may means no border color in MK dictionary. In this case, please call function
   *         @link Widget::HasMKEntry @endlink with value @link Annot::e_MKEntryBorderColor @endlink to check.
   */
  RGB GetMKBorderColor() const;
  /**
   * @brief Set the border color in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *
   * @param[in] color  The border color to be set in MK dictionary. Value format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetMKBorderColor(RGB color);
  /**
   * @brief Get the background color in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *
   * @return The background color in MK dictionary. Value format: 0xRRGGBB. <br>
   *         0 may means no background color in MK dictionary. In this case, please call function
   *         @link Widget::HasMKEntry @endlink with value @link Annot::e_MKEntryBackgroundColor @endlink to check.
   */
  RGB GetMKBackgroundColor() const;
  /**
   * @brief Set the background color in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *
   * @param[in] color  The background color to be set in MK dictionary. Value format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetMKBackgroundColor(RGB color);
  /**
   * @brief Get the normal caption string in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Normal caption in MK dictionary is used to displayed when the widget is not
   *          interacting with the user. This is applicable for widget associated with
   *          pushbutton field, check box field or radio button field. For other type of fields, this will be useless.
   *
   * @return Normal caption string.
   *         An empty string may means no normal caption in MK dictionary. In this case, please call function
   *         @link Widget::HasMKEntry @endlink with value @link Annot::e_MKEntryNormalCaption @endlink to check.
   */
  WString GetMKNormalCaption() const;
  /**
   * @brief Set the normal caption string in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Normal caption in MK dictionary is used to displayed when the widget is not
   *          interacting with the user. This is applicable for widgets associated with
   *          pushbutton field, check box field or radio button field. For other type of fields, this will be useless.
   *
   * @param[in] caption  Normal caption string to be set in MK dictionary. It can be an empty string.
   *
   * @return None.
   */
  void SetMKNormalCaption(const wchar_t* caption);
  /**
   * @brief Get the rollover caption string in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Rollover caption in MK dictionary is used to displayed when the user rolls the cursor into
   *          its active area without pressing the mouse button.
   *          This is applicable for widget associated with pushbutton field. For other type of fields,
   *          this will be useless.
   *
   * @return Rollover caption string.
   *         An empty string may means no rollover caption in MK dictionary. In this case, please call function
   *         @link Widget::HasMKEntry @endlink with value @link Annot::e_MKEntryRolloverCaption @endlink to check.
   */
  WString GetMKRolloverCaption() const;

  /**
   * @brief Set the rollover caption string in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Rollover caption in MK dictionary is used to displayed when the user rolls the cursor into
   *          its active area without pressing the mouse button.
   *          This is applicable for widget associated with pushbutton field. For other type of fields,
   *          this will be useless.
   *
   * @param[in] caption  Rollover caption string to be set in MK dictionary. It can be an empty string.
   *
   * @return None.
   */
  void SetMKRolloverCaption(const wchar_t* caption);

  /**
   * @brief Get the down caption string in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Down caption (or alternate caption) in MK dictionary is used to displayed when the mouse button is
   *          pressed within its active area. This is applicable for widget associated with pushbutton field.
   *          For other type of fields, this will be useless.
   *
   * @return Down caption string. An empty string may means no down caption in MK dictionary. In this case,
   *         please call function @link Widget::HasMKEntry @endlink with value
   *         @link Annot::e_MKEntryDownCaption @endlink to check.
   */
  WString GetMKDownCaption() const;

  /**
   * @brief Set the down caption string in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Down caption (or alternate caption) in MK dictionary is used to displayed when the mouse button is
   *          pressed within its active area. This is applicable for widget associated with pushbutton field.
   *          For other type of fields, this will be useless.
   *
   * @param[in] caption  Down caption string to be set in MK dictionary. It can be an empty string.
   *
   * @return None.
   */
  void SetMKDownCaption(const wchar_t* caption);

  /**
   * @brief Get the normal icon bitmap in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Normal icon in MK dictionary is used to displayed when the widget is not
   *          interacting with the user. This is applicable for widget associated with pushbutton field.
   *          For other type of fields, this will be useless.
   *
   * @return Normal icon bitmap. If function @link common::Bitmap::IsEmpty @endlink for the returned bitmap object returns <b>true</b>,
   *         that means current widget annotation does not have normal icon bitmap.
   */
  common::Bitmap GetMKNormalIconBitmap();

  /**
   * @brief Set a bitmap as normal icon in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Normal icon in MK dictionary is used to displayed when the widget is not
   *          interacting with the user. This is applicable for widget associated with pushbutton field.
   *          For other type of fields, this will be useless.
   *
   * @param[in] bitmap  A valid bitmap to be set as normal icon in MK dictionary.
   *
   * @return None.
   */
  void SetMKNormalIconBitmap(const common::Bitmap& bitmap);

  /**
   * @brief Set an image with specified frame index as normal icon in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Normal icon in MK dictionary is used to displayed when the widget is not
   *          interacting with the user. This is applicable for widget associated with pushbutton field.
   *          For other type of fields, this will be useless.
   *
   * @param[in] image        An image. One of its frames will be set as normal icon in MK dictionary.
   *                         This image should contain at least one frame and the image type should not be
   *                         @link common::Image::e_Unknown @endlink.
   * @param[in] frame_index  Frame index. Valid range: from 0 to (<i>count</i>-1).
   *                         <i>count</i> is returned by function @link common::Image::GetFrameCount @endlink.
   */
  void SetMKNormalIconImage(const common::Image& image, int frame_index);

  /**
   * @brief Get the rollover icon bitmap in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Rollover icon in MK dictionary is used to displayed when the user rolls the cursor into
   *          its active area without pressing the mouse button.
   *          This is applicable for widget associated with pushbutton field. For other type of fields,
   *          this will be useless.
   *
   * @return Rollover icon bitmap. If function @link common::Bitmap::IsEmpty @endlink for the returned bitmap object
   *         returns <b>true</b>, that means current widget annotation does not have rollover icon bitmap.
   */
  common::Bitmap GetMKRolloverIconBitmap();

  /**
   * @brief Set the rollover icon bitmap in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Rollover icon in MK dictionary is used to displayed when the user rolls the cursor into
   *          its active area without pressing the mouse button.
   *          This is applicable for widget associated with pushbutton field. For other type of fields,
   *          this will be useless.
   *
   * @param[in] bitmap  A valid bitmap to be set as rollover icon in MK dictionary.
   *
   * @return None.
   */
  void SetMKRolloverIconBitmap(const common::Bitmap& bitmap);

  /**
   * @brief Set an image with specified frame index as rollover icon in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Rollover icon in MK dictionary is used to displayed when the user rolls the cursor into
   *          its active area without pressing the mouse button.
   *          This is applicable for widget associated with pushbutton field. For other type of fields,
   *          this will be useless.
   *
   * @param[in] image        An image. One of its frames will be set as rollover icon in MK dictionary.
   *                         This image should contain at least one frame and the image type should not be
   *                         @link common::Image::e_Unknown @endlink.
   * @param[in] frame_index  Frame index. Valid range: from 0 to (<i>count</i>-1).
   *                         <i>count</i> is returned by function @link common::Image::GetFrameCount @endlink.
   */
  void SetMKRolloverIconImage(const common::Image& image, int frame_index);

  /**
   * @brief Get the down icon bitmap in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Down icon (or alternate icon) in MK dictionary is used to displayed when the mouse button is
   *          pressed within its active area. This is applicable for widget associated with pushbutton field.
   *          For other type of fields, this will be useless.
   *
   * @return Down icon bitmap. If function @link common::Bitmap::IsEmpty @endlink for the returned bitmap object returns <b>true</b>,
   *         that means current widget annotation does not have down icon bitmap.
   */
  common::Bitmap GetMKDownIconBitmap();

  /**
   * @brief Set the down icon bitmap in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Down icon (or alternate icon) in MK dictionary is used to displayed when the mouse button is
   *          pressed within its active area. This is applicable for widget associated with pushbutton field.
   *          For other type of fields, this will be useless.
   *
   * @param[in] bitmap  A valid bitmap to be set as down icon in MK dictionary.
   *
   * @return None.
   */
  void SetMKDownIconBitmap(const common::Bitmap& bitmap);

  /**
   * @brief Set an image with specified frame index as down icon in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          Down icon (or alternate icon) in MK dictionary is used to displayed when the mouse button is
   *          pressed within its active area. This is applicable for widget associated with pushbutton field.
   *          For other type of fields, this will be useless.
   *
   * @param[in] image        An image. One of its frames will be set as down icon in MK dictionary.
   *                         This image should contain at least one frame and the image type should not be
   *                         @link common::Image::e_Unknown @endlink.
   * @param[in] frame_index  Frame index. Valid range: from 0 to (<i>count</i>-1).
   *                         <i>count</i> is returned by function @link common::Image::GetFrameCount @endlink.
   */
  void SetMKDownIconImage(const common::Image& image, int frame_index);

  /**
   * @brief Get the icon fit information in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          The icon fit information specifies how to display the widget annotation's icon within
   *          its annotation rectangle. If present, the icon fit information applies to all of the annotation's icons.
   *          This is applicable for widget associated with pushbutton field. For other type of fields,
   *          this will be useless.
   *
   * @return An icon fit object, which contains the icon fit information in MK dictionary.
   *         If <i>scale way type</i> of icon fit object is 0, that means no icon fit information in MK dictionary.
   */
  IconFit GetMKIconFit() const;
  /**
   * @brief Set the icon fit information in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          The icon fit information specifies how to display the widget annotation's icon within
   *          its annotation rectangle. If present, the icon fit information applies to all of the annotation's icons.
   *          This is applicable for widget associated with pushbutton field. For other type of fields,
   *          this will be useless.
   *
   * @param[in] icon_fit  An icon fit object which represents the icon fit information to be set in MK dictionary.
   *                      If value of any member in this object is invalid, this function will throw exception
   *                      @link foxit::e_ErrParam @endlink.
   *                      Please refer to class @link IconFit @endlink to check the valid value range for each member.
   *
   * @return None.
   */
  void SetMKIconFit(const IconFit& icon_fit);

  /**
   * @brief Get the relation of icon and caption in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          The relation position of caption and icon specifies where to position the text of
   *          the widget annotation's caption relative to its icon.
   *          This is applicable for widget associated with pushbutton field. For other type of fields,
   *          this will be useless.
   *
   * @return The relation position of caption and icon. Please refer to @link Annot::e_MKRelationNoIcon @endlink
   *         values and it should be one of these values.
   */
  MKIconCaptionRelation GetMKIconCaptionRelation() const;

  /**
   * @brief Set the relation of icon and caption in the MK dictionary
   *
   * @details MK dictionary is an appearance characteristics dictionary to be used in
   *          constructing a dynamic appearance stream specifying the annotation's visual presentation on the page.
   *          The relation position of caption and icon specifies where to position the text of
   *          the widget annotation's caption relative to its icon.
   *          This is applicable for widget associated with pushbutton field. For other type of fields,
   *          this will be useless.
   *
   * @param[in] relation  The relation position of caption and icon. Please refer to values starting from
   *                      @link Annot::e_MKRelationNoIcon @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetMKIconCaptionRelation(MKIconCaptionRelation relation);

  /**
   * @brief Set the annotation's appearance state, which selects the applicable appearance stream from an appearance subdictionary.
   *
   * @param[in] appearance_state  The annotation's appearance state.
   *
   * @return None.
   */
  void SetAppearanceState(const String& appearance_state);

  /**
   * @brief Get the annotation's appearance state, which selects the applicable appearance stream from an appearance subdictionary.
   *
   * @return The annotation's appearance state.
   */
  String GetAppearanceState() const;

  /**
  * @brief Get the name of the annotation's appearance "ON" state.
  *
  * @return The name of the annotation's appearance "ON" state.
  */
  String GetAppearanceOnStateName() const;

#ifdef _SUPPORTWEBSDK_
  //Set push button icon form icon stream. stream is from doc::createIcon.
  //face: 0: normal, 1: down, 2: roller
  void  SetButtonIcon(objects::PDFStream* icon, int face);
#endif
};

/**
 * Class @link Redact @endlink represents a Foxit custom annotation type (not a standard annotation type). This kind of annotation
 * is used to mark some content of a PDF page and these content will be removed once the redact annotations are
 * applied. An existed redact annotation can be retrieved from PDF page by functions @link pdf::PDFPage::GetAnnot @endlink and
 * @link pdf::PDFPage::GetAnnotAtPoint @endlink. A new redact annotation would be returned by function
 * @link addon::Redaction::MarkRedactAnnot @endlink, instead of @link pdf::PDFPage::AddAnnot @endlink.<br>
 * Class @link annots::Redact @endlink is derived from class @link Markup @endlink and also offers functions to
 * get/set markup annotation's basic properties of a redact annotation.
 * Currently, @link Annot::SetBorderInfo @endlink can be used for a redact annotation, but will not
 * have any effect on the appearance of redact annotation.
 * Besides, redact annotation cannot be moved by function @link Annot::Move @endlink.
 *
 * @see @link addon::Redaction @endlink
 * @see @link pdf::PDFPage @endlink
 * @see @link Markup @endlink
 */
class Redact FS_FINAL : public Markup {
 public:
  /** @brief Constructor. */
  Redact() {}
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] annot  Parent class object.
   */
  explicit Redact(const Annot& annot);
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Redact(FS_HANDLE handle);
#ifndef __EMSCRIPTEN_RENDER__
  /** @brief Destructor. */
   ~Redact();
#endif  
  /**
   * @brief Get quadrilaterals.
   *
   * @details The order of points in a quadrilateral should be:
   *          <ul>
   *          <li>The first point is the point in left-top corner of the quadrilateral.</li>
   *          <li>The second point is the point in right-top corner of the quadrilateral.</li>
   *          <li>The third point is the point in left-bottom corner of the quadrilateral.</li>
   *          <li>The fourth point is the point in right-bottom corner of the quadrilateral.</li>
   *          </ul>
   *
   * @return A quadrilateral points array that receives the quadrilaterals value.
   */
  QuadPointsArray GetQuadPoints() const;

  /**
   * @brief Set quadrilaterals.
   *
   * @details This property has effect on the redact annotation's appearance.The order of points in a quadrilateral
   *          should be :
   *          <ul>
   *          <li>The first point is the point in left-top corner of the quadrilateral.</li>
   *          <li>The second point is the point in right-top corner of the quadrilateral.</li>
   *          <li>The third point is the point in left-bottom corner of the quadrilateral.</li>
   *          <li>The fourth point is the point in right-bottom corner of the quadrilateral.</li>
   *          </ul>
   *          If user wants the new quadrilaterals has effect on annotation's appearance, please call function
   *          @link Annot::ResetAppearanceStream @endlink after setting quadrilaterals.
   *
   * @param[in] quad_points_array  A valid array of quadrilaterals. It should not be an empty array.
   *
   * @return None.
   */
  void SetQuadPoints(const QuadPointsArray& quad_points_array);

  /**
   * @brief Get fill color.
   *
   * @return The fill color. Format: 0xRRGGBB.
   *         If no fill color can be found, 0x000000 will be returned.
   */
  RGB GetFillColor() const;
  /**
   * @brief Set fill color.
   *
   * @param[in] fill_color  New fill color to be set. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetFillColor(RGB fill_color);

  /**
   * @brief Get the filling color which is used for rollover appearance and will be used after redaction is applied.
   *
   * @return The fill color. Format: 0xRRGGBB.
   *         If no fill color can be found, 0x000000 will be returned.
   */
  RGB GetApplyFillColor() const;

  /**
   * @brief Set the filling color which is used for rollover appearance and will be used after redaction is applied.
   *
   * @param[in] fill_color  New fill color to be set. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetApplyFillColor(RGB fill_color);

  /**
   * @brief Get the overlay text.
   *
   * @return The overlay text string.
   */
  WString GetOverlayText() const;

  /**
   * @brief Set the overlay text.
   *
   * @param[in] overlay_text  The overlay text string to be set.
   *
   * @return None.
   */
  void SetOverlayText(const WString& overlay_text);

  /**
   * @brief Get alignment value of overlay text.
   *
   * @details This property has effect on the overlay text of redact annotation's appearance.
   *
   * @return The alignment value. Please refer to values starting from @link common::e_AlignmentLeft @endlink and
   *         this would be one of these values.
   */
  common::Alignment GetOverlayTextAlignment() const;

  /**
   * @brief Set alignment value of overlay text.
   *
   * @details This property has effect on the overlay text of redact annotation's appearance. If user wants the new alignment has effect
   *          on the overlay text of annotation's appearance, please call function @link Annot::ResetAppearanceStream @endlink after setting
   *          new alignment.
   *
   * @param[in] alignment  The new alignment value. Please refer to values starting from @link common::e_AlignmentLeft @endlink
   *                       and this should be one of these values.
   *
   * @return None.
   */
  void SetOverlayTextAlignment(common::Alignment alignment);

  /**
   * @brief Get default appearance data.
   *
   * @details This property has effect on redact annotation's appearance. Default appearance data can be used in
   *          formatting text.
   *
   * @return The default appearance data.
   */
  DefaultAppearance GetDefaultAppearance();

  /**
   * @brief Set default appearance data.
   *
   * @details This property has effect on redact annotation's appearance. Default appearance data can be used in
   *          formatting text.<br>
   *          If user wants the new default appearance data has effect on annotation's appearance,
   *          please call function @link Annot::ResetAppearanceStream @endlink after setting new default appearance data.
   *
   * @param[in] default_ap  The new default appearance data to be set.
   *                        <i>flags</i> of input data can be used to decide which information is/are to
   *                        be updated with the new data; for those no updated data, they will keep to use old data.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Specially, this function will return <b>false</b>
   *         if the parameter <i>default_ap</i> contains any incorrect value, for example:
   *         <ul>
   *         <li><i>flags</i> of input data includes the @link DefaultAppearance::e_FlagFont @endlink
   *             but <i>font</i> of input data is invalid.</li>
   *         <li><i>flags</i> of input data includes the @link DefaultAppearance::e_FlagFontSize @endlink
   *             but <i>text size</i> of input data is not bigger than zero.</li>
   *         </ul>
   */
  bool SetDefaultAppearance(const DefaultAppearance& default_ap);
	
  /**
   * @brief Apply current redact annotation: remove the text or graphics under annotation rectangle permanently.
   *
   * @details Once this functions is called successfully, all page content(text object, image object, and path object)
   *          within area of current redact annotation rectangle will be removed permanently. And current redact annotation
   *          will be removed (with its pop-up annotation if any) as well - that means current annotation object will
   *          be useless when this function succeeds. Area of current redact annotation rectangle will be filled by
   *          the color specified by function @link pdf::annots::Redact::SetApplyFillColor @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Apply();
};

/**
 * A sound annotation (PDF 1.2) is analogous to a text annotation except that instead of a text note,
 * it contains sound recorded from the computer's microphone or imported from a file.
 * Sound annotation is a kind of markup annotation, so class @link Sound @endlink is derived from
 * class @link Markup @endlink. Currently, only support to get the properties or data of a sound annotation.
 * Not suppoort to modify a sound annotation (including reseting appearance) yet.
 *
 * @see @link Markup @endlink
 */
class Sound FS_FINAL : public Markup{
 public:
  /**
   * @brief Enumeration for encoding format of sound sample data.
   *
   * @details Values of this enumeration must be used alone.
   */
  typedef enum _SampleEncodingFormat {
    /** @brief Unspecified or unsigned values in the range 0 to (2^B - 1). */
    e_SampleEncodingFormatRaw = 0,
    /** @brief Twos-complement values. */
    e_SampleEncodingFormatSigned = 1,
    /** @brief μ-law-encoded samples */
    e_SampleEncodingFormatMuLaw = 2,
    /** @brief A-law-encoded samples */
    e_SampleEncodingFormatALaw = 3
  } SampleEncodingFormat;
  

  /** @brief Constructor. */
  Sound() {}

 /**
  * @brief Constructor, with parent class object.
  *
  * @param[in] annot  Parent class object.
  */
  explicit Sound(const Annot& annot);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Sound(FS_HANDLE handle);

#ifndef __EMSCRIPTEN_RENDER__
  /** @brief Destructor. */
  ~Sound();
#endif

 /**
  * @brief Get the stream of sound data.
  *
  * @details The stream of sound data represents the sound and can be used to be played
  *          when the annotation is activated.<br>
  *          Specially, if function @link Sound::GetFileSpec @endlink returns a valid file specification object
  *          (whose @link FileSpec::IsEmpty @endlink returns <b>false</b>), please use that file specification object
  *          instead of the stream returned by this function.
  *
  * @return The stream of sound data.
  */
  objects::PDFStream* GetSoundStream() const;

 /**
  * @brief Get the sampling rate, in samples per second.
  *
  * @return The sampling rate. If there is any error, this function will return -1.
  */
  float GetSamplingRate() const;

 /**
  * @brief Get the count of sound channels.
  *
  * @return The count of sound channels.
  */
  int GetChannelCount() const;

 /**
  * @brief Get the number of bits per sample value per channel.
  *
  * @return The number of bits per sample value per channel.
  */
  int GetBits() const;

 /**
  * @brief Get the encoding format for the sample data.
  *
  * @return The encoding format for the sample data. Please refer to values starting from
  *         @link Sound::e_SampleEncodingFormatRaw @endlink and this would be one of these values.
  */
  SampleEncodingFormat GetSampleEncodingFormat() const;

 /**
  * @brief Get the name of the sound compression format used on the sample data.
  *
  * @return The name of the sound compression format used on the sample data.
  */
  String GetCompressionFormat() const;

 /**
  * @brief Get the file specification object which represents an external sound file.
  *
  * @details A sound may be defined in an external file (represented by a file specification object).
  *          The sound file should be self-describing, containing all information needed to render the sound; 
  *          no additional information need be present in the PDF file.<br>
  *          In this case, the returned stream object should be ignored.
  *
  * @return A file specification object which represents an external sound file. If the return value of
  *         function @link FileSpec::IsEmpty @endlink for the returned file specification object is <b>true</b>,
  *         that means no external sound file is used for current sound annotation.
  *         In this case, please use function @link Sound::GetSoundStream @endlink to get the sound data.
  */
  FileSpec GetFileSpec() const;
};

}  // namespace annots
}  // namespace pdf
}  // namespace foxit

#endif  // FS_ANNOT_H_

