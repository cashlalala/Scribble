// ScribbleDoc.h : CScribbleDoc ���O������
//


#pragma once
#include "afxwin.h"
#include "CStroke.h"


class CScribbleDoc : public CDocument
{
protected: // �ȱq�ǦC�ƫإ�
	CScribbleDoc();
	DECLARE_DYNCREATE(CScribbleDoc)

// �ݩ�
public:
	CTypedPtrList<CObList, CStroke*> m_strokeList;
	CPen m_penCur;
	UINT m_nPenWidth;
	BOOL    m_bThickPen;    // Thick currently selected or not
	UINT    m_nThinWidth;    // Current definition of thin
	UINT    m_nThickWidth;    // Current definition of thick
protected:
	CSize m_sizeDoc;

// �@�~
public:
	CPen*   GetCurrentPen();
public:
	CSize GetDocSize() { return m_sizeDoc; }

// �мg
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �{���X��@
public:
	virtual ~CScribbleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ͪ��T�������禡
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


