// ScribbleView.h : CScribbleView ���O������
//


#pragma once


class CScribbleView : public CView
{
protected: // �ȱq�ǦC�ƫإ�
	CScribbleView();
	DECLARE_DYNCREATE(CScribbleView)

// �ݩ�
public:
	CScribbleDoc* GetDocument() const;

// �@�~
public:

// �мg
public:
	virtual void OnDraw(CDC* pDC);  // �мg�H�yø���˵�
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �{���X��@
public:
	virtual ~CScribbleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ScribbleView.cpp ������������
inline CScribbleDoc* CScribbleView::GetDocument() const
   { return reinterpret_cast<CScribbleDoc*>(m_pDocument); }
#endif

