#ifndef _IREADER_TOOL_H_
#define _IREADER_TOOL_H_

#include "PDFReader/Framework/interface/IApp.h"

class IReader_App;
class IReader_Page;
class IReader_Document;

// A class representing tool handler
class IReader_ToolHandler
{
public:
	virtual ~IReader_ToolHandler(){}

	// Initialization
	virtual void Tool_OnInit(IReader_App* pApp) = 0;

	// Destory
	virtual void Tool_Destroy() = 0;

	// Get tool basic info. Note: all strings should be in host encoding
	virtual CString Tool_GetName() = 0;

	virtual BOOL Tool_IsProcessing() = 0;

	// UI Events
	virtual void Tool_OnActivate(BOOL bPersistent) = 0;

	virtual void Tool_OnDeactivate() = 0;

	// Mouse events
	virtual BOOL Tool_OnLButtonDown(IReader_Page* pPage, UINT nFlags,const CPoint& point) = 0;

	virtual BOOL Tool_OnLButtonUp(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL Tool_OnLButtonDblClk(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL Tool_OnMouseMove(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL Tool_OnRButtonDown(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL Tool_OnRButtonUp(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL Tool_OnRButtonDblClk(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL Tool_OnMouseWheel(IReader_Page* pPage, UINT nFlags, short zDelta, const CPoint& point) = 0;

    //[Draw]
	virtual BOOL Tool_OnDraw(IReader_Document* pDoc, HDC hDC) = 0;
};

#endif