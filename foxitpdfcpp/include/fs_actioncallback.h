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
 * @file fs_actioncallback.h
 * @brief Header file for action callback related definitions and classes.
 */

#ifndef FS_ACTIONCALLBACK_H_
#define FS_ACTIONCALLBACK_H_

#include "common/fs_common.h"
/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/** This class represents menu list. */
class MenuList FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  MenuList() : level(0) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] level  Level of menu.
   * @param[in] name   Title of menu.
   */
  MenuList(int level, const wchar_t* name) {
    this->level = level;
    if (name)
      this->name = name;
  }

  /**
   * @brief Constructor, with another menu list object.
   *
   * @param[in] menu_list  Another menu list object.
   */
  MenuList(const MenuList& menu_list) {
    level = menu_list.level;
    name = menu_list.name;
  }

  /**
   * @brief Set values.
   *
   * @param[in] level  Level of menu.
   * @param[in] name   Title of menu.
   *
   * @return None.
   */
  void Set(int level, const wchar_t* name) {
    this->level = level;
    if (name)
      this->name = name;
  }

  /** @brief The level of menu. */
  int level;
  /** @brief The title of menu. */
  WString name;
};

/** This class represents an array of menu list objects. */
FSDK_DEFINE_ARRAY(MenuListArray, MenuList)

/**
 * This class represents identity properties of current user, and is used for callback function
 * @link ActionCallback::GetIdentityProperties @endlink.
 */
class IdentityProperties FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  IdentityProperties() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] corporation  The corporation name.
   * @param[in] email        The email address.
   * @param[in] login_name   The login name. Usually, this is the name used to log in current operating system.
   * @param[in] name         The user name.
   */
  IdentityProperties(const wchar_t* corporation, const wchar_t* email, const wchar_t* login_name, const wchar_t* name)
      : corporation(corporation)
      , email(email)
      , login_name(login_name)
      , name(name) {}

  /**
   * @brief Constructor, with another identity properties object.
   *
   * @param[in] id_properities  Another identity properties object.
   */
  IdentityProperties(const IdentityProperties& id_properities)
      : corporation(id_properities.corporation)
      , email(id_properities.email)
      , login_name(id_properities.login_name)
      , name(id_properities.name) {}

  /**
   * @brief Set values.
   *
   * @param[in] corporation  The corporation name.
   * @param[in] email        The email address.
   * @param[in] login_name   The login name. Usually, this is the name used to log in current operating system.
   * @param[in] name         The user name.
   *
   * @return None.
   */
  void Set(const wchar_t* corporation, const wchar_t* email, const wchar_t* login_name, const wchar_t* name) {
    this->corporation = corporation;
    this->email = email;
    this->login_name = login_name;
    this->name = name;
  }

  /** @brief The corporation name. */
  WString corporation;
  /** @brief The email address. */
  WString email;
  /** @brief The login name. Usually, this is the name used to log in current operating system. */
  WString login_name;
  /** @brief The user name. */
  WString name;
};

/**
 * This class represents a callback object for performing PDF actions.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user,
 * to perform PDF actions, such as javascript actions.
 */
class ActionCallback {
 public:
  /**
   * @brief Enumeration for language.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Language {
    /** @brief Unknown language. */
    e_LanguageUnknown = 0,
    /** @brief Chinese Simplified. */
    e_LanguageCHS = 1,
    /** @brief Chinese Traditional. */
    e_LanguageCHT = 2,
    /** @brief Danish. */
    e_LanguageDAN = 3,
    /** @brief German. */
    e_LanguageDEU = 4,
    /** @brief English. */
    e_LanguageENU = 5,
    /** @brief Spanish. */
    e_LanguageESP = 6,
    /** @brief French. */
    e_LanguageFRA = 7,
    /** @brief Italian. */
    e_LanguageITA = 8,
    /** @brief Korean. */
    e_LanguageKOR = 9,
    /** @brief Japanese. */
    e_LanguageJPN = 10,
    /** @brief Dutch. */
    e_LanguageNLD = 11,
    /** @brief Norwegian. */
    e_LanguageNOR = 12,
    /** @brief Brazilian Portuguese. */
    e_LanguagePTB = 13,
    /** @brief Finnish. */
    e_LanguageSUO = 14,
    /** @brief Swedish. */
    e_LanguageSVE = 15
  } Language;
  
  /**
   * @brief Enumeration for application's information type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _AppInfoType {
    /** @brief Application's forms version information. */
    e_AppInfoTypeFormsVersion = 0x0,
    /** @brief Application's viewer type information. */
    e_AppInfoTypeViewerType = 0x01,
    /** @brief Application's viewer variation information. */
    e_AppInfoTypeViewerVariation = 0x02,
    /** @brief Application's viewer version information. */
    e_AppInfoTypeViewerVersion = 0x03,
    /** @brief Application's app version information. */
    e_AppInfoTypeAppVersion = 0x04
  } AppInfoType;
  
  /**
   * @brief Enumeration for data type to be mailed.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MailType {
    /** @brief Mailed data type: document. */
    e_MailTypeDoc = 0,
    /** @brief Mailed data type: form. */
    e_MailTypeForm = 1,
    /** @brief Mailed data type: string message. */
    e_MailTypeMsg = 2
  } MailType;
  

  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function to invalidate the client area within the specified rectangle.
   *
   * @details All positions are measured in PDF "user space". Implementation should call function
   *          @link common::Renderer::StartRender @endlink for repainting a specified page area.
   *
   * @param[in] document    A PDF document object. It would be valid.
   * @param[in] page_index  A page index. It would start from 0 and less than page count of the specified document.
   * @param[in] pdf_rect    A rectangle that specifies the page area in [PDF coordinate system] (@ref pdf::PDFPage).
   *                        If this is an empty rectangle, that means to refresh the whole page.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool InvalidateRect(const pdf::PDFDoc& document, int page_index, const RectF& pdf_rect) = 0;

  /**
   * @brief A callback function used to receive current page index.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document  A PDF document object. It would be valid.
   *
   * @return Current page index. The value should be stared from 0 and less than page count of the specified document.
   */
  virtual int GetCurrentPage(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function used to set the current page by index.
   *
   * @details This callback function is optional, so it can be implemented to do nothing.
   *
   * @param[in] document    A PDF document object. It would be valid.
   * @param[in] page_index  A page index which is used to change current page.
   *                        The index would start from 0 and less than page count of the specified document.
   *
   * @return None.
   */
  virtual void SetCurrentPage(const pdf::PDFDoc& document, int page_index) = 0;

  /**
   * @brief A callback function used to receive current displaying rotation of a page on PDF viewer.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document    A PDF document object. It would be valid.
   * @param[in] page_index  A page index, used to specify which page's rotation is to be retrieved.
   *                        The index would start from 0 and less than page count of the specified document.
   *
   * @return The rotation of specified page. Please refer to values starting from @link common::e_Rotation0 @endlink
   *         and this should be one of these values.
   */
  virtual common::Rotation GetPageRotation(const pdf::PDFDoc& document, int page_index) = 0;

  /**
   * @brief A callback function used to set the rotation value of a page on PDF viewer.
   *
   * @details This callback function is optional, so it can be implemented to do nothing.
   *
   * @param[in] document    A PDF document object. It would be valid.
   * @param[in] page_index  A page index, used to specify which page's rotation is to be changed.
   *                        The index would start from 0 and less than page count of the specified document.
   * @param[in] rotation    New rotation value. Please refer to values starting from @link common::e_Rotation0 @endlink
   *                        and this should be one of these values except @link common::e_RotationUnknown @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool SetPageRotation(const pdf::PDFDoc& document, int page_index, common::Rotation rotation) = 0;

  /**
   * @brief A callback function to execute a named action.
   *
   * @details Please refer to description of "Named Actions" in Section 8.5.3 of <PDF Reference 1.7> for more details.
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document      A PDF document object. It would be valid.
   * @param[in] named_action  A string to specify a named action.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool ExecuteNamedAction(const pdf::PDFDoc& document, const char* named_action) = 0;

  /**
   * @brief A callback function to set the change mark which indicates whether the content of document is
   *        changed or not.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document     A PDF document object. It would be valid.
   * @param[in] change_mark  A boolean value that indicates whether the content of document is changed or not.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool SetDocChangeMark(const pdf::PDFDoc& document, bool change_mark) = 0;

  /**
   * @brief A callback function to receive the change mark which indicates whether the content of document is
   *        changed or not.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document  A PDF document object. It would be valid.
   *
   * @return <b>true</b> means the PDF document is changed, while <b>false</b> means not.
  */
  virtual bool GetDocChangeMark(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function to receive the count of opened documents.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return The count of opened documents.
   */
  virtual int GetOpenedDocCount() = 0;

  /**
   * @brief A callback function to receive an opened PDF document object by index.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] index  The index of an opened PDF documents. Valid range: from 0 to <i>count</i>-1.
   *                   <i>countt</i> is returned by callback function @link ActionCallback::GetOpenedDocCount @endlink;
   *
   * @return A opened PDF document object.
   */
  virtual pdf::PDFDoc GetOpenedDoc(int index) = 0;

  /**
   * @brief A callback function to cause the system to play a sound.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] type    Sound type. The value would be on of following values:<br>
   *                    <ul>
   *                    <li>0: Error</li>
   *                    <li>1: Warning</li>
   *                    <li>2: Question</li>
   *                    <li>3: Status</li>
   *                    <li>4: Default (default value)</li>
   *                    </ul>
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool Beep(int type) = 0;

  /**
   * @brief A callback function to display a dialog box containing a question and an entry field for the user to
   *        reply to the question.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] question       A string that specifies the question to be posed to the user.
   * @param[in] title          A string that specifies the title of the dialog box.
   * @param[in] default_value  A string that specifies a default value as the answer to the question.
   *                           If the answer is not specified, no default value is presented.
   * @param[in] label          A string that specifies a short string to appear in front of the edit text field.
   * @param[in] is_password    A boolean value that indicates whether user's response should be masked to show:<br>
   *                           <b>true</b> means that the user's response should show as asterisks (*) or bullets (?)
   *                           to mask the response, which might be sensitive information. <br>
   *                           Default: <b>false</b>.
   *
   * @return User's response. It can be an empty string.
   */
  virtual WString Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_value,
                                const wchar_t* label, bool is_password) = 0;

  /**
   * @brief A callback function to get the file path of current PDF document.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document  A PDF document object. It would be valid.
   *
   * @return The file path.
   */
  virtual WString GetFilePath(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function to print pages within a specified index range.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document             A PDF document object. It would be valid.
   * @param[in] is_ui                <b>true</b> means that a UI should be presented to the user
   *                                 to obtain printing information and confirm the action.
   * @param[in] page_range           A range object to specify the page range for printing.
   *                                 All the indexes represented in this range would start from 0 and
   *                                 less than page count of the specified document.
   * @param[in] is_silent            <b>true</b> means that the cancel dialog box should be suppressed
   *                                 while the document is printing.
   * @param[in] is_shrunk_to_fit     <b>true</b> means that the page should be shrunk (if necessary)
   *                                 to fit within the area of the printed page.
   * @param[in] is_printed_as_image  <b>true</b> means that pages should be printed as image.
   * @param[in] is_reversed          <b>true</b> means that the printing order should be from parameter <i>end</i> to
   *                                 parameter <i>start</i>.
   * @param[in] is_to_print_annots   <b>true</b> means that annotations should be printed with page.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool Print(const pdf::PDFDoc& document, bool is_ui,
                     const common::Range& page_range, bool is_silent ,
                     bool is_shrunk_to_fit, bool is_printed_as_image,
                     bool is_reversed, bool is_to_print_annots) = 0;

  /**
   * @brief A callback function to submit the form data to a specified url.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document   A PDF document object. It would be valid.
   * @param[in] form_data  A form data buffer which is to be submit.
   * @param[in] length     The size (in bytes) of the buffer parameter<i>form_data</i>.
   * @param[in] url        A url, to which the form data will be submit.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool SubmitForm(const pdf::PDFDoc& document, void* form_data, uint32 length, const char* url) = 0;

  /**
   * @brief A callback function to launch to a specified url.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] url  A url.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool LaunchURL(const char* url) = 0;

  /**
   * @brief A callback function to show a file selection dialog, and the selected file path should be returned.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return The file path. It can be an empty string.
   */
  virtual WString BrowseFile() = 0;

  /**
   * @brief A callback function to get the language of the running viewer application.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return The language type. Please refer to values starting from @link ActionCallback::e_LanguageUnknown @endlink
   *         and this should be one of these values.
   */
  virtual Language GetLanguage() = 0;

  /**
   * @brief A callback function used to pop up a dialog to show warnings or hints.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] msg    The message string to be displayed in the dialog.
   * @param[in] title  The title of the dialog.
   * @param[in] type   Type of button group. It would be one of following values:
   *                   <ul>
   *                   <li>0: OK;(default value.)</li>
   *                   <li>1: OK, Cancel;</li>
   *                   <li>2: Yes, NO; </li>
   *                   <li>3: Yes, NO, Cancel.</li>
   *                   </ul>
   * @param[in] icon   Icon type. It would be one of following values:
   *                   <ul>
   *                   <li>0: Error;(default value.)</li>
   *                   <li>1: Warning;</li>
   *                   <li>2: Question;</li>
   *                   <li>3: Status.</li>
   *                   </ul>
   *
   * @return The return value should be one of following values:<br>
   *         <ul>
   *         <li>1: OK;</li>
   *         <li>2: Cancel; </li>
   *         <li>3: NO;</li>
   *         <li>4: Yes;</li>
   *         </ul>
   */
  virtual int Alert(const wchar_t* msg, const wchar_t* title, int type, int icon) = 0;

  /**
   * @brief A callback function used to get identity properties of current user.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return An identity properties object that specifies the identity properties of current user.
   */
  virtual IdentityProperties GetIdentityProperties() = 0;

  /**
   * @brief A callback function to pop up a menu window.
   *
   * @details The position of menu window is same as cursor's.
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] menus  An array of menu list objects.
   *
   * @return The name of the menu item that was selected.
   */
  virtual WString PopupMenu(const MenuListArray& menus) = 0;

  /**
   * @brief A callback function to get application information.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.<br>
   *          For the digital information like
   *          @link ActionCallback::e_AppInfoTypeViewerVersion @endlink, @link ActionCallback::e_AppInfoTypeAppVersion @endlink
   *          and @link ActionCallback::e_AppInfoTypeFormsVersion @endlink, please use string to represent it.
   *
   * @param[in] type  Type of information. Please refer to values starting from 
   *                  @link ActionCallback::e_AppInfoTypeFormsVersion @endlink and this would be one of these values.
   *
   * @return The application information.
   */
  virtual WString GetAppInfo(AppInfoType type) = 0;

  /**
   * @brief A callback function to mail data or message, with or without user interaction.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] data       A data which is to be mailed.
   *                       The value and type of the data depends on parameter <i>data_type</i>:
   *                       <ul>
   *                       <li>This should be <b>NULL</b> when parameter <i>data_type</i> is
   *                           @link ActionCallback::e_MailTypeMsg @endlink.</li>
   *                       <li>This should represents a WString object when parameter <i>data_type</i> is
   *                           @link ActionCallback::e_MailTypeForm @endlink.</li>
   *                       <li>This should represents a @link pdf::PDFDoc @endlink object when parameter <i>data_type</i> is
   *                           @link ActionCallback::e_MailTypeDoc @endlink.</li>
   *                       </ul>
   * @param[in] data_type  Mail type. Please refer to values starting from @link ActionCallback::e_MailTypeDoc @endlink
   *                       and this would be one of these values.
   * @param[in] is_ui      <b>true</b> means that the remaining parameters are used to
   *                       seed the compose-new-message window which is displayed to the user.<br>
   *                       <b>false</b> means that the parameter <i>to</i> is required and all other parameters
   *                       are optional.
   * @param[in] to         A string that specifies a semicolon-delimited list of recipients for the message.
   * @param[in] subject    A string that specifies the subject of the message.
   *                       The limit of this string's length is 64 KB.
   * @param[in] cc         A string that specifies a semicolon-delimited list of CC recipients for the message.
   * @param[in] bcc        A string that specifies a semicolon-delimited list of BCC recipients for the message.
   * @param[in] message    A string that specifies the content of the message.
   *                       The limit of this string's length is 64 KB.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool MailData(void* data, MailType data_type, bool is_ui, const wchar_t* to,
                        const wchar_t* subject, const wchar_t* cc, const wchar_t* bcc, const wchar_t* message) = 0;

  /**
   * @brief A callback function to verify specified signature..
   *
   * @details This callback function will be triggered when a signature is to be verified by an action.
   *          If user does not want to verify the signature, just implement this function to do nothing and
   *          just return @link pdf::Signature::e_StateUnknown @endlink.
   *          User is recommended to use class @link pdf::LTVVerifier @endlink to verify if a signed signature is valid or not.
   *
   * @param[in] document       A PDF document object. It would be valid.
   * @param[in] pdf_signature  A PDF signature which is signed. This signature belongs to input paramter <i>document</i>.
   *
   * @return The signature verified state. Please refer to values starting from @link pdf::Signature::e_StateUnknown @endlink and
   *         this would be one or combination of them.
   */
  virtual uint32 VerifySignature(const pdf::PDFDoc& document, const pdf::Signature& pdf_signature) = 0;

 protected:
  ~ActionCallback() {}
};
}  // namespace foxit

#endif  // FS_ACTIONCALLBACK_H_

