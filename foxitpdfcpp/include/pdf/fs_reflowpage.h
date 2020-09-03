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
 * @file fs_reflowpage.h
 * @brief Header file for PDF reflow page related definitions and classes.
 */

#ifndef FS_REFLOWPAGE_H_
#define FS_REFLOWPAGE_H_

#include "common/fs_common.h"
//#include "pdf/fs_pdfpage.h"

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
class PDFPage;

/**
 * In order to display page contents in a small screen device, Foxit PDF SDK introduces the concept of "reflow page".
 * In the reflow page, original PDF page contents will be laid out to fit the specified screen size.<br>
 * For a PDF page, user may wants to keep focusing on a location in the reflow page when user switches between
 * this PDF page and its related reflow page, or switch among these related reflow pages which are in different size.
 * In order to track the focus location, Foxit PDF SDK uses "focus data" to represent the focus location.
 * Focus data is similar to bookmark or destination in PDF, but it is simpler. User can store the focus data
 * (or save the data to file) so that use can retrieved the focus location again by the focus data later, even if
 * the size of reflow page is changed.<br>
 * A reflow page object should be constructed from a parsed PDF page. This class offers functions to:
 * <ul>
 * <li>Start to parse a reflow page by functions @link ReflowPage::StartParse @endlink. Before paring a reflow page,
 *     use should use function @link ReflowPage::SetScreenSize @endlink to specify the screen size for the reflow page.
 *     User can also use following functions to specify other factors which will affect on the parsing result
 *     for the reflow page: @link ReflowPage::SetZoom @endlink, @link ReflowPage::SetParseFlags @endlink,
 *     @link ReflowPage::SetLineSpace @endlink, @link ReflowPage::SetImageScale @endlink, @link ReflowPage::SetTopSpace @endlink. 
 *     If these function are not called before parsing a reflow page, default values will be used. Please refer to comment of these functions
 *     for more details. </li>
 * <li>Get the actual content size and matrix of a parsed reflow page, by functions
 *     @link ReflowPage::GetContentWidth @endlink, @link ReflowPage::GetContentHeight @endlink,@link ReflowPage::GetDisplayMatrix @endlink.
 * </li>
 * <li>Get the focus data for a specified position in reflow page, by function @link ReflowPage::GetFocusData @endlink,
 *     or retrieve the position by a focus data, by function @link ReflowPage::GetFocusPosition @endlink. </li>
 * </ul>
 * To render the reflow page, please use function @link common::Renderer::StartRenderReflowPage @endlink.
 *
 * @see @link PDFPage @endlink
 * @see @link common::Renderer @endlink
 */
class ReflowPage FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for parsing flags used for a reflow page.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _Flags {
    /** @brief Parsing flag for normal mode, without image. */
    e_Normal = 0x0,
    /** @brief Parsing flag for image mode. */
    e_WithImage = 0x1,
    /**
   @brief Parsing flag to decide whether to allow to truncate the first/last image or line of text within
          the specified screen size or not.
   @details The height of final parsed reflow page may be larger than the actual screen height. In this case,
            the content of a reflow page would be shown in more than one screen in application. <br>
            Application may use following modes to show such reflow page:
            <ul>
            <li>Show only part of content of the reflow page in the screen in one time. When user clicks or taps,
                show the previous or next part of content. This is like to turn to a page in a real book.
                Here, call this mode as "single screen mode".</li>
            <li>Show the reflow page continuously -- that means user can scroll the screen to see any part of content
                in this reflow page. Here, call this mode as "scroll screen mode".</li>
            </ul>
            If use "single screen mode" to show a reflow page, a truncate problem may occurs: the first line of text
            or image just shows the bottom half in the top of the screen, or the last line of text of image just shows
            the top half in the bottom of the screen. This flag can be set to avoid such problem.<br>
            If use "scroll screen mode", no need to use this flag.
     */
    e_NoTruncate = 0x2
  } Flags;
  

  /**
   * @brief Constructor, from a parsed PDF page.
   *
   * @param[in] page  A valid PDF page object which has been parsed.
   */
  explicit ReflowPage(const PDFPage& page);

  /**
   * @brief Constructor, with another reflow page object.
   *
   * @param[in] other  Another reflow page object.
   */
  ReflowPage(const ReflowPage& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another reflow page object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ReflowPage& operator = (const ReflowPage& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another reflow page object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const ReflowPage& other) const ;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another reflow page object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const ReflowPage& other) const ;
  /** @brief Destructor. */
  ~ReflowPage();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;
  /**
   * @brief Set screen size. This should be called before calling function @link ReflowPage::StartParse @endlink.
   *
   * @details Before paring a reflow page, user should call this function to set the screen size
   *          for parsing the reflow page.
   *
   * @param[in] width   The screen width.
   * @param[in] height  The screen height.
   *
   * @return None.
   */
  void SetScreenSize(float width, float height);

  /**
   * @brief Set margin. This can be called before calling function @link ReflowPage::StartParse @endlink.
   *
   * @details If no margin has ever been set to current reflow page, Foxit PDF SDK will use value (0, 0, 0, 0)
   *          as default margin.<br>
   *          If new margin is set, the new margin will take effect until current reflow page has been
   *          re-parsed and rendered again.
   *
   * @param[in] left    The left margin. This value should between 0 and (screen width / 3).
   * @param[in] top     The left margin. This value should between 0 and (screen height/ 3).
   * @param[in] right   The left margin. This value should between 0 and (screen width / 3).
   * @param[in] bottom  The left margin. This value should between 0 and (screen height / 3).
   *
   * @return None.
   */
  void SetScreenMargin(int left, int top, int right, int bottom);

  /**
   * @brief Set zoom factor. This can be called before calling function @link ReflowPage::StartParse @endlink.
   *
   * @details If no zoom factor has ever been set to current reflow page, Foxit PDF SDK will use value 100
   *          as default zoom factor, which means 100%.<br>
   *          If new zoom factor is set, the new zoom factor will take effect until current reflow page has been
   *          re-parsed and rendered again.
   *
   * @param[in] zoom  Zoom factor. The value represents the percent value, for example, 100 means 100%.
   *                  This value should between 25 and 1000.<br>
   *                  If no zoom factor is set, value 100 will be used by default.
   *
   * @return None.
   */
  void SetZoom(int zoom);

  /**
   * @brief Set the parsing flag. This can be called before calling function @link ReflowPage::StartParse @endlink.
   *
   * @param[in] flags  Parsing flags. Please refer to values starting from @link ReflowPage::e_Normal @endlink and
   *                   this should be one or a combination of these values.
   *                   If no parsing flag is set, value @link ReflowPage::e_Normal @endlink will be
   *                   used by default.
   *
   * @return None.
   */
  void SetParseFlags(uint32 flags);

  /**
   * @brief Set line space. This can be called before calling function @link ReflowPage::StartParse @endlink.
   *
   * @param[in] line_space  The line space. This value should between -25 to (<i>height</i>/2). <br>
   *                        If no line space is set, value 0 will be used by default.
   *
   * @return None.
   */
  void SetLineSpace(float line_space);

  /**
   * @brief Set image scale. This can be called before calling function @link ReflowPage::StartParse @endlink.
   *
   * @param[in] image_scale  The image scale. This value should be positive number. <br>
   *                         If no image scale is set, value 1.0f will be used by default.
   *
   * @return None.
   */
  void SetImageScale(float image_scale);

  /**
   * @brief Set the top space. This can be called before calling function @link ReflowPage::StartParse @endlink.
   *
   * @details This function is used to set the distance between the page's top and the screen's top. The distance will
   *          take effect when parsing a reflow page.
   *
   * @param[in] top_space  The top space. This value should between 0 and <i>height</i>.<br>
   *                       If no top space is set, value 0 will be used by default.
   *
   * @return None.
   */
  void SetTopSpace(float top_space);

  /**
   * @brief Start to parse current reflow page.
   *
   * @details It may take a long time to parsing a reflow page, so Foxit PDF SDK uses a progressive process to do this.
   *          All the resources about reflow page will be loaded after the reflow page is parsed. <br>
   *          This function should be called before any getting function of current reflow page object can be used.
   *
   * @param[in] pause  Pause callback object which decides if the parsing process needs to be paused.
   *                   This can be <b>NULL</b> which means not to pause during the parsing process.
   *                   If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                   Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartParse(common::PauseCallback* pause = NULL);

  /**
   * @brief Get content width after current reflow page object has been parsed.
   *
   * @return Content width.
   */
  float GetContentWidth() const;

  /**
   * @brief Get content height after current reflow page object has been parsed.
   *
   * @return Content height.
   */
  float GetContentHeight() const;

  /**
   * @brief Get the display matrix, according to the offset of top side between current reflow page and screen.
   *
   * @details This function can only be used when reflow page has been parsed.
   *
   * @param[in] offset_x  Offset value, which means the offset from top side of current reflow page
   *                      to the top side of screen.
   * @param[in] offset_y  Offset value, which means the offset from left side of current reflow page
   *                      to the left side of screen.
   * @param[in] width     Width of the transformation area in screen, commonly in pixels.
   * @param[in] height    Height of the transformation area in screen, commonly in pixels.
   * @param[in] rotate    Rotation value. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                      this should be one of these values.
   *
   * @return The display matrix.
   */
  Matrix GetDisplayMatrix(float offset_x, float offset_y,int width, int height,common::Rotation rotate) const;

  /**
   * @brief Get focus data corresponding to a given position in device coordinate system.
   *
   * @details This function can only be used when reflow page has been parsed.<br>
   *          Focus data, similar to bookmark or destination in PDF, is used to locate the position of
   *          a specified content in reflow page. For a PDF page, position of a specified content is fixed
   *          and will not be changed even if the size of related reflow page is changed. So focus data can be
   *          used to locate the same content from a PDF page in its related reflow pages with different sizes
   *          but same reflow content.<br>
   *          Usually, user can call function @link ReflowPage::GetFocusData @endlink to get focus data for
   *          a specified location, and store the focus data. When the reflow page's size is changed,
   *          user can use the stored focus data in function @link ReflowPage::GetFocusPosition @endlink
   *          to get the new position and then still focus on or near the same content.
   *
   * @param[in] matrix  A matrix returned by function @link ReflowPage::GetDisplayMatrix @endlink.
   * @param[in] point   The point of a specified position, in device coordinate system.
   *
   * @return The focus data.
   */
  String GetFocusData(const Matrix& matrix, const PointF& point) const;

  /**
   * @brief Get the position in device coordinate system corresponding to a given focus data.
   *
   * @details This function can only be used when reflow page has been parsed.<br>
   *          Focus data, similar to bookmark or destination in PDF, is used to locate the position of
   *          a specified content in reflow page. For a PDF page, position of a specified content is fixed
   *          and will not be changed even if the size of related reflow page is changed. So focus data can be
   *          used to locate the same content from a PDF page in its related reflow pages with different sizes
   *          but same reflow content.<br>
   *          Usually, user can call function @link ReflowPage::GetFocusData @endlink to get focus data for
   *          a specified location, and store the focus data. When the reflow page's size is changed,
   *          user can use the stored focus data in function @link ReflowPage::GetFocusPosition @endlink
   *          to get the new position and then still focus on or near the same content.
   *
   * @param[in] matrix      A matrix returned by function @link ReflowPage::GetDisplayMatrix @endlink.
   * @param[in] focus_data  Focus data used to get its corresponding position in device coordinate system,
   *                        with specified matrix.
   *                        This is retrieved by previous calling of function @link ReflowPage::GetFocusData @endlink.
   *
   * @return The position in device coordinate system.
   */
  PointF GetFocusPosition(const Matrix& matrix, const char* focus_data) const;

  /**
   * @brief Check if current reflow page has been parsed or not.
   *
   * @return <b>true</b> means current reflow page has been parsed,
   *         while <b>false</b> means current page has not been parsed yet.
   */
  bool IsParsed() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit ReflowPage(FS_HANDLE handle =  NULL);
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_REFLOWPAGE_H_

