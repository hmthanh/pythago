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
 * @file fs_readingbookmark.h
 * @brief Header file for reading bookmark related definitions and classes.
 */

#ifndef FS_READINGBOOKMARK_H_
#define FS_READINGBOOKMARK_H_

#include "common/fs_common.h"

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
 * Reading bookmark is not a PDF bookmark, in other words, it is not PDF outlines.
 * It is the bookmark in applicable level. It is stored in the metadata (XML format) of catalog. It allows
 * user to add or remove a reading bookmark according to their reading preferences and navigate one PDF page
 * easily by selecting one reading bookmark.<br>
 * In order to retrieve the reading bookmark, function @link PDFDoc::GetReadingBookmarkCount @endlink could be called to
 * count the reading bookmarks, and function @link PDFDoc::GetReadingBookmark @endlink could be called to
 * get a reading bookmark by index.<br>
 * This class offers several functions to get/set properties of reading bookmarks, such as title,
 * destination page index and creation/modified date time.
 *
 * @see @link PDFDoc @endlink
 */
class ReadingBookmark FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, with another reading bookmark object.
   *
   * @param[in] other  Another reading bookmark object.
   */
  ReadingBookmark(const ReadingBookmark& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another reading bookmark object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ReadingBookmark& operator = (const ReadingBookmark& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another reading bookmark object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const ReadingBookmark& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another reading bookmark object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const ReadingBookmark& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the title.
   *
   * @return Title string. If no title property can be found, this function will return an empty string.
   */
  WString GetTitle() const;

  /**
   * @brief Set the title.
   *
   * @param[in] title  New title string.
   *
   * @return None.
   */
  void SetTitle(const WString& title);

  /**
   * @brief Get the index of the destination page.
   *
   * @return The page index, starting from 0. If no page index property can be found, this function will return -1.
   */
  int GetPageIndex() const;

  /**
   * @brief Set the index of the destination page.
   *
   * @param[in] index  The new destination page index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is the page count of the PDF document to which current reading bookmark belongs.
   *                   The page count can be retrieved by function @link PDFDoc::GetPageCount @endlink.
   *
   * @return None.
   */
  void SetPageIndex(int index);

  /**
   * @brief Get date time information.
   *
   * @param[in] is_creation_date  <b>true</b> means to get creation date time information,
   *                              and <b>false</b> means to get last modified date time information.
   *
   * @return The specified date and time. If no specified date and time property can be found,
   *         this function will return a date and time object with all values 0.
   */
  DateTime GetDateTime(bool is_creation_date) const;

  /**
   * @brief Set date time information.
   *
   * @param[in] date_time         New date time information. All the values of this date obejct should be valid.
   *                              Please refer to comment of class @link foxit::DateTime @endlink for more details.
   * @param[in] is_creation_date  <b>true</b> means to get creation date time information,
   *                              and <b>false</b> means to get last modified date time information.
   *
   * return None.
   */
  void SetDateTime(const DateTime& date_time, bool is_creation_date);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit ReadingBookmark(FS_HANDLE handle =  NULL);
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_READINGBOOKMARK_H_

