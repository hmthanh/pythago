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
* @file fs_optimization.h
* @brief Header file for PDF optimization related definitions and classes.
*/

#ifndef FS_PDFOPTIMIZATION_H_
#define FS_PDFOPTIMIZATION_H_

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
 * @brief Optimization namespace.
 */
namespace optimization {
 class ImageSettings;
 class MonoImageSettings;
 class OptimizerSettings;
 
/** 
 * This class can be used to optimize PDF file to reduce file size.
 * Before using this class to do optimization, please ensure Foxti PDF SDK has been initialized successfully
 * by function @link common::Library::Initialize @endlink with a key including "Optimizer" module.
 *
 * @see @link common::Library @endlink
 */ 
class Optimizer FS_FINAL : public Base {
 public:
    typedef foxit::addon::optimization::OptimizerSettings OptimizerSettings;
   /**
    * @brief Optimize the given PDF document with specified optimizers settings.
    *
    * @param[in] doc       A valid PDF document object to be optimized.
    * @param[in] settings  Setting data used for optimization processing settings.
    * @param[in] pause     Pause object which decides if the process needs to be paused.
    *                      This can be <b>NULL</b> which means not to pause during the optimization process.
    *                      If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
    *
    * @note If module "Optimizer" is not defined in the license information which is used in function
    *       @link common::Library::Initialize @endlink, that means user has no right in using Optimization related functions and
    *       this function will throw exception @link foxit::e_ErrNoOptimizerModuleRight @endlink.
    *
    * @return A progressive object. Please check the rate of current progress by function
    *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
    *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
    */
    static common::Progressive Optimize(const pdf::PDFDoc& doc,const OptimizerSettings& settings,common::PauseCallback* pause);
    
	/**
   * @brief Start to make subsets for embedded fonts in the given PDF document.
   *
   * @details This function can be used to remove useless embedded characters from the data of embedded fonts (if there's any in a PDF document)
   *          in order to reduce the size of a PDF document.
   *
   * @param[in] doc       A valid PDF document object to be processed a subset of embedded fonts.
   * @param[in] pause     Pause object which decides if the process needs to be paused.
   *                      This can be <b>NULL</b> which means not to pause during the embeded font subset process.
   *                      If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *
   * @note If module "Optimizer" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using Optimization related
   *       functions and this function will throw exception @link foxit::e_ErrNoOptimizerModuleRight @endlink.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
	static common::Progressive StartSubsetEmbedFont(const pdf::PDFDoc& doc, common::PauseCallback* pause);
};

/**
 * This class represents downsampling/recompression settings for color and grayscale images. 
 * This class object can be set to class @link OptimizerSettings @endlink and then be used to optimize a PDF document.
 *
 * @see @link OptimizerSettings @endlink
 */
class ImageSettings FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for compression mode used for color or gray image.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ImageCompressMode {
    /** @brief Compression mode: high. */
    e_ImageCompressHigh = 10003,
    /** @brief Compression mode: jpeg. */
    e_ImageCompressjpeg = 10005,
    /** @brief Compression mode: jpeg2000. */
    e_ImageCompressjpeg2000 = 10006,
    /** @brief Compression mode: retain, which means no compression. */
    e_ImageCompressRetain  = 10007
  } ImageCompressMode;
  
  /**
   * @brief Enumeration for loss compression quality used for color or gray image.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ImageCompressQuality {
    /** @brief Compression quality: Minimum. */
    e_ImageCompressQualityMinimum = 1,
    /** @brief Compression quality: Low. */
    e_ImageCompressQualityLow = 2,
    /** @brief Compression quality: Medium. */
    e_ImageCompressQualityMedium = 3,
    /** @brief Compression quality: High. */
    e_ImageCompressQualityHigh  = 4,
    /** @brief Compression quality: Maximum. */
    e_ImageCompressQualityMaximum  = 5
  } ImageCompressQuality;
  
  /**
   * @brief Enumeration for stretch mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _StretchMode {
    /** @brief When this is set, that means do without stretching */
    e_StretchOff  = 0x00,
    /** @brief When this is set, that means to do interpolation for zooming. */
    e_StretchInterpol = 0x20,
    /** @brief When this is set, that means not to do halftone for shrinking or rotating*/
    e_StretchDownsample = 0x04,
    /** @brief When this is set, that means to do bicubic interpolation for zooming. */
    e_StretchBicubic = 0x80,
    /** @brief When this is set, that means not to do any interpolation for stretching. */
    e_StretchNoSmooth = 0x100
  } StretchMode;
  
  /**
   * @brief Constructor.
   *
   * @details This constructor is to construct a color/gray image settings object with default setting options.
   *          User can also calling "set" methods in this class to change these setting options.
   *          Please refer to comment of these "set" methods for more details about default values.
   */
  ImageSettings();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit ImageSettings(FS_HANDLE handle);

  /** @brief Destructor. */
  ~ImageSettings();

  /**
   * @brief Constructor, with another image setting object.
   *
   * @param[in] other  Another ImageSettings object.
   */
  ImageSettings(const ImageSettings& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another result image setting object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ImageSettings& operator = (const ImageSettings& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another result ImageSettings object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const ImageSettings& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another result image setting object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const ImageSettings& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set stretch mode used for optimizing color/gray images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use @link ImageSettings::e_StretchBicubic @endlink as the deault value of this option.
   *
   * @param[in] mode  Stretch mode. Please refer to values starting from @link ImageSettings::e_StretchOff @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
   void SetStretchMode(StretchMode mode);

  /**
   * @brief Set the image DPI used for optimizing color/gray images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set option,
   *          that means to use 150 as the deault value of this option.
   *
   * @param[in] dpi  DPI value.
   *
   * @return None.
   */
  void SetImageDPI(int32 dpi);
  /**
   * @brief Set compression mode used for optimizing color/gray images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set option,
   *          that means to use @link ImageSettings::e_ImageCompressjpeg @endlink as the deault value of this option.
   *
   * @param[in] mode  Image compression mode. Please refer to values starting from @link ImageSettings::e_ImageCompressHigh @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
  void SetCompressionMode(ImageCompressMode mode);

  /**
   * @brief Set the quality for lossy compression modes, used for optimizing color/gray images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use @link ImageSettings::e_ImageCompressQualityMinimum @endlink as
   *          the deault value of this option.
   *
   * @param[in] quality  Quality value for lossy compression modes. Please refer to values starting from
   *                     @link ImageSettings::e_ImageCompressQualityMinimum @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetQuality(ImageCompressQuality quality);
};

/**
 * This class represents downsampling/recompression settings for monochrome images.
 * This class object can be set to class @link OptimizerSettings @endlink and then be used to optimize a PDF document.
 *
 * @see @link OptimizerSettings @endlink
 */
class MonoImageSettings FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for compression mode used for monochrome image.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MonoImageCompressMode {
    /** @brief Compression mode: CCITT Group 3. */
    e_ImageCompressCCITT3 = 10001,
    /** @brief Compression mode: CCITT Group 4. */
    e_ImageCompressCCITT4 = 10002,
    /** @brief Compression mode: high. */
    e_ImageCompressHigh = 10003,
    /** @brief Compression mode: jbig2. */
    e_ImageCompressjbig2 = 10004,
    /** @brief Compression mode: retain, which means no compression. */
    e_ImageCompressRetain  = 10007,
    /** @brief Compression mode: run-length. */
    e_ImageCompressRunLength = 10008
  } MonoImageCompressMode;
  
  /**
  * @brief Enumeration for compression quality used for monochrome image.
  *
  * @details Values of this enumeration should be used alone.
  */
  typedef enum _MonoImageCompressQuality {
    /** @brief Compression quality: Lossless. */
    e_ImageCompressQualityLossless = 1,
    /** @brief Compression quality: Lossy. */
    e_ImageCompressQualityLossy = 2
  } MonoImageCompressQuality;
  
  /**
   * @brief Enumeration for stretch mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _StretchMode {
    /** @brief When this is set, that means do without stretching */
    e_StretchOff  = 0x00,
    /** @brief When this is set, that means to do interpolation for zooming. */
    e_StretchInterpol = 0x20,
    /** @brief When this is set, that means not to do halftone for shrinking or rotating*/
    e_StretchDownsample = 0x04,
    /** @brief When this is set, that means to do bicubic interpolation for zooming. */
    e_StretchBicubic = 0x80,
    /** @brief When this is set, that means not to do any interpolation for stretching. */
    e_StretchNoSmooth = 0x100
  } StretchMode;
  
  /**
   * @brief Constructor.
   *
   * @details This constructor is to construct a monochrome image settings object with default setting options.
   *          User can also calling "set" methods in this class to change these setting options.
   *          Please refer to comment of these "set" methods for more details about default values.
   */
  MonoImageSettings();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit MonoImageSettings(FS_HANDLE handle);

  /** @brief Destructor. */
  ~MonoImageSettings();

  /**
   * @brief Constructor, with another result information object.
   *
   * @param[in] other  Another monochrome image settings object.
   */
  MonoImageSettings(const MonoImageSettings& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another monochrome image settings object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  MonoImageSettings& operator = (const MonoImageSettings& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another monochrome image settings object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const MonoImageSettings& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another monochrome image settings object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const MonoImageSettings& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set the image DPI used for optimizing monochrome images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set option,
   *          that means to use 250 as the deault value of this option.
   *
   * @param[in] dpi  DPI value.
   *
   * @return None.
   */
  void SetImageDPI(int32 dpi);

  /**
   * @brief Set compression mode used for optimizing monochrome images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set option,
   *          that means to use @link MonoImageSettings::e_ImageCompressCCITT4 @endlink as the deault value of this option.
   *
   * @param[in] mode  Image compression mode. Please refer to values starting from @link MonoImageSettings::e_ImageCompressHigh @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
  void SetCompressionMode(MonoImageCompressMode mode);

  /**
   * @brief Set stretch mode used for optimizing monochrome images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use @link MonoImageSettings::e_StretchBicubic @endlink as the deault value of this option.
   *
   * @param[in] mode  Stretch mode. Please refer to values starting from @link ImageSettings::e_StretchOff @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
    void SetStretchMode(StretchMode mode) ;

  /**
   * @brief Set compression quality, used for optimizing monochrome images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use @link MonoImageSettings::e_ImageCompressQualityLossless @endlink
   *		  as the deault value of this option.
   *
   * @param[in] quality  Compression quality. Please refer to values starting from
   *					 @link MonoImageSettings::e_ImageCompressQualityLossless @endlink
   *                     and this should be one of these values.
   *
   * @return None.
   */
   void SetQuality(MonoImageCompressQuality quality);
};

/**
 * This class represents the settings for unembedded fonts.
 * This class object can be set to class @link OptimizerSettings @endlink and then be used to optimize a PDF document.
 *
 * @see @link OptimizerSettings @endlink
 */
class UnembeddedFontSettings FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor.
   */
  UnembeddedFontSettings();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit UnembeddedFontSettings(FS_HANDLE handle);

  /** @brief Destructor. */
  ~UnembeddedFontSettings();

  /**
   * @brief Constructor, with another unembedded fonts setting object.
   *
   * @param[in] other  Another ImageSettings object.
   */
  UnembeddedFontSettings(const UnembeddedFontSettings& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another unembedded fonts setting object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  UnembeddedFontSettings& operator=(const UnembeddedFontSettings& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another unembedded fonts setting object. This function will check if current object is equal to this
   * one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const UnembeddedFontSettings& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another unembedded fonts setting object. This function will check if current object is not equal to
   * this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const UnembeddedFontSettings& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set a font name array to specify which fonts are to be unembeded.
   *
   * @details This function can be used to specify whic fonts are to be unembedded.
   *          User can use function @link pdf::PDFDoc::GetEmbeddedFontData @endlink to
   *          get the embedded font name arrays of a PDF document, then decide which embeded fonts are to be unembeded,
   *          and pass the unembeded font name array to current function.
   *
   * @param[in] font_name_array  A font name array to specify which fonts are to be unembeded.
   *
   * @return the unembedded font data object.
   */
  void SetUnembeddedFontNameArray(const WStringArray& font_name_array);
};

/**
 * This class represents settings for optimizing a PDF document. It would be used in class @link Optimizer @endlink.
 *
 * @see @link Optimizer @endlink
 */
class OptimizerSettings FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for optimizer options.
   *
   * @details Values of this enumeration can be used alone or in a combination.
   */
  typedef enum _OptimizerOptions {
    /** @brief Optimize PDF document by compressing images. */
    e_OptimizerCompressImages  = 0x01,
    /** @brief Optimize PDF document by cleaning up. */
    e_OptimizerCleanUp = 0x02,
    /** @brief Optimize PDF document by discarding objects. */
    e_OptimizerDiscardObjects = 0x04,
    /** @brief Optimize PDF document by unembedding some embedded fonts. */
    e_OptimizerUnembeddedFonts = 0x08,
    /** @brief Optimize PDF document by discarding user data. */
    e_OptimizerDiscardUserData = 0x10
  } OptimizerOptions;
  
  /**
   * @brief Enumeration for cleaning up options.
   *
   * @details Values of this enumeration can be used alone or in a combination.
   */
  typedef enum _CleanUpOptions {
    /** @brief Use Flate to encode streams that are not encoded. */
    e_CleanUpUseFlateForNonEncodedStream  = 0x01,
    /** @brief In streams that use LZW encoding, use Flate instead. */
    e_CleanUpUseFlateInsteadOfLZW = 0x02,
    /** @brief Remove invalid bookmarks.*/
    e_CleanUpRemoveInvalidBookmarks = 0x04,
    /** @brief Remove invalid links. */
    e_CleanUpRemoveInvalidLinks = 0x08
  } CleanUpOptions;
  
  /**
   * @brief Enumeration for discarding objects options.
   *
   * @details Values of this enumeration can be used alone or in a combination.
   */
  typedef enum _DiscardObjectsOptions {
    /** @brief Discard all form submission, import and reset actions. */
    e_DiscardObjectsFormActions  = 0x01,
    /** @brief Flatten form fields. */
    e_DiscardObjectsFlattenFormFields = 0x02,
    /**
     * @brief Discard all JavaScript actions.
     * 
     * @details Currently, it can not remove the javascript action in "OpenAction" of catalog. 
     */
    e_DiscardObjectsJavaScriptActions = 0x04,
    /** @brief Discard embedded page thumbnails. */
    e_DiscardObjectsEmbeddedPageThumbnails = 0x08,
    /** @brief Discard embedded print settings. */
    e_DiscardObjectsEmbeddedPrintSettings = 0x10,
    /** @brief Discard bookmarks. */
    e_DiscardObjectsBookmarks = 0x20,
    /**
     * @brief Discard all alternate images.
     *
     * @details Some PDF documents include multiple versions of the same image for different purposes,
     *          such as low-resolution on-screen viewing and high-resolution printing.
     *          If this option value is set to be used, that means to remove all versions of
     *          an image except the one destined for on-screen viewing.
     */
    e_DiscardObjectsAlternateImages = 0x40,
    /** @brief Discard document tags. */
    e_DiscardObjectsDocumentTags = 0x80,
    /** @brief Discard embedded search index. */
    e_DiscardObjectsEmbeddedSearchIndex = 0x100
  } DiscardObjectsOptions;
  
  /**
   * @brief Enumeration for discarding user data options.
   *
   * @details Values of this enumeration can be used alone or in a combination.
   */
  typedef enum _DiscardUserDataOptions {
    /** @brief Discard all annotations, forms and multimedia. */
    e_DiscardUserDataAllAnnotsFormsAndMultimedia  = 0x01,
    /** @brief Discard external cross references. */
    e_DiscardUserDataExternalCrossReferences = 0x02,
    /** @brief Discard document information and metadata. */
    e_DiscardUserDataDocumentInfoAndMetaData = 0x04,
    /** @brief Discard file attachments. */
    e_DiscardUserDataFileAttchments = 0x08,
    /** @brief Discard private data of other applications. */
    e_DiscardUserDataPrivateDataOfOtherApp = 0x10,
    /** @brief Discard hidden layer content and flatten visible layers. */
    e_DiscardUserDataLayer = 0x20
  } DiscardUserDataOptions;
  
  /**
   * @brief Constructor.
   *
   * @details This constructor is to construct a optimizer settings object with default setting options.
   *          User can also calling "set" methods in this class to change setting options.
   *          Please refer to comment in other settings class (which can be set to current object)
   *          for more details about what default setting options are.
   */
  OptimizerSettings(); 

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit OptimizerSettings(FS_HANDLE handle);

  /** @brief Destructor. */
  ~OptimizerSettings();

  /**
   * @brief Constructor, with another result information object.
   *
   * @param[in] other  Another optimizer settings object.
   */
  OptimizerSettings(const OptimizerSettings& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another result optimizer settings object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OptimizerSettings& operator = (const OptimizerSettings& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another result optimizer settings object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const OptimizerSettings& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another result optimizer settings object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const OptimizerSettings& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set options to decide which kind of optimizer setting will be used for optimizing PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set any optimizer options,
   *          that means no optimizer setting is useful.
   *
   * @param[in] optimize_options  The options to decide which kind of optimizer setting will be used for optimizing PDF document.
   *                              0 means no optimizer setting of any kind is useful. Please refer to values starting from
   *                              @link OptimizerSettings::e_OptimizerCompressImages @endlink and this can be one or
   *                              a combination of these values.
   *
   * @return None.
   */
  void SetOptimizerOptions(uint32 optimize_options);

  /**
   * @brief Set optimization related settings for color/gray image.
   *
   * @details For a newly constructed object, if this function is not called to set any color/gray image settings,
   *          that means to use default color/gray image settings. Please refer to comment in
   *          class @link ImageSettings @endlink for default values.<br>
   *          ImageSettings set by this function is useful only when option value
   *          @link OptimizerSettings::e_OptimizerCompressImages @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] settings  Optimization related settings for color and grayscale images.
   *
   * @return None.
   */
  void SetColorGrayImageSettings(const ImageSettings& settings); 
    
  /**
   * @brief Set optimization related settings for monochrome image.
   *
   * @details For a newly constructed object, if this function is not called to set any monochrome image settings,
   *          that means to use default monochrome image settings.
   *          Please refer to comment in class @link MonoImageSettings @endlink for detail values.<br>
   *          MonoImageSettings set by this function is useful only when option value
   *          @link OptimizerSettings::e_OptimizerCompressImages @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] settings  Optimization related settings for monochrome images.
   *
   * @return None.
   */
  void SetMonoImageSettings(const MonoImageSettings& settings);

  /**
   * @brief Set optimization related settings for unembedding fonts.
   *
   * @details For a newly constructed object, if this function is not called to set any unembedded fonts settings,
   *          that means to no font is to be unembedded.
   *          UnembeddedFontSettings set by this function is useful only when option value
   *          @link OptimizerSettings::e_OptimizerUnembeddedFonts @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] settings  Optimization related settings for unembedding fonts.
   *
   * @return None.
   */
  void SetUnembeddedFontSettings(const UnembeddedFontSettings& settings);

  /**
   * @brief Set optimization related options for cleaning up.
   *
   * @details For a newly constructed object, if this function is not called to set any clean-up options,
   *          that means not to do clean-up optimization.
   *          Clean-up options set by this function are useful only when option value
   *          @link OptimizerSettings::e_OptimizerCleanUp @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] clean_up_options  Optimization related options for cleaning up. 0 means not to do clean-up optimization.
   *                              Please refer to values starting from
   *                              @link OptimizerSettings::e_CleanUpUseFlateForNonEncodedStream @endlink and
   *                              this can be one or a combination of these values.
   *
   * @return None.
   */
  void SetCleanUpOptions(foxit::uint32 clean_up_options);

  /**
   * @brief Set optimization related options for discarding objects.
   *
   * @details For a newly constructed object, if this function is not called to set any discard-objects options,
   *          that means not to do discard-objects optimization.
   *          Discard-objects options set by this function are useful only when option value
   *          @link OptimizerSettings::e_OptimizerDiscardObjects @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] discard_objects_options  Optimization related options for discarding objects.
   *                                     0 means not to do discarding-objects optimization. Please refer to
   *                                     values starting from @link OptimizerSettings::e_DiscardObjectsFormActions @endlink
   *                                     and this can be one or a combination of these values.
   *
   * @return None.
   */
  void SetDiscardObjectsOptions(foxit::uint32 discard_objects_options);

  /**
   * @brief Set optimization related options for discarding user data.
   *
   * @details For a newly constructed object, if this function is not called to set any discard-userdata options,
   *          that means not to do discard-userdata optimization.
   *          Discard-userdata options set by this function are useful only when option value
   *          @link OptimizerSettings::e_OptimizerDiscardUserData @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] discard_userdata_options  Optimization related options for discarding user data.
   *                                      0 means not to do discarding-userdata optimization. Please refer to
   *                                      values starting from @link OptimizerSettings::e_DiscardUserDataAllAnnotsFormsAndMultimedia @endlink
   *                                      and this can be one or a combination of these values.
   *
   * @return None.
   */
  void SetDiscardUserDataOptions(foxit::uint32 discard_userdata_options);
};

}  // namespace optimization 
}  // namespace addon
}  // namespace foxit

#endif
