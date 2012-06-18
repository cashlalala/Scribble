#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define MAX_SCROLL_WIDTH 20
#define MIN_SCROLL_WIDTH 1

// CPenWidthsDlg dialog

class CPenWidthsDlg : public CDialog
{
	DECLARE_DYNAMIC(CPenWidthsDlg)

public:
	CPenWidthsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPenWidthsDlg();

// Dialog Data
	enum { IDD = IDD_PEN_WIDTHS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDefaultPenWidths();
	//int m_nThinWidth;
	//// int with validation
	//int m_nThickWidth;
protected:
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_ctrSliderThinWidth;
	CString m_sThinWidth;
	CString m_sThickWidth;
	CSliderCtrl m_ctrSliderThickWidth;
	afx_msg void OnEnUpdateThinPenWidth();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};
