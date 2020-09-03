// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to add form field and
// get form field information.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/interform/fs_pdfform.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace annots;
using namespace actions;
using namespace interform;

static const char* sn = "eUcaj+XFRdwDeV4fx2eGZzF7ZmQiBNInjxfWhiHCIinKYg3KsYgcKg==";
static const char* key = "8f0YFcONvRsJ+nePmKBLSM8bw7bGx79neQeRmlgo13uto3HGtEFz4BLMd5BErJbDU1Nll8omHE6H+Vx20kaMiDQYMDldaA9ctpwcoLODu8yfFtHTm2UseIiHVjqu52IRK18VKf4pLWI6ekSbkAafVjd3XxT8Gv6TtRASa2U4/v/xFR99REZVOqq8tPSQT5b521y1tTBJaTKxB23KwsVuONGlSM8ZH0PiPkjuRmZsfp9aVqpWVSfBMZFqw4+XYbQdImYgzqkq/vgaZ7ApxW0ICzjtIiJ0x/15o+rOFQhMh6+9kSGq4OhjfzY8ZRqTyFQ2dy2SRF+tQKD87bTJUrDkf9mRXbvK+xpDrPpT7dMgTj0R6yjrwJpRt6LcimMv+LvSjbKvAG6KFxn6UMfWVi8bkFM/hzvwRJe/aoyPbYQ72lFMHeYreJNaAKYpO8CBF9mi5KbDDXYNtaoEgUVVukppYbS/wVpdQwlC7J85A9yLmelDEufSbz/RVOwv2LZKHsk6iFgaV4U74YrYiwIT4xE8znliw4xnOd6j+MCBdcmMvOyGKUeNrD7Q042c6Pn5QPGchkmmPuhqwrcnRXYiYEOyMs4LnsdhKSxJk4Q2yoc9b6Fhb8RQbUARzbTfAw9L/ZgooZ2tVhFFJnCFhkU4U76twoB1plg3L2KEAH4smtZjVh0k8uoaDt9JQOk/K5YaKiAI3TPB6AlsaDLguQClqyRsK04OyO/CZkoPsvLoGa1EyBpppKcwOe3PyF4zYuNEQRRZh48L/5loWJPf+ynWj1fR+NcVnTqe8GqFk0vP3uK5C8FaJxKP3a0bekr0tKCfe4yxte4Ej8yo/3plnDz03GXUB+FgsdMINm3rA2UhTNdYjRJtIRNJomCkjQr7GHyEsTq71Q6O0wuOSet0byPcLPPhcXzsSqpWYZ9+opORXE92LCwuHJRZOtuzpjvAphi0kiCRk4dSR0VP8FmL5yNG2M2okeEb8bjXD52ErTBTIAk3VZnh4OOCSfzgpZhoEvr5usjkfyry9BmgX2gWAJYRTUrEgDTXHj5YQ6MT3grfDGYMqKoy7GSpb3tY5zBHzzoJDK/E1VvO+ScyQaJQJ0eHgsgy2QZbCnEB3W4N5M8HqBqNMw+0oUvqw0P1i4uK9XwCGzVyyOXs1czCsWGg8R8Ej51AL+9gXdu7RMdEaP2lTMkOJfScJbzsOkfjxvX5LBrHVZ98XuzZylbeFkVr/gjrvBnfucL9zCmjngYq4RfzDYBOzx31gRuFFAsllK4zFRgtHWSXGXwXim4OJpMVKEuFHO5Oupowvd9cdzRIjGpWzR0=";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/");
#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/");
#endif

class SdkLibMgr {
public:
  SdkLibMgr() : is_initialize_(false){};
  ErrorCode Initialize() {
    ErrorCode error_code = Library::Initialize(sn, key);
    if (error_code != foxit::e_ErrSuccess) {
      printf("Library Initialize Error: %d\n", error_code);
    } else {
      is_initialize_ = true;
    }
    return error_code;

  }
  ~SdkLibMgr(){
    if(is_initialize_)
      Library::Release();
  }
private:
  bool is_initialize_;
};

void AddInteractiveForms(PDFPage & page,interform::Form &form)
{
  {
    // Add push button field.
    Control btn_submit = form.AddControl(page, L"Push Button Submit", Field::e_TypePushButton, RectF(50, 750, 150, 780));

    // Set default appearance
    foxit::pdf::DefaultAppearance default_ap;
    default_ap.flags = DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor;
    default_ap.font = Font(Font::e_StdIDHelveticaB);
    default_ap.text_size = 12.0f;
    default_ap.text_color = 0x000000;
    form.SetDefaultAppearance(default_ap);

    // Set push button appearance.
    Widget widget = btn_submit.GetWidget();
    widget.SetHighlightingMode(foxit::pdf::annots::Annot::e_HighlightingPush);
    widget.SetMKBorderColor(0xFF0000);
    widget.SetMKBackgroundColor(0xF0F0F0);
    widget.SetMKNormalCaption(L"Submit");
    widget.ResetAppearanceStream();

    // Set submit form action.
    actions::SubmitFormAction submit_action = (actions::SubmitFormAction)Action::Create(form.GetDocument(), Action::e_TypeSubmitForm);
    int count = form.GetFieldCount(NULL);
    WStringArray name_array;
    for (int i = 0; i < count; i++) {
      name_array.Add(form.GetField(i,NULL).GetName());
    }

    submit_action.SetFieldNames(name_array);
    submit_action.SetURL("http://www.foxitsoftware.com");
    widget.SetAction(submit_action);
    cout << "Add button field." << endl;
  }
  {
    // Add radio button group
    Control control = form.AddControl(page, L"Radio Button0", Field::e_TypeRadioButton, RectF(50.0, 700, 90, 740));
    Control control1 = form.AddControl(page, L"Radio Button0", Field::e_TypeRadioButton, RectF(100.0, 700, 140, 740));
    control.SetExportValue(L"YES");
    control.SetChecked(true);
    // Update radio button's appearance.
    control.GetWidget().ResetAppearanceStream();

    control1.SetExportValue(L"NO");
    control1.SetChecked(false);
    // Update radio button's appearance.
    control1.GetWidget().ResetAppearanceStream();

    cout << "Add radio button." << endl;
  }
  {
    // Add check box
    Control control = form.AddControl(page, L"Check Box0", Field::e_TypeCheckBox, RectF(50.0, 650, 90, 690));
    control.SetChecked(true);

    Widget widget = control.GetWidget();
    widget.SetMKBorderColor(0x000000);
    widget.SetMKBackgroundColor(0xFFFFFF);
    widget.ResetAppearanceStream();
    cout << "Add check box." << endl;
  }
  {
    // Add text field
    Control control = form.AddControl(page, L"Text Field0", Field::e_TypeTextField, RectF(50, 600, 90, 640));
    control.GetField().SetValue(L"3");
    // Update text field's appearance.
    control.GetWidget().ResetAppearanceStream();

    Control control1 = form.AddControl(page, L"Text Field1", Field::e_TypeTextField, RectF(100, 600, 140, 640));
    control1.GetField().SetValue(L"23");
    // Update text field's appearance.
    control1.GetWidget().ResetAppearanceStream();

    Control control2 = form.AddControl(page, L"Text Field2", Field::e_TypeTextField, RectF(150, 600, 190, 640));
    actions::JavaScriptAction javascipt_action = (actions::JavaScriptAction)Action::Create(form.GetDocument(), Action::e_TypeJavaScript);
    javascipt_action.SetScript(L"AFSimple_Calculate(\"SUM\", new Array (\"Text Field0\", \"Text Field1\"));" );
    Field field2 = control2.GetField();
    AdditionalAction additional_act(field2);
    additional_act.SetAction(AdditionalAction::e_TriggerFieldRecalculateValue,javascipt_action);
    // Update text field's appearance.
    control2.GetWidget().ResetAppearanceStream();

    cout << "Add text field." << endl;

  }
  {
    // Add text field with flag comb
    Control control = form.AddControl(page, L"Text Field3", Field::e_TypeTextField, RectF(50, 570, 100, 590));
    Field field = control.GetField();
    uint32 flag = Field::e_FlagTextComb;
    field.SetFlags(flag);
    field.SetValue(L"94538");
    field.SetMaxLength(5);
    // Update text field's appearance.
    control.GetWidget().ResetAppearanceStream();

  }
  {
    // Add text field, with flag multiline.
    Control control = form.AddControl(page, L"Text Field4", Field::e_TypeTextField, RectF(110, 550, 190, 590));
    Field field = control.GetField();
    uint32 flag = Field::e_FlagTextMultiline;
    field.SetFlags(flag);
    field.SetValue(L"Text fields are boxes or spaces in which the user can enter text from the keyboard.");
    // Update text field's appearance.
    control.GetWidget().ResetAppearanceStream();
  }
  {
    // Add text field, with flag password.
    Control control = form.AddControl(page, L"Text Field5", Field::e_TypeTextField, RectF(200, 570, 240, 590));
    Field field = control.GetField();
    uint32 flag = Field::e_FlagTextPassword;
    field.SetFlags(flag);
    field.SetValue(L"Password");
    // Update text field's appearance.
    control.GetWidget().ResetAppearanceStream();
  }
  {
    // Add list box
    Control control = form.AddControl(page, L"List Box0",  Field::e_TypeListBox,RectF(50, 450, 350, 500));

    Field field = control.GetField();
    ChoiceOptionArray options;
    options.Add(interform::ChoiceOption(L"Foxit SDK", L"Foxit SDK",true,true));
    options.Add(interform::ChoiceOption(L"Foxit Reader", L"Foxit Reader",true,true));
    options.Add(interform::ChoiceOption(L"Foxit Phantom", L"Foxit Phantom",true,true));
    field.SetOptions(options);

    Widget widget = control.GetWidget();
    widget.SetMKBorderColor(0x000000);
    widget.SetMKBackgroundColor(0xFFFFFF);
    widget.ResetAppearanceStream();
  }
  {
    // Add combo box
    Control control = form.AddControl(page, L"Combo Box0",  Field::e_TypeComboBox,RectF(50, 350, 350, 400));

    Field field = control.GetField();
    ChoiceOptionArray options;
    options.Add(interform::ChoiceOption(L"Foxit SDK", L"Foxit SDK",true,true));
    options.Add(interform::ChoiceOption(L"Foxit Reader", L"Foxit Reader",true,true));
    options.Add(interform::ChoiceOption(L"Foxit Phantom", L"Foxit Phantom",true,true));
    field.SetOptions(options);

    Widget widget = control.GetWidget();
    widget.SetMKBorderColor(0x000000);
    widget.SetMKBackgroundColor(0xFFFFFF);
    widget.ResetAppearanceStream();
  }
}
int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"form/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    PDFDoc doc;
    interform::Form form(doc);
     // Create a blank new page and add some form fields.
    PDFPage page = doc.InsertPage(0);
    AddInteractiveForms(page,form);

    WString newPdf = output_directory + L"form.pdf";

    doc.SaveAs(newPdf, PDFDoc::e_SaveFlagNoOriginal);
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }
  catch(...)
  {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}
