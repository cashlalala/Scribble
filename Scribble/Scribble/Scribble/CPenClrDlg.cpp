// CPenClrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "CPenClrDlg.h"


// CPenClrDlg dialog

IMPLEMENT_DYNAMIC(CPenClrDlg, CDialog)

CPenClrDlg::CPenClrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPenClrDlg::IDD, pParent)
	, m_nPenClrBlue(0)
	, m_nPenClrGreen(0)
	, m_nPenClrRed(0)
{

}

CPenClrDlg::~CPenClrDlg()
{
}

void CPenClrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PEN_CLR_BLUE, m_nPenClrBlue);
	DDV_MinMaxUInt(pDX, m_nPenClrBlue, 0, 255);
	DDX_Text(pDX, IDC_EDIT_PEN_CLR_GREEN, m_nPenClrGreen);
	DDV_MinMaxUInt(pDX, m_nPenClrGreen, 0, 255);
	DDX_Text(pDX, IDC_EDIT_PEN_CLR_RED, m_nPenClrRed);
	DDV_MinMaxUInt(pDX, m_nPenClrRed, 0, 255);
}


BEGIN_MESSAGE_MAP(CPenClrDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPenClrDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPenClrDlg message handlers

void CPenClrDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	OnOK();
}
