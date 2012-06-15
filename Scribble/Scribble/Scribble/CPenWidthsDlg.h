#pragma once


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
	int m_nThinWidth;
	// int with validation
	int m_nThickWidth;
};
