// CStroke.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "CStroke.h"


// CStroke

IMPLEMENT_DYNAMIC(CStroke, CWnd)

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
		ar << (WORD)m_nPenWidth;
		m_pointArray.Serialize( ar );
	}
	else
	{
		WORD w;
		ar >> w;
		m_nPenWidth = w;
		m_pointArray.Serialize( ar );
	}
}
