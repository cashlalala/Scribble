// CPenWidthsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scribble.h"
#include "CPenWidthsDlg.h"


// CPenWidthsDlg dialog

IMPLEMENT_DYNAMIC(CPenWidthsDlg, CDialog)

CPenWidthsDlg::CPenWidthsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPenWidthsDlg::IDD, pParent)
	, m_nThinWidth(0)
	, m_nThickWidth(0)
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
	DDX_Text(pDX, IDC_THIN_PEN_WIDTH, m_nThinWidth);
	DDV_MinMaxInt(pDX, m_nThinWidth, 1, 20);
	DDX_Text(pDX, IDC_THICK_PEN_WIDTH, m_nThickWidth);
	DDV_MinMaxInt(pDX, m_nThickWidth, 1, 20);
}


BEGIN_MESSAGE_MAP(CPenWidthsDlg, CDialog)
	ON_BN_CLICKED(IDC_DEFAULT_PEN_WIDTHS, &CPenWidthsDlg::OnBnClickedDefaultPenWidths)
END_MESSAGE_MAP()


// CPenWidthsDlg message handlers

void CPenWidthsDlg::OnBnClickedDefaultPenWidths()
{
	m_nThinWidth = 2;
	m_nThickWidth = 5;

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
