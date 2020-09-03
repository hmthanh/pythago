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
 * @file fs_fulltextsearch.h
 * @brief Header file for definitions and classes to search among PDF files in a directory.
 */

#ifndef FS_FULLTEXTSEARCH_H_
#define FS_FULLTEXTSEARCH_H_

#include "common/fs_common.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/**
 * @brief Full text search namespace.
 */
namespace fts {
/**
 * This class represents a callback object to retrieve the searching result during the searching progress by function
 * @link FullTextSearch::SearchOf @endlink.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 *
 * @see @link FullTextSearch @endlink
 */
class SearchCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;
  /**
   * @brief A callback function used to retrieve the searching result.
   *
   * @param[in] file_path               A file path that specifies in which file the matched result is found.
   * @param[in] page_index              A page index that specifies in which page of the file
   *                                    the matched result is found.
   * @param[in] match_result            A string that represents the matched result.
   * @param[in] match_start_text_index  The index of start character in the matched result.
   * @param[in] match_end_text_index    The index of end character in the matched result.
   *
   * @return If non-zero is returned, the search engine will stop searching.
   */
  virtual int RetrieveSearchResult(const wchar_t* file_path, int page_index, const WString& match_result,
                                   int match_start_text_index, int match_end_text_index) = 0;

 protected:
  ~SearchCallback() {}
};

/**
 * This class is used to represent a specified directory, which contains PDF files and user wants to
 * search among these PDF files.
 */
class DocumentsSource FS_FINAL : public Base{
 public:
  /**
   * @brief Constructor, with a directory.
   *
   * @param[in] directory  A path string that represents a directory.
   */
  explicit DocumentsSource(const char* directory);
  /** @brief Destructor. */
  ~DocumentsSource();
  /**
   * @brief Constructor, with another documents source object.
   *
   * @param[in] other  Another documents source object.
   */
  DocumentsSource(const DocumentsSource& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another documents source object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  DocumentsSource& operator = (const DocumentsSource& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another documents source object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const DocumentsSource& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another documents source object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const DocumentsSource& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit DocumentsSource(FS_HANDLE handle =  NULL);

};

/**
 * This class is used to index some PDF files and then search specified text among these indexed PDF files.
 */
class FullTextSearch FS_FINAL : public Base{
 public:
  /**
   * @brief Enumeration for rank mode of full text search.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _RankMode {
    /** @brief No ranking mode is used for searching results. */
    e_RankNone = 0,
    /**
   @brief Rank the searching results according to how the result matches the expected searching patten,
          in ascending order (from less similar to most similar or the same).
     */
    e_RankHitCountASC = 1,
    /**
   @brief Rank the searching results according to how the result matches the expected searching patten,
          in descending order (from the same or most similar to less similar).
     */
    e_RankHitCountDESC = 2
  } RankMode;
  

  /** @brief Constructor. */
  FullTextSearch();
  /** @brief Destructor. */
  ~FullTextSearch();
  /**
   * @brief Constructor, with another full text search object.
   *
   * @param[in] other  Another full text search object.
   */
  FullTextSearch(const FullTextSearch& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another full text search object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  FullTextSearch& operator = (const FullTextSearch& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another full text search object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const FullTextSearch& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another full text search object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const FullTextSearch& other) const;
  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set a file path as sqlite data base which is used for storing the indexed data.
   *
   * @details This function is only useful before updating the index of PDF files for the first time by function
   *          @link FullTextSearch::StartUpdateIndex @endlink or @link FullTextSearch::UpdateIndexWithFilePath @endlink.
   *          Once the updating has been done, this function will be useless.<br>
   *          If this function has never called for current full text search object successfully, the default file
   *          for sqlite data would be named as "fts.db" and located with application file.
   *
   * @param[in] path_of_data_base  A file path to specify a file as sqlite data base. It should not be an empty string.
   *
   * @return None.
   */
  void SetDataBasePath(const char* path_of_data_base);

  /**
   * @brief Start to update the index of PDF files defined in a documents source object.
   *
   * @details It may take a long time to do this updating, so Foxit PDF SDK uses a progressive process to do this.<br>
   *          Only PDF files under the specified directory (including sub-directory) defined in documents source
   *          can be indexed.
   *
   * @param[in] source    A documents source object, which defines a directory to be indexed.
   * @param[in] pause     Pause callback object which decides if the updating process needs to be paused.
   *                      This can be <b>NULL</b> which means not to pause during the updating process.
   *                      If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                      Default value: <b>NULL</b>.
   * @param[in] reupdate  <b>true</b> means to re-update the indexes, and <b>false</b> means not to
   *                      re-update the indexes. Default value: <b>false</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  common::Progressive StartUpdateIndex(const DocumentsSource& source, common::PauseCallback* pause = NULL,
                                       bool reupdate = false);

  /**
   * @brief Update the index result of a specified PDF file.
   *
   * @details This function can be used to update the index result of a single PDF file.
   *
   * @param[in] file_path  An existed PDF file path. It should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool UpdateIndexWithFilePath(const char* file_path);

  /**
   * @brief Search for specified text among the indexed PDF files.
   *
   * @details This function can be used to search among several PDF files, which have been indexed by function
   *          @link FullTextSearch::StartUpdateIndex @endlink or @link FullTextSearch::UpdateIndexWithFilePath @endlink.
   *          The searching result will be returned through callback function
   *          @link SearchCallback::RetrieveSearchResult @endlink, in specified ranking mode.
   *
   * @param[in] match_string  A string to be searched. It should not be an empty string.
   * @param[in] rank_mode     The ranking mode used for searching results. Please refer to values starting from
   *                          @link FullTextSearch::e_RankNone @endlink and this should be one of these values.
   * @param[in] callback      A @link SearchCallback @endlink object. It should not be <b>NULL</b>.
   *                          User should implement it and use it to retrieve the searching results.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SearchOf(const char* match_string, RankMode rank_mode, SearchCallback* callback);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit FullTextSearch(FS_HANDLE handle);
};
}  // namespace fts
};  // namespace foxit

#endif  // FS_FULLTEXTSEARCH_H_

