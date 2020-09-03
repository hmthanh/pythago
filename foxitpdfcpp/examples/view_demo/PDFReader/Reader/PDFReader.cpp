
// PDFReader.cpp : Defines the class behaviors for the application.
//

#include <io.h>
#include <fcntl.h>

#include "PDFReader/Source/Stdafx.h"

#include "PDFReader/Reader/StartInterfaceDlg.h"
#include "PDFReader/Reader/PDFReader.h"
#include "PDFReader/Reader/MainFrm.h"
#include "PDFReader/Reader/PDFReaderDoc.h"
#include "PDFReader/Reader/PDFReaderView.h"

#include "afxwinappex.h"
#include "afxdialogex.h"
#include "afxeditbrowsectrl.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// The implementation of class ActionHandler
void ActionHandler::Release() {
  delete this;
}

int ActionHandler::GetCurrentPage(const PDFDoc& pdfDoc){
  return 0;
}

void ActionHandler::SetCurrentPage(const PDFDoc& pdfDoc, int pageIndex){}

Rotation ActionHandler::GetPageRotation(const PDFDoc& pdfDoc, int pageIndex) {
  return e_Rotation0;
}

bool ActionHandler::SetPageRotation(const PDFDoc& pdfDoc, int pageIndex, Rotation rotation) {
  return FALSE;
}

bool ActionHandler::InvalidateRect(const PDFDoc& pdfDoc, int pageIndex, const foxit::RectF& pdfRect) {
    CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
    CPDFReaderView *pView = (CPDFReaderView *)pMain->GetActiveView();

    CRect rect;
    pView->DocToWindow(pageIndex, pdfRect, rect);
    pView->InvalidateRect(rect, FALSE);
    return true;
}

bool ActionHandler::ExecuteNamedAction(const PDFDoc& pdfDoc, const char* namedAction) {
  return FALSE;
}

bool ActionHandler::SetDocChangeMark(const PDFDoc& pdfDoc, bool changeMark) {
    CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
    CPDFReaderView *pView = (CPDFReaderView *)pMain->GetActiveView();
    if (pView) pView->GetDocument()->SetModifiedFlag(changeMark ? TRUE : FALSE);
    return true;
}

bool ActionHandler::GetDocChangeMark(const PDFDoc& pdfDoc) {
  return FALSE;
}

int ActionHandler::GetOpenedDocCount() {
  return 1;
}

PDFDoc ActionHandler::GetOpenedDoc(int index) {
  return PDFDoc();
}

bool ActionHandler::Beep(int nType) {
  CString funname(_T("Beep\n\n"));
  CString strType;
  switch (nType)
  {
  case 0:
    strType = _T("Error");
    break;
  case 1:
    strType = _T("Warning");
    break;
  case 2:
    strType = _T("Question");
    break;
  case 3:
    strType = _T("Status");
    break;
  case 4:
    strType = _T("Default");
    break;
  default:
    strType = _T("not defined");
  }
  CString str = funname + strType;

  AfxMessageBox(str);
  return TRUE;
}

foxit::WString ActionHandler::Response(const wchar_t* question, const wchar_t* title, const wchar_t* defaultValue,
  const wchar_t* label, bool isPassword) {
  return L"response";
}

foxit::WString ActionHandler::GetFilePath(const PDFDoc& pdfDoc) {
  return L"getFilePath";
}

bool ActionHandler::Print(const PDFDoc& pdfDoc, bool isUI, const Range& page_set, bool isSilent ,
  bool isShrinkToFit, bool isPrintAsImage, bool isReverse, bool isAnnotations) {
  return TRUE;
}

bool ActionHandler::SubmitForm(const PDFDoc& pdfDoc, void* formData, foxit::uint32 length, const char* URL) {
  std::wstring strURL((const wchar_t*)foxit::WString::FromLocal(URL));
  std::wstring funname(_T("SubmitForm URL\n\n"));
  std::wstring str = funname + strURL;
  AfxMessageBox(str.c_str());
  return TRUE;
}

bool ActionHandler::LaunchURL(const char* URL) {
  std::wstring strURL((const wchar_t*)foxit::WString::FromLocal(URL));
  std::wstring str = _T("LaunchURL\n\n") + strURL;
  AfxMessageBox(str.c_str());

  return TRUE;
}

foxit::WString ActionHandler::BrowseFile() {
  return L"";
}

foxit::ActionCallback::Language ActionHandler::GetLanguage() {
  return e_LanguageCHS;
}

int ActionHandler::Alert(const wchar_t* msg, const wchar_t* title, int type, int icon) {
  if (2 == type) type = MB_YESNO;
  int ret = AfxMessageBox(msg, type);
  if (IDYES == ret)
    return 4;
  return 0;
}

foxit::IdentityProperties  ActionHandler::GetIdentityProperties() {
  return foxit::IdentityProperties(L"Blanc&Eclare", L"miao@neko.com", L"Sooyoen", L"Jessica");
}

foxit::WString ActionHandler::PopupMenu(const foxit::MenuListArray& menus) {
  return L"popupMenu";
}

foxit::WString ActionHandler::GetAppInfo(AppInfoType type) {
  wchar_t* info = NULL;
  switch(type)
  {
  case foxit::ActionCallback::e_AppInfoTypeFormsVersion:
    info = L"7.3";
    break;
  case foxit::ActionCallback::e_AppInfoTypeViewerType:
    info = L"foxit sdk ui demo for windows";
    break;
  case foxit::ActionCallback::e_AppInfoTypeViewerVariation:
    info = L"full expired";
    break;
  case foxit::ActionCallback::e_AppInfoTypeViewerVersion:
    info = L"6.5";
    break;
  case foxit::ActionCallback::e_AppInfoTypeAppVersion:
    info = L"5.6";
    break;
  }

  return info;
}

bool ActionHandler::MailData(void* data, MailType dataType, bool bUI, const wchar_t* wsTo,
  const wchar_t* wsSubject, const wchar_t* wsCC, const wchar_t* wsBCC, const wchar_t* wsMsg) {
  CString csMessage;
  switch(dataType) {
    case foxit::ActionCallback::e_MailTypeDoc:
      csMessage = L"call MailData() to mail doc";
      break;
    case foxit::ActionCallback::e_MailTypeForm:
      csMessage = L"call MailData() to mail form";
      break;
    case foxit::ActionCallback::e_MailTypeMsg:
      csMessage = L"call MailData() to mail msg";
      break;
  }

  CString csTemp;
  csTemp.Format(L"\n%s\t:\t%s", L"To", wsTo);
  csMessage.Append(csTemp);
  csTemp.Format(L"\n%s\t:\t%s", L"Subject", wsSubject);
  csMessage.Append(csTemp);
  csTemp.Format(L"\n%s\t:\t%s", L"CC", wsCC);
  csMessage.Append(csTemp);
  csTemp.Format(L"\n%s\t:\t%s", L"BCC", wsBCC);
  csMessage.Append(csTemp);
  csTemp.Format(L"\n%s\t:\t%s", L"Msg", wsMsg);
  csMessage.Append(csTemp);

  AfxMessageBox(csMessage);
  return TRUE;
}

foxit::uint32 ActionHandler::VerifySignature(const PDFDoc& document, const Signature& pdf_signature) {
  // Here's a simple sample about verifying a signature by LTVVerifier.
  LTVVerifier ltv_verifier(document, true, true, false, LTVVerifier::e_SignatureCreationTime);
  ltv_verifier.SetVerifyMode(LTVVerifier::e_VerifyModeAcrobat);
  SignatureVerifyResultArray sig_verify_result_array = ltv_verifier.VerifySignature(pdf_signature);
  foxit::uint32 state = sig_verify_result_array[0].GetSignatureState();
  return state;
}

// The implementation of class XFAAppProviderHandler
void XFAAppProviderHandler::Release() {
  delete this;
}

foxit::WString XFAAppProviderHandler::GetAppInfo(AppInfo app_info) {
  switch(app_info) {
  case AppProviderCallback::e_AppInfoVersion:
    return L"11.0";
  case AppProviderCallback::e_AppInfoType:
    return L"Exchange-Pro";
  case AppProviderCallback::e_AppInfoLanguage:
    return L"en-US";
  case AppProviderCallback::e_AppInfoPlatform:
    return L"WIN";
  case AppProviderCallback::e_AppInfoName:
    return L"Acrobat";
  case AppProviderCallback::e_AppInfoVariation:
    return L"Full";
  default:
    break;
  }
  return L"";
}

void XFAAppProviderHandler::Beep(BeepType type) {
  CString funname(_T("XFA Beep\n\n"));
  CString strType;
  switch (type)
  {
  case AppProviderCallback::e_BeepTypeError:
    strType = _T("Error");
    break;
  case AppProviderCallback::e_BeepTypeWarning:
    strType = _T("Warning");
    break;
  case AppProviderCallback::e_BeepTypeQuestion:
    strType = _T("Question");
    break;
  case AppProviderCallback::e_BeepTypeStatus:
    strType = _T("Status");
    break;
  case AppProviderCallback::e_BeepTypeDefault:
    strType = _T("Default");
    break;
  default:
    strType = _T("not defined");
  }
  CString str = funname + strType;

  AfxMessageBox(str);
  return;
}

AppProviderCallback::MsgBoxButtonID XFAAppProviderHandler::MsgBox(const wchar_t* message, const wchar_t* title /* = NULL */, MsgBoxIconType icon_type /* = e_MsgBoxIconError */, MsgBoxButtonType button_type /* = e_MsgBtnTypeOK */) {
  CString strMessage;
  strMessage.Format(_T("%s"), message);
  return (MsgBoxButtonID)AfxMessageBox(strMessage);
}

foxit::WString XFAAppProviderHandler::Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_answer /* = NULL */, bool is_mask /* = TRUE */) {
  CString strMessage;
  strMessage.Format(_T("question: %s\r\ntitle:%s\r\ndefault_answer:%s\r\nis mask:%d"), question, title, default_answer, is_mask);
  AfxMessageBox(strMessage);
  return L"answer";
}

ReaderCallback* XFAAppProviderHandler::DownLoadUrl(const wchar_t* url) {
  CString str;
  str.Format(_T("%s"), url);

  AfxMessageBox(_T("DownLoadUrl") + str);
  return NULL;
}

foxit::WString XFAAppProviderHandler::PostRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* content_type, const wchar_t* encode, const wchar_t* header) {
  return L"PostRequestUrl";
}

bool XFAAppProviderHandler::PutRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* encode) {
  return TRUE;
}

foxit::WString XFAAppProviderHandler::LoadString(StringID string_id) {
  wchar_t* wsString = L"";
  switch (string_id)
  {
  case AppProviderCallback::e_StringIDValidateFailed:
    wsString = L"%s validate failed";
    break;
  case AppProviderCallback::e_StringIDCalcOverride:
    wsString = L"Calculate Override";
    break;
  case AppProviderCallback::e_StringIDModifyField:
    wsString = L"Are you sure you want to modify this field?";
    break;
  case AppProviderCallback::e_StringIDNotModifyField:
    wsString = L"You are not allowed to modify this field.";
    break;
  case AppProviderCallback::e_StringIDAppName:
    wsString = L"Foxit SDK";
    break;
  case AppProviderCallback::e_StringIDImageFilter:
    wsString = L"Image Files(*.bmp;*.jpg;*.png;*.gif;*.tif)|*.bmp;*.jpg;*.png;*.gif;*.tif|All Files(*.*)|*.*||";
    break;
  case AppProviderCallback::e_StringIDUnknownCaught:
    wsString = L"unknown error is catched!";
    break;
  case AppProviderCallback::e_StringIDUnableToSet:
    wsString = L"Unable to set ";
    break;
  case AppProviderCallback::e_StringIDValueExcalmatory:
    wsString = L" value!";
    break;
  case AppProviderCallback::e_StringIDInvalidEnumValue:
    wsString = L"Invalid enumerated value: ";
    break;
  case AppProviderCallback::e_StringIDUnsupportMethod:
    wsString = L"Unsupport %s method.";
    break;
  case AppProviderCallback::e_StringIDUnsupportProperty:
    wsString = L"Usupport %s property.";
    break;
  case AppProviderCallback::e_StringIDInvalidPropertySetOperation:
    wsString = L"Invalid property set operation;";
    break;
  case AppProviderCallback::e_StringIDNotDefaultValue:
    wsString = L" doesn't have a default property";
    break;
  case AppProviderCallback::e_StringIDUnableSetLanguage:
    wsString = L"Unable to set language value!";
    break;
  case AppProviderCallback::e_StringIDUnableSetNumPages:
    wsString = L"Unable to set numPages value!";
    break;
  case AppProviderCallback::e_StringIDUnableSetPlatformValue:
    wsString = L"Unable to set platform value!";
    break;
  case AppProviderCallback::e_StringIDUnableSetValidationsEnabledValue:
    wsString = L"Unable to set validationsEnabled value!";
    break;
  case AppProviderCallback::e_StringIDUnableSetValidationsValue:
    wsString = L"Unable to set variation value!";
    break;
  case AppProviderCallback::e_StringIDUnableSetVersion:
    wsString = L"Unable to set version value!";
    break;
  case AppProviderCallback::e_StringIDUnableSetReady:
    wsString = L"Unable to set ready value!";
    break;
  case AppProviderCallback::e_StringIDNumberOfOccur:
    wsString = L"The element [%s] has violated its allowable number of occurrences";
    break;
  case AppProviderCallback::e_StringIDUnableSetClassName:
    wsString = L"Unable to set className value!";
    break;
  case AppProviderCallback::e_StringIDUnableSetLengthValue:
    wsString = L"Unable to set length value!";
    break;
  case AppProviderCallback::e_StringIDUnsupportChar:
    wsString = L"unsupported char '%c'";
    break;
  case AppProviderCallback::e_StringIDBadSuffix:
    wsString = L"bad suffix on number";
    break;
  case AppProviderCallback::e_StringIDExpectedIdent:
    wsString = L"expected identifier instead of '%s'";
    break;
  case AppProviderCallback::e_StringIDExpectedString:
    wsString = L"expected '%s' instead of '%s'";
    break;
  case AppProviderCallback::e_StringIDInvalidateChar:
    wsString = L"invalidate char '%c'";
    break;
  case AppProviderCallback::e_StringIDRedefinition:
    wsString = L"'%s' redefinition ";
    break;
  case AppProviderCallback::e_StringIDInvalidToken:
    wsString = L"invalidate token '%s'";
    break;
  case AppProviderCallback::e_StringIDInvalidExpression:
    wsString = L"invalidate expression '%s'";
    break;
  case AppProviderCallback::e_StringIDUndefineIdentifier:
    wsString = L"undefined identifier '%s'";
    break;
  case AppProviderCallback::e_StringIDInvalidateLeftValue:
    wsString = L"invalidate left-value '%s'";
    break;
  case AppProviderCallback::e_StringIDCompilerError:
    wsString = L"compiler error";
    break;
  case AppProviderCallback::e_StringIDCannotModifyValue:
    wsString = L"can't modify the '%s' value";
    break;
  case AppProviderCallback::e_StringIDParametersError:
    wsString = L"function '%s' has not %d parameters";
    break;
  case AppProviderCallback::e_StringIDExpectedEndIf:
    wsString = L"expected 'endif' instead of '%s'";
    break;
  case AppProviderCallback::e_StringIDUnexpectedExpression:
    wsString = L"unexpected expression '%s'";
    break;
  case AppProviderCallback::e_StringIDConditionIsNull:
    wsString = L"condition is null";
    break;
  case AppProviderCallback::e_StringIDIllegalBreak:
    wsString = L"illegal break";
    break;
  case AppProviderCallback::e_StringIDIllegalContinue:
    wsString = L"illegal continue";
    break;
  case AppProviderCallback::e_StringIDExpectedOperator:
    wsString = L"expected operator '%s' instead of '%s'";
    break;
  case AppProviderCallback::e_StringIDDivideZero:
    wsString = L"divide by zero";
    break;
  case AppProviderCallback::e_StringIDCannotCovertToObject:
    wsString = L"%s.%s can not covert to object";
    break;
  case AppProviderCallback::e_StringIDNotFoundContainer:
    wsString = L"can not found container '%s'";
    break;
  case AppProviderCallback::e_StringIDNotFoundProperty:
    wsString = L"can not found property '%s'";
    break;
  case AppProviderCallback::e_StringIDNotFoundMethod:
    wsString = L"can not found method '%s'";
    break;
  case AppProviderCallback::e_StringIDNotFoundConst:
    wsString = L"can not found const '%s'";
    break;
  case AppProviderCallback::e_StringIDNotAssignObject:
    wsString = L"can not direct assign value to object";
    break;
  case AppProviderCallback::e_StringIDInvalidateInstruction:
    wsString = L"invalidate instruction";
    break;
  case AppProviderCallback::e_StringIDExpectedNumber:
    wsString = L"expected number instead of '%s'";
    break;
  case AppProviderCallback::e_StringIDValidateOutOfArray:
    wsString = L"validate access index '%s' out of array";
    break;
  case AppProviderCallback::e_StringIDCannotAssign:
    wsString = L"can not assign to %s";
    break;
  case AppProviderCallback::e_StringIDNotFoundFunction:
    wsString = L"can not found '%s' function";
    break;
  case AppProviderCallback::e_StringIDIsNotArray:
    wsString = L"'%s' doesn't an array";
    break;
  case AppProviderCallback::e_StringIDOutOfArrayRange:
    wsString = L"out of range of '%s' array";
    break;
  case AppProviderCallback::e_StringIDNotSupportArrayCalculate:
    wsString = L"'%s' operator can not support array calculate";
    break;
  case AppProviderCallback::e_StringIDArgumentNotArray:
    wsString = L"'%s' function's %d argument can not be array";
    break;
  case AppProviderCallback::e_StringIDArgumentExpectContainer:
    wsString = L"'%s' argument expected a container";
    break;
  case AppProviderCallback::e_StringIDAccessProertyInNotObject:
    wsString = L"an attempt was made to reference property '%s' of a non-object in SOM expression %s";
    break;
  case AppProviderCallback::e_StringIDFunctionBuildIn:
    wsString = L"function '%s' is buildin";
    break;
  case AppProviderCallback::e_StringIDErrorMessage:
    wsString = L"%s : %s";
    break;
  case AppProviderCallback::e_StringIDIndexValueOutOfBounds:
    wsString = L"Index value is out of bounds";
    break;
  case AppProviderCallback::e_StringIDIncorrectNumberOfMethod:
    wsString = L"Incorrect number of parameters calling method '%s'";
    break;
  case AppProviderCallback::e_StringIDArgumentMismatch:
    wsString = L"Argument mismatch in property or function argument";
    break;
  case AppProviderCallback::e_StringIDInvalidEnumerate:
    wsString = L"Invalid enumerated value: %s";
    break;
  case AppProviderCallback::e_StringIDInvalidAppend:
    wsString = L"Invalid append operation: %s cannot have a child element of %s";
    break;
  case AppProviderCallback::e_StringIDSOMExpectedList:
    wsString = L"SOM expression breaked list when single result was expected";
    break;
  case AppProviderCallback::e_StringIDNotHaveProperty:
    wsString = L"'%s' doesn't have property '%s'";
    break;
  case AppProviderCallback::e_StringIDInvalidNodeType:
    wsString = L"Invalid node type : '%s'";
    break;
  case AppProviderCallback::e_StringIDViolateBoundary:
    wsString = L"The element [%s] has violated its allowable number of occurrences";
    break;
  case AppProviderCallback::e_StringIDServerDeny:
    wsString = L"Server does not permit";
    break;
  case AppProviderCallback::e_StringIDWeekDaySun:
    wsString = L"Sunday";
    break;
  case AppProviderCallback::e_StringIDWeekDayMon:
    wsString = L"Monday";
    break;
  case AppProviderCallback::e_StringIDWeekDayTue:
    wsString = L"Tuesday";
    break;
  case AppProviderCallback::e_StringIDWeekDayWed:
    wsString = L"Wednesday";
    break;
  case AppProviderCallback::e_StringIDWeekDayThu:
    wsString = L"Thursday";
    break;
  case AppProviderCallback::e_StringIDWeekDayFri:
    wsString = L"Friday";
    break;
  case AppProviderCallback::e_StringIDWeekDaySat:
    wsString = L"Saturday";
    break;
  case AppProviderCallback::e_StringIDMonthJan:
    wsString = L"January";
    break;
  case AppProviderCallback::e_StringIDMonthFeb:
    wsString = L"February";
    break;
  case AppProviderCallback::e_StringIDMonthMarch:
    wsString = L"March";
    break;
  case AppProviderCallback::e_StringIDMonthApril:
    wsString = L"April";
    break;
  case AppProviderCallback::e_StringIDMonthMay:
    wsString = L"May";
    break;
  case AppProviderCallback::e_StringIDMonthJune:
    wsString = L"June";
    break;
  case AppProviderCallback::e_StringIDMonthJuly:
    wsString = L"July";
    break;
  case AppProviderCallback::e_StringIDMonthAug:
    wsString = L"August";
    break;
  case AppProviderCallback::e_StringIDMonthSep:
    wsString = L"September";
    break;
  case AppProviderCallback::e_StringIDMonthOct:
    wsString = L"October";
    break;
  case AppProviderCallback::e_StringIDMonthNov:
    wsString = L"November";
    break;
  case AppProviderCallback::e_StringIDMonthDec:
    wsString = L"December";
    break;
  case AppProviderCallback::e_StringIDToday:
    wsString = L"Today";
    break;
  case AppProviderCallback::e_StringIDValidateLimit:
    wsString = L"Message limit exceeded. Remaining %d validation errors not reported.";
    break;
  case AppProviderCallback::e_StringIDValidateNullWarning:
    wsString = L"%s cannot be left blank. To ignore validations for %s, click Ignore.";
    break;
  case AppProviderCallback::e_StringIDValidateNullError:
    wsString = L"%s cannot be left blank.";
    break;
  case AppProviderCallback::e_StringIDValidateWarning:
    wsString = L"The value you entered for %s is invalid. To ignore validations for %s, click Ignore.";
    break;
  case AppProviderCallback::e_StringIDValidateError:
    wsString = L"The value you entered for %s is invalid.";
    break;
  case AppProviderCallback::e_StringIDValidateNumberError:
    wsString = L"Illegal value:cannot assign '%s' to %s.";
    break;
  case AppProviderCallback::e_StringIDScriptFailedError:
    wsString = L"Script failed(language is %s;context is %s) script=%s ";
    break;
  case AppProviderCallback::e_StringIDScriptInvalidValue:
    wsString = L"Error:Invalid enumerated value:%s";
    break;
  case AppProviderCallback::e_StringIDSubmitValidateNullError:
    wsString = L"At least one required field was empty.Please fill in the required fields(highlighted) before continuing.";
    break;
  }

  return wsString;
}

foxit::WStringArray XFAAppProviderHandler::ShowFileDialog(const wchar_t* string_title, const wchar_t* string_filter, bool is_openfile_dialog) {
  foxit::WStringArray wide_str_array;
  CFileDialog dialog(is_openfile_dialog?TRUE:FALSE, _T(""), NULL, OFN_HIDEREADONLY, string_filter);
  if (dialog.DoModal() == IDOK) {
    CString m_strFilePath = dialog.GetPathName();
    foxit::WString file_path = (wchar_t*)m_strFilePath.AllocSysString();
    wide_str_array.Add(file_path);
  }
  return wide_str_array;
}

// CPDFReaderApp
BEGIN_MESSAGE_MAP(CPDFReaderApp, CWinAppEx)
ON_COMMAND(ID_APP_ABOUT, &CPDFReaderApp::OnAppAbout)
ON_COMMAND(ID_FILE_NEW_FRAME, &CPDFReaderApp::OnFileNewFrame)
ON_COMMAND(ID_FILE_NEW, &CPDFReaderApp::OnFileNew)
// Standard file based document commands
ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
// Standard print setup command
ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()

// CPDFReaderApp construction

CPDFReaderApp::CPDFReaderApp()
    : m_pDocTemplate(NULL)
    , m_bHiColorIcons(TRUE)
    , m_pXFAAppProviderHandler(NULL) {
  // support Restart Manager
  m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
  // If the application is built using Common Language Runtime support (/clr):
  //     1) This additional setting is needed for Restart Manager support to work properly.
  //     2) In your project, you must add a reference to System.Windows.Forms in order to build.
  System::Windows::Forms::Application::SetUnhandledExceptionMode(
      System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

  // TODO: replace application ID string below with unique ID string; recommended
  // format for string is CompanyName.ProductName.SubProduct.VersionInformation
  SetAppID(_T("PDFReader.AppID.NoVersion"));

  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

CPDFReaderApp::~CPDFReaderApp() {

}

void CPDFReaderApp::SetMainFrame(CView * pView) {
  SetMainFrame(pView->GetDocument());
}

void CPDFReaderApp::SetMainFrame(CDocument * pDoc) {
  if (CWnd* pFrame = GetFrameByDoc(pDoc)) {
    m_pMainWnd = pFrame;
  }
}

void CPDFReaderApp::AddFrame(CWnd* frame) {
  m_pFrameArray.Add(frame);
}

void CPDFReaderApp::AddDocument(CDocument * pDoc) {
  m_mapDocToFrame.SetAt(pDoc, m_pFrameArray.GetAt(m_pFrameArray.GetCount() - 1));
}

CWnd* CPDFReaderApp::GetFrameByDoc(CDocument * pDoc) {
  return (CWnd*) m_mapDocToFrame.GetValueAt(pDoc);
}

CDocument* CPDFReaderApp::GetDocByFrame(CWnd * frame) {
  POSITION pos = m_mapDocToFrame.GetStartPosition();
  void* doc = NULL;
  void* value = NULL;
  while (pos) {
    m_mapDocToFrame.GetNextAssoc(pos, doc, value);
    if (value == frame)
      return (CDocument*)doc;
  }
  return NULL;
}

void CPDFReaderApp::RemoveFrame(CWnd* frame) {
  // remove frame and reset main frame.
  int nFind = -1;
  for (int i = 0; i < m_pFrameArray.GetCount(); i++) {
    if (frame == m_pFrameArray[i])
      nFind = i;
  }
  if (nFind == -1)
    return;
  m_pFrameArray.RemoveAt(nFind);
  if (m_pFrameArray.GetCount() > 0) {
    m_pMainWnd = m_pFrameArray.GetAt(0);
  }

  POSITION pos = m_mapDocToFrame.GetStartPosition();
  void* doc = NULL;
  void* value = NULL;
  while (pos) {
    m_mapDocToFrame.GetNextAssoc(pos, doc, value);
    if (value == frame)
      break;
  }
  m_mapDocToFrame.RemoveKey(doc);
}

CRecentFileList* CPDFReaderApp::GetRecentFileList() {
  return m_pRecentFileList;
}

bool CPDFReaderApp::IsHadOpenDocumentSucessful() {
  POSITION pos = m_mapDocToFrame.GetStartPosition();
  void* doc = NULL;
  void* value = NULL;
  while (pos) {
    m_mapDocToFrame.GetNextAssoc(pos, doc, value);
    CDocument* pDoc = (CPDFReaderDoc*)doc;
    CPDFReaderDoc* pPdfDoc = DYNAMIC_DOWNCAST(CPDFReaderDoc, pDoc);
    if (pPdfDoc && !pPdfDoc->GetPDFDocument().IsEmpty())
      return true;
  }

  return false;
}

// The one and only CPDFReaderApp object

CPDFReaderApp theApp;
// This identifier was generated to be statistically unique for your app
// You may change it if you prefer to choose a specific identifier

// {1B686C72-D3E5-4B41-988F-2055D7088280}
static const CLSID clsid = {0x1B686C72, 0xD3E5, 0x4B41, {0x98, 0x8F, 0x20, 0x55, 0xD7, 0x8, 0x82, 0x80}};

const GUID CDECL _tlid = {0xD1A96569, 0x209D, 0x4D84, {0xB4, 0xF3, 0x52, 0xE2, 0xE2, 0xBD, 0x67, 0x6B}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

void InitConsoleWindow() {
  AllocConsole();
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  int hCrt = _open_osfhandle((long) handle, _O_TEXT);
  FILE * hf = _fdopen(hCrt, "w");
  *stdout = *hf;
}

BOOL CPDFReaderApp::InitInstance() {
  // InitCommonControlsEx() is required on Windows XP if an application
  // manifest specifies use of ComCtl32.dll version 6 or later to enable
  // visual styles.  Otherwise, any window creation will fail.
  INITCOMMONCONTROLSEX InitCtrls;
  InitCtrls.dwSize = sizeof(InitCtrls);
  // Set this to include all the common control classes you want to use
  // in your application.
  InitCtrls.dwICC = ICC_WIN95_CLASSES;
  InitCommonControlsEx(&InitCtrls);

  CWinAppEx::InitInstance();

  Gdiplus::GdiplusStartup(&m_GdiplusToken, &m_GdiplusStartupInput, NULL);

  // Initialize Library
  foxit::ErrorCode code = Library::Initialize(sn, key);
  if (code != foxit::e_ErrSuccess) {
    const char* error_message = GetErrorMessage(foxit::e_ErrInvalidLicense);
    AfxMessageBox(CString(GetErrorMessage(foxit::e_ErrInvalidLicense)), MB_OK | MB_ICONERROR);
    return FALSE;
  }

  try {
    m_pXFAAppProviderHandler = new XFAAppProviderHandler();
    Library::RegisterXFAAppProviderCallback(m_pXFAAppProviderHandler);
  } catch (foxit::Exception &) {
    delete m_pXFAAppProviderHandler;
    m_pXFAAppProviderHandler = NULL;
  }

  ActionHandler* actionHandler = new ActionHandler();
  Library::SetActionCallback(actionHandler);

  if (!AfxSocketInit()) {
    AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
    return FALSE;
  }

  // Initialize OLE libraries
  if (!AfxOleInit()) {
    AfxMessageBox(IDP_OLE_INIT_FAILED);
    return FALSE;
  }

  AfxEnableControlContainer();

  EnableTaskbarInteraction(FALSE);

  // Standard initialization
  // If you are not using these features and wish to reduce the size
  // of your final executable, you should remove from the following
  // the specific initialization routines you do not need
  // Change the registry key under which our settings are stored
  // TODO: You should modify this string to be something appropriate
  // such as the name of your company or organization
  SetRegistryKey(_T("Local AppWizard-Generated Applications"));
  LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

  InitContextMenuManager();

  InitKeyboardManager();

  InitTooltipManager();
  CMFCToolTipInfo ttParams;
  ttParams.m_bVislManagerTheme = TRUE;
  theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views
  CMultiDocTemplate* pDocTemplate;
  pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME, RUNTIME_CLASS(CPDFReaderDoc),
                                       RUNTIME_CLASS(CMainFrame),  // main SDI frame window
                                       RUNTIME_CLASS(CPDFReaderView));
  if (!pDocTemplate)
    return FALSE;
  m_pDocTemplate = pDocTemplate;
  AddDocTemplate(pDocTemplate);
  // Connect the COleTemplateServer to the document template
  //  The COleTemplateServer creates new documents on behalf
  //  of requesting OLE containers by using information
  //  specified in the document template
  m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);
  // Register all OLE server factories as running.  This enables the
  //  OLE libraries to create objects from other applications
  COleTemplateServer::RegisterAll();
  // Note: MDI applications register all server objects without regard
  //  to the /Embedding or /Automation on the command line

  // Parse command line for standard shell commands, DDE, file open
  CCommandLineInfo cmdInfo;
  ParseCommandLine(cmdInfo);

  // Enable DDE Execute open
  EnableShellOpen();
  RegisterShellFileTypes(TRUE);

  // App was launched with /Embedding or /Automation switch.
  // Run app as automation server.
  if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated) {
    // Don't show the main window
    return TRUE;
  }
  // App was launched with /Unregserver or /Unregister switch.  Unregister
  // typelibrary.  Other unregistration occurs in ProcessShellCommand().
  else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister) {
    UnregisterShellFileTypes();
    m_server.UpdateRegistry(OAT_DISPATCH_OBJECT, NULL, NULL, FALSE);
    AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
  }
  // App was launched standalone or with other switches (e.g. /Register
  // or /Regserver).  Update registry entries, including typelibrary.
  else {
    m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
    COleObjectFactory::UpdateRegistryAll();
    AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
  }

  if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew) {
    if (!GetCommondInfoFromDlg(&cmdInfo))
      return FALSE;
  }

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.
  if (!ProcessShellCommand(cmdInfo))
    return FALSE;

  // The one and only window has been initialized, so show and update it
  m_pMainWnd->ShowWindow(SW_SHOW);
  m_pMainWnd->UpdateWindow();

  // call DragAcceptFiles only if there's a suffix
  //  In an SDI app, this should occur after ProcessShellCommand
  // Enable drag/drop open
  m_pMainWnd->DragAcceptFiles();
  return TRUE;
}

int CPDFReaderApp::ExitInstance() {
  AfxOleTerm(FALSE);
  Library::Release();
  Gdiplus::GdiplusShutdown(m_GdiplusToken);
  return CWinAppEx::ExitInstance();
}

bool CPDFReaderApp::GetCommondInfoFromDlg(CCommandLineInfo* line_info) {
  CStartInterfaceDlg dlg;

  if (dlg.DoModal() != IDOK) {
    return false;
  }
  line_info->m_nShellCommand = CCommandLineInfo::FileOpen;
  line_info->m_strFileName = dlg.GetFilePath();
  return true;
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx {
 public:
  CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_ABOUTBOX };
#endif

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support

  // Implementation
 protected:
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg()
    : CDialogEx(IDD_ABOUTBOX) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CPDFReaderApp::OnAppAbout() {
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}

// CPDFReaderApp customization load/save methods

void CPDFReaderApp::PreLoadState() {}

void CPDFReaderApp::LoadCustomState() {}

void CPDFReaderApp::SaveCustomState() {}

// CPDFReaderApp message handlers

void CPDFReaderApp::OnFileNewFrame() {
  ASSERT(m_pDocTemplate != NULL);

  CDocument* pDoc = NULL;
  CFrameWnd* pFrame = NULL;

  // Create a new instance of the document referenced
  // by the m_pDocTemplate member.
  if (m_pDocTemplate != NULL)
    pDoc = m_pDocTemplate->CreateNewDocument();

  if (pDoc != NULL) {
    // If creation worked, use create a new frame for
    // that document.
    pFrame = m_pDocTemplate->CreateNewFrame(pDoc, NULL);
    if (pFrame != NULL) {
      // Set the title, and initialize the document.
      // If document initialization fails, clean-up
      // the frame window and document.

      m_pDocTemplate->SetDefaultTitle(pDoc);
      if (!pDoc->OnNewDocument()) {
        pFrame->DestroyWindow();
        pFrame = NULL;
      } else {
        // Otherwise, update the frame
        m_pDocTemplate->InitialUpdateFrame(pFrame, pDoc, TRUE);
      }
    }
  }

  // If we failed, clean up the document and show a
  // message to the user.

  if (pFrame == NULL || pDoc == NULL) {
    delete pDoc;
    AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
  }
}

void CPDFReaderApp::OnFileNew() {
  CDocument* pDoc = NULL;
  CFrameWnd* pFrame;
  pFrame = DYNAMIC_DOWNCAST(CFrameWnd, CWnd::GetActiveWindow());

  if (pFrame != NULL)
    pDoc = pFrame->GetActiveDocument();

  if (pFrame == NULL || pDoc == NULL) {
    // if it's the first document, create as normal
    CWinApp::OnFileNew();
  } else {
    // Otherwise, see if we have to save modified, then
    // ask the document to reinitialize itself.
    if (!pDoc->SaveModified())
      return;

    CDocTemplate* pTemplate = pDoc->GetDocTemplate();
    ASSERT(pTemplate != NULL);

    if (pTemplate != NULL)
      pTemplate->SetDefaultTitle(pDoc);
    pDoc->OnNewDocument();
  }
}
