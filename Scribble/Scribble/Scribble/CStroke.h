#pragma once
#include "afxwin.h"


// CStroke

class CStroke : public CWnd
{
	DECLARE_DYNAMIC(CStroke)

public:
	CStroke(UINT nPenWidth);
	CStroke();
	virtual ~CStroke();

	// ���ͪ��T�������禡
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


