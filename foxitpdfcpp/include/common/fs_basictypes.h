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
 * @file fs_basictypes.h
 * @brief Header file for basic types definitions.
 */

#ifndef FS_BASIC_TYPES_H_
#define FS_BASIC_TYPES_H_

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <exception>
#include <cmath>
#include <cfloat>
#include <stdlib.h>
#include <string.h>

#include "common/fxcrt/fx_basic.h"
#include "common/fxcrt/fx_coordinates.h"
#include "common/fxcrt/fx_process.h"

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif  // defined(_WIN32) || defined(_WIN64)

#define FSDK_DEFINE_ARRAY(ArrayName, Type) \
class ArrayName : public Object { \
 public: \
  /** @brief Constructor. */\
  ArrayName(); \
  /** @brief Destructor. */\
  ~ArrayName(); \
  /**
   @brief Constructor, with another array object.
   @param[in] other  Another array object.
   */\
  ArrayName(const ArrayName& other); \
  /**
   @brief Assign operator.
   @param[in] other  Another array object, whose value will be assigned to current object.
   @return Reference to current object itself.
   */\
  ArrayName& operator = (const ArrayName& other); \
  /**
   @brief Get the size of elements in current array.
   @return The size.
   */\
  size_t GetSize() const; \
  /**
  @brief Retrieve a copy of the element at position specified by index in current array.
  @param[in] index  An index to specify which element is to be retrieved.
  @return A copy of an element.
  */\
  Type GetAt(size_t index) const; \
  /**
   @brief Retrieve a reference to the element at position specified by index in current array.
   @param[in] index  An index to specify which element is to be retrieved.
   @return Reference to an element.
   */\
  Type& operator[](size_t index) const; \
  /**
   @brief Add an element to the end of current array.
   @param[in] element  New element to be added to current array.
   @return None.
   */\
  void Add(const Type& element); \
  /**
   @brief Remove the element in position specified by index.
   @param[in] index  An index to specify which element is to be removed. Valid range: from 0 to (<i>size</i>-1).
   <i>size</i> is the size of elements in current array.
   @return None.
   */\
  void RemoveAt(size_t index); \
  /**
   @brief Insert an element before the position specified by index.
   @param[in] index    An index to specify where to insert the new element. Valid range: from 0 to (<i>size</i>-1).
   <i>size</i> is the size of elements in current array.
   @param[in] element  New element to be inserted to current array.
   @return None.
   */\
  void InsertAt(size_t index, const Type& element); \
  /**
   @brief Remove all the element from current array.
   @return None.
   */\
  void RemoveAll(); \
     \
 private: \
  void* data_; \
};

namespace std {
class exception;
}

/**
 * @brief Convert wide string to UTF-8 encoding byte string.
 *
 * @param[in] wstr  Wide string.
 *
 * @return A UTF-8 encoding byte string.
 */
inline CFX_ByteString FX_UTF8Encode(const wchar_t* wstr) {
  return ::FX_UTF8Encode((FX_LPCWSTR) wstr, (FX_STRSIZE)FXSYS_wcslen(wstr));
}

/**
 * @brief Check if two byte strings are equal.
 *
 * @param[in] str1  A byte string.
 * @param[in] str2  A CFX_ByteString object.
 *
 * @return <b>true</b> means equal, while <b>false</b> means not equal.
 */
inline bool operator==(const char* str1, const CFX_ByteString& str2) {
  return str2.Equal(str1);
}

/**
 * @brief Check if two byte strings are not equal.
 *
 * @param[in] str1  A byte string.
 * @param[in] str2  A CFX_ByteString object.
 *
 * @return <b>true</b> means not equal, while <b>false</b> means equal.
 */
inline bool operator!=(const char* str1, const CFX_ByteString& str2) {
  return !str2.Equal(str1);
}

/**
 * @brief Output byte string to std::osstream.
 *
 * @param[in] os   A std::osstream object.
 * @param[in] str  A CFX_ByteString object.
 *
 * @return A reference to the input std::osstream.
 */
inline std::ostream& operator<<(std::ostream& os, const CFX_ByteString& str) {
  return os << (const char*) str;
}

/**
 * @brief Output wide string to std::wostream.
 *
 * @param[in] os   A std::wostream object.
 * @param[in] str  A CFX_WideString object.
 *
 * @return A reference to the input std::wostream.
 */
inline std::wostream& operator<<(std::wostream& os, const CFX_WideString& str) {
  return os << (const wchar_t*) str;
}

#if !defined(_SWIG_ANDROID_) && !defined(_SWIG_IOS_) && !defined(_SWIG_JAVA_)
#ifndef TRUE
/** @brief Keyword used as value of type boolean. Value equals to 1. */
#define TRUE true
#endif

#ifndef FALSE
/** @brief Keyword used as value of type boolean. Value equals to 0. */
#define FALSE false
#endif

#ifndef NULL
/** @brief Keyword used as null-pointer value. */
#define NULL ((void*)0)
#endif
#endif

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/** @brief Signed 64-bit integer. */
typedef FX_INT64        int64;
/** @brief Unsigned 64-bit integer. */
typedef FX_UINT64       uint64;
/** @brief 32-bit signed integer. */
typedef FX_INT32        int32;
/** @brief 32-bit unsigned integer. */
typedef FX_UINT32       uint32;
/** @brief 16-bit signed integer. */
typedef FX_INT16        int16;
/** @brief 16-bit unsigned integer. */
typedef FX_UINT16       uint16;
/** @brief 8-bit signed integer. */
typedef FX_INT8         int8;
/** @brief 8-bit unsigned integer. */
typedef FX_UINT8        uint8;
/** @brief A value used to denote the position of an element in a collection. */
typedef FX_POSITION     POSITION;
/** @brief File size. Support large file directly*/
typedef FX_FILESIZE     FILESIZE;
/** @brief ARGB color type, 32 bits, ((b) | ((g) << 8) | ((r) << 16)) | ((a) << 24) */
typedef uint32 ARGB;
/** @brief RGB color type, 24 bits, ((b) | ((g) << 8) | ((r) << 16))) */
typedef uint32 RGB;
/** @brief Handle type. */
typedef void* FS_HANDLE;

/** @brief Object type. */
typedef CFX_Object Object;
/** @brief Wide string. */
typedef CFX_WideString WString;
/** @brief Byte string. */
typedef CFX_ByteString String;

/** This class represents an array of WString objects. */
FSDK_DEFINE_ARRAY(WStringArray, WString)
/** This class represents an array of String objects. */
FSDK_DEFINE_ARRAY(StringArray, String)

#if !defined(_SWIG_ANDROID_) && !defined(_SWIG_JAVA_)
/**
 * @brief Enumeration for error code.
 *
 * @details Values of this enumeration should be used alone.
 */
typedef enum _ErrorCode {
  /** @brief Success, and no error occurs. */
  e_ErrSuccess = 0,
  /** @brief File cannot be found or could not be opened. */
  e_ErrFile = 1,
  /** @brief Format is invalid. For files, this may also mean that file is corrupted. */
  e_ErrFormat = 2,
  /**
 @brief Invalid password. Usually, this error may occur when loading a PDF document with password.
        When meet this, user should load document again with correct password.
   */
  e_ErrPassword = 3,
  /** @brief Error handle. */
  e_ErrHandle = 4,
  /**
 @brief Certificate error: PDF document is encrypted by digital certificate 
        but current user does not have the correct certificate.
   */
  e_ErrCertificate = 5,
  /** @brief Any unknown error occurs. */
  e_ErrUnknown = 6,
  /** @brief Invalid license is used to initialize Foxit PDF SDK library. */
  e_ErrInvalidLicense = 7,
  /** @brief Parameter error: value of any input parameter for a function is invalid.*/
  e_ErrParam = 8,
  /** @brief Some types are not supported.*/
  e_ErrUnsupported = 9,
  /** @brief Out-of-memory error occurs.*/
  e_ErrOutOfMemory = 10,
  /** @brief PDF document is encrypted by some unsupported security handler. */
  e_ErrSecurityHandler = 11,
  /** @brief Content has not been parsed yet. Usually, this represents PDF page has not been parsed yet. */
  e_ErrNotParsed = 12,
  /** @brief Expected data or object is not found. */
  e_ErrNotFound = 13,
  /** @brief The type of input object or current object is invalid. */
  e_ErrInvalidType = 14,
  /** @brief New data conflicts with existed data. */
  e_ErrConflict = 15,
  /** @brief Any unknown state occurs. */
  e_ErrUnknownState = 16,
  /**
 @brief Data is not ready. Usually this is used as an exception error code
        when loading document in asynchronous way.
   */
  e_ErrDataNotReady = 17,
  /** @brief Data of current object is invalid. */
  e_ErrInvalidData = 18,
  /** @brief XFA loading error. */
  e_ErrXFALoadError = 19,
  /** @brief Current object has not been loaded yet.*/
  e_ErrNotLoaded = 20,
  /** @brief Invalid or incorrect state.*/
  e_ErrInvalidState = 21,
  /** @brief (For ConnectedPDF only) The loaded document is not a ConnectedPDF DRM document. */
  e_ErrNotCDRM = 22,
  /** @brief (For ConnectedPDF only) Cannot connect to ConnectedPDF server. */
  e_ErrCanNotConnectToServer = 23,
  /** @brief (For ConnectedPDF only) Input user token is invalid. */
  e_ErrInvalidUserToken = 24,
  /** @brief (For ConnectedPDF only) Current user has no right to open the ConnectedPDF DRM document. */
  e_ErrNoRights = 25,
  /** @brief (For ConnectedPDF only) The rights of Current user has expired. */
  e_ErrRightsExpired = 26,
  /** @brief (For ConnectedPDF only) Current device is limited to open the ConnectedPDF DRM document. */
  e_ErrDeviceLimitation = 27,
  /** @brief (For ConnectedPDF only) Cannot remove the security from ConnectedPDF server. */
  e_ErrCanNotRemoveSecurityFromServer = 28,
  /** @brief (For ConnectedPDF only) Cannot get the ACL from ConnectedPDF server. */
  e_ErrCanNotGetACL = 29,
  /** @brief (For ConnectedPDF only) Cannot set the ACL to ConnectedPDF server. */
  e_ErrCanNotSetACL = 30,
  /** @brief (For ConnectedPDF only) Loaded document is already a ConnectedPDF document. */
  e_ErrIsAlreadyCPDF = 31,
  /** @brief (For ConnectedPDF only) Loaded document is already a ConnectedPDF DRM document. */
  e_ErrIsAlreadyCDRM = 32,
  /** @brief (For ConnectedPDF only) Cannot upload ConnectedPDF document info to ConnectedPDF server. */
  e_ErrCanNotUploadDocInfo = 33,
  /** @brief (For ConnectedPDF only) Cannot upload ConnectedPDF DRM document info to ConnectedPDF server. */
  e_ErrCanNotUploadCDRMInfo = 34,
  /** @brief (For ConnectedPDF only) The input ConnectedPDF DRM wrapper document is invalid. */
  e_ErrInvalidWrapper = 35,
  /** @brief (For ConnectedPDF only) Cannot get client ID from ConnectedPDF server. */
  e_ErrCanNotGetClientID = 36,
  /** @brief (For ConnectedPDF only) Cannot get user token from ConnectedPDF server. */
  e_ErrCanNotGetUserToken = 37,
  /** @brief (For ConnectedPDF only) Input ACL is invalid. */
  e_ErrInvalidACL = 38,
  /** @brief (For ConnectedPDF only) Input client ID is invalid. */
  e_ErrInvalidClientID = 39,
  /** @brief (For OCR only) OCR engine has not been initialized successfully. */
  e_ErrOCREngineNotInit = 40,
  /** @brief (For OCR only) Not enough disk space.*/
  e_ErrDiskFull = 41,
  /** @brief (For OCR only) The trial for OCR module is end.*/
  e_ErrOCRTrialIsEnd = 42,
  /** @brief File or folder path does not exist. */
  e_ErrFilePathNotExist = 43,
  /** @brief (For compliance only) Compliance engine has not been initialized successfully. */
  e_ErrComplianceEngineNotInit = 44,
  /** @brief (For compliance only) Invalid unlock code is used to initialize compliance engine. */
  e_ErrComplianceEngineInvalidUnlockCode = 45,
  /** @brief (For compliance only) Fail to initialize compliance engine. */
  e_ErrComplianceEngineInitFailed = 46,
  /** @brief Time stamp server manager has not been initialized successfully. */
  e_ErrTimeStampServerMgrNotInit = 47,
  /** @brief (For LTV only) LTV verify mode has not been set. */
  e_ErrLTVVerifyModeNotSet = 48,
  /** @brief (For LTV only) Revocation callback for LTV has not been set. */
  e_ErrLTVRevocationCallbackNotSet = 49,
  /** @brief (For LTV only) Fail to switch PDF verion. */
  e_ErrLTVCannotSwitchVersion = 50,
  /** @brief (For LTV only) Fail to check DTS. */
  e_ErrLTVCannotCheckDTS = 51,
  /** @brief (For LTV only) Fail to load DSS. */
  e_ErrLTVCannotLoadDSS = 52,
  /** @brief (For LTV only) Fail to load DTS. */
  e_ErrLTVCannotLoadDTS = 53,
  /** @brief (For signature only) The signature being operated needs to be signed.  */
  e_ErrNeedSigned = 54,
  /**
   * @brief (For compliance only) Compliance resource file(s) cannot be found or opened. Please check
   *        if compliance resource folder and files in this folder are valid.
   */
  e_ErrComplianceResourceFile = 55,
  /** @brief No default server has been set to time stamp server manager yet. */
  e_ErrTimeStampServerMgrNoDefaltServer = 56,
  /** @brief Cannot use current default time stamp server. Please check if default time stamp server can be used. */
  e_ErrDefaultTimeStampServer = 57,
  /** @brief No "ConnectedPDF" module right. */
  e_ErrNoConnectedPDFModuleRight = 58,
  /** @brief No "XFA" module right. */
  e_ErrNoXFAModuleRight = 59,
  /** @brief No "Redaction" module right. */
  e_ErrNoRedactionModuleRight = 60,
  /** @brief No "RMS" module right. */
  e_ErrNoRMSModuleRight = 61,
  /** @brief No "OCR" module right. */
  e_ErrNoOCRModuleRight = 62,
  /** @brief No "Comparison" module right. */
  e_ErrNoComparisonModuleRight = 63,
  /** @brief No "Compliance" module right. */
  e_ErrNoComplianceModuleRight = 64,
  /** @brief No "Optimizer" module right. */
  e_ErrNoOptimizerModuleRight = 65,
  /** @brief No "Conversion" module right. */
  e_ErrNoConversionModuleRight = 66,
  /** @brief (For Office-to-PDF conversion only) Office COM has not been initialized successfully. */
  e_ErrOfficeComNotInit = 67,
  /** @brief (For Office-to-PDF conversion only) No Microsoft Office is installed in current system. */
  e_ErrNoMicroOfficeInstalled = 68,
  /** @brief (For Excel-to-PDF conversion only) Excel document does not have any content so it cannot be converted to PDF file. */
  e_ErrExcelHasNoContent = 69
} ErrorCode;

#endif

/** @brief An array of float values. */
typedef CFX_ArrayTemplate<float> FloatArray;
/** @brief An array of integer values. */
typedef CFX_ArrayTemplate<int32> Int32Array;

/** The base class in Foxit PDF SDK. */
class Base : public Object {
 public:
  /**
   * @brief Get the handle of current object.
   *
   * @return The handle.
   */
  FS_HANDLE Handle() const {
    return handle_;
  }
  virtual ~Base(){}

 protected:
  explicit Base(FS_HANDLE handle = NULL) : handle_(handle) {}
  FS_HANDLE handle_;
};

/** @brief Matrix information, in float. */
typedef CFX_Matrix Matrix;
/** @brief Point information, in float. */
typedef CFX_PointF PointF;
/** @brief Offset information, in float. */
typedef PointF Offset;
/** @brief Rectangle, in float. */
typedef CFX_FloatRect RectF;
/** @brief Rectangle, in integer. */
typedef FX_RECT RectI;
/** @brief An array of RectF objects. */
typedef CFX_ArrayTemplate<RectF> RectFArray;
/** @brief An array of PointF objects. */
typedef CFX_ArrayTemplate<PointF> PointFArray;

/** This class represents date, time and timezone. */
class DateTime : public Object {
 public:
  /**
   * @brief Get UTC time.
   *
   * @return UTC time.
   */
  static DateTime GetUTCTime();
  /**
   * @brief Get local time.
   *
   * @return Local time.
   */
  static DateTime GetLocalTime();

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] year               Year. It should be a four-digit number, such as 2014.
   * @param[in] month              Month. Valid range: from 1 to 12.
   * @param[in] day                Day of month. Valid range: from 1 to 31.
   * @param[in] hour               Hour. Valid range: from 0 to 23.
   * @param[in] minute             Minute. Valid range: from 0 to 59.
   * @param[in] second             Second. Valid range: from 0 to 60. 60 for leap second.
   * @param[in] milliseconds       Millisecond. Valid range: from 0 to 999.
   *                               PDF standard does not support now,
   *                               this can be omitted if it is not applicable.
   * @param[in] utc_hour_offset    Hour of time zone. Valid range: from -12 to 12.
   *                               Positive value for the eastern time zone,
   *                               and negative value for the western time zone.
   * @param[in] utc_minute_offset  Minute of time zone. Valid range: from 0 to 59.
   */
  DateTime(uint16 year, uint16 month, uint16 day,
           uint16 hour, uint16 minute, uint16 second, uint16 milliseconds,
           int16 utc_hour_offset, uint16 utc_minute_offset)
      : year(year)
      , month(month)
      , day(day)
      , hour(hour)
      , minute(minute)
      , second(second)
      , milliseconds(milliseconds)
      , utc_hour_offset(utc_hour_offset)
      , utc_minute_offset(utc_minute_offset) {}

  /** @brief Constructor. */
  DateTime()
      : year(0)
      , month(0)
      , day(0)
      , hour(0)
      , minute(0)
      , second(0)
      , milliseconds(0)
      , utc_hour_offset(0)
      , utc_minute_offset(0) {}
  /**
   * @brief Constructor, with FXCRT_DATETIMEZONE object.
   *
   * @param[in] time  A FXCRT_DATETIMEZONE object.
   */
  explicit DateTime(const FXCRT_DATETIMEZONE& time);
  /**
   * @brief Constructor, with another date and time object.
   *
   * @param[in] dt  Another date and time object.
   */
  DateTime(const DateTime& dt)
      : year(dt.year)
      , month(dt.month)
      , day(dt.day)
      , hour(dt.hour)
      , minute(dt.minute)
      , second(dt.second)
      , milliseconds(dt.milliseconds)
      , utc_hour_offset(dt.utc_hour_offset)
      , utc_minute_offset(dt.utc_minute_offset) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] dt  Another date and time object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  DateTime& operator = (const DateTime& dt) {
    year = dt.year;
    month = dt.month;
    day = dt.day;
    hour = dt.hour;
    minute = dt.minute;
    second = dt.second;
    milliseconds = dt.milliseconds;
    utc_hour_offset = dt.utc_hour_offset;
    utc_minute_offset = dt.utc_minute_offset;
    return *this;
  }
  /** @brief Convert to a FXCRT_DATETIMEZONE object. */
  operator FXCRT_DATETIMEZONE() const;

#if (defined(_WIN32) || defined(_WIN64)) && !defined(SWIG)
  /**
   * @brief Constructor, with SYSTEMTIME in Windows.
   *
   * @param[in] systime  A SYSTEMTIME object
   */
  explicit DateTime(const SYSTEMTIME& systime)
      : year(systime.wYear)
      , month(systime.wMonth)
      , day(systime.wDay)
      , hour(systime.wHour)
      , minute(systime.wMinute)
      , second(systime.wSecond)
      , milliseconds(systime.wMilliseconds)
      , utc_hour_offset(0)
      , utc_minute_offset(0) {}

  /** @brief Convert to SYSTEMTIME in Windows. */
  operator SYSTEMTIME() const;
#endif  // defined(_WIN32) || defined(_WIN64)

  /**
   * @brief Set value.
   *
   * @param[in] year               Year. It should be a four-digit number, such as 2014.
   * @param[in] month              Month. Valid range: from 1 to 12.
   * @param[in] day                Day of month. Valid range: from 1 to 31.
   * @param[in] hour               Hour. Valid range: from 0 to 23.
   * @param[in] minute             Minute. Valid range: from 0 to 59.
   * @param[in] second             Second. Valid range: from 0 to 60. 60 for leap second.
   * @param[in] milliseconds       Millisecond. Valid range: from 0 to 999.
   *                               PDF standard does not support now,
   *                               this can be omitted if it is not applicable.
   * @param[in] utc_hour_offset    Hour of time zone. Valid range: from -12 to 12.
   *                               Positive value for the eastern time zone,
   *                               and negative value for the western time zone.
   * @param[in] utc_minute_offset  Minute of time zone. Valid range: from 0 to 59.
   *
   * @return None.
   */
  void Set(uint16 year, uint16 month, uint16 day,
           uint16 hour, uint16 minute, uint16 second, uint16 milliseconds,
           int16 utc_hour_offset, uint16 utc_minute_offset) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
    this->milliseconds = milliseconds;
    this->utc_hour_offset = utc_hour_offset;
    this->utc_minute_offset = utc_minute_offset;
  }

  /**
   * @brief Check whether current object is valid or not.
   *
   * @details When the current object is not valid, that means current object is useless.
   *
   * @return <b>true</b> means current object is valid, while <b>false</b> means not.
   */
  bool IsValid() const;

  /**
   * @brief Equal operator.
   *
   * @param[in] datetime  Another date and time object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const DateTime& datetime) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] datetime  Another date and time object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const DateTime& datetime) const;
  /**
   * @brief Greater operator.
   *
   * @param[in] datetime  Another date and time object. This function will check if current object is greater than this one.
   *
   * @return <b>true</b> means current object is greater, while <b>false</b> means current object is not greater.
   */
  bool operator > (const DateTime& datetime) const;
  /**
   * @brief Greater or equal operator.
   *
   * @param[in] datetime  Another date and time object. This function will check if current object is greater than
   *                      or equal to this one.
   *
   * @return <b>true</b> means current object is greater than or equal to the input one,
   *         while <b>false</b> means current object is smaller than the input one.
   */
  bool operator >= (const DateTime& datetime) const;
  /**
   * @brief Smaller operator.
   *
   * @param[in] datetime  Another date and time object. This function will check if current object is smaller than this one.
   *
   * @return <b>true</b> means current object is smaller, while <b>false</b> means current object is not smaller.
   */
  bool operator < (const DateTime& datetime) const;
  /** @brief Smaller or equal operator. */
  /**
   * @brief Smaller or equal operator.
   *
   * @param[in] datetime  Another date and time object. This function will check if current object is smaller than
   *                      or equal to this one.
   *
   * @return <b>true</b> means current object is smaller than or equal to the input one,
   *         while <b>false</b> means current object is greater than the input one.
   */
  bool operator <= (const DateTime& datetime) const;

  /**
   * @brief Convert current object to local time.
   *
   * @return Refernce to current object itself.
   */
  DateTime& ToLocalTime();

  /**
   * @brief Convert current object to UTC time.
   *
   * @return Refernce to current object itself.
   */
  DateTime& ToUTCTime();

  /** @brief Year. It should be a four-digit number, such as 2014. */
  uint16 year;
  /** @brief Month. Valid range: from 1 to 12. */
  uint16 month;
  /** @brief Day of month. Valid range: from 1 to 31. */
  uint16 day;
  /** @brief Hour. Valid range: from 0 to 23. */
  uint16 hour;
  /** @brief Minute. Valid range: from 0 to 59. */
  uint16 minute;
  /** @brief Second. Valid range: from 0 to 60. 60 for leap second. */
  uint16 second;
  /**
   * @brief Millisecond. Valid range: from 0 to 999. PDF standard does not support now, this can be omitted
   *        if it is not applicable.
   */
  uint16 milliseconds;
  /**
   * @brief Hour of time zone. Valid range: from -12 to 12.
   *
   * @details Positive value for the eastern time zone, and negative value for the western time zone.
   */
  int16 utc_hour_offset;
  /** @brief Minute of time zone. Valid range: from 0 to 59. */
  uint16 utc_minute_offset;
};

//#if !defined(_SWIG_ANDROID_) && !defined(_SWIG_IOS_)
  
/** This class represents the Foxit PDF SDK exception. */
class Exception : public std::exception , public Object {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] file_name      The name of the file, where the exception occurs.
   * @param[in] line_number    The number of line, where the exception occurs.
   * @param[in] function_name  The name of function, where the exception occurs.
   * @param[in] error_code     The error code value, which represents the meaning of current exception.
   *                           Please refer to values starting from @link foxit::e_ErrSuccess @endlink and
   *                           this should be one of these values.
   */
  Exception(const char* file_name, int line_number, const char* function_name, ErrorCode error_code);

  /**
   * @brief Constructor, with another exception object.
   *
   * @param[in] exception  Another exception object.
   */
  Exception(const Exception& exception)
      : error_code_(exception.error_code_)
      , error_message_(exception.error_message_)
      , name_(exception.name_) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] exception  Another exception object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Exception& operator = (const Exception& exception) {
    error_code_ = exception.error_code_;
    error_message_ = exception.error_message_;
    return *this;
  }

  /** @brief Destructor. */
  ~Exception() throw() {}

  /**
   * @brief Get the error code.
   *
   * @return The error code.
   */
  ErrorCode GetErrCode() const {
    return error_code_;
  }

  /**
   * @brief Get the error message string.
   *
   * @return Error message string.
   */
  String GetMessage() const
  {
    return error_message_;
  }

  /**
   * @brief Get the string of error code.
   *
   * @return A string of error code.
   */
  String GetName() const
  { return name_; }

 private:
  ErrorCode error_code_;
  String error_message_;
  String name_;
};
  
#define throw(Exception)
//#endif  // !defined(_SWIG_ANDROID_) && !defined(_SWIG_IOS_)

#if __cpluscplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1700)
#define FS_FINAL final
#else
#define FS_FINAL 
#endif

#if __cpluscplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1600)
#define FS_OVERRIDE override
#else
#define FS_OVERRIDE 
#endif

}  // namespace foxit
#endif
