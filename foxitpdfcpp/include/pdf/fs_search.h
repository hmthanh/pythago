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
 * @file fs_search.h
 * @brief Header file for text related definitions and classes.
 */

#ifndef FS_SEARCH_H_
#define FS_SEARCH_H_

#include "common/fs_common.h"
#include "pdf/annots/fs_annot.h"
#include "pdf/fs_pdfpage.h"
#ifndef _FX_NO_XFA_
#include "addon/xfa/fs_xfa.h"
#endif

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
 * This class represents a callback object which can be used to cancel a searching process.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class SearchCancelCallback
{
 public:
  /**
   * @brief A callback function used to check whether to cancel the searching process or not.
   *
   * @return <b>true</b> means the searching process needs to be canceled, while <b>false</b> means
   *         the searching process does not need to be canceled.
   */
  virtual bool NeedToCancelNow() = 0;
};

/** This class represents textpage character information. */
class TextPageCharInfo FS_FINAL : public Object {
 public:
  /**
   * @brief Enumeration for PDF textpage character flag.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _TextCharFlag {
    /** @brief Character flag: Unknown. */
    e_Unknown = -1,
    /** @brief Character flag: Normal. */
    e_Normal = 0,
    /** @brief Character flag: Generated. */
    e_Generated = 1,
    /** @brief Character flag: UnUnicode. */
    e_UnUnicode = 2,
    /** @brief Character flag: Hyphen. */
    e_Hyphen = 3,
    /** @brief Character flag: ComboWord. */
    e_ComboWord = 4
  } TextCharFlag;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] font         A valid font object.
   * @param[in] flag        Flags to indicate which properties of textpage character flag are meaningful.
   *                         Please refer to values starting from @link TextPageCharInfo::e_Normal @endlink and
   *                         this should be one of these values except @link TextPageCharInfo::e_Unknown @endlink.
   * @param[in] font_size    Font size. This should be a positive value.
   * @param[in] origin_x     The x-coordinate of the origin position.
   * @param[in] origin_y     The y-coordinate of the origin position.
   * @param[in] char_box     The glyph bounding box in page space.
   * @param[in] char_outbox  The typographic (display and printing) bounding box in page space. 
   *                         The width is advance width, and the height is the sum of the ascent and descent.
   * @param[in] matrix       The matrix.
   */
  TextPageCharInfo(const common::Font& font, TextCharFlag flag, float font_size, float origin_x, float origin_y,
                   const RectF& char_box, const RectF& char_outbox, const Matrix& matrix) {
    this->font = font;
    this->flag = flag;
    this->font_size = font_size;
    this->origin_x = origin_x;
    this->origin_y = origin_y;
    this->char_box = char_box;
    this->char_outbox = char_outbox;
    this->matrix = matrix;
  }

  /** @brief Constructor. */
  TextPageCharInfo()
      : flag(TextPageCharInfo::e_Unknown)
      , font_size(0)
      , origin_x(0)
      , origin_y(0) {}

  /** @brief Destructor. */
  ~TextPageCharInfo() {}

  /**
   * @brief Constructor, with another character information object.
   *
   * @param[in] char_info  Another character information object.
   */
  TextPageCharInfo(const TextPageCharInfo& char_info) {
    this->font = char_info.font;
    this->flag = char_info.flag;
    this->font_size = char_info.font_size;
    this->origin_x = char_info.origin_x;
    this->origin_y = char_info.origin_y;
    this->char_box = char_info.char_box;
    this->char_outbox = char_info.char_outbox;
    this->matrix = char_info.matrix;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] char_info  Another character information object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TextPageCharInfo& operator = (const TextPageCharInfo& char_info) {
    this->font = char_info.font;
    this->flag = char_info.flag;
    this->font_size = char_info.font_size;
    this->origin_x = char_info.origin_x;
    this->origin_y = char_info.origin_y;
    this->char_box = char_info.char_box;
    this->char_outbox = char_info.char_outbox;
    this->matrix = char_info.matrix;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] char_info  Another character information object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const TextPageCharInfo& char_info) const {
    if (font != char_info.font || flag != char_info.flag || fabs(font_size - char_info.font_size) > FLT_EPSILON ||
        fabs(origin_x - char_info.origin_x) > FLT_EPSILON || fabs(origin_y - char_info.origin_y) > FLT_EPSILON ||
        char_box != char_info.char_box || char_outbox != char_info.char_outbox || matrix != char_info.matrix)
      return false;

    return true;
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] char_info  Another character information object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const TextPageCharInfo& char_info) const{
    if (font != char_info.font || flag != char_info.flag || fabs(font_size - char_info.font_size) > FLT_EPSILON ||
        fabs(origin_x - char_info.origin_x) > FLT_EPSILON || fabs(origin_y - char_info.origin_y) > FLT_EPSILON ||
        char_box != char_info.char_box || char_outbox != char_info.char_outbox || matrix != char_info.matrix)
      return true;

    return false;
  }

  /**
   * @brief Set value.
   *
   * @param[in] font         A valid font object.
   * @param[in] flag         Flags to indicate which properties of textpage character flag are meaningful.
   *                         Please refer to values starting from @link TextPageCharInfo::e_Normal @endlink and
   *                         this should be one of these values except @link TextPageCharInfo::e_Unknown @endlink.
   * @param[in] font_size    Font size. This should be a positive value.
   * @param[in] origin_x     The x-coordinate of the origin position.
   * @param[in] origin_y     The y-coordinate of the origin position.
   * @param[in] char_box     The glyph bounding box in page space.
   * @param[in] char_outbox  The typographic (display and printing) bounding box in page space. 
   *                         The width is advance width, and the height is the sum of the ascent and descent.
   * @param[in] matrix       The matrix.
   *
   * @return None.
   */
  void Set(const common::Font& font, TextCharFlag flag, float font_size, float origin_x, float origin_y,
           const RectF& char_box, const RectF& char_outbox, const Matrix& matrix) {
    this->font = font;
    this->flag = flag;
    this->font_size = font_size;
    this->origin_x = origin_x;
    this->origin_y = origin_y;
    this->char_box = char_box;
    this->char_outbox = char_outbox;
    this->matrix = matrix;
  }

  /**
   * @brief A font for character.
   */
  common::Font font;

  /**
   * @brief Flags to indicate which properties of textpage character flag are meaningful.
   *
   * @details Please refer to values starting from @link TextPageCharInfo::e_Normal @endlink and
   *          this should be one of these values.
   */
  TextCharFlag flag;

  /**
   * @brief Font size for character.
   *
   * @details This value would a positive value.
   */
  float font_size;

  /**
   * @brief The x-coordinate of the origin position.
   */
  float origin_x;

  /**
   * @brief The y-coordinate of the origin position.
   */
  float origin_y;

  /**
   * @brief The glyph bounding box in page space.
   */
  RectF char_box;

  /**
   * @brief The typographic(display and printing) bounding box in page space. 
   */
  RectF char_outbox;

  /**
   * @brief The matrix of the character.
   */
  Matrix matrix;
};

/**
 * PDF text page represents all the text contents in a PDF page, according to a specified parsing flag for these text.
 * Class @link TextPage @endlink can be used to retrieve information about text in a PDF page, such as single character, single word,
 * text content within specified character range or rectangle and so on.<br>
 * This class object can also be used to construct objects of other text related classes in order to do more operation
 * for text contents or access specified information from text contents:
 * <ul>
 * <li>To search text in text contents of a PDF page, please construct a @link TextSearch @endlink object with text page object.</li>
 * <li>To access text that are used as a hypertext link, please construct a @link PageTextLinks @endlink object
 *     with text page object.</li>
 * </ul>
 *
 * @see @link TextSearch @endlink
 * @see @link PageTextLinks @endlink
 */
class TextPage FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for parsing flags used for text page.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _TextParseFlags {
    /** @brief Parse the text content of a PDF page by normalizing characters based on their positions in the PDF page.*/
    e_ParseTextNormal = 0x0000,
    /** @brief Parse the text content of a PDF page with outputting the hyphen on a line feed.*/
    e_ParseTextOutputHyphen = 0x0001,
    /** @brief Parse the text content of a PDF page by the stream order.*/
    e_ParseTextUseStreamOrder = 0x0002
  } TextParseFlags;
  
  /**
   * @brief Enumeration for text order flag which is used when getting text content of a PDF page.
   *
   * @details Values of this enumeration can be used alone.
   */
  typedef enum _TextOrderFlag {
    /** @brief If this is set, that means to get text content of a PDF page by the stream order.*/
    e_TextStreamOrder = 0,
    /** @brief If this is set, that means to get text content of a PDF page by the display order.*/
    e_TextDisplayOrder = 1
  } TextOrderFlag;
  

  /**
   * @brief Constructor, from a parsed PDF page.
   *
   * @param[in] page   A valid PDF page object. This page should has been parsed.
   * @param[in] flags  Parsing flags for the text page. Please refer to values starting from
   *                   @link TextPage::e_ParseTextNormal @endlink and this can be one or combination of these values.
   */
  explicit TextPage(const PDFPage& page, int flags = foxit::pdf::TextPage::e_ParseTextNormal);

  /** @brief Destructor. */
  ~TextPage();
  /**
   * @brief Constructor, with another text page object.
   *
   * @param[in] other  Another text page object.
   */
  TextPage(const TextPage& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another text page object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TextPage& operator = (const TextPage& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another text page object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const TextPage& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another text page object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const TextPage& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the count of all the characters.
   *
   * @return Count of characters.
   */
  int GetCharCount() const;

  /**
   * @brief	Get character information of a specific character.
   *
   * @param[in]	char_index	A zero-based index of character.
   *						Range: from 0 to (charcount - 1).<i>charcount</i> is returned by function
   *                        @link TextPage::GetCharCount @endlink.
   *
   * @return Character information for the character speicifed by character index.
   */
  TextPageCharInfo GetCharInfo(int char_index);

  /**
   * @brief Get all the characters within a range specified by a start index and count.
   *
   * @param[in] start  Index of start character, which is the first character of the expected text content.
   *                   Valid range: from 0 to (<i>charcount</i> -1). <i>charcount</i> is returned by function
   *                   @link TextPage::GetCharCount @endlink. Default value: 0.
   * @param[in] count  Count of characters to be retrieved. -1 means to get the whole characters
   *                   from <i>start_index</i> to the end of PDF page. Especially, when parameter <i>count</i>
   *                   is larger than (<i>charcount</i> - start), all the rest character
   *                   (from <i>start_index</i>) will be retrieved. <i>charcount</i> is returned by function
   *                   @link TextPage::GetCharCount @endlink. Default value: -1.
   *
   * @return The characters within the specified character index range.
   */
  WString GetChars(int start = 0, int count = -1) const;

  /**
   * @brief Get the character index at or around a specified position on the page,
   *        in [PDF coordinate system] (@ref PDFPage).
   *
   * @param[in] x          Value of x position, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] y          Value of y position, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] tolerance  Tolerance value for character hit detection, in point units. This should not be a negative.
   *
   * @return Index of the character, which is at or nearby point (x,y), starting from 0. Specially, if there are
   *         several characters near by point (x, y), the smallest character index will be returned.
   *         If there is no character at or nearby the point, -1 will be returned.
   */
  int GetIndexAtPos(float x, float y, float tolerance) const;

  /**
   * @brief Get the text within a rectangle, in [PDF coordinate system] (@ref PDFPage).
   *
   * @param[in] rect  A rectangle region, in [PDF coordinate system] (@ref PDFPage).
   *
   * @return Text string within the specified rectangle.
   */
  WString GetTextInRect(const RectF& rect) const;

  /**
   * @brief Get the page text.
   *
   * @param[in] flag  Text order flag to decide how to get text content of the related PDF page. Please refer to values starting from
   *                  @link TextPage::e_TextStreamOrder @endlink and this should be one of these values.
   *
   * @return All the text content of the related PDF page, in specified text order.
   */
  WString GetText(TextOrderFlag flag) const;

  /**
   * @brief Get the character range of a word at or around a specified position on the page,
   *        in [PDF coordinate system] (@ref PDFPage).
   *
   * @details Currently, for Chinese/Japanese/Korean, only support to get a single character at or
   *          around the specified position.
   *
   * @param[in] x          Value of x position, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] y          Value of y position, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] tolerance  Tolerance value for word hit detection, in point units.This should not be a negative.
   *
   * @return The character range that represents the expected word. There would be at most one valid range segment
   *         in this range object. If returned range object is empty, that means no such word is found.
   */
  common::Range GetWordAtPos(float x, float y, float tolerance) const;

  /**
   * @brief Count the text rectangles within a range specified by a start index and count.
   *
   * @param[in] start  Index of start character in the character index range.
   *                   Valid range: from 0 to (<i>charcount</i> -1). <i>charcount</i> is returned by function
   *                   @link TextPage::GetCharCount @endlink.
   * @param[in] count  Count of characters in the character index range. -1 means to get the whole characters
   *                   from <i>start_index</i> to the end of PDF page.
   *
   * @return The count of text rectangles in the specified character index range. -1 means error.
   */
  int GetTextRectCount(int start = 0, int count = -1);

  /**
   * @brief Get the text rectangle by the index.
   *
   * @param[in] rect_index  The index of the rectangle to be retrieved.
   *                        Valid range: from 0 to (<i>count</i> -1). <i>count</i> is returned by function
   *                        @link TextPage::GetTextRectCount @endlink.
   *
   * @return A specified text rectangle.
   */
  RectF GetTextRect(int rect_index) const;

  /**
   * @brief Get the text trend (as rotation) of a specified rectangle.
   *
   * @param[in] rect_index  The index of the rectangle to be retrieved.
   *                        Valid range: from 0 to (<i>count</i> -1). <i>count</i> is returned by function
   *                        @link TextPage::GetTextRectCount @endlink.
   *
   * @return Text trend, as rotation value. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *         this would be one of these values.
   */
  common::Rotation GetBaselineRotation(int rect_index);

  /**
   * @brief Get the array of all text rectangles within the specified rectangle region.
   *
   * @param[in] rect  A rectangle region, in [PDF coordinate system] (@ref PDFPage).
   *
   * @return Text rectangle array within the specified rectangle.
   */
  RectFArray GetTextRectArrayByRect(const RectF& rect);

  /**
   * @brief Get the character index range of all text rectangles within the specified rectangle region.
   *
   * @param[in] rect  A rectangle region, in [PDF coordinate system] (@ref PDFPage).
   *
   * @return Character index range of all text rectangles within the specified rectangle region.
   */
  common::Range GetCharRange(const RectF& rect);

  /**
   * @brief Get the page text which intersect with a specified an annotation.
   *
   * @details If the whole character or most part of the character intersects with an annotation, 
   *          this character will be retieved by current function.
   *
   * @param[in] annot  An annotation. Page text which intersects with this annotation is to be retrieved.
   *                   Currently, only support text markup annotation
   *                   (highlight/underline/strike-out/squggly annotations); for annotation in other types,
   *                   this function will throw exception @link foxit::e_ErrUnsupported @endlink.
   *
   * @return The text which intersects with the specified annotation.
   */
  WString GetTextUnderAnnot(annots::Annot& annot) const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit TextPage(FS_HANDLE handle =  NULL);
};

/**
 * This class can construct text search in a PDF document/an XFA document/a text page or
 * in a PDF annotation's appearance. It offers functions to do a text search and get the searching result:
 * <ul>
 * <li>To specify the searching pattern and options, use functions @link TextSearch::SetPattern @endlink,
 *     @link TextSearch::SetStartPage @endlink, @link TextSearch::SetEndPage @endlink and
 *     @link TextSearch::SetSearchFlags @endlink.</li>
 * <li>To do the searching, use function @link TextSearch::FindNext @endlink or @link TextSearch::FindPrev @endlink.</li>
 * <li>To get the searching result, use functions GetMatchXXX().</li>
 * </ul>
 */
class TextSearch FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for searching flags.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _SearchFlags {
    /** @brief No special searching options.*/
    e_SearchNormal        = 0x00,
    /** @brief If set, match the case of keyword when searching. */
    e_SearchMatchCase      = 0x01,
    /** @brief If set, match the whole word of keyword when searching. */
    e_SearchMatchWholeWord    = 0x02,
    /** @brief If set, match the key word consecutively when searching. For example, "CC" will be matched twice in "CCC". */
    e_SearchConsecutive     = 0x04
  } SearchFlags;
  

  /**
   * @brief Constructor, for a PDF document.
   *
   * @details User can set a valid @link SearchCancelCallback @endlink object in order to decide whether to cancel the searching
   *          process or not when the callback function in SearchCancelCallback is triggered.
   *
   * @param[in] document  A valid PDF document object.
   * @param[in] cancel    A @link SearchCancelCallback @endlink object which decides if the searching process needs to
   *                      be canceled when the callback function is triggered. This can be <b>NULL</b> which means not to
   *                      cancel the searching process. If this is not <b>NULL</b>, it should be a valid
   *                      @link SearchCancelCallback @endlink object implemented by user. Default value: <b>NULL</b>.
   */
  explicit TextSearch(const PDFDoc& document, SearchCancelCallback* cancel = NULL);

 #ifndef _FX_NO_XFA_
  /**
   * @brief Constructor, for a specified XFA document.
   *
   * @param[in] xfa_document  A valid XFA document object. It should have been loaded by
   *                          function @link addon::xfa::XFADoc::StartLoad @endlink.
   * @param[in] cancel        A @link SearchCancelCallback @endlink object which decides if the searching process
   *                          needs to be canceled when the callback function is triggered. This can be <b>NULL</b>
   *                          which means not to cancel the searching process. If this is not <b>NULL</b>,
   *                          it should be a valid @link SearchCancelCallback @endlink object implemented by user.
   *                          Default value: <b>NULL</b>.
   */
  explicit TextSearch(const foxit::addon::xfa::XFADoc& xfa_document, foxit::pdf::SearchCancelCallback* cancel = NULL);
#endif
  /**
   * @brief Constructor, for a specified text page.
   *
   * @param[in] text_page  A text page object.
   */
  explicit TextSearch(const foxit::pdf::TextPage& text_page);

  /**
   * @brief Constructor, for a specified PDF annotation.
   *
   * @details Currently, only support to search in appearance of following annotation types:
   *          free text annotation, stamp annotation, widget annotation, and line annotation.
   *
   * @param[in] annot  A valid annotation object.
   */
  explicit TextSearch(const foxit::pdf::annots::Annot& annot);

  /** @brief Destructor. */
  ~TextSearch();
  /**
   * @brief Constructor, with another text search object.
   *
   * @param[in] other  Another text search object.
   */
  TextSearch(const TextSearch& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another text search object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TextSearch& operator = (const TextSearch& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another text search object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const TextSearch& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another text search object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const TextSearch& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set keywords to search.
   *
   * @param[in] key_words  The text content to be searched. It should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetPattern(const wchar_t* key_words);

  /**
   * @brief Set starting page index.
   *
   * @details This function can only be used for a text search object which is constructed with 
   *          @link PDFDoc @endlink object or @link addon::xfa::XFADoc @endlink object.
   *          For other case, this function will throw exception @link foxit::e_ErrUnsupported @endlink.<br>
   *          If this function is not called, default value 0 will be used as the starting page index.
   *
   * @param[in] page_index  Index of the page, from which the search starts.
   *                        Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                        @link PDFDoc::GetPageCount @endlink for PDF document or by function
   *                        @link addon::xfa::XFADoc::GetPageCount @endlink for XFA document.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetStartPage(int page_index);

  /**
   * @brief Set ending page index.
   *
   * @details This function can only be used for a text search object which is constructed with 
   *          @link PDFDoc @endlink object or @link addon::xfa::XFADoc @endlink object.
   *          For other case, this function will throw exception @link foxit::e_ErrUnsupported @endlink.<br>
   *          If this function is not called, default value <i>count</i>-1 will be used as the ending page index.
   *
   * @param[in] page_index  Index of the page, from which the search ended.
   *                        Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                        @link PDFDoc::GetPageCount @endlink for PDF document or by function
   *                        @link addon::xfa::XFADoc::GetPageCount @endlink for XFA document.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetEndPage(int page_index);

  /**
   * @brief Set search flags.
   *
   * @details If this function is not called, default value @link TextSearch::e_SearchNormal @endlink
   *          will be used.
   *
   * @param[in] search_flags  Search flags. Please refer to values starting from @link TextSearch::e_SearchNormal @endlink
   *                          and this can be one or combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetSearchFlags(uint32 search_flags);

  /**
   * @brief Search for next matched pattern.
   *
   * @return <b>true</b> means the next match is found, while <b>false</b> means no next match can be found or
   *         any other error.
   */
  bool FindNext();

  /**
   * @brief Search for previous matched pattern.
   *
   * @return <b>true</b> means the previous match is found, while <b>false</b> means no previous match can be found or
   *         any other error.
   */
  bool FindPrev();

  /**
   * @brief Get the rectangles of current match pattern.
   *
   * @return An array of rectangles.
   */
  RectFArray GetMatchRects() const;

  /**
   * @brief Get the page index, to which current match belongs.
   *
   * @details This function can only be used for a text search in PDF document or in XFA document.
   *
   * @return The index of the page, which contains the current match, starting from 0.
   *         -1 means not matched pattern has been found.
   */
  int GetMatchPageIndex() const;

  /**
   * @brief Get the sentence that contains current match pattern.
   *
   * @return The sentence content, which contains current match.
   */
  WString GetMatchSentence();

  /**
   * @brief Get the index of the first character of current match pattern, based on the match sentence.
   *
   * @details In a sentence, there may be more than 2 match patterns. This function can help to confirm which pattern
   *          in the sentence is just current match pattern.
   *
   * @return The index of the first character of current match pattern, based on the match sentence, starting from 0.
   *         -1 means no matched sentence is found.
   */
  int GetMatchSentenceStartIndex();

  /**
   * @brief Get the index of the first character of current match pattern, based on current match page.
   *
   * @return The index of the first character, in current match page, starting from 0.
   *         -1 means no matched sentence is found.
   */
  int GetMatchStartCharIndex() const;

  /**
   * @brief Get the index of the last character of current match pattern, based on current match page.
   *
   * @return The index of the last character, in current match page, starting from 0.
   *         -1 means no matched sentence is found.
   */
  int GetMatchEndCharIndex() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit TextSearch(FS_HANDLE handle =  NULL);
};

/**
 * A text link is just text content, which represents a hypertext link to a website or a resource on the internet,
 * or an e-mail address.<br>
 * This class offers functions to get information from the text link.<br>
 * A text link object is retrieved by function @link PageTextLinks::GetTextLink @endlink.
 *
 * @see @link PageTextLinks @endlink
*/
class TextLink FS_FINAL : public Base{
 public:
  /** @brief Destructor. */
  ~TextLink();
  /**
   * @brief Constructor, with another text link object.
   *
   * @param[in] other  Another text link object.
   */
  TextLink(const TextLink& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another text link object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TextLink& operator = (const TextLink& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another text link object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const TextLink& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another text link object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const TextLink& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get URI string.
   *
   * @details A text link's URI can be a hypertext link to a website or a resource on the internet.
   *          It can also be an e-mail address.
   *
   * @return URI string.
   */
  WString GetURI();

  /**
   * @brief Get the index of start character of current hyper-link URI, based on PDF page.
   *
   * @return The index of start character, starting from 0.
   */
  int GetStartCharIndex();

  /**
   * @brief Get the index of last character of current hyper-link URI, based on PDF page.
   *
   * @return The index of last character, starting from 0.
   */
  int GetEndCharIndex();

  /**
   * @brief Get the text rectangles of current text link object.
   *
   * @return An array of rectangles.
   */
  RectFArray GetRects();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit TextLink(FS_HANDLE handle =  NULL);

};

/**
 * In a PDF page, some text content may represent a hypertext link to a website or a resource on the internet,
 * or an e-mail address. Class @link PageTextLinks @endlink is used to manage these kind of text content as text links.
 */
class PageTextLinks FS_FINAL : public Base{
 public:
  /**
   * @brief Constructor, from a parsed PDF page.
   *
   * @param[in] page  A valid PDF page object. This page should has been parsed.
   */
  explicit PageTextLinks(const TextPage& page);
  /**
   * @brief Constructor, with another @link PageTextLinks @endlink object.
   *
   * @param[in] other  Another @link PageTextLinks @endlink object.
   */
  PageTextLinks(const PageTextLinks& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another @link PageTextLinks @endlink object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PageTextLinks& operator = (const PageTextLinks& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another @link PageTextLinks @endlink object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PageTextLinks& other) const ;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another @link PageTextLinks @endlink object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PageTextLinks& other) const ;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;
  /** @brief Destructor. */
  ~PageTextLinks();

  /**
   * @brief Get the count of the URL formatted texts, in related PDF page.
   *
   * @return The count of the text links, if returned -1 means error on the construct.
   */
  int GetTextLinkCount();

  /**
   * @brief Get a text link object by index.
   *
   * @param[in] index  Index of a text link object. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PageTextLinks::GetTextLinkCount @endlink.
   *
   * @return The specified text link object.
   */
  TextLink GetTextLink(int index);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PageTextLinks(FS_HANDLE handle =  NULL);
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_SEARCH_H_

