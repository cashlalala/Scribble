// ChildFrm.h : CChildFrame ���O������
//


#pragma once
#include "afxext.h"

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// �ݩ�
public:

// �@�~
public:

// �мg
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �{���X��@
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()
	CSplitterWnd m_wndSplitter;
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};
