// CStroke.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "CStroke.h"


// CStroke
IMPLEMENT_SERIAL(CStroke,CObject,3)

CStroke::CStroke()
: m_nPenWidth(0)
{

}

CStroke::~CStroke()
{
}


BEGIN_MESSAGE_MAP(CStroke, CWnd)
END_MESSAGE_MAP()



// CStroke message handlers



CStroke::CStroke(UINT nPenWidth)
{
	m_nPenWidth = nPenWidth;
	m_rectBounding.SetRectEmpty();
}

// operations
BOOL CStroke::DrawStroke( CDC* pDC )
{
	CPen penStroke;
	if( !penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)))
		return FALSE;

	CPen* pOldPen = pDC->SelectObject( &penStroke );

	pDC->MoveTo( m_pointArray[0] );
	for( int i=1; i < m_pointArray.GetSize(); i++ )
	{
		pDC->LineTo( m_pointArray[i] );
	}
	pDC->SelectObject( pOldPen );
	return TRUE;
}

void CStroke::Serialize(CArchive& ar)
{
	if( ar.IsStoring( ) )
	{
		ar << m_rectBounding;
		ar << (WORD)m_nPenWidth;
		m_pointArray.Serialize( ar );
	}
	else
	{
		ar >> m_rectBounding;
		WORD w;
		ar >> w;
		m_nPenWidth = w;
		m_pointArray.Serialize( ar );
	}
}

void CStroke::FinishStroke(void)
{
	if( m_pointArray.GetSize() == 0 )
	{
		m_rectBounding.SetRectEmpty();
		return;
	}
	CPoint pt = m_pointArray[0];
	m_rectBounding = CRect( pt.x, pt.y, pt.x, pt.y );

	for (int i=1; i < m_pointArray.GetSize(); i++)
	{
		// If the point lies outside of the accumulated bounding
		// rectangle, then inflate the bounding rect to include it.
		pt = m_pointArray[i];
		m_rectBounding.left   = min(m_rectBounding.left, pt.x);
		m_rectBounding.right  = max(m_rectBounding.right, pt.x);
		m_rectBounding.top    = min(m_rectBounding.top, pt.y);
		m_rectBounding.bottom = max(m_rectBounding.bottom, pt.y);
	}

	// Add the pen width to the bounding rectangle.  This is needed
	// to account for the width of the stroke when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth,-(int) m_nPenWidth));
	return;
}

BOOL CStroke::DrawStrokeIn( CDC* pDC, int nRestricWidth, int nRestricHeight )
{
	CPen penStroke;
	if( !penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)))
		return FALSE;

	CPen* pOldPen = pDC->SelectObject( &penStroke );

	CPoint prev = m_pointArray[0];

	pDC->MoveTo( m_pointArray[0] );
	for( int i=1; i < m_pointArray.GetSize(); i++ )
	{
		if (m_pointArray[i].x>nRestricWidth || m_pointArray[i].y > nRestricHeight)
		{
			prev = m_pointArray[i];
			continue;
		}

		if (prev.x>nRestricWidth || prev.y > nRestricHeight)
		{
			pDC->MoveTo(m_pointArray[i]);
		}
		pDC->LineTo( m_pointArray[i] );
		prev = m_pointArray[i];
	}
	pDC->SelectObject( pOldPen );
	return TRUE;
}
