// CanvPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "CanvPropDlg.h"


// CCanvPropDlg dialog

IMPLEMENT_DYNAMIC(CCanvPropDlg, CDialog)

CCanvPropDlg::CCanvPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCanvPropDlg::IDD, pParent)
	, m_nCanvHeight(0)
	, m_nCanvWidth(0)
	, m_szBkImgPath(_T(""))
{
	m_dwColorToBeSet = RGB(0,0,0);
}

CCanvPropDlg::~CCanvPropDlg()
{
}

void CCanvPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CANV_HEIGHT, m_nCanvHeight);
	DDV_MinMaxInt(pDX, m_nCanvHeight, 0, 1500);
	DDX_Text(pDX, IDC_EDIT_CANV_WIDTH, m_nCanvWidth);
	DDV_MinMaxInt(pDX, m_nCanvWidth, 0, 1500);
	DDX_Control(pDX, IDC_CUR_COLOR, m_ctlCurColor);
	DDX_Text(pDX, IDC_EDIT_BK_IMG_PATH, m_szBkImgPath);
	DDX_Control(pDX, IDC_EDIT_CANV_HEIGHT, m_ctlCanvHeight);
	DDX_Control(pDX, IDC_EDIT_CANV_WIDTH, m_ctlCanvWidth);
	DDX_Control(pDX, IDC_BTN_COLOR_PICKER, m_ctlCurClrPicker);
}


BEGIN_MESSAGE_MAP(CCanvPropDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_COLOR_PICKER, &CCanvPropDlg::OnBnClickedBtnColorPicker)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_SELECT_PATH, &CCanvPropDlg::OnBnClickedButtonSelectPath)
	ON_BN_CLICKED(IDC_BUTTON_CLR_PATH, &CCanvPropDlg::OnBnClickedButtonClrPath)
	ON_EN_CHANGE(IDC_EDIT_BK_IMG_PATH, &CCanvPropDlg::OnEnChangeEditBkImgPath)
END_MESSAGE_MAP()


// CCanvPropDlg message handlers

void CCanvPropDlg::OnBnClickedBtnColorPicker()
{
	// TODO: Add your control notification handler code here
	CColorDialog clrDlg;
	if (clrDlg.DoModal()==IDOK)
	{
		m_dwColorToBeSet = clrDlg.GetColor();
		Invalidate();
	}
}

HBRUSH CCanvPropDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch (pWnd->GetDlgCtrlID()) 
	{
		case IDC_CUR_COLOR:
			if (m_CanvBkBrush.GetSafeHandle())
				m_CanvBkBrush.DeleteObject();
			m_CanvBkBrush.CreateSolidBrush(m_dwColorToBeSet);
			return (HBRUSH)m_CanvBkBrush.GetSafeHandle();
         default:
            return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    }
}

void CCanvPropDlg::OnBnClickedButtonSelectPath()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE);
	if (fileDlg.DoModal() == IDOK)
	{
		m_szBkImgPath = fileDlg.GetFolderPath() + _T("\\") + fileDlg.GetFileName();
		UpdateData(FALSE);
		OnEnChangeEditBkImgPath();
	}
}

void CCanvPropDlg::OnBnClickedButtonClrPath()
{
	// TODO: Add your control notification handler code here
	m_szBkImgPath.Empty();
	UpdateData(FALSE);
	OnEnChangeEditBkImgPath();
}

void CCanvPropDlg::OnEnChangeEditBkImgPath()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	if (m_szBkImgPath.IsEmpty())
	{
		m_ctlCanvHeight.EnableWindow(TRUE);
		m_ctlCanvWidth.EnableWindow(TRUE);
		m_ctlCurColor.EnableWindow(TRUE);
		m_ctlCurClrPicker.EnableWindow(TRUE);
	}
	else
	{
		m_ctlCanvHeight.EnableWindow(FALSE);
		m_ctlCanvWidth.EnableWindow(FALSE);
		m_ctlCurColor.EnableWindow(FALSE);
		m_ctlCurClrPicker.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}
BOOL CCanvPropDlg::IsBySetting(void)
{
	return m_szBkImgPath.IsEmpty();
}
