#pragma once
#include "afxwin.h"


// CStroke

class CStroke : public CWnd
{
	DECLARE_SERIAL(CStroke)

public:
	CStroke(UINT nPenWidth,COLORREF dwCurColor);
	CStroke();
	virtual ~CStroke();

	// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()

	// Attributes
public:
	unsigned int m_nPenWidth;
public:
	CArray<CPoint,CPoint> m_pointArray;
protected:
	CRect m_rectBounding;  // smallest rect that surrounds all
	// of the points in the stroke
	
	// operations
	virtual void Serialize(CArchive& ar);
public:
	BOOL DrawStroke(CDC* pDC);

public:
	CRect& GetBoundingRect() { return m_rectBounding; }

protected:
public:
	void FinishStroke();
	BOOL DrawStrokeIn(CDC* pDC, int nRestricWidth, int nRestricHeight);

	COLORREF m_rgbPenColor;
};


