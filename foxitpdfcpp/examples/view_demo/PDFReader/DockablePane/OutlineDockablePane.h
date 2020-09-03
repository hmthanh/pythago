#pragma once

class CMainFrame;

class COutlineViewTree : public CTreeCtrl {
  // Construction
public:
  COutlineViewTree(CMainFrame* pFrame);

  // Overrides
  Bookmark GetItemData(_In_ HTREEITEM hItem) const;
  BOOL SetItemData(_In_ HTREEITEM hItem, Bookmark bookmark);

protected:
  virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
  virtual ~COutlineViewTree();

protected:
  afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnPaint();
  DECLARE_MESSAGE_MAP()

private:
  CMainFrame* m_pFrame;
  std::vector<Bookmark> m_vBookmarks;
};


class COutlineToolBar : public CMFCToolBar
{
  virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
  {
    CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
  }

  virtual BOOL AllowShowOnList() const { return FALSE; }
};

class COutlineView : public CDockablePane
{
// Construction
public:
  COutlineView(CMainFrame* pFrame);
  void AdjustLayout();
  void OnChangeVisualStyle();

// Attributes
protected:
  CMainFrame* m_pFrame;
  COutlineViewTree m_wndOutlineView;
  CImageList m_OutlineViewImages;
  BOOL m_bHasFill;

protected:
  void AddOutlineItem(Bookmark parent_bookmark, HTREEITEM hParent);
  void FillOutlineView();

// Implementation
public:
  virtual void ConvertToTabbedDocument(BOOL bActiveTabOnly = TRUE);
  virtual ~COutlineView();

protected:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnPaint();
  afx_msg void OnSetFocus(CWnd* pOldWnd);

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

