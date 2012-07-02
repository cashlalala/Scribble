// ScribbleDoc.cpp : CScribbleDoc 類別的實作
//

#include "stdafx.h"
#include "Scribble.h"

#include "ScribbleDoc.h"
#include "CPenWidthsDlg.h"
#include "CPenClrDlg.h"
#include "CanvPropDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScribbleDoc

IMPLEMENT_DYNCREATE(CScribbleDoc, CDocument)

BEGIN_MESSAGE_MAP(CScribbleDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CScribbleDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CScribbleDoc::OnUpdateFileSendMail)
	ON_COMMAND(ID_EDIT_C, &CScribbleDoc::OnEditClearAll)
	ON_COMMAND(ID_PEN_THICK_OR_THIN, &CScribbleDoc::OnPenThickOrThin)
	ON_UPDATE_COMMAND_UI(ID_EDIT_C, &CScribbleDoc::OnUpdateEditC)
	ON_UPDATE_COMMAND_UI(ID_PEN_THICK_OR_THIN, &CScribbleDoc::OnUpdatePenThickOrThin)
	ON_COMMAND(ID_PEN_WIDTHS, &CScribbleDoc::OnPenWidths)
	ON_COMMAND(ID_PEN_COLOR, &CScribbleDoc::OnPenColor)
END_MESSAGE_MAP()


// CScribbleDoc 建構/解構

CScribbleDoc::CScribbleDoc()
: m_nPenWidth(0)
, m_nRestrictWidth(0)
, m_nRestrictHeight(0)
, m_bIsBySetting(false)
, m_bThickPen(false)
, m_nThickWidth(2)
, m_nThinWidth(5)
{
	m_rgbPenCurColor = m_rgbCurBkColor = RGB(0,0,0);
}

CScribbleDoc::~CScribbleDoc()
{
}

BOOL CScribbleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	InitDocument();

	CCanvPropDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		if (dlg.IsBySetting())
		{
			m_nRestrictHeight = dlg.m_nCanvHeight;
			m_nRestrictWidth = dlg.m_nCanvWidth;
			m_rgbCurBkColor = dlg.m_dwColorToBeSet;
			m_bIsBySetting = true;
		}
		else
		{
			//HBITMAP hBmp = (HBITMAP)::LoadImage(NULL,dlg.m_szBkImgPath,
			//									IMAGE_BITMAP,0,0,
			//									LR_LOADFROMFILE|LR_CREATEDIBSECTION);
			m_bmpBkImg.LoadBitMapFromFile(dlg.m_szBkImgPath);
			m_bIsBySetting = false;
			m_nRestrictHeight = m_bmpBkImg.GetHeightPixel();
			m_nRestrictWidth = m_bmpBkImg.GetWidthPixel();
		}
	}
	else
		return FALSE;
	return TRUE;
}




BOOL CScribbleDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	//InitDocument();

	/*
	* Serialization is implemented in CDocument::OnOpenDocument(lpszPathName)
	* most of member var is initialized via the serialization function except
	* the current pen
	*/
	CScribbleApp* pApp = (CScribbleApp*)AfxGetApp();

	CString sRegistryName = CString(pApp->m_pszUserSettingSection) + _T("\\") + this->GetDocName(lpszPathName);

	m_penCur.CreatePen(PS_SOLID,m_nPenWidth,m_rgbPenCurColor);
	m_rgbCurBkColor = pApp->GetProfileInt(sRegistryName,pApp->m_pszCanvasBkgColor,0);
	m_nRestrictHeight = pApp->GetProfileInt(sRegistryName,pApp->m_pszRestrictCanvasHeight,0);
	m_nRestrictWidth = pApp->GetProfileInt(sRegistryName,pApp->m_pszRestrictCanvasWidth,0);
	m_nThickWidth = pApp->GetProfileInt(sRegistryName,pApp->m_pszThickPenWidth,0);
	m_nThinWidth = pApp->GetProfileInt(sRegistryName,pApp->m_pszThinPenWidth,0);

	//m_penCur.CreatePen(PS_SOLID,m_nPenWidth,m_rgbPenCurColor);
	//m_CurBkColor = pApp->GetProfileInt(pApp->m_pszUserSettingSection,pApp->m_pszCanvasBkgColor,0);
	//m_nRestrictHeight = pApp->GetProfileInt(pApp->m_pszUserSettingSection,pApp->m_pszRestrictCanvasHeight,0);
	//m_nRestrictWidth = pApp->GetProfileInt(pApp->m_pszUserSettingSection,pApp->m_pszRestrictCanvasWidth,0);
	//m_nThickWidth = pApp->GetProfileInt(pApp->m_pszUserSettingSection,pApp->m_pszThickPenWidth,0);
	//m_nThinWidth = pApp->GetProfileInt(pApp->m_pszUserSettingSection,pApp->m_pszThinPenWidth,0);
	
	return TRUE;
}

// Called on File/Close

void CScribbleDoc::DeleteContents()
{
	while( !m_strokeList.IsEmpty( ) )
	{
		delete m_strokeList.RemoveHead( );
	}

	CDocument::DeleteContents();
}

// CScribbleDoc 序列化

void CScribbleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_sizeDoc;
		ar << m_bThickPen;
		ar << m_nPenWidth;
		ar << m_bIsBySetting;
		ar << m_bmpBkImg.m_szFilePath;
		ar << m_rgbPenCurColor;
	}
	else
	{
		ar >> m_sizeDoc;
		ar >> m_bThickPen;
		ar >> m_nPenWidth;
		ar >> m_bIsBySetting;
		ar >> m_bmpBkImg.m_szFilePath;
		ar >> m_rgbPenCurColor;
		if (!m_bmpBkImg.m_szFilePath.IsEmpty())
			m_bmpBkImg.LoadBitMapFromFile();
	}
	m_strokeList.Serialize( ar );
}


CPen* CScribbleDoc::GetCurrentPen()
{
	return &m_penCur;
}


// CScribbleDoc 診斷

#ifdef _DEBUG
void CScribbleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScribbleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}


#endif //_DEBUG


// CScribbleDoc 命令

void CScribbleDoc::InitDocument(void)
{
	m_nPenWidth = 2;  // Default 2-pixel pen width
	// Solid black pen
	m_penCur.CreatePen( PS_SOLID, m_nPenWidth, m_rgbPenCurColor );
	m_bThickPen = FALSE;
	m_nThinWidth = 2;     // Default thin pen is 2 pixels wide
	m_nThickWidth = 5;    // Default thick pen is 5 pixels wide
	// Default document size is 800 x 900 screen pixels.
	m_sizeDoc = CSize(800,900);
}

CStroke* CScribbleDoc::NewStroke(void)
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth,m_rgbPenCurColor);
	m_strokeList.AddTail( pStrokeItem );
	SetModifiedFlag( );    // Mark document as modified
	// to confirm File Close.
	return pStrokeItem;
}

void CScribbleDoc::ReplacePen(void)
{
	m_nPenWidth = m_bThickPen ? m_nThickWidth : m_nThinWidth;
	// Change the current pen to reflect the new width.
	m_penCur.DeleteObject( );
	m_penCur.CreatePen( PS_SOLID, m_nPenWidth, m_rgbPenCurColor );
}

void CScribbleDoc::OnEditClearAll()
{
	DeleteContents( );
	SetModifiedFlag();
	UpdateAllViews( NULL );
}

void CScribbleDoc::OnPenThickOrThin()
{
	// Toggle the state of the pen between thin and thick.
	m_bThickPen = !m_bThickPen;

	// Change the current pen to reflect the new width.
	ReplacePen( );
}

void CScribbleDoc::OnUpdateEditC(CCmdUI *pCmdUI)
{
	// Enable the user-interface object (menu item or tool-
	// bar button) if the document is non-empty, i.e., has
	// at least one stroke.
	pCmdUI->Enable( !m_strokeList.IsEmpty( ) );
}

void CScribbleDoc::OnUpdatePenThickOrThin(CCmdUI *pCmdUI)
{
	// Add check mark to Pen Thick Line menu item if the current
	// pen width is "thick."
	pCmdUI->SetCheck( m_bThickPen );
}

void CScribbleDoc::OnPenWidths()
{
	CPenWidthsDlg dlg(m_nThickWidth,m_nThinWidth);

	// Invoke the dialog box
	if (dlg.DoModal() == IDOK)
	{
		// retrieve the dialog data
		m_nThinWidth = dlg.GetThinWidth();
		m_nThickWidth = dlg.GetThickWidth();

		// Update the pen used by views when drawing new strokes
		// to reflect the new pen widths for "thick" and "thin".
		ReplacePen();
	}
}

void CScribbleDoc::OnPenColor()
{
	CPenClrDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		m_penCur.DeleteObject();
		m_rgbPenCurColor = RGB(dlg.m_nPenClrRed,dlg.m_nPenClrGreen,dlg.m_nPenClrBlue);
		m_penCur.CreatePen( PS_SOLID, m_nPenWidth, m_rgbPenCurColor );
	}
}


void CScribbleDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	CScribbleApp* pApp = (CScribbleApp*)AfxGetApp();

	CString sRegistryName = CString(pApp->m_pszUserSettingSection) + _T("\\") + this->GetDocName();

	pApp->WriteProfileInt(sRegistryName,pApp->m_pszThickPenWidth,m_nThickWidth);
	pApp->WriteProfileInt(sRegistryName,pApp->m_pszThinPenWidth,m_nThinWidth);
	pApp->WriteProfileInt(sRegistryName,pApp->m_pszRestrictCanvasWidth,m_nRestrictWidth);
	pApp->WriteProfileInt(sRegistryName,pApp->m_pszRestrictCanvasHeight,m_nRestrictHeight);
	pApp->WriteProfileInt(sRegistryName,pApp->m_pszCanvasBkgColor,m_rgbCurBkColor);

	//pApp->WriteProfileInt(pApp->m_pszUserSettingSection,pApp->m_pszThickPenWidth,m_nThickWidth);
	//pApp->WriteProfileInt(pApp->m_pszUserSettingSection,pApp->m_pszThinPenWidth,m_nThinWidth);
	//pApp->WriteProfileInt(pApp->m_pszUserSettingSection,pApp->m_pszRestrictCanvasWidth,m_nRestrictWidth);
	//pApp->WriteProfileInt(pApp->m_pszUserSettingSection,pApp->m_pszRestrictCanvasHeight,m_nRestrictHeight);
	//pApp->WriteProfileInt(pApp->m_pszUserSettingSection,pApp->m_pszCanvasBkgColor,m_CurBkColor);

	CDocument::OnCloseDocument();
}

CString CScribbleDoc::GetDocName(CString sCurPathName)
{
	CString sDocName;
	int nTokPos = 0;
	CString sPathName = (sCurPathName.IsEmpty())? this->GetPathName() : sCurPathName;
	CString sTok = sPathName.Tokenize(_T("\\"),nTokPos);
	while (!sTok.IsEmpty())
	{
		sDocName = sTok;
		sTok = sPathName.Tokenize(_T("\\"),nTokPos);
	}
	return sDocName;
}
