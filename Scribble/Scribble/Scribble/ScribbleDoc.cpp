// ScribbleDoc.cpp : CScribbleDoc 類別的實作
//

#include "stdafx.h"
#include "Scribble.h"

#include "ScribbleDoc.h"
#include "CPenWidthsDlg.h"

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
END_MESSAGE_MAP()


// CScribbleDoc 建構/解構

CScribbleDoc::CScribbleDoc()
: m_nPenWidth(0)
{
	// TODO: 在此加入一次建構程式碼

}

CScribbleDoc::~CScribbleDoc()
{
}

BOOL CScribbleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	InitDocument();
	return TRUE;
}




BOOL CScribbleDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	InitDocument();
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
	}
	else
	{
		ar >> m_sizeDoc;
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
	m_penCur.CreatePen( PS_SOLID, m_nPenWidth, RGB(0,0,0) );
	m_bThickPen = FALSE;
	m_nThinWidth = 2;     // Default thin pen is 2 pixels wide
	m_nThickWidth = 5;    // Default thick pen is 5 pixels wide
	// Default document size is 800 x 900 screen pixels.
	m_sizeDoc = CSize(800,900);
}

CStroke* CScribbleDoc::NewStroke(void)
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth);
	m_strokeList.AddTail( pStrokeItem );
	SetModifiedFlag( );    // Mark document as modified
	// to confirm File Close.
	return pStrokeItem;
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

void CScribbleDoc::ReplacePen(void)
{
	m_nPenWidth = m_bThickPen ? m_nThickWidth : m_nThinWidth;
	// Change the current pen to reflect the new width.
	m_penCur.DeleteObject( );
	m_penCur.CreatePen( PS_SOLID, m_nPenWidth, RGB(0,0,0) );
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
	CPenWidthsDlg dlg;
	// Initialize dialog data
	dlg.m_nThinWidth = m_nThinWidth;
	dlg.m_nThickWidth = m_nThickWidth;

	// Invoke the dialog box
	if (dlg.DoModal() == IDOK)
	{
		// retrieve the dialog data
		m_nThinWidth = dlg.m_nThinWidth;
		m_nThickWidth = dlg.m_nThickWidth;

		// Update the pen used by views when drawing new strokes
		// to reflect the new pen widths for "thick" and "thin".
		ReplacePen();
	}
}
