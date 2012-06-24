// ScribbleView.h : CScribbleView 類別的介面
//


#pragma once
//#include "CStroke.h"
//#include "ScribbleDoc.h"
#include "cpenwidthsdlg.h"


class CScribbleView : public CScrollView 
{
protected: // 僅從序列化建立
	CScribbleView();
	DECLARE_DYNCREATE(CScribbleView)
// 屬性
protected:
	CStroke*   m_pStrokeCur;    // The stroke in progress
	CPoint     m_ptPrev;    // The last mouse pt in the stroke
public:
	CScribbleDoc* GetDocument() const;

// 作業
public:

// 覆寫
public:
	virtual void OnDraw(CDC* pDC);  // 覆寫以描繪此檢視
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 程式碼實作
public:
	virtual ~CScribbleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
protected:
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
public:
	void PrintTitlePage(CDC* pDC, CPrintInfo* pInfo);
	void PrintPageHeader(CDC*  pDC, CPrintInfo* pInfo, CString& strHeader);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
};

#ifndef _DEBUG  // ScribbleView.cpp 中的偵錯版本
inline CScribbleDoc* CScribbleView::GetDocument() const
   { return reinterpret_cast<CScribbleDoc*>(m_pDocument); }
#endif

