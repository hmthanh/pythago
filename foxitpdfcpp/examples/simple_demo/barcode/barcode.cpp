// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to generate barcode.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/common/fs_barcode.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;

static const char* sn = "eUcaj+XFRdwDeV4fx2eGZzF7ZmQiBNInjxfWhiHCIinKYg3KsYgcKg==";
static const char* key = "8f0YFcONvRsJ+nePmKBLSM8bw7bGx79neQeRmlgo13uto3HGtEFz4BLMd5BErJbDU1Nll8omHE6H+Vx20kaMiDQYMDldaA9ctpwcoLODu8yfFtHTm2UseIiHVjqu52IRK18VKf4pLWI6ekSbkAafVjd3XxT8Gv6TtRASa2U4/v/xFR99REZVOqq8tPSQT5b521y1tTBJaTKxB23KwsVuONGlSM8ZH0PiPkjuRmZsfp9aVqpWVSfBMZFqw4+XYbQdImYgzqkq/vgaZ7ApxW0ICzjtIiJ0x/15o+rOFQhMh6+9kSGq4OhjfzY8ZRqTyFQ2dy2SRF+tQKD87bTJUrDkf9mRXbvK+xpDrPpT7dMgTj0R6yjrwJpRt6LcimMv+LvSjbKvAG6KFxn6UMfWVi8bkFM/hzvwRJe/aoyPbYQ72lFMHeYreJNaAKYpO8CBF9mi5KbDDXYNtaoEgUVVukppYbS/wVpdQwlC7J85A9yLmelDEufSbz/RVOwv2LZKHsk6iFgaV4U74YrYiwIT4xE8znliw4xnOd6j+MCBdcmMvOyGKUeNrD7Q042c6Pn5QPGchkmmPuhqwrcnRXYiYEOyMs4LnsdhKSxJk4Q2yoc9b6Fhb8RQbUARzbTfAw9L/ZgooZ2tVhFFJnCFhkU4U76twoB1plg3L2KEAH4smtZjVh0k8uoaDt9JQOk/K5YaKiAI3TPB6AlsaDLguQClqyRsK04OyO/CZkoPsvLoGa1EyBpppKcwOe3PyF4zYuNEQRRZh48L/5loWJPf+ynWj1fR+NcVnTqe8GqFk0vP3uK5C8FaJxKP3a0bekr0tKCfe4yxte4Ej8yo/3plnDz03GXUB+FgsdMINm3rA2UhTNdYjRJtIRNJomCkjQr7GHyEsTq71Q6O0wuOSet0byPcLPPhcXzsSqpWYZ9+opORXE92LCwuHJRZOtuzpjvAphi0kiCRk4dSR0VP8FmL5yNG2M2okeEb8bjXD52ErTBTIAk3VZnh4OOCSfzgpZhoEvr5usjkfyry9BmgX2gWAJYRTUrEgDTXHj5YQ6MT3grfDGYMqKoy7GSpb3tY5zBHzzoJDK/E1VvO+ScyQaJQJ0eHgsgy2QZbCnEB3W4N5M8HqBqNMw+0oUvqw0P1i4uK9XwCGzVyyOXs1czCsWGg8R8Ej51AL+9gXdu7RMdEaP2lTMkOJfScJbzsOkfjxvX5LBrHVZ98XuzZylbeFkVr/gjrvBnfucL9zCmjngYq4RfzDYBOzx31gRuFFAsllK4zFRgtHWSXGXwXim4OJpMVKEuFHO5Oupowvd9cdzRIjGpWzR0=";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/");
#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/");
#endif
WString output_directory = output_path + L"barcode/";

class SdkLibMgr {
public:
  SdkLibMgr() : isInitialize(false){};
  ErrorCode Initialize() {
    ErrorCode error_code = Library::Initialize(sn, key);
    if (error_code != foxit::e_ErrSuccess) {
      printf("Library Initialize Error: %d\n", error_code);
    } else {
      isInitialize = true;
    }
    return error_code;

  }
  ~SdkLibMgr(){
    if(isInitialize)
      Library::Release();
  }
private:
  bool isInitialize;
};

void Save2Image(Bitmap& bitmap, WString bmp_name)
{
  // Add the bitmap to image and save the image.
  Image image;
  image.AddFrame(bitmap);

  WString filepath = output_directory + bmp_name;
  image.SaveAs(filepath);
}

// Generate barcode in different type and save each of them as an image file.
void Barcode_GenerateEachType(WString code_string, Barcode::Format code_format, int unit_width, int unit_height, Barcode::QRErrorCorrectionLevel qr_level, WString bmp_name)
{
  Barcode barcode;
  Bitmap bitmap = barcode.GenerateBitmap(code_string, code_format, unit_width, unit_height, qr_level);

  Save2Image(bitmap, bmp_name);
}

// Generate all types of barcode and save each of them as an image file.
void Barcode_GenerateAll( )
{
  // Strings used as barcode content.
  WString sz_code_string[8] = {L"TEST-SHEET", L"102030405060708090", L"80674313", L"890444000335", L"9780804816632", L"070429", L"Unknown - change me!", L"TestForBarcodeQrCode"};
  // Barcode format types
  Barcode::Format code_format[8] = {Barcode::e_FormatCode39, Barcode::e_FormatCode128,
    Barcode::e_FormatEAN8, Barcode::e_FormatUPCA, 
    Barcode::e_FormatEAN13, Barcode::e_FormatITF, 
    Barcode::e_FormatPDF417, Barcode::e_FormatQRCode};

  // Image names for the saved image files.(except QR code)
  WString sz_bmp_name[7] = {L"/code39_TEST-SHEET.bmp", L"/CODE_128_102030405060708090.bmp",
    L"/EAN_8_80674313.bmp", L"/UPC_A_890444000335.bmp", L"/EAN_13_9780804816632.bmp",
    L"/ITF_070429.bmp", L"/PDF_417_Unknown.bmp"};

  //Format error correction level of QR code.
  Barcode::QRErrorCorrectionLevel sz_qr_level[4] = {Barcode::e_QRCorrectionLevelLow, Barcode::e_QRCorrectionLevelMedium, 
    Barcode::e_QRCorrectionLevelQuater, Barcode::e_QRCorrectionLevelHigh};
  //Image names for the saved image files for QR code.
  WString bmp_qr_name[4] = {L"/QR_CODE_TestForBarcodeQrCode_L.bmp", L"/QR_CODE_TestForBarcodeQrCode_M.bmp",
    L"/QR_CODE_TestForBarcodeQrCode_Q.bmp", L"/QR_CODE_TestForBarcodeQrCode_H.bmp"};

  // Unit width for barcode in pixels, preferred value is 1-5 pixels.
  int unit_width = 2;
  // Unit height for barcode in pixels, preferred value is >= 20 pixels.
  int unit_height = 120;

  // Generate barcode for different types.
  for (int i = 0; i < 8; i++)
  {
    if (code_format[i] != Barcode::e_FormatQRCode) {
      // Not QR code
      Barcode_GenerateEachType(sz_code_string[i], code_format[i], unit_width, unit_height, (Barcode::QRErrorCorrectionLevel)0, sz_bmp_name[i]);
    } else {
      // QR code
      //Generate for each format error correction level.
      for (int j = 0; j < 4; j++)
        Barcode_GenerateEachType(sz_code_string[i], code_format[i], unit_width, unit_height, sz_qr_level[j], bmp_qr_name[j]);
    }
  }

}
int main(int argc, char *argv[])
{
  int err_ret = 0;

#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  SdkLibMgr spSdkLibMgr;
  // Initialize library.
  ErrorCode error_code = spSdkLibMgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    // Generate all types of barcode
    Barcode_GenerateAll();
    cout << "Barcode demo." << endl;

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