// CPenWidthsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "CPenWidthsDlg.h"


// CPenWidthsDlg dialog

IMPLEMENT_DYNAMIC(CPenWidthsDlg, CDialog)

CPenWidthsDlg::CPenWidthsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPenWidthsDlg::IDD, pParent)
	, m_sThinWidth(_T(""))
	, m_sThickWidth(_T(""))
{
}

CPenWidthsDlg::~CPenWidthsDlg()
{
}

/*
// The DoDataExchange function is implemented using DDX and DDV function calls. 
// A DDX (for Dialog Data eXchange) function specifies which control in the dialog 
// box corresponds to a particular member variable and transfers the data between 
// the two. A DDV (for Dialog Data Validation) function specifies the validation 
// parameters for a particular member variable, ensuring that its value is legal. 
// The DDX and DDV function calls shown in PenWidthsDlg.cpp reflect the mapping 
// and validation parameters you specified with ClassWizard.
*/
void CPenWidthsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	/*DDX_Text(pDX, IDC_THIN_PEN_WIDTH, m_nThinWidth);
	DDV_MinMaxInt(pDX, m_nThinWidth, 1, 20);
	DDX_Text(pDX, IDC_THICK_PEN_WIDTH, m_nThickWidth);
	DDV_MinMaxInt(pDX, m_nThickWidth, 1, 20);*/
	DDX_Text(pDX, IDC_THIN_PEN_WIDTH, m_sThinWidth);
	DDV_MinMaxInt(pDX, _ttoi(m_sThinWidth), 1, 20);
	DDX_Control(pDX, IDC_SLIDER_THIN_PEN_WIDTH, m_ctrSliderThinWidth);
	DDX_Text(pDX, IDC_THICK_PEN_WIDTH, m_sThickWidth);
	DDV_MinMaxInt(pDX, _ttoi(m_sThickWidth), 1, 20);
	DDX_Control(pDX, IDC_SLIDER_THICK_PEN_WIDTH, m_ctrSliderThickWidth);
}


BEGIN_MESSAGE_MAP(CPenWidthsDlg, CDialog)
	ON_BN_CLICKED(IDC_DEFAULT_PEN_WIDTHS, &CPenWidthsDlg::OnBnClickedDefaultPenWidths)
	ON_WM_HSCROLL()
	ON_EN_UPDATE(IDC_THIN_PEN_WIDTH, &CPenWidthsDlg::OnEnUpdateThinPenWidth)
	ON_WM_CHAR()
END_MESSAGE_MAP()


// CPenWidthsDlg message handlers

void CPenWidthsDlg::OnBnClickedDefaultPenWidths()
{
	m_sThinWidth.Format(_T("%d"),2);
	m_sThickWidth.Format(_T("%d"),5);

	/************************************************************************/
	/* The UpdateData member function calls the DoDataExchange function 
	to move values between the member variables and the controls displayed
	on the screen. The direction in which the data values are moved is specified
	by the argument to UpdateData. The default value of this argument is TRUE,
	which moves data from the controls to the member variables. A value of FALSE 
	moves data from the member variables to the controls. The OnDefaultPenWidths
	member function passes FALSE, causing the default values to be displayed in 
	the edit boxes on the screen                                                                     */
	/************************************************************************/
	UpdateData(FALSE);  // causes DoDataExchange()
	// bSave=FALSE means don't save from screen, rather, write
	// to screen
}


BOOL CPenWidthsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Initialize scroll bar position one time
	if (!m_ctrSliderThickWidth.GetPos()){
		m_ctrSliderThickWidth.SetRange(MIN_SCROLL_WIDTH,MAX_SCROLL_WIDTH,TRUE);
		m_ctrSliderThickWidth.SetPos(1);
	}
	if (!m_ctrSliderThinWidth.GetPos()){
		m_ctrSliderThinWidth.SetRange(MIN_SCROLL_WIDTH,MAX_SCROLL_WIDTH,TRUE);
		m_ctrSliderThinWidth.SetPos(1);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPenWidthsDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == (CScrollBar *) &m_ctrSliderThinWidth)
	{
		m_sThinWidth.Format(_T("%d"),m_ctrSliderThinWidth.GetPos());
		m_ctrSliderThickWidth.SetRangeMin(m_ctrSliderThinWidth.GetPos(),TRUE);
		if(m_ctrSliderThinWidth.GetPos()>m_ctrSliderThickWidth.GetPos())
			m_ctrSliderThickWidth.SetPos(m_ctrSliderThinWidth.GetPos());
		UpdateData(FALSE);
	}
	else if (pScrollBar == (CScrollBar *) &m_ctrSliderThickWidth)
	{
		m_sThickWidth.Format(_T("%d"),m_ctrSliderThickWidth.GetPos());
		UpdateData(FALSE);
	}
	else{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
	
}


void CPenWidthsDlg::OnEnUpdateThinPenWidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	TCHAR buf[512]; memset(buf,0,512);
	m_ctrSliderThinWidth.GetWindowText( buf, sizeof( buf ) / sizeof(TCHAR) );

	m_sThinWidth.Format(_T("%d"),_ttoi(buf));
	m_ctrSliderThinWidth.SetPos(_ttoi(m_sThinWidth));
	UpdateData(FALSE);
}

void CPenWidthsDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	BOOL alpha = IsCharAlpha( (TCHAR)nChar );
	if (alpha)
		MessageBeep((UINT)-1);
	else
		CDialog::OnChar(nChar, nRepCnt, nFlags);
}
