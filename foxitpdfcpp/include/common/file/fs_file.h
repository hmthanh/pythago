/**
 * Copyright (C) 2003-2020, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software
 * Inc.. It is not allowed to distribute any parts of Foxit PDF SDK to third
 * party or public without permission unless an agreement is signed between
 * Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file fs_file.h
 * @brief Header file for file operation related definitions and functions.
 */

#ifndef FS_COMMON_FILE_FILE_H_
#define FS_COMMON_FILE_FILE_H_

#include "common/fs_basictypes.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/**
 * @brief Common namespace.
 */
namespace common {
/**
 * @brief File namespace.
 */
namespace file {
/**
 * This class represents a callback object to do file reading.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user
 * to do file reading in a customized way.
 */
typedef IFX_FileRead ReaderCallback;

/**
 * This class represents a callback object to do file writing.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user
 * to do file writing in a customized way.
 */
typedef IFX_FileWrite WriterCallback;

/**
 * This class represents a callback object to do file reading and writing.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user
 * to do file reading and writing in a customized way.
 */
typedef IFX_FileStream StreamCallback;

/**
 * This class represents a callback object to do file reading asynchronously.
 * This class is derived from class @link ReaderCallback @endlink. All the pure virtual functions in this class
 * and its base class are used as callback functions and should be implemented by user, in order to
 * asynchronously read file data (especially used for loading document), in a customized way.
 *
 * @see @link ReaderCallback @endlink
 */
class AsyncReaderCallback : public ReaderCallback {
 public:
  /**
   * @brief A callback function used to check whether the specified data section is available or not.
   *
   * @details A data section is available only if all bytes in the section are available.
   *
   * @param[in] offset  The offset in file.
   * @param[in] size    The size of the data section, which is to be checked if available.
   *
   * @return <b>true</b> means the specified data section is available,
   *         while <b>false</b> means the specified data section is not available yet.
   */
  virtual bool IsDataAvail(int64 offset, size_t size) = 0;

  /**
   * @brief A callback function used to add offset and size to specify a data section,
   *        which should be downloaded by application then.
   *
   * @details Foxit PDF SDK would call this callback function to report downloading hints for
   *          the download manager of application.<br>
   *          The position (as offset) and size of the section may not be accurate because part of the section might
   *          already be available. The download manager must manage this to maximize download efficiency.
   *
   * @param[in] offset  The offset of a data section, which is to be hinted.
   * @param[in] size    The size of the data section.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool AddDownloadHint(int64 offset, size_t size) = 0;

#if   !defined (_SWIG_DOTNET_)
 protected:
  ~AsyncReaderCallback() {}
#endif
};
}  // namespace file
}  // namespace common
}  // namespace foxit

#endif
