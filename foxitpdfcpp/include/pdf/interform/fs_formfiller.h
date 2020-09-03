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
 * @file fs_formfiller.h
 * @brief Header file for form filler related definitions and classes.
 */

#ifndef FS_FORMFILLER_H_
#define FS_FORMFILLER_H_

#include "common/fs_common.h"
#include "common/fs_render.h"
//#include "pdf/fs_pdfpage.h"
//#include "pdf/fs_pdfpage.h"

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
  class PDFPage;
/**
 * @brief Interform namespace.
 */
namespace interform {
// forward declaration
class Form;
class Control;

/**
 * This class represents a callback object to represent a timer.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class TimerCallback {
 public:
  /**
   * @brief A callback function used as a timer on every time interval.
   *
   * @param[in] timer  Identifier of a timer.
   *
   * @return None.
   */
  virtual void OnTimer(int timer) = 0;

 protected:
  ~TimerCallback() {}
};

/**
 * This class represents a callback object to assist form filler.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class FillerAssistCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief Get the version of derived implementation, for compatibility reason.
   *
   * @return Version of derived implementation.
   */
  virtual int GetVersion() {return 1;}

  /**
   * @brief A callback function used to refresh the specified area on a specified page.
   *
   * @param[in] page  A PDF page object.
   * @param[in] rect  A rectangle that specifies the area on the page to be redrawn.
   *                  <b>NULL</b> means to refresh the whole page.
   *
   * @return None.
   */
  virtual void Refresh(const PDFPage& page, const RectF* rect) = 0;

  /**
   * @brief A callback function used to set a system timer.
   *
   * @details This callback function is called to install a system timer. When a time-out value is specified,
   *          and every time when a time-out occurs, the system passes a message to the timer callback function.
   *
   * @param[in] elapse         Specifies the time-out value, in milliseconds.
   * @param[in] timer          A @link TimerCallback @endlink object as timer.
   * @param[out] out_timer_id  Output parameter that receives the timer identifier of the new timer if the function is
   *                           finished successfully. This value would be passed to callback function
   *                           @link FillerAssistCallback::KillTimer @endlink to kill the timer.
   *                           Nonzero if the function is successful; otherwise, this should be zero.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool SetTimerCallback(int elapse, TimerCallback* timer, int* out_timer_id) = 0;

  /**
   * @brief A callback function used to kill the timer event by timer identifier.
   *
   * @param[in] timer_id  The timer identifier returned by an earlier calling of
   *                      callback function @link FillerAssistCallback::SetTimerCallback @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool KillTimer(int timer_id) = 0;

  /**
   * @brief A callback function which is triggered when the focus is set to a form control.
   *
   * @details This callback function supports text field, combo box field, list box field, push button field,
   *          check box field, radio button field.
   *
   * @param[in] control  The form control object to which the focus is set.
   * @param[in] value    The value of form field associated with the control.
   *                     If the control belongs to a push button field, this value would always be an empty string.
   *
   * @return None.
   */
  virtual void FocusGotOnControl(const Control& control, const char* value) = 0;

  /**
   * @brief A callback function which is triggered when the focus is lost from a form control.
   *
   * @details This callback function supports text field, combo box field, list box field, push button field,
   *          check box field, radio button field.
   *
   * @param[in] control  The form control object, from which the focus is lost.
   * @param[in] value    The value of form field associated with the control.
   *                     If the control belongs to a push button field, this value would always be an empty string.
   *
   * @return None.
   */
  virtual void FocusLostFromControl(const Control& control, const char* value) = 0;

 protected:
  ~FillerAssistCallback() {}
};

/**
 * This class represents a form filler used for filling PDF form. There should be only one form filler object for
 * an interactive form, so do not construct form filler for one @link Form @endlink object
 * more than one time. User is recommended to implement an @link foxit::ActionCallback @endlink and set it to
 * Foxit PDF SDK by function @link common::Library::SetActionCallback @endlink, in order to implement more features of
 * form filler.
 *
 * @see @link common::Library @endlink
 */
class Filler FS_FINAL : public Base {
 public:
   /**
    * @brief Enumeration for virtual key code.
    *
    * @details Values of this enumeration should be used alone.
    */
   typedef enum _VirtualKeyCode {
     /** @brief An unknown key. */
     e_VkeyUnknown  = 0x00,
     /** @brief Backspace key. */
     e_VkeyBack = 0x08,
     /** @brief Tab key. */
     e_VkeyTab = 0x09,
     /** @brief Enter key. */
     e_VkeyReturn = 0x0D,
     /** @brief Shift key. */
     e_VkeyShift = 0x10,
     /** @brief Ctrl key. */
     e_VkeyControl = 0x11,
     /** @brief Menu key. */
     e_VkeyMenu = 0x12,
     /** @brief Pause Break key. */
     e_VkeyPause = 0x13,
     /** @brief ESC key. */
     e_VkeyEscape = 0x1B,
     /** @brief Space key. */
     e_VkeySpace = 0x20,
     /** @brief Page Up key. */
     e_VkeyPrior = 0x21,
     /** @brief Page Down key. */
     e_VkeyNext = 0x22,
     /** @brief End key. */
     e_VkeyEnd =   0x23,
     /** @brief Home key. */
     e_VkeyHome = 0x24,
     /** @brief Left arrow key. */
     e_VkeyLeft = 0x25,
     /** @brief Up arrow key. */
     e_VkeyUp =   0x26,
     /** @brief Right arrow key. */
     e_VkeyRight = 0x27,
     /** @brief Down arrow key. */
     e_VkeyDown = 0x28,
     /** @brief Print key. */
     e_VkeyPrint = 0x2A,
     /** @brief Print Screen key. */
     e_VkeySnapshot = 0x2C,
     /** @brief Insert key. */
     e_VkeyInsert = 0x2D,
     /** @brief Delete key. */
     e_VkeyDelete = 0x2E,
     /** @brief Help key. */
     e_VkeyHelp = 0x2F,
     /** @brief 0 key. */
     e_Vkey0 = 0x30,
     /** @brief 1 key. */
     e_Vkey1 = 0x31,
     /** @brief 2 key. */
     e_Vkey2 = 0x32,
     /** @brief 3 key. */
     e_Vkey3 = 0x33,
     /** @brief 4 key. */
     e_Vkey4 = 0x34,
     /** @brief 5 key. */
     e_Vkey5 = 0x35,
     /** @brief 6 key. */
     e_Vkey6 = 0x36,
     /** @brief 7 key. */
     e_Vkey7 = 0x37,
     /** @brief 8 key. */
     e_Vkey8 = 0x38,
     /** @brief 9 key. */
     e_Vkey9 = 0x39,
     /** @brief A key. */
     e_VkeyA = 0x41,
     /** @brief B key. */
     e_VkeyB = 0x42,
     /** @brief C key. */
     e_VkeyC = 0x43,
     /** @brief D key. */
     e_VkeyD = 0x44,
     /** @brief E key. */
     e_VkeyE = 0x45,
     /** @brief F key. */
     e_VkeyF = 0x46,
     /** @brief G key. */
     e_VkeyG = 0x47,
     /** @brief H key. */
     e_VkeyH = 0x48,
     /** @brief I key. */
     e_VkeyI = 0x49,
     /** @brief J key. */
     e_VkeyJ = 0x4A,
     /** @brief K key. */
     e_VkeyK = 0x4B,
     /** @brief L key. */
     e_VkeyL = 0x4C,
     /** @brief M key. */
     e_VkeyM = 0x4D,
     /** @brief N key. */
     e_VkeyN = 0x4E,
     /** @brief O key. */
     e_VkeyO = 0x4F,
     /** @brief P key. */
     e_VkeyP = 0x50,
     /** @brief Q key. */
     e_VkeyQ = 0x51,
     /** @brief R key. */
     e_VkeyR = 0x52,
     /** @brief S key. */
     e_VkeyS = 0x53,
     /** @brief T key. */
     e_VkeyT = 0x54,
     /** @brief U key. */
     e_VkeyU = 0x55,
     /** @brief V key. */
     e_VkeyV = 0x56,
     /** @brief W key. */
     e_VkeyW = 0x57,
     /** @brief X key. */
     e_VkeyX = 0x58,
     /** @brief Y key. */
     e_VkeyY = 0x59,
     /** @brief Z key. */
     e_VkeyZ = 0x5A,
     /** @brief 0 key in the numeric keypad. */
     e_VkeyNumpad0 = 0x60,
     /** @brief 1 key in the numeric keypad. */
     e_VkeyNumpad1 = 0x61,
     /** @brief 2 key in the numeric keypad. */
     e_VkeyNumpad2 = 0x62,
     /** @brief 3 key in the numeric keypad. */
     e_VkeyNumpad3 = 0x63,
     /** @brief 4 key in the numeric keypad. */
     e_VkeyNumpad4 = 0x64,
     /** @brief 5 key in the numeric keypad. */
     e_VkeyNumpad5 = 0x65,
     /** @brief 6 key in the numeric keypad. */
     e_VkeyNumpad6 = 0x66,
     /** @brief 7 key in the numeric keypad. */
     e_VkeyNumpad7 = 0x67,
     /** @brief 8 key in the numeric keypad. */
     e_VkeyNumpad8 = 0x68,
     /** @brief 9 key in the numeric keypad. */
     e_VkeyNumpad9 = 0x69,
     /** @brief Multiply key in the numeric keypad. */
     e_VkeyMultiply = 0x6A,
     /** @brief Plus key in the numeric keypad. */
     e_VkeyAdd = 0x6B,
     /** @brief Enter key in the numeric keypad. */
     e_VkeySeparator =  0x6C,
     /** @brief Minus key in the numeric keypad. */
     e_VkeySubtract =  0x6D,
     /** @brief Dot key in the numeric keypad. */
     e_VkeyDecimal = 0x6E,
     /** @brief Slash key in the numeric keypad. */
     e_VkeyDivide = 0x6F,
     /** @brief F1 key. */
     e_VkeyF1 = 0x70,
     /** @brief F2 key. */
     e_VkeyF2 = 0x71,
     /** @brief F3 key. */
     e_VkeyF3 = 0x72,
     /** @brief F4 key. */
     e_VkeyF4 = 0x73,
     /** @brief F5 key. */
     e_VkeyF5 = 0x74,
     /** @brief F6 key. */
     e_VkeyF6 = 0x75,
     /** @brief F7 key. */
     e_VkeyF7 = 0x76,
     /** @brief F8 key. */
     e_VkeyF8 = 0x77,
     /** @brief F9 key. */
     e_VkeyF9 = 0x78,
     /** @brief F10 key. */
     e_VkeyF10 = 0x79,
     /** @brief F11 key. */
     e_VkeyF11 = 0x7A,
     /** @brief F12 key. */
     e_VkeyF12 = 0x7B
   } VirtualKeyCode;
   
   /**
    * @brief Enumeration for key event flags.
    *
    * @details Values of this enumeration can be used alone or in combination.
    */
   typedef enum _EventFlags {
     /** @brief Event flag: "Shift" key. */
     e_EventFlagShiftKey =  0x0001,
     /** @brief Event flag: "Ctrl" key. */
     e_EventFlagControlKey  = 0x0002,
     /** @brief Event flag: "Alt" key. */
     e_EventFlagAltKey  = 0x0004,
     /** @brief Event flag: meta key. */
     e_EventFlagMetaKey = 0x0008,
     /** @brief Event flag: key pad. */
     e_EventFlagKeyPad = 0x0010,
     /** @brief Event flag: auto repeat. */
     e_EventFlagAutoRepeat = 0x0020,
     /** @brief Event flag: the left button of the mouse is down. */
     e_EventFlagLeftButtonDown = 0x0040,
     /** @brief Event flag: the middle button of the mouse is down. */
     e_EventFlagMiddleButtonDown = 0x0080,
     /** @brief Event flag: the right button of the mouse is down. */
     e_EventFlagRightButtonDown = 0x0100,
     /** @brief Event flag: the command key. */
     e_EventFlagCommand = 0x0200
   } EventFlags;
   

  /**
   * @brief Constructor.
   *
   * @details There can be only one form filler for a form.
   *
   * @param[in] form    A valid PDF form.
   * @param[in] assist  An assistant callback class for form filler. This should be implemented by user and should not
   *                    be <b>NULL</b>.
   */
  explicit Filler(const Form& form, FillerAssistCallback* assist);

  /** @brief Destructor. */
  ~Filler();

  /**
   * @brief Constructor, with another filler object.
   *
   * @param[in] other  Another filler object.
   */
  Filler(const Filler& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another filler object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Filler& operator = (const Filler& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another filler object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Filler& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another filler object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Filler& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Draw the currently focused form control on the page.
   *
   * @details If there is no focused form control on the page, nothing will be drawn by this function.
   *          The focused form control has to be the topmost visible element, so that it should be
   *          always rendered after page content and all the other annotations have been rendered.<br>
   *          For how to render form control (which is associated with widget annotations), please refer to
   *          the recommended flow mentioned in comment of class Renderer.
   *
   * @param[in] page      A valid PDF page object.
   * @param[in] matrix    The transformation matrix used for rendering, which is usually returned by function
   *                      @link PDFPage::GetDisplayMatrix @endlink.
   * @param[in] renderer  A valid renderer object for rendering.
   *
   * @return None.
   */
  void Render(const PDFPage& page, const Matrix& matrix,const common::Renderer& renderer);

  /**
   * @brief Call this function when left mouse button is down.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is down in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnLButtonDown(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief Call this function when left mouse button is up.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnLButtonUp(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief Call this function when left mouse button is double clicked.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnLButtonDoubleClick(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief Call this function when mouse moves.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnMouseMove(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when mouse enters somewhere.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>false</b>.
   */
  bool OnMouseEnter(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when mouse hovers somewhere.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>false</b>.
   */
  bool OnMouseHover(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when mouse leaves somewhere.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>false</b>.
   */
  bool OnMouseLeave(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when mouse wheel moves.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] delta  Indicates the amount the mouse wheel has been moved. A positive value means to be moved forward,
   *                   and a negative value means to be moved backward.
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>false</b>.
   */
  bool OnMouseWheel(const PDFPage& page, const PointF& point, int32 delta, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when right mouse button is down.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>false</b>.
   */
  bool OnRButtonDown(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when right mouse button is up.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>false</b>.
   */
  bool OnRButtonUp(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when right mouse button is double clicked.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>false</b>.
   */
  bool OnRButtonDoubleClick(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when right mouse wheel button is down.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>false</b>.
   */
  bool OnWheelButtonDown(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when right mouse wheel button is up.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>false</b>.
   */
  bool OnWheelButtonUp(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when mouse wheel button is double clicked.
   *
   * @param[in] page   A valid PDF page object.
   * @param[in] point  A point where left mouse button is up in the page, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags  Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>false</b>.
   */
  bool OnWheelButtonDoubleClick(const PDFPage& page, const PointF& point, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when key on the keyboard is down.
   *
   * @param[in] key_code  The key code. Please refer to values starting from @link Filler::e_VkeyUnknown @endlink and
   *                      this should be one of these values.
   * @param[in] flags     Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                      this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>true</b>.
   */
  bool OnKeyDown(uint32 key_code, uint32 flags);

  /**
   * @brief (Reserved, unsupported yet) Call this function when key on the keyboard is up.
   *
   * @param[in] key_code  The key code. Please refer to values starting from @link Filler::e_VkeyUnknown @endlink and
   *                      this should be one of these values.
   * @param[in] flags     Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                      this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   *         Currently this function does not support to be used yet, so this function will always return <b>true</b>.
   */
  bool OnKeyUp(uint32 key_code, uint32 flags);

  /**
   * @brief Call this function when a character code is about to be inputted to a form field.
   *
   * @param[in] char_code  A character code, in UTF16-LE encoding.
   * @param[in] flags      Event flags. Please refer to values starting from @link Filler::e_EventFlagShiftKey @endlink and
   *                       this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnChar(uint32 char_code, uint32 flags);

  /**
   * @brief Set focus on a form control.
   *
   * @param[in] control  A form control object. If this is constructed by default constructor and not set any value,
   *                     that means no focus control.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetFocus(const Control& control);

  /**
   * @brief Kill focus from form.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool KillFocus();

  /**
   * @brief Decide whether to highlight form fields or not.
   *
   * @details All types of form fields can be highlighted except push button fields.
   *          If this function is not called, Foxit PDF SDK will highlight all form fields by default.
   *
   * @param[in] is_highlight  <b>true</b> means to highlight form fields, and <b>false</b> means not to
   *                          highlight form fields.
   *
   * @return None.
   */
  void HighlightFormFields(bool is_highlight);

  /**
   * @brief Set the highlight color used for highlighting form fields.
   *
   * @details If this function is not called, Foxit PDF SDK will use a kind of light blue grey color (value 0x80C8D2FF)
   *          by default.
   *
   * @param[in] color  The highlight color to be set for highlighting form fields.
   *
   * @return None.
   */
  void SetHighlightColor(ARGB color);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Filler(FS_HANDLE handle =  NULL);
};
}  // namespace interform
}  // namespace pdf
}  // namespace foxit
#endif  // FS_FORMFILLER_H_

