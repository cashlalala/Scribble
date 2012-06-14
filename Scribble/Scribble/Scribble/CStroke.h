#pragma once
#include "afxwin.h"


// CStroke

class CStroke : public CWnd
{
	DECLARE_SERIAL(CStroke)

public:
	CStroke(UINT nPenWidth);
	CStroke();
	virtual ~CStroke();

	// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()

	// Attributes
	unsigned int m_nPenWidth;
public:
	CArray<CPoint,CPoint> m_pointArray;
	
	// operations
	BOOL DrawStroke(CDC* pDC);
	virtual void Serialize(CArchive& ar);

protected:
};


