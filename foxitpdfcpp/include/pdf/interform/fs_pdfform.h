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
 * @file fs_pdfform.h
 * @brief Header file for PDF form related definitions and classes.
 */

#ifndef FS_PDFFORM_H_
#define FS_PDFFORM_H_

#include "common/fs_common.h"
#include "fdf/fs_fdfdoc.h"
#include "pdf/interform/fs_formfiller.h"
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
class PDFDoc;
class PDFPage;
/**
 * @brief Interform namespace.
 */
namespace interform {
// forward declaration
class Control;
class Field;

/** This class represents an array of form fields. */
FSDK_DEFINE_ARRAY(FieldArray,Field)

/** This class represents the data of an option in list box or combo box. */
class ChoiceOption FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  ChoiceOption()
      : option_value(WString())
      , option_label(WString())
      , selected(false)
      , default_selected(false) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] option_value      The option string value.
   * @param[in] option_label      The displayed string value for the option.
   * @param[in] selected          <b>true </b> means the option is selected, and <b>false</b> means
   *                              the option is not selected.
   * @param[in] default_selected  <b>true </b> means the option would be selected by default, and <b>false</b> means
   *                              the option would not be selected by default.
   */
  ChoiceOption(const wchar_t* option_value, const wchar_t* option_label, bool selected, bool default_selected)
      : option_value(option_value)
      , option_label(option_label)
      , selected(selected)
      , default_selected(default_selected) {}

  /**
   * @brief Constructor, with another choice option object.
   *
   * @param[in] option  Another choice option object.
   */
  ChoiceOption(const ChoiceOption& option)
      : option_value(option.option_value)
      , option_label(option.option_label)
      , selected(option.selected)
      , default_selected(option.default_selected) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] option  Another choice option object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ChoiceOption& operator = (const ChoiceOption& option) {
    option_value = option.option_value;
    option_label = option.option_label;
    selected = option.selected;
    default_selected = option.default_selected;
    return *this;
  }

  /**
   * @brief Set value.
   *
   * @param[in] option_value      The option string value.
   * @param[in] option_label      The displayed string value for the option.
   * @param[in] selected          <b>true </b> means the option is selected, and <b>false</b> means
   *                              the option is not selected.
   * @param[in] default_selected  <b>true </b> means the option would be selected by default, and <b>false</b> means
   *                              the option would not be selected by default.
   *
   * @return None.
   */
  void Set(const wchar_t* option_value, const wchar_t* option_label, bool selected, bool default_selected) {
    this->option_value = option_value;
    this->option_label = option_label;
    this->selected = selected;
    this->default_selected = default_selected;
  }
  /** @brief The option string value. */
  WString option_value;

  /** @brief The displayed string value for the option. */
  WString option_label;

  /** @brief Used to indicate whether the option is selected or not. */
  bool selected;

  /** @brief Used to indicate whether the option would be selected by default or not. */
  bool default_selected;
};

/** This class represents an array of choice options. */
FSDK_DEFINE_ARRAY(ChoiceOptionArray, ChoiceOption)

/**
 * In a PDF document, form fields appear on any combination of pages and all of them make up a single,
 * global interactive form spanning the entire document. Function @link Form::GetField @endlink can use to
 * get a form field from interactive form. This class offers functions to get some information/properties of
 * a form field, reset the form field to its default value, and get form control from form field.<br>
 * When a form fiels's type is @link Field::e_TypeSignature @endlink,
 * the form field object is a signature object in fact.<br>
 * To access additional actions, please construct an @link actions::AdditionalAction @endlink object with Field object.
 *
 * @see @link Form @endlink
 * @see @link pdf::Signature @endlink
 * @see @link actions::AdditionalAction @endlink
 */
class Field : public Base {
 public:
  /**
   * @brief Enumeration for form field type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Type {
    /** @brief Form field type: unknown.*/
    e_TypeUnknown = 0,
    /** @brief Form field type: push button.*/
    e_TypePushButton = 1,
    /** @brief Form field type: check box.*/
    e_TypeCheckBox = 2,
    /** @brief Form field type: radio button.*/
    e_TypeRadioButton = 3,
    /** @brief Form field type: combo box.*/
    e_TypeComboBox = 4,
    /** @brief Form field type: list box.*/
    e_TypeListBox = 5,
    /** @brief Form field type: text field.*/
    e_TypeTextField = 6,
    /** @brief Form field type: signature field.*/
    e_TypeSignature = 7
  } Type;
  
  /**
   * @brief Enumeration for form field flags.
   *
   * @details Values of this enumeration can be used alone or in a combination.
   */
  typedef enum _Flags {
    /**
   @brief If set, the user may not change the value of the field. Any associated widget annotations will not
          interact with the user; that is, they will not respond to mouse clicks or change their appearance
          in response to mouse motions. This flag is useful for fields whose values are computed or imported
          from a database.
     */
    e_FlagReadOnly = 0x01,
    /** @brief If set, the field must have a value at the time it is exported by a submit-form action. */
    e_FlagRequired = 0x02,
    /** @brief if set, the field must not be exported by a submit-form action.*/
    e_FlagNoExport = 0x04,
    /**
   @brief (Only useful for radio button) If set, exactly one radio button must be selected at all times;
          clicking the currently selected button has no effect. If clear, clicking the selected button deselects it,
          leaving no button selected.
     */
    e_FlagButtonNoToggleToOff = 0x100,
    /**
   @brief (Only useful for radio button) If set, a group of radio buttons within a radio button field
          that use the same value for the on state will turn on and off in unison; that is if one is checked,
          they are all checked. If clear, the buttons are mutually exclusive.
     */
    e_FlagButtonRadiosInUnison = 0x200,
    /**
   @brief (Only useful for text field) If set, the text field can contain multiple lines of text;
          if clear, the field's text is restricted to a single line.
     */
    e_FlagTextMultiline = 0x100,
    /**
   @brief (Only useful for text field) If set, the field is intended for entering a secure password that should not
          be echoed visibly to the screen. Characters typed from the keyboard should instead be echoed
          in some unreadable form, such as asterisks or bullet characters.
   @note To protect password confidentiality, viewer applications should never store the value of the text field
         in the PDF file if this flag is set.
     */
    e_FlagTextPassword = 0x200,
    /**
   @brief (Only useful for text field) If set, the field does not scroll (horizontally for single-line fields,
          vertically for multiple-line fields) to accommodate more text than fits within its annotation rectangle.
          Once the field is full, no further text is accepted.
     */
    e_FlagTextDoNotScroll = 0x400,
    /**
   @brief (Only useful for text field) If set, use combs.
   @details If set, the field is automatically divided into as many equally spaced positions,
            or combs, as the value of maximum length of a field's text, and the text is laid out into those combs.
     */
    e_FlagTextComb = 0x800,
    /**
   @brief (Only useful for combo box) If set, the combo box includes an editable text control with a drop-down list,
          if clear, it includes only a drop-down list.
     */
    e_FlagComboEdit = 0x100,
    /**
   @brief (Only useful for combo box and list box) If set, more than one items may be selected simultaneously;
          if clear, no more than one item at a time may be selected.
     */
    e_FlagChoiceMultiSelect = 0x100
  } Flags;
  

  /**
   * @brief Constructor, from field dictionary.
   *
   * @param[in] document    A valid PDF document.
   * @param[in] field_dict  A PDF dictionary which represents a form field. It should belong to the PDF document
   *                        specified by parameter <i>document</i>;
   */
  Field(const PDFDoc& document, objects::PDFDictionary* field_dict);

  /**
   * @brief Constructor, with another form field object.
   *
   * @param[in] field  Another form field object.
   */
  Field(const Field& field);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another form field object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Field& operator = (const Field& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another form field object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Field& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another form field object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Field& other) const;

  /** @brief Destructor. */
  ~Field();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get field type.
   *
   * @return Form field type. Please refer to values starting from @link Field::e_TypeUnknown @endlink and
   *         this would be one of these values.
   */
  Type GetType() const;

  /**
   * @brief Get field flags.
   *
   * @details Field flags specifies various characteristics of a form field.
   *
   * @return Form field flags. Please refer to values starting from @link Field::e_FlagReadOnly @endlink and
   *         this would be one or a combination of these values.
   */
  uint32 GetFlags() const;

  /**
   * @brief Set field flags.
   *
   * @details Field flags specifies various characteristics of a form field.
   *
   * @param[in] flags  New form field flags. Please refer to values starting from @link Field::e_FlagReadOnly @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return None.
   */
  void SetFlags(uint32 flags);

  /**
   * @brief Get field name.
   *
   * @return Field name string.
   */
  WString GetName() const;

  /**
   * @brief Get default value.
   *
   * @details Applicable for all fields except push button.
   *          For field types that are not applicable, an empty string will be returned.
   *
   * @return Default value string.
   */
  WString GetDefaultValue() const;

  /**
   * @brief Set default value.
   *
   * @details Applicable for all fields except push button.
   *          For field types that are not applicable, this function will do nothing.
   *
   * @param[in] value  New default value string. It should not be an empty string.
   *
   * @return None.
   */
  void SetDefaultValue(const wchar_t* value);

  /**
   * @brief Get value.
   *
   * @details Applicable for all fields except push button.
   *          For field types that are not applicable, an empty string will be returned.
   *
   * @return Value string. Specially, when current field is a list box field with multiple values,
   *         only the first value would be returned.
   */
  WString GetValue() const;

  /**
   * @brief Set value.
   *
   * @details Applicable for all fields except push button. For field types that are not applicable,
   *          this function will do nothing.<br>
   *          Specially, for combo box and text field, when setting value successfully, this function will also
   *          trigger related calculation and formatting events and update the appearance of the field.
   *
   * @param[in] value  New value string. Specially, when current field is a list box field, this parameter can
   *                   contain multiple values:<br>
   *                   When to set multiple values, each value should be wrapped by "()". For example,
   *                   "(ABC)(CCC)" means to set 2 value "ABC" and "CCC".<br>
   *                   If a value contains "()", or "\" as its content, please add an additional "\" as
   *                   an escape character just in front of each character of "()" or "\". For example:
   *                   <ul>
   *                   <li>"ABC" means to set the value "ABC".</li>
   *                   <li>"(ABC)" means to set the value "ABC".</li>
   *                   <li>"(ABC" means to set the value "(ABC".</li>
   *                   <li>"(\\(ABC\\)\\(BBB\\)\\(CCC\\))" means to set the value "(ABC)(BBB)(CCC)".</li>
   *                   <li>"456\\\\" means to set the value "456\".</li>
   *                   <li>"(\\(ABC\\))" means to set the value "(ABC)".</li>
   *                   </ul>
   *
   * @return None.
   */
  void SetValue(const wchar_t* value);

  /**
   * @brief Get the alignment value
   *
   * @details Alignment is a property for variable text and it is only useful for text field and list box,
   *          which may contain variable text as their content.<br>
   *          If a text field or list box has its own alignment value, the document-wide default alignment value will
   *          be ignored; otherwise, the document-wide default alignment value will be used for the text field
   *          or list box.
   *
   * @return The alignment value. Please refer to values starting from @link common::e_AlignmentLeft @endlink and
   *         this would be one of these values.
   */
  common::Alignment GetAlignment() const;

  /**
   * @brief Set alignment property of a form, as a document-wide default value. (Not support signature field)
   *
   * @details Alignment is a property for variable text and it is only useful for text field and list box,
   *          which may contain variable text as their content.<br>
   *          If a text field or list box has its own alignment value, the document-wide default alignment value will
   *          be ignored; otherwise, the document-wide default alignment value will be used for the text field
   *          or list box.<br>
   *          If current form field is a signature field, this function will do nothing.
   *
   * @param[in] alignment  The new default alignment type of variable text. Please refer to values starting from
   *                       @link common::e_AlignmentLeft @endlink and this should be one of these values.<br>
   *                       If other values is used to set, @link common::e_AlignmentLeft @endlink will be used by default.
   *
   * @return None.
   */
  void SetAlignment(common::Alignment alignment);

  /**
   * @brief Get alternate name.
   *
   * @details An alternate field name to be used in place of the actual field name wherever the field must be
   *          identified in the user interface (such as in error or status messages referring to the field).
   *          This text is also useful when extracting the document's contents in support of accessibility to
   *          users with disabilities or for other purposes.
   *
   * @return The alternate name.
   */
  WString GetAlternateName() const;

  /**
   * @brief Set alternate name. (Not support signature field)
   *
   * @details An alternate field name is to be used in place of the actual field name wherever the field must be
   *          identified in the user interface (such as in error or status messages referring to the field).
   *          This text is also useful when extracting the document's contents in support of accessibility to
   *          users with disabilities or for other purposes.<br>
   *          If current form field is a signature field, this function will do nothing.
   *
   * @param[in] alternate_name  A new alternate name string. It should not be an empty string.
   *
   * @return None.
   */
  void SetAlternateName(const wchar_t* alternate_name);

  /**
   * @brief Get the default appearance data.
   *
   * @return The default appearance data.
   */
  DefaultAppearance GetDefaultAppearance() const;

  /**
   * @brief Set default appearance data.
   *
   * @param[in] default_ap  The new default appearance. <i>flags</i> of input data can be used to decide
   *                        which information is/are to be updated with the new data; for those no updated data,
   *                        they will keep to use old data.<br>
   *                        If <i>text_size</i> of input default appearance data is 0, that means the text size
   *                        should be calculated automatically.
   *
   * @return None.
   */
  void SetDefaultAppearance(const DefaultAppearance& default_ap);

  /**
   * @brief Get mapping name
   *
   * @details Mapping name is to be used when exporting interactive form field data from the document.
   *
   * @return The mapping name.
   */
  WString GetMappingName() const;

  /**
   * @brief Set mapping name. (Not support signature field)
   *
   * @details Mapping name is to be used when exporting interactive form field data from the document.
   *          If current form field is a signature field, this function will do nothing.
   *
   * @param[in] name  New mapping name string.It should not be an empty string.
   *
   * @return None.
   */
  void SetMappingName(const wchar_t* name);

  /**
   * @brief Get maximum length of the field's text, in characters.
   *
   * @details Applicable for text fields. For field types that are not applicable, this function will return 0.
   *
   * @return The maximum length of the field's text.
   */
  int GetMaxLength() const;

  /**
   * @brief Set maximum length of the field's text, in characters.
   *
   * @details Applicable for text fields. For field types that are not applicable, this function will do nothing.
   *
   * @param[in] max_length  New maximum length of the field's text. It should be non-negative.
   *
   * @return None.
   */
  void SetMaxLength(int max_length);

  /**
   * @brief Get options of list box or combo box.
   *
   * @details Applicable for list box and combo box. For field types that are not applicable,
   *          this function will return an empty array.
   *
   * @return An array that contains the options.
   */
  ChoiceOptionArray GetOptions() const;

  /**
   * @brief Set options of list box or combo box.
   *
   * @details Applicable for list box and combo box. For field types that are not applicable,
   *          this function will do nothing.
   *
   * @param[in] option_array  An array of options which is to be set to list box or combo box.
   *
   * @return None.
   */
  void SetOptions(const ChoiceOptionArray& option_array);

  /**
   * @brief Get top index of option for scrollable list boxes.
   *
   * @details Applicable for list box. For field types that are not applicable,
   *          this function will return 0.<br>
   *          Top index of option is the the index of the first option visible in the list.
   *
   * @return The index of first item which is in visible scope of list box.
   */
  int GetTopVisibleIndex();

  /**
   * @brief Set top index for scrollable list boxes.
   *
   * @details Applicable for list box. For field types that are not applicable,
   *          this function will do nothing.<br>
   *          Top index of option is the the index of the first option visible in the list.
   *
   * @param[in] index  The index of the first option visible in the list.
   *
   * @return None.
   */
  void SetTopVisibleIndex(int index);

  /**
   * @brief Get count of form controls.
   *
   * @return The count of the form controls.
   */
  int GetControlCount() const;

  /**
   * @brief Get a form control by index.
   *
   * @param[in] index  Form control index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Field::GetControlCount @endlink.
   *
   * @return A form control object.
   */
  Control GetControl(int index);

  /**
   * @brief Get count of form controls in a specified PDF page.
   *
   * @param[in] page  A valid PDF page object. It should be in the same document as current form field.
   *
   * @return The count of the form controls in the specified PDF page.
   */
  int GetControlCount(const foxit::pdf::PDFPage& page) const;

  /**
   * @brief Get a form control by index, in a specified PDF page.
   *
   * @param[in] page   A valid PDF page object. It should be in the same document as current form field.
   * @param[in] index  Form control index. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Field::GetControlCount @endlink with
   *                   same parameter <i>page</i>.
   *
   * @return form control object.
   */
  Control GetControl(const foxit::pdf::PDFPage& page, int index);

  /**
   * @brief Reset data in current field to its default value. (Not support signature field)
   *
   * @return <b>true</b> means success, while <b>false</b> means current form field is a signature field or failure.
   */
  bool Reset();

  /**
   * @brief Get the PDF dictionary of current object.
   *
   * @return The PDF dictionary of current object.
   */
  objects::PDFDictionary* GetDict() const;
  /**
   * @brief Get the PDF object of field's value.
   *
   * @details The format of field's value varies depending on the field type. For more details, please refer to
   *          "TABLE 8.69 Entries common to all field dictionaries" in <PDF reference 1.7> P676.
   *
   * @return A PDF object.
   */
  objects::PDFObject* GetValueObj() const;

  /**
   * @brief Get the PDF object of field's default value.
   *
   * @details The format of field's default value varies depending on the field type. For more details,
   *          please refer to "TABLE 8.69 Entries common to all field dictionaries" in <PDF reference 1.7> P676.
   *
   * @return A PDF object.
   */
  objects::PDFObject* GetDefaultValueObj() const;
  /**
   * @brief Get the PDF object for specified attribute which may be inherited from the ancestor node in the field tree.
   *
   * @details Some of the field attributes are designated as inheritable, such as "Ff", "V", "DV", and so on.
   *          Please refer to "TABLE 8.69 Entries common to all field dictionaries" in <PDF Reference 1.7> P675.
   *
   * @param[in] attribute_name  The name of attribute to be found.
   *
   * @return A PDF object. If not found, this function will return <b>NULL</b>.
   */
  objects::PDFObject* GetInheritedAttribute(const char* attribute_name) const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Field(FS_HANDLE handle =  NULL);
};

/**
 * An interactive form -- sometimes referred to as an AcroForm -- is a collection of fields for gathering information
 * interactively from the user. A PDF document may contain any number of fields appearing on any combination of pages,
 * all of which make up a single, global interactive form spanning the entire document. Arbitrary subsets of
 * these fields can be imported or exported from the document.<br>
 * Function @link pdf::PDFDoc::HasForm @endlink can be used to judge if a PDF document has interactive form.<br>
 * A form object can be constructed form a specified PDF document. This class offers functions to retrieve form fields
 * or form controls, import/export form data and other features. For example:
 * <ul>
 * <li>To retrieve form fields, please use functions @link Form::GetFieldCount @endlink and @link Form::GetField @endlink.</li>
 * <li>To retrieve form controls from a PDF page, please use functions @link Form::GetControlCount @endlink and
 *     @link Form::GetControl @endlink.</li>
 * <li>To import form data from an XML file, please use function @link Form::ImportFromXML @endlink;
 *     to export form data to an XML file, please use function @link Form::ExportToXML @endlink.</li>
 * <li>To retrieve form filler object, please use function @link Form::GetFormFiller @endlink.</li>
 * </ul>
 * To import form data from a FDF/XFDF file or export such data to a FDF/XFDF file, please refer to functions
 * @link pdf::PDFDoc::ImportFromFDF @endlink and @link pdf::PDFDoc::ExportToFDF @endlink.<br>
 * To fill the form, please construct a form filler object by current form object or retrieve the filler object by function
 * @link Form::GetFormFiller @endlink if such object has been constructed. (There should be only one form filler object for
 * an interactive form).
 *
 * @see @link pdf::PDFDoc @endlink
 * @see @link Filler @endlink
 */
class Form FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, with PDF document.
   *
   * @details If PDF document does not have AcroForm, this constructor will add an empty AcroForm to the PDF document
   *          in order that new fields can be added to the PDF document later.
   *
   * @param[in] document  A valid PDF document.
   */
  explicit Form(const pdf::PDFDoc& document);
  /**
   * @brief Constructor, with another form object.
   *
   * @param[in] other  Another form object.
   */
  Form(const Form& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another form object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Form& operator = (const Form& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another other object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Form& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another other object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Form& other) const;

  /** @brief Destructor. */
  ~Form();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the alignment value which is used as document-wide default value.
   *
   * @details Alignment is a property for variable text. It is only applicable for text field and list box,
   *          which may contain variable text as their content.<br>
   *          If a text field or list box has its own alignment value, the document-wide default alignment value
   *          will be ignored; otherwise, the document-wide default value will be used for the text field or list box.
   *
   * @return The alignment value. Please refer to values starting from @link common::e_AlignmentLeft @endlink and
   *         this would be one of these values.
   */
  common::Alignment GetAlignment() const;

  /**
   * @brief Set alignment value which is used as document-wide default value.
   *
   * @details Alignment is a property for variable text. It is only applicable for text field and list box,
   *          which may contain variable text as their content.<br>
   *          If a text field or list box has its own alignment value, the document-wide default alignment value
   *          will be ignored; otherwise, the document-wide default value will be used for the text field or list box.
   *
   * @param[in] alignment  The new default alignment type of variable text. Please refer to values starting from
   *                       @link common::e_AlignmentLeft @endlink and this should be one of these values.<br>
   *                       If other values is used to set, @link common::e_AlignmentLeft @endlink will be used by default.
   *
   * @return None.
   */
  void SetAlignment(common::Alignment alignment);

  /**
   * @brief Check whether to construct appearance when loading form controls.
   *
   * @return <b>true</b> means to construct appearances when loading form controls, while <b>false</b> means not.
   */
  bool NeedConstructAppearances() const;

  /**
   * @brief Set a flag that specifies whether to construct appearances when loading form controls.
   *
   * @param[in] need_construct  <b>true</b> means to construct appearances when loading form controls,
   *                            and <b>false</b> means not.
   *
   * @return None.
   */
  void SetConstructAppearances(bool need_construct);

  /**
   * @brief Get the form control at a specified position, in device coordination system.
   *
   * @param[in] page       A valid PDF page object. It should be in the same document as current form.
   * @param[in] point      A position, in device coordinate system.
   * @param[in] tolerance  Tolerance value. Valid range: 0.0f to 30.0f.
   * @param[in] type       The field type whose form control will be retrieved. Please refer to values starting from
   *                       @link Field::e_TypeUnknown @endlink and this should be one of these values.
   *                       @link Field::e_TypeUnknown @endlink means not to care about the field type
   *                       and just to retrieve the first form control at the specified position.
   * @param[in] matrix     A transformation matrix. Usually this is returned by function
   *                       @link pdf::PDFPage::GetDisplayMatrix @endlink. If this is <b>NULL</b>,
   *                       current function will have the same feature as function @link Form::GetControlAtPoint @endlink.
   *                       Default value: <b>NULL</b>.
   *
   * @return A form control object. If the return value of function @link Control::IsEmpty @endlink for
   *         the returned form control object is <b>true</b>, that means no suitable form control is around the specified position.
   */
  Control GetControlAtDevicePoint(const PDFPage& page, const PointF& point, float tolerance, Field::Type type,
                                  const Matrix* matrix = NULL);

  /**
   * @brief Get the form control at a specified position, in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @param[in] page       A valid PDF page object. It should be in the same document as current form.
   * @param[in] point      A position, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] tolerance  Tolerance value. Valid range: 0.0f to 30.0f.
   * @param[in] type       The field type whose form control will be retrieved. Please refer to values starting from
   *                       @link Field::e_TypeUnknown @endlink and this should be one of these values.
   *                       @link Field::e_TypeUnknown @endlink means not to care about the field type
   *                       and just to retrieve the first form control at the specified position.
   *
   * @return A form control object. If the return value of function @link Control::IsEmpty @endlink for
   *         the returned form control object is <b>true</b>, that means no suitable form control is around the specified position.
   */
  Control GetControlAtPoint(const PDFPage& page, const PointF& point, float tolerance, Field::Type type);

  /**
   * @brief Get the default appearance data.
   *
   * @return The default appearance data.
   */
  DefaultAppearance GetDefaultAppearance() const;

  /**
   * @brief Set default appearance data.
   *
   * @param[in] default_ap  The new default appearance. <i>flags</i> of input data can be used to decide
   *                        which information is/are to be updated with the new data; for those no updated data,
   *                        they will keep to use old data.<br>
   *                        If <i>text_size</i> of input default appearance data is 0, that means the text size
   *                        should be calculated automatically.
   *
   * @return None.
   */
  void SetDefaultAppearance(const DefaultAppearance& default_ap);

  /**
   * @brief Get the PDF document, with which current form object is associated.
   *
   * @return A PDF document object.
   */
  PDFDoc GetDocument() const;

  /**
   * @brief Get an array of form fields in calculation order.
   *
   * @details The calculation order defines the order in which the values of fields will be recalculated
   *          when value of any field is changed. Usually, these fields have calculation actions.
   *
   * @return An array of form field in calculation order.
   */
  FieldArray GetFieldsInCalculationOrder();

  /**
   * @brief Set an array of form fields in calculation order.
   *
   * @details The calculation order defines the order in which the values of fields will be recalculated
   *          when value of any field is changed. Usually, these fields have calculation actions.
   *
   * @param[in] field_array  An array of form fields to specify the new calculation order.
   *
   * @return None.
   */
  void SetFieldsInCalculationOrder(const FieldArray& field_array);

  /**
   * @brief Validate whether a field name can be used for a new field in specified field type.
   *
   * @details This method can be used to check whether a field name can be used for a new field
   *          in specified field type. User is recommended to call this function before using function
   *          @link Form::AddControl @endlink to add a new field with a new control.<br>
   *
   * @param[in] type            Field type, for which the input field name will be validated.
   * @param[in] field_name      A string value. It should not be an empty string.<br>
   *
   * @return  <b>true</b> means the input field name is valid for the specified field type, <b>false</b> means not.
   */
  bool ValidateFieldName(Field::Type type, const WString& field_name);

  /**
   * @brief Rename a field with a new name.
   *
   * @param[in] field           A valid form field object.
   * @param[in] new_field_name  A new field name. It should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool RenameField(Field& field, const wchar_t* new_field_name);

  /**
   * @brief Add a new form control to a specified form field. If the form field does not exist, this function will
   *        add a form field as well. (Not support signature field)
   *
   * @details Application can use this function to add a new form control:
   *          <ul>
   *          <li>If the specified form field exists, a new form control will be created and set to the field.</li>
   *          <li>If the specified form field does not exist, a new form field will be created according to
   *              parameter <i>field_name</i> and <i>field_type</i> and added to form, along with
   *              a newly created form control.</li>
   *          </ul>
   *          Whether a form field exists or not, it will be judged with input parameters <i>field_name</i> and
   *          <i>field_type</i>.<br>
   *          If user wants to add a new signature field, please use function @link pdf::PDFPage::AddSignature @endlink
   *          instead of current function.<br>
   *          The newly added form control has no appearance, so user should use setting methods in class Control
   *          or in related pdf field or widget annotation to set properties which will affect appearance.
   *          Some setting methods of class @link interform::Control @endlink and @link Field @endlink may
   *          directly update appearance, but function@link annots::Annot::ResetAppearanceStream @endlink of
   *          related widget annotation is still recommended to be called to ensure the appearance will
   *          indeed be updated.<br>
   *          For push button, check box, radio button, if user calls function
   *          @link annots::Annot::ResetAppearanceStream @endlink directly without setting any properties,
   *          the default appearance style will be used:
   *          <ul>
   *          <li>push button: In related widget annotation, background color (in the MK dictionary) = 0xC0C0C0,
   *              highlighting mode = @link annots::Annot::e_HighlightingPush @endlink.
   *          </li>
   *          <li>check box/radio button: In related widget annotation, border width = 1.0,
   *              border style = @link annots::BorderInfo::e_Solid @endlink,
   *              background color (in the MK dictionary) = 0xFFFFFF, border color (in the MK dictionary) = 0xFFFFFF.
   *          </li>
   *          </ul>
   *
   * @param[in] page        A valid PDF page, in which the new form control will be added. It should belong to
   *                        the same PDF document as current form.
   * @param[in] field_name  Field name. It should not be an empty string.
   * @param[in] field_type  Field type. Please refer to values starting from @link Field::e_TypePushButton @endlink and
   *                        this should be one of these values except @link Field::e_TypeSignature @endlink.
   *                        If this is @link Field::e_TypeSignature @endlink, this function will throw exception
   *                        @link foxit::e_ErrUnsupported @endlink.
   * @param[in] rect        Rectangle of the new form control which specifies the position in PDF page.
   *                        It should be in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @return The newly added form control object.
   */
  Control AddControl(const PDFPage& page, const wchar_t* field_name, Field::Type field_type, const RectF& rect);

  /**
   * @brief Move the control to a field specified by field name.
   *
   * @details Operation of current function for different cases: 
   *          <ul>
   *          <li>If the field specified by field name does not exist, a new field will be created with the field name and
   *              the control will be moved to this new field.</li>
   *          <li>If the field specified by field name exists and the field type is same as
   *              the field that control currently belongs to, the control will be combined into this field.</li>
   *          <li>If the field specified by field name exists but the field type is different from
   *              the field that control currently belongs to, this function will throw exception
   *              @link foxit::e_ErrConflict @endlink.</li>
   *          <li>If the field that control currently belongs to has only one control, this function will throw exception
   *              @link foxit::e_ErrUnsupported @endlink. In this case, please use
   *              function @link pdf::interform::Form::RenameField @endlink instead.</li>
   *          </ul>
   *
   * @param[in] control     A valid form control object.
   * @param[in] field_name  A field name. It should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool MoveControl(Control& control, const wchar_t* field_name);

  /**
   * @brief Remove a form field. (Not support signature field)
   *
   * @details If the form field appears on more than one PDF page, all representations will be removed.<br>
   *          If user wants to remove a signature field, please use function @link pdf::PDFDoc::RemoveSignature @endlink
   *          instead of current function.
   *
   * @param[in] field  A form field to be removed. If the field type is @link Field::e_TypeSignature @endlink,
   *                   this function will throw exception @link foxit::e_ErrUnsupported @endlink.
   *
   * @return None.
   */
  void RemoveField(Field& field);

  /**
   * @brief Remove a form control. (Not support to remove a form control from a signature field)
   *
   * @details If the specified form control is the only form control of related form field, the related form field will
   *          be removed as well.<br>
   *
   * @param[in] control  A form control to be removed. If the field type of related form field is
   *                     @link Field::e_TypeSignature @endlink, this function will throw exception @link foxit::e_ErrUnsupported @endlink.
   *
   * @return None.
   */
  void RemoveControl(Control& control);

  /**
   * @brief Get the count of form fields, whose names satisfy the specified name filter.
   *
   * @param[in] filter  A filter string. If this is an empty string, that means to
   *                    count all form fields; if this is valid, that means to count those form fields
   *                    whose names are partially matched parameter <i>filter</i>. For example,
   *                    if parameter <i>filter</i> is "text1", the filter will match text1.0, text1.2.0, etc;
   *                    but not match test10 or test11.1.<br>
   *                    Default value: an empty string.
   *
   * @return The count of the form fields with specified name filter.
   */
  int GetFieldCount(const wchar_t* filter = NULL) const;
          
  /**
   * @brief Get a form field by index, whose names satisfy the specified name filter.
   *
   * @param[in] index   Index of form field to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                    <i>count</i> is returned by function @link Form::GetFieldCount @endlink with
   *                    same parameter <i>filter</i>.
   * @param[in] filter  A filter string. If this is an empty string, that means to
   *                    count all form fields; if this is valid, that means to count those form fields
   *                    whose names are partially matched parameter <i>filter</i>. For example,
   *                    if parameter <i>filter</i> is "text1", the filter will match text1.0, text1.2.0, etc;
   *                    but not match test10 or test11.1.<br>
   *                    Default value: an empty string.
   *
   * @return A form field object.
   */
  Field GetField(int index, const wchar_t* filter = NULL);

  /**
   * @brief Get count of form controls in a specified PDF page.
   *
   * @param[in] page  A valid PDF page object. It should belong to the same PDF document as current form.
   *
   * @return The count of the form controls in the specified PDF page.
   */
  int GetControlCount(const PDFPage& page) const;

  /**
   * @brief Get a form control by index, in a specified PDF page.
   *
   * @param[in] page   A valid PDF page object. It should belong to the same PDF document as current form.
   * @param[in] index  Index of form control to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Field::GetControlCount @endlink with
   *                   same parameter <i>page</i>.
   *
   * @return A form control object.
   */
  Control GetControl(const PDFPage& page, int index);

#ifndef _FX_NO_JSE_
  /**
   * @brief Get the form filler.
   *
   * @return The filler object. If the return value of function @link Filler::IsEmpty @endlink for
   *         the returned filler object is <b>true</b>, that means form filler has not been constructed yet.
   *         For this case, please construct a filler with current form.
   */
  Filler GetFormFiller() const;
#endif

  /**
   * @brief Reset data of all fields (except signature fields) to their default value.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Reset();

  /**
   * @brief Export the form data to an XML file.
   *
   * @param[in] file_path  A full file_path of an XML file.
   *                       This specifies the XML file that form data will be exported to.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ExportToXML(const char* file_path);

  /**
   * @brief Import the form data from an XML file.
   *
   * @param[in] file_path  A full file_path of an existing XML file.
   *                       This specifies the XML file that form data will be imported from.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ImportFromXML(const char* file_path);

  /**
   * @brief Get the dictionary of current object.
   *
   * @return The dictionary of current object.
   */
  objects::PDFDictionary* GetDict() const;

  /**
   * @brief Fix the fields which are in a PDF page but cannot be counted by current form object.
   *
   * @details It may cost much time if there are many fields in the specified page.
   *
   * @param[in] page_index  The page index. Valid range: from 0 to (<i>count</i>-1).
   *                        <i>count</i> is returned by function @link PDFDoc::GetPageCount @endlink.
   *
   * @return None.
   */
  void FixPageFields(int page_index);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Form(FS_HANDLE handle =  NULL);
};

/**
 * Foxit PDF SDK defines "form control" to associate form field with its related widget annotations.
 * A form field may have one or more form controls, and each form control is associated with a widget annotation.
 * A form control object can be retrieved by following functions:
 * <ul>
 * <li>from a form, please use function @link Form::GetControl @endlink.</li>
 * <li>from a form field, please use functions @link Field::GetControl @endlink.</li>
 * </ul>
 * Form control also offers functions to get related form field object and widget annotation object. <br>
 * Function @link Form::AddControl @endlink can be used to add a new form control to a form field, and function
 * @link Form::RemoveControl @endlink can be used to remove a form control.
 *
 * @see @link Form @endlink
 * @see @link Field @endlink
 */
class Control FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, with another form control object.
   *
   * @param[in] other  Another form control object.
   */
  Control(const Control& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another form control object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Control& operator = (const Control& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another form control object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Control& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another form control object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Control& other) const;

  /** @brief Destructor. */
  ~Control();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the related form field.
   *
   * @return The related form field object.
   */
  Field GetField() const;

  /**
   * @brief Get the dictionary of related widget annotation.
   *
   * @return Dictionary of related widget annotation.
   */
  objects::PDFDictionary* GetWidgetDict() const;

  /**
  * @brief Get the related widget annotation.
  *
  * @return The related widget annotation.
  */
  annots::Widget GetWidget() const;

  /**
   * @brief Get the index of current form control among all the controls of related form field.
   *
   * @return The index of the form control.
   */
  int GetIndex() const;

  /**
   * @brief Get export mapping name when related form field is check box or radio button.
   *
   * @details Applicable for check box and radio button as related form field.
   *          If related form field is other field type, this function will return an empty string.
   *
   * @return The export mapping name.
   */
  WString GetExportValue() const;

  /**
   * @brief Set export mapping name when related form field is check box or radio button.
   *
   * @details Applicable for check box and radio button as related form field.
   *          If related form field is other field type, this function will do nothing.
   *
   * @param[in] value  The new export mapping name. It should not be an empty string.
   *
   * @return None.
   */
  void SetExportValue(const wchar_t* value);

  /**
   * @brief Check if the current form control is checked when related form field is check box or radio button.
   *
   * @details Applicable for check box and radio button as related form field.
   *          If related form field is other field type, this function will return <b>false</b>.
   *
   * @return <b>true</b> means checked, and <b>false</b> means not checked.
   */
  bool IsChecked() const;

  /**
   * @brief Set the check state of current form control when related form field is check box or radio button.
   *
   * @details Applicable for check box and radio button as related form field.
   *          If related form field is other field type, this function will do nothing.
   *
   * @param[in] checked_status  <b>true</b> means checked, and <b>false</b> means not checked.
   *
   * @return None.
   */
  void SetChecked(bool checked_status);

  /**
   * @brief Check if the current form control is checked by default when related form field is check box or
   *        radio button.
   *
   * @details Applicable for check box and radio button as related form field.
   *          If related form field is other field type, this function will return <b>false</b>.
   *
   * @return <b>true</b> means checked by default, and <b>false</b> means not checked by default.
   */
  bool IsDefaultChecked() const;

  /**
   * @brief Set the default check state of current form control when related form field is check box or radio button.
   *
   * @details Applicable for check box and radio button as related form field.
   *          If related form field is other field type, this function will do nothing.
   *
   * @param[in] checked_status  <b>true</b> means checked by default, and <b>false</b> means not checked by default.
   *
   * @return None.
   */
  void SetDefaultChecked(bool checked_status);

  /**
   * @brief Get the default appearance data.
   *
   * @return The default appearance data.
   */
  DefaultAppearance GetDefaultAppearance() const;

  /**
   * @brief Set default appearance data.
   *
   * @param[in] default_ap  The new default appearance. <i>flags</i> of input data can be used to decide
   *                        which information is/are to be updated with the new data; for those no updated data,
   *                        they will keep to use old data.<br>
   *                        If <i>text_size</i> of input default appearance data is 0, that means the text size
   *                        should be calculated automatically.
   *
   * @return None.
   */
  void SetDefaultAppearance(const DefaultAppearance& default_ap);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Control(FS_HANDLE handle =  NULL);

};
}  // namespace interform
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PDFFORM_H_

