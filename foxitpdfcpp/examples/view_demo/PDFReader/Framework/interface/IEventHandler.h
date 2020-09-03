
#ifndef _IREADER_EVENTHANDLER_
#define _IREADER_EVENTHANDLER_

#include "PDFReader/Framework/interface/IApp.h"

class IReader_AppEventHandler
{
public:
	virtual ~IReader_AppEventHandler(){}
};

class IReader_DocEventHandler
{
public:
	virtual ~IReader_DocEventHandler(){}

	virtual void OnDocWillOpen(IReader_Document* pDoc) = 0;

	virtual void OnDocDidOpen(IReader_Document* pDoc) = 0;

	virtual	void OnDocWillClose(IReader_Document* pDoc) = 0;

	virtual	void OnDocDidClose(IReader_Document* pDoc) = 0;

	virtual BOOL OnDocWillSave(IReader_Document* pDoc, BOOL bSaveAs) = 0;

	virtual void OnDocDidSave(IReader_Document* pDoc) = 0;

	virtual void OnDocActivate(IReader_Document* pDoc) = 0;

	virtual void OnDocDeactivate(IReader_Document* pDoc) = 0;

	virtual void OnDocChange(IReader_Document* pDoc) = 0;

	virtual void OnDocWillDraw(IReader_Document* pDoc, HDC hdc) = 0;

	virtual void OnDocDidDraw(IReader_Document* pDoc, HDC hdc) = 0;

	virtual void OnDocFinishRender(IReader_Document* pDoc) = 0;

	virtual	void OnDocViewCreate(IReader_Document* pDoc) = 0;

	virtual	void OnDocViewDestroy(IReader_Document* pDoc) = 0;

	virtual	void OnDocFrameCreate(IReader_Document* pDoc, HWND hFrameWnd) = 0;

	virtual void OnDocFrameDestroy(IReader_Document* pDoc, HWND hFrameWnd) = 0;

	virtual void OnDocFrameSize(IReader_Document* pDoc, HWND hFrameWnd, CRect rtClient) = 0;

	virtual BOOL OnKeyDown(IReader_Document* pDoc, UINT nKeyCode, UINT nFlags) = 0;

	virtual BOOL OnKeyUp(IReader_Document* pDoc, UINT nKeyCode, UINT nFlags) = 0;

	virtual BOOL OnChar(IReader_Document* pDoc, UINT nKeyCode, UINT nFlags) = 0;

	virtual BOOL OnLButtonDown(IReader_Page* pPage, UINT nFlags,const CPoint& point) = 0;

	virtual BOOL OnLButtonUp(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL OnLButtonDblClk(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL OnMouseMove(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL OnRButtonDown(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL OnRButtonUp(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL OnRButtonDblClk(IReader_Page* pPage, UINT nFlags, const CPoint& point) = 0;

	virtual BOOL OnMouseWheel(IReader_Page* pPage, UINT nFlags, short zDelta, const CPoint& point) = 0;
};

class IReader_PageEventHandler
{
public:
	virtual ~IReader_PageEventHandler(){}

	virtual void OnPageOpen(IReader_Page* pPage) = 0;

	virtual void OnPageClose(IReader_Page* pPage) = 0;

	virtual void OnPageVisible(IReader_Page* pPage) = 0;

	virtual void OnPageInvisible(IReader_Page* pPage) = 0;

	virtual	void OnPageContentChanged(IReader_Page* pPage) = 0;

	virtual void OnPageBeforeParse(IReader_Page* pPage, BOOL bPageVisable) = 0;

	virtual void OnPageParseComplete(IReader_Page* pPage, BOOL bPageVisable) = 0;
};

#endif