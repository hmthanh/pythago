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
 * @file fs_render.h
 * @brief Header file for rendering related definitions and classes.
 */

#ifndef FS_RENDER_H_
#define FS_RENDER_H_

#include "common/fs_common.h"
#include "common/fs_image.h"
#ifndef __EMSCRIPTEN_RENDER__
#include "pdf/annots/fs_annot.h"
#include "pdf/fs_pdflayer.h"
#include "pdf/fs_reflowpage.h"
#ifndef _FX_NO_XFA_
#include "addon/xfa/fs_xfa.h"
#endif
#endif

#ifdef __APPLE__
#include <CoreGraphics/CoreGraphics.h>
#endif
/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
namespace pdf {
class PDFPage;
}
/**
 * @brief Common namespace.
 */
namespace common {
/**
 * PDF renderer is a graphics engine and is used to render page to a bitmap or a platform device context.
 * This class can be constructed with a bitmap, or a device object. It offers functions to set rendering options/flags,
 * and do rendering. In this class, there are several ways to do rendering:
 * <ul>
 * <li>To render page and annotations, first use function @link Renderer::SetRenderContentFlags @endlink to
 *     decide whether to render page and annotation both or not, and then use functions
 *     @link Renderer::StartRender @endlink to do the rendering.
 *     Function @link Renderer::StartQuickRender @endlink can also be used to render page but only for thumbnail purpose.
 * </li>
 * <li>To render a single annotation, use function @link Renderer::RenderAnnot @endlink.</li>
 * <li>To render a bitmap, use function @link Renderer::StartRenderBitmap @endlink.</li>
 * <li>To render a reflow page, use function @link Renderer::StartRenderReflowPage @endlink.</li>
 * </ul>
 * Widget annotation is always associated with form field and form control in Foxit PDF SDK. For how to render
 * widget annotations, here is a recommended flow:
 * <ul>
 * <li>After loading a PDF page, first render the page and all annotations in this page (including widget annotations).</li>
 * <li>Then, if user uses @link pdf::interform::Filler @endlink object to fill the form, user should use function
 *     @link pdf::interform::Filler::Render @endlink to render the focused form control instead of using function
 *     @link Renderer::RenderAnnot @endlink.</li>
 * </ul>
 *
 * @see @link pdf::interform::Filler @endlink
 */
class Renderer FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for rendering color mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ColorMode {
    /** @brief Normal color mode. */
    e_ColorModeNormal = 0,
    /** @brief Map gray/white/black color value to background/foreground; for other colors, no change. */
    e_ColorModeMappingGray = 1,
    /** @brief Map a color value to the color range defined by a background color and a foreground color. */
    e_ColorModeMapping = 2
  } ColorMode;
  
  /**
   * @brief Enumeration for rendering content flags.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _ContentFlag {
    /** @brief If set, page content will be rendered. */
    e_RenderPage = 0x01,
    /** @brief If set, annotations will be rendered. */
    e_RenderAnnot = 0x02
  } ContentFlag;
  
  #ifdef __APPLE__
  /**
   * @brief Enumeration for rendering device type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _DeviceType {
  /** @brief Device type: display device. */
    e_DeviceDisplay = 1,
    /** @brief Device type: printer. */
    e_DevicePrinter = 2
  }DeviceType;
  #endif
  /**
   * @brief Constructor, with bitmap.
   *
   * @details The input bitmap is treated as an independent device and all the content rendered by the renderer
   *          would appear in the bitmap.
   *
   * @param[in] bitmap        A bitmap used for rendering. User should ensure the bitmap to keep valid until
   *                          the end of life cycle of current renderer object.
   * @param[in] is_rgb_order  <b>true</b> means Foxit PDF SDK needs to use RGB byte-order
   *                          (Red is in the lowest order) when rendering. <br>
   *                          <b>false</b> means Foxit PDF SDK needs to use BGR byte-order
   *                          (Blue is in the lowest order) when rendering.
   */
  Renderer(const Bitmap& bitmap, bool is_rgb_order);

#if (defined(_WIN32) || defined(_WIN64)) && (!defined(SWIG) || defined(_SWIG_DOTNET_))
  /**
   * @brief Constructor, with specified device object.
   *
   * @details All the content rendered by the renderer would appear in the input device object.
   *
   * @param[in] dc  A handle of DC.
   */
  explicit Renderer(HDC dc);
#endif

#ifdef __APPLE__
  /**
   * @brief Constructor, with device context.
   *
   * @details All the content rendered by the renderer would appear in CGContextRef object.
   *
   * @param[in] context      A CGContextRef object. User should ensure the device to keep valid until the end of
   *                         life cycle of current renderer object.
   * @param[in] device_type  The device type of parameter <i>context</i>. Please refer to values starting from
   *                         @link Renderer::e_DeviceDisplay @endlink and this should be one of these values.
   */
  Renderer(const CGContextRef& context, DeviceType device_type);
#endif
  /**
   * @brief Constructor, with another renderer object.
   *
   * @param[in] other  Another renderer object.
   */
  Renderer(const Renderer& other);
  /** @brief Destructor. */
  ~Renderer();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another renderer object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Renderer& operator = (const Renderer& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another renderer object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Renderer& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another renderer object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Renderer& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Start to quickly render a PDF page, mainly for thumbnail purpose.
   *
   * @details This function is mainly used for render a page for thumbnail purpose.
   *          The rendered content will not be completed: all the annotations will be ignored, event if
   *          flag @link Renderer::e_RenderAnnot @endlink is set by function
   *          @link Renderer::SetRenderContentFlags @endlink; text content will become blurred and
   *          will be replace by pixel point.<br>
   *          It may still take a long time to do this quick rendering when page has complex or large contents,
   *          so Foxit PDF SDK uses a progressive process to do this.
   *
   * @param[in] page    A valid PDF page. It should have been parsed.
   * @param[in] matrix  The transformation matrix used for rendering, which is usually returned by function
   *                    @link pdf::PDFPage::GetDisplayMatrix @endlink.
   * @param[in] pause   Pause callback object which decides if the rendering process needs to be paused.
   *                    This can be <b>NULL</b> which means not to pause during the rendering process.
   *                    If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                    Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  Progressive StartQuickRender(const pdf::PDFPage& page, const Matrix& matrix, PauseCallback* pause = NULL);

 /**
   * @brief Start to render a PDF page.
   *
   * @details It may take a long time to render a PDF page with complex or large contents, so Foxit PDF SDK uses
   *          a progressive process to do this.<br>
   *          Widget annotation is always associated with form field and form control in Foxit PDF SDK. For how to
   *          render widget annotations, here is a recommended flow:
   *          <ul>
   *          <li>After loading a PDF page, first render the page and all annotations in this page
   *              (including widget annotations).</li>
   *          <li>Then, if user uses @link pdf::interform::Filler @endlink object to fill the form, user should use function
   *              @link pdf::interform::Filler::Render @endlink to render the focused form control instead of using
   *              function @link Renderer::RenderAnnot @endlink.</li>
   *          </ul>
   *
   * @param[in] page    A valid PDF page. If only to render annotations (that means only
   *                    @link Renderer::e_RenderAnnot @endlink is set by function
   *                    @link Renderer::SetRenderContentFlags @endlink), there is no need to parse the input page;
   *                    otherwise the input page should have been parsed.
   * @param[in] matrix  The transformation matrix used for rendering, which is usually returned by function
   *                    @link pdf::PDFPage::GetDisplayMatrix @endlink.
   * @param[in] pause   Pause callback object which decides if the rendering process needs to be paused.
   *                    This can be <b>NULL</b> which means not to pause during the rendering process.
   *                    If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                    Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  Progressive StartRender(const pdf::PDFPage& page, const Matrix& matrix, PauseCallback* pause = NULL);
#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Start to render a reflow page.
   *
   * @details It may take a long time to render a reflow page with complex or large contents, so Foxit PDF SDK uses
   *          a progressive process to do this.
   *
   * @param[in] reflow_page  A valid reflow page. It should have been parsed.
   * @param[in] matrix       The transformation matrix used for rendering, which is usually returned by function
   *                         @link pdf::ReflowPage::GetDisplayMatrix @endlink.
   * @param[in] pause        Pause callback object which decides if the rendering process needs to be paused.
   *                         This can be <b>NULL</b> which means not to pause during the rendering process.
   *                         If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                         Default value:<b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  Progressive StartRenderReflowPage(const pdf::ReflowPage& reflow_page, const Matrix& matrix,
                                    PauseCallback* pause = NULL);

#ifndef _FX_NO_XFA_
  /**
   * @brief Start to render an XFA page.
   *
   * @details It will take a long time to render an XFA page with complex or large contents, so Foxit PDF SDK uses
   *          a progressive process to do this.
   *
   * @param[in] xfa_page_view  A valid XFA page.
   * @param[in] matrix         The transformation matrix used for rendering, which is usually returned by function
   *                           @link addon::xfa::XFAPage::GetDisplayMatrix @endlink.
   * @param[in] is_highlight   <b>true</b> means to highlight XFA widgets, and <b>false</b> means not to highlight
   *                           XFA widgets.
   * @param[in] pause          Pause callback object which decides if the rendering process needs to be paused.
   *                           This can be <b>NULL</b> which means not to pause during the rendering process.
   *                           If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                           Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  Progressive StartRenderXFAPage(const addon::xfa::XFAPage& xfa_page_view, const Matrix& matrix, bool is_highlight,
                                 PauseCallback* pause = NULL);
#endif
#endif
  /**
   * @brief Start to render a bitmap.
   *
   * @details It may take a long time to render a bitmap with complex or large contents, so Foxit PDF SDK uses
   *          a progressive process to do this.
   *
   * @param[in] bitmap         A valid bitmap. User should ensure the bitmap to keep valid until
   *                           current rendering process is finished.
   * @param[in] matrix         The transformation matrix used for rendering. This matrix is used as image matrix:<br>
   *                           assume that <i>h</i> is image height, <i>w</i> is image width, and then matrix
   *                           [w 0 0 h 0 0] will produce an identical image.
   * @param[in] clip_rect      Clip rectangle for the rendering device. This can be <b>NULL</b>.
   *                           Default value: <b>NULL</b>.
   * @param[in] interpolation  Bitmap interpolation flags. Please refer to values starting from
   *                           @link Bitmap::e_Downsample @endlink and this can be one or a combination of these values.
   *                           If not specify any flag, please use 0. Default value: 0.
   * @param[in] pause          Pause callback object which decides if the rendering process needs to be paused.
   *                           This can be <b>NULL</b> which means not to pause during the rendering process.
   *                           If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                           Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  Progressive StartRenderBitmap(const Bitmap& bitmap, const Matrix& matrix,
                                const RectI* clip_rect = NULL, uint32 interpolation = 0,
                                PauseCallback* pause = NULL);
#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Set the annotation's appearance type for rendering.
   *
   * @param[in] ap_type  Type of annotation's appearance. Please refer to values starting from
   *                     @link pdf::annots::Annot::e_AppearanceTypeNormal @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetRenderAnnotAppearanceType(foxit::pdf::annots::Annot::AppearanceType ap_type);

  /**
   * @brief Render a specified annotation.
   *
   * @details When this function is called, rendering flag (set by function @link Renderer::SetRenderContentFlags @endlink or
   *          by default) will be ignored.
   *
   * @param[in] annot   An annotation object to be rendered. If input annot is a pop-up annotation, this function will
   *                    not render it and will return <b>false</b>.
   * @param[in] matrix  The transformation matrix used for rendering, which is usually returned by function
   *                    @link pdf::PDFPage::GetDisplayMatrix @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RenderAnnot(const pdf::annots::Annot& annot, const Matrix& matrix);
#endif
  /**
   * @brief Render form controls.
   *
   * @details When this function is called, rendering flag (set by function @link Renderer::SetRenderContentFlags @endlink 
   * 		  or by default) will be ignored.
   *
   * @param[in] page    A valid PDF page. If input page is invalid, this function do nothing and return <b>false</b> directly.
   * @param[in] matrix  The transformation matrix used for rendering, which is usually returned by function
   *                    @link pdf::PDFPage::GetDisplayMatrix @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RenderFormControls(const pdf::PDFPage& page, const Matrix& matrix);
#ifndef __EMSCRIPTEN_RENDER__  
  /**
   * @brief Render a graphics object.
   *
   * @details When this function is called, rendering flag (set by function @link Renderer::SetRenderContentFlags @endlink or
   *          by default) will be ignored.
   *
   * @param[in] graphics_object  A valid PDF graphics object to be rendered. 
   * @param[in] page             A valid PDF page. Parameter <i>graphics_object</i> belongs to this PDF page.
   * @param[in] matrix           The transformation matrix used for rendering, which is usually returned by function
   *                             @link pdf::PDFPage::GetDisplayMatrix @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RenderGraphicsObject(const pdf::graphics::GraphicsObject* graphics_object, const pdf::PDFPage& page, const Matrix& matrix);
#endif
  /**
   * @brief Set the clipping rectangle which will be used in following rendering progress
   *
   * @param[in] clip_rect  A clipping rectangle. If it is <b>NULL</b>, that means not to use clipping rectangle in
   *                       following rendering progress.
   *
   * @return None.
   */
  void SetClipRect(const RectI* clip_rect);

  /**
   * @brief Set clipping path using filled region.
   *
   * @param[in] clip_path  A clipping path.
   * @param[in] matrix     The transformation matrix used for clipping.
   * @param[in] fill_mode  Fill mode. It should be value @link e_FillModeAlternate @endlink or
   *                       @link e_FillModeWinding @endlink.
   *
   * @return None.
   */
  void SetClipPathFill(const Path& clip_path, const Matrix& matrix, foxit::common::FillMode fill_mode);

  /**
   * @brief Set clipping path using stroked region.
   *
   * @param[in] clip_path    A clipping path.
   * @param[in] matrix       The transformation matrix used for clipping.
   * @param[in] graph_state  New graph state, for pen attributes. It can be <b>NULL</b>. Default value: <b>NULL</b>.
   *
   * @return None.
   */
  void SetClipPathStroke(const Path& clip_path, const Matrix& matrix, const GraphState* graph_state = NULL);

  /**
   * @brief Set rendering flag to decide what content will be rendered.
   *
   * @details If this function is not called, default value
   *          (@link Renderer::e_RenderPage @endlink | @link Renderer::e_RenderAnnot @endlink) will be used.
   *
   * @param[in] render_content_flags  Rendering content flags. Please refer to values starting from
   *                                  @link Renderer::e_RenderPage @endlink and this should be one or a combination of
   *                                  these values.
   *
   * @return None.
   */
  void SetRenderContentFlags(uint32 render_content_flags);

  /**
   * @brief Set rendering flag to decide whether to render annotations in thumbnail mode or not.
   *
   * @details In thumbnail mode, the flags of annotations, "NoZoom" and "NoRotate", will be ignored.
   *          This rendering flag is available only when flag @link Renderer::e_RenderAnnot @endlink is used for rendering or
   *          function @link Renderer::RenderAnnot @endlink is called. Please refer to function @link Renderer::SetRenderContentFlags @endlink
   *          about setting flag @link Renderer::e_RenderAnnot @endlink.<br>
   *          If this function is not called, default value <b>false</b> will be used when this rendering flag is available.
   *
   * @param[in] is_render_annots_for_thumbnail  <b>true</b> means to render annotations in thumbnail mode.
   *                                            <b>false</b> means not to render annotations in thumbnail mode.
   *
   * @return None.
   */
  void SetRenderAnnotsForThumbnail(bool is_render_annots_for_thumbnail);

  /**
   * @brief Set the flag to decide whether to render form fields (except signature fields).
   *
   * @details This rendering flag is available only when flag @link Renderer::e_RenderAnnot @endlink is used for rendering or
   *          function @link Renderer::RenderAnnot @endlink is called. Please refer to function @link Renderer::SetRenderContentFlags @endlink
   *          about setting flag @link Renderer::e_RenderAnnot @endlink.<br>
   *          If this function is not called, default value <b>true</b> will be used when this flag is available.
   *
   * @param[in] is_render_formfield  <b>true</b> means to render form fields (except signature fields).
   *                                 <b>false</b> means not to render form fields (except signature fields).
   *
   * @return None.
   */
  void SetRenderFormField(bool is_render_formfield);

  /**
   * @brief Set the flag to decide whether to render signatures or not.
   *
   * @details This rendering flag is available only when flag @link Renderer::e_RenderAnnot @endlink is used for rendering or
   *          function @link Renderer::RenderAnnot @endlink is called. Please refer to function @link Renderer::SetRenderContentFlags @endlink
   *          about setting flag @link Renderer::e_RenderAnnot @endlink.<br>
   *          If this function is not called, default value <b>true</b> will be used when this flag is available.
   *
   * @param[in] is_render_signature  <b>true</b> means to render signatures.
   *                                 <b>false</b> means not to render signatures.
   *
   * @return None.
   */
  void SetRenderSignature(bool is_render_signature);
#ifndef __EMSCRIPTEN_RENDER__  
  /**
   * @brief Set layer context to render context handle.
   *
   * @details In order to render one layer when PDF page's contents is rendered on a rendering context,
   *          user should call this function to set the layer context to render context.
   *
   * @param[in] layer_context  A layer context object.
   *
   * @return None.
   */
  void SetLayerContext(const pdf::LayerContext& layer_context);
#endif
  /**
   * @brief Set color mode.
   *
   * @details If this function is not called, default value
   *          @link Renderer::e_ColorModeNormal @endlink will be used.
   *
   * @param[in] color_mode  Color mode value. It should be one of following values:
   *                        <ul>
   *                        <li>@link Renderer::e_ColorModeNormal @endlink means normal color mode.</li>
   *                        <li>@link Renderer::e_ColorModeMappingGray @endlink means to
   *                            map white/black color value to background/foreground; for other colors, no change.
   *                            If this mode is used, please call function
   *                            @link Renderer::SetMappingModeColors @endlink to set "background color" and
   *                            "foreground color".</li>
   *                        <li>@link Renderer::e_ColorModeMapping @endlink means to
   *                            map a color value to the color range defined by a background color and
   *                            a foreground color. If this mode is used, please call function
   *                            @link Renderer::SetMappingModeColors @endlink to set "background color" and
   *                            "foreground color".</li>
   *                        </ul>
   *
   * @return None.
   */
  void SetColorMode(ColorMode color_mode);
  /**
   * @brief Set background color and foreground color when color mode is @link Renderer::e_ColorModeMappingGray @endlink
   *        or @link Renderer::e_ColorModeMapping @endlink.
   *
   * @param[in] background_color  The background color. Format: 0xAARRGGBB.
   * @param[in] foreground_color  The foreground color. Format: 0xAARRGGBB.
   *
   * @return None.
   */
  void SetMappingModeColors(ARGB background_color, ARGB foreground_color);

  /**
   * @brief Set the flag to decide whether to use ClearType-like anti-aliasing to render text objects.
   *
   * @details If this function is not called, default value <b>true</b> will be used.
   *
   * @param[in] is_clear_type  <b>true</b> means to use ClearType-like anti-aliasing to render text objects.
   *                           <b>false</b> means not to use ClearType-like anti-aliasing to render text objects.
   *
   * @return None.
   */
  void SetClearType(bool is_clear_type);
  /**
   * @brief Set the flag to decide whether to print text as path or bitmap.
   *
   * @details When this flag is <b>true</b>, Foxit PDF SDK will render text in different way:
   *          if font size is greater than 50, print text as path; otherwise, print text as bitmap.<br>
   *          If this function is not called, default value <b>false</b> will be used.
   *
   * @param[in] is_to_print_text_graphic  <b>true</b> means to print text as path or bitmap.
   *                                      <b>false</b> means not to print text as path or bitmap.
   *
   * @return None.
   */
  void SetPrintTextAsGraphic(bool is_to_print_text_graphic);

  /**
   * @brief Set the flag to decide whether to print text as image.
   *
   * @details If this function is not called, default value <b>false</b> will be used.
   *
   * @param[in] is_to_print_text_image  <b>true</b> means to print text as image.
   *                                    <b>false</b> means not to print text as image.
   *
   * @return None.
   */
  void SetPrintTextAsImage(bool is_to_print_text_image);

  /**
   * @brief Set the flag to decide whether to use down-sampling for image stretching.
   *
   * @details If this function is not called, default value <b>false</b> will be used.
   *
   * @param[in] is_to_force_down_sample  <b>true</b> means to use down-sampling for image stretching.
   *                                     <b>false</b> means not to use down-sampling for image stretching.
   *
   * @return None.
   */
  void SetForceDownSample(bool is_to_force_down_sample);

  /**
   * @brief Set the flag to decide whether to do rendering in print mode.
   *
   * @details Please ensure this rendering flag is set as expected when current renderer is to used for printing.
   *          For rendering annotations, if this flag is set to be <b>true</b>, Foxit PDF SDK will only render annotations
   *          which have annotation flag @link pdf::annots::Annot::e_FlagPrint @endlink.<br>
   *          If this function is not called for current renderer object yet, default value <b>false</b> will be used.
   *
   * @param[in] is_render_for_print  <b>true</b> means to render in print mode, while <b>false</b> means to render not in print mode.
   *
   * @return None.
   */
  void EnableForPrint(bool is_render_for_print);

  /**
   * @brief Set the flag to decide whether to use halftone for image stretching.
   *
   * @details If this function is not called, default value <b>true</b> will be used.
   *
   * @param[in] is_to_force_halftone  <b>true</b> means to use halftone for image stretching.
   *                                  <b>false</b> means not to use halftone for image stretching.
   *
   * @return None.
   */
  void SetForceHalftone(bool is_to_force_halftone);

  /**
   * @brief Set the flag to decide whether to draw path as thin line.
   *
   * @details If this function is not called, default value <b>false</b> will be used.
   *
   * @param[in] is_render_path_thin_line  <b>true</b> means to draw path as thin line.
   *                                      <b>false</b> means not to draw path as thin line.
   *
   * @return None.
   */
  void SetRenderPathThinLine(bool is_render_path_thin_line);

  /**
   * @brief Set the flag to decide whether to draw text anti-aliasing.
   *
   * @details If this function is not called, default value <b>true</b> will be used.
   *
   * @param[in] is_render_text_antialiasing  <b>true</b> means to draw text anti-aliasing.
   *                                         <b>false</b> means to draw text aliasing.
   *
   * @return None.
   */
  void SetRenderTextAntiAliasing(bool is_render_text_antialiasing);

  /**
   * @brief Set the flag to decide whether to draw path anti-aliasing.
   *
   * @details If this function is not called, default value <b>true</b> will be used.
   *
   * @param[in] is_render_path_antialiasing  <b>true</b> means to draw path anti-aliasing.
   *                                         <b>false</b> means to draw path aliasing.
   *
   * @return None.
   */
  void SetRenderPathAntiAliasing(bool is_render_path_antialiasing);

  /**
   * @brief Set the flag to decide whether to draw image anti-aliasing.
   *
   * @details If this function is not called, default value <b>true</b> will be used.
   *
   * @param[in] is_render_image_antialiasing  <b>true</b> means to draw image anti-aliasing, and the effect would be
   *                                          similar to values defined in enum class InterpolationFlag.
   *                                          <b>false</b> means to draw image aliasing.
   *
   * @return None.
   */
  void SetRenderImageAntiAliasing(bool is_render_image_antialiasing);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Renderer(FS_HANDLE handle =  NULL);
};
}  // namespace common
}  // namespace foxit
#endif  // FS_RENDER_H_

