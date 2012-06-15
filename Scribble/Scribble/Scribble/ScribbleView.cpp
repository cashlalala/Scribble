// ScribbleView.cpp : CScribbleView 類別的實作
//

#include "stdafx.h"
#include "Scribble.h"

#include "ScribbleDoc.h"
#include "ScribbleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScribbleView

IMPLEMENT_DYNCREATE(CScribbleView, CScrollView)

BEGIN_MESSAGE_MAP(CScribbleView, CScrollView)
	// 標準列印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CScribbleView 建構/解構

CScribbleView::CScribbleView()
{
	// TODO: 在此加入建構程式碼

}

CScribbleView::~CScribbleView()
{
}

BOOL CScribbleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CScribbleView 描繪
/*
In the OnDraw function, the view first calls the GetClipBox member function of CDC to get the invalidated portion of the client area.
Then the view iterates through the list of strokes in the document, calling IntersectRect for each to determine if any part of the
stroke lies in the invalidated region. If so, the view asks the stroke to draw itself. Any strokes that don’t intersect the invalidated 
region don’t have to be redrawn.
*/

void CScribbleView::OnDraw(CDC* pDC)
{
	CScribbleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Get the invalidated rectangle of the view, or in the case
	// of printing, the clipping region of the printer DC.
	CRect rectClip;
	CRect rectStroke;
	pDC->GetClipBox(&rectClip);

	//Note: CScrollView::OnPaint() will have already adjusted the
	//viewpoint origin before calling OnDraw(), to reflect the
	//currently scrolled position.

	if (!pDoc)
		return;

	// The view delegates the drawing of individual strokes to
	// CStroke::DrawStroke( ).
	CTypedPtrList<CObList, CStroke*>& strokeList =
		pDoc->m_strokeList;
	POSITION pos = strokeList.GetHeadPosition( );
	while (pos != NULL)
	{
		CStroke* pStroke = strokeList.GetNext(pos);
		rectStroke = pStroke->GetBoundingRect();
		if (!rectStroke.IntersectRect(&rectStroke, &rectClip))
			continue;
		pStroke->DrawStroke( pDC );
	}
}


// CScribbleView 列印

BOOL CScribbleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CScribbleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CScribbleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
}


// CScribbleView 診斷

#ifdef _DEBUG
void CScribbleView::AssertValid() const
{
	CView::AssertValid();
}

void CScribbleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CScribbleDoc* CScribbleView::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScribbleDoc)));
	return (CScribbleDoc*)m_pDocument;
}
#endif //_DEBUG


// CScribbleView 訊息處理常式

void CScribbleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// CScrollView changes the viewport origin and mapping mode.
	// It's necessary to convert the point from device coordinates
	// to logical coordinates, such as are stored in the document.
	CClientDC dc(this);
	OnPrepareDC(&dc); // set up mapping mode and viewport origin
	dc.DPtoLP(&point);

	// Pressing the mouse button in the view window
	// starts a new stroke.

	m_pStrokeCur = GetDocument( )->NewStroke( );
	// Add first point to the new stroke
	m_pStrokeCur->m_pointArray.Add(point);

	SetCapture( );  // Capture the mouse until button up
	m_ptPrev = point;  // Serves as the MoveTo( ) anchor point
	// for the LineTo() the next point, as
	// the user drags the mouse
	return;

	//CView::OnLButtonDown(nFlags, point);
}

void CScribbleView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// Mouse button up is interesting in the Scribble
	// application only if the user is currently drawing a new
	// stroke by dragging the captured mouse.

	if( GetCapture( ) != this )
		return;    // If this window (view) didn't capture the
	// mouse, the user isn't drawing in this window.

	CScribbleDoc* pDoc = GetDocument();
	CClientDC dc( this );
	// CScrollView changes the viewport origin and mapping mode.
	// It's necessary to convert the point from device coordinates
	// to logical coordinates, such as are stored in the document.
	OnPrepareDC(&dc);  // set up mapping mode and viewport origin
	dc.DPtoLP(&point);

	CPen* pOldPen = dc.SelectObject( pDoc->GetCurrentPen( ) );
	dc.MoveTo( m_ptPrev );
	dc.LineTo( point );
	dc.SelectObject( pOldPen );
	m_pStrokeCur->m_pointArray.Add(point);

	// Tell the stroke item that we're done adding points to it.
	// This is so it can finish computing its bounding rectangle.
	m_pStrokeCur->FinishStroke(); 

	// Tell the other views that this stroke has been added
	// so that they can invalidate this stroke's area in their
	// client area.
	pDoc->UpdateAllViews(this, 0L, m_pStrokeCur);

	ReleaseCapture( );    // Release the mouse capture established
	// at the beginning of the mouse drag.
	return;

	//CView::OnLButtonUp(nFlags, point);
}

void CScribbleView::OnMouseMove(UINT nFlags, CPoint point)
{
	// Mouse movement is interesting in the Scribble application
	// only if the user is currently drawing a new stroke by
	// dragging the captured mouse.

	if( GetCapture( ) != this )
		return;        // If this window (view) didn't capture the
	// mouse, the user isn't drawing in this window.

	CClientDC dc( this );
	// CScrollView changes the viewport origin and mapping mode.
	// It's necessary to convert the point from device coordinates
	// to logical coordinates, such as are stored in the document.
	OnPrepareDC(&dc); // set up mapping mode and viewport origin
	dc.DPtoLP(&point);

	m_pStrokeCur->m_pointArray.Add(point);

	// Draw a line from the previous detected point in the mouse
	// drag to the current point.
	CPen* pOldPen =
		dc.SelectObject( GetDocument( )->GetCurrentPen( ) );
	dc.MoveTo( m_ptPrev );
	dc.LineTo( point );
	dc.SelectObject( pOldPen );
	m_ptPrev = point;
	return;
	//
	//CView::OnMouseMove(nFlags, point);
}

void CScribbleView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// The document has informed this view that some data has changed.

	if (pHint != NULL)
	{
		if (pHint->IsKindOf(RUNTIME_CLASS(CStroke)))
		{
			// The hint is that a stroke has been added (or changed).
			// So, invalidate its rectangle.
			CStroke* pStroke = (CStroke*)pHint;
			CClientDC dc(this);
			OnPrepareDC(&dc);
			CRect rectInvalid = pStroke->GetBoundingRect();
			InvalidateRect(&rectInvalid);
			dc.LPtoDP(&rectInvalid);
			return;
		}
	}
	// We can't interpret the hint, so assume that anything might
	// have been updated.
	Invalidate();
	return;
}


/*
The SetScrollSizes member function is defined by CScrollView. Its first parameter is the mapping mode used to display the document.
The current version of Scribble uses MM_TEXT as the mapping mode; in Lesson 9, Enhancing Printing, Scribble will use the MM_LOENGLISH 
mapping mode for better printing. (For more information on mapping modes, see Enlarge the Printed Image in Lesson 9.)

The second parameter is the total size of the document, which is needed to determine the scrolling limits. 
The view uses the value returned by the document’s GetDocSize member function for this parameter.

SetScrollSizes also has two other parameters for which Scribble uses the default values. 
These are CSize values that represent the size of one “page” and one “line,”
the distances to be scrolled if the user clicks the scroll bar or a scroll arrow. 
The default values are 1/10th and 1/100th of the document size, respectively.
*/
void CScribbleView::OnInitialUpdate()
{
	SetScrollSizes( MM_TEXT, GetDocument()->GetDocSize() );

	CScrollView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}
