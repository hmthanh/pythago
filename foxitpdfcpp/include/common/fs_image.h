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
 * @file fs_image.h
 * @brief Header file for image and bitmap related definitions and classes.
 */

#ifndef FS_IMAGE_H_
#define FS_IMAGE_H_

#include "common/fs_common.h"
#include "common/file/fs_file.h"

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
 * Bitmap is one of most important data structures in Foxit PDF SDK. It is commonly used for rendering.
 * This class can construct a new bitmap object (not retrieved from other object) and offer methods to
 * get information or operate the bitmap.
 */
class Bitmap FS_FINAL : public Base {
 public:
  /**
  * @brief Enumeration for DIB format.
  *
  * @details Values of this enumeration should be used alone.
  */
  typedef enum _DIBFormat {
    /** @brief Invalid DIB format. */
    e_DIBInvalid = 0,
    /** @brief DIB format: 24bpp format, with bits order "Blue, Green, Red". Blue is in the lowest order. */
    e_DIBRgb = 0x018,
    /** @brief DIB format: 32bpp format, with bits order "Blue, Green, Red, not used". Blue is in the lowest order. */
    e_DIBRgb32 = 0x020,
    /** @brief DIB format: 32bpp format, with bits order "Blue, Green, Red, Alpha". Blue is in the lowest order. */
    e_DIBArgb = 0x220,
    /** @brief DIB format: 8bpp alpha mask. */
    e_DIB8bppMask = 0x108,
    /** @brief DIB format: 8bpp format, 256 color RGB bitmap. */
    e_DIB8bpp = 0x008,
    /** @brief DIB format: 8bpp format, 256 color GrayScale bitmap */
    e_DIB8bppGray = 0x1008,
    /** @brief DIB format: 32bpp format, with bits order "Red, Green, Blue, Alpha". Red is in the lowest order. */
    e_DIBAbgr = 0x222,
    /** @brief 16bpp format, bits order: Red 5 bits, Green 6 bits, Blue 5 bits. Red is the lowest order. */
    e_DIBRgb565 = 0x565
  } DIBFormat;
  
  /**
   * @brief Enumeration for bitmap interpolation flags.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _InterpolationFlag {
    /** @brief If set, do not do halftone for shrinking or rotating. */
    e_Downsample = 0x01,
    /** @brief If set, do interpolation for stretching or transforming. */
    e_Quadratic = 0x02,
    /** @brief If set, do bicubic interpolation for stretching or transforming. */
    e_Bicubic = 0x04
  } InterpolationFlag;
  
  /**
   * @brief Constructor, with parameters.
   *
   * @details If parameter <i>buffer</i> is not <b>NULL</b>, it should be initialized by application;
   *          if parameter <i>buffer</i> is <b>NULL</b>, Foxit PDF SDK will allocate and
   *          initialize the pixels buffer internally. <br>
   *          Application is suggested to use the same colors as Foxit PDF SDK uses internally
   *          to initialize bitmap's pixel buffer:
   *          <ul>
   *          <li>For the bitmap without alpha channel, initialize the pixels buffer with 0xFFFFFFFF.</li>
   *          <li>For the bitmap with alpha channel, initialize the pixels buffer with 0x00000000.</li>
   *          </ul>
   *
   * @param[in] width   Width of bitmap, in pixels. This should be above 0.
   * @param[in] height  Height of bitmap, in pixels. This should be above 0.
   * @param[in] format  Bitmap format type. Please refer to values starting from @link Bitmap::e_DIBRgb @endlink and
   *                    this should be one of these values except @link Bitmap::e_DIBInvalid @endlink.
   * @param[in] buffer  A buffer that specifies bitmap data.<br>
   *                    If it is not <b>NULL</b>, this function will use the parameter <i>buffer</i>
   *                    to initialize a bitmap. In this case, please do not free the parameter <i>buffer</i>
   *                    before the life-cycle of parameter <i>bitmap</i> ends.<br>
   *                    If it is <b>NULL</b>, a new bitmap buffer will be created internally.
   *                    Default value: <b>NULL</b>.
   * @param[in] pitch   The number of bytes for each scan line. This is useful only when parameter <i>buffer</i>
   *                    is not <b>NULL</b>. If this value is 0, 4-byte alignment is assumed. Default value: 0.
   */
  Bitmap(int width, int height, DIBFormat format, uint8* buffer = NULL, int pitch = 0);
  /**
   * @brief Constructor, with another bitmap object.
   *
   * @param[in] other  Another bitmap object.
   */
  Bitmap(const Bitmap& other);
  /** @brief Constructor, as an empty bitmap object. */
  Bitmap();

  /** @brief Destructor. */
  ~Bitmap();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another bitmap object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Bitmap& operator = (const Bitmap& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another bitmap object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Bitmap& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another bitmap object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Bitmap& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Clone current bitmap, with specified clip rectangle.
   *
   * @param[in] clip_rect  The clipping region in current bitmap to specify the region to be cloned. <br>
   *                       <ul>
   *                       <li>For bitmap format @link Bitmap::e_DIBRgb565 @endlink,
   *                           currently only support to clone the whole bitmap, so this should always be <b>NULL</b>.
   *                       </li>
   *                       <li>For rest format, this can be either <b>NULL</b> or valid. If this is <b>NULL</b>,
   *                           that means to clone the whole bitmap. If this is not <b>NULL</b>, it specifies
   *                           a clipping region in bitmap to be cloned and the cloned bitmap will
   *                           have the same size as the clipping region.
   *                       </li>
   *                       </ul>
   *                       Default value: <b>NULL</b>.
   *
   * @return A new bitmap as cloned result.
   */
  Bitmap Clone(const RectI* clip_rect = NULL) const;

  /**
   * @brief Get bitmap width.
   *
   * @return Bitmap width.
   */
  int GetWidth() const;
  /**
   * @brief Get bitmap height.
   *
   * @return Bitmap height.
   */
  int GetHeight() const;
  /**
   * @brief Get bitmap pitch.
   *
   * @return Bitmap pitch.
   */
  int GetPitch() const;
  /**
   * @brief Get bitmap bits-per-pixel.
   *
   * @return Bitmap bits-per-pixel value.
   */
  int GetBpp() const;
  /**
   * @brief Get bitmap buffer.
   *
   * @details Bitmap data are organized in scan-lines, from top to down.
   *
   * @return Bitmap buffer.
   */
  const uint8* GetBuffer() const;
  /**
   * @brief Get bitmap format.
   *
   * @return Format value. Please refer to values starting from @link Bitmap::e_DIBInvalid @endlink and
   *         this would be one of these values.
   */
  DIBFormat GetFormat() const;

  /**
   * @brief Fill current bitmap with a specified color.
   *
   * @param[in] color  A color value which is used to fill bitmap. Format: 0xAARRGGBB
   * @param[in] rect   A rectangle that represents a region in bitmap to specify where the color will be filled.
   *                   This can be <b>NULL</b>, which means to fill the whole bitmap. Default value: <b>NULL</b>.
   *
   * @return None.
   */
  void FillRect(ARGB color, const RectI* rect = NULL);

  /**
   * @brief Convert a bitmap to another specified DIB format.
   *
   * @param[in] format         New bitmap format type. It should be one of following values:<br>
   *                           @link Bitmap::e_DIB8bppMask @endlink, @link Bitmap::e_DIB8bpp @endlink,
   *                           @link Bitmap::e_DIBRgb @endlink, @link Bitmap::e_DIBRgb32 @endlink,
   *                           @link Bitmap::e_DIBArgb @endlink. @link Bitmap::e_DIBRgb565 @endlink.
   * @param[in] icc_transform  The color mapping context for source format to destination format.
   *                           It can be <b>NULL</b>, which means not use the color mapping.
   *                           Default value: <b>NULL</b>.
   * @return The converted bitmap.
   */
  Bitmap& ConvertFormat(DIBFormat format, void* icc_transform = NULL);

  /**
   * @brief Calculate the bounding box according to the given background color.
   *
   * @details This function can support the following formats:<br>
   *          @link Bitmap::e_DIB8bppMask @endlink, @link Bitmap::e_DIB8bpp @endlink,
   *          @link Bitmap::e_DIBRgb @endlink, @link Bitmap::e_DIBRgb32 @endlink,
   *          @link Bitmap::e_DIBArgb @endlink.
   *
   * @param[in] backgroud_color  A valid background color. Format: 0xAARRGGBB.
   *
   * @return The rectangle of bounding box for content.
   */
  RectI CalculateBBoxByColor(ARGB backgroud_color);

  /**
   * @brief Detect the bounding box of content according to the given color difference between content and margin.
   *
   * @details This function can support the following formats:<br>
   *          @link Bitmap::e_DIB8bppMask @endlink, @link Bitmap::e_DIB8bpp @endlink,
   *          @link Bitmap::e_DIBRgb @endlink, @link Bitmap::e_DIBRgb32 @endlink,
   *          @link Bitmap::e_DIBArgb @endlink.
   *
   * @param[in] detection_size  Detection size to analyze background.
   * @param[in] color_differ    Color difference used to detect margin. The value should be between 0 and 255, and
   *                            the suggested value is 64. Default value: 64.
   *
   * @return The rectangle of bounding box for content.
   */
  RectI DetectBBoxByColorDiffer(int detection_size, int color_differ = 64);

  /**
   * @brief Swap X,Y coordinations of the bitmap. After being swapped, the image can also be flipped at the same time.
   *
   * @details Optionally a clipping region (in destination bitmap coordinate) can be specified to
   *          limit the size of result.<br>
   *          Suppose the original image has the following 4 pixels:
   *          <pre>
   *          +---+---+
   *          | 1 | 2 |
   *          +---+---+
   *          | 3 | 4 |
   *          +---+---+
   *          </pre>
   *          Then, depends on parameter <i>is_flip_horz</i> and <i>is_flip_vert</i>, the result would look like:
   *          if parameter <i>is_flip_horz</i> = <b>false</b>, parameter <i>is_flip_vert</i> = <b>false</b>:
   *          <pre>
   *          +---+---+
   *          | 1 | 3 |
   *          +---+---+
   *          | 2 | 4 |
   *          +---+---+
   *          </pre>
   *          if parameter <i>is_flip_horz</i> = <b>true</b>, parameter <i>is_flip_vert</i> = <b>false</b>:
   *          <pre>
   *          +---+---+
   *          | 3 | 1 |
   *          +---+---+
   *          | 4 | 2 |
   *          +---+---+
   *          </pre>
   *          if parameter <i>is_flip_horz</i> = <b>false</b>, parameter <i>is_flip_vert</i> = <b>true</b>:
   *          <pre>
   *          +---+---+
   *          | 2 | 4 |
   *          +---+---+
   *          | 1 | 3 |
   *          +---+---+
   *          </pre>
   *          if parameter <i>is_flip_horz</i> = <b>true</b>, parameter <i>is_flip_vert</i> = <b>true</b>:
   *          <pre>
   *          +---+---+
   *          | 4 | 2 |
   *          +---+---+
   *          | 3 | 1 |
   *          +---+---+
   *          </pre>
   *
   * @param[in] is_flip_horz  A boolean value to indicate whether to flipping bitmap in horizontal direction:
   *                          <b>true</b> means the bitmap will be flipped in horizontal direction,
   *                          and <b>false</b> means not.
   * @param[in] is_flip_vert  A boolean value to indicate whether to flipping bitmap in vertical direction:
   *                          <b>true</b> means the bitmap will be flipped in vertical direction,
   *                          and <b>false</b> means not.
   * @param[in] clip_rect     The clipping region of destination bitmap. This can be <b>NULL</b>,
   *                          which means the whole bitmap. Default value: <b>NULL</b>.
   *
   * @return A new bitmap as swapped result.
   */
  Bitmap SwapXY(bool is_flip_horz, bool is_flip_vert, const RectI* clip_rect = NULL);

  /**
   * @brief Flip bitmap.
   *
   * @details This function can support following formats:<br>
   *          @link Bitmap::e_DIB8bppMask @endlink, @link Bitmap::e_DIB8bpp @endlink,
   *          @link Bitmap::e_DIBRgb @endlink, @link Bitmap::e_DIBRgb32 @endlink,
   *          @link Bitmap::e_DIBArgb @endlink.
   *
   * @param[in] is_flip_horz  A boolean value to indicate whether to flipping bitmap in horizontal direction:
   *                          <b>true</b> means a bitmap will be flipped in horizontal direction,
   *                          and <b>false</b> means not.
   * @param[in] is_flip_vert  A boolean value to indicate whether to flipping bitmap in vertical direction.
   *                          <b>true</b> means a bitmap will be flipped in vertical direction,
   *                          and <b>false</b> means not.
   *
   * @return A new bitmap as flipped result.
   */
  Bitmap Flip(bool is_flip_horz, bool is_flip_vert);

  /**
   * @brief Stretch with different size.
   *
   * @details If parameter <i>dest_width</i> or parameter <i>dest_height</i> is negative, the bitmap will be flipped.
   *          If the stretching is to be done in down-sample mode, that would be much faster than
   *          not to be done in down-sample mode, especially when stretching big bitmaps into small ones.
   *          Optionally a clipping region in result bitmap coordinate can be specified to limit the size of
   *          result bitmap.
   *
   * @param[in] dest_width   The width of the destination bitmap.
   * @param[in] dest_height  The height of the destination bitmap.
   * @param[in] flag         Stretch flag, It should be value @link Bitmap::e_Downsample @endlink
   *                         or @link Bitmap::e_Quadratic @endlink.
   * @param[in] clip_rect    The clipping region of destination bitmap. It can be <b>NULL</b>.
                             Default value: <b>NULL</b>.
   *
   * @return A new bitmap as stretched result.
   */
  Bitmap StretchTo(int dest_width, int dest_height, InterpolationFlag flag,
                   const RectI* clip_rect = NULL);

  /**
   * @brief Transform current bitmap (as source bitmap) into destination one.
   *
   * @details The dimension of returned bitmap always match the dimension of the matrix.
   *          If the transformation is to be done in down-sample mode, that would be much faster than
   *          not to be done in down-sample mode, especially when transforming big images into small ones.
   *          Optionally a clipping region in result bitmap coordinate can be specified to
   *          limit the size of result bitmap. The position of left-top corner (in destination coordinate) of
   *          the result bitmap would be returned as well.
   *
   * @param[in] matrix     The transformation matrix.
   * @param[in] flag       Transform flag. It should be value @link Bitmap::e_Downsample @endlink
   *                       or @link Bitmap::e_Quadratic @endlink.
   * @param[out] out_left  Output parameter that receives x-coordinate of the left-top corner of
   *                       the result bitmap in destination coordinate.
   * @param[out] out_top   Output parameter that receives y-coordinate of the left-top corner of
   *                       the result bitmap in destination coordinate.
   * @param[in] clip_rect  The clipping region of destination bitmap. It can be <b>NULL</b>.
   *                       Default value: <b>NULL</b>.
   *
   * @return A new bitmap as transformed result.
   */
  Bitmap TransformTo(const Matrix& matrix, InterpolationFlag flag,
                     int& out_left, int &out_top, const RectI* clip_rect = NULL);

  /**
   * @brief Get the mask if bitmap has mask.
   *
   * @param[in] clip_rect  The clipping region of current bitmap (as source bitmap).
   *                       It can be <b>NULL</b>. Default value: <b>NULL</b>.
   *
   * @return A new bitmap as mask bitmap. If the return value of function @link Bitmap::IsEmpty @endlink for
   *         the returned bitmap object is <b>true</b>, that means current bitmap does not have mask.
   */
  Bitmap GetMask(const RectI* clip_rect = NULL);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Bitmap(FS_HANDLE handle);
};

/**
 * Foxit PDF SDK offers following image types:<br>
 * <ul>
 * <li>BMP: bitmap image format. It only support single frame. Foxit PDF SDK supports to load image from
 *     a BMP image file, get some basic information, get its bitmap, change its bitmap and save it as
 *     an image file.</li>
 * <li>JPG: joint photographic experts group image format. It only support single frame. Foxit PDF SDK supports to
 *     load image from a JPG image file, get some basic information, get its bitmap, change its bitmap and
 *     save it as an image file. </li>
 * <li>PNG: portable network graphics image format. It only support single frame. Foxit PDF SDK supports to
 *     load image from a PNG image file, get some basic information, get its bitmap, change its bitmap and
 *     save it as an image file. </li>
 * <li>GIF: graphics interchange format. It supports multiple frames. Foxit PDF SDK supports to load image from
 *     a GIF image file, get its size, get its bitmap, change its bitmap and save it as an image file.</li>
 * <li>TIF: tagged image file format. It supports multiple frames. Foxit PDF SDK supports to load image from
 *     a TIF image file, get some basic information, get its bitmap, change its bitmap and save it as
 *     an image file. </li>
 * <li>JPX: JPEG-2000 image format. It only support single frame. Foxit PDF SDK supports to load image from
 *     a JPX image file, get its size, get its bitmap, change its bitmap and save it as an image file.</li>
 * <li>JBIG2: JBIG2 image format. It only support single frame. Foxit PDF SDK supports to load image from
 *     a JBIG2 image file, get its size, and save it as an image file. Foxit PDF SDK does not support to
 *     get its frame bitmap yet. </li>
 * </ul>
 */
class Image FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for image type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Type {
    /** @brief Unknown image type. */
    e_Unknown  =  -1,
    /**
   @brief Not have image type yet.
   @note This is only for a new image object, which is not constructed from any image file or
         retrieved from other object.
     */
    e_None  =  0,
    /** @brief Image type is BMP. */
    e_BMP  =  1,
    /** @brief Image type is JPG or JPeg. */
    e_JPG  =  2,
    /** @brief Image type is PNG. */
    e_PNG  =  3,
    /** @brief Image type is GIF. */
    e_GIF  =  4,
    /** @brief Image type is TIF or TIFF. */
    e_TIF  =  5,
    /** @brief Image type is JPX or JPeg-2000. */
    e_JPX  =  6,
    /**
   @brief Image type is JBIG2.
   @note Currently, only few functions in class @link Image @endlink support this type.
     */
    e_JBIG2  =  8
  } Type;
  

  /**
   * @brief Constructor.
   *
   * @details This constructor is to construct a new image object (without any data).
   *          The image type of this constructed image object would be @link Image::e_None @endlink.
   */
  Image();

  /**
   * @brief Constructor, from an existing image file path.
   *
   * @param[in] path  A full path of an existing image file. It should not be an empty string.
   */
  explicit Image(const char* path);

  /**
   * @brief Constructor, from an existing image file path.
   *
   * @param[in] path  A full path of an existing image file. It should not be an empty string.
   */
  explicit Image(const wchar_t* path);

  /**
   * @brief Constructor, from a memory buffer.
   *
   * @param[in] buffer  A memory buffer. The image file data should be fully loaded in this memory buffer.
   *                    It should not be <b>NULL</b>.
   * @param[in] length  The size of memory buffer. It should be above 0.
   */
  explicit Image(const void* buffer, size_t length);

  /**
   * @brief Constructor, with a file read callback object.
   *
   * @param[in] file_read  A @link common::file::ReaderCallback @endlink object which is implemented by user to load an image file.
   *                       It should not be <b>NULL</b>.
   */
  explicit Image(foxit::common::file::ReaderCallback* file_read);

  /** @brief Destructor. */
  ~Image();

  /**
   * @brief Constructor, with another image object.
   *
   * @param[in] other  Another image object.
   */
  Image(const Image& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another image object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Image& operator = (const Image& other);

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another image object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Image& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another image object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Image& other) const;

  /**
   * @brief Get image type.
   *
   * @details If current image is a new image (not constructed from any image file), its type would be @link Image::e_None @endlink.
   *
   * @return Image type. Please refer to values starting from @link Image::e_Unknown @endlink and
   *         this would be one of these values.
   */
  Type GetType() const;

  /**
   * @brief Get image width.
   *
   * @details If the image has multiple frames, usually the first frame's size will be treated as the image size.
   *
   * @return Image width..
   */
  int GetWidth() const;

  /**
   * @brief Get image height.
   *
   * @details If the image has multiple frames, usually the first frame's size will be treated as the image size.
   *
   * @return Image height.
   */
  int GetHeight() const;

  /**
   * @brief Get frame count.
   *
   * @details Currently, this function does not support an image with type @link Image::e_JBIG2 @endlink.
   *
   * @return The frame count.
   */
  int GetFrameCount() const;

  /**
   * @brief Get a frame bitmap, specified by index.
   *
   * @details Currently, this function does not support an image with type @link Image::e_JBIG2 @endlink.
   *          This function can only support to get a frame bitmap which is in following formats:<br>
   *          @link Bitmap::e_DIB8bppMask @endlink, @link Bitmap::e_DIB8bpp @endlink,
   *          @link Bitmap::e_DIBRgb @endlink, @link Bitmap::e_DIBRgb32 @endlink,
   *          @link Bitmap::e_DIBArgb @endlink.<br>
   *          For other unsupported DIB format,  this function will return a bitmap object
   *          which's function @link Bitmap::IsEmpty @endlink returns <b>true</b>.
   *
   * @param[in] index  Index of the frame. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Image::GetFrameCount @endlink.
   *
   * @return The frame bitmap. If the return value of function @link Bitmap::IsEmpty @endlink for
   *         the returned bitmap object is <b>true</b>, that means the frame's DIB format is not supported.
   */
  Bitmap GetFrameBitmap(int index) const;

  /**
   * @brief Get DPI for X-axis.
   *
   * @details Currently, this function does not support an image with type @link Image::e_JPX @endlink,
   *          @link Image::e_GIF @endlink or @link Image::e_JBIG2 @endlink.<br>
   *          For a new image (not constructed from any image file), the default DPI for X-axis is 96.
   *
   * @return DPI value for X-axis.
   */
  int GetXDPI() const;

  /**
   * @brief Get DPI for Y-axis.
   *
   * @details Currently, this function does not support an image with type @link Image::e_JPX @endlink,
   *          @link Image::e_GIF @endlink or @link Image::e_JBIG2 @endlink.<br>
   *          For a new image (not constructed from any image file), the default DPI for Y-axis is 96.
   *
   * @return DPI value for Y-axis.
   */
  int GetYDPI() const;

  /**
   * @brief Add a bitmap as a frame. (Unsupported DIB formats: @link Bitmap::e_DIBRgb565 @endlink and
   *        @link Bitmap::e_DIB8bppMask @endlink)
   *
   * @details Currently, this function does not support an image with type @link Image::e_JBIG2 @endlink,
   *          or @link Image::e_Unknown @endlink .<br>
   *          For supporting image types:
   *          <ul>
   *          <li>If current image's type is @link Image::e_TIF @endlink, @link Image::e_GIF @endlink,
   *              or @link Image::e_None @endlink, this function will add the new bitmap
   *              to be the new last frame.
   *          </li>
   *          <li>If current image's type is one of other types, which only contains single frame,
   *              this function will use the new bitmap to replace the first frame.</li>
   *          </ul>
   *
   * @param[in] bitmap  A valid bitmap as a frame to be added or set.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool AddFrame(const Bitmap& bitmap);

  /**
   * @brief Set DPI for X-axis and Y-axis.
   *
   * @details Currently, this function does not support an image with type @link Image::e_JPX @endlink,
   *          @link Image::e_GIF @endlink, or @link Image::e_JBIG2 @endlink.
   *
   * @param[in] x_dpi  DPI for X-axis. It should be above 0.
   * @param[in] y_dpi  DPI for Y-axis. It should be above 0.
   *
   * @return None.
   */
  void SetDPIs(int x_dpi, int y_dpi);

  /**
   * @brief Save current image as an image file.
   *
   * @details If the type of current image is @link Image::e_TIF @endlink, @link Image::e_GIF @endlink or
   *          @link Image::e_None @endlink, and the saved image file type does not support multiply frames,
   *          only the first frame of current image will be saved to the image file.<br>
   *          For an image object (not constructed from any image file), please ensure to
   *          add at least one valid frame bitmap to the image object before using this function;
   *          otherwise this function will fail.
   *
   * @param[in] file_path  A full path of the saved image file. It should not be an empty string.<br>
   *                       Currently, this function supports following extension names:<br>
   *                       .bmp, .jpg, .jpeg, .png, .tif, .tiff, .jpx, .jp2.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note This function does not support to save current image object just back to the image file which is used to
   *       construct current image object. In order to do so, user is recommended to do as following steps:<br>
   *       Assume that current image object is constructed from an image file named "org.bmp".
   *       <ol>
   *       <li>Use current function to save current image object to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that current image object has destructed.</li>
   *       <li>Remove "org.bmp" and rename "temp.tmp" to "org.bmp".</li>
   *       </ol>
   */
  bool SaveAs(const char* file_path);

  /**
   * @brief Save current image as an image file.
   *
   * @details If the type of current image is @link Image::e_TIF @endlink, @link Image::e_GIF @endlink or
   *          @link Image::e_None @endlink, and the saved image file type does not support multiply frames,
   *          only the first frame of current image will be saved to the image file.<br>
   *          For an image object (not constructed from any image file), please ensure to
   *          add at least one valid frame bitmap to the image object before using this function;
   *          otherwise this function will fail.
   *
   * @param[in] file_path  A full path of the saved image file. It should not be an empty string.<br>
   *                       Currently, this function supports following extension names:<br>
   *                       .bmp, .jpg, .jpeg, .png, .tif, .tiff, .jpx, .jp2.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note This function does not support to save current image object just back to the image file which is used to
   *       construct current image object. In order to do so, user is recommended to do as following steps:<br>
   *       Assume that current image object is constructed from an image file named "org.bmp".
   *       <ol>
   *       <li>Use current function to save current image object to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that current image object has destructed.</li>
   *       <li>Remove "org.bmp" and rename "temp.tmp" to "org.bmp".</li>
   *       </ol>
   */
  bool SaveAs(const wchar_t* file_path);

  /**
   * @brief Save current image as an image file.
   *
   * @details If the type of current image is @link Image::e_TIF @endlink, @link Image::e_GIF @endlink or
   *          @link Image::e_None @endlink, and the saved image file type does not support multiply frames,
   *          only the first frame of current image will be saved to the image file.<br>
   *          For an image object (not constructed from any image file), please ensure to
   *          add at least one valid frame bitmap to the image object before using this function;
   *          otherwise this function will fail.
   *
   * @param[in] file            A @link file::StreamCallback @endlink object which is implemented by user to save image file.
   * @param[in] file_extension  A full path of the saved image file. It should not be an empty string.<br>
   *                            Currently, this function supports following extension names:<br>
   *                            .bmp, .jpg, .jpeg, .png, .tif, .tiff, .jpx, .jp2.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note This function does not support to save current image object just back to the image file which is used to
   *       construct current image object. In order to do so, user is recommended to do as following steps:<br>
   *       Assume that current image object is constructed from an image file named "org.bmp".
   *       <ol>
   *       <li>Use current function to save current image object to an temporary file. Here, this temporary file is
   *           named as "temp.tmp".</li>
   *       <li>Ensure that current image object has destructed.</li>
   *       <li>Remove "org.bmp" and rename "temp.tmp" to "org.bmp".</li>
   *       </ol>
   */
  bool SaveAs(foxit::common::file::StreamCallback* file, const wchar_t* file_extension);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Image(FS_HANDLE handle);
};
}  // namespace common
}  // namespace foxit
#endif  // FS_IMAGE_H_

