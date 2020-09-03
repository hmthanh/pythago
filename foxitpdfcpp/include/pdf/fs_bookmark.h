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
 * @file fs_bookmark.h
 * @brief Header file for bookmark related definitions and classes.
 */

#ifndef FS_BOOKMARK_H_
#define FS_BOOKMARK_H_

#include "common/fs_common.h"
#include "pdf/actions/fs_action.h"
#include "pdf/objects/fs_pdfobject.h"

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
/**
 * PDF bookmark is also called "outline". It's a tree-structured hierarchy. It allows user to navigate PDF document
 * easily by selecting a bookmark. One bookmark contains a destination or actions to indicate how to response
 * when user selects it.<br>
 * In order to get/set the bookmark tree, function @link PDFDoc::GetRootBookmark @endlink must be called first to
 * get the root of the whole bookmark tree. If the "root bookmark" does not exist, function
 * @link PDFDoc::CreateRootBookmark @endlink could be called to create a new "root bookmark".
 * Here, "root bookmark" is an abstract object. It represents the  "Outline" of PDF document.
 * For more details about "Outline", please refer to  Section 8.2.3 in PDF Reference 1.7.
 * "root bookmark" can only have some child bookmarks, but no parent,
 * no next sibling bookmarks or any data (including bookmark data, destination data and action data).
 * And "root bookmark" cannot be shown on the application UI since it has no data. So, for a root bookmark,
 * only function @link Bookmark::GetFirstChild @endlink can be used.<br>
 * From the root bookmark, the bookmark tree can be traversed and each bookmark node can be accessed.<br>
 * This class offers several functions to get/set other bookmarks from current bookmark. For example:
 * <ul>
 * <li>To access the parent bookmark, use function @link Bookmark::GetParent @endlink.</li>
 * <li>To access the first child bookmark, use function @link Bookmark::GetFirstChild @endlink.</li>
 * <li>To access the next sibling bookmark, use function @link Bookmark::GetNextSibling @endlink.</li>
 * <li>To Insert a new bookmark, use function @link Bookmark::Insert @endlink.</li>
 * <li>To move a bookmark, use function @link Bookmark::MoveTo @endlink. </li>
 * </ul>
 * This class also offers functions to get/set the data of a PDF bookmark.
 *
 * @see @link PDFDoc @endlink
 */
class Bookmark FS_FINAL : public Base{
 public:
  /**
   * @brief Enumeration for bookmark style type.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _Style {
    /** @brief Show bookmark title as normal text. */
    e_StyleNormal  = 0x00,
    /** @brief Show bookmark title as italic text. */
    e_StyleItalic  = 0x01,
    /** @brief Show bookmark title as bold text. */
    e_StyleBold    = 0x02
  } Style;
  
  /**
   * @brief Enumeration for bookmark position.
   *
   * @details Values of this enumeration should be used alone.<br>
   *          Actually, "bookmark position" means the relationship between a bookmark and another bookmark.
   */
  typedef enum _Position {
    /** @brief A bookmark is the first child of another specified bookmark. */
    e_PosFirstChild  = 0,
    /** @brief A bookmark is the last child of another specified bookmark. */
    e_PosLastChild = 1,
    /** @brief A bookmark is the previous sibling of another specified bookmark. */
    e_PosPrevSibling = 2,
    /** @brief A bookmark is the next sibling of another specified bookmark. */
    e_PosNextSibling = 3,
    /** @brief A bookmark is the first sibling of another specified bookmark. */
    e_PosFirstSibling = 4,
    /** @brief A bookmark is the last sibling of another specified bookmark. */
    e_PosLastSibling = 5
  } Position;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] pdf_doc        A valid PDF document object.
   * @param[in] bookmark_dict  A PDF dictionary which represents a bookmark. This PDF dictionary should have existed
   *                           in the PDF document represented by parameter <i>pdf_doc</i>.
   */
  Bookmark(const PDFDoc& pdf_doc, objects::PDFDictionary* bookmark_dict);
  /**
   * @brief Constructor, with another bookmark object.
   *
   * @param[in] other  Another bookmark object.
   */
  Bookmark(const Bookmark& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another bookmark object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Bookmark& operator = (const Bookmark& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another bookmark object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Bookmark& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another bookmark object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Bookmark& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /** @brief Destructor. */
  ~Bookmark();

  /**
   * @brief Get the parent bookmark.
   *
   * @details If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have a parent bookmark. In this case, this function will
   *          return a bookmark object which's function @link Bookmark::IsEmpty @endlink returns <b>true</b>.
   *
   * @return The parent bookmark object.
   */
  Bookmark GetParent();

  /**
   * @brief Check if current bookmark has child bookmark(s).
   *
   * @return <b>true</b> means current bookmark has child bookmark(s), and <b>false</b> means
   *         current bookmark does not have any child bookmark.
   */
  bool HasChild();

  /**
   * @brief Get the first child bookmark.
   *
   * @return The first child bookmark object.
   */
  Bookmark GetFirstChild();

  /**
   * @brief Get the next sibling bookmark.
   *
   * @details If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have any sibling bookmark. In this case, this function will
   *          return a bookmark object which's function @link Bookmark::IsEmpty @endlink returns <b>true</b>.
   *
   * @return The next sibling bookmark object.
   */
  Bookmark GetNextSibling();

  /**
   * @brief Get the destination.
   *
   * @details Bookmark's destination is some place in current document where the bookmark can "goto".
   *          If the bookmark cannot "goto" any place in current document, that means no destination information can
   *          be retrieved and this function will return a destination object which's function
   *          @link Destination::IsEmpty @endlink returns <b>true</b>.<br>
   *          If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have any destination information. In this case, this function will
   *          return a destination object which's function @link Destination::IsEmpty @endlink returns <b>true</b>.
   *
   * @return The destination object.
   */
  Destination GetDestination();

  /**
   * @brief Set the destination.
   *
   * @details Bookmark's destination is some place in current document where the bookmark can "goto".<br>
   *          If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have any destination information. In this case, this function will
   *          return directly without doing anything.
   *
   * @param[in] destination  A valid destination.
   *
   * @return None.
   */
  void SetDestination(const Destination& destination);

  /**
   * @brief Get the title.
   *
   * @details If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have title. In this case, this function will return an empty string.
   *
   * @return The title string.
   */
  WString GetTitle() const;

  /**
   * @brief Set the title.
   *
   * @details If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have title. In this case, this function will return directly without doing anything.
   *
   * @param[in] title  New title string. It should not be an empty string.
   *
   * @return None.
   */
  void SetTitle(const WString& title);

  /**
   * @brief Get the color used for displaying title.
   *
   * @details If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have color. In this case, this function will return 0x000000
   *          by default.
   *
   * @return The color used for displaying title. Format: 0xRRGGBB.
   */
  RGB GetColor() const;

  /**
   * @brief Set the color used for displaying title.
   *
   * @details If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have color. In this case, this function will return directly
   *          without doing anything.
   *
   * @param[in] color  New color used for displaying title. Format:0xRRGGBB.
   *
   * @return None.
   */
  void SetColor(RGB color);

  /**
   * @brief Get the style.
   *
   * @details If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have style information. In this case, this function will return
   *          @link Bookmark::e_StyleNormal @endlink by default.
   *
   * @return Value for The bookmark style. Please refer to values starting from @link Bookmark::e_StyleNormal @endlink and
   *         this would be one or a combination of these values.
   */
  uint32 GetStyle() const;

  /**
   * @brief Set the style.
   *
   * @details If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have style information. In this case, this function will
   *          return directly without doing anything.
   *
   * @param[in] style  New bookmark style. Please refer to values starting from @link Bookmark::e_StyleNormal @endlink and
   *                   this can be one or a combination of these values.
   *                   If the <i>style</i> is invalid, @link Bookmark::e_StyleNormal @endlink will be set by default.
   *
   * @return None.
   */
  void SetStyle(uint32 style);

  /**
   * @brief Insert a new bookmark according to the relationship position to current bookmark.
   *
   * @details For the new bookmark, the color would be 0x000000 and the style would be
   *          @link Bookmark::e_StyleNormal @endlink by default.<br>
   *
   * @param[in] title     Title string for the new bookmark. It should not be an empty string.
   * @param[in] position  The position where the new bookmark item is to be inserted, based on current bookmark.
   *                      Please refer to values starting from @link Bookmark::e_PosFirstChild @endlink and
   *                      this should be one of these values.<br>
   *                      If current bookmark is just the "root bookmark", parameter <i>position</i> can only be
   *                      @link Bookmark::e_PosFirstChild @endlink or @link Bookmark::e_PosLastChild @endlink.
   *
   * @return A new bookmark object.
   */
  Bookmark Insert(const WString& title, Position position);

  /**
   * @brief Move current bookmark to be child or sibling of another bookmark.
   *
   * @details If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it cannot be moved to be child or sibling of any bookmark in the bookmark tree.
   *          In this case, this function will return <b>false</b> directly.
   *
   * @param[in] dest_bookmark  The destination bookmark. It should not be current bookmark itself or
   *                           any descendant of current bookmark.<br>
   *                           Current bookmark will be moved to be child or sibling of the destination bookmark.
   * @param[in] position       The position where the current bookmark is to be moved to,
   *                           based on parameter <i>destBookmark</i>. Please refer to values starting from
   *                           @link Bookmark::e_PosFirstChild @endlink and this should be one of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool MoveTo(const Bookmark& dest_bookmark, Position position);

  /**
   * @brief Get action.
   *
   * @details If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have any action information. In this case, this function will
   *          return an action object which's function @link actions::Action::IsEmpty @endlink returns <b>true</b>.
   *
   * @return An action object.
   */
  actions::Action GetAction();

  /**
   * @brief Set action.
   *
   * @details If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have any action information. In this case, this function will
   *          return directly without doing anything.
   *
   * @param[in] action  A valid action to be set. Currently only support following types as the new action:<br>
   *                    @link actions::Action::e_TypeGoto @endlink, @link actions::Action::e_TypeURI @endlink,
   *                    @link actions::Action::e_TypeJavaScript @endlink, @link actions::Action::e_TypeNamed @endlink,
   *                    @link actions::Action::e_TypeGoToR @endlink, @link actions::Action::e_TypeGoToE @endlink,
   *                    @link actions::Action::e_TypeSubmitForm @endlink, @link actions::Action::e_TypeResetForm @endlink,
   *                    @link actions::Action::e_TypeHide @endlink, @link actions::Action::e_TypeLaunch @endlink,
   *                    @link actions::Action::e_TypeImportData @endlink, @link actions::Action::e_TypeRendition @endlink.
   *
   * @return None.
   */
  void SetAction(const actions::Action& action);

  /**
   * @brief Remove action.
   *
   * @details When removing bookmark's action, bookmark's destination will be removed at the same time.<br>
   *          If current bookmark is returned by function @link PDFDoc::GetRootBookmark @endlink
   *          or @link PDFDoc::CreateRootBookmark @endlink, that means it is the "root bookmark",
   *          and it does not have any action information. In this case, this function will
   *          return <b>true</b> directly.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveAction();

  /**
   * @brief Check if current bookmark is the root bookmark.
   *
   * @details "root bookmark" is an abstract object. It represents the  "Outline" of PDF document.
   *          For more details about "Outline", please refer to  Section 8.2.3 in PDF Reference 1.7.
   *          "root bookmark" can only have some child bookmarks, but no parent,
   *          no next sibling bookmarks or any data (including bookmark data, destination data and action data).
   *          And "root bookmark" cannot be shown on the application UI since it has no data.
   *
   * @return <b>true</b> means current bookmark is the root bookmark, while <b>false</b> means not.
   */
  bool IsRoot();

  /**
   * @brief Check if current bookmark is the first child of its parent bookmark.
   *
   * @return <b>true</b> means current bookmark is the first child of its parent bookmark,
   *         while <b>false</b> means not.
   */
  bool IsFirstChild();

  /**
   * @brief Check if current bookmark is the last child of its parent bookmark.
   *
   * @return <b>true</b> means current bookmark is the last child of its parent bookmark,
   *         while <b>false</b> means not.
   */
  bool IsLastChild();

  /**
   * @brief Get PDF dictionary of current bookmark.
   *
   * @return The PDF dictionary.
   */
  objects::PDFDictionary* GetDict() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Bookmark(FS_HANDLE handle =  NULL);

};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_BOOKMARK_H_

