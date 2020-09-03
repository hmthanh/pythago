//#include "PDFReader/Source/stdafx.h"
#include "PDFReader/Source/util.h"

static const char* kErrorMessage[] = {
  "Success, and no error occurs.",
  "File error: file cannot be found or could not be opened",
  "Format error: format is invalid. For files, this may also mean that file is corrupted.",
  "Password error: invalid password.",
  "Error handle.",
  "Certificate error: PDF document is encrypted by digital certificate and current user does not have the \
  correct certificate.",
  "Unknown error: any unknown error occurs.",
  "License error: invalid license is used to initialize Foxit PDF SDK library.",
  "Parameter error: value of any input parameter for a function is invalid.",
  "Unsupported error: some types are not supported.",
  "Memory error: out-of-memory error occurs.",
  "Security handler error: PDF document is encrypted by some unsupported security handler.",
  "Not parsed error: content has not been parsed yet. Usually, this represents PDF page has not been parsed \
  yet.",
  "Not found error: expected data or object is not found.",
  "Invalid type error: the type of input object or current object is invalid.",
  "Conflict error: new data conflicts with existed data.",
  "Unknown state error: any unknown state occurs.",
  "Data not ready error: data is not ready yet. Usually, this may occur when the PDF document is loaded by \
  using asynchronous loader handler and it represents application has not download enough PDF document \
  data yet."
  "Invalid data error: data of current object is invalid."
  "XFA loading error."
  "Noe loaded erorr: current object has not been loaded yet"
  "Invalid state error: invalid or incorrect state."
};

const char* GetErrorMessage(foxit::ErrorCode error_code) {
  int error_index = error_code;
  if (error_code > sizeof(kErrorMessage) / sizeof(kErrorMessage[0]) || error_code < 0)
    error_index = 0;
  return kErrorMessage[error_index];
}

bool IsAnnotSupportedToChangeProperty(Annot annot) {
  Annot::Type annot_type = annot.GetType();
  switch(annot_type) {
    case Annot::e_Note:
    case Annot::e_Highlight:
    case Annot::e_Underline:
    case Annot::e_StrikeOut:
    case Annot::e_Squiggly:
    case Annot::e_Link:
    case Annot::e_Square:
    case Annot::e_Circle:
    case Annot::e_FreeText:
    case Annot::e_Stamp:
    case Annot::e_Caret:
    case Annot::e_Ink:
    case Annot::e_Line:
    case Annot::e_Polygon:
    case Annot::e_PolyLine:
    case Annot::e_FileAttachment:
    case Annot::e_Popup:
    case Annot::e_Widget:
    case Annot::e_Screen:
      return true;
    default:
      return false;
  }
}

bool IsAnnotRelatedToField(Annot annot, bool only_check_signature/* = false*/) {
  if (Annot::e_Widget == annot.GetType()) {
    Field field = ((annots::Widget)annot).GetField();
    if (field.IsEmpty()) return false;
    if (only_check_signature) {
      if (field.GetType() == Field::e_TypeSignature)
        return true;
      else
        return false;
    } else {
      return true;
    }
  }
  return false;
}

