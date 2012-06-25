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
	DDX_Control(pDX, IDC_CUR_COLOR, m_CurClr);
}


BEGIN_MESSAGE_MAP(CCanvPropDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_COLOR_PICKER, &CCanvPropDlg::OnBnClickedBtnColorPicker)
	ON_WM_CTLCOLOR()
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
			if (m_pCanvBkBrush.GetSafeHandle())
				m_pCanvBkBrush.DeleteObject();
			m_pCanvBkBrush.CreateSolidBrush(m_dwColorToBeSet);
			return (HBRUSH)m_pCanvBkBrush.GetSafeHandle();
         default:
            return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    }
}
