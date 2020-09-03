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
 * @file fs_pdfdocviewerprefs.h
 * @brief Header file for PDF document viewer preference related definitions and classes.
 */

#ifndef FS_PDFDOCVIEWERPREFS_H_
#define FS_PDFDOCVIEWERPREFS_H_

#include "common/fs_common.h"
#include "fs_pdfdoc.h"
#include "objects/fs_pdfobject.h"

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
 * Viewer preferences defines the way that a document is to be presented on the screen or in print.
 * This class should be constructed by a valid PDF document object. This class offers functions to
 * get/set different part of a PDF document's viewer preferences, such as UI visibility, display mode for
 * non full-screen mode, reading direction, the type of box item for specified purpose,
 * some preference options used for print and so on.
 *
 * @see @link PDFDoc @endlink
 */
class DocViewerPrefs FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for page scaling option.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PrintScale {
    /** @brief This means the print dialog should reflect no page scaling. */
    e_PrintScaleNone = 0,
    /** @brief This means applications should use the current print scaling. */
    e_PrintScaleAppDefault = 1
  } PrintScale;
  
  /**
   * @brief Enumeration for how various GUI elements should behave when the document is opened.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ViewerPref {
    /** @brief A flag specifying whether to hide the viewer application's tool bars when the document is active.*/
    e_HideToolbar = 0,
    /** @brief A flag specifying whether to hide the viewer application's menu bar when the document is active.*/
    e_HideMenubar = 1,
    /**
   @brief A flag specifying whether to hide user interface elements in the document's window (such as
          scroll bars and navigation controls), leaving only the document's contents displayed.
     */
    e_HideWindowUI = 2,
    /** @brief A flag specifying whether to resize the document's window to fit the size of the first displayed page.*/
    e_FitWindow = 3,
    /** @brief A flag specifying whether to position the document's window in the center of the screen.*/
    e_CenterWindow = 4,
    /**
   @brief A flag specifying whether the window's title bar should display the document title taken
          from the "Title" entry of the document information dictionary. If <b>false</b>, the title bar should
          instead display the name of the PDF file containing the document.
     */
    e_DisplayDocTitle = 5
  } ViewerPref;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @details When input parameter <i>pdf_dict</i> is <b>NULL</b>, Foxit PDF SDK will try to
   *          access viewer preferences information in the specified PDF document:
   *          if there exists viewer preferences information in the PDF document, this function is
   *          just to construct a document viewer preferences object to be associated with these information;
   *          if there is no such information in the specified PDF document, the constructed document viewer preferences object
   *          can be used to set these information to PDF document.
   *
   * @param[in] document  A valid PDF document object.
   * @param[in] pdf_dict  A PDF dictionary which represents PDF document viewer preferences information.
   *                      If this parameter is not <b>NULL</b>, this PDF dictionary should have existed
   *                      in the specified PDF document. If this parameter is <b>NULL</b>, that means to
   *                      access access viewer preferences information in the specified PDF document.
   *                      Please refer to "Details" part for more details. Default value: <b>NULL</b>.
   */
  explicit DocViewerPrefs(const PDFDoc& document, objects::PDFDictionary* pdf_dict = NULL);

  /** @brief Destructor. */
  ~DocViewerPrefs();
  /**
   * @brief Constructor, with another document viewer preferences object.
   *
   * @param[in] other  Another document viewer preferences object.
   */
  DocViewerPrefs(const DocViewerPrefs& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another document viewer preferences object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  DocViewerPrefs& operator = (const DocViewerPrefs& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another document viewer preferences object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const DocViewerPrefs& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another document viewer preferences object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const DocViewerPrefs& other) const;
  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;
  /**
   * @brief Get UI display status of a specified viewer preference item type.
   *
   * @param[in] pref  A viewer preference item type. Please refer to values starting from
   *                  @link DocViewerPrefs::e_HideToolbar @endlink and this should be one of these values.
   *
   * @return The value of the specified viewer preference item type.
   */
  bool GetUIDisplayStatus(ViewerPref pref) const;

  /**
   * @brief Set UI display status of a specified viewer preference item type.
   *
   * @details If the viewer preference item type does not existed before and has never been set,
   *          the value would be <b>false</b> by default.
   *
   * @param[in] pref   A viewer preference item type. Please refer to values starting from
   *                   @link DocViewerPrefs::e_HideToolbar @endlink and this should be one of these values.
   * @param[in] value  The new value for the specified viewer preference item type.
   *
   * @return None.
   */
  void SetUIDisplayStatus(ViewerPref pref, bool value);

  /**
   * @brief Get display mode which specifies how to display the document on exiting full-screen mode
   *        when document's display mode is full-screen.
   *
   * @details This display mode is only useful when document's display mode is full-screen.
   *          Function @link PDFDoc::GetDisplayMode @endlink can be used to check document's displaying mode.
   *
   * @return Value of non full-screen mode. It would be one of following values:
   *         <ul>
   *         <li>@link PDFDoc::e_DisplayUseNone @endlink</li>
   *         <li>@link PDFDoc::e_DisplayUseOutlines @endlink</li>
   *         <li>@link PDFDoc::e_DisplayUseThumbs @endlink</li>
   *         <li>@link PDFDoc::e_DisplayUseOC @endlink</li>
   *         </ul>
   */
  PDFDoc::DisplayMode GetNonFullScreenPageMode() const;

  /**
   * @brief Set display mode which specifies how to display the document on exiting full-screen mode
   *        when document's display mode is full-screen.
   *
   * @details This display mode is only useful when document's display mode is full-screen.
   *          Function @link PDFDoc::GetDisplayMode @endlink can be used to document's displaying mode.
   *
   * @param[in] display_mode  New display mode when exiting full-screen mode. It should be one of following values:
   *                          <ul>
   *                          <li>@link PDFDoc::e_DisplayUseNone @endlink</li>
   *                          <li>@link PDFDoc::e_DisplayUseOutlines @endlink</li>
   *                          <li>@link PDFDoc::e_DisplayUseThumbs @endlink</li>
   *                          <li>@link PDFDoc::e_DisplayUseOC @endlink</li>
   *                          </ul>
   *
   * @return None.
   */
  void SetNonFullScreenPageMode(PDFDoc::DisplayMode display_mode);

  /**
   * @brief Get the predominant reading direction for text.
   *
   * @details The reading direction information has no direct effect on the document's contents or page numbering
   *          but can be used to determine the relative positioning of pages when displayed side by side or
   *          printed n-up.
   *
   * @return <b>true</b> means left-to-right reading order, while <b>false</b> means right-to-left reading order.
   */
  bool GetReadingDirection() const;

  /**
   * @brief Set the predominant reading direction for text.
   *
   * @details The reading direction information has no direct effect on the document's contents or page numbering
   *          but can be used to determine the relative positioning of pages when displayed side by side or
   *          printed n-up.
   *
   * @param[in] is_left_to_right  The new reading direction: <b>true</b> means left-to-right reading order,
   *                              while <b>false</b> means right-to-left reading order.
   *
   * @return None.
   */
  void SetReadingDirection(bool is_left_to_right);

  /**
   * @brief Get the page boundary representing the area of a page to be displayed
   *        when viewing the document on the screen.
   *
   * @return The page box type. Please refer to values starting from @link PDFPage::e_MediaBox @endlink and
   *         this would be one of these values.
   */
  PDFPage::BoxType GetViewArea();

  /**
   * @brief Set the page boundary representing the area of a page to be displayed
   *        when viewing the document on the screen.
   *
   * @param[in] box_type  The page box type. Please refer to values starting from @link PDFPage::e_MediaBox @endlink and
   *                      this should be one of these values.
   *
   * @return None.
   */
  void SetViewArea(PDFPage::BoxType box_type);

  /**
   * @brief Get the page boundary to which the contents of a page are to be clipped
   *        when viewing the document on the screen.
   *
   * @return The page box type. Please refer to values starting from @link PDFPage::e_MediaBox @endlink and
   *         this would be one of these values.
   */
  PDFPage::BoxType GetViewClip();

  /**
   * @brief Set the page boundary to which the contents of a page are to be clipped
   *        when viewing the document on the screen.
   *
   * @param[in] box_type  The page box type. Please refer to values starting from @link PDFPage::e_MediaBox @endlink and
   *                      this should be one of these values.
   *
   * @return None.
   */
  void SetViewClip(PDFPage::BoxType box_type);

  /**
   * @brief Get the page boundary representing the area of a page to be rendered when printing the document.
   *
   * @return The page box type. Please refer to values starting from @link PDFPage::e_MediaBox @endlink and
   *         this would be one of these values.
   */
  PDFPage::BoxType GetPrintArea();

  /**
   * @brief Set the page boundary representing the area of a page to be rendered when printing the document.
   *
   * @param[in] box_type  The page box type. Please refer to values starting from @link PDFPage::e_MediaBox @endlink and
   *                      this should be one of these values.
   *
   * @return None.
   */
  void SetPrintArea(PDFPage::BoxType box_type);

  /**
   * @brief Get the page boundary to which the contents of a page are to be clipped when printing the document.
   *
   * @return The page box type. Please refer to values starting from @link PDFPage::e_MediaBox @endlink and
   *         this would be one of these values.
   */
  PDFPage::BoxType GetPrintClip();

  /**
   * @brief Set the page boundary to which the contents of a page are to be clipped when printing the document.
   *
   * @param[in] box_type  The page box type. Please refer to values starting from @link PDFPage::e_MediaBox @endlink and
   *                      this should be one of these values.
   *
   * @return None.
   */
  void SetPrintClip(PDFPage::BoxType box_type);

  /**
   * @brief Get page scaling option to be selected when a print dialog is displayed for PDF document.
   *
   * @return Page scaling option string value. Please refer to values starting from
   *         @link DocViewerPrefs::e_PrintScaleNone @endlink and this would be one of these values.
   */
  PrintScale GetPrintScale() const;

  /**
   * @brief Set page scaling option to be selected when a print dialog is displayed for PDF document.
   *
   * @param[in] print_scale  New page scaling option string. Please refer to values starting from
   *                         @link DocViewerPrefs::e_PrintScaleNone @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetPrintScale(PrintScale print_scale);

  /**
   * @brief Get the number of copies to be printed when the print dialog is opened for PDF document.
   *
   * @return The number of copies.
   */
  int GetPrintCopies() const;

  /**
   * @brief Set the number of copies to be printed when the print dialog is opened for PDF document.
   *
   * @param[in] print_copies  New integer value for number of copies. Valid range: from 1 to 5.
   *                          If input value is outside the valid range, Foxit PDF SDK will use 1 by default.
   *
   * @return None.
   */
  void SetPrintCopies(int print_copies);

  /**
   * @brief Get page range information which is used to initialize the print dialog
   *        when the print dialog is opened for the PDF document.
   *
   * @details All the indexes specified in the page range is from 0 to (pagecount - 1).
   *          If page range information is invalid, this function will throw exception
   *          @link foxit::e_ErrFormat @endlink.
   *
   * @return Page range.
   */
  common::Range GetPrintRange() const;

  /**
   * @brief Set the page range which is used to initialize the print dialog
   *        when the print dialog is opened for the PDF document.
   *
   * @param[in] page_range   A range object that represents the new page range information. It should contain at least
   *                         one valid range segment. All the indexes specified by this range should be
   *                         from 0 to (<i>pagecount</i> - 1). <i>pagecount</i> is returned by function
   *                         @link PDFDoc::GetPageCount @endlink.
   *
   * @return None.
   */
  void SetPrintRange(const common::Range& page_range);

  /**
   * @brief Get PDF dictionary from current object.
   *
   * @return The PDF dictionary.
   */
  objects::PDFDictionary* GetDict() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit DocViewerPrefs(FS_HANDLE handle =  NULL);
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PDFDOCVIEWERPREFS_H_

