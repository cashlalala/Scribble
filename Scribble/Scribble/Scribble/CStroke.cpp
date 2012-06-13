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
	return false;
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
