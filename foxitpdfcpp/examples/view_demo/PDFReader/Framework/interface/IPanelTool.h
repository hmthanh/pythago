#ifndef _IREADER_PANELTOOL_H_
#define _IREADER_PANELTOOL_H_

#include "PDFReader/Framework/interface/IApp.h"
class IReader_PanelToolHandler;
// A class representing Panel View
class IReader_PanelView
{
public:
	virtual ~IReader_PanelView(){}
	//Like Add Bookmark.
	virtual BOOL AddItem() = 0;

	// Quickly page locate
	virtual BOOL SetPos(int nPage) = 0;

	virtual HWND GetHwnd() = 0;

	virtual void OnPanelActive() = 0;

	virtual BOOL GetBDockBottom() = 0;

	virtual void RotateView(int nRotate) = 0;
};

//class  IReader_PanelToolHandler
// A class representing tool handler
class IReader_PanelToolHandler
{
public:
	virtual ~IReader_PanelToolHandler(){}

	// Initialization
	virtual BOOL Tool_OnInit() = 0;
	// Destory
	virtual BOOL Tool_Destroy() = 0;

	virtual CString Tool_GetName() = 0;

	virtual CString	Tool_GetLabel() = 0;

	virtual CString	Tool_GetToolTip() = 0;

	// View operation
	virtual IReader_PanelView* Tool_CreateNewView(FSPDFDoc* pDocument, HWND hOwner) = 0;

	virtual IReader_PanelView* Tool_GetView(FSPDFDoc* pDocument, HWND hOwner) = 0;

	virtual void Tool_CloseView(FSPDFDoc* pDocument, HWND hOwner) = 0;

	virtual void Tool_SetActiveView(FSPDFDoc* pDocument, HWND hOwner) = 0;

	// Get tool Icon 24
	virtual HBITMAP Tool_GetIcon() = 0;
};
#endif