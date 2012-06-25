#pragma once
#include "afxwin.h"


// CCanvPropDlg dialog

class CCanvPropDlg : public CDialog
{
	DECLARE_DYNAMIC(CCanvPropDlg)

public:
	CCanvPropDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCanvPropDlg();

// Dialog Data
	enum { IDD = IDD_CAV_SZ_BG_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnColorPicker();
	int m_nCanvHeight;
	int m_nCanvWidth;
	CStatic m_CurClr;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush m_pCanvBkBrush;
	COLORREF m_dwColorToBeSet;
};
