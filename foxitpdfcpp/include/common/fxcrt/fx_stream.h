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
 * @file fx_stream.h
 * @brief Header file for Streams related definitions and classes.
 */

//<<<+++OPENSOURCE
//<<<+++OPENSOURCE_LICENSE
//<<<+++OPENSOURCE_BEGIN LIC==FOXIT||LIC==GOOGLE

/**
 * @addtogroup FXCRT
 * @{
 */

//<<<+++OPENSOURCE_MUST_BEGIN
#ifndef _FX_STREAM_H_
#define _FX_STREAM_H_

#ifndef _FX_MEMORY_H_
  #include "fx_memory.h"
#endif
//<<<+++OPENSOURCE_MUST_END

//*****************************************************************************
//* Folder access
//*****************************************************************************
#if !defined(_FPDFAPI_MINI_) || (defined(_WIN32) && !defined(_FX_NO_WINDOWS_)) || _FXM_PLATFORM_ == _FXM_PLATFORM_LINUX_ || _FX_OS_ == _FX_ANDROID_ || _FXM_PLATFORM_ == _FXM_PLATFORM_APPLE_
/**
 * @brief Open a folder for reading.
 *
 * @param[in] path  Path name of folder.
 *
 * @return Folder handle. <b>NULL</b> means failure.
 */
void* FX_OpenFolder(FX_LPCSTR path);
/**
 * @brief Open a folder for reading.
 *
 * @param[in] path  Path name of folder.
 *
 * @return Folder handle. <b>NULL</b> means failure.
 */
void* FX_OpenFolder(FX_LPCWSTR path);

/**
 * @brief Read next entry in the folder.
 *
 * @param[in] handle     Folder handle returned by function {@link ::FX_OpenFolder}.
 * @param[out] filename  Receives file name when find a folder item.
 * @param[out] bFolder   Indicates filename is a sub-folder or normal file.
 * @param[in] absPath    Absolute path. Default value: <b>NULL</b>.
 *
 * @return <b>true</b> means success, which <b>false</b> means that reach end of folder.
 */
FX_BOOL FX_GetNextFile(void* handle, CFX_ByteString& filename, FX_BOOL& bFolder, FX_LPCSTR absPath=NULL);
/**
 * @brief Read next entry in the folder.
 *
 * @param[in] handle     Folder handle returned by function {@link ::FX_OpenFolder}.
 * @param[out] filename  Receives file name when find a folder item.
 * @param[out] bFolder   Indicates filename is a sub-folder or normal file.
 * @param[in] absPath    Absolute path. Default value: <b>NULL</b>.
 *
 * @return <b>true</b> means success, which <b>false</b> means that reach end of folder.
 */
FX_BOOL FX_GetNextFile(void* handle, CFX_WideString& filename, FX_BOOL& bFolder, FX_LPCSTR absPath=NULL);

/**
 * @brief Close folder handle.
 *
 * @param[in] handle  folder handle returned by FX_OpenFolder function.
 *
 * @return None.
 */
void FX_CloseFolder(void* handle);

/**
 * @brief Get folder separator for the system. Most likely it's either /' or '\'.
 *
 * @return Folder separator.
 */
FX_WCHAR FX_GetFolderSeparator();

#endif

#if _FX_OS_ != _FX_EMBEDDED_
//<<<+++OPENSOURCE_BEGIN LIC==FOXIT
/**
 * @brief Create new folder.
 *
 * @param[in] path  path name of folder.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL FX_CreateFolder(FX_LPCSTR path);
/**
 * @brief Create new folder.
 *
 * @param[in] path  path name of folder.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL FX_CreateFolder(FX_LPCWSTR path);

/**
 * @brief Check if the path exists, including file path and folder path.
 *
 * @param[in] path  Path name of file or folder.
 *
 * @return <b>true</b> means input path exists, while <b>false</b> means input path does not exist.
 */
FX_BOOL FX_IsFilePathExist(FX_LPCWSTR path);
//<<<+++OPENSOURCE_END
#endif

//*****************************************************************************
//* File access
//*****************************************************************************
/** @brief File accessing handle. */
FX_DEFINEHANDLE(FX_HFILE)

  //<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
  #if _FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN32_MOBILE_ || _FX_OS_ == _FX_WIN64_
    #if defined(_FX_LARGEFILE_SUPPORT_)
      /** @brief Preprocessor for large file support. */
      #define _FX_LARGEFILE_USED_

      /** @brief Support large file directly. */
      #define FX_FILESIZE    FX_INT64
      #define FX_GETBYTEOFFSET32(a)  ((FX_BYTE)((a>>16)>>16))
      #define FX_GETBYTEOFFSET40(a)  ((FX_BYTE)(((a>>16)>>16)>>8))
      #define FX_GETBYTEOFFSET48(a)  ((FX_BYTE)(((a>>16)>>16)>>16))
      #define FX_GETBYTEOFFSET56(a)  ((FX_BYTE)((((a>>16)>>16)>>16)>>8))
    #else
      /** @brief Only support 32-bit file size. */
      #define FX_FILESIZE    FX_INT32
      #define FX_GETBYTEOFFSET32(a)  0
      #define FX_GETBYTEOFFSET40(a)  0
      #define FX_GETBYTEOFFSET48(a)  0
      #define FX_GETBYTEOFFSET56(a)  0
    #endif
	#elif _FX_OS_ == _FX_LINUX_DESKTOP_ || _FX_OS_ == _FX_MACOSX_ || _FX_OS_ == _FX_IOS_ || _FX_OS_ == _FX_ANDROID_ || _FX_OS_==_FX_LINUX_EMBEDDED_
    #if defined(_FX_LARGEFILE_SUPPORT_)
      /** @brief Preprocessor for large file support. */
      #define _FX_LARGEFILE_USED_

      #ifndef _LARGEFILE_SOURCE
        #define _LARGEFILE_SOURCE
      #endif
      #ifndef _LARGEFILE64_SOURCE
        #define _LARGEFILE64_SOURCE
      #endif
    #endif
    #if defined(_FX_LARGEFILE_SUPPORT_)
      #define FX_GETBYTEOFFSET32(a)  ((FX_BYTE)((a>>16)>>16))
      #define FX_GETBYTEOFFSET40(a)  ((FX_BYTE)(((a>>16)>>16)>>8))
      #define FX_GETBYTEOFFSET48(a)  ((FX_BYTE)(((a>>16)>>16)>>16))
      #define FX_GETBYTEOFFSET56(a)  ((FX_BYTE)((((a>>16)>>16)>>16)>>8))
    #else
      #define FX_GETBYTEOFFSET32(a)  0
      #define FX_GETBYTEOFFSET40(a)  0
      #define FX_GETBYTEOFFSET48(a)  0
      #define FX_GETBYTEOFFSET56(a)  0
    #endif
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/stat.h>

    #ifndef O_BINARY
      #define O_BINARY   0
    #endif
    #ifndef O_LARGEFILE
      #define O_LARGEFILE 0
    #endif

    /** @brief Use system-defined file size, 64-bit in Mac. */
    #if defined(_FX_LARGEFILE_SUPPORT_)
      #if _FX_OS_ == _FX_LINUX_DESKTOP_ || _FX_OS_ == _FX_LINUX_EMBEDDED_ || _FX_OS_ == _FX_ANDROID_
        // mac and bsd are always 64 bit. use off_t
        // linux and android uses off64_t
#ifndef _CHROME_PNACL_
        #define _FX_USE_OFF64_T_
#endif
      #endif
    #endif
    #if defined(_FX_USE_OFF64_T_)
      #define FX_FILESIZE    off64_t
		#elif _FX_OS_ == _FX_LINUX_EMBEDDED_
			#define FX_FILESIZE FX_INT32
    #else
      #ifndef _CHROME_PNACL_
        #define FX_FILESIZE    off_t
      #else
        #define FX_FILESIZE    FX_INT32
      #endif
    #endif
  #else //do not support large file.
    /** @brief Only support 32-bit file size. */
    #define FX_FILESIZE    FX_INT32
    #define FX_GETBYTEOFFSET32(a)  0
    #define FX_GETBYTEOFFSET40(a)  0
    #define FX_GETBYTEOFFSET48(a)  0
    #define FX_GETBYTEOFFSET56(a)  0
  #endif
  //<<<+++OPENSOURCE_MUST_END

#define FX_GETBYTEOFFSET24(a)  ((FX_BYTE)(a>>24))
#define FX_GETBYTEOFFSET16(a)  ((FX_BYTE)(a>>16))
#define FX_GETBYTEOFFSET8(a)   ((FX_BYTE)(a>>8))
#define FX_GETBYTEOFFSET0(a)   ((FX_BYTE)(a))

/**
 * @name Macro definitions for File accessing modes
 */
/*@{*/
/** @brief Write mode. To create automatically if the file doesn't exist.*/
#define FX_FILEMODE_Write    0
/** @brief Read-only mode.*/
#define FX_FILEMODE_ReadOnly  1
/** @brief Clear existing contents, and size of file is to be 0. For writing mode only. */
#define FX_FILEMODE_Truncate  2  //
/*@}*/

/**
 * @brief Open file with specified accessing mode.
 *
 * @param[in] fileName    File path name which specifies a file to be opened.
 * @param[in] dwMode      File accessing mode. Please refer to values starting from {@link ::FX_FILEMODE_Write} and
 *                        this should be one of these values.
 * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
 *
 * @return File handler. <b>NULL</b> means failure.
 */
FX_HFILE  FX_File_Open(FX_BSTR fileName, FX_DWORD dwMode, IFX_Allocator* pAllocator = NULL);
/**
 * @brief Open file with specified accessing mode.
 *
 * @param[in] fileName    File path name which specifies a file to be opened.
 * @param[in] dwMode      File accessing mode. Please refer to values starting from {@link ::FX_FILEMODE_Write} and
 *                        this should be one of these values.
 * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
 *
 * @return File handler. <b>NULL</b> means failure.
 */
FX_HFILE  FX_File_Open(FX_WSTR fileName, FX_DWORD dwMode, IFX_Allocator* pAllocator = NULL);
/**
 * @brief Close file.
 *
 * @param[in] hFile       File handler returned by function {@link ::FX_File_Open}.
 * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
 *
 * @return None.
 */
void    FX_File_Close(FX_HFILE hFile, IFX_Allocator* pAllocator = NULL);
//<<<+++OPENSOURCE_END

/**
 * @brief Get file size.
 *
 * @param[in] hFile  File handler returned by function {@link ::FX_File_Open}.
 *
 * @return File size. 0 means file is empty or failure.
 */
FX_FILESIZE  FX_File_GetSize(FX_HFILE hFile);
/**
 * @brief Get the current file accessing position.
 *
 * @param[in] hFile  File handler returned by function {@link ::FX_File_Open}.
 *
 * @return The current file accessing position from the beginning of file. -1 means failure.
 */
FX_FILESIZE  FX_File_GetPosition(FX_HFILE hFile);
/**
 * @brief Set the current file accessing position.
 *
 * @param[in] hFile  File handler returned by function {@link ::FX_File_Open}.
 * @param[in] pos    The new accessing position.
 *
 * @return The current file accessing position from the beginning of file. -1 means failure.
 */
FX_FILESIZE  FX_File_SetPosition(FX_HFILE hFile, FX_FILESIZE pos);
/**
 * @brief Read data from the current file accessing position.
 *
 * @param[in] hFile     File handler returned by function {@link ::FX_File_Open}.
 * @param[out] pBuffer  Buffer to receive data.
 * @param[in] szBuffer  Buffer size, in bytes.
 *
 * @return The size of data read from file. 0 means there is no data or failure.
 */
size_t    FX_File_Read(FX_HFILE hFile, void* pBuffer, size_t szBuffer);
/**
 * @brief Read data from specified position.
 *
 * @param[in] hFile     File handler returned by function {@link ::FX_File_Open}.
 * @param[out] pBuffer  Buffer to receive data.
 * @param[in] szBuffer  Buffer size, in bytes.
 * @param[in] pos       Position from which to read data, from the beginning of file.
 *
 * @return The size of data read from file. 0 means there is no data or failure.
 */
size_t    FX_File_ReadPos(FX_HFILE hFile, void* pBuffer, size_t szBuffer, FX_FILESIZE pos);
/**
 * @brief Write data from the current file accessing position.
 *
 * @param[in] hFile     File handler returned by function {@link ::FX_File_Open}.
 * @param[in] pBuffer   Buffer of data.
 * @param[in] szBuffer  Data size, in bytes.
 *
 * @return The size of data write into file. If return value is less than szBuffer, that means failure.
 */
size_t    FX_File_Write(FX_HFILE hFile, const void* pBuffer, size_t szBuffer);
/**
 * @brief Write data at specified position.
 *
 * @param[in] hFile     File handler returned by function {@link ::FX_File_Open}.
 * @param[in] pBuffer   Buffer of data.
 * @param[in] szBuffer  Data size, in bytes.
 * @param[in] pos       Position from which to write data, from the beginning of file.
 *
 * @return The size of data write into file. If return value is less than szBuffer, that means failure.
 */
size_t    FX_File_WritePos(FX_HFILE hFile, const void* pBuffer, size_t szBuffer, FX_FILESIZE pos);
/**
 * @brief Flush internal buffer if need.
 *
 * @param[in] hFile  File handler returned by function {@link ::FX_File_Open}.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL    FX_File_Flush(FX_HFILE hFile);
/**
 * @brief Truncate file size.
 *
 * @param[in] hFile   File handler returned by function {@link ::FX_File_Open}.
 * @param[in] szFile  New file size.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL    FX_File_Truncate(FX_HFILE hFile, FX_FILESIZE szFile);

/**
 * @brief Determine whether a file exists or not.
 *
 * @param[in] fileName  File path name.
 *
 * @return <b>true</b> means file exists, while <b>false</b> means file does not exist.
 */
FX_BOOL    FX_File_Exist(FX_BSTR fileName);
/**
 * @brief Determine whether a file exists or not.
 *
 * @param[in] fileName  File path name.
 *
 * @return <b>true</b> means file exists, while <b>false</b> means file does not exist.
 */
FX_BOOL    FX_File_Exist(FX_WSTR fileName);
/**
 * @brief Delete file.
 *
 * @param[in] fileName  File path name.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL    FX_File_Delete(FX_BSTR fileName);
/**
 * @brief Delete file.
 *
 * @param[in] fileName  File path name.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL    FX_File_Delete(FX_WSTR fileName);
/**
 * @brief Copy file.
 *
 * @param[in] fileNameSrc  Source file path name.
 * @param[in] fileNameDst  Destination file path name.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL    FX_File_Copy(FX_BSTR fileNameSrc, FX_BSTR fileNameDst);
/**
 * @brief Copy file.
 *
 * @param[in] fileNameSrc  Source file path name.
 * @param[in] fileNameDst  Destination file path name.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL    FX_File_Copy(FX_WSTR fileNameSrc, FX_WSTR fileNameDst);
/**
 * @brief Move file.
 *
 * @param[in] fileNameSrc  Source file path name.
 * @param[in] fileNameDst  Destination file path name.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL    FX_File_Move(FX_BSTR fileNameSrc, FX_BSTR fileNameDst);
/**
 * @brief Move file.
 *
 * @param[in] fileNameSrc  Source file path name.
 * @param[in] fileNameDst  Destination file path name.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
FX_BOOL    FX_File_Move(FX_WSTR fileNameSrc, FX_WSTR fileNameDst);

//*****************************************************************************
//* IFX_StreamWrite/IFX_FileWrite
//*****************************************************************************
/** @brief Stream writing interface. */
class IFX_StreamWrite
{
 public:
  /** @brief Called when to release everything */
  virtual void    Release() = 0;

  /**
   * @brief Write a block data.
   *
   * @param[in] pData  The block data.
   * @param[in] size   The length in bytes of the block data.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual  FX_BOOL    WriteBlock(const void* pData, size_t size) = 0;
  /**
   * @brief Flush stream data.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual FX_BOOL    Flush() { return true; }

 protected:
  virtual ~IFX_StreamWrite() {}
};

/** @brief File writing interface. */
class IFX_FileWrite : public IFX_StreamWrite
{
 public:
  /** @brief Called when to release everything */
  virtual void      Release() = 0;

  /**
   * @brief Get total size of the file
   *
   * @return File size, in bytes. Implementation can return 0 for any error.
   */
  virtual FX_FILESIZE    GetSize() = 0;
  /**
   * @brief Flush internal buffer of the file
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual FX_BOOL      Flush() = 0;
  /**
   * @brief Write a block data.
   *
   * @param[in] pData   The block data.
   * @param[in] offset  Byte offset from beginning of the file
   * @param[in] size    The length in bytes of the block data.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual  FX_BOOL      WriteBlock(const void* pData, FX_FILESIZE offset, size_t size) = 0;
  /**
   * @brief Write a block data to the end.
   *
   * @param[in] pData   The block data.
   * @param[in] size    The length in bytes of the block data.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual  FX_BOOL      WriteBlock(const void* pData, size_t size) {return WriteBlock(pData, GetSize(), size);}

 protected:
  virtual ~IFX_FileWrite() {}
};

/**
 * @brief (Available only for platforms supporting CRT file access (fopen, ...)) Create a CRT based file writing interface.
 *
 * @param[in] filename    File name, using MBCS file name.
 * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
 *
 * @return An instance of IFX_FileWrite interface. Please call function {@link IFX_FileWrite::Release} to
 *         destroy returned object when not use it any more.
 */
IFX_FileWrite* FX_CreateFileWrite(FX_LPCSTR filename, IFX_Allocator* pAllocator = NULL);

/**
 * @brief (Available only for platforms supporting CRT file access (fopen, ...)) Create a CRT based file writing interface.
 *
 * @param[in] filename    File name, using unicode file name.
 * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
 *
 * @return An instance of IFX_FileWrite interface. Please call function {@link IFX_FileWrite::Release} to
 *         destroy returned object when not use it any more.
 */
IFX_FileWrite* FX_CreateFileWrite(FX_LPCWSTR filename, IFX_Allocator* pAllocator = NULL);
//<<<+++OPENSOURCE_END

//*****************************************************************************
//* IFX_FileRead
//*****************************************************************************
/** @brief Stream reading interface. */
class IFX_StreamRead
{
 public:
  /**
   * @brief Called when to release everything.
   *
   * @return None.
   */
  virtual void      Release() = 0;

  /**
   * @brief Determine whether reach the end of stream.
   *
   * @return <b>true</b> means reach the end of stream, and <b>false</b> means not yet.
   */
  virtual FX_BOOL      IsEOF() = 0;
  /**
   * @brief Get the current reading position in stream.
   *
   * @return Current reading position.
   */
  virtual FX_FILESIZE    GetPosition() = 0;
  /**
   * @brief Read data block from sequential stream.
   *
   * @param[in,out] buffer  Buffer to store data.
   * @param[in] size        Total size of buffer, in bytes.
   *
   * @return The length of data stored in buffer. If returns 0, means error or no data.
   */
  virtual size_t      ReadBlock(void* buffer, size_t size) = 0;

  /**
   * @brief Set the current file accessing position.
   *
   * @param[in] pos    The new accessing position.
   *
   * @return The current file accessing position from the beginning of file. Default value:-1, means Unsupport.
   */
  virtual FX_FILESIZE SetPosition(FX_FILESIZE pos) { FXSYS_assert(false && "Unsupport");  return -1; }

 protected:
  virtual ~IFX_StreamRead() {}
};

/** @brief File reading interface. */
class IFX_FileRead : public IFX_StreamRead
{
 public:
  /**
   * @brief Called when to release everything
   *
   * @return None.
   */
  virtual void      Release() = 0;

  /**
   * @brief Get total size of the file.
   *
   * @return File size, in bytes. Implementation can return 0 for any error.
   */
  virtual FX_FILESIZE    GetSize() = 0;
  /**
   * @brief Determine whether reach the end of stream.
   *
   * @return <b>true</b> means reach the end of stream, and <b>false</b> means not yet.
   */
  virtual FX_BOOL      IsEOF() {return false;}
  /**
   * @brief Get the current reading position in stream.
   *
   * @return The current reading position in stream.
   */
  virtual FX_FILESIZE    GetPosition() {return 0;}
  /**
  * @brief Set accessing range.
   *
   * @param[in] offset  
   * @param[in] size    
   *
   * @return <b>true</b> means success, and <b>false</b> means failure.
   */
  virtual FX_BOOL      SetRange(FX_FILESIZE offset, FX_FILESIZE size) {return false;}
  /**
   * @brief Clear accessing range set by function {@link IFX_FileRead::SetRange}.
   *
   * @return None.
   */
  virtual void      ClearRange() {}
  /**
   * @brief Read a data block from the file.
   *
   * @param[in,out] buffer  Pointer to a buffer receiving read data
   * @param[in] offset      Byte offset from beginning of the file
   * @param[in] size        Number of bytes for the block.
   *
   * @return <b>true</b> means success, and <b>false</b> means failure.
   */
  virtual FX_BOOL      ReadBlock(void* buffer, FX_FILESIZE offset, size_t size) = 0;
  /**
   * @brief Read data block from stream.
   *
   * @param[in,out] buffer  Buffer to store data.
   * @param[in] size        Total size of buffer, in bytes.
   *
   * @return The length of data stored in buffer. If returns 0, that means error or no data.
   */
  virtual size_t      ReadBlock(void* buffer, size_t size) {return 0;}

  /**
   * @brief Set the current file accessing position.
   *
   * @param[in] pos    The new accessing position.
   *
   * @return The current file accessing position from the beginning of file. Default value:-1, means Unsupport.
   */
  virtual FX_FILESIZE		SetPosition(FX_FILESIZE pos) { FXSYS_assert(false && "Unsupport");  return -1; }

 protected:
  virtual ~IFX_FileRead() {}
};

/**
 * @brief (Available only for platforms supporting CRT file access) Create a CRT based file reading interface. 
 *
 * @param[in] filename    File name, using MBCS file name. 
 * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
 *
 * @return An instance of IFX_FileRead interface. Please call function {@link IFX_FileRead::Release} to
 *         destroy the returned object when not use it any more.
 */
IFX_FileRead* FX_CreateFileRead(FX_LPCSTR filename, IFX_Allocator* pAllocator = NULL);

/**
 * @brief (Available only for platforms supporting CRT file access) Create a CRT based file reading interface.
  *
  * @param[in] filename    File name, using Unicode file name. 
  * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
  *
  * @return An instance of IFX_FileRead interface. Please call function {@link IFX_FileRead::Release} to
  *         destroy the returned object when not use it any more.
 */
IFX_FileRead* FX_CreateFileRead(FX_LPCWSTR filename, IFX_Allocator* pAllocator = NULL);
//<<<+++OPENSOURCE_END

//*****************************************************************************
//* IFX_FileStream
//*****************************************************************************
/** @brief File stream interface, reading & writing. */
class IFX_FileStream 
: public IFX_FileRead, public IFX_FileWrite
{
 public:
  /**
   * @brief Create a shared instance. 
   *
   * @return File stream interface.
   */
  virtual IFX_FileStream*    Retain() = 0;
  /**
   * @brief Destroy the current instance. 
   *
   * @return None.
   */
  virtual void        Release() = 0;

  /**
   * @brief Get the current stream size, in bytes.
   *
   * @return Current stream size, in bytes.
   */
  virtual FX_FILESIZE      GetSize() = 0;
  /**
   * @brief Determine whether reach the end of stream.
   *
   * @return <b>true</b> means reach the end of stream, and <b>false</b> means not yet.
   */
  virtual FX_BOOL        IsEOF() = 0;
  /**
   * @brief Get the current reading position in stream.
   *
   * @return Current reading position.
   */
  virtual FX_FILESIZE      GetPosition() = 0;

  /**
   * @brief Read a data block from stream.
   *
   * @param[in,out] buffer  Pointer to a buffer receiving data.
   * @param[in] offset      Byte offset from beginning of the file, the position to read data.
   * @param[in] size        Number of bytes to be read from stream.
   *
   * @return <b>true</b> means success, and <b>false</b> means failure.
   */
  virtual FX_BOOL        ReadBlock(void* buffer, FX_FILESIZE offset, size_t size) = 0;
  /**
   * @brief Read data block from stream.
   *
   * @param[in,out] buffer  Buffer to store data.
   * @param[in] size        Total size of buffer, in bytes.
   *
   * @return The length of data stored in buffer. If returns 0, means error or no data.
   */
  virtual size_t        ReadBlock(void* buffer, size_t size) = 0;

  /**
   * @brief Write a block data into stream.
   *
   * @param[in] buffer  Pointer to the data block.
   * @param[in] offset  Byte offset from beginning of the file, the position to write data.
   * @param[in] size    The length in bytes of the buffer.
   *
   * @return <b>true</b> means success, and <b>false</b> means failure.
   */
  virtual  FX_BOOL        WriteBlock(const void* buffer, FX_FILESIZE offset, size_t size) = 0;
  /**
   * @brief Write a block data to the end of current stream.
   *
   * @param[in] buffer  Pointer to the data block.
   * @param[in] size    The length in bytes of the buffer.
   *
   * @return <b>true</b> means success, and <b>false</b> means failure.
   */
  virtual  FX_BOOL        WriteBlock(const void* buffer, size_t size) {return WriteBlock(buffer, GetSize(), size);}

  /**
   * @brief Flush internal buffer.
   *
   * @return <b>true</b> means success, and <b>false</b> means failure.
   */
  virtual FX_BOOL        Flush() = 0;

 protected:
  virtual ~IFX_FileStream() {}
};

/**
 * @brief (Available only for platforms supporting CRT file access) Create a CRT based file I/O interface.
 *
 * @param filename    File name, using MBCS file name.
 * @param dwModes
 * @param pAllocator  An allocator. Default value: <b>NULL</b>.
 *
 * @return An instance of IFX_FileStream interface. <b>NULL</b> means failure.
 *         Please call function {@link IFX_FileStream::Release} to destroy returned object when not use it any more.
 */
IFX_FileStream*    FX_CreateFileStream(FX_LPCSTR filename, FX_DWORD dwModes, IFX_Allocator* pAllocator = NULL);

/**
 * @brief (Available only for platforms supporting CRT file access) Create a CRT based file I/O interface.
 *
 * @param filename    File name, using Unicode file name.
 * @param dwModes
 * @param pAllocator  An allocator. Default value: <b>NULL</b>.
 *
 * @return An instance of IFX_FileStream interface. <b>NULL</b> means failure.
 *         Please call function {@link IFX_FileStream::Release} to destroy returned object when not use it any more.
 */
IFX_FileStream*    FX_CreateFileStream(FX_LPCWSTR filename, FX_DWORD dwModes, IFX_Allocator* pAllocator = NULL);
//<<<+++OPENSOURCE_END

//*****************************************************************************
//* IFX_FileAccess
//*****************************************************************************
/** @brief File access interface, open file. */
class IFX_FileAccess
{
 public:
  /**
   * @brief Destroy the current instance.
   *
   * @return None.
   */
  virtual void        Release() = 0;

  /**
   * @brief Create a shared instance.
   *
   * @return A shared instance of current object.
   */
  virtual IFX_FileAccess*    Retain() = 0;
  /**
   * @brief Get current path string.
   *
   * @param[out] wsPath  Receive current file path.
   *
   * @return None.
   */
  virtual void        GetPath(CFX_WideString& wsPath) = 0;

  /**
   * @brief Create IFX_FileStream to operate file.
   *
   * @param[in] dwModes  Open file mode.
   *
   * @return A new IFX_FileStream object.
   */
  virtual IFX_FileStream*    CreateFileStream(FX_DWORD dwModes) = 0;

 protected:
  virtual ~IFX_FileAccess() {}
};

/**
 * @brief Create a CRT based file I/O interface. 
 *
 * @param[in] wsPath      File path.
 * @param[in] pAllocator  An allocator. Default value: <b>NULL</b>.
 *
 * @return An instance of IFX_FileAccess interface. <b>NULL</b> means failure.
 *         Please call function {@link IFX_FileAccess::Release} to destroy the returned object when not use it any more.
 */
IFX_FileAccess*    FX_CreateDefaultFileAccess(FX_WSTR  wsPath, IFX_Allocator* pAllocator = NULL);

class IFX_FileCollection
{
 public:
  virtual void        Release() = 0;

  virtual FX_POSITION      GetStartPos() = 0;
  virtual IFX_FileAccess*    GetNextFile(FX_POSITION& pos) = 0;

 protected:
  virtual ~IFX_FileCollection() {}
};
//<<<+++OPENSOURCE_END

//*****************************************************************************
//* Memory stream
//*****************************************************************************
/** @brief Memory stream interface. */
class IFX_MemoryStream : public IFX_FileStream
{
 public:
  virtual ~IFX_MemoryStream() {}

  /**
   * @brief Determine whether the current mode is consecutive or not.
   *
   * @return <b>true</b> means current mode is consecutive, while <b>false</b> means current mode is non-consecutive.
   */
  virtual FX_BOOL      IsConsecutive() const = 0;
  /**
   * @brief Change initialize size and grow size.
   *
   * @param[in] nInitSize  Initial size for memory block.
   * @param[in] nGrowSize  Grow up size for next change when write data.
   *
   * @return None.
   *
   * @note For consecutive mode, if parameter <i>nInitSize</i> is greater than the current size,
   *         block memory will be reallocated; parameter <i>nGrowSize</i> will be used when reallocate memory next time.
   *         For non-consecutive mode, parameter <i>nGrowSize</i> will be used to allocate each memory block,
   *         this method should be called at first; parameter <i>nInitSize</i> will be ignored.
   */
  virtual void      EstimateSize(size_t nInitSize, size_t nGrowSize) = 0;
  /**
   * @brief Get the current memory buffer.
   *
   * @return The current memory buffer.
   *
   * @note If the current memory stream works under non-consecutive mode(there are more than one memory blocks),
   *         only the first block returns.
   */
  virtual FX_LPBYTE    GetBuffer() const = 0;
  /**
   * @brief Attach a memory buffer.
   *
   * @param[in] pBuffer    Memory buffer to attach.
   * @param[in] nSize      Buffer size, in bytes.
   * @param[in] bTakeOver  Indicates whether need free attached memory buffer(pBuffer) when memory stream is to be released.
   *                       Default value: <b>false</b>
   *
   * @return None.
   *
   * @note This method will let memory stream works under consecutive mode, that's only one block exists,
   *         it will be expanded when writes data into it if necessary. If memory stream works under non-consecutive mode,
   *         this method makes no sense.
   */
  virtual void      AttachBuffer(FX_LPBYTE pBuffer, size_t nSize, FX_BOOL bTakeOver = false) = 0;
  /**
   * @brief Detach the current memory buffer.
   *
   * @return None.
   *
   * @note If memory stream works under non-consecutive mode, this method makes no sense.
   */
  virtual void      DetachBuffer() = 0;
};
/**
 * @brief Creates a stream object by a given memory buffer. This function creates a consecutive memory stream object.
 *
 * @param[in] pBuffer     A memory buffer to read/write data.
 * @param[in] nSize       Buffer size, in bytes.
 * @param[in] bTakeOver   Indicates whether need to take over parameter <i>pBuffer</i>. If this is <b>true</b>,
 *                        parameter <i>pBuffer</i> will release internally when destroy returned IFX_MemoryStream object.
 *                        Default value: <b>false</b>.
 * @param[in] pAllocator  Pointer to ::IFX_Allocator object, this specifies an allocator. If this is <b>NULL</b>,
 *                        default allocator is used. Default value: <b>NULL</b>.
 *
 * @return An instance of IFX_MemoryStream interface. <b>NULL</b> means failure.
 */
IFX_MemoryStream*  FX_CreateMemoryStream(FX_LPBYTE pBuffer, size_t nSize, FX_BOOL bTakeOver = false, IFX_Allocator* pAllocator = NULL);

/**
 * @brief Create a memory stream object. Memory buffer will be created internally, and the size will increase when need more space.
 *
 * @param[in] bConsecutive  Indicates whether to create a consecutive memory stream.
 *                          <b>true</b> means to create a consecutive memory stream, while <b>false</b> means to
 *                          create a non-consecutive stream. Default value: <b>false</b>.
 * @param[in] pAllocator    Pointer to ::IFX_Allocator object which specifies an allocator.
 *                          <b>NULL</b> means to use default allocator. Default value: <b>NULL</b>.
 *
 * @return An instance of IFX_MemoryStream interface. <b>NULL</b> means failure.
 */
IFX_MemoryStream*  FX_CreateMemoryStream(FX_BOOL bConsecutive = false, IFX_Allocator* pAllocator = NULL);
//<<<+++OPENSOURCE_END

//*****************************************************************************
//* Buffer read stream
//*****************************************************************************
/**
 * @brief IFX_BufferRead stream provides an optimized approach to read stream data.
 *        Usually, one stream maintains an internal buffer for data access, this buffer can be used directly to caller,
 *        and avoids data-copy.
 */
class IFX_BufferRead : public IFX_StreamRead
{
 public:
  /**
   * @brief Called when to release the current instance.
   *
   * @return None.
   */
  virtual void      Release() = 0;

  /**
   * @brief Determine whether reach the end of stream.
   *
   * @return <b>true</b> means reach the end of stream, and <b>false</b> means not yet.
   */
  virtual FX_BOOL      IsEOF() = 0;
  /**
   * @brief Get the current reading position in stream.
   *
   * @return Current reading position in stream.
   */
  virtual FX_FILESIZE    GetPosition() = 0;

  /**
   * @brief Read data block from sequential stream.
   *
   * @param[in,out] buffer  buffer to store data.
   * @param[in] size      total size of buffer, in bytes.
   *
   * @return The length of data stored in buffer. 0 means error or no data.
   */
  virtual size_t      ReadBlock(void* buffer, size_t size) = 0;

  /**
   * @brief Read the next block in sequential stream.
   *
   * @param[in] bRestart  Indicates to read data from the beginning of stream. Default value: <b>false</b>.
   *
   * @return <b>true</b> means success, and <b>false</b> means failure.
   */
  virtual FX_BOOL      ReadNextBlock(FX_BOOL bRestart = false) = 0;
  /**
   * @brief Get internal buffer of block data.
   *
   * @return The internal buffer.
   */
  virtual FX_LPCBYTE    GetBlockBuffer() = 0;
  /**
   * @brief Get the size of data in internal buffer.
   *
   * @return Size of data in internal buffer.
   */
  virtual size_t      GetBlockSize() = 0;
  /**
   * @brief Get the offset of data in internal buffer.
   *
   * @details This offset starts from the beginning of stream.
   *
   * @return The offset of data in internal buffer.
   */
  virtual FX_FILESIZE    GetBlockOffset() = 0;

 protected:
  virtual ~IFX_BufferRead() {}
};

//*****************************************************************************
//* Cached file read
//*****************************************************************************
#define FX_FILECACHE_CHUNKSIZE  32768
#define FX_FILECACHE_CHUNKCOUNT  64

/** @brief Cached file read interface. */
class CFX_CachedFileRead : public IFX_FileStream, public CFX_Object
{
 public:
  /** @brief Constructor. */
  CFX_CachedFileRead();
  /** @brief Destructor.  */
  virtual  ~CFX_CachedFileRead();

  /**
   * @brief Initialize the chunk size and chunk count.
   *
   * @param[in] nChunkSize   The size of each chunk.
   * @param[in] nChunkCount  The total count of chunks.
   * @param[in] pBuffer      External buffer. <b>NULL</b> means cache is disabled.
   * @param[in] pAllocator   Allocator used in this class. <b>NULL</b> means to use default allocator.
   *                         Default value: <b>NULL</b>.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL      Init(FX_INT32 nChunkSize, FX_INT32 nChunkCount, FX_LPVOID pBuffer, IFX_Allocator* pAllocator = NULL);
  /**
   * @brief Attach a file read.
   *
   * @param[in] pFile      The file to be attached.
   * @param[in] bTakeOver  Take over the file or not.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL      AttachFile(IFX_FileRead* pFile, FX_BOOL bTakeOver);
  /**
   * @brief Attach a file read.
   *
   * @param[in] offset       The file to be attached.
   * @param[in] nCacheCount  Take over the file or not.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  FX_BOOL      PreCache(FX_FILESIZE offset, FX_INT32 nCacheCount);

  /**
   * @brief Get total size of the file
   *
   * @return File size, in bytes. Implementation can return 0 for any error.
   */
  virtual FX_FILESIZE    GetSize();
  /**
   * @brief Determine whether reach the end of stream.
   *
   * @return <b>true</b> means reach the end of stream, and <b>false</b> means not yet.
   */
  virtual FX_BOOL      IsEOF();
  /**
   * @brief Get the current reading position in stream.
   *
   * @return The current reading position in stream.
   */
  virtual FX_FILESIZE    GetPosition();

  /**
   * @brief Read a data block from the file
   *
   * @param[in,out] buffer  Pointer to a buffer receiving read data
   * @param[in] offset      Byte offset from beginning of the file
   * @param[in] size        Number of bytes for the block.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual FX_BOOL      ReadBlock(void* buffer, FX_FILESIZE offset, size_t size);
  /**
   * @brief Read data block from stream.
   *
   * @param[in,out] buffer  Buffer to store data.
   * @param[in] size        Total size of buffer, in bytes.
   *
   * @return The length of data stored in buffer. 0 means error or no data.
   */
  virtual size_t      ReadBlock(void* buffer, size_t size);

 protected:
  FXMT_LOCKOBJECT_DEFINE(m_LockObj);
  FX_LPVOID        m_pData;
  FX_DWORD        m_dwCount;

  /* @brief Create a shared instance. */
  virtual IFX_FileStream*  Retain();
  /* @brief Called when to release everything */
  virtual void      Release();
  /** @brief  Write a block data into stream. Unsupported for reading mode, return false directly. */
  virtual  FX_BOOL      WriteBlock(const void* buffer, FX_FILESIZE offset, size_t size) {return false;}
  /** @brief  Flush internal buffer. Unsupported for reading mode, return false directly. */
  virtual FX_BOOL      Flush() {return false;}
};
//<<<+++OPENSOURCE_END

//<<<+++OPENSOURCE_MUST_BEGIN
#endif // _FX_STREAM_H_
//<<<+++OPENSOURCE_MUST_END

/** @} */

//<<<+++OPENSOURCE_END
