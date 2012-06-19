// ScribbleDoc.h : CScribbleDoc 類別的介面
//


#pragma once
#include "afxwin.h"
#include "CStroke.h"


class CScribbleDoc : public CDocument
{
protected: // 僅從序列化建立
	CScribbleDoc();
	DECLARE_DYNCREATE(CScribbleDoc)

// 屬性
public:
	CTypedPtrList<CObList, CStroke*> m_strokeList;
	CPen m_penCur;
	UINT m_nPenWidth;
	BOOL    m_bThickPen;    // Thick currently selected or not
	UINT    m_nThinWidth;    // Current definition of thin
	UINT    m_nThickWidth;    // Current definition of thick
protected:
	CSize m_sizeDoc;

// 作業
public:
	CPen*   GetCurrentPen();
public:
	CSize GetDocSize() { return m_sizeDoc; }

// 覆寫
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 程式碼實作
public:
	virtual ~CScribbleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
	void InitDocument(void);
public:
	CStroke* NewStroke(void);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	afx_msg void OnEditClearAll();
	afx_msg void OnPenThickOrThin();
protected:
	void ReplacePen(void);
public:
	afx_msg void OnUpdateEditC(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePenThickOrThin(CCmdUI *pCmdUI);
	afx_msg void OnPenWidths();
	afx_msg void OnPenColor();
};


