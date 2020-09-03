#pragma once

#pragma warning(disable : 4996)
#pragma warning(disable : 4290)

#include "common/fs_basictypes.h"
#include "common/fs_common.h"
#include "common/fs_image.h"
#include "common/fs_render.h"

#include "pdf/annots/fs_annot.h"
#include "pdf/interform/fs_pdfform.h"
#include "pdf/interform/fs_formfiller.h"
#include "pdf/fs_bookmark.h"
#include "pdf/fs_filespec.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/fs_pdfdocviewerprefs.h"
#include "pdf/fs_pdfpage.h"
#include "pdf/fs_pdfpagelabel.h"
#include "pdf/fs_pdfmetadata.h"
#include "pdf/fs_search.h"
#include "pdf/fs_ltvverifier.h"

#include "addon/xfa/fs_xfa.h"

#include "fs_actioncallback.h"

#include "PDFReader/Source/util.inc"

#include <vector>

using namespace foxit::common;
using namespace foxit::common::file;
using namespace foxit::pdf;
using namespace foxit::pdf::actions;
using namespace foxit::pdf::annots;
using namespace foxit::pdf::interform;
using namespace foxit::addon::xfa;

#define DEFAULT_PAGESPACE 6
static const float kDefaultMaxZoomFactor = 640;
static const float kDefaultMinZoomFactor = 0.25;

// Get error message by error code.
const char* GetErrorMessage(foxit::ErrorCode err_code);

bool IsAnnotSupportedToChangeProperty(Annot annot);

bool IsAnnotRelatedToField(Annot annot, bool only_check_signature = false);

