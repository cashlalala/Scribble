// ChildFrm.h : CChildFrame 類別的介面
//


#pragma once
#include "afxext.h"

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 屬性
public:

// 作業
public:

// 覆寫
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 程式碼實作
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
	CSplitterWnd m_wndSplitter;
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
//	afx_msg void OnUpdatePenThickOrThin(CCmdUI *pCmdUI);
};
