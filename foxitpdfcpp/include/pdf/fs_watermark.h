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
 * @file fs_watermark.h
 * @brief Header file for PDF watermark related definitions and classes.
 */

#ifndef FS_WATERMARK_H_
#define FS_WATERMARK_H_

#include "common/fs_common.h"
#include "common/fs_image.h"
#include "pdf/fs_pdfdoc.h"

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
class WatermarkSettings;
class WatermarkTextProperties;

/**
 * This class is mainly used to construct a watermark with specified parameters, and then insert it to PDF page.
 * The watermark object can be constructed from text, bitmap or image, and PDF page.
 */
class Watermark FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, from specified text content.
   *
   * @param[in] document    A valid PDF document object, for which the constructed watermark will be used.
   * @param[in] text        A text string. This will be used as the content of the watermark.
   *                        It should not be an empty string.
   * @param[in] properties  Text properties for watermark.
   * @param[in] settings    Watermark settings, containing layout setting.
   */
  explicit Watermark(const PDFDoc& document, const wchar_t* text, const WatermarkTextProperties& properties,
                     const WatermarkSettings& settings);

  /**
   * @brief Constructor, from a specified bitmap.
   *
   * @param[in] document    A valid PDF document object, for which the constructed watermark will be used.
   * @param[in] bitmap      A valid bitmap object used as the content of the watermark.
   * @param[in] settings    Watermark settings, containing layout setting.
   */
  explicit Watermark(const foxit::pdf::PDFDoc& document, const foxit::common::Bitmap& bitmap, const foxit::pdf::WatermarkSettings& settings);

  /**
   * @brief Constructor, from a specified image.
   *
   * @param[in] document     A valid PDF document object, for which the constructed watermark will be used.
   * @param[in] image        A valid image object. One frame of this image will be used as
   *                         the content of the watermark. So, this image should contain at least one frame and
   *                         the image type should not be @link common::Image::e_Unknown @endlink.
   * @param[in] frame_index  Frame index, to specify which frame of the image will be used for the watermark.
   *                         Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                         @link common::Image::GetFrameCount @endlink.
   * @param[in] settings     Watermark settings, containing layout setting.
   */
  explicit Watermark(const foxit::pdf::PDFDoc& document, const foxit::common::Image& image, int frame_index,
                     const foxit::pdf::WatermarkSettings& settings);

  /**
   * @brief Constructor, from a specified page.
   *
   * @param[in] document  A valid PDF document object, for which the constructed watermark will be used.
   * @param[in] page      A valid PDF page, whose content will be used as the content of the watermark.
   * @param[in] settings  Watermark settings, containing layout setting.
   */
  explicit Watermark(const foxit::pdf::PDFDoc& document, const foxit::pdf::PDFPage& page, const foxit::pdf::WatermarkSettings& settings);

  /**
   * @brief Constructor, with another watermark object.
   *
   * @param[in] other  Another watermark object.
   */
  Watermark(const Watermark& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another watermark object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Watermark& operator = (const Watermark& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another watermark object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Watermark& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another watermark object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Watermark& other) const;

  /** @brief Destructor. */
  ~Watermark();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the original width of current watermark.
   *
   * @details The original size of a watermark is based on no scaling and no rotation.
   *
   * @return Watermark width.
   */
  float GetWidth() const;

  /**
   * @brief Get the original height of current watermark.
   *
   * @details The original size of a watermark is based on no scaling and no rotation.
   *
   * @return Watermark height.
   */
  float GetHeight() const;

  /**
   * @brief Insert current watermark into a PDF page.
   *
   * @details If current watermark is treated as page content (which is specified by <i>flags</i> of @link WatermarkSettings @endlink
   *          when current watermark is constructed), Foxit PDF SDK will generate content for the input PDF page
   *          by default after the watermark is inserted successfully. In this case , if user wants to render
   *          the PDF page correctly after this function has been called successfully, user is recommended to
   *          call function @link PDFPage::StartParse @endlink with parameter <i>is_reparse</i> <b>true</b>
   *          before rendering; otherwise, the page content may not be rendered as expected.
   *
   * @param[in] page  A PDF page, to which current watermark would be inserted. This page should belong to
   *                  the same document as current watermark belongs to. And the page should have been already parsed.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool InsertToPage(PDFPage page);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Watermark(FS_HANDLE handle =  NULL);
};

/** This class represents the watermark settings used to construct a watermark object from any supported resource. */
class WatermarkSettings FS_FINAL : public Object {
 public:
  /**
   * @brief Enumeration for watermark setting flags.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _Flags {
    /** @brief If set, the watermark will be a part of page content when inserted to a PDF page. */
    e_FlagASPageContents = 0x0000,
    /** @brief If set, the watermark will be an annotation when inserted to a PDF page. */
    e_FlagASAnnot = 0x0001,
    /** @brief If set, show watermark above other page content. */
    e_FlagOnTop = 0x0002,
    /** @brief If set, do not print a watermark. */
    e_FlagNoPrint = 0x0004,
    /** @brief If set, do not display a watermark. */
    e_FlagInvisible = 0x0008
  } Flags;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] position  Watermark position. Please refer to values starting from @link common::e_PosTopLeft @endlink and
   *                      this should be one of these values.
   * @param[in] offset_x  Horizontal offset, in points.
   * @param[in] offset_y  Vertical offset, in points.
   * @param[in] flags     Watermark flags. Please refer to values starting from
   *                      @link WatermarkSettings::e_FlagASPageContents @endlink and
   *                      this can be one or a combination of these values.
   * @param[in] scale_x   Horizontal scale coefficient. It should be greater than 0.001f.
   * @param[in] scale_y   Vertical scale coefficient. It should be greater than 0.001f.
   * @param[in] rotation  Rotation angle in degrees. It should be greater than 0.001f.
   * @param[in] opacity   Opacity in percents. Valid range: from 0 to 100.
   *                      0 for fully transparent and 100 for fully opaque.
   */
  explicit WatermarkSettings(const common::Position position, float offset_x, float offset_y, uint32 flags,
                      float scale_x, float scale_y, float rotation, int opacity)
      : position(position)
      , offset_x(offset_x)
      , offset_y(offset_y)
      , flags(flags)
      , scale_x(scale_x)
      , scale_y(scale_y)
      , rotation(rotation)
      , opacity(opacity) {}

  /** @brief Constructor. */
  WatermarkSettings()
      : position(CommonDefines::e_PosTopLeft)
      , offset_x(0)
      , offset_y(0)
      , flags(0)
      , scale_x(0)
      , scale_y(0)
      , rotation(0)
      , opacity(100) {}

  /**
   * @brief Constructor, with another watermark settings object.
   *
   * @param[in] settings  Another watermark settings object.
   */
  WatermarkSettings(const WatermarkSettings& settings)
      : position(settings.position)
      , offset_x(settings.offset_x)
      , offset_y(settings.offset_y)
      , flags(settings.flags)
      , scale_x(settings.scale_x)
      , scale_y(settings.scale_y)
      , rotation(settings.rotation)
      , opacity(settings.opacity) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] settings  Another watermark settings object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  WatermarkSettings& operator = (const WatermarkSettings& settings) {
    position = settings.position;
    offset_x = settings.offset_x;
    offset_y = settings.offset_y;
    flags = settings.flags;
    scale_x = settings.scale_x;
    scale_y = settings.scale_y;
    rotation = settings.rotation;
    opacity = settings.opacity;
    return *this;
  }

  /**
   * @brief Set value.
   *
   * @param[in] position  Watermark position. Please refer to values starting from @link common::e_PosTopLeft @endlink and
   *                      this should be one of these values.
   * @param[in] offset_x  Horizontal offset, in points.
   * @param[in] offset_y  Vertical offset, in points.
   * @param[in] flags     Watermark flags. Please refer to values starting from
   *                      @link WatermarkSettings::e_FlagASPageContents @endlink and
   *                      this can be one or a combination of these values.
   * @param[in] scale_x   Horizontal scale coefficient. It should be greater than 0.001f.
   * @param[in] scale_y   Vertical scale coefficient. It should be greater than 0.001f.
   * @param[in] rotation  Rotation angle in degrees. It should be greater than 0.001f.
   * @param[in] opacity   Opacity in percents. Valid range: from 0 to 100.
   *                      0 for fully transparent and 100 for fully opaque.
   *
   * @return None.
   */
  void Set(const common::Position position, float offset_x, float offset_y, uint32 flags, float scale_x, float scale_y,
           float rotation, int opacity) {
    this->position = position;
    this->offset_x = offset_x;
    this->offset_y = offset_y;
    this->flags = flags;
    this->scale_x = scale_x;
    this->scale_y = scale_y;
    this->rotation = rotation;
    this->opacity = opacity;
  }

  /**
   * @brief Watermark position.
   *
   * @details Please refer to values starting from @link common::e_PosTopLeft @endlink and this should be one of these values.
   */
  common::Position position;
  /** @brief Horizontal offset, in points. */
  float offset_x;
  /** @brief Vertical offset, in points. */
  float offset_y;
  /**
   * @brief Watermark flags.
   *
   * @details Please refer to values starting from @link WatermarkSettings::e_FlagASPageContents @endlink and
   *          this can be one or a combination of these values.
   */
  uint32 flags;
  /** @brief Horizontal scale coefficient. It should be greater than 0.001f. */
  float scale_x;
  /** @brief Vertical scale coefficient. It should be greater than 0.001f. */
  float scale_y;
  /** @brief Rotation angle in degrees. */
  float rotation;
  /**
   * @brief Opacity in percents. Valid range: from 0 to 100.
   *        0 for fully transparent and 100 for fully opaque.
   */ 
  int opacity;
};

/** This class represents the watermark text settings used to construct a watermark object from text. */
class WatermarkTextProperties FS_FINAL : public Object {
 public:
  /**
   * @brief Enumeration for watermark font style.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _FontStyle {
    /** @brief Watermark font style: normal. */
    e_FontStyleNormal = 0,
    /** @brief Watermark font style: with underline. */
    e_FontStyleUnderline = 1
  } FontStyle;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] font        A valid font object used for the text.
   * @param[in] font_size   Font size in points.
   * @param[in] color       Text color. Format: 0xRRGGBB.
   * @param[in] style       Font style. It should be one of the following values:
   *                        <ul>
   *                        <li>@link WatermarkTextProperties::e_FontStyleNormal @endlink</li>
   *                        <li>@link WatermarkTextProperties::e_FontStyleUnderline @endlink</li>
   *                        </ul>
   * @param[in] line_space  Space between vertical center of lines, in line heights. This value specifies
   *                        the multiple of line heights for the space between vertical center of lines.
   *                        Valid range: from 0 to 10 (not including 0 but including 10). If this value is above 10,
   *                        10 will be used as default for the text watermark.
   * @param[in] alignment   Text horizontal alignment. It should be one of the following values:
   *                        <ul>
   *                        <li>@link common::e_AlignmentLeft @endlink</li>
   *                        <li>@link common::e_AlignmentCenter @endlink</li>
   *                        <li>@link common::e_AlignmentRight @endlink</li>
   *                        </ul>   */
  WatermarkTextProperties(const common::Font& font, float font_size, RGB color, FontStyle style, float line_space,
                          CommonDefines::Alignment alignment)
      : font(font)
      , font_size(font_size)
      , color(color)
      , font_style(style)
      , line_space(line_space)
      , alignment(alignment) {}

  /** @brief Constructor. */
  WatermarkTextProperties()
      : font_size(0)
      , color(0x000000)
      , font_style(e_FontStyleNormal)
      , line_space(0)
      , alignment(CommonDefines::e_AlignmentLeft) {}

  /**
   * @brief Constructor, with another watermark text properties object.
   *
   * @param[in] properties  Another watermark text properties object.
   */
  WatermarkTextProperties(const WatermarkTextProperties& properties)
      : font(properties.font)
      , font_size(properties.font_size)
      , color(properties.color)
      , font_style(properties.font_style)
      , line_space(properties.line_space)
      , alignment(properties.alignment) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] properties  Another watermark text properties object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  WatermarkTextProperties& operator = (const WatermarkTextProperties& properties) {
    font = properties.font;
    font_size = properties.font_size;
    color = properties.color;
    font_style = properties.font_style;
    line_space = properties.line_space;
    alignment = properties.alignment;
    return *this;
  }

  /**
   * @brief Set value.
   *
   * @param[in] font        A valid font object used for the text.
   * @param[in] font_size   Font size in points.
   * @param[in] color       Text color. Format: 0xRRGGBB.
   * @param[in] style       Font style. It should be one of the following values:
   *                        <ul>
   *                        <li>@link WatermarkTextProperties::e_FontStyleNormal @endlink</li>
   *                        <li>@link WatermarkTextProperties::e_FontStyleUnderline @endlink</li>
   *                        </ul>
   * @param[in] line_space  Space between vertical center of lines, in line heights. This value specifies
   *                        the multiple of line heights for the space between vertical center of lines.
   *                        Valid range: from 0 to 10 (not including 0 but including 10). If this value is above 10,
   *                        10 will be used as default for the text watermark.
   * @param[in] alignment   Text horizontal alignment. It should be one of the following values:
   *                        <ul>
   *                        <li>@link common::e_AlignmentLeft @endlink</li>
   *                        <li>@link common::e_AlignmentCenter @endlink</li>
   *                        <li>@link common::e_AlignmentRight @endlink</li>
   *                        </ul>
   *
   * @return None.
   */
  void Set(const common::Font& font, float font_size, RGB color, FontStyle style, float line_space,
           CommonDefines::Alignment alignment) {
    this->font = font;
    this->font_size = font_size;
    this->color = color;
    this->font_style = style;
    this->line_space = line_space;
    this->alignment = alignment;
  }

  /** @brief A font object used for the text. */
  common::Font font;
  /** @brief Font size in points. */
  float font_size;
  /** @brief Text color. Format: 0xRRGGBB.*/
  RGB color;
  /**
   * @brief Font style.
   *
   * @details It should be one of the following values:
   *          <ul>
   *          <li>@link WatermarkTextProperties::e_FontStyleNormal @endlink</li>
   *          <li>@link WatermarkTextProperties::e_FontStyleUnderline @endlink</li>
   *          </ul>   */
  FontStyle font_style;
  /**
   * @brief Space between vertical center of lines, in line heights.
   *
   * @details This value is used to specify the multiple of line heights for the space between vertical center of lines.
   *          Valid range: from 0 to 10 (not including 0 but including 10). If this value is above 10, 10 will be used
   *          as default for the text watermark.
   */
  float line_space;
  /**
   * @brief Text horizontal alignment.
   *
   * @details It should be one of the following macro definitions:
   *          <ul>
   *          <li>@link common::e_AlignmentLeft @endlink</li>
   *          <li>@link common::e_AlignmentCenter @endlink</li>
   *          <li>@link common::e_AlignmentRight @endlink</li>
   *          </ul>   */
  CommonDefines::Alignment alignment;
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_WATERMARK_H_

