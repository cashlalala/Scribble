#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define MAX_SCROLL_WIDTH 20
#define MIN_SCROLL_WIDTH 1

#define DEFAUT_THIN_VAL		2 
#define DEFAUT_THICK_VAL	5


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
	int m_nThinWidth;
	int m_nThickWidth;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDefaultPenWidths();
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_ctrSliderThinWidth;
	CSliderCtrl m_ctrSliderThickWidth;
	afx_msg void OnEnUpdateThinPenWidth();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
//public:
//	void DoSyncUpdateData(UINT id);
//	void SyncDataForView(UINT id);
public:
	inline void InitThinCtrls();
	inline void InitThickCtrls();
	int GetThinWidth() const;
	void SetThinWidth(const int width);
	int GetThickWidth() const;
	void SetThickWidth(const int width);
	afx_msg void OnEnUpdateThickPenWidth();
};
