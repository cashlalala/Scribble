// ScribbleDoc.cpp : CScribbleDoc ���O����@
//

#include "stdafx.h"
#include "Scribble.h"

#include "ScribbleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScribbleDoc

IMPLEMENT_DYNCREATE(CScribbleDoc, CDocument)

BEGIN_MESSAGE_MAP(CScribbleDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CScribbleDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CScribbleDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()


// CScribbleDoc �غc/�Ѻc

CScribbleDoc::CScribbleDoc()
: m_nPenWidth(0)
{
	// TODO: �b���[�J�@���غc�{���X

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

// CScribbleDoc �ǦC��

void CScribbleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �b���[�J�x�s�{���X
	}
	else
	{
		// TODO: �b���[�J���J�{���X
	}
	m_strokeList.Serialize( ar );
}


CPen* CScribbleDoc::GetCurrentPen()
{
	return &m_penCur;
}


// CScribbleDoc �E�_

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


// CScribbleDoc �R�O

void CScribbleDoc::InitDocument(void)
{
	m_nPenWidth = 2;  // Default 2-pixel pen width
	// Solid black pen
	m_penCur.CreatePen( PS_SOLID, m_nPenWidth, RGB(0,0,0) );
}

CStroke* CScribbleDoc::NewStroke(void)
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth);
	m_strokeList.AddTail( pStrokeItem );
	SetModifiedFlag( );    // Mark document as modified
	// to confirm File Close.
	return pStrokeItem;
}
