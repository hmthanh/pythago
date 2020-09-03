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
 * @file fs_common.h
 * @brief Header file for common definitions and classes.
 */

#ifndef FS_COMMON_H_
#define FS_COMMON_H_

#include "common/fs_basictypes.h"
#include "common/file/fs_file.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
class ActionCallback;
namespace common {
class DocEventCallback;
class FontMapperCallback;
class Color;
}  // namespace common
namespace pdf {
namespace annots {
class IconProviderCallback;
}  // namespace annots
class PDFDoc;
class SignatureCallback;
class SecurityCallback;
}  // namespace pdf
namespace addon {
namespace xfa {
class AppProviderCallback;
}  // namespace xfa
}  // namespace addon

/**
 * @brief Common namespace.
 */
namespace common {
#if defined(_SWIG_ANDROID_) || defined(_SWIG_JAVA_)
/** This class contains definitions for constants. */
class Constants {
 public:
  /**
   * @brief Enumeration for rotation.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Rotation {
    /** @brief No rotation. */
    e_Rotation0 = 0,
    /** @brief Rotate 90 degrees in clockwise direction. */
    e_Rotation90 = 1,
    /** @brief Rotate 180 degrees in clockwise direction. */
    e_Rotation180 = 2,
    /** @brief Rotate 270 degrees in clockwise direction. */
    e_Rotation270 = 3,
    /** @brief Unknown rotation. */
    e_RotationUnknown = 4
  } Rotation;
  
  /**
   * @brief Enumeration for alignment (horizontal).
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Alignment {
    /** @brief Left alignment.*/
    e_AlignmentLeft = 0,
    /** @brief Center alignment.*/
    e_AlignmentCenter = 1,
    /** @brief Right alignment.*/
    e_AlignmentRight = 2
  } Alignment;
  
  /**
   * @brief Enumeration for filling mode type, mainly for path graphics object.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _FillMode {
    /** @brief Fill mode: none. */
    e_FillModeNone  = 0,
    /**
   @brief Alternate fill mode, in which the system fills this area between odd-numbered
          and even-numbered polygon sides on each scan line.
     */
    e_FillModeAlternate= 1,
    /**
   @brief Winding fill mode, in which the system uses a direction in which a figure is drawn to
          determine whether to fill an area.
     */
    e_FillModeWinding = 2
  } FillMode;
  
  /**
   * @brief Enumeration for watermark position in a PDF page.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Position {
    /** @brief Position: top left. */
    e_PosTopLeft = 0,
    /** @brief Position: top center. */
    e_PosTopCenter = 1,
    /** @brief Position: top right. */
    e_PosTopRight = 2,
    /** @brief Position center left. */
    e_PosCenterLeft = 3,
    /** @brief Position: center. */
    e_PosCenter = 4,
    /** @brief Position: center right. */
    e_PosCenterRight = 5,
    /** @brief Position: bottom left. */
    e_PosBottomLeft = 6,
    /** @brief Position: bottom center. */
    e_PosBottomCenter = 7,
    /** @brief Position: bottom right. */
    e_PosBottomRight = 8
  } Position;
  
  /**
   * @brief Enumeration for module name which is used in license information.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ModuleName {
    /** @brief (Reserved, currently, this module is not provided) Name for module "ConnectedPDF". */
    e_ModuleNameConnectedPDF = 1,
    /** @brief Name for module "XFA". */
    e_ModuleNameXFA = 2,
    /** @brief Name for module "Redaction". */
    e_ModuleNameRedaction = 3,
    /** @brief Name for module "RMS". */
    e_ModuleNameRMS = 4,
    /** @brief Name for module "OCR". */
    e_ModuleNameOCR = 5,
    /** @brief Name for module "Comparison". */
    e_ModuleNameComparison = 6,
    /** @brief Name for module "Compliance". */
    e_ModuleNameCompliance = 7,
    /** @brief Name for module "Optimizer". */
    e_ModuleNameOptimizer = 8,
    /** @brief Name for module "Conversion". */
    e_ModuleNameConversion = 9
  } ModuleName;
  
  /**
   * @brief Enumeration for color space.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ColorSpaceType {
    /** @brief Color space: Invalid. */
    e_ColorSpaceInvalid  = 0,
    /** @brief Color space: DeviceGray. (1 component, gray) */
    e_ColorSpaceDeviceGray = 1,
    /** @brief Color space: DeviceRGB. (3 components, R, G, B) */
    e_ColorSpaceDeviceRGB = 2,
    /** @brief Color space: DeviceCMYK. (4 components, C, M, Y, K) */
    e_ColorSpaceDeviceCMYK = 3,
    /** @brief Color space: CalGray. (1 component, A) */
    e_ColorSpaceCalGray = 4,
    /** @brief Color space: CalRGB. (3 components, A, B, C) */
    e_ColorSpaceCalRGB = 5,
    /** @brief Color space: Lab. (3 components, A, B, C)*/
    e_ColorSpaceLab = 6,
    /** @brief Color space: Separation. */
    e_ColorSpaceSeparation = 8,
    /** @brief Color space: DeviceN. */
    e_ColorSpaceDeviceN = 9,
    /** @brief Color space: Pattern. */
    e_ColorSpacePattern = 11,
    /** @brief Color space: ICCBased DeviceGray. (1 component, gray) */
    e_ColorSpaceICCBasedDeviceGray = 12,
    /** @brief Color space: ICCBased DeviceRGB. (3 components, R, G, B) */
    e_ColorSpaceICCBasedDeviceRGB = 13,
    /** @brief Color space: ICCBased DeviceCMYK. (4 components, C, M, Y, K) */
    e_ColorSpaceICCBasedDeviceCMYK = 14
  } ColorSpaceType;
  
};
#else
#if defined(__ANDROID__) || defined(_JAVA_)
/** This class contains definitions for constants. */
class Constants {
 public:
  /**
   * @brief Enumeration for rotation.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Rotation {
    /** @brief No rotation. */
    e_Rotation0 = 0,
    /** @brief Rotate 90 degrees in clockwise direction. */
    e_Rotation90 = 1,
    /** @brief Rotate 180 degrees in clockwise direction. */
    e_Rotation180 = 2,
    /** @brief Rotate 270 degrees in clockwise direction. */
    e_Rotation270 = 3,
    /** @brief Unknown rotation. */
    e_RotationUnknown = 4
  } Rotation;
  
  /**
   * @brief Enumeration for alignment (horizontal).
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Alignment {
    /** @brief Left alignment.*/
    e_AlignmentLeft = 0,
    /** @brief Center alignment.*/
    e_AlignmentCenter = 1,
    /** @brief Right alignment.*/
    e_AlignmentRight = 2
  } Alignment;
  
  /**
   * @brief Enumeration for filling mode type, mainly for path graphics object.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _FillMode {
    /** @brief Fill mode: none. */
    e_FillModeNone  = 0,
    /**
   @brief Alternate fill mode, in which the system fills this area between odd-numbered
          and even-numbered polygon sides on each scan line.
     */
    e_FillModeAlternate= 1,
    /**
   @brief Winding fill mode, in which the system uses a direction in which a figure is drawn to
          determine whether to fill an area.
     */
    e_FillModeWinding = 2
  } FillMode;
  
  /**
   * @brief Enumeration for watermark position in a PDF page.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Position {
    /** @brief Position: top left. */
    e_PosTopLeft = 0,
    /** @brief Position: top center. */
    e_PosTopCenter = 1,
    /** @brief Position: top right. */
    e_PosTopRight = 2,
    /** @brief Position center left. */
    e_PosCenterLeft = 3,
    /** @brief Position: center. */
    e_PosCenter = 4,
    /** @brief Position: center right. */
    e_PosCenterRight = 5,
    /** @brief Position: bottom left. */
    e_PosBottomLeft = 6,
    /** @brief Position: bottom center. */
    e_PosBottomCenter = 7,
    /** @brief Position: bottom right. */
    e_PosBottomRight = 8
  } Position;
  
  /**
   * @brief Enumeration for module name which is used in license information.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ModuleName {
    /** @brief (Reserved, currently, this module is not provided) Name for module "ConnectedPDF". */
    e_ModuleNameConnectedPDF = 1,
    /** @brief Name for module "XFA". */
    e_ModuleNameXFA = 2,
    /** @brief Name for module "Redaction". */
    e_ModuleNameRedaction = 3,
    /** @brief Name for module "RMS". */
    e_ModuleNameRMS = 4,
    /** @brief Name for module "OCR". */
    e_ModuleNameOCR = 5,
    /** @brief Name for module "Comparison". */
    e_ModuleNameComparison = 6,
    /** @brief Name for module "Compliance". */
    e_ModuleNameCompliance = 7,
    /** @brief Name for module "Optimizer". */
    e_ModuleNameOptimizer = 8,
    /** @brief Name for module "Conversion". */
    e_ModuleNameConversion = 9
  } ModuleName;
  
  /**
   * @brief Enumeration for color space.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ColorSpaceType {
    /** @brief Color space: Invalid. */
    e_ColorSpaceInvalid  = 0,
    /** @brief Color space: DeviceGray. (1 component, gray) */
    e_ColorSpaceDeviceGray = 1,
    /** @brief Color space: DeviceRGB. (3 components, R, G, B) */
    e_ColorSpaceDeviceRGB = 2,
    /** @brief Color space: DeviceCMYK. (4 components, C, M, Y, K) */
    e_ColorSpaceDeviceCMYK = 3,
    /** @brief Color space: CalGray. (1 component, A) */
    e_ColorSpaceCalGray = 4,
    /** @brief Color space: CalRGB. (3 components, A, B, C) */
    e_ColorSpaceCalRGB = 5,
    /** @brief Color space: Lab. (3 components, A, B, C)*/
    e_ColorSpaceLab = 6,
    /** @brief Color space: Separation. */
    e_ColorSpaceSeparation = 8,
    /** @brief Color space: DeviceN. */
    e_ColorSpaceDeviceN = 9,
    /** @brief Color space: Pattern. */
    e_ColorSpacePattern = 11,
    /** @brief Color space: ICCBased DeviceGray. (1 component, gray) */
    e_ColorSpaceICCBasedDeviceGray = 12,
    /** @brief Color space: ICCBased DeviceRGB. (3 components, R, G, B) */
    e_ColorSpaceICCBasedDeviceRGB = 13,
    /** @brief Color space: ICCBased DeviceCMYK. (4 components, C, M, Y, K) */
    e_ColorSpaceICCBasedDeviceCMYK = 14
  } ColorSpaceType;
  
};
#endif
/**
 * @brief Enumeration for rotation.
 *
 * @details Values of this enumeration should be used alone.
 */
typedef enum _Rotation {
  /** @brief No rotation. */
  e_Rotation0 = 0,
  /** @brief Rotate 90 degrees in clockwise direction. */
  e_Rotation90 = 1,
  /** @brief Rotate 180 degrees in clockwise direction. */
  e_Rotation180 = 2,
  /** @brief Rotate 270 degrees in clockwise direction. */
  e_Rotation270 = 3,
  /** @brief Unknown rotation. */
  e_RotationUnknown = 4
} Rotation;

/**
 * @brief Enumeration for alignment (horizontal).
 *
 * @details Values of this enumeration should be used alone.
 */
typedef enum _Alignment {
  /** @brief Left alignment.*/
  e_AlignmentLeft = 0,
  /** @brief Center alignment.*/
  e_AlignmentCenter = 1,
  /** @brief Right alignment.*/
  e_AlignmentRight = 2
} Alignment;

/**
 * @brief Enumeration for filling mode type, mainly for path graphics object.
 *
 * @details Values of this enumeration should be used alone.
 */
typedef enum _FillMode {
  /** @brief Fill mode: none. */
  e_FillModeNone  = 0,
  /**
 @brief Alternate fill mode, in which the system fills this area between odd-numbered
        and even-numbered polygon sides on each scan line.
   */
  e_FillModeAlternate= 1,
  /**
 @brief Winding fill mode, in which the system uses a direction in which a figure is drawn to
        determine whether to fill an area.
   */
  e_FillModeWinding = 2
} FillMode;

/**
 * @brief Enumeration for watermark position in a PDF page.
 *
 * @details Values of this enumeration should be used alone.
 */
typedef enum _Position {
  /** @brief Position: top left. */
  e_PosTopLeft = 0,
  /** @brief Position: top center. */
  e_PosTopCenter = 1,
  /** @brief Position: top right. */
  e_PosTopRight = 2,
  /** @brief Position center left. */
  e_PosCenterLeft = 3,
  /** @brief Position: center. */
  e_PosCenter = 4,
  /** @brief Position: center right. */
  e_PosCenterRight = 5,
  /** @brief Position: bottom left. */
  e_PosBottomLeft = 6,
  /** @brief Position: bottom center. */
  e_PosBottomCenter = 7,
  /** @brief Position: bottom right. */
  e_PosBottomRight = 8
} Position;

/**
 * @brief Enumeration for module name which is used in license information.
 *
 * @details Values of this enumeration should be used alone.
 */
typedef enum _ModuleName {
  /** @brief (Reserved, currently, this module is not provided) Name for module "ConnectedPDF". */
  e_ModuleNameConnectedPDF = 1,
  /** @brief Name for module "XFA". */
  e_ModuleNameXFA = 2,
  /** @brief Name for module "Redaction". */
  e_ModuleNameRedaction = 3,
  /** @brief Name for module "RMS". */
  e_ModuleNameRMS = 4,
  /** @brief Name for module "OCR". */
  e_ModuleNameOCR = 5,
  /** @brief Name for module "Comparison". */
  e_ModuleNameComparison = 6,
  /** @brief Name for module "Compliance". */
  e_ModuleNameCompliance = 7,
  /** @brief Name for module "Optimizer". */
  e_ModuleNameOptimizer = 8,
  /** @brief Name for module "Conversion". */
  e_ModuleNameConversion = 9
} ModuleName;

/**
 * @brief Enumeration for color space.
 *
 * @details Values of this enumeration should be used alone.
 */
typedef enum _ColorSpaceType {
  /** @brief Color space: Invalid. */
  e_ColorSpaceInvalid  = 0,
  /** @brief Color space: DeviceGray. (1 component, gray) */
  e_ColorSpaceDeviceGray = 1,
  /** @brief Color space: DeviceRGB. (3 components, R, G, B) */
  e_ColorSpaceDeviceRGB = 2,
  /** @brief Color space: DeviceCMYK. (4 components, C, M, Y, K) */
  e_ColorSpaceDeviceCMYK = 3,
  /** @brief Color space: CalGray. (1 component, A) */
  e_ColorSpaceCalGray = 4,
  /** @brief Color space: CalRGB. (3 components, A, B, C) */
  e_ColorSpaceCalRGB = 5,
  /** @brief Color space: Lab. (3 components, A, B, C)*/
  e_ColorSpaceLab = 6,
  /** @brief Color space: Separation. */
  e_ColorSpaceSeparation = 8,
  /** @brief Color space: DeviceN. */
  e_ColorSpaceDeviceN = 9,
  /** @brief Color space: Pattern. */
  e_ColorSpacePattern = 11,
  /** @brief Color space: ICCBased DeviceGray. (1 component, gray) */
  e_ColorSpaceICCBasedDeviceGray = 12,
  /** @brief Color space: ICCBased DeviceRGB. (3 components, R, G, B) */
  e_ColorSpaceICCBasedDeviceRGB = 13,
  /** @brief Color space: ICCBased DeviceCMYK. (4 components, C, M, Y, K) */
  e_ColorSpaceICCBasedDeviceCMYK = 14
} ColorSpaceType;

#endif

#define CommonDefines foxit::common

/**
 * This class provides utility functions such as encoding or compression.
 * Foxit PDF SDK library should has been initialized successfully by function @link Library::Initialize @endlink
 * before calling any function of this class.
 */
class Codec FS_FINAL : public Base {
 public:
  /**
   * @brief Encode the source data buffer by Base64 algorithm.
   *
   * @param[in] data_buffer  The raw source data buffer.
   * @param[in] length       The length of data buffer in byte.
   *
   * @return The encoded data.
   */
  static String Base64Encode(const void* data_buffer, size_t length);

  /**
   * @brief Decode the encoded data buffer by Base64 algorithm.
   *
   * @param[in] encoded_data_buffer  The encoded source data buffer.
   * @param[in] length               The length of data buffer in byte.
   *
   * @return The decoded data.
   */
  static String Base64Decode(const void* encoded_data_buffer, size_t length);

  /**
   * @brief Compress the source data buffer by DEFLATE algorithm.
   *
   * @param[in] data_buffer  The raw source data buffer.
   * @param[in] length       The length of data buffer in byte.
   *
   * @return The compressed data.
   */
  static String FlateCompress(const void* data_buffer, size_t length);

  /**
   * @brief Decompress the compressed data buffer by DEFLATE algorithm.
   *
   * @param[in] compressed_data_buffer  The compressed source data buffer.
   * @param[in] length                  The length of data buffer in byte.
   *
   * @return The decompressed data.
   */
  static String FlateDecompress(const void* compressed_data_buffer, size_t length);
};

/**
 * This class represents a callback object to notify the Foxit PDF SDK events.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 * An implemented @link NotifierCallback @endlink object can be set to Foxit PDF SDK by
 * function @link Library::SetNotifierCallback @endlink.
 *
 * @see @link Library @endlink
 */
class NotifierCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function used to notify application when Foxit PDF SDK runs out of memory.
   *
   * @details When this callback function is triggered, that means Foxit PDF SDK runs out of memory.
   *          At this moment, application cannot use any API in Foxit PDF SDK.
   *          In this case, application can exit with some warning information,
   *          or application is aborted and tried to restart.
   *          Here, "restart an application" does not mean to call function @link Library::Reinitialize @endlink
   *          but to call function @link Library::Initialize @endlink again to load Foxit PDF SDK again from the beginning.
   *
   * @return None.
   */
  virtual void OnOutOfMemory() = 0;

 protected:
  ~NotifierCallback() {}
};

/**
 * This class represents a progressive object, which is used for progressive process such as loading document,
 * parsing page and so on.
 */
class Progressive FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for progress state.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _State {
    /** @brief Progress state: any error occurs. */
    e_Error = 0,
    /** @brief Progress state: progress needs to be continued. */
    e_ToBeContinued = 1,
    /** @brief Progress state: progress is finished. */
    e_Finished = 2
  } State;
  
  /**
   * @brief Constructor, with another progressive object.
   *
   * @param[in] other  Another progressive object.
   */
  Progressive(const Progressive& other);
  /** @brief Destructor. */
  ~Progressive();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another progressive object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Progressive& operator = (const Progressive& other);

  /**
   * @brief Continue the progressive process.
   *
   * @return @link Progressive::e_Finished @endlink means current process is finished successfully.<br>
   *         @link Progressive::e_ToBeContinued @endlink means current process is suspended,
   *         and this function needs to be called again to continue the process.<br>
   *         @link Progressive::e_Error @endlink means any error occurs.
   */
  State Continue();

  /**
   * @brief Get the rate of current progress.
   *
   * @return An integer between 0 and 100 (inclusive), indicating the rate of current progress.
   *         -1 means error.
   */
  int GetRateOfProgress();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Progressive(FS_HANDLE handle = NULL);
};

/**
 * This class represents the library management.
 * It contains functions to initialize/re-initialize/release Foxit PDF SDK library, and also contains functions
 * for global use.<br>
 * Any application should load Foxit PDF SDK by function @link Library::Initialize @endlink before calling any other
 * Foxit PDF SDK functions. When there is no need to use Foxit PDF SDK any more, please call
 * function @link Library::Release @endlink.
 * Functions in Foxit PDF SDK may throw exception when some error occurs. User can catch these exceptions and
 * check the error code with values starting from @link foxit::e_ErrFile @endlink to know more about what error occurs.
 */
class Library FS_FINAL : public Object {
 public:
  /**
   * @brief Initialize Foxit PDF SDK Library, with valid license information.
   *
   * @details This function should be called first before any other functions in Foxit PDF SDK can be called.
   *
   * @param[in] sn   String of sn information, which can be retrieved from "SN=" part in key file "gsdk_sn.txt" or "rdk_sn.txt".
   * @param[in] key  String of key information, which can be retrieved from "Sign=" part in key file "gsdk_key.txt" or "rdk_key.txt".
   *
   * @return @link foxit::e_ErrSuccess @endlink means success.<br>
   *         @link foxit::e_ErrInvalidLicense @endlink means input license information is invalid.<br>
   *         @link foxit::e_ErrParam @endlink means parameter <i>sn</i> or <i>key</i> is an empty string.<br>
   *         For more information about error code values, please refer to values starting from @link foxit::e_ErrSuccess @endlink.
   */
  static ErrorCode Initialize(const char* sn, const char* key);

  /**
   * @brief Reinitialize Foxit PDF SDK Library.
   *
   * @details When user meets out-of-memory error, user can call this function to reinitialize Foxit PDF SDK Library.
   *
   * @return @link foxit::e_ErrSuccess @endlink means success.
   *         For more information about error code values, please refer to values starting from @link foxit::e_ErrSuccess @endlink.
   */
  static ErrorCode Reinitialize();

  /**
   * @brief Release all resource allocated by Foxit PDF SDK Library.
   *
   * @details User can call this function to release all memory blocks allocated by the library.
   *          After this function is called, user should not use Foxit PDF SDK any more
   *          until call @link Library::Initialize @endlink again.
   *
   * @return None.
   */
  static void Release();

  /**
   * @brief Check if user has right to use a specified module of Foxit PDF SDK in current used license information
   *        (which is used to initialize Foxit PDF SDK).
   *
   * @details In Foxit PDF SDK, once the library is initialized successfully, most feature can be used.
   *          But for some special features, they can be used only when specified modules are defined in license information.
   *          This function can be used to check if user has right for these special modules before using these feature.
   *
   * @param[in] module_name  Name of the module whose right is to be checked. Please refer to values starting
   *                         from @link common::e_ModuleNameConnectedPDF @endlink and this should be one of these values.
   *
   * @return <b>true</b> means user has right to use the specified module, while <b>false</b> means user does not
   *         have right to use the specified module.
   */
  static bool HasModuleLicenseRight(common::ModuleName module_name);

  /**
   * @brief Get the version of current Foxit PDF SDK library.
   *
   * @return Version string.
   */
  static String GetVersion();

  /**
   * @brief Set the upper limit of PDF library cache size.
   *
   * @details If no cache size limit is set by application, the cache size will be set to 200 MegaBytes
   *          internally by default.
   *
   * @param[in] size  The upper limit of the cache, in MegaBytes, 0~4096.
   *                  If set to 0, that means not to use limit of cache size.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool SetCacheSize(uint32 size);

  /**
   * @brief Enable or disable javascript for PDF.
   *
   * @details Javascript for PDF is enabled by default.
   *
   * @param[in] enable_javascript  <b>true</b> means to enable javascript, and <b>false</b> means to
   *                               disable javascript.
   *                               If this function is not called, javascript for PDF is enabled by default.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool EnableJavaScript(bool enable_javascript);

#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Set a customized @link pdf::annots::IconProviderCallback @endlink object to Foxit PDF SDK.
   *
   * @details User can call this function to set a customized icon provider for annotation.
   *          If this function has been called several times, Foxit PDF SDK will only keep the last icon provider.
   *          If this function has not been called even once, Foxit PDF SDK will use the default standard icon provider.
   *
   * @param[in] annot_icon_provider  A customized annotation icon provider,
   *                                 which is implemented based on callback class @link pdf::annots::IconProviderCallback @endlink.
   *                                 If this is <b>NULL</b>, customized annotation icon provider
   *                                 will be removed from Foxit PDF SDK and default standard icon provider
   *                                 will be used instead. Application should ensure this icon provider object valid
   *                                 until it has been removed from Foxit PDF SDK or function
   *                                 @link Library::Release @endlink is called.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note Icon provider's ID and version are treated as the name of the icon provider,
   *       so please offer different "ID + version" for different icon providers
   *       by callback functions @link pdf::annots::IconProviderCallback::GetProviderID @endlink
   *       and @link pdf::annots::IconProviderCallback::GetProviderVersion @endlink.
   */
  static bool SetAnnotIconProviderCallback(pdf::annots::IconProviderCallback* annot_icon_provider);
#endif
  /**
   * @brief Set a @link NotifierCallback @endlink object to Foxit PDF SDK.
   *
   * @details User can call this function to set a notifier callback object to Foxit PDF SDK,
   *          so that when events (such as OOM) happens, user would be notified.
   *
   * @param[in] notifier  A @link NotifierCallback @endlink object. User should ensure all the callback functions
   *                      have been implemented in application level.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool SetNotifierCallback(NotifierCallback* notifier);

  /**
   * @brief Set a @link foxit::ActionCallback @endlink object to Foxit PDF SDK, in aid of performing PDF actions.
   *
   * @details User should implement an action callback object and call this function to set the action callback object
   *          to Foxit PDF SDK if PDF actions need to be performed, such as filling a PDF form.
   *
   * @param[in] action_callback  A customized @link foxit::ActionCallback @endlink object. <b>NULL</b> means not use
   *                             any action callback object. User should ensure all the callback functions have been
   *                             implemented in application level. If this is a valid action callback object,
   *                             Foxit PDF SDK will take over the management of this callback object and
   *                             user should not release it directly.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool SetActionCallback(ActionCallback* action_callback);

  /**
   * @brief Set a @link DocEventCallback @endlink object to Foxit PDF SDK.
   *
   * @param[in] callback  A @link DocEventCallback @endlink object.
   *                      <b>NULL</b> means not use any document event callback object.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool SetDocEventCallback(DocEventCallback* callback);

  /**
   * @brief Register a third-party @link pdf::SignatureCallback @endlink object to Foxit PDF SDK for signing and verifying signature,
   *        along with the filter and sub filter name of the callback.
   *
   * @details Foxit PDF SDK has default signature callbacks defined with filter and sub filter:
   *          <ul>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "adbe.pkcs7.sha1"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.CAdES.detached"</li>
   *          <li>filter: "Adobe.PPKLite" and sub filter: "ETSI.RFC3161"</li>
   *          </ul>
   *          If user wants to use a third-party signature callback, please call this function before signing or
   *          verifying signature process.<br>
   *          If user register a customized signature callback with the same filter and filter as default ones
   *          by this function, the default signature callback in Foxit PDF SDK will not have any effect any more.
   *
   * @param[in] filter              The filter name of the signature callback, in ASCII encoding.
   *                                This should not be an empty string.
   *                                Filter name is the name of the signature callback.
   * @param[in] sub_filter          The sub filter name of the signature callback, in ASCII encoding.
   *                                Sub filter is to describe the encoding of signature value and
   *                                key information in the signature dictionary.
   * @param[in] signature_callback  A customized @link pdf::SignatureCallback @endlink object, which is implemented by user
   *                                and based on callback class @link pdf::SignatureCallback @endlink.
   *                                User should ensure all the callback functions have been implemented
   *                                in application level and should also ensure this signature callback object valid
   *                                until Foxit PDF SDK is released by function @link Library::Release @endlink.<br>
   *                                If this is <b>NULL</b>, that means the registered third-party callback is to
   *                                be removed from Foxit PDF SDK.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool RegisterSignatureCallback(const char* filter, const char* sub_filter,
                                        pdf::SignatureCallback* signature_callback);

  /**
   * @brief Register a @link pdf::SecurityCallback @endlink object to Foxit PDF SDK for decryption of the PDFs with special encryption filters.
   *
   * @details When this function is successful, Foxit PDF SDK will take over the input security callback object
   *          and user should not release this callback object directly anymore;
   *          otherwise unexpected crash may occurs later.<br>
   *          Foxit PDF SDK may release the security callback object by callback function
   *          @link pdf::SecurityCallback::Release @endlink, when unregister it and find that it has not been used
   *          by other object. So, user is recommended not to use the security callback object any more
   *          after function @link Library::UnregisterSecurityCallback @endlink.
   *
   * @param[in] filter    The filter name of the security callback object. This should not be <b>NULL</b> or
   *                      an empty string.<br>
   *                      When users implement security callback of @link  pdf::CustomSecurityCallback @endlink,
   *                      users could specified their own custom filter string,
   *                      but need to follow the PDF name conventions.<br>
   *                      When users implement security callback of @link pdf::CertificateSecurityCallback @endlink,
   *                      the filter value must be set to "Adobe.PubSec".<br>
   *                      When users implement security callback of @link  pdf::DRMSecurityCallback @endlink,
   *                      the filter value must be set to "FoxitDRM", or some error may occur later.<br>
   *                      When users implement security callback of @link pdf::RMSSecurityCallback @endlink,
   *                      the filter value must be set to "MicrosoftIRMServices", or some error may occur later.
   * @param[in] callback  A @link pdf::SecurityCallback @endlink object, which is implemented by user and based on
   *                      callback class @link pdf::SecurityCallback @endlink. User should not inherit
   *                      @link pdf::SecurityCallback @endlink directly, but inherit its derived class,
   *                      such as @link pdf::CustomSecurityCallback @endlink, @link pdf::CertificateSecurityCallback @endlink,
   *                      etc.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note If module "RMS" is not defined in the license information which is used in function
   *       @link Library::Initialize @endlink, that means user has no right in using RMS related functions and
   *       this function will throw exception @link foxit::e_ErrNoRMSModuleRight @endlink.
   */
  static bool RegisterSecurityCallback(const char* filter, pdf::SecurityCallback* callback);

  /**
   * @brief Unregister a @link pdf::SecurityCallback @endlink object from Foxit PDF SDK.
   *
   * @details Foxit PDF SDK may release the security callback function by callback function
   *          @link pdf::SecurityCallback::Release @endlink, when unregister it and find that
   *          it has not been used by other object. So, user is recommended not to use the security callback object
   *          any more after function @link Library::UnregisterSecurityCallback @endlink.
   *
   * @param[in] filter  The filter name which is used for registering a security callback object.
   *                    Please refer to comment of parameter <i>filter</i> in function
   *                    @link Library::RegisterSecurityCallback @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note If module "RMS" is not defined in the license information which is used in function
   *       @link Library::Initialize @endlink, that means user has no right in using RMS related functions and
   *       this function will throw exception @link foxit::e_ErrNoRMSModuleRight @endlink.
   */
  static bool UnregisterSecurityCallback(const char* filter);

  #if defined(__ANDROID__) || defined(FS_IOS_) || defined(_SWIG_ANDROID_) || defined(_SWIG_IOS_)
  /**
   * @brief Check that whether the Foxit PDF SDK works on the FIPS mode(Federal Information Processing Standard).
   *        FIPS mode support requires a special build from Foxit.
   *
   * @return <b>true</b> means the Foxit PDF SDK works on the FIPS mode(Federal Information Processing Standard),
   *         while <b>false</b> means the Foxit PDF SDK does not work on the FIPS mode(Federal Information Processing
   * Standard).
   */
  static bool IsFipsMode();
  #endif

  #ifndef _FX_NO_XFA_
  /**
   * @brief Register an @link addon::xfa::AppProviderCallback @endlink object to Foxit PDF SDK.
   *
   * @details This function should be called first before processing XFA document.
   *
   * @param[in] callback  An @link addon::xfa::AppProviderCallback @endlink object, which is implemented by user
   *                      and based on callback class @link addon::xfa::AppProviderCallback @endlink.
   *                      User should ensure all the callback functions have been implemented in application level
   *                      and should also ensure this XFA application provider callback object valid
   *                      until Foxit PDF SDK is released by function @link Library::Release @endlink.
   *
   * @return None.
   *
   * @note If module "XFA" is not defined in the license information which is used in function
   *       @link Library::Initialize @endlink, that means user has no right in using XFA related functions and
   *       this function will throw exception @link foxit::e_ErrNoXFAModuleRight @endlink.
   */
  static void RegisterXFAAppProviderCallback(addon::xfa::AppProviderCallback* callback);
  #endif

  /**
   * @brief Set gamma value for text rendering.
   *
   * @details If this function is not called to set gamma value, Foxit PDF SDK will use 2.2 as the default value.
   *
   * @param[in] gamma  Gamma value. It should be greater than 0.
   *
   * @return None.
   */
  static void SetRenderTextGamma(float gamma);

  /**
   * @brief Allocate a memory block
   *
   * @details When the memory block is not used any more, please remember to call function
   *          @link Library::Free @endlink to free the memory block.
   *
   * @param[in] size  The number of bytes to be allocated.
   *
   * @return Pointer to the allocated memory block.
   */
  static void* Alloc(size_t size);

  /**
   * @brief Free a memory block
   *
   * @param[in] ptr  Pointer to a memory block allocated by function @link Library::Alloc @endlink to be released.
   *
   * @return None.
   */
  static void Free(void* ptr);

  /**
   * @brief Reallocate a memory block.
   *
   * @details If the param <i>ptr</i> is <b>NULL</b>, this function will allocate a new memory block.
   *
   * @param[in] ptr       Pointer to a memory block which is allocated by @link Library::Alloc @endlink and
   *                      now is to be reallocated. <b>NULL</b> means this function will allocate a new memory block.
   * @param[in] new_size  New size of memory block in bytes.
   *
   * @return Pointer to a new reallocated memory block.
   */
  static void* Realloc(void* ptr, size_t new_size);

  /**
   * @brief Set the log file path.
   *
   * @details After a log file path is set to Foxit PDF SDK, all the logs will be written to the log file.
   *          Currently, the log information in Foxit PDF SDK is simple; this will be improved in future version.
   *
   * @param[in] log_file_path  A log file path.
   *
   * @return None.
   */
  static void SetLogFile(const char* log_file_path);

  /**
   * @brief Set the log file path.
   *
   * @details After a log file path is set to Foxit PDF SDK, all the logs will be written to the log file.
   *          Currently, the log information in Foxit PDF SDK is simple; this will be improved in future version.
   *
   * @param[in] log_file_path  A log file path.
   *
   * @return None.
   */
  static void SetLogFile(const wchar_t* log_file_path);

  /**
   * @brief Set a @link FontMapperCallback @endlink object to Foxit PDF SDK.
   *
   * @details Once a valid custom font mapper callback is set to Foxit PDF SDK, Foxit PDF SDK will first
   *          use this callback when mapping a font.
   *
   * @param[in] callback  A @link FontMapperCallback @endlink object.
   *                      <b>NULL</b> means not use any custom font mapper callback object.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool SetFontMapperCallback(FontMapperCallback* callback);

 private:
  Library(const Library&);
  Library& operator = (const Library&);
};
/** This class represents PDF graph states. */
class GraphState FS_FINAL : public Object {
 public:
  /**
   * @brief Enumeration for line cap style.
   *
   * @details Values of this enumeration should be used alone. The line cap style specifies the shape to be
   *          used at the ends of open sub paths (and dashes, if any) when they are stroked.
   */
  typedef enum _LineCapStyle {
    /**
     * @brief Butt cap. The stroke is squared off at the endpoint of a path. There is no projection
     *        beyond the end of a path.
     */
    e_LineCapButt  = 0,
    /**
   @brief Round cap. A semicircular arc with a diameter equal to the line width is drawn
          around the endpoint and filled in.
     */
    e_LineCapRound= 1,
    /**
   @brief Projecting square cap. The stroke continues beyond the endpoint of the path for a distance equal to
          half the line width and is squared off.
     */
    e_LineCapSquare = 2
  } LineCapStyle;
  
  /**
   * @brief Enumeration for line join style.
   * 
   * @details Values of this enumeration should be used alone.
   *         The line join style specifies the shape to be used at the corners of paths that are stroked.
   */
  typedef enum _LineJoinStyle {
    /**
   @brief Miter line join type.
   @details The outer edges of the strokes for the two segments are extended until they meet at an angle.
     */
    e_LineJoinMiter = 0,
    /**
   @brief Round line join type.
   @details An arc of a circle with a diameter equal to the line width is drawn around the point
     *          where the two segments meet, connecting the outer edges of the strokes for the two segments.
     */
    e_LineJoinRound = 1,
    /**
   @brief Bevel line join type.
   @details The two segments are finished with butt caps and the resulting notch
            beyond the end of the segments is filled with a triangle.
     */
    e_LineJoinBevel = 2
  } LineJoinStyle;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] line_width   Line width. If 0 is set to this, it will be treated as 1 by default.
   * @param[in] line_join    Line join style. Please refer to values starting from @link GraphState::e_LineJoinMiter @endlink
   *                         and this should be one of these values.
   * @param[in] miter_limit  The miter limit for line join.
   * @param[in] line_cap     Line cap style. Please refer to values starting from @link GraphState::e_LineCapButt @endlink
   *                         and this should be one of these values.
   * @param[in] dash_phase   Dash phase for line dash pattern.
   * @param[in] dashes       A dash array that represents the dash patterns. The value of each element in this array
   *                         should not be negative.
   */
  GraphState(float line_width, LineJoinStyle line_join, float miter_limit,
             LineCapStyle line_cap, float dash_phase, const FloatArray& dashes) {
    this->line_width = line_width;
    this->line_join = line_join;
    this->miter_limit = miter_limit;
    this->line_cap = line_cap;
    this->dash_phase = dash_phase;
    this->dashes = dashes;
  }

  /** @brief Constructor. */
  GraphState()
      : line_width(1.0f)
      , line_join(e_LineJoinMiter)
      , miter_limit(10*1.0f)
      , line_cap(e_LineCapButt)
      , dash_phase(0) {}

  /** @brief Destructor. */
  ~GraphState() {}

  /**
   * @brief Constructor, with another graph state object.
   *
   * @param[in] state  Another graph state object.
   */
  GraphState(const GraphState& state) {
    this->line_width = state.line_width;
    this->line_join = state.line_join;
    this->miter_limit = state.miter_limit;
    this->line_cap = state.line_cap;
    this->dash_phase = state.dash_phase;
    this->dashes = state.dashes;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] state  Another graph state object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  GraphState& operator = (const GraphState& state) {
    this->line_width = state.line_width;
    this->line_join = state.line_join;
    this->miter_limit = state.miter_limit;
    this->line_cap = state.line_cap;
    this->dash_phase = state.dash_phase;
    this->dashes = state.dashes;
    return *this;
  }

  /**
   * @brief Set value.
   *
   * @param[in] line_width   Line width. If 0 is set to this, it will be treated as 1 by default.
   * @param[in] line_join    Line join style. Please refer to values starting from @link GraphState::e_LineJoinMiter @endlink
   *                         and this should be one of these values.
   * @param[in] miter_limit  The miter limit for line join.
   * @param[in] line_cap     Line cap style. Please refer to values starting from @link GraphState::e_LineCapButt @endlink
   *                         and this should be one of these values.
   * @param[in] dash_phase   Dash phase for line dash pattern.
   * @param[in] dashes       A dash array that represents the dash patterns. The value of each element in this array
   *                         should not be negative.
   *
   * @return None.
   */
  void Set(float line_width, LineJoinStyle line_join, float miter_limit, LineCapStyle line_cap, float dash_phase,
           const FloatArray& dashes) {
    this->line_width = line_width;
    this->line_join = line_join;
    this->miter_limit = miter_limit;
    this->line_cap = line_cap;
    this->dash_phase = dash_phase;
    this->dashes = dashes;
  }

  /**
   * @brief Line width.
   *
   * @details It should be a non-negative number in [PDF coordinate system] (@ref pdf::PDFPage).
   *          If 0 is set to this, it will be treated as 1 by default.
   */
  float line_width;
  /**
   * @brief Line join style
   *
   * @details The line join style specifies the shape to be used at the corners of paths that are stroked.
   *          Please refer to values starting from @link GraphState::e_LineJoinMiter @endlink and
   *          this should be one of these values.
   */
  LineJoinStyle line_join;
  /**
   * @brief The miter limit for line join.
   *
   * @details When two line segments meet at a sharp angle and mitered joins have been specified
   *          as the line join style, it is possible for the miter to extend far beyond the thickness of
   *          the line stroking the path. The miter limit imposes a maximum on the ratio of the miter length
   *          to the line width. When the limit is exceeded, the join is converted from a miter to a bevel.<br>
   *          Please refer to <PDF Reference 1.7> P217 "Miter Limit" for more details.
   */
  float miter_limit;
  /**
   * @brief Line cap style.
   *
   * @details The line cap style specifies the shape to be used at the ends of open sub-paths (and dashes, if any)
   *          when they are stroked. Please refer to values starting from @link GraphState::e_LineCapButt @endlink and
   *          this should be one of these values.
   */
  LineCapStyle line_cap;

  /** @brief Dash phase for dash pattern.*/
  float dash_phase;

  /**
   * @brief A dash array that represents the dash patterns. Value of each element in this array should not be negative.
   */
  FloatArray dashes;
};

/**
 * This class represents a callback object used for pausing during a progressive process.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user
 * to do pausing in a customized way.
 */
typedef IFX_Pause PauseCallback;

/**
 * This class represents a callback object used to listen PDF document event.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user
 * in derived class. User can also re-write the virtual functions in this class in custom way.
 */
class DocEventCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

 /**
  * @brief Triggered when the document will be opened.
  *
  * @return None.
  */
  virtual void OnDocWillOpen() {}

 /**
  * @brief Triggered when a PDF document is opened.
  *
  * @param[in] document    A PDF document object which is opened.
  * @param[in] error_code  Error code which represents the error state when opening the PDF document.
  *                        Please refer to values starting from @link foxit::e_ErrSuccess @endlink and 
  *                        this would be one of these values.
  *
  * @return None.
  */
  virtual void OnDocOpened(const pdf::PDFDoc& document, ErrorCode error_code) {}

 /**
  * @brief Triggered when a PDF document will be destroyed.
  *
  * @param[in] document  A PDF document object which will be destroyed.
  *
  * @return None.
  */
  virtual void OnDocWillDestroy(const pdf::PDFDoc& document) {}

 /**
  * @brief Triggered when a PDF document will be saved.
  *
  * @param[in] document  A PDF document object which will be saved.
  *
  * @return None.
  */
  virtual void OnDocWillSave(const pdf::PDFDoc& document) {}

 /**
  * @brief Triggered when a PDF document is saved.
  *
  * @param[in] document    A PDF document object which is saved.
  * @param[in] error_code  Error code which represents the error state when saving the PDF document.
  *                        Please refer to values starting from @link foxit::e_ErrSuccess @endlink and 
  *                        this would be one of these values.
  *
  * @return None.
  */
  virtual void OnDocSaved(const pdf::PDFDoc& document, ErrorCode error_code) {}

 protected:
  ~DocEventCallback() {}
};

/**
 * This class represents index range. Here, a range consists of one or more segments and each segment consists of
 * one single index or a group of consecutive indexes.<br>
 * For some special case, such as used in @link pdf::HeaderFooter @endlink, index values specified in this range represent page numbers directly instead of page indexes.
 *
 * @see @link pdf::HeaderFooter @endlink
 */
class Range FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for range filter.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Filter {
    /** @brief All the indexes within a range will be used. */
    e_All = 0,
    /** @brief Only even numbers in a range will be used (discards odd numbers). */
    e_Even = 1,
    /** @brief Only odd numbers in a range will be used (discards even numbers). */
    e_Odd = 2
  } Filter;
  
  /** @brief Constructor. */
  Range();

  /**
   * @brief Constructor, with a single index.
   *
   * @param[in] index  A single index.
   */
  explicit Range(int index);

  /**
   * @brief Constructor, with a specified index range.
   *
   * @param[in] start_index  The start index of a range segment.
   * @param[in] end_index    The end index of a range segment.
   * @param[in] filter       Filter type to decide which indexes of this range would be used. Please refer to values
   *                         starting from @link Range::e_All @endlink and this should be one of these values.
   *                         Default value: @link Range::e_All @endlink.<br>
   *                         Specially, when this value is @link Range::e_Even @endlink or @link Range::e_Odd @endlink,
   *                         that means each even or odd number within the specified range segment will
   *                         be treated as a single segment.
   */
  explicit Range(int start_index, int end_index, Filter filter = e_All);

  /**
   * @brief Constructor, with another range object.
   *
   * @param[in] other  Another range object.
   */
  Range(const Range& other);

  /** @brief Destructor. */
  ~Range();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another range object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Range& operator = (const Range& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another range object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Range& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another range object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Range& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Add an index as a new range segment.
   *
   * @param[in] index  An index to be added as a new range segment.
   */
  void AddSingle( int index );

  /**
   * @brief Add a new range segment. (Reverse ordering is legal.)
   *
   * @param[in] start_index  The start index of a new range segment.
   * @param[in] end_index    The end index of a new range segment.
   * @param[in] filter       Filter type to decide which indexes of this range would be used. Please refer to values
   *                         starting from @link Range::e_All @endlink and this should be one of these values.
   *                         Default value: @link Range::e_All @endlink.<br>
   *                         Specially, when this value is @link Range::e_Even @endlink or @link Range::e_Odd @endlink,
   *                         that means each even or odd number within the specified range segment will
   *                         be treated as a single segment.
   *
   * @return None.
   */
  void AddSegment( int start_index, int end_index, Filter filter = e_All );

  /**
   * @brief Get the count of range segments.
   *
   * @return The count of range segments.
   */
  int GetSegmentCount() const;

  /**
   * @brief Get the start index of a specified range segment.
   *
   * @param[in] segment_index  The segment index. Valid range: 0 to (<i>count</i>-1).
   *                           <i>count</i> is returned by function @link Range::GetSegmentCount @endlink.
   *
   * @return The start index of a specified range segment.
   */
  int GetSegmentStart(int segment_index) const;

  /**
   * @brief Get the end index of a specified range segment.
   *
   * @param[in] segment_index  The segment index. Valid range: 0 to (<i>count</i>-1).
   *                           <i>count</i> is returned by function @link Range::GetSegmentCount @endlink.
   *
   * @return The end index of a specified range segment.
   */
  int GetSegmentEnd(int segment_index) const;

  /**
   * @brief Remove all range segments.
   *
   * @return None.
   */
  void RemoveAll();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Range(FS_HANDLE handle);
};

/**
 * In PDF document, font is used for drawing text in PDF page.<br>
 * This class represents font used in Foxit PDF SDK. This class offers different constructor for user to construct
 * a new font object, by specified parameters, by standard font ID, or from a font file path.
 * A font object can also be retrieved directly from other object (such as free text annotation,
 * a text graphics object, etc) in a PDF document.
 * This class also offers some functions to get some basic information from a font.
 */
class Font FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for font styles.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _Styles {
    /** @brief Font style: fixed pitch. */
    e_StyleFixedPitch = 0x0001,
    /** @brief Font style: serif. */
    e_StyleSerif = 0x0002,
    /** @brief Font style: symbolic. */
    e_StyleSymbolic = 0x0004,
    /** @brief Font style: script. */
    e_StyleScript = 0x0008,
    /** @brief Font style: non-symbolic. */
    e_StyleNonSymbolic = 0x0020,
    /** @brief Font style: italic. */
    e_StyleItalic = 0x0040,
    /** @brief Font style: all cap. */
    e_StyleAllCap = 0x10000,
    /** @brief Font style: small cap. */
    e_StylesSmallCap = 0x20000,
    /** @brief Font style: force bold. */
    e_StylesBold = 0x40000
  } Styles;
  
  /**
   * @brief Enumeration for font charset.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Charset {
    /** @brief Font charset: ANSI (United States, Western Europe). */
    e_CharsetANSI = 0,
    /** @brief Font charset: System default, for unknown or mapping purpose. */
    e_CharsetDefault = 1,
    /** @brief Font charset: Standard symbols. */
    e_CharsetSymbol = 2,
    /** @brief Font charset: Japanese (Shift-JIS). */
    e_CharsetShift_JIS = 128,
    /** @brief Font charset: Korean (Wansung). */
    e_CharsetHangeul = 129,
    /** @brief Font charset: Simplified Chinese. */
    e_CharsetGB2312 = 134,
    /** @brief Font charset: Traditional Chinese. */
    e_CharsetChineseBig5 = 136,
    /** @brief Font charset: Thai. */
    e_CharsetThai = 222,
    /** @brief Font charset: Eastern European. */
    e_CharsetEastEurope = 238,
    /** @brief Font charset: Russian. */
    e_CharsetRussian = 204,
    /** @brief Font charset: Greek. */
    e_CharsetGreek = 161,
    /** @brief Font charset: Turkish. */
    e_CharsetTurkish = 162,
    /** @brief Font charset: Hebrew. */
    e_CharsetHebrew = 177,
    /** @brief Font charset: Arabic. */
    e_CharsetArabic = 178,
    /** @brief Font charset: Baltic. */
    e_CharsetBaltic = 186
  } Charset;
  
  /**
  * @brief Enumeration for CID font charset.
  *
  * @details Values of this enumeration should be used alone.
  */
  typedef enum _CIDCharset {
    /** @brief CID Font charset: Unknown. */
    e_CIDCharsetUnknown = 0,
    /** @brief CID Font charset: Adobe-GB1. */
    e_CIDCharsetGB1 = 1,
    /** @brief CID Font charset: Adobe-CNS1. */
    e_CIDCharsetCNS1 = 2,
    /** @brief CID Font charset: Adobe-Japan1. */
    e_CIDCharsetJAPAN1 = 3,
    /** @brief CID Font charset: Adobe-Korea1. */
    e_CIDCharsetKOREA1 = 4,
    /** @brief CID Font charset: Unicode. */
    e_CIDCharsetUNICODE = 5
  } CIDCharset;
  
  /**
   * @brief Enumeration for standard font ID.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _StandardID {
    /** @brief Standard font: Courier. */
    e_StdIDCourier = 0,
    /** @brief Standard font: Courier-Bold. */
    e_StdIDCourierB = 1,
    /** @brief Standard font: Courier-BoldOblique, Bold italic. */
    e_StdIDCourierBI = 2,
    /** @brief Standard font: Courier-Oblique, Italic. */
    e_StdIDCourierI = 3,
    /** @brief Standard font: Helvetica. */
    e_StdIDHelvetica = 4,
    /** @brief Standard font: Helvetica-Bold. */
    e_StdIDHelveticaB = 5,
    /** @brief Standard font: Helvetica-BoldOblique, Bold italic. */
    e_StdIDHelveticaBI = 6,
    /** @brief Standard font: Helvetica-Oblique, Italic. */
    e_StdIDHelveticaI = 7,
    /** @brief Standard font: Times-Roman. */
    e_StdIDTimes = 8,
    /** @brief Standard font: Times-Bold. */
    e_StdIDTimesB = 9,
    /** @brief Standard font: Times-BoldItalic. */
    e_StdIDTimesBI = 10,
    /** @brief Standard font: Times-Italic. */
    e_StdIDTimesI = 11,
    /** @brief Standard font: Symbol. */
    e_StdIDSymbol = 12,
    /** @brief Standard font: ZapfDingbats. */
    e_StdIDZapfDingbats = 13
  } StandardID;
  
  /**
  * @brief Enumeration for font type.
  *
  * @details Values of this enumeration can be used alone .
  */
  typedef enum _FontTypes {
    /** @brief Font type: Type1. */
    e_FontTypeType1 = 1,
    /** @brief Font type: TrueType. */
    e_FontTypeTrueType = 2,
    /** @brief Font type: Type3. */
    e_FontTypeType3 = 3,
    /** @brief Font type: CID font. */
    e_FontTypeCIDFont = 4
  } FontTypes;
  
  /**
   * @brief Constructor, with given attribute.
   *
   * @details This function is to construct font based on system fonts.
   *
   * @param[in] name    The PostScript name of the font to be created.
   * @param[in] styles  Font styles. Please refer to values starting from @link Font::e_StyleFixedPitch @endlink and
   *                    this can be one or a combination of these values.
   * @param[in] charset The charset of the font to be created. Please refer to values starting from
   *                    @link Font::e_CharsetANSI @endlink and this should be one of these values.
   * @param[in] weight  Original font weight. 0 means unspecified.
   */
  Font(const wchar_t* name, uint32 styles, Charset charset, int weight);

  /**
   * @brief Constructor, by a standard font ID.
   *
   * @param[in] font_id  Standard font ID of the font to be created. Please refer to values starting from
   *                     @link Font::e_StdIDCourier @endlink and this should be one of these values.
   */
  explicit Font(StandardID font_id);

  /**
   * @brief Constructor, from a font file.
   *
   * @param[in] font_file_path  A full path to an existing font file.
   * @param[in] face_index      The zero-based face index. Valid range: from 0 to (<i>face_count</i>-1).
   *                            Please call the system functions to get the <i>face_count</i>.
   * @param[in] charset         The charset of the font to be created. Please refer to values starting from
   *                            @link Font::e_CharsetANSI @endlink and this should be one of these values.
   */
  Font(const char* font_file_path, int face_index, Charset charset);

  /**
   * @brief Constructor, from a font file.
   *
   * @param[in] font_file_path  A full path to an existing font file.
   * @param[in] face_index      The zero-based face index. Valid range: from 0 to (<i>face_count</i>-1).
   *                            Please call the system functions to get the <i>face_count</i>.
   * @param[in] charset         The charset of the font to be created. Please refer to values starting from
   *                            @link Font::e_CharsetANSI @endlink and this should be one of these values.
   */
  Font(const wchar_t* font_file_path, int face_index, Charset charset);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Font(FS_HANDLE handle = NULL);

  /**
   * @brief Constructor, with another font object.
   *
   * @param[in] other  Another font object.
   */
  Font(const Font& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another font object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Font& operator = (const Font& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another font object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Font& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another font object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Font& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /** @brief Destructor. */
  ~Font();

  /**
   * @brief Retrieve the postscript name.
   *
   * @return The postscript name.
   */
  WString GetName();

  /**
  * @brief Retrieve the famliy name.
  *
  * @return The famliy name.
  */
  String GetFamilyName();

  /**
   * @brief Judge whether current font is bold or not.
   *
   * @return <b>true</b> means current font is bold, while <b>false</b> means not.
   */
  bool IsBold() const;

  /**
   * @brief Judge whether current font object is italic or not.
   *
   * @return <b>true</b> means current font is italic, while <b>false</b> means not.
   */
  bool IsItalic() const;

  /**
   * @brief Judge whether current font is embedded in a specified PDF document or not.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @return <b>true</b> means the font is embedded in the specified PDF document, while <b>false</b> means not.
   */
  bool IsEmbedded(const pdf::PDFDoc& document);
  
  /**
   * @brief Check whether current font is supported to be embedded to the specified PDF document or not.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @return <b>true</b> means current font is supported to be embedded to the specified PDF document,
   *         while <b>false</b> means not.
   */
  bool IsSupportEmbedded(const pdf::PDFDoc& document);

  /**
   * @brief Embed current font to the specified PDF document.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @return The embedded font.
   */
  Font Embed(pdf::PDFDoc document);

#ifdef _FONT_GETWOFFDATA_
  /**
   * @brief Get WOFF Data from the specified PDF document.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @return The WOFF Data.
   */
  String GetWoffData(pdf::PDFDoc document);
#endif
  
  /**
   * @brief Get the ascent value, in 1/1000 of em size (PDF units).
   *
   * @return The ascent value, in 1/1000 of em size (PDF units).
   */
  int GetAscent() const;

  /**
   * @brief Get the descent value, in 1/1000 of em size (PDF units).
   *
   * @return The descent value, in 1/1000 of em size (PDF units).
   */
  int GetDescent() const;

  /**
   * @brief Get the bounding box of a character specified by unicode.
   *
   * @param[in] unicode  A character unicode value.
   *
   * @return The character bounding box.
   */
  RectI GetCharBBox(uint32 unicode) const;

  /**
   * @brief Get the width (in 1/1000 of em size (PDF units)) of a character specified by unicode.
   *
   * @param[in] unicode  A character unicode value.
   *
   * @return The character width, in 1/1000 of em size (PDF units).
   */
  float GetCharWidth(uint32 unicode) const;

  /**
  * @brief Get the bounding box of a character that  in document specified by unicode 
  *
  * @param[in] unicode  A character unicode value.
  * @param[in] document  A valid PDF document object.
  *
  * @return The character bounding box.
  */
  RectI GetCharBBox(foxit::uint32 unicode,const foxit::pdf::PDFDoc& document);
  
  /**
  * @brief Get the width (in 1/1000 of em size (PDF units)) of a character that  in document specified by unicode.
  *
  * @param[in] unicode  A character unicode value.
  * @param[in] document  A valid PDF document object.
  *
  * @return The character width, in 1/1000 of em size (PDF units).
  */
  float GetCharWidth(foxit::uint32 unicode,const foxit::pdf::PDFDoc& document);

  /**
   * @brief Get font styles.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @return  Font styles. Please refer to values starting from @link Font::e_StyleFixedPitch @endlink 
   *          and this would be one or a combination of these values.
   */
  foxit::uint32 GetStyles(const pdf::PDFDoc& document);

  /**
   * @brief Get CID font charset.
   *
   * @details Applicable for CID based fonts. For rest type of font, exception
   *          @link foxit::e_ErrUnsupported @endlink will be thrown.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @return Font charset. Please refer to values starting from @link Font::e_CIDCharsetUnknown @endlink
   *         and this would be one of these values.
   */
  CIDCharset GetCIDCharset(const pdf::PDFDoc& document);

  /**
   * @brief Check whether current font is a standard font.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @return  <b>true</b> means current font is a standard font, while <b>false</b> means not.
   */
  bool IsStandardFont(const pdf::PDFDoc& document);

  /**
   * @brief Get standard font ID.
   *
   * @details Applicable for standard fonts. For rest type of font, exception
   *          @link foxit::e_ErrUnsupported @endlink will be thrown.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @return Standard font ID. Please refer to values starting from
   *         @link Font::e_StdIDCourier @endlink and this would be one of these values.
   */
  StandardID GetStandard14Font(const pdf::PDFDoc& document);

  /**
   * @brief Get font type.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @return Font type. Please refer to values starting from @link Font::e_FontTypeType1 @endlink
   *         and this would be one of these values.
   */
  FontTypes GetFontType(const pdf::PDFDoc& document);

  /**
   * @brief Get base font name.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @return Base font name.
   */
  String  GetBaseFontName(const pdf::PDFDoc& document);
};

/**
 * This class represents font mappping result returned by callback function
 * @link FontMapperCallback::MapFont @endlink.
 */
class FontMapResult FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  FontMapResult() : file_read(NULL), face_index(-1) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] file_read   A @link common::file::ReaderCallback @endlink object which is implemented by user. Foxit PDF SDK will use this
   *                        callback object to read data for mapped font. If this is <b>NULL</b>, that means no mapped font.
   * @param[in] face_index  A zero-based index value:
   *                        <ul>
   *                        <li>If the mapped font (represented by <i>file_read</i>) is a "collection" (which means that
   *                            a number of faces are stored in the same file), this index value represents the index of the mapped font face.</li>
   *                        <li>If the mapped font (represented by <i>file_read</i>) is not a collection, the index value shall be zero.</li>
   *                        </ul>
   *                        -1 means no mapped font.
   */
  FontMapResult(foxit::common::file::ReaderCallback* file_read, int face_index) {
    this->file_read = file_read;
    this->face_index = face_index;
  }

  /**
   * @brief Constructor, with another font mapping result object.
   *
   * @param[in] other  Another font mapping result object.
   */
  FontMapResult(const FontMapResult& other) {
    this->file_read = other.file_read;
    this->face_index = other.face_index;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another font mapping result object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  FontMapResult& operator = (const FontMapResult& other) {
    this->file_read = other.file_read;
    this->face_index = other.face_index;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another font mapping result object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const FontMapResult& other) const {
    if (this->file_read != other.file_read || this->face_index != other.face_index)
      return false;
    return true;
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another font mapping result object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const FontMapResult& other) const {
    return !(*this == other);
  }

  /**
   * @brief Set value.
   *
   * @param[in] file_read   A @link common::file::ReaderCallback @endlink object which is implemented by user. Foxit PDF SDK will use this
   *                        callback object to read data for mapped font. If this is <b>NULL</b>, that means no mapped font.
   * @param[in] face_index  A zero-based index value:
   *                        <ul>
   *                        <li>If the mapped font (represented by <i>file_read</i>) is a "collection" (which means that
   *                            a number of faces are stored in the same file), this index value represents the index of the mapped font face.</li>
   *                        <li>If the mapped font (represented by <i>file_read</i>) is not a collection, the index value shall be zero.</li>
   *                        </ul>
   *                        -1 means no mapped font.
   */
  void Set(foxit::common::file::ReaderCallback* file_read, int face_index) {
    this->file_read = file_read;
    this->face_index = face_index;
  }

  /**
   * @brief A @link common::file::ReaderCallback @endlink object which is implemented by user. Foxit PDF SDK will use this
   *        callback object to read data for mapped font.If this is <b>NULL</b>, that means no mapped font.
   */
  foxit::common::file::ReaderCallback* file_read;
  /**
   * @brief Face index. This is a zero-based index value:
   *          <ul>
   *          <li>If the mapped font (represented by <i>file_read</i>) is a "collection" (which means that
   *              a number of faces are stored in the same file), this index value represents the index of the mapped font face.</li>
   *          <li>If the mapped font (represented by <i>file_read</i>) is not a collection, the index value shall be zero.</li>
   *          </ul>
   *          -1 means no mapped font.
   */
  int face_index;
};

/**
 * This class represents a callback object to map font in customized way.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 * An implemented @link FontMapperCallback @endlink object can be set to Foxit PDF SDK by
 * function @link Library::SetFontMapperCallback @endlink.
 *
 * @see @link Library @endlink
 */
class FontMapperCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function used to map a suitable font according to input parameters.
   *
   * @param[in] font_name     Font name.
   * @param[in] is_truetype   <b>true</b> means the font is expected to be a TrueType font, while <b>false</b> means the font is expected to be a Type1 font.
   * @param[in] styles        Font styles. Please refer to values starting from @link Font::e_StyleFixedPitch @endlink and
   *                          this would be one or a combination of these values.
   * @param[in] weight        Original font weight. 0 means unspecified.
   * @param[in] italic_angle  Italic angle.
   * @param[in] charset       The charset of the font to be mapped. Please refer to values starting from
   *                          @link Font::e_CharsetANSI @endlink and this would be one of these values.
   *
   * @return Font map result object. If any member in the returned @link FontMapResult @endlink is invalid,
   *         that means no mapped font is found. Then Foxit PDF SDK will do font mapping.
   */
  virtual FontMapResult MapFont(const char* font_name, bool is_truetype, uint32 styles,
                                int weight, int italic_angle, Font::Charset charset) = 0;

 protected:
  ~FontMapperCallback() {}
};

/** This class represents a path which contains one or more figures. */
class Path FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for point type in path.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PointType {
    /** @brief Indicates that the point is the first point of a figure. */
    e_TypeMoveTo = 1,
    /** @brief Indicates that a line is drawn from the previous point to this point. */
    e_TypeLineTo = 2,
    /**
   @brief Indicates that a line is drawn from the previous point to this point,
          and this point will also be connected to the nearest @link Path::e_TypeMoveTo @endlink
          point before this point, in order to close current figure.
     */
    e_TypeLineToCloseFigure  = 3,
    /** @brief Indicates that this point is a control point or ending point for a Bezier spline. */
    e_TypeBezierTo = 4,
    /**
   @brief Indicates that this point is the ending point for a Bezier spline,
          and this point will also be connected to the nearest @link Path::e_TypeMoveTo @endlink
          point before this point, in order to close current figure.
     */
    e_TypeBezierToCloseFigure = 5
  } PointType;
  
  /** @brief Constructor. */
  Path();
  /** @brief Destructor. */
  ~Path();
  /**
   * @brief Constructor, with another path object.
   *
   * @param[in] other  Another path object.
   */
  Path(const Path& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another path object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Path& operator=(const Path& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another path object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator ==(const Path& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another path object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Path& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the count of points.
   *
   * @return The count of points.
   */
  int GetPointCount();

  /**
   * @brief Get a point specified by index.
   *
   * @param[in] index  The index of the point. Valid range: 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Path::GetPointCount @endlink.
   *
   * @return The specified point.
   */
  PointF GetPoint(int index);

  /**
   * @brief Get the type of a point specified by index.
   *
   * @param[in] index  The index of the point. Valid range: 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Path::GetPointCount @endlink.
   *
   * @return The type of specified point. Please refer to values starting from @link Path::e_TypeMoveTo @endlink and
   *         this would be one of these values.
   */
  PointType GetPointType(int index);

  /**
   * @brief Change the value and type of a point specified by index.
   *
   * @param[in] index  The index of the point. Valid range: 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Path::GetPointCount @endlink.
   * @param[in] point  The new point to set, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] type   The type used to set to the new point. Please refer to values starting from
   *                   @link Path::e_TypeMoveTo @endlink and this should be one of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetPoint(int index, const PointF& point, PointType type);

  /**
   * @brief Add a point to the end of current path, to start a new figure.
   *
   * @details If this function succeeds, the new point will become the new "current point", and the new figure will
   *          become the new "current figure".
   *
   * @param[in] point  New point, in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool MoveTo(const PointF& point);

  /**
   * @brief Add a point to the end of current figure, and a line is to be drawn from current point to the new point.
   *
   * @details If this function succeeds, the new point will become the new "current point".
   *
   * @param[in] point  New point, in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool LineTo(const PointF& point);

  /**
   * @brief Add a cubic bezier spline to the end of current figure, by three points:
   *        two control points and one target point.
   *
   * @details If this function succeeds, parameter <i>point3</i> will become the new "current point".
   *
   * @param[in] point1  New point as the first control point for cubic bezier, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] point2  New point as the second control point for cubic bezier, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] point3  New point as target point for cubic bezier, in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool CubicBezierTo(const PointF& point1, const PointF& point2, const PointF& point3);

  /**
   * @brief Close current figure (which is also the last figure in current path).
   *
   * @details When closing current figure, the last point's type may be changed:
   *          <ul>
   *          <li>If the last point's type is @link Path::e_TypeMoveTo @endlink, that means the last figure just
   *              has one point and cannot be closed and current function will return <b>false</b>.</li>
   *          <li>If the last point's type is @link Path::e_TypeLineTo @endlink,
   *              the type will be changed to @link Path::e_TypeLineToCloseFigure @endlink.
   *          </li>
   *          <li>If the last point's type is @link Path::e_TypeLineTo @endlink, the type will be changed to
   *              @link Path::e_TypeBezierToCloseFigure @endlink.</li>
   *          <li>If the last point's type is already @link Path::e_TypeLineToCloseFigure @endlink or
   *              @link Path::e_TypeBezierToCloseFigure @endlink, that means the last figure has been closed.
   *              The type will not be changed and function will still return <b>true</b>.</li>
   *          </ul>
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool CloseFigure();

  /**
   * @brief Remove a point specified by index.
   *
   * @param[in] index  The index of the point to be removed. Valid range: 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Path::GetPointCount @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemovePoint(int index);

  /**
   * @brief Add a rectangle figure to the end of current path.
   *
   * @param[in] rect  A rectangle which specifies a rectangle figure.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool AppendRect(const RectF& rect);

  /**
   * @brief Add an ellipse figure to the end of current path.
   *
   * @param[in] rect  The enclosing rectangle of an ellipse figure.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool AppendEllipse(const RectF& rect);

  /**
   * @brief Transform all points in current path with a given matrix.
   *
   * @param[in] matrix  A matrix used for transforming.
   *
   * @return None.
   */
  void Transform(const Matrix& matrix);
  /**
   * @brief Clear all points.
   *
   * @return None.
   */
  void Clear();

  /**
   * @brief Increase the point count and prepare adequate memory for these new points.
   *
   * @details This function will allocate more memory for given point count and initialize these new points
   *          with point (0, 0) and type @link Path::e_TypeMoveTo @endlink by default.
   *          After calling this function successfully, user can use function @link Path::SetPoint @endlink to
   *          set these new points.
   *
   * @param[in] count  The new point count. It should not be negative.
   *
   * @return None.
   */
  void IncreasePointCount(int count);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Path(FS_HANDLE handle);
};

/**
 * This class represents color space. User can use this class to covert colors.
 */
class ColorSpace FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for rendering intent.
   *
   * @details Values of this enumeration should be used alone.<br>
   *          Rendering intent can be used for color conversion. Please refer to 
   *          Section 8.6.5.8 "Rendering intents" in the reference doucment for PDF 2.0 
   *          for more details.
   */
  typedef enum _RenderingIntent {
    /** @brief Rendering intent: Perceptual. */
    e_RenderIntentPerceptual  = 0,
    /** @brief Rendering intent: Relative Colorimetric. */
    e_RenderIntentRelColorimetric = 1,
    /** @brief Rendering intent: Saturation. */
    e_RenderIntentSaturation = 2,
    /** @brief Rendering intent: Absolute Colorimetric. */
    e_RenderIntentAbsColorimetric = 3
  } RenderingIntent;
  

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit ColorSpace(FS_HANDLE handle);

  /**
   * @brief Constructor, with specified color type.
   *
   * @param[in] type  The color space type. Currently, this value can only be one of following values:
   *                  @link common::e_ColorSpaceDeviceGray @endlink, @link common::e_ColorSpaceDeviceRGB @endlink,
   *                  @link common::e_ColorSpaceDeviceCMYK @endlink.<br>
   *                  For other unsupported color space type, exception @link foxit::e_ErrUnsupported @endlink will be thrown.
   */
  ColorSpace(foxit::common::ColorSpaceType type);
  /** @brief Destructor. */
  ~ColorSpace();

  /**
   * @brief Constructor, with another color space object.
   *
   * @param[in] other  Another color space object.
   */
  ColorSpace(const ColorSpace& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another color space object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ColorSpace& operator=(const ColorSpace& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another color space object. This function will check if current object is
   *                   equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const ColorSpace& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another color space object. This function will check if current object is not
   *                   equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const ColorSpace& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the count of components.
   *
   * @details For different colorspace type, the count of components are not the same.
   *
   * @return Count of components.
   */
  int GetComponentCount() const;

  /**
   * @brief Get color space type.
   *
   * @return Color space type. Please refer to values starting from @link common::e_ColorSpaceInvalid @endlink
   *         and this would be one of these values.
   */
  foxit::common::ColorSpaceType GetColorSpaceType() const;

  /**
   * @brief Convert input color to the color in current color space.
   *
   * @param[in] color  Input color, which is to be converted to current color space.
   *
   * @return Converted color. If the return value of function @link Color::IsEmpty @endlink
   *         for the returned color is <b>true</b>, that means the conversion failed.
   */
  Color ConvertColor(const Color& color);

  /**
   * @brief Convert input R/G/B component values to a color in current color space.
   *
   * @param[in] r_value  R component value. Valid range: from 0 to 255.
   * @param[in] g_value  G component value. Valid range: from 0 to 255.
   * @param[in] b_value  B component value. Valid range: from 0 to 255.
   *
   * @return Converted color. If the return value of function @link Color::IsEmpty @endlink
   *         for the returned color is <b>true</b>, that means the conversion failed.
   */
  Color ConvertColor(int r_value, int g_value, int b_value);

  /**
   * @brief Convert input C/M/Y/K component values to a color object in current color space.
   *
   * @param[in] c_value  C component value. Valid range: from 0 to 255.
   * @param[in] m_value  M component value. Valid range: from 0 to 255.
   * @param[in] y_value  Y component value. Valid range: from 0 to 255.
   * @param[in] k_value  K component value. Valid range: from 0 to 255.
   *
   * @return Converted color. If the return value of function @link Color::IsEmpty @endlink
   *         for the returned color is <b>true</b>, that means the conversion failed.
   */
  Color ConvertColor(int c_value, int m_value, int y_value, int k_value);
};

/**
 * This class represents a color.
 */
class Color FS_FINAL : public Base {
 public:
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Color(FS_HANDLE handle);

  /** @brief Construct an empty color. */
  Color();
  /**
   * @brief Constructor, with a color space object
   *
   * @param[in] color_space  A valid color space object.
   */
  explicit Color(const ColorSpace& color_space);
  /** @brief Destructor. */
  ~Color();

  /**
   * @brief Constructor, with another color object.
   *
   * @param[in] other  Another @link Color @endlink object.
   */
  Color(const Color& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another color object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Color& operator=(const Color& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another color object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const Color& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another color object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const Color& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the color space that current color belongs to.
   *
   * @return Color space object.
   */
  ColorSpace GetColorSpace();

  /**
   * @brief Get component value array.
   *
   * @details The count of components depends on the color space that current color belongs to.
   *          User can get the color space object by function @link Color::GetColorSpace @endlink, and then
   *          get the count of componets by function @link ColorSpace::GetComponentCount @endlink.
   *
   * @return A component value array. Each component value would be in the range from 0.0 to 1.0.
   */
  FloatArray GetValue() const;

  /**
   * @brief Set component value array.
   *
   * @details The count of components depends on the color space that current color belongs to.
   *          User can get the color space object by function @link Color::GetColorSpace @endlink, and then
   *          get the count of componets by function @link ColorSpace::GetComponentCount @endlink.
   *
   * @param[in] component_array  A component value array. The count of components in this array should match the count of components
   *                             of the color space that current color belongs to. Valid range of each component value: from 0.0 to 1.0.
   *
   * @return None.
   */
  void SetValue(const FloatArray& component_array);

  /**
   * @brief Convert to a RGB color.
   *
   * @param[in] intent  (Reserved) Rendering intent used for color conversion.
   *
   * @return Converted color. If the return value of function @link Color::IsEmpty @endlink
   *         for the returned color is <b>true</b>, that means the conversion failed.
   */
  Color ConvertToRGB(ColorSpace::RenderingIntent intent = ColorSpace::e_RenderIntentRelColorimetric) const;

  /**
   * @brief Convert to a CMYK color.
   *
   * @param[in] intent  (Reserved) Rendering intent used for color conversion.
   *
   * @return Converted color. If the return value of function @link Color::IsEmpty @endlink
   *         for the returned color is <b>true</b>, that means the conversion failed.
   */
  Color ConvertToCMYK(ColorSpace::RenderingIntent intent = ColorSpace::e_RenderIntentRelColorimetric) const;
};
}  // namespace common
}  // namespace foxit

#endif  // FS_COMMON_H_

