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
 * @file fs_pdfgraphicsobject.h
 * @brief Header file for PDF graphics object related definitions and classes.
 */

#ifndef FS_PDFGRAPHICSOBJECT_H_
#define FS_PDFGRAPHICSOBJECT_H_

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
namespace pdf {
namespace graphics {
class TextObject;
class FormXObject;
class ImageObject;
class PathObject;
class ShadingObject;
}  // namespace graphics
class PDFPage;
class GraphicsObjects;
class LayerNodeArray;
class LayerTree;
}  // namespace pdf

/**
 * @brief PDF namespace.
 */
namespace pdf {
/**
 * @brief PDF graphics namespace.
 */
namespace graphics {
/** This class represents PDF color state. */
class ColorState FS_FINAL : public Base {
 public:
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit ColorState(FS_HANDLE handle);

  /** @brief Destructor. */
  ~ColorState();

  /**
   * @brief Constructor, with another color state object.
   *
   * @param[in] other  Another color state object.
   */
  ColorState(const ColorState& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another color state object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ColorState& operator=(const ColorState& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another color state object. This function will check if current object is 
   *                   equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const ColorState& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another color state object. This function will check if current object is not
   *                   equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const ColorState& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get fill color.
   *
   * @return Fill color.
   */
  common::Color GetFillColor();

  /**
   * @brief Set fill color.
   *
   * @param[in] color  A color to be set as fill color.
   *
   * @return None.
   */
  void SetFillColor(const common::Color& color);

  /**
   * @brief Get stroke color.
   *
   * @return Stroke color.
   */
  common::Color GetStrokeColor();
  
  /**
   * @brief Set stroke color.
   *
   * @param[in] color  A color to be set as stroke color.
   *
   * @return None.
   */
  void SetStrokeColor(const common::Color& color);
};

/**
 * Marked-content operators (PDF 1.2) identify a portion of a PDF content stream as a marked-content element of
 * interest to a particular application or PDF plug-in extension. For more details, please refer to
 * Section 10.5 "Marked Content" in <PDF Reference 1.7>.<br>
 * To get a marked content object, please use function @link GraphicsObject::GetMarkedContent @endlink.
 *
 * @see @link GraphicsObject @endlink
 */
class MarkedContent FS_FINAL : public Object {
 public:
  /** @brief Destructor. */
  ~MarkedContent() {}

  /**
   * @brief Check whether current marked content object has a specified marked content item or not.
   *
   * @param[in] tag_name  The tag name to be checked.
   *
   * @return <b>true</b> means current marked content object has the specified marked content item.
   *         <b>false</b> means current marked content object does not have the specified marked content item.
   */
  bool HasTag(const char* tag_name);
  /**
   * @brief Get the count of marked content items.
   *
   * @details A marked content object may be nested one within another, and this function is used to
   *          get the count of marked content items in the current marked content sequence.
   *
   * @return The count of marked content items.
   */
  int GetItemCount() const;
  /**
   * @brief Get the tag name of a marked content item specified by index.
   *
   * @details A marked content object may be nested one within another, and this function is used to
   *          get the count of marked content items in the current marked content sequence.
   *
   * @param[in] index  Item index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link MarkedContent::GetItemCount @endlink.
   *
   * @return The tag name.
   */
  String GetItemTagName(int index) const;
  /**
   * @brief Get marked-content identifier (MCID) of a marked content item specified by index.
   *
   * @param[in] index  Item index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link MarkedContent::GetItemCount @endlink.
   *
   * @return The MCID value. A negative number means that the specified marked content item does not have a MCID.
   */
  int GetItemMCID(int index) const;
  /**
   * @brief Get the property dictionary of a marked content item specified by index.
   *
   * @param[in] index  Item index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link MarkedContent::GetItemCount @endlink.
   *
   * @return The property dictionary. <b>NULL</b> means no property dictionary.
   */
  objects::PDFDictionary* GetItemPropertyDict(int index) const;
  /**
   * @brief Add a new marked content item.
   *
   * @param[in] tag_name       New tag name. It should not be an empty string.
   *                           If parameter <i>tag_name</i> exists in current marked content object,
   *                           it cannot be added to current marked content object again.
   * @param[in] property_dict  A property dictionary. Default value: <b>NULL</b>.
   *                           <b>NULL</b> means the new marked content item will not have a property dictionary.<br>
   *                           If this dictionary is newly created and not set to other object yet, user should
   *                           release this dictionary object after calling this function.
   *
   * @return The index of the newly added marked content item. If there is any error, this function will return -1.
   */
  int AddItem(const char* tag_name, objects::PDFDictionary* property_dict = NULL);
  /**
   * @brief Remove a marked content item by tag name.
   *
   * @param[in] tag_name  Tag name. It should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveItem(const char* tag_name);

 private:
  MarkedContent(const MarkedContent& markedcontent);
  MarkedContent &operator = (const MarkedContent& markedcontent);
};

/**
 * Content of a PDF page usually consists of a sequence of graphics objects. Each graphics object contains
 * its state information, data and instructions for rendering.<br>
 * Class @link GraphicsObject @endlink is the base class for all types of PDF graphics objects.
 * It offers the base functions to get/set graphics object's common properties. For concrete graphics object types,
 * please refer to derived classes.<br>
 * To get or insert/remove a graphics object, please refer to class @link pdf::GraphicsObjects @endlink.<br>
 * If any change is done to a PDF graphics object, please remember to call function
 * @link GraphicsObjects::GenerateContent @endlink for @link pdf::GraphicsObjects @endlink object (to which current graphics object belongs).
 * Please refer to comment of function @link GraphicsObjects::GenerateContent @endlink
 * for more details.
 *
 * @see @link pdf::GraphicsObjects @endlink
 */
class GraphicsObject : public Object {
 public:
  /**
   * @brief Enumeration for render blend mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _BlendMode {
    /**
   @brief Selecting source color and ignoring backdrop color.
   @details Here is the formula :<br>
            <pre>B(Cb, Cs) = Cs.</pre>
     */
    e_BlendNormal  = 0,
    /**
   @brief Multiply backdrop by source color values.
   @details Here is the formula :<br>
              <pre>B(Cb, Cs) = Cb * Cs.</pre>
     */
    e_BlendMultiply = 1,
    /**
   @brief Multiply complements of backdrop by source color values, and then complement the result.
   @details Here is the formula :<br>
              <pre>B(Cb, Cs) = 1 - [(1 - Cb) * (1 - Cs)] = Cb + Cs - Cb * Cs.</pre>
     */
    e_BlendScreen = 2,
    /**
   @brief Multiply or screens colors, depending on backdrop color value.
   @details Here is the formula :<br>
            <pre>B(Cb, Cs) = HardLight(Cs, Cb).</pre>
     */
    e_BlendOverlay = 3,
    /**
   @brief Select darker one of backdrop and source colors.
   @details Here is the formula :<br>
            <pre>B(Cb, Cs) = min(Cb, Cs).</pre>
     */
    e_BlendDarken = 4,
    /**
   @brief Select lighter one of backdrop and source colors.
   @details Here is the formula :<br>
            <pre>B(Cb, Cs) = max(Cb, Cs).</pre>
     */
    e_BlendLighten = 5,
    /**
   @brief Brightens backdrop color to reflect source colors.
   @details Painting with black produces no changes.<br>
            Here is the formula :<br>
            <pre>
            B(Cb, Cs) = 
            -min(1, Cb / (1 - Cs))    if Cs < 1 
            -1              if Cs = 1
            </pre>
     */
    e_BlendColorDodge = 6,
    /**
   @brief Darkens backdrop color to reflect the source color.
   @details Painting with white produces no changes.<br>
            Here is the formula :<br>
            <pre>
            B(Cb, Cs) = 
            -1 - min(1, (1 - Cb) / Cs)  if Cs > 0
            -0              if Cs = 0
            </pre>
     */
    e_BlendColorBurn = 7,
    /**
   @brief Multiply or screens colors, depending on source color value.
   @details Here is the formula :<br>
            <pre>
            B(Cb, Cs) =
              -Multiply(Cb, 2 * Cs)    if Cs <= 0.5
              -Screen(Cb, 2 * Cs - 1)  if Cs > 0.5
            </pre>
     */
    e_BlendHardlight = 8,
    /**
   @brief Darkens or lightens colors, depending on source color value.
   @details Here is the formula :<br>
            <pre>
            B(Cb, Cs) =
              -Cb - (1 - 2 * Cs) * Cb * (1 - Cb)    if Cs <= 0.5
              -Cb + (2 * Cs - 1) * (D(Cb) - Cb)    if Cs > 0.5
            where D(x) = 
              -((16 * x - 12) * x + 4) * x      if x <= 0.25
            -sqrt(x)                if x > 0.25
            </pre>
     */
    e_BlendSoftlight = 9,
    /**
   @brief Subtracts the darker of the two constituent colors from lighter colors.
   @details Here is the formula :<br>
            <pre>B(Cb, Cs) = |Cb - Cs|.</pre>
     */
    e_BlendDifference = 10,
    /**
   @brief Creates a color with the hue of the source color,
          and the saturation and luminosity of the backdrop color.
   @details Here is the formula :<br>
            <pre>B(Cb, Cs) = SetLum(SetSat(Cs, Sat(Cb)), Lum(Cb)).</pre>
     */
    e_BlendExclusion = 11,
    /**
   @brief Creates a color with the hue of the source color,
          and the saturation and luminosity of the backdrop color.
   @details Here is the formula :<br>
            <pre>B(Cb, Cs) = SetLum(SetSat(Cs, Sat(Cb)), Lum(Cb)).</pre>
     */
    e_BlendHue = 21,
    /**
   @brief Creates a color with the saturation of the source color,
          and the hue and luminosity of the backdrop color.
   @details Here is the formula :<br>
            <pre>B(Cb, Cs) = SetLum(SetSat(Cb, Sat(Cs)), Lum(Cb)).</pre>
     */
    e_BlendSaturation = 22,
    /**
   @brief Creates a color with the hue and saturation of the source color,
          and the luminosity of the backdrop color.
   @details Here is the formula :<br>
            <pre>B(Cb, Cs) = SetLum(Cs, Lum(Cb)).</pre>
     */
    e_BlendColor = 23,
    /**
   @brief Creates a color with the luminosity of the source color,
          and the hue and saturation of the backdrop color.
   @details Here is the formula :<br>
            <pre>B(Cb, Cs) = SetLum(Cb, Lum(Cs)).</pre>
     */
    e_BlendLuminosity = 24
  } BlendMode;
  
  /**
   * @brief Enumeration for PDF graphics object type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Type {
    /** @brief Represents all graphics object types, only used as filter. */
    e_TypeAll  = 0,
    /** @brief Text graphics object. */
    e_TypeText = 1,
    /** @brief Path graphics object. */
    e_TypePath = 2,
    /** @brief Image graphics object. */
    e_TypeImage = 3,
    /** @brief Shading graphics object. */
    e_TypeShading = 4,
    /** @brief Form XObject graphics object. */
    e_TypeFormXObject = 5
  } Type;
  

#if !defined(_SWIG_IOS_) && !defined(_SWIG_MACOC_)
  /**
   * @brief Release a cloned or newly created PDF graphics object which has not been inserted into any PDF page
   *        or other object.
   *
   * @return None.
   */
  void Release();
#endif

  /**
   * @brief Get the type of current graphics object.
   *
   * @return Graphics object type. Please refer to values starting from @link GraphicsObject::e_TypeText @endlink and
   *         this would be one of these values except @link GraphicsObject::e_TypeAll @endlink.
   */
  Type GetType() const;

  /**
   * @brief Get the rectangle of current graphics object.
   *
   * @return Rectangle of current graphics object.
   *         If there is any error, this function will return a RectF object with all values 0.
   */
  RectF GetRect() const;

  /**
   * @brief Check whether current graphics object has transparency or not.
   *
   * @return <b>true</b> means current graphics object has transparency, while <b>false</b> means not.
   */
  bool HasTransparency();

  /**
   * @brief Get the stroke color.
   *
   * @details Text graphics object, path graphics object, and form XObject graphics object can have this property.<br>
   *          Function @link GraphicsObject::GetColorState @endlink can be used to get stroke color in other color space, like CMYK color space.
   *
   * @return Color value, in format 0xAARRGGBB.
   */
  ARGB GetStrokeColor() const;

  /**
   * @brief Get the fill color.
   *
   * @details Text graphics object, path graphics object, and form XObject graphics object can have this property.
   *          Function @link GraphicsObject::GetColorState @endlink can be used to get fille color in other color space, like CMYK color space.
   *
   * @return Color value, in format 0xAARRGGBB.
   */
  ARGB GetFillColor() const;

  /**
   * @brief Set the stroke color.
   *
   * @details Text graphics object, path graphics object, and form XObject graphics object can have this property.
   *          If current graphics object is a text graphics object and the text mode is @link TextState::e_ModeFill @endlink,
   *          the stroke color will not have effect on the text graphics object.<br>
   *          If try to set stroke color for rest unsupported types, exception @link foxit::e_ErrUnsupported @endlink
   *          will be thrown.<br>
   *          Function @link GraphicsObject::SetColorState @endlink can be used to set stroke color in other color space, like CMYK color space.
   *
   * @param[in] color  New color value, in format 0xAARRGGBB.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetStrokeColor(ARGB color);

  /**
   * @brief Set the fill color.
   *
   * @details Text graphics object, path graphics object, and form XObject graphics object can have color state.
   *          If try to set fill color for rest unsupported types, @link foxit::e_ErrUnsupported @endlink will be thrown.<br>
   *          For path graphics object, please ensure the fill mode is not @link common::e_FillModeNone @endlink;
   *          otherwise the fill color will not have any effect on the path graphics object. Please refer to functions
   *          @link PathObject::GetFillMode @endlink and @link PathObject::SetFillMode @endlink to
   *          check and change the fill mode of a path graphics object.<br>
   *          Function @link GraphicsObject::SetColorState @endlink can be used to set fill color in other color space, like CMYK color space.
   *
   * @param[in] color  New color value, in format 0xAARRGGBB.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetFillColor(ARGB color);

  /**
   * @brief Get color state.
   *
   * @details Text graphics object, path graphics object, and form XObject graphics object can have color state.
   *
   * @return Color state.
   */
  ColorState GetColorState() const;

  /**
   * @brief Set color state.
   *
   * @details Text graphics object, path graphics object, and form XObject graphics object can have this property.
   *          If try to set color state for rest unsupported types, exception @link foxit::e_ErrUnsupported @endlink will be thrown.
   *
   * @param[in] color_state  A color state object to be set to current graphics object.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetColorState(const ColorState& color_state);

  /**
   * @brief Set the opacity value for painting operations other than stroking.
   *
   * @param[in] opacity The new opacity value. Valid range: 0.0 to 1.0.
   *                    0.0 means full transparency and 1.0 means full opaque.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetFillOpacity(float opacity);

  /**
   * @brief Set opacity value for stroke painting operations for paths and glyph outlines.
   *
   * @param[in] opacity The new opacity value. Valid range: 0.0 to 1.0.
   *                    0.0 means full transparency and 1.0 means full opaque.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetStrokeOpacity(float opacity);

  /**
   * @brief Get the opacity value for painting operations other than stroking.
   *
   * @return The opacity value. Valid range: 0.0 to 1.0. 0.0 means full transparency and 1.0 means full opaque.
   *         If no opacity value can be found, 1 will be returned as default value.
   */
  float GetFillOpacity() const;
  
  /**
  * @brief Get opacity value for stroke painting operations for paths and glyph outlines.
  *
  * @return The opacity value. Valid range: 0.0 to 1.0. 0.0 means full transparency and 1.0 means full opaque.
  *         If no opacity value can be found, 1 will be returned as default value.
  */
  float GetStrokeOpacity()const;

  /**
   * @brief Get matrix.
   *
   * @return Matrix value.
   *         If there is any error, this function will return a Matrix with all values 0.
   */
  Matrix GetMatrix() const;

  /**
   * @brief Set matrix.
   *
   * @param[in] matrix  New matrix value.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetMatrix(const Matrix& matrix);

  /**
   * @brief Transform current graphics object.
   *
   * @param[in] matrix                   Transform matrix.
   * @param[in] need_transform_clippath  <b>true</b> means to transform clip path with current graphics object.
   *                                     <b>false</b> means to transform current graphics object only.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  bool Transform(const Matrix& matrix, bool need_transform_clippath);

  /**
   * @brief Clone a new graphics object.
   *
   * @details Newly cloned graphics object is related to the same page with current graphics object by default.
   *          Newly cloned graphics object can only be used inside the PDF file which contains current graphics object.
   *
   * @return Cloned graphics object. If there is any error, this function will return <b>NULL</b>.<br>
   *         If the cloned graphics object is not inserted to any PDF page or other object,
   *         please remember to call function @link GraphicsObject::Release @endlink to release it when not use it any more.
   */
  GraphicsObject* Clone();

  /**
   * @brief Get graph state.
   *
   * @details Form XObjet graphics object, path graphics object and text graphics object can have this property.
   *
   * @return Graph state.
   */
  common::GraphState GetGraphState() const;

  /**
   * @brief Set graph state.
   *
   * @details Form XObjet graphics object, path graphics object and text graphics object can have this property.
   *          If try to set graph state to rest unsupported types, exception
   *          @link foxit::e_ErrUnsupported @endlink will be thrown.
   *
   * @param[in] graph_state  New graph state.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetGraphState(const common::GraphState& graph_state);

  /**
   * @brief Get the blend mode for transparent imaging model.
   *
   * @return The Blend mode for transparent imaging model. Please refer to values starting from
   *         @link GraphicsObject::e_BlendNormal @endlink and this would be one of these values.
   */
  BlendMode GetBlendMode() const;

  /**
   * @brief Set the blend mode for transparent imaging model.
   *
   * @param[in] blend_mode  New blend mode. Please refer to values starting from @link GraphicsObject::e_BlendNormal @endlink
   *                        and this should be one of these values.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetBlendMode(BlendMode blend_mode);

  /**
   * @brief Get the count of path clip.
   *
   * @return Count of path clip.
   */
  int GetClipPathCount() const;

  /**
   * @brief Get a path clip by index.
   *
   * @param[in] index  Path clip index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link GraphicsObject::GetClipPath @endlink.
   *
   * @return Path data. If the return value of function @link common::Path::IsEmpty @endlink for
   *         the returned path object is <b>true</b>, that means there is any error.
   */
  common::Path GetClipPath(int index) const;

  /**
   * @brief Get the fill mode of a path clip by index.
   *
   * @param[in] index  Path clip index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link GraphicsObject::GetClipPath @endlink.
   *
   * @return Fill mode. Please refer to values starting from @link common::e_FillModeNone @endlink and
   *         this would be one of these values.
   */
  common::FillMode GetClipPathFillMode(int index) const;

  /**
   * @brief Add a path for clipping.
   *
   * @param[in] path       Path data to be added to current graphics object.
   * @param[in] fill_mode  Fill mode for the input path. Please refer to values starting from
   *                       @link common::e_FillModeNone @endlink and this should be one of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  bool AddClipPath(const common::Path& path, common::FillMode fill_mode);

  /**
   * @brief Remove a path clip by index.
   *
   * @param[in] index  Path clip index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link GraphicsObject::GetClipPath @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  bool RemoveClipPath(int index);

  /**
   * @brief Get the count of text clip.
   *
   * @return Count of text clip.
   */
  int GetClipTextObjectCount() const;

  /**
   * @brief Get the text object of a text clip by index.
   *
   * @param[in] index  Text clip index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link GraphicsObject::GetClipTextObjectCount @endlink.
   *
   * @return A text graphics object. If there is any error, this function will return <b>NULL</b>.
   */
  TextObject* GetClipTextObject(int index) const;

  /**
   * @brief Add text object for clipping.
   *
   * @param[in] textobject  Text object to be added for clipping.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  bool AddClipTextObject(TextObject* textobject);

  /**
   * @brief Remove a text clip by index for clipping.
   *
   * @param[in] index  Text clip index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link GraphicsObject::GetClipTextObjectCount @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  bool RemoveClipTextObject(int index);

  /**
   * @brief Get clip rectangle.
   *
   * @return Clip rectangle. If there is no clip rectangle, a RectF object with all values 0 will be returned.
   */
  RectF GetClipRect() const;

  /**
   * @brief Set clip rectangle.
   *
   * @details New clip rectangle will be set with fill mode @link common::e_FillModeWinding @endlink by default.
   *
   * @param[in] clip_rect  New clip rectangle.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetClipRect(const RectF& clip_rect);

  /**
   * @brief Clear all clips.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  bool ClearClips();

  /**
   * @brief Get marked content object
   *
   * @return A marked content object.
   */
  MarkedContent* GetMarkedContent() const;

  /**
   * @brief Get all the layers which are associated with current graphics object.
   *
   * @param[in] layer_tree  A valid layer tree. All the layer nodes in this layer tree will be enumerated\
   *                        in order to find which are associated with current graphics object.
   *
   * @return A layer node array which contains all the matched layer node.
   */
  LayerNodeArray GetLayers(const LayerTree& layer_tree);

  /**
   * @brief Get the text graphics object if current graphics object represents a text object.
   *
   * @return Text graphics object. If current graphics object does not represent a text object,
   *         this function will return <b>NULL</b>.
   */
  TextObject* GetTextObject() const;

  /**
   * @brief Get the form XObject graphics object if current graphics object represents a form XObject object.
   *
   * @return Form XObject graphics object. If current graphics object does not represent a form XObject object,
   *         this function will return <b>NULL</b>.
   */
  FormXObject* GetFormXObject() const;

  /**
   * @brief Get the image graphics object if current graphics object represents an image object.
   *
   * @return Image graphics object. If current graphics object does not represent an image object,
   *         this function will return <b>NULL</b>.
   */
  ImageObject* GetImageObject() const;

  /**
   * @brief Get the path graphics object if current graphics object represents a path object.
   *
   * @return Path graphics object. If current graphics object does not represent a path object,
   *         this function will return <b>NULL</b>.
   */
  PathObject* GetPathObject() const;

  /**
   * @brief Get the shading graphics object if current graphics object represents a shading object.
   *
   * @return Shading graphics object. If current graphics object does not represent a shading object,
   *         this function will return <b>NULL</b>.
   */
  ShadingObject* GetShadingObject() const;

  /**
   * @brief Rotate current graphics object from current state with specified angle degree in clockwise.
   *
   * @param[in] angle  Angle degree value, which is used to rotate current graphics object from current state in clockwise.
   *                   Value range: from 0 to 360. Specially, if the input value is 0 or 360 (which means not to
   *                   rotate current graphics object), current function will do nothing.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void Rotate(int angle);
 protected:
  ~GraphicsObject() {}

 private:
  GraphicsObject(const GraphicsObject& graphicsobject);
  GraphicsObject &operator = (const GraphicsObject& graphicsobject);
};

/** This class represents an array of @link graphics::GraphicsObject @endlink objects. */
typedef CFX_ArrayTemplate<GraphicsObject*> GraphicsObjectArray;

/** This class represents PDF text state. */
class TextState FS_FINAL : public Object {
 public:
  /**
   * @brief Enumeration for text mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Mode {
    /** @brief Text mode: fill text. */
    e_ModeFill  = 0,
    /** @brief Text mode: stroke text. */
    e_ModeStroke = 1,
    /** @brief Text mode: fill and stroke text. */
    e_ModeFillStroke = 2,
    /** @brief Text mode: neither fill nor stroke text, to make it invisible. */
    e_ModeInvisible = 3,
    /** @brief Text mode: fill text and add to path for clipping. */
    e_ModeFillClip = 4,
    /** @brief Text mode: stroke text and add to path for clipping. */
    e_ModeStrokeClip = 5,
    /** @brief Text mode: fill and stroke text, and add to path for clipping. */
    e_ModeFillStrokeClip = 6,
    /** @brief Text mode: add text to path for clipping. */
    e_ModeClip = 7
  } Mode;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] version          Version of this structure, which is used to decide which members are useful.
   *                             Currently, only 1 is valid.
   * @param[in] font             (Version 1) A valid font object.
   * @param[in] font_size        (Version 1) Font size. It should be above 0.
   * @param[in] charspace        (Version 1) Character spacing.
   * @param[in] wordspace        (Version 1) Word spacing (only apply to space character).
   * @param[in] textmode         (Version 1) Text rendering mode. Please refer to values starting from
   *                             @link TextState::e_ModeFill @endlink and this should be one of these values.
   * @param[in] origin_position  (Version 1) The origin point, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] textmatrix       (Version 1) Text transformation matrix.
   *
   * @return None.
   */
  TextState(uint32 version, const common::Font& font, float font_size, float charspace, float wordspace, Mode textmode,
            const PointF& origin_position, float textmatrix[4]) {
    this->version = version;
    this->font = font;
    this->font_size = font_size;
    this->charspace = charspace;
    this->wordspace = wordspace;
    this->textmode = textmode;
    this->origin_position = origin_position;
    for (int i=0; i < 4; i++)
      this->textmatrix[i] = textmatrix[i];
  }

  /** @brief Constructor. */
  TextState()
      :version(1)
      , font_size(0.0f)
      , charspace(0.0f)
      , wordspace(0.0f)
      , textmode(TextState::e_ModeFill) {
    origin_position = PointF();
    this->textmatrix[0] = 1;
    this->textmatrix[1] = 0;
    this->textmatrix[2] = 0;
    this->textmatrix[3] = 1;
  }

  /**
   * @brief Constructor, with another text state object.
   *
   * @param[in] state  Another text state object.
   */
  TextState(const TextState& state) {
    version = state.version;
    font = state.font;
    font_size = state.font_size;
    charspace = state.charspace;
    wordspace = state.wordspace;
    textmode = state.textmode;
    origin_position = state.origin_position;
    for (int i=0; i < 4; i++)
      textmatrix[i] = state.textmatrix[i];
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] state  Another text state object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TextState &operator = (const TextState& state) {
    version = state.version;
    font = state.font;
    font_size = state.font_size;
    charspace = state.charspace;
    wordspace = state.wordspace;
    textmode = state.textmode;
    origin_position = state.origin_position;
    for (int i=0; i < 4; i++)
      textmatrix[i] = state.textmatrix[i];
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] version          Version of this structure, which is used to decide which members are useful.
   *                             Currently, only 1 is valid.
   * @param[in] font             (Version 1) A valid font object.
   * @param[in] font_size        (Version 1) Font size. It should be above 0.
   * @param[in] charspace        (Version 1) Character spacing.
   * @param[in] wordspace        (Version 1) Word spacing (only apply to space character).
   * @param[in] textmode         (Version 1) Text rendering mode. Please refer to values starting from
   *                             @link TextState::e_ModeFill @endlink and this should be one of these values.
   * @param[in] origin_position  (Version 1) The origin point, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] textmatrix       (Version 1) Text transformation matrix.
   *
   * @return None.
   */
  void Set(uint32 version, const common::Font& font, float font_size, float charspace, float wordspace,
           Mode textmode, const PointF& origin_position, float textmatrix[4]) {
    this->version = version;
    this->font = font;
    this->font_size = font_size;
    this->charspace = charspace;
    this->wordspace = wordspace;
    this->textmode = textmode;
    this->origin_position = origin_position;
    for (int i=0; i < 4; i++)
      this->textmatrix[i] = textmatrix[i];
  }

  /**
   * @brief Version of this class.
   *
   * @version 1
   *
   * @details Members of this class may be extended in the future. This version can be used to
   *          separate the different extended members.
   */
  uint32 version;

  /**
   * @brief A font object.
   *
   * @version 1   */
  common::Font font;

  /**
   * @brief Font size. If valid, it should be above 0.
   *
   * @version 1   */
  float font_size;
  /**
   * @brief Character spacing.
   *
   * @version 1
   *
   * @details For horizontal writing, a positive value has the effect of expanding the distance between glyphs,
   *          whereas for vertical writing, a negative value has this effect.
   */
  float charspace;

  /**
   * @brief Word spacing (only apply to space character).
   *
   * @version 1
   *
   * @details For horizontal writing, a positive value has the effect of increasing the spacing between words.
   *          For vertical writing, a positive value decreases the spacing between words
   *          (and a negative value increases it), since vertical coordinates increase from bottom to top.
   *          This will not take effect if <i>font</i> of current object is an embedded font.
   */
  float wordspace;

  /**
   * @brief Text rendering mode. Please refer to values starting from @link TextState::e_ModeFill @endlink and
   *        this should be one of these values.
   *
   * @version 1
   */
  Mode textmode;

  /**
   * @brief The origin point, in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @version 1
   */
  PointF origin_position;

  /**
   * @brief Text transformation matrix.
   *
   * @version 1
   */
  float textmatrix[4];
};

/**
 * Image graphics object is a kind of PDF graphics object, so class @link ImageObject @endlink is derived from
 * class @link GraphicsObject @endlink. It offers functions to get/set image graphics object's data. <br>
 * To create a new image graphics object, please use function @link ImageObject::Create @endlink and then
 * use setting functions to set information to the new image graphics object.
 *
 * @see @link GraphicsObject @endlink
 */
class ImageObject FS_FINAL : public GraphicsObject {
 public:
  /**
   * @brief Create a new image graphics object.
   *
   * @details The newly created image graphics object does not have any data yet. Then, setting functions can
   *          be called to set data to the new image graphics object.
   *
   * @param[in] document  A valid PDF document object.  The new image graphics object should be inserted to
   *                      one page of this PDF document then.
   *
   * @return A new image object.<br>
   *         If the newly created image graphics object will not inserted to any page or other objects,
   *         please remember to call function @link GraphicsObject::Release @endlink to release it when no use.
   */
  static ImageObject* Create(const PDFDoc& document);

  /**
   * @brief Set a bitmap to current image graphics object.
   *
   * @param[in] bitmap  A valid bitmap object to be set to current image.
   * @param[in] mask    Mask bitmap. Default value: A bitmap object by default constructor and not set any value,
   *                    which means no mask is used.<br>
   *                    If this is valid, its format should be @link common::Bitmap::e_DIB8bppMask @endlink. <br>
   *                    This is useful only when parameter <i>bitmap</i> does not have an alpha channel.
   *
   * @return None
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetBitmap(const common::Bitmap& bitmap, const common::Bitmap& mask = common::Bitmap());

  /**
   * @brief Set one frame of an image to current image graphics object.
   *
   * @details Input image may contain multiple frames, and only one frame of the image can be set
   *          to current image graphics object.
   *
   * @param[in] image        A valid image object. This image should contain at least one frame and the image type
   *                         should not be @link common::Image::e_Unknown @endlink.
   * @param[in] frame_index  Frame index used to decide which frame of parameter <i>image</i> is to be set.
   *                         Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                         @link common::Image::GetFrameCount @endlink.
   *
   * @return None
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetImage(const common::Image& image, int frame_index);

  /**
   * @brief Clone the bitmap from current image graphics object.
   *
   * @details Currently, the bitmap can be cloned from image graphics object only when the bitmap format is
   *          one of following formats: <br>
   *          @link common::Bitmap::e_DIB8bppMask @endlink, @link common::Bitmap::e_DIB8bpp @endlink,
   *          @link common::Bitmap::e_DIBRgb @endlink, @link common::Bitmap::e_DIBRgb32 @endlink,
   *          @link common::Bitmap::e_DIBArgb @endlink.<br>
   *          If the return value of function @link common::Bitmap::IsEmpty @endlink for the returned bitmap object is <b>true</b>,
   *          that means the DIB format of the bitmap is unsupported.
   *
   * @param[in] graphics_objects  A valid @link pdf::GraphicsObjects @endlink object. Please ensure that current image graphics object
   *                              just belongs to this @link pdf::GraphicsObjects @endlink object (it may be a PDF page).
   *
   * @return The new cloned bitmap object. If the return value of function @link common::Bitmap::IsEmpty @endlink for
   *         the returned bitmap object is <b>true</b>, that means the DIB format of the bitmap is unsupported.
   */
  common::Bitmap CloneBitmap(const GraphicsObjects& graphics_objects);

  /**
   * @brief Get color space.
   *
   * @return Color space. Please refer to values starting from @link common::e_ColorSpaceDeviceGray @endlink and
   *         this would be one of these values.
   */
  common::ColorSpaceType GetColorSpace() const;

  /**
   * @brief Get image stream.
   *
   * @return A @link objects::PDFStream @endlink that represents the image stream.
   *         If there is any error, this function will return <b>NULL</b>.
   */
  objects::PDFStream* GetStream() const;

  /**
   * @brief Check if current image object is treated as mask.
   *
   * @return <b>true</b> means current object is treated as mask, while <b>false</b> means not.
   */
  bool IsImageMask() const;

  /**
   * @brief Get the PDF object that represents the mask of current image graphics object.
   *
   * @details The mask can be either a PDF dictionary or a PDF array:
   *          <ul>
   *          <li>A PDF dictionary represents an image mask to be applied to this image.</li>
   *          <li>A PDF array represents a range of colors to be applied to it as a color key mask.</li>
   *          </ul>
   *          Please refer to Section 4.8.4 "Image Dictionaries" in <PDF Reference 1.7> for more details.
   *
   * @return A PDF object that represents the mask.
   *         If @link ImageObject::IsImageMask @endlink returns <b>true</b>, this function will return <b>NULL</b>.
   */
  objects::PDFObject* GetMask() const;

 private:
	~ImageObject() {}
	
 private:
  ImageObject(const ImageObject& imageobject);
  ImageObject &operator = (const ImageObject& imageobject);

};

/**
 * Text graphics object is a kind of PDF graphics object, so class @link TextObject @endlink is derived from
 * class @link GraphicsObject @endlink. It offers functions to get/set text graphics object's data. <br>
 * To create a new text graphics object, please use function @link TextObject::Create @endlink and then
 * use setting functions to set information to the new text graphics object.
 *
 * @see @link GraphicsObject @endlink
 */
class TextObject FS_FINAL : public GraphicsObject {
 public:
  /**
   * @brief Create a new text graphics object.
   *
   * @details The newly created text graphics object does not have any data yet. Then, setting functions can
   *          be called to set data to the new text graphics object.
   *
   * @return A new text graphics object.<br>
   *         If the newly created text graphics object will not inserted to any page or other objects,
   *         please remember to call function @link GraphicsObject::Release @endlink to release it when no use.
   */
  static TextObject* Create();

  /**
   * @brief Get text string.
   *
   * @return Text string.
   */
  WString GetText() const;

  /**
   * @brief Set text string.
   *
   * @param[in] text  New text string.
   *
   * @return None.
   *
   * @note Before setting text, please ensure that current text graphics object has valid font
   *       which is a part of text state. If not, please call function @link TextObject::SetTextState @endlink to
   *       set valid font first; otherwise setting text will fail.<br>
   *       When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetText(const wchar_t* text);

  /**
   * @brief Get text state information.
   *
   * @param[in] page  A valid PDF page.Please ensure that current graphics object just belongs to this page.
   *
   * @return Text state information.
   */
  TextState GetTextState(const PDFPage& page) const;

  /**
   * @brief Set text state information.
   *
   * @param[in] page        A valid PDF page.Please ensure that current graphics object just belongs to this page.
   * @param[in] text_state  New text state information.
   * @param[in] is_italic   <b>true</b> means the text of current graphics object is italic,
   *                        while <b>false</b> means not.
   * @param[in] weight      Original font weight. If the value is larger than 500, that means to use bold.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetTextState(const PDFPage& page, const TextState& text_state, bool is_italic, int weight);

  /**
   * @brief Get character count in current text object.
   *
   * @return Character count.
   */
  int GetCharCount() const;

  /**
   * @brief Get the position of a character specified by index in current text object.
   *
   * @param[in] index  The index of character whose position is to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link TextObject::GetCharCount @endlink.
   *
   * @return Position of the specified character, in [PDF coordinate system] (@ref pdf::PDFPage).
   */
  PointF GetCharPos(int index) const;

  /**
   * @brief Get the width of a character specified by index in current text object.
   *
   * @param[in] index  The index of character whose position is to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link TextObject::GetCharCount @endlink.
   *
   * @return Width of the specified character.
   */
  float GetCharWidthByIndex(int index) const;

  /**
   * @brief Get the height of a character specified by index in current text object.
   *
   * @param[in] index  The index of character whose position is to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link TextObject::GetCharCount @endlink.
   *
   * @return Height of the specified character.
   */
  float GetCharHeightByIndex(int index) const;

 private:
	~TextObject() {}
	
 private:
  TextObject(const TextObject& textobject);
  TextObject &operator = (const TextObject& textobject);
};

/**
 * Path graphics object is a kind of PDF graphics object, so class @link PathObject @endlink is derived from
 * class @link GraphicsObject @endlink. It offers functions to get/set path graphics object's data. <br>
 * To create a new path graphics object, please use function @link PathObject::Create @endlink and then
 * use setting functions to set information to the new path graphics object.
 * Function @link PathObject::CreateFromTextObject @endlink can be used to create a path graphics object
 * from a text graphics object.
 *
 * @see @link GraphicsObject @endlink
 */
class PathObject FS_FINAL : public GraphicsObject {
 public:
  /**
   * @brief Create a new path graphics object.
   *
   * @details The newly created path graphics object does not have any data yet. Then, setting functions can
   *          be called to set data to the new path graphics object.
   *
   * @return A new path graphics object.<br>
   *         If the newly created path graphics object will not inserted to any page or other objects,
   *         please remember to call function @link GraphicsObject::Release @endlink to release it when no use.
   */
  static PathObject* Create();

  /**
   * @brief Create a path graphics object from a text object.
   *
   * @param[in] page      A valid PDF page object.
   * @param[in] text_obj  A text graphics object. It should not be <b>NULL</b>.
   *                      Please ensure the text graphics object is in the PDF page specified by parameter <i>page</i>.
   *
   * @return A new path graphics object.<br>
   *         If the newly created path graphics object will not inserted to any page or other objects,
   *         please remember to call function @link GraphicsObject::Release @endlink to release it when no use.
   */
  static PathObject* CreateFromTextObject(const PDFPage& page, TextObject* text_obj);

  /**
   * @brief Get fill mode.
   *
   * @return Fill mode. Please refer to values starting from @link common::e_FillModeNone @endlink and
   *         this would be one of these values.
   */
  common::FillMode GetFillMode() const;
  /**
   * @brief Set fill mode.
   *
   * @param[in] fill_mode  Fill mode. Please refer to values starting from @link common::e_FillModeNone @endlink and
   *                       this should be one of these values.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetFillMode(common::FillMode fill_mode);
  /**
   * @brief Get stroke state
   *
   * @return <b>true</b> means current path graphics object is stroked, and <b>false</b> means
   *          current path graphics object is not stroked.
   */
  bool GetStrokeState() const;
  /**
   * @brief Set stroke state.
   *
   * @param[in] is_stroke  <b>true</b> means current path graphics object is to be stroked.
   *                       <b>false</b> means current path graphics object is not to be stroked.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetStrokeState(bool is_stroke);
  /**
   * @brief Get the path data.
   *
   * @return Path data. If the return value of function @link common::Path::IsEmpty @endlink for the returned path object is <b>true</b>,
   *         that means there is any error.
   */
  common::Path GetPathData() const;

  /**
   * @brief Set the path data.
   *
   * @param[in] path_data  A valid path object which represents the path data to be set.
   *
   * @return None.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  void SetPathData(const common::Path& path_data);
	
 private:
	~PathObject() {}
	
 private:
  PathObject(const PathObject& pathobject);
  PathObject &operator = (const PathObject& pathobject);
};

/**
 * A form XObject is not only a graphics object, but also a container. A form XObject consists of
 * a set of graphics objects or sub form XObjects. Form XObject is a kind of PDF graphics object,
 * so class @link graphics::FormXObject @endlink is derived from class @link GraphicsObject @endlink. It offers functions to
 * get/set form XObject's data. <br>
 * To create a new form XObject graphics object, please use function @link PathObject::Create @endlink and then
 * import page content to the new form XObject, or insert new graphics object to form XObject through
 * @link pdf::GraphicsObjects @endlink object returned by function @link FormXObject::GetGraphicsObjects @endlink.
 *
 * @see @link GraphicsObject @endlink
 */
class FormXObject FS_FINAL : public GraphicsObject {
 public:
  /**
   * @brief Create a new form XObject graphics object.
   *
   * @details The newly created form XObject graphics object does not have any data yet. Then, setting functions can
   *          be called to set data to the new form XObject graphics object.
   *
   * @param[in] document  A valid PDF document object. The new form XObject graphics object should be inserted to
   *                      one page of this PDF document then.
   *
   * @return A new form XObject.<br>
   *         If the newly created form XObject will not inserted to any page or other objects,
   *         please remember to call function @link GraphicsObject::Release @endlink to release it when no use.
   */
  static FormXObject* Create(const PDFDoc& document);

  /**
   * @brief Get stream.
   *
   * @return A @link objects::PDFStream @endlink that represents the stream data of current form XObject.
   *         If there is any error, this function will return <b>NULL</b>.
   */
  objects::PDFStream* GetStream() const;

  /**
   * @brief Get graphics objects that associated with current form XObject.
   *
   * @return A @link pdf::GraphicsObjects @endlink object.
   */
  GraphicsObjects GetGraphicsObjects() const;
  /**
   * @brief Import page content from a specified PDF page to current form XObject.
   *
   * @details If this function succeeds, the boundary box of current form XObject will be the same as page's size.
   *
   * @param[in] source_page         A valid PDF page object that represents the source PDF page whose content will be
   *                                imported to current form XObject.
   * @param[in] is_annots_included  <b>true</b> means annotations should be included with the content of
   *                                parameter <i>source_page</i>.
   *                                <b>false</b> means annotations should be ignored from the content of
   *                                parameter <i>source_page</i>.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  bool ImportPageContent(const PDFPage& source_page, bool is_annots_included);

 private:
	~FormXObject() {}
	
 private:
  FormXObject(const FormXObject& formxobject);
  FormXObject &operator = (const FormXObject& formxobject);

};

/**
 * Shading graphics object is a kind of PDF graphics object, so class @link ShadingObject @endlink is derived from
 * class @link GraphicsObject @endlink. It offers functions to get shading graphics object's data.
 *
 * @see @link GraphicsObject @endlink
 */
class ShadingObject FS_FINAL : public GraphicsObject {
 public:
  /**
   * @brief Get the PDF object which represents the shading graphics object in PDF file.
   *
   * @return A @link objects::PDFObject @endlink object. It would be a PDF dictionary or a PDF stream object.
   *         If there is any error, this function will return <b>NULL</b>.
   */
  objects::PDFObject* GetPDFObject() const;

 private:
	~ShadingObject() {}
	
 private:
  ShadingObject(const ShadingObject& shadingobject);
  ShadingObject &operator = (const ShadingObject& shadingobject);

};
}  // namespace graphics
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PDFGRAPHICSOBJECT_H_

