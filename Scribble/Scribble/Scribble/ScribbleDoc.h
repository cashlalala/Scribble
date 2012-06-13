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

// �@�~
public:
	CPen*   GetCurrentPen();

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
};


