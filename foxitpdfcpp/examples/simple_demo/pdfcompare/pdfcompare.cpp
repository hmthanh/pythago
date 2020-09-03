// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to compare pdf page with the other.

#include <time.h>
#include <math.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/fs_search.h"
#include "../../../include/addon/comparison/fs_compare.h"
#include "../../../include/common/fxcrt/fx_basic.h"

using namespace std;
using namespace foxit;
using namespace common;
using namespace addon;
using foxit::common::Library;
using namespace pdf;
using namespace foxit::pdf::annots;
using namespace foxit::addon::comparison;

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
void CreateInsertStamp(PDFPage page, RectFArray rects, RGB color, WString csContents, WString csType, WString csObjType)
{
	RectF rcStamp;
	int rectSize = rects.GetSize();
	if (rectSize > 0)
	{
		RectF item = rects.GetAt(0);
		rcStamp.left = item.left;
		rcStamp.top = item.top-4 ;
		rcStamp.right = rcStamp.left + 4;
		rcStamp.bottom = rcStamp.top - 8;
	}

	Image pImage = Image(input_path + L"pdfcompare/insert_stamp.png");

	annots::Stamp stamp(page.AddAnnot(Annot::e_Stamp, rcStamp));
	stamp.SetContent(csContents);
	stamp.SetBorderColor(color);
	stamp.SetSubject(csObjType);
	stamp.SetTitle(csType);
	stamp.SetCreationDateTime(GetLocalDateTime());
	stamp.SetModifiedDateTime(GetLocalDateTime());
	stamp.SetUniqueID(WString::FromLocal(RandomUID()));
	stamp.SetImage(pImage, 0, 0);

	stamp.ResetAppearanceStream();
}
void CreateSquigglyRect(PDFPage page, RectFArray rects, RGB color, WString csContents, WString csType, WString csObjType)
{
	annots::Squiggly squiggly(page.AddAnnot(Annot::e_Squiggly, RectF()));
	squiggly.SetContent(csContents);

    annots::QuadPointsArray quad_points_array;
    int rectSize = rects.GetSize();
    for (int i=0; i<rectSize; i++)
    {
        CFX_FloatRect item = rects.GetAt(i);
        annots::QuadPoints quad_points;
        quad_points.first = PointF(item.left, item.top);
        quad_points.second = PointF(item.right, item.top);
        quad_points.third = PointF(item.left, item.bottom);
        quad_points.fourth = PointF(item.right, item.bottom);
        quad_points_array.Add(quad_points);
    }
	squiggly.SetQuadPoints(quad_points_array);

	squiggly.SetBorderColor(color);
	squiggly.SetSubject(csObjType);
	squiggly.SetTitle(csType);
	squiggly.SetCreationDateTime(GetLocalDateTime());
	squiggly.SetModifiedDateTime(GetLocalDateTime());
	squiggly.SetUniqueID(WString::FromLocal(RandomUID()));

	squiggly.ResetAppearanceStream();
}

void CreateDeleteTextStamp(PDFPage page, RectFArray rects, RGB color, WString csContents, WString csType, WString csObjType)
{
    RectF rcStamp;
    int rectSize = rects.GetSize();
    if (rectSize > 0)
    {
        RectF item = rects.GetAt(0);
        rcStamp.left = item.left;
        rcStamp.top = item.top + 12;
        rcStamp.right = rcStamp.left + 9;
        rcStamp.bottom = rcStamp.top - 12;
    }

    Image pImage = Image(input_path + L"pdfcompare/delete_stamp.png");

    annots::Stamp stamp(page.AddAnnot(Annot::e_Stamp, rcStamp));
    stamp.SetContent(csContents);
    stamp.SetBorderColor(color);
    stamp.SetSubject(csObjType);
    stamp.SetTitle(csType);
    stamp.SetCreationDateTime(GetLocalDateTime());
    stamp.SetModifiedDateTime(GetLocalDateTime());
    stamp.SetUniqueID(WString::FromLocal(RandomUID()));
    stamp.SetImage(pImage, 0, 0);

    stamp.ResetAppearanceStream();
}
void CreateDeleteText(PDFPage page, RectFArray rects, RGB color, WString csContents, WString csType, WString csObjType)
{
	annots::StrikeOut strikeout(page.AddAnnot(Annot::e_StrikeOut, RectF()));
	strikeout.SetContent(csContents);

	annots::QuadPointsArray quad_points_array;
	int rectSize = rects.GetSize();
	for (int i = 0; i<rectSize; i++)
	{
		CFX_FloatRect item = rects.GetAt(i);
		annots::QuadPoints quad_points;
		quad_points.first = PointF(item.left, item.top);
		quad_points.second = PointF(item.right, item.top);
		quad_points.third = PointF(item.left, item.bottom);
		quad_points.fourth = PointF(item.right, item.bottom);
		quad_points_array.Add(quad_points);
	}
	strikeout.SetQuadPoints(quad_points_array);

	strikeout.SetBorderColor(color);
	strikeout.SetSubject(csObjType);
	strikeout.SetTitle(csType);
	strikeout.SetCreationDateTime(GetLocalDateTime());
	strikeout.SetModifiedDateTime(GetLocalDateTime());
	strikeout.SetUniqueID(WString::FromLocal(RandomUID()));

	strikeout.ResetAppearanceStream();
}
WString output_directory = output_path + L"pdfcompare/";

int main(int argc, char *argv[])
{
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_base_file = input_path + L"pdfcompare/test_base.pdf";
  WString input_compared_file = input_path + L"pdfcompare/test_compared.pdf";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  if(sdk_lib_mgr.Initialize() != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    PDFDoc base_doc(input_base_file);
    ErrorCode error_code = base_doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_base_file), error_code);
      return 1;
    }

    PDFDoc compared_doc(input_compared_file);
    error_code = compared_doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_compared_file), error_code);
        return 1;
    }

    Comparison comparison(base_doc, compared_doc);
    CompareResults result = comparison.DoCompare(0, 0, Comparison::e_CompareTypeText);
    CompareResultInfoArray& oldInfo = result.base_doc_results;
    CompareResultInfoArray& newInfo = result.compared_doc_results;
    int oldInfoSize = oldInfo.GetSize();
    int newInfoSize = newInfo.GetSize();
	PDFPage page1 = base_doc.GetPage(0);
    PDFPage page = compared_doc.GetPage(0);
	for (int i = 0; i<oldInfoSize; i++)
	{
		const CompareResultInfo& item = oldInfo.GetAt(i);
		CompareResultInfo::CompareResultType type = item.type;
		if (type == CompareResultInfo::e_CompareResultTypeDeleteText)
		{
			String res_string;
			res_string.Format((FX_LPCSTR)"\"%s\"", (FX_LPCSTR)String::FromUnicode(item.diff_contents));
			CreateDeleteText(page1, item.rect_array, 0xff0000, WString::FromLocal(res_string), L"Compare : Delete", L"Text");
		}
		else if (type == CompareResultInfo::e_CompareResultTypeInsertText)
		{
			String res_string;
			res_string.Format((FX_LPCSTR)"\"%s\"", (FX_LPCSTR)String::FromUnicode(item.diff_contents));
			CreateInsertStamp(page1, item.rect_array, 0x0000ff, WString::FromLocal(res_string), L"Compare : Insert", L"Text");
		}
		else if (type == CompareResultInfo::e_CompareResultTypeReplaceText)
		{
			String res_string;

			res_string.Format("[New]: \"%s\"\r\n[Old]: \"%s\"", (FX_LPCSTR)String::FromUnicode(newInfo.GetAt(i).diff_contents), (FX_LPCSTR)String::FromUnicode(item.diff_contents));
			CreateSquigglyRect(page1, item.rect_array, 0xe7651a, WString::FromLocal(res_string), L"Compare : Replace", L"Text");
		}
	}
    for (int i=0; i<newInfoSize; i++)
    {
        const CompareResultInfo& item = newInfo.GetAt(i);
        CompareResultInfo::CompareResultType type = item.type;
        if (type == CompareResultInfo::e_CompareResultTypeDeleteText)
        {
            String res_string;
            res_string.Format((FX_LPCSTR)"\"%s\"", (FX_LPCSTR)String::FromUnicode(item.diff_contents));
            CreateDeleteTextStamp(page, item.rect_array, 0xff0000, WString::FromLocal(res_string), L"Compare : Delete", L"Text");
        }
        else if (type == CompareResultInfo::e_CompareResultTypeInsertText)
        {
            String res_string;
            res_string.Format((FX_LPCSTR)"\"%s\"", (FX_LPCSTR)String::FromUnicode(item.diff_contents));
			CreateDeleteText(page, item.rect_array, 0x0000ff, WString::FromLocal(res_string), L"Compare : Insert", L"Text");
        }
        else if (type == CompareResultInfo::e_CompareResultTypeReplaceText)
        {
            String res_string;
			
            res_string.Format("[Old]: \"%s\"\r\n[New]: \"%s\"", (FX_LPCSTR)String::FromUnicode(oldInfo.GetAt(i).diff_contents), (FX_LPCSTR)String::FromUnicode(item.diff_contents));
			CreateSquigglyRect(page, item.rect_array, 0xe7651a, WString::FromLocal(res_string), L"Compare : Replace", L"Text");
        }
    }
	base_doc.SaveAs(output_directory+ L"old.pdf");
	compared_doc.SaveAs(output_directory + L"new.pdf");

    cout << "Pdf compare test." << endl;
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

