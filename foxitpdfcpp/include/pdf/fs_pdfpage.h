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
 * @file fs_pdfpage.h
 * @brief Header file for PDF page related definitions and classes.
 */

#ifndef FS_PDFPAGE_H_
#define FS_PDFPAGE_H_

#include "common/fs_common.h"
#include "common/fs_image.h"
#ifndef __EMSCRIPTEN_RENDER__
#include "pdf/annots/fs_annot.h"
#endif
#include "pdf/graphics/fs_pdfgraphicsobject.h"
#include "pdf/objects/fs_pdfobject.h"
#ifndef __EMSCRIPTEN_RENDER__
#include "pdf/fs_signature.h"
#endif
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
// forward declaration
namespace interform {
class Control;
}  // namespace interform
class PDFDoc;
//class Signature;

/**
 * This class is used as a manager for graphics objects. It stores all its graphics objects in a graphics list,
 * and use POSITION object to enumerate them. A valid POSITION object can be used to get one graphics object,
 * insert new graphics object and even remove one.<br>
 * If any graphics object is changed, or graphics object is inserted/removed, function
 * @link GraphicsObjects::GenerateContent @endlink should be called to ensure that all these changes would be stored
 * to PDF document. Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.<br>
 * A PDF page's content usually consists of a sequence of graphics objects, that means PDF page is used like a manager
 * for graphics objects as well. So class @link pdf::PDFPage @endlink is derived from class @link GraphicsObjects @endlink in order that
 * class @link PDFPage @endlink can retrieve its graphics object.<br>
 * A form XObject, a kind of graphics object, is a self-contained description of any  sequence of graphics objects,
 * so function @link graphics::FormXObject::GetGraphicsObjects @endlink can be used to retrieve a GraphicsObjects object
 * from a form XObject in order to manage graphics objects which are contained in a form XObject.
 *
 * @see @link PDFPage @endlink
 * @see @link graphics::FormXObject @endlink
 * @see @link graphics::GraphicsObject @endlink
 */
class GraphicsObjects : public Base {
 public:
   // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit GraphicsObjects(FS_HANDLE handle = NULL);
  /** @brief Destructor. */
  virtual ~GraphicsObjects();

  /**
   * @brief Constructor, with another @link GraphicsObjects @endlink object.
   *
   * @param[in] other  Another @link GraphicsObjects @endlink object.
   */
  GraphicsObjects(const GraphicsObjects& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another @link GraphicsObjects @endlink object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  GraphicsObjects& operator=(const GraphicsObjects& other);

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
   * @param[in] other  Another @link GraphicsObjects @endlink object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const GraphicsObjects& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another @link GraphicsObjects @endlink object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const GraphicsObjects& other) const;

  /**
   * @brief Get the position of first graphics object in graphics object list, based on type filter.
   *
   * @details After getting a position in the graphics object list, then user can call function
   *          @link GraphicsObjects::GetGraphicsObject @endlink to get the graphics object with this position.
   *
   * @param[in] filter  Type filter that specifies which kind of graphics object is to be gotten.
   *                    Please refer to values starting from @link graphics::GraphicsObject::e_TypeAll @endlink and
   *                    this should be one of these values.
   *                    @link graphics::GraphicsObject::e_TypeAll @endlink means for all kinds of
   *                    graphics objects. Default value: @link graphics::GraphicsObject::e_TypeAll @endlink.
   *
   * @return A POSITION object that represents the position of first graphics object in graphics object list.
   *         <b>NULL</b> or 0 means there is no graphics object.
   */
  POSITION GetFirstGraphicsObjectPosition(graphics::GraphicsObject::Type filter = graphics::GraphicsObject::e_TypeAll) const;
  /**
   * @brief Get the position of next graphics object in graphics object list,
   *        based on type filter and specified current position.
   *
   * @details After getting a position in the graphics object list, then user can call function
   *          @link GraphicsObjects::GetGraphicsObject @endlink to get the graphics object with this position.
   *
   * @param[in] position  A POSITION object that indicates a position in the graphics object list,
   *                      whose next position is to be gotten. It should not be <b>NULL</b> or 0.
   * @param[in] filter    Type filter that specifies which kind of graphics object is to be gotten.
   *                      Please refer to values starting from @link graphics::GraphicsObject::e_TypeAll @endlink and
   *                      this should be one of these values.
   *                      @link graphics::GraphicsObject::e_TypeAll @endlink means for all kinds of
   *                      graphics objects. Default value: @link graphics::GraphicsObject::e_TypeAll @endlink.
   *
   * @return A POSITION object that represents the position of next graphics object in graphics object list.
   *         <b>NULL</b> or 0 means parameter <i>position</i> is the last position in graphics object list.
   */
  POSITION GetNextGraphicsObjectPosition(POSITION position, graphics::GraphicsObject::Type filter = graphics::GraphicsObject::e_TypeAll) const;

  /**
   * @brief Get the position of last graphics object in graphics object list, based on type filter.
   *
   * @details After getting a position in the graphics object list, then user can call function
   *          @link GraphicsObjects::GetGraphicsObject @endlink to get the graphics object with this position.
   *
   * @param[in] filter  Type filter that specifies which kind of graphics object is to be gotten.
   *                    Please refer to values starting from @link graphics::GraphicsObject::e_TypeAll @endlink and
   *                    this should be one of these values.
   *                    @link graphics::GraphicsObject::e_TypeAll @endlink means for all kinds of
   *                    graphics objects. Default value: @link graphics::GraphicsObject::e_TypeAll @endlink.
   *
   * @return A POSITION object that represents the position of last graphics object in graphics object list.
   *         <b>NULL</b> or 0 means there is no graphics object.
   */
  POSITION GetLastGraphicsObjectPosition(graphics::GraphicsObject::Type filter = graphics::GraphicsObject::e_TypeAll) const;

  /**
   * @brief Get the position of previous graphics object in graphics object list,
   *        based on type filter and specified current position.
   *
   * @details After getting a position in the graphics object list, then user can call function
   *          @link GraphicsObjects::GetGraphicsObject @endlink to get the graphics object with this position.
   *
   * @param[in] position  A POSITION object that indicates a position in the graphics object list,
   *                      whose previous position is to be gotten. It should not be <b>NULL</b> or 0.
   * @param[in] filter    Type filter that specifies which kind of graphics object is to be gotten.
   *                      Please refer to values starting from @link graphics::GraphicsObject::e_TypeAll @endlink and
   *                      this should be one of these values.
   *                      @link graphics::GraphicsObject::e_TypeAll @endlink means for all kinds of
   *                      graphics objects. Default value: @link graphics::GraphicsObject::e_TypeAll @endlink.
   *
   * @return A POSITION object that represents the position of previous graphics object in graphics object list.
   *         <b>NULL</b> or 0 means parameter <i>position</i> is already in the first position in graphics object list.
   */
  POSITION GetPrevGraphicsObjectPosition(POSITION position, graphics::GraphicsObject::Type filter = graphics::GraphicsObject::e_TypeAll) const;

  /**
   * @brief Get the graphics object by position in graphics object list.
   *
   * @param[in] position  A POSITION object that indicates the position in the graphics object list.
   *                      It should not be <b>NULL</b> or 0.
   *
   * @return A @link graphics::GraphicsObject @endlink object.
   */
  graphics::GraphicsObject* GetGraphicsObject(POSITION position) const;

  /**
   * @brief Insert a graphics object after the specified position.
   *
   * @param[in] position_insert_after  Used to specify the position, in order to insert
   *                                   parameter <i>graphics_object</i> after this position.
   *                                   <b>NULL</b> means that parameter <i>graphics_object</i>
   *                                   will be inserted before all objects.
   * @param[in] graphics_object        A graphics object to be inserted. User should ensure that parameter
   *                                   <i>graphics_object</i> belongs to the same PDF document
   *                                   as current graphics objects.
   *
   * @return The new position of the inserted graphics object.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  POSITION InsertGraphicsObject(POSITION position_insert_after, graphics::GraphicsObject* graphics_object);

  /**
   * @brief Remove a graphics object.
   *
   * @details To remove a graphics object by position (function
   *          @link GraphicsObjects::RemoveGraphicsObjectByPosition @endlink) is more direct and effective than
   *          to remove a graphics object directly (function @link GraphicsObjects::RemoveGraphicsObject @endlink).
   *
   * @param[in] graphics_object  A graphics object to be removed. Please ensure this graphics object belongs to
   *                             current graphics objects.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  bool RemoveGraphicsObject(graphics::GraphicsObject* graphics_object);

  /**
   * @brief Remove a graphics object by position.
   *
   * @details To remove a graphics object by position (function
   *          @link GraphicsObjects::RemoveGraphicsObjectByPosition @endlink) is more direct and effective than to
   *          remove a graphics object directly (function @link GraphicsObjects::RemoveGraphicsObject @endlink).
   *
   * @param[in] position  Used to specify the position of a graphics object, to be removed.
   *                      It should not be <b>NULL</b> or 0.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *
   * @note When this function succeeds, function @link GraphicsObjects::GenerateContent @endlink should be called.
   *       Please refer to function @link GraphicsObjects::GenerateContent @endlink for more details.
   */
  bool RemoveGraphicsObjectByPosition(POSITION position);

  /**
   * @brief Get the count of graphics objects in graphics object list.
   *
   * @return Count of graphics object in graphics object list.
   *
   */
  int GetGraphicsObjectCount() const;

  /**
   * @brief Get the index of a specified graphics object in graphics object list.
   *
   * @param[in] graphics_object  A graphics object whose index is to be retrieved. Please ensure that
   *                             input graphics object belongs to current graphics objects.
   *
   * @return Index of specified graphics object in graphics object list.
   *         -1 means parameter <i>graphics_object</i> does not belong to current graphics object list.
   */
  int GetGraphicsObjectIndex(graphics::GraphicsObject* graphics_object) const;

  /**
   * @brief Get a graphics object by index.
   *
   * @param[in] index  Index of a graphics object to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link GraphicsObjects::GetGraphicsObjectCount @endlink.
   *
   * @return A graphics object.
   */
  graphics::GraphicsObject* GetGraphicsObject(int index) const;

  /**
   * @brief Generate contents of current graphics objects.
   *
   * @details If any graphics object is changed, or graphics object is inserted/removed, this function should
   *          be called before saving related PDF document to ensure that all these changes would be stored to
   *          PDF document. Since it may takes a long time to generate content, user is not recommended to
   *          call this function frequently, but only call this function when necessary, for example,
   *          just before the related PDF document is to be saved.<br>
   *          When this function succeeds, and current graphics objects represents a PDF page, user is recommended to
   *          re-parse the PDF page by function @link PDFPage::StartParse @endlink with parameter <i>is_reparse</i> <b>true</b>
   *          before doing some operation about page content; otherwise the result of the operation may be unexpected.
   *          For example, if render the PDF page without re-parsing PDF page after this function succeeds, the page content
   *          may not be rendered as expected or unexpected error may occurs.
   *          Please refer to function @link PDFPage::StartParse @endlink for more details about re-parsing a PDF page.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool GenerateContent();
};

/**
 * A PDF page is defined in <b>PDF coordinate system</b> which uses the lower-left corner of the page as
 * origin point (0, 0).<br>
 * Usually, a PDF page object is retrieved from a PDF document by function @link PDFDoc::GetPage @endlink.
 * For most case, a PDF page should be parsed first and then be used. Function @link PDFPage::IsParsed @endlink can
 * be used to judge whether the PDF page has been parsed or not. For a unparsed page, please use function
 * @link PDFPage::StartParse @endlink to parse it.<br>
 * This class offers functions to get/set data of a PDF page, such as page width/height, page rotation,
 * display matrix and so on. Also, this class offers functions to retrieve PDF annotations:
 * <ul>
 * <li>To get a PDF annotation, use function @link pdf::PDFPage::GetAnnot @endlink, @link PDFPage::GetAnnotAtPoint @endlink,
 *     or @link PDFPage::GetAnnotAtDevicePoint @endlink.</li>
 * <li>To add a new PDF annotation, use function @link PDFPage::AddAnnot @endlink.</li>
 * <li>To remove a PDF annotation, use function @link PDFPage::RemoveAnnot @endlink.</li>
 * </ul>
 * Class @link pdf::PDFPage @endlink is derived from class @link pdf::GraphicsObjects @endlink, so class PDFPage also offers functions to
 * retrieve PDF graphics objects:
 * <ul>
 * <li>To get a PDF graphics object, use functions @link GraphicsObjects::GetFirstGraphicsObjectPosition @endlink,
 *     @link GraphicsObjects::GetNextGraphicsObjectPosition @endlink,
 *     @link GraphicsObjects::GetLastGraphicsObjectPosition @endlink,
 *     @link pdf::GraphicsObjects::GetPrevGraphicsObjectPosition @endlink and @link GraphicsObjects::GetGraphicsObject @endlink
 *     (these functions are inherited from parent class), or @link PDFPage::GetGraphicsObjectAtPoint @endlink.
 * </li>
 * <li>To insert a PDF graphics object, use function @link GraphicsObjects::InsertGraphicsObject @endlink
 *     (inherited from parent class).</li>
 * <li>To remove a PDF graphics object, use functions @link GraphicsObjects::RemoveGraphicsObjectByPosition @endlink
 *     or @link GraphicsObjects::RemoveGraphicsObject @endlink (these functions are inherited from parent class).</li>
 * </ul>
 * This class object can also be used to construct objects of other classes in order to access specified information
 * in PDF page:
 * <ul>
 * <li>To access text content in PDF page, please construct a @link TextPage @endlink with PDF page object.</li>
 * <li>To do reflowing, please construct a @link ReflowPage @endlink with PDF page object.</li>
 * <li>To access additional actions, please construct an @link actions::AdditionalAction @endlink object with PDF page object.</li>
 * <li>To manage the tab order of annotations in PDF page, please construct a @link TabOrderMgr @endlink with PDF page object.</li>
 * </ul>
 *
 * @see @link PDFDoc @endlink
 * @see @link GraphicsObjects @endlink
 * @see @link TextPage @endlink
 * @see @link ReflowPage @endlink
 * @see @link actions::AdditionalAction @endlink
 * @see @link TabOrderMgr @endlink
 */
class PDFPage FS_FINAL : public GraphicsObjects {
 public:
  /**
   * @brief Enumeration for parsing flags used for PDF page.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _ParseFlags {
    /** @brief Parsing flag for normal mode, which means to parse all the contents in a PDF page. */
    e_ParsePageNormal = 0x0000,
    /** @brief Parsing flag for text-only mode. */
    e_ParsePageTextOnly = 0x0001
  } ParseFlags;
  
  /**
   * @brief Enumeration for calculating margin mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _CalcMarginMode {
    /** @brief Calculate margin according to bounding box of all contents. */
    e_CalcContentsBox  = 0,
    /** @brief Calculate margin by detecting paths or images. */
    e_CalcDetection = 1
  } CalcMarginMode;
  
  /**
   * @brief Enumeration for flatten options.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _FlattenOptions {
    /** @brief Flatten all contents of a PDF page. */
    e_FlattenAll        = 0,
    /** @brief Flatten a PDF page without annotations.  */
    e_FlattenNoAnnot      = 0x0001,
    /** @brief Flatten a PDF page without form controls.  */
    e_FlattenNoFormControl  = 0x0002
  } FlattenOptions;
  
  /**
   * @brief Enumeration for page box type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _BoxType {
    /**
   @brief Media Box for page boundary.
   @details The boundary of the physical medium on which page is to be displayed or printed.
     */
    e_MediaBox = 0,
    /**
   @brief Crop Box for page boundary.
   @details The region to which the contents of page are to be clipped (cropped) while displaying or printing.
     */
    e_CropBox = 1,
    /**
   @brief Trim Box for page boundary.
   @details The region to which the contents of page should be clipped while outputting in a production environment.
     */
    e_TrimBox = 2,
    /**
   @brief Art Box for page boundary.
   @details The intended dimensions of a finished page after trimming.
     */
    e_ArtBox = 3,
    /**
   @brief Bleed Box for page boundary.
   @details The extent of page's meaningful content (including potential white space) as intended by page's creator.
     */
    e_BleedBox = 4
  } BoxType;
  
  /**
   * @brief Enumeration for page size type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Size {
    /** @brief Page size: letter. */
    e_SizeLetter = 1,
    /**  @brief Page size: legal. */
    e_SizeLegal = 2,
    /** @brief Page size: A2. */
    e_SizeA2 = 3,
    /** @brief Page size: A3. */
    e_SizeA3 = 4,
    /** @brief Page size: A4. */
    e_SizeA4 = 5,
    /** @brief Page size: A5. */
    e_SizeA5 = 6,
    /** @brief Page size: A6. */
    e_SizeA6 = 7,
    /** @brief Page size: B2. */
    e_SizeB2 = 8,
    /** @brief Page size: B3. */
    e_SizeB3 = 9,
    /** @brief Page size: B4. */
    e_SizeB4 = 10,
    /** @brief Page size: B5. */
    e_SizeB5 = 11,
    /** @brief Page size: B6. */
    e_SizeB6 = 12
  } Size;
  
  /**
   * @brief Constructor, from a PDF dictionary which represents a PDF page and the PDF document
   *        which contains the dictionary..
   *
   * @param[in] document   A valid PDF document.
   * @param[in] page_dict  A PDF dictionary of a PDF page. It should belong to the PDF document specified
   *                       by parameter <i>document</i>.
   */
  PDFPage(const PDFDoc& document, objects::PDFDictionary* page_dict);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDFPage(FS_HANDLE handle = NULL);

  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] other  Parent class object.
   */
  explicit PDFPage(const foxit::pdf::GraphicsObjects& other);

  /** @brief Destructor. */
  virtual ~PDFPage();

  /**
   * @brief Get the PDF document, to which current PDF page belongs.
   *
   * @return A PDF document object.
   */
  PDFDoc GetDocument() const;
  /**
   * @brief Get the page dictionary.
   *
   * @return The page dictionary object.
   */
  objects::PDFDictionary* GetDict() const;

  /**
   * @brief Check if current page has been parsed or not.
   *
   * @return <b>true</b> means current page has been parsed,
   *         while <b>false</b> means current page has not been parsed yet.
   */
  bool IsParsed() const;
  /**
   * @brief Start to parse current page.
   *
   * @details It may take a long time to parsing a PDF page, so Foxit PDF SDK uses a progressive process to do this.
   *          All the resources of page content will be loaded after the PDF page is parsed.
   *
   * @param[in] flags       Parsing flags. Please refer to values starting from @link PDFPage::e_ParsePageNormal @endlink and
   *                        this should be one or a combination of these values.
   *                        Default value: @link PDFPage::e_ParsePageNormal @endlink.
   * @param[in] pause       Pause callback object which decides if the parsing process needs to be paused.
   *                        This can be <b>NULL</b> which means not to pause during the parsing process.
   *                        If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                        Default value: <b>NULL</b>.
   * @param[in] is_reparse  <b>true</b> means to re-parse current page, while <b>false</b> means not to
   *                        re-parse current page. Default value: <b>false</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   *
   * @note When parameter <i>is_reparse</i> is set to <b>true</b>, that means to re-parse current PDF page,
   *       and all the retrieved graphics object's position (as POSITION object) and graphics object (as
   *       @link graphics::GraphicsObject @endlink object) will be invalid.<br>
   *       Application needs to get graphics objects again after re-parsing a PDF page.
   */
  common::Progressive StartParse(uint32 flags = PDFPage::e_ParsePageNormal, common::PauseCallback* pause = NULL,
                                 bool is_reparse = false);

  /**
   * @brief Get page index.
   *
   * @return Page index, starting from 0 and within the count of pages in related PDF document.
   */
  int GetIndex() const;
  /**
   * @brief Get the page height.
   *
   * @return Page height.
   */
  float GetHeight() const;
  /**
   * @brief Get the page width.
   *
   * @return Page width
   */
  float GetWidth() const;
  /**
   * @brief Get the page rotation.
   *
   * @return Page rotation value. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *         this would be one of these values.
   */
  common::Rotation GetRotation() const;
  /**
   * @brief Load the thumbnail bitmap.
   *
   * @return The thumbnail bitmap of current page. If the return value of function @link common::Bitmap::IsEmpty @endlink for
   *         the returned bitmap object is <b>true</b>, that means no thumbnail can be found.
   */
  common::Bitmap LoadThumbnail();

  /**
   * @brief Get the display matrix of PDF page, from [PDF coordinate system] (@ref PDFPage) to
   *        targeted device coordinate system.
   *
   * @param[in] left    Left position of the transformation area in device coordinate system, commonly in pixels.
   * @param[in] top     Top position of the transformation area in device coordinate system, commonly in pixels.
   * @param[in] width   Width of the transformation area in device coordinate system, commonly in pixels.
   * @param[in] height  Height of the transformation area in device coordinate system, commonly in pixels.
   * @param[in] rotate  Rotation value. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                    this should be one of these values except @link common::e_RotationUnknown @endlink.
   *
   * @return The display matrix used for current PDF page.
   */
  Matrix GetDisplayMatrix(int left, int top, int width, int height, common::Rotation rotate);

  /**
   * @brief Calculate the content area of PDF page.
   *
   * @details Before using this function, please ensure current page has been parsed.
   *
   * @param[in] mode  Calculation mode. It should be one of following values:
   *                  <ul>
   *                  <li>@link PDFPage::e_CalcContentsBox @endlink means to
   *                      calculate margin according to bounding box of all contents.</li>
   *                  <li>@link PDFPage::e_CalcDetection @endlink means to
   *                      calculate margin by detecting paths or images.</li>
   *                  </ul>
   *
   * @return The minimal rectangle which contains the visible page content.
   */
  RectF CalcContentBBox(CalcMarginMode mode);
#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Get the count of annotations.
   *
   * @return The count of annotations.
   */
  int GetAnnotCount();

  /**
   * @brief Get an annotation by index.
   *
   * @param[in] index  Annotation index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFPage::GetAnnotCount @endlink.
   *
   * @return An annotation object.
   */
  annots::Annot GetAnnot(int index);

  /**
   * @brief Get the annotation at a specified position, in [PDF coordinate system] (@ref PDFPage).
   *
   * @details If there are several annotations in this specified position, this function will always return
   *          the topmost annotation. Annotations with flag @link annots::Annot::e_FlagNoView @endlink or
   *          @link annots::Annot::e_FlagReadOnly @endlink or @link annots::Annot::e_FlagHidden @endlink or
   *          @link annots::Annot::e_FlagInvisible @endlink will not be retrieved by this function.
   *
   * @param[in] position   The specified position, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] tolerance  Tolerance value. Valid range: 0.0f to 30.0f.
   *
   * @return An annotation object. If the return value of function @link annots::Annot::IsEmpty @endlink for
   *         the returned annotation object is <b>true</b>, that means no PDF annotation can be found.
   */
  annots::Annot GetAnnotAtPoint(const PointF& position, float tolerance);

  /**
   * @brief Get the annotation at a specified position, in device coordination system.
   *
   * @details If there are several annotations in this specified position, this function will always return
   *          the topmost annotation. Annotations with flag @link annots::Annot::e_FlagNoView @endlink or
   *          @link annots::Annot::e_FlagReadOnly @endlink or @link annots::Annot::e_FlagHidden @endlink or
   *          @link annots::Annot::e_FlagInvisible @endlink will not be retrieved by this function.
   *
   * @param[in] position   The specified position, in device coordinate system.
   * @param[in] tolerance  Tolerance value. Valid range: 0.0f to 30.0f.
   * @param[in] matrix     The transformation matrix. Usually this is returned by function
   *                       @link PDFPage::GetDisplayMatrix @endlink. If this is <b>NULL</b>, current function will
   *                       have the same feature as function @link PDFPage::GetAnnotAtPoint @endlink.
   *                       Default value: <b>NULL</b>.
   *
   * @return An annotation object. If the return value of function @link annots::Annot::IsEmpty @endlink for
   *         the returned annotation object is <b>true</b>, that means no PDF annotation can be found.
   */
  annots::Annot GetAnnotAtDevicePoint(const PointF& position, float tolerance, const Matrix* matrix = NULL);

  /**
   * @brief Add an annotation to PDF page.
   *
   * @details Currently, this function can support to add most annotation types except:<br>
   *          Widget, Sound, Movie, PrinterMark, TrapNet, Watermark, 3D, PSInk, Redact.<br>
   *          Attention:
   *          <ul>
   *          <li>Widget annotation are used to represent the appearance of a form field,
   *              including signature field:<br>
   *              For signature field, function @link PDFPage::AddSignature @endlink can be called to
   *              add a new signature object. <br>
   *              For other types of form field, function @link interform::Form::AddControl @endlink can be called to
   *              add a new form field (with form control).<br>
   *          </li>
   *          <li>PSInk annotation should be converted from a PSI object by function @link PSI::ConvertToPDFAnnot @endlink.
   *          </li>
   *          <li>Redact annotation should be added to mark areas in PDF page by function
   *              @link addon::Redaction::MarkRedactAnnot @endlink.
   *          </li>
   *          <li>For supported annotations types, if user does not set any properties of the newly created annotation
   *              (except the required properties) and directly calls function
   *              @link annots::Annot::ResetAppearanceStream @endlink, default appearance will be used. Please refer to
   *              comment of concrete annotation class for more details of their own default appearance.
   *          </li>
   *          </ul>
   *
   * @param[in] type  The type of annotation to be added. Please refer to values starting from
   *                  @link annots::Annot::e_Note @endlink and this should be one of these values
   *                  except @link annots::Annot::e_PSInk @endlink, @link annots::Annot::e_Sound @endlink,
   *                  @link annots::Annot::e_Movie @endlink, @link annots::Annot::e_Widget @endlink,
   *                  @link annots::Annot::e_PrinterMark @endlink, @link annots::Annot::e_TrapNet @endlink,
   *                  @link annots::Annot::e_Watermark @endlink, @link annots::Annot::e_3D @endlink.
   * @param[in] rect  Rectangle of the new annotation.
   *                  <ul>
   *                  <li>For annotation in following type, they needs a valid rectangle when being added.
   *                      So for them, <i>rect</i> should be valid:<br>
   *                      @link annots::Annot::e_Note @endlink, @link annots::Annot::e_Link @endlink,
   *                      @link annots::Annot::e_Square @endlink, @link annots::Annot::e_Circle @endlink,
   *                      @link annots::Annot::e_FreeText @endlink, @link annots::Annot::e_Stamp @endlink,
   *                      @link annots::Annot::e_Caret @endlink, @link annots::Annot::e_FileAttachment @endlink,
   *                      @link annots::Annot::e_Screen @endlink.</li>
   *                  <li>For rest supported annotation types, their rectangle will be updated when
   *                      other required properties of them have been set. So for these annotations,
   *                      <i>rect</i> can be an empty rectangle. If an invalid rectangle is passed to <i>rect</i>,
   *                      an empty rectangle will be used instead.</li>
   *                  </ul>
   *
   * @return The newly created annotation object.
   */
  annots::Annot AddAnnot(annots::Annot::Type type, const RectF& rect);

  /**
   * @brief Remove an annotation.
   *
   * @details This function can remove any annotation returned by getting function or adding function.<br>
   *          But for widget annotation, this function can only remove an independent widget annotation.
   *          If the widget annotation is associated with a form field, this function cannot remove it and
   *          will throw exception @link foxit::e_ErrUnsupported @endlink.<br>
   *          For a widget annotation associated with a form field, please call function
   *          @link interform::Form::RemoveControl @endlink to remove it along with associated form control.
   *
   * @param[in] annot  An annotation object to be removed. It should be in current PDF page.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveAnnot(const annots::Annot& annot);

  /**
   * @brief Change specified annotation to be the first one of all annotations.
   *
   * @details In PDF page, all the annotations are managed in an annotation list. In the annotation list,
   *          annotations with small indexes (as in the font part of the list) will be drawn to the page first,
   *          and annotations with large indexes (as in the last part of the list) will be drawn to the page later.
   *          So, in a page, if an annotation is shown on the top of other annotations in z-order, that means
   *          its index is larger than other annotations in the annotation list.<br>
   *          This function is used to move an annotation from current index position to the first position
   *          in the annotation list, in order to move the annotation to the bottom in z-order when displayed.
   *
   * @param[in] annot  An annotation object to be moved to first. It should be in current PDF page.
   *
   * @return None.
   */
  void MoveAnnotToFirst(const annots::Annot& annot);

  /**
   * @brief Change specified annotation to be the last one of all annotations.
   *
   * @details In PDF page, all the annotations are managed in an annotation list. In the annotation list,
   *          annotations with small indexes (as in the font part of the list) will be drawn to the page first,
   *          and annotations with large indexes (as in the last part of the list) will be drawn to the page later.
   *          So, in a page, if an annotation is shown on the top of other annotations in z-order, that means
   *          its index is larger than other annotations in the annotation list.<br>
   *          This function is used to move an annotation from current index position to the last position
   *          in the annotation list, in order to move the annotation to the top in z-order when displayed.
   *
   * @param[in] annot  An annotation object to be moved to last. It should be in current PDF page.
   *
   * @return None.
   */
  void MoveAnnotToLast(const annots::Annot& annot);

  /**
   * @brief Exchange the indexes of current annotation and its previous annotation.
   *
   * @details In PDF page, all the annotations are managed in an annotation list. In the annotation list,
   *          annotations with small indexes (as in the font part of the list) will be drawn to the page first,
   *          and annotations with large indexes (as in the last part of the list) will be drawn to the page later.
   *          So, in a page, if an annotation is shown on the top of other annotations in z-order, that means
   *          its index is larger than other annotations in the annotation list.<br>
   *          This function is used to exchange the indexes position of current annotation and its previous annotation
   *          in the annotation list, in order to move the annotation to a lower level in z-order when displayed.
   *
   * @param[in] annot  An annotation object to be moved. It should be in current PDF page.
   *
   * @return None.
   */
  void  MoveAnnotToPrev(const annots::Annot& annot);

  /**
   * @brief Exchange the indexes of current annotation and its next annotation.
   *
   * @details In PDF page, all the annotations are managed in an annotation list. In the annotation list,
   *          annotations with small indexes (as in the font part of the list) will be drawn to the page first,
   *          and annotations with large indexes (as in the last part of the list) will be drawn to the page later.
   *          So, in a page, if an annotation is shown on the top of other annotations in z-order, that means
   *          its index is larger than other annotations in the annotation list.<br>
   *          This function is used to exchange the indexes position of current annotation and its next annotation
   *          in the annotation list, in order to move the annotation to a lower level in z-order when displayed.
   *
   * @param[in] annot  An annotation object to be moved. It should be in current PDF page.
   *
   * @return None.
   */
  void  MoveAnnotToNext(const annots::Annot& annot);
#endif
  /**
   * @brief Check whether current PDF page has transparency or not.
   *
   * @details Before using this function, please ensure current page has been parsed.
   *
   * @return <b>true</b> means current page has transparency,
   *         while <b>false</b> means current page does not have transparency.
   */
  bool HasTransparency();

  /**
   * @brief Flatten current PDF page: annotations or form fields may be made to be a part of the page contents
   *        according to specified options.
   *
   * @details Annotation flag can decide if an annotation can be displayed or if an annotation can be printed.
   *          This also affects the flattened result:
   *          <ul>
   *          <li>If the flattened result is used for displaying, only annotations which can be displayed
   *              will be flattened to be a part of page contents.</li>
   *          <li>If the flattened result is used for printing, only annotations which can be printed
   *              will be flattened to be a part of page contents.</li>
   *          </ul>
   *          Form field's appearance is represents by widget annotation which is a kind of annotation and
   *          treated as form control in Foxit PDF SDK. So annotation flag affects a form field as well
   *          when a form field is to be flattened. For more details about annotation flag, please refer to
   *          values starting from @link annots::Annot::e_FlagInvisible @endlink and Section 8.4.2 "Annotation Flags"
   *          in <PDF Reference 1.7>.<br>
   *          After an annotation or a form field is flattened, it will not be an annotation or a form field any more.
   *          After flattening current page successfully, user should re-parse this page by function
   *          @link PDFPage::StartParse @endlink.
   *
   * @param[in] for_display  Decide the purpose of the flattened result:
   *                         <b>true</b> means the flatten result is used for display only,
   *                         and <b>false</b> means the flatten result is used for print only.
   * @param[in] options      The flatten options. Please refer to values starting from @link PDFPage::e_FlattenAll @endlink
   *                         and this should one or a combination of them.<br>
   *                         Specially, if @link PDFPage::e_FlattenNoAnnot @endlink and @link PDFPage::e_FlattenNoFormControl @endlink
   *                         are used together, that means nothing is to be flatten to page and this function will
   *                         return <b>true</b> directly.
   *                         Default value: @link PDFPage::e_FlattenAll @endlink.
   *
   * @return <b>true</b> means current page is flattened successfully, while <b>false</b> means failure.
   */
  bool Flatten(bool for_display, uint32 options = PDFPage::e_FlattenAll);
#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Flatten an annotation: the annotation is made to be a part of the page contents and be removed then.
   *  
   * @details After flattening the annotation successfully, user should re-parse this page by function @link PDFPage::StartParse @endlink.
   *
   * @param[in] annot  An annotation to be flattened and removed.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool FlattenAnnot(annots::Annot annot);

  /**
   * @brief Group all the input markup annotations together.
   *
   * @details Markup annotations can be grouped. The group consists of a primary annotation and one or
   *          more subordinate annotations. Some entries in the primary annotation are treated as group attributes
   *          that should apply to the group as a whole; the corresponding entries in the subordinate annotations
   *          should be ignored. These entries are contents, last modification time, fill color/border color,
   *          title, pop-up annotation, creation time, subject, and open status. So user should
   *          respect the group property: when a property of an annotation in the group is changed,
   *          the other annotations in the same group should be changed too.<br>
   *          Operations that manipulate any annotation in a group, such as movement, cut, and copy, should be
   *          treated by viewer applications as acting on the entire group.
   *
   * @param[in] annot_array   An array of Markup objects that specifies markup annotations
   *                          which are to be grouped together. This array should contains at least
   *                          2 markup annotations, and all the markup annotations in this array should be
   *                          different from others. All the markup annotations in this array should be
   *                          in current page. <br>
   *                          Specially, if a markup annotation in this array is already in another group,
   *                          that group will be set to the new group with the new header as well.
   * @param[in] header_index  The index that specifies a markup annotation in parameter <i>annot_array</i> to
   *                          be the header of the group. Valid range: from 0 to (<i>ammot_count</i> -1).
   *
   * @return <b>true</b> means group input markup annotations together successfully, while <b>false</b> means failure.
   */
  bool SetAnnotGroup(const annots::MarkupArray& annot_array, int header_index);

  /**
   * @brief Add an ordinary signature to PDF page.
   *
   * @details For a new ordinary signature, its filter will be "Adobe.PPKLite" and sub filter will be "adbe.pkcs7.detached"
   *          by default. Please refer to class @link Signature @endlink for more details about signature's filter and
   *          sub-filter.<br>
   *          Before signing the new signature, user can also call setting functions of class @link Signature @endlink
   *          to set other information used for signing and signed appearance.
   *
   * @param[in] rect  Rectangle position for the new signature, in [PDF coordinate system] (@ref PDFPage).
   *                  It should be a valid rectangle in [PDF coordinate system] (@ref PDFPage).
   *
   * @return The newly added signature object.
   */
  foxit::pdf::Signature AddSignature(const foxit::RectF& rect);

  /**
   * @brief Add an ordinary signature to PDF page.
   *
   * @details For a new ordinary signature, its filter will be "Adobe.PPKLite" and sub filter will be "adbe.pkcs7.detached"
   *          by default. Please refer to class @link Signature @endlink for more details about signature's filter and
   *          sub-filter.<br>
   *          Before signing the new signature, user can also call setting functions of class @link Signature @endlink
   *          to set other information used for signing and signed appearance.
   *
   * @param[in] rect       Rectangle position for the new signature, in [PDF coordinate system] (@ref PDFPage).
   *                       It should be a valid rectangle in [PDF coordinate system] (@ref PDFPage).
   * @param[in] field_name The signature field name.  This can be an empty string.
   *
   * @return The newly added signature object.
   */
  foxit::pdf::Signature AddSignature(const foxit::RectF& rect, const foxit::WString& field_name);

  /**
   * @brief Add a signature to PDF page.
   *
   * @details For a new ordinary signature, its filter will be "Adobe.PPKLite" and sub filter will be "adbe.pkcs7.detached"
   *          by default.
   *          For a new time stamp signature, its fileter will be "Adobe.PPKLite" and sub filter will be "ETSI.RFC3161" by default.
   *          Please refer to class @link Signature @endlink for more details about signature's filter and sub-filter.<br>
   *          Before signing the new signature, user can also call setting functions of class @link Signature @endlink
   *          to set other information used for signing and signed appearance.
   *
   * @param[in] rect            Rectangle position for the new signature, in [PDF coordinate system] (@ref PDFPage).
   *                            If parameter <i>signature_type</i> is @link Signature::e_SignatureTypeTimeStamp @endlink,
   *                            this rectangle will be ignored; otherwise, this should be a valid rectangle
   *                            in [PDF coordinate system] (@ref PDFPage).
   * @param[in] field_name      The signature field name. This can be an empty string.
   * @param[in] signature_type  Signature type. Please refer to values starting from
   *                            @link Signature::e_SignatureTypeOrdinary @endlink and this should be one of these values.
   *
   * @return The newly added signature object.
   */
  foxit::pdf::Signature AddSignature(const foxit::RectF& rect, const foxit::WString& field_name, foxit::pdf::Signature::SignatureType signature_type);
#endif
  
  /**
   * @brief Check whether the current page has any watermark (not including Foxit PDF SDK trial watermark).
   *
   * @details Before using this function, please ensure current page has been parsed.
   *
   * @return <b>true</b> means the current page has watermark, and <b>false</b> means
   *         the current page has no watermark.
   */
  bool HasWatermark();

  /**
   * @brief Remove all watermarks.
   *
   * @details Before using this function, please ensure current page has been parsed.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveAllWatermarks();

  /**
   * @brief Set page rotation.
   *
   * @param[in] rotate  New page rotation value. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                    this should be one of these values except @link common::e_RotationUnknown @endlink.
   *
   * @return None.
   */
  void SetRotation(common::Rotation rotate);

  /**
   * @brief Set page width and height.
   *
   * @details When changing page width/height, Foxit PDF SDK will always do as following:<br>
   *          First, choose "page rotation is 0" as the basis page status and choose the
   *          left-bottom corner of the page (with page rotation is 0) as the basis point.
   *          And then, always change the position of top page boundary and right page boundary
   *          (with page rotation is 0) to change page size.
   *
   * @param[in] width   New page width. It should be a positive value and the unit is 1/72 inch.
   * @param[in] height  New page height. It should be a positive value and the unit is 1/72 inch.
   *
   * @return None.
   */
  void SetSize(float width, float height);
  /**
   * @brief Set page size type.
   *
   * @details When changing page size, Foxit PDF SDK will always do as following:<br>
   *          First, choose "page rotation is 0" as the basis page status and choose the
   *          left-bottom corner of the page (with page rotation is 0) as the basis point.
   *          And then, always change the position of top page boundary and right page boundary
   *          (with page rotation is 0) to change page size.
   *
   * @param[in] size  Size type to specify the new size of current page. Please refer to values starting from
   *                  @link PDFPage::e_SizeLetter @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetSize(foxit::pdf::PDFPage::Size size);

  /**
   * @brief Set page box.
   *
   * @param[in] box_type  Page box type. Please refer to values starting from @link PDFPage::e_MediaBox @endlink and
   *                      this should be one of these values.
   * @param[in] box       New box rectangle, in [PDF coordinate system] (@ref PDFPage).
   *
   * @return None.
   */
  void SetBox(BoxType box_type, const RectF& box);

  /**
   * @brief Get page box.
   *
   * @param[in] box_type  Page box type. Please refer to values starting from @link PDFPage::e_MediaBox @endlink and
   *                      this should be one of these values.
   *
   * @return A box rectangle, in [PDF coordinate system] (@ref PDFPage).
   */
  RectF GetBox(BoxType box_type);

  /**
   * @brief Get the user unit.
   *
   * @details A positive number giving the size of default user space units, in multiples of 1/72 inch.
   *          The range of supported values is implementation-dependent.
   *
   * @return User unit.
   */
  float GetUserUnitSize() const;

  /**
   * @brief Set the user unit.
   *
   * @details A positive number giving the size of default user space units, in multiples of 1/72 inch.
   *          The range of supported values is implementation-dependent. If not set,
   *          Foxit PDF SDK will use default value 1.0 (user unit is 1/72 inch).
   *
   * @param[in] user_unit  A positive number giving the size of default user space units, in multiples of 1/72 inch.
   *
   * @return None.
   */
  void  SetUserUnitSize(float user_unit);

  /**
   * @brief Transform a PDF page, including annotations and form fields on the page.
   *
   * @note This function only supports scaling and translating. After this operation, please re-parse current page
   *       by function @link PDFPage::StartParse @endlink with parameter <i>is_reparse</i> <b>true</b>, in order that
   *       expected content will be displayed.
   *
   * @param[in] matrix                    Transform matrix.
   * @param[in] need_transform_clip_path  <b>true</b> means to transform the page with clip rectangle,
   *                                      while <b>false</b> means not.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Transform(const Matrix& matrix, bool need_transform_clip_path);

  /**
   * @brief Set clip rectangle for all graphics objects on current PDF page.
   *
   * @details After this function finishes successfully, please re-parse current page by function
   *          @link PDFPage::StartParse @endlink with parameter <i>is_reparse</i> <b>true</b>.
   *
   * @param[in] clip_rect  New clip rectangle, in [PDF coordinate system] (@ref PDFPage).
   *
   * @return None.
   */
  void SetClipRect(const RectF& clip_rect);

  /**
   * @brief Set page thumbnail.
   *
   * @details Thumbnail bitmap does not use alpha channel. So user is recommended to set a bitmap
   *          without alpha channel to be the new thumbnail. If a bitmap with alpha channel is set,
   *          the new thumbnail will use white background by default.
   *
   * @param[in] thumbnail  New page thumbnail. It should be a valid bitmap.
   *
   * @return None.
   */
  void SetThumbnail(const common::Bitmap& thumbnail);

  /**
   * @brief Get the topmost graphics object in specified point, with specified type filter.
   *
   * @param[in] point      A specified position, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] tolerance  Tolerance value for a graphics object hit detection, in point units. It should be positive.
   * @param[in] filter     Type filter that specifies which kind of graphics object is to be gotten.
   *                       Please refer to values starting from @link graphics::GraphicsObject::e_TypeAll @endlink and
   *                       this should be one of these values.
   *                       @link graphics::GraphicsObject::e_TypeAll @endlink means for all kinds of graphics objects.
   *                       Default value: @link graphics::GraphicsObject::e_TypeAll @endlink.
   *
   * @return A @link graphics::GraphicsObject @endlink object. If no graphics object can be found, this function will return <b>NULL</b>.
   */
  graphics::GraphicsObject* GetGraphicsObjectAtPoint(const PointF& point, float tolerance,
                                                     graphics::GraphicsObject::Type filter = graphics::GraphicsObject::e_TypeAll) const;

  /**
   * @brief Get all the graphics objects in specified point, with specified type filter.
   *
   * @param[in] point      A specified position, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] tolerance  Tolerance value for a graphics object hit detection, in point units. It should be positive.
   * @param[in] filter     Type filter that specifies which kind of graphics object is to be gotten.
   *                       Please refer to values starting from @link graphics::GraphicsObject::e_TypeAll @endlink and
   *                       this should be one of these values.
   *                       @link graphics::GraphicsObject::e_TypeAll @endlink means for all kinds of graphics objects.
   *                       Default value: @link graphics::GraphicsObject::e_TypeAll @endlink.
   *
   * @return An array of @link graphics::GraphicsObject @endlink objects.
   */
  graphics::GraphicsObjectArray GetGraphicsObjectsAtPoint(const PointF& point, float tolerance,
                                                          graphics::GraphicsObject::Type filter = graphics::GraphicsObject::e_TypeAll);

  /**
   * @brief Get the topmost graphics object in specified point in device coordinate system, with specified type filter.
   *
   * @param[in] point      A specified position, in device coordinate system.
   * @param[in] tolerance  Tolerance value for a graphics object hit detection, in point units. It should be positive.
   * @param[in] matrix     The transformation matrix. Usually this is returned by function
   *                       @link PDFPage::GetDisplayMatrix @endlink.
   *                       Default value: <b>NULL</b>.
   * @param[in] filter     Type filter that specifies which kind of graphics object is to be gotten.
   *                       Please refer to values starting from @link graphics::GraphicsObject::e_TypeAll @endlink and
   *                       this should be one of these values.
   *                       @link graphics::GraphicsObject::e_TypeAll @endlink means for all kinds of graphics objects.
   *                       Default value: @link graphics::GraphicsObject::e_TypeAll @endlink.
   *
   * @return A @link graphics::GraphicsObject @endlink object. If no graphics object can be found, this function will return <b>NULL</b>.
   */
  graphics::GraphicsObject* GetGraphicsObjectAtDevicePoint(const PointF& point, float tolerance,const Matrix* matrix ,
                                                     graphics::GraphicsObject::Type filter = graphics::GraphicsObject::e_TypeAll) const;

  /**
   * @brief Get all the graphics objects in specified point in device coordinate system, with specified type filter.
   *
   * @param[in] point      A specified position, in device coordinate system.
   * @param[in] tolerance  Tolerance value for a graphics object hit detection, in point units. It should be positive.
   * @param[in] matrix     The transformation matrix. Usually this is returned by function
   *                       @link PDFPage::GetDisplayMatrix @endlink. 
   *                       Default value: <b>NULL</b>.
   * @param[in] filter     Type filter that specifies which kind of graphics object is to be gotten.
   *                       Please refer to values starting from @link graphics::GraphicsObject::e_TypeAll @endlink and
   *                       this should be one of these values.
   *                       @link graphics::GraphicsObject::e_TypeAll @endlink means for all kinds of graphics objects.
   *                       Default value: @link graphics::GraphicsObject::e_TypeAll @endlink.
   *
   * @return An array of @link graphics::GraphicsObject @endlink objects.
   */
  graphics::GraphicsObjectArray GetGraphicsObjectsAtDevicePoint(const PointF& point, float tolerance,const Matrix* matrix,
                                                          graphics::GraphicsObject::Type filter = graphics::GraphicsObject::e_TypeAll);
  /**
   * @brief Add an image to current page.
   *
   * @details If the type of image is @link common::Image::e_JPG @endlink, the image should be kept valid
   *          until the related document is closed.
   *
   * @param[in] image                  An image. One of its frames will be set to current page.
   *                                   This image contains at least one frame and the image type should not be
   *                                   @link common::Image::e_Unknown @endlink.
   * @param[in] frame_index            Frame index. Valid range: from 0 to (<i>count</i>-1).
   *                                   <i>count</i> is returned by function @link common::Image::GetFrameCount @endlink.
   * @param[in] position               A specified position, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] width                  The width which is used for the image to set into page.
   *                                   The value should be larger than 0.
   * @param[in] height                 The height which is used for the image to set into page.
   *                                   The value should be larger than 0.
   * @param[in] auto_generate_content  <b>true</b> means to generate content internally. <br>
   *                                   When using <b>false</b>, user should ensure to call function
   *                                   @link GraphicsObjects::GenerateContent @endlink after adding image.
   *                                   Please refer to function @link GraphicsObjects::GenerateContent @endlink
   *                                   for more details. Default value: <b>true</b>.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool AddImage(const common::Image& image, int frame_index, const PointF& position, float width, float height,
                bool auto_generate_content = true);

  /**
   * @brief Add an image to current page from file path.
   *
   * @details If input image (specified by file path) has more than one frame, only the first frame will be added to
   *          current page acquiescently.
   *
   * @param[in] file_path              A full path of an existing image file. It should not be an empty string.
   * @param[in] position               A specified position, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] width                  The width which is used for the image to set into page.
   *                                   The value should be larger than 0.
   * @param[in] height                 The height which is used for the image to set into page.
   *                                   The value should be larger than 0.
   * @param[in] auto_generate_content  <b>true</b> means to generate content internally. <br>
   *                                   When using <b>false</b>, user should ensure to call function
   *                                   @link GraphicsObjects::GenerateContent @endlink after adding image.
   *                                   Please refer to function @link GraphicsObjects::GenerateContent @endlink
   *                                   for more details. Default value: <b>true</b>.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool AddImageFromFilePath(const char* file_path, const PointF& position, float width, float height,
                            bool auto_generate_content = true);

  /**
   * @brief Add an image to current page from file path.
   *
   * @details If input image (specified by file path) has more than one frame, only the first frame will be added to
   *          current page acquiescently.
   *
   * @param[in] file_path              A full path of an existing image file. It should not be an empty string.
   * @param[in] position               A specified position, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] width                  The width which is used for the image to set into page.
   *                                   The value should be larger than 0.
   * @param[in] height                 The height which is used for the image to set into page.
   *                                   The value should be larger than 0.
   * @param[in] auto_generate_content  <b>true</b> means to generate content internally. <br>
   *                                   When using <b>false</b>, user should ensure to call function
   *                                   @link GraphicsObjects::GenerateContent @endlink after adding image.
   *                                   Please refer to function @link GraphicsObjects::GenerateContent @endlink
   *                                   for more details. Default value: <b>true</b>.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool AddImageFromFilePath(const wchar_t* file_path, const PointF& position, float width, float height,
                            bool auto_generate_content = true);

  /**
   * @brief Get the PDF array of "Annots".
   *
   * @note Please refer to "TABLE 3.27 Entries in a page object" in <PDF Reference 1.7> P147 for more details.
   *
   * @return The PDF array of "Annots".
   */
  objects::PDFArray* GetAnnots() const;

  /**
   * @brief Get the PDF dictionary of "Resources".
   *
   * @note Please refer to "TABLE 3.27 Entries in a page object" in <PDF Reference 1.7> P145 for more details.
   *
   * @return The PDF dictionary of "Resources".
   */
  objects::PDFDictionary* GetResources() const;

  /**
   * @brief Get the PDF object of "Contents".
   *
   * @note "Contents" can be either a PDF stream or a PDF array. Please refer to "TABLE 3.27 Entries in a page object"
   *       in <PDF Reference 1.7> P146 for more details.
   *
   * @return The PDF object of "Contents".
   */
  objects::PDFObject* GetContents() const;

  /**
   * @brief Get the PDF stream of "Thumb".
   *
   * @note Please refer to "TABLE 3.27 Entries in a page object" in <PDF Reference 1.7> P146 for more details.
   *
   * @return The PDF stream of "Thumb".
   */
  objects::PDFStream* GetThumb() const;

  /**
   * @brief Get the PDF object for specified attribute which may be inherited from the ancestor node in the page tree.
   *
   * @details Some of the page attributes are designated as inheritable, such as "Resources", "MediaBox", "CropBox",
   *          and "Rotate". Please refer to "TABLE 3.27 Entries in a page object" in <PDF Reference 1.7> P145 and
   *          "Inheritance of Page Attributes" in <PDF Reference 1.7> P149 for more details.
   *
   * @param[in] attruibute_name  The name of attribute to be found.
   *
   * @return A PDF object. If not found, this function will return <b>NULL</b>.
   */
  objects::PDFObject* GetInheritedAttribute(const char* attruibute_name) const;

  /**
   * @brief Clear render cache.
   *
   * @return None.
   */
  void ClearRenderCache();
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PDFPAGE_H_

