#pragma once


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
};
