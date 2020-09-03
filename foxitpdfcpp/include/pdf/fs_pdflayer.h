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
 * @file fs_pdflayer.h
 * @brief Header file for PDF layer related definitions and classes.
 */

#ifndef FS_PDFLAYER_H_
#define FS_PDFLAYER_H_

#include "common/fs_common.h"
#include "pdf/graphics/fs_pdfgraphicsobject.h"

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
class PDFDoc;
class PDFPage;
class LayerPrintData;
class LayerNode;

/** This class represents an array of layer nodes. */
FSDK_DEFINE_ARRAY(LayerNodeArray, LayerNode)

/**
 * This class represents data for PDF layer zooming usage.
 */
class LayerZoomData FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  LayerZoomData()
      : min_factor(0)
      , max_factor(0) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] min_factor  The minimum recommended magnification factor, in float.
   *                        A negative number means no minimum zoom factor.
   * @param[in] max_factor  The magnification factor, in float.
   *                        A negative number means no magnification zoom factor.
   */
  LayerZoomData(float min_factor, float max_factor) {
    this->min_factor = min_factor;
    this->max_factor = max_factor;
  }

  /**
   * @brief Constructor, with another layer zoom data object.
   *
   * @param[in] data  Another layer zoom data object.
   */
  LayerZoomData(const LayerZoomData& data) {
    min_factor = data.min_factor;
    max_factor = data.max_factor;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another layer zoom data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  LayerZoomData &operator = (const LayerZoomData& data) {
    min_factor = data.min_factor;
    max_factor = data.max_factor;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] min_factor  The minimum recommended magnification factor, in float.
   *                        A negative number means no minimum zoom factor.
   * @param[in] max_factor  The magnification factor, in float.
   *                        A negative number means no magnification zoom factor.
   *
   * @return None.
   */
  void Set(float min_factor, float max_factor) {
    this->min_factor = min_factor;
    this->max_factor = max_factor;
  }

  /**
   * @brief The minimum recommended magnification factor at which the group should be ON.
   *        A negative number means no minimum zoom factor.
   */
  float min_factor;
  /**
   * @brief The magnification factor below which the group should be ON.
   *         A negative number means no magnification zoom factor.
   */
  float max_factor;
};

/**
 * PDF layer nodes are stored in a PDF layer tree. If user wants to retrieve a layer node, user must construct
 * a layer tree object from a PDF document first and then call function @link LayerTree::GetRootNode @endlink to
 * get the root layer node of the whole layer tree. Then, user can enumerate all the nodes in the layer tree
 * from the root layer node.
 *
 * @see @link LayerNode @endlink
 */
class LayerTree FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for PDF layer base state.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _UsageState {
    /** @brief The state is ON. */
    e_StateON = 0x0000,
    /** @brief The state is OFF. */
    e_StateOFF = 0x0001,
    /** @brief The state is unchanged. */
    e_StateUnchanged = 0x0002,
    /** @brief The state is undefined. */
    e_StateUndefined = 0x0003
  } UsageState;
  

  /**
   * @brief Constructor, from a PDF document.
   *
   * @details The constructed layer tree object can be associated with existed layer tree in PDF document.
   *          If there is no layer tree in PDF document which can be judged by functoin @link PDFDoc::HasLayer @endlink,
   *          the constructed layer tree object will build layer related dictionary.
   *
   * @param[in] document  A valid PDF document object.
   */
  explicit LayerTree(const PDFDoc& document);
  /**
   * @brief Constructor, with another layer tree object.
   *
   * @param[in] other  Another layer tree object.
   */
  LayerTree(const LayerTree& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another layer tree object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  LayerTree& operator = (const LayerTree& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another layer tree object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const LayerTree& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another layer tree object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const LayerTree& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;
  /** @brief Destructor. */
  ~LayerTree();

  /**
   * @brief Set the base state for all layers in the default configuration.
   *
   * @details If user wants the new state to have effect on rendering result, please construct a new layer context object
   *          after this function succeeds, and then use the new LayerContext to Renderer to do rendering.<br>\
   *
   * @param[in] state  Layer usage state. Please refer to values starting from @link LayerTree::e_StateON @endlink and
   *                   this should be one of these values except @link LayerTree::e_StateUndefined @endlink.
   *
   *  @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetBaseState(UsageState state);

  /**
   * @brief Get the root layer node.
   *
   * @details After getting the root layer node, user can enumerate all layer nodes in current layer tree by
   *          functions of class LayerNode.
   *
   * @return Root layer node.
   */
  LayerNode GetRootNode();

  /**
   * @brief Get the dictionary of current object.
   *
   * @note Please refer to "Optional Content Properties Dictionary" in <PDF Reference 1.7> P375 for more details.
   *
   * @return The dictionary of current object.
   */
  objects::PDFDictionary* GetDict() const;

  /**
   * @brief Get the "OCGs" PDF array from current object.
   *
   * @note Please refer to "Optional Content Properties Dictionary" in <PDF Reference 1.7> P375 for more details.
   *
   * @return The "OCGs" PDF array.
   */
  objects::PDFArray* GetOCGs() const;
#ifndef __EMSCRIPTEN_RENDER__
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit LayerTree(FS_HANDLE handle =  NULL);
#endif
};

/**
 * This class represents a layer context for rendering. If user wants to render layers, please construct
 * a layer context object first and then set it to a @link common::Renderer @endlink object by function
 * @link common::Renderer::SetLayerContext @endlink.
 *
 * @see @link common::Renderer @endlink
 */
class LayerContext FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for PDF layer usage type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _UsageType {
    /** @brief Use for a viewer. */
    e_UsageView = 0x0000,
    /** @brief Use for representing a document designer's structural organization of artwork. */
    e_UsageDesign = 0x0001,
    /** @brief Use for printing. */
    e_UsagePrint = 0x0002,
    /** @brief Use for exporting. */
    e_UsageExport = 0x0003,
    /** @brief Use for zooming. */
    e_UsageZoom = 0x0004
  } UsageType;
  

  /**
   * @brief Constructor, based on a PDF document and specified layer usage type.
   *
   * @param[in] document    A valid PDF document object.
   * @param[in] usage_type  Layer usage type. Please refer to values starting from @link LayerContext::e_UsageView @endlink
   *                        and this should be one of these values except @link LayerContext::e_UsageZoom @endlink.
   */
  explicit LayerContext(const PDFDoc& document, UsageType usage_type);

  /**
   * @brief Constructor, with another layer context object.
   *
   * @param[in] other  Another layer context object.
   */
  LayerContext(const LayerContext& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another layer context object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  LayerContext& operator = (const LayerContext& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another layer context object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const LayerContext& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another layer context object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const LayerContext& other) const;
  /** @brief Destructor. */
  ~LayerContext();
  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the related PDF document.
   *
   * @return The related PDF document object.
   */
  PDFDoc GetDocument();
  /**
   * @brief Get the layer usage type for rendering.
   *
   * @return Layer usage type. Please refer to values starting from @link LayerContext::e_UsageView @endlink and
   *         this would be one of these values except @link LayerContext::e_UsageZoom @endlink.
   */
  UsageType GetUsageType();
  /**
   * @brief Reset current layer context, back to the initialized state.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Reset();
  /**
   * @brief Copy states from another layer context.
   *
   * @param[in] source_context  The source layer context, whose state will be copied to current layer context.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool CopyStates(const LayerContext& source_context);
  /**
   * @brief Merge states from another layer context.
   *
   *  @param[in] source_context  The source layer context, whose state will be merged to current layer context.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.

  */
  bool MergeStates(const LayerContext& source_context);
  /**
   * @brief Check if a specified layer node is visible in current layer context.
   *
   * @param[in] layer  A layer node. It should belong to the same PDF document which is related to
   *                   current layer context.
   *
   * @return <b>true</b> means the layer node is visible, while <b>false</b> means the layer node is invisible.
   */
  bool IsVisible(const LayerNode& layer);
  /**
   * @brief Set the visibility of a specified layer node in current layer context.
   *
   * @param[in] layer         A layer node. It should belong to the same PDF document which is related to
   *                          current layer context.
   * @param[in] is_visible    <b>true</b> means visible, and <b>false</b> means invisible.
   *
   * @return <b>true</b> means the layer node is visible, while <b>false</b> means the layer node is invisible.
   */
  bool SetVisible(const LayerNode& layer, bool is_visible);
#ifndef __EMSCRIPTEN_RENDER__
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit LayerContext(FS_HANDLE handle =  NULL);
#endif
};

/**
 * A PDF layer (known as "Optional content group" in <PDF reference 1.7>) is a collection of graphics
 * (known as @link graphics::GraphicsObject @endlink in Foxit PDF SDK) that can be made visible or invisible. These graphics
 * belonging to the same layer can reside anywhere in the document: they need not be consecutive in drawing order,
 * nor even belong to the same content stream.<br>
 * In Foxit PDF SDK, a PDF layer is associated with a layer node and Foxit PDF SDK offers class and methods to
 * get/set layer data via layer node. If user wants to retrieve a layer node, user must construct
 * a layer tree object first and then call function @link LayerTree::GetRootNode @endlink to get the root layer node
 * of the whole layer tree. Here, "root layer node" is an abstract object. "root layer node" can only have
 * some child layer nodes but no parent, or any data (such as name, intent and so on). And "root layer node" cannot
 * be shown on the application UI since it has no data. So, for a root layer node, only functions
 * @link LayerNode::GetChildrenCount @endlink and @link LayerNode::GetChild @endlink are useful.<br>
 * This class offers functions to get/set layer data and the graphics belonging to it. For example:
 * <ul>
 * <li>To get/set layer data, following functions can be used: @link LayerNode::GetName @endlink,
 *     @link LayerNode::GetViewUsage @endlink, @link LayerNode::GetExportUsage @endlink, @link LayerNode::GetPrintUsage @endlink,
 *     @link LayerNode::GetZoomUsage @endlink and setting functions for these data.</li>
 * <li>To get the graphics belonging to it, use function @link LayerNode::GetGraphicsObjects @endlink;
 *     function @link LayerNode::AddGraphicsObject @endlink and @link LayerNode::RemoveGraphicsObject @endlink can
 *     be used to add/remove a specified graphics object to/from the layer.</li>
 * </ul>
 *
 * @see @link LayerTree @endlink
 */
class LayerNode FS_FINAL : public Base{
 public:
  /**
   * @brief Constructor, with another layer node object.
   *
   * @param[in] other  Another layer node object.
   */
  LayerNode(const LayerNode& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another layer node object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  LayerNode& operator = (const LayerNode& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another layer node object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const LayerNode& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another layer node object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const LayerNode& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;
  /** @brief Destructor. */
  ~LayerNode();

  /**
   * @brief Get the count of children nodes.
   *
   * @return The count of children nodes.
   */
  int GetChildrenCount();
  /**
   * @brief Get a child node.
   *
   * @param[in] index  Index of the child to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link LayerNode::GetChildrenCount @endlink.
   *
   * @return A child layer node object.
   */
  LayerNode GetChild(int index);
  /**
   * @brief Remove a child node by index.
   *
   * @param[in] index  Index of the child node to be removed. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link LayerNode::GetChildrenCount @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveChild(int index);
  /**
   * @brief Move current layer node to be one of the children of another layer node.
   *
   * @param[in] parent_layer_node  The destination layer node. It should not be current layer node itself or
   *                               any descendant of current layer node. Current layer node will be moved to be
   *                               one of the children of the destination layer node.
   * @param[in] index              Child index which specifies where current layer node will be moved
   *                               as a child of destination layer node. Valid range: from 0 to <i>count</i>.
   *                               <i>count</i> means to be the last child of destination layer node and
   *                               is returned by function @link LayerNode::GetChildrenCount @endlink
   *                               for parameter <i>parent_layer_node</i>.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool MoveTo(LayerNode parent_layer_node, int index);
  /**
   * @brief Add a new layer node as a child for current layer node.
   *
   * @param[in] index      Child index for the new child layer node. Valid range: from 0 to <i>count</i>.
   *                       <i>count</i> means to be the last child of current layer node and
   *                       is returned by function @link LayerNode::GetChildrenCount @endlink for current layer node.
   * @param[in] name       Name for the new layer node. It should not be an empty string.
   * @param[in] has_Layer  <b>true</b> means the new child layer node would be associated with a layer,
   *                       and <b>false</b> means the new child layer node is not associated with a layer.
   *
   * @return A layer node object that specifies the new child layer node.
   */
  LayerNode AddChild(int index, const wchar_t* name, bool has_Layer);
  /**
   * @brief Get the name of current layer node.
   *
   * @return Layer node name.
   */
  WString GetName();
  
  /**
   * @brief Check if current layer node is locked.
   *
   * @return <b>true</b> means current layer node is locked,
   *         while <b>false</b> means current layer node is not locked.
   */
   bool IsLocked();

  /**
   * @brief Check if current layer node is associated with a layer.
   *
   * @return <b>true</b> means current layer node is associated with a layer,
   *         while <b>false</b> means current layer node is not associated with a layer.
   */
  bool HasLayer();
  /**
   * @brief Check if current layer node has a specified intent.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.<br>
   *          Specially, when this function with input parameter "View" returns <b>false</b>,
   *          that means the layer related to current layer node will always be visible, and will not be
   *          affected by the changing in visibility.
   *
   * @param[in] intent  Intent name to be checked. It should not be an empty string.
   *                    Pre-defined intent names are "View" and "Design".
   *
   * @return <b>true</b> means current layer node has the specified intent,
   *         while <b>false</b> means current layer node does not the specified intent.
   */
  bool HasIntent(const char* intent);
  /**
   * @brief Check if current layer node is in a specified PDF page.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *
   * @param[in] page  A valid PDF page.
   *
   * @return <b>true</b> means current layer node is in the specified PDF page,
   *         while <b>false</b> means current layer node is not in the specified PDF page.
   */
  bool IsInPage(const PDFPage& page);
  /**
   * @brief Get the state for viewing usage.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *
   * @return Layer usage state. Please refer to values starting from @link LayerTree::e_StateON @endlink and
   *         this would be one of these values except @link LayerTree::e_StateUnchanged @endlink.
   */
  LayerTree::UsageState GetViewUsage();
  /**
   * @brief Get the state for exporting usage.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *
   * @return Layer usage state. Please refer to values starting from @link LayerTree::e_StateON @endlink and
   *         this would be one of these values except @link LayerTree::e_StateUnchanged @endlink.
   */
  LayerTree::UsageState GetExportUsage();
  /**
   * @brief Get the data for printing usage.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *
   * @return Data for layer printing usage.
   */
  LayerPrintData GetPrintUsage();
  /**
   * @brief Get the data for zooming usage.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *
   * @return Data for layer zooming usage.
   */
  LayerZoomData GetZoomUsage();
  /**
   * @brief Set the name of current layer node.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *
   * @param[in] name  New layer node name. It should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetName(const wchar_t* name);
  /**
   * @brief Set default visibility.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *
   * @param[in] is_visible  <b>true</b> means visible, and <b>false</b> means invisible.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetDefaultVisible(bool is_visible);
  /**
   * @brief Set state for viewing usage.
   *
   * @details If user wants the new state to have effect on rendering result, please construct a new layer context object
   *          after this function succeeds, and then use the new layer context object to Renderer to do rendering.<br>
   *          This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *          
   *
   * @param[in] state  Layer usage state. It should be one of following values:
   *                   <ul>
   *                   <li>@link LayerTree::e_StateON @endlink</li>
   *                   <li>@link LayerTree::e_StateOFF @endlink</li>
   *                   <li>@link LayerTree::e_StateUndefined @endlink means to remove this property from current layer node</li>
   *                   </ul>
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetViewUsage(LayerTree::UsageState state);
  /**
   * @brief Set state for exporting usage.
   *
   * @details If user wants the new state to have effect on rendering result, please construct a new layer context object
   *          after this function succeeds, and then use the new layer context object to Renderer to do rendering.<br>
   *          This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *
   * @param[in] state  Layer usage state. It should be one of following values:
   *                   <ul>
   *                   <li>@link LayerTree::e_StateON @endlink</li>
   *                   <li>@link LayerTree::e_StateOFF @endlink</li>
   *                   <li>@link LayerTree::e_StateUndefined @endlink means to remove this property from current layer node</li>
   *                   </ul>
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetExportUsage(LayerTree::UsageState state);
  /**
   * @brief Set data for layer printing usage.
   *
   * @details If user wants the new state to have effect on rendering result, please construct a new layer context object
   *          after this function succeeds, and then use the new layer context object to Renderer to do rendering.<br>
   *          This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *
   * @param[in] data  New data for layer printing usage. The value of <i>print state</i> of input data
   *                  should be one of following values:
   *                  <ul>
   *                  <li>@link LayerTree::e_StateON @endlink</li>
   *                  <li>@link LayerTree::e_StateOFF @endlink</li>
   *                  <li>@link LayerTree::e_StateUndefined @endlink means to remove this property from current layer node</li>
   *                  </ul>
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetPrintUsage(const LayerPrintData& data);
  /**
   * @brief Set data for layer zooming usage.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *
   * @param[in] data  New data for layer zooming usage.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetZoomUsage(const LayerZoomData& data);

  /**
   * @brief Get all graphics objects related to the layer which is associated with current layer node.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.<br>
   *
   * @param[in] page  A valid PDF page, to which the input graphics object belongs.
   *
   * @return A graphics object array which contains related graphic objects.
   */
  graphics::GraphicsObjectArray GetGraphicsObjects(const PDFPage& page);

  /**
   * @brief Add a graphics object to current layer node.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.
   *
   * @param[in] page            A valid PDF page, to which the input graphics object belongs.
   * @param[in] graphicsobject  A graphics object to be added to current layer node.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool AddGraphicsObject(const PDFPage& page, graphics::GraphicsObject* graphicsobject);
  /**
   * @brief Remove a graphics object from current layer node.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.<br>
   *          If the input graphics object does not belong to current layer node,
   *          this function will return <b>true</b> directly.
   *
   * @param[in] graphics_object  A graphics object to be removed from current layer node.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveGraphicsObject(graphics::GraphicsObject* graphics_object);
  /**
   * @brief Remove a kind of usage property.
   *
   * @details This function can only be used when function @link LayerNode::HasLayer @endlink returns <b>true</b>.
   *          If current layer node does not have layer, this function will throw exception
   *          @link foxit::e_ErrUnsupported @endlink.<br>
   *          If current layer node does not have the specified usage or does not have any usage,
   *          this function will return <b>true</b>.
   *
   * @param[in] usage_type  Layer usage type to be removed. Please refer to values starting from
   *                        @link LayerContext::e_UsageView @endlink and this should be one of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RemoveUsage(LayerContext::UsageType usage_type);

  /**
   * @brief Get the PDF dictionary of current object.
   *
   * @note Please refer to "Optional Content Groups" in <PDF Reference 1.7> P364 for more details.
   *
   * @return The PDF dictionary. If @link LayerNode::HasLayer @endlink of current layer node returns <b>false</b>,
   *         this function will return <b>NULL</b>.
   */
  objects::PDFDictionary* GetDict() const;

#ifndef __EMSCRIPTEN_RENDER__
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit LayerNode(FS_HANDLE handle =  NULL);
#endif
};

/**
 * This class represents data for PDF layer printing usage.
 */
class LayerPrintData FS_FINAL : public Object {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] subtype      A string to specify the kind of content controlled by a layer.
   * @param[in] print_state  Layer usage state, indicating that the layer should be set to
   *                         that state when the document is printed from a viewer application.
   *                         Please refer to values starting from @link LayerTree::e_StateON @endlink and
   *                         this should be one of these values except @link LayerTree::e_StateUnchanged @endlink.
   */
  LayerPrintData(const String &subtype, LayerTree::UsageState print_state) {
    this->subtype = subtype;
    this->print_state = print_state;
  }

  /** @brief Constructor. */
  LayerPrintData()
      :print_state(LayerTree::e_StateUndefined) {
  }

  /**
   * @brief Constructor, with another layer print data object.
   *
   * @param[in] data  Another layer print data object.
   */
  LayerPrintData(const LayerPrintData& data) {
    subtype = data.subtype;
    print_state = data.print_state;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another layer print data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  LayerPrintData &operator = (const LayerPrintData& data) {
    subtype = data.subtype;
    print_state = data.print_state;
    return (*this);
  }
  /**
   * @brief Set value.
   *
   * @param[in] subtype      A string to specify the kind of content controlled by a layer.
   * @param[in] print_state  Layer usage state, indicating that the layer should be set to
   *                         that state when the document is printed from a viewer application.
   *                         Please refer to values starting from @link LayerTree::e_StateON @endlink and
   *                         this should be one of these values except @link LayerTree::e_StateUnchanged @endlink.
   *
   * @return None.
   */
  void Set(const String &subtype, LayerTree::UsageState print_state) {
    this->subtype = subtype;
    this->print_state = print_state;
  }

  /** @brief A string that specifies the kind of content controlled by a layer.*/
  String subtype;
  /**
   * @brief Layer usage state, indicating that the group should be set to
   *        that state when the document is printed from a viewer application.
   *
   * @details Please refer to values starting from @link LayerTree::e_StateON @endlink and this should be one of these values
   *          except @link LayerTree::e_StateUnchanged @endlink.
   */
  LayerTree::UsageState print_state;
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PDFLAYER_H_

