#pragma once


// CPenClrDlg dialog

class CPenClrDlg : public CDialog
{
	DECLARE_DYNAMIC(CPenClrDlg)

public:
	CPenClrDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPenClrDlg();

// Dialog Data
	enum { IDD = IDD_PEN_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT m_nPenClrBlue;
	UINT m_nPenClrGreen;
	UINT m_nPenClrRed;
	afx_msg void OnBnClickedOk();
};
