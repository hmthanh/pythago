// Copyright (C) 2003-2020, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to loading PDF document asynchronously.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/common/fs_render.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;

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

// Data of asynchronous loader callback object.
struct DownloadHintDataInfo {
  DownloadHintDataInfo() {
    offset = 0;
    size = 0;
    is_downloaded = false;
  }
  DownloadHintDataInfo(int64 offset, int64 size, bool is_downloaded) {
    this->offset = offset;
    this->size = size;
    this->is_downloaded = is_downloaded;
  }
  int64 offset;
  int64 size;
  bool is_downloaded;
};

// This callback just simulates the downloading progress by DownloadHintDataInfo::is_downloaded,
// not really to download data.
class AsyncFileRead : public foxit::common::file::AsyncReaderCallback {
public:
  AsyncFileRead()
    : file_(NULL)
    , is_large_file_(false) {}

  ~AsyncFileRead() {
    hint_data_record_.clear();
  }

  bool LoadFile(const wchar_t* file_path, bool is_large_file = false) {
#if defined(_WIN32) || (_WIN64)
    fopen_s(&file_, String::FromUnicode(file_path), "rb");
#else
    file_ = fopen(String::FromUnicode(file_path), "rb");
#endif
    if (!file_)
      return false;

    is_large_file_ = is_large_file;
    return true;
  }

  FILESIZE GetSize() {
    if (is_large_file_) {
#if defined(_WIN32) || defined(_WIN64)
      _fseeki64(file_, 0, SEEK_END);
      long long size_long = _ftelli64(file_);
#elif defined(__linux__) || defined(__APPLE__)
      fseeko(file_, 0, SEEK_END);
      long long size_long = ftello(file_);
#endif
      return size_long;
    } else {
      fseek(file_, 0, SEEK_END);
      return (int64)ftell(file_);
    }
    return 0;
  }

  FX_BOOL      ReadBlock(void* buffer, FILESIZE offset, size_t size) {
    if (is_large_file_) {
#if defined(_WIN32) || defined(_WIN64)
      _fseeki64(file_, offset, SEEK_SET);
#elif defined(__linux__) || defined(__APPLE__)
      fseeko(file_, offset, SEEK_SET);
#endif
      long long read_size = fread(buffer, 1, size, file_);
      return read_size == size ? true : false;
    } else {
      if (!file_)
        return false;
      if (0 != fseek(file_, static_cast<long>(offset), 0))
        return false;
      if (0 == fread(buffer, size, 1, file_))
        return false;
      return true;
    }
    return false;
  }

  void Release() {
    if (file_)
      fclose(file_);
    file_ = NULL;
    delete this;
  }

  virtual bool IsDataAvail(int64 offset, size_t size) {
    return CheckRecordDownloaded(offset, size, false);
  }
  virtual bool AddDownloadHint(int64 offset, size_t size) {
    // Record the range and downloaded data.
    return CheckRecordDownloaded(offset, size, true);
  }

protected:
  bool CheckRecordDownloaded(int64 offset, int64 size, bool to_download) {
    size_t record_count = hint_data_record_.size();
    for (size_t i = 0; i < record_count; i++) {
      DownloadHintDataInfo data_info = hint_data_record_[i];

      // If (offset+size) is out of current data_info, just continue to check other record in hint_data_record_.
      if (offset > (data_info.offset + data_info.size))
        continue;
      if (offset + size < data_info.offset)
        continue;

      // If data defined by <offset, size> has been in/within current data info, just download the data.
      if (offset >= data_info.offset && (offset + size) <= (data_info.offset + data_info.size)) {
        if (to_download)
          data_info.is_downloaded = true;
        return data_info.is_downloaded;
      }

      // If only part of data defined by <offset, size> is in current data_info, download current data_info and
      // also check and download rest data.
      if (offset >= data_info.offset && offset < (data_info.offset + data_info.size) &&
        (offset + size) > (data_info.offset + data_info.size)) {
          if (to_download)
            data_info.is_downloaded = true;
          if (!data_info.is_downloaded)
            return data_info.is_downloaded;
          int64 new_offset = data_info.offset + data_info.size + 1;
          int64 new_size = size - 1 - (data_info.offset + data_info.size - offset);
          return CheckRecordDownloaded(new_offset, new_size, to_download);
      }

      if (offset < data_info.offset && (offset + size) >= data_info.offset &&
        (offset + size) <= (data_info.offset + data_info.size)) {
          if (to_download)
            data_info.is_downloaded = true;
          if (!data_info.is_downloaded)
            return data_info.is_downloaded;
          int64 new_offset = offset;
          int64 new_size = data_info.offset - 1 - offset;
          return CheckRecordDownloaded(new_offset, new_size, to_download);
      }
      if (offset < data_info.offset && (offset + size) > (data_info.offset + data_info.size)) {
        if (to_download)
          data_info.is_downloaded = true;
        if (!data_info.is_downloaded)
          return data_info.is_downloaded;
        int64 new_offset = offset;
        int64 new_size = data_info.offset - 1 - offset;
        if (CheckRecordDownloaded(new_offset, new_size, to_download)) {
          new_offset = data_info.offset + data_info.size + 1;
          new_size = size - 1 - (data_info.offset - offset + data_info.size);
          return CheckRecordDownloaded(new_offset, new_size, to_download);
        } else
          return false;
      }
    }
    if (to_download) {
      return DownloadData(offset, size);
    }
    return false;
  }
  bool DownloadData(int64 offset, int64 size) {
    DownloadHintDataInfo new_info(offset, size, true);
    hint_data_record_.push_back(new_info);
    return true;
  }

private:
  // Used to record added hint range and if the range is downloaded.
  std::vector<DownloadHintDataInfo> hint_data_record_;
  FILE* file_;
  bool is_large_file_;
};

int main(int argc, char *argv[])
{
  int err_ret = 0;

  WString input_file = input_path + L"AboutFoxit.pdf";
  WString output_directory = output_path + L"async_load/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  WString output_file = output_directory + L"page0.bmp";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {

    AsyncFileRead* file_read = new AsyncFileRead();
    file_read->LoadFile(input_file);
    PDFDoc doc(file_read, true);

    // Actually, here, application should download needed data which specified by AsyncFileRead::AddDownloadHint().
    // But here, for simple example, we just "download" these data inside AsyncFileRead::AddDownloadHint().
    // So, just continue to check the ready state here, which will trigger AsyncFileRead::AddDownloadHint() to
    // "download" data.
    ErrorCode code = foxit::e_ErrDataNotReady;
    while (code == foxit::e_ErrDataNotReady)
      code = doc.Load();
    if (code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }

    // Actually, here, application should download needed data which specified by AsyncFileRead::AddDownloadHint().
    // But here, for simple example, we just "download" these data inside AsyncFileRead::AddDownloadHint().
    // So, just continue to check the ready state here, which will trigger AsyncFileRead::AddDownloadHint() to
    // "download" data.
    PDFPage page;
    code = foxit::e_ErrDataNotReady;
    while (code == foxit::e_ErrDataNotReady) {
      try {
        page = doc.GetPage(0);
        break;
      }
      catch (Exception e) {
        code = e.GetErrCode();
      }
      catch (...) {
        throw;
      }
    }
    // Parse page.
    page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

    int width = static_cast<int>(page.GetWidth());
    int height = static_cast<int>(page.GetHeight());
    foxit::Matrix matrix = page.GetDisplayMatrix(0, 0, width, height, page.GetRotation());

    // Prepare a bitmap for rendering.
    foxit::common::Bitmap bitmap(width, height, foxit::common::Bitmap::e_DIBArgb, NULL, 0);
    bitmap.FillRect(0xFFFFFFFF, NULL);
    // Render page
    foxit::common::Renderer render(bitmap, false);
    render.StartRender(page, matrix, NULL);

    foxit::common::Image image;
    image.AddFrame(bitmap);
    image.SaveAs(output_file);

    cout << "async-load demo finished." << endl;

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

