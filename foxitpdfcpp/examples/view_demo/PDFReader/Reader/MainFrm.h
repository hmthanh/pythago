
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "PDFReader/DockablePane/OutlineDockablePane.h"

class CZoomSliderButton;
class CPageGotoButton;

class CSelfToolBar : public CMFCToolBar {
  DECLARE_SERIAL(CSelfToolBar)
 public:
  CSelfToolBar();
  virtual BOOL LoadState(LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);
  virtual BOOL SaveState(LPCTSTR lpszProfileName = NULL, int nIndex = -1, UINT uiID = (UINT) -1);

};

class CMainFrame : public CFrameWndEx {
 protected:  // create from serialization only
  CMainFrame();
  DECLARE_DYNCREATE(CMainFrame)

  // Attributes
 public:
  CPageGotoButton* GetPageGotoButton();
  CZoomSliderButton* GetZoomSliderButton();
  // Operations
 public:
  // Overrides
 public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
                         CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
  // Implementation
 public:
  virtual ~CMainFrame();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

 protected:  // control bar embedded members
  CSelfToolBar m_wndToolBar;
  CSelfToolBar m_wndGotoBar;
  CSelfToolBar m_wndZoomBar;
  CMFCStatusBar m_wndStatusBar;
  COutlineView m_wndOutlineView;
  CFont m_font;

  // Generated message map functions
 protected:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnFileClose();
  afx_msg void OnClose();
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  afx_msg LRESULT OnToolbarReset(WPARAM wParam, LPARAM lParam);
  DECLARE_MESSAGE_MAP()

  BOOL CreateDockingWindows();
  void SetDockingWindowIcons(BOOL bHiColorIcons);

 public:
  afx_msg void OnViewOutlineview();
  afx_msg void OnUpdateViewOutlineview(CCmdUI* pCmdUI);
  afx_msg void OnAppExit();
  afx_msg void OnViewGotobar();
  afx_msg void OnUpdateViewGotobar(CCmdUI* pCmdUI);
  afx_msg void OnViewToolbar();
  afx_msg void OnUpdateViewToolbar(CCmdUI* pCmdUI);
  afx_msg void OnViewZoombar();
  afx_msg void OnUpdateViewZoombar(CCmdUI *pCmdUI);
  afx_msg void OnFileOpen();
};
