// ScribbleView.cpp : CScribbleView 類別的實作
//

#include "stdafx.h"
#include "Scribble.h"

#include "ScribbleDoc.h"
#include "ScribbleView.h"
#include "CanvPropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ABS(x) (x>0)?x:-x

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
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CScribbleView 建構/解構

CScribbleView::CScribbleView()
{
	// TODO: 在此加入建構程式碼
}

CScribbleView::~CScribbleView()
{
}

// CScribbleView 列印

BOOL CScribbleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	pInfo->SetMaxPage(2);  // the document is two pages long:
	// the first page is the title page
	// the second page is the drawing

	BOOL bRet = DoPreparePrinting (pInfo);      // default preparation
	pInfo->m_nNumPreviewPages = 2;        //Preview 2 pages at a time
	// Set this value after calling DoPreparePrinting to override
	// value read from registry
	return bRet;
}

void CScribbleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CScribbleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
}


/*
The PrintTitlePage function uses m_rectDraw, which stores the usable drawing area of the page, 
as the rectangle in which the title should be centered.

Notice that PrintTitlePage declares a local CFont object to use when printing the title page. 
If you needed the font for the entire printing process, you could declare a CFont member variable in your view class,
create the font in the OnBeginPrinting member function, and destroy it in EndPrinting. 
However, since Scribble uses the font for just the title page, 
the font doesn’t have to exist beyond the PrintTitlePage function. 
When the function ends, the destructor is automatically called for the local CFont object.
*/
void CScribbleView::PrintTitlePage(CDC* pDC, CPrintInfo* pInfo)
{
	// Prepare a font size for displaying the file name
	LOGFONT logFont;
	memset(&logFont, 0, sizeof(LOGFONT));
	logFont.lfHeight = 75; //  3/4th inch high in MM_LOENGLISH
	CFont font;
	CFont* pOldFont = NULL;
	if (font.CreateFontIndirect(&logFont))
		pOldFont = pDC->SelectObject(&font);

	// Get the file name, to be displayed on title page
	CString strPageTitle = GetDocument()->GetTitle();

	// Display the file name 1 inch below top of the page,
	// centered horizontally
	pDC->SetTextAlign(TA_CENTER);
	pDC->TextOut(pInfo->m_rectDraw.right/2, -100, strPageTitle);

	if (pOldFont != NULL)
		pDC->SelectObject(pOldFont);
}

void CScribbleView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	if (pInfo->m_nCurPage == 1)     // page no. 1 is the title page
	{
		PrintTitlePage(pDC, pInfo);
	}
	else
	{
		CString strHeader = GetDocument()->GetTitle();

		PrintPageHeader(pDC, pInfo, strHeader);
		// PrintPageHeader() subtracts out from the pInfo->m_rectDraw the
		// amount of the page used for the header.
		pDC->SetWindowOrg(pInfo->m_rectDraw.left,-pInfo->m_rectDraw.top);

		// Now print the rest of the page
		OnDraw(pDC);
	}
	return;
}


/*
The PrintPageHeader member function prints the name of the document at the top of the page
, and then draws a horizontal line separating the header from the drawing.
It adjusts the m_rectDraw member of the pInfo parameter to account for the height of the header; 
recall that OnPrint uses this value to adjust the window origin before it calls OnDraw.
*/
void CScribbleView::PrintPageHeader(CDC*  pDC, CPrintInfo* pInfo, CString& strHeader)
{
	// Specify left text alignment
	pDC->SetTextAlign(TA_LEFT);

	// Print a page header consisting of the name of
	// the document and a horizontal line
	pDC->TextOut(0, -25, strHeader);  // 1/4 inch down

	// Draw a line across the page, below the header
	TEXTMETRIC textMetric;
	pDC->GetTextMetrics(&textMetric);
	int y = -35 - textMetric.tmHeight;        // line 1/10th in.
	// below text
	pDC->MoveTo(0, y);                        // from left margin
	pDC->LineTo(pInfo->m_rectDraw.right, y); //  to right margin

	// Subtract from the drawing rectangle the space used by header.
	y -= 25;     // space 1/4 inch below (top of) line
	pInfo->m_rectDraw.top += y;
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


BOOL CScribbleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的
	return CView::PreCreateWindow(cs);
}

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
	
	//if (point.x > m_nrestrictWidth
	//	|| point.y < -(int)m_nrestrictHeight)
	//{
	//	return;
	//}
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

	//To avoid button up right after button down.
	if (point.x > GetDocument()->m_nRestrictWidth
		|| point.y > GetDocument()->m_nRestrictHeight)
	{
		return;
	}


	CPen* pOldPen = dc.SelectObject( pDoc->GetCurrentPen( ) );
	//if (m_ptPrev.x!=point.x && m_ptPrev.y!=point.y)
	//{
	//	dc.MoveTo( m_ptPrev );
	//	dc.LineTo( point );
	//}
	if (&m_ptPrev &&
		(m_ptPrev.x > GetDocument()->m_nRestrictWidth || 
		m_ptPrev.y > GetDocument()->m_nRestrictHeight))
		dc.MoveTo( point );
	else
		dc.MoveTo(m_ptPrev);
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

	CPen* pOldPen =
		dc.SelectObject( GetDocument( )->GetCurrentPen( ) );

	// Draw a line from the previous detected point in the mouse
	// drag to the current point.

	if (&m_ptPrev &&
		(m_ptPrev.x > GetDocument()->m_nRestrictWidth || 
		m_ptPrev.y > GetDocument()->m_nRestrictHeight))
		dc.MoveTo( point );
	else
		dc.MoveTo(m_ptPrev);

	if (point.x <= GetDocument()->m_nRestrictWidth && point.y <= GetDocument()->m_nRestrictHeight)
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
/*
Recall that OnInitialUpdate is called immediately after the view is attached to the document. 
This lets the view set its mapping mode before OnDraw is called.
*/
void CScribbleView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes( MM_TEXT, GetDocument()->GetDocSize() );
	
}

void CScribbleView::DocToClient(CPoint& point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(&point);
}

void CScribbleView::DocToClient(CRect& rect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(rect);
	rect.NormalizeRect();
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
	if (!pDoc)
		return;
	TRACE("<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>\n");
	CDC						memDC;
	CDC*					pDrawDC = pDC;
	CBitmap					memBitmap;
	CBitmap*				pMemBitmap = NULL;
	BITMAP					bmpRef;
	CBitmap*				pOldBit = NULL;
	CRect					rectClip;
	pDC->GetClipBox(&rectClip);
	TRACE("0 rectClip >> l:%d,t:%d,r:%d,b:%d\n",rectClip.left, rectClip.top,rectClip.right,rectClip.bottom);
	TRACE("0 rectClip >> w:%d,h:%d\n",rectClip.Width(), rectClip.Height());
	CRect					rect = rectClip;
	DocToClient(rect);

	if (memDC.CreateCompatibleDC(pDC))
	{
		pDrawDC = &memDC;
		pMemBitmap = &memBitmap;
		if (pMemBitmap->CreateCompatibleBitmap(pDC,rect.Width(), rect.Height()))
		{
			pDrawDC = &memDC;
			OnPrepareDC(&memDC);

			TRACE("1 memDC.GetViewportOrg():%d,%d\n",memDC.GetViewportOrg().x,memDC.GetViewportOrg().y);
			TRACE("1 pDC->GetViewportOrg():%d,%d\n",pDC->GetViewportOrg().x,pDC->GetViewportOrg().y);
			memDC.OffsetViewportOrg(-rect.left, -rect.top);
			TRACE("2 memDC.GetViewportOrg():%d,%d\n",memDC.GetViewportOrg().x,memDC.GetViewportOrg().y);
			TRACE("2 pDC->GetViewportOrg():%d,%d\n",pDC->GetViewportOrg().x,pDC->GetViewportOrg().y);

			pOldBit = memDC.SelectObject(pMemBitmap);

			memDC.SetBrushOrg(rect.left % 8, rect.top % 8);	

			CBrush brushBkClient;
			CBrush brushBkgd;
			CRect rcBkCanv;
	
			/*
			* Fill Background
			*/
			brushBkClient.CreateSolidBrush(RGB(255,255,255));
			brushBkClient.UnrealizeObject();			
			memDC.FillRect(&rectClip, &brushBkClient);	
			

			/*
			* Fill drawable area
			*/
			if (GetDocument()->m_bIsBySetting)
			{
				//CRect rcBkCanv(CPoint(0,0),CSize(GetDocument()->m_nRestrictWidth,GetDocument()->m_nRestrictHeight));
				rcBkCanv.SetRect(0,0,GetDocument()->m_nRestrictWidth,GetDocument()->m_nRestrictHeight);
				rcBkCanv.InflateRect(1,1);
				brushBkgd.CreateSolidBrush(GetDocument()->m_CurBkColor);
			}
			else
			{
				GetDocument()->m_BkImg.GetBitmap(&bmpRef);
				//CRect tmp(CPoint(0,0),CSize(bmpRef.bmWidth,bmpRef.bmHeight));//X
				rcBkCanv.SetRect(0,0,bmpRef.bmWidth,bmpRef.bmHeight);
				brushBkgd.CreatePatternBrush(&GetDocument()->m_BkImg);
			}

			brushBkgd.UnrealizeObject();
			memDC.FillRect(&rcBkCanv,&brushBkgd);

			memDC.IntersectClipRect(rectClip);
		}
	}
	
	/*
	* Fill strokes
	*/
	CTypedPtrList<CObList, CStroke*>& strokeList =
		pDoc->m_strokeList;
	POSITION pos = strokeList.GetHeadPosition( );
	while (pos != NULL)
	{
		CStroke* pStroke = strokeList.GetNext(pos);
		CRect rectStroke = pStroke->GetBoundingRect();

		//DocToClient(rectStroke);
		//rectStroke.InflateRect(1, 1);
		//if (!rectStroke.IntersectRect(&rectStroke, &rectClip))
		//	pDrawDC->IntersectClipRect(&rectStroke);

		pStroke->DrawStrokeIn(pDrawDC,GetDocument()->m_nRestrictWidth,GetDocument()->m_nRestrictHeight);
	}

	if (pDrawDC != pDC)
	{
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0,0);
		pDC->SetMapMode(MM_TEXT);
		memDC.SetViewportOrg(0, 0);
		memDC.SetWindowOrg(0,0);
		memDC.SetMapMode(MM_TEXT);
		TRACE("3 rectClip in Client >> l:%d,t:%d,r:%d,b:%d\n",rect.left, rect.top,rect.right,rect.bottom);
		TRACE("3 rectClip in Client >> w:%d,h:%d\n",rect.Width(), rect.Height());
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
			&memDC, 0, 0, SRCCOPY);
		if(pOldBit)
			memDC.SelectObject(pOldBit);
	}	
}


void CScribbleView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	CScrollView::OnPrepareDC(pDC, pInfo);
}

BOOL CScribbleView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return CScrollView::OnEraseBkgnd(pDC);
}
