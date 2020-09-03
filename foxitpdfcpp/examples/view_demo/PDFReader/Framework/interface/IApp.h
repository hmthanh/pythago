#ifndef _IREADER_APP_H_
#define _IREADER_APP_H_
#include "PDFReader\source\stdafx.h"
class IReader_App;
class IReader_Module;
class IReader_ToolHandler;
class IReader_PanelToolHandler;
class IReader_AppEventHandler;
class IReader_DocEventHandler;
class IReader_PageEventHandler;
class IReader_Document;
class IReader_AnnotHandlerMgr;
class IReader_Page;
class IReader_Annot;

// Prototype of module initialization
typedef IReader_Module* (*IReader_CreateModuleProc)(HMODULE hModule, IReader_App* pApp);

/************************************************************************/
/* class  IReader_Module												*/
/* A class representing the Module										*/
/* This is an interface class implemented by Module                     */
/************************************************************************/
class IReader_Module
{
public:
	virtual ~IReader_Module(){}
	virtual void Destroy() = 0;
	virtual	CString GetModuleName() = 0;
};

class IReader_MenuToolbarCommandHandler
{
public:
	virtual ~IReader_MenuToolbarCommandHandler(){}

	virtual void OnInit(IReader_App* pApp) = 0;

	virtual void Destroy() = 0;

	virtual void GetIDs(CArray<UINT, UINT>& arrayID) = 0;

	virtual void OnCommand() = 0;

	virtual void OnUpdateCommandUI(CCmdUI * pCmdUI) = 0;
};

/************************************************************************/
/* class  CDataType												*/
/* A class representing the Mouse at object										*/

/************************************************************************/
#define ANNOTATION				L"Annotation"

class CDataType
{
public:
	virtual ~CDataType(){}
	virtual CString	GetDataType() = 0;

};

/************************************************************************/
/* class  IReader_App													*/
/* A class representing the Reader application							*/
/* This is an interface class implemented by Reader                     */
/************************************************************************/
class IReader_App
{
public:
	virtual ~IReader_App(){}

	// Register a tool handler
	virtual BOOL RegisterToolHandler(IReader_ToolHandler* pToolHandler) = 0;

	// Register a Panel Tool handler
	virtual BOOL RegisterPanelToolHandler(IReader_PanelToolHandler* pPanelToolHandler) = 0;

	// Register a App Event handle
	virtual BOOL RegisterAppEventHandler(IReader_AppEventHandler* pAppEventHandler) = 0;

	// Register A Doc Event handle
	virtual	BOOL RegisterDocEventHandler(IReader_DocEventHandler* pDocEventHandler) = 0;

	//Page Event handle
	virtual	BOOL RegisterPageEventHandler(IReader_PageEventHandler* pPageEventHandler) = 0;

	virtual BOOL RegisterMenuToolbarCommandHandler(IReader_MenuToolbarCommandHandler* pCommandHandler) = 0;

	// Get a panel tool handler from name
	virtual IReader_PanelToolHandler* GetPanelToolHandler(LPCWSTR  pToolName) = 0;

	virtual int CountToolHandlers() = 0;

	virtual IReader_ToolHandler* GetToolHandlerByIndex(int index) = 0;

	virtual IReader_ToolHandler* GetToolHandlerByName(LPCWSTR pToolName) = 0;

	virtual IReader_ToolHandler* GetCurrentToolHandler() = 0;

	virtual void SetCurrentToolHandler(IReader_ToolHandler* pToolHandler, BOOL bPersistent, BOOL bDelay =FALSE) = 0;

	virtual void SetCurrentToolHandler(LPCWSTR csToolname, BOOL bPersistent) = 0;

	virtual IReader_Document* GetCurrentDocument() = 0;

	virtual BOOL SetCurrentDocument(IReader_Document* pDocument) = 0;

	virtual IReader_Document* OpenDocument(LPCWSTR wsFilePath,  BOOL bAttachment, BOOL bMakeVisible = TRUE, LPCWSTR wsPassword = L"", BOOL bAddToMRU = TRUE) = 0;

	virtual BOOL CloseDocument(IReader_Document* pDocument, BOOL bPromptToSave = TRUE, BOOL bDelay = TRUE) = 0;

	virtual IReader_Document* GetReaderDocument(PDFDoc* pDoc) = 0;

	virtual int CountDocuments() = 0;

	virtual IReader_Document* GetReaderDocument(int index) = 0;

	//HandlerMgr
	virtual	IReader_AnnotHandlerMgr* GetAnnotHandlerMgr() = 0;

	// MainFrame/Menu Operator
	virtual HWND GetMainFrameWnd() = 0;

	//Get Module
	virtual IReader_Module*	GetModuleByName(LPCWSTR wsName) = 0;
};

/************************************************************************/
/*class  IReader_Document                                               */
/************************************************************************/
class IReader_Document
{
public:
	virtual ~IReader_Document(){}

	virtual IReader_App* GetApp() = 0;

	virtual PDFDoc* GetDocument() = 0;

	virtual int GetPageCount() = 0;

	virtual IReader_Page* GetPage(int nIndex) = 0;

	virtual BOOL GotoPage(int nIndex) = 0;

	virtual BOOL MovePage(const CPoint& curPoint, const CPoint& toPoint) = 0;

	virtual BOOL MovePage(short zDelta) = 0;

	virtual void SetChangeMark() = 0;

	virtual BOOL GetChangeMark() = 0;

	virtual void ClearChangeMark() = 0;

	virtual HWND GetDocViewHwnd() = 0;

	//virtual void SetSelectedAnnot(IReader_Annot* pReaderAnnot) = 0;

	//virtual IReader_Annot* GetSelectedAnnot() = 0;

	//virtual void SetCapturedAnnot(IReader_Annot* pReaderAnnot) = 0;

	//virtual IReader_Annot* GetCapturedAnnot() = 0;

	virtual BOOL Save() = 0;

	virtual BOOL SaveAs() = 0;

	//virtual void SetLayerContext(FSLayerContext* LayerContext) = 0;
};

//[page show mode]
typedef enum _LAYOUTMODE
{
	SHOW_MODE_SINGLE				= 0	,
	SHOW_MODE_CONTINUOUS				,
	SHOW_MODE_FACING					,
	SHOW_MODE_CONTINUOUS_FACING
}LAYOUTMODE;

//******************************************
//[page zoom mode]
typedef enum _ZOOMMODE
{
	ZOOM_MODE_NONE           = 0 ,
	ZOOM_MODE_ACTUAL_SCALE   ,
	ZOOM_MODE_ACTUAL_SIZE    ,
	ZOOM_MODE_FIT_PAGE       ,
	ZOOM_MODE_FIT_WIDTH      ,
	ZOOM_MODE_FIT_HEIGHT     ,
	ZOOM_MODE_FIT_RECTANGLE  ,
	ZOOM_MODE_FIT_VISIBLE	 ,

}ZOOMMODE;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//class  IReader_Page
// A class representing a page
// This is an interface class implemented by Reader

class IReader_Page
{
public:
	virtual ~IReader_Page(){}

	virtual IReader_Document* GetDocument() = 0;

	virtual PDFPage* GetPage() = 0;

  virtual BOOL ParsePage(bool bReparse) = 0;

  virtual int GetPageIndex() = 0;

  virtual BOOL DocToWindow(const foxit::RectF& rcDoc, CRect& rcWindow) = 0;

  virtual BOOL WindowToDoc(const CPoint& ptWindow, foxit::PointF& ptDoc) = 0;

  virtual BOOL WindowToDoc(const CRect& rcWindow, foxit::RectF& rcDoc) = 0;

  virtual BOOL WindowToDocForPrint(int nPageIndex, const CRect& rcWindow, foxit::RectF& rcDoc) = 0;

	/*virtual TextLink* GetTextLink() = 0;

	virtual void SetPDFPageTextLink(TextLink* textLink) = 0;

	virtual void SetPDFTextPage(foxit::pdf::TextPage* textPage)= 0;

	virtual BOOL IsParseTextLink() = 0;*/

	//virtual IReader_Annot* AddAnnot(LPCSTR lpSubType, foxit::RectF rect) = 0;

	//virtual BOOL DeleteAnnot(IReader_Annot* pAnnot) = 0;

	//virtual	void MoveAnnot(IReader_Page* pDestPage, IReader_Annot *pAnnot) = 0;

	//virtual int CountAnnots() = 0;

	//virtual IReader_Annot* GetAnnot(int index) = 0;

	//// there can be only one focus annotation in the page, and actually in one document
	//virtual IReader_Annot* GetFocusAnnot() = 0;

	//virtual void SetFocusAnnot(IReader_Annot* pAnnot) = 0;
};

#endif//_IREADER_APP_H_

