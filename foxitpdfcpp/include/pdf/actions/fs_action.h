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
 * @file fs_action.h
 * @brief Header file for destination and action related definitions and classes.
 */

#ifndef FS_ACTION_H_
#define FS_ACTION_H_

#include "common/fs_common.h"
#include "pdf/objects/fs_pdfobject.h"
#include "common/file/fs_file.h"
#include "pdf/fs_rendition.h"

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
class FileSpec;
class PDFDoc;
class PDFPage;
namespace objects {
    class PDFDictionary;
} // namespace objects
namespace annots {
class Annot;
class Screen;
}  // namespace annots
namespace interform {
  class Field;
}  // namespace interform

/**
 * A destination defines a particular view of a PDF document, consisting of the following items:
 * <ul>
 * <li>The page of the document to be displayed.</li>
 * <li>The location of the document window on that page.</li>
 * <li>The magnification (zoom) factor to use when displaying the page.</li>
 * </ul>
 * Destinations may be associated with bookmarks, or some types of actions. In each case, the destination specifies
 * the view of the document to be presented when the bookmark item or link annotation is opened or
 * the action is performed.<br>
 * This class offers functions to create destination objects for different zoom mode, and get destination data.
 *
 * @see @link pdf::Bookmark @endlink
 * @see @link actions::GotoAction @endlink
 * @see @link actions::RemoteGotoAction @endlink
 * @see @link actions::EmbeddedGotoAction @endlink
 */
class Destination FS_FINAL : public Base {
 public:
   /**
    * @brief Enumeration for zoom mode.
    *
    * @details Values of this enumeration should be used alone.
    */
   typedef enum _ZoomMode {
     /**
    @brief Display page with a specified position and a specified zoom factor.
    @details If this is used, that means the specified position of the page will be treated as the left-top position
             when the page is rendered and this position should be at the upper-left corner of the display area.
             Contents of the page should be magnified by the specified zoom factor.
      */
     e_ZoomXYZ = 1,
     /**
    @brief Fit the entire page within the display area when display the page.
    @details If this is used, that means the contents of the page should be magnified just enough to
             fit the entire page within the display area both horizontally and vertically.
             If the required horizontal and vertical magnification factors are different,
             use the smaller of the two, centering the page within the window in the other dimension.
      */
     e_ZoomFitPage = 2,
     /**
    @brief Fit the entire width of the page within the display area when display the page.
    @details If this is used, that means the contents of the page should be magnified
             just enough to fit the entire width of the page within the display area.
      */
     e_ZoomFitHorz = 3,
     /**
      * @brief Fit the entire height of the page within the display area when display the page.
      *
      * @details If this is used, that means the contents of the page should be magnified
      *          just enough to fit the entire height of the page within the display area.
      */
     e_ZoomFitVert = 4,
     /**
    @brief Fit the page content in a specified rectangle entirely within the display area when display the page.
    @details If this is used, that means the contents of the page should be magnified just enough to
             fit the page content in the specified rectangle entirely within the display area
             both horizontally and vertically. If the required horizontal and vertical magnification factors
             are different, use the smaller of the two, centering the rectangle within the display area
             in the other dimension.
      */
     e_ZoomFitRect = 5,
     /**
    @brief Fit the bounding box of page entirely within the display area when display the page.
    @details If this is used, that means the contents of the page should be magnified just enough to
             fit its bounding box entirely within the display area both horizontally and vertically.
             If the required horizontal and vertical magnification factors are different,
             use the smaller of the two, centering the bounding box within the display area in the other dimension.
      */
     e_ZoomFitBBox = 6,
     /**
    @brief Fit the entire width of the page's bounding box within the display area when display the page.
    @details If this is used, that means the contents of the page should be magnified
             just enough to fit the entire width of the page's bounding box within the display area.
      */
     e_ZoomFitBHorz = 7,
     /**
    @brief Fit the entire height of the page's bounding box within the display area when display the page.
    @details If this is used, that means the contents of the page should be magnified
             just enough to fit the entire height of the page's bounding box within the display area.
      */
     e_ZoomFitBVert = 8
   } ZoomMode;
   

  /**
   * @brief Create a destination object for zoom mode @link Destination::e_ZoomXYZ @endlink.
   *
   * @param[in] document     A valid PDF document object.
   * @param[in] page_index   The index of the destination page in the PDF document.
   * @param[in] left         Horizontal coordinate value of a position as page's left-top position.
   * @param[in] top          Vertical coordinate value of a position as page's left-top position.
   * @param[in] zoom_factor  Zoom factor value.
   *
   * @return A new destination object.
   */
  static Destination CreateXYZ(const PDFDoc& document, int page_index, float left, float top, float zoom_factor);

  /**
   * @brief Create a destination object for zoom mode @link Destination::e_ZoomFitPage @endlink.
   *
   * @param[in] document     A valid PDF document object.
   * @param[in] page_index  The index of the destination page in the PDF document.
   *
   * @return A new destination object.
   */
  static Destination CreateFitPage(const PDFDoc& document, int page_index) ;

  /**
   * @brief Create a destination object for zoom mode @link Destination::e_ZoomFitHorz @endlink.
   *
   * @param[in] document    A valid PDF document object.
   * @param[in] page_index  The index of the destination page in the PDF document.
   * @param[in] top         Vertical coordinate of top edge.
   *
   * @return A new destination object.
   */
  static Destination CreateFitHorz(const PDFDoc& document, int page_index, float top);

  /**
   * @brief Create a destination object for zoom mode @link Destination::e_ZoomFitVert @endlink.
   *
   * @param[in] document    A valid PDF document object.
   * @param[in] page_index  The index of the destination page in the PDF document.
   * @param[in] left        Horizontal coordinate of left edge.
   *
   * @return A new destination object.
   */
  static Destination CreateFitVert(const PDFDoc& document, int page_index, float left);

  /**
   * @brief Create a destination object for zoom mode @link Destination::e_ZoomFitRect @endlink.
   *
   * @param[in] document    A valid PDF document object.
   * @param[in] page_index  The index of the destination page in the PDF document.
   * @param[in] left        The coordinate left of a rectangle.
   * @param[in] bottom      The coordinate bottom of a rectangle.
   * @param[in] right       The coordinate right of a rectangle.
   * @param[in] top         The coordinate top of a rectangle.
   *
   * @return A new destination object.
   */
  static Destination CreateFitRect(const PDFDoc& document, int page_index,
                                   float left, float bottom, float right, float top);

  /**
   * @brief Create a destination object for zoom mode @link Destination::e_ZoomFitBBox @endlink.
   *
   * @param[in] document    A valid PDF document object.
   * @param[in] page_index  The index of the destination page in the PDF document.
   *
   * @return A new destination object.
   */
  static Destination CreateFitBBox(const PDFDoc& document, int page_index);

  /**
   * @brief Create a destination object for zoom mode @link Destination::e_ZoomFitBHorz @endlink.
   *
   * @param[in] document    A valid PDF document object.
   * @param[in] page_index  The index of the destination page in the PDF document.
   * @param[in] top         The vertical coordinate of top edge
   *
   * @return A new destination object.
   */
  static Destination CreateFitBHorz(const PDFDoc& document, int page_index, float top);

  /**
   * @brief Create a destination object for zoom mode @link Destination::e_ZoomFitBVert @endlink.
   *
   * @param[in] document    A valid PDF document object.
   * @param[in] page_index  The index of the destination page in the PDF document.
   * @param[in] left        Horizontal coordinate of left edge.
   *
   * @return A new destination object.
   */
  static Destination CreateFitBVert(const PDFDoc& document, int page_index, float left);

  /**
   * @brief Create a destination object from an existing destination array.
   *
   * @param[in] document   A valid PDF document object.
   * @param[in] pdf_array  A destination PDF array. This PDF array can be retrieved from a @link objects::PDFNameTree @endlink
   *                       in type @link objects::PDFNameTree::e_Dests @endlink.
   *
   * @return A new destination object.
   */
  static Destination CreateFromPDFArray(const PDFDoc& document, objects::PDFArray* pdf_array);

  /**
   * @brief Constructor, with a specified PDF array object.
   *
   * @param[in] dest_array  A PDF array object that represents destination data.
   */
  explicit Destination(objects::PDFArray* dest_array);
  /** @brief Destructor. */
  ~Destination();
  /**
   * @brief Constructor, with another destination object.
   *
   * @param[in] other  Another destination object.
   */
  Destination(const Destination& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another destination object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Destination& operator = (const Destination& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another destination object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Destination& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another destination object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Destination& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the index of the destination page.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @return The page index, starting from 0. If there is any error, this function will return -1.
   */
  int GetPageIndex(const PDFDoc& document) const;

  /**
   * @brief Get the zoom mode.
   *
   * @return Zoom mode value. Please refer to values starting from @link Destination::e_ZoomXYZ @endlink and
   *         this would be one of these values. If no zoom mode or zoom mode is unknown, this function will return 0.
   */
  Destination::ZoomMode GetZoomMode() const;

  /**
   * @brief Get left position value.
   *
   * @details This is only useful when zoom mode is @link Destination::e_ZoomXYZ @endlink, @link Destination::e_ZoomFitVert @endlink,
   *          @link Destination::e_ZoomFitRect @endlink or @link Destination::e_ZoomFitBVert @endlink.
   *          Specially for @link Destination::e_ZoomXYZ @endlink, @link Destination::e_ZoomFitVert @endlink and
   *          @link Destination::e_ZoomFitBVert @endlink, left value may be a null object,
   *          which means that just use current left value of application as the destination's left value.
   *          For this case, this function will return 0.0f. In order to check if the left value is just 0 or
   *          a null object, user is recommended to call function @link Destination::IsLeftNull @endlink.<br>
   *          For other zoom mode, this function will return 0.0f.
   *
   * @return The left position value.
   */
  float GetLeft() const;

  /**
   * @brief Check if left value is a null object.
   *
   * @details This is only useful when zoom mode is @link Destination::e_ZoomXYZ @endlink, @link Destination::e_ZoomFitVert @endlink
   *          or @link Destination::e_ZoomFitBVert @endlink.
   *          This function can be used to check if the left value is a null object.
   *          For other zoom mode, this function will return <b>false</b>.
   *
   * @return <b>true</b> means left value is a null object, and <b>false</b> means left value is not a null object
   *         and the left value can be retrieved by function @link Destination::GetLeft @endlink.
   */
  bool IsLeftNull() const;

  /**
   * @brief Get top position value.
   *
   * @details This is only useful when zoom mode is @link Destination::e_ZoomXYZ @endlink, @link Destination::e_ZoomFitHorz @endlink,
   *          @link Destination::e_ZoomFitBHorz @endlink or @link Destination::e_ZoomFitRect @endlink.
   *          Specially for @link Destination::e_ZoomXYZ @endlink, @link Destination::e_ZoomFitHorz @endlink and
   *          @link Destination::e_ZoomFitBHorz @endlink, top value may be a null object, which means that just
   *          use current top value of application as the destination's top value. For this case,
   *          this function will return 0.0f. In order to check if the left value is just 0 or a null object,
   *          user is recommended to call function @link Destination::IsTopNull @endlink.<br>
   *          For other zoom mode, this function will return 0.0f.
   *
   * @return The top position value.
   */
  float GetTop() const;

  /**
   * @brief Check if top value is a null object.
   *
   * @details This is only useful when zoom mode is @link Destination::e_ZoomXYZ @endlink, @link Destination::e_ZoomFitHorz @endlink,
   *          or @link Destination::e_ZoomFitBHorz @endlink.
   *          This function can be used to check if the top value is a null object.
   *          For other zoom mode, this function will return <b>false</b>.
   *
   * @return <b>true</b> means top value is a null object, and <b>false</b> means top value is not a null object
   *         and the top value can be retrieved by function @link Destination::GetTop @endlink.
   */
  bool IsTopNull() const;

  /**
   * @brief Get right position value.
   *
   * @details This is only useful when zoom mode is @link Destination::e_ZoomFitRect @endlink.
   *          For other zoom mode, this function will be 0.0f.
   *
   * @return The right position value.
   */
  float GetRight() const;

  /**
   * @brief Get bottom position value.
   *
   * @details This is only useful when zoom mode is @link Destination::e_ZoomFitRect @endlink.
   *          For other zoom mode, this function will be 0.0f.
   *
   * @return The bottom position value.
   */
  float GetBottom() const;

  /**
   * @brief Get zoom factor.
   *
   * @details This is only useful when zoom mode is @link Destination::e_ZoomXYZ @endlink.
   *          For @link Destination::e_ZoomXYZ @endlink, if the zoom factor is 0,
   *          that means just use current zoom factor of application as the destination zoom factor.<br>
   *          For other zoom mode, this function will be 0.0f.
   *
   * @return The zoom factor.
   */
  float GetZoomFactor() const;

  /**
   * @brief Get the destination PDF array.
   *
   * @return The destination PDF array.
   */
  objects::PDFArray* GetDestArray() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Destination(FS_HANDLE handle =  NULL);
};

/** @brief Actions namespace.*/
namespace actions{
/**
 * PDF supports following standard action types:<br>
 * "Go-To Action", "Remote Go-To Action", "Embedded Go-To Action", "Launch Action", "Thread Action",
 * "URI Action", "Sound Action","Movie Action", "Hide Action", "Named Action", "Submit-Form Action",
 * "Reset-Form Action", "Import-Data Action", "JavaScript Action", "Set-OCG-State Action",
 * "Rendition Action","Transition Action","Go-To-3D-View Action".<br>
 * A PDF action may have sub-actions. When this action is triggered, its sub-actions should also
 * be triggered in turn.<br>
 * Class @link Action @endlink is the base class for all kinds of PDF actions. For concrete action types, please refer to
 * derived classes. Function @link Action::Create @endlink can be used to create a new action -- currently only support
 * some action types. Please refer to comment of this function for more details. This class also offers functions to
 * modify sub-actions.
 */
class Action : public Base {
 public:
  /**
   * @brief Enumeration for action type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Type {
    /** @brief Action type: unknown action. */
    e_TypeUnknown = 0,
    /** @brief Action type: go-to action. */
    e_TypeGoto = 1,
    /** @brief Action type: remote go-to action. */
    e_TypeGoToR = 2,
    /** @brief Action type: embedded go-to action. */
    e_TypeGoToE = 3,
    /** @brief Action type: launch action. */
    e_TypeLaunch = 4,
    /** @brief Action type: thread action. */
    e_TypeThread = 5,
    /** @brief Action type: uniform resource identifier (URI) action. */
    e_TypeURI = 6,
    /** @brief Action type: sound action. */
    e_TypeSound = 7,
    /** @brief Action type: movie action. */
    e_TypeMovie = 8,
    /** @brief Action type: hide action. */
    e_TypeHide = 9,
    /** @brief Action type: named action. */
    e_TypeNamed = 10,
    /** @brief Action type: submit-form action. */
    e_TypeSubmitForm = 11,
    /** @brief Action type: reset-form action. */
    e_TypeResetForm = 12,
    /** @brief Action type: import-data action. */
    e_TypeImportData = 13,
    /** @brief Action type: JavaScript action. */
    e_TypeJavaScript = 14,
    /** @brief Action type: set-OCG-state action. */
    e_TypeSetOCGState = 15,
    /** @brief Action type: rendition action. */
    e_TypeRendition = 16,
    /** @brief Action type: transition action. */
    e_TypeTrans = 17,
    /** @brief Action type: go-to-3D-view action. */
    e_TypeGoTo3DView = 18
  } Type;
  
  /**
   * @brief Enumeration for new window flag.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _NewWindowFlag {
    /** @brief "NewWindow" flag is <b>false</b>. */
    e_NewWindowFlagFalse = 0,
    /** @brief "NewWindow" flag is <b>true</b>. */
    e_NewWindowFlagTrue = 1,
    /** @brief No "NewWindow" flag. */
    e_NewWindowFlagNone = 2
  } NewWindowFlag;
  

  /**
   * @brief Create a new action, for specified action type.
   *
   * @details The newly created action has no action data (except action type) yet.
   *          User needs to call the functions in concrete action classes to set action data.
   *
   * @param[in] document     A valid PDF document, to which the new action belongs.
   * @param[in] action_type  Action type, used to specify which type of action is to be created.
   *                         Currently only support:<br>
   *                         @link actions::Action::e_TypeGoto @endlink, @link Action::e_TypeURI @endlink,
   *                         @link actions::Action::e_TypeJavaScript @endlink, @link Action::e_TypeNamed @endlink,
   *                         @link actions::Action::e_TypeGoToR @endlink, @link Action::e_TypeGoToE @endlink,
   *                         @link actions::Action::e_TypeSubmitForm @endlink, @link Action::e_TypeResetForm @endlink,
   *                         @link actions::Action::e_TypeHide @endlink, @link Action::e_TypeLaunch @endlink,
   *                         @link actions::Action::e_TypeImportData @endlink, @link Action::e_TypeRendition @endlink.
   *
   * @return A new action object, with no action data.
   */
  static Action Create(const foxit::pdf::PDFDoc& document, Type action_type);

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] document     A valid PDF document object.
   * @param[in] action_dict  A PDF dictionary object that represents an action.
   */
  explicit Action(const PDFDoc& document, objects::PDFDictionary* action_dict);
  /**
   * @brief Constructor, with another action object.
   *
   * @param[in] action  Another action object.
   */
  Action(const Action& action);
  /** @brief Destructor. */
  ~Action();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another action object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Action& operator = (const Action& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another action object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Action& other) const ;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another action object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Action& other) const ;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get action type.
   *
   * @return Action type. Please refer to values starting from @link Action::e_TypeGoto @endlink and
   *         this would be one of these values.
   */
  Type GetType();

  /**
   * @brief Get the PDF document, to which current action belongs.
   *
   * @return A PDF document object.
   */
  PDFDoc GetDocument();

  /**
   * @brief Get PDF dictionary of current object.
   *
   * @return The PDF dictionary.
   */
  objects::PDFDictionary* GetDict() const;

  /**
   * @brief Get the count of sub-actions.
   *
   * @return Count of sub-actions.
   */
  int GetSubActionCount();

  /**
   * @brief Get a sub-action by index.
   *
   * @param[in] index  Index of sub-action to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Action::GetSubActionCount @endlink.
   *
   * @return An action object that represents the specified sub-action.
   */
  Action GetSubAction(int index);

  /**
   * @brief Set a sub-action by index.
   *
   * @param[in] index       Index of sub-action to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                        <i>count</i> is returned by function @link Action::GetSubActionCount @endlink.
   * @param[in] sub_action  An action object to be set as a sub-action. Currently only support following types
   *                        as sub-action:<br>
   *                        @link actions::Action::e_TypeGoto @endlink, @link Action::e_TypeURI @endlink,
   *                        @link actions::Action::e_TypeJavaScript @endlink, @link Action::e_TypeNamed @endlink,
   *                        @link actions::Action::e_TypeGoToR @endlink, @link Action::e_TypeGoToE @endlink,
   *                        @link actions::Action::e_TypeSubmitForm @endlink, @link Action::e_TypeResetForm @endlink,
   *                        @link actions::Action::e_TypeHide @endlink, @link Action::e_TypeLaunch @endlink,
   *                        @link actions::Action::e_TypeImportData @endlink, @link Action::e_TypeRendition @endlink.
   *
   * @return None.
   */
  void SetSubAction(int index, const Action& sub_action);

  /**
   * @brief Insert a new sub-action to the location specified by index.
   *
   * @param[in] index       Index of the location, where the new sub-action is inserted. <br>
   *                        If this index value is below zero, the new sub-action will be inserted to be the first.<br>
   *                        If this index value equals or larger than current sub-action count, the new sub-action will
   *                        be inserted to be the last.
   * @param[in] sub_action  New sub-action to be inserted. Currently only support following types
   *                        as the new sub-action:<br>
   *                        @link actions::Action::e_TypeGoto @endlink, @link Action::e_TypeURI @endlink,
   *                        @link actions::Action::e_TypeJavaScript @endlink, @link Action::e_TypeNamed @endlink,
   *                        @link actions::Action::e_TypeGoToR @endlink, @link Action::e_TypeGoToE @endlink,
   *                        @link actions::Action::e_TypeSubmitForm @endlink, @link Action::e_TypeResetForm @endlink,
   *                        @link actions::Action::e_TypeHide @endlink, @link Action::e_TypeLaunch @endlink,
   *                        @link actions::Action::e_TypeImportData @endlink, @link Action::e_TypeRendition @endlink.
   *
   * @return None.
   */
  void InsertSubAction(int index, const Action& sub_action);

  /**
   * @brief Remove a sub-action, specified by index.
   *
   * @param[in] index  Index of sub-action to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Action::GetSubActionCount @endlink.
   *
   * @return None.
   */
  void RemoveSubAction(int index);

  /**
   * @brief Remove all the sub-actions.
   *
   * @return None.
   */
  void RemoveAllSubActions();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Action(FS_HANDLE handle =  NULL);
};

/**
 * Go-to action is an action that changes the view to a specified destination (page, location,
 * and magnification factor).<br>
 * Class @link actions::GotoAction @endlink is derived from @link Action @endlink and offers functions to
 * get/set go-to action data.
 *
 * @see @link Action @endlink
 */
class GotoAction FS_FINAL : public Action {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit GotoAction(const Action& action);

  /**
   * @brief Get the destination information.
   *
   * @return A destination object.
   */
  Destination GetDestination();

  /**
   * @brief Set the destination information.
   *
   * @param[in] dest  A valid destination object to be set.
   *
   * @return None.
   */
  void SetDestination(const Destination& dest);
};

/**
 * URI (uniform resource identifier) action is an action that causes a URI to be resolved.
 * Class @link actions::URIAction @endlink is derived from @link Action @endlink and offers functions to
 * get/set URI action data.
 *
 * @see @link Action @endlink
 */
class URIAction FS_FINAL : public Action {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit URIAction(const Action& action);

  /**
   * @brief Get the URI string.
   *
   * @return URI string.
   */
  String GetURI();

  /**
   * @brief Set the URI string.
   *
   * @param[in] uri  A URI string to be set. It should not be an empty string.
   *
   * @return None.

   */
  void SetURI(const String& uri);

  /**
   * @brief Check whether to track the mouse position when the URI is resolved.
   *
   * @return <b>true</b> means application should track the mouse position,
   *         while <b>false</b> means no need to track the mouse position.
   */
  bool IsTrackPosition();

  /**
   * @brief Set the value for tracking position flag.
   *
   * @param[in] is_track_position  <b>true</b> means to track position, while <b>false</b> means not to track position.
   *
   * @return None.
   */
  void SetTrackPositionFlag(bool is_track_position);

};

/**
 * JavaScript action is an action that causes a script to be compiled and executed by the JavaScript interpreter.<br>
 * Class @link actions::JavaScriptAction @endlink is derived from @link Action @endlink and offers functions to
 * get/set JavaScript action data.
 *
 * @see @link Action @endlink
 */
class JavaScriptAction FS_FINAL : public Action {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit JavaScriptAction(const Action& action);

  /**
   * @brief Get JavaScript script.
   *
   * @return JavaScript script.
   */
  WString GetScript();

  /**
   * @brief Set JavaScript script.
   *
   * @param[in] script  A JavaScript script to be set. It should not be an empty string.
   *
   * @return None.
   */
  void SetScript(const WString& script);
};

/**
 * Named action is an action that executes an action predefined by the viewer application.<br>
 * Class @link actions::NamedAction @endlink is derived from @link Action @endlink and offers functions to
 * get/set named action data.
 *
 * @see @link Action @endlink
 */
class NamedAction FS_FINAL : public Action {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit NamedAction(const Action& action);

  /**
   * @brief Get the name of the action..
   *
   * @details In PDF reference 1.7, following names are defined and PDF viewer applications are
   *          expected to support them:<br>
   *          "NextPage", "PrevPage", "FirstPage", "LastPage".<br>
   *          Some more standard names may be added in later version.
   *          Application can also use additional, non-standard names.
   *
   * @return Name of the action.
   */
  String GetName();

  /**
   * @brief Set the name of the action..
   *
   * @details In PDF reference 1.7, following names are defined and PDF viewer applications are
   *          expected to support them:<br>
   *          "NextPage", "PrevPage", "FirstPage", "LastPage".<br>
   *          Some more standard names may be added in later version.
   *          Application can also use additional, non-standard names.
   *
   * @param[in] name  A string that represents the new name. It should not be an empty string.
   *
   * @return None.
   */
  void SetName(const String& name);
};

/**
 * Remote go-to action is similar to an ordinary go-to action but jumps to a destination in another PDF file
 * (not embedded file) instead of current PDF file (which contains the remote go-to action). <br>
 * Class @link actions::RemoteGotoAction @endlink is derived from @link Action @endlink and offers functions to
 * get/set remote go-to action data.
 * Destination information of a remote go-to action can be represents as either a destination array or
 * a destination name:
 * <ul>
 * <li>If the destination information is a destination array, Foxit PDF SDK uses a destination object to
 *     represent it and @link RemoteGotoAction::GetDestination @endlink can be used to get such value.</li>
 * <li>If the destination information is a destination name, Foxit PDF SDK uses a string to represent it and
 *     @link RemoteGotoAction::GetDestinationName @endlink can be used to get such value.
 *     Specially, the related destination array is defined in the target PDF file, not current PDF file.
 *     User can use functions in class @link objects::PDFNameTree @endlink to retrieve the actual destination array from target PDF file.
 * </li>
 * </ul>
 * Destination PDF file and destination information are necessary for a remote go-to action, so user should
 * ensure to set both data by @link RemoteGotoAction::SetFileSpec @endlink and
 * @link RemoteGotoAction::SetDestination @endlink or @link RemoteGotoAction::SetDestinationName @endlink,
 * especially for a new remote go-to action; otherwise, the remote go-to action would be useless.
 *
 * @see @link Action @endlink
 */
class RemoteGotoAction FS_FINAL : public Action {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit RemoteGotoAction(const Action& action);

  /**
   * @brief Get the destination information.
   *
   * @details For a remote go-to action, the destination information can be stored as either a destination object
   *          or a destination name:
   *          <ul>
   *          <li>If it is a destination object, function @link RemoteGotoAction::GetDestination @endlink would
   *              return a valid destination object.</li>
   *          <li>If it is a destination name, function @link RemoteGotoAction::GetDestinationName @endlink would
   *              return a valid string, and the destination name would be defined in the target PDF file.</li>
   *          </ul>
   *          If the return value of function @link Destination::IsEmpty @endlink for
   *          the returned destination object is <b>true</b> and function @link RemoteGotoAction::GetDestinationName @endlink
   *          returns an empty string, that means the remote go-to action does not have any destination information.
   *
   * @return A destination object. If the return value of function @link Destination::IsEmpty @endlink for
   *         the returned destination object is <b>true</b>, please try function
   *         @link RemoteGotoAction::GetDestinationName @endlink.
   */
  Destination GetDestination();

  /**
   * @brief Set the destination information, which is used to specify the position in target PDF file to jump to.
   *
   * @param[in] destination  A valid destination object to be set.
   *
   * @return None.
   */
  void SetDestination(const Destination& destination);

  /**
   * @brief Get the destination name, which is defined in target PDF file.
   *
   * @details For a remote go-to action, the destination information can be stored as either a destination object
   *          or a destination name:
   *          <ul>
   *          <li>If it is a destination object, function @link RemoteGotoAction::GetDestination @endlink would
   *              return a valid destination object.</li>
   *          <li>If it is a destination name, function @link RemoteGotoAction::GetDestinationName @endlink would
   *              return a valid string, and the destination name would be defined in the target PDF file.</li>
   *          </ul>
   *          If the return value of function @link Destination::IsEmpty @endlink for
   *          the returned destination object is <b>true</b> and function @link RemoteGotoAction::GetDestinationName @endlink
   *          returns an empty string, that means the remote go-to action does not have any destination information.
   *
   * @return The destination name. If this function returns an empty string, please try function
   *         @link RemoteGotoAction::GetDestination @endlink.
   */
  String GetDestinationName();

  /**
   * @brief Set the destination name.
   *
   * @details The destination name should have been in the "Dests" name tree in the target PDF file.
   *
   * @param[in] dest_name  A destination name to be set. It should be not be an empty string.
   *
   * @return None.
   */
  void SetDestinationName(const String& dest_name);

  /**
   * @brief Get the file specification which specifies the destination file.
   *
   * @return A non-embedded file specification object.
   */
  FileSpec GetFileSpec();

  /**
   * @brief Set the file specification which specifies the destination file.
   *
   * @param[in] file_specification  A valid file specification object to be set. This object should belong to
   *                                the same PDF file as current action. It should represent another PDF file as
   *                                the target file, and should not represent an embedded file.
   *
   * @return None.
   */
  void SetFileSpec(const FileSpec& file_specification);

  /**
   * @brief Get the flag which is used to decide whether to open the destination document in a new window or not.
   *
   * @return The new window flag. It would be one of following values:<br>
   *         <ul>
   *         <li>@link Action::e_NewWindowFlagTrue @endlink means to open the destination document in a new window.</li>
   *         <li>@link Action::e_NewWindowFlagFalse @endlink means that
   *             the destination document replaces current document in the same window.</li>
   *         <li>@link Action::e_NewWindowFlagNone @endlink means that
   *             no such flag and the viewer application should behave in accordance with the current user preference.
   *         </li>
   *         </ul>
   */
  NewWindowFlag GetNewWindowFlag();

  /**
   * @brief Set the flag which is used to decide whether to open the destination document in a new window or not.
   *
   * @param[in] flag  The new window flag. It should be one of following values:<br>
   *                  <ul>
   *                  <li>@link Action::e_NewWindowFlagTrue @endlink means to
   *                      open the destination document in a new window.</li>
   *                  <li>@link Action::e_NewWindowFlagFalse @endlink means that
   *                      the destination document replaces current document in the same window.</li>
   *                  <li>@link Action::e_NewWindowFlagNone @endlink means that
   *                      such flag is not needed and the viewer application should behave in accordance
   *                      with the current user preference.</li>
   *                  </ul>
   *
   * @return None.
   */
  void SetNewWindowFlag(NewWindowFlag flag);
};

/**
 * The target of an embedded go-to action is the document in which the destination lives.
 *
 * @see @link EmbeddedGotoAction @endlink
 */
class EmbeddedGotoTarget FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, with PDF document.
   *
   * @details This constructor is to construct a new embedded goto target object (without any data).
   *
   * @param[in] document  A valid PDF document object.
   */
  explicit EmbeddedGotoTarget(const PDFDoc& document);
  /**
   * @brief Constructor, with PDF dictionary.
   *
   * @param[in] document       A valid PDF document object.
   * @param[in] target_object  A PDF dictionary that represents the embedded goto target data.
   */
  EmbeddedGotoTarget(const foxit::pdf::PDFDoc& document, foxit::pdf::objects::PDFDictionary* target_object);
  /** @brief Destructor. */
  ~EmbeddedGotoTarget();

  /**
   * @brief Constructor, with another embedded goto target object.
   *
   * @param[in] action  Another embedded goto target object.
   */
  EmbeddedGotoTarget(const EmbeddedGotoTarget& action);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another embedded goto target object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  EmbeddedGotoTarget& operator = (const EmbeddedGotoTarget& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another embedded goto target object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const EmbeddedGotoTarget& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another embedded goto target object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const EmbeddedGotoTarget& other) const;

  /**
   * @brief Get PDF dictionary of current object.
   *
   * @return The PDF dictionary.
   */
  objects::PDFDictionary* GetDict() const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get relationship between current target object and the object that current target object belongs to.
   *
   * @details The relationship is the relationship between current target object and
   *          the object that current target object belongs to. Currently, the relationship could be one of following:
   *          <ul>
   *          <li>"P": current target object is the parent of the object that current target object belongs to.</li>
   *          <li>"C": current target object is the child of the object that current target object belongs to.</li>
   *          </ul>
   *
   * @return Relationship string.
   */
  String GetRelationship();

  /**
   * @brief Set relationship between current target object and the object that current target object belongs to.
   *
   * @details The relationship is the relationship between current target object and
   *          the object that current target object belongs to. Currently, the relationship could be one of following:
   *          <ul>
   *          <li>"P": current target object is the parent of the object that current target object belongs to.</li>
   *          <li>"C": current target object is the child of the object that current target object belongs to.</li>
   *          </ul>
   *
   * @param[in] relationship  It should be one of following strings:"P", "C".
   *
   * @return None.
   */
  void SetRelationship(const String& relationship);

  /**
   * @brief Get the embedded file name, which is used in "EmbeddedFile" name tree of current target file.
   *
   * @details This is useful only when relationship is "C". If this property is a valid string,
   *          that means the target file is an embedded file defined in "EmbeddedFiles" name tree.
   *
   * @return Embedded file name.
   */
  WString GetAttachedFileName();

  /**
   * @brief Set the embedded file name, which is used in "EmbeddedFile" name tree of current target file.
   *
   * @details This is useful only when relationship is "C". If this property exists, that means the target file is
   *          an embedded file defined in "EmbeddedFiles" name tree.
   *
   * @param[in] embed_file_name  Name for embedded file.
   *
   * @return None.
   */
  void SetAttachedFileName(const WString& embed_file_name);

  /**
   * @brief Get the page index which specifies the page that contains the target file attachment annotation.
   *
   * @details This is useful only when relationship is "C". If this property exists, that means the target file is
   *          related to a file attachment annotation. And this property just specifies the page which contains
   *          the file attachment annotation. Function @link EmbeddedGotoTarget::GetFileAttachmentAnnotIndex @endlink
   *          can be used to get the annotation index of the target file attachment annotation.
   *
   * @return Page index. Valid value would starts from 0. -1 means no such property
   */
  int GetPageIndex();

  /**
   * @brief Set the page index which specifies the page that contains the target file attachment annotation.
   *
   * @details This is useful only when relationship is "C". If this property exists, that means the target file is
   *          related to a file attachment annotation, and this property just specifies the page which contains
   *          the file attachment annotation. Function @link EmbeddedGotoTarget::SetFileAttachmentAnnotIndex @endlink
   *          can be used to set the annotation index of the target file attachment annotation.
   *
   * @param[in] page_index  Page index to specify a page which contains the target file attachment annotation.
   *                        Valid range: from 0 to (<i>count</i>-1). <i>count</i> means the page count of
   *                        current target PDF file.
   *
   * @return None.
   */
  void SetPageIndex(int page_index);

  /**
   * @brief Get the annotation index which specifies a file attachment annotation in a specified page.
   *
   * @details This is useful only when relationship is "C". If this property exists, that means the target file is
   *          related to a file attachment annotation, and this property just specifies the file attachment annotation
   *          in the specified page. Function @link EmbeddedGotoTarget::GetPageIndex @endlink can be used to
   *          get the page index specifying the page that contains the target file attachment annotation.
   *
   * @return Annotation index which specifies a file attachment annotation. Valid value would starts from 0.
   *         -1 means no such property.
   */
  int GetFileAttachmentAnnotIndex();

  /**
   * @brief Set the annotation index which specifies a file attachment annotation in a specified page.
   *
   * @details This is useful only when relationship is "C". If this property exists, that means the target file is
   *          related to a file attachment annotation, and this property just specifies the file attachment annotation
   *          in the specified page. Function @link EmbeddedGotoTarget::SetPageIndex @endlink can be used to
   *          set the page index specifying the page that contains the target file attachment annotation.
   *
   * @param[in] annot_index  Annotation index to specify the file attachment annotation.
   *                         Valid range: from 0 to (<i>count</i>-1). <i>count</i> means the annotation count
   *                         in that specified page.
   *
   * @return None.
   */
  void SetFileAttachmentAnnotIndex(int annot_index);

  /**
   * @brief Get the target which specifies additional path information to the target document.
   *
   * @return An embedded goto target object. If the return value of function @link EmbeddedGotoTarget::IsEmpty @endlink for
   *         the returned embedded goto target object is <b>true</b>, that means current target object represents
   *         the final target file.
   */
  EmbeddedGotoTarget GetTarget();

  /**
   * @brief Set the target which specifies additional path information to the target document.
   *
   * @param[in] target  An embedded goto target object. If the return value of function @link EmbeddedGotoTarget::IsEmpty @endlink for
   *                    the returned embedded goto target object is <b>true</b>, that means current target object represents
   *                    the final target file.
   *
   * @return None.
   */
  void SetTarget(const EmbeddedGotoTarget& target);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit EmbeddedGotoTarget(FS_HANDLE handle =  NULL);
};

/**
 * Embedded go-to action is similar to a remote go-to action but allows jumping to or from a PDF file that is
 * embedded in another PDF file. Class @link actions::EmbeddedGotoTarget @endlink is derived from @link Action @endlink and
 * offers functions to get/set embedded go-to action data.
 *
 * @see @link Action @endlink
 */
class EmbeddedGotoAction FS_FINAL : public Action {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit EmbeddedGotoAction(const Action& action);

  /**
   * @brief Get the destination information which specifies where to jump to in the final target file.
   *
   * @details For a embedded go-to action, the destination information can be stored as either a destination object
   *          or a destination name:
   *          <ul>
   *          <li>If it is a destination object, function @link EmbeddedGotoAction::GetDestination @endlink would
   *              return a valid destination object.</li>
   *          <li>If it is a destination name, function @link EmbeddedGotoAction::GetDestinationName @endlink would
   *              return a valid string, and the destination name would be defined in the final target PDF file.</li>
   *          </ul>
   *          If the return value of function @link Destination::IsEmpty @endlink for
   *          the returned destination object is <b>true</b> and function @link EmbeddedGotoAction::GetDestinationName @endlink
   *          returns an empty string, that means the embedded go-to action does not have any destination information.
   *
   * @return A destination object. If the return value of function @link Destination::IsEmpty @endlink for
   *         the returned destination object is <b>true</b>, please try function
   *         @link EmbeddedGotoAction::GetDestinationName @endlink.
   */
  Destination GetDestination();

  /**
   * @brief Set the destination information which specifies where to jump to in the final target file.
   *
   * @param[in] destination  A valid destination object to be set.
   *
   * @return None.
   */
  void SetDestination(const Destination& destination);

  /**
   * @brief Get the destination name which is defined in final target PDF file.
   *
   * @details For a remote go-to action, the destination information can be stored as either a destination object or
   *          a destination name:
   *          <ul>
   *          <li>If it is a destination object, function @link EmbeddedGotoAction::GetDestination @endlink
   *              would return a valid destination object.</li>
   *          <li>If it is a destination name, function @link EmbeddedGotoAction::GetDestinationName @endlink
   *              would return a valid string, and the destination name would be defined in the target PDF file.</li>
   *          </ul>
   *          If the return value of function @link Destination::IsEmpty @endlink for
   *          the returned destination object is <b>true</b> and function @link EmbeddedGotoAction::GetDestinationName @endlink
   *          returns an empty string, that means the embedded go-to action does not have any destination information.
   *
   * @return The destination name. If this function returns an empty string, please try function
   *         @link EmbeddedGotoAction::GetDestination @endlink.
   */
  String GetDestinationName();

  /**
   * @brief Set the destination name.
   *
   * @details The destination name should have been in the "Dests" name tree in the target PDF file.
   *
   * @param[in] dest_name  A destination name to be set. It should not be an empty string.
   *
   * @return None.
   */
  void SetDestinationName(const String& dest_name);

  /**
   * @brief Get the file specification of the root file which is the root file for the target.
   *
   * @return A non-embedded file specification object. If the return value of function @link FileSpec::IsEmpty @endlink for
   *         the returned file specification object is <b>true</b>, that means the PDF file which contains
   *         current embedded goto action is just the root file for target object.
   */
  FileSpec GetRootFile();

  /**
   * @brief Set the file specification of the root file which is the root file for the target.
   *
   * @param[in] file_specification  The file specification object:
   *                                <ul>
   *                                <li>It can be constructed by default constructor and not set any value.
   *                                    In this case, that means the PDF file which contains current embedded goto action
   *                                    is also the root file for target.</li>
   *                                <li>Otherwise, this should be a valid file specification object, and should represent
   *                                    another file, not an embedded file. The file specification object should
   *                                    be in the same PDF file as current action.</li>
   *                                </ul>
   *
   * @return None.
   */
  void SetRootFile(const FileSpec& file_specification);

  /**
   * @brief Get the flag which is used to decide whether to open the destination document in a new window or not.
   *
   * @return The new windows flag. It would be one of following values:<br>
   *         <ul>
   *         <li>@link Action::e_NewWindowFlagTrue @endlink means to
   *             open the destination document in a new window.</li>
   *         <li>@link Action::e_NewWindowFlagFalse @endlink means that
   *             the destination document replaces current document in the same window.</li>
   *         <li>@link Action::e_NewWindowFlagNone @endlink means that
   *             no such flag and the viewer application should behave in accordance with the current user preference.
   *         </li>
   *         </ul>
   */
  NewWindowFlag GetNewWindowFlag();

  /**
   * @brief Set the flag which is used to decide whether to open the destination document in a new window or not.
   *
   * @param[in] flag  The new window flag. It should be one of following values:<br>
   *                  <ul>
   *                  <li>@link Action::e_NewWindowFlagTrue @endlink means to
   *                      open the destination document in a new window.</li>
   *                  <li>@link Action::e_NewWindowFlagFalse @endlink means that
   *                      the destination document replaces current document in the same window.</li>
   *                  <li>@link Action::e_NewWindowFlagNone @endlink means that
   *                      no such flag and the viewer application should behave in accordance
   *                      with the current user preference.</li>
   *                  </ul>
   *
   * @return None.
   */
  void SetNewWindowFlag(NewWindowFlag flag);

  /**
   * @brief Get the target.
   *
   * @return An embedded goto target object. If the return value of function @link EmbeddedGotoTarget::IsEmpty @endlink for
   *         the returned embedded goto target object is <b>true</b>, that means no target.
   */
  EmbeddedGotoTarget GetTarget();

  /**
   * @brief Set the target.
   *
   * @param[in] target  An embedded goto target object. If this is constructed by default constructor and
   *                    has not been set any value, that means no target.
   *
   * @return None.
   */
  void SetTarget(const EmbeddedGotoTarget& target);
};

/**
 * Submit-form action is to send data to a uniform resource locator.
 * Class @link actions::SubmitFormAction @endlink is derived from @link Action @endlink and offers functions to
 * get/set submit-form action data.
 *
 * @see @link Action @endlink
 */
class SubmitFormAction FS_FINAL : public Action {
 public:
  /**
   * @brief Enumeration for flags of submit form action.
   *
   * @details Values of this enumeration could be used alone or in a combination.
   */
  typedef enum _Flags {
    /**
   @brief Bit 1. If set, fields name defined in submit form action should be excluded from submitting;
          if not set, only these fields name (including their descendants) are to be submit.
     */
    e_FlagExclude = 0x0001,
    /**
   @brief Bit 2. Submit fields regardless of whether they have a value.
   @note For fields without a value, only the field name is transmitted.
     */
    e_FlagIncludeNoValueFields = 0x0002,
    /**
   @brief Bit 3. Field names and values are submitted in HTML Form format.
   @note Meaningful only if flags @link SubmitFormAction::e_FlagAsXFDF @endlink and
         @link SubmitFormAction::e_FlagSubmitAsPDF @endlink are clear.<br>
         If this flag is clear, that means to submit in Forms Data Format (FDF).
     */
    e_FlagExportFormat = 0x0004,
    /**
   @brief Bit 4. Field names and values are submitted using an HTTP GET request.
   @note Meaningful only when flag @link SubmitFormAction::e_FlagExportFormat @endlink
         is set. If this flag is clear, that means to submit using a POST request.
     */
    e_FlagGetMethod = 0x0008,
    /** @brief Bit 5. Coordinates of the mouse are transmitted as part of the form data. */
    e_FlagWithCoordinates = 0x0010,
    /** @brief Bit 6. Field names and values are submitted as XFDF. */
    e_FlagAsXFDF = 0x0020,
    /**
   @brief Bit 7. Submitted FDF file includes contents as contained in differences entry in the FDF dictionary.
   @note Meaningful only when the form is being submitted in Forms Data Format.
     */
    e_FlagIncludeAppendSaves = 0x0040,
    /**
   @brief Bit 8. Submitted FDF file includes all markup annotations in underlying PDF document.
   @note Meaningful only when the form is being submitted in Forms Data Format.
     */
    e_FlagIncludeAnnotations = 0x0080,
    /** @brief Bit 9. The document is submitted as PDF. */
    e_FlagSubmitAsPDF = 0x0100,
    /** @brief Bit 10. Any submitted field values representing dates are converted to the standard format.*/
    e_FlagCanonicalFormat = 0x0200,
    /**
   @brief Bit 11. Only those markup annotations whose "T" entry matches the name of the current user
          are being submitted.
     */
    e_FlagExclNonUserAnnots = 0x0400,
    /** @brief Bit 12. Submitted FDF excludes "F" entry. */
    e_FlagExclFKey = 0x0800,
    /** @brief Bit 14. "F" entry of submitted FDF is an embedded file stream. */
    e_FlagEmbedForm = 0x2000
  } Flags;
  
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit SubmitFormAction(const Action& action);

  /**
   * @brief Get the URI string of the script at the Web server that will process the submission
   *
   * @return URI string.
   */
  String GetURL();

  /**
   * @brief Set the URI string of the script at the Web server that will process the submission
   *
   * @param[in] url  URI string. It should not be an empty string.
   *
   * @return None.
   */
  void SetURL(const String& url);

  /**
   * @brief Get all field names from the array in current submit form action.
   *
   * @details A submit form action can have an array identifying which fields to include in the submission or
   *          which to exclude, depending on the flag value.
   *
   * @return An array of field names.
   */
  WStringArray GetFieldNames();

  /**
   * @brief Set field name array.
   *
   * @details A submit form action can have an array identifying which fields to include in the submission or
   *          which to exclude, depending on the flag value.
   *
   * @param[in] field_names  An array of form fields' names, to identify which fields to
   *                         include in or exclude from submission. This parameter can be an empty array.
   *                         Field name can be retrieved by function @link interform::Field::GetName @endlink.
   *
   * @return None.
   */
  void SetFieldNames(const WStringArray& field_names);

  /**
   * @brief Get the flag value used for submission.
   *
   * @return Flag value. Please refer to values starting from @link SubmitFormAction::e_FlagExclude @endlink and
   *         this would be one or a combination of these values. 0 means all bits in the flag are 0.
   */
  uint32 GetFlags();

  /**
   * @brief Set the flag value used for submission.
   *
   * @param[in] flags  New flag value. Please refer to values starting from @link SubmitFormAction::e_FlagExclude @endlink and
   *                   this can be one or a combination of these values
   *                   It could also be 0, which means all bits in the flag are 0.
   *
   * @return None.
   */
  void SetFlags(uint32 flags);
};

/**
 * Reset-form action is to set fields to their default values
 * Class @link actions::ResetFormAction @endlink is derived from @link Action @endlink and offers functions to
 * get/set reset-form action data.
 *
 * @see @link Action @endlink
 */
class ResetFormAction FS_FINAL : public Action {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit ResetFormAction(const Action& action);

  /**
   * @brief Get all field names from the array of current reset form action.
   *
   * @details A reset form action can have an array identifying which fields to reset or to exclude from resetting,
   *          depending on the flag value.
   *
   * @return An array of field names.
   */
  WStringArray GetFieldNames();

  /**
   * @brief Set field name array.
   *
   * @details A reset form action can have an array identifying which fields to reset or to exclude from resetting,
   *          depending on the flag value.
   *
   * @param[in] field_names  An array of form fields' names, to identify which fields to reset or
   *                         to exclude from resetting. Field name can be retrieved by function
   *                         @link interform::Field::GetName @endlink.
   *
   * @return None.
   */
  void SetFieldNames(const WStringArray& field_names);

  /**
   * @brief Get the flag value used for resetting.
   *
   * @return Flag value. Currently, the value would be :
   *         <ul>
   *         <li>0: means to reset fields defined in the array.</li>
   *         <li>1: means to reset all fields except those defined in the array.</li>
   *         </ul>
   */
  uint32 GetFlags();

  /**
   * @brief Set the flag value used for resetting.
   *
   * @param[in] flags  Flag value. Currently, valid values are:
   *                   <ul>
   *                   <li>0: means to reset fields defined in the array.</li>
   *                   <li>1: means to reset all fields except those defined in the array.</li>
   *                   </ul>
   *
   * @return None.
   */
  void SetFlags(uint32 flags);
};

/**
 * Import-data action is to import field values from a FDF file.
 * Class @link actions::ImportDataAction @endlink is derived from @link Action @endlink and offers functions to
 * get/set import-data action data.
 *
 * @see @link Action @endlink
 */
class ImportDataAction FS_FINAL : public Action {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit ImportDataAction(const Action& action);

  /**
   * @brief Get the file specification for the FDF file, from which to import form data.
   *
   * @return A file specification object. If the return value of function @link FileSpec::IsEmpty @endlink for
   *         the returned file specification object is <b>true</b>, that means no such object is found.
   */
  FileSpec GetFDFFileSpec();

  /**
   * @brief Set a file specification of a FDF file, from which to import form data.
   *
   * @details File specification of a FDF file is necessary for a import-data action.
   *          So, for a new import-data action, user should call this function to
   *          set the file specification of a FDF file; otherwise the action will be useless.
   *
   * @param[in] file_specification  A file specification object which represents a FDF file.
   *                                It should be valid and be in the same PDF document as current action.
   *
   * @return None.
   */
  void SetFDFFileSpec(const FileSpec& file_specification);
};

/**
 * Hide action is to hide or show specified form fields.
 * Class @link actions::HideAction @endlink is derived from @link Action @endlink and offers functions to
 * get/set hide action data.
 *
 * @see @link Action @endlink
 */
class HideAction FS_FINAL : public Action {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit HideAction(const Action& action);

  /**
   * @brief Get all field names from the array of current hide action.
   *
   * @details A hide action can have an array identifying which fields to hide or to show.
   *          This array is necessary to a hide action.
   *
   * @return An array of field names.
   */
  WStringArray GetFieldNames();

  /**
   * @brief Set field name array.
   *
   * @details A hide action can have an array identifying which fields to hide or to show.
   *          This array is necessary to a hide action. So, for a new hide action, user should
   *          call this function to set the array.
   *
   * @param[in] field_names  An array of form fields' names, to specify which fields is to hide or show.
   *                         Field name can be retrieved by function @link interform::Field::GetName @endlink.
   *
   * @return None.
   */
  void SetFieldNames(const WStringArray& field_names);

  /**
   * @brief Get the hide state.
   *
   * @return <b>true</b> means to hide specified fields , and <b>false</b> means to show specified fields.
   */
  bool GetHideState();

  /**
   * @brief Set the hide state.
   *
   * @details For a new hide action, if no hide state is set, <b>true</b> would be used by default,
   *
   * @param[in] is_hide  <b>true</b> means to hide specified fields, and <b>false</b> means to show specified fields.
   *
   * @return None.
   */
  void SetHideState(bool is_hide);
};

/**
 * Launch action is to launch an application, usually to open a file.
 * Class @link actions::LaunchAction @endlink is derived from @link Action @endlink and offers functions to
 * get/set launch action data.
 *
 * @see @link Action @endlink
 */
class LaunchAction FS_FINAL : public Action {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit LaunchAction(const Action& action);

  /**
   * @brief Get the file specification which specifies the application to be launched
   *        or the document to be opened or printed.
   *
   * @return A file specification object. If the return value of function @link FileSpec::IsEmpty @endlink for
   *         the returned file specification object is <b>true</b>, that means no such property is found.
   */
  FileSpec GetFileSpec();

  /**
   * @brief Set a file specification which specifies an application to be launched
   *        or a document to be opened or printed.
   *
   * @param[in] file_specification  A valid file specification object. This object should be in the same document
   *                                with current action object.
   *
   * @return None.
   */
  void SetFileSpec(const FileSpec& file_specification);

  /**
   * @brief Get the flag which is used to decide whether to open the destination document in a new window or not.
   *
   * @return The new windows flag. It would be one of following values:<br>
   *         <ul>
   *         <li>@link Action::e_NewWindowFlagTrue @endlink means to
   *             open the destination document in a new window.</li>
   *         <li>@link Action::e_NewWindowFlagFalse @endlink means that
   *             the destination document replaces current document in the same window.</li>
   *         <li>@link Action::e_NewWindowFlagNone @endlink means that
   *             no such flag and the viewer application should behave in accordance
   *             with the current user preference.</li>
   *         </ul>
   */
  NewWindowFlag GetNewWindowFlag();

  /**
   * @brief Set the flag which is used to decide whether to open the destination document in a new window or not.
   *
   * @param[in] flag  The new window flag. It should be one of following values:<br>
   *                  <ul>
   *                  <li>@link Action::e_NewWindowFlagTrue @endlink means to
   *                      open the destination document in a new window.</li>
   *                  <li>@link Action::e_NewWindowFlagFalse @endlink means that
   *                      the destination document replaces current document in the same window.</li>
   *                  <li>@link Action::e_NewWindowFlagNone @endlink means that
   *                      no such flag and the viewer application should behave in accordance
   *                      with the current user preference.</li>
   *                  </ul>
   *
   * @return None.
   */
  void SetNewWindowFlag(NewWindowFlag flag);

  /**
   * @brief (Windows-specific launch parameters) Get the file name of the application to be launched or
   *        the document to be opened or printed.
   *
   * @return File name.
   */
  String GetWinFileName();

  /**
   * @brief (Windows-specific launch parameters) Get the default directory in standard DOS syntax.
   *
   * @return Default directory.
   */
  String GetWinDefaultDirectory();

  /**
   * @brief (Windows-specific launch parameters) Get the operation name.
   *
   * @details Standard strings for operation name are:
   *          <ul>
   *          <li>"open": Open a document.</li>
   *          <li>"print": Print a document</li>
   *          </ul>
   *          If the file name of Windows-specific launch parameters represents an application,
   *          the operation name would be useless for current action.
   *
   * @return Operation name.
   */
  String GetWinAppOperation();

  /**
   * @brief (Windows-specific launch parameters) Get parameter string to be passed to the specified application.
   *
   * @details If the file name of Windows-specific launch parameters represents a document,
   *          app parameter string will be ignored.
   *
   * @return Parameter string.
   */
  String GetWinAppParameter();

  /**
   * @brief (Windows-specific launch parameters)Set Windows-specific launch parameters.
   *
   * @details This function is used to set Windows-specific launch parameters.
   *          Parameter <i>file_name</i> is necessary and can represent either an application or a document.
   *          When parameter <i>file_name</i> represents an application, parameters <i>operation</i> and
   *          <i>app_parameter</i> are useless.
   *
   * @param[in] file_name          The file name of the application to be launched or the document to
   *                               be opened or printed. It should not be an empty string.
   * @param[in] default_directory  Default directory in standard DOS syntax.
   * @param[in] operation          Operation name. This can be an empty string. If this is not an empty string,
   *                               it should be one of following strings:
   *                               <ul>
   *                               <li>"open": Open a document.</li>
   *                               <li>"print": Print a document</li>
   *                               </ul>
   * @param[in] app_parameter      Parameter string to be passed to the specified application.
   *
   * @return None.
   */
  void SetWinLaunchParameter(const String& file_name, const String& default_directory,
    const String& operation, const String& app_parameter);

};

/**
 * Rendition action is to control the playing of multimedia content. (For more details, please refer to
 * <PDF Reference 1.7> P668 "Rendition Actions")
 * Class @link actions::RenditionAction @endlink is derived from @link Action @endlink and offers functions to
 * get/set rendition action data.
 *
 * @see @link Action @endlink
 */
class RenditionAction FS_FINAL : public Action {
 public:
  /**
  * @brief Enumeration for operation type to perform when the rendition action is triggered.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _OperationType {
    /** @brief No operation is specified. */
    e_OpTypeNone = -1,
    /**
   @brief Associate rendition to related screen annotation.
   @details If no rendition is associated with related screen annotation,
            play rendition (which is specified in rendition action), associating it with the annotation.
            If a rendition is already associated with related screen annotation, it is stopped, and
            the new rendition (which is specified in rendition action) is associated with the annotation.
     */
    e_OpTypeAssociate = 0,
    /** 
   @brief Stop any rendition being played in association with related screen annotation and remove the association.
          If no rendition is being played, there is no effect.
     */
    e_OpTypeStop = 1,
    /**
   @brief Pause any rendition being played in association with related screen annotation.
          If no rendition is being played, there is no effect.
     */
    e_OpTypePause = 2,
    /**
   @brief Resume any rendition being played in association with related screen annotation.
          If no rendition is being played or the rendition is not paused, there is no effect.
     */
    e_OpTypeResume = 3,
    /**
   @brief Play rendition (which is specified in rendition action), associating it with related screen annotation.
          If a rendition is already associated with the annotation, resume that rendition if it is paused;
          otherwise, do nothing.
     */
    e_OpTypePlay = 4
  } OperationType;
  
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] action  Parent class object.
   */
  explicit RenditionAction(const Action& action);

  /**
   * @brief Get the operation type of current rendition action when being triggered.
   *
   * @details As a useful rendition action, it should contain a JavaScript script to be executed or
   *          is specified an operation type to be performed when triggered. If both JavaScript script and
   *          operation type exist, application should execute JavaScript; if application is unable to
   *          execute JavaScript script, then perform as operation type defines. If no JavaScript script and
   *          operation type is invalid, that means the action is invalid.
   *
   * @return Operation type. Please refer to values starting from @link RenditionAction::e_OpTypeNone @endlink and
   *         this would be one of these values.
   */
  OperationType GetOperationType();
  /**
   * @brief Set the operation type of current rendition action when being triggered.
   *
   * @details As a useful rendition action, it should contain a JavaScript script to be executed or
   *          is specified an operation type to be performed when triggered. If both JavaScript script and
   *          operation type exist, application should execute JavaScript; if application is unable to
   *          execute JavaScript script, then perform as operation type defines. If no JavaScript script and
   *          operation type is invalid, that means the action is invalid.
   *
   * @param[in] op_type  Operation type. Please refer to values starting from @link RenditionAction::e_OpTypeAssociate @endlink
   *                     and this should be one of these values. If set value @link RenditionAction::e_OpTypeNone @endlink,
   *                     that means no operation type is specified.
   *
   * @return None.
   */
  void SetOperationType(OperationType op_type);

  /**
   * @brief Get the count of rendition objects.
   *
   * @return The count of rendition objects.
   */
  int GetRenditionCount() const;
  /**
   * @brief Get a rendition by index.
   *
   * @param[in] index  Index of rendition object to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link RenditionAction::GetRenditionCount @endlink.
   *
   * @return A rendition object.
   */
  Rendition GetRendition(int index);
  /**
   * @brief Insert a rendition to current rendition action, at the position specified by index.
   *
   * @details Rendition object is necessary for a rendition action when operation type is
   *          @link RenditionAction::e_OpTypeAssociate @endlink or @link RenditionAction::e_OpTypeAssociate @endlink.
   *
   * @param[in] rendition  A rendition object to be inserted.
   * @param[in] index      Index that specifies where to insert the rendition object.
   *                       If index is below 0 or bigger than (<i>count</i>-1), the input rendition will
   *                       be inserted to be the end. <i>count</i> is returned by function
   *                       @link RenditionAction::GetRenditionCount @endlink.
   *
   * @return None.
   */
  void InsertRendition(const Rendition& rendition, int index = -1);
  /**
   * @brief Remove a rendition object from current rendition action.
   *
   * @param[in] rendition  A rendition object to be removed from current rendition action.
   *
   * @return None.
   */
  void RemoveRendition(const Rendition& rendition);

  /**
   * @brief Get the related screen annotation.
   *
   * @return A screen annotation object.
   */
  annots::Screen GetScreenAnnot();
  /**
   * @brief Set related screen annotation.
   *
   * @details This property is necessary when operation type is set with valid value.
   *
   * @param[in] screen_annot  A screen annotation object to be set as related screen annotation.
   *
   * @return None.
   */
  void SetScreenAnnot(const annots::Screen& screen_annot);

  /**
   * @brief Get the JavaScript script to be executed.
   *
   * @details As a useful rendition action, it should contain a JavaScript script to be executed or
   *          is specified an operation type to be performed when triggered. If both JavaScript script and
   *          operation type exist, application should execute JavaScript; if application is unable to
   *          execute JavaScript script, then perform as operation type defines. If no JavaScript script and
   *          operation type is invalid, that means the action is invalid.
   *
   * @return A JavaScript script.
   */
  WString GetJavaScript();
  /**
   * @brief Set the JavaScript script to be executed.
   *
   * @details As a useful rendition action, it should contain a JavaScript script to be executed or
   *          is specified an operation type to be performed when triggered. If both JavaScript script and
   *          operation type exist, application should execute JavaScript; if application is unable to
   *          execute JavaScript script, then perform as operation type defines. If no JavaScript script and
   *          operation type is invalid, that means the action is invalid.
   *
   * @param[in] script  A JavaScript script to be set.
   *
   * @return None.
   */
  void SetJavaScript(const WString& script);
};

/**
 * An annotation, page object, or (beginning with PDF 1.3) interactive form field may include an entry named "AA"
 * which specifies an additional-actions dictionary (PDF 1.2) that extends the set of events
 * that can trigger the execution of an action. In PDF 1.4, the document catalog dictionary may also contain
 * an "AA" entry for trigger events affecting the document as a whole.<br>
 * This class can be constructed from PDF document, PDF page, PDF form field, PDF annotation (only some types) or
 * an existing additional-actions dictionary and can be used to get/set data from an additional-actions dictionary
 * from PDF document, PDF page, PDF form field or PDF annotation.
 */
class AdditionalAction FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for trigger event.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _TriggerEvent {
    /**
   @brief Trigger an action to be performed when the page is opened.
   @details This represents "O" entry in a page object's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF page.
     */
    e_TriggerPageOpened = 0,
    /**
   @brief Trigger an action to be performed when the page is closed.
   @details This represents "C" entry in a page object's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF page.
     */
    e_TriggerPageClosed = 1,
    /**
   @brief Trigger a JavaScript action to be performed before closing a document.
   @details This represents "WC" entry in a document catalog's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF document.
     */
    e_TriggerDocWillClose = 2,
    /**
   @brief Trigger a JavaScript action to be performed before saving a document.
   @details This represents "WS" entry in a document catalog's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF document.
     */
    e_TriggerDocWillSave = 3,
    /**
   @brief Trigger a JavaScript action to be performed after saving a document.
   @details This represents "DS" entry in a document catalog's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF document.
     */
    e_TriggerDocSaved = 4,
    /**
   @brief Trigger a JavaScript action to be performed before printing a document.
   @details This represents "WP" entry in a document catalog's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF document.
     */
    e_TriggerDocWillPrint = 5,
    /**
   @brief Trigger a JavaScript action to be performed after printing a document.
   @details This represents "DP" entry in a document catalog's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF document.
     */
    e_TriggerDocPrinted = 6,
    /**
   @brief Trigger a JavaScript action to be performed when the user types a keystroke
          into a text field or combo box or modifies the selection in a scrollable list box.
   @details This represents "K" entry in a form field's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF form field.<br>
            The triggered action can check the keystroke for validity and reject or modify it.
     */
    e_TriggerFieldKeyStroke = 7,
    /**
   @brief Trigger a JavaScript action to be performed before the field is formatted to display its current value.
   @details This represents "F" entry in a form field's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF form field.<br>
            The triggered action can modify the field's value before formatting.
     */
    e_TriggerFieldWillFormat = 8,
    /**
   @brief Trigger a JavaScript action to be performed when the field's value is changed.
   @details This represents "V" entry in a form field's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF form field.<br>
            The triggered action can check the new value for validity.
     */
    e_TriggerFieldValueChanged = 9,
    /**
   @brief Trigger a JavaScript action to be performed to recalculate the value of this field
          when that of another field changes.
   @details This represents "C" entry in a form field's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF form field.<br>
            The order in which the document's fields are recalculated can be gotten by function
            @link interform::Form::GetFieldsInCalculationOrder @endlink.
     */
    e_TriggerFieldRecalculateValue = 10,
    /**
   @brief Trigger an action to be performed when the cursor enters the annotation's active area.
   @details This represents "E" entry in an annotation's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF annotation.
     */
    e_TriggerAnnotCursorEnter = 11,
    /**
   @brief Trigger an action to be performed when the cursor exits the annotation's active area.
   @details This represents "X" entry in an annotation's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF annotation.
     */
    e_TriggerAnnotCursorExit = 12,
    /**
   @brief Trigger an action to be performed when the mouse button is pressed inside the annotation's active area.
   @details This represents "D" (stands for "Down") entry in an annotation's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF annotation.
     */
    e_TriggerAnnotMouseButtonPressed = 13,
    /**
   @brief Trigger an action to be performed when the mouse button is released inside the annotation's active area.
   @details This represents "U" (stands for "Up") entry in an annotation's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF annotation.
     */
    e_TriggerAnnotMouseButtonReleased = 14,
    /**
   @brief (Applicable for widget annotation only) Trigger an action to be performed when the annotation
          receives the input focus.
   @details This represents "Fo" entry in an annotation's additional-actions dictionary.
            Only applicable for additional action object constructed from a widget annotation.
     */
    e_TriggerAnnotReceiveInputFocus = 15,
    /**
   @brief (Applicable for widget annotation only) Trigger an action to be performed when the annotation
          loses the input focus.
   @details This represents "Bl" (Uppercase B and lowercase L, which stands for "blurred") entry in
            an annotation's additional-actions dictionary. Only applicable for additional action object constructed
            from a widget annotation.
     */
    e_TriggerAnnotLoseInputFocus = 16,
    /**
   @brief Trigger an action to be performed when the page containing the annotation is opened.
   @details This represents "PO" entry in an annotation's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF annotation.
            The triggered action is executed after
            action for @link AdditionalAction::e_TriggerPageOpened @endlink is triggered and
            open action of PDF document, if such actions present.
     */
    e_TriggerAnnotPageOpened = 17,
    /**
   @brief Trigger an action to be performed when the page containing the annotation is closed.
   @details This represents "PC" entry in an annotation's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF annotation.
            The triggered action is executed after
            action for @link AdditionalAction::e_TriggerPageClosed @endlink is triggered,
            if such action present.
     */
    e_TriggerAnnotPageClosed = 18,
    /**
   @brief Trigger an action to be performed when the page containing the annotation becomes visible
          in the viewer application's user interface.
   @details This represents "PV" entry in an annotation's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF annotation.
     */
    e_TriggerAnnotPageVisible = 19,
    /**
   @brief Trigger an action to be performed when the page containing the annotation is no longer visible
          in the viewer application's user interface.
   @details This represents "PI" entry in an annotation's additional-actions dictionary.
            Only applicable for additional action object constructed from PDF annotation.
     */
    e_TriggerAnnotPageInvisible = 20
  } TriggerEvent;
  
  /**
   * @brief Constructor, from a PDF document or a PDF dictionary (if any).
   *
   * @param[in] doc       A valid PDF document object.
   * @param[in] pdf_dict  A PDF dictionary which represents an additional action dictionary.
   *                      If this parameter is <b>NULL</b>, that means just to construct an Additional action object
   *                      with PDF document. If this parameter is not <b>NULL</b>, that means to construct
   *                      an Additional action object from this PDF dictionary should have existed
   *                      in the specified PDF document and represents the additional action dictionary.
   *                      Default value: <b>NULL</b>.
   */
   explicit AdditionalAction(const PDFDoc& doc, objects::PDFDictionary* pdf_dict = NULL);

  /**
   * @brief Constructor, from a PDF page.
   *
   * @param[in] page  A valid PDF page object.
   */
  explicit AdditionalAction(const foxit::pdf::PDFPage& page);

  /**
   * @brief Constructor, from a PDF form field.
   *
   * @param[in] field  A valid PDF form field.
   */
  explicit AdditionalAction(const foxit::pdf::interform::Field& field);

  /**
   * @brief Constructor, from a PDF annotation.
   *
   * @param[in] annot  A valid PDF annotation. Currently, only support widget and screen annotation.
   *                   For other types of annotations, this function will throw exception
   *                   @link foxit::e_ErrUnsupported @endlink.
   */
  explicit AdditionalAction(const foxit::pdf::annots::Annot& annot);

  /** @brief Destructor. */
  ~AdditionalAction();

  /**
   * @brief Constructor, with another additional action object.
   *
   * @param[in] other  Another additional action object.
   */
  AdditionalAction(const AdditionalAction& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another additional action object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  AdditionalAction& operator = (const AdditionalAction& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another additional action object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const AdditionalAction& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another additional action object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const AdditionalAction& other) const;
  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get an action with specified trigger event type.
   *
   * @param[in] trigger  The input trigger event type. It should be:
   *                     <ul>
   *                     <li>If current additional-action is constructed from PDF dictionary, the trigger value can be
   *                         one of values defined in enum class TriggerEvent.</li>
   *                     <li>If current additional-action is constructed from PDF page, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerPageOpened @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF document, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerDocWillClose @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF form field, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerFieldKeyStroke @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF annotation, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerAnnotCursorEnter @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     </ul>
   *
   * @return An action object.
   */
  Action GetAction(TriggerEvent trigger);

  /**
   * @brief Set a additional-action for specified trigger event type.
   *
   * @param[in] trigger  The input trigger event type. It should be:
   *                     <ul>
   *                     <li>If current additional-action is constructed from PDF dictionary, the trigger value can be
   *                         one of values defined in enum class TriggerEvent.</li>
   *                     <li>If current additional-action is constructed from PDF page, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerPageOpened @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF document, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerDocWillClose @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF form field, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerFieldKeyStroke @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF annotation, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerAnnotCursorEnter @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     </ul>
   * @param[in] action   An action object to be set.<br>
   *                     If current additional-action is constructed from PDF document or PDF form field, the type of this action should
   *                     be @link Action::e_TypeJavaScript @endlink.<br>
   *                     If current additional-action is constructed from PDF page, PDF annotation, or PDF dictionary,
   *                     please refer to comment of the trigger event to check if only specified type of action
   *                     can be used. Usually, support following types as the new action:<br>
   *                     @link Action::e_TypeGoto @endlink,
   *                     @link Action::e_TypeURI @endlink,
   *                     @link Action::e_TypeJavaScript @endlink,
   *                     @link Action::e_TypeNamed @endlink,
   *                     @link Action::e_TypeGoToR @endlink,
   *                     @link Action::e_TypeGoToE @endlink,
   *                     @link Action::e_TypeSubmitForm @endlink,
   *                     @link Action::e_TypeResetForm @endlink,
   *                     @link Action::e_TypeHide @endlink,
   *                     @link Action::e_TypeLaunch @endlink,
   *                     @link Action::e_TypeImportData @endlink,
   *                     @link Action::e_TypeRendition @endlink.
   *
   * @return None.
   */
  void SetAction(TriggerEvent trigger,const Action& action);

  /**
   * @brief Remove an action with specified trigger event type.
   *
   * @details If there is no action for input trigger event type when it is valid, this function will
   *          return <b>true</b> directly.
   *
   * @param[in] trigger  The input trigger event type. It should be:
   *                     <ul>
   *                     <li>If current additional-action is constructed from PDF dictionary, the trigger value can be
   *                         one of values defined in enum class TriggerEvent.</li>
   *                     <li>If current additional-action is constructed from PDF page, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerPageOpened @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF document, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerDocWillClose @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF form field, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerFieldKeyStroke @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF annotation, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerAnnotCursorEnter @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     </ul>
   *
   * @return <b>true</b> means success , while <b>false</b> means failure.
   */
  bool RemoveAction(TriggerEvent trigger);

  /**
  * @brief Remove all actions.
  *
  * @return <b>true</b> means success , while <b>false</b> means failure.
  */
  bool RemoveAllActions();

  /**
   * @brief Perform javascript action which is specified by a trigger event type.
   *
   * @details If current object is constructed with a valid PDF dictionary, current function will return <b>false</b>
   *          directly because Foxit PDF SDK cannot know which kind of object the additional action dictionary is
   *          associated with.
   *
   * @param[in] trigger  The input trigger event type. It should be:
   *                     <ul>
   *                     <li>If current additional-action is constructed from PDF page, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerPageOpened @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF document, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerDocWillClose @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF form field, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerFieldKeyStroke @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     <li>If current additional-action is constructed from PDF annotation, the trigger value must be
   *                         one of values starting from @link AdditionalAction::e_TriggerAnnotCursorEnter @endlink
   *                         (with same prefix name).
   *                     </li>
   *                     </ul>
   *
   * @return <b>true</b> means success , while <b>false</b> means failure or current object is constructed
   *         from PDF dictionary.
   */
  bool DoJSAction(TriggerEvent trigger);

  /**
   * @brief Get the PDF dictionary of current object.
   *
   * @return The PDF dictionary.
   */
  objects::PDFDictionary* GetDict() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit AdditionalAction(FS_HANDLE handle =  NULL);
};
}  // namespace actions
}  // namespace pdf
}  // namespace foxit

#endif  // FS_ACTION_H_

