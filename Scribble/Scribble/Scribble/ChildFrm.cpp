// ChildFrm.cpp : CChildFrame 類別的實作
//
#include "stdafx.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
END_MESSAGE_MAP()


// CChildFrame 建構/解構

CChildFrame::CChildFrame()
{
	// TODO: 在此加入成員初始化程式碼
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 達到修改視窗類別或樣式的目的
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CChildFrame 診斷

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CChildFrame 訊息處理常式
/*
In OnCreateClient, the frame window creates the window that will cover its client area by calling the Create function of its CSplitterWnd member variable. 
The following parameters passed to the Create function describe the panes that the splitter window will manage:

The first parameter passed to Create specifies the parent window for the client window.
The function passes the this pointer, making the CScribbleFrame window the parent of the CSplitterWnd object (the member variable, m_wndSplitter). 

The second and third parameters specify the maximum number of rows and columns that the splitter window can have. 
A value of two is used for each, so Scribble’s splitter windows can have up to four panes. 

The fourth parameter specifies the minimum size of a pane: a square 10 logical units on a side. 

The fifth parameter is the CCreateContext structure that is passed to OnCreateClient. 
This structure is used to determine which view class should be used for each pane in the splitter window.
The Create function accepts two additional arguments:

The sixth argument specifies the styles to be used for the splitter window.
The default value specifies a visible child window with vertical and horizontal scroll bars that supports dynamic splitting. 

The seventh argument specifies the ID to be assigned to the splitter window. 
Its default value is AFX_IDW_PANE_FIRST, which is the ID of the first pane.
Because Scribble doesn't pass any values for these, the default values are used.
*/

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	//m_wndSplitter.CreateStatic(this,
	//	1,  //col
	//	2);  //row
	//m_wndSplitter.CreateView(0, 0, //col, row
	//	RUNTIME_CLASS(CView), //view class
	//	CSize(200, 150), //size
	//	pContext);   //constructor of parent window

	//m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CView),
	//	CSize(200, 150), pContext);
	//return 1; 

	return m_wndSplitter.Create(this,
								1, 2,       // TODO: adjust the number of rows, columns
								CSize(10, 10),  // TODO: adjust the minimum pane size
								pContext);

	//return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}
