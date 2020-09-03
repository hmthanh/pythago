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
 * @file fx_system.h
 * @brief Header file for system related definitions.
 */
//<<<+++OPENSOURCE
//<<<+++OPENSOURCE_LICENSE
//<<<+++OPENSOURCE_BEGIN LIC==FOXIT||LIC==GOOGLE

/**
 * @addtogroup FXCRT
 * @{
 */

/*
 * @brief System dependant service routines.
 * All system-specific function and non-standard C/C++ routines go here
 *
 * FPDFAPI PREDEFINED MACROES
 *
 * FPDFAPI makes use of a number of predefined macroes to support all kind of platforms
 * with a single set of codes. In most of times, application developers can ignore those
 * macroes because they are properly defined according to system or compiler environment
 * settings. However, sometimes, especially for cross platform development, FPDFAPI might
 * take incorrect settings of the host platform, rather then the target platform. In such
 * case, the application developers should manually set necessary macroes in their project
 * settings.
 *
 *
 * Currently the following macroes are defined:
 * - #_FX_OS_        The target operating system
 * - #_FX_COMPILER_      The compiler
 * - #_FX_CPU_        The CPU
 * - #_FX_ENDIAN_      Little endian or big endian
 *
 * #_FX_OS_ can be one of the followings:
 * - #_FX_WIN32_DESKTOP_  Windows desktop OS (from Windows 95)
 * - #_FX_WIN32_MOBILE_    Windows Mobile OS (from Windows CE 4.0)
 * - #_FX_WIN64_      Windows 64 bit
 * - #_FX_LINUX_DESKTOP_  Linux Desktop OS
 * - #_FX_LINUX_EMBEDDED_  Embedded Linux OS
 * - #_FX_SYMBIAN_      Symbian OS (from 7.0)
 * - #_FX_MACOSX_      MAC OS X
 * - #_FX_EMBEDDED_      Embedded OS
 * - #_FX_SOLARIS_      Solaris 8 or later
 * - #_FX_PALMOS_      PalmOS (5.0 or later)
 * - #_FX_NETBSD_      NetBSD
 * - #_FX_ANDROID_      Android
 * - #_FX_VXWORKS_      VxWorks
 *
 * #_FX_COMPILER_ can be one of the following:
 * - #_FX_VC6_      Microsoft Visual C++ 6.0
 * - #_FX_VC7_      Microsoft Visual Studio.Net 2003
 * - #_FX_VC8_      Microsoft Visual Studio.Net 2005
 * - #_FX_GCC_      GNU C++ Compiler
 * - #_FX_ADS_      ADS 1.2 Compiler
 * - #_FX_RVCT_      RVCT 2.1 Compiler
 * - #_FX_IARCC_    IAR C/C++ Compiler
 * - #_FX_NOKIA_X86_  Nokia X86 Compiler
 * - #_FX_METROWERKS_  Metrowerks C/C++ Compiler (with MSL)
 * - #_FX_PACC_      Protein C/C++ Compiler (used by PalmOS)
 * - #_FX_MIPS_SDE_    MIPS SDE
 *
 * #_FX_CPU_ can be one of the following:
 * - #_FX_X86_      32-bit x86 CPU
 * - #_FX_X64_      64-bit x86 CPU
 * - #_FX_POWERPC_    Power PC
 * - #_FX_ARM_      ARM
 * - #_FX_SPARC_    Sparc
 * - #_FX_MIPS_      MIPS
 * - #_FX_ARM64_        64-bit ARM
 *
 * #_FX_ENDIAN_ can be one of the following:
 * - #_FX_BIG_ENDIAN_
 * - #_FX_LITTLE_ENDIAN_
 *
 * #_FX_WORDSIZE_ can be one of the following:
 * - #_FX_W32_      32-bit instruct
 * - #_FX_W64_      64-bit instruct
 */

//<<<+++OPENSOURCE_MUST_BEGIN
#ifndef _FX_SYSTEM_H_
#define _FX_SYSTEM_H_
//<<<+++OPENSOURCE_MUST_END

#ifdef _WIN32_WCE
    #ifndef _SIZE_T_DEFINED
    #define _SIZE_T_DEFINED
    #endif  //_SIZE_T_DEFINED
#endif

/**
 * @name OS Defines
 */
/*@{*/

/** @brief Windows desktop OS (from Windows 95) */
#define _FX_WIN32_DESKTOP_    1
  //<<<+++OPENSOURCE_BEGIN LIC==FOXIT
  /** @brief Windows Mobile OS (from Windows CE 4.0) */
  #define _FX_WIN32_MOBILE_    2
  /** @brief Windows 64 bit */
  #define _FX_WIN64_        3
  //<<<+++OPENSOURCE_END

/** @brief Linux Desktop OS */
#define _FX_LINUX_DESKTOP_    4

  /** @brief Embedded Linux OS */
  #define _FX_LINUX_EMBEDDED_    5
  /** @brief Symbian OS (from 7.0) */
  #define _FX_SYMBIAN_      6

/** @brief MAC OS X */
#define _FX_MACOSX_        7

  /** @brief Embedded OS */
  #define _FX_EMBEDDED_      8
  /** @brief Solaris 8 or later */
  #define _FX_SOLARIS_      9
  /** @brief PalmOS (5.0 or later) */
  #define _FX_PALMOS_        10
  /** @brief NetBSD */
  #define _FX_NETBSD_        11
  //<<<+++OPENSOURCE_END

/** @brief Android */
#define _FX_ANDROID_      12

  /** @brief VxWorks */
  #define _FX_VXWORKS_      13
  /** @brief Media Tech */
  #define _FX_MTK_        14
  /** @brief IOS */
  #define _FX_IOS_                15

/** @brief Windows OS platformas. */
#define _FXM_PLATFORM_WINDOWS_    1
/** @brief Linux OS platformas. */
#define _FXM_PLATFORM_LINUX_    2
/** @brief Apple OS platformas. */
#define _FXM_PLATFORM_APPLE_    3
/** @brief Android OS platformas. */
#define _FXM_PLATFORM_ANDROID_    4

#ifdef __pnacl__
#define _CHROME_PNACL_
#endif

#if defined(_FXM_PLATFORM_LINUX_JS_) || defined(_CHROME_PNACL_)
  #define _FX_OS_ _FX_LINUX_DESKTOP_
  #define _FXM_PLATFORM_ _FXM_PLATFORM_LINUX_
#endif

/* OS */

#ifndef _FX_OS_
  #if   defined(__SYMBIAN32__) || defined(__symbian__)
    #define _FX_OS_ _FX_SYMBIAN_
  #elif defined(_WIN32_WCE)
    #define _FX_OS_ _FX_WIN32_MOBILE_
    #define _FXM_PLATFORM_ _FXM_PLATFORM_WINDOWS_
    #if defined (_WIN32_WCE) && (_WIN32_WCE == 0x600)
      #define UNSUPPORT_CPP0X
    #endif
  #elif defined(__linux__) || defined(__native_client__)
    #if defined(__arm__) && (!defined(OS_CHROMEOS))
      #define _FX_OS_ _FX_LINUX_EMBEDDED_
    #else
      #define _FX_OS_ _FX_LINUX_DESKTOP_
    #endif
    #define _FXM_PLATFORM_ _FXM_PLATFORM_LINUX_
  #elif defined(__NetBSD__)
    #define _FX_OS_ _FX_NETBSD_
  #elif defined(_WIN64)
    #define _FX_OS_ _FX_WIN64_
    #define _FXM_PLATFORM_ _FXM_PLATFORM_WINDOWS_
  #elif defined(_WIN32)
    #define _FX_OS_ _FX_WIN32_DESKTOP_
    #define _FXM_PLATFORM_ _FXM_PLATFORM_WINDOWS_
  #elif defined(__sparc__)
    #define _FX_OS_ _FX_SOLARIS_
    #define _FXM_PLATFORM_ _FXM_PLATFORM_LINUX_
  #elif defined(__ARMCC_VERSION) || defined(__ICCARM__) || defined(__TMS470__)
    #define _FX_OS_ _FX_EMBEDDED_
  #elif defined(__APPLE__)
        #include "TargetConditionals.h"
        #if (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE == 1) || (defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR == 1)
            #define _FX_OS_ _FX_IOS_
        #else
            #define _FX_OS_ _FX_MACOSX_
        #endif
    #define _FXM_PLATFORM_ _FXM_PLATFORM_APPLE_
  #elif defined(__ARM_EABI__)
    #define _FX_OS_ _FX_EMBEDDED_
  #endif
#else
    #if _FX_OS_ == _FX_ANDROID_
        #ifndef _FXM_PLATFORM_
            #define _FXM_PLATFORM_ _FXM_PLATFORM_ANDROID_
        #endif
    #elif (_FX_OS_ == _FX_WIN32_MOBILE_ || _FX_OS_ == _FX_WIN64_ || _FX_OS_ == _FX_WIN32_DESKTOP_)
        #ifndef _FXM_PLATFORM_
            #define _FXM_PLATFORM_ _FXM_PLATFORM_WINDOWS_
        #endif
    #elif (_FX_OS_ == _FX_IOS_ || _FX_OS_ == _FX_MACOSX_)
        #ifndef _FXM_PLATFORM_
            #define _FXM_PLATFORM_ _FXM_PLATFORM_APPLE_
        #endif
    #elif _FX_OS_ == _FX_SOLARIS_ || _FX_OS_ == _FX_LINUX_EMBEDDED_ || _FX_OS_ == _FX_LINUX_DESKTOP_
        #ifndef _FXM_PLATFORM_
            #define _FXM_PLATFORM_ _FXM_PLATFORM_LINUX_
        #endif
    #endif
#endif //_FX_OS_

#if !defined(_FX_OS_) || _FX_OS_ == 0
  #error Sorry, can not figure out what OS you are targeting to. Please specify _FX_OS_ macro.
#endif

//<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
#if (_FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN32_MOBILE_ || _FX_OS_ == _FX_WIN64_) && !defined(_FX_NO_WINDOWS_)
  /** @brief Disable the security enhancements in the CRT */
  #define _CRT_SECURE_NO_WARNINGS
  #if defined(_MSC_VER) && _MSC_VER < 1300
    #define _WIN32_WINNT 0x400
  #endif
  #if defined(_MSC_VER) && _MSC_VER < 1600
  #define UNSUPPORT_CPP0X
  #endif
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
  #include <windows.h>

  #ifdef WINAPI_FAMILY
    #if (0x00000001 == WINAPI_PARTITION_DESKTOP) && (0x00000002 == WINAPI_PARTITION_APP) //Macros in Windows Kit/8
    #define _FX_WIN8_
    #else //Macros in Windows Kit/8.1
    #define _FX_WIN81_
    #endif //(0x00000001 == WINAPI_PARTITION_DESKTOP) && (0x00000002 == WINAPI_PARTITION_APP)

    #ifdef _FX_WIN8_
      #if /*defined(WINAPI_FAMILY) && */((WINAPI_FAMILY&WINAPI_PARTITION_APP) == WINAPI_PARTITION_APP)
      /** @brief For Windows Store App*/
      #define _FX_WINAPI_PARTITION_APP_
      #endif
      #if /*!defined(WINAPI_FAMILY) || */defined(WINAPI_FAMILY) && ((WINAPI_FAMILY&WINAPI_PARTITION_DESKTOP) == WINAPI_PARTITION_DESKTOP)
      /** @brief For Windows Destop App*/
      #define _FX_WINAPI_PARTITION_DESKTOP_
      #endif
    #endif //_FX_WIN8_

    #ifdef _FX_WIN81_

      #if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_PC_APP)
      /** @breif For Windows Store App */
      #define _FX_WINAPI_PARTITION_APP_
      #endif

      #if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_PHONE_APP) && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_PC_APP)
      /** @breif For Windows Phone App */
      #define _FX_WINAPI_PARTITION_PHONE_APP_
      #endif

      #if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
      /** @breif For Windows Desktop App */
      #define _FX_WINAPI_PARTITION_DESKTOP_
      #endif
    #endif //_FX_WIN81_
  #else // !defined(WINAPI_FAMILY)
  #ifndef _WIN32_WCE
    #define _FX_WINAPI_PARTITION_DESKTOP_
  #endif
  #endif //WINAPI_FAMILY
#endif //(_FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN32_MOBILE_ || _FX_OS_ == _FX_WIN64_) && !defined(_FX_NO_WINDOWS_)
//<<<+++OPENSOURCE_MUST_END

/*@}*/

/**
 * @name Compiler Defines
 */
/*@{*/

/** @brief Microsoft Visual C++ 6.0 */
#define _FX_VC6_    1
/** @brief Microsoft Visual Studio.Net 2003 */
#define _FX_VC7_    2
/** @brief Microsoft Visual Studio.Net 2005 */
#define _FX_VC8_    3
/** @brief GNU C++ Compiler */
#define _FX_GCC_    4
/** @brief ADS 1.2 Compiler */
#define _FX_ADS_    5
/** @brief RVCT 2.1 Compiler */
#define _FX_RVCT_    6
/** @brief IAR C/C++ Compiler */
#define _FX_IARCC_    7
/** @brief Nokia X86 Compiler */
#define _FX_NOKIA_X86_  8
/** @brief Metrowerks C/C++ Compiler (with MSL) */
#define _FX_METROWERKS_  9
/** @brief Protein C/C++ Compiler (used by PalmOS) */
#define _FX_PACC_    10
/** @brief TMS470 */
#define _FX_TMS470_    11
/** @brief MIPS SDE */
#define _FX_MIPS_SDE_  12

/* Compiler */
#ifndef _FX_COMPILER_
  #ifdef _MSC_VER
    #if _MSC_VER >= 1400
      #define _FX_COMPILER_ _FX_VC8_
    #elif _MSC_VER >= 1300
      #define _FX_COMPILER_ _FX_VC7_
    #else
      /**
       * @brief Current Compiler.
       *
       * Now it can be:
       * - #_FX_VC6_
       * - #_FX_VC7_
       * - #_FX_VC8_
       * - #_FX_GCC_
       * - #_FX_ADS_
       * - #_FX_RVCT_
       * - #_FX_IARCC_
       * - #_FX_NOKIA_X86_
       * - #_FX_METROWERKS_
       * - #_FX_PACC_
       * - #_FX_TMS470_
       * - #_FX_MIPS_SDE_
       *
       * @hideinitializer
       */
      #define _FX_COMPILER_ _FX_VC6_
    #endif
  #elif defined(__GNUC__)
    #define _FX_COMPILER_ _FX_GCC_
  #elif defined(__ARMCC_VERSION)
    #if __ARMCC_VERSION < 200000
      #define _FX_COMPILER_ _FX_ADS_
    #else
      #define _FX_COMPILER_ _FX_RVCT_
    #endif
  #elif defined(__ICCARM__)
    #define _FX_COMPILER_ _FX_IARCC_
  #elif defined(_PACC_VER)
    #define _FX_COMPILER_ _FX_PACC_
  #elif defined(__TMS470__)
    #define _FX_COMPILER_ _FX_TMS470_
  #endif
#endif  /* !_FX_COMPILER_ */
#if !defined(_FX_COMPILER_) || _FX_COMPILER_ == 0
  #error Sorry, can not figure out what compiler you are using. Please specify _FX_COMPILER_ macro.
#endif
//<<<+++OPENSOURCE_MUST_END

/*@}*/

/**
 * @name CPU Defines
 */
/*@{*/

/** @brief 32-bit x86 CPU */
#define _FX_X86_    1
/** @brief ARM */
#define _FX_ARM_    2
/** @brief Power PCPower PC */
#define _FX_POWERPC_  3
/** @brief Sparc */
#define _FX_SPARC_    4
/** @brief IA64 */
#define _FX_IA64_    5
/** @brief MIPS */
#define _FX_MIPS_    6
/** @brief 64-bit x86 CPU */
#define _FX_X64_    7
/** @brief ARM64 */
#define _FX_ARM64_      8

#if defined(_FXM_PLATFORM_LINUX_JS_)
#define _FX_CPU_ _FX_X64_
#endif

#if defined(_CHROME_PNACL_)
  #define _FX_CPU_ _FX_X86_
#endif
/* CPU */
#ifndef _FX_CPU_
  #if defined(__arm__) || defined(ARM) || defined(_ARM_) || defined(__ARMCC_VERSION) || defined(__ICCARM__) || defined(__arm) || defined(arm9)
    #define _FX_CPU_ _FX_ARM_
    #elif defined(__arm64) || defined(__arm64__) || defined(__aarch64__)
        #define _FX_CPU_ _FX_ARM64_
  #elif defined(_M_IX86) || defined(__i386__)
    /**
     * @brief Current CPU.
     *
     * Now it can be:
     * - #_FX_X86_
     * - #_FX_ARM_
     * - #_FX_POWERPC_
     * - #_FX_SPARC_
     * - #_FX_IA64_
     * - #_FX_MIPS_
     * - #_FX_X64_
     * - #_FX_MIPS_
     *
     * @hideinitializer
     */
    #define _FX_CPU_ _FX_X86_
  #elif defined(_M_X64) || defined(__x86_64__)
    #define _FX_CPU_ _FX_X64_
  #elif defined(_M_IA64)
    #define _FX_CPU_ _FX_IA64_
  #elif defined(__POWERPC__)
    #define _FX_CPU_ _FX_POWERPC_
  #elif defined(__sparc__)
    #define _FX_CPU_ _FX_SPARC_
  #elif defined(MIPS) || defined(_MIPS_) || defined(__mips)
    #define _FX_CPU_ _FX_MIPS_
  #endif
#endif
#if !defined(_FX_CPU_) || _FX_CPU_ == 0
  #error Sorry, can not figure out what CPU you are targeting to. Please specify _FX_CPU_ macro.
#endif
//<<<+++OPENSOURCE_MUST_END

/*@}*/
#ifdef _MSC_VER
  #if _MSC_VER >= 1600
    #define _FX_EMBEDFONT_PRINT_
  #endif
#endif

/**
 * @name Word Size Defines
 */
/*@{*/

//<<<+++OPENSOURCE_MUST_BEGIN
/** @brief 32-bit instruct */
#define _FX_W32_    1
/** @brief 64-bit instruct */
#define _FX_W64_    2

/* Word size or instruct length */
#ifndef _FX_WORDSIZE_
#if defined(_WIN64) || defined(__arm64) || defined(__arm64__) || defined(_M_AMD64) || defined(_M_X64) || defined(_M_IA64) || defined(__powerpc64__) || defined(__x86_64__) || __WORDSIZE == 64 || defined(__LP64__)
    #define _FX_WORDSIZE_  _FX_W64_
  #else
    #define _FX_WORDSIZE_  _FX_W32_
  #endif
#endif
//<<<+++OPENSOURCE_MUST_END

/*@}*/

/**
 * @name Byte Order Defines
 */
/*@{*/

/** @brief big endian */
#define _FX_BIG_ENDIAN_    1
/** @brief little endian */
#define _FX_LITTLE_ENDIAN_  2

/* Byte Order */
#ifndef _FX_ENDIAN_
  #if _FX_CPU_ == _FX_POWERPC_ || _FX_CPU_ == _FX_SPARC_
    #define _FX_ENDIAN_ _FX_BIG_ENDIAN_
  #else
    /**
     * @brief Current Byte Order.
     *
     * Now it can be:
     * - #_FX_BIG_ENDIAN_
     * - #_FX_LITTLE_ENDIAN_
     *
     * @hideinitializer
     */
    #define _FX_ENDIAN_ _FX_LITTLE_ENDIAN_
  #endif
#endif

/*@}*/

/* Include basic headers */
#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <float.h>

  //<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
  #ifndef _FX_NO_ANSIC_
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <assert.h>
    #if _FX_OS_ != _FX_VXWORKS_ && ((_FX_COMPILER_ == _FX_GCC_ && _FX_OS_ != _FX_SYMBIAN_) || _FX_COMPILER_ == _FX_NOKIA_X86_ || _FX_COMPILER_ == _FX_METROWERKS_ || _FX_COMPILER_ == _FX_IARCC_)
      #include <wchar.h>
    #endif
  #endif
  //<<<+++OPENSOURCE_MUST_END

//<<<+++OPENSOURCE_MUST_BEGIN
#if _FXM_PLATFORM_ == _FXM_PLATFORM_APPLE_
  #include <libkern/OSAtomic.h>
  #if _FX_OS_ == _FX_MACOSX_
    #include <Carbon/Carbon.h>
  #elif _FX_OS_ == _FX_IOS_
     #include <CoreText/CoreText.h>
     #include <CoreGraphics/CoreGraphics.h>
  #endif
#endif
//<<<+++OPENSOURCE_MUST_END

#ifdef _UNICODE
  #define GetObject GetObjectW
  #define GetModuleFileName GetModuleFileNameW
  #define GetFullPathName GetFullPathNameW
#else
  /**
   * @brief Get object information. GetObjectW defined for unicode-mode, GetObjectA for ansi-mode.
   * @hideinitializer
   */
  #define GetObject GetObjectA
  /**
   * @brief Get the fully-qualified path for specified module. GetModuleFileNameW defined for unicode-mode,
   *        GetModuleFileNameA for ansi-mode.
   * @hideinitializer
   */
  #define GetModuleFileName GetModuleFileNameA
  /**
   * @brief Get the full path and file name of a specified file. GetFullPathNameW defined for unicode-mode,
   *        GetFullPathNameA for ansi-mode.
   * @hideinitializer
   */
  #define GetFullPathName GetFullPathNameA
#endif

#if ( _FX_OS_ == _FX_IOS_ && (_FX_CPU_ == _FX_ARM_ || _FX_CPU_ == _FX_ARM64_)) || (_FX_OS_ == _FX_ANDROID_) || (_FX_OS_ == _FX_WIN32_MOBILE_)
  #ifndef _FXCORE_LIMITED_MEMORY_
    #define _FXCORE_LIMITED_MEMORY_
  #endif
  #ifndef _FXCORE_LIMITED_CPU_
    #define _FXCORE_LIMITED_CPU_
  #endif
#endif

#if _FX_COMPILER_ == _FX_ADS_ || _FX_COMPILER_ == _FX_RVCT_  || _FX_COMPILER_ == _FX_TMS470_ || _FX_OS_ == _FX_ANDROID_
  //#define _FX_NO_EXCEPTION_    //Removed by Malcolm J. Xue, Sep. 9th, 2010, should be defined outside
  #define _FX_NO_NAMESPACE_
#endif

/**
 * @name Target Defines
 */
/*@{*/

/** @brief The default sdk information */
#define _FX_DEFAULT_TARGET_    0
/** @brief Brew SDK */
#define _FX_BREW_        1

/*@}*/
//<<<+++OPENSOURCE_MUST_END

#if (((_FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN64_) && (defined(_FX_WINAPI_PARTITION_DESKTOP_) || defined(_FX_WINAPI_PARTITION_APP_))) || _FX_OS_ == _FX_LINUX_DESKTOP_ || _FX_OS_ == _FX_MACOSX_)
#ifndef _FX_NO_SIMD_
  #if !defined(_FXM_PLATFORM_LINUX_JS_) && !defined(_CHROME_PNACL_) && (_FX_CPU_ != _FX_ARM_) && (_FX_CPU_ != _FX_ARM64_)
    #define _FXM_SIMD_
  #endif
#endif
#endif
#if _FX_OS_ != _FX_MACOSX_
  //#define  _FXM_OPENMP_
#endif

#ifndef _FX_NO_OPENSSL_
  #define _FX_NO_OPENSSL_
#endif

#if (((_FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN64_) && defined(_FX_WINAPI_PARTITION_DESKTOP_)) || _FX_OS_ == _FX_LINUX_DESKTOP_ || _FX_OS_ == _FX_MACOSX_)
#ifndef _FX_NO_JPEG_TURBO_
  #if !defined(_FXM_PLATFORM_LINUX_JS_) && !defined(_CHROME_PNACL_)
    #define _FX_JPEG_TURBO_
  #endif
#endif
#ifndef _FX_NO_OPENSSL_
   #define _FXM_OPENSSL_
#endif
  #define _FX_LARGEFILE_SUPPORT_
#ifndef _FX_NO_SIMD_
  #define WITH_SIMD
#endif
  #define _FPDF_STREAM_RENDER_
#ifndef _FX_ENABLE_OVERPRINT_
  #define _FX_ENABLE_OVERPRINT_
#endif
#endif

#ifdef _FX_WINAPI_PARTITION_APP_
#define _FPDF_STREAM_RENDER_
#endif
//<<<+++OPENSOURCE_MUST_END

//<<<+++OPENSOURCE_MUST_BEGIN
#ifdef __cplusplus
extern "C" {
#endif
//<<<+++OPENSOURCE_MUST_END

/**
 * @name BASIC DATA TYPES
 */
/*@{*/
/** @brief Pointer to any type. */
typedef void*          FX_LPVOID;
/** @brief Pointer to any constant type. */
typedef void const*        FX_LPCVOID;
/** @brief A value used to denote the position of an element in a collection. */
  typedef void*          FX_POSITION;

/** @brief Signed 8bits integer. */
typedef signed char        FX_INT8;
/** @brief Unsigned 8bits integer. */
typedef unsigned char      FX_UINT8;
/** @brief Byte (8 bits). */
typedef unsigned char      FX_BYTE;
/** @brief Pointer to a FX_BYTE. */
typedef unsigned char*      FX_LPBYTE;
/** @brief Pointer to a constant FX_BYTE. */
typedef unsigned char const*  FX_LPCBYTE;
/** @brief Signed 16bits integer. */
typedef short          FX_INT16;
/** @brief Unsigned 16bits integer. */
typedef unsigned short      FX_UINT16;
/** @brief Short integer (16 bits). */
typedef short          FX_SHORT;
/** @brief 16-bit unsigned integer. */
typedef unsigned short      FX_WORD;
/** @brief Pointer to a WORD. */
typedef unsigned short*      FX_LPWORD;
/** @brief Pointer to a WORD. */
typedef unsigned short const*  FX_LPCWORD;
/** @brief 32-bit signed integer. */
typedef int            FX_INT32;
/** @brief 32-bit floating-point number. */
typedef float          FX_FLOAT;
#ifdef __cplusplus
/** @brief Boolean variable (should be true or false). */
typedef bool          FX_BOOL;
#else
/** @brief Boolean variable (should be TRUE or FALSE). */
typedef int            FX_BOOL;
#endif
/** @brief Error indicator. */
typedef int            FX_ERR;
/** @brief Determine whether a status is successful. */
#define FX_SUCCEEDED(Status)  ((FX_ERR)(Status) >= 0)
/** @brief Determine whether a status is failure. */
#define FX_FAILED(Status)    ((FX_ERR)(Status) < 0)

/** @brief 8-bit Windows (ANSI) character. */
typedef char          FX_CHAR;
/** @brief Pointer to 8-bit Windows (ANSI) characters. */
typedef char*          FX_LPSTR;
/** @brief Pointer to constant 8-bit Windows (ANSI) characters. */
typedef char const*        FX_LPCSTR;

  //<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
  /**
   *  TYPE    LP32  ILP32  LP64  ILP64  LLP64
   *  CHAR       8    8      8    8    8
   *  SHORT      16     16    16     16     16
   *  INT        16     32    32     64     32
   *  LONG      32     32    64     64     32
   *  LONG LONG    64     64    64     64     64
   *  POINTER      32     32    64     64     64
   */
  #if !defined(_MSC_VER) && (_FX_CPU_ == _FX_X64_ || _FX_CPU_ == _FX_IA64_ || _FX_CPU_ == _FX_ARM64_)
    /** @brief 32-bit unsigned integer. */
    typedef unsigned int      FX_DWORD;
    /** @brief Pointer to a DWORD. */
    typedef unsigned int*      FX_LPDWORD;
  #else
    /** @brief 32-bit unsigned integer. */
    typedef unsigned long      FX_DWORD;
    /** @brief Pointer to a DWORD. */
    typedef unsigned long*      FX_LPDWORD;
  #endif

  /** @brief Compiler dependant Unicode character (16-bit for Microsoft Compiler, 32-bit for gcc). */
  typedef wchar_t          FX_WCHAR;
  /** @brief Pointer to Unicode characters. */
  typedef wchar_t*        FX_LPWSTR;
  /** @brief Pointer to constant Unicode characters. */
  typedef wchar_t const*      FX_LPCWSTR;

  #ifdef _MSC_VER
    /** @brief Signed 64-bit integer. */
    typedef __int64        FX_INT64;
    /** @brief Unsigned 64-bit integer. */
    typedef unsigned __int64  FX_UINT64;
  #else
    typedef long long int    FX_INT64;
    typedef unsigned long long  FX_UINT64;
  #endif

  #if (_FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN64_) && !defined(_FX_NO_WINDOWS_)
    /** @brief Signed integral type for pointer precision. */
    typedef INT_PTR FX_INTPTR;
    /** @brief Unsigned integral type for pointer precision. */
    typedef UINT_PTR FX_UINTPTR;
  #else
    #if (_FX_CPU_ == _FX_X64_ || _FX_CPU_ == _FX_IA64_ || _FX_CPU_ == _FX_ARM64_)
      typedef FX_INT64      FX_INTPTR;
      typedef FX_UINT64      FX_UINTPTR;
    #else
      typedef int          FX_INTPTR;
      typedef unsigned int    FX_UINTPTR;
    #endif
  #endif
  //<<<+++OPENSOURCE_MUST_END

//<<<+++OPENSOURCE_MUST_BEGIN
/** @brief unsigned 32bits integer. */
typedef FX_DWORD        FX_UINT32;
/** @brief unsigned quad-word integer. */
typedef FX_UINT64        FX_QWORD;

/** @brief Macro to define a handle type. */
#define FX_DEFINEHANDLE(name)  typedef struct _##name {FX_LPVOID pData;} * name;

#if defined(DEBUG) && !defined(_DEBUG)
  #define _DEBUG
#endif

#ifndef __cplusplus
#ifndef TRUE
  /** @brief Keyword which value is 1. */
  #define TRUE  1
#endif

#ifndef FALSE
  /** @brief Keyword which value is 0. */
  #define FALSE  0
#endif
#endif

#ifndef NULL
  /** @brief The null-pointer value. */
  #define NULL  0
#endif
//<<<+++OPENSOURCE_MUST_END

/* Assertion */

  //<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
  #if !defined(_FX_NO_ANSIC_)
    /**
     * @brief Assertion.
     * @hideinitializer
     */
    #define FXSYS_assert assert
  #else
    void  FXSYS_assert(int condition);
  #endif
  //<<<+++OPENSOURCE_MUST_END

//<<<+++OPENSOURCE_MUST_BEGIN
#ifndef ASSERT
  #ifdef _DEBUG
    #define ASSERT FXSYS_assert
  #else
    /**
     * @brief Assertion for debug mode, do nothing for release mode.
     * @hideinitializer
     */
    #define ASSERT(a)
  #endif
#endif

/** @brief A macro that returns the maximum of a and b. */
#define FX_MAX(a, b) (((a) > (b)) ? (a) : (b))
/** @brief A macro that returns the minimum of a and b. */
#define FX_MIN(a, b) (((a) < (b)) ? (a) : (b))

/** @brief A macro to PI */
#define FX_PI  3.1415926535897932384626433832795f

/** @brief A macrio to malloc size limit. */
#if _FX_WORDSIZE_ == _FX_W64_ && _FXM_PLATFORM_ == _FXM_PLATFORM_WINDOWS_
  #define _FX_CRT_MALLOC_LIMIT_  0x7fffffffffffffffL
#else
  #define _FX_CRT_MALLOC_LIMIT_  0x7fffffffL
#endif

//<<<+++OPENSOURCE_MUST_END

/*@}*/

/**
 * @name Byte string operations
 */
/*@{*/

  //<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
  #if !defined(_FX_NO_ANSIC_)
    /**
     * @brief Write formatted data to a ANSIC string.
     * @hideinitializer
     */
    #define FXSYS_sprintf sprintf
    /**
     * @brief Write formatted data to a ANSIC string, with max length.
     * @hideinitializer
     */
    #ifdef _WIN32
      #define FXSYS_snprintf _snprintf
      #define FXSYS_vsnprintf  _vsnprintf
    #else
      #define FXSYS_snprintf snprintf
      #define FXSYS_vsnprintf  vsnprintf
    #endif
    /**
     * @brief Write formatted output using a pointer to a list of arguments.
     * @hideinitializer
     */
    #define FXSYS_vsprintf vsprintf
    /**
     * @brief Find a character in a ANSIC string.
     * @hideinitializer
     */
    #define FXSYS_strchr strchr
    /**
     * @brief Get the length of a ANSIC string.
     * @hideinitializer
     */
    #define FXSYS_strlen strlen
    /**
     * @brief Compare characters of two ANSIC strings.
     * @hideinitializer
     */
    #define FXSYS_strncmp strncmp
    /**
     * @brief Compare ANSIC strings.
     * @hideinitializer
     */
    #define FXSYS_strcmp strcmp
    /**
     * @brief Copy an ANSIC string.
     * @hideinitializer
     */
    #define FXSYS_strcpy strcpy
    /**
     * @brief Copy an ANSIC string with length limitation.
     * @hideinitializer
     */
    #define FXSYS_strncpy strncpy
    /**
     * @brief Find a substring
     * @hideinitializer
     */
    #define FXSYS_strstr strstr
  #else
    int    FXSYS_sprintf(char* buffer, const char* format, ...);
    int    FXSYS_vsprintf(char *buffer, const char *format, va_list args);
    char*  FXSYS_strchr(const char* str, int ch);
    long  FXSYS_strlen(const char* str);
    int    FXSYS_strncmp(const char* str1, const char* str2, size_t len);
    int    FXSYS_strcmp(const char* str1, const char* str2);
    char*  FXSYS_strcpy(char* dest, const char* src);
    char*  FXSYS_strncpy(char* dest, const char* src, size_t len);
    char*  FXSYS_strstr(const char *string, const char *strFind);
  #endif
  //<<<+++OPENSOURCE_MUST_END

/*@}*/

/**
 * @name File operations
 */
/*@{*/
  //<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
  #if !defined(_FX_NO_ANSIC_) && !defined(__EMSCRIPTEN__)
    /**
     * @brief File structure.
     * @hideinitializer
     */
    #define FXSYS_FILE FILE
    /**
     * @brief Open a file.
     * @hideinitializer
     */
    #define FXSYS_fopen fopen
    /**
     * @brief Close a file.
     * @hideinitializer
     */
    #define FXSYS_fclose fclose
    /**
     * @brief End of file.
     * @hideinitializer
     */
    #define FXSYS_SEEK_END SEEK_END
    /**
     * @brief Beginning of file.
     * @hideinitializer
     */
    #define FXSYS_SEEK_SET SEEK_SET
    /**
     * @brief Moves the file pointer to a specified location.
     * @hideinitializer
     */
    #define FXSYS_fseek fseek
    /**
     * @brief Gets the current position of a file pointer.
     * @hideinitializer
     */
    #define FXSYS_ftell ftell
    /**
     * @brief Reads data from a file.
     * @hideinitializer
     */
    #define FXSYS_fread fread
    /**
     * @brief Writes data to a file.
     * @hideinitializer
     */
    #define FXSYS_fwrite fwrite
    /**
     * @brief Print formatted data to a file.
     * @hideinitializer
     */
    #define FXSYS_fprintf fprintf
    /**
     * @brief Flush file.
     * @hideinitializer
     */
    #define FXSYS_fflush fflush
  #else
    #define FXSYS_FILE void
    FXSYS_FILE*  FXSYS_fopen(const char* filename, const char* mode);
    int    FXSYS_fclose(FXSYS_FILE*);
    #define  FXSYS_SEEK_END  2
    #define  FXSYS_SEEK_SET  0
    int    FXSYS_fseek(FXSYS_FILE*, long, int);
    long  FXSYS_ftell(FXSYS_FILE*);
    size_t  FXSYS_fread(void*, size_t, size_t, FXSYS_FILE*);
    long  FXSYS_fwrite(const void*, long, long, FXSYS_FILE*);
    int    FXSYS_fprintf(FXSYS_FILE*, const char*, ...);
    int    FXSYS_fflush(FXSYS_FILE*);
  #endif

  // For now, we provide wide-string file name support for Windows only
  #if _FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN32_MOBILE_ || _FX_OS_ == _FX_WIN64_
    /**
     * @brief Open a file using wide-string parameters. Only supported on Windows platforms now.
     * @hideinitializer
     */
    #ifdef _NATIVE_WCHAR_T_DEFINED
      #define FXSYS_wfopen(f, m) _wfopen((const wchar_t*)(f), (const wchar_t*)(m))
    #else
      #define FXSYS_wfopen _wfopen
    #endif
  #else
    FXSYS_FILE* FXSYS_wfopen(FX_LPCWSTR filename, FX_LPCWSTR mode);
  #endif

/*@}*/

/**
 * @name Wide string operations
 */
/*@{*/

  //<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
  /* Basic wide string operations, not available in ADS/RVCT/PACC/Android/MIPS_SDE */
  #if _FX_OS_ != _FX_VXWORKS_ && _FX_OS_ != _FX_ANDROID_ && !defined(_FX_NO_ANSIC_) && _FX_COMPILER_ != _FX_ADS_ && _FX_COMPILER_ != _FX_RVCT_ && _FX_COMPILER_ != _FX_PACC_ && _FX_COMPILER_ != _FX_TMS470_ && _FX_COMPILER_ != _FX_MIPS_SDE_
    #ifdef _NATIVE_WCHAR_T_DEFINED
      #define FXSYS_wcslen(str) wcslen((wchar_t*)(str))
      #define FXSYS_wcscmp(str1, str2) wcscmp((wchar_t*)(str1), (wchar_t*)(str2))
    #else
      /**
       * @brief Get the length of a wide-character string.
       * @hideinitializer
       */
      #define FXSYS_wcslen wcslen
      /**
       * @brief Compare wide-character strings.
       * @hideinitializer
       */
      #define FXSYS_wcscmp wcscmp
    #endif
  #else
    size_t  FXSYS_wcslen(const wchar_t*);
    int    FXSYS_wcscmp(const wchar_t*, const wchar_t*);
  #endif

  /* Some other wide string functions, not available in ADS/RVCT/GCCE/PACC/Android/MIPS_SDE */
  #if _FX_OS_ != _FX_VXWORKS_ && _FX_OS_ != _FX_ANDROID_ && !defined(_FX_NO_ANSIC_) && _FX_COMPILER_ != _FX_ADS_ && _FX_COMPILER_ != _FX_RVCT_ && !(_FX_COMPILER_ == _FX_GCC_ && _FX_OS_ == _FX_SYMBIAN_) && _FX_COMPILER_ != _FX_PACC_ && _FX_COMPILER_ != _FX_TMS470_ && _FX_COMPILER_ != _FX_MIPS_SDE_
    #ifdef _NATIVE_WCHAR_T_DEFINED
      #define FXSYS_wcschr(str, ch) (FX_LPCWSTR)wcschr((wchar_t*)(str), ch)
      #define FXSYS_wcsstr(str1, str2) (FX_LPCWSTR)wcsstr((wchar_t*)(str1), (wchar_t*)(str2))
      #define FXSYS_wcsncmp(str1, str2, n) wcsncmp((wchar_t*)(str1), (wchar_t*)(str2), n)
    #else
      /**
       * @brief Find a wide-character in a wide-character string.
       * @hideinitializer
       */
      #define FXSYS_wcschr wcschr
      /**
       * @brief Find a sub-wide-character-string.
       * @hideinitializer
       */
      #define FXSYS_wcsstr wcsstr
      /**
       * @brief Compare characters of two wide-character strings.
       * @hideinitializer
       */
      #define FXSYS_wcsncmp wcsncmp
    #endif
    /**
     * @brief Write formatted output wide character string using a pointer to a list of arguments.
     * @hideinitializer
     */
    #define FXSYS_vswprintf vswprintf
  #else
    wchar_t*  FXSYS_wcschr(const wchar_t*, wchar_t);
    wchar_t*  FXSYS_wcsstr(const wchar_t*, const wchar_t*);
    int    FXSYS_wcsncmp(const wchar_t*, const wchar_t*, size_t);
    #if _FX_OS_ != _FX_ANDROID_
      int    FXSYS_vswprintf(wchar_t*, const wchar_t*, va_list);
    #else
      #define FXSYS_vswprintf vswprintf
    #endif
  #endif

  #if !defined(_FX_NO_ANSIC_) && _FX_COMPILER_ != _FX_TMS470_
    /**
     * @brief Converts a sequence of multi-byte characters to a corresponding sequence of wide characters.
     * @hideinitializer
     */
    #define FXSYS_mbstowcs mbstowcs
    /**
     * @brief Converts a sequence of wide characters to a corresponding sequence of multi-byte characters.
     * @hideinitializer
     */
    #define FXSYS_wcstombs wcstombs
  #else
    size_t  FXSYS_mbstowcs(wchar_t *dest, const char *src, size_t n);
    size_t  FXSYS_wcstombs(char *dest, const wchar_t *src, size_t n);
  #endif
  //<<<+++OPENSOURCE_MUST_END

/*@}*/

  //<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
  /**
   * @name Memory block operations
   */
  /*@{*/

  #if !defined(_FX_NO_ANSIC_)
    /**
     * @brief Compares two buffers.
     * @hideinitializer
     */
    #define FXSYS_memcmp memcmp
    /**
     * @brief Copy from one buffer to another.
     * @hideinitializer
     */
    #define FXSYS_memcpy memcpy
    /**
     * @brief Moves one buffer to another. If some regions of the source area and the destination overlap,
     *        {@link ::FXSYS_memmove} ensures that the original source bytes in the overlapping region are copied
     *        before being overwritten.
     * @hideinitializer
     */
    #define FXSYS_memmove memmove
    /**
     * @brief Use given character to initialize the buffer.
     * @hideinitializer
     */
    #define FXSYS_memset memset
    /**
     * @brief Search for a byte in a memory block.
     * @hideinitializer
     */
    #define FXSYS_memchr memchr
  #else
    int    FXSYS_memcmp(const void*, const void*, size_t);
    void*  FXSYS_memcpy(void*, const void*, size_t);
    void*  FXSYS_memmove(void*, const void*, size_t);
    void*  FXSYS_memset(void*, int, size_t);
    void*  FXSYS_memchr(const void*, int, size_t);
  #endif

  /*@}*/

  /* Others */
  #if !defined(_FX_NO_ANSIC_)
    /**
     * @brief Performs a quick sort. A generic algorithm.
     * @hideinitializer
     */
    #define FXSYS_qsort qsort
  #else
    void  FXSYS_qsort(void*, unsigned, unsigned, int (*)(const void*, const void*));
  #endif

  #if _FX_OS_ != _FX_WIN32_MOBILE_ && !defined(_FX_NO_ANSIC_) && _FX_OS_ != _FX_SYMBIAN_
    /**
     * @brief Performs a binary search of a sorted array. A generic algorithm.
     * @hideinitializer
     */
    #define FXSYS_bsearch bsearch
  #else
    /* WinCE doesn't support bsearch. The bsearch function comes with Symbian also has crash problem. */
    void *  FXSYS_bsearch(const void *key, const void *base, size_t num, size_t width, int (*compare)(const void *, const void *));
  #endif

  #if (_FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN32_MOBILE_ || _FX_OS_ == _FX_WIN64_) && !defined(_FX_NO_WINDOWS_)
    /* On Windows platform, we can replace more system calls */

    /**
     * @brief Convert an integer to a ANSIC string.
     * @hideinitializer
     */
    #define FXSYS_itoa _itoa
    /**
     * @brief Convert a ANSIC string to lowercase.
     * @hideinitializer
     */
    #define FXSYS_strlwr _strlwr
    /**
     * @brief Convert a ANSIC string to uppercase.
     * @hideinitializer
     */
    #define FXSYS_strupr _strupr
    /**
     * @brief Compare two ANSIC strings. case-insensitive.
     * @hideinitializer
     */
    #define FXSYS_stricmp _stricmp

    #ifdef _NATIVE_WCHAR_T_DEFINED
      #define FXSYS_wcsicmp(str1, str2) _wcsicmp((wchar_t*)(str1), (wchar_t*)(str2))
      #define FXSYS_WideCharToMultiByte(p1, p2, p3, p4, p5, p6, p7, p8) WideCharToMultiByte(p1, p2, (const wchar_t*)(p3), p4, p5, p6, p7, p8)
      #define FXSYS_MultiByteToWideChar(p1, p2, p3, p4, p5, p6) MultiByteToWideChar(p1, p2, p3, p4, (wchar_t*)(p5), p6)
      #define FXSYS_wcslwr(str) _wcslwr((wchar_t*)(str))
      #define FXSYS_wcsupr(str) _wcsupr((wchar_t*)(str))
    #else
      /**
       * @brief Compare two wide character strings. case-insensitive.
       * @hideinitializer
       */
      #define FXSYS_wcsicmp _wcsicmp
      /**
       * @brief Maps a wide-character string to a character string.
       * @hideinitializer
       */
      #define FXSYS_WideCharToMultiByte WideCharToMultiByte
      /**
       * @brief Maps a character string to a wide-character string.
       * @hideinitializer
       */
      #define FXSYS_MultiByteToWideChar MultiByteToWideChar
      /**
       * @brief Convert a wide-character string to lowercase.
       * @hideinitializer
       */
      #define FXSYS_wcslwr _wcslwr
      /**
       * @brief Convert a wide-character string to uppercase.
       * @hideinitializer
       */
      #define FXSYS_wcsupr _wcsupr
    #endif

    #ifndef _FX_WINAPI_PARTITION_DESKTOP_
      int      FXSYS_IntersectRect(struct FX_RECT*, const struct FX_RECT*, const struct FX_RECT*);
      int      FXSYS_GetACP(void);
      FX_DWORD  FXSYS_GetFullPathName(const char* filename, FX_DWORD buflen, char* buf, char** filepart);
      FX_DWORD  FXSYS_GetModuleFileName(void* hModule, char* buf, FX_DWORD bufsize);
    #else
      /**
       * @brief Get the full path and file name of a specified file.
       * @hideinitializer
       */
      #define FXSYS_GetFullPathName GetFullPathName
      /**
       * @brief Get the fully-qualified path for specified module.
       * @hideinitializer
       */
      #define FXSYS_GetModuleFileName GetModuleFileName
      /**
       * @brief Retrieve the current ANSI code-page identifier for the system.
       * @hideinitializer
       */
      #define FXSYS_GetACP GetACP
    #endif
  #else
    char*    FXSYS_itoa(int value, char* string, int radix);
    int      FXSYS_GetACP(void);
    int      FXSYS_WideCharToMultiByte(FX_DWORD codepage, FX_DWORD dwFlags, const wchar_t* wstr, int wlen,
                char* buf, int buflen, const char* default_str, int* pUseDefault);
    int      FXSYS_MultiByteToWideChar(FX_DWORD codepage, FX_DWORD dwFlags, const char* bstr, int blen,
                wchar_t* buf, int buflen);
    FX_DWORD  FXSYS_GetFullPathName(const char* filename, FX_DWORD buflen, char* buf, char** filepart);
    FX_DWORD  FXSYS_GetModuleFileName(void* hModule, char* buf, FX_DWORD bufsize);

    char*    FXSYS_strlwr(char* str);
    char*    FXSYS_strupr(char* str);
    int      FXSYS_stricmp(const char*, const char*);
    int      FXSYS_wcsicmp(const wchar_t *string1, const wchar_t *string2);

    wchar_t*  FXSYS_wcslwr(wchar_t* str);
    wchar_t*  FXSYS_wcsupr(wchar_t* str);
  #endif
  //<<<+++OPENSOURCE_MUST_END

  //*****************************************************************************
  //* Memory utilities
  //*****************************************************************************
  /**
   * @name Memory utilities
   */
  /*@{*/

  /**
   * @brief Copy buffer data from source to destination.
   *
   * @details Parameter <i>dst</i> and <i>src</i> should start from 4-bytes-aligned position, but size can be any value.
   *
   * @param[in,out] dst  Destination buffer pointer.
   * @param[in] src      Source buffer pointer to copy from.
   * @param[in] size     Length of data to copy, in bytes.
   *
   * @return The dest buffer.
   *
   */
  void*    FXSYS_memcpy32(void* dst, const void* src, size_t size);

  /**
   * @brief Compare data in two buffers.
   *
   * @details Input buffers should start from 4-bytes-aligned position, but size can be any value.
   *
   * @param[in] buf1  First buffer pointer.
   * @param[in] buf2  Second buffer pointer.
   * @param[in] size  Length of data to compare, in bytes.
   *
   * @return The result would be following:
   *         <ul>
   *         <li>The result would be less than zero if <b>buf1</b> less than <b>buf2</b>;</li>
   *         <li>The result would be equal to zero if <b>buf1</b> identical to <b>buf2</b>;</li>
   *         <li>The result would be bigger than 0, if <b>buf2</b> greater than <b>buf2</b>.</li>
   *         </ul>
   */
  FX_INT32  FXSYS_memcmp32(const void* buf1, const void* buf2, size_t size);

  /**
   * @brief Set buffer data to specified value.
   *
   * @details Parameter <i>dst</i> should start from 4-bytes-aligned position, but size can be any value.
   *
   * @param[in,out] dst  Destination buffer pointer.
   * @param[in] v        Value to set.
   * @param[in] size     Length of data to set, in bytes.
   *
   * @return The dest buffer.
   */
  void*    FXSYS_memset32(void* dst, FX_INT32 v, size_t size);

  /**
   * @brief Set buffer data to specified value.
   *
   * @details Parameter <i>dst</i> should start from 4-bytes-aligned position, but size can be any value.
   *
   * @param[in,out] dst  Destination buffer pointer.
   * @param[in] v        Value to set.
   * @param[in] size     Length of data to set, in bytes.
   *
   * @return The dest buffer.
   */
  void*    FXSYS_memset8(void* dst, FX_BYTE v, size_t size);

  /**
   * @brief Move source buffer data into destination.
   *
   * @param[in,out] dst  Destination buffer pointer.
   * @param[in] src      Source buffer pointer.
   * @param[in] size     Length of source buffer data to move, in bytes.
   *
   * @return The dest buffer.
   */
  void*    FXSYS_memmove32(void* dst, const void* src, size_t size);
  /*@}*/
//<<<+++OPENSOURCE_MUST_END

//<<<+++OPENSOURCE_MUST_BEGIN
#ifdef __cplusplus
}
#endif
//<<<+++OPENSOURCE_MUST_END

  //<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
  /**
   * @name Math functions
   */
  /*@{*/

  #if _FX_OS_ == _FX_PALMOS_ && _FX_COMPILER_ == _FX_METROWERKS_
    #ifdef __cplusplus
      extern "C" {
    #endif

    /* Metrowerks for Palm OS (9.3) doesn't support standard math.h */
    extern double __ieee754_pow(double, double);
    extern double __ieee754_sqrt(double);
    extern double __fabs(double);
    extern double __ieee754_atan2(double, double);
    extern double __ceil(double);
    extern double __floor(double);
    extern double __cos(double);
    extern double __ieee754_acos(double);
    extern double __sin(double);
    extern double __ieee754_log(double);
    extern double __ieee754_log10(double);

    #define FXSYS_pow(x, y) __ieee754_pow(x, y)
    #define FXSYS_sqrt(x) __ieee754_sqrt(x)
    #define FXSYS_fabs(x) __fabs(x)
    #define FXSYS_atan2(x, y) __ieee754_atan2(x, y)
    #define FXSYS_ceil(x) __ceil(x)
    #define FXSYS_floor(x) __floor(x)
    #define FXSYS_cos(x) __cos(x)
    #define FXSYS_acos(x) __ieee754_acos(x)
    #define FXSYS_sin(x) __sin(x)
    #define FXSYS_log(x) __ieee754_log(x)
    #define FXSYS_log10(x) __ieee754_log10(x)

    #ifdef __cplusplus
    }
    #endif
  #else
    #include <math.h>
    #if _FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN64_ || _FX_OS_ == _FX_LINUX_DESKTOP_
      /**
       * @brief Calculate the power. FXSYS_pow(x,y) means x^y.
       * @hideinitializer
       */
      #define FXSYS_pow powf
      /**
       * @brief Calculate the square root. FXSYS_sqrt(x) means sqrt(x).
       * @hideinitializer
       */
      #define FXSYS_sqrt sqrtf
      /**
       * @brief Calculate the absolute. FXSYS_fabs(x) means |x|.
       * @hideinitializer
       */
      #define FXSYS_fabs fabsf
      /**
       * @brief Calculate the arctangent. FXSYS_atan2(y,x) means atan(y/x).
       * @hideinitializer
       */
      #define FXSYS_atan2 atan2f
      /**
       * @brief Calculate the ceiling of a value.
       * @hideinitializer
       */
      #define FXSYS_ceil ceilf
      /**
       * @brief Calculate the floor of a value.
       * @hideinitializer
       */
      #define FXSYS_floor floorf
      /**
       * @brief Calculate the cosine of a floating-point number from a radian argument.
       * @hideinitializer
       */
      #define FXSYS_cos cosf
      /**
       * @brief Calculate the arccosine of a floating-point number, in radians.
       * @hideinitializer
       */
      #define FXSYS_acos acosf
      /**
       * @brief Calculate the sine of a floating-point number from a radian argument.
       * @hideinitializer
       */
      #define FXSYS_sin sinf
      /**
       * @brief Calculate the natural logarithm (base e) of a floating-point number.
       * @hideinitializer
       */
      #define FXSYS_log logf
      /**
       * @brief Calculate the common logarithm (base 10) of a floating-point number.
       * @hideinitializer
       */
      #define FXSYS_log10 log10f
      /**
       * @brief Calculate the floating-point remainder.
       * @hideinitializer
       */
      #define FXSYS_fmod fmodf
    #else
      #define FXSYS_pow(a, b)    (FX_FLOAT)pow(a, b)
      #define FXSYS_sqrt(a)    (FX_FLOAT)sqrt(a)
      #define FXSYS_fabs(a)    (FX_FLOAT)fabs(a)
      #define FXSYS_atan2(a, b)  (FX_FLOAT)atan2(a, b)
      #define FXSYS_ceil(a)    (FX_FLOAT)ceil(a)
      #define FXSYS_floor(a)    (FX_FLOAT)floor(a)
      #define FXSYS_cos(a)    (FX_FLOAT)cos(a)
      #define FXSYS_acos(a)    (FX_FLOAT)acos(a)
      #define FXSYS_sin(a)    (FX_FLOAT)sin(a)
      #define FXSYS_log(a)    (FX_FLOAT)log(a)
      #define FXSYS_log10(a)    (FX_FLOAT)log10(a)
      #define FXSYS_fmod(a, b)  (FX_FLOAT)fmod(a, b)
    #endif
  #endif

  #if !defined(_FX_NO_ANSIC_)
    /**
     * @brief A macro that return the absolute value.
     * @hideinitializer
     */
    #define FXSYS_abs abs
  #else
    #define FXSYS_abs(a) ((a)<0?-(a):(a))
  #endif

  /*@}*/
  //<<<+++OPENSOURCE_MUST_END

//<<<+++OPENSOURCE_MUST_BEGIN
#ifdef __cplusplus
extern "C" {
#endif
//<<<+++OPENSOURCE_MUST_END

  //<<<+++OPENSOURCE_MUST_BEGIN LIC==FOXIT
  #ifdef _FX_NO_GLOBAL_
    /* If platform doesn't support global variable, then we have to get from static functions */
    /** Set the first global variable. */
    void    FXSYS_SetStaticPointer1(void*);
    /** Get the first global variable. */
    void*    FXSYS_GetStaticPointer1(void);
    /** Set the second global variable. */
    void    FXSYS_SetStaticPointer2(void*);
    /** Get the second global variable. */
    void*    FXSYS_GetStaticPointer2(void);
  #endif

  /* CPU byte order */
  #if _FX_ENDIAN_ == _FX_BIG_ENDIAN_
    #define _FX_MSB_FIRST_
    #define FXDWORD_FROM_LSBFIRST(i) ( ((FX_BYTE)(i) << 24) | ((FX_BYTE)((i) >> 8) << 16) | ((FX_BYTE)((i) >> 16) << 8) | (FX_BYTE)((i) >> 24) )
    #define FXDWORD_FROM_MSBFIRST(i) (i)
  #else
    #define _FX_LSB_FIRST_
    #define FXDWORD_FROM_LSBFIRST(i) (i)
    #define FXDWORD_FROM_MSBFIRST(i) ( ((FX_BYTE)(i) << 24) | ((FX_BYTE)((i) >> 8) << 16) | ((FX_BYTE)((i) >> 16) << 8) | (FX_BYTE)((i) >> 24) )
  #endif

  #if _FX_CPU_ == _FX_X86_ || _FX_CPU_ == _FX_X64_ || _FX_CPU_ == _FX_ARM64_
    #define FXDWORD_GET_LSBFIRST(p) (*(FX_DWORD*)(p))
  #else
    #define FXDWORD_GET_LSBFIRST(p) ((((FX_LPBYTE)(p))[3] << 24) | (((FX_LPBYTE)(p))[2] << 16) | (((FX_LPBYTE)(p))[1] << 8) | (((FX_LPBYTE)(p))[0]))
  #endif

#define FXDWORD_GET_MSBFIRST(p) ((((FX_LPBYTE)(p))[0] << 24) | (((FX_LPBYTE)(p))[1] << 16) | (((FX_LPBYTE)(p))[2] << 8) | (((FX_LPBYTE)(p))[3]))

#define FXSYS_HIBYTE(word)  ((FX_BYTE)((word) >> 8))
#define FXSYS_LOBYTE(word)  ((FX_BYTE)(word))
#define FXSYS_HIWORD(dword)  ((FX_WORD)((dword) >> 16))
#define FXSYS_LOWORD(dword)  ((FX_WORD)(dword))

/** @brief Convert string to long integer. */
#define    FXSYS_strtol strtol

/**
 * @brief Convert an ANSI string to an integer.
 *
 * @param[in] str  An ANSI string.
 *
 * @return An integer as converted result.
 */
FX_INT32  FXSYS_atoi(FX_LPCSTR str);
/**
 * @brief Convert a wide string to an integer.
 *
 * @param[in] str  A wide string.
 *
 * @return An integer as converted result.
 */
FX_INT32  FXSYS_wtoi(FX_LPCWSTR str);
/**
 * @brief Convert an ANSI string to an integer.
 *
 * @param[in] str  An ANSI string.
 *
 * @return An integer as converted result.
 */
FX_INT64  FXSYS_atoi64(FX_LPCSTR str);
/**
 * @brief Convert a wide string to an integer.
 *
 * @param[in] str  A wide string.
 *
 * @return An integer as converted result.
 */
FX_INT64  FXSYS_wtoi64(FX_LPCWSTR str);
/**
 * @brief Convert an integer to an ANSI string.
 *
 * @param[in] value  An integer.
 * @param[in] str
 * @param[in] radix  Base of value; which must be in the range 2¨C36.
 *
 * @return 
 */
FX_LPCSTR  FXSYS_i64toa(FX_INT64 value, FX_LPSTR str, int radix);
/**
 * @brief Convert an integer to an wide string.
 *
 * @param[in] value  An integer.
 * @param[in] str
 * @param[in] radix  Base of value; which must be in the range 2¨C36.
 *
 * @return 
 */
FX_LPCWSTR  FXSYS_i64tow(FX_INT64 value, FX_LPWSTR str, int radix);
/**
 * @brief Get nearest integer
 *
 * @param[in] f  A float value.
 *
 * @return The nearest integer.
 */
int      FXSYS_round(FX_FLOAT f);
/** @brief Multiply two numbers. */
#define    FXSYS_Mul(a, b) ((a) * (b))
/** @brief Division between two numbers. */
#define    FXSYS_Div(a, b) ((a) / (b))
/** @brief Fist do multiplication, then do division. */
#define    FXSYS_MulDiv(a, b, c) ((a) * (b) / (c))
/** @brief sqrt(a^2 + b^2). */
#define    FXSYS_sqrt2(a, b) (FX_FLOAT)FXSYS_sqrt((a)*(a) + (b)*(b))

//*****************************************************************************
//* Multiple thread controls
//*****************************************************************************
/** @brief Definition for mutex/critical section and read-write lock. */
#if (_FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN32_MOBILE_ || _FX_OS_ == _FX_WIN64_) && !defined(_FX_NO_WINDOWS_)
  typedef CRITICAL_SECTION  FX_MUTEX;
  FX_DEFINEHANDLE(FX_RWLOCK)
#elif _FX_OS_ == _FX_LINUX_DESKTOP_ || _FX_OS_ == _FX_LINUX_EMBEDDED_ || _FX_OS_ == _FX_MACOSX_ || _FX_OS_ == _FX_IOS_ || _FX_OS_ == _FX_ANDROID_
  #include <pthread.h>
  typedef pthread_mutex_t    FX_MUTEX;
  #if _FX_OS_ == _FX_ANDROID_
    FX_DEFINEHANDLE(FX_RWLOCK)
  #else
    typedef pthread_rwlock_t  FX_RWLOCK;
  #endif
#else
  FX_DEFINEHANDLE(FX_MUTEX)
  FX_DEFINEHANDLE(FX_RWLOCK)
#endif
// The following five functions are defined in fx_process.h, please refer there.
FX_BOOL  FX_Mutex_Initialize(FX_MUTEX* pMutex);
void    FX_Mutex_Destroy(FX_MUTEX* pMutex);
FX_BOOL  FX_Mutex_TryLock(FX_MUTEX* pMutex);
void    FX_Mutex_Lock(FX_MUTEX* pMutex);
void    FX_Mutex_Unlock(FX_MUTEX* pMutex);

#define FX_CRITICAL_SECTION    FX_MUTEX
#define FX_InitializeCriticalSection(a)    FX_Mutex_Initialize(a)
#define FX_DeleteCriticalSection(a)      FX_Mutex_Destroy(a)
#define FX_TryEnterCriticalSection(a)    FX_Mutex_TryLock(a)
#define FX_EnterCriticalSection(a)      FX_Mutex_Lock(a)
#define FX_LeaveCriticalSection(a)      FX_Mutex_Unlock(a)

/** @brief Definition for spinlock. */
#if (_FX_OS_ == _FX_WIN32_DESKTOP_ || _FX_OS_ == _FX_WIN32_MOBILE_ || _FX_OS_ == _FX_WIN64_) && !defined(_FX_NO_WINDOWS_)
  typedef void*    FX_SPINLOCK;
#elif _FX_OS_ == _FX_LINUX_DESKTOP_
  #ifdef _FX_SPINLOCK_USEGCCCAS_
    typedef size_t    FX_SPINLOCK;
  #else
#ifndef _CHROME_PNACL_
    typedef pthread_spinlock_t  FX_SPINLOCK;
#else
    typedef size_t    FX_SPINLOCK;
#endif
  #endif
#elif _FX_OS_ == _FX_MACOSX_ || _FX_OS_ == _FX_IOS_
  typedef OSSpinLock  FX_SPINLOCK;
#else // android/embeded linux/other os
  FX_DEFINEHANDLE(FX_SPINLOCK)
#endif
//<<<+++OPENSOURCE_MUST_END

//<<<+++OPENSOURCE_MUST_BEGIN
#ifdef __cplusplus
};
#endif
//<<<+++OPENSOURCE_MUST_END

#if _FX_OS_ == _FX_PALMOS_ && _FX_COMPILER_ == _FX_PACC_
  #include <errtrycatch.h>
  #define setjmp ErrSetJump
  #define longjmp ErrLongJump
  #define jmp_buf ErrJumpBuf
#else
  #include <setjmp.h>
#endif

#if _FX_OS_ == _FX_MACOSX_
  #include <Carbon/Carbon.h>
#elif _FX_OS_ == _FX_IOS_
  #include <CoreText/CoreText.h>
  #include <CoreGraphics/CoreGraphics.h>
#endif
//<<<+++OPENSOURCE_MUST_END
//<<<+++OPENSOURCE_MUST_BEGIN
#endif  /* _FPDF_SYSTEM_H_ */
//<<<+++OPENSOURCE_MUST_END

/** @} */

//<<<+++OPENSOURCE_END
