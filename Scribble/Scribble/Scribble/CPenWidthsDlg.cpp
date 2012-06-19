// CPenWidthsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "CPenWidthsDlg.h"


// CPenWidthsDlg dialog

IMPLEMENT_DYNAMIC(CPenWidthsDlg, CDialog)

CPenWidthsDlg::CPenWidthsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPenWidthsDlg::IDD, pParent)
	, m_nTextBoxThinWidth(0)
	, m_nTextBoxThickWidth(0)
	, m_nThinPenWidth(0)
	, m_nThickPenWidth(0)
{
}

CPenWidthsDlg::CPenWidthsDlg(UINT nThickWidth,UINT nThinWidth)
	: CDialog(CPenWidthsDlg::IDD)
	, m_nThinPenWidth(nThinWidth)
	, m_nThickPenWidth(nThickWidth)
	, m_nTextBoxThickWidth(nThickWidth)
	, m_nTextBoxThinWidth(nThinWidth)
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

	DDX_Text(pDX, IDC_THIN_PEN_WIDTH, m_nTextBoxThinWidth);
	DDX_Control(pDX, IDC_SLIDER_THIN_PEN_WIDTH, m_ctrSliderThinWidth);
	DDX_Text(pDX, IDC_THICK_PEN_WIDTH, m_nTextBoxThickWidth);
	DDX_Control(pDX, IDC_SLIDER_THICK_PEN_WIDTH, m_ctrSliderThickWidth);
	//DDV_MinMaxInt(pDX, m_nTextBoxThinWidth, MIN_SCROLL_WIDTH, MAX_SCROLL_WIDTH);
	//DDV_MinMaxInt(pDX, m_nTextBoxThickWidth, m_nThinPenWidth, MAX_SCROLL_WIDTH);
}


BEGIN_MESSAGE_MAP(CPenWidthsDlg, CDialog)
	ON_BN_CLICKED(IDC_DEFAULT_PEN_WIDTHS, &CPenWidthsDlg::OnBnClickedDefaultPenWidths)
	ON_WM_HSCROLL()
	ON_WM_CHAR()
	ON_EN_CHANGE(IDC_THICK_PEN_WIDTH, &CPenWidthsDlg::OnEnChangeThickPenWidth)
	ON_EN_CHANGE(IDC_THIN_PEN_WIDTH, &CPenWidthsDlg::OnEnChangeThinPenWidth)
END_MESSAGE_MAP()


// CPenWidthsDlg message handlers

void CPenWidthsDlg::OnBnClickedDefaultPenWidths()
{
	InitThickCtrls();
	InitThinCtrls();

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
	m_ctrSliderThinWidth.SetRange(MIN_SCROLL_WIDTH,MAX_SCROLL_WIDTH,TRUE);
	SetValidThinWidth((m_nThinPenWidth)?m_nThinPenWidth:DEFAUT_THIN_VAL);

	m_ctrSliderThickWidth.SetRange(m_nThinPenWidth,MAX_SCROLL_WIDTH,TRUE);
	SetValidThickWidth(m_nThickPenWidth?m_nThickPenWidth:DEFAUT_THICK_VAL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPenWidthsDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == (CScrollBar *) &m_ctrSliderThinWidth)
	{
		SetValidThinWidth(m_ctrSliderThinWidth.GetPos());
	}
	else if (pScrollBar == (CScrollBar *) &m_ctrSliderThickWidth)
	{
		SetValidThickWidth(m_ctrSliderThickWidth.GetPos());
	}
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
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


inline void CPenWidthsDlg::InitThinCtrls()
{
	m_nThickPenWidth = DEFAUT_THICK_VAL;
	m_nTextBoxThinWidth= DEFAUT_THIN_VAL;
	m_ctrSliderThinWidth.SetRange(MIN_SCROLL_WIDTH,MAX_SCROLL_WIDTH,TRUE);
	m_ctrSliderThinWidth.SetPos(m_nTextBoxThinWidth);
}

inline void CPenWidthsDlg::InitThickCtrls()
{
	m_nThickPenWidth = DEFAUT_THIN_VAL;
	m_nTextBoxThickWidth=DEFAUT_THICK_VAL;
	m_ctrSliderThickWidth.SetRange(DEFAUT_THIN_VAL,MAX_SCROLL_WIDTH,TRUE);
	m_ctrSliderThickWidth.SetPos(DEFAUT_THICK_VAL);
}

int CPenWidthsDlg::GetThinWidth() const
{
	return m_nThinPenWidth;
}

int CPenWidthsDlg::GetThickWidth() const
{
	return m_nThickPenWidth;
}

void CPenWidthsDlg::SetValidThinWidth( const int width )
{
	if (width > MAX_SCROLL_WIDTH){
		MessageBox(_T("寬度不能大於20"),_T("警告"));
		return;
	}
	else if (width < MIN_SCROLL_WIDTH)
	{
		MessageBox(_T("寬度不能小於1"),_T("警告"));
		return;
	}
	else
		SetThinWidth(width);
}

void CPenWidthsDlg::SetValidThickWidth( const int width )
{
	if (width < m_nThinPenWidth)
	{
		MessageBox(_T("寬度不能小於Thin Pen!!"),_T("警告"));
		return;
	}
	else if (width > MAX_SCROLL_WIDTH)
	{
		MessageBox(_T("寬度不能大於20!!"),_T("警告"));
		return;
	}
	SetThickWidth(width);	
}

void CPenWidthsDlg::OnEnChangeThickPenWidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	SetValidThickWidth(m_nTextBoxThickWidth);
	UpdateData(FALSE);
}

void CPenWidthsDlg::OnEnChangeThinPenWidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	SetValidThinWidth(m_nTextBoxThinWidth);
	UpdateData(FALSE);
}

void CPenWidthsDlg::SetThinWidth( const int width )
{
	m_nThinPenWidth = width;
	//set all relative thin width
	m_nTextBoxThinWidth = m_nThinPenWidth;
	m_ctrSliderThinWidth.SetPos(m_nThinPenWidth);
	//update thick width 
	if(m_nThinPenWidth>m_nThickPenWidth)
		SetValidThickWidth(m_nThinPenWidth);
	m_ctrSliderThickWidth.SetRangeMin(m_nThinPenWidth,TRUE);
}

void CPenWidthsDlg::SetThickWidth( const int width )
{
	m_nThickPenWidth = width;

	//set all relative thick width
	m_nTextBoxThickWidth = m_nThickPenWidth;
	m_ctrSliderThickWidth.SetPos(m_nThickPenWidth);
}
