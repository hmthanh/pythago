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
* @file fs_convert.h
* @brief Header file for PDF conversion related definitions and classes.
*/

#ifndef FS_CONVERT_H_
#define FS_CONVERT_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/fs_pdfpage.h"

/**
* @brief Foxit namespace.
*
* @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
*/
namespace foxit {
/**
 * @brief Add-on namespace.
 */
namespace addon {
/**
 * @brief Conversion namespace.
 */
namespace conversion {
/** This class represents setting data used for converting HTML to PDF. */
class HTML2PDFSettingData  FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for page mode used for converting HTML to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _HTML2PDFPageMode {
    /** @brief Single page mode.*/
    e_PageModeSinglePage  = 0,
    /** @brief Multiple page mode. */
    e_PageModeMultiplePage = 1
  } HTML2PDFPageMode;
  
  /** @brief Constructor. */
  HTML2PDFSettingData()
        : page_width(0)
        , page_height(0)
        , is_to_page_scale(false)
        , page_margin(0.0f, 0.0f, 0.0f, 0.0f)
        , rotate_degrees(common::e_Rotation0)
        , is_convert_link(false)
        , is_generate_tag(false)
        , page_mode(e_PageModeSinglePage)
        {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] page_width        The page width used for the coverted PDF document.
   * @param[in] page_height       The page height used for the coverted PDF document. This would be ignored if page mode
   *                              @link HTML2PDFSettingData::e_PageModeSinglePage @endlink is used.
   * @param[in] is_to_page_scale  Used to decide whether to scale the coverted PDF page or not.
   * @param[in] page_margin       The page margin used for coverted PDF document.
   * @param[in] is_convert_link   Used to decide whether the web link should be coverted or not.
   * @param[in] rotate_degrees    The rotation degree used for the coverted PDF page.Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                              this should be one of these values. 
   * @param[in] is_generate_tag   Used to decide whether the tag should be generated or not.
   * @param[in] page_mode         The page mode used for the converting.. Please refer to values starting from @link HTML2PDFSettingData::e_PageModeSinglePage @endlink and
   *                              this should be one of these values.
   *
   * @return None.
   */
  HTML2PDFSettingData(float page_width, float page_height, bool is_to_page_scale, RectF page_margin,
      bool is_convert_link, common::Rotation rotate_degrees, bool is_generate_tag, HTML2PDFPageMode page_mode) {
    this->page_width = page_width;
    this->page_height = page_height;
    this->is_to_page_scale = is_to_page_scale;
    this->page_margin = page_margin;
    this->is_convert_link = is_convert_link;
    this->rotate_degrees = rotate_degrees;
    this->is_generate_tag = is_generate_tag;
    this->page_mode = page_mode;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another HTML-to-pdf setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  HTML2PDFSettingData &operator = (const HTML2PDFSettingData& data) {
    page_width = data.page_width;
    page_height = data.page_height;
    is_to_page_scale = data.is_to_page_scale;
    page_margin = data.page_margin;
    is_convert_link = data.is_convert_link;
    rotate_degrees = data.rotate_degrees;
    is_generate_tag = data.is_generate_tag;
    page_mode = data.page_mode;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] page_width        The page width used for the coverted PDF document.
   * @param[in] page_height       The page height used for the coverted PDF document. This would be ignored if page mode
   *                              @link HTML2PDFSettingData::e_PageModeSinglePage @endlink is used.
   * @param[in] is_to_page_scale  Used to decide whether to scale the coverted PDF page or not.
   * @param[in] page_margin       The page margin used for coverted PDF document.
   * @param[in] is_convert_link   Used to decide whether the web link should be coverted or not.
   * @param[in] rotate_degrees    The rotation degree used for the coverted PDF page.Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                              this should be one of these values.
   * @param[in] is_generate_tag   Used to decide whether the tag should be generated or not.
   * @param[in] page_mode         The page mode used for the converting.. Please refer to values starting from @link HTML2PDFSettingData::e_PageModeSinglePage @endlink and
   *                              this should be one of these values.
   *
   * @return None.
   */
  void Set(float page_width, float page_height, bool is_to_page_scale, RectF page_margin,
      bool is_convert_link, common::Rotation rotate_degrees, bool is_generate_tag, HTML2PDFPageMode page_mode) {
      this->page_width = page_width;
      this->page_height = page_height;
      this->is_to_page_scale = is_to_page_scale;
      this->page_margin = page_margin;
      this->is_convert_link = is_convert_link;
      this->rotate_degrees = rotate_degrees;
      this->is_generate_tag = is_generate_tag;
      this->page_mode = page_mode;
  }

  /** @brief The page width used for the coverted PDF document. */
  float          page_width;

  /**
   * @brief The page height used for the coverted PDF document.
   *
   * @note The page height would be ignored if page mode @link HTML2PDFSettingData::e_PageModeSinglePage @endlink is used.
   */
  float          page_height;

  /** @brief Used to decide whether to scale the coverted PDF page or not. */
  bool           is_to_page_scale;

  /**
   * @brief The page margin used for coverted PDF document.
   *
   * @note This value does not represents a rectangle. It just defines the left margin, bottom margin,
   *       right margin and top margin of a PDF page.
   */
  RectF          page_margin;

  /** 
   * @brief The rotation degree used for the coverted PDF page.Please refer to values starting from @link common::e_Rotation0 @endlink and
   *        this should be one of these values. 
   */
  common::Rotation       rotate_degrees;

  /** @brief Used to decide whether the web link should be coverted or not. */
  bool           is_convert_link;

  /** @brief Used to decide whether the tag should be generated or not. */
  bool           is_generate_tag;

  /**
   * @brief The page mode used for the converting. Please refer to values starting from @link HTML2PDFSettingData::e_PageModeSinglePage @endlink and
   *        this should be one of these values.
   */
  HTML2PDFPageMode page_mode;
};

#if (defined(_WIN32) || defined(_WIN64))

/** This class represents setting data used for converting Word to PDF. */
class Word2PDFSettingData FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for optimize option (which specifies resolution and quality)
   *        for converting Word to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ConvertOptimizeOption {
    /** @brief Optimize option: convert for print, which is higher quality and results in a larger file size. */
    e_ConvertOptimizeOptionForPrint  = 0,
    /** @brief Optimize option: convert for screen, which is a lower quality and results in a smaller file size. */
    e_ConvertOptimizeOptionForOnScreen = 1
  } ConvertOptimizeOption;
  
  /**
   * @brief Enumeration for content option which specifies
   *        how much content of Word document is to be converted to PDF document.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ConvertContentOption {
    /** @brief Convert Word document without markup. */
    e_ConvertContentOptionOnlyContent  = 0,
    /** @brief Convert Word document with markup. */
    e_ConvertContentOptionWithMarkup = 1
  } ConvertContentOption;
  
  /**
   * @brief Enumeration for bookmark option for for converting Word to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ConvertBookmarkOption {
    /** @brief Do not create bookmark in converted PDF file. */
    e_ConvertBookmarkOptionNone  = 0,
    /**
     * @brief Create bookmarks in converted PDF file by using each heading of Word document.
     * @details Here, "Word heading" includes only headings within the main document and text boxes
     *          not within headers, footers, endnotes, footnotes, or comments.
     */
    e_ConvertBookmarkOptionUseHeadings = 1,
    /**
     * @brief Create bookmarks in converted PDF file by using each bookmarks of Word document.
     * @details Here, "Word bookmark" includes all bookmarks except those contained within headers and footers.
     */
    e_ConvertBookmarkOptionUseWordBookmark = 2
  } ConvertBookmarkOption;
  

  /** @brief Constructor. */
  Word2PDFSettingData()
      : include_doc_props(false)
      , convert_to_pdfa(false)
      , optimize_option(Word2PDFSettingData::e_ConvertOptimizeOptionForPrint)
      , content_option(Word2PDFSettingData::e_ConvertContentOptionOnlyContent)
      , bookmark_option(Word2PDFSettingData::e_ConvertBookmarkOptionNone)
  {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] include_doc_props  A boolean value which indicates whether to include
   *                               Word document properties in the converted PDF document.
   * @param[in] convert_to_pdfa    (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *                               or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   * @param[in] optimize_option    Optimize option for covnerting Word to PDF, which specifies
   *                               the resolution and quality of the converted PDF document.
   *                               Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertOptimizeOptionForPrint @endlink
   *                               and this should be one of these values.
   * @param[in] content_option     Content option for covnerting Word to PDF, which specifies
   *                               how much content of Word document is to be converted to PDF file.
   *                               Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertContentOptionOnlyContent @endlink
   *                               and this should be one of these values.
   * @param[in] bookmark_option    Bookmark option for covnerting Word to PDF, which specifies
   *                               whether to export bookmarks to converted PDF file,
   *                               and the type of bookmarks. Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertBookmarkOptionNone @endlink
   *                               and this should be one of these values.
   */
  Word2PDFSettingData(bool include_doc_props, bool convert_to_pdfa, ConvertOptimizeOption optimize_option,
                      ConvertContentOption content_option, ConvertBookmarkOption bookmark_option) {
    this->include_doc_props = include_doc_props;
    this->convert_to_pdfa = convert_to_pdfa;
    this->optimize_option = optimize_option;
    this->content_option = content_option;
    this->bookmark_option = bookmark_option;
  }

  /**
  * @brief Assign operator.
  *
  * @param[in] data  Another Word-to-PDF setting data object, whose value would be assigned to current object.
  *
  * @return Reference to current object itself.
  */
  Word2PDFSettingData &operator = (const Word2PDFSettingData& data) {
    include_doc_props = data.include_doc_props;
    convert_to_pdfa = data.convert_to_pdfa;
    optimize_option = data.optimize_option;
    content_option = data.content_option;
    bookmark_option = data.bookmark_option;
    return (*this);
  }

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] include_doc_props  A boolean value which indicates whether to include
   *                               Word document properties in the converted PDF document.
   * @param[in] convert_to_pdfa    (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *                               or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   * @param[in] optimize_option    Optimize option for covnerting Word to PDF, which specifies
   *                               the resolution and quality of the converted PDF document.
   *                               Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertOptimizeOptionForPrint @endlink
   *                               and this should be one of these values.
   * @param[in] content_option     Content option for covnerting Word to PDF, which specifies
   *                               how much content of Word document is to be converted to PDF file.
   *                               Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertContentOptionOnlyContent @endlink
   *                               and this should be one of these values.
   * @param[in] bookmark_option    Bookmark option for covnerting Word to PDF, which specifies
   *                               whether to export bookmarks to converted PDF file,
   *                               and the type of bookmarks. Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertBookmarkOptionNone @endlink
   *                               and this should be one of these values.
   *
   * @return None.
   */
  void Set(bool include_doc_props, bool convert_to_pdfa, ConvertOptimizeOption optimize_option,
           ConvertContentOption content_option, ConvertBookmarkOption bookmark_option) {
    this->include_doc_props = include_doc_props;
    this->convert_to_pdfa = convert_to_pdfa;
    this->optimize_option = optimize_option;
    this->content_option = content_option;
    this->bookmark_option = bookmark_option;
  }

  /**
   * @brief A boolean value which indicates whether to include Word document properties
   *        in the converted PDF document.
   *
   * @details <b>true</b> means to include Word document properties in the converted PDF document.<br>
   *          <b>false</b> means not to include Word document properties in the converted PDF document.
   */
  bool include_doc_props;

  /**
   * @brief (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *        or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   *
   * @details <b>true</b> means to convert Word document to a PDF/A file.<br>
   *          <b>false</b> means to convert Word document to a common file.
   */
  bool convert_to_pdfa;

  /**
   * @brief Optimize option for covnerting Word to PDF, which specifies the resolution and quality of
   *        the converted PDF document. Please refer to values starting
   *        from @link Word2PDFSettingData::e_ConvertOptimizeOptionForPrint @endlink and
   *        this should be one of these values.
   */
  ConvertOptimizeOption optimize_option;

  /**
   * @brief Content option for covnerting Word to PDF, which specifies how much content of Word document
   *        is to be converted to PDF file. Please refer to values starting
   *        from @link Word2PDFSettingData::e_ConvertContentOptionOnlyContent @endlink and
   *        this should be one of these values.
   */
  ConvertContentOption content_option;

  /**
   * @brief Bookmark option for covnerting Word to PDF, which specifies whether to export bookmarks to converted PDF file,
   *        and the type of bookmarks. Please refer to values starting
   *        from @link Word2PDFSettingData::e_ConvertBookmarkOptionNone @endlink and
   *        this should be one of these values.
   */
  ConvertBookmarkOption bookmark_option;
};

/** This class represents setting data used for converting Excel to PDF. */
class Excel2PDFSettingData FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for quality for converting Excel to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ConvertQuality {
    /** @brief Standard quality. */
    e_ConvertQualityStandard  = 0,
    /** @brief Minimum quality. */
    e_ConvertQualityMinimum = 1
  } ConvertQuality;
  
  /**
   * @brief Enumeration for scaling type for each sheet in the Excel document for convertin Excel to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ScaleType {
    /** @brief No scaling. */
    e_ScaleTypeNone  = 0,
    /** @brief Fit all columns of one sheet on one page. */
    e_ScaleTypeFitAllColumns = 1,
    /** @brief Fit all rows of one sheet on one page. */
    e_ScaleTypeFitAllRows = 2,
    /** @brief Fit a sheet on one page. */
    e_ScaleTypeFitSheet = 3
  } ScaleType;
  

  /** @brief Constructor. */
  Excel2PDFSettingData()
      : include_doc_props(false)
      , convert_to_pdfa(false)
      , quality(Excel2PDFSettingData::e_ConvertQualityStandard)
      , ignore_print_area(true)
      , scale_type(Excel2PDFSettingData::e_ScaleTypeNone)
    {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] include_doc_props  A boolean value which indicates whether to include
   *                               Excel document properties in the converted PDF document.
   * @param[in] convert_to_pdfa    (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *                               or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   * @param[in] quality            Quality for covnerting Excel to PDF. Please refer to values starting
   *                               from @link Excel2PDFSettingData::e_ConvertQualityStandard @endlink and
   *                               this should be one of these values.
   * @param[in] ignore_print_area  A boolean value which indicates whether to ignore any print area set
   *                               when convering Excel document to PDF file.
   * @param[in] scale_type         Scale type for the Excel sheet when converting Excel document to
   *                               PDF file. Please refer to values starting from
   *                               @link Excel2PDFSettingData::e_ScaleTypeNone @endlink
   *                               and this should be one of these values.
   */
  Excel2PDFSettingData(bool include_doc_props, bool convert_to_pdfa, ConvertQuality quality,
                       bool ignore_print_area, ScaleType scale_type) {
    this->include_doc_props = include_doc_props;
    this->convert_to_pdfa = convert_to_pdfa;
    this->quality = quality;
    this->ignore_print_area = ignore_print_area;
    this->scale_type = scale_type;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another Excel-to-PDF setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Excel2PDFSettingData &operator = (const Excel2PDFSettingData& data) {
    include_doc_props = data.include_doc_props;
    convert_to_pdfa = data.convert_to_pdfa;
    quality = data.quality;
    ignore_print_area = data.ignore_print_area;
    scale_type = data.scale_type;
    return (*this);
  }

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] include_doc_props  A boolean value which indicates whether to include
   *                               Excel document properties in the converted PDF document.
   * @param[in] convert_to_pdfa    (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *                               or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   * @param[in] quality            Quality for covnerting Excel to PDF. Please refer to values starting
   *                               from @link Excel2PDFSettingData::e_ConvertQualityStandard @endlink and
   *                               this should be one of these values.
   * @param[in] ignore_print_area  A boolean value which indicates whether to ignore any print area set
   *                               when convering Excel document to PDF file.
   * @param[in] scale_type         Scale type for the Excel sheet when converting Excel document to
   *                               PDF file. Please refer to values starting from
   *                               @link Excel2PDFSettingData::e_ScaleTypeNone @endlink
   *                               and this should be one of these values.
   *
   * @return None.
   */
  void Set(bool include_doc_props, bool convert_to_pdfa, ConvertQuality quality,
           bool ignore_print_area, ScaleType scale_type) {
    this->include_doc_props = include_doc_props;
    this->convert_to_pdfa = convert_to_pdfa;
    this->quality = quality;
    this->ignore_print_area = ignore_print_area;
    this->scale_type = scale_type;
  }

  /**
   * @brief A boolean value which indicates whether to include Excel document properties
   *        in the converted PDF document.
   *
   * @details <b>true</b> means to include Excel document properties in the converted PDF document.<br>
   *          <b>false</b> means not to include Excel document properties in the converted PDF document.
   */
  bool include_doc_props;

  /**
   * @brief (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *        or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   *
   * @details <b>true</b> means to convert Excel document to a PDF/A file.<br>
   *          <b>false</b> means to convert Excel document to a common file.
   */
  bool convert_to_pdfa;

  /**
   * @brief Quality for covnerting Excel to PDF. Please refer to values starting
   *        from @link Excel2PDFSettingData::e_ConvertQualityStandard @endlink and
   *        this should be one of these values.
   */
  ConvertQuality quality;

  /**
   * @brief A boolean value which indicates whether to ignore any print area set
   *        when convering Excel document to PDF file.
   *
   * @details <b>true</b> means to ignore any setting of print area in Excel document.<br>
   *          <b>false</b> means to use the setting of print areas in Excel document.
   */
  bool ignore_print_area;

  /**
   * @brief Scale type for the Excel sheet when converting Excel document to PDF file.
   *        Please refer to values starting from @link Excel2PDFSettingData::e_ScaleTypeNone @endlink
   *        and this should be one of these values.
   */
  ScaleType scale_type;
};
#endif  // #if (defined(_WIN32) || defined(_WIN64))

/**
 * Conversion add-on module can be used to do some conversion between PDF file and other file formats.
 * Before using "Conversion" module, user should first prepare font resource folder as described in "Foxit PDF SDK Developer Guide.pdf" document.
 * Before using any class or methods in this module, please ensure Foxit PDF SDK has been initialized successfully
 * by function @link common::Library::Initialize @endlink with a key including "Conversion" module.
 *
 * @see @link common::Library @endlink
 */
class Convert FS_FINAL : public Base {
 public:
   /**
    * @brief Convert a HTML format file or a url of a Web page to a PDF file.
    *
    * @details Currently, this function can only be used for Windows and Mac OS; for other platform, this function will
    *          return directly without doing anything.
    *
    * @param[in] src_html        A URL of Web page or a HTML format file path. This should not be an empty string.
    * @param[in] engine_path     The directory path of "HTML to PDF" engine. This should not be an empty string.
    * @param[in] cookies_path    Path of cookies file. If this is an empty string, that means no cookie file is used.
    * @param[in] setting_data    Setting data used for converting.
    * @param[in] saved_pdf_path  A path for saving the converted PDF file. This should not be an empty string.
    * @param[in] timeout         Seconds for timeout used for loading webpages. It should be set to a value greater than 15.
    *                            If this is less than 15, 15 will be used by default.
    *
    * @return None.
    */
   static void FromHTML(const wchar_t* src_html, const wchar_t* engine_path, const wchar_t* cookies_path, const HTML2PDFSettingData& setting_data, const wchar_t* saved_pdf_path, int32 timeout);

#if (defined(_WIN32) || defined(_WIN64))
   /**
    * @brief Convert a Word format file to a PDF file.
    *
    * @details Currently, this function can only be used for Windows.
    *
    * @param[in] src_word_file_path  Path of a Word format file. This should not be an empty string.
    * @param[in] src_file_password   Password for the input Word format file. If no password is needed for the file,
    *                                please pass an empty string.
    * @param[in] saved_pdf_path      Path of the saved PDF file as conversion result. This should not be an empty string.
    * @param[in] setting_data        Setting data used for converting.
    *
    * @return None.
    */
   static void FromWord(const wchar_t* src_word_file_path, const wchar_t* src_file_password, const wchar_t* saved_pdf_path, const Word2PDFSettingData& setting_data);

   /**
    * @brief Convert a Excel format file to a PDF file.
    *
    * @details Currently, this function can only be used for Windows.
    *
    * @param[in] src_excel_file_path  Path of a Excel format file. This should not be an empty string.
    * @param[in] src_file_password    Password for the input Excel format file. If no password is needed for the file,
    *                                 please pass an empty string.
    * @param[in] saved_pdf_path       Path of the saved PDF file as conversion result. This should not be an empty string.
    * @param[in] setting_data         Setting data used for converting.
    *
    * @return None.
    */
   static void FromExcel(const wchar_t* src_excel_file_path, const wchar_t* src_file_password, const wchar_t* saved_pdf_path, const Excel2PDFSettingData& setting_data);
#endif  // #if (defined(_WIN32) || defined(_WIN64))

};
}
}
}
#endif
