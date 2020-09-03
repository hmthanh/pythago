
// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to add various annotations to PDF document.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#include <map>

#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"

#include "../../../include/pdf/actions/fs_action.h"
#include "../../../include/pdf/fs_signature.h"
#include "../../../include/fs_actioncallback.h"
#include "../../../include/pdf/annots/fs_annot.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/objects/fs_pdfobject.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/fs_psi.h"
#include "../../../include/pdf/fs_filespec.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace annots;
using foxit::pdf::annots::Line;

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

DateTime GetLocalDateTime() {
  time_t t = time(NULL);
#if (WINAPI_PARTITION_APP || WINAPI_PARTITION_PC_APP) || \
  (defined(_WIN32) || defined(_WIN64)) && _FX_COMPILER_ != _FX_VC6_
  struct tm _Tm;
  localtime_s(&_Tm, &t);
  struct tm* rime = &_Tm;
  _tzset();
  long time_zone = NULL;
  _get_timezone(&time_zone);
  int timezone_hour = time_zone / 3600 * -1;
  int timezone_minute = (abs(time_zone) % 3600) / 60;
#elif defined(__linux__)
  struct tm* rime = localtime(&t);
  tzset();
  int timezone_hour = __timezone / 3600 * -1;
  int timezone_minute = ((int)abs(__timezone) % 3600) / 60;
#elif defined(__APPLE__)
  struct tm* rime = localtime(&t);
  tzset();
  int timezone_hour = timezone / 3600 * -1;
  int timezone_minute = ((int)abs(timezone) % 3600) / 60;
#endif
  DateTime datetime;
  datetime.year = static_cast<uint16>(rime->tm_year + 1900);
  datetime.month = static_cast<uint16>(rime->tm_mon + 1);
  datetime.day = static_cast<uint16>(rime->tm_mday);
  datetime.hour = static_cast<uint16>(rime->tm_hour);
  datetime.minute = static_cast<uint16>(rime->tm_min);
  datetime.second = static_cast<uint16>(rime->tm_sec);
  datetime.utc_hour_offset = timezone_hour;
  datetime.utc_minute_offset = timezone_minute;

  return datetime;
}

String RandomUID() {
  String uuid;
  const char* c = "0123456789qwertyuiopasdfghjklzxcvbnm";

  for (int n = 0; n < 16; n++) {
    String uuid_temp;
    int b = rand() % 255;
    switch (n) {
    case 6:
      uuid_temp.Format("4%x", b % 15);
      break;
    case 8:
      uuid_temp.Format("%c%x", c[rand() % strlen(c)], b % 15);
      break;
    default:
      uuid_temp.Format("%02x", b);
      break;
    }
    uuid += uuid_temp;

    switch (n) {
    case 3:
    case 5:
    case 7:
    case 9:
      uuid += '-';
      break;
    }
  }
  return uuid;
}
class IconProvider : public IconProviderCallback {
public:
  static IconProvider* Create(string path) {
    return new IconProvider(path);
  }
  virtual void Release() {
    delete this;
  }

  // If one icon provider offers different style icon for one icon name of a kind of annotaion,
  // please use different provider ID or version in order to distinguish different style for Foxit PDF SDK.
  // Otherwise, only the first style icon for the same icon name of same kind of annotation will have effect.
  virtual String GetProviderID() {
    if (use_dynamic_stamp_)
      return "Simple Demo Dynamic IconProvider";
    else
      return "Simple Demo IconProvider";
  }

  virtual String GetProviderVersion() {
    return "1.0.0";
  }

  virtual bool HasIcon(Annot::Type annot_type, const char* icon_name) {
    std::map<string, PDFDoc>::iterator it = pdf_doc_map_.find(icon_name);

    if(it != pdf_doc_map_.end())
    {
      PDFDoc doc = (*it).second;
      return !doc.IsEmpty();
    }
    PDFDoc doc = PDFDoc();
    string path;
    if (doc.GetPageCount()==0) {
      try {
        if (use_dynamic_stamp_) {
          path = file_folder_ + "/DynamicStamps/" + icon_name + ".pdf";
        } else {
          path = file_folder_ + "/StaticStamps/" + icon_name + ".pdf";
        }
        doc = PDFDoc(path.c_str());
        ErrorCode error_code = doc.Load();
        if (foxit::e_ErrSuccess != error_code) {
          doc = PDFDoc();
        } else {
          pdf_doc_map_.insert(std::pair<string, PDFDoc>(path, doc));
        }
      } catch (const Exception& e) {
        cout << e.GetMessage() << endl;
      }
    }
    return !doc.IsEmpty();
  }

  virtual bool CanChangeColor(Annot::Type annot_type, const char* icon_name) {
    return false;
  }

  virtual PDFPage GetIcon(Annot::Type annot_type, const char* icon_name, foxit::ARGB color) {
    string path;
    if (use_dynamic_stamp_) {
      path = file_folder_ + "/DynamicStamps/" + icon_name + ".pdf";
    } else {
      path = file_folder_ + "/StaticStamps/" + icon_name + ".pdf";
    }
    std::map<string, PDFDoc>::iterator it = pdf_doc_map_.find(path);

    PDFDoc doc = ((it != pdf_doc_map_.end()) ? (*it).second : PDFDoc());
    if (doc.IsEmpty() || doc.GetPageCount() == 0)
      return PDFPage();
    return doc.GetPage(0);
  }

  virtual bool GetShadingColor(Annot::Type annot_type, const char* icon_name, foxit::RGB referenced_color,
    int shading_index, foxit::pdf::annots::ShadingColor& shading_color) {
      return false;
  }

  virtual float GetDisplayWidth(Annot::Type annot_type, const char* icon_name) {
    return 0.0f;
  }

  virtual float GetDisplayHeight(Annot::Type annot_type, const char* icon_name) {
    return 0.0f;
  }

  void SetUseDynamicStamp(bool use_dynamic_stamp) {
    use_dynamic_stamp_ = use_dynamic_stamp;
  }

private:
  IconProvider(string file_folder)
    : file_folder_(file_folder)
    , use_dynamic_stamp_(false)
    {}
  virtual ~IconProvider() {
  }
  std::map<string, PDFDoc> pdf_doc_map_;
  string file_folder_;
  vector<string> incon_names_;
  bool use_dynamic_stamp_;
};

class ActionEvent : public foxit::ActionCallback {
public:
  ActionEvent() {}
  ~ActionEvent() {}
  virtual void Release() {delete this;}
  virtual bool InvalidateRect(const PDFDoc& document, int page_index, const RectF& pdf_rect) {
    return false;
  }
  virtual int GetCurrentPage(const PDFDoc& document) {
    return -1;
  }
  virtual void SetCurrentPage(const PDFDoc& document, int page_index) {}
  virtual foxit::common::Rotation GetPageRotation(const PDFDoc& document, int page_index) {
    return foxit::common::e_Rotation0;
  }
  virtual bool SetPageRotation(const PDFDoc& document, int page_index, foxit::common::Rotation rotation) {
    return false;
  }
  virtual bool ExecuteNamedAction(const PDFDoc& document, const char* named_action) {
    return false;
  }
  virtual bool SetDocChangeMark(const PDFDoc& document, bool change_mark) {
    return false;
  }
  virtual bool GetDocChangeMark(const PDFDoc& document) {
    return false;
  }
  virtual int GetOpenedDocCount() {
    return -1;
  }
  virtual PDFDoc GetOpenedDoc(int index) {
    return PDFDoc();
  }
  virtual bool Beep(int type) {
    return false;
  }
  virtual WString Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_value, const wchar_t* label,
    bool is_password) {
      return L"";
  }
  virtual WString GetFilePath(const PDFDoc& document) {
    return L"";
  }
  virtual bool Print(const PDFDoc& document, bool is_ui,
    const common::Range& page_set, bool is_silent ,
    bool is_shrunk_to_fit, bool is_printed_as_image,
    bool is_reversed, bool is_to_print_annots) {
      return false;
  }
  virtual bool SubmitForm(const PDFDoc& document, void* form_data, foxit::uint32 length, const char* url) {
    return false;
  }
  virtual bool LaunchURL(const char* url) {
    return false;
  }
  virtual WString BrowseFile() {
    return L"";
  }
  virtual foxit::ActionCallback::Language GetLanguage() {
    return foxit::ActionCallback::e_LanguageCHS;
  }
  virtual int Alert(const wchar_t* msg, const wchar_t* title, int type, int icon) {
    return 0;
  }
  virtual foxit::IdentityProperties GetIdentityProperties() {
    return foxit::IdentityProperties(L"foxitsoftware", L"simple_demo@foxitsoftware.cn", L"simple demo", L"Simple");
  }
  virtual WString PopupMenu(const foxit::MenuListArray& menus) {
    return L"";
  }
  virtual WString GetAppInfo(foxit::ActionCallback::AppInfoType type) {
    return L"";
  }
  virtual bool MailData(void* data, MailType data_type, bool is_ui, const wchar_t* to,
    const wchar_t* subject, const wchar_t* cc, const wchar_t* bcc, const wchar_t* message) {
      return false;
  }
  virtual uint32 VerifySignature(const pdf::PDFDoc& document, const pdf::Signature& pdf_signature) {
    return pdf::Signature::e_StateUnknown;
  }

};

void AddAnnotations(PDFPage &page)
{
  {
    // Add line annotation 
    // No special intent, as a common line.
    annots::Line line(page.AddAnnot(Annot::e_Line,RectF(0,650,100,750)));
    line.SetStartPoint(PointF(20,650));
    line.SetEndPoint(PointF(100,740));
    // Intent, as line arrow.
    line.SetContent(L"A line arrow annotation");
    line.SetIntent("LineArrow");
    line.SetSubject(L"Arrow");
    line.SetTitle(L"Foxit SDK");
    line.SetCreationDateTime(GetLocalDateTime());
    line.SetModifiedDateTime(GetLocalDateTime());
    line.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    line.ResetAppearanceStream();

    line = annots::Line(page.AddAnnot(Annot::e_Line,RectF(0,650,100,760)));
    // Set foxit RGB color
    line.SetBorderColor(0x00FF00);
    line.SetStartPoint(PointF(10,650));
    line.SetEndPoint(PointF(100,750));
    line.SetContent(L"A common line.");
    line.SetLineStartStyle(annots::Markup::e_EndingStyleSquare);
    line.SetLineEndStyle(annots::Markup::e_EndingStyleOpenArrow);
    // Show text in line
    line.EnableCaption(true);
    line.SetCaptionOffset(PointF(0,5));

    line.SetSubject(L"Line");
    line.SetTitle(L"Foxit SDK");
    line.SetCreationDateTime(GetLocalDateTime());
    line.SetModifiedDateTime(GetLocalDateTime());
    line.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    line.ResetAppearanceStream();
    cout << "Add a line annotations." << endl;
  }

  {
    // Add circle annotation
    annots::Circle circle(page.AddAnnot(Annot::e_Circle,RectF(100,650,200,750)));
    circle.SetInnerRect(RectF(120,660,160,740));
    circle.SetSubject(L"Circle");
    circle.SetTitle(L"Foxit SDK");
    circle.SetCreationDateTime(GetLocalDateTime());
    circle.SetModifiedDateTime(GetLocalDateTime());
    circle.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    circle.ResetAppearanceStream();
    cout << "Add a circle annotation." << endl;
  }

  {
    // Add square annotation
    annots::Square square(page.AddAnnot(Annot::e_Square,RectF(200,650,300,750)));
    square.SetFillColor(0x00FF00);
    square.SetInnerRect(RectF(220,660,260,740));
    square.SetSubject(L"Square");
    square.SetTitle(L"Foxit SDK");
    square.SetCreationDateTime(GetLocalDateTime());
    square.SetModifiedDateTime(GetLocalDateTime());
    square.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    square.ResetAppearanceStream();
    cout << "Add a square annotation." << endl;
  }

  {
    // Add polygon annotation, as cloud.
    annots::Polygon polygon(page.AddAnnot(Annot::e_Polygon,RectF(300,650,500,750)));
    polygon.SetIntent("PolygonCloud");
    polygon.SetFillColor(0x0000FF);
    foxit::PointFArray vertexe_array;
    vertexe_array.Add(PointF(335,665));
    vertexe_array.Add(PointF(365,665));
    vertexe_array.Add(PointF(385,705));
    vertexe_array.Add(PointF(365,740));
    vertexe_array.Add(PointF(335,740));
    vertexe_array.Add(PointF(315,705));
    polygon.SetVertexes(vertexe_array);
    polygon.SetSubject(L"Cloud");
    polygon.SetTitle(L"Foxit SDK");
    polygon.SetCreationDateTime(GetLocalDateTime());
    polygon.SetModifiedDateTime(GetLocalDateTime());
    polygon.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    polygon.ResetAppearanceStream();
    cout << "Add a polygon annotation." << endl;
  }

  {
    // Add polygon annotation, with dashed border.
    BorderInfo borderinfo;
    borderinfo.cloud_intensity = 2.0f;
    borderinfo.width = 2.0f;
    borderinfo.style = BorderInfo::e_Dashed;
    borderinfo.dash_phase = 3.f;
    borderinfo.dashes.SetSize(2);
    borderinfo.dashes.SetAt(0,2);
    borderinfo.dashes.SetAt(1,2);

    annots::Polygon polygon(page.AddAnnot(Annot::e_Polygon,RectF(400,650,500,750)));
    polygon.SetFillColor(0x0000FF);
    polygon.SetBorderInfo(borderinfo);
    foxit::PointFArray vertexe_array;
    vertexe_array.Add(PointF(435,665));
    vertexe_array.Add(PointF(465,665));
    vertexe_array.Add(PointF(485,705));
    vertexe_array.Add(PointF(465,740));
    vertexe_array.Add(PointF(435,740));
    vertexe_array.Add(PointF(415,705));

    polygon.SetVertexes(vertexe_array);
    polygon.SetSubject(L"Polygon");
    polygon.SetTitle(L"Foxit SDK");
    polygon.SetCreationDateTime(GetLocalDateTime());
    polygon.SetModifiedDateTime(GetLocalDateTime());
    polygon.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    polygon.ResetAppearanceStream();
    cout << "Add a polygon cloud annotation." << endl;
  }

  {
    // Add polyline annotation
    annots::PolyLine polyline(page.AddAnnot(Annot::e_PolyLine,RectF(500,650,600,700)));
    foxit::PointFArray vertexe_array;
    vertexe_array.Add(PointF(515,705));
    vertexe_array.Add(PointF(535,740));
    vertexe_array.Add(PointF(565,740));
    vertexe_array.Add(PointF(585,705));
    vertexe_array.Add(PointF(565,665));
    vertexe_array.Add(PointF(535,665));
    polyline.SetVertexes(vertexe_array);
    polyline.SetSubject(L"PolyLine");
    polyline.SetTitle(L"Foxit SDK");
    polyline.SetCreationDateTime(GetLocalDateTime());
    polyline.SetModifiedDateTime(GetLocalDateTime());
    polyline.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    polyline.ResetAppearanceStream();
    cout << "Add a polyline annotation." << endl;
  }

  {
    // Add freetext annotation, as type writer.
    annots::FreeText freetext(page.AddAnnot(Annot::e_FreeText,RectF(10,550,200,600)));
    // Set default appearance
    foxit::pdf::DefaultAppearance default_ap;
    default_ap.flags = DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor;
    default_ap.font = common::Font(common::Font::e_StdIDHelvetica);
    default_ap.text_size = 12.0f;
    default_ap.text_color = 0x000000;
    // Set default appearance for form.
    freetext.SetDefaultAppearance(default_ap);
    freetext.SetAlignment(common::e_AlignmentLeft);
    freetext.SetIntent("FreeTextTypewriter");
    freetext.SetContent(L"A typewriter annotation");
    freetext.SetSubject(L"FreeTextTypewriter");
    freetext.SetTitle(L"Foxit SDK");
    freetext.SetCreationDateTime(GetLocalDateTime());
    freetext.SetModifiedDateTime(GetLocalDateTime());
    freetext.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    freetext.ResetAppearanceStream();
    cout << "Add a typewriter freetext annotation." << endl;

  }
  {
    // Add freetext annotation, as call-out.
    annots::FreeText freetext(page.AddAnnot(Annot::e_FreeText,RectF(300,550,400,600)));
    // Set default appearance
    foxit::pdf::DefaultAppearance default_ap;
    default_ap.flags = DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor;
    default_ap.font = common::Font(common::Font::e_StdIDHelveticaB);
    default_ap.text_size = 12.0f;
    default_ap.text_color = 0x000000;
    // Set default appearance for form.
    freetext.SetDefaultAppearance(default_ap);
    freetext.SetAlignment(common::e_AlignmentCenter);
    //
    freetext.SetIntent("FreeTextCallout");
    PointFArray callout_points;
    callout_points.Add(PointF(250,540));
    callout_points.Add(PointF(280,570));
    callout_points.Add(PointF(300,570));

    freetext.SetCalloutLinePoints(callout_points);
    freetext.SetCalloutLineEndingStyle(annots::Markup::e_EndingStyleOpenArrow);
    freetext.SetContent(L"A callout annotation.");
    freetext.SetSubject(L"FreeTextCallout");
    freetext.SetTitle(L"Foxit SDK");
    freetext.SetCreationDateTime(GetLocalDateTime());
    freetext.SetModifiedDateTime(GetLocalDateTime());
    freetext.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    freetext.ResetAppearanceStream();
    cout << "Add a callout freetext annotation." << endl;
  }
  {
    // Add freetext annotation, as text box.
    annots::FreeText freetext(page.AddAnnot(Annot::e_FreeText,RectF(450,550,550,600)));
    // Set default appearance
    foxit::pdf::DefaultAppearance default_ap;
    default_ap.flags = DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor;
    default_ap.font = common::Font(common::Font::e_StdIDHelveticaI);
    default_ap.text_size = 12.0f;
    default_ap.text_color = 0x000000;
    // Set default appearance for form.
    freetext.SetDefaultAppearance(default_ap);
    freetext.SetAlignment(common::e_AlignmentCenter);
    freetext.SetContent(L"A text box annotation.");
    freetext.SetSubject(L"Textbox");
    freetext.SetTitle(L"Foxit SDK");
    freetext.SetCreationDateTime(GetLocalDateTime());
    freetext.SetModifiedDateTime(GetLocalDateTime());
    freetext.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    freetext.ResetAppearanceStream();
    cout << "Add a text box freetext annotation." << endl;
  }
  {
    // Add highlight annotation.
    annots::Highlight highlight(page.AddAnnot(Annot::e_Highlight,RectF(10,450,100,550)));
    highlight.SetContent(L"Highlight");
    annots::QuadPoints quad_points;
    quad_points.first = PointF(10, 500);
    quad_points.second = PointF(90, 500);
    quad_points.third = PointF(10, 480);
    quad_points.fourth = PointF(90, 480);
    annots::QuadPointsArray quad_points_array;
    quad_points_array.Add(quad_points);
    highlight.SetQuadPoints(quad_points_array);
    highlight.SetSubject(L"Highlight");
    highlight.SetTitle(L"Foxit SDK");
    highlight.SetCreationDateTime(GetLocalDateTime());
    highlight.SetModifiedDateTime(GetLocalDateTime());
    highlight.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    highlight.ResetAppearanceStream();
    cout << "Add a highlight annotation." << endl;
  }
  {
    // Add underline annotation.
    annots::Underline underline(page.AddAnnot(Annot::e_Underline,RectF(100,450,200,550)));
    annots::QuadPoints quad_points;
    quad_points.first = PointF(110, 500);
    quad_points.second = PointF(190, 500);
    quad_points.third = PointF(110, 480);
    quad_points.fourth = PointF(190, 480);
    annots::QuadPointsArray quad_points_array;
    quad_points_array.Add(quad_points);
    underline.SetQuadPoints(quad_points_array);
    underline.SetSubject(L"Underline");
    underline.SetTitle(L"Foxit SDK");
    underline.SetCreationDateTime(GetLocalDateTime());
    underline.SetModifiedDateTime(GetLocalDateTime());
    underline.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    underline.ResetAppearanceStream();
    cout << "Add a underline annotation." << endl;
  }
  {
    // Add squiggly annotation.
    annots::Squiggly squiggly(page.AddAnnot(Annot::e_Squiggly,RectF(200,450,300,550)));
    squiggly.SetIntent("Squiggly");

    annots::QuadPoints quad_points;
    quad_points.first = PointF(210, 500);
    quad_points.second = PointF(290, 500);
    quad_points.third = PointF(210, 480);
    quad_points.fourth = PointF(290, 480);
    annots::QuadPointsArray quad_points_array;
    quad_points_array.Add(quad_points);
    squiggly.SetQuadPoints(quad_points_array);
    squiggly.SetSubject(L"Squiggly");
    squiggly.SetTitle(L"Foxit SDK");
    squiggly.SetCreationDateTime(GetLocalDateTime());
    squiggly.SetModifiedDateTime(GetLocalDateTime());
    squiggly.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    squiggly.ResetAppearanceStream();
    cout << "Add a squiggly annotation." << endl;
  }
  {
    // Add strikeout annotation.
    annots::StrikeOut strikeout(page.AddAnnot(Annot::e_StrikeOut, RectF(300,450,400,550)));
    annots::QuadPoints quad_points;
    quad_points.first = PointF(310, 500);
    quad_points.second = PointF(390, 500);
    quad_points.third = PointF(310, 480);
    quad_points.fourth = PointF(390, 480);
    annots::QuadPointsArray quad_points_array;
    quad_points_array.Add(quad_points);
    strikeout.SetQuadPoints(quad_points_array);
    strikeout.SetSubject(L"StrikeOut");
    strikeout.SetTitle(L"Foxit SDK");
    strikeout.SetCreationDateTime(GetLocalDateTime());
    strikeout.SetModifiedDateTime(GetLocalDateTime());
    strikeout.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    strikeout.ResetAppearanceStream();
    cout << "Add a strikeout annotation." << endl;
  }
  {
    // Add caret annotation.
    annots::Caret caret(page.AddAnnot( Annot::e_Caret, RectF(400,450,420,470)));
    caret.SetInnerRect(RectF(410,450,430,470));
    caret.SetContent(L"Caret annotation");
    caret.SetSubject(L"Caret");
    caret.SetTitle(L"Foxit SDK");
    caret.SetCreationDateTime(GetLocalDateTime());
    caret.SetModifiedDateTime(GetLocalDateTime());
    caret.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    caret.ResetAppearanceStream();
    cout << "Add a caret annotation." << endl;
  }
  {
    // Add note annotation
    annots::Note note(page.AddAnnot( Annot::e_Note, RectF(10,350,50,400)));
    note.SetIconName("Comment");
    note.SetSubject(L"Note");
    note.SetTitle(L"Foxit SDK");
    note.SetContent(L"Note annotation.");
    note.SetCreationDateTime(GetLocalDateTime());
    note.SetModifiedDateTime(GetLocalDateTime());
    note.SetUniqueID(WString::FromLocal(RandomUID()));
    // Add popup to note annotation
    Popup popup(page.AddAnnot(Annot::e_Popup, RectF(300,450,500,550)));
    popup.SetBorderColor(0x00FF00);
    popup.SetOpenStatus(false);
    popup.SetModifiedDateTime(GetLocalDateTime());
    note.SetPopup(popup);

    // Add reply annotation to note annotation
    Note reply = note.AddReply();
    reply.SetContent(L"reply");
    reply.SetModifiedDateTime(GetLocalDateTime());
    reply.SetTitle(L"Foxit SDK");
    reply.SetUniqueID(WString::FromLocal(RandomUID()));
    reply.ResetAppearanceStream();

    // Add state annotation to note annotation
    Note state = note.AddStateAnnot(Markup::e_StateModelReview, Markup::e_StateAccepted);
    state.SetContent(L"Accepted set by Foxit SDK");
    state.SetTitle(L"Foxit SDK");
    state.SetModifiedDateTime(GetLocalDateTime());
    state.SetUniqueID(WString::FromLocal(RandomUID()));
    state.ResetAppearanceStream();
    // Appearance should be reset.
    note.ResetAppearanceStream();
    cout << "Add a note annotation." << endl;
  }
  {
    // Add ink annotation
    annots::Ink ink(page.AddAnnot( Annot::e_Ink, RectF(100,350,200,450)));

    foxit::common::Path inklist;
    float width = 100;
    float height = 100;
    float out_width = min(width, height) * 2 / 3.f;
    float inner_width = out_width * sin(18.f / 180.f * 3.14f) / sin(36.f / 180.f * 3.14f);
    PointF center(150, 400);
    float x = out_width;
    float y = 0;
    inklist.MoveTo(PointF(center.x + x, center.y + y));
    for (int i = 0; i < 5; i++) {
      x = out_width * cos(72.f * i / 180.f * 3.14f);
      y = out_width * sin(72.f * i / 180.f * 3.14f);
      inklist.LineTo(PointF(center.x + x, center.y + y));

      x = inner_width * cos((72.f * i + 36) / 180.f * 3.14f);
      y = inner_width * sin((72.f * i + 36) / 180.f * 3.14f);
      inklist.LineTo(PointF(center.x + x, center.y + y));
    }
    inklist.LineTo(PointF(center.x + out_width, center.y + 0));
    inklist.CloseFigure();
    ink.SetInkList(inklist);
    ink.SetSubject(L"Ink");
    ink.SetTitle(L"Foxit SDK");
    ink.SetContent(L"Note annotation.");
    ink.SetCreationDateTime(GetLocalDateTime());
    ink.SetModifiedDateTime(GetLocalDateTime());
    ink.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    ink.ResetAppearanceStream();
    cout << "Add an ink annotation." << endl;
  }
  {
    // Add file attachment annotation
    WString pdf_file = input_path + L"AboutFoxit.pdf";
    annots::FileAttachment file_attachment(page.AddAnnot( Annot::e_FileAttachment, RectF(280,350,300,380)));
    file_attachment.SetIconName("Graph");

    foxit::pdf::FileSpec file_spec = foxit::pdf::FileSpec(page.GetDocument());
    file_spec.SetFileName(L"attachment.pdf");
    file_spec.SetCreationDateTime(GetLocalDateTime());
    file_spec.SetDescription("The original file");
    file_spec.SetModifiedDateTime(GetLocalDateTime());
    file_spec.Embed(pdf_file);
    file_attachment.SetFileSpec(file_spec);
    file_attachment.SetSubject(L"File Attachment");
    file_attachment.SetTitle(L"Foxit SDK");
    // Appearance should be reset.
    file_attachment.ResetAppearanceStream();
    cout << "Add an attachment annotation." << endl;
  }
  {
    // Add link annotation
    annots::Link link(page.AddAnnot( Annot::e_Link, RectF(350,350,380,400)));
    link.SetHighlightingMode(Annot::e_HighlightingToggle);

    // Add action for link annotation
    using foxit::pdf::actions::Action;
    using foxit::pdf::actions::URIAction;
    URIAction action = (URIAction)Action::Create(page.GetDocument(), Action::e_TypeURI);
    action.SetTrackPositionFlag(true);
    action.SetURI("www.foxitsoftware.com");
    link.SetAction(action);
    // Appearance should be reset.
    link.ResetAppearanceStream();
    cout << "Add a link annotation." << endl;
  }
  {
    // Set icon provider for annotation to Foxit PDF SDK.
#if defined(_WIN32) || defined(_WIN64)
    IconProvider* icon_provider = IconProvider::Create("../input_files/Stamps");
#else
    IconProvider* icon_provider = IconProvider::Create("./input_files/Stamps");
#endif

    icon_provider->SetUseDynamicStamp(false);
    Library::SetAnnotIconProviderCallback(icon_provider);

    // Add common stamp annotation.
    Library::SetActionCallback(NULL);
    Stamp static_stamp(page.AddAnnot(Annot::e_Stamp, RectF(110,150,200,250)));
    static_stamp.SetIconName("Approved");
    // Appearance should be reset.
    static_stamp.ResetAppearanceStream();

    // Add dynamic stamp annotation.
    Library::SetActionCallback(new ActionEvent());
    icon_provider->SetUseDynamicStamp(true);
    Stamp dynamic_stamp(page.AddAnnot(Annot::e_Stamp, RectF(10,150,100,250)));
    dynamic_stamp.SetIconName("Approved");
    // Appearance should be reset.
    dynamic_stamp.ResetAppearanceStream();
    cout << "Add stamp annotations." << endl;

  }
}
int main(int argc, char *argv[])
{
  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try{
    WString input_file = input_path + L"annotation_input.pdf";
    WString output_directory = output_path + L"annotation/";
#if defined(_WIN32) || defined(_WIN64)
    _mkdir(String::FromUnicode(output_directory));
#else
    mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    // Load a document
    PDFDoc doc = PDFDoc(input_file);
    doc.Load();
    // Get first page with index 0
    PDFPage page = doc.GetPage(0);
    AddAnnotations(page);
    // Save PDF file
    WString newPdf = output_directory + L"annotation.pdf";
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
